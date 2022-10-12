#pragma once

#include <iterator>
#include <utility>

#include <qc-core/core.hpp>

namespace qc
{
    struct SemiStableDequeError {};

    ///
    /// The most significant differences between this and `std::deque`:
    ///   1. This does not provide reference stability. References and iterators are invalidated when the capacity grows
    ///   2. This DOES provide positional stability. That is, a `DequePos` remains valid in all cases
    ///
    /// Essentially, this allows you to `pop` a middle element without invalidating other elements, at the cost of
    ///   reference stability if only working with front/back operations
    ///
    template <typename T>
    class SemiStableDeque
    {
        static_assert(std::is_nothrow_default_constructible_v<T>);
        static_assert(std::is_nothrow_move_constructible_v<T>);
        static_assert(std::is_nothrow_move_assignable_v<T>);
        static_assert(std::is_nothrow_destructible_v<T>);

        template <bool constant, bool reverse> class _Iterator;

      public:

        using iterator = _Iterator<false, false>;
        using const_iterator = _Iterator<true, false>;
        using reverse_iterator = _Iterator<false, true>;
        using const_reverse_iterator = _Iterator<true, true>;

        SemiStableDeque() noexcept = default;

        SemiStableDeque(const SemiStableDeque &) = delete;
        SemiStableDeque(SemiStableDeque && other) noexcept;

        SemiStableDeque & operator=(const SemiStableDeque &) = delete;
        SemiStableDeque & operator=(SemiStableDeque && other) noexcept;

        ~SemiStableDeque() noexcept;

        u32 push_back(const T & v);
        u32 push_back(T && v);

        u32 push_front(const T & v);
        u32 push_front(T && v);

        template <typename... Args> u32 emplace_back(Args &&... args);

        template <typename... Args> u32 emplace_front(Args &&... args);

        void pop_back();

        void pop_front();

        void pop(u32 pos);
        void pop(iterator it);

        T & front();
        const T & front() const;

        T & back();
        const T & back() const;

        T & operator[](u32 pos) noexcept;
        const T & operator[](u32 pos) const noexcept;

        iterator getIterator(u32 pos) noexcept;
        const_iterator getIterator(u32 pos) const noexcept;

        reverse_iterator getReverseIterator(u32 pos) noexcept;
        const_reverse_iterator getReverseIterator(u32 pos) const noexcept;

        u32 size() const noexcept { return _presentCount; }

        bool empty() const noexcept { return !_presentCount; }

        u32 capacity() const noexcept { return _capacity; }

        iterator begin() noexcept;
        const_iterator begin() const noexcept;
        const_iterator cbegin() const noexcept { return begin(); };

        iterator end() noexcept;
        const_iterator end() const noexcept;
        const_iterator cend() const noexcept { return end(); };

        reverse_iterator rbegin() noexcept;
        const_reverse_iterator rbegin() const noexcept;
        const_reverse_iterator crbegin() const noexcept { return rbegin(); };

        reverse_iterator rend() noexcept;
        const_reverse_iterator rend() const noexcept;
        const_reverse_iterator crend() const noexcept { return rend(); };

      private:

        struct _Slot
        {
            u32 prevI;
            u32 nextI;
            T value;
        };

        inline constexpr static u32 _minCapacity{16u};
        inline constexpr static u32 _invalidI{~u32(0u)};

        _Slot * _slots{};
        u32 _capacity{};
        u32 _presentCount{};
        u32 _presentHeadI{_invalidI};
        u32 _presentTailI{_invalidI};
        u32 _vacantHeadI{_invalidI};

        void _expand();
    };

    template <typename T>
    template <bool constant, bool reverse>
    class SemiStableDeque<T>::_Iterator
    {
        friend SemiStableDeque;

        using T_ = std::conditional_t<constant, const T, T>;
        using _Slot_ = std::conditional_t<constant, const _Slot, _Slot>;

      public:

        using iterator_category = std::forward_iterator_tag;
        using value_type = T_;
        using reference = value_type &;
        using pointer = value_type *;
        using difference_type = ptrdiff_t;

        _Iterator() noexcept = default;

