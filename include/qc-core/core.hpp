#pragma once

#include <cstdint>

#include <limits>
#include <utility>

namespace qc
{
#ifdef NDEBUG
    constexpr bool debug{false};
#else
    constexpr bool debug{true};
#endif

    static_assert(sizeof(uintptr_t) <= 8u);
    static_assert(std::is_same_v<uintptr_t, size_t>);

    inline namespace types
    {
        using nat = intptr_t;
        using unat = uintptr_t;

        using schar = signed char;
        using uchar = unsigned char;
        using ushort = unsigned short;
        using uint = unsigned int;
        using ulong = unsigned long;
        using llong = long long;
        using ullong = unsigned long long;
        using ldouble = long double;

        using s8 = int8_t;
        using u8 = uint8_t;
        using s16 = int16_t;
        using u16 = uint16_t;
        using s32 = int32_t;
        using u32 = uint32_t;
        using f32 = float;
        using s64 = int64_t;
        using u64 = uint64_t;
        using f64 = double;

        template <typename T> concept Integral = std::is_integral_v<T> && !std::is_same_v<T, bool> && !std::is_same_v<T, char>;
        template <typename T> concept SignedIntegral = Integral<T> && std::is_signed_v<T>;
        template <typename T> concept UnsignedIntegral = Integral<T> && std::is_unsigned_v<T>;
        template <typename T> concept Floating = std::is_floating_point_v<T>;
        template <typename T> concept Numeric = Integral<T> || Floating<T>;
        template <typename T> concept SignedNumeric = SignedIntegral<T> || Floating<T>;
        template <typename T> concept NumericOrBoolean = Numeric<T> || std::is_same_v<T, bool>;
        template <typename T> concept Enum = std::is_enum_v<T>;
        template <typename T> concept Pointer = std::is_pointer_v<T>;
        template <typename T> concept NumericOrPointer = Numeric<T> || Pointer<T>;
        template <typename T> concept IntegralOrPointer = Integral<T> || Pointer<T>;
        template <typename T1, typename T2> concept SameNumericType = SignedIntegral<T1> == SignedIntegral<T2> && UnsignedIntegral<T1> == UnsignedIntegral<T2> && Floating<T1> == Floating<T2>;
    }

    template <int size> struct sized;
    template <> struct sized<1> { using stype =  s8; using utype =  u8; };
    template <> struct sized<2> { using stype = s16; using utype = u16; };
    template <> struct sized<4> { using stype = s32; using utype = u32; using ftype = f32; };
    template <> struct sized<8> { using stype = s64; using utype = u64; using ftype = f64; };
    template <typename T> using stype = typename sized<sizeof(T)>::stype;
    template <typename T> using utype = typename sized<sizeof(T)>::utype;
    template <typename T> using ftype = typename sized<sizeof(T)>::ftype;

    inline namespace numbers
    {
        template <Floating T> inline constexpr T infinity{std::numeric_limits<T>::infinity()};
        template <Floating T> inline constexpr T nan{std::numeric_limits<T>::quiet_NaN()};
        template <Floating T> inline constexpr T pi{T(3.141592653589793)};
        template <Floating T> inline constexpr T e{T(2.718281828459045)};
        template <Floating T> inline constexpr T phi{T(1.618033988749895)};
        template <Floating T> inline constexpr T sqrt2{T(1.414213562373095)};
        template <Floating T> inline constexpr T sqrt3{T(1.732050807568877)};
        template <Floating T> inline constexpr T sqrt5{T(2.236067977499790)};
    }

    template <typename T, typename... Ts> concept OneOf = (std::same_as<T, Ts> || ...);

    template <Enum E> constexpr std::underlying_type_t<E> underlyingVal(const E e);

    ///
    /// Simple guard lock
    ///
    /// Calls the given prodecure (function pointer, lambda, std::function, etc.) when it goes out of scope
    ///
    template <typename Proc>
    struct ScopeGuard
    {
        Proc proc;
        ScopeGuard(Proc && proc) : proc{std::move(proc)} {};
        ~ScopeGuard() noexcept { proc(); }
    };

    //
    // ...
    //
    template <NumericOrPointer T1, NumericOrPointer T2> requires SameNumericType<T1, T2> constexpr auto min(T1 v1, T2 v2);
    template <typename T1, typename T2, typename T3, typename... Ts> constexpr decltype(auto) min(T1 && v1, T2 && v2, T3 && v3, Ts && ... vs);

    //
    // ...
    //
    template <NumericOrPointer T1, NumericOrPointer T2> requires SameNumericType<T1, T2> constexpr auto max(T1 v1, T2 v2);
    template <typename T1, typename T2, typename T3, typename... Ts> constexpr decltype(auto) max(T1 && v1, T2 && v2, T3 && v3, Ts && ... vs);

    //
    // ...
    //
    template <NumericOrPointer T1, NumericOrPointer T2> requires (SameNumericType<T1, T2> && sizeof(T1) >= sizeof(T2)) T1 & minify(T1 & v1, T2 v2);
    template <typename T, typename T1, typename T2, typename... Ts> T & minify(T & min, T1 && v1, T2 && v2, Ts && ... vs);

