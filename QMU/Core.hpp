#pragma once



#include <cstdint>
#include <limits>
#include <tuple>



namespace qmu {



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



namespace size_types {

using qmu::s08; using qmu::u08;
using qmu::s16; using qmu::u16;
using qmu::s32; using qmu::u32; using qmu::f32;
using qmu::s64; using qmu::u64; using qmu::f64;

}



//namespace detail { enum class enabler {}; }

// would be std::enable_if_t<t_b, detail::enabler>, used as
// template <typename T, eif_t<T, bool>...>
// but IntelliSense doesn't like variadic SFINAE
template <bool t_b> using eif_t = std::enable_if_t<t_b, int>;

template <typename T> using eif_floating_t = eif_t<std::is_floating_point_v<T>>;

template <typename T> using eif_integral_t = eif_t<std::is_integral_v<T>>;

template <typename T> using eif_signed_t = eif_t<std::is_signed_v<T>>;

template <typename T> using eif_unsigned_t = eif_t<std::is_unsigned_v<T>>;

template <typename T> using eif_sintegral_t = eif_t<std::is_signed_v<T> && std::is_integral_v<T>>;

template <typename T> using eif_uintegral_t = eif_t<std::is_unsigned_v<T> && std::is_integral_v<T>>;

template <typename T> using eif_arithmetic_t = eif_t<std::is_arithmetic_v<T>>;



template <typename T, size_t t_n = 0> using array_t = std::conditional_t<t_n == 0, T[], T[t_n]>;

template <int t_p> struct precision;
template <> struct precision<1> { using stype = s08; using utype = u08; using ftype = void; };
template <> struct precision<2> { using stype = s16; using utype = u16; using ftype = void; };
template <> struct precision<4> { using stype = s32; using utype = u32; using ftype =  f32; };
template <> struct precision<8> { using stype = s64; using utype = u64; using ftype =  f64; };

template <int t_p> using precision_st = typename precision<t_p>::stype;
template <int t_p> using precision_ut = typename precision<t_p>::utype;
template <int t_p> using precision_ft = typename precision<t_p>::ftype;

template <typename T1, typename T2> using match_sign_t = std::conditional_t<std::is_signed_v<T2>, std::make_signed_t<T1>, std::make_unsigned_t<T1>>;

template <typename T1, typename T2> constexpr bool equivocal_v = std::is_same_v<std::decay_t<T1>, std::decay_t<T2>>;



namespace types {

using namespace size_types;

}



namespace detail {

constexpr f64 sqrtConstexprHelper(f64 v, f64 curr, f64 prev) {
    if (curr == prev) {
        return curr;
    }

    return sqrtConstexprHelper(v, 0.5 * (curr + v / curr), curr);
}

constexpr f64 sqrtConstexpr(f64 v) {
    if (v == 0.0 || v == std::numeric_limits<f64>::infinity()) {
        return v;
    }
    if (v < 0.0) {
        return std::numeric_limits<f64>::quiet_NaN();
    }

    return sqrtConstexprHelper(v, v, 0.0);
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

template <u32 t_v> constexpr f64 sqrt = detail::sqrtConstexpr(f64(t_v));
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

// allows unsigned
template <typename T, eif_arithmetic_t<T> = 0>
T abs(T v);

template <typename T, eif_arithmetic_t<T> = 0>
bool zero(T v, T e = std::numeric_limits<T>::min());

template <typename T>
bool equal(const T & v1, const T & v2);

template <typename T, typename... Ts>
bool equal(const T & v1, const T & v2, const Ts &... rest);

template <typename T, eif_arithmetic_t<T> = 0>
T sign(T v);

// ~2x faster than std::floor
// doesn't work with some edge cases
template <typename T, eif_floating_t<T> = 0>
precision_st<sizeof(T)> floor(T v);

template <typename T, eif_integral_t<T> = 0>
T floor(T v);

// ~2x faster than std::ceil
// doesn't work with some edge cases
template <typename T, eif_floating_t<T> = 0>
precision_st<sizeof(T)> ceil(T v);

template <typename T, eif_integral_t<T> = 0>
T ceil(T v);

template <typename T>
constexpr T pow2(int v);

template <typename T, eif_integral_t<T> = 0>
constexpr bool isPow2(T v);

template <typename T, eif_integral_t<T> = 0>
T log2Floor(T v);

template <typename T, eif_integral_t<T> = 0>
T log2Ceil(T v);

template <typename T, eif_integral_t<T> = 0>
T floor2(T v);

template <typename T, eif_integral_t<T> = 0>
T ceil2(T v);

template <typename T, eif_integral_t<T> = 0>
T highBit(T v);

template <typename T, eif_integral_t<T> = 0>
T lowBit(T v);

template <typename T, eif_integral_t<T> = 0>
T iBit(T v, int i);

// ~3.3x faster than std::modf
template <typename T, eif_floating_t<T> = 0>
T fract(T v);

template <typename T, eif_floating_t<T> = 0>
std::pair<T, precision_st<sizeof(T)>> fract_i(T v);

// ~2.5x faster than std::fmod
template <typename T, eif_arithmetic_t<T> = 0>
T mod(T v, T d);

template <typename T, eif_arithmetic_t<T> = 0>
std::pair<T, T> mod_q(T v, T d);

template <typename T, eif_floating_t<T> = 0>
T mix(T v1, T v2, T t);

template <typename T, typename... Args>
constexpr T sum(const T & v, const Args &... args);

template <typename T, typename... Args>
constexpr T product(const T & v, const Args &... args);

template <typename T, eif_floating_t<T> = 0, typename... Args>
constexpr T average(T v, Args... args);

template <typename T, eif_floating_t<T> = 0>
T radians(T degrees);

template <typename T, eif_floating_t<T> = 0>
T degrees(T radians);

// converts between normalized types
// works with floats and integers, signed and unsigned
template <typename To, typename From, eif_t<std::is_arithmetic_v<To> && std::is_arithmetic_v<From>> = 0>
inline To transnorm(From v);



namespace bits {



template <typename T, eif_uintegral_t<T> = 0>
inline T rotateL(T v, int n);

template <typename T, eif_uintegral_t<T> = 0>
inline T rotateR(T v, int n);

template <typename SrcT, typename DstT, eif_t<std::is_integral_v<SrcT> && std::is_integral_v<DstT> && std::is_unsigned_v<SrcT> && std::is_unsigned_v<DstT> && (sizeof(DstT) > sizeof(SrcT))> = 0>
inline DstT spread(SrcT v);

template <typename SrcT, typename DstT, eif_t<std::is_integral_v<SrcT> && std::is_integral_v<DstT> && std::is_unsigned_v<SrcT> && std::is_unsigned_v<DstT> && (sizeof(DstT) >= sizeof(SrcT))> = 0>
inline DstT repeat(SrcT v);

template <typename T, eif_uintegral_t<T> = 0>
inline T interleave(T v);

template <typename T, eif_uintegral_t<T> = 0>
inline T scramble(T v);



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
inline T abs(T v) {
    if constexpr (std::is_unsigned_v<T>) {
        return v;
    }
    if constexpr (std::is_signed_v<T>) {
        return std::abs(v);
        /// constexpr version
        ///return v < T(0) ? -v : v;
    }
}

template <typename T, eif_arithmetic_t<T>>
inline bool zero(T v, T e) {
    if constexpr (std::is_floating_point_v<T>) {
        return abs(v) < e;
    }
    if constexpr (std::is_integral_v<T>) {
        return v == T(0);
    }
}

template <typename T>
inline bool equal(const T & v1, const T & v2) {
    if constexpr (std::is_floating_point_v<T>) {
        return zero(v1 - v2);
    }
    if constexpr (!std::is_floating_point_v<T>) {
        return v1 == v2;
    }
}

template <typename T, typename... Ts>
inline bool equal(const T & v1, const T & v2, const Ts &... rest) {
    return equal(v1, v2) && equal(v2, rest...);
}

template <typename T, eif_arithmetic_t<T>>
inline T sign(T v) {
    if constexpr (std::is_signed_v<T>) {
        return static_cast<T>(T(0) < v) - static_cast<T>(v < T(0));
    }
    if constexpr (std::is_unsigned_v<T>) {
        return static_cast<T>(v > T(0));
    }
}

template <typename T, eif_floating_t<T>>
inline precision_st<sizeof(T)> floor(T v) {
    precision_st<sizeof(T)> i = precision_st<sizeof(T)>(v);
    return i - (v < i);
}

template <typename T, eif_integral_t<T>>
inline T floor(T v) {
    return v;
}

template <typename T, eif_floating_t<T>>
inline precision_st<sizeof(T)> ceil(T v) {
    precision_st<sizeof(T)> i = precision_st<sizeof(T)>(v);
    return i + (v > i);
}

template <typename T, eif_integral_t<T>>
inline T ceil(T v) {
    return v;
}

template <typename T>
constexpr T pow2(int v) {
    return T(1) << v;
}

template <typename T, eif_integral_t<T>>
constexpr bool isPow2(T v) {
    return (v & (v - 1)) == 0;
}

template <typename T, eif_integral_t<T>>
inline T log2Floor(T v) {
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
inline T log2Ceil(T v) {
    return log2Floor(2 * v - 1);
}

template <typename T, eif_integral_t<T>>
inline T floor2(T v) {
    return T(1) << log2Floor(v);
}

template <typename T, eif_integral_t<T>>
inline T ceil2(T v) {
    return T(1) << log2Ceil(v);
}

template <typename T, eif_integral_t<T>>
inline T highBit(T v) {
    using UT = std::make_unsigned_t<T>;
    constexpr UT mask(UT(1) << (sizeof(T) * 8 - 1));

    return T(v & mask);
}

template <typename T, eif_integral_t<T>>
inline T lowBit(T v) {
    return v & T(1);
}

template <typename T, eif_integral_t<T>>
inline T iBit(T v, int i) {
    using UT = std::make_unsigned_t<T>;
    constexpr UT mask(UT(1) << i);

    return T(v & mask);
}

template <typename T, eif_floating_t<T>>
inline T fract(T v) {
    return v - precision_st<sizeof(T)>(v);
}

template <typename T, eif_floating_t<T>>
inline std::pair<T, precision_st<sizeof(T)>> fract_i(T v) {
    precision_st<sizeof(T)> i = precision_st<sizeof(T)>(v);
    return { v - i, i };
}

template <typename T, eif_arithmetic_t<T>>
inline T mod(T v, T d) {
    if constexpr (std::is_floating_point_v<T>) {
        return fract(v / d) * d;
    }
    if constexpr (std::is_integral_v<T>) {
        return v % d;
    }
}

template <typename T, eif_arithmetic_t<T>>
inline std::pair<T, T> mod_q(T v, T d) {
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
inline T mix(T v1, T v2, T t) {
    return (T(1.0) - t) * v1 + t * v2;
}

template <typename T, typename... Args>
constexpr T sum(const T & v, const Args &... args) {
    if constexpr (sizeof...(Args) == 0) {
        return v;
    }
    if constexpr (sizeof...(Args) > 0) {
        return v + sum(args...);
    }
}

template <typename T, typename... Args>
constexpr T product(const T & v, const Args &... args) {
    if constexpr (sizeof...(Args) == 0) {
        return v;
    }
    if constexpr (sizeof...(Args) > 0) {
        return v * product(args...);
    }
}

template <typename T, eif_floating_t<T>, typename... Args>
constexpr T average(T v, Args... args) {
    return sum(v, args...) / (T(1) + sizeof...(Args));
}

template <typename T, eif_floating_t<T>>
inline T radians(T degrees) {
    return degrees * pi<T> / T(180.0);
}

template <typename T, eif_floating_t<T>>
inline T degrees(T radians) {
    return radians * T(180.0) / pi<T>;
}

template <typename To, typename From, eif_t<std::is_arithmetic_v<To> && std::is_arithmetic_v<From>>>
inline To transnorm(From v) {
    if constexpr (std::is_same_v<From, To>) {
        return v;
    }
    // float -> float
    if constexpr (std::is_floating_point_v<To> && std::is_floating_point_v<From>) {
        return To(v);
    }
    if constexpr (std::is_integral_v<From> && std::is_integral_v<To>) {
        // signed int -> signed int / unsigned int -> unsigned int
        if constexpr (std::is_signed_v<From> == std::is_signed_v<To>) {
            if constexpr (sizeof(From) > sizeof(To)) {
                return To(v >> ((sizeof(From) - sizeof(To)) * 8));
            }
            if constexpr (sizeof(From) < sizeof(To)) {
                if (v == std::numeric_limits<From>::max()) return std::numeric_limits<To>::max();
                return To(v) << ((sizeof(To) - sizeof(From)) * 8);
            }
        }
        // signed int -> unsigned int
        if constexpr (std::is_signed_v<From>) {
            if constexpr (sizeof(From) == sizeof(To)) {
                if (v <= From(0)) return To(0);
                if (v == std::numeric_limits<From>::max()) return std::numeric_limits<To>::max();
                return To(v << 1);
            }
            if constexpr (sizeof(From) > sizeof(To)) {
                if (v <= From(0)) return To(0);
                return To(v >> ((sizeof(From) - sizeof(To)) * 8 - 1));
            }
            if constexpr (sizeof(From) < sizeof(To)) {
                if (v <= From(0)) return To(0);
                if (v == std::numeric_limits<From>::max()) return std::numeric_limits<To>::max();
                return To(v) << ((sizeof(To) - sizeof(From)) * 8 + 1);
            }
        }
        // unsigned int -> signed int
        if constexpr (std::is_unsigned_v<From>) {
            if constexpr (sizeof(From) == sizeof(To)) {
                return To(v >> 1);
            }
            if constexpr (sizeof(From) > sizeof(To)) {
                return To(v >> ((sizeof(From) - sizeof(To)) * 8 + 1));
            }
            if constexpr (sizeof(From) < sizeof(To)) {
                if (v == std::numeric_limits<From>::max()) return std::numeric_limits<To>::max();
                return To(v) << ((sizeof(To) - sizeof(From)) * 8 - 1);
            }
        }
    }
    if constexpr (std::is_floating_point_v<From> && std::is_integral_v<To>) {
        // float -> signed int
        if constexpr (std::is_signed_v<To>) {
            constexpr From maxVal(From(std::numeric_limits<To>::max()) + From(1.0));
            constexpr From upperThreshold(From(1.0) - From(1.0) / maxVal);
            if (v >=  upperThreshold) return std::numeric_limits<To>::max();
            if (v <= -upperThreshold) return std::numeric_limits<To>::min();
            return To(v * maxVal);
        }
        // float -> unsigned int
        if constexpr (std::is_unsigned_v<To>) {
            constexpr From maxVal(From(std::numeric_limits<To>::max()) + From(1.0));
            constexpr From upperThreshold(From(1.0) - From(1.0) / maxVal);
            if (v < From(0.0)) return To(0);
            if (v >= upperThreshold) return std::numeric_limits<To>::max();
            return To(v * maxVal);
        }
    }
    if constexpr (std::is_integral_v<From> && std::is_floating_point_v<To>) {
        // signed int -> float
        if constexpr (std::is_signed_v<From>) {
            constexpr To maxVal(To(std::numeric_limits<From>::max()) + To(1.0));
            if (v == std::numeric_limits<From>::max()) return To(1.0);
            return To(v) * (To(1.0) / maxVal);
        }
        // unsigned int -> float
        if constexpr (std::is_unsigned_v<From>) {
            constexpr To maxVal(To(std::numeric_limits<From>::max()) + To(1.0));
            if (v == std::numeric_limits<From>::max()) return To(1.0);
            return To(v) * (To(1.0) / maxVal);
        }
    }
}



namespace bits {



template <typename SrcT, typename DstT, eif_t<std::is_integral_v<SrcT> && std::is_integral_v<DstT> && std::is_unsigned_v<SrcT> && std::is_unsigned_v<DstT> && (sizeof(DstT) > sizeof(SrcT))>>
inline DstT spread(SrcT v) {
    constexpr int factor(sizeof(DstT) / sizeof(SrcT) - 1);
    
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

template <typename SrcT, typename DstT, eif_t<std::is_integral_v<SrcT> && std::is_integral_v<DstT> && std::is_unsigned_v<SrcT> && std::is_unsigned_v<DstT> && (sizeof(DstT) >= sizeof(SrcT))>>
inline DstT repeat(SrcT v) {
    constexpr int factor(sizeof(DstT) / sizeof(SrcT));

    DstT w(v);

    if constexpr (factor >= 2) {
        w |= w << (sizeof(SrcT) * 1 * 8);
    }
    if constexpr (factor >= 4) {
        w |= w << (sizeof(SrcT) * 2 * 8);
    }
    if constexpr (factor >= 8) {
        w |= w << (sizeof(SrcT) * 4 * 8);
    }

    return w;
}

template <typename T, eif_uintegral_t<T>>
inline T interleave(T v) {
    if constexpr (sizeof(T) > 1) {
        using H = match_sign_t<precision_ut<sizeof(T) / 2>, T>;

        H h1 = H(v >> sizeof(H) * 8), h2 = H(v);

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

template <typename T, eif_uintegral_t<T>>
inline T rotateL(T v, int n) {
    if constexpr (std::is_unsigned_v<T>) {
        return (v << n) | (v >> (sizeof(T) * 8 - n));
    }
    if constexpr (std::is_signed_v<T>) {
        return rotateL(std::make_unsigned_t<T>(v), n);
    }
}

template <typename T, eif_uintegral_t<T>>
inline T rotateR(T v, int n) {
    if constexpr (std::is_unsigned_v<T>) {
        return (v >> n) | (v << (sizeof(T) * 8 - n));
    }
    if constexpr (std::is_signed_v<T>) {
        return rotateR(std::make_unsigned_t<T>(v), n);
    }
}

template <typename T, eif_uintegral_t<T>>
inline T scramble(T v) {
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