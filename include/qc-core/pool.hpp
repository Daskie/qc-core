#pragma once

#include <utility>
#include <vector>

#include <qc-core/core-ext.hpp>
#include <qc-core/paging.hpp>

namespace qc
{
    struct PoolError {};

    // Common code for Pool and FixedPool
    template <typename T>
    class _Pool
    {
        template <bool constant> class _Iterator;

      public:

        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using difference_type = ptrdiff_t;
        using size_type = size_t;
        using iterator = _Iterator<false>;
        using const_iterator = _Iterator<true>;

        void destroy(T & v);

        bool contains(const T * v) const noexcept;

        size_t capacity() const noexcept { return size_t(_slotRange.end - _slotRange.start); }

        size_t size() const noexcept { return _size; }

        bool empty() const noexcept { return _size == 0u; }

        bool full() const noexcept { return _size == capacity(); }

        iterator begin() noexcept;
        const_iterator begin() const noexcept;
        const_iterator cbegin() const noexcept { return begin(); };

        iterator end() noexcept;
        const_iterator end() const noexcept;
        const_iterator cend() const noexcept { return end(); };

      protected:

        struct _Range
        {
            T * start;
            T * end;
        };

        inline static _Range _nullRange{};

        _Range _slotRange{};
        size_t _size{};
        std::vector<_Range> _freeRanges{};

        _Pool() noexcept = default;

        _Pool(const _Pool &) = delete;
        _Pool(_Pool && other) noexcept;

        _Pool & operator=(const _Pool &) = delete;
        _Pool & operator=(_Pool && other) noexcept;

        ~_Pool() noexcept;

        template <typename... Args> T & _create(Args &&... args);

        typename std::vector<_Range>::iterator _find(const T * slot) noexcept;
    };

    template <typename T>
    class Pool : public _Pool<T>
    {
      public:

        Pool() noexcept = default;
        explicit Pool(size_t maxCapacity) noexcept;

        Pool(Pool && other) noexcept;

        Pool & operator=(Pool && other) noexcept;

        ~Pool() noexcept;

        template <typename... Args> [[nodiscard]] T & create(Args &&... args);

        void setMaxCapacity(size_t maxCapacity);

        void freeUnusedPages();

        size_t maxCapacity() const noexcept { return _maxCapacity; };

        u32 maxPageCount() const noexcept { return _maxPageCount; }

        u32 pageCount() const noexcept { return _pageCount; }

      private:

        using typename _Pool<T>::_Range;

        using _Pool<T>::_slotRange;
        using _Pool<T>::_size;
        using _Pool<T>::_freeRanges;

        u32 _maxPageCount{};
        u32 _pageCount{};
        size_t _maxCapacity{};

        void _expand();
    };

    template <typename T>
    class FixedPool : public _Pool<T>
    {
      public:

        FixedPool() noexcept = default;
        explicit FixedPool(size_t capacity) noexcept;

        ~FixedPool() noexcept;

        template <typename... Args> [[nodiscard]] T & create(Args &&... args);

        void setCapacity(size_t capacity);

      private:

        using typename _Pool<T>::_Range;

        using _Pool<T>::_slotRange;
        using _Pool<T>::_size;
        using _Pool<T>::_freeRanges;
    };

    template <typename T>
    template <bool constant>
    class _Pool<T>::_Iterator
    {
        friend class _Pool<T>;

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
    inline void _Pool<T>::destroy(T & v)
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

    template <typename T>
    inline bool _Pool<T>::contains(const T * const v) const noexcept
    {
        return v >= _slotRange.start && v < _slotRange.end;
    }

    template <typename T>
    inline auto _Pool<T>::begin() noexcept -> iterator
    {
        const const_iterator it{const_cast<const _Pool *>(this)->begin()};
        return reinterpret_cast<const iterator &>(it);
    }

    template <typename T>
    inline auto _Pool<T>::begin() const noexcept -> const_iterator
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
    inline auto _Pool<T>::end() noexcept -> iterator
    {
        return iterator{_slotRange.end, nullptr};
    }

