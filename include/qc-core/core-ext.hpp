#pragma once

#include <bit>
#include <cmath>

#include <qc-core/core.hpp>

// TODO: Remove once MSVC has implemented <bit>
#ifdef _MSC_VER
namespace std {

    template <qc::UnsignedIntegral T>
    constexpr T bit_ceil(T v) {
        --v;
                                       v |= v >>  1;
                                       v |= v >>  2;
                                       v |= v >>  4;
        if constexpr (sizeof(T) >= 2u) v |= v >>  8;
        if constexpr (sizeof(T) >= 4u) v |= v >> 16;
        if constexpr (sizeof(T) >= 8u) v |= v >> 32;
        return ++v;
    }

    template <qc::UnsignedIntegral T>
    constexpr int countl_zero(T v) noexcept {
        int n{0};
        if constexpr (sizeof(T) >= 8) if (!(v & 0xFFFFFFFF00000000u)) n += 32; else v >>= 32;
        if constexpr (sizeof(T) >= 4) if (!(v &         0xFFFF0000u)) n += 16; else v >>= 16;
        if constexpr (sizeof(T) >= 2) if (!(v &             0xFF00u)) n +=  8; else v >>=  8;
                                      if (!(v &               0xF0u)) n +=  4; else v >>=  4;
                                      if (!(v &                0xCu)) n +=  2; else v >>=  2;
                                      if (!(v &                0x2u))     ++n; else v >>=  1;
                                      if (!(v &                0x1u))     ++n;
        return n;
    }

    template <qc::UnsignedIntegral T>
    constexpr bool has_single_bit(const T v) noexcept {
        return v != 0u && (v & (v - 1u)) == 0u;
    }

}
#endif

namespace qc {

    //
    // ...
    //
    template <Numeric T> constexpr std::pair<T, T> minmax(T v);
    template <Numeric T> constexpr std::pair<T, T> minmax(T v1, T v2);
    template <Numeric T, Numeric... Ts> constexpr std::pair<T, T> minmax(T v1, T v2, T v3, Ts... vs);

    //
    // ...
    //
    template <Numeric T> constexpr T median(T v1, T v2, T v3);

    //
    // ...
    //
    template <Numeric T> constexpr T clamp(const T & v, const T & min, const T & max);

    //
    // ...
    //
    template <Numeric T> constexpr T abs(T v);

    //
    // ...
    //
    template <Numeric T> bool zero(T v, T e = std::numeric_limits<T>::epsilon());

    //
    // ...
    //
    template <typename T> bool equal(const T & v1, const T & v2);
    template <typename T, typename... Ts> bool equal(const T & v1, const T & v2, const T & v3, const Ts &... vs);

    //
    // ...
    //
    template <Floating T> bool equal_e(T v1, T v2, T e = std::numeric_limits<T>::epsilon());

    //
    // ...
    //
    template <Numeric T> constexpr int sign(T v);

    //
    // Returns `v` stripped of any fractional part.
    // If `T` is a float, only works for values that can fit in an `s32`.
    // If `T` is a double, only works for values that can fit in a `s64`.
    // If `T` is integral, simply returns `v`.
    //
    template <Numeric T> T trunc(T v);

    //
    // ...
    // ~2x faster than std::floor
    // doesn't work with extremely large or extremely small floating point values
    //
    template <Floating T> stype<sizeof(T)> floor(T v);
    template <Integral T> T floor(T v);

    //
    // ...
    // ~2x faster than std::ceil
    // doesn't work with extremely large or extremely small floating point values
    //
    template <Floating T> stype<sizeof(T)> ceil(T v);
    template <Integral T> T ceil(T v);

    //
    // ...
    // ~12x faster than std::llround
    // Only works for "normal" values of absolute magnitude smaller than roughly one quadrillion for doubles or one million for floats
    // Any exact 0.5 value is not guaranteed to round up - it may go either way
    //
    s64 round(double v);
    s32 round(float v);
    template <Integral T> T round(T v);

