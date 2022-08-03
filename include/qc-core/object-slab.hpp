#pragma once

#include <cassert>

#include <new>
#include <utility>
#include <vector>

#include <qc-core/core-ext.hpp>

namespace qc
{
    struct ObjectSlabError {};

    namespace _internal
    {
        class ObjectSlabFriend;
    }

    template <typename T>
    class ObjectSlab
    {
        friend ::qc::_internal::ObjectSlabFriend;

        template <bool constant> class _Iterator;

      public:

        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using difference_type = ptrdiff_t;
        using size_type = size_t;
        using iterator = _Iterator<false>;
        using const_iterator = _Iterator<true>;

        using Error = ObjectSlabError;

        explicit ObjectSlab(size_t size);

        ObjectSlab(const ObjectSlab &) = delete;
        ObjectSlab(ObjectSlab && other) noexcept;

        ObjectSlab & operator=(const ObjectSlab &) = delete;
        ObjectSlab & operator=(ObjectSlab && other) noexcept;

        ~ObjectSlab() noexcept;

        /// @throws `ObjectSlabError` if the slab is full
        template <typename... Args> [[nodiscard]] T & construct(Args &&... args);

        void destruct(T & v);

        bool contains(const T & v) const noexcept;

        size_t size() const noexcept { return size_t(_slabRange.end - _slabRange.start); }

        size_t usedCount() const noexcept { return _usedCount; }

        size_t freeCount() const noexcept { return size() - _usedCount; }

        bool empty() const noexcept { return _usedCount == 0u; }

        bool full() const noexcept { return _usedCount == size(); }

        iterator begin() noexcept;
        const_iterator begin() const noexcept;
        const_iterator cbegin() const noexcept { return begin(); };

        iterator end() noexcept;
        const_iterator end() const noexcept;
        const_iterator cend() const noexcept { return end(); };

      private:

        struct _Range
        {
            T * start;
            T * end;
        };

        _Range _slabRange{};
        size_t _usedCount{};
        std::vector<_Range> _inactiveRanges{};

        typename std::vector<_Range>::iterator _find(const T * slot) noexcept;
    };

    template <typename T>
    template <bool constant>
    class ObjectSlab<T>::_Iterator
    {
        friend ObjectSlab;

        using T_ = std::conditional_t<constant, const T, T>;
        using _Range_ = std::conditional_t<constant, const _Range, _Range>;

      public:

        using iterator_category = std::forward_iterator_tag;
        using value_type = T_;
        using reference = T_ &;
        using pointer = T_ *;
        using difference_type = ptrdiff_t;

        _Iterator(const _Iterator<false> &) noexcept requires constant;

        _Iterator(const _Iterator &) noexcept = default;

        _Iterator & operator=(const _Iterator &) noexcept = default;

        reference operator*() const noexcept { return *_slot; }

        pointer operator->() const noexcept { return _slot; }

        _Iterator & operator++() noexcept;
        _Iterator operator++(int) noexcept;

        bool operator==(const _Iterator & other) const noexcept;

      private:

        T_ * _slot{};
        _Range_ * _nextInactiveRange{};

        _Iterator(T_ * slot, _Range_ * nextInactiveRange) noexcept;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    ObjectSlab<T>::ObjectSlab(const size_t size)
    {
        assert(size > 0u);

        _slabRange.start = static_cast<T *>(::operator new(size * sizeof(T), std::align_val_t{alignof(T)}));
        _slabRange.end = _slabRange.start + size;
        _inactiveRanges.push_back(_slabRange);
    }

    template <typename T>
    inline ObjectSlab<T>::ObjectSlab(ObjectSlab && other) noexcept :
        _slabRange{std::exchange(other._slabRange, {})},
        _usedCount{std::exchange(other._usedCount, 0u)},
        _inactiveRanges{std::move(other._inactiveRanges)}
    {}

    template <typename T>
    inline ObjectSlab<T> & ObjectSlab<T>::operator=(ObjectSlab && other) noexcept
    {
        _slabRange = std::exchange(other._slabRange, {});
        _usedCount = std::exchange(other._usedCount, 0u);
        _inactiveRanges = std::move(other._inactiveRanges);

        return *this;
    }

    template <typename T>
    inline ObjectSlab<T>::~ObjectSlab<T>() noexcept
    {
        if constexpr (debug)
        {
            assert(_usedCount == 0u);
            _slabRange = {};
        }
    }

    template <typename T>
    template <typename... Args>
    inline T & ObjectSlab<T>::construct(Args &&... args)
    {
        if (_inactiveRanges.empty()) [[unlikely]]
        {
            throw Error{};
        }

        _Range & lowRange{_inactiveRanges.back()};
        T * const lowSlot{lowRange.start};
        ++lowRange.start;
        if (lowRange.start == lowRange.end)
        {
            _inactiveRanges.pop_back();
        }
        ++_usedCount;
        return *(new (lowSlot) T{std::forward<Args>(args)...});
    }

