#pragma once

#include <utility>

#include <qc-core/core-ext.hpp>
#include <qc-core/paging.hpp>

namespace qc
{
    ///
    /// Provides a reference-stable supply of a specific type of object
    /// Very fast shared pointer reference counting
    /// Stores each element along with an eight byte header, plus an extra element's worth of memory is reserved at the
    ///   start and end of the allocated memory for the purposes of pool object pointer tracking and iteration
    /// Properties:
    ///   Create: O(1)
    ///   Destroy: O(1)
    ///   Iteration: O(1) per increment
    ///   Reference stable: Yes
    ///   Index stable: Yes
    ///   Order stable: Yes
    ///   Contiguous elements: No
    ///
    template <typename T>
    class Pool
    {
        friend struct PoolFriend;

        template <bool constant> class _Iterator;

        struct alignas(8u) _ChunkMeta
        {
            u32 refN;
            u32 pageI;
        };

        struct _BubbleInfo
        {
            u32 ordinal; // Indicates the relative position of a bubble in the chain, descending
            u32 headTailOffset; // Size of bubble minus one
            s32 prevOffset; // Offset from bubble head to previous bubble head
            s32 nextOffset; // Offset from bubble head to next bubble head
        };

        struct _Chunk : _ChunkMeta
        {
            union
            {
                T val;
                _BubbleInfo bubble;
                Pool * poolPtr; // Only set for head chunk
            };

            ~_Chunk() = delete; // Prevents warnings about union not being destructed properly

            nodisc Pool & pool();

            nodisc forceinline _Chunk * bubbleHead() { return this - bubble.headTailOffset; }
            nodisc forceinline _Chunk * bubbleTail() { return this + bubble.headTailOffset; }

            nodisc forceinline _Chunk * prevBubble() { return this + bubble.prevOffset; }
            nodisc forceinline _Chunk * nextBubble() { return this + bubble.nextOffset; }
        };

      public:

        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using difference_type = s64;
        using size_type = u64;
        using iterator = _Iterator<false>;
        using const_iterator = _Iterator<true>;

        template <bool constant>
        class UnqT
        {
            friend Pool;

            using _T = ConstIf<T, constant>;

          public:

            UnqT() = default;

            UnqT(const UnqT &) = delete;
            UnqT(UnqT && other);
            forceinline UnqT(UnqT<false> && other) requires (constant) : UnqT{reinterpret_cast<UnqT &&>(other)} {}

            UnqT & operator=(const UnqT &) = delete;
            UnqT & operator=(UnqT && other);
            forceinline UnqT & operator=(UnqT<false> && other) requires constant { return *this = reinterpret_cast<UnqT &&>(other); }

            ~UnqT();

            nodisc forceinline operator UnqT<true> &() & requires (!constant) { return reinterpret_cast<UnqT<true> &>(*this); }
            nodisc forceinline operator const UnqT<true> &() const & requires (!constant) { return reinterpret_cast<const UnqT<true> &>(*this); }

            void reset();

            nodisc forceinline explicit operator bool() const { return bool(_chunk); }

            nodisc forceinline _T & operator*() const { return _chunk->val; }

            nodisc forceinline _T * operator->() const { return &_chunk->val; }

            bool operator==(const UnqT &) const = default;
            nodisc forceinline friend bool operator==(const UnqT & a, const T * b) { return &a._chunk->val == b; }
            nodisc forceinline friend bool operator==(const T * a, const UnqT & b) { return a == &b._chunk->val; }

          private:

            _Chunk * _chunk{};

            explicit UnqT(_Chunk * chunk);
        };

        using Unq = UnqT<false>;
        using CUnq = UnqT<true>;

        template <bool constant>
        class ShrT
        {
            friend Pool;

            using _T = ConstIf<T, constant>;

          public:

            ShrT() = default;

            ShrT(const ShrT & other);
            ShrT(ShrT && other);
            forceinline ShrT(ShrT<false> && other) requires (constant) : ShrT{reinterpret_cast<ShrT &&>(other)} {}

            ShrT & operator=(const ShrT & other);
            ShrT & operator=(ShrT && other);
            forceinline ShrT & operator=(ShrT<false> && other) requires constant { return *this = reinterpret_cast<ShrT &&>(other); }

            ~ShrT();

            nodisc forceinline operator ShrT<true> &() & requires (!constant) { return reinterpret_cast<ShrT<true> &>(*this); }
            nodisc forceinline operator const ShrT<true> &() const & requires (!constant) { return reinterpret_cast<const ShrT<true> &>(*this); }

