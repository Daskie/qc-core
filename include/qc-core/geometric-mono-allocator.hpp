#pragma once

#include <cassert>

#include <array>
#include <bit>
#include <exception>

#include <qc-core/core.hpp>

namespace qc
{
    ///
    /// Simple, fast single-element allocator whose backing memory capacity is increasing powers of two
    ///
    /// Example growth over time:
    ///   Capacity  2: AA -- ---- --------
    ///   Capacity  4: AA BB ---- --------
    ///   Capacity  8: AA BB CCCC --------
    ///   Capacity 16: AA BB CCCC DDDDDDDD
    ///
    template <size_t slotSize, size_t slotAlignment>
    class GeometricMonoAllocator
    {
        static_assert(std::has_single_bit(slotSize));
        static_assert(std::has_single_bit(slotAlignment));

        public: //--------------------------------------------------------------

        // Must be a power of two
        inline static constexpr size_t defaultInitialCapacity{256u};

        GeometricMonoAllocator() noexcept = default;
        explicit GeometricMonoAllocator(size_t initialCapacity) noexcept;

        GeometricMonoAllocator(const GeometricMonoAllocator &) = delete;
        GeometricMonoAllocator(GeometricMonoAllocator && other) noexcept;

        GeometricMonoAllocator & operator=(const GeometricMonoAllocator &) = delete;
        GeometricMonoAllocator & operator=(GeometricMonoAllocator && other) noexcept;

        ~GeometricMonoAllocator() noexcept;

        void reserve(size_t capacity);

        [[nodiscard]] void * allocate();

        void deallocate(void * ptr) noexcept(qc::debug);

        size_t capacity() const noexcept { return _capacity; }

        size_t count() const noexcept { return _allocatedCount; }

        private: //-------------------------------------------------------------

        union _ReleaseSlot
        {
            alignas(slotAlignment) std::byte data[slotSize];
            _ReleaseSlot * nextFree;
        };

        struct _DebugSlot
        {
            alignas(slotAlignment) std::byte data[slotSize];
            _DebugSlot * nextFree;
        };

        using _Slot = std::conditional_t<qc::debug, _DebugSlot, _ReleaseSlot>;

        inline static _Slot * const _special{std::bit_cast<_Slot *>(~uintptr_t{0u})};

        size_t _capacity{defaultInitialCapacity};
        size_t _allocatedCount{};
        size_t _memoryCount{};
        std::array<_Slot *, 32u> _memories;
        _Slot * _nextFree{};

        // Takes current tail and returns next tail
        _Slot * & _expand(_Slot * & tail);

        _Slot * & _findTail() noexcept;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <size_t slotSize, size_t slotAlignment>
    GeometricMonoAllocator<slotSize, slotAlignment>::GeometricMonoAllocator(const size_t initialCapacity) noexcept :
        _capacity{std::bit_ceil(initialCapacity)}
    {
        assert(initialCapacity > 0u);
    }

    template <size_t slotSize, size_t slotAlignment>
    GeometricMonoAllocator<slotSize, slotAlignment>::GeometricMonoAllocator(GeometricMonoAllocator && other) noexcept :
        _capacity{std::exchange(other._capacity, defaultInitialCapacity)},
        _allocatedCount{std::exchange(other._allocatedCount, 0u)},
        _memoryCount{std::exchange(other._memoryCount, 0u)},
        _nextFree{std::exchange(other._nextFree, nullptr)}
    {}

    template <size_t slotSize, size_t slotAlignment>
    GeometricMonoAllocator<slotSize, slotAlignment> & GeometricMonoAllocator<slotSize, slotAlignment>::operator=(GeometricMonoAllocator && other) noexcept
    {
        _capacity = std::exchange(other._capacity, defaultInitialCapacity);
        _allocatedCount = std::exchange(other._allocatedCount, 0u);
        _memoryCount = std::exchange(other._memoryCount, 0u);
        _nextFree = std::exchange(other._nextFree, nullptr);
    }

    template <size_t slotSize, size_t slotAlignment>
    GeometricMonoAllocator<slotSize, slotAlignment>::~GeometricMonoAllocator() noexcept
    {
        assert(_allocatedCount == 0u);

        for (size_t memoryI{0u}; memoryI < _memoryCount; ++memoryI)
        {
            ::operator delete(_memories[memoryI]);
        }

        if constexpr (qc::debug)
        {
            _capacity = 0u;
            _allocatedCount = 0u;
            _memoryCount = 0u;
            _nextFree = nullptr;
        }
    }

    template <size_t slotSize, size_t slotAlignment>
    void GeometricMonoAllocator<slotSize, slotAlignment>::reserve(const size_t capacity)
    {
        if (!_memoryCount)
        {
            qc::maxify(_capacity, std::bit_ceil(capacity));
        }
        else if (_capacity < capacity)
        {
            _Slot * * tail{&_findTail()};
            do
            {
                tail = &_expand(*tail);
            } while (_capacity < capacity);
        }
    }

    template <size_t slotSize, size_t slotAlignment>
    void * GeometricMonoAllocator<slotSize, slotAlignment>::allocate()
    {
        if (!_nextFree) [[unlikely]]
        {
            _expand(_nextFree);
        }

        _Slot * const slot{_nextFree};
        _nextFree = slot->nextFree;
        if constexpr (qc::debug)
        {
            slot->nextFree = _special;
        }
        ++_allocatedCount;
        return slot;
    }

    template <size_t slotSize, size_t slotAlignment>
    void GeometricMonoAllocator<slotSize, slotAlignment>::deallocate(void * ptr) noexcept(qc::debug)
    {
        _Slot * const slot{reinterpret_cast<_Slot *>(ptr)};

        // Check that the slot is currently allocated
        assert(slot->nextFree == _special);

        slot->nextFree = _nextFree;
        _nextFree = slot;
        --_allocatedCount;
    }

    template <size_t slotSize, size_t slotAlignment>
    auto GeometricMonoAllocator<slotSize, slotAlignment>::_expand(_Slot * & tail) -> _Slot * &
    {
        // `_capacity` will always be greater than zero
        const size_t newSlotsCount{_capacity};

        // Allocate new slab of memory
        _Slot * & newSlots{_memories.at(_memoryCount)};
        static_assert(slotAlignment <= __STDCPP_DEFAULT_NEW_ALIGNMENT__);
        newSlots = static_cast<_Slot *>(::operator new(newSlotsCount * sizeof(_Slot)));
        if (_memoryCount) _capacity *= 2u;
        ++_memoryCount;

        // Establish free links
        _Slot * const lastSlot{newSlots + newSlotsCount - 1u};
        for (_Slot * slot{newSlots}; slot < lastSlot; ++slot)
        {
            slot->nextFree = slot + 1;
        }
        lastSlot->nextFree = _nextFree;
        tail = newSlots;

        return lastSlot->nextFree;
    }

    template <size_t slotSize, size_t slotAlignment>
    auto GeometricMonoAllocator<slotSize, slotAlignment>::_findTail() noexcept -> _Slot * &
    {
        _Slot * * tail{&_nextFree};
        while (*tail) tail = &(*tail)->nextFree;
        return *tail;
    }
}
