#pragma once

#include <qc-core/bubble-tracker.hpp>
#include <qc-core/list.hpp>
#include <qc-core/paging.hpp>
#include <qc-core/smart-pointer.hpp>

namespace qc
{
    ///
    /// ...
    /// Each element in the arena is stored with a leading 8 byte header. Of this, the lower four bytes are used to
    ///   store the size of the value, and the upper four bytes are left empty for other uses. `Shr` uses these upper
    ///   four bytes to reference count, for example.
    ///
    class Arena
    {
      public:

        Arena() = default;
        explicit Arena(u64 capacity);

        Arena(const Arena &) = delete;
        Arena(Arena && other);

        Arena & operator=(const Arena &) = delete;
        Arena & operator=(Arena && other);

        ~Arena();

        void setCapacity(u64 capacity);

        template <typename T, typename... Args> nodisc T & create(Args && ... args);

        template <typename T, typename... Args> nodisc Unq<T> createUnique(Args && ... args);

        template <typename T, typename... Args> nodisc Shr<T> createShared(Args && ... args);

        template <typename T> void destroy(T & v);

        void shrinkToFit();

        nodisc u64 capacity() const { return _capacity; }

        nodisc u64 size() const { return _size; }

        nodisc bool empty() const { return !_size; }

      private:

        inline static List<Arena *> _arenas{};

        template <typename T> static void _destroy(T & v);

        u64 _capacity{};
        u64 _size{};
        u64 * _memory{};
        BubbleTracker<u64 *> _bubbles{};

        void _expand(u64 newSize);
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    inline Arena::Arena(const u64 capacity)
    {
        setCapacity(capacity);
    }

    inline Arena::Arena(Arena && other) :
        _capacity{std::exchange(other._capacity, 0u)},
        _size{std::exchange(other._size, 0u)},
        _memory{std::exchange(other._memory, nullptr)},
        _bubbles{std::move(other._bubbles)}
    {}

    inline auto Arena::operator=(Arena && other) -> Arena &
    {
        if (&other == this)
        {
            return *this;
        }

        _capacity = std::exchange(other._capacity, 0u);
        _size = std::exchange(other._size, 0u);
        _memory = std::exchange(other._memory, nullptr);
        _bubbles = std::move(other._bubbles);

        return *this;
    }

    inline Arena::~Arena()
    {
        if (_memory)
        {
            // Check for dangling references
            if constexpr (debug)
            {
                assert(_bubbles.bubbles().size() == 1u);

                const auto & bubble{_bubbles.bubbles().front()};
                assert(bubble.pos == _memory && u64(bubble.size) * 8u == _capacity);
            }

            freePages(_memory);

            // Remove self from sorted arena list
            auto it{_arenas.begin()};
            for (; (*it)->_memory != _memory; ++it);
            _arenas.erase(it);
        }

        if constexpr (debug)
        {
            _capacity = 0u;
            _size = 0u;
            _memory = nullptr;
        }
    }

    inline void Arena::setCapacity(const u64 capacity)
    {
        // May only be called before memory is reserved
        if (_memory)
        {
            assert(false);
            return;
        }

        const u64 pageCount{std::bit_ceil((capacity + (pageSize - 1u)) / pageSize)};
        _capacity = pageCount * pageSize;
        _memory = static_cast<u64 *>(reservePages(pageCount));
        _bubbles.add(_memory, s64(_capacity / 8u));

        // Insert self into sorted arena list
        auto it{_arenas.begin()};
        for (; it != _arenas.end() && (*it)->_memory < _memory; ++it);
        _arenas.insert(it, this);
    }

    template <typename T, typename... Args>
    inline T & Arena::create(Args &&... args)
    {
        static_assert(alignof(T) <= 8u);

        const u64 wordCount{1u + (sizeof(T) + 7u) / 8u};
        const auto [wasSpace, ptr]{_bubbles.remove(wordCount)};

        // Arena is full
        ABORT_IF(!wasSpace);

        const u64 requiredSize{(u64(ptr - _memory) + wordCount) * 8u};
        if (requiredSize > _size)
        {
            _expand(requiredSize);
        }

        *ptr = sizeof(T); // Assuming value size will always fit in first four bytes; upper four must be 0
        return *(new (ptr + 1) T{std::forward<Args>(args)...});
    }

    template <typename T, typename... Args>
    inline Unq<T> Arena::createUnique(Args &&... args)
    {
        return Unq<T>{
            &create<T>(std::forward<Args>(args)...),
            [](void * const ptr) { _destroy(*static_cast<T *>(ptr)); }};
    }

    template <typename T, typename... Args>
    inline Shr<T> Arena::createShared(Args &&... args)
    {
        return Shr<T>{
            &create<T>(std::forward<Args>(args)...),
            [](void * const ptr) { _destroy(*static_cast<T *>(ptr)); }};
    }

    template <typename T>
    inline void Arena::destroy(T & v)
    {
        v.~T();

        u64 * const ptr{reinterpret_cast<u64 *>(&v) - 1};
        const u32 valSize{u32(*ptr & 0xFFFFFFFFu)};
        const u64 wordCount{1u + (valSize + 7u) / 8u};
        _bubbles.add(ptr, s64(wordCount));
    }

    inline void Arena::shrinkToFit()
    {
        const u64 freeTailSize{u64(_bubbles.tail(_memory + _capacity / 8u)) * 8u};

        // Arena is unallocated or full
        if (!freeTailSize)
        {
            return;
        }

        u64 necessaryPageCount{(_capacity - freeTailSize + (pageSize - 1u)) / pageSize};
        if (necessaryPageCount) necessaryPageCount = std::bit_ceil(necessaryPageCount);
        const u64 currentPageCount{(_size + (pageSize - 1u)) / pageSize};
        const u64 unnecessaryPageCount{currentPageCount - necessaryPageCount};

        // Free tail is smaller than hald the current size
        if (!unnecessaryPageCount)
        {
            return;
        }

        // Decommit uneccessary pages
        decommitPages(reinterpret_cast<std::byte *>(_memory) + necessaryPageCount * pageSize, unnecessaryPageCount);

        _size = necessaryPageCount * pageSize;
    }

    template <typename T>
    inline void Arena::_destroy(T & v)
    {
        static const auto comp{[](Arena * const arena, const T & val)
        {
            const std::byte * const arenaEnd{reinterpret_cast<const std::byte *>(arena->_memory) + arena->_capacity};
            return arenaEnd > reinterpret_cast<const std::byte *>(&val);
        }};

        // Find arena
        const auto it{upperBound(Arena::_arenas.cbegin(), Arena::_arenas.cend(), v, comp)};

        if (it != Arena::_arenas.cend())
        {
            Arena & arena{**it};
            arena.destroy(v);
        }
        else
        {
            assert(false);
        }
    }

    inline void Arena::_expand(u64 newSize)
    {
        const u64 newPageCount{std::bit_ceil((newSize + (pageSize - 1u)) / pageSize)};
        newSize = newPageCount * pageSize;

        // Ensure we have sufficient reserved memory
        ABORT_IF(newSize > _capacity);

        // Commit new pages
        const u64 currentPageCount{_size / pageSize};
        std::byte * const pages{reinterpret_cast<std::byte *>(_memory)};
        commitPages(pages + currentPageCount * pageSize, newPageCount - currentPageCount);

        _size = newSize;
    }
}
