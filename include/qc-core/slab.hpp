#pragma once

#include <utility>
#include <vector>

#include <qc-core/core-ext.hpp>
#include <qc-core/paging.hpp>

namespace qc
{
    struct SlabError {};

    namespace _internal
    {
        class SlabFriend;
    }

    template <typename T>
    class Slab
    {
        friend ::qc::_internal::SlabFriend;

        template <bool constant> class _Iterator;

      public:

        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using difference_type = ptrdiff_t;
        using size_type = size_t;
        using iterator = _Iterator<false>;
        using const_iterator = _Iterator<true>;

        using Error = SlabError;

        Slab() noexcept = default;
        explicit Slab(size_t maxSize) noexcept;

        Slab(const Slab &) = delete;
        Slab(Slab && other) noexcept;

        Slab & operator=(const Slab &) = delete;
        Slab & operator=(Slab && other) noexcept;

        ~Slab() noexcept;

        void setMaxSize(size_t maxSize);

        template <typename... Args> [[nodiscard]] T & construct(Args &&... args);

        void destruct(T & v);

        bool contains(const T * v) const noexcept;

        void freeUnusedPages();

        size_t maxSize() const noexcept { return _maxSize; }

        size_t size() const noexcept { return size_t(_slabRange.end - _slabRange.start); }

        size_t usedCount() const noexcept { return _usedCount; }

        size_t freeCount() const noexcept { return size() - _usedCount; }

        bool empty() const noexcept { return _usedCount == 0u; }

        bool full() const noexcept { return _usedCount == size(); }

        u32 maxPageCount() const noexcept { return _maxPageCount; }

        u32 pageCount() const noexcept { return _pageCount; }

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

        u32 _maxPageCount{};
        u32 _pageCount{};
        size_t _maxSize{};
        _Range _slabRange{};
        size_t _usedCount{};
        std::vector<_Range> _freeRanges{};

        void _expand();

        typename std::vector<_Range>::iterator _find(const T * slot) noexcept;
    };

    template <typename T>
    template <bool constant>
    class Slab<T>::_Iterator
    {
        friend Slab;

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
        _Range_ * _nextFreeRange{};

        _Iterator(T_ * slot, _Range_ * nextFreeRange) noexcept;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    Slab<T>::Slab(const size_t maxSize) noexcept
    {
        setMaxSize(maxSize);
    }

    template <typename T>
    inline Slab<T>::Slab(Slab && other) noexcept :
        _maxPageCount{std::exchange(other._maxPageCount, 0u)},
        _pageCount{std::exchange(other._pageCount, 0u)},
        _maxSize{std::exchange(other._maxSize, 0u)},
        _slabRange{std::exchange(other._slabRange, {})},
        _usedCount{std::exchange(other._usedCount, 0u)},
        _freeRanges{std::move(other._freeRanges)}
    {}

    template <typename T>
    inline Slab<T> & Slab<T>::operator=(Slab && other) noexcept
    {
        _maxPageCount = std::exchange(other._maxPageCount, 0u);
        _pageCount = std::exchange(other._pageCount, 0u);
        _maxSize = std::exchange(other._maxSize, 0u);
        _slabRange = std::exchange(other._slabRange, {});
        _usedCount = std::exchange(other._usedCount, 0u);
        _freeRanges = std::move(other._freeRanges);

        return *this;
    }

    template <typename T>
    inline Slab<T>::~Slab<T>() noexcept
    {
        // Destruct any in-use objects
        for (T & v : *this) v.~T();

        // Free memory
        freePages(_slabRange.start);

        if constexpr (debug)
        {
            _maxPageCount = 0u;
            _pageCount = 0u;
            _maxSize = 0u;
            _slabRange = {};
            _usedCount = 0u;
        }
    }

    template <typename T>
    inline void Slab<T>::setMaxSize(const size_t maxSize)
    {
        // May only be called before memory is reserved
        if (_slabRange.start)
        {
            throw Error{};
        }

        _maxPageCount =  u32((maxSize * sizeof(T) + pageSize - 1) / pageSize);
        _maxSize = _maxPageCount * pageSize / sizeof(T);
    }

