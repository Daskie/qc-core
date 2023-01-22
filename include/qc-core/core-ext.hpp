#pragma once

#include <cmath>

#include <bit>

#include <qc-core/core.hpp>

namespace qc
{
    //
    // ...
    //
    template <Numeric T> constexpr T median(T v1, T v2, T v3) noexcept;

    //
    // ...
    //
    template <Numeric T> constexpr T abs(T v) noexcept;

    //
    // ...
    //
    template <Numeric T> constexpr bool zeroish(T v, T e = std::numeric_limits<T>::epsilon()) noexcept;

    //
    // ...
    //
    template <Numeric T> bool equalish(const T v1, const T v2, T e = std::numeric_limits<T>::epsilon());

    //
    // ...
    //
    template <Numeric T> constexpr int sign(T v) noexcept;

    //
    // Returns `v` stripped of any fractional part.
    // If `T` is a float, only works for values that can fit in an `s32`.
    // If `T` is a double, only works for values that can fit in a `s64`.
    // If `T` is integral, simply returns `v`.
    //
    template <Numeric T> constexpr T trunc(T v) noexcept;

    //
    // Fast round for "normal" values of absolute magnitude smaller than roughly one quadrillion
    // .5 values rounds to even, not up
    //
    template <Numeric R, Numeric T> constexpr R round(T v) noexcept;

    //
    // Fast floor for "normal" values whose truncated form can fit in an intmax_t
    //
    template <Numeric R, Numeric T> constexpr R floor(T v) noexcept;

    //
    // Fast ceil for "normal" values whose truncated form can fit in an intmax_t
    //
    template <Numeric R, Numeric T> constexpr R ceil(T v) noexcept;

    // Simple wrapper around std::pow
    template <Floating T> T pow(T v, T e) noexcept;

    //
    // ...
    // ~2.15x faster than std::pow
    //
    template <Floating T> T pow(T v, int e) noexcept;
    template <Floating T> T pow(T v, uint e) noexcept;

    //
    // ...
    //
    template <UnsignedIntegral T> constexpr T log2Floor(T v) noexcept;

    //
    // ...
    //
    template <UnsignedIntegral T> constexpr T mipmaps(T size) noexcept;

    //
    // ...
    // ~3.3x faster than std::modf
    //
    template <Floating T> constexpr T fract(T v) noexcept;

    //
    // ...
    //
    template <SignedIntegral R, Floating T> constexpr Duo<T, R> fract_i(T v) noexcept;

    //
    // ...
    // ~2.5x faster than std::fmod
    // `d` must be > 0
    //
    template <Numeric T> constexpr T mod(T v, T d) noexcept;

    //
    // ...
    // `d` must be > 0
    //
    template <Numeric T> constexpr Duo<T, T> mod_q(T v, T d) noexcept;

    //
    // ...
    //
    template <Floating T> constexpr T mix(T v1, T v2, T t) noexcept;

    //
    // ...
    //
    template <Floating T> constexpr T unmix(T v1, T v2, T v) noexcept;

    //
    // ...
    //
    template <Floating T> constexpr T smoothstep(T v1, T v2, T t) noexcept;

    //
    // ...
    //
    template <typename T, typename... Args> constexpr T sum(const T & v, const Args & ... args);

    //
    // ...
    //
    template <typename T, typename... Args> constexpr T product(const T & v, const Args & ... args);

    //
    // ...
    //
    template <Floating T, Floating... Args> constexpr T average(T v, Args... args) noexcept;

    //
    // ...
    //
    template <Floating T> constexpr T radians(T degrees) noexcept;

    //
    // ...
    //
    template <Floating T> constexpr T degrees(T radians) noexcept;

    //
    // Converts between normalized types.
    //
    template <Floating         To, Floating         From> constexpr To transnorm(From v) noexcept;
    template <SignedIntegral   To, Floating         From> constexpr To transnorm(From v) noexcept;
    template <UnsignedIntegral To, Floating         From> constexpr To transnorm(From v) noexcept;
    template <Floating         To, SignedIntegral   From> constexpr To transnorm(From v) noexcept;
    template <Floating         To, UnsignedIntegral From> constexpr To transnorm(From v) noexcept;
    template <UnsignedIntegral To, UnsignedIntegral From> constexpr To transnorm(From v) noexcept;

    ///
    /// Branchless binary search
    ///
    /// `GreaterEqual` must provide the following comparison: `*std::declval(It) >= v`
    ///
    /// @return iterator to the first element greater than or equal to `v`
    ///
    template <typename It, typename T, typename GreaterEqual = std::greater_equal<>> It lowerBound(It first, It last, const T & v, GreaterEqual greaterEqual = std::greater_equal<>{}) noexcept;

    ///
    /// Branchless binary search
    ///
    /// `Greater` must provide the following comparison: `*std::declval(It) > v`
    ///
    /// @return iterator to the first element greater than `v`
    ///
    template <typename It, typename T, typename Greater = std::greater<>> It upperBound(It first, It last, const T & v, Greater greater = std::greater<>{}) noexcept;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <Numeric T>
    inline constexpr T median(T v1, T v2, T v3) noexcept
    {
        if (v1 > v2) std::swap(v1, v2);
        if (v2 > v3) std::swap(v2, v3);
        return max(v1, v2);
    }

    template <Numeric T>
    inline constexpr T abs(const T v) noexcept
    {
        if constexpr (UnsignedIntegral<T>)
        {
            return v;
        }
        else
        {
            return v < 0 ? -v : v;
        }
    }

