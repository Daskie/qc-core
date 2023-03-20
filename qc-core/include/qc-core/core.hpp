#pragma once

#include <cassert>
#include <cstdint>

#include <limits>
#include <utility>

#ifndef forceinline
    #ifdef QC_MSVC
        #define forceinline __forceinline
    #elif QC_GCC
        #define forceinline __attribute__((always_inline)) inline
    #else
        #error "Unsupported compiler"
    #endif
#else
    #error "`forceinline` already defined"
#endif

#ifndef nodisc
    #define nodisc [[nodiscard]]
#else
    #error "`nodisc` already defined"
#endif

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
    #define FAIL() do { if constexpr (::qc::debug) ::qc::failBreak(); return {}; } while (false)
#else
    #error "`FAIL` already defined"
#endif

#ifndef FAIL_IF
    #define FAIL_IF(condition) if (condition) [[unlikely]] FAIL()
#else
    #error "`FAIL_IF` already defined"
#endif

#ifndef TRIVIALLY_SERIALIZABLE
    #define TRIVIALLY_SERIALIZABLE static constexpr bool triviallySerializable{true}
#else
    #error "`TRIVIALLY_SERIALIZABLE` already defined"
#endif

#ifndef TRIVIALLY_SERIALIZABLE_IF
    #define TRIVIALLY_SERIALIZABLE_IF(condition) static constexpr bool triviallySerializable{condition}
#else
    #error "`TRIVIALLY_SERIALIZABLE_IF` already defined"
#endif

#ifndef SERIALIZABLE
    #define SERIALIZABLE(n) friend class ::qc::Serializer; friend class ::qc::Deserializer; static constexpr int serializableN{n}
#else
    #error "`SERIALIZABLE` already defined"
#endif

namespace qc
{
    #ifdef QC_DEBUG
        constexpr bool debug{false};
    #else
        constexpr bool debug{true};
    #endif

    /// Only support 64 bit platform
    static_assert(std::is_same_v<std::size_t, uint64_t>);
    static_assert(std::is_same_v<std::intptr_t, int64_t>);

    inline namespace primitives
    {
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

        using schar = signed char;
        using uchar = unsigned char;
        using ushort = unsigned short;
        using uint = unsigned int;
        using ulong = unsigned long;
        using llong = long long;
        using ullong = unsigned long long;
        using ldouble = long double;
    }

    inline namespace types
    {
        template <typename T1, typename T2> concept Same = std::is_same_v<std::remove_cv_t<T1>, std::remove_cv_t<T2>>;
        template <typename T, typename... Ts> concept OneOf = (Same<T, Ts> || ...);
        template <typename T> concept Void = Same<T, void>;
        template <typename T> concept Boolean = Same<T, bool>;
        template <typename T> concept SignedIntegral = OneOf<T, signed char, short, int, long, long long>;
        template <typename T> concept UnsignedIntegral = OneOf<T, unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long>;
        template <typename T> concept Integral = SignedIntegral<T> || UnsignedIntegral<T>;
        template <typename T> concept Floating = OneOf<T, float, double>;
        template <typename T> concept Numeric = Integral<T> || Floating<T>;
        template <typename T> concept Signed = SignedIntegral<T> || Floating<T>;
        template <typename T> concept Unsigned = UnsignedIntegral<T>;
        template <typename T> concept NumericOrBoolean = Numeric<T> || Boolean<T>;
        template <typename T> concept Enum = std::is_enum_v<T>;
        template <typename T> concept EnumOrBoolean = Enum<T> || Same<T, bool>;
        template <typename T> concept Pointer = std::is_pointer_v<T>;
        template <typename T> concept NumericOrPointer = Numeric<T> || Pointer<T>;
        template <typename T> concept IntegralOrPointer = Integral<T> || Pointer<T>;
        template <typename T> concept TriviallyCopyable = std::is_trivially_copyable_v<T>;

        template <int size> struct Sized;
        template <> struct Sized<1> { using S =  s8; using U =  u8; };
        template <> struct Sized<2> { using S = s16; using U = u16; };
        template <> struct Sized<4> { using S = s32; using U = u32; using F = f32; };
        template <> struct Sized<8> { using S = s64; using U = u64; using F = f64; };

        template <typename T, u64 n> using CArray = T[n];

        template <typename T1, typename T2> using LargerOf = std::conditional_t<sizeof(T1) >= sizeof(T2), T1, T2>;
    }

