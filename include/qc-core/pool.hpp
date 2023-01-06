#pragma once

#include <utility>
#include <vector>

#include <qc-core/core-ext.hpp>
#include <qc-core/paging.hpp>

namespace qc
{
    struct PoolError {};

    template <typename T, bool fixed = false> class Pool;
    template <typename T> using FixedPool = Pool<T, true>;

    template <typename T, bool fixed> class _PoolExtra;

    template <typename T>
    class _PoolExtra<T, true>
    {
        friend class Pool<T, true>;

      protected:

        _PoolExtra() noexcept = default;
    };

    template <typename T>
    class _PoolExtra<T, false>
    {
        friend class Pool<T, false>;

      public:

        void shrinkToFit();

        u32 maxPageCount() const noexcept { return _maxPageCount; }

        u32 pageCount() const noexcept { return _pageCount; }

      protected:

        u32 _maxPageCount{};
        u32 _pageCount{};
        unat _maxCapacity{};

        _PoolExtra() noexcept = default;
    };

    template <typename T, bool fixed>
    class Pool : public _PoolExtra<T, fixed>
    {
        static_assert(alignof(T) <= 8u); // TODO: Use std::align_val_t once supported by intellisense

        friend class _PoolExtra<T, fixed>;

        using _Extra = _PoolExtra<T, fixed>;

        template <bool constant> class _Iterator;

      public:

        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using difference_type = ptrdiff_t;
        using size_type = unat;
        using iterator = _Iterator<false>;
        using const_iterator = _Iterator<true>;

        Pool() noexcept = default;
        explicit Pool(unat capacity);

        Pool(const Pool &) = delete;
        Pool(Pool && other) noexcept;

        Pool & operator=(const Pool &) = delete;
        Pool & operator=(Pool && other) noexcept;

        ~Pool() noexcept;

        void setCapacity(unat capacity);

        template <typename... Args> [[nodiscard]] T & create(Args &&... args);

        void destroy(T & v);

        bool contains(const T * v) const noexcept;

        unat capacity() const noexcept;

        unat size() const noexcept { return _size; }

        bool empty() const noexcept { return _size == 0u; }

        bool full() const noexcept { return _size >= capacity(); }

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

        inline static _Range _nullRange{};

        _Range _slotRange{};
        unat _size{};
        std::vector<_Range> _freeRanges{};

        typename std::vector<_Range>::iterator _find(const T * slot) noexcept;

        void _expand() requires (!fixed);

        void _shrinkToFit() requires (!fixed);
    };

    template <typename T, bool fixed>
    template <bool constant>
    class Pool<T, fixed>::_Iterator
    {
        friend class Pool<T, fixed>;

        using _T = std::conditional_t<constant, const T, T>;
        using _Range = std::conditional_t<constant, const _Range, _Range>;

      public:

        using iterator_category = std::forward_iterator_tag;
        using value_type = _T;
        using reference = _T &;
        using pointer = _T *;
        using difference_type = ptrdiff_t;

        _Iterator(const _Iterator &) noexcept = default;
        _Iterator(const _Iterator<false> &) noexcept requires constant;

        _Iterator & operator=(const _Iterator &) noexcept = default;

        reference operator*() const noexcept { return *_slot; }

        pointer operator->() const noexcept { return _slot; }

        _Iterator & operator++() noexcept;
        _Iterator operator++(int) noexcept;

        bool operator==(const _Iterator & other) const noexcept;

      private:

        _T * _slot{};
        _Range * _nextFreeRange{};

        _Iterator(_T * slot, _Range * nextFreeRange) noexcept;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    inline void _PoolExtra<T, false>::shrinkToFit()
    {
        // Doing this weird little redirect so `shrinkToFit` doesn't show up in `FixedPool`'s intellisense
        static_cast<Pool<T, false> &>(*this)._shrinkToFit();
    }

    template <typename T, bool fixed>
    inline Pool<T, fixed>::Pool(const unat capacity)
    {
        setCapacity(capacity);
    }

    template <typename T, bool fixed>
    inline Pool<T, fixed>::Pool(Pool && other) noexcept :
        _PoolExtra<T, fixed>{std::exchange(static_cast<_Extra &>(other), {})},
        _slotRange{std::exchange(other._slotRange, {})},
        _size{std::exchange(other._size, 0u)},
        _freeRanges{std::move(other._freeRanges)}
    {}

