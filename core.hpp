#pragma once

#include <cstdint>
#include <limits>
#include <utility>

// Workaround for IntelliSense bug
#define Q_CONSTEX constexpr
#define Q_CX_ABLE

namespace qc::core {

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
        template <typename T> concept Orderable = Numeric<T> || std::is_pointer_v<T>;

    } // namespace types

    template <typename T, int n> struct _array_t_struct { using type = T[n]; };
    template <typename T> struct _array_t_struct<T, 0> { using type = T[]; };

    template <typename T, int n = 0> using array_t = typename _array_t_struct<T, n>::type;

    template <int size> struct sized;
    template <> struct sized<1> { using stype =  s8; using utype =  u8; };
    template <> struct sized<2> { using stype = s16; using utype = u16; };
    template <> struct sized<4> { using stype = s32; using utype = u32; using ftype = f32; };
    template <> struct sized<8> { using stype = s64; using utype = u64; using ftype = f64; };
    template <int size> using stype = typename sized<size>::stype;
    template <int size> using utype = typename sized<size>::utype;
    template <int size> using ftype = typename sized<size>::ftype;

    template <typename T> using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

    //
    // Unique identification of floating point numbers
    //
    //  precision | bits | digits
    // -----------+------+--------
    //  half      |   16 |      5
    //  single    |   32 |      9
    //  double    |   64 |     17
    //  extended  |   80 |     21
    //  quad      |  128 |     36
    //
    template <Floating T> constexpr T    pi = T(3.14159265358979323846264338327950288L);
    template <Floating T> constexpr T     e = T(2.71828182845904523536028747135266250L);
    template <Floating T> constexpr T   phi = T(1.61803398874989484820458683436563812L);
    template <Floating T> constexpr T sqrt2 = T(1.41421356237309504880168872420969808L);
    template <Floating T> constexpr T sqrt3 = T(1.73205080756887729352744634150587237L);
    template <Floating T> constexpr T sqrt5 = T(2.23606797749978969640917366873127624L);
    template <Floating T> constexpr T infinity = std::numeric_limits<T>::infinity();
    template <Floating T> constexpr T nan = std::numeric_limits<T>::quiet_NaN();

    //
    // ...
    //
    template <Orderable T> constexpr T min(T v1, T v2);
    template <typename T1, typename T2, typename T3, typename... Ts> constexpr decltype(auto) min(T1 && v1, T2 && v2, T3 && v3, Ts &&... vs);

    //
    // ...
    //
    template <Orderable T> constexpr T max(T v1, T v2);
    template <typename T1, typename T2, typename T3, typename... Ts> constexpr decltype(auto) max(T1 && v1, T2 && v2, T3 && v3, Ts &&... vs);

    //
    // ...
    //
    template <Orderable T> T & minify(T & v1, T v2);
    template <typename T, typename T1, typename T2, typename... Ts> T & minify(T & min, T1 && v1, T2 && v2, Ts &&... vs);

    //
    // ...
    //
    template <Orderable T> T & maxify(T & v1, T v2);
    template <typename T, typename T1, typename T2, typename... Ts> T & maxify(T & min, T1 && v1, T2 && v2, Ts &&... vs);

} // namespace qc::core

// INLINE IMPLEMENTATION ///////////////////////////////////////////////////////////////////////////////////////////////

namespace qc::core {

    template <Orderable T>
    inline constexpr T min(const T v1, const T v2) {
        return v1 <= v2 ? v1 : v2;
    }

    template <typename T1, typename T2, typename T3, typename... Ts>
    inline constexpr decltype(auto) min(T1 && v1, T2 && v2, T3 && v3, Ts &&... vs) {
        return min(min(std::forward<T1>(v1), std::forward<T2>(v2)), std::forward<T3>(v3), std::forward<Ts>(vs)...);
    }

    template <Orderable T>
    inline constexpr T max(const T v1, const T v2) {
        return v1 >= v2 ? v1 : v2;
    }

    template <typename T1, typename T2, typename T3, typename... Ts>
    inline constexpr decltype(auto) max(T1 && v1, T2 && v2, T3 && v3, Ts &&... vs) {
        return max(max(std::forward<T1>(v1), std::forward<T2>(v2)), std::forward<T3>(v3), std::forward<Ts>(vs)...);
    }

    template <Orderable T>
    inline T & minify(T & v1, const T v2) {
        return v1 <= v2 ? v1 : v1 = v2;
    }

    template <typename T, typename T1, typename T2, typename... Ts>
    inline T & minify(T & min, T1 && v1, T2 && v2, Ts &&... vs) {
        return minify(minify(min, std::forward<T1>(v1)), std::forward<T2>(v2), std::forward<Ts>(vs)...);
    }

    template <Orderable T>
    inline T & maxify(T & v1, const T v2) {
        return v1 >= v2 ? v1 : v1 = v2;
    }

    template <typename T, typename T1, typename T2, typename... Ts>
    inline T & maxify(T & min, T1 && v1, T2 && v2, Ts &&... vs) {
        return maxify(maxify(min, std::forward<T1>(v1)), std::forward<T2>(v2), std::forward<Ts>(vs)...);
    }

} // namespace qc::core
