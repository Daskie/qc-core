#pragma once

#include <utility>
#include <vector>

#include <qc-core/core-ext.hpp>
#include <qc-core/pool-common.hpp>

namespace qc
{
    namespace _internal
    {
        class PoolFriend;
    }

    struct PoolError {};

    ///
    /// Stable, fixed size object pool
    ///
    /// Very similar to Sea, and should be kept mostly in sync
    ///
    template <typename T>
    class Pool
    {
        friend ::qc::_internal::PoolFriend;

        using _Range = _pool::Range<T>;
        template <bool constant> using _Iterator = _pool::Iterator<T, constant>;

      public:

        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using difference_type = ptrdiff_t;
        using size_type = size_t;
        using iterator = _Iterator<false>;
        using const_iterator = _Iterator<true>;

        Pool() noexcept = default;
        explicit Pool(size_t capacity) noexcept;

        Pool(const Pool &) = delete;
        Pool(Pool && other) noexcept;

        Pool & operator=(const Pool &) = delete;
        Pool & operator=(Pool && other) noexcept;

        ~Pool() noexcept;

        void setCapacity(size_t capacity);

        template <typename... Args> [[nodiscard]] T & create(Args &&... args);

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

      private:

        inline static _Range _nullRange{};

        _Range _slotRange{};
        size_t _size{};
        std::vector<_Range> _freeRanges{};

        void _expand();

        typename std::vector<_Range>::iterator _find(const T * slot) noexcept;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    inline Pool<T>::Pool(const size_t capacity) noexcept
    {
        setCapacity(capacity);
    }

    template <typename T>
    inline Pool<T>::Pool(Pool && other) noexcept :
        _slotRange{std::exchange(other._slotRange, {})},
        _size{std::exchange(other._size, 0u)},
        _freeRanges{std::move(other._freeRanges)}
    {}

    template <typename T>
    inline Pool<T> & Pool<T>::operator=(Pool && other) noexcept
    {
        _slotRange = std::exchange(other._slotRange, {});
        _size = std::exchange(other._size, 0u);
        _freeRanges = std::move(other._freeRanges);

        return *this;
    }

    template <typename T>
    inline Pool<T>::~Pool() noexcept
    {
        if (!_slotRange.start)
        {
            return;
        }

        // Destruct any constructed objects
        if constexpr (!std::is_trivially_destructible_v<T>)
        {
            for (T & v: *this) v.~T();
        }

        // Free memory
        ::operator delete(_slotRange.start, std::align_val_t{alignof(T)});

        if constexpr (debug)
        {
            _slotRange = {};
            _size = 0u;
        }
    }

    template <typename T>
    inline void Pool<T>::setCapacity(const size_t capacity)
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
    inline T & Pool<T>::create(Args &&... args)
    {
        if (_freeRanges.empty()) [[unlikely]]
        {
            throw PoolError{};
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

    template <typename T>
    inline void Pool<T>::destroy(T & v)
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
    inline bool Pool<T>::contains(const T * const v) const noexcept
    {
        return v >= _slotRange.start && v < _slotRange.end;
    }

    template <typename T>
    inline auto Pool<T>::begin() noexcept -> iterator
    {
        const const_iterator it{const_cast<const Pool *>(this)->begin()};
        return reinterpret_cast<const iterator &>(it);
    }

    template <typename T>
    inline auto Pool<T>::begin() const noexcept -> const_iterator
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
    inline auto Pool<T>::end() noexcept -> iterator
    {
        return iterator{_slotRange.end, nullptr};
    }

    template <typename T>
    inline auto Pool<T>::end() const noexcept -> const_iterator
    {
        return const_iterator{_slotRange.end, nullptr};
    }

    template <typename T>
    inline auto Pool<T>::_find(const T * const slot) noexcept -> typename std::vector<_Range>::iterator
    {
        return lowerBound(_freeRanges.begin(), _freeRanges.end(), slot, [](const _Range & range, const T * const slot) -> bool { return range.start <= slot; });
    }
}
