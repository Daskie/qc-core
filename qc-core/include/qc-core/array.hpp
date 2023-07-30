#pragma once

#include <array>

#include <qc-core/view.hpp>

namespace qc
{
    struct FillTag {};

    constexpr FillTag fill{};

    template <typename T, u32 n>
    struct Array : std::array<T, n> // TODO: Don't use std::array
    {
        forceinline constexpr Array() = default;

        template <typename T_>
        requires (n == 1u)
        forceinline constexpr Array(T_ && val) :
            std::array<T, n>{std::forward<T_>(val)}
        {}

        template <typename First, typename Second, typename... Rest>
        requires (sizeof...(Rest) == n - 2u)
        forceinline constexpr Array(First && first, Second && second, Rest &&... rest) :
            std::array<T, n>{std::forward<First>(first), std::forward<Second>(second), std::forward<Rest>(rest)...}
        {}

        constexpr Array(FillTag, const T & v)
        {
            for (T & element : *this) element = v;
        }

        forceinline constexpr Array(const std::array<T, n> & array) :
            std::array<T, n>{array}
        {}

        forceinline constexpr Array(std::array<T, n> && array) :
            std::array<T, n>{std::move(array)}
        {}

        nodisc forceinline operator View<T>() { return {this->data(), u32(this->size())}; }
        nodisc forceinline operator CView<T>() const { return {this->data(), u32(this->size())}; }
    };
}
