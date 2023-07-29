#pragma once

#include <array>

#include <qc-core/core.hpp>

namespace qc
{
    struct FillTag {};

    constexpr FillTag fill{};

    template <typename T, u32 n>
    struct Array : std::array<T, n>
    {
        constexpr Array() :
            std::array<T, n>{}
        {};

        template <typename T_>
        requires (n == 1u)
        constexpr Array(T_ && val) :
            std::array<T, n>{std::forward<T_>(val)}
        {}

        template <typename First, typename Second, typename... Rest>
        requires (sizeof...(Rest) == n - 2u)
        constexpr Array(First && first, Second && second, Rest &&... rest) :
            std::array<T, n>{std::forward<First>(first), std::forward<Second>(second), std::forward<Rest>(rest)...}
        {}

        constexpr Array(FillTag, const T & v)
        {
            for (T & element : *this) element = v;
        }

        constexpr Array(const std::array<T, n> & array) :
            std::array<T, n>{array}
        {}

        constexpr Array(std::array<T, n> && array) :
            std::array<T, n>{std::move(array)}
        {}
    };
}
