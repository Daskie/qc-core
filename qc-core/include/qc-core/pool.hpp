#pragma once

#include <utility>

#include <qc-core/core-ext.hpp>
#include <qc-core/list.hpp>
#include <qc-core/paging.hpp>

namespace qc
{
    ///
    /// ...
    /// Properties:
    ///   Create: O(1)
    ///   Destroy: O(log(m)), where `m` is the number of free ranges
    ///   Reference stable: Yes
    ///   Index stable: Yes
    ///   Order stable: Yes
    ///   Contiguous elements: No
    ///
    template <typename T>
    class Pool
    {
        template <bool constant> class _Iterator;

      public:

        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using difference_type = s64;
        using size_type = u64;
        using iterator = _Iterator<false>;
        using const_iterator = _Iterator<true>;

        Pool() = default;
        explicit Pool(u64 capacity);

        Pool(const Pool &) = delete;
        Pool(Pool && other);

        Pool & operator=(const Pool &) = delete;
        Pool & operator=(Pool && other);

        ~Pool();

        void setCapacity(u64 capacity);

        void shrinkToFit();

        template <typename... Args> nodisc T & create(Args &&... args);

        void destroy(T & v);

        nodisc bool contains(const T * v) const;

        nodisc u64 capacity() const;

        nodisc u64 size() const { return _size; }

        nodisc bool empty() const { return _size == 0u; }

        nodisc bool full() const { return _size >= capacity(); }

        nodisc u32 maxPageN() const { return _maxPageN; }

        nodisc u32 pageN() const { return _pageN; }

        nodisc iterator begin();
        nodisc const_iterator begin() const;
        nodisc const_iterator cbegin() const { return begin(); };

        nodisc iterator end();
        nodisc const_iterator end() const;
        nodisc const_iterator cend() const { return end(); };

      private:

        struct _Range
        {
            T * start;
            T * end;
        };

        inline static _Range _nullRange{};

        _Range _slotRange{};
        u64 _size{};
        List<_Range> _freeRanges{};
        u32 _maxPageN{};
        u32 _pageN{};
        u64 _maxCapacity{};

        nodisc _Range * _find(const T * slot);

        void _expand();
    };

    template <typename T>
    template <bool constant>
    class Pool<T>::_Iterator
    {
        friend class Pool<T>;

        using _T_ = std::conditional_t<constant, const T, T>;
        using _Range_ = std::conditional_t<constant, const _Range, _Range>;

      public:

        using iterator_category = std::forward_iterator_tag;
        using value_type = _T_;
        using reference = _T_ &;
        using pointer = _T_ *;
        using difference_type = s64;

        _Iterator(const _Iterator &) = default;
        _Iterator(const _Iterator<false> &) requires (constant);

        _Iterator & operator=(const _Iterator &) = default;

        nodisc reference operator*() const { return *_slot; }

        nodisc pointer operator->() const { return _slot; }

        _Iterator & operator++();
        _Iterator operator++(int);

        nodisc bool operator==(const _Iterator & other) const;

      private:

        _T_ * _slot{};
        _Range_ * _nextFreeRange{};

        _Iterator(_T_ * slot, _Range_ * nextFreeRange);
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    inline Pool<T>::Pool(const u64 capacity)
    {
        setCapacity(capacity);
    }

    template <typename T>
    inline Pool<T>::Pool(Pool && other) :
        _slotRange{std::exchange(other._slotRange, {})},
        _size{std::exchange(other._size, 0u)},
        _freeRanges{std::move(other._freeRanges)},
        _maxPageN{std::exchange(other._maxPageN, 0u)},
        _pageN{std::exchange(other._pageN, 0u)},
        _maxCapacity{std::exchange(other._maxCapacity, 0u)}
    {}

    template <typename T>
    inline auto Pool<T>::operator=(Pool && other) -> Pool &
    {
        if (&other == this)
        {
            return *this;
        }

        _slotRange = std::exchange(other._slotRange, {});
        _size = std::exchange(other._size, 0u);
        _freeRanges = std::move(other._freeRanges);
        _maxPageN = std::exchange(other._maxPageN, 0u);
        _pageN = std::exchange(other._pageN, 0u);
        _maxCapacity = std::exchange(other._maxCapacity, 0u);

        return *this;
    }

