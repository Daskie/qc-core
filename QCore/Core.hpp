#pragma once



#include <cstdint>
#include <limits>
#include <tuple>



#define Q_CONSTEX constexpr // workaround for IntelliSense bug
#define Q_CX_ABLE



namespace qc {



namespace types {

using uint = unsigned int;

using  nat =  intptr_t;
using unat = uintptr_t;

constexpr nat operator""_n(unsigned long long int v) { return nat(v); }
constexpr unat operator""_un(unsigned long long int v) { return unat(v); }

constexpr int k_nat_p = sizeof(nat);

using s08 =   int8_t;
using u08 =  uint8_t;
using s16 =  int16_t;
using u16 = uint16_t;
using s32 =  int32_t;
using u32 = uint32_t;
using f32 =    float;
using s64 =  int64_t;
using u64 = uint64_t;
using f64 =   double;

template <bool t_b> using eif_t = std::enable_if_t<t_b, int>;
// alternative (safer) option that doesn't play nice with IntelliSense and
// doesn't work with other variadic templates
// used as: template <typename T, eif_t<T, bool>...>
///namespace detail { enum class enabler {}; }
///template <bool t_b> using eif_t = std::enable_if_t<t_b, detail::enabler>;

template <typename T> using eif_arithmetic_t = eif_t<std::is_arithmetic_v<T>>;
template <typename T> using eif_floating_t   = eif_t<std::is_floating_point_v<T>>;
template <typename T> using eif_integral_t   = eif_t<std::is_integral_v<T>>;
template <typename T> using eif_signed_t     = eif_t<std::is_signed_v<T>>;
template <typename T> using eif_unsigned_t   = eif_t<std::is_unsigned_v<T>>;
template <typename T> using eif_sintegral_t  = eif_t<std::is_signed_v<T> && std::is_integral_v<T>>;
template <typename T> using eif_uintegral_t  = eif_t<std::is_unsigned_v<T> && std::is_integral_v<T>>;

template <typename T, unat t_n = 0> using array_t = std::conditional_t<t_n == 0, T[], T[t_n]>;

template <int t_p> struct precision;
template <> struct precision<1> { using stype = s08; using utype = u08; using ftype = void; };
template <> struct precision<2> { using stype = s16; using utype = u16; using ftype = void; };
template <> struct precision<4> { using stype = s32; using utype = u32; using ftype =  f32; };
template <> struct precision<8> { using stype = s64; using utype = u64; using ftype =  f64; };

template <int t_p> using precision_st = typename precision<t_p>::stype;
template <int t_p> using precision_ut = typename precision<t_p>::utype;
template <int t_p> using precision_ft = typename precision<t_p>::ftype;

template <typename T1, typename T2> using match_sign_t = std::conditional_t<std::is_signed_v<T2>, std::make_signed_t<T1>, std::make_unsigned_t<T1>>;

template <typename T> using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

template <typename T1, typename T2> constexpr bool equivocal_v = std::is_same_v<remove_cvref_t<T1>, remove_cvref_t<T2>>;

}

using namespace types;



namespace detail {

template <typename T>
constexpr T sqrtConstexprHelper(T v, T curr, T prev) {
    if (curr == prev) {
        return curr;
    }

    return sqrtConstexprHelper(v, T(0.5) * (curr + v / curr), curr);
}

template <typename T>
constexpr T sqrtConstexpr(T v) {
    if (v == T(0.0) || v == std::numeric_limits<T>::infinity()) {
        return v;
    }
    if (v < T(0.0)) {
        return std::numeric_limits<T>::quiet_NaN();
    }

    return sqrtConstexprHelper(v, v, T(0.0));
}

}


// unique identification of floating point numbers
//           | bits | digits
// ----------+------+--------
//      half |   16 |      5
//    single |   32 |      9
//    double |   64 |     17
//  extended |   80 |     21
//      quad |  128 |     36

template <typename T, eif_floating_t<T> = 0> constexpr T  pi = T(3.14159265358979323846264338327950288L);
template <typename T, eif_floating_t<T> = 0> constexpr T   e = T(2.71828182845904523536028747135266250L);
template <typename T, eif_floating_t<T> = 0> constexpr T phi = T(1.61803398874989484820458683436563812L);

template <u32 t_v, typename T, eif_floating_t<T> = 0> constexpr T sqrt = detail::sqrtConstexpr(T(t_v));
template <typename T, eif_floating_t<T> = 0> constexpr T infinity = std::numeric_limits<T>::infinity();
template <typename T, eif_floating_t<T> = 0> constexpr T nan = std::numeric_limits<T>::quiet_NaN();



template <typename T>
Q_CONSTEX const T & min(const T & a, const T & b);
template <typename T, typename... Ts>
Q_CONSTEX const T & min(const T & a, const T & b, const Ts &... rest);

template <typename T>
Q_CONSTEX const T & max(const T & a, const T & b);
template <typename T, typename... Ts>
Q_CONSTEX const T & max(const T & a, const T & b, const Ts &... rest);

template <typename T>
Q_CONSTEX std::pair<const T &, const T &> minmax(const T & a, const T & b);
template <typename T>
Q_CONSTEX std::pair<const T &, const T &> minmax(const T & a, const T & b, const T & c);
template <typename T>
Q_CONSTEX std::pair<const T &, const T &> minmax(const T & a, const T & b, const T & c, const T & d);
template <typename T, typename... Ts>
Q_CONSTEX std::pair<const T &, const T &> minmax(const T & a, const T & b, const T & c, const T & d, const Ts &... rest);



}



#include "Core.tpp"