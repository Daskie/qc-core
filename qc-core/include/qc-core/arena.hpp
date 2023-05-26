#pragma once

#include <qc-core/bubble-tracker.hpp>
#include <qc-core/paging.hpp>
#include <qc-core/smart-pointer.hpp>

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

        struct Deallocator
        {
            void operator()(void * ptr) const;
        };

        template <typename T> using Unq = Unq<T, Deallocator>;
        template <typename T> using Shr = Shr<T, Deallocator>;

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
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    inline void Arena::Deallocator::operator()(void * const ptr) const
    {
        _Chunk & header{Arena::_header(ptr)};
        header.arena->_bubbles.add(&header, 1 + header.valChunkN);
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
    forceinline auto Arena::unq(Args &&... args) -> Unq<T>
    {
        return Unq<T>{IKnowWhatImDoing{}, _create<T>(std::forward<Args>(args)...)};
    }

    template <typename T, typename... Args>
    forceinline auto Arena::shr(Args &&... args) -> Shr<T>
    {
        return Shr<T>{IKnowWhatImDoing{}, _create<T>(std::forward<Args>(args)...)};
    }

    template <typename T>
    forceinline auto Arena::shr(T * const ptr) -> Shr<T>
    {
        if constexpr (debug)
        {
            _Chunk & header{_header(ptr)};
            ABORT_IF(header.arena != this);
            ABORT_IF(!header.refN);
        }

        return Shr<T>{IKnowWhatImDoing{}, ptr};
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
}