        _Iterator(const _Iterator<false, reverse> &) noexcept requires constant;

        _Iterator(const _Iterator &) noexcept = default;

        _Iterator & operator=(const _Iterator &) noexcept = default;

        reference operator*() const noexcept { return _slot->value; }

        pointer operator->() const noexcept { return &_slot->value; }

        _Iterator & operator++() noexcept;
        _Iterator operator++(int) noexcept;

        u32 index() const noexcept { return u32(_slot - _slots); }

        bool operator==(const _Iterator & other) const noexcept;

      private:

        _Slot_ * _slots{};
        _Slot_ * _slot{};

        _Iterator(_Slot_ * slots, _Slot_ * slot) noexcept;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    inline SemiStableDeque<T>::SemiStableDeque(SemiStableDeque && other) noexcept :
        _slots{std::exchange(other._slots, nullptr)},
        _capacity{std::exchange(other._capacity, 0u)},
        _presentCount{std::exchange(other._presentCount, 0u)},
        _presentHeadI{std::exchange(other._presentHeadI, _invalidI)},
        _presentTailI{std::exchange(other._presentTailI, _invalidI)},
        _vacantHeadI{std::exchange(other._vacantHeadI, _invalidI)}
    {}

    template <typename T>
    inline SemiStableDeque<T> & SemiStableDeque<T>::operator=(SemiStableDeque && other) noexcept
    {
        _slots = std::exchange(other._slots, nullptr);
        _capacity = std::exchange(other._capacity, 0u);
        _presentCount = std::exchange(other._presentCount, 0u);
        _presentHeadI = std::exchange(other._presentHeadI, _invalidI);
        _presentTailI = std::exchange(other._presentTailI, _invalidI);
        _vacantHeadI = std::exchange(other._vacantHeadI, _invalidI);

        return *this;
    }

    template <typename T>
    inline SemiStableDeque<T>::~SemiStableDeque() noexcept
    {
        if constexpr (!std::is_trivially_destructible_v<T>)
        {
            for (T & v : *this)
            {
                v.~T();
            }
        }

        ::operator delete(_slots);

        if constexpr (qc::debug)
        {
            _slots = nullptr;
            _capacity = 0u;
            _presentCount = 0u;
            _presentHeadI = _invalidI;
            _presentTailI = _invalidI;
            _vacantHeadI = _invalidI;
        }
    }

    template <typename T>
    inline u32 SemiStableDeque<T>::push_back(const T & v)
    {
        return emplace_back(v);
    }

    template <typename T>
    inline u32 SemiStableDeque<T>::push_back(T && v)
    {
        return emplace_back(std::move(v));
    }

    template <typename T>
    inline u32 SemiStableDeque<T>::push_front(const T & v)
    {
        return emplace_front(v);
    }

    template <typename T>
    inline u32 SemiStableDeque<T>::push_front(T && v)
    {
        return emplace_front(std::move(v));
    }

    template <typename T>
    template <typename... Args>
    inline u32 SemiStableDeque<T>::emplace_back(Args &&... args)
    {
        if (_vacantHeadI == _invalidI) [[unlikely]]
        {
            _expand();
        }

        const u32 slotI{_vacantHeadI};
        _Slot & slot{_slots[slotI]};
        new (&slot.value) T{std::forward<Args>(args)...};

        _vacantHeadI = slot.nextI;

        slot.prevI = _presentTailI;
        slot.nextI = _invalidI;

        if (_presentTailI != _invalidI) _slots[_presentTailI].nextI = slotI;
        _presentTailI = slotI;

        if (_presentHeadI == _invalidI) _presentHeadI = slotI;

        ++_presentCount;

        return slotI;
    }

    template <typename T>
    template <typename... Args>
    inline u32 SemiStableDeque<T>::emplace_front(Args &&... args)
    {
        if (_vacantHeadI == _invalidI) [[unlikely]]
        {
            _expand();
        }

        const u32 slotI{_vacantHeadI};
        _Slot & slot{_slots[slotI]};
        new (&slot.value) T{std::forward<Args>(args)...};

        _vacantHeadI = slot.nextI;

        slot.prevI = _invalidI;
        slot.nextI = _presentHeadI;

        if (_presentHeadI != _invalidI) _slots[_presentHeadI].prevI = slotI;
        _presentHeadI = slotI;

        if (_presentTailI == _invalidI) _presentTailI = slotI;

        ++_presentCount;

        return slotI;
    }

