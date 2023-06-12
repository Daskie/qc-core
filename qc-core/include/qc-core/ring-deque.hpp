#pragma once

#include <cstring>

#include <bit>
#include <iterator>
#include <new>

#include <qc-core/core.hpp>

namespace qc
{
    template <typename T>
    class RingDeque
    {
        static_assert(std::is_default_constructible_v<T>);
        static_assert(std::is_move_constructible_v<T>);
        static_assert(std::is_move_assignable_v<T>);

        template <bool constant> class Iterator;

      public:

        using value_type = T;
        using reference = value_type &;
        using const_reference = const value_type &;
        using difference_type = s64;
        using size_type = u64;
        using iterator = Iterator<false>;
        using const_iterator = Iterator<true>;

        RingDeque() = default;

        RingDeque(const RingDeque & other) = delete;
        RingDeque(RingDeque && other);

        RingDeque & operator=(const RingDeque & other) = delete;
        RingDeque & operator=(RingDeque && other);

        ~RingDeque();

        void reserve(u64 capacity);

        T & push_front(const T & v);

        T & push_front(T && v);

        template <typename... Args> T & emplace_front(Args &&... args);

        T & push_back(const T & v);

        T & push_back(T && v);

        template <typename... Args> T & emplace_back(Args &&... args);

        nodisc T & front();
        nodisc const T & front() const;

        nodisc T & back();
        nodisc const T & back() const;

        nodisc T & operator[](u64 i);
        nodisc const T & operator[](u64 i) const;

        void pop_front();

        void pop_back();

        void clear();

        nodisc u64 size() const { return _size; };

        nodisc bool empty() const { return !_size; };

        nodisc u64 capacity() const { return _capacity; }

        nodisc iterator begin();
        nodisc const_iterator begin() const;
        nodisc const_iterator cbegin() const;

        nodisc iterator end();
        nodisc const_iterator end() const;
        nodisc const_iterator cend() const;

      private:

        constexpr static u64 _minCapacity{16u}; // Must be power of two

        T * _slots{};
        u64 _capacity{};
        u64 _size{};
        T * _front{}; // First element
        T * _back{}; // One past the last element

        void _expand(u64 newCapacity);
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
        using difference_type = s64;

        Iterator(const Iterator & other) = default;
        Iterator(const Iterator<false> & other) requires (constant);

        nodisc value_type & operator*() const { return *_v; }

        nodisc value_type * operator->() const { return _v; }

        Iterator & operator++();

        Iterator operator++(int);

        template <bool constant_> nodisc bool operator==(const Iterator<constant_> & other) const;

      private:

        Iterator(value_type * v, value_type * start, value_type * end);

        value_type * _v;
        value_type * _start;
        value_type * _end;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    inline RingDeque<T>::RingDeque(RingDeque && other) :
        _slots{other._slots},
        _capacity{other._capacity},
        _size{other._size},
        _front{other._front},
        _back{other._back}
    {
        other._lots = nullptr;
        other._capacity = 0u;
        other._size = 0u;
        other._front = nullptr;
        other._back = nullptr;
    }

    template <typename T>
    inline RingDeque<T> & RingDeque<T>::operator=(RingDeque && other)
    {
        if (&other == this)
        {
            return *this;
        }

        _slots = other._slots;
        _capacity = other._capacity;
        _size = other._size;
        _front = other._front;
        _back = other._back;

        other._slots = nullptr;
        other._capacity = 0u;
        other._size = 0u;
        other._front = nullptr;
        other._back = nullptr;

        return *this;
    }

    template <typename T>
    inline RingDeque<T>::~RingDeque()
    {
        if (_slots)
        {
            clear();
            ::operator delete(_slots, std::align_val_t{alignof(T)});
        }
    }

    template <typename T>
    inline void RingDeque<T>::reserve(const u64 capacity)
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
        assert(_size);

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
        assert(_size);

        return _back[_back == _slots ? s64(_capacity) - 1 : -1];
    }

    template <typename T>
    inline T & RingDeque<T>::operator[](const u64 i)
    {
        const u64 absoluteI{_front - _slots + i};
        return _slots[absoluteI < _capacity ? absoluteI : absoluteI - _capacity];
    }

    template <typename T>
    inline const T & RingDeque<T>::operator[](const u64 i) const
    {
        const u64 absoluteI{_front - _slots + i};
        return _slots[absoluteI < _capacity ? absoluteI : absoluteI - _capacity];
    }

    template <typename T>
    inline void RingDeque<T>::pop_front()
    {
        assert(_size);

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
        assert(_size);

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
    inline auto RingDeque<T>::begin() -> iterator
    {
        return iterator{_front, _slots, _slots + _capacity};
    }

    template <typename T>
    inline auto RingDeque<T>::begin() const -> const_iterator
    {
        return const_iterator{_front, _slots, _slots + _capacity};
    }

    template <typename T>
    inline auto RingDeque<T>::cbegin() const -> const_iterator
    {
        return begin();
    }

    template <typename T>
    inline auto RingDeque<T>::end() -> iterator
    {
        return iterator{_back, _slots, _slots + _capacity};
    }

    template <typename T>
    inline auto RingDeque<T>::end() const -> const_iterator
    {
        return const_iterator{_back, _slots, _slots + _capacity};
    }

    template <typename T>
    inline auto RingDeque<T>::cend() const -> const_iterator
    {
        return end();
    }

    template <typename T>
    inline void RingDeque<T>::_expand(const u64 newCapacity)
    {
        T * const newSlots{static_cast<T *>(::operator new(newCapacity * sizeof(T), std::align_val_t{alignof(T)}))};

        // Move elements over
        if constexpr (std::is_trivially_move_constructible_v<T> && std::is_trivially_destructible_v<T>)
        {
            if (_back > _front)
            {
                memcpy(newSlots, _front, u64(_back - _front) * sizeof(T));
            }
            else if (_back <= _front && _size)
            {
                const u64 n{u64(_slots + _capacity - _front)};
                memcpy(newSlots, _front, n * sizeof(T));
                memcpy(newSlots + n, _slots, u64(_back - _slots) * sizeof(T));
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
    inline RingDeque<T>::Iterator<constant>::Iterator(const Iterator<false> & other) requires (constant) :
        _v{other._v},
        _start{other._start},
        _end{other._end}
    {}

    template <typename T>
    template <bool constant>
    inline auto RingDeque<T>::Iterator<constant>::operator++() -> Iterator &
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
    inline auto RingDeque<T>::Iterator<constant>::operator++(int) -> Iterator
    {
        Iterator temp{*this};
        operator++();
        return temp;
    }

    template <typename T>
    template <bool constant>
    template <bool constant_>
    inline bool RingDeque<T>::Iterator<constant>::operator==(const Iterator<constant_> & other) const
    {
        return _v == other._v;
    }

    template <typename T>
    template <bool constant>
    inline RingDeque<T>::Iterator<constant>::Iterator(value_type * const v, value_type * const start, value_type * const end) :
        _v(v),
        _start(start),
        _end(end)
    {}
}
