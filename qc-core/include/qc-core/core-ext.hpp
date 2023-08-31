#pragma once

#include <cmath>

#include <bit>
#include <functional>

#include <qc-core/core.hpp>

namespace qc
{
    //
    // ...
    //
    template <Numeric T> nodisc constexpr T median(T v1, T v2, T v3);

    //
    // ...
    //
    template <Numeric T> nodisc constexpr T abs(T v);

    //
    // ...
    //
    template <Numeric T> T & absify(T & v);

    //
    // ...
    //
    template <Numeric T> nodisc constexpr bool zeroish(T v, T e = std::numeric_limits<T>::epsilon());

    //
    // ...
    //
    template <Numeric T> nodisc bool equalish(const T v1, const T v2, T e = std::numeric_limits<T>::epsilon());

    //
    // ...
    //
    template <Numeric T> nodisc constexpr T sign(T v);

    //
    // Returns `v` stripped of any fractional part.
    // If `T` is a float, only works for values that can fit in an `s32`.
    // If `T` is a double, only works for values that can fit in a `s64`.
    // If `T` is integral, simply returns `v`.
    //
    template <Numeric T> nodisc constexpr T trunc(T v);

    //
    // ...
    // ~3.3x faster than std::modf
    //
    template <Floating T> nodisc constexpr T fract(T v);

    //
    // ...
    //
    template <SignedIntegral R, Floating T> nodisc constexpr Duo<T, R> fract_i(T v);

    //
    // ...
    // ~2.5x faster than std::fmod
    // `d` must be > 0
    //
    template <Numeric T> nodisc constexpr T mod(T v, T d);

    //
    // ...
    // `d` must be > 0
    //
    template <Numeric T> nodisc constexpr Duo<T, T> mod_q(T v, T d);

    ///
    /// @return whether the floating value is an integer
    ///
    template <Floating T> nodisc constexpr bool isInteger(T v);

    //
    // Fast round for "normal" values of absolute magnitude smaller than roughly one quadrillion
    // .5 values rounds to even, not up
    //
    template <Numeric R, Numeric T> nodisc constexpr R round(T v);

    //
    // Fast floor for "normal" values whose truncated form can fit in an intmax_t
    //
    template <Numeric R, Numeric T> nodisc constexpr R floor(T v);

    //
    // Fast ceil for "normal" values whose truncated form can fit in an intmax_t
    //
    template <Numeric R, Numeric T> nodisc constexpr R ceil(T v);

    // Simple wrapper around std::pow
    template <Floating T> nodisc T pow(T v, T e);

    //
    // ...
    // ~2.15x faster than std::pow
    //
    template <Floating T> nodisc T pow(T v, s32 e);
    template <Floating T> nodisc T pow(T v, u32 e);

    //
    // ...
    //
    template <UnsignedIntegral T> nodisc constexpr T log2Floor(T v);

    //
    // ...
    //
    template <UnsignedIntegral T> nodisc constexpr T mipmaps(T size);

    //
    // ...
    //
    template <Floating T> nodisc constexpr T mix(T v1, T v2, T t);

    //
    // ...
    //
    template <Floating T> nodisc constexpr T unmix(T v1, T v2, T v);

    //
    // ...
    //
    template <Floating T> nodisc constexpr T smoothstep(T v1, T v2, T t);

    //
    // ...
    //
    template <Floating T> nodisc constexpr T radians(T degrees);

    //
    // ...
    //
    template <Floating T> nodisc constexpr T degrees(T radians);

    //
    // Converts between normalized types.
    //
    template <Floating         To, Floating         From> nodisc constexpr To transnorm(From v);
    template <SignedIntegral   To, Floating         From> nodisc constexpr To transnorm(From v);
    template <UnsignedIntegral To, Floating         From> nodisc constexpr To transnorm(From v);
    template <Floating         To, SignedIntegral   From> nodisc constexpr To transnorm(From v);
    template <Floating         To, UnsignedIntegral From> nodisc constexpr To transnorm(From v);
    template <UnsignedIntegral To, UnsignedIntegral From> nodisc constexpr To transnorm(From v);

    ///
    /// Branchless binary search
    ///
    /// `GreaterEqual` must provide the following comparison: `*std::declval(It) >= v`
    ///
    /// @return iterator to the first element greater than or equal to `v`
    ///
    template <typename It, typename T, typename GreaterEqual = std::greater_equal<>> nodisc It lowerBound(It first, It last, const T & v, GreaterEqual greaterEqual = std::greater_equal<>{});

    ///
    /// Branchless binary search
    ///
    /// `Greater` must provide the following comparison: `*std::declval(It) > v`
    ///
    /// @return iterator to the first element greater than `v`
    ///
    template <typename It, typename T, typename Greater = std::greater<>> nodisc It upperBound(It first, It last, const T & v, Greater greater = std::greater<>{});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <Numeric T>
    finline constexpr T median(T v1, T v2, T v3)
    {
        if (v1 > v2) std::swap(v1, v2);
        if (v2 > v3) std::swap(v2, v3);
        return max(v1, v2);
    }