    template <typename T>
    inline void SemiStableDeque<T>::pop_back()
    {
        if (_presentTailI == _invalidI) [[unlikely]]
        {
            throw SemiStableDequeError{};
        }

        pop(_presentTailI);
    }

    template <typename T>
    inline void SemiStableDeque<T>::pop_front()
    {
        if (_presentHeadI == _invalidI) [[unlikely]]
        {
            throw SemiStableDequeError{};
        }

        pop(_presentHeadI);
    }

    template <typename T>
    inline void SemiStableDeque<T>::pop(const u32 pos)
    {
        _Slot & slot{_slots[pos]};
        slot.value.~T();

        if (slot.prevI != _invalidI)
        {
            _slots[slot.prevI].nextI = slot.nextI;
        }
        else
        {
            _presentHeadI = slot.nextI;
        }

        if (slot.nextI != _invalidI)
        {
            _slots[slot.nextI].prevI = slot.prevI;
        }
        else
        {
            _presentTailI = slot.prevI;
        }

        slot.prevI = _invalidI;
        slot.nextI = _vacantHeadI;
        _vacantHeadI = pos;

        --_presentCount;
    }

    template <typename T>
    inline void SemiStableDeque<T>::pop(const iterator it)
    {
        pop(it.index());
    }

    template <typename T>
    inline T & SemiStableDeque<T>::front()
    {
        return const_cast<T &>(const_cast<const SemiStableDeque &>(*this).front());
    }

    template <typename T>
    inline const T & SemiStableDeque<T>::front() const
    {
        if (_presentHeadI == _invalidI) [[unlikely]]
        {
            throw SemiStableDequeError{};
        }

        return _slots[_presentHeadI].value;
    }

    template <typename T>
    inline T & SemiStableDeque<T>::back()
    {
        return const_cast<T &>(const_cast<const SemiStableDeque &>(*this).back());
    }

    template <typename T>
    inline const T & SemiStableDeque<T>::back() const
    {
        if (_presentTailI == _invalidI) [[unlikely]]
        {
            throw SemiStableDequeError{};
        }

        return _slots[_presentTailI].value;
    }

    template <typename T>
    inline T & SemiStableDeque<T>::operator[](const u32 pos) noexcept
    {
        return _slots[pos].value;
    }

    template <typename T>
    inline const T & SemiStableDeque<T>::operator[](const u32 pos) const noexcept
    {
        return _slots[pos].value;
    }

    template <typename T>
    inline auto SemiStableDeque<T>::getIterator(const u32 pos) noexcept -> iterator
    {
        return iterator{_slots, _slots + pos};
    }

    template <typename T>
    inline auto SemiStableDeque<T>::getIterator(const u32 pos) const noexcept -> const_iterator
    {
        return const_iterator{_slots, _slots + pos};
    }

    template <typename T>
    inline auto SemiStableDeque<T>::getReverseIterator(const u32 pos) noexcept -> reverse_iterator
    {
        return reverse_iterator{_slots, _slots + pos};
    }

    template <typename T>
    inline auto SemiStableDeque<T>::getReverseIterator(const u32 pos) const noexcept -> const_reverse_iterator
    {
        return const_reverse_iterator{_slots, _slots + pos};
    }

    template <typename T>
    inline auto SemiStableDeque<T>::begin() noexcept -> iterator
    {
        const const_iterator it{const_cast<const SemiStableDeque *>(this)->begin()};
        return reinterpret_cast<const iterator &>(it);
    }

    template <typename T>
    inline auto SemiStableDeque<T>::begin() const noexcept -> const_iterator
    {
        return _presentHeadI != _invalidI ? const_iterator{_slots, _slots + _presentHeadI} : const_iterator{};
    }

    template <typename T>
    inline auto SemiStableDeque<T>::end() noexcept -> iterator
    {
        return iterator{};
    }

