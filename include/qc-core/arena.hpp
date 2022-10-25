#pragma once

#include <qc-core/bubble-tracker.hpp>
#include <qc-core/paging.hpp>

namespace qc
{
    struct ArenaError {};

    class Arena;

    template <typename T>
    class Unq
    {
        template <typename T_> friend class Unq;
        friend class Arena;

      public:

        Unq() noexcept = default;

        Unq(const Unq &) = delete;
        Unq(Unq && other) noexcept;
        template <typename T_> requires std::derived_from<T_, T> Unq(Unq<T_> && other) noexcept;

        Unq & operator=(const Unq &) = delete;
        Unq & operator=(Unq && other) noexcept;

        ~Unq() noexcept;

        T & operator*() noexcept { return *_ptr; }

        const T & operator*() const noexcept { return *_ptr; }

        T * operator->() noexcept { return _ptr; }

        const T * operator->() const noexcept { return _ptr; }

        T * get() noexcept { return _ptr; }

        const T * get() const noexcept { return _ptr; }

      private:

        T * _ptr{};

        explicit Unq(T * ptr) noexcept;
    };

    template <typename T>
    class Shr
    {
        template <typename T_> friend class Shr;
        friend class Arena;

      public:

        Shr() noexcept = default;

        Shr(const Shr & other) noexcept;
        template <typename T_> requires std::derived_from<T_, T> Shr(const Shr<T_> & other) noexcept;
        Shr(Shr && other) noexcept;
        template <typename T_> requires std::derived_from<T_, T> Shr(Shr<T_> && other) noexcept;

        Shr & operator=(const Shr & other) noexcept;
        Shr & operator=(Shr && other) noexcept;

        ~Shr() noexcept;

        T & operator*() noexcept { return *_ptr; }

        const T & operator*() const noexcept { return *_ptr; }

        T * operator->() noexcept { return _ptr; }

        const T * operator->() const noexcept { return _ptr; }

        T * get() noexcept { return _ptr; }

        const T * get() const noexcept { return _ptr; }

      private:

        T * _ptr{};

        explicit Shr(T * ptr) noexcept;
    };

    class Arena
    {
        template <typename T> friend class Unq;
        template <typename T> friend class Shr;

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
    namespace _arena_internal
    {
        struct alignas(8) Header
        {
            u32 size;
            u32 refCount;
        };

        Header & header(void * ptr)
        {
            return static_cast<Header *>(ptr)[-1];
        }

        const Header & header(const void * ptr)
        {
            return static_cast<const Header *>(ptr)[-1];
        }
    }

    template <typename T>
    inline Unq<T>::Unq(Unq && other) noexcept :
        _ptr{std::exchange(other._ptr, nullptr)}
    {}

    template <typename T>
    template <typename T_> requires std::derived_from<T_, T>
    inline Unq<T>::Unq(Unq<T_> && other) noexcept :
        _ptr{std::exchange(other._ptr, nullptr)}
    {}

    template <typename T>
    inline Unq<T> & Unq<T>::operator=(Unq && other) noexcept
    {
        if (&other == this)
        {
            return *this;
        }

        if (_ptr)
        {
            Arena::_destroy(*_ptr);
        }

        _ptr = std::exchange(other._ptr, nullptr);

        return *this;
    }

    template <typename T>
    inline Unq<T>::~Unq() noexcept
    {
        if (_ptr)
        {
            Arena::_destroy(*_ptr);
        }

        if constexpr (debug)
        {
            _ptr = nullptr;
        }
    }

    template <typename T>
    inline Unq<T>::Unq(T * const ptr) noexcept :
        _ptr{ptr}
    {}

    template <typename T>
    inline Shr<T>::Shr(const Shr & other) noexcept :
        _ptr{other._ptr}
    {
        ++_arena_internal::header(_ptr).refCount;
    }

    template <typename T>
    template <typename T_> requires std::derived_from<T_, T>
    inline Shr<T>::Shr(const Shr<T_> & other) noexcept :
        _ptr{other._ptr}
    {
        ++_arena_internal::header(_ptr).refCount;
    }

    template <typename T>
    inline Shr<T>::Shr(Shr && other) noexcept :
        _ptr{std::exchange(other._ptr, nullptr)}
    {}

    template <typename T>
    template <typename T_> requires std::derived_from<T_, T>
    inline Shr<T>::Shr(Shr<T_> && other) noexcept :
        _ptr{std::exchange(other._ptr, nullptr)}
    {}

    template <typename T>
    inline Shr<T> & Shr<T>::operator=(const Shr & other) noexcept
    {
        if (&other == this)
        {
            return *this;
        }

        if (_ptr)
        {
            if (!--_arena_internal::header(_ptr).refCount)
            {
                Arena::_destroy(*_ptr);
            }
        }

        _ptr = other._ptr;

        if (_ptr)
        {
            ++_arena_internal::header(_ptr).refCount;
        }

        return *this;
    }

    template <typename T>
    inline Shr<T> & Shr<T>::operator=(Shr && other) noexcept
    {
        if (&other == this)
        {
            return *this;
        }

        if (_ptr)
        {
            if (!--_arena_internal::header(_ptr).refCount)
            {
                Arena::_destroy(*_ptr);
            }
        }

        _ptr = std::exchange(other._ptr, nullptr);

        return *this;
    }

    template <typename T>
    inline Shr<T>::~Shr() noexcept
    {
        if (_ptr)
        {
            Arena::_destroy(*_ptr);
        }

        if constexpr (debug)
        {
            _ptr = nullptr;
        }
    }

    template <typename T>
    inline Shr<T>::Shr(T * const ptr) noexcept :
        _ptr{ptr}
    {
        ++_arena_internal::header(_ptr).refCount;
    }

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
        const auto [wasSpace, ptr]{_bubbles.remove(intptr_t(wordCount))};

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

        _arena_internal::Header * const header{reinterpret_cast<_arena_internal::Header *>(ptr)};
        header->size = sizeof(T);
        header->refCount = 0u;
        return *(new (header + 1u) T{std::forward<Args>(args)...});
    }

    template <typename T, typename... Args>
    inline Unq<T> Arena::createUnique(Args &&... args)
    {
        return Unq<T>{&create<T>(std::forward<Args>(args)...)};
    }

    template <typename T, typename... Args>
    inline Shr<T> Arena::createShared(Args &&... args)
    {
        return Shr<T>{&create<T>(std::forward<Args>(args)...)};
    }

    template <typename T>
    inline void Arena::destroy(T & v)
    {
        v.~T();

        const size_t wordCount{1u + (_arena_internal::header(&v).size + 7u) / 8u};
        _bubbles.add(reinterpret_cast<u64 *>(&v) - 1u, wordCount);
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
