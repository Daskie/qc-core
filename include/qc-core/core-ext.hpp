#pragma once

#include <bit>
#include <cmath>

#include <qc-core/core.hpp>

namespace qc {

    //
    // ...
    //
    template <Numeric T> Q_CX_ABLE std::pair<T, T> minmax(T v);
    template <Numeric T> Q_CX_ABLE std::pair<T, T> minmax(T v1, T v2);
    template <Numeric T, Numeric... Ts> Q_CX_ABLE std::pair<T, T> minmax(T v1, T v2, T v3, Ts... vs);

    //
    // ...
    //
    template <Numeric T> Q_CX_ABLE T median(T v1, T v2, T v3);

    //
    // ...
    //
    template <Numeric T> Q_CX_ABLE T clamp(const T & v, const T & min, const T & max);

    //
    // ...
    //
    template <Numeric T> Q_CX_ABLE T abs(T v);

    //
    // ...
    //
    template <Numeric T> Q_CX_ABLE bool zero(T v, T e = std::numeric_limits<T>::epsilon());

    //
    // ...
    //
    template <typename T> Q_CX_ABLE bool equal(const T & v1, const T & v2);
    template <typename T, typename... Ts> Q_CX_ABLE bool equal(const T & v1, const T & v2, const T & v3, const Ts &... vs);

    //
    // ...
    //
    template <Floating T> Q_CX_ABLE bool equal_e(T v1, T v2, T e = std::numeric_limits<T>::epsilon());

    //
    // ...
    //
    template <Numeric T> Q_CX_ABLE int sign(T v);

    //
    // Returns `v` stripped of any fractional part.
    // If `T` is a float, only works for values that can fit in an `s32`.
    // If `T` is a double, only works for values that can fit in a `s64`.
    // If `T` is integral, simply returns `v`.
    //
    template <Numeric T> Q_CX_ABLE T trunc(T v);

    //
    // ...
    // ~2x faster than std::floor
    // doesn't work with extememly large or extremely small floating point values
    //
    template <Floating T> Q_CX_ABLE stype<sizeof(T)> floor(T v);
    template <Integral T> Q_CX_ABLE T floor(T v);

    //
    // ...
    // ~2x faster than std::ceil
    // doesn't work with extememly large or extremely small floating point values
    //
    template <Floating T> Q_CX_ABLE stype<sizeof(T)> ceil(T v);
    template <Integral T> Q_CX_ABLE T ceil(T v);

    //
    // ...
    // ~12x faster than std::llround
    // Only works for "normal" values of absolute magnitude smaller than roughly one quadrillion for doubles or one million for floats
    // Any exact 0.5 value is not guaranteed to round up - it may go either way
    //
    Q_CX_ABLE s64 round(double v);
    Q_CX_ABLE s32 round(float v);
    template <Integral T> Q_CX_ABLE T round(T v);

    //
    // ...
    // ~2.15x faster than std::pow
    //
    template <Floating T> Q_CX_ABLE T pow(T v, int e);
    template <Floating T> Q_CX_ABLE T pow(T v, uint e);

    //
    // ...
    //
    template <UnsignedIntegral T> Q_CONSTEX int log2Floor(T v);

    //
    // ...
    //
    template <UnsignedIntegral T> Q_CONSTEX int log2Ceil(T v);

    //
    // ...
    //
    Q_CX_ABLE int mipmaps(UnsignedIntegral auto size);

    //
    // ...
    // ~3.3x faster than std::modf
    //
    template <Floating T> Q_CX_ABLE T fract(T v);

    //
    // ...
    //
    template <Floating T> Q_CX_ABLE std::pair<T, stype<sizeof(T)>> fract_i(T v);

    //
    // ...
    // ~2.5x faster than std::fmod
    // `d` must be > 0
    //
    template <Numeric T> Q_CX_ABLE T mod(T v, T d);

    //
    // ...
    // `d` must be > 0
    //
    template <Numeric T> Q_CX_ABLE std::pair<T, T> mod_q(T v, T d);

    //
    // ...
    //
    template <Floating T> Q_CX_ABLE T mix(T v1, T v2, T t);

    //
    // ...
    //
    template <Floating T> Q_CX_ABLE T unmix(T v1, T v2, T v);

    //
    // ...
    //
    template <Floating T> Q_CX_ABLE T smoothstep(T v1, T v2, T t);

    //
    // ...
    //
    template <typename T, typename... Args> Q_CONSTEX T sum(const T & v, const Args &... args);

    //
    // ...
    //
    template <typename T, typename... Args> Q_CONSTEX T product(const T & v, const Args &... args);

    //
    // ...
    //
    template <Floating T, Floating... Args> Q_CX_ABLE T average(T v, Args... args);

    //
    // ...
    //
    template <Floating T> Q_CX_ABLE T radians(T degrees);

    //
    // ...
    //
    template <Floating T> Q_CX_ABLE T degrees(T radians);

