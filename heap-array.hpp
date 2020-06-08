#pragma once

#include <stdexcept>

namespace qc::core {

    template <typename T>
    class HeapArray {

        public: //--------------------------------------------------------------

        using value_type = T;
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using reference = T &;
        using const_reference = const T &;
        using pointer = T *;
        using const_pointer = const T *;
        using iterator = pointer;
        using const_iterator = const_pointer;

        static_assert(std::is_nothrow_default_constructible_v<T>);
        static_assert(std::is_nothrow_move_constructible_v<T>);
        static_assert(std::is_nothrow_move_assignable_v<T>);
        static_assert(std::is_nothrow_swappable_v<T>);
        static_assert(std::is_nothrow_destructible_v<T>);

        constexpr HeapArray() noexcept = default;

        explicit HeapArray(const size_t size) noexcept :
            _size(size),
            _values(_size ? static_cast<T *>(::operator new(_size * sizeof(T))) : nullptr)
        {
            if constexpr (!std::is_trivially_default_constructible_v<T>) {
                for (size_t i(0u); i < _size; ++i) {
                    new (_values + i) T();
                }
            }
        }

        HeapArray(const size_t size, const T & v) noexcept :
            _size(size),
            _values(_size ? ::operator new(_size * sizeof(T)) : nullptr)
        {
            for (size_t i(0u); i < _size; ++i) {
                new (_values + i) T(v);
            }
        }

        template <typename Iter>
        HeapArray(const Iter first, const Iter last) :
            _size(std::distance(first, last)),
            _values(_size ? static_cast<T *>(::operator new(_size * sizeof(T))) : nullptr)
        {
            if constexpr (std::is_trivially_copy_constructible_v<T>) {
                std::copy_n(first, _size, _values);
            }
            else {
                T * pos(_values);
                for (Iter iter(first); iter != last; ++iter, ++pos) {
                    new (pos) T(*iter);
                }
            }
        }

        HeapArray(T * const values, const size_t size) :
            _size(size),
            _values(values)
        {}

        HeapArray(const HeapArray & other) noexcept :
            _size(other._size),
            _values(_size ? static_cast<T *>(::operator new(_size * sizeof(T))) : nullptr)
        {
            for (size_t i(0u); i < _size; ++i) {
                new (_values + i) T(other._values[i]);
            }
        }

        constexpr HeapArray(HeapArray && other) noexcept :
            _size(std::exchange(other._size, 0u)),
            _values(std::exchange(other._values, nullptr))
        {}

        HeapArray & operator=(const HeapArray & other) noexcept {
            if (&other == this) {
                return *this;
            }

            if (_size == other.size) {
                for (size_t i(0u); i < _size; ++i) {
                    _values[i] = other._values[i];
                }
            }
            else {
                clear();

                if (other._size) {
                    _size = other._size;
                    _values = ::operator new(_size * sizeof(T));
                    for (size_t i(0u); i < _size; ++i) {
                        new (_values + i) T(other._values[i]);
                    }
                }
            }

            return *this;
        }

        HeapArray & operator=(HeapArray && other) noexcept {
            if (&other == this) {
                return *this;
            }

            clear();

            _size = std::exchange(other._size, 0u);
            _values = std::exchange(other._values, nullptr);

            return *this;
        }

        ~HeapArray() noexcept {
            clear();
        }

        constexpr void swap(HeapArray & other) noexcept {
            std::swap(_size, other._size);
            std::swap(_values, other._values);
        }

        constexpr size_t size() const noexcept {
            return _size;
        }

        constexpr bool empty() const noexcept {
            return bool(_size);
        }

        constexpr T * data() noexcept {
            return _values;
        }

        constexpr const T * data() const noexcept {
            return _values;
        }

        constexpr T & front() noexcept {
            return *_values;
        }

        constexpr const T & front() const noexcept {
            return *_values;
        }

        constexpr T & back() noexcept {
            return _values[_size - 1u];
        }

        constexpr const T & back() const noexcept {
            return _values[_size - 1u];
        }

        constexpr T & operator[](const size_t i) {
            return _values[i];
        }

        constexpr const T & operator[](const size_t i) const {
            return _values[i];
        }

        constexpr T & at(const size_t i) {
            return const_cast<T &>(const_cast<const HeapArray &>(*this).at(i));
        }

        constexpr const T & at(const size_t i) const {
            if (i >= _size) {
                throw std::out_of_range();
            }

            return operator[](i);
        }

        constexpr iterator begin() noexcept {
            return _values;
        }

        constexpr const_iterator begin() const noexcept {
            return _values;
        }

        constexpr const_iterator cbegin() const noexcept {
            return _values;
        }

        constexpr iterator end() noexcept {
            return _values + _size - 1u;
        }

        constexpr const_iterator end() const noexcept {
            return _values + _size - 1u;
        }

        constexpr const_iterator cend() const noexcept {
            return _values + _size - 1u;
        }

        void clear() noexcept {
            if (_size) {
                if constexpr (!std::is_trivially_destructible_v<T>) {
                    for (size_t i(0u); i < _size; ++i) {
                        _values[i].~T();
                    }
                }

                ::operator delete(_values);
                _size = 0u;
                _values = nullptr;
            }
        }

        private: //-------------------------------------------------------------

        size_t _size{};
        T * _values{};

    };

    template <typename T>
    bool operator==(const HeapArray<T> & arr1, const HeapArray<T> & arr2) {
        if (&arr1 == &arr2) {
            return true;
        }

        if (arr1.size() != arr2.size()) {
            return false;
        }

        for (size_t i(0u); i < arr1.size(); ++i) {
            if (arr1[i] != arr2[i]) {
                return false;
            }
        }

        return true;
    }

} // namespace qc::core

namespace std {

    template <typename T>
    inline constexpr void swap(qc::core::HeapArray<T> & lhs, qc::core::HeapArray<T> & rhs) noexcept {
        lhs.swap(rhs);
    }

} // namespace std