    template <typename T>
    inline Pool<T>::~Pool()
    {
        if (_slotRange.start)
        {
            // Destruct any constructed objects
            if constexpr (!std::is_trivially_destructible_v<T>)
            {
                for (T & v: *this) v.~T();
            }

            // Free memory
            freePages(_slotRange.start, this->_maxPageN);
        }

        if constexpr (debug)
        {
            _slotRange = {};
            _size = 0u;
            _maxPageN = 0u;
            _pageN = 0u;
            _maxCapacity = 0u;
        }
    }

    template <typename T>
    inline void Pool<T>::setCapacity(const u64 capacity)
    {
        // May only be called before memory is reserved
        if (_slotRange.start)
        {
            DEBUG_ABORT();
            return;
        }

        this->_maxPageN = u32((capacity * sizeof(T) + pageSize - 1) / pageSize);
        this->_maxCapacity = this->_maxPageN * pageSize / sizeof(T);
    }

    template <typename T>
    inline void Pool<T>::shrinkToFit()
    {
        // Pool is full or unallocated
        if (_freeRanges.empty())
        {
            return;
        }

        _Range & highRange{_freeRanges.front()};

        // The tail of the allocated memory is in use
        if (highRange.end != _slotRange.end)
        {
            return;
        }

        const u64 necessaryCapacity{u64(highRange.start - _slotRange.start)};
        const u32 necessaryPageN{u32((necessaryCapacity * sizeof(T) + pageSize - 1u) / pageSize)};
        const u32 unnecessaryPageN{this->_pageN - necessaryPageN};

        // Not enough free tail slots to make up a page
        if (!unnecessaryPageN)
        {
            return;
        }

        // Decommit uneccessary pages
        decommitPages(reinterpret_cast<std::byte *>(_slotRange.start) + necessaryPageN * pageSize, unnecessaryPageN);

        // Update state
        this->_pageN = necessaryPageN;
        const u64 newCapacity{this->_pageN * pageSize / sizeof(T)};
        _slotRange.end = _slotRange.start + newCapacity;
        highRange.end = _slotRange.end;
        if (highRange.end == highRange.start)
        {
            _freeRanges.erase(_freeRanges.begin());
        }
    }

    template <typename T>
    template <typename... Args>
    inline T & Pool<T>::create(Args &&... args)
    {
        if (_freeRanges.empty()) [[unlikely]]
        {
            _expand();
        }

        _Range & lowRange{_freeRanges.back()};
        T * const lowSlot{lowRange.start};
        ++lowRange.start;
        if (lowRange.start == lowRange.end)
        {
            _freeRanges.pop();
        }
        ++_size;
        return *(new (lowSlot) T{std::forward<Args>(args)...});
    }

    template <typename T>
    inline void Pool<T>::destroy(T & v)
    {
        // Ensure the slot is in the pool
        if (!contains(&v))
        {
            DEBUG_ABORT();
            return;
        }

        // Find the free range before or including the slot
        const auto lowerIt{_find(&v)};
        const bool isLower{lowerIt != _freeRanges.end()};
        const bool isUpper{lowerIt != _freeRanges.begin()};
        const auto upperIt{lowerIt - isUpper};

        // Ensure slot is in-use, i.e. it's not in a free range
        if (isLower && &v < lowerIt->end)
        {
            DEBUG_ABORT();
            return;
        }

        // Destruct object
        v.~T();

        // Add slot to free ranges
        const bool againstLower{isLower && &v == lowerIt->end};
        const bool againstUpper{isUpper && &v == upperIt->start - 1};
        switch (againstUpper + againstUpper + againstLower)
        {
            // Create a new free range
            // [...]...X...[...] -> [...]...[X]...[...]
            // [...]...X...      -> [...]...[X]...
            // [...]...X         -> [...]...[X]
            //      ...X...[...] ->      ...[X]...[...]
            //         X...[...] ->         [X]...[...]
            //      ...X...      ->      ...[X]...
            //         X         ->         [X]
            case 0:
            {
                _freeRanges.emplace(lowerIt, &v, &v + 1);
                break;
            }

            // Expand the lower free range
            // [...]...X[...] -> [...]...[X...]
            //      ...X[...] ->      ...[X...]
            //         X[...] ->         [X...]
            case 1:
            {
                ++lowerIt->end;
                break;
            }

            // Expand the upper free range
            // [...]X...[...] -> [...X]...[...]
            // [...]X...      -> [...X]...
            // [...]X         -> [...X]
            case 2:
            {
                --upperIt->start;
                break;
            }

            // Merge the free ranges
            // [...]X[...] -> [...X...]
            case 3:
            {
                upperIt->start = lowerIt->start;
                _freeRanges.erase(lowerIt);
                break;
            }
        }

        --_size;
    }

