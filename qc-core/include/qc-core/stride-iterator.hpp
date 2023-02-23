#pragma once

#include <iterator>

#include <qc-core/core.hpp>

namespace qc
{
    template <typename T>
    class StrideIter
    {
      public:

        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using reference = value_type &;
        using pointer = value_type *;
        using difference_type = ptrdiff_t;

        //
        // `stride` should be at least `sizeof(value_type)` and an even multiple of `alignof(value_type)`
        //
        constexpr StrideIter(value_type * ptr, const unat stride) :
            _ptr(ptr),
            _stride(stride)
        {}

        constexpr StrideIter(const StrideIter & other) = default;

        template <typename U> requires (Same<U, T> && std::is_const_v<T>)
        constexpr explicit StrideIter(const StrideIter<U> & other) :
            _ptr(other._ptr),
            _stride(other._stride)
        {}

        constexpr StrideIter(StrideIter && other) = default;

        StrideIter & operator=(const StrideIter & other) = default;

        template <typename U> requires (Same<U, T> && std::is_const_v<T>)
        StrideIter & operator=(const StrideIter<U> & other)
        {
            if (&other == this)
            {
                return *this;
            }

            _ptr = other._ptr;
            _stride = other._stride;

            return *this;
        }

        StrideIter & operator=(StrideIter && other) = default;

        ~StrideIter() = default;

        value_type & operator*() const
        {
            return *_ptr;
        }

        value_type * operator->() const
        {
            return _ptr;
        }

        StrideIter & operator++()
        {
            using Byte = std::conditional_t<std::is_const_v<value_type>, const std::byte, std::byte>;
            reinterpret_cast<Byte * &>(_ptr) += _stride;
            return *this;
        }

        StrideIter operator++(int)
        {
            StrideIter temp(*this);
            operator++();
            return temp;
        }

        difference_type operator-(const StrideIter other) const
        {
            return (reinterpret_cast<const std::byte *>(_ptr) - reinterpret_cast<const std::byte *>(other._ptr)) / _stride;
        }

        template <typename U>
        requires Same<U, T>
        constexpr bool operator==(const StrideIter<U> other) const
        {
            return _ptr == other._ptr;
        }

      private:

        value_type * _ptr;
        unat _stride;
    };
}