    template <typename T>
    template <typename... Args>
    inline T & Slab<T>::construct(Args &&... args)
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
            _freeRanges.pop_back();
        }
        ++_usedCount;
        return *(new (lowSlot) T{std::forward<Args>(args)...});
    }

    template <typename T>
    inline void Slab<T>::destruct(T & v)
    {
        // Ensure the slot is in the slab
        if (!contains(&v))
        {
            throw Error{};
        }

        // Find the free range before or including the slot
        const auto lowerIt{_find(&v)};
        const bool isLower{lowerIt != _freeRanges.end()};
        const bool isUpper{lowerIt != _freeRanges.begin()};
        const auto upperIt{lowerIt - isUpper};

        // Ensure slot is in-use, i.e. it's not in a free range
        if (isLower && &v < lowerIt->end)
        {
            throw Error{};
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

        --_usedCount;
    }

    template <typename T>
    inline bool Slab<T>::contains(const T * const v) const noexcept
    {
        return v >= _slabRange.start && v < _slabRange.end;
    }

    template <typename T>
    inline void Slab<T>::freeUnusedPages()
    {
        // Slab is full or unallocated
        if (_freeRanges.empty())
        {
            return;
        }

        _Range & highRange{_freeRanges.front()};

        // The tail of the allocated memory is in use
        if (highRange.end != _slabRange.end)
        {
            return;
        }

        const size_t necessarySize{size_t(highRange.start - _slabRange.start)};
        const u32 necessaryPageCount{u32((necessarySize * sizeof(T) + pageSize - 1u) / pageSize)};
        const u32 unnecessaryPageCount{_pageCount - necessaryPageCount};

        // Not enough free tail slots to make up a page
        if (!unnecessaryPageCount)
        {
            return;
        }

        // Decommit uneccessary pages
        decommitPages(reinterpret_cast<std::byte *>(_slabRange.start) + necessaryPageCount * pageSize, unnecessaryPageCount);

        // Update state
        _pageCount = necessaryPageCount;
        const size_t newSize{_pageCount * pageSize / sizeof(T)};
        _slabRange.end = _slabRange.start + newSize;
        highRange.end = _slabRange.end;
        if (highRange.end == highRange.start)
        {
            _freeRanges.erase(_freeRanges.begin());
        }
    }

    template <typename T>
    inline auto Slab<T>::begin() noexcept -> iterator
    {
        const const_iterator it{const_cast<const Slab *>(this)->begin()};
        return reinterpret_cast<const iterator &>(it);
    }

    template <typename T>
    inline auto Slab<T>::begin() const noexcept -> const_iterator
    {
        if (_freeRanges.empty())
        {
            return const_iterator{_slabRange.start, &_nullRange};
        }
        else
        {
            const _Range & lowestFreeRange{_freeRanges.back()};

            // First in-use range is at the start of the slab
            if (lowestFreeRange.start > _slabRange.start)
            {
                return const_iterator{_slabRange.start, &lowestFreeRange};
            }
            // First in-use range is after the free range at the start of the slab
            else
            {
                return const_iterator{lowestFreeRange.end, &lowestFreeRange - 1};
            }
        }
    }

    template <typename T>
    inline auto Slab<T>::end() noexcept -> iterator
    {
        return iterator{_slabRange.end, nullptr};
    }

    template <typename T>
    inline auto Slab<T>::end() const noexcept -> const_iterator
    {
        return const_iterator{_slabRange.end, nullptr};
    }

    template <typename T>
    inline void Slab<T>::_expand()
    {
        // Reserve virtual memory if haven't done so already
        if (!_slabRange.start)
        {
            // Max size must have been set by this point
            if (!_maxPageCount)
            {
                throw Error{};
            }

            _slabRange.start = static_cast<T *>(reservePages(_maxPageCount));
            _slabRange.end = _slabRange.start;
        }

        // Ensure we still have more reserved pages
        if (_pageCount == _maxPageCount)
        {
            throw Error{};
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
        std::byte * const pages{reinterpret_cast<std::byte *>(_slabRange.start)};
        commitPages(pages + _pageCount * pageSize, newPageCount - _pageCount);
        _pageCount = newPageCount;

        // Update slab range
        const size_t newSize{_pageCount * pageSize / sizeof(T)};
        T * const currentRangeEnd{_slabRange.end};
        _slabRange.end = _slabRange.start + newSize;

        // Update free ranges
        if (_freeRanges.empty() || _freeRanges.front().end != currentRangeEnd)
        {
            // Insert new free range
            _freeRanges.insert(_freeRanges.begin(), _Range{currentRangeEnd, _slabRange.end}); // TODO: Switch to `emplace` once intellisense supports it
        }
        else
        {
            // Update existing free range
            _freeRanges.front().end = _slabRange.end;
        }
    }

    template <typename T>
    inline auto Slab<T>::_find(const T * const slot) noexcept -> typename std::vector<_Range>::iterator
    {
        return lowerBound(_freeRanges.begin(), _freeRanges.end(), slot, [](const _Range & range, const T * const slot) -> bool { return range.start <= slot; });
    }

    template <typename T>
    template <bool constant>
    Slab<T>::_Iterator<constant>::_Iterator(const _Iterator<false> & other) noexcept requires constant :
        _slot{other._slot},
        _nextFreeRange{other._nextFreeRange}
    {}

    template <typename T>
    template <bool constant>
    Slab<T>::_Iterator<constant>::_Iterator(T_ * const slot, _Range_ * const nextFreeRange) noexcept :
        _slot{slot},
        _nextFreeRange{nextFreeRange}
    {}

    template <typename T>
    template <bool constant>
    auto Slab<T>::_Iterator<constant>::operator++() noexcept -> _Iterator &
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
    auto Slab<T>::_Iterator<constant>::operator++(int) noexcept -> _Iterator
    {
        _Iterator temp{*this};
        ++*this;
        return temp;
    }

    template <typename T>
    template <bool constant>
    bool Slab<T>::_Iterator<constant>::operator==(const _Iterator & other) const noexcept
    {
        return _slot == other._slot;
    }
}