    template <typename T>
    inline bool Pool<T>::contains(const T * const v) const
    {
        return v >= _slotRange.start && v < _slotRange.end;
    }

    template <typename T>
    inline u64 Pool<T>::capacity() const
    {
        return this->_maxCapacity;
    }

    template <typename T>
    inline auto Pool<T>::begin() -> iterator
    {
        const const_iterator it{const_cast<const Pool *>(this)->begin()};
        return {const_cast<T *>(it._slot), const_cast<_Range *>(it._nextFreeRange)};
    }

    template <typename T>
    inline auto Pool<T>::begin() const -> const_iterator
    {
        if (_freeRanges.empty())
        {
            return const_iterator{_slotRange.start, &_nullRange};
        }
        else
        {
            const _Range & lowestFreeRange{_freeRanges.back()};

            // First in-use range is at the start of the pool
            if (lowestFreeRange.start > _slotRange.start)
            {
                return const_iterator{_slotRange.start, &lowestFreeRange};
            }
            // First in-use range is after the free range at the start of the pool
            else
            {
                return const_iterator{lowestFreeRange.end, &lowestFreeRange - 1};
            }
        }
    }

    template <typename T>
    inline auto Pool<T>::end() -> iterator
    {
        return iterator{_slotRange.end, nullptr};
    }

    template <typename T>
    inline auto Pool<T>::end() const -> const_iterator
    {
        return const_iterator{_slotRange.end, nullptr};
    }

    template <typename T>
    inline auto Pool<T>::_find(const T * const slot) -> _Range *
    {
        return lowerBound(_freeRanges.begin(), _freeRanges.end(), slot, [](const _Range & range, const T * const slot_) -> bool { return range.start <= slot_; });
    }

    template <typename T>
    inline void Pool<T>::_expand()
    {
        // Reserve virtual memory if haven't done so already
        if (!_slotRange.start)
        {
            // Max capacity must have been set by this point
            ABORT_IF(!this->_maxPageN);

            _slotRange.start = static_cast<T *>(reservePages(this->_maxPageN));
            _slotRange.end = _slotRange.start;
        }

        // Ensure we still have more reserved pages
        ABORT_IF(this->_pageN >= this->_maxPageN);

        // Double the number of committed pages
        const u32 minPageN{u32((sizeof(T) + pageSize - 1u) / pageSize)};
        u32 newPageN{qc::max(this->_pageN * 2u, minPageN)};

        // Round up and reserve all pages if within +50% of new page count
        if (newPageN + newPageN / 2 >= this->_maxPageN)
        {
            newPageN = this->_maxPageN;
        }

        // Commit new pages
        std::byte * const pages{reinterpret_cast<std::byte *>(_slotRange.start)};
        commitPages(pages + this->_pageN * pageSize, newPageN - this->_pageN);
        this->_pageN = newPageN;

        // Update full range
        const u64 newCapacity{this->_pageN * pageSize / sizeof(T)};
        T * const currentRangeEnd{_slotRange.end};
        _slotRange.end = _slotRange.start + newCapacity;

        // Update free ranges
        if (_freeRanges.empty() || _freeRanges.front().end != currentRangeEnd)
        {
            // Insert new free range
            _freeRanges.emplace(_freeRanges.begin(), currentRangeEnd, _slotRange.end);
        }
        else
        {
            // Update existing free range
            _freeRanges.front().end = _slotRange.end;
        }
    }

    template <typename T>
    template <bool constant>
    inline Pool<T>::_Iterator<constant>::_Iterator(const _Iterator<false> & other) requires (constant) :
        _slot{other._slot},
        _nextFreeRange{other._nextFreeRange}
    {}

    template <typename T>
    template <bool constant>
    inline Pool<T>::_Iterator<constant>::_Iterator(_T_ * const slot, _Range_ * const nextFreeRange) :
        _slot{slot},
        _nextFreeRange{nextFreeRange}
    {}

    template <typename T>
    template <bool constant>
    inline auto Pool<T>::_Iterator<constant>::operator++() -> _Iterator &
    {
        ++_slot;

        if (_slot == _nextFreeRange->start)
        {
            _slot = _nextFreeRange->end;
            --_nextFreeRange;
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

    template <typename T>
    template <bool constant>
    inline bool Pool<T>::_Iterator<constant>::operator==(const _Iterator & other) const
    {
        return _slot == other._slot;
    }
}