    template <Numeric T>
    inline constexpr bool zeroish(const T v, const T e) noexcept
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
    inline bool equalish(const T v1, const T v2, const T e)
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
    inline constexpr int sign(const T v) noexcept
    {
        if constexpr (UnsignedIntegral<T>)
        {
            return int(v > 0u);
        }
        else
        {
            return int(0 < v) - int(v < 0);
        }
    }

    template <Numeric T>
    inline constexpr T trunc(const T v) noexcept
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
    inline constexpr T fract(const T v) noexcept
    {
        return v - trunc(v);
    }

    template <SignedIntegral R, Floating T>
    inline constexpr Duo<T, R> fract_i(const T v) noexcept
    {
        const intmax_t i{intmax_t(v)};
        return {v - T(i), R(i)};
    }

    template <Numeric T>
    inline constexpr T mod(const T v, const T d) noexcept
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
    inline constexpr Duo<T, T> mod_q(const T v, const T d) noexcept
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

    template <Numeric R, Numeric T>
    inline constexpr R round(const T v) noexcept
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
    inline constexpr R floor(const T v) noexcept
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
    inline constexpr R ceil(const T v) noexcept
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
    inline T pow(const T v, const T e) noexcept
    {
        return std::pow(v, e);
    }

    template <Floating T>
    inline T pow(const T v, const int e) noexcept
    {
        if (e >= 0)
        {
            return pow(v, uint(e));
        }
        else
        {
            return pow(T(1.0) / v, uint(-e));
        }
    }

    template <Floating T>
    inline T pow(T v, uint e) noexcept
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
    inline constexpr T log2Floor(const T v) noexcept
    {
        // Old, non-std way of doing it
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

        return v ? T(std::bit_width(v) - 1u) : T(0u);
    }

    template <UnsignedIntegral T>
    inline constexpr T mipmaps(const T size) noexcept
    {
        return T(std::bit_width(size));
    }

    template <Floating T>
    inline constexpr T mix(const T v1, const T v2, const T t) noexcept
    {
        return std::lerp(v1, v2, t);
    }

    template <Floating T>
    inline constexpr T unmix(const T v1, const T v2, const T v) noexcept
    {
        return (v - v1) / (v2 - v1);
    }

    template <Floating T>
    inline constexpr T smoothstep(const T v1, const T v2, const T t) noexcept
    {
        return mix(v1, v2, t * t * (T(3.0) - T(2.0) * t));
    }

    template <typename T, typename... Args>
    inline constexpr T sum(const T & v, const Args & ... args)
    {
        return T((v + ... + args));
    }

    template <typename T, typename... Args>
    inline constexpr T product(const T & v, const Args & ... args)
    {
        return T((v * ... * args));
    }

    template <Floating T, Floating... Args>
    inline constexpr T average(const T v, const Args... args) noexcept
    {
        return (v + ... + args) * (T(1.0) / T(1 + sizeof...(Args)));
    }

    template <Floating T>
    inline constexpr T radians(const T degrees) noexcept
    {
        return degrees * T(pi<T> / 180.0);
    }

    template <Floating T>
    inline constexpr T degrees(const T radians) noexcept
    {
        return radians * T(180.0 / pi<T>);
    }

    template <Floating To, Floating From>
    inline constexpr To transnorm(const From v) noexcept
    {
        return To(v);
    }

    template <SignedIntegral To, Floating From>
    inline constexpr To transnorm(From v) noexcept
    {
        if (v <= From(-1.0)) return -std::numeric_limits<To>::max();
        if (v >= From(1.0)) return std::numeric_limits<To>::max();
        return To(v * From(std::numeric_limits<To>::max()) + (v >= From(0.0) ? From(0.5) : From(-0.5)));
    }

    template <UnsignedIntegral To, Floating From>
    inline constexpr To transnorm(const From v) noexcept
    {
        if (v <= From(0.0)) return To(0u);
        if (v >= From(1.0)) return std::numeric_limits<To>::max();
        return To(v * From(std::numeric_limits<To>::max()) + From(0.5));
    }

    template <Floating To, SignedIntegral From>
    inline constexpr To transnorm(const From v) noexcept
    {
        return max(To(v) * (To(1.0) / To(std::numeric_limits<From>::max())), To(-1.0));
    }

    template <Floating To, UnsignedIntegral From>
    inline constexpr To transnorm(const From v) noexcept
    {
        return To(v) * (To(1.0) / To(std::numeric_limits<From>::max()));
    }

    template <UnsignedIntegral To, UnsignedIntegral From>
    inline constexpr To transnorm(const From v) noexcept
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
            using NextFrom = typename sized<sizeof(From) * 2>::utype;
            using OpType = typename sized<max(sizeof(NextFrom), sizeof(decltype(v << 1)))>::utype;
            return transnorm<To>(NextFrom(v | (OpType(v) << (8u * sizeof(From)))));
        }
    }

    template <typename It, typename T, typename GreaterEqual>
    inline It lowerBound(It first, const It last, const T & v, GreaterEqual greaterEqual) noexcept
    {
        unat size{unat(last - first)};

        while (size)
        {
            const unat half{size / 2u};
            const It mid{first + nat(half)};
            const It firstAlt{mid + nat(size & 1u)};
            first = greaterEqual(*mid, v) ? first : firstAlt;
            size = half;
        }

        return first;
    }

    template <typename It, typename T, typename Greater>
    inline It upperBound(It first, const It last, const T & v, Greater greater) noexcept
    {
        unat size{unat(last - first)};

        while (size)
        {
            const unat half{size / 2u};
            const It mid{first + nat(half)};
            const It firstAlt{mid + nat(size & 1u)};
            first = greater(*mid, v) ? first : firstAlt;
            size = half;
        }

        return first;
    }
}