    template <typename T>
    inline auto SemiStableDeque<T>::end() const noexcept -> const_iterator
    {
        return const_iterator{};
    }

    template <typename T>
    inline auto SemiStableDeque<T>::rbegin() noexcept -> reverse_iterator
    {
        const const_iterator it{const_cast<const SemiStableDeque *>(this)->rbegin()};
        return reinterpret_cast<const iterator &>(it);
    }

    template <typename T>
    inline auto SemiStableDeque<T>::rbegin() const noexcept -> const_reverse_iterator
    {
        return _presentTailI != _invalidI ? const_reverse_iterator{_slots, _slots + _presentTailI} : const_reverse_iterator{};
    }

    template <typename T>
    inline auto SemiStableDeque<T>::rend() noexcept -> reverse_iterator
    {
        return reverse_iterator{};
    }

    template <typename T>
    inline auto SemiStableDeque<T>::rend() const noexcept -> const_reverse_iterator
    {
        return const_reverse_iterator{};
    }

    template <typename T>
    inline void SemiStableDeque<T>::_expand()
    {
        const u32 oldCapacity{_capacity};
        const u32 newCapacity{qc::max(oldCapacity * 2u, _minCapacity)};

        // Expand underlying array
        {
            _Slot * const newSlots{static_cast<_Slot *>(::operator new(newCapacity * sizeof(_Slot)))};
            if constexpr (std::is_trivially_copyable_v<T>)
            {
                std::memcpy(newSlots, _slots, oldCapacity * sizeof(_Slot));
            }
            else
            {
                for (_Slot * src{_slots}, * dst{newSlots}, * srcEnd{_slots + oldCapacity}; src != srcEnd; ++src, ++dst)
                {
                    new (dst) _Slot(std::move(*src));
                }
            }
            ::operator delete(_slots);
            _slots = newSlots;
            _capacity = newCapacity;
        }

        // Link first new slot
        {
            _Slot & slot{_slots[oldCapacity]};
            slot.prevI = _invalidI;
            slot.nextI = oldCapacity + 1u;
        }

        // Link middle new slots
        for (u32 slotI{oldCapacity + 1u}; slotI < newCapacity - 1u; ++slotI)
        {
            _Slot & slot{_slots[slotI]};
            slot.prevI = slotI - 1;
            slot.nextI = slotI + 1;
        }

        // Link last new slot
        {
            _Slot & slot{_slots[newCapacity - 1u]};
            slot.prevI = newCapacity - 2u;
            slot.nextI = _invalidI;
        }

        _vacantHeadI = oldCapacity;
    }

    template <typename T>
    template <bool constant, bool reverse>
    SemiStableDeque<T>::_Iterator<constant, reverse>::_Iterator(const _Iterator<false, reverse> & other) noexcept requires constant :
        _slots{other._slots},
        _slot{other._slot}
    {}

    template <typename T>
    template <bool constant, bool reverse>
    SemiStableDeque<T>::_Iterator<constant, reverse>::_Iterator(_Slot_ * const slots, _Slot_ * const slot) noexcept :
        _slots{slots},
        _slot{slot}
    {}

    template <typename T>
    template <bool constant, bool reverse>
    auto SemiStableDeque<T>::_Iterator<constant, reverse>::operator++() noexcept -> _Iterator &
    {
        if constexpr (!reverse)
        {
            _slot = _slot->nextI != _invalidI ? _slots + _slot->nextI : nullptr;
        }
        else
        {
            _slot = _slot->prevI != _invalidI ? _slots + _slot->prevI : nullptr;
        }

        return *this;
    }

    template <typename T>
    template <bool constant, bool reverse>
    auto SemiStableDeque<T>::_Iterator<constant, reverse>::operator++(int) noexcept -> _Iterator
    {
        const _Iterator tmp{*this};
        ++*this;
        return tmp;
    }

    template <typename T>
    template <bool constant, bool reverse>
    bool SemiStableDeque<T>::_Iterator<constant, reverse>::operator==(const _Iterator & other) const noexcept
    {
        return _slot == other._slot;
    }
}
