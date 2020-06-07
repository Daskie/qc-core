#pragma once

// TODO: remove this define nonsense once Microsoft gets their shit together
#ifdef __cpp_lib_bitops
#include <bit>
#else
#define __cpp_lib_bitops
#include <bit>
#undef __cpp_lib_bitops
#endif

#include "core.hpp"

namespace qc::core {

    //
    // ...
    //
    template <Number T> Q_CX_ABLE std::pair<T, T> minmax(T a);
    template <Number T> Q_CX_ABLE std::pair<T, T> minmax(T a, T b);
    template <Number T, Number... Ts> Q_CX_ABLE std::pair<T, T> minmax(T v1, T v2, Ts... vs);

    //
    // ...
    //
    template <Number T> Q_CX_ABLE T median(T a, T b, T c);

    //
    // ...
    //
    template <Number T> Q_CX_ABLE T clamp(const T & v, const T & min, const T & max);

    //
    // ...
    //
    template <Number T> Q_CX_ABLE T abs(T v);

    //
    // ...
    //
    template <Number T> Q_CX_ABLE bool zero(T v, T e = std::numeric_limits<T>::epsilon());

    //
    // ...
    //
    template <typename T> Q_CX_ABLE bool equal(const T & v1, const T & v2);
    template <typename T, typename... Ts> Q_CX_ABLE bool equal(const T & v1, const T & v2, const T & v3, const Ts &... vs);

    //
    // ...
    //
    template <Floater T> Q_CX_ABLE bool equal_e(T v1, T v2, T e = std::numeric_limits<T>::epsilon());

    //
    // ...
    //
    template <Number T> Q_CX_ABLE int sign(T v);

    //
    // Returns `v` stripped of any fractional part.
    // If `T` is a float, only works for values that can fit in an `s32`.
    // If `T` is a double, only works for values that can fit in a `s64`.
    // If `T` is integral, simply returns `v`.
    //
    template <Number T> Q_CX_ABLE T trunc(T v);

    //
    // ...
    // ~2x faster than std::floor
    // doesn't work with extememly large or extremely small floating point values
    //
    template <Floater T> Q_CX_ABLE stype<sizeof(T)> floor(T v);
    template <Integer T> Q_CX_ABLE T floor(T v);

    //
    // ...
    // ~2x faster than std::ceil
    // doesn't work with extememly large or extremely small floating point values
    //
    template <Floater T> Q_CX_ABLE stype<sizeof(T)> ceil(T v);
    template <Integer T> Q_CX_ABLE T ceil(T v);

    //
    // ...
    // ~12x faster than std::llround
    // Only works for "normal" values of absolute magnitude smaller than roughly one quadrillion for doubles or one million for floats
    // Any exact 0.5 value is not guaranteed to round up - it may go either way
    //
    Q_CX_ABLE s64 round(double v);
    Q_CX_ABLE s32 round(float v);
    template <Integer T> Q_CX_ABLE T round(T v);

    //
    // ...
    // ~2.15x faster than std::pow
    //
    template <Floater T> Q_CX_ABLE T pow(T v, int e);
    template <Floater T> Q_CX_ABLE T pow(T v, uint e);

    //
    // ...
    // Depreciated in favor of `std::ispow2`
    //
    //template <Integer T> Q_CONSTEX bool isPow2(T v);

    //
    // ...
    //
    template <UnsignedInteger T> Q_CONSTEX int log2Floor(T v);

    //
    // ...
    //
    template <UnsignedInteger T> Q_CONSTEX int log2Ceil(T v);

    //
    // ...
    // Depreciated in favor of `std::floor2`
    //
    //template <Integer T> Q_CONSTEX T floor2(T v);

    //
    // ...
    // Depreciated in favor of `std::ceil2`
    //
    //template <Integer T> Q_CONSTEX T ceil2(T v);

    //
    // ...
    //
    template <UnsignedInteger T> Q_CX_ABLE int mipmaps(T size);

    //
    // ...
    //
    //template <Integer T> Q_CONSTEX T smear(T v);

    //
    // ...
    // ~3.3x faster than std::modf
    //
    template <Floater T> Q_CX_ABLE T fract(T v);

    //
    // ...
    //
    template <Floater T> Q_CX_ABLE std::pair<T, stype<sizeof(T)>> fract_i(T v);

    //
    // ...
    // ~2.5x faster than std::fmod
    // `d` must be > 0
    //
    template <Number T> Q_CX_ABLE T mod(T v, T d);

    //
    // ...
    // `d` must be > 0
    //
    template <Number T> Q_CX_ABLE std::pair<T, T> mod_q(T v, T d);

    //
    // ...
    //
    template <Floater T> Q_CX_ABLE T mix(T v1, T v2, T t);

    //
    // ...
    //
    template <Floater T> Q_CX_ABLE T unmix(T v1, T v2, T v);

    //
    // ...
    //
    template <Floater T> Q_CX_ABLE T smoothstep(T v1, T v2, T t);

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
    template <Floater T, Floater... Args> Q_CX_ABLE T average(T v, Args... args);