    template <typename T>
    inline void ObjectSlab<T>::destruct(T & v)
    {
        // Find the inactive range before or including the slot
        const auto lowerIt{_find(&v)};
        const bool isLower{lowerIt != _inactiveRanges.end()};
        const bool isUpper{lowerIt != _inactiveRanges.begin()};
        const auto upperIt{lowerIt - isUpper};

        // Ensure slot is active, i.e. it's in the slab and it's not in an inactive range
        assert(contains(v) && (!isLower || &v >= lowerIt->end));

        // Destruct object
        v.~T();

        // Add slot to inactive ranges
        const bool againstLower{isLower && &v == lowerIt->end};
        const bool againstUpper{isUpper && &v == upperIt->start - 1};
        switch (againstUpper + againstUpper + againstLower)
        {
            // Create a new inactive range
            // [...]...X...[...] -> [...]...[X]...[...]
            // [...]...X...      -> [...]...[X]...
            // [...]...X         -> [...]...[X]
            //      ...X...[...] ->      ...[X]...[...]
            //         X...[...] ->         [X]...[...]
            //      ...X...      ->      ...[X]...
            //         X         ->         [X]
            case 0:
            {
                _inactiveRanges.insert(lowerIt, _Range{&v, &v + 1}); // TODO: Change to `emplace` once intellisense supports it
                break;
            }

            // Expand the lower inactive range
            // [...]...X[...] -> [...]...[X...]
            //      ...X[...] ->      ...[X...]
            //         X[...] ->         [X...]
            case 1:
            {
                ++lowerIt->end;
                break;
            }

            // Expand the upper inactive range
            // [...]X...[...] -> [...X]...[...]
            // [...]X...      -> [...X]...
            // [...]X         -> [...X]
            case 2:
            {
                --upperIt->start;
                break;
            }

            // Merge the inactive ranges
            // [...]X[...] -> [...X...]
            case 3:
            {
                upperIt->start = lowerIt->start;
                _inactiveRanges.erase(lowerIt);
                break;
            }
        }

        --_usedCount;
    }

    template <typename T>
    inline bool ObjectSlab<T>::contains(const T & v) const noexcept
    {
        return &v >= _slabRange.start && &v < _slabRange.end;
    }

    template <typename T>
    inline auto ObjectSlab<T>::begin() noexcept -> iterator
    {
        const const_iterator it{const_cast<const ObjectSlab *>(this)->begin()};
        return iterator{const_cast<T *>(it._slot), const_cast<_Range *>(it._nextInactiveRange)};
    }

    template <typename T>
    inline auto ObjectSlab<T>::begin() const noexcept -> const_iterator
    {
        const _Range * const lowestInactiveRange{_inactiveRanges.data() + _inactiveRanges.size() - 1};
        if (_inactiveRanges.empty() || lowestInactiveRange->start > _slabRange.start)
        {
            return const_iterator{_slabRange.start, lowestInactiveRange};
        }
        else
        {
            return const_iterator{lowestInactiveRange->end, lowestInactiveRange - 1};
        }
    }

    template <typename T>
    inline auto ObjectSlab<T>::end() noexcept -> iterator
    {
        return iterator{_slabRange.end, nullptr};
    }

    template <typename T>
    inline auto ObjectSlab<T>::end() const noexcept -> const_iterator
    {
        return const_iterator{_slabRange.end, nullptr};
    }

    template <typename T>
    inline auto ObjectSlab<T>::_find(const T * const slot) noexcept -> typename std::vector<_Range>::iterator
    {
        return lowerBound(_inactiveRanges.begin(), _inactiveRanges.end(), slot, [](const _Range & range, const T * const slot) -> bool { return range.start <= slot; });
    }

    template <typename T>
    template <bool constant>
    ObjectSlab<T>::_Iterator<constant>::_Iterator(const _Iterator<false> & other) noexcept requires constant :
        _slot{other._slot},
        _nextInactiveRange{other._nextInactiveRange}
    {}

    template <typename T>
    template <bool constant>
    ObjectSlab<T>::_Iterator<constant>::_Iterator(T_ * const slot, _Range_ * const nextInactiveRange) noexcept :
        _slot{slot},
        _nextInactiveRange{nextInactiveRange}
    {}

    template <typename T>
    template <bool constant>
    auto ObjectSlab<T>::_Iterator<constant>::operator++() noexcept -> _Iterator &
    {
        ++_slot;

        if (_slot == _nextInactiveRange->start)
        {
            _slot = _nextInactiveRange->end;
            --_nextInactiveRange;
        }

        return *this;
    }

    template <typename T>
    template <bool constant>
    auto ObjectSlab<T>::_Iterator<constant>::operator++(int) noexcept -> _Iterator
    {
        _Iterator temp{*this};
        ++*this;
        return temp;
    }

    template <typename T>
    template <bool constant>
    bool ObjectSlab<T>::_Iterator<constant>::operator==(const _Iterator & other) const noexcept
    {
        return _slot == other._slot;
    }
}