    template <typename T>
    inline auto _Pool<T>::end() const noexcept -> const_iterator
    {
        return const_iterator{_slotRange.end, nullptr};
    }

    template <typename T>
    inline _Pool<T>::_Pool(_Pool && other) noexcept :
        _slotRange{std::exchange(other._slotRange, {})},
        _size{std::exchange(other._size, 0u)},
        _freeRanges{std::move(other._freeRanges)}
    {}

    template <typename T>
    inline _Pool<T> & _Pool<T>::operator=(_Pool && other) noexcept
    {
        _slotRange = std::exchange(other._slotRange, {});
        _size = std::exchange(other._size, 0u);
        _freeRanges = std::move(other._freeRanges);

        return *this;
    }

    template <typename T>
    inline _Pool<T>::~_Pool() noexcept
    {
        if constexpr (debug)
        {
            _slotRange = {};
            _size = 0u;
        }
    }

    template <typename T>
    template <typename... Args>
    inline T & _Pool<T>::_create(Args &&... args)
    {
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

    template <typename T>
    inline auto _Pool<T>::_find(const T * const slot) noexcept -> typename std::vector<_Range>::iterator
    {
        return lowerBound(_freeRanges.begin(), _freeRanges.end(), slot, [](const _Range & range, const T * const slot) -> bool { return range.start <= slot; });
    }

    template <typename T>
    inline Pool<T>::Pool(const size_t maxCapacity) noexcept
    {
        setMaxCapacity(maxCapacity);
    }

    template <typename T>
    inline Pool<T>::Pool(Pool && other) noexcept :
        _Pool<T>{std::move(other)},
        _maxPageCount{std::exchange(other._maxPageCount, 0u)},
        _pageCount{std::exchange(other._pageCount, 0u)},
        _maxCapacity{std::exchange(other._maxCapacity, 0u)}
    {}

    template <typename T>
    inline Pool<T> & Pool<T>::operator=(Pool && other) noexcept
    {
        _Pool<T>::operator=(std::move(other));

        _maxPageCount = std::exchange(other._maxPageCount, 0u);
        _pageCount = std::exchange(other._pageCount, 0u);
        _maxCapacity = std::exchange(other._maxCapacity, 0u);

        return *this;
    }

    template <typename T>
    inline Pool<T>::~Pool() noexcept
    {
        if (_slotRange.start)
        {
            // Destruct any constructed objects
            if constexpr (!std::is_trivially_destructible_v<T>)
            {
                for (T & v: *this) v.~T();
            }

            // Free memory
            freePages(_slotRange.start);
        }

        if constexpr (debug)
        {
            _maxPageCount = 0u;
            _pageCount = 0u;
            _maxCapacity = 0u;
        }
    }

    template <typename T>
    inline void Pool<T>::setMaxCapacity(const size_t maxCapacity)
    {
        // May only be called before memory is reserved
        if (this->_slotRange.start)
        {
            throw PoolError{};
        }

        _maxPageCount =  u32((maxCapacity * sizeof(T) + pageSize - 1) / pageSize);
        _maxCapacity = _maxPageCount * pageSize / sizeof(T);
    }

    template <typename T>
    template <typename... Args>
    inline T & Pool<T>::create(Args &&... args)
    {
        if (_freeRanges.empty()) [[unlikely]]
        {
            _expand();
        }

        return this->_create(std::forward<Args>(args)...);
    }

    template <typename T>
    inline void Pool<T>::freeUnusedPages()
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
        const u32 unnecessaryPageCount{_pageCount - necessaryPageCount};

        // Not enough free tail slots to make up a page
        if (!unnecessaryPageCount)
        {
            return;
        }

        // Decommit uneccessary pages
        decommitPages(reinterpret_cast<std::byte *>(_slotRange.start) + necessaryPageCount * pageSize, unnecessaryPageCount);

        // Update state
        _pageCount = necessaryPageCount;
        const size_t newCapacity{_pageCount * pageSize / sizeof(T)};
        _slotRange.end = _slotRange.start + newCapacity;
        highRange.end = _slotRange.end;
        if (highRange.end == highRange.start)
        {
            _freeRanges.erase(_freeRanges.begin());
        }
    }

