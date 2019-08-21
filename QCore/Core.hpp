#pragma once

#include <cstdint>
#include <limits>
#include <utility>

// workaround for IntelliSense bug
#define Q_CONSTEX constexpr
#define Q_CX_ABLE inline

namespace qc {

namespace types {

    using llong = long long;

    using  uchar = unsigned char;
    using ushort = unsigned short;
    using   uint = unsigned int;
    using  ulong = unsigned long;
    using ullong = unsigned long long;

    using s08 = int8_t;
    using s16 = int16_t;
    using s32 = int32_t;
    using s64 = int64_t;
    using u08 = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;
    using f32 = float;
    using f64 = double;

    using s08_fast = int_fast8_t;
    using s16_fast = int_fast16_t;
    using s32_fast = int_fast32_t;
    using s64_fast = int_fast64_t;
    using u08_fast = uint_fast8_t;
    using u16_fast = uint_fast16_t;
    using u32_fast = uint_fast32_t;
    using u64_fast = uint_fast64_t;

    using  nat =  intptr_t;
    using unat = uintptr_t;

    constexpr  nat  operator""_n(unsigned long long int v) { return  nat(v); }
    constexpr unat operator""_un(unsigned long long int v) { return unat(v); }

    using std::move;
    using std::forward;

    using std::pair;
    template <typename T> using duo = pair<T, T>;

}

using namespace types;

template <typename T, typename... Ts> constexpr bool is_same_v = std::conjunction_v<std::is_same<T, Ts>...>;
template <typename... Ts> constexpr bool     is_arithmetic_v = std::conjunction_v<std::    is_arithmetic<Ts>...>;
template <typename... Ts> constexpr bool       is_integral_v = std::conjunction_v<std::      is_integral<Ts>...>;
template <typename... Ts> constexpr bool is_floating_point_v = std::conjunction_v<std::is_floating_point<Ts>...>;
template <typename... Ts> constexpr bool         is_signed_v = std::conjunction_v<std::        is_signed<Ts>...>;
template <typename... Ts> constexpr bool       is_unsigned_v = std::conjunction_v<std::      is_unsigned<Ts>...>;

template <bool t_b> using eif_t = std::enable_if_t<t_b>;

template <typename... Ts> using eif_arithmetic_t = eif_t<    is_arithmetic_v<Ts...>>;
template <typename... Ts> using   eif_floating_t = eif_t<is_floating_point_v<Ts...>>;
template <typename... Ts> using   eif_integral_t = eif_t<      is_integral_v<Ts...>>;
template <typename... Ts> using     eif_signed_t = eif_t<        is_signed_v<Ts...>>;
template <typename... Ts> using   eif_unsigned_t = eif_t<      is_unsigned_v<Ts...>>;
template <typename... Ts> using  eif_sintegral_t = eif_t<  is_signed_v<Ts...> && is_integral_v<Ts...>>;
template <typename... Ts> using  eif_uintegral_t = eif_t<is_unsigned_v<Ts...> && is_integral_v<Ts...>>;

namespace detail {
    template <typename T, int t_n> struct array_t_struct { using type = T[t_n]; };
    template <typename T> struct array_t_struct<T, 0> { using type = T[]; };
}
template <typename T, int t_n = 0> using array_t = typename detail::array_t_struct<T, t_n>::type;

template <int t_s> struct sized;
template <> struct sized<1> { using stype = s08; using utype = u08;                    using stype_fast = s08_fast; using utype_fast = u08_fast; };
template <> struct sized<2> { using stype = s16; using utype = u16;                    using stype_fast = s16_fast; using utype_fast = u16_fast; };
template <> struct sized<4> { using stype = s32; using utype = u32; using ftype = f32; using stype_fast = s32_fast; using utype_fast = u32_fast; };
template <> struct sized<8> { using stype = s64; using utype = u64; using ftype = f64; using stype_fast = s64_fast; using utype_fast = u64_fast; };
template <int t_s> using stype = typename sized<t_s>::stype;
template <int t_s> using utype = typename sized<t_s>::utype;
template <int t_s> using ftype = typename sized<t_s>::ftype;
template <int t_s> using stype_fast = typename sized<t_s>::stype_fast;
template <int t_s> using utype_fast = typename sized<t_s>::utype_fast;

template <typename T> using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

namespace detail {
    template <typename T, typename = eif_arithmetic_t<T>> constexpr T getInfinity() {
        if constexpr (is_floating_point_v<T>) return std::numeric_limits<T>::infinity();
        else return std::numeric_limits<T>::max();
    }
}

// Unique identification of floating point numbers
//  precision | bits | digits
// -----------+------+--------
//       half |   16 |      5
//     single |   32 |      9
//     double |   64 |     17
//   extended |   80 |     21
//       quad |  128 |     36

template <typename T, typename =   eif_floating_t<T>> constexpr T       pi = T(3.14159265358979323846264338327950288L);
template <typename T, typename =   eif_floating_t<T>> constexpr T        e = T(2.71828182845904523536028747135266250L);
template <typename T, typename =   eif_floating_t<T>> constexpr T      phi = T(1.61803398874989484820458683436563812L);
template <typename T, typename =   eif_floating_t<T>> constexpr T    sqrt2 = T(1.41421356237309504880168872420969808L);
template <typename T, typename =   eif_floating_t<T>> constexpr T    sqrt3 = T(1.73205080756887729352744634150587237L);
template <typename T, typename =   eif_floating_t<T>> constexpr T    sqrt5 = T(2.23606797749978969640917366873127624L);
template <typename T, typename = eif_arithmetic_t<T>> constexpr T infinity = detail::getInfinity<T>();
template <typename T, typename =   eif_floating_t<T>> constexpr T      nan = std::numeric_limits<T>::quiet_NaN();

template <typename T, typename = eif_t<is_arithmetic_v<T> || std::is_pointer_v<T>>> Q_CONSTEX T min(T v1, T v2);
template <typename T1, typename T2, typename T3, typename... Ts> Q_CONSTEX decltype(auto) min(T1 && v1, T2 && v2, T3 && v3, Ts &&... vs);

template <typename T, typename = eif_t<is_arithmetic_v<T> || std::is_pointer_v<T>>> Q_CONSTEX T max(T v1, T v2);
template <typename T1, typename T2, typename T3, typename... Ts> Q_CONSTEX decltype(auto) max(T1 && v1, T2 && v2, T3 && v3, Ts &&... vs);

template <typename T, typename = eif_t<is_arithmetic_v<T> || std::is_pointer_v<T>>> T & minify(T & min, T v);
template <typename T, typename T1, typename T2, typename... Ts> T & minify(T & min, T1 && v1, T2 && v2, Ts &&... vs);

template <typename T, typename = eif_t<is_arithmetic_v<T> || std::is_pointer_v<T>>> T & maxify(T & max, T v);
template <typename T, typename T1, typename T2, typename... Ts> T & maxify(T & max, T1 && v1, T2 && v2, Ts &&... vs);

}

#include "Core.tpp"