            void reset();

            nodisc forceinline explicit operator bool() const { return bool(_chunk); }

            nodisc forceinline _T & operator*() const { return _chunk->val; }

            nodisc forceinline _T * operator->() const { return &_chunk->val; }

            bool operator==(const ShrT &) const = default;
            nodisc forceinline friend bool operator==(const ShrT & a, const T * b) { return &a._chunk->val == b; }
            nodisc forceinline friend bool operator==(const T * a, const ShrT & b) { return a == &b._chunk->val; }

          private:

            _Chunk * _chunk{};

            explicit ShrT(_Chunk * chunk);
        };

        using Shr = ShrT<false>;
        using CShr = ShrT<true>;

        explicit Pool(u64 capacity);

        Pool(const Pool &) = delete;
        Pool(Pool && other);

        Pool & operator=(const Pool &) = delete;
        Pool & operator=(Pool && other);

        ~Pool();

        void shrinkToFit();

        template <typename... Args> nodisc Unq unq(Args &&... args);
        template <typename... Args> nodisc CUnq cunq(Args &&... args);

        template <typename... Args> nodisc Shr shr(Args &&... args);
        template <typename... Args> nodisc CShr cshr(Args &&... args);

        ///
        /// @param ptr an existing shared value of the pool
        /// @return another shr of the given pointer
        ///
        nodisc Shr shrOf(T * ptr);

        nodisc u64 capacity() const;

        nodisc u64 size() const { return _size; }

        nodisc bool empty() const { return !_size; }

        nodisc bool full() const { return _size >= capacity(); }

        nodisc u64 reservedPageN() const { return _reservedPageN; }

        nodisc u64 committedPageN() const { return _committedPageN; }

        nodisc iterator begin();
        nodisc const_iterator begin() const;
        nodisc const_iterator cbegin() const { return begin(); };

        nodisc iterator end();
        nodisc const_iterator end() const;
        nodisc const_iterator cend() const { return end(); };

      private:

        // Limited by max `prevOffset`/`nextOffset` values
        static constexpr u64 _maxBubbleSize{1u << 31};

        static void _destroy(_Chunk * chunk);

        u64 _reservedPageN{};
        u64 _committedPageN{};
        u64 _size{};
        _Chunk * _chunksStart{};
        _Chunk * _chunksEnd{};
        _Chunk * _firstBubble{};

        template <typename... Args> nodisc _Chunk * _create(Args &&... args);

        void _expand();

        void _setupHeadChunk();

        void _setupTailChunk();
    };

    template <typename T>
    template <bool constant>
    class Pool<T>::_Iterator
    {
        friend class Pool<T>;

        using _T = ConstIf<T, constant>;
        using _Chunk = ConstIf<_Chunk, constant>;

      public:

        using iterator_category = std::forward_iterator_tag;
        using value_type = _T;
        using reference = _T &;
        using pointer = _T *;
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

        _Chunk * _chunk{};

        explicit _Iterator(_Chunk * chunk);
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    forceinline Pool<T> & Pool<T>::_Chunk::pool()
    {
        const u64 startOfPageAddr{std::bit_cast<u64>(this) & ~u64(pageSize - 1u)};
        const u64 firstPageAddr{startOfPageAddr - this->pageI * pageSize};
        return *std::bit_cast<_Chunk *>(firstPageAddr)->poolPtr;
    }

    template <typename T>
    template <bool constant>
    forceinline Pool<T>::UnqT<constant>::UnqT(_Chunk * const chunk) :
        _chunk{chunk}
    {
        assert(!_chunk->refN);

        _chunk->refN = 1u;
    }

    template <typename T>
    template <bool constant>
    forceinline Pool<T>::UnqT<constant>::UnqT(UnqT && other) :
        _chunk{other._chunk}
    {
        other._chunk = nullptr;
    }

    template <typename T>
    template <bool constant>
    inline auto Pool<T>::UnqT<constant>::operator=(UnqT && other) -> UnqT &
    {
        if (&other == this)
        {
            return *this;
        }

        reset();

        _chunk = other._chunk;
        other._chunk = nullptr;

        return *this;
    }

    template <typename T>
    template <bool constant>
    forceinline Pool<T>::UnqT<constant>::~UnqT()
    {
        reset();
    }

    template <typename T>
    template <bool constant>
    inline void Pool<T>::UnqT<constant>::reset()
    {
        if (_chunk)
        {
            assert(_chunk->refN == 1u);
            _chunk->refN = 0u;
            _destroy(_chunk);
            _chunk = nullptr;
        }
    }

    template <typename T>
    template <bool constant>
    forceinline Pool<T>::ShrT<constant>::ShrT(_Chunk * const chunk) :
        _chunk{chunk}
    {
        ++_chunk->refN;
    }

    template <typename T>
    template <bool constant>
    forceinline Pool<T>::ShrT<constant>::ShrT(const ShrT & other) :
        _chunk{other._chunk}
    {
        if (_chunk)
        {
            ++_chunk->refN;
        }
    }

    template <typename T>
    template <bool constant>
    forceinline Pool<T>::ShrT<constant>::ShrT(ShrT && other) :
        _chunk{other._chunk}
    {
        other._chunk = nullptr;
    }

    template <typename T>
    template <bool constant>
    inline auto Pool<T>::ShrT<constant>::operator=(const ShrT & other) -> ShrT &
    {
        if (&other == this)
        {
            return *this;
        }

        reset();

        _chunk = other._chunk;

        if (_chunk)
        {
            ++_chunk->refN;
        }

        return *this;
    }

    template <typename T>
    template <bool constant>
    inline auto Pool<T>::ShrT<constant>::operator=(ShrT && other) -> ShrT &
    {
        if (&other == this)
        {
            return *this;
        }

        reset();

        _chunk = other._chunk;
        other._chunk = nullptr;

        return *this;
    }

    template <typename T>
    template <bool constant>
    forceinline Pool<T>::ShrT<constant>::~ShrT()
    {
        reset();
    }

    template <typename T>
    template <bool constant>
    inline void Pool<T>::ShrT<constant>::reset()
    {
        if (_chunk)
        {
            assert(_chunk->refN >= 1u);

            if (!--_chunk->refN)
            {
                _destroy(_chunk);
                _chunk = nullptr;
            }
        }
    }

    template <typename T>
    inline Pool<T>::Pool(const u64 capacity)
    {
        _reservedPageN = ((capacity + 2u) * sizeof(_Chunk) + (pageSize - 1u)) / pageSize;

        // Limited by max bubble size
        ABORT_IF(this->capacity() > _maxBubbleSize);
    }

    template <typename T>
    inline Pool<T>::Pool(Pool && other) :
        _reservedPageN{other._reservedPageN},
        _committedPageN{other._committedPageN},
        _size{other._size},
        _chunksStart{other._chunksStart},
        _chunksEnd{other._chunksEnd},
        _firstBubble{other._firstBubble}
    {
        other._reservedPageN = 0u;
        other._committedPageN = 0u;
        other._size = 0u;
        other._chunksStart = nullptr;
        other._chunksEnd = nullptr;
        other._firstBubble = nullptr;

        if (_chunksStart)
        {
            _chunksStart[-1].poolPtr = this;
        }
    }

    template <typename T>
    inline auto Pool<T>::operator=(Pool && other) -> Pool &
    {
        if (&other == this)
        {
            return *this;
        }

        _reservedPageN = other._reservedPageN;
        _committedPageN = other._committedPageN;
        _size = other._size;
        _chunksStart = other._chunksStart;
        _chunksEnd = other._chunksEnd;
        _firstBubble = other._firstBubble;

        other._reservedPageN = 0u;
        other._committedPageN = 0u;
        other._size = 0u;
        other._chunksStart = nullptr;
        other._chunksEnd = nullptr;
        other._firstBubble = nullptr;

        if (_chunksStart)
        {
            _chunksStart[-1].poolPtr = this;
        }

        return *this;
    }

    template <typename T>
    inline Pool<T>::~Pool()
    {
        assert(!_size);

        // Free memory
        if (_chunksStart)
        {
            freePages(_chunksStart - 1, _reservedPageN);
        }
    }