    //
    // Converts between normalized types.
    //
    template <Floating To, Floating From> Q_CX_ABLE To transnorm(From v);
    template <SignedIntegral To, Floating From> Q_CX_ABLE To transnorm(From v);
    template <UnsignedIntegral To, Floating From> Q_CX_ABLE To transnorm(From v);
    template <Floating To, SignedIntegral From> Q_CX_ABLE To transnorm(From v);
    template <Floating To, UnsignedIntegral From> Q_CX_ABLE To transnorm(From v);
    template <UnsignedIntegral To, UnsignedIntegral From> Q_CX_ABLE To transnorm(From v);

} // namespace qc

// INLINE IMPLEMENTATION ///////////////////////////////////////////////////////////////////////////////////////////////

namespace qc {

    template <Numeric T>
    inline Q_CX_ABLE std::pair<T, T> minmax(const T v) {
        return {v, v};
    }

    template <Numeric T>
    inline Q_CX_ABLE std::pair<T, T> minmax(const T v1, const T v2) {
        return (v1 < v2) ? std::pair<T, T>{v1, v2} : std::pair<T, T>{v2, v1};
    }

    template <Numeric T, Numeric... Ts>
    inline Q_CX_ABLE std::pair<T, T> minmax(T v1, T v2, T v3, Ts... vs) {
        if constexpr (!sizeof...(Ts)) {
            const auto [m1, M1](minmax(v1, v2));
            return {min(m1, v3), max(M1, v3)};
        }
        else {
            const auto [m1, M1](minmax(v1, v2));
            const auto [m2, M2](minmax(vs...));
            return {min(m1, m2), max(M1, M2)};
        }
    }

    template <Numeric T>
    inline Q_CX_ABLE T median(T a, T b, T c) {
        if (a > b) std::swap(a, b);
        if (b > c) std::swap(b, c);
        return max(a, b);
    }

    template <Numeric T>
    inline Q_CX_ABLE T clamp(const T & v, const T & min, const T & max) {
        return ::qc::min(::qc::max(v, min), max);
    }

    template <Numeric T>
    inline Q_CX_ABLE T abs(const T v) {
        if constexpr (std::is_unsigned_v<T>) {
            return v;
        }
        if constexpr (std::is_signed_v<T>) {
            return v < 0 ? -v : v;
        }
    }

    template <Numeric T>
    inline Q_CX_ABLE bool zero(const T v, const T e) {
        if constexpr (std::is_floating_point_v<T>) {
            return abs(v) < e;
        }
        else {
            return v == T(0);
        }
    }

    template <typename T>
    inline Q_CX_ABLE bool equal(const T & v1, const T & v2) {
        if constexpr (std::is_floating_point_v<T>) {
            return zero(v1 - v2);
        }
        else {
            return v1 == v2;
        }
    }

    template <typename T, typename... Ts>
    inline Q_CX_ABLE bool equal(const T & v1, const T & v2, const T & v3, const Ts &... vs) {
        return equal(v1, v2) && equal(v2, v3, vs...);
    }

    template <Floating T>
    inline Q_CX_ABLE bool equal_e(const T v1, const T v2, const T e) {
        return zero(v1 - v2, e);
    }

    template <Numeric T>
    inline Q_CX_ABLE int sign(const T v) {
        if constexpr (std::is_signed_v<T>) {
            return int(0 < v) - int(v < 0);
        }
        if constexpr (std::is_unsigned_v<T>) {
            return int(v > 0u);
        }
    }

    template <Numeric T>
    inline Q_CX_ABLE T trunc(const T v) {
        if constexpr (std::is_floating_point_v<T>) {
            return T(stype<sizeof(T)>(v));
        }
        else {
            return v;
        }
    }

    template <Floating T>
    inline Q_CX_ABLE stype<sizeof(T)> floor(const T v) {
        stype<sizeof(T)> i{stype<sizeof(T)>(v)};
        return i - (v < T(i));
    }

    template <Integral T>
    inline Q_CX_ABLE T floor(const T v) {
        return v;
    }

    template <Floating T>
    inline Q_CX_ABLE stype<sizeof(T)> ceil(const T v) {
        stype<sizeof(T)> i{stype<sizeof(T)>(v)};
        return i + (v > T(i));
    }

    template <Integral T>
    inline Q_CX_ABLE T ceil(const T v) {
        return v;
    }

    inline Q_CX_ABLE s64 round(double v) {
        // Right bit shift on signed integer must be arithmetic
        static_assert((s64(-1) >> 1) == s64(-1));

        return reinterpret_cast<s64 &>(v += 6755399441055744.0) << 13 >> 13;
    }

    inline Q_CX_ABLE s32 round(float v) {
        // Right bit shift on signed integer must be arithmetic
        static_assert((s32(-1) >> 1) == s32(-1));

        return reinterpret_cast<s32 &>(v += 12582912.0f) << 10 >> 10;
    }

    template <Integral T>
    inline Q_CX_ABLE T round(const T v) {
        return v;
    }

