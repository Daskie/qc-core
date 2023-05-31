#pragma once

#include <utility>

#include <qc-core/core-ext.hpp>
#include <qc-core/paging.hpp>

namespace qc
{
    ///
    /// ...
    /// Properties:
    ///   Create: O(1)
    ///   Destroy: O(log(m)), where `m` is the number of free ranges
    ///   Reference stable: Yes
    ///   Index stable: Yes
    ///   Order stable: Yes
    ///   Contiguous elements: No
    ///
    template <typename T>
    class Pool
    {
        template <bool constant> class _Iterator;

      public:

        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using difference_type = s64;
        using size_type = u64;
        using iterator = _Iterator<false>;
        using const_iterator = _Iterator<true>;

        class Unq
        {
            friend Pool;

          public:

            Unq() = default;

            Unq(const Unq &) = delete;
            Unq(Unq && other);

            Unq & operator=(const Unq &) = delete;
            Unq & operator=(Unq && other);

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

            explicit Unq(T & v);

            nodisc u32 & _refN();
        };

        class Shr
        {
            friend Pool;

          public:

            Shr() = default;

            Shr(const Shr & other);
            Shr(Shr && other);

            Shr & operator=(const Shr & other);
            Shr & operator=(Shr && other);

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

            explicit Shr(T & v);

            nodisc u32 & _refN();
        };

        explicit Pool(u64 capacity);

        Pool(const Pool &) = delete;
        Pool(Pool && other);

        Pool & operator=(const Pool &) = delete;
        Pool & operator=(Pool && other);

        ~Pool();

        void shrinkToFit();

        template <typename... Args> nodisc Unq unq(Args &&... args);

        template <typename... Args> nodisc Shr shr(Args &&... args);

        ///
        /// @param ptr an existing shared value of the pool
        /// @return another shr of the given pointer
        ///
        nodisc Shr shrOf(T * ptr);

        nodisc u64 capacity() const;

        nodisc u64 size() const { return _size; }

        nodisc bool empty() const { return _size == 0u; }

        nodisc bool full() const { return _size >= capacity(); }

        nodisc u64 maxPageN() const { return _maxPageN; }

        nodisc u64 pageN() const { return _pageN; }

        nodisc iterator begin();
        nodisc const_iterator begin() const;
        nodisc const_iterator cbegin() const { return begin(); };

        nodisc iterator end();
        nodisc const_iterator end() const;
        nodisc const_iterator cend() const { return end(); };

      private:

        struct alignas(8u) _ChunkMeta
        {
            u32 pageI;
            u32 refN;
        };

        struct _Chunk : _ChunkMeta
        {
            union
            {
                T val;
                _Chunk * nextFreeChunk;
            };

            MSVC_WARNING_SUPPRESS(4624) // This type is never destructed
        };

        // Chunks must be contiguous with head and tail
        static_assert(alignof(_Chunk) <= 8u);

        static void _destroy(T & v);

        u64 _maxPageN{};
        u64 _maxCapacity{};
        u64 _pageN{};
        u64 _size{};
        _Chunk * _chunksStart{};
        _Chunk * _chunksEnd{};
        _Chunk * _firstFreeChunk{};

        template <typename... Args> nodisc T & _create(Args &&... args);

        void _expand();

        void _setHead();
    };

    template <typename T>
    template <bool constant>
    class Pool<T>::_Iterator
    {
        friend class Pool<T>;

        using _T_ = std::conditional_t<constant, const T, T>;
        using _Chunk_ = std::conditional_t<constant, const _Chunk, _Chunk>;

      public:

        using iterator_category = std::forward_iterator_tag;
        using value_type = _T_;
        using reference = _T_ &;
        using pointer = _T_ *;
        using difference_type = s64;

        _Iterator(const _Iterator &) = default;
        _Iterator(const _Iterator<false> &) requires (constant);

        _Iterator & operator=(const _Iterator &) = default;

        nodisc reference operator*() const { return _chunk->val; }