    //
    // ...
    //
    template <Floater T> Q_CX_ABLE T radians(T degrees);

    //
    // ...
    //
    template <Floater T> Q_CX_ABLE T degrees(T radians);

    //
    // Converts between normalized types.
    // Works with floats and integers, signed and unsigned.
    //
    template <Number To, Number From> Q_CONSTEX To transnorm(From v);

} // namespace qc::core

// INLINE IMPLEMENTATION ///////////////////////////////////////////////////////////////////////////////////////////////

namespace qc::core {

    template <Number T>
    inline Q_CX_ABLE std::pair<T, T> minmax(const T a) {
        return {a, a};
    }

    template <Number T>
    inline Q_CX_ABLE std::pair<T, T> minmax(const T a, const T b) {
        return (a < b) ? std::pair<T, T>{a, b} : std::pair<T, T>{b, a};
    }

    template <Number T, Number... Ts>
    inline Q_CX_ABLE std::pair<T, T> minmax(const T v1, const T v2, const Ts... vs) {
        const auto [m1, M1](minmax(v1, v2));
        const auto [m2, M2](minmax(vs...));
        return {min(m1, m2), max(M1, M2)};
    }

    template <Number T>
    inline Q_CX_ABLE T median(T a, T b, T c) {
        if (a > b) std::swap(a, b);
        if (b > c) std::swap(b, c);
        return max(a, b);
    }

    template <Number T>
    inline Q_CX_ABLE T clamp(const T & v, const T & min, const T & max) {
        return ::qc::core::min(::qc::core::max(v, min), max);
    }

    template <Number T>
    inline Q_CX_ABLE T abs(const T v) {
        if constexpr (std::is_unsigned_v<T>) {
            return v;
        }
        if constexpr (std::is_signed_v<T>) {
            return v < 0 ? -v : v;
        }
    }

    template <Number T>
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

    template <Floater T>
    inline Q_CX_ABLE bool equal_e(const T v1, const T v2, const T e) {
        return zero(v1 - v2, e);
    }

    template <Number T>
    inline Q_CX_ABLE int sign(const T v) {
        if constexpr (std::is_signed_v<T>) {
            return int(0 < v) - int(v < 0);
        }
        if constexpr (std::is_unsigned_v<T>) {
            return int(v > 0u);
        }
    }

    template <Number T>
    inline Q_CX_ABLE T trunc(const T v) {
        if constexpr (std::is_floating_point_v<T>) {
            return T(stype<sizeof(T)>(v));
        }
        else {
            return v;
        }
    }

    template <Floater T>
    inline Q_CX_ABLE stype<sizeof(T)> floor(const T v) {
        stype<sizeof(T)> i{stype<sizeof(T)>(v)};
        return i - (v < T(i));
    }

    template <Integer T>
    inline Q_CX_ABLE T floor(const T v) {
        return v;
    }

    template <Floater T>
    inline Q_CX_ABLE stype<sizeof(T)> ceil(const T v) {
        stype<sizeof(T)> i{stype<sizeof(T)>(v)};
        return i + (v > T(i));
    }

    template <Integer T>
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

    template <Integer T>
    inline Q_CX_ABLE T round(const T v) {
        return v;
    }

    template <Floater T>
    inline Q_CX_ABLE T pow(const T v, const int e) {
        if (e >= 0) {
            return pow(v, uint(e));
        }
        else {
            return pow(T(1.0) / v, uint(-e));
        }
    }

    template <Floater T>
    inline Q_CX_ABLE T pow(T v, uint e) {
        T r(T(1.0));

        do {
            if (e & 1u) r *= v; // exponent is odd
            e >>= 1;
            v *= v;
        } while (e);

        return r;
    }

    // Depreciated in favor of `std::ispow2`
    //template <Integer T>
    //inline Q_CONSTEX bool isPow2(const T v) {
    //    return !(v & (v - T(1)));
    //}

    template <UnsignedInteger T>
    inline Q_CONSTEX int log2Floor(const T v) {
        //static_assert(sizeof(T) <= 8u);
        //
        //int log(0);
        //if constexpr (sizeof(T) >= 8u) if (v & 0xFFFFFFFF00000000) { v >>= 32; log += 32; }
        //if constexpr (sizeof(T) >= 4u) if (v & 0x00000000FFFF0000) { v >>= 16; log += 16; }
        //if constexpr (sizeof(T) >= 2u) if (v & 0x000000000000FF00) { v >>=  8; log +=  8; }
        //                               if (v & 0x00000000000000F0) { v >>=  4; log +=  4; }
        //                               if (v & 0x000000000000000C) { v >>=  2; log +=  2; }
        //                               if (v & 0x0000000000000002) {           log +=  1; }
        //return log;

        return v == T(0) ? 0 : std::numeric_limits<T>::digits - 1 - std::countl_zero(v);
    }

