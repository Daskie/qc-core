#pragma once

#include <bit>
#include <iterator>
#include <new>

#include <qc-core/core.hpp>

namespace qc
{
    struct RingDequeError {};

    template <typename T>
    class RingDeque
    {
        static_assert(std::is_nothrow_default_constructible_v<T>);
        static_assert(std::is_nothrow_move_constructible_v<T>);
        static_assert(std::is_nothrow_move_assignable_v<T>);
        static_assert(std::is_nothrow_destructible_v<T>);

        template <bool constant> class Iterator;

      public:

        using value_type = T;
        using reference = value_type &;
        using const_reference = const value_type &;
        using difference_type = ptrdiff_t;
        using size_type = size_t;
        using iterator = Iterator<false>;
        using const_iterator = Iterator<true>;

        RingDeque() noexcept = default;

        RingDeque(const RingDeque & other) noexcept = delete;
        RingDeque(RingDeque && other) noexcept;

        RingDeque & operator=(const RingDeque & other) noexcept = delete;
        RingDeque & operator=(RingDeque && other) noexcept;

        ~RingDeque() noexcept;

        void reserve(size_t capacity);

        T & push_front(const T & v);

        T & push_front(T && v);

        template <typename... Args> T & emplace_front(Args &&... args);

        T & push_back(const T & v);

        T & push_back(T && v);

        template <typename... Args> T & emplace_back(Args &&... args);

        T & front();
        const T & front() const;

        T & back();
        const T & back() const;

        T & operator[](size_t i) noexcept;
        const T & operator[](size_t i) const noexcept;

        void pop_front();

        void pop_back();

        void clear();

        size_t size() const noexcept { return _size; };

        bool empty() const noexcept { return !_size; };

        size_t capacity() const noexcept { return _capacity; }

        iterator begin() noexcept;
        const_iterator begin() const noexcept;
        const_iterator cbegin() const noexcept;

        iterator end() noexcept;
        const_iterator end() const noexcept;
        const_iterator cend() const noexcept;

      private:

        constexpr static size_t _minCapacity{16u}; // Must be power of two

        T * _slots{};
        size_t _capacity{};
        size_t _size{};
        T * _front{}; // First element
        T * _back{}; // One past the last element

        void _expand(size_t newCapacity);
    };

    template <typename T>
    template <bool constant>
    class RingDeque<T>::Iterator
    {
        friend class RingDeque<T>;

      public:

        using iterator_category = std::forward_iterator_tag;
        using value_type = std::conditional_t<constant, const T, T>;
        using reference = value_type &;
        using pointer = value_type *;
        using difference_type = ptrdiff_t;

        Iterator(const Iterator & other) noexcept = default;
        Iterator(const Iterator<false> & other) noexcept requires constant;

        value_type & operator*() const noexcept { return *_v; }

        value_type * operator->() const noexcept { return _v; }

        Iterator & operator++() noexcept;

        Iterator operator++(int) noexcept;

        template <bool constant_> bool operator==(const Iterator<constant_> & other) const noexcept;

      private:

        Iterator(value_type * v, value_type * start, value_type * end) noexcept;

        value_type * _v;
        value_type * _start;
        value_type * _end;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    inline RingDeque<T>::RingDeque(RingDeque && other) noexcept :
        _slots{std::exchange(other._slots, nullptr)},
        _capacity{std::exchange(other._capacity, 0u)},
        _size{std::exchange(other._size, 0u)},
        _front{std::exchange(other._front, nullptr)},
        _back{std::exchange(other._back, nullptr)}
    {}

    template <typename T>
    inline RingDeque<T> & RingDeque<T>::operator=(RingDeque && other) noexcept
    {
        _slots = std::exchange(other._slots, nullptr);
        _capacity = std::exchange(other._capacity, 0u);
        _size = std::exchange(other._size, 0u);
        _front = std::exchange(other._front, nullptr);
        _back = std::exchange(other._back, nullptr);

        return *this;
    }

    template <typename T>
    inline RingDeque<T>::~RingDeque() noexcept
    {
        if (_slots)
        {
            clear();
            ::operator delete(_slots, std::align_val_t{alignof(T)});
        }
    }

    template <typename T>
    inline void RingDeque<T>::reserve(const size_t capacity)
    {
        if (capacity > _capacity)
        {
            _expand(qc::max(std::bit_ceil(capacity), _minCapacity));
        }
    }

    template <typename T>
    inline T & RingDeque<T>::push_front(const T & v)
    {
        return emplace_front(v);
    }

    template <typename T>
    inline T & RingDeque<T>::push_front(T && v)
    {
        return emplace_front(std::move(v));
    }

    template <typename T>
    template <typename... Args>
    inline T & RingDeque<T>::emplace_front(Args &&... args)
    {
        if (_size == _capacity)
        {
            _expand(qc::max(_capacity * 2u, _minCapacity));
        }

        if (_front == _slots)
        {
            _front += _capacity;
        }
        --_front;

        ++_size;
        return *(new (_front) T{std::forward<Args>(args)...});
    }

    template <typename T>
    inline T & RingDeque<T>::push_back(const T & v)
    {
        return emplace_back(v);
    }

    template <typename T>
    inline T & RingDeque<T>::push_back(T && v)
    {
        return emplace_back(std::move(v));
    }

    template <typename T>
    template <typename... Args>
    inline T & RingDeque<T>::emplace_back(Args &&... args)
    {
        if (_size == _capacity)
        {
            _expand(qc::max(_capacity * 2u, _minCapacity));
        }

        T & newV{*(new (_back) T{std::forward<Args>(args)...})};
        ++_size;

        ++_back;
        if (_back == _slots + _capacity)
        {
            _back = _slots;
        }

        return newV;
    }

    template <typename T>
    inline T & RingDeque<T>::front()
    {
        return const_cast<T &>(const_cast<const RingDeque &>(*this).front());
    }

    template <typename T>
    inline const T & RingDeque<T>::front() const
    {
        if (!_size) [[unlikely]]
        {
            throw RingDequeError{};
        }

        return *_front;
    }

    template <typename T>
    inline T & RingDeque<T>::back()
    {
        return const_cast<T &>(const_cast<const RingDeque &>(*this).back());
    }

    template <typename T>
    inline const T & RingDeque<T>::back() const
    {
        if (!_size) [[unlikely]]
        {
            throw RingDequeError{};
        }

        return _back[_back == _slots ? intptr_t(_capacity) - 1 : -1];
    }

    template <typename T>
    inline T & RingDeque<T>::operator[](const size_t i) noexcept
    {
        const size_t absoluteI{_front - _slots + i};
        return _slots[absoluteI < _capacity ? absoluteI : absoluteI - _capacity];
    }

    template <typename T>
    inline const T & RingDeque<T>::operator[](const size_t i) const noexcept
    {
        const size_t absoluteI{_front - _slots + i};
        return _slots[absoluteI < _capacity ? absoluteI : absoluteI - _capacity];
    }

    template <typename T>
    inline void RingDeque<T>::pop_front()
    {
        if (!_size) [[unlikely]]
        {
            throw RingDequeError{};
        }

        _front->~T();
        --_size;

        ++_front;
        if (_front == _slots + _capacity)
        {
            _front = _slots;
        }
    }

    template <typename T>
    inline void RingDeque<T>::pop_back()
    {
        if (!_size) [[unlikely]]
        {
            throw RingDequeError{};
        }

        if (_back == _slots)
        {
            _back += _capacity;
        }
        --_back;

        _back->~T();
        --_size;
    }

    template <typename T>
    inline void RingDeque<T>::clear()
    {
        if constexpr (!std::is_trivially_destructible_v<T>)
        {
            for (T & v: *this) v.~T();
        }

        _size = 0u;
        _front = _slots;
        _back = _slots;
    }

    template <typename T>
    inline auto RingDeque<T>::begin() noexcept -> iterator
    {
        return iterator{_front, _slots, _slots + _capacity};
    }

    template <typename T>
    inline auto RingDeque<T>::begin() const noexcept -> const_iterator
    {
        return const_iterator{_front, _slots, _slots + _capacity};
    }

    template <typename T>
    inline auto RingDeque<T>::cbegin() const noexcept -> const_iterator
    {
        return begin();
    }

    template <typename T>
    inline auto RingDeque<T>::end() noexcept -> iterator
    {
        return iterator{_back, _slots, _slots + _capacity};
    }

    template <typename T>
    inline auto RingDeque<T>::end() const noexcept -> const_iterator
    {
        return const_iterator{_back, _slots, _slots + _capacity};
    }

    template <typename T>
    inline auto RingDeque<T>::cend() const noexcept -> const_iterator
    {
        return end();
    }

    template <typename T>
    inline void RingDeque<T>::_expand(const size_t newCapacity)
    {
        T * const newSlots{static_cast<T *>(::operator new(newCapacity * sizeof(T), std::align_val_t{alignof(T)}))};

        // Move elements over
        if constexpr (std::is_trivially_move_constructible_v<T> && std::is_trivially_destructible_v<T>)
        {
            if (_back > _front)
            {
                memcpy(newSlots, _front, size_t(_back - _front) * sizeof(T));
            }
            else if (_back <= _front && _size)
            {
                const size_t n{size_t(_slots + _capacity - _front)};
                memcpy(newSlots, _front, n * sizeof(T));
                memcpy(newSlots + n, _slots, size_t(_back - _slots) * sizeof(T));
            }
        }
        else
        {
            T * dst{newSlots};
            for (T & v : *this)
            {
                new (dst) T{std::move(v)};
                v.~T();
                ++dst;
            }
        }

        ::operator delete(_slots, std::align_val_t{alignof(T)});
        _slots = newSlots;
        _capacity = newCapacity;
        _front = _slots;
        _back = _slots + _size;
    }

    template <typename T>
    template <bool constant>
    inline RingDeque<T>::Iterator<constant>::Iterator(const Iterator<false> & other) noexcept requires constant :
        _v{other._v},
        _start{other._start},
        _end{other._end}
    {}

    template <typename T>
    template <bool constant>
    inline auto RingDeque<T>::Iterator<constant>::operator++() noexcept -> Iterator &
    {
        ++_v;

        if (_v == _end) [[unlikely]]
        {
            _v = _start;
        }

        return *this;
    }

    template <typename T>
    template <bool constant>
    inline auto RingDeque<T>::Iterator<constant>::operator++(int) noexcept -> Iterator
    {
        Iterator temp{*this};
        operator++();
        return temp;
    }

    template <typename T>
    template <bool constant>
    template <bool constant_>
    inline bool RingDeque<T>::Iterator<constant>::operator==(const Iterator<constant_> & other) const noexcept
    {
        return _v == other._v;
    }

    template <typename T>
    template <bool constant>
    inline RingDeque<T>::Iterator<constant>::Iterator(value_type * const v, value_type * const start, value_type * const end) noexcept :
        _v(v),
        _start(start),
        _end(end)
    {}
}
