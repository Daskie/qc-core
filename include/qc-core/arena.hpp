#pragma once

#include <qc-core/bubble-tracker.hpp>
#include <qc-core/paging.hpp>
#include <qc-core/smart-pointer.hpp>

namespace qc
{
    struct ArenaError {};

    ///
    /// ...
    /// Each element in the arena is stored with a leading 8 byte header. Of this, the lower four bytes are used to
    ///   store the size of the value, and the upper four bytes are left empty for other uses. `Shr` uses these upper
    ///   four bytes to reference count, for example.
    ///
    class Arena
    {
      public:

        Arena() noexcept = default;
        explicit Arena(size_t capacity);

        Arena(const Arena &) = delete;
        Arena(Arena && other) noexcept;

        Arena & operator=(const Arena &) = delete;
        Arena & operator=(Arena && other) noexcept;

        ~Arena() noexcept (!debug);

        void setCapacity(size_t capacity);

        template <typename T, typename... Args> [[nodiscard]] T & create(Args && ... args);

        template <typename T, typename... Args> [[nodiscard]] Unq<T> createUnique(Args && ... args);

        template <typename T, typename... Args> [[nodiscard]] Shr<T> createShared(Args && ... args);

        template <typename T> void destroy(T & v);

        void shrinkToFit();

        size_t capacity() const noexcept { return _capacity; }

        size_t size() const noexcept { return _size; }

        bool empty() const noexcept { return !_size; }

      private:

        inline static std::vector<Arena *> _arenas{};

        template <typename T> static void _destroy(T & v);

        size_t _capacity{};
        size_t _size{};
        u64 * _memory{};
        BubbleTracker<u64 *> _bubbles{};

        void _expand(size_t newSize);
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    inline Arena::Arena(const size_t capacity)
    {
        setCapacity(capacity);
    }

    inline Arena::Arena(Arena && other) noexcept :
        _capacity{std::exchange(other._capacity, 0u)},
        _size{std::exchange(other._size, 0u)},
        _memory{std::exchange(other._memory, nullptr)},
        _bubbles{std::move(other._bubbles)}
    {}

    inline auto Arena::operator=(Arena && other) noexcept -> Arena &
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

    inline Arena::~Arena() noexcept (!debug)
    {
        if (_memory)
        {
            // Check for dangling references
            if constexpr (debug)
            {
                if (_bubbles.bubbles().size() != 1u)
                {
                    throw ArenaError{};
                }

                const auto & bubble{_bubbles.bubbles().front()};
                if (bubble.pos != _memory || size_t(bubble.size) * 8u != _capacity)
                {
                    throw ArenaError{};
                }
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

    inline void Arena::setCapacity(const size_t capacity)
    {
        // May only be called before memory is reserved
        if (_memory)
        {
            throw ArenaError{};
        }

        const size_t pageCount{std::bit_ceil((capacity + (pageSize - 1u)) / pageSize)};
        _capacity = pageCount * pageSize;
        _memory = static_cast<u64 *>(reservePages(pageCount));
        _bubbles.add(_memory, _capacity / 8u);

        // Insert self into sorted arena list
        auto it{_arenas.begin()};
        for (; it != _arenas.end() && (*it)->_memory < _memory; ++it);
        _arenas.insert(it, this);
    }

    template <typename T, typename... Args>
    inline T & Arena::create(Args &&... args)
    {
        static_assert(alignof(T) <= 8u);

        const size_t wordCount{1u + (sizeof(T) + 7u) / 8u};
        const auto [wasSpace, ptr]{_bubbles.remove(ptrdiff_t(wordCount))};

        // Arena is full
        while (!wasSpace)
        {
            throw ArenaError{};
        }

        const size_t requiredSize{(size_t(ptr - _memory) + wordCount) * 8u};
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
        const u64 valSize{*ptr & 0xFFFFFFFFu};
        const size_t wordCount{1u + (valSize + 7u) / 8u};
        _bubbles.add(ptr, wordCount);
    }

    inline void Arena::shrinkToFit()
    {
        const size_t freeTailSize{size_t(_bubbles.tail(_memory + _capacity / 8u)) * 8u};

        // Arena is unallocated or full
        if (!freeTailSize)
        {
            return;
        }

        size_t necessaryPageCount{(_capacity - freeTailSize + (pageSize - 1u)) / pageSize};
        if (necessaryPageCount) necessaryPageCount = std::bit_ceil(necessaryPageCount);
        const size_t currentPageCount{(_size + (pageSize - 1u)) / pageSize};
        const size_t unnecessaryPageCount{currentPageCount - necessaryPageCount};

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
        else if constexpr (debug)
        {
            throw ArenaError{};
        }
    }

    inline void Arena::_expand(size_t newSize)
    {
        const size_t newPageCount{std::bit_ceil((newSize + (pageSize - 1u)) / pageSize)};
        newSize = newPageCount * pageSize;

        // Ensure we have sufficient reserved memory
        if (newSize > _capacity)
        {
            throw ArenaError{};
        }

        // Commit new pages
        const size_t currentPageCount{_size / pageSize};
        std::byte * const pages{reinterpret_cast<std::byte *>(_memory)};
        commitPages(pages + currentPageCount * pageSize, newPageCount - currentPageCount);

        _size = newSize;
    }
}
