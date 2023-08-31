#pragma once

#include <qc-core/view.hpp>

namespace qc
{
    struct FillTag {};

    template <typename T, u32 n>
    struct Array
    {
        static_assert(n > 0u);

        inline static constexpr u32 size{n};

        T data[n];

        constexpr Array() = default;
        template <typename T_> requires (n == 1u) constexpr Array(T_ && val);
        template <typename First, typename Second, typename... Rest> requires (sizeof...(Rest) == n - 2u) constexpr Array(First && first, Second && second, Rest &&... rest);
        constexpr Array(FillTag, const T & v);

        constexpr Array(const Array &) = default;
        constexpr Array(Array &&) = default;

        Array & operator=(const Array &) = default;
        Array & operator=(Array &&) = default;

        nodisc finline operator View<T>() { return {data, n}; }
        nodisc finline operator CView<T>() const { return {data, n}; }

        constexpr void fill(const T & v);

        /// Necessary to enable structured bindings
        template <u32 i> requires (i < n) nodisc finline constexpr       T &  get()       &  { return data[i]; }
        template <u32 i> requires (i < n) nodisc finline constexpr const T &  get() const &  { return data[i]; }
        template <u32 i> requires (i < n) nodisc finline constexpr       T && get()       && { return std::move(data[i]); }
        template <u32 i> requires (i < n) nodisc finline constexpr const T && get() const && { return std::move(data[i]); }

        nodisc finline constexpr T & operator[](const u32 i) { ASSERT(i < n); return data[i]; }
        nodisc finline constexpr const T & operator[](const u32 i) const { ASSERT(i < n); return data[i]; }

        nodisc finline constexpr T & front() { return *data; }
        nodisc finline constexpr const T & front() const { return *data; }

        nodisc finline constexpr T & back() { return data[n - 1u]; }
        nodisc finline constexpr const T & back() const { return data[n - 1u]; }

        nodisc finline constexpr T * begin() { return data; }
        nodisc finline constexpr const T * begin() const { return data; }
        nodisc finline constexpr const T * cbegin() const { return data; }

        nodisc finline constexpr T * end() { return data + n; }
        nodisc finline constexpr const T * end() const { return data + n; }
        nodisc finline constexpr const T * cend() const { return data + n; }

        nodisc constexpr bool operator==(const Array &) const = default;
    };
}

/// Necessary to enable structured bindings
template <typename T, qc::u32 n> struct std::tuple_size<qc::Array<T, n>> : std::integral_constant<std::size_t, n> {};

/// Necessary to enable structured bindings
template <std::size_t i, typename T, qc::u32 n> struct std::tuple_element<i, qc::Array<T, n>> { using type = T; };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T, u32 n>
    template <typename T_> requires (n == 1u)
    inline constexpr Array<T, n>::Array(T_ && val) :
        data{std::forward<T_>(val)}
    {}

    template <typename T, u32 n>
    template <typename First, typename Second, typename... Rest> requires (sizeof...(Rest) == n - 2u)
    inline constexpr Array<T, n>::Array(First && first, Second && second, Rest &&... rest) :
       data{std::forward<First>(first), std::forward<Second>(second), std::forward<Rest>(rest)...}
    {}

    template <typename T, u32 n>
    inline constexpr Array<T, n>::Array(FillTag, const T & v)
    {
        for (T & element : *this) element = v;
    }

    template <typename T, u32 n>
    inline constexpr void Array<T, n>::fill(const T & v)
    {
        for (T & element : *this) element = v;
    }
}
