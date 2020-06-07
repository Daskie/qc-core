#pragma once

namespace qc::core {

    template <typename T>
    class StrideIter {

        public: //--------------------------------------------------------------

        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        //using inv_const_value_type = std::conditional_t<std::is_const_v<value_type>, std::remove_c_t<value_type>, const value_type>;
        using difference_type = ptrdiff_t;
        using pointer = value_type *;
        using reference = value_type &;


        //
        // `stride` should be at least `sizeof(value_type)` and an even multiple of `alignof(value_type)`
        //
        constexpr StrideIter(value_type * ptr, const size_t stride) noexcept :
            _ptr(ptr),
            _stride(stride)
        {}

        constexpr StrideIter(const StrideIter & other) noexcept = default;

        template <typename U> requires (std::is_same_v<std::remove_const_t<U>, std::remove_const_t<T>> && std::is_const_v<T>)
        constexpr StrideIter(const StrideIter<U> & other) noexcept :
            _ptr(other._ptr),
            _stride(other._stride)
        {}

        constexpr StrideIter(StrideIter && other) noexcept = default;

        StrideIter & operator=(const StrideIter & other) noexcept = default;

        template <typename U> requires (std::is_same_v<std::remove_const_t<U>, std::remove_const_t<T>> && std::is_const_v<T>)
        StrideIter & operator=(const StrideIter<U> & other) noexcept {
            _ptr = other._ptr;
            _stride = other._stride;
        }

        StrideIter & operator=(StrideIter && other) noexcept = default;

        ~StrideIter() noexcept = default;

        value_type & operator*() const noexcept {
            return *_ptr;
        }

        value_type * operator->() const noexcept {
            return _ptr;
        }

        StrideIter & operator++() noexcept {
            using Byte = std::conditional_t<std::is_const_v<value_type>, const std::byte, std::byte>;
            reinterpret_cast<Byte * &>(_ptr) += _stride;
            return *this;
        }

        StrideIter operator++(int) noexcept {
            StrideIter temp(*this);
            operator++();
            return temp;
        }

        difference_type operator-(StrideIter other) const {
            return _ptr - other._ptr;
        }

        template <typename U> requires (std::is_same_v<std::remove_const_t<U>, std::remove_const_t<T>>)
        constexpr bool operator==(StrideIter<U> other) const noexcept {
            return _ptr == other._ptr;
        }

        private: //-------------------------------------------------------------

        value_type * _ptr;
        size_t _stride;

    };

} // namespace qc::core
