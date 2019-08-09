#pragma once

#include <cstdint>
#include <limits>
#include <utility>

#define Q_CONSTEX constexpr // workaround for IntelliSense bug
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

    using s08f = int_fast8_t;
    using s16f = int_fast16_t;
    using s32f = int_fast32_t;
    using s64f = int_fast64_t;
    using u08f = uint_fast8_t;
    using u16f = uint_fast16_t;
    using u32f = uint_fast32_t;
    using u64f = uint_fast64_t;

    using  nat =  intptr_t;
    using unat = uintptr_t;

    constexpr nat operator""_n(unsigned long long int v) { return nat(v); }
    constexpr unat operator""_un(unsigned long long int v) { return unat(v); }

    using std::pair;
    template <typename T> using duo = pair<T, T>;
    using std::move;

}

using namespace types;

using std::enable_if_t;
using std::is_same_v;
using std::is_arithmetic_v;
using std::is_integral_v;
using std::is_floating_point_v;
using std::is_signed_v;
using std::is_unsigned_v;

template <bool t_b> using eif_t = enable_if_t<t_b>;

template <typename T> using eif_arithmetic_t = eif_t<is_arithmetic_v<T>>;
template <typename T> using eif_floating_t   = eif_t<is_floating_point_v<T>>;
template <typename T> using eif_integral_t   = eif_t<is_integral_v<T>>;
template <typename T> using eif_signed_t     = eif_t<is_signed_v<T>>;
template <typename T> using eif_unsigned_t   = eif_t<is_unsigned_v<T>>;
template <typename T> using eif_sintegral_t  = eif_t<is_signed_v<T> && is_integral_v<T>>;
template <typename T> using eif_uintegral_t  = eif_t<is_unsigned_v<T> && is_integral_v<T>>;

namespace detail {
    template <typename T, int t_n> struct array_t_struct { using type = T[t_n]; };
    template <typename T> struct array_t_struct<T, 0> { using type = T[]; };
}
template <typename T, int t_n = 0> using array_t = typename detail::array_t_struct<T, t_n>::type;

template <int t_s> struct sized;
template <> struct sized<1> { using stype = s08; using utype = u08;                    using sftype = s08f; using uftype = u08f; };
template <> struct sized<2> { using stype = s16; using utype = u16;                    using sftype = s16f; using uftype = u16f; };
template <> struct sized<4> { using stype = s32; using utype = u32; using ftype = f32; using sftype = s32f; using uftype = u32f; };
template <> struct sized<8> { using stype = s64; using utype = u64; using ftype = f64; using sftype = s64f; using uftype = u64f; };
template <int t_s> using stype = typename sized<t_s>::stype;
template <int t_s> using utype = typename sized<t_s>::utype;
template <int t_s> using ftype = typename sized<t_s>::ftype;
template <int t_s> using sftype = typename sized<t_s>::sftype;
template <int t_s> using uftype = typename sized<t_s>::uftype;

template <typename T> using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

// Unique identification of floating point numbers
//  precision | bits | digits
// -----------+------+--------
//       half |   16 |      5
//     single |   32 |      9
//     double |   64 |     17
//   extended |   80 |     21
//       quad |  128 |     36

template <typename T, typename = eif_floating_t<T>> constexpr T    pi = T(3.14159265358979323846264338327950288L);
template <typename T, typename = eif_floating_t<T>> constexpr T     e = T(2.71828182845904523536028747135266250L);
template <typename T, typename = eif_floating_t<T>> constexpr T   phi = T(1.61803398874989484820458683436563812L);
template <typename T, typename = eif_floating_t<T>> constexpr T sqrt2 = T(1.41421356237309504880168872420969808L);
template <typename T, typename = eif_floating_t<T>> constexpr T sqrt3 = T(1.73205080756887729352744634150587237L);
template <typename T, typename = eif_floating_t<T>> constexpr T sqrt5 = T(2.23606797749978969640917366873127624L);
template <typename T, typename = eif_floating_t<T>> constexpr T infinity = std::numeric_limits<T>::infinity();
template <typename T, typename = eif_floating_t<T>> constexpr T nan = std::numeric_limits<T>::quiet_NaN();

template <typename T,                 typename = eif_arithmetic_t<T>> Q_CONSTEX T min(T a, T b);
template <typename T, typename... Ts, typename = eif_arithmetic_t<T>> Q_CONSTEX T min(T a, T b, Ts... rest);

template <typename T,                 typename = eif_arithmetic_t<T>> Q_CONSTEX T max(T a, T b);
template <typename T, typename... Ts, typename = eif_arithmetic_t<T>> Q_CONSTEX T max(T a, T b, Ts... rest);

}

#include "Core.tpp"
