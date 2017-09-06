#pragma once



#include <cstdint>
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
using f32 =    float;
using s64 =  int64_t;
using u64 = uint64_t;
using f64 =   double;



namespace ntypes {

using qmu::nat;
using qmu::unat;

using qmu::operator""_n;
using qmu::operator""_un;

}

namespace size_types {

using qmu::s08; using qmu::u08;
using qmu::s16; using qmu::u16;
using qmu::s32; using qmu::u32; using qmu::f32;
using qmu::s64; using qmu::u64; using qmu::f64;

}

namespace types {

using namespace ntypes;
using namespace size_types;

}



template <typename T, nat t_n = 0> using array_t = std::conditional_t<t_n == 0, T[], T[t_n]>;

template <nat t_p> struct precision;
template <> struct precision<1> { using stype = s08; using utype = u08; };
template <> struct precision<2> { using stype = s16; using utype = u16; };
template <> struct precision<4> { using stype = s32; using utype = u32; using ftype = f32; };
template <> struct precision<8> { using stype = s64; using utype = u64; using ftype = f64; };

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

template <typename T1, typename T2> constexpr bool equivocal_v = std::is_same_v<std::decay_t<T1>, std::decay_t<T2>>;



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
constexpr std::pair<const T &, const T &> minmax(const T & a, const T & b);
template <typename T>
constexpr std::pair<const T &, const T &> minmax(const T & a, const T & b, const T & c);
template <typename T>
constexpr std::pair<const T &, const T &> minmax(const T & a, const T & b, const T & c, const T & d);
template <typename T, typename... Ts>
constexpr std::pair<const T &, const T &> minmax(const T & a, const T & b, const T & c, const T & d, const Ts &... rest);

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

template <typename T = nat>
constexpr T pow2(nat v);

template <typename T, eif_integral_t<T> = 0>
constexpr bool isPow2(T v);

template <typename T, eif_integral_t<T> = 0>
constexpr T log2Floor(T v);

template <typename T, eif_integral_t<T> = 0>
constexpr T log2Ceil(T v);

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



namespace bits {



template <typename T, eif_integral_t<T> = 0>
constexpr T rotateL(T v, nat n);

template <typename T, eif_integral_t<T> = 0>
constexpr T rotateR(T v, nat n);

template <typename SrcT, typename DstT, eif_t<std::is_integral_v<SrcT> && std::is_integral_v<DstT> && (sizeof(DstT) > sizeof(SrcT))> = 0>
constexpr DstT spread(SrcT v);

template <typename T, eif_integral_t<T> = 0>
constexpr T interleave(T v);

template <typename T, eif_integral_t<T> = 0>
constexpr T scramble(T v);



}



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
constexpr std::pair<const T &, const T &> minmax(const T & a) {
    return { a, a };
}

template <typename T>
constexpr std::pair<const T &, const T &> minmax(const T & a, const T & b) {
    if (a < b) {
        return { a, b };
    }
    else {
        return { b, a };
    }
}

template <typename T>
constexpr std::pair<const T &, const T &> minmax(const T & a, const T & b, const T & c) {
    auto mm(minmax(a, b)); // apparently can't use structed bindings in constexpr function
    return { min(mm.first, c), max(mm.second, c) };
}

template <typename T>
constexpr std::pair<const T &, const T &> minmax(const T & a, const T & b, const T & c, const T & d) {
    auto mm1(minmax(a, b));
    auto mm2(minmax(c, d));
    return { min(mm1.first, mm2.first), max(mm1.second, mm2.second) };
}