    template <typename T>
    inline void Pool<T>::_expand()
    {
        // Reserve virtual memory if haven't done so already
        if (!_slotRange.start)
        {
            // Max capacity must have been set by this point
            if (!_maxPageCount)
            {
                throw PoolError{};
            }

            _slotRange.start = static_cast<T *>(reservePages(_maxPageCount));
            _slotRange.end = _slotRange.start;
        }

        // Ensure we still have more reserved pages
        if (_pageCount == _maxPageCount)
        {
            throw PoolError{};
        }

        // Double the number of committed pages
        const u32 minPageCount{u32((sizeof(T) + pageSize - 1u) / pageSize)};
        u32 newPageCount{qc::max(_pageCount * 2u, minPageCount)};

        // Round up and reserve all pages if within +50% of new page count
        if (newPageCount + newPageCount / 2 >= _maxPageCount)
        {
            newPageCount = _maxPageCount;
        }

        // Commit new pages
        std::byte * const pages{reinterpret_cast<std::byte *>(_slotRange.start)};
        commitPages(pages + _pageCount * pageSize, newPageCount - _pageCount);
        _pageCount = newPageCount;

        // Update full range
        const size_t newCapacity{_pageCount * pageSize / sizeof(T)};
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

    template <typename T>
    inline FixedPool<T>::FixedPool(const size_t capacity) noexcept
    {
        setCapacity(capacity);
    }

    template <typename T>
    inline FixedPool<T>::~FixedPool() noexcept
    {
        if (_slotRange.start)
        {
            // Destruct any constructed objects
            if constexpr (!std::is_trivially_destructible_v<T>)
            {
                for (T & v: *this) v.~T();
            }

            // Free memory
            ::operator delete(_slotRange.start, std::align_val_t{alignof(T)});
        }
    }

    template <typename T>
    inline void FixedPool<T>::setCapacity(const size_t capacity)
    {
        // May only be called before memory is reserved
        if (_slotRange.start)
        {
            throw PoolError{};
        }

        // Ignore zero call
        if (capacity == 0u)
        {
            return;
        }

        _slotRange.start = static_cast<T *>(::operator new(capacity * sizeof(T), std::align_val_t{alignof(T)}));
        _slotRange.end = _slotRange.start + capacity;
        _freeRanges.push_back(_slotRange);
    }

    template <typename T>
    template <typename... Args>
    inline T & FixedPool<T>::create(Args &&... args)
    {
        if (_freeRanges.empty()) [[unlikely]]
        {
            throw PoolError{};
        }

        return this->_create(std::forward<Args>(args)...);
    }

    template <typename T>
    template <bool constant>
    inline _Pool<T>::_Iterator<constant>::_Iterator(const _Iterator<false> & other) noexcept requires constant :
        _slot{other._slot},
        _nextFreeRange{other._nextFreeRange}
    {}

    template <typename T>
    template <bool constant>
    inline _Pool<T>::_Iterator<constant>::_Iterator(_T * const slot, _Range * const nextFreeRange) noexcept :
        _slot{slot},
        _nextFreeRange{nextFreeRange}
    {}

    template <typename T>
    template <bool constant>
    inline auto _Pool<T>::_Iterator<constant>::operator++() noexcept -> _Iterator &
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
    inline auto _Pool<T>::_Iterator<constant>::operator++(int) noexcept -> _Iterator
    {
        const _Iterator tmp{*this};
        ++*this;
        return tmp;
    }

    template <typename T>
    template <bool constant>
    inline bool _Pool<T>::_Iterator<constant>::operator==(const _Iterator & other) const noexcept
    {
        return _slot == other._slot;
    }
}
