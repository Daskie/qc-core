#pragma once

#include <qc-core/bubble-tracker.hpp>
#include <qc-core/paging.hpp>

namespace qc
{
    ///
    /// Efficient allocator supporting very fast shared pointer reference tracking and polymorphism
    /// Each element in the arena is stored with an eight byte header. Additionally, one additional eight byte pointer
    ///   is stored at the very start of the allocated memory to track the arena for the purposes of value deletion
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

            using _T = std::remove_const_t<T>;

          public:

            Unq() = default;

            Unq(const Unq &) = delete;
            Unq(Unq && other);
            Unq(Unq<_T> && other) requires (std::is_const_v<T>) : Unq{reinterpret_cast<Unq &&>(other)} {}
            template <typename T_> requires std::is_base_of_v<T, T_> Unq(Unq<T_> && other) : Unq{reinterpret_cast<Unq &&>(other)} {}

            Unq & operator=(const Unq &) = delete;
            Unq & operator=(Unq && other);
            Unq & operator=(Unq<_T> && other) requires std::is_const_v<T> { return *this = reinterpret_cast<Unq &&>(other); }
            template <typename T_> requires std::is_base_of_v<T, T_> Unq & operator=(Unq<T_> && other) { return *this = reinterpret_cast<Unq &&>(other); }

            ~Unq();

            nodisc forceinline operator Unq<const T> &() & requires (!std::is_const_v<T>) { return reinterpret_cast<Unq<const T> &>(*this); }
            nodisc forceinline operator const Unq<const T> &() const & requires (!std::is_const_v<T>) { return reinterpret_cast<const Unq<const T> &>(*this); }

            void reset();

            nodisc forceinline explicit operator bool() const { return _ptr; }

            nodisc forceinline T & operator*() const { return *_ptr; }

            nodisc forceinline T * operator->() const { return _ptr; }

            template <typename T_> requires EqualityComparable<T *, T_ *> nodisc forceinline bool operator==(const Unq<T_> & other) const { return _ptr == other._ptr; }
            nodisc forceinline friend bool operator==(const Unq & a, const T * b) { return a._ptr == b; }
            nodisc forceinline friend bool operator==(const T * a, const Unq & b) { return a == b._ptr; }

          private:

            _T * _ptr{};

            explicit Unq(_T & v);