    template <typename T>
    inline void Pool<T>::shrinkToFit()
    {
        // Definitely no room to shrink
        if (!_firstBubble)
        {
            return;
        }

        // Can completely decommit memory
        if (!_size)
        {
            if (_committedPageN)
            {
                decommitPages(_chunksStart - 1, _committedPageN);
                _committedPageN = 0u;
                _chunksEnd = _chunksStart;
                _firstBubble = nullptr;
            }

            return;
        }

        // Find last bubble
        _Chunk * bubble{_firstBubble};
        for (_Chunk * b{bubble}; b->bubble.nextOffset; )
        {
            b = b->nextBubble();
            maxify(bubble, b);
        }

        // Bubble must be adjacent to end of memory
        if (bubble->bubbleTail() + 1 < _chunksEnd)
        {
            return;
        }

        const u64 neededPageN{bubble->pageI + 1u};
        const u64 excessPageN{_committedPageN - neededPageN};

        // Must be able to free at least one page
        if (!excessPageN)
        {
            return;
        }

        // Decommit excess pages
        const u64 newMemSize{neededPageN * pageSize};
        decommitPages(reinterpret_cast<std::byte *>(_chunksStart - 1) + newMemSize, excessPageN);
        _committedPageN = neededPageN;
        const u64 newChunksN{newMemSize / sizeof(_Chunk)};
        _chunksEnd = _chunksStart + newChunksN - 2u;

        // Fix bubble
        // Bubble should shrink
        if (bubble < _chunksEnd)
        {
            bubble->bubble.headTailOffset = u32((_chunksEnd - 1) - bubble);
        }
        // Bubble should be removed
        else
        {
            if (bubble->bubble.prevOffset && bubble->bubble.nextOffset)
            {
                _Chunk * const prevBubble{bubble->prevBubble()};
                _Chunk * const nextBubble{bubble->nextBubble()};
                prevBubble->bubble.nextOffset = s32(nextBubble - prevBubble);
                nextBubble->bubble.prevOffset = -prevBubble->bubble.nextOffset;
            }
            else if (bubble->bubble.prevOffset)
            {
                bubble->prevBubble()->bubble.nextOffset = 0;
            }
            else if (bubble->bubble.nextOffset)
            {
                _Chunk * const nextBubble{bubble->nextBubble()};
                nextBubble->bubble.prevOffset = 0;
                _firstBubble = nextBubble;
            }
            else
            {
                _firstBubble = nullptr;
            }
        }

        // Setup tail chunk (must happen last, would overwrite bubble if it's fully erased)
        _setupTailChunk();
    }

    template <typename T>
    template <typename... Args>
    inline auto Pool<T>::unq(Args &&... args) -> Unq
    {
        return Unq{_create(std::forward<Args>(args)...)};
    }

    template <typename T>
    template <typename... Args>
    inline auto Pool<T>::cunq(Args &&... args) -> CUnq
    {
        return CUnq{_create(std::forward<Args>(args)...)};
    }

    template <typename T>
    template <typename... Args>
    inline auto Pool<T>::shr(Args &&... args) -> Shr
    {
        return Shr{_create(std::forward<Args>(args)...)};
    }

    template <typename T>
    template <typename... Args>
    inline auto Pool<T>::cshr(Args &&... args) -> CShr
    {
        return CShr{_create(std::forward<Args>(args)...)};
    }

    template <typename T>
    forceinline auto Pool<T>::shrOf(T * const ptr) -> Shr
    {
        if (!ptr)
        {
            return {};
        }

        _Chunk * const chunk{static_cast<_Chunk *>(reinterpret_cast<_ChunkMeta *>(ptr) - 1)};

        assert(chunk >= _chunksStart && chunk < _chunksEnd);
        assert(chunk->refN);

        return Shr{chunk};
    }

    template <typename T>
    inline u64 Pool<T>::capacity() const
    {
        return _reservedPageN * pageSize / sizeof(_Chunk) - 2u;
    }