    template <Numeric T1, Numeric T2> struct _CommonHelper;
    template <Floating T1, Floating T2> struct _CommonHelper<T1, T2> { using T = LargerOf<T1, T2>; };
    template <SignedIntegral T1, SignedIntegral T2> struct _CommonHelper<T1, T2> { using T = LargerOf<T1, T2>; };
    template <UnsignedIntegral T1, UnsignedIntegral T2> struct _CommonHelper<T1, T2> { using T = LargerOf<T1, T2>; };
    template <SignedIntegral T1, UnsignedIntegral T2> requires (sizeof(T2) <= 4u) struct _CommonHelper<T1, T2> { using T = typename Sized<sizeof(T2) >= sizeof(T1) ? sizeof(T2) * 2u : sizeof(T1)>::S; };
    template <UnsignedIntegral T1, SignedIntegral T2> requires (sizeof(T1) <= 4u) struct _CommonHelper<T1, T2> { using T = typename Sized<sizeof(T1) >= sizeof(T2) ? sizeof(T1) * 2u : sizeof(T2)>::S; };

    inline namespace types
    {
        template <Numeric T1, Numeric T2> using Common = _CommonHelper<T1, T2>::T;
        template <typename T1, typename T2> concept CommonExists = requires { typename Common<T1, T2>; };
        template <typename T1, typename T2> concept SuperOf = std::is_same_v<T1, Common<T1, T2>>;
        template <typename T1, typename T2> concept SubOf = std::is_same_v<T2, Common<T1, T2>>;
        template <typename T1, typename T2> concept UnsignedSuperOf = UnsignedIntegral<T1> && UnsignedIntegral<T2> && sizeof(T1) >= sizeof(T2);
        template <typename T1, typename T2> concept UnsignedSubOf = UnsignedIntegral<T1> && UnsignedIntegral<T2> && sizeof(T1) <= sizeof(T2);
        template <typename T1, typename T2> concept SignedSuperOf = SignedIntegral<T1> && SignedIntegral<T2> && sizeof(T1) >= sizeof(T2);
        template <typename T1, typename T2> concept SignedSubOf = SignedIntegral<T1> && SignedIntegral<T2> && sizeof(T1) <= sizeof(T2);
        template <typename T1, typename T2> concept FloatingSuperOf = Floating<T1> && Floating<T2> && sizeof(T1) >= sizeof(T2);
        template <typename T1, typename T2> concept FloatingSubOf = Floating<T1> && Floating<T2> && sizeof(T1) <= sizeof(T2);
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

    enum Platform { other, windows, linux };

    constexpr Platform platform{
        #if defined QC_WINDOWS
            Platform::windows
        #elif defined QC_LINUX
            Platform::linux
        #else
            Platform::other
        #endif
    };

    // Forward declarations
    class Serializer;
    class Deserializer;

    template <bool condition, typename T1, typename T2>
    nodisc constexpr decltype(auto) ternary(T1 && v1, T2 && v2)
    {
        if constexpr (condition) return std::forward<T1>(v1);
        else return std::forward<T2>(v2);
    }

    template <Enum E> nodisc constexpr std::underlying_type_t<E> underlyingVal(const E e) { return std::underlying_type_t<E>(e); }

    inline void failBreak() {};

    template <typename T1, typename T2 = T1>
    struct Duo
    {
        SERIALIZABLE(2);

        T1 a;
        T2 b;
    };

    template <typename T>
    struct Duo<T, T>
    {
        SERIALIZABLE(2);

        T a;
        T b;

        template <std::integral I> nodisc forceinline T & operator[](const I i) { return (&a)[i]; }
        template <std::integral I> nodisc forceinline const T & operator[](const I i) const { return (&a)[i]; }

        nodisc forceinline T * begin() { return &a; };
        nodisc forceinline const T * begin() const { return &a; };

        nodisc forceinline T * end() { return &b + 1; };
        nodisc forceinline const T * end() const { return &b + 1; };
    };

    template <typename T1, typename T2 = T1, typename T3 = T2>
    struct Trio
    {
        SERIALIZABLE(3);

        T1 a;
        T2 b;
        T3 c;
    };

    template <typename T>
    struct Trio<T, T, T>
    {
        SERIALIZABLE(3);

        T a;
        T b;
        T c;

        template <std::integral I> nodisc forceinline T & operator[](const I i) { return (&a)[i]; }
        template <std::integral I> nodisc forceinline const T & operator[](const I i) const { return (&a)[i]; }

        nodisc forceinline T * begin() { return &a; };
        nodisc forceinline const T * begin() const { return &a; };

        nodisc forceinline T * end() { return &c + 1; };
        nodisc forceinline const T * end() const { return &c + 1; };
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

        nodisc explicit operator bool() const { return _success; }

        nodisc T & operator*();
        nodisc const T & operator*() const;

        nodisc T * operator->();
        nodisc const T * operator->() const;

      private:

        // Putting val in a union stops its default constructor and destructor from being called automatically
        union { T _val; };
        bool _success;
    };

    //
    // ...
    //
    template <Numeric T1, Numeric T2> nodisc constexpr Common<T1, T2> min(T1 v1, T2 v2);
    template <typename T> nodisc constexpr T * min(T * v1, T * v2);
    template <Numeric T1, Numeric T2, Numeric T3, Numeric... Ts> nodisc constexpr auto min(T1 v1, T2 v2, T3 v3, Ts... vs);
    template <typename T, typename... Ts> nodisc constexpr T * min(T * v1, T * v2, T * v3, Ts... vs);

    //
    // ...
    //
    template <Numeric T1, Numeric T2> nodisc constexpr Common<T1, T2> max(T1 v1, T2 v2);
    template <typename T> nodisc constexpr T * max(T * v1, T * v2);
    template <Numeric T1, Numeric T2, Numeric T3, Numeric... Ts> nodisc constexpr auto max(T1 v1, T2 v2, T3 v3, Ts... vs);
    template <typename T, typename... Ts> nodisc constexpr T * max(T * v1, T * v2, T * v3, Ts... vs);

    //
    // ...
    //
    template <Numeric T1, SubOf<T1> T2> T1 & minify(T1 & v1, T2 v2);
    template <typename T> T * & minify(T * & v1, T * v2);
    template <Numeric T, Numeric T1, Numeric T2, Numeric... Ts> T & minify(T & min, T1 v1, T2 v2, Ts... vs);
    template <typename T, typename... Ts> T * & minify(T * & min, T * v1, T * v2, Ts... vs);

    //
    // ...
    //
    template <Numeric T1, SubOf<T1> T2> T1 & maxify(T1 & v1, T2 v2);
    template <typename T> T * & maxify(T * & v1, T * v2);
    template <Numeric T, Numeric T1, Numeric T2, Numeric... Ts> T & maxify(T & min, T1 v1, T2 v2, Ts... vs);
    template <typename T, typename... Ts> T * & maxify(T * & min, T * v1, T * v2, Ts... vs);

    //
    // ...
    //
    template <Numeric T> nodisc constexpr T clamp(T v, T min, T max);

    //
    // ...
    //
    template <Numeric T> T & clampify(T & v, T min, T max);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    forceinline Result<T>::Result() :
        _success{false}
    #pragma warning(suppress: 4582)
    {}

    template <typename T>
    forceinline Result<T>::Result(T && v) :
        _val{std::move(v)},
        _success{true}
    {}

    template <typename T>
    forceinline Result<T>::~Result()
    #pragma warning(suppress: 4583)
    {
        if (_success)
        {
            this->_val.~T();
        }
    }

    template <typename T>
    forceinline T & Result<T>::operator*()
    {
        assert(_success);
        return this->_val;
    }

    template <typename T>
    forceinline const T & Result<T>::operator*() const
    {
        assert(_success);
        return this->_val;
    }

    template <typename T>
    forceinline T * Result<T>::operator->()
    {
        assert(_success);
        return &this->_val;
    }

    template <typename T>
    forceinline const T * Result<T>::operator->() const
    {
        assert(_success);
        return &this->_val;
    }

    template <Numeric T1, Numeric T2>
    forceinline constexpr Common<T1, T2> min(const T1 v1, const T2 v2)
    {
        using T = Common<T1, T2>;
        if constexpr (Signed<T1> == Signed<T2>) return T(v2 < v1 ? v2 : v1);
        else return min(T{v1}, T{v2});
    }

    template <typename T>
    forceinline constexpr T * min(T * const v1, T * const v2)
    {
        return v2 < v1 ? v2 : v1;
    }

    template <Numeric T1, Numeric T2, Numeric T3, Numeric... Ts>
    forceinline constexpr auto min(const T1 v1, const T2 v2, const T3 v3, Ts... vs)
    {
        return min(min(v1, v2), v3, vs...);
    }

    template <typename T, typename... Ts>
    forceinline constexpr T * min(T * const v1, T * const v2, T * const v3, Ts... vs)
    {
        return min(min(v1, v2), v3, vs...);
    }

    template <Numeric T1, Numeric T2>
    forceinline constexpr Common<T1, T2> max(const T1 v1, const T2 v2)
    {
        using T = Common<T1, T2>;
        if constexpr (Signed<T1> == Signed<T2>) return T(v2 > v1 ? v2 : v1);
        else return max(T{v1}, T{v2});
    }

    template <typename T>
    forceinline constexpr T * max(T * const v1, T * const v2)
    {
        return v2 > v1 ? v2 : v1;
    }

    template <Numeric T1, Numeric T2, Numeric T3, Numeric... Ts>
    forceinline constexpr auto max(const T1 v1, const T2 v2, const T3 v3, Ts... vs)
    {
        return max(max(v1, v2), v3, vs...);
    }

    template <typename T, typename... Ts>
    forceinline constexpr T * max(T * const v1, T * const v2, T * const v3, Ts... vs)
    {
        return max(max(v1, v2), v3, vs...);
    }

    template <Numeric T1, SubOf<T1> T2>
    forceinline T1 & minify(T1 & v1, const T2 v2)
    {
        return v2 < v1 ? v1 = v2 : v1;
    }

    template <typename T>
    forceinline T * & minify(T * & v1, T * const v2)
    {
        return v2 < v1 ? v1 = v2 : v1;
    }

    template <Numeric T, Numeric T1, Numeric T2, Numeric... Ts>
    forceinline T & minify(T & min, const T1 v1, const T2 v2, Ts... vs)
    {
        return minify(minify(min, v1), v2, vs...);
    }

    template <typename T, Same<T>... Ts>
    forceinline T * & minify(T * & min, T * const v1, T * const v2, Ts... vs)
    {
        return minify(minify(min, v1), v2, vs...);
    }

    template <Numeric T1, SubOf<T1> T2>
    forceinline T1 & maxify(T1 & v1, const T2 v2)
    {
        return v2 > v1 ? v1 = v2 : v1;
    }

    template <typename T>
    forceinline T * & maxify(T * & v1, T * const v2)
    {
        return v2 > v1 ? v1 = v2 : v1;
    }

    template <Numeric T, Numeric T1, Numeric T2, Numeric... Ts>
    forceinline T & maxify(T & min, const T1 v1, const T2 v2, Ts... vs)
    {
        return maxify(maxify(min, v1), v2, vs...);
    }

    template <typename T, typename... Ts>
    forceinline T * & maxify(T * & min, T * const v1, T * const v2, Ts... vs)
    {
        return maxify(maxify(min, v1), v2, vs...);
    }

    template <Numeric T>
    forceinline constexpr T clamp(const T v, const T min, const T max)
    {
        return qc::min(qc::max(v, min), max);
    }

    template <Numeric T>
    forceinline T & clampify(T & v, const T min, const T max)
    {
        return qc::minify(qc::maxify(v, min), max);
    }
}
