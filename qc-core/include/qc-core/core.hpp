#pragma once

#include <cassert>
#include <cstdint>

#include <limits>
#include <utility>

#ifndef ABORT
    #define ABORT() ::std::abort()
#else
    #error "`ABORT` already defined"
#endif

#ifndef ABORT_IF
    #define ABORT_IF(condition) if (condition) [[unlikely]] ::std::abort()
#else
    #error "`ABORT_IF` already defined"
#endif

#ifndef FAIL
    #define FAIL() return {}
#else
    #error "`FAIL` already defined"
#endif

#ifndef FAIL_IF
    #define FAIL_IF(condition) if (condition) [[unlikely]] return {}
#else
    #error "`FAIL_IF` already defined"
    #error
#endif

// Set forceinline
// TODO: Add forceinline where appropriate
#ifndef forceinline
    #ifdef _MSC_VER
        #define forceinline __forceinline
    #elif __GNUC__
        #define forceinline __attribute__((always_inline)) inline
    #else
        #error "Unsupported compiler"
    #endif
#else
    #warning "`forceinline` already defined"
#endif

namespace qc
{
    #ifdef NDEBUG
        constexpr bool debug{false};
    #else
        constexpr bool debug{true};
    #endif

    /// Only support 64 bit platform
    static_assert(std::is_same_v<size_t, uint64_t>);
    static_assert(std::is_same_v<intptr_t, int64_t>);
    static_assert(std::is_same_v<ptrdiff_t , int64_t>);

    inline namespace types
    {
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
    }

    inline namespace concepts
    {
        template <typename T1, typename T2> concept Same = std::is_same_v<std::remove_cv_t<T1>, std::remove_cv_t<T2>>;
        template <typename T> concept Void = Same<T, void>;
        template <typename T> concept Boolean = Same<T, bool>;
        template <typename T> concept Integral = std::is_integral_v<T> && !Boolean<T> && !Same<T, char>;
        template <typename T> concept SignedIntegral = Integral<T> && std::is_signed_v<T>;
        template <typename T> concept UnsignedIntegral = Integral<T> && std::is_unsigned_v<T>;
        template <typename T> concept Floating = std::is_floating_point_v<T>;
        template <typename T> concept Numeric = Integral<T> || Floating<T>;
        template <typename T> concept Signed = SignedIntegral<T> || Floating<T>;
        template <typename T> concept Unsigned = UnsignedIntegral<T>;
        template <typename T> concept NumericOrBoolean = Numeric<T> || Boolean<T>;
        template <typename T> concept Enum = std::is_enum_v<T>;
        template <typename T> concept EnumOrBoolean = Enum<T> || Same<T, bool>;
        template <typename T> concept Pointer = std::is_pointer_v<T>;
        template <typename T> concept NumericOrPointer = Numeric<T> || Pointer<T>;
        template <typename T> concept IntegralOrPointer = Integral<T> || Pointer<T>;
        template <typename T1, typename T2> concept SameNumericType = SignedIntegral<T1> == SignedIntegral<T2> && UnsignedIntegral<T1> == UnsignedIntegral<T2> && Floating<T1> == Floating<T2>;
        template <typename T1, typename T2> concept Sameish = std::is_same_v<std::decay_t<T1>, std::decay_t<T2>> || (Numeric<T1> && Numeric<T2> && SameNumericType<T1, T2>);
    }

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

    template <int size> struct sized;
    template <> struct sized<1> { using stype =  s8; using utype =  u8; };
    template <> struct sized<2> { using stype = s16; using utype = u16; };
    template <> struct sized<4> { using stype = s32; using utype = u32; using ftype = f32; };
    template <> struct sized<8> { using stype = s64; using utype = u64; using ftype = f64; };
    template <typename T> using stype = typename sized<sizeof(T)>::stype;
    template <typename T> using utype = typename sized<sizeof(T)>::utype;
    template <typename T> using ftype = typename sized<sizeof(T)>::ftype;

    template <typename T, typename... Ts> concept OneOf = (std::same_as<T, Ts> || ...);

    template <bool condition, typename T1, typename T2>
    constexpr decltype(auto) ternary(T1 && v1, T2 && v2)
    {
        if constexpr (condition) return std::forward<T1>(v1);
        else return std::forward<T2>(v2);
    }

    template <Enum E> constexpr std::underlying_type_t<E> underlyingVal(const E e) { return std::underlying_type_t<E>(e); }

    template <typename T1, typename T2 = T1>
    struct Duo
    {
        T1 a;
        T2 b;

        T1 * begin() requires (Same<T1, T2>) { return &a; };
        const T1 * begin() const requires (Same<T1, T2>) { return &a; };

        T1 * end() requires (Same<T1, T2>) { return &b + 1; };
        const T1 * end() const requires (Same<T1, T2>) { return &b + 1; };
    };

    template <typename T1, typename T2 = T1, typename T3 = T2>
    struct Trio
    {
        T1 a;
        T2 b;
        T2 c;

        T1 * begin() requires (Same<T1, T2> && Same<T1, T3>) { return &a; };
        const T1 * begin() const requires (Same<T1, T2> && Same<T1, T3>) { return &a; };

        T1 * end() requires (Same<T1, T2> && Same<T1, T3>) { return &c + 1; };
        const T1 * end() const requires (Same<T1, T2> && Same<T1, T3>) { return &c + 1; };
    };

    ///
    /// Simple guard lock
    ///
    /// Calls the given prodecure (function pointer, lambda, std::function, etc.) when it goes out of scope
    ///
    template <typename Proc>
    class ScopeGuard
    {
      public:

        ScopeGuard(const Proc & proc) : _proc{proc} {};
        ScopeGuard(Proc && proc) : _proc{std::move(proc)} {};