    template <UnsignedInteger T>
    inline Q_CONSTEX int log2Ceil(const T v) {
        return v == T(0) ? 0 : std::numeric_limits<T>::digits - std::countl_zero(std::make_unsigned_t<decltype(v - 1u)>(v - 1u));
    }

    // Depreciated in favor of std::floor2
    //template <Integer T>
    //inline Q_CONSTEX T floor2(T v) {
    //    v = smear(v);
    //    return v ^ (v >> 1);
    //}

    // Depreciated in favor of std::ceil2
    //template <Integer T>
    //inline Q_CONSTEX T ceil2(const T v) {
    //    return smear(v - T(1)) + T(1);
    //}

    template <UnsignedInteger T>
    inline Q_CX_ABLE int mipmaps(const T size) {
        return log2Floor(size) + T(1);
    }

    //template <Integer T>
    //inline Q_CONSTEX T smear(T v) {
    //                                   v |= v >>  1;
    //                                   v |= v >>  2;
    //                                   v |= v >>  4;
    //    if constexpr (sizeof(T) >= 2u) v |= v >>  8;
    //    if constexpr (sizeof(T) >= 4u) v |= v >> 16;
    //    if constexpr (sizeof(T) >= 8u) v |= v >> 32;
    //    return v;
    //}

    template <Floater T>
    inline Q_CX_ABLE T fract(const T v) {
        return v - trunc(v);
    }

    template <Floater T>
    inline Q_CX_ABLE std::pair<T, stype<sizeof(T)>> fract_i(const T v) {
        stype<sizeof(T)> i{stype<sizeof(T)>(v)};
        return { v - T(i), i };
    }

    template <Number T>
    inline Q_CX_ABLE T mod(const T v, const T d) {
        if constexpr (std::is_floating_point_v<T>) {
            return fract(v / d) * d;
        }
        if constexpr (std::is_integral_v<T>) {
            return v % d;
        }
    }

    template <Number T>
    inline Q_CX_ABLE std::pair<T, T> mod_q(const T v, const T d) {
        if constexpr (std::is_floating_point_v<T>) {
            T q(v / d);
            return { fract(q) * d, q };
        }
        if constexpr (std::is_integral_v<T>) {
            T q(v / d);
            return { v - q * d, q };
        }
    }

    template <Floater T>
    inline Q_CX_ABLE T mix(const T v1, const T v2, const T t) {
        return (T(1.0) - t) * v1 + t * v2;
    }

    template <Floater T>
    inline Q_CX_ABLE T unmix(const T v1, const T v2, const T v) {
        return (v - v1) / (v2 - v1);
    }

    template <Floater T>
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

    template <Floater T, Floater... Args>
    inline Q_CX_ABLE T average(const T v, const Args... args) {
        return sum(v, args...) / T(sizeof...(Args) + 1);
    }

    template <Floater T>
    inline Q_CX_ABLE T radians(const T degrees) {
        return degrees * (pi<T> / T(180.0));
    }

    template <Floater T>
    inline Q_CX_ABLE T degrees(T radians) {
        return radians * (T(180.0) / pi<T>);
    }

    template <Number To, Number From>
    inline Q_CONSTEX To transnorm(const From v) {
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
                    return To(v >> ((sizeof(From) - sizeof(To)) * 8u));
                }
                if constexpr (sizeof(From) < sizeof(To)) {
                    if (v == std::numeric_limits<From>::max()) return std::numeric_limits<To>::max();
                    return To(v) << ((sizeof(To) - sizeof(From)) * 8u);
                }
            }
            // signed int -> unsigned int
            if constexpr (std::is_signed_v<From>) {
                if constexpr (sizeof(From) == sizeof(To)) {
                    if (v <= 0) return 0u;
                    if (v == std::numeric_limits<From>::max()) return std::numeric_limits<To>::max();
                    return To(v << 1);
                }
                if constexpr (sizeof(From) > sizeof(To)) {
                    if (v <= 0) return 0u;
                    return To(v >> ((sizeof(From) - sizeof(To)) * 8u - 1u));
                }
                if constexpr (sizeof(From) < sizeof(To)) {
                    if (v <= 0) return 0u;
                    if (v == std::numeric_limits<From>::max()) return std::numeric_limits<To>::max();
                    return To(v) << ((sizeof(To) - sizeof(From)) * 8u + 1u);
                }
            }
            // unsigned int -> signed int
            if constexpr (std::is_unsigned_v<From>) {
                if constexpr (sizeof(From) == sizeof(To)) {
                    return To(v >> 1);
                }
                if constexpr (sizeof(From) > sizeof(To)) {
                    return To(v >> ((sizeof(From) - sizeof(To)) * 8u + 1u));
                }
                if constexpr (sizeof(From) < sizeof(To)) {
                    if (v == std::numeric_limits<From>::max()) return std::numeric_limits<To>::max();
                    return To(v) << ((sizeof(To) - sizeof(From)) * 8u - 1u);
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
                if (v < From(0.0)) return 0u;
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

} // namespace qc::core