        nodisc pointer operator->() const { return &_chunk->val; }

        _Iterator & operator++();
        _Iterator operator++(int);

        nodisc bool operator==(const _Iterator & other) const = default;

      private:

        _Chunk_ * _chunk{};

        explicit _Iterator(_Chunk_ * chunk);
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    forceinline Pool<T>::Unq::Unq(T & v) :
        _ptr{&v}
    {
        u32 & refN{_refN()};
        assert(!refN);
        refN = ~u32{};
    }

    template <typename T>
    forceinline Pool<T>::Unq::Unq(Unq && other) :
        _ptr{std::exchange(other._ptr, nullptr)}
    {}

    template <typename T>
    inline auto Pool<T>::Unq::operator=(Unq && other) -> Unq &
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
    forceinline Pool<T>::Unq::~Unq()
    {
        reset();
    }

    template <typename T>
    inline void Pool<T>::Unq::reset()
    {
        if (_ptr)
        {
            u32 & refN{_refN()};
            assert(refN == ~u32{});
            refN = 0u;
            _destroy(*std::exchange(_ptr, nullptr));
        }
    }

    template <typename T>
    forceinline u32 & Pool<T>::Unq::_refN()
    {
        return reinterpret_cast<u32 *>(_ptr)[-1];
    }

    template <typename T>
    forceinline Pool<T>::Shr::Shr(T & v) :
        _ptr{&v}
    {
        u32 & refN{_refN()};
        assert(refN != ~u32{});
        ++_refN();
    }

    template <typename T>
    forceinline Pool<T>::Shr::Shr(const Shr & other) :
        _ptr{other._ptr}
    {
        ++_refN();
    }

    template <typename T>
    forceinline Pool<T>::Shr::Shr(Shr && other) :
        _ptr{std::exchange(other._ptr, nullptr)}
    {}

    template <typename T>
    inline auto Pool<T>::Shr::operator=(const Shr & other) -> Shr &
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
    inline auto Pool<T>::Shr::operator=(Shr && other) -> Shr &
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
    forceinline Pool<T>::Shr::~Shr()
    {
        reset();
    }

    template <typename T>
    inline void Pool<T>::Shr::reset()
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
    forceinline u32 & Pool<T>::Shr::_refN()
    {
        return reinterpret_cast<u32 *>(_ptr)[-1];
    }

    template <typename T>
    inline Pool<T>::Pool(const u64 capacity)
    {
        _maxPageN = (sizeof(Pool *) + capacity * sizeof(_Chunk) + sizeof(_ChunkMeta) + (pageSize - 1u)) / pageSize;
        _maxCapacity = (_maxPageN * pageSize - sizeof(Pool *) - sizeof(_ChunkMeta)) / sizeof(_Chunk);
    }

    template <typename T>
    inline Pool<T>::Pool(Pool && other) :
        _maxPageN{std::exchange(other._maxPageN, 0u)},
        _maxCapacity{std::exchange(other._maxCapacity, 0u)},
        _pageN{std::exchange(other._pageN, 0u)},
        _size{std::exchange(other._size, 0u)},
        _chunksStart{std::exchange(other._chunksStart, nullptr)},
        _chunksEnd{std::exchange(other._chunksEnd, nullptr)},
        _firstFreeChunk{std::exchange(other._firstFreeChunk)}
    {

        _setHead();
    }

    template <typename T>
    inline auto Pool<T>::operator=(Pool && other) -> Pool &
    {
        if (&other == this)
        {
            return *this;
        }

        _maxPageN = std::exchange(other._maxPageN, 0u);
        _maxCapacity = std::exchange(other._maxCapacity, 0u);
        _pageN = std::exchange(other._pageN, 0u);
        _size = std::exchange(other._size, 0u);
        _chunksStart = std::exchange(other._chunksStart, nullptr);
        _chunksEnd = std::exchange(other._chunksEnd, nullptr);
        _firstFreeChunk = std::exchange(other._firstFreeChunk, nullptr);

        _setHead();

        return *this;
    }

    template <typename T>
    inline Pool<T>::~Pool()
    {
        assert(!_size);

        // Free memory
        if (_chunksStart)
        {
            freePages(reinterpret_cast<std::byte *>(_chunksStart) - sizeof(Pool *), _maxPageN);
        }

        if constexpr (debug)
        {
            _maxPageN = 0u;
            _maxCapacity = 0u;
            _pageN = 0u;
            _size = 0u;
            _chunksStart = nullptr;
            _chunksEnd = nullptr;
            _firstFreeChunk = nullptr;
        }
    }

    template <typename T>
    inline void Pool<T>::shrinkToFit()
    {
        // NOCOMMIT
        /*
        // Pool is full or unallocated
        if (_freeRanges.empty())
        {
            return;
        }

        _Range & highRange{_freeRanges.front()};

        // The tail of the allocated memory is in use
        if (highRange.end != _slotRange.end)
        {
            return;
        }

        const u64 necessaryCapacity{u64(highRange.start - _slotRange.start)};
        const u64 necessaryPageN{(necessaryCapacity * sizeof(T) + pageSize - 1u) / pageSize};
        const u64 unnecessaryPageN{_pageN - necessaryPageN};

        // Not enough free tail slots to make up a page
        if (!unnecessaryPageN)
        {
            return;
        }

        // Decommit uneccessary pages
        decommitPages(reinterpret_cast<std::byte *>(_slotRange.start) + necessaryPageN * pageSize, unnecessaryPageN);

        // Update state
        _pageN = necessaryPageN;
        const u64 newCapacity{_pageN * pageSize / sizeof(T)};
        _slotRange.end = _slotRange.start + newCapacity;
        highRange.end = _slotRange.end;
        if (highRange.end == highRange.start)
        {
            _freeRanges.erase(_freeRanges.begin());
        }
         */
    }

    template <typename T>
    template <typename... Args>
    inline auto Pool<T>::unq(Args &&... args) -> Unq
    {
        return Unq{_create(std::forward<Args>(args)...)};
    }

    template <typename T>
    template <typename... Args>
    inline auto Pool<T>::shr(Args &&... args) -> Shr
    {
        return Shr{_create(std::forward<Args>(args)...)};
    }

    template <typename T>
    forceinline auto Pool<T>::shrOf(T * const ptr) -> Shr
    {
        if (!ptr)
        {
            return {};
        }

        if constexpr (debug)
        {
            _Chunk & chunk{static_cast<_Chunk &>(reinterpret_cast<_ChunkMeta *>(ptr)[-1])};
            ABORT_IF(&chunk < _chunksStart || &chunk >= _chunksEnd);
            ABORT_IF(chunk.refN == 0u || chunk.refN == ~u32{});
        }

        return Shr{*ptr};
    }

    template <typename T>
    inline u64 Pool<T>::capacity() const
    {
        return _maxCapacity;
    }

    template <typename T>
    inline auto Pool<T>::begin() -> iterator
    {
        if (_chunksStart)
        {
            return  ++iterator{_chunksStart - 1};
        }
        else
        {
            return end();
        }
    }

    template <typename T>
    inline auto Pool<T>::begin() const -> const_iterator
    {
        return ++const_iterator{_chunksStart - 1};
    }

    template <typename T>
    inline auto Pool<T>::end() -> iterator
    {
        return iterator{_chunksEnd};
    }

    template <typename T>
    inline auto Pool<T>::end() const -> const_iterator
    {
        return const_iterator{_chunksEnd};
    }

    template <typename T>
    inline void Pool<T>::_destroy(T & v)
    {
        // Get chunk of value
        _Chunk & chunk{static_cast<_Chunk &>(reinterpret_cast<_ChunkMeta *>(&v)[-1])};

        assert(!chunk.refN);

        // Destruct value
        v.~T();

        // Get pool pointer
        const u64 startOfPageAddr{std::bit_cast<u64>(&chunk) & ~u64(pageSize - 1u)};
        const u64 firstPageAddr{startOfPageAddr - chunk.pageI * pageSize};
        Pool & pool{**std::bit_cast<Pool * *>(firstPageAddr)};

        // Update free chunk chain
        chunk.nextFreeChunk = pool._firstFreeChunk;
        pool._firstFreeChunk = &chunk;

        --pool._size;
    }