    template <Numeric T>
    finline constexpr T abs(const T v)
    {
        if constexpr (Signed<T>)
        {
            // std::abs is fast (generates minimal assembly)
            return T(std::abs(v));
        }
        else
        {
            return v;
        }
    }

    template <Numeric T>
    finline T & absify(T & v)
    {
        if constexpr (Signed<T>)
        {
            // std::abs is fast (generates minimal assembly)
            v = T(std::abs(v));
        }

        return v;
    }

    template <Numeric T>
    finline constexpr bool zeroish(const T v, const T e)
    {
        if constexpr (Floating<T>)
        {
            return v < e && v > -e;
        }
        else
        {
            return v == T(0);
        }
    }

    template <Numeric T>
    finline bool equalish(const T v1, const T v2, const T e)
    {
        if constexpr (Floating<T>)
        {
            return zeroish(v1 - v2, e);
        }
        else
        {
            return v1 == v2;
        }
    }

    template <Numeric T>
    finline constexpr T sign(const T v)
    {
        if constexpr (UnsignedIntegral<T>)
        {
            return T(v > 0u);
        }
        else if constexpr (SignedIntegral<T>)
        {
            return T(T(0 < v) - T(v < 0));
        }
        else
        {
            // Correctly propagates NaN
            return v > T(0.0) ? T(1.0) : (v < T(0.0) ? T(-1.0) : v);
        }
    }

    template <Numeric T>
    finline constexpr T trunc(const T v)
    {
        if constexpr (Floating<T>)
        {
            return T(intmax_t(v));
        }
        else
        {
            return v;
        }
    }

    template <Floating T>
    finline constexpr T fract(const T v)
    {
        return v - trunc(v);
    }

    template <SignedIntegral R, Floating T>
    finline constexpr Duo<T, R> fract_i(const T v)
    {
        const intmax_t i{intmax_t(v)};
        return {v - T(i), R(i)};
    }

    template <Numeric T>
    finline constexpr T mod(const T v, const T d)
    {
        if constexpr (Floating<T>)
        {
            return fract(v / d) * d;
        }
        else
        {
            return T(v % d);
        }
    }

    template <Numeric T>
    finline constexpr Duo<T, T> mod_q(const T v, const T d)
    {
        if constexpr (Floating<T>)
        {
            const T q{v / d};
            return {fract(q) * d, q};
        }
        else
        {
            const auto q{v / d};
            return {T(v - q * d), T(q)};
        }
    }

    template <Floating T>
    finline constexpr bool isInteger(const T v)
    {
        return v == trunc(v);
    }

    template <Numeric R, Numeric T>
    finline constexpr R round(const T v)
    {
        // Integral -> Anything
        if constexpr (Integral<T>)
        {
            return R(v);
        }
        else
        {
            // Floating -> Floating
            if constexpr (Floating<R>)
            {
                // Can't find any faster option than this ATM
                return R(std::nearbyint(v));
            }
            // Floating -> Integral
            else
            {
                if constexpr (sizeof(R) >= 8u)
                {
                    // Right bit shift on signed integer must be arithmetic
                    static_assert((-1 >> 1) == -1);

                    return std::bit_cast<s64>(v + 0x1.8p52) << 13 >> 13;
                }
                else
                {
                    return R(std::bit_cast<s64>(v + 0x1.8p52));
                }
            }
        }
    }

    template <Numeric R, Numeric T>
    finline constexpr R floor(const T v)
    {
        // Integral -> Anything
        if constexpr (Integral<T>)
        {
            return R(v);
        }
        else
        {
            // Floating -> Floating
            if constexpr (Floating<R>)
            {
                // Can't find any faster option than this ATM
                return R(std::floor(v));
            }
            // Floating -> Integral
            else
            {
                const intmax_t i{intmax_t(v)};
                return R(i - (v < T(i)));
            }
        }
    }

    template <Numeric R, Numeric T>
    finline constexpr R ceil(const T v)
    {
        // Integral -> Anything
        if constexpr (Integral<T>)
        {
            return R(v);
        }
        else
        {
            // Floating -> Floating
            if constexpr (Floating<R>)
            {
                // Can't find any faster option than this ATM
                return R(std::ceil(v));
            }
            // Floating -> Integral
            else
            {
                const intmax_t i{intmax_t(v)};
                return R(i + (v > T(i)));
            }
        }
    }

    template <Floating T>
    finline T pow(const T v, const T e)
    {
        return std::pow(v, e);
    }

    template <Floating T>
    finline T pow(const T v, const s32 e)
    {
        if (e >= 0)
        {
            return pow(v, u32(e));
        }
        else
        {
            return pow(T(1.0) / v, u32(-e));
        }
    }

