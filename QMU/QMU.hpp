#pragma once



#include <cstdint>
#include <type_traits>
#include <cmath>
#include <limits>
#include <tuple>



namespace qmu {



using  nat =  intptr_t;
using unat = uintptr_t;

constexpr nat operator""_n(unsigned long long int v) { return static_cast<nat>(v); }
constexpr unat operator""_un(unsigned long long int v) { return static_cast<unat>(v); }

using s08 =   int8_t;
using u08 =  uint8_t;
using s16 =  int16_t;
using u16 = uint16_t;
using s32 =  int32_t;
using u32 = uint32_t;
using s64 =  int64_t;
using u64 = uint64_t;



namespace ntypes {

using qmu::nat;
using qmu::unat;

using qmu::operator""_n;
using qmu::operator""_un;

}

namespace itypes {

using qmu::s08; using qmu::u08;
using qmu::s16; using qmu::u16;
using qmu::s32; using qmu::u32;
using qmu::s64; using qmu::u64;

}

namespace types {

using namespace ntypes;
using namespace itypes;

}



template <nat t_p> struct precision;
template <> struct precision<1> { using stype = s08; using utype = u08; };
template <> struct precision<2> { using stype = s16; using utype = u16; };
template <> struct precision<4> { using stype = s32; using utype = u32; using ftype =  float; };
template <> struct precision<8> { using stype = s64; using utype = u64; using ftype = double; };

template <nat t_p> using precision_st = typename precision<t_p>::stype;
template <nat t_p> using precision_ut = typename precision<t_p>::utype;
template <nat t_p> using precision_ft = typename precision<t_p>::ftype;

constexpr nat k_nat_p = sizeof(nat);

template <typename T1, typename T2>
using match_sign_t = std::conditional_t<std::is_signed_v<T2>, std::make_signed_t<T1>, std::make_unsigned_t<T1>>;

//namespace detail { enum class enabler {}; }

template <bool t_b> using eif_t = std::enable_if_t<t_b, int>;
// would be std::enable_if_t<t_b, detail::enabler>, used as
// template <typename T, eif_t<T, bool>...>
// but IntelliSense doesn't like variadic SFINAE

template <typename T> using eif_floating_t = eif_t<std::is_floating_point_v<T>>;

template <typename T> using eif_integral_t = eif_t<std::is_integral_v<T>>;

template <typename T> using eif_arithmetic_t = eif_t<std::is_arithmetic_v<T>>;



namespace detail {

template <typename T, eif_floating_t<T> = 0>
constexpr T sqrtConstexprHelper(T v, T curr, T prev) {
    if (curr == prev) {
        return curr;
    }

    return sqrtConstexprHelper(v, static_cast<T>(0.5) * (curr + v / curr), curr);
}

template <typename T, eif_floating_t<T> = 0>
constexpr T sqrtConstexpr(T v) {
    if (v == static_cast<T>(0.0) || v == std::numeric_limits<T>::infinity()) {
        return v;
    }
    if (v < static_cast<T>(0.0)) {
        return std::numeric_limits<T>::quiet_NaN();
    }

    return sqrtConstexprHelper(v, v, static_cast<T>(0.0));
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

template <typename T, eif_floating_t<T> = 0> constexpr T  pi = static_cast<T>(3.14159265358979323846264338327950288L);
template <typename T, eif_floating_t<T> = 0> constexpr T   e = static_cast<T>(2.71828182845904523536028747135266250L);
template <typename T, eif_floating_t<T> = 0> constexpr T phi = static_cast<T>(1.61803398874989484820458683436563812L);

template <typename T, nat t_v, eif_floating_t<T> = 0> constexpr T sqrt = detail::sqrtConstexpr(static_cast<T>(t_v));
template <typename T, eif_floating_t<T> = 0> constexpr T infinity = std::numeric_limits<T>::infinity();
template <typename T, eif_floating_t<T> = 0> constexpr T nan = std::numeric_limits<T>::quiet_NaN();



template <typename T>
constexpr const T & min(const T & a, const T & b);

template <typename T, typename... Ts>
constexpr const T & min(const T & a, const T & b, const Ts &... rest);

template <typename T>
constexpr const T & max(const T & a, const T & b);

template <typename T, typename... Ts>
constexpr const T & max(const T & a, const T & b, const Ts &... rest);

template <typename T>
constexpr T clamp(const T & v, const T & min, const T & max);

// similar performance to std but allows constexpr
template <typename T, eif_arithmetic_t<T> = 0>
constexpr T abs(T v);

template <typename T, eif_arithmetic_t<T> = 0>
constexpr bool zero(T v, T e = std::numeric_limits<T>::min());

template <typename T>
constexpr bool equal(const T & v1, const T & v2);

template <typename T, typename... Ts>
constexpr bool equal(const T & v1, const T & v2, const Ts &... rest);

template <typename T, eif_arithmetic_t<T> = 0>
constexpr T sign(T v);

// ~2x faster than std::floor
template <typename T, eif_floating_t<T> = 0>
constexpr nat floor(T v);

template <typename T, eif_integral_t<T> = 0>
constexpr T floor(T v);

// ~2x faster than std::ceil
template <typename T, eif_floating_t<T> = 0>
constexpr nat ceil(T v);

template <typename T, eif_integral_t<T> = 0>
constexpr T ceil(T v);

template <typename T, eif_arithmetic_t<T> = 0>
constexpr T log2(T v);

template <typename T, eif_integral_t<T> = 0>
constexpr bool isPow2(T v);

template <typename T, eif_integral_t<T> = 0>
constexpr T floor2(T v);

template <typename T, eif_integral_t<T> = 0>
constexpr T ceil2(T v);

template <typename T, eif_integral_t<T> = 0>
constexpr T highBit(T v);

template <typename T, eif_integral_t<T> = 0>
constexpr T lowBit(T v);

// ~3.3x faster than std::modf
template <typename T, eif_floating_t<T> = 0>
constexpr T fract(T v);

template <typename T, eif_floating_t<T> = 0>
constexpr std::pair<T, nat> fract_i(T v);

// ~2.5x faster than std::fmod
template <typename T, eif_arithmetic_t<T> = 0>
constexpr T mod(T v, T d);

template <typename T, eif_arithmetic_t<T> = 0>
constexpr std::pair<T, T> mod_q(T v, T d);

template <typename T, eif_floating_t<T> = 0>
constexpr T mix(T v1, T v2, T t);

template <typename T, eif_floating_t<T> = 0>
constexpr T radians(T degrees);

template <typename T, eif_floating_t<T> = 0>
constexpr T degrees(T radians);



//==============================================================================================================================================================
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION ==============================================================================================================================================
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================================================



template <typename T>
constexpr const T & min(const T & a, const T & b) {
    return a < b ? a : b;
}

template <typename T, typename... Ts>
constexpr const T & min(const T & a, const T & b, const Ts &... rest) {
    return min(a < b ? a : b, rest...);
}

template <typename T>
constexpr const T & max(const T & a, const T & b) {
    return a > b ? a : b;
}

template <typename T, typename... Ts>
constexpr const T & max(const T & a, const T & b, const Ts &... rest) {
    return max(a > b ? a : b, rest...);
}

template <typename T>
constexpr T clamp(const T & v, const T & min, const T & max) {
    return qmu::min(qmu::max(v, min), max);
}

template <typename T, eif_arithmetic_t<T>>
constexpr T abs(T v) {
    if constexpr (std::is_unsigned_v<T>) {
        return v;
    }
    else {
        return v < static_cast<T>(0) ? -v : v;
    }
}

// constexpr does not allow reinterpret_cast
/*
template <typename T, eif_floating_t<T> = 0>
constexpr T abs(T v) {
    using itype = precision_ut<sizeof(T)>;
    constexpr itype mask = static_cast<itype>(-1) >> 1;

    reinterpret_cast<itype &>(v) = reinterpret_cast<itype &>(v) & mask;
    return v;
}
*/

template <typename T, eif_arithmetic_t<T>>
constexpr bool zero(T v, T e) {
    if (std::is_floating_point_v<T>) {
        return abs(v) < e;
    }
    else {
        return v == static_cast<T>(0);
    }
}

template <typename T>
constexpr bool equal(const T & v1, const T & v2) {
    if constexpr (std::is_floating_point_v<T>) {
        return zero(v1 - v2);
    }
    else {
        return v1 == v2;
    }
}

template <typename T, typename... Ts>
constexpr bool equal(const T & v1, const T & v2, const Ts &... rest) {
    return equal(v1, v2) && equal(v2, rest...);
}

template <typename T, eif_arithmetic_t<T>>
constexpr T sign(T v) {
    if constexpr (std::is_signed_v<T>) {
        return static_cast<T>(static_cast<T>(0) < v) - static_cast<T>(v < static_cast<T>(0));
    }
    else {
        return static_cast<T>(v > static_cast<T>(0));
    }
}

template <typename T, eif_floating_t<T>>
constexpr nat floor(T v) {
    nat i(static_cast<nat>(v));
    return i - (v < i);
}

template <typename T, eif_integral_t<T>>
constexpr T floor(T v) {
    return v;
}

template <typename T, eif_floating_t<T>>
constexpr nat ceil(T v) {
    nat i(static_cast<nat>(v));
    return i + (v > i);
}

template <typename T, eif_integral_t<T>>
constexpr T ceil(T v) {
    return v;
}

template <typename T, eif_arithmetic_t<T>>
constexpr T log2(T v) {
    if constexpr (std::is_integral_v<T>) {
        static_assert(sizeof(T) <= 8, "log2 function needs updated for larger integer types");
        T log(0);
        if constexpr (sizeof(T) >= 8) {
            if (v & 0xFFFFFFFF00000000ULL) { v >>= 32; log += 32; }
        }
        if constexpr (sizeof(T) >= 4) {
            if (v & 0x00000000FFFF0000ULL) { v >>= 16; log += 16; }
        }
        if constexpr (sizeof(T) >= 2) {
            if (v & 0x000000000000FF00ULL) { v >>=  8; log +=  8; }
        }
        if (    v & 0x00000000000000F0ULL) { v >>=  4; log +=  4; }
        if (    v & 0x000000000000000CULL) { v >>=  2; log +=  2; }
        if (    v & 0x0000000000000002ULL) {           log +=  1; }
        return log;
    }
    else {
        return std::log2(v);
    }
}

template <typename T, eif_integral_t<T>>
constexpr bool isPow2(T v) {
    return (v & (v - 1)) == 0;
}

template <typename T, eif_integral_t<T>>
constexpr T floor2(T v) {
    if (v == 0) return 0;
    return T(1) << log2(v);
}

template <typename T, eif_integral_t<T>>
constexpr T ceil2(T v) {
    if (v == 0) return 0;
    return floor2(v * 2 - 1);
}

template <typename T, eif_integral_t<T>>
constexpr T highBit(T v) {
    using UT = std::make_unsigned_t<T>;
    constexpr UT mask(static_cast<UT>(1) << (sizeof(T) * 8 - 1));

    return static_cast<T>(static_cast<UT>(v) & mask);
}

template <typename T, eif_integral_t<T>>
constexpr T lowBit(T v) {
    return v & static_cast<T>(1);
}

template <typename T, eif_floating_t<T>>
constexpr T fract(T v) {
    return v - static_cast<nat>(v);
}

template <typename T, eif_floating_t<T>>
constexpr std::pair<T, nat> fract_i(T v) {
    nat i(static_cast<nat>(v));
    return { v - i, i };
}

template <typename T, eif_arithmetic_t<T>>
constexpr T mod(T v, T d) {
    if constexpr (std::is_floating_point_v<T>) {
        return fract(v / d) * d;
    }
    else {
        return v % d;
    }
}

template <typename T, eif_arithmetic_t<T>>
constexpr std::pair<T, T> mod_q(T v, T d) {
    if constexpr (std::is_floating_point_v<T>) {
        T q(v / d);
        return { fract(q) * d, q };
    }
    else {
        d = abs(d);
        T q(v / d);
        return { v - q * d, q };
    }
}

template <typename T, eif_floating_t<T>>
constexpr T mix(T v1, T v2, T t) {
    return (static_cast<T>(1.0) - t) * v1 + t * v2;
}

template <typename T, eif_floating_t<T>>
constexpr T radians(T degrees) {
    return degrees * pi<T> / static_cast<T>(180.0);
}

template <typename T, eif_floating_t<T>>
constexpr T degrees(T radians) {
    return radians * static_cast<T>(180.0) / pi<T>;
}



}