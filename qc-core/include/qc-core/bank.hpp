#pragma once

#include <bit>

#include <qc-core/core.hpp>
#include <qc-core/list.hpp>

namespace qc
{
    template <typename T>
    class Bank
    {
        static_assert(std::is_move_constructible_v<T>);

      public:

        Bank() = default;

        Bank(const Bank &) = delete;
        Bank(Bank && other);

        Bank & operator=(const Bank &) = delete;
        Bank & operator=(Bank && other);

        ~Bank();

        void reserve(u32 capacity);

        struct NewElement { T & v; u32 i; };

        template <typename... Args> nodisc NewElement create(Args && ... args);

        nodisc T & operator[](u32 i);
        nodisc const T & operator[](u32 i) const;

        void destroy(u32 i);

        void clear();

        nodisc u32 size() const { return _size; }

        nodisc bool empty() const { return _size == 0u; }

        nodisc u32 capacity() const { return _capacity; }

      private:

        union _Slot
        {
            u32 nextFreeI;
            T value;

            ~_Slot() = delete;
        };

        static_assert(sizeof(_Slot) == sizeof(T)); // Necessary for backing array values to be contiguous

        inline constexpr static u32 _minCapacity{16u}; // Must be power of two
        inline constexpr static u32 _invalidI{~u32(0u)};

        _Slot * _slots{};
        u32 _capacity{};
        u32 _size{};
        u32 _headFreeI{_invalidI};

        void _expand(u32 newCapacity);

        // TODO: Dynamic bit field
        nodisc List<bool> _makeFreeMap() const;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    inline Bank<T>::Bank(Bank && other) :
        _slots{std::exchange(other._slots, nullptr)},
        _capacity{std::exchange(other._capacity, 0u)},
        _size{std::exchange(other._size, 0u)},
        _headFreeI{std::exchange(other._headFreeI, _invalidI)}
    {}

    template <typename T>
    inline Bank<T> & Bank<T>::operator=(Bank && other)
    {
        if (&other == this)
        {
            return *this;
        }

        _slots = std::exchange(other._slots, nullptr);
        _capacity = std::exchange(other._capacity, 0u);
        _size = std::exchange(other._size, 0u);
        _headFreeI = std::exchange(other._headFreeI, _invalidI);

        return *this;
    }

    template <typename T>
    inline Bank<T>::~Bank()
    {
        // Destroy elements and free memory
        if (_slots)
        {
            if constexpr (!std::is_trivially_destructible_v<T>)
            {
                clear();
            }

            ::operator delete(_slots, std::align_val_t{alignof(T)});
        }

        // Reset state
        if constexpr (qc::debug)
        {
            _slots = nullptr;
            _capacity = 0u;
            _size = 0u;
            _headFreeI = _invalidI;
        }
    }

    template <typename T>
    inline void Bank<T>::reserve(u32 capacity)
    {
        if (capacity > _capacity)
        {
            _expand(qc::max(std::bit_ceil(capacity), _minCapacity));
        }
    }

    template <typename T>
    template <typename... Args>
    inline auto Bank<T>::create(Args &&... args) -> NewElement
    {
        if (_headFreeI == _invalidI) [[unlikely]]
        {
            _expand(qc::max(_capacity * 2u, _minCapacity));
        }

        const u32 i{_headFreeI};
        _Slot & slot{_slots[i]};
        _headFreeI = slot.nextFreeI;
        new (&slot.value) T{std::forward<Args>(args)...};
        ++_size;

        return {slot.value, i};
    }

    template <typename T>
    inline T & Bank<T>::operator[](const u32 i)
    {
        return _slots[i].value;
    }

    template <typename T>
    inline const T & Bank<T>::operator[](const u32 i) const
    {
        return _slots[i].value;
    }

    template <typename T>
    inline void Bank<T>::destroy(const u32 i)
    {
        _Slot & slot{_slots[i]};
        slot.value.~T();
        slot.nextFreeI = _headFreeI;
        _headFreeI = i;
        --_size;
    }

    template <typename T>
    inline void Bank<T>::clear()
    {
        if (_size)
        {
            const List<bool> freeMap{_makeFreeMap()};

            // Iterate from back to front to try to keep the free chain linked forwards
            for (u32 i{_capacity - 1u}; _size; --i)
            {
                if (!freeMap[i])
                {
                    destroy(i);
                }
            }
        }
    }

    template <typename T>
    inline void Bank<T>::_expand(const u32 newCapacity)
    {
        const u32 oldCapacity{_capacity};

        // Allocate new slots
        _Slot * const newSlots{static_cast<_Slot *>(::operator new(newCapacity * sizeof(_Slot), std::align_val_t{alignof(T)}))};

        // Copy over existing slots
        // Simply memcpy if the type is trivially move constructible and destructible
        if constexpr (std::is_trivially_move_constructible_v<T> && std::is_trivially_destructible_v<T>)
        {
            std::memcpy(newSlots, _slots, oldCapacity * sizeof(_Slot));
        }
        // Otherwise we need to manually move and destruct the elements
        else
        {
            // If all slots are occupied, we can just move/destruct all values
            // This is commonly the case, e.g. when expanding from the `create` method
            if (_size == _capacity)
            {
                for (u32 i{0u}; i < _capacity; ++i)
                {
                    T & srcV{_slots[i].value};
                    new (&newSlots[i].value) T{std::move(srcV)};
                    srcV.~T();
                }
            }
            // Otherwise we need to figure out which slots actually have elements and only move/destruct those
            else
            {
                const List<bool> freeMap{_makeFreeMap()};
                for (u32 i{0u}; i < _capacity; ++i)
                {
                    if (freeMap[i])
                    {
                        newSlots[i].nextFreeI = _slots[i].nextFreeI;
                    }
                    else
                    {
                        T & srcV{_slots[i].value};
                        new (&newSlots[i].value) T{std::move(srcV)};
                        srcV.~T();
                    }
                }
            }
        }

        // Free old slots
        ::operator delete(_slots, std::align_val_t{alignof(T)});

        // Update state
        _slots = newSlots;
        _capacity = newCapacity;

        // Link new free slots
        for (u32 i{oldCapacity}; i < _capacity; ++i)
        {
            _slots[i].nextFreeI = i + 1u;
        }
        _slots[_capacity - 1u].nextFreeI = _headFreeI;
        _headFreeI = oldCapacity;
    }

    template <typename T>
    inline List<bool> Bank<T>::_makeFreeMap() const
    {
        // TODO: Use own bit-field implementation to more efficiently iterate over set bits
        List<bool> freeMap(_capacity, false);
        for (u32 freeI{_headFreeI}; freeI != _invalidI; freeI = _slots[freeI].nextFreeI)
        {
            freeMap[freeI] = true;
        }
        return freeMap;
    }
}