        ~ScopeGuard() { if (!_released) _proc(); }

        void release() { _released = true;  }

      private:

        Proc _proc;
        bool _released{false};
    };

    ///
    /// Simple object that holds a return error, or a value if there was no error
    /// @tparam T value type
    /// @tparam E error type
    ///
    template <typename T>
    class Result
    {
      public:

        Result();
        Result(T && v);

        Result(const Result &) = delete;
        Result(Result &&) = delete;

        Result & operator=(const Result &) = delete;
        Result & operator=(Result &&) = delete;

        ~Result();

        [[nodiscard]] explicit operator bool() const { return _success; }

        [[nodiscard]] T & operator*();
        [[nodiscard]] const T & operator*() const;

        [[nodiscard]] T * operator->();
        [[nodiscard]] const T * operator->() const;

      private:

        // Putting val in a union stops its default constructor and destructor from being called automatically
        union { T _val; };
        bool _success;
    };

    //
    // ...
    //
    template <NumericOrPointer T1, NumericOrPointer T2> requires Sameish<T1, T2> constexpr auto min(T1 v1, T2 v2);
    template <NumericOrPointer T1, NumericOrPointer T2, NumericOrPointer T3, typename... Ts> constexpr auto min(T1 v1, T2 v2, T3 v3, Ts... vs);

    //
    // ...
    //
    template <NumericOrPointer T1, NumericOrPointer T2> requires Sameish<T1, T2> constexpr auto max(T1 v1, T2 v2);
    template <NumericOrPointer T1, NumericOrPointer T2, NumericOrPointer T3, typename... Ts> constexpr auto max(T1 v1, T2 v2, T3 v3, Ts... vs);

    //
    // ...
    //
    template <NumericOrPointer T1, NumericOrPointer T2> requires (Sameish<T1, T2> && sizeof(T1) >= sizeof(T2)) T1 & minify(T1 & v1, T2 v2);
    template <NumericOrPointer T, NumericOrPointer T1, NumericOrPointer T2, typename... Ts> T & minify(T & min, T1 v1, T2 v2, Ts... vs);

    //
    // ...
    //
    template <NumericOrPointer T1, NumericOrPointer T2> requires (Sameish<T1, T2> && sizeof(T1) >= sizeof(T2)) T1 & maxify(T1 & v1, T2 v2);
    template <NumericOrPointer T, NumericOrPointer T1, NumericOrPointer T2, typename... Ts> T & maxify(T & min, T1 v1, T2 v2, Ts... vs);

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
    template <typename T>
    inline Result<T>::Result() :
        _success{false}
    #pragma warning(suppress: 4582)
    {}

    template <typename T>
    inline Result<T>::Result(T && v) :
        _val{std::move(v)},
        _success{true}
    {}

    template <typename T>
    inline Result<T>::~Result()
    #pragma warning(suppress: 4583)
    {
        if (_success)
        {
            this->_val.~T();
        }
    }

    template <typename T>
    inline T & Result<T>::operator*()
    {
        assert(_success);
        return this->_val;
    }

    template <typename T>
    inline const T & Result<T>::operator*() const
    {
        assert(_success);
        return this->_val;
    }

    template <typename T>
    inline T * Result<T>::operator->()
    {
        assert(_success);
        return &this->_val;
    }

    template <typename T>
    inline const T * Result<T>::operator->() const
    {
        assert(_success);
        return &this->_val;
    }

    template <NumericOrPointer T1, NumericOrPointer T2>
    requires Sameish<T1, T2>
    inline constexpr auto min(const T1 v1, const T2 v2)
    {
        using U = std::conditional_t<sizeof(T1) >= sizeof(T2), T1, T2>;

        return v2 < v1 ? U(v2) : U(v1);
    }

    template <NumericOrPointer T1, NumericOrPointer T2, NumericOrPointer T3, NumericOrPointer... Ts>
    inline constexpr auto min(const T1 v1, const T2 v2, const T3 v3, const Ts... vs)
    {
        return min(min(v1, v2), v3, vs...);
    }

    template <NumericOrPointer T1, NumericOrPointer T2>
    requires Sameish<T1, T2>
    inline constexpr auto max(const T1 v1, const T2 v2)
    {
        using U = std::conditional_t<sizeof(T1) >= sizeof(T2), T1, T2>;

        return v2 > v1 ? U(v2) : U(v1);
    }

    template <NumericOrPointer T1, NumericOrPointer T2, NumericOrPointer T3, NumericOrPointer... Ts>
    inline constexpr auto max(const T1 v1, const T2 v2, const T3 v3, const Ts... vs)
    {
        return max(max(v1, v2), v3, vs...);
    }

    template <NumericOrPointer T1, NumericOrPointer T2>
    requires (Sameish<T1, T2> && sizeof(T1) >= sizeof(T2))
    inline T1 & minify(T1 & v1, const T2 v2)
    {
        return v2 < v1 ? v1 = v2 : v1;
    }

    template <NumericOrPointer T, NumericOrPointer T1, NumericOrPointer T2, NumericOrPointer... Ts>
    inline T & minify(T & min, const T1 v1, const T2 v2, const Ts... vs)
    {
        return minify(minify(min, v1), v2, vs...);
    }

    template <NumericOrPointer T1, NumericOrPointer T2>
    requires (Sameish<T1, T2> && sizeof(T1) >= sizeof(T2))
    inline T1 & maxify(T1 & v1, const T2 v2)
    {
        return v2 > v1 ? v1 = v2 : v1;
    }

    template <NumericOrPointer T, NumericOrPointer T1, NumericOrPointer T2, NumericOrPointer... Ts>
    inline T & maxify(T & min, const T1 v1, const T2 v2, const Ts... vs)
    {
        return maxify(maxify(min, v1), v2, vs...);
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