    template <Floating T>
    inline Q_CX_ABLE T pow(const T v, const int e) {
        if (e >= 0) {
            return pow(v, uint(e));
        }
        else {
            return pow(T(1.0) / v, uint(-e));
        }
    }

    template <Floating T>
    inline Q_CX_ABLE T pow(T v, uint e) {
        T r{T(1.0)};

        do {
            if (e & 1u) r *= v; // exponent is odd
            e >>= 1;
            v *= v;
        } while (e);

        return r;
    }

    template <UnsignedIntegral T>
    inline Q_CONSTEX int log2Floor(const T v) {
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
    inline Q_CONSTEX int log2Ceil(const T v) {
        return v == T(0) ? 0 : std::numeric_limits<T>::digits - std::countl_zero(std::make_unsigned_t<decltype(v - 1u)>(v - 1u));
    }

    inline Q_CX_ABLE int mipmaps(const UnsignedIntegral auto size) {
        return log2Floor(size) + 1;
    }

    template <Floating T>
    inline Q_CX_ABLE T fract(const T v) {
        return v - trunc(v);
    }

    template <Floating T>
    inline Q_CX_ABLE std::pair<T, stype<sizeof(T)>> fract_i(const T v) {
        const stype<sizeof(T)> i{stype<sizeof(T)>(v)};
        return { v - T(i), i };
    }

    template <Numeric T>
    inline Q_CX_ABLE T mod(const T v, const T d) {
        if constexpr (std::is_floating_point_v<T>) {
            return fract(v / d) * d;
        }
        if constexpr (std::is_integral_v<T>) {
            return v % d;
        }
    }

    template <Numeric T>
    inline Q_CX_ABLE std::pair<T, T> mod_q(const T v, const T d) {
        if constexpr (std::is_floating_point_v<T>) {
            const T q{v / d};
            return { fract(q) * d, q };
        }
        if constexpr (std::is_integral_v<T>) {
            const auto q{v / d};
            return { v - q * d, q };
        }
    }

    template <Floating T>
    inline Q_CX_ABLE T mix(const T v1, const T v2, const T t) {
        return (T(1.0) - t) * v1 + t * v2;
    }

    template <Floating T>
    inline Q_CX_ABLE T unmix(const T v1, const T v2, const T v) {
        return (v - v1) / (v2 - v1);
    }

    template <Floating T>
    inline Q_CX_ABLE T smoothstep(const T v1, const T v2, const T t) {
        return mix(v1, v2, t * t * (T(3.0) - T(2.0) * t));
    }

    template <typename T, typename... Args>
    inline Q_CONSTEX T sum(const T & v, const Args &... args) {
        if constexpr (sizeof...(Args) == 0) {
            return v;
        }
        else {
            return v + sum(args...);
        }
    }

    template <typename T, typename... Args>
    inline Q_CONSTEX T product(const T & v, const Args &... args) {
        if constexpr (sizeof...(Args) == 0) {
            return v;
        }
        else {
            return v * product(args...);
        }
    }

    template <Floating T, Floating... Args>
    inline Q_CX_ABLE T average(T v, Args... args) {
        return sum(v, args...) / T(sizeof...(Args) + 1);
    }

    template <Floating T>
    inline Q_CX_ABLE T radians(const T degrees) {
        return degrees * (pi<T> / T(180.0));
    }

    template <Floating T>
    inline Q_CX_ABLE T degrees(T radians) {
        return radians * (T(180.0) / pi<T>);
    }

    template <Floating To, Floating From>
    inline Q_CX_ABLE To transnorm(const From v) {
        return To(v);
    }

    template <SignedIntegral To, Floating From>
    inline Q_CX_ABLE To transnorm(const From v) {
        if (v <= From(-1.0)) return std::numeric_limits<To>::min();
        if (v >= From(1.0)) return std::numeric_limits<To>::max();
        return v < From(0.0) ? To(std::round(v * -From(std::numeric_limits<To>::min()))) : To(std::round(v * From(std::numeric_limits<To>::max())));
    }

    template <UnsignedIntegral To, Floating From>
    inline Q_CX_ABLE To transnorm(const From v) {
        if (v <= From(0.0)) return To(0u);
        if (v >= From(1.0)) return std::numeric_limits<To>::max();
        return To(std::round(v * From(std::numeric_limits<To>::max())));
    }

    template <Floating To, SignedIntegral From>
    inline Q_CX_ABLE To transnorm(const From v) {
        return To(v) * (v < 0 ? To(1.0) / -To(std::numeric_limits<From>::min()) : To(1.0) / To(std::numeric_limits<From>::max()));
    }

    template <Floating To, UnsignedIntegral From>
    inline Q_CX_ABLE To transnorm(const From v) {
        return To(v) * (To(1.0) / To(std::numeric_limits<From>::max()));
    }

    template <UnsignedIntegral To, UnsignedIntegral From>
    inline Q_CX_ABLE To transnorm(const From v) {
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