    template <typename T>
    inline auto Pool<T>::begin() -> iterator
    {
        if (_chunksStart)
        {
            return ++iterator{_chunksStart - 1};
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
    inline void Pool<T>::_destroy(_Chunk * const chunk)
    {
        assert(!chunk->refN);

        Pool & pool{chunk->pool()};

        // Destruct value
        chunk->val.~T();

        // Update bubbles
        _Chunk * const prevChunk{chunk - 1};
        _Chunk * const nextChunk{chunk + 1};

        // If adjacent to two existing bubbles, combine
        if (!prevChunk->refN && !nextChunk->refN)
        {
            _Chunk * const bubble{prevChunk->bubbleHead()};
            _Chunk * const bubbleAlt{nextChunk};

            // Update head and tail
            bubble->bubble.headTailOffset += bubbleAlt->bubble.headTailOffset + 2u;
            bubble->bubbleTail()->bubble.headTailOffset = bubble->bubble.headTailOffset;

            // Bubbles A - F are laid out logically in chain order, left to right, highest ordinal to lowest
            // Memory sequence and bubble sequence are opposite; naive merge would result in a loop in the chain
            const bool inOrder{bubble->bubble.ordinal > bubbleAlt->bubble.ordinal};
            _Chunk * const bubbleB{inOrder ? bubble : bubbleAlt};
            _Chunk * const bubbleE{inOrder ? bubbleAlt : bubble};

            _Chunk * const bubbleA{bubbleB->bubble.prevOffset ? bubbleB->prevBubble() : nullptr};
            _Chunk * const bubbleC{bubbleB->bubble.nextOffset ? bubbleB->nextBubble() : nullptr};
            _Chunk * const bubbleD{bubbleE->bubble.prevOffset ? bubbleE->prevBubble() : nullptr};
            _Chunk * const bubbleF{bubbleE->bubble.nextOffset ? bubbleE->nextBubble() : nullptr};

            // Update ordinal
            bubble->bubble.ordinal = bubbleE->bubble.ordinal;

            // Update bubble chain

            if (bubbleC != bubbleE)
            {
                if (bubbleA)
                {
                    bubbleA->bubble.nextOffset = s32(bubbleC - bubbleA);
                    bubbleC->bubble.prevOffset = -bubbleA->bubble.nextOffset;
                }
                else
                {
                    pool._firstBubble = bubbleC;
                    bubbleC->bubble.prevOffset = 0;
                }

                bubbleD->bubble.nextOffset = s32(bubble - bubbleD);
                bubble->bubble.prevOffset = -bubbleD->bubble.nextOffset;
            }
            else
            {
                if (bubbleA)
                {
                    bubbleA->bubble.nextOffset = s32(bubble - bubbleA);
                    bubble->bubble.prevOffset = -bubbleA->bubble.nextOffset;
                }
                else
                {
                    pool._firstBubble = bubble;
                    bubble->bubble.prevOffset = 0;
                }
            }

            if (bubbleF)
            {
                bubble->bubble.nextOffset = s32(bubbleF - bubble);
                bubbleF->bubble.prevOffset = -bubble->bubble.nextOffset;
            }
            else
            {
                bubble->bubble.nextOffset = 0;
            }
        }
        // Otherwise if adjacent only to bubble tail, expand it
        else if (!prevChunk->refN)
        {
            // Update head
            _Chunk * const bubbleHead{prevChunk->bubbleHead()};
            ++bubbleHead->bubble.headTailOffset;

            // Update tail
            chunk->bubble.headTailOffset = bubbleHead->bubble.headTailOffset;
        }
        // Otherwise if adjacent only to bubble head, expand it
        else if (!nextChunk->refN)
        {
            // Update head
            chunk->bubble = nextChunk->bubble;
            ++chunk->bubble.headTailOffset;

            // Update tail
            chunk->bubbleTail()->bubble.headTailOffset = chunk->bubble.headTailOffset;

            // Update previous bubble
            if (chunk->bubble.prevOffset)
            {
                ++chunk->bubble.prevOffset;
                --chunk->prevBubble()->bubble.nextOffset;
            }
            else
            {
                pool._firstBubble = chunk;
            }

            // Update next bubble
            if (chunk->bubble.nextOffset)
            {
                ++chunk->bubble.nextOffset;
                --chunk->nextBubble()->bubble.prevOffset;
            }
        }
        // Otherwise create new bubble
        else
        {
            // Update bubble chain
            if (pool._firstBubble)
            {
                chunk->bubble.nextOffset = s32(pool._firstBubble - chunk);
                pool._firstBubble->bubble.prevOffset = -chunk->bubble.nextOffset;
                chunk->bubble.ordinal = pool._firstBubble->bubble.ordinal + 1u;
            }
            else
            {
                chunk->bubble.nextOffset = 0;
                chunk->bubble.ordinal = 0u;
            }

            chunk->bubble.headTailOffset = 0u;
            chunk->bubble.prevOffset = 0;
            pool._firstBubble = chunk;
        }

        --pool._size;
    }

    template <typename T>
    template <typename... Args>
    inline auto Pool<T>::_create(Args &&... args) -> _Chunk *
    {
        if (!_firstBubble) [[unlikely]]
        {
            _expand();
        }

        _Chunk * const chunk{_firstBubble};

        assert(!chunk->refN);

        // If bubble has at least two slots, push head back
        if (_firstBubble->bubble.headTailOffset)
        {
            ++_firstBubble;

            // Update head/tail
            _firstBubble->bubble = chunk->bubble;
            --_firstBubble->bubble.headTailOffset;
            _firstBubble->bubbleTail()->bubble.headTailOffset = _firstBubble->bubble.headTailOffset;

            // Update bubble chain
            if (_firstBubble->bubble.nextOffset)
            {
                --_firstBubble->bubble.nextOffset;
                ++_firstBubble->nextBubble()->bubble.prevOffset;
            }
        }
        // Otherwise, this bubble is done
        else
        {
            // Update bubble chain
            if (_firstBubble->bubble.nextOffset)
            {
                _firstBubble = _firstBubble->nextBubble();
                _firstBubble->bubble.prevOffset = 0;
            }
            else
            {
                _firstBubble = nullptr;
            }
        }

        new (&chunk->val) T{std::forward<Args>(args)...};

        ++_size;

        return chunk;
    }

    template <typename T>
    inline void Pool<T>::_expand()
    {
        // Reserve virtual memory if haven't done so already
        if (!_chunksStart)
        {
            assert(_reservedPageN);

            _chunksStart = static_cast<_Chunk *>(reservePages(_reservedPageN)) + 1;
            _chunksEnd = _chunksStart;
        }

        // Ensure we still have more reserved pages
        ABORT_IF(_committedPageN >= _reservedPageN);

        // Double the number of committed pages
        static constexpr u64 minPageN{(sizeof(_Chunk) * 3u + (pageSize - 1u)) / pageSize};
        u64 newPageN{qc::max(_committedPageN * 2u, minPageN)};

        // Round up and reserve all pages if within +50% of new page count
        if (newPageN + newPageN / 2u >= _reservedPageN)
        {
            newPageN = _reservedPageN;
        }

        _Chunk * const newChunksStart{_chunksEnd};

        // Commit new pages
        std::byte * const pages{reinterpret_cast<std::byte *>(_chunksStart - 1)};
        commitPages(pages + _committedPageN * pageSize, newPageN - _committedPageN);
        _committedPageN = newPageN;
        const u64 newCapacity{_committedPageN * pageSize / sizeof(_Chunk) - 2u};
        _chunksEnd = _chunksStart + newCapacity;

        // Setup head
        if (newChunksStart == _chunksStart)
        {
            _setupHeadChunk();
        }

        // Setup chunks
        for (_Chunk * chunk{newChunksStart}; chunk < _chunksEnd; ++chunk)
        {
            chunk->refN = 0u;
            chunk->pageI = u32(u64(chunk - (_chunksStart - 1)) * sizeof(_Chunk) / pageSize);
        }

        // Setup tail
        _setupTailChunk();

        // Setup bubble
        assert(!_firstBubble); // Should only be expanding if no empty slots
        _firstBubble = newChunksStart;
        newChunksStart->bubble.ordinal = 0u;
        newChunksStart->bubble.headTailOffset = u32(_chunksEnd - 1 - newChunksStart);
        newChunksStart->bubble.prevOffset = 0;
        newChunksStart->bubble.nextOffset = 0;
        newChunksStart->bubbleTail()->bubble.headTailOffset = newChunksStart->bubble.headTailOffset;
    }

    template <typename T>
    inline void Pool<T>::_setupHeadChunk()
    {
        _chunksStart[-1].refN = ~u32{};
        _chunksStart[-1].pageI = 0u;
        _chunksStart[-1].poolPtr = this;
    }

    template <typename T>
    inline void Pool<T>::_setupTailChunk()
    {
        _chunksEnd->refN = ~u32{};
        _chunksEnd->pageI = u32(_committedPageN - 1u);
    }

    template <typename T>
    template <bool constant>
    inline Pool<T>::_Iterator<constant>::_Iterator(const _Iterator<false> & other) requires (constant) :
        _chunk{other._chunk}
    {}

    template <typename T>
    template <bool constant>
    inline Pool<T>::_Iterator<constant>::_Iterator(_Chunk * const chunk) :
        _chunk{chunk}
    {}

    template <typename T>
    template <bool constant>
    inline auto Pool<T>::_Iterator<constant>::operator++() -> _Iterator &
    {
        ++_chunk;

        if (!_chunk->refN)
        {
            _chunk += s64(_chunk->bubble.headTailOffset) + 1;
        }

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
