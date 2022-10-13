#pragma once

#include <vector>

#include <qc-core/core.hpp>

namespace qc
{
    template <typename T>
    class Bank
    {
        static_assert(std::is_nothrow_move_constructible_v<T>);
        static_assert(std::is_nothrow_destructible_v<T>);

      public:

        Bank() noexcept = default;

        Bank(const Bank &) = delete;
        Bank(Bank && other) noexcept;

        Bank & operator=(const Bank &) = delete;
        Bank & operator=(Bank && other) noexcept;

        ~Bank() noexcept;

        void reserve(u32 capacity);

        template <typename... Args> u32 create(Args && ... args);

        void destroy(u32 i);

        T & operator[](u32 i) noexcept;
        const T & operator[](u32 i) const noexcept;

        u32 size() const noexcept { return _size; }

        bool empty() const noexcept { return _size == 0u; }

        u32 capacity() const noexcept { return _capacity; }

      private:

        union _Slot
        {
            u32 nextFreeI;
            T value;

            ~_Slot() noexcept = delete;
        };

        inline constexpr static u32 _minCapacity{16u}; // Must be power of two
        inline constexpr static u32 _invalidI{~u32(0u)};

        _Slot * _slots{};
        u32 _capacity{};
        u32 _size{};
        u32 _headFreeI{_invalidI};

        void _expand(u32 newCapacity);

        std::vector<bool> _makeFreeMap() const;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    inline Bank<T>::Bank(Bank && other) noexcept :
        _slots{std::exchange(other._slots, nullptr)},
        _capacity{std::exchange(other._capacity, 0u)},
        _size{std::exchange(other._size, 0u)},
        _headFreeI{std::exchange(other._headFreeI, _invalidI)}
    {}

    template <typename T>
    inline Bank<T> & Bank<T>::operator=(Bank && other) noexcept
    {
        _slots = std::exchange(other._slots, nullptr);
        _capacity = std::exchange(other._capacity, 0u);
        _size = std::exchange(other._size, 0u);
        _headFreeI = std::exchange(other._headFreeI, _invalidI);

        return *this;
    }

    template <typename T>
    inline Bank<T>::~Bank() noexcept
    {
        // Destruct existing elements
        if constexpr (!std::is_trivially_destructible_v<T>)
        {
            if (_size)
            {
                const std::vector<bool> freeMap{_makeFreeMap()};

                for (u32 i{0u}; _size; ++i)
                {
                    if (!freeMap[i])
                    {
                        _slots[i].value.~T();
                        --_size;
                    }
                }
            }
        }

        // Free memory
        if (_slots)
        {
            ::operator delete(_slots, std::align_val_t{alignof(_Slot)});
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
    inline u32 Bank<T>::create(Args &&... args)
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

        return i;
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
    inline T & Bank<T>::operator[](const u32 i) noexcept
    {
        return _slots[i].value;
    }

    template <typename T>
    inline const T & Bank<T>::operator[](const u32 i) const noexcept
    {
        return _slots[i].value;
    }

    template <typename T>
    inline void Bank<T>::_expand(const u32 newCapacity)
    {
        const u32 oldCapacity{_capacity};

        // Allocate new slots
        _Slot * const newSlots{static_cast<_Slot *>(::operator new(newCapacity * sizeof(_Slot), std::align_val_t{alignof(_Slot)}))};

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
                const std::vector<bool> freeMap{_makeFreeMap()};
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
        ::operator delete(_slots, std::align_val_t{alignof(_Slot)});

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
    inline std::vector<bool> Bank<T>::_makeFreeMap() const
    {
        std::vector<bool> freeMap(_capacity);
        for (u32 freeI{_headFreeI}; freeI != _invalidI; freeI = _slots[freeI].nextFreeI)
        {
            freeMap[freeI] = true;
        }
        return freeMap;
    }
}