    //
    // ...
    // ~2.15x faster than std::pow
    //
    template <Floating T> T pow(T v, int e);
    template <Floating T> T pow(T v, uint e);

    //
    // ...
    //
    template <UnsignedIntegral T> constexpr int log2Floor(T v);

    //
    // ...
    //
    template <UnsignedIntegral T> constexpr int log2Ceil(T v);

    //
    // ...
    //
    template <UnsignedIntegral T> constexpr int mipmaps(T size);

    //
    // ...
    // ~3.3x faster than std::modf
    //
    template <Floating T> T fract(T v);

    //
    // ...
    //
    template <Floating T> std::pair<T, stype<sizeof(T)>> fract_i(T v);

    //
    // ...
    // ~2.5x faster than std::fmod
    // `d` must be > 0
    //
    template <Numeric T> constexpr T mod(T v, T d);

    //
    // ...
    // `d` must be > 0
    //
    template <Numeric T> constexpr std::pair<T, T> mod_q(T v, T d);

    //
    // ...
    //
    template <Floating T> T mix(T v1, T v2, T t);

    //
    // ...
    //
    template <Floating T> T unmix(T v1, T v2, T v);

    //
    // ...
    //
    template <Floating T> T smoothstep(T v1, T v2, T t);

    //
    // ...
    //
    template <typename T, typename... Args> constexpr T sum(const T & v, const Args &... args);

    //
    // ...
    //
    template <typename T, typename... Args> constexpr T product(const T & v, const Args &... args);

    //
    // ...
    //
    template <Floating T, Floating... Args> T average(T v, Args... args);

    //
    // ...
    //
    template <Floating T> T radians(T degrees);

    //
    // ...
    //
    template <Floating T> T degrees(T radians);

    //
    // Converts between normalized types.
    //
    template <Floating To, Floating From> To transnorm(From v);
    template <SignedIntegral To, Floating From> To transnorm(From v);
    template <UnsignedIntegral To, Floating From> To transnorm(From v);
    template <Floating To, SignedIntegral From> To transnorm(From v);
    template <Floating To, UnsignedIntegral From> To transnorm(From v);
    template <UnsignedIntegral To, UnsignedIntegral From> To transnorm(From v);

} // namespace qc

// INLINE IMPLEMENTATION ///////////////////////////////////////////////////////////////////////////////////////////////

namespace qc {

    template <Numeric T>
    inline constexpr std::pair<T, T> minmax(const T v) {
        return {v, v};
    }

    template <Numeric T>
    inline constexpr std::pair<T, T> minmax(const T v1, const T v2) {
        return (v1 < v2) ? std::pair<T, T>{v1, v2} : std::pair<T, T>{v2, v1};
    }

    template <Numeric T, Numeric... Ts>
    inline constexpr std::pair<T, T> minmax(T v1, T v2, T v3, Ts... vs) {
        if constexpr (!sizeof...(Ts)) {
            const auto [m1, M1](minmax(v1, v2));
            return {min(m1, v3), max(M1, v3)};
        }
        else {
            const auto [m1, M1](minmax(v1, v2));
            const auto [m2, M2](minmax(v3, vs...));
            return {min(m1, m2), max(M1, M2)};
        }
    }

    template <Numeric T>
    inline constexpr T median(T v1, T v2, T v3) {
        if (v1 > v2) std::swap(v1, v2);
        if (v2 > v3) std::swap(v2, v3);
        return max(v1, v2);
    }

    template <Numeric T>
    inline constexpr T clamp(const T & v, const T & min, const T & max) {
        return ::qc::min(::qc::max(v, min), max);
    }

    template <Numeric T>
    inline constexpr T abs(const T v) {
        if constexpr (UnsignedIntegral<T>) {
            return v;
        }
        else {
            return v < 0 ? -v : v;
        }
    }

    template <Numeric T>
    inline bool zero(const T v, const T e) {
        if constexpr (Floating<T>) {
            return abs(v) < e;
        }
        else {
            return v == T(0);
        }
    }

