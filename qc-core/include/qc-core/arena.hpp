#pragma once

#include <qc-core/bubble-tracker.hpp>
#include <qc-core/paging.hpp>

namespace qc
{
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
      public:

        template <typename T>
        class Unq
        {
            friend Arena;

          public:

            Unq() = default;

            Unq(const Unq &) = delete;
            Unq(Unq && other);
            template <typename T_> requires std::is_base_of_v<T, T_> Unq(Unq<T_> && other);

            Unq & operator=(const Unq &) = delete;
            Unq & operator=(Unq && other);
            template <typename T_> requires std::is_base_of_v<T, T_> Unq & operator=(Unq<T_> && other);

            ~Unq();

            void reset();

            nodisc forceinline explicit operator bool() const { return _ptr; }

            nodisc forceinline T & operator*() const { return *_ptr; }

            nodisc forceinline T * operator->() const { return _ptr; }

            nodisc forceinline bool operator==(const Unq & other) const { return _ptr == other._ptr; }
            nodisc forceinline friend bool operator==(const Unq & a, const T * b) { return a._ptr == b; }
            nodisc forceinline friend bool operator==(const T * a, const Unq & b) { return a == b._ptr; }

          private:

            T * _ptr{};

            explicit Unq(T & v);

            nodisc u32 & _refN();
        };

        template <typename T>
        class Shr
        {
            friend Arena;

          public:

            Shr() = default;

            Shr(const Shr & other);
            template <typename T_> requires std::is_base_of_v<T, T_> Shr(const Shr<T_> & other);
            Shr(Shr && other);
            template <typename T_> requires std::is_base_of_v<T, T_> Shr(Shr<T_> && other);

            Shr & operator=(const Shr & other);
            template <typename T_> requires std::is_base_of_v<T, T_> Shr & operator=(const Shr<T_> & other);
            Shr & operator=(Shr && other);
            template <typename T_> requires std::is_base_of_v<T, T_> Shr & operator=(Shr<T_> && other);

            ~Shr();

            void reset();

            nodisc forceinline explicit operator bool() const { return _ptr; }

            nodisc forceinline T & operator*() const { return *_ptr; }

            nodisc forceinline T * operator->() const { return _ptr; }

            nodisc forceinline bool operator==(const Shr & other) const { return _ptr == other._ptr; }
            nodisc forceinline friend bool operator==(const Shr & a, const T * b) { return a._ptr == b; }
            nodisc forceinline friend bool operator==(const T * a, const Shr & b) { return a == b._ptr; }

          private:

            T * _ptr{};

            explicit Shr(T & ptr);

            nodisc u32 & _refN();
        };

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
        template <typename T> nodisc Shr<T> shrOf(T * ptr);

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

        template <typename T> static void _destroy(T & v);

        u64 _capacity;
        u64 _size{};
        _Chunk * _memory;
        BubbleTracker<_Chunk *> _bubbles{};

        void _expand(u64 newSize);

        template <typename T, typename... Args> nodisc T & _create(Args &&... args);
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    forceinline Arena::Unq<T>::Unq(T & v) :
        _ptr{&v}
    {
        u32 & refN{_refN()};
        assert(!refN);
        refN = 1u;
    }

    template <typename T>
    forceinline Arena::Unq<T>::Unq(Unq && other) :
        _ptr{std::exchange(other._ptr, nullptr)}
    {}

    template <typename T>
    template <typename T_> requires std::is_base_of_v<T, T_>
    forceinline Arena::Unq<T>::Unq(Unq<T_> && other) :
        _ptr{std::exchange(other._ptr, nullptr)}
    {}

    template <typename T>
    inline auto Arena::Unq<T>::operator=(Unq && other) -> Unq &
    {
        if (&other == this)
        {
            return *this;
        }

        reset();

        _ptr = std::exchange(other._ptr, nullptr);

        return *this;
    }

    template <typename T>
    template <typename T_> requires std::is_base_of_v<T, T_>
    forceinline auto Arena::Unq<T>::operator=(Unq<T_> && other) -> Unq &
    {
        return *this = reinterpret_cast<Unq &&>(other);
    }

    template <typename T>
    forceinline Arena::Unq<T>::Unq::~Unq()
    {
        reset();
    }

