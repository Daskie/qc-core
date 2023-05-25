#pragma once

#include <qc-core/bubble-tracker.hpp>
#include <qc-core/paging.hpp>

namespace qc
{
    class Arena;

    template <typename T>
    class Unq
    {
        template <typename T_> friend class Unq;
        friend class Arena;

      public:

        Unq() = default;

        Unq(const Unq &) = delete;
        Unq(Unq && other);
        template <typename T_> requires std::derived_from<T_, T> Unq(Unq<T_> && other);

        Unq & operator=(const Unq &) = delete;
        Unq & operator=(Unq && other);
        template <typename T_> requires std::derived_from<T_, T> Unq & operator=(Unq<T_> && other);

        ~Unq();

        void reset();

        nodisc forceinline explicit operator bool() const { return _ptr; }

        nodisc forceinline T & operator*() const { return *_ptr; }

        nodisc forceinline T * operator->() const { return _ptr; }

        nodisc forceinline T * get() const { return _ptr; }

        nodisc forceinline bool operator==(const Unq & other) const { return _ptr == other._ptr; }
        nodisc forceinline friend bool operator==(const Unq & a, const T * b) { return a._ptr == b; }
        nodisc forceinline friend bool operator==(const T * a, const Unq & b) { return a == b._ptr; }

      private:

        T * _ptr{};

        explicit Unq(T * ptr);
    };

    template <typename T>
    class Shr
    {
        template <typename T_> friend class Shr;
        friend class Arena;

      public:

        Shr() = default;

        Shr(const Shr & other);
        template <typename T_> requires std::derived_from<T_, T> Shr(const Shr<T_> & other);
        Shr(Shr && other);
        template <typename T_> requires std::derived_from<T_, T> Shr(Shr<T_> && other);

        Shr & operator=(const Shr & other);
        template <typename T_> requires std::derived_from<T_, T> Shr & operator=(const Shr<T_> & other);
        Shr & operator=(Shr && other);
        template <typename T_> requires std::derived_from<T_, T> Shr & operator=(Shr<T_> && other);

        ~Shr();

        void reset();

        nodisc forceinline explicit operator bool() const { return _ptr; }

        nodisc forceinline T & operator*() const { return *_ptr; }

        nodisc forceinline T * operator->() const { return _ptr; }

        nodisc forceinline T * get() const { return _ptr; }

        nodisc forceinline bool operator==(const Shr & other) const { return _ptr == other._ptr; }
        nodisc forceinline friend bool operator==(const Shr & a, const T * b) { return a._ptr == b; }
        nodisc forceinline friend bool operator==(const T * a, const Shr & b) { return a == b._ptr; }

      private:

        T * _ptr{};

        explicit Shr(T * ptr);
    };

    ///
    /// ...
    /// Each element in the arena is stored with a leading 16 byte header. Of this, the lower 8 bytes are used for a
    ///   pointer to the arena, the next four bytes are used for the size of the value (necessary for polymorphism), and
    ///   the upper four bytes are used for the reference count (used by `Shr`)
    /// Properties:
    ///   Create: O(m), where `m` is number of unallocated bubbles
    ///   Destroy: O(log(m)), where `m` is number of unallocated bubbles
    ///   Reference stable: Yes
    ///   Index stable: Yes
    ///   Order stable: Yes
    ///   Contiguous elements: No
    ///
    class Arena
    {
        template <typename> friend class Unq;
        template <typename> friend class Shr;

      public:

        explicit Arena(u64 capacity);

        Arena(const Arena &) = delete;
        Arena(Arena &&) = delete;

        Arena & operator=(const Arena &) = delete;
        Arena & operator=(Arena &&) = delete;

        ~Arena();

        template <typename T, typename... Args> nodisc Unq<T> unq(Args && ... args);

        template <typename T, typename... Args> nodisc Shr<T> shr(Args && ... args);

        ///
        /// @param ptr an existing shared value of the arena
        /// @return another shr of the given pointer
        ///
        template <typename T> nodisc Shr<T> shr(T * ptr);

        void shrinkToFit();

        nodisc forceinline u64 capacity() const { return _capacity; }

        nodisc forceinline u64 size() const { return _size; }

        nodisc forceinline bool empty() const { return !_size; }

      private:

        struct _Chunk
        {
            Arena * arena;
            u32 valChunkN;
            u32 refN;
        };