            nodisc u32 & _refN();
        };

        template <typename T>
        class Shr
        {
            friend Arena;

            using _T = std::remove_const_t<T>;

          public:

            Shr() = default;

            Shr(const Shr & other);
            forceinline Shr(const Shr<_T> & other) requires (std::is_const_v<T>) : Shr{reinterpret_cast<const Shr &>(other)} {}
            template <typename T_> requires std::is_base_of_v<T, T_> forceinline Shr(const Shr<T_> & other) : Shr{reinterpret_cast<const Shr &>(other)} {}
            Shr(Shr && other);
            forceinline Shr(Shr<_T> && other) requires (std::is_const_v<T>) : Shr{reinterpret_cast<Shr &&>(other)} {}
            template <typename T_> requires std::is_base_of_v<T, T_> forceinline Shr(Shr<T_> && other) : Shr{reinterpret_cast<Shr &&>(other)} {}

            Shr & operator=(const Shr & other);
            forceinline Shr & operator=(const Shr<_T> & other) requires std::is_const_v<T> { return *this = reinterpret_cast<const Shr &>(other); }
            template <typename T_> requires std::is_base_of_v<T, T_> forceinline Shr & operator=(const Shr<T_> & other) { return *this = reinterpret_cast<const Shr &>(other); }
            Shr & operator=(Shr && other);
            forceinline Shr & operator=(Shr<_T> && other) requires std::is_const_v<T> { return *this = reinterpret_cast<Shr &&>(other); }
            template <typename T_> requires std::is_base_of_v<T, T_> forceinline Shr & operator=(Shr<T_> && other) { return *this = reinterpret_cast<Shr &&>(other); }

            ~Shr();

            nodisc forceinline operator Shr<const T> &() & requires (!std::is_const_v<T>) { return reinterpret_cast<Shr<const T> &>(*this); }
            nodisc forceinline operator const Shr<const T> &() const & requires (!std::is_const_v<T>) { return reinterpret_cast<const Shr<const T> &>(*this); }

            void reset();

            nodisc forceinline explicit operator bool() const { return _ptr; }

            nodisc forceinline T & operator*() const { return *_ptr; }

            nodisc forceinline T * operator->() const { return _ptr; }

            template <typename T_> requires EqualityComparable<T *, T_ *> nodisc forceinline bool operator==(const Shr<T_> & other) const { return _ptr == other._ptr; }
            nodisc forceinline friend bool operator==(const Shr & a, const T * b) { return a._ptr == b; }
            nodisc forceinline friend bool operator==(const T * a, const Shr & b) { return a == b._ptr; }

          private:

            _T * _ptr{};

            explicit Shr(_T & ptr);

            nodisc u32 & _refN();
        };

        explicit Arena(u64 capacity);

        Arena(const Arena &) = delete;
        Arena(Arena && other);

        Arena & operator=(const Arena &) = delete;
        Arena & operator=(Arena && other);

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

        nodisc bool empty() const;

      private:

        struct alignas(8u) _Chunk
        {
            u16 pageI;
            u16 valChunkN;
            u32 refN;
        };

        static constexpr u64 _maxPageN{1u << 16};
        static constexpr u64 _maxCapacity{_maxPageN * pageSize - sizeof(_Chunk)};
        static constexpr u64 _maxValChunkN{(1u << 16) - 1u};

        static u64 _pageN(u64 capacity);

        static _Chunk & _header(void * valPtr);

        template <typename T> static void _destroy(T & v);

        u64 _capacity{};
        u64 _size{};
        _Chunk * _memory{};
        BubbleTracker<u32> _bubbles{};

        void _expand(u64 newSize);

        template <typename T, typename... Args> nodisc T & _create(Args &&... args);
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    forceinline Arena::Unq<T>::Unq(_T & v) :
        _ptr{&v}
    {
        u32 & refN{_refN()};
        assert(!refN);
        refN = 1u;
    }

    template <typename T>
    forceinline Arena::Unq<T>::Unq(Unq && other) :
        _ptr{other._ptr}
    {
        other._ptr = nullptr;
    }

    template <typename T>
    inline auto Arena::Unq<T>::operator=(Unq && other) -> Unq &
    {
        if (&other == this)
        {
            return *this;
        }

        reset();

        _ptr = other._ptr;
        other._ptr = nullptr;

        return *this;
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
            _destroy(*_ptr);
            _ptr = nullptr;
        }
    }

    template <typename T>
    forceinline u32 & Arena::Unq<T>::_refN()
    {
        return reinterpret_cast<u32 *>(_ptr)[-1];
    }

    template <typename T>
    forceinline Arena::Shr<T>::Shr(_T & v) :
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
    forceinline Arena::Shr<T>::Shr(Shr && other) :
        _ptr{other._ptr}
    {
        other._ptr = nullptr;
    }

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
    inline auto Arena::Shr<T>::operator=(Shr && other) -> Shr &
    {
        if (&other == this)
        {
            return *this;
        }

        reset();

        _ptr = other._ptr;
        other._ptr = nullptr;

        return *this;
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
                _destroy(*_ptr);
                _ptr = nullptr;
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
        ABORT_IF(capacity > _maxCapacity);

        const u64 pageN{_pageN(sizeof(_Chunk) + capacity)};
        _capacity = pageN * pageSize - sizeof(_Chunk);
        _bubbles.add(0u, u32(_capacity / sizeof(_Chunk)));
    }

    inline Arena::Arena(Arena && other) :
        _capacity{other._capacity},
        _size{other._size},
        _memory{other._memory},
        _bubbles{std::move(other._bubbles)}
    {
        other._capacity = 0u;
        other._size = 0u;
        other._memory = nullptr;

        // Update self pointer
        if (_memory)
        {
            *reinterpret_cast<Arena * *>(_memory - 1) = this;
        }
    }

    inline Arena & Arena::operator=(Arena && other)
    {
        _capacity = other._capacity;
        _size = other._size;
        _memory = other._memory;
        _bubbles = std::move(other._bubbles);

        other._capacity = 0u;
        other._size = 0u;
        other._memory = nullptr;

        // Update self pointer
        if (_memory)
        {
            *reinterpret_cast<Arena * *>(_memory - 1) = this;
        }

        return *this;
    }

    inline Arena::~Arena()
    {
        if (_capacity)
        {
            // Check for dangling references
            assert(empty());

            freePages(_memory - 1, (sizeof(_Chunk) + _capacity) / pageSize);
        }
    }

    template <typename T, typename... Args>
    forceinline auto Arena::unq(Args &&... args) -> Unq<T>
    {
        return Unq<T>{_create<std::remove_const_t<T>>(std::forward<Args>(args)...)};
    }

    template <typename T, typename... Args>
    forceinline auto Arena::shr(Args &&... args) -> Shr<T>
    {
        return Shr<T>{_create<std::remove_const_t<T>>(std::forward<Args>(args)...)};
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
            ABORT_IF(&header < _memory || &header >= _memory + _size / sizeof(_Chunk));
            ABORT_IF(!header.refN);
        }

        return Shr<T>{*ptr};
    }

    inline void Arena::shrinkToFit()
    {
        if (!_size)
        {
            return;
        }

        const u64 freeTailSize{_bubbles.tail(u32(_capacity / sizeof(_Chunk))) * sizeof(_Chunk)};

        // Arena is unallocated or full
        if (!freeTailSize)
        {
            return;
        }

        const u64 necessarySize{_capacity - freeTailSize};
        const u64 necessaryPageN{necessarySize ? _pageN(sizeof(_Chunk) + necessarySize) : 0u};
        const u64 currentPageN{(sizeof(_Chunk) + _size) / pageSize};
        const u64 unnecessaryPageN{currentPageN - necessaryPageN};

        // Free tail is smaller than hald the current size
        if (!unnecessaryPageN)
        {
            return;
        }

        // Decommit uneccessary pages
        decommitPages(reinterpret_cast<std::byte *>(_memory - 1) + necessaryPageN * pageSize, unnecessaryPageN);

        _size = necessaryPageN ? necessaryPageN * pageSize - sizeof(_Chunk) : 0u;
    }

    inline bool Arena::empty() const
    {
        if (!_capacity)
        {
            return true;
        }

        if (_bubbles.bubbles().size() != 1u)
        {
            return false;
        }

        const auto & bubble{_bubbles.bubbles().front()};
        return bubble.pos == 0u && bubble.size * sizeof(_Chunk) == _capacity;
    }

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

        // Destruct value
        v.~T();

        // Get arena pointer
        const u64 startOfPageAddr{std::bit_cast<u64>(&header) & ~u64(pageSize - 1u)};
        const u64 firstPageAddr{startOfPageAddr - header.pageI * pageSize};
        Arena & arena{**std::bit_cast<Arena * *>(firstPageAddr)};

        // Add bubble
        arena._bubbles.add(u32(&header - arena._memory), 1u + header.valChunkN);
    }

    inline void Arena::_expand(u64 newSize)
    {
        const u64 newPageN{_pageN(sizeof(_Chunk) + newSize)};
        newSize = newPageN * pageSize - sizeof(_Chunk);

        // Larger than maximum capacity
        ABORT_IF(newSize > _capacity);

        // Reserve memory if this is the first time
        if (!_memory)
        {
            _memory = static_cast<_Chunk *>(reservePages(_pageN((1u + _capacity) * sizeof(_Chunk)))) + 1;
        }

        // Commit new pages
        const u64 currentPageN{_size ? (sizeof(_Chunk) + _size) / pageSize : 0u};
        std::byte * const pages{reinterpret_cast<std::byte *>(_memory - 1)};
        commitPages(pages + currentPageN * pageSize, newPageN - currentPageN);

        // Set self pointer if this is the first commit
        if (!_size)
        {
            *reinterpret_cast<Arena * *>(_memory - 1) = this;
        }

        _size = newSize;
    }

    template <typename T, typename... Args>
    inline T & Arena::_create(Args &&... args)
    {
        static constexpr u64 valChunkN{(sizeof(T) + sizeof(_Chunk) - 1u) / sizeof(_Chunk)};
        static_assert(valChunkN <= _maxValChunkN);
        static_assert(alignof(T) <= sizeof(_Chunk));

        const auto [wasSpace, headerPos]{_bubbles.remove(1u + valChunkN)};

        // Arena is full
        ABORT_IF(!wasSpace);

        const u64 requiredSize{(headerPos + 1u + valChunkN) * sizeof(_Chunk)};
        if (requiredSize > _size)
        {
            _expand(requiredSize);
        }

        _Chunk & header{_memory[headerPos]};
        header.pageI = u16((1u + headerPos) * sizeof(_Chunk) / pageSize);
        header.valChunkN = valChunkN;
        header.refN = 0u;
        return *(new (&header + 1) T{std::forward<Args>(args)...});
    }
}
