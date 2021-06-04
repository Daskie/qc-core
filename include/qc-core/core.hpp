#pragma once

#include <cstdint>

#include <limits>
#include <utility>

namespace qc {

    inline namespace types {

        using uint = unsigned int;

        using s8 = int8_t;
        using u8 = uint8_t;
        using s16 = int16_t;
        using u16 = uint16_t;
        using s32 = int32_t;
        using u32 = uint32_t;
        using f32 = float;
        using s64 = int64_t;
        using u64 = uint64_t;
        using f64 = double;

        template <typename T> concept Integral = std::is_integral_v<T> && !std::is_same_v<T, bool> && !std::is_same_v<T, char>;
        template <typename T> concept SignedIntegral = Integral<T> && std::is_signed_v<T>;
        template <typename T> concept UnsignedIntegral = Integral<T> && std::is_unsigned_v<T>;
        template <typename T> concept Floating = std::is_floating_point_v<T>;
        template <typename T> concept Numeric = Integral<T> || Floating<T>;
        template <typename T> concept SignedNumeric = SignedIntegral<T> || Floating<T>;

    } // namespace types

    template <int size> struct sized;
    template <> struct sized<1> { using stype =  s8; using utype =  u8; };
    template <> struct sized<2> { using stype = s16; using utype = u16; };
    template <> struct sized<4> { using stype = s32; using utype = u32; using ftype = f32; };
    template <> struct sized<8> { using stype = s64; using utype = u64; using ftype = f64; };
    template <int size> using stype = typename sized<size>::stype;
    template <int size> using utype = typename sized<size>::utype;
    template <int size> using ftype = typename sized<size>::ftype;

    template <typename T> concept _MinMaxable = Numeric<T> || std::is_pointer_v<T>;

    //
    // ...
    //
    template <_MinMaxable T> constexpr T min(T v1, T v2);
    template <typename T1, typename T2, typename T3, typename... Ts> constexpr decltype(auto) min(T1 && v1, T2 && v2, T3 && v3, Ts &&... vs);

    //
    // ...
    //
    template <_MinMaxable T> constexpr T max(T v1, T v2);
    template <typename T1, typename T2, typename T3, typename... Ts> constexpr decltype(auto) max(T1 && v1, T2 && v2, T3 && v3, Ts &&... vs);

    //
    // ...
    //
    template <_MinMaxable T> T & minify(T & v1, T v2);
    template <typename T, typename T1, typename T2, typename... Ts> T & minify(T & min, T1 && v1, T2 && v2, Ts &&... vs);

    //
    // ...
    //
    template <_MinMaxable T> T & maxify(T & v1, T v2);
    template <typename T, typename T1, typename T2, typename... Ts> T & maxify(T & min, T1 && v1, T2 && v2, Ts &&... vs);

    //
    // ...
    //
    template <_MinMaxable T> constexpr std::pair<T, T> minmax(T v1, T v2);
    template <typename T1, typename T2, typename T3, typename... Ts> constexpr auto minmax(T1 && v1, T2 && v2, T3 && v3, Ts &&... vs);

} // namespace qc

// INLINE IMPLEMENTATION ///////////////////////////////////////////////////////////////////////////////////////////////

namespace qc {

    template <_MinMaxable T>
    inline constexpr T min(const T v1, const T v2) {
        return v2 < v1 ? v2 : v1;
    }

    template <typename T1, typename T2, typename T3, typename... Ts>
    inline constexpr decltype(auto) min(T1 && v1, T2 && v2, T3 && v3, Ts &&... vs) {
        return min(min(std::forward<T1>(v1), std::forward<T2>(v2)), std::forward<T3>(v3), std::forward<Ts>(vs)...);
    }

    template <_MinMaxable T>
    inline constexpr T max(const T v1, const T v2) {
        return v2 > v1 ? v2 : v1;
    }

    template <typename T1, typename T2, typename T3, typename... Ts>
    inline constexpr decltype(auto) max(T1 && v1, T2 && v2, T3 && v3, Ts &&... vs) {
        return max(max(std::forward<T1>(v1), std::forward<T2>(v2)), std::forward<T3>(v3), std::forward<Ts>(vs)...);
    }

    template <_MinMaxable T>
    inline T & minify(T & v1, const T v2) {
        return v2 < v1 ? v1 = v2 : v1;
    }

    template <typename T, typename T1, typename T2, typename... Ts>
    inline T & minify(T & min, T1 && v1, T2 && v2, Ts &&... vs) {
        return minify(minify(min, std::forward<T1>(v1)), std::forward<T2>(v2), std::forward<Ts>(vs)...);
    }

    template <_MinMaxable T>
    inline T & maxify(T & v1, const T v2) {
        return v2 > v1 ? v1 = v2 : v1;
    }

    template <typename T, typename T1, typename T2, typename... Ts>
    inline T & maxify(T & min, T1 && v1, T2 && v2, Ts &&... vs) {
        return maxify(maxify(min, std::forward<T1>(v1)), std::forward<T2>(v2), std::forward<Ts>(vs)...);
    }

    template <_MinMaxable T>
    inline constexpr std::pair<T, T> minmax(const T v1, const T v2) {
        return (v2 < v1) ? std::pair{v2, v1} : std::pair{v1, v2};
    }

    template <typename T1, typename T2, typename T3, typename... Ts>
    inline constexpr auto minmax(T1 && v1, T2 && v2, T3 && v3, Ts &&... vs) {
        if constexpr (!sizeof...(Ts)) {
            const auto [min1, max1]{minmax(v1, v2)};
            return std::pair{min(min1, v3), max(max1, v3)};
        }
        else {
            const auto [min1, max1]{minmax(v1, v2)};
            const auto [min2, max2]{minmax(v3, vs...)};
            return std::pair{min(min1, min2), max(max1, max2)};
        }
    }

} // namespace qc
