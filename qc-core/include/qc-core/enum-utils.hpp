#pragma once

#include <array>
#include <iterator>
#include <type_traits>

#include <qc-core/core.hpp>

namespace qc
{
    template <typename E>
    concept CountableEnum =
        std::is_enum_v<E> &&
        std::is_unsigned_v<std::underlying_type_t<E>> &&
        requires { E::_n; };

    template <CountableEnum E> constexpr unat enumCount{unat(E::_n)};

    // Don't think we need this, but keeping it around for a little while just in case
    #if 0

    template <CountableEnum E>
    struct EnumIterator
    {
        using iterator_category = std::input_iterator_tag;
        using difference_type = ptrdiff_t;
        using value_type = const E;
        using pointer = const E *;
        using reference = const E &;

        E current{};

        constexpr reference operator*() const
        {
            return current;
        }

        constexpr pointer operator->() const
        {
            return &current;
        }

        constexpr EnumIterator & operator++()
        {
            current = E(underlyingVal(current) + 1u);
            return *this;
        };

        constexpr EnumIterator operator++(int)
        {
            EnumIterator temp{*this};
            ++*this;
            return temp;
        }

        constexpr bool operator==(const EnumIterator &) const = default;
    };

    // Ensure `EnumIterator<const E>` resolves to same type as `EnumIterator<E>`
    template <CountableEnum E> requires (std::is_const_v<E>) struct EnumIterator<E> : EnumIterator<std::remove_const_t<E>> {};

    template <CountableEnum E>
    struct EnumIteration
    {
        constexpr EnumIterator<E> begin() const
        {
            return {};
        }

        constexpr EnumIterator<E> end() const
        {
            return {E::_n};
        }
    };

    // Ensure `EnumIteration<const E>` resolves to same type as `EnumIteration<E>`
    template <CountableEnum E> requires (std::is_const_v<E>) struct EnumIteration<E> : EnumIteration<std::remove_const_t<E>> {};

    template <CountableEnum E> constexpr EnumIteration<E> iterateEnum{};

    #endif

    namespace _internal
    {
        template <CountableEnum E>
        constexpr std::array<E, enumCount<E>> makeEnumArray()
        {
            std::array<E, enumCount<E>> array{};
            for (E v{}; v != E::_n; v = E(underlyingVal(v) + 1u))
            {
                array[underlyingVal(v)] = v;
            }
            return array;
        }
    }

    template <CountableEnum E> constexpr std::array<E, enumCount<E>> enumArray{_internal::makeEnumArray<E>()};
}