    template <Floating T>
    inline T pow(T v, u32 e)
    {
        T r{T(1.0)};

        do
        {
            if (e & 1u) r *= v; // exponent is odd
            e >>= 1;
            v *= v;
        } while (e);

        return r;
    }

    template <UnsignedIntegral T>
    finline constexpr T log2Floor(const T v)
    {
        // Old, non-std way of doing it
        //static_assert(sizeof(T) <= 8u);
        //
        //T log{0u};
        //if constexpr (sizeof(T) >= 8u) if (v & 0xFFFFFFFF00000000) { v >>= 32; log += 32u; }
        //if constexpr (sizeof(T) >= 4u) if (v & 0x00000000FFFF0000) { v >>= 16; log += 16u; }
        //if constexpr (sizeof(T) >= 2u) if (v & 0x000000000000FF00) { v >>=  8; log +=  8u; }
        //                               if (v & 0x00000000000000F0) { v >>=  4; log +=  4u; }
        //                               if (v & 0x000000000000000C) { v >>=  2; log +=  2u; }
        //                               if (v & 0x0000000000000002) {           log +=  1u; }
        //return log;

        return v ? T(std::bit_width(v) - 1) : 0u;
    }

    template <UnsignedIntegral T>
    finline constexpr T mipmaps(const T size)
    {
        return T(std::bit_width(size));
    }

    template <Floating T>
    finline constexpr T mix(const T v1, const T v2, const T t)
    {
        return std::lerp(v1, v2, t);
    }

    template <Floating T>
    finline constexpr T unmix(const T v1, const T v2, const T v)
    {
        return (v - v1) / (v2 - v1);
    }

    template <Floating T>
    finline constexpr T smoothstep(const T v1, const T v2, const T t)
    {
        return mix(v1, v2, t * t * (T(3.0) - T(2.0) * t));
    }

    template <Floating T>
    finline constexpr T radians(const T degrees)
    {
        return degrees * (number::pi<T> / T(180.0));
    }

    template <Floating T>
    finline constexpr T degrees(const T radians)
    {
        return radians * (T(180.0) / number::pi<T>);
    }

    template <Floating To, Floating From>
    finline constexpr To transnorm(const From v)
    {
        return To(v);
    }

    template <SignedIntegral To, Floating From>
    finline constexpr To transnorm(From v)
    {
        if (v <= From(-1.0)) return -std::numeric_limits<To>::max();
        if (v >= From(1.0)) return std::numeric_limits<To>::max();
        return To(v * From(std::numeric_limits<To>::max()) + (v >= From(0.0) ? From(0.5) : From(-0.5)));
    }

    template <UnsignedIntegral To, Floating From>
    finline constexpr To transnorm(const From v)
    {
        if (v <= From(0.0)) return To(0u);
        if (v >= From(1.0)) return std::numeric_limits<To>::max();
        return To(v * From(std::numeric_limits<To>::max()) + From(0.5));
    }

    template <Floating To, SignedIntegral From>
    finline constexpr To transnorm(const From v)
    {
        return max(To(v) * (To(1.0) / To(std::numeric_limits<From>::max())), To(-1.0));
    }

    template <Floating To, UnsignedIntegral From>
    finline constexpr To transnorm(const From v)
    {
        return To(v) * (To(1.0) / To(std::numeric_limits<From>::max()));
    }

    template <UnsignedIntegral To, UnsignedIntegral From>
    finline constexpr To transnorm(const From v)
    {
        if constexpr (sizeof(From) == sizeof(To))
        {
            return v;
        }
        else if constexpr (sizeof(From) > sizeof(To))
        {
            return To(v >> (8u * (sizeof(From) - sizeof(To))));
        }
        else
        {
            using NextFrom = typename Sized<sizeof(From) * 2>::U;
            using OpType = typename Sized<max(sizeof(NextFrom), sizeof(decltype(v << 1)))>::U;
            return transnorm<To>(NextFrom(v | (OpType(v) << (8u * sizeof(From)))));
        }
    }

    template <typename It, typename T, typename GreaterEqual>
    inline It lowerBound(It first, const It last, const T & v, GreaterEqual greaterEqual)
    {
        u64 size{u64(last - first)};

        while (size)
        {
            const u64 half{size / 2u};
            const It mid{first + s64(half)};
            const It firstAlt{mid + s64(size & 1u)};
            first = greaterEqual(*mid, v) ? first : firstAlt;
            size = half;
        }

        return first;
    }

    template <typename It, typename T, typename Greater>
    inline It upperBound(It first, const It last, const T & v, Greater greater)
    {
        u64 size{u64(last - first)};

        while (size)
        {
            const u64 half{size / 2u};
            const It mid{first + s64(half)};
            const It firstAlt{mid + s64(size & 1u)};
            first = greater(*mid, v) ? first : firstAlt;
            size = half;
        }

        return first;
    }
}