    template <typename T, bool fixed>
    inline auto Pool<T, fixed>::operator=(Pool && other) noexcept -> Pool &
    {
        if (&other == this)
        {
            return *this;
        }

        static_cast<_Extra &>(*this) = std::exchange(static_cast<_Extra &>(other), {});
        _slotRange = std::exchange(other._slotRange, {});
        _size = std::exchange(other._size, 0u);
        _freeRanges = std::move(other._freeRanges);

        return *this;
    }

    template <typename T, bool fixed>
    inline Pool<T, fixed>::~Pool() noexcept
    {
        if (_slotRange.start)
        {
            // Destruct any constructed objects
            if constexpr (!std::is_trivially_destructible_v<T>)
            {
                for (T & v: *this) v.~T();
            }

            // Free memory
            if constexpr (fixed)
            {
                ::operator delete(_slotRange.start);
            }
            else
            {
                freePages(_slotRange.start);
            }
        }

        if constexpr (debug)
        {
            static_cast<_Extra &>(*this) = {};
            _slotRange = {};
            _size = 0u;
        }
    }

    template <typename T, bool fixed>
    inline void Pool<T, fixed>::setCapacity(const unat capacity)
    {
        // May only be called before memory is reserved
        if (_slotRange.start)
        {
            throw PoolError{};
        }

        if constexpr (fixed)
        {
            // Ignore zero call
            if (capacity == 0u)
            {
                return;
            }

            _slotRange.start = static_cast<T *>(::operator new(capacity * sizeof(T)));
            _slotRange.end = _slotRange.start + capacity;
            _freeRanges.push_back(_slotRange);
        }
        else
        {
            this->_maxPageCount = u32((capacity * sizeof(T) + pageSize - 1) / pageSize);
            this->_maxCapacity = this->_maxPageCount * pageSize / sizeof(T);
        }
    }

    template <typename T, bool fixed>
    template <typename... Args>
    inline T & Pool<T, fixed>::create(Args &&... args)
    {
        if (_freeRanges.empty()) [[unlikely]]
        {
            if constexpr (fixed)
            {
                throw PoolError{};
            }
            else
            {
                _expand();
            }
        }

        _Range & lowRange{_freeRanges.back()};
        T * const lowSlot{lowRange.start};
        ++lowRange.start;
        if (lowRange.start == lowRange.end)
        {
            _freeRanges.pop_back();
        }
        ++_size;
        return *(new (lowSlot) T{std::forward<Args>(args)...});
    }

    template <typename T, bool fixed>
    inline void Pool<T, fixed>::destroy(T & v)
    {
        // Ensure the slot is in the pool
        if (!contains(&v))
        {
            throw PoolError{};
        }

        // Find the free range before or including the slot
        const auto lowerIt{_find(&v)};
        const bool isLower{lowerIt != _freeRanges.end()};
        const bool isUpper{lowerIt != _freeRanges.begin()};
        const auto upperIt{lowerIt - isUpper};

        // Ensure slot is in-use, i.e. it's not in a free range
        if (isLower && &v < lowerIt->end)
        {
            throw PoolError{};
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
                _freeRanges.insert(lowerIt, _Range{&v, &v + 1}); // TODO: Change to `emplace` once intellisense supports it
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

    template <typename T, bool fixed>
    inline bool Pool<T, fixed>::contains(const T * const v) const noexcept
    {
        return v >= _slotRange.start && v < _slotRange.end;
    }

    template <typename T, bool fixed>
    inline unat Pool<T, fixed>::capacity() const noexcept
    {
        if constexpr (fixed)
        {
            return size_t(_slotRange.end - _slotRange.start);
        }
        else
        {
            return this->_maxCapacity;
        }
    }

    template <typename T, bool fixed>
    inline auto Pool<T, fixed>::begin() noexcept -> iterator
    {
        const const_iterator it{const_cast<const Pool *>(this)->begin()};
        return reinterpret_cast<const iterator &>(it);
    }

    template <typename T, bool fixed>
    inline auto Pool<T, fixed>::begin() const noexcept -> const_iterator
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

    template <typename T, bool fixed>
    inline auto Pool<T, fixed>::end() noexcept -> iterator
    {
        return iterator{_slotRange.end, nullptr};
    }

    template <typename T, bool fixed>
    inline auto Pool<T, fixed>::end() const noexcept -> const_iterator
    {
        return const_iterator{_slotRange.end, nullptr};
    }

    template <typename T, bool fixed>
    inline auto Pool<T, fixed>::_find(const T * const slot) noexcept -> typename std::vector<_Range>::iterator
    {
        return lowerBound(_freeRanges.begin(), _freeRanges.end(), slot, [](const _Range & range, const T * const slot) -> bool { return range.start <= slot; });
    }

    template <typename T, bool fixed>
    inline void Pool<T, fixed>::_expand() requires (!fixed)
    {
        // Reserve virtual memory if haven't done so already
        if (!_slotRange.start)
        {
            // Max capacity must have been set by this point
            if (!this->_maxPageCount)
            {
                throw PoolError{};
            }

            _slotRange.start = static_cast<T *>(reservePages(this->_maxPageCount));
            _slotRange.end = _slotRange.start;
        }

        // Ensure we still have more reserved pages
        if (this->_pageCount == this->_maxPageCount)
        {
            throw PoolError{};
        }

        // Double the number of committed pages
        const u32 minPageCount{u32((sizeof(T) + pageSize - 1u) / pageSize)};
        u32 newPageCount{qc::max(this->_pageCount * 2u, minPageCount)};

        // Round up and reserve all pages if within +50% of new page count
        if (newPageCount + newPageCount / 2 >= this->_maxPageCount)
        {
            newPageCount = this->_maxPageCount;
        }

        // Commit new pages
        std::byte * const pages{reinterpret_cast<std::byte *>(_slotRange.start)};
        commitPages(pages + this->_pageCount * pageSize, newPageCount - this->_pageCount);
        this->_pageCount = newPageCount;

        // Update full range
        const size_t newCapacity{this->_pageCount * pageSize / sizeof(T)};
        T * const currentRangeEnd{_slotRange.end};
        _slotRange.end = _slotRange.start + newCapacity;

        // Update free ranges
        if (_freeRanges.empty() || _freeRanges.front().end != currentRangeEnd)
        {
            // Insert new free range
            _freeRanges.insert(_freeRanges.begin(), _Range{currentRangeEnd, _slotRange.end}); // TODO: Switch to `emplace` once intellisense supports it
        }
        else
        {
            // Update existing free range
            _freeRanges.front().end = _slotRange.end;
        }
    }

    template <typename T, bool fixed>
    inline void Pool<T, fixed>::_shrinkToFit() requires (!fixed)
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

        const size_t necessaryCapacity{size_t(highRange.start - _slotRange.start)};
        const u32 necessaryPageCount{u32((necessaryCapacity * sizeof(T) + pageSize - 1u) / pageSize)};
        const u32 unnecessaryPageCount{this->_pageCount - necessaryPageCount};

        // Not enough free tail slots to make up a page
        if (!unnecessaryPageCount)
        {
            return;
        }

        // Decommit uneccessary pages
        decommitPages(reinterpret_cast<std::byte *>(_slotRange.start) + necessaryPageCount * pageSize, unnecessaryPageCount);

        // Update state
        this->_pageCount = necessaryPageCount;
        const size_t newCapacity{this->_pageCount * pageSize / sizeof(T)};
        _slotRange.end = _slotRange.start + newCapacity;
        highRange.end = _slotRange.end;
        if (highRange.end == highRange.start)
        {
            _freeRanges.erase(_freeRanges.begin());
        }
    }

    template <typename T, bool fixed>
    template <bool constant>
    inline Pool<T, fixed>::_Iterator<constant>::_Iterator(const _Iterator<false> & other) noexcept requires constant :
        _slot{other._slot},
        _nextFreeRange{other._nextFreeRange}
    {}

    template <typename T, bool fixed>
    template <bool constant>
    inline Pool<T, fixed>::_Iterator<constant>::_Iterator(_T * const slot, _Range * const nextFreeRange) noexcept :
        _slot{slot},
        _nextFreeRange{nextFreeRange}
    {}

    template <typename T, bool fixed>
    template <bool constant>
    inline auto Pool<T, fixed>::_Iterator<constant>::operator++() noexcept -> _Iterator &
    {
        ++_slot;

        if (_slot == _nextFreeRange->start)
        {
            _slot = _nextFreeRange->end;
            --_nextFreeRange;
        }

        return *this;
    }

    template <typename T, bool fixed>
    template <bool constant>
    inline auto Pool<T, fixed>::_Iterator<constant>::operator++(int) noexcept -> _Iterator
    {
        const _Iterator tmp{*this};
        ++*this;
        return tmp;
    }

    template <typename T, bool fixed>
    template <bool constant>
    inline bool Pool<T, fixed>::_Iterator<constant>::operator==(const _Iterator & other) const noexcept
    {
        return _slot == other._slot;
    }
}