    template <typename T>
    template <typename... Args>
    inline T & Pool<T>::_create(Args &&... args)
    {
        if (!_firstFreeChunk) [[unlikely]]
        {
            _expand();
        }

        _Chunk & chunk{*_firstFreeChunk};

        assert(!chunk.refN);

        _firstFreeChunk = chunk.nextFreeChunk;
        ++_size;

        return *(new (&chunk.val) T{std::forward<Args>(args)...});
    }

    template <typename T>
    inline void Pool<T>::_expand()
    {
        // Reserve virtual memory if haven't done so already
        if (!_chunksStart)
        {
            assert(_maxPageN);

            _chunksStart = static_cast<_Chunk *>(static_cast<_ChunkMeta *>(reservePages(_maxPageN)) + 1);
            _chunksEnd = _chunksStart;
        }

        // Ensure we still have more reserved pages
        ABORT_IF(_pageN >= _maxPageN);

        // Double the number of committed pages
        static constexpr u64 minPageN{(sizeof(Pool *) + sizeof(_Chunk) + sizeof(_ChunkMeta) + (pageSize - 1u)) / pageSize};
        u64 newPageN{qc::max(_pageN * 2u, minPageN)};

        // Round up and reserve all pages if within +50% of new page count
        if (newPageN + newPageN / 2 >= _maxPageN)
        {
            newPageN = _maxPageN;
        }

        _Chunk * const newChunksStart{_chunksEnd};

        // Commit new pages
        std::byte * const pages{reinterpret_cast<std::byte *>(_chunksStart) - sizeof(Pool *)};
        commitPages(pages + _pageN * pageSize, newPageN - _pageN);
        _pageN = newPageN;
        const u64 newCapacity{(_pageN * pageSize - sizeof(Pool *) - sizeof(_ChunkMeta)) / sizeof(_Chunk)};
        _chunksEnd = _chunksStart + newCapacity;

        // Setup head
        if (newChunksStart == _chunksStart)
        {
            _setHead();
        }

        // Setup chunks
        for (_Chunk * chunk{newChunksStart}; chunk < _chunksEnd; ++chunk)
        {
            chunk->pageI = u32(u64(reinterpret_cast<std::byte *>(chunk) - pages) / pageSize);
            chunk->refN = 0u;
            chunk->nextFreeChunk = chunk + 1;
        }

        // Setup tail
        _chunksEnd->pageI = u32(_pageN - 1u);
        _chunksEnd->refN = ~u32{};

        // Update next free chunk
        _chunksEnd[-1].nextFreeChunk = _firstFreeChunk;
        _firstFreeChunk = newChunksStart;
    }

    template <typename T>
    inline void Pool<T>::_setHead()
    {
        reinterpret_cast<Pool * *>(_chunksStart)[-1] = this;
    }

    template <typename T>
    template <bool constant>
    inline Pool<T>::_Iterator<constant>::_Iterator(const _Iterator<false> & other) requires (constant) :
        _chunk{other._chunk}
    {}

    template <typename T>
    template <bool constant>
    inline Pool<T>::_Iterator<constant>::_Iterator(_Chunk_ * const chunk) :
        _chunk{chunk}
    {}

    template <typename T>
    template <bool constant>
    inline auto Pool<T>::_Iterator<constant>::operator++() -> _Iterator &
    {
        // NOCOMMIT: Change strategy to store ranges of free chunks
        while (!(++_chunk)->refN);

        return *this;
    }

    template <typename T>
    template <bool constant>
    inline auto Pool<T>::_Iterator<constant>::operator++(int) -> _Iterator
    {
        const _Iterator tmp{*this};
        ++*this;
        return tmp;
    }
}
