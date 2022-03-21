#pragma once

#include <vector>

namespace qc
{
    template <typename T>
    class UniqueOrderedVector
    {
        public: //--------------------------------------------------------------

        using value_type = T;
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using reference = T &;
        using const_reference = const T &;
        using pointer = T *;
        using const_pointer = const T *;
        using iterator = typename std::vector<T>::iterator;
        using const_iterator = typename std::vector<T>::const_iterator;
        using reverse_iterator = typename std::vector<T>::reverse_iterator;
        using const_reverse_iterator = typename std::vector<T>::const_reverse_iterator;

        UniqueOrderedVector() noexcept = default;

        UniqueOrderedVector(const UniqueOrderedVector &) noexcept = default;
        UniqueOrderedVector(UniqueOrderedVector &&) noexcept = default;

        ~UniqueOrderedVector() noexcept = default;

        void reserve(size_t capacty);

        std::pair<iterator, bool> insert(const T & v);
        std::pair<iterator, bool> insert(T && v);

        template <typename... Args> std::pair<iterator, bool> emplace(Args &&... args);

        iterator find(const T & v) noexcept;
        const_iterator find(const T & v) const noexcept;

        iterator findFirstGreaterThanOrEqualTo(const T & v) noexcept;
        const_iterator findFirstGreaterThanOrEqualTo(const T & v) const noexcept;

        bool contains(const T & v) noexcept;

        iterator erase(iterator pos);
        bool erase(const T & v);

        void clear() noexcept;

        size_t size() const noexcept { return _data.size(); }

        bool empty() const noexcept { return _data.empty(); }

        iterator begin() noexcept { return _data.begin(); }
        const_iterator begin() const noexcept { return _data.begin(); }
        const_iterator cbegin() const noexcept { return _data.cbegin(); }

        iterator end() noexcept { return _data.end(); }
        const_iterator end() const noexcept { return _data.end(); }
        const_iterator cend() const noexcept { return _data.cend(); }

        reverse_iterator rbegin() noexcept { return _data.rbegin(); }
        const_reverse_iterator rbegin() const noexcept { return _data.rbegin(); }
        const_reverse_iterator rcbegin() const noexcept { return _data.rcbegin(); }

        reverse_iterator rend() noexcept { return _data.rend(); }
        const_reverse_iterator rend() const noexcept { return _data.rend(); }
        const_reverse_iterator rcend() const noexcept { return _data.rcend(); }

        private: //-------------------------------------------------------------

        std::vector<T> _data{};

        template <typename T_> std::pair<iterator, bool> _insert(T_ && v);
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    void UniqueOrderedVector<T>::reserve(const size_t capacity)
    {
        _data.reserve(capacity);
    }

    template <typename T>
    auto UniqueOrderedVector<T>::insert(const T & v) -> std::pair<iterator, bool>
    {
        return _insert(v);
    }

    template <typename T>
    auto UniqueOrderedVector<T>::insert(T && v) -> std::pair<iterator, bool>
    {
        return _insert(std::move(v));
    }

    template <typename T>
    template <typename... Args>
    auto UniqueOrderedVector<T>::emplace(Args &&... args) -> std::pair<iterator, bool>
    {
        return _insert(T{std::forward<Args>(args)...});
    }

    template <typename T>
    auto UniqueOrderedVector<T>::find(const T & v) noexcept -> iterator
    {
        const const_iterator pos{static_cast<const UniqueOrderedVector *>(this)->find(v)};
        return reinterpret_cast<const iterator &>(pos);
    }

    template <typename T>
    auto UniqueOrderedVector<T>::find(const T & v) const noexcept -> const_iterator
    {
        const const_iterator pos{findFirstGreaterThanOrEqualTo(v)};
        return (pos == _data.cend() || *pos == v) ? pos : _data.cend();
    }

    template <typename T>
    auto UniqueOrderedVector<T>::findFirstGreaterThanOrEqualTo(const T & v) noexcept -> iterator
    {
        const const_iterator pos{static_cast<const UniqueOrderedVector *>(this)->findFirstGreaterThanOrEqualTo(v)};
        return reinterpret_cast<const iterator &>(pos);
    }

    template <typename T>
    auto UniqueOrderedVector<T>::findFirstGreaterThanOrEqualTo(const T & v) const noexcept -> const_iterator
    {
        //--- Binary search ---

        size_t lowI{0u};
        size_t highI{_data.size()};

        while (lowI < highI)
        {
            const size_t midI{(lowI + highI) / 2u};

            if (_data[midI] < v)
            {
                lowI = midI + 1u;
            }
            else
            {
                highI = midI;
            }
        }

        return _data.cbegin() + lowI;
    }

    template <typename T>
    bool UniqueOrderedVector<T>::contains(const T & v) noexcept
    {
        return find(v) != _data.cend();
    }

    template <typename T>
    auto UniqueOrderedVector<T>::erase(const iterator pos) -> iterator
    {
        return _data.erase(pos);
    }

    template <typename T>
    bool UniqueOrderedVector<T>::erase(const T & v)
    {
        const iterator pos{find(v)};

        if (pos != _data.cend())
        {
            _data.erase(pos);
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename T>
    void UniqueOrderedVector<T>::clear() noexcept
    {
        _data.clear();
    }

    template <typename T>
    template <typename T_>
    auto UniqueOrderedVector<T>::_insert(T_ && v) -> std::pair<iterator, bool>
    {
        const iterator pos{findFirstGreaterThanOrEqualTo(v)};

        if (pos != _data.end() && *pos == v)
        {
            return {pos, false};
        }
        else
        {
            return {_data.insert(pos, std::forward<T_>(v)), true};
        }
    }
}