template <typename T, typename... Ts>
constexpr std::pair<const T &, const T &> minmax(const T & a, const T & b, const T & c, const T & d, const Ts &... rest) {
    auto mm1(minmax(a, b, c, d));
    auto mm2(minmax(rest...));
    return { min(mm1.first, mm2.first), max(mm1.second, mm2.second) };
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
    if constexpr (std::is_signed_v<T>) {
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
    if constexpr (std::is_floating_point_v<T>) {
        return abs(v) < e;
    }
    if constexpr (std::is_integral_v<T>) {
        return v == static_cast<T>(0);
    }
}

template <typename T>
constexpr bool equal(const T & v1, const T & v2) {
    if constexpr (std::is_floating_point_v<T>) {
        return zero(v1 - v2);
    }
    if constexpr (std::is_integral_v<T>) {
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
    if constexpr (std::is_unsigned_v<T>) {
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

template <typename T>
constexpr T pow2(nat v) {
    return T(1) << v;
}

template <typename T, eif_integral_t<T>>
constexpr bool isPow2(T v) {
    return (v & (v - 1)) == 0;
}

template <typename T, eif_integral_t<T>>
constexpr T log2Floor(T v) {
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

template <typename T, eif_integral_t<T>>
constexpr T log2Ceil(T v) {
    return log2Floor(2 * v - 1);
}

template <typename T, eif_integral_t<T>>
constexpr T floor2(T v) {
    return T(1) << log2Floor(v);
}

template <typename T, eif_integral_t<T>>
constexpr T ceil2(T v) {
    return T(1) << log2Ceil(v);
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
    if constexpr (std::is_integral_v<T>) {
        return v % d;
    }
}

template <typename T, eif_arithmetic_t<T>>
constexpr std::pair<T, T> mod_q(T v, T d) {
    if constexpr (std::is_floating_point_v<T>) {
        T q(v / d);
        return { fract(q) * d, q };
    }
    if constexpr (std::is_integral_v<T>) {
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



namespace bits {



template <typename SrcT, typename DstT, eif_t<std::is_integral_v<SrcT> && std::is_integral_v<DstT> && (sizeof(DstT) > sizeof(SrcT))>>
constexpr DstT spread(SrcT v) {
    constexpr nat factor(sizeof(DstT) / sizeof(SrcT) - 1);
    
    DstT w(v);

    if constexpr (sizeof(SrcT) >= 4) {
        w = ((w << (16 * factor)) | w) & DstT(0x0000FFFF0000FFFFULL);
    }
    if constexpr (sizeof(SrcT) >= 2) {
        w = ((w << ( 8 * factor)) | w) & DstT(0x00FF00FF00FF00FFULL);
    }
        w = ((w << ( 4 * factor)) | w) & DstT(0x0F0F0F0F0F0F0F0FULL);
        w = ((w << ( 2 * factor)) | w) & DstT(0x3333333333333333ULL);
        w = ((w << ( 1 * factor)) | w) & DstT(0x5555555555555555ULL);

    return w;
}

template <typename T, eif_integral_t<T>>
constexpr T interleave(T v) {
    if constexpr (sizeof(T) > 1) {
        using H = match_sign_t<precision_ut<sizeof(T) / 2>, T>;

        H h1(static_cast<H>(v >> sizeof(H) * 8)), h2(static_cast<H>(v));

        return (spread<H, T>(h1) << 1) | spread<H, T>(h2);
    }
    if constexpr (sizeof(T) == 1) {
        T h1(v >> 4), h2(v);

        h1 = ((h1 << 2) | h1) & T(0x33);
        h1 = ((h1 << 1) | h1) & T(0x55);
        h2 = ((h2 << 2) | h2) & T(0x33);
        h2 = ((h2 << 1) | h2) & T(0x55);

        return (h1 << 1) | h2;
    }
}

template <typename T, eif_integral_t<T>>
constexpr T rotateL(T v, nat n) {
    if constexpr (std::is_unsigned_v<T>) {
        return (v << n) | (v >> (sizeof(T) * 8 - n));
    }
    if constexpr (std::is_signed_v<T>) {
        return rotateL(std::make_unsigned_t<T>(v), n);
    }
}

template <typename T, eif_integral_t<T>>
constexpr T rotateR(T v, nat n) {
    if constexpr (std::is_unsigned_v<T>) {
        return (v >> n) | (v << (sizeof(T) * 8 - n));
    }
    if constexpr (std::is_signed_v<T>) {
        return rotateR(std::make_unsigned_t<T>(v), n);
    }
}

template <typename T, eif_integral_t<T>>
constexpr T scramble(T v) {
    if constexpr (sizeof(T) == 1) {
        return v;
    }

    if constexpr (sizeof(T) == 2) {
        u64 w(0);

        w |= spread<u08, u64>(u08(v)) << 0; v >>= 8;
        w |= spread<u08, u64>(u08(v)) << 4; v >>= 8;

        return u16(w >> 45) | u16(w >> 30) | u16(w >> 15) | u16(w);
    }

    if constexpr (sizeof(T) == 4) {
        u64 w(0);

        w |= spread<u08, u64>(u08(v)) << 0; v >>= 8;
        w |= spread<u08, u64>(u08(v)) << 2; v >>= 8;
        w |= spread<u08, u64>(u08(v)) << 4; v >>= 8;
        w |= spread<u08, u64>(u08(v)) << 6; v >>= 8;

        return u32(w >> 31) | u32(w);
    }

    if constexpr (sizeof(T) == 8) {
        u64 w(0);

        w |= spread<u08, u64>(u08(v)) << 0; v >>= 8;
        w |= spread<u08, u64>(u08(v)) << 1; v >>= 8;
        w |= spread<u08, u64>(u08(v)) << 2; v >>= 8;
        w |= spread<u08, u64>(u08(v)) << 3; v >>= 8;
        w |= spread<u08, u64>(u08(v)) << 4; v >>= 8;
        w |= spread<u08, u64>(u08(v)) << 5; v >>= 8;
        w |= spread<u08, u64>(u08(v)) << 6; v >>= 8;
        w |= spread<u08, u64>(u08(v)) << 7; v >>= 8;

        return w;
    }
}



}



}