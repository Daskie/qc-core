#pragma once

#include <iterator>
#include <type_traits>

#include <qc-core/core.hpp>

namespace qc
{
    template <typename E> concept IterableEnum =
        std::is_enum_v<E> &&
        std::is_unsigned_v<std::underlying_type_t<E>> &&
        requires { E::_n; };

    template <IterableEnum E>
    struct EnumIterator
    {
        using iterator_category = std::input_iterator_tag;
        using difference_type = ptrdiff_t;
        using value_type = const E;
        using pointer = const E *;
        using reference = const E &;

        E current{};

        reference operator*() const noexcept
        {
            return current;
        }

        pointer operator->() const noexcept
        {
            return &current;
        }

        EnumIterator & operator++() noexcept
        {
            ++reinterpret_cast<std::underlying_type_t<E> &>(current);
            return *this;
        };

        EnumIterator operator++(int) noexcept
        {
            EnumIterator temp{*this};
            ++*this;
            return temp;
        }

        bool operator==(const EnumIterator &) const noexcept = default;
    };

    // Ensure `EnumIterator<const E>` resolves to same type as `EnumIterator<E>`
    template <IterableEnum E> requires (std::is_const_v<E>) struct EnumIterator<E> : EnumIterator<std::remove_const_t<E>> {};

    template <IterableEnum E>
    struct EnumIteration
    {
        EnumIterator<E> begin() const noexcept
        {
            return {};
        }

        EnumIterator<E> end() const noexcept
        {
            return {E::_n};
        }
    };

    // Ensure `EnumIteration<const E>` resolves to same type as `EnumIteration<E>`
    template <IterableEnum E> requires (std::is_const_v<E>) struct EnumIteration<E> : EnumIteration<std::remove_const_t<E>> {};

    template <IterableEnum E> constexpr EnumIteration<E> iterateEnum{};
}