    //
    // ...
    //
    template <NumericOrPointer T1, NumericOrPointer T2> requires (SameNumericType<T1, T2> && sizeof(T1) >= sizeof(T2)) T1 & maxify(T1 & v1, T2 v2);
    template <typename T, typename T1, typename T2, typename... Ts> T & maxify(T & min, T1 && v1, T2 && v2, Ts && ... vs);

    //
    // ...
    //
    template <NumericOrPointer T1, NumericOrPointer T2> requires SameNumericType<T1, T2> constexpr auto minmax(T1 v1, T2 v2);
    template <typename T1, typename T2, typename T3, typename... Ts> constexpr auto minmax(T1 && v1, T2 && v2, T3 && v3, Ts && ... vs);

    //
    // ...
    //
    template <Numeric T> constexpr T clamp(T v, T min, T max);

    //
    // ...
    //
    template <Numeric T> T & clampify(T & v, T min, T max);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <Enum E>
    inline constexpr std::underlying_type_t<E> underlyingVal(const E e)
    {
        return std::underlying_type_t<E>(e);
    }

    template <NumericOrPointer T1, NumericOrPointer T2>
    requires SameNumericType<T1, T2>
    inline constexpr auto min(const T1 v1, const T2 v2)
    {
        using U = std::conditional_t<sizeof(T1) >= sizeof(T2), T1, T2>;

        return v2 < v1 ? U(v2) : U(v1);
    }

    template <typename T1, typename T2, typename T3, typename... Ts>
    inline constexpr decltype(auto) min(T1 && v1, T2 && v2, T3 && v3, Ts && ... vs)
    {
        return min(min(std::forward<T1>(v1), std::forward<T2>(v2)), std::forward<T3>(v3), std::forward<Ts>(vs)...);
    }

    template <NumericOrPointer T1, NumericOrPointer T2>
    requires SameNumericType<T1, T2>
    inline constexpr auto max(const T1 v1, const T2 v2)
    {
        using U = std::conditional_t<sizeof(T1) >= sizeof(T2), T1, T2>;

        return v2 > v1 ? U(v2) : U(v1);
    }

    template <typename T1, typename T2, typename T3, typename... Ts>
    inline constexpr decltype(auto) max(T1 && v1, T2 && v2, T3 && v3, Ts && ... vs)
    {
        return max(max(std::forward<T1>(v1), std::forward<T2>(v2)), std::forward<T3>(v3), std::forward<Ts>(vs)...);
    }

    template <NumericOrPointer T1, NumericOrPointer T2>
    requires (SameNumericType<T1, T2> && sizeof(T1) >= sizeof(T2))
    inline T1 & minify(T1 & v1, const T2 v2)
    {
        return v2 < v1 ? v1 = v2 : v1;
    }

    template <typename T, typename T1, typename T2, typename... Ts>
    inline T & minify(T & min, T1 && v1, T2 && v2, Ts && ... vs)
    {
        return minify(minify(min, std::forward<T1>(v1)), std::forward<T2>(v2), std::forward<Ts>(vs)...);
    }

    template <NumericOrPointer T1, NumericOrPointer T2>
    requires (SameNumericType<T1, T2> && sizeof(T1) >= sizeof(T2))
    inline T1 & maxify(T1 & v1, const T2 v2)
    {
        return v2 > v1 ? v1 = v2 : v1;
    }

    template <typename T, typename T1, typename T2, typename... Ts>
    inline T & maxify(T & min, T1 && v1, T2 && v2, Ts && ... vs)
    {
        return maxify(maxify(min, std::forward<T1>(v1)), std::forward<T2>(v2), std::forward<Ts>(vs)...);
    }

    template <NumericOrPointer T1, NumericOrPointer T2>
    requires SameNumericType<T1, T2>
    inline constexpr auto minmax(const T1 v1, const T2 v2)
    {
        using U = std::conditional_t<sizeof(T1) >= sizeof(T2), T1, T2>;

        return (v2 < v1) ? std::pair<U, U>{v2, v1} : std::pair<U, U>{v1, v2};
    }

    template <typename T1, typename T2, typename T3, typename... Ts>
    inline constexpr auto minmax(T1 && v1, T2 && v2, T3 && v3, Ts && ... vs)
    {
        if constexpr (!sizeof...(Ts))
        {
            const auto [min1, max1]{minmax(v1, v2)};
            return std::pair{min(min1, v3), max(max1, v3)};
        }
        else
        {
            const auto [min1, max1]{minmax(v1, v2)};
            const auto [min2, max2]{minmax(v3, vs...)};
            return std::pair{min(min1, min2), max(max1, max2)};
        }
    }

    template <Numeric T>
    inline constexpr T clamp(const T v, const T min, const T max)
    {
        return qc::min(qc::max(v, min), max);
    }

    template <Numeric T>
    inline T & clampify(T & v, const T min, const T max)
    {
        return qc::minify(qc::maxify(v, min), max);
    }
}