    template <typename T>
    inline void Arena::Unq<T>::reset()
    {
        if (_ptr)
        {
            u32 & refN{_refN()};
            assert(refN == 1u);
            refN = 0u;
            _destroy(*std::exchange(_ptr, nullptr));
        }
    }

    template <typename T>
    forceinline u32 & Arena::Unq<T>::_refN()
    {
        return reinterpret_cast<u32 *>(_ptr)[-1];
    }

    template <typename T>
    forceinline Arena::Shr<T>::Shr(T & v) :
        _ptr{&v}
    {
        ++_refN();
    }

    template <typename T>
    forceinline Arena::Shr<T>::Shr(const Shr & other) :
        _ptr{other._ptr}
    {
        if (_ptr)
        {
            ++_refN();
        }
    }

    template <typename T>
    template <typename T_> requires std::is_base_of_v<T, T_>
    forceinline Arena::Shr<T>::Shr(const Shr<T_> & other) :
        _ptr{other._ptr}
    {
        ++_refN();
    }

    template <typename T>
    forceinline Arena::Shr<T>::Shr(Shr && other) :
        _ptr{std::exchange(other._ptr, nullptr)}
    {}

    template <typename T>
    template <typename T_> requires std::is_base_of_v<T, T_>
    forceinline Arena::Shr<T>::Shr(Shr<T_> && other) :
        _ptr{std::exchange(other._ptr, nullptr)}
    {}

    template <typename T>
    inline auto Arena::Shr<T>::operator=(const Shr & other) -> Shr &
    {
        if (&other == this)
        {
            return *this;
        }

        reset();

        _ptr = other._ptr;

        if (_ptr)
        {
            ++_refN();
        }

        return *this;
    }

    template <typename T>
    template <typename T_> requires std::is_base_of_v<T, T_>
    forceinline auto Arena::Shr<T>::operator=(const Shr<T_> & other) -> Shr &
    {
        return *this = reinterpret_cast<const Shr &>(other);
    }

    template <typename T>
    inline auto Arena::Shr<T>::operator=(Shr && other) -> Shr &
    {
        if (&other == this)
        {
            return *this;
        }

        reset();

        _ptr = std::exchange(other._ptr, nullptr);

        return *this;
    }

    template <typename T>
    template <typename T_> requires std::is_base_of_v<T, T_>
    forceinline auto Arena::Shr<T>::operator=(Shr<T_> && other) -> Shr &
    {
        return *this = reinterpret_cast<Shr &&>(other);
    }

    template <typename T>
    forceinline Arena::Shr<T>::Shr::~Shr()
    {
        reset();
    }

    template <typename T>
    inline void Arena::Shr<T>::reset()
    {
        if (_ptr)
        {
            u32 & refN{_refN()};
            assert(refN >= 1u);

            if (!--refN)
            {
                _destroy(*std::exchange(_ptr, nullptr));
            }
        }
    }

    template <typename T>
    forceinline u32 & Arena::Shr<T>::_refN()
    {
        return reinterpret_cast<u32 *>(_ptr)[-1];
    }

    inline Arena::Arena(const u64 capacity)
    {
        const u64 pageN{_pageN(capacity)};
        _capacity = pageN * pageSize;
        _memory = static_cast<_Chunk *>(reservePages(pageN)); // TODO: Don't reserve pages until first expansion
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
    forceinline auto Arena::unq(Args &&... args) -> Unq<T>
    {
        return Unq<T>{_create<T>(std::forward<Args>(args)...)};
    }

    template <typename T, typename... Args>
    forceinline auto Arena::shr(Args &&... args) -> Shr<T>
    {
        return Shr<T>{_create<T>(std::forward<Args>(args)...)};
    }

    template <typename T>
    forceinline auto Arena::shrOf(T * const ptr) -> Shr<T>
    {
        if (!ptr)
        {
            return {};
        }

        if constexpr (debug)
        {
            _Chunk & header{_header(ptr)};
            ABORT_IF(&header < _memory || &header >= _memory + _capacity);
            ABORT_IF(!header.refN);
        }

        return Shr<T>{*ptr};
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

    template <typename T>
    inline void Arena::_destroy(T & v)
    {
        _Chunk & header{Arena::_header(&v)};
        assert(!header.refN);
        v.~T();
        header.arena->_bubbles.add(&header, 1 + header.valChunkN);
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
    inline T & Arena::_create(Args &&... args)
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
        return *(new (header + 1) T{std::forward<Args>(args)...});
    }
}