    template <typename T>
    inline bool equal(const T & v1, const T & v2) {
        if constexpr (Floating<T>) {
            return zero(v1 - v2);
        }
        else {
            return v1 == v2;
        }
    }

    template <typename T, typename... Ts>
    inline bool equal(const T & v1, const T & v2, const T & v3, const Ts &... vs) {
        return equal(v1, v2) && equal(v2, v3, vs...);
    }

    template <Floating T>
    inline bool equal_e(const T v1, const T v2, const T e) {
        return zero(v1 - v2, e);
    }

    template <Numeric T>
    inline constexpr int sign(const T v) {
        if constexpr (UnsignedIntegral<T>) {
            return int(v > 0u);
        }
        else {
            return int(0 < v) - int(v < 0);
        }
    }

    template <Numeric T>
    inline T trunc(const T v) {
        if constexpr (Floating<T>) {
            return T(stype<sizeof(T)>(v));
        }
        else {
            return v;
        }
    }

    template <Floating T>
    inline stype<sizeof(T)> floor(const T v) {
        stype<sizeof(T)> i{stype<sizeof(T)>(v)};
        return i - (v < T(i));
    }

    template <Integral T>
    inline T floor(const T v) {
        return v;
    }

    template <Floating T>
    inline stype<sizeof(T)> ceil(const T v) {
        stype<sizeof(T)> i{stype<sizeof(T)>(v)};
        return i + (v > T(i));
    }

    template <Integral T>
    inline T ceil(const T v) {
        return v;
    }

    inline s64 round(double v) {
        // Right bit shift on signed integer must be arithmetic
        static_assert((s64(-1) >> 1) == s64(-1));

        return reinterpret_cast<s64 &>(v += 6755399441055744.0) << 13 >> 13;
    }

    inline s32 round(float v) {
        // Right bit shift on signed integer must be arithmetic
        static_assert((s32(-1) >> 1) == s32(-1));

        return reinterpret_cast<s32 &>(v += 12582912.0f) << 10 >> 10;
    }

    template <Integral T>
    inline T round(const T v) {
        return v;
    }

    template <Floating T>
    inline T pow(const T v, const int e) {
        if (e >= 0) {
            return pow(v, uint(e));
        }
        else {
            return pow(T(1.0) / v, uint(-e));
        }
    }

    template <Floating T>
    inline T pow(T v, uint e) {
        T r{T(1.0)};

        do {
            if (e & 1u) r *= v; // exponent is odd
            e >>= 1;
            v *= v;
        } while (e);

        return r;
    }

    template <UnsignedIntegral T>
    inline constexpr int log2Floor(const T v) {
        //static_assert(sizeof(T) <= 8u);
        //
        //int log{0};
        //if constexpr (sizeof(T) >= 8u) if (v & 0xFFFFFFFF00000000) { v >>= 32; log += 32; }
        //if constexpr (sizeof(T) >= 4u) if (v & 0x00000000FFFF0000) { v >>= 16; log += 16; }
        //if constexpr (sizeof(T) >= 2u) if (v & 0x000000000000FF00) { v >>=  8; log +=  8; }
        //                               if (v & 0x00000000000000F0) { v >>=  4; log +=  4; }
        //                               if (v & 0x000000000000000C) { v >>=  2; log +=  2; }
        //                               if (v & 0x0000000000000002) {           log +=  1; }
        //return log;

        return v == T(0) ? 0 : std::numeric_limits<T>::digits - 1 - std::countl_zero(v);
    }

    template <UnsignedIntegral T>
    inline constexpr int log2Ceil(const T v) {
        return v == T(0) ? 0 : std::numeric_limits<T>::digits - std::countl_zero(std::make_unsigned_t<decltype(v - 1u)>(v - 1u));
    }

    template <UnsignedIntegral T>
    inline constexpr int mipmaps(const T size) {
        return log2Floor(size) + 1;
    }

    template <Floating T>
    inline T fract(const T v) {
        return v - trunc(v);
    }