        static constexpr u64 _maxValChunkN{(u64(1u) << 32) - 1u};

        static u64 _pageN(u64 capacity);

        static _Chunk & _header(void * valPtr);

        u64 _capacity;
        u64 _size{};
        _Chunk * _memory;
        BubbleTracker<_Chunk *> _bubbles{};

        void _expand(u64 newSize);

        template <typename T, typename... Args> nodisc T * _create(Args && ... args);
        template <typename T> void _destroy(T * v);
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    forceinline Unq<T>::Unq(T * const ptr) :
        _ptr{ptr}
    {}

    template <typename T>
    forceinline Unq<T>::Unq(Unq && other) :
        _ptr{std::exchange(other._ptr, nullptr)}
    {}

    template <typename T>
    template <typename T_> requires std::derived_from<T_, T>
    forceinline Unq<T>::Unq(Unq<T_> && other) :
        _ptr{std::exchange(other._ptr, nullptr)}
    {}

    template <typename T>
    forceinline Unq<T> & Unq<T>::operator=(Unq && other)
    {
        return this->operator=<T>(std::move(other));
    }

    template <typename T>
    template <typename T_> requires std::derived_from<T_, T>
    inline Unq<T> & Unq<T>::operator=(Unq<T_> && other)
    {
        if (static_cast<void *>(&other) == this)
        {
            return *this;
        }

        reset();

        _ptr = std::exchange(other._ptr, nullptr);

        return *this;
    }

    template <typename T>
    forceinline Unq<T>::~Unq()
    {
        reset();
    }

    template <typename T>
    inline void Unq<T>::reset()
    {
        if (_ptr)
        {
            // Ensure this object's state is reset first in case of cyclical ownership
            T * const ptr{_ptr};
            _ptr = nullptr;

            Arena * const arena{Arena::_header(ptr).arena};
            arena->_destroy(ptr);
        }
    }

    template <typename T>
    forceinline Shr<T>::Shr(T * const ptr) :
        _ptr{ptr}
    {
        ++Arena::_header(_ptr).refN;
    }

    template <typename T>
    forceinline Shr<T>::Shr(const Shr & other) :
        _ptr{other._ptr}
    {
        ++Arena::_header(_ptr).refN;
    }

    template <typename T>
    template <typename T_> requires std::derived_from<T_, T>
    forceinline Shr<T>::Shr(const Shr<T_> & other) :
        _ptr{other._ptr}
    {
        ++Arena::_header(_ptr).refN;
    }

    template <typename T>
    forceinline Shr<T>::Shr(Shr && other) :
        _ptr{std::exchange(other._ptr, nullptr)}
    {}

    template <typename T>
    template <typename T_> requires std::derived_from<T_, T>
    forceinline Shr<T>::Shr(Shr<T_> && other) :
        _ptr{std::exchange(other._ptr, nullptr)}
    {}

    template <typename T>
    forceinline Shr<T> & Shr<T>::operator=(const Shr & other)
    {
        return this->operator=<T>(other);
    }

    template <typename T>
    template <typename T_> requires std::derived_from<T_, T>
    inline Shr<T> & Shr<T>::operator=(const Shr<T_> & other)
    {
        if (static_cast<const void *>(&other) == this)
        {
            return *this;
        }

        reset();

        _ptr = other._ptr;

        if (_ptr)
        {
            ++Arena::_header(_ptr).refN;
        }

        return *this;
    }

    template <typename T>
    forceinline Shr<T> & Shr<T>::operator=(Shr && other)
    {
        return this->operator=<T>(std::move(other));
    }

    template <typename T>
    template <typename T_> requires std::derived_from<T_, T>
    inline Shr<T> & Shr<T>::operator=(Shr<T_> && other)
    {
        if (static_cast<void *>(&other) == this)
        {
            return *this;
        }

        reset();

        _ptr = std::exchange(other._ptr, nullptr);

        return *this;
    }

    template <typename T>
    forceinline Shr<T>::~Shr()
    {
        reset();
    }

    template <typename T>
    inline void Shr<T>::reset()
    {
        if (_ptr)
        {
            Arena::_Chunk & header{Arena::_header(_ptr)};
            assert(header.refN >= 1u);

            // Ensure this object's state is reset first in case of cyclical ownership
            T * const ptr{_ptr};
            _ptr = nullptr;

            if (!--header.refN)
            {
                header.arena->_destroy(ptr);
            }
        }
    }

    inline Arena::Arena(const u64 capacity)
    {
        const u64 pageN{_pageN(capacity)};
        _capacity = pageN * pageSize;
        _memory = static_cast<_Chunk *>(reservePages(pageN));
        _bubbles.add(_memory, s64(_capacity / sizeof(_Chunk)));
    }

    inline Arena::~Arena()
    {
        // Check for dangling references
        if constexpr (debug)
        {
            ABORT_IF(_bubbles.bubbles().size() != 1u);
            const auto & bubble{_bubbles.bubbles().front()};
            ABORT_IF(bubble.pos != _memory || u64(bubble.size) * sizeof(_Chunk) != _capacity);
        }

        freePages(_memory, _pageN(_capacity));
    }

    template <typename T, typename... Args>
    forceinline Unq<T> Arena::unq(Args &&... args)
    {
        return Unq<T>{_create<T>(std::forward<Args>(args)...)};
    }

    template <typename T, typename... Args>
    forceinline Shr<T> Arena::shr(Args &&... args)
    {
        return Shr<T>{_create<T>(std::forward<Args>(args)...)};
    }

    template <typename T>
    forceinline Shr<T> Arena::shr(T * const ptr)
    {
        if constexpr (debug)
        {
            _Chunk & header{_header(ptr)};
            ABORT_IF(header.arena != this);
            ABORT_IF(!header.refN);
        }

        return Shr<T>{ptr};
    }

    inline void Arena::shrinkToFit()
    {
        const u64 freeTailSize{u64(_bubbles.tail(_memory + _capacity / sizeof(_Chunk))) * sizeof(_Chunk)};

        // Arena is unallocated or full
        if (!freeTailSize)
        {
            return;
        }

        u64 necessaryPageN{(_capacity - freeTailSize + (pageSize - 1u)) / pageSize};
        if (necessaryPageN) necessaryPageN = std::bit_ceil(necessaryPageN);
        const u64 currentPageN{(_size + (pageSize - 1u)) / pageSize};
        const u64 unnecessaryPageN{currentPageN - necessaryPageN};

        // Free tail is smaller than hald the current size
        if (!unnecessaryPageN)
        {
            return;
        }

        // Decommit uneccessary pages
        decommitPages(reinterpret_cast<std::byte *>(_memory) + necessaryPageN * pageSize, unnecessaryPageN);

        _size = necessaryPageN * pageSize;
    }

    // TODO: Move to paging.hpp
    forceinline u64 Arena::_pageN(const u64 capacity)
    {
        return std::bit_ceil((capacity + (pageSize - 1u)) / pageSize);
    }

    forceinline auto Arena::_header(void * const valPtr) -> _Chunk &
    {
        return reinterpret_cast<_Chunk *>(valPtr)[-1];
    }

    inline void Arena::_expand(u64 newSize)
    {
        const u64 newPageN{std::bit_ceil((newSize + (pageSize - 1u)) / pageSize)};
        newSize = newPageN * pageSize;

        // Ensure we have sufficient reserved memory
        ABORT_IF(newSize > _capacity);

        // Commit new pages
        const u64 currentPageN{_size / pageSize};
        std::byte * const pages{reinterpret_cast<std::byte *>(_memory)};
        commitPages(pages + currentPageN * pageSize, newPageN - currentPageN);

        _size = newSize;
    }

    template <typename T, typename... Args>
    inline T * Arena::_create(Args &&... args)
    {
        static constexpr u64 valChunkN{(sizeof(T) + sizeof(_Chunk) - 1u) / sizeof(_Chunk)};
        static_assert(valChunkN <= _maxValChunkN);
        static_assert(alignof(T) <= sizeof(_Chunk));

        const auto [wasSpace, header]{_bubbles.remove(1u + valChunkN)};

        // Arena is full
        ABORT_IF(!wasSpace);

        const u64 requiredSize{(u64(header - _memory) + 1u + valChunkN) * sizeof(_Chunk)};
        if (requiredSize > _size)
        {
            _expand(requiredSize);
        }

        header->arena = this;
        header->valChunkN = valChunkN;
        header->refN = 0u;
        return new (header + 1) T{std::forward<Args>(args)...};
    }

    template <typename T>
    inline void Arena::_destroy(T * const v)
    {
        v->~T();

        _Chunk & header{_header(v)};
        _bubbles.add(&header, 1 + header.valChunkN);
    }
}
