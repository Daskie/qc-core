#pragma once

#include <iterator>

namespace qc
{
    template <typename T> class Pool;
    template <typename T> class Sea;
}

namespace qc::_pool
{
    template <typename T>
    struct Range
    {
        T * start;
        T * end;
    };

    template <typename T, bool constant>
    class Iterator
    {
        friend class Pool<T>;
        friend class Sea<T>;

        using T_ = std::conditional_t<constant, const T, T>;
        using Range_ = std::conditional_t<constant, const Range<T>, Range<T>>;

      public:

        using iterator_category = std::forward_iterator_tag;
        using value_type = T_;
        using reference = T_ &;
        using pointer = T_ *;
        using difference_type = ptrdiff_t;

        Iterator(const Iterator &) noexcept = default;
        Iterator(const Iterator<T, false> &) noexcept requires constant;

        Iterator & operator=(const Iterator &) noexcept = default;

        reference operator*() const noexcept { return *_slot; }

        pointer operator->() const noexcept { return _slot; }

        Iterator & operator++() noexcept;
        Iterator operator++(int) noexcept;

        bool operator==(const Iterator & other) const noexcept;

      private:

        T_ * _slot{};
        Range_ * _nextFreeRange{};

        Iterator(T_ * slot, Range_ * nextFreeRange) noexcept;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc::_pool
{
    template <typename T, bool constant>
    inline Iterator<T, constant>::Iterator(const Iterator<T, false> & other) noexcept requires constant :
        _slot{other._slot},
        _nextFreeRange{other._nextFreeRange}
    {}

    template <typename T, bool constant>
    inline Iterator<T, constant>::Iterator(T_ * const slot, Range_ * const nextFreeRange) noexcept :
        _slot{slot},
        _nextFreeRange{nextFreeRange}
    {}

    template <typename T, bool constant>
    inline auto Iterator<T, constant>::operator++() noexcept -> Iterator &
    {
        ++_slot;

        if (_slot == _nextFreeRange->start)
        {
            _slot = _nextFreeRange->end;
            --_nextFreeRange;
        }

        return *this;
    }

    template <typename T, bool constant>
    inline auto Iterator<T, constant>::operator++(int) noexcept -> Iterator
    {
        const Iterator tmp{*this};
        ++*this;
        return tmp;
    }

    template <typename T, bool constant>
    inline bool Iterator<T, constant>::operator==(const Iterator & other) const noexcept
    {
        return _slot == other._slot;
    }
}