    template <Floating T>
    inline std::pair<T, stype<sizeof(T)>> fract_i(const T v) {
        const stype<sizeof(T)> i{stype<sizeof(T)>(v)};
        return { v - T(i), i };
    }

    template <Numeric T>
    inline constexpr T mod(const T v, const T d) {
        if constexpr (Floating<T>) {
            return fract(v / d) * d;
        }
        else {
            return T(v % d);
        }
    }

    template <Numeric T>
    inline constexpr std::pair<T, T> mod_q(const T v, const T d) {
        if constexpr (Floating<T>) {
            const T q{v / d};
            return { fract(q) * d, q };
        }
        else {
            const auto q{v / d};
            return { T(v - q * d), T(q) };
        }
    }

    template <Floating T>
    inline T mix(const T v1, const T v2, const T t) {
        return (T(1.0) - t) * v1 + t * v2;
    }

    template <Floating T>
    inline T unmix(const T v1, const T v2, const T v) {
        return (v - v1) / (v2 - v1);
    }

    template <Floating T>
    inline T smoothstep(const T v1, const T v2, const T t) {
        return mix(v1, v2, t * t * (T(3.0) - T(2.0) * t));
    }

    template <typename T, typename... Args>
    inline constexpr T sum(const T & v, const Args &... args) {
        if constexpr (sizeof...(Args) == 0) {
            return v;
        }
        else {
            return v + sum(args...);
        }
    }

    template <typename T, typename... Args>
    inline constexpr T product(const T & v, const Args &... args) {
        if constexpr (sizeof...(Args) == 0) {
            return v;
        }
        else {
            return v * product(args...);
        }
    }

    template <Floating T, Floating... Args>
    inline T average(T v, Args... args) {
        return sum(v, args...) / T(sizeof...(Args) + 1);
    }

    template <Floating T>
    inline T radians(const T degrees) {
        return degrees * (pi<T> / T(180.0));
    }

    template <Floating T>
    inline T degrees(T radians) {
        return radians * (T(180.0) / pi<T>);
    }

    template <Floating To, Floating From>
    inline To transnorm(const From v) {
        return To(v);
    }

    template <SignedIntegral To, Floating From>
    inline To transnorm(const From v) {
        if (v <= From(-1.0)) return std::numeric_limits<To>::min();
        if (v >= From(1.0)) return std::numeric_limits<To>::max();
        return v < From(0.0) ? To(std::round(v * -From(std::numeric_limits<To>::min()))) : To(std::round(v * From(std::numeric_limits<To>::max())));
    }

    template <UnsignedIntegral To, Floating From>
    inline To transnorm(const From v) {
        if (v <= From(0.0)) return To(0u);
        if (v >= From(1.0)) return std::numeric_limits<To>::max();
        return To(std::round(v * From(std::numeric_limits<To>::max())));
    }

    template <Floating To, SignedIntegral From>
    inline To transnorm(const From v) {
        return To(v) * (v < 0 ? To(1.0) / -To(std::numeric_limits<From>::min()) : To(1.0) / To(std::numeric_limits<From>::max()));
    }

    template <Floating To, UnsignedIntegral From>
    inline To transnorm(const From v) {
        return To(v) * (To(1.0) / To(std::numeric_limits<From>::max()));
    }

    template <UnsignedIntegral To, UnsignedIntegral From>
    inline To transnorm(const From v) {
        if constexpr (sizeof(From) == sizeof(To)) {
            return v;
        }
        else if constexpr (sizeof(From) > sizeof(To)) {
            return To(v >> (8u * (sizeof(From) - sizeof(To))));
        }
        else {
            using NextFrom = typename sized<sizeof(From) * 2>::utype;
            using OpType = typename sized<max(sizeof(NextFrom), sizeof(decltype(v << 1)))>::utype;
            return transnorm<To>(NextFrom(v | (OpType(v) << (8u * sizeof(From)))));
        }
    }

} // namespace qc
