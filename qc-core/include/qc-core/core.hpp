#pragma once

#include <cassert>
#include <cstdint>
#include <cstdlib>

#include <bit>
#include <limits>
#include <utility>

#if defined QC_MSVC
    #define forceinline __forceinline
#elif defined QC_GCC
    #define forceinline __attribute__((always_inline)) inline
#else
    #error "Unsupported compiler"
#endif

#define nodisc [[nodiscard]]

#define ABORT() ::std::abort()

#define ABORT_IF(condition) if (condition) [[unlikely]] ::std::abort()

#define DEBUG_ABORT() if constexpr (::qc::debug) ABORT()

#define DEBUG_ABORT_IF(condition) if constexpr (::qc::debug) ABORT_IF(condition)

#define FAIL() do { if constexpr (::qc::debug) ::qc::failBreak(); return {}; } while (false)

#define FAIL_IF(condition) if (condition) [[unlikely]] FAIL()

#define SERIALIZABLE(n) friend class ::qc::Serializer; friend class ::qc::Deserializer; static constexpr ::qc::u32 _serializableN{n}

#ifdef QC_MSVC
    #define MSVC_WARNING_PUSH __pragma(warning(push))
#else
    #define MSVC_WARNING_PUSH
#endif

#ifdef QC_MSVC
    #define MSVC_WARNING_POP __pragma(warning(pop))
#else
    #define MSVC_WARNING_POP
#endif

#ifdef QC_MSVC
    #define MSVC_WARNING_DISABLE(code) __pragma(warning(disable: code))
#else
    #define MSVC_WARNING_DISABLE(code)
#endif

#ifdef QC_MSVC
    #define MSVC_WARNING_SUPPRESS(code) __pragma(warning(suppress: code))
#else
    #define MSVC_WARNING_SUPPRESS(code)
#endif

#ifdef QC_GCC
    #define GCC_DIAGNOSTIC_PUSH _Pragma("GCC diagnostic push")
#else
    #define GCC_DIAGNOSTIC_PUSH
#endif

#ifdef QC_GCC
    #define GCC_DIAGNOSTIC_POP _Pragma("GCC diagnostic pop")
#else
    #define GCC_DIAGNOSTIC_POP
#endif

#ifdef QC_GCC
    #define STRINGIFY(x) #x
    #define GCC_DIAGNOSTIC_IGNORED(code) _Pragma(STRINGIFY(GCC diagnostic ignored code))
#else
    #define GCC_DIAGNOSTIC_IGNORED(code)
#endif

namespace qc
{
    /// Only support 64 bit, little endian platforms
    static_assert(std::is_same_v<std::size_t, uint64_t>);
    static_assert(std::is_same_v<std::intptr_t, int64_t>);
    static_assert(std::endian::native == std::endian::little);

    #ifdef QC_DEBUG
        constexpr bool debug{true};
        constexpr bool release{false};
    #else
        constexpr bool debug{false};
        constexpr bool release{true};
    #endif

    enum class Compiler { other, msvc, gcc };

    #if defined QC_MSVC
        constexpr Compiler compiler{Compiler::msvc};
        constexpr bool msvc{true};
        constexpr bool gcc{false};
    #elif defined QC_GCC
        constexpr Compiler compiler{Compiler::gcc};
        constexpr bool msvc{false};
        constexpr bool gcc{true};
    #else
        constexpr Compiler compiler{Compiler::other};
        constexpr bool msvc{false};
        constexpr bool gcc{false};
    #endif

    enum class Platform { other, windows, linux };

    #if defined QC_WINDOWS
        constexpr Platform platform{Platform::windows};
        constexpr bool windows{true};
        constexpr bool linux{false};
    #elif defined QC_LINUX
        constexpr Platform platform{Platform::linux};
        constexpr bool windows{false};
        constexpr bool linux{true};
    #else
        constexpr Platform platform{Platform::other};
        constexpr bool msvc{false};
        constexpr bool gcc{false};
    #endif

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

        ///
        /// Literal suffixes for primitive types
        /// Divide by zero when literal is out of range to force compile-time error
        ///
        consteval  s8 operator "" _s8(const unsigned long long v) { return  s8(v / static_cast<unsigned long long>(v <= u64(std::numeric_limits< s8>::max()))); }
        consteval s16 operator ""_s16(const unsigned long long v) { return s16(v / static_cast<unsigned long long>(v <= u64(std::numeric_limits<s16>::max()))); }
        consteval s32 operator ""_s32(const unsigned long long v) { return s32(v / static_cast<unsigned long long>(v <= u64(std::numeric_limits<s32>::max()))); }
        consteval s64 operator ""_s64(const unsigned long long v) { return s64(v / static_cast<unsigned long long>(v <= u64(std::numeric_limits<s64>::max()))); }
        consteval  u8 operator "" _u8(const unsigned long long v) { return  u8(v / static_cast<unsigned long long>(v <= std::numeric_limits< u8>::max())); }
        consteval u16 operator ""_u16(const unsigned long long v) { return u16(v / static_cast<unsigned long long>(v <= std::numeric_limits<u16>::max())); }
        consteval u32 operator ""_u32(const unsigned long long v) { return u32(v / static_cast<unsigned long long>(v <= std::numeric_limits<u32>::max())); }
        consteval u64 operator ""_u64(const unsigned long long v) { return u64(v / static_cast<unsigned long long>(v <= std::numeric_limits<u64>::max())); }
    }

    inline namespace types
    {
        template <typename T1, typename T2> concept Same = std::is_same_v<T1, T2>;
        template <typename T1, typename T2> concept Sameish = Same<std::decay_t<T1>, std::decay_t<T2>>;
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
        template <typename T1, typename T2> concept EqualityComparable = requires (T1 v1, T2 v2) { { v1 == v2 } -> Boolean; };
        template <typename From, typename To> concept ImplicitlyConvertibleTo = requires (From from, To to) { new (&to) To{from}; }; // Should just be able to say `To{from}`; some kind of MSVC bug
        template <typename From, typename To> concept ExplicitlyConvertibleTo = requires (From from) { static_cast<To>(from); };

        template <u32 size> struct Sized;
        template <> struct Sized<1u> { using S =  s8; using U =  u8; };
        template <> struct Sized<2u> { using S = s16; using U = u16; };
        template <> struct Sized<4u> { using S = s32; using U = u32; using F = f32; };
        template <> struct Sized<8u> { using S = s64; using U = u64; using F = f64; };

        template <typename T, u64 n> using CArray = T[n];

        template <typename T1, typename T2> using LargerOf = std::conditional_t<sizeof(T1) >= sizeof(T2), T1, T2>;
    }

    template <Numeric T1, Numeric T2> struct _CommonHelper;
    template <Floating T1, Floating T2> struct _CommonHelper<T1, T2> { using Type = LargerOf<T1, T2>; };
    template <SignedIntegral T1, SignedIntegral T2> struct _CommonHelper<T1, T2> { using Type = LargerOf<T1, T2>; };
    template <UnsignedIntegral T1, UnsignedIntegral T2> struct _CommonHelper<T1, T2> { using Type = LargerOf<T1, T2>; };
    template <SignedIntegral T1, UnsignedIntegral T2> requires (sizeof(T2) <= 4u) struct _CommonHelper<T1, T2> { using Type = typename Sized<sizeof(T2) >= sizeof(T1) ? sizeof(T2) * 2u : sizeof(T1)>::S; };
    template <UnsignedIntegral T1, SignedIntegral T2> requires (sizeof(T1) <= 4u) struct _CommonHelper<T1, T2> { using Type = typename Sized<sizeof(T1) >= sizeof(T2) ? sizeof(T1) * 2u : sizeof(T2)>::S; };

    inline namespace types
    {
        template <typename T1, typename T2> using Common = _CommonHelper<T1, T2>::Type;
        template <typename T1, typename T2> concept CommonExists = requires { typename Common<T1, T2>; };

        template <typename T1, typename T2> concept InclusiveSuperOf = Same<T1, Common<T1, T2>>;
        template <typename T1, typename T2> concept ExclusiveSuperOf = InclusiveSuperOf<T1, T2> && !Same<T1, T2>;
        template <typename T1, typename T2> concept InclusiveSubOf = Same<T2, Common<T1, T2>>;
        template <typename T1, typename T2> concept ExclusiveSubOf = InclusiveSubOf<T1, T2> && !Same<T1, T2>;
        template <typename T1, typename T2> concept InclusiveUnsignedSuperOf = UnsignedIntegral<T1> && UnsignedIntegral<T2> && sizeof(T1) >= sizeof(T2);
        template <typename T1, typename T2> concept ExclusiveUnsignedSuperOf = UnsignedIntegral<T1> && UnsignedIntegral<T2> && sizeof(T1) > sizeof(T2);
        template <typename T1, typename T2> concept InclusiveUnsignedSubOf = UnsignedIntegral<T1> && UnsignedIntegral<T2> && sizeof(T1) <= sizeof(T2);
        template <typename T1, typename T2> concept ExclusiveUnsignedSubOf = UnsignedIntegral<T1> && UnsignedIntegral<T2> && sizeof(T1) < sizeof(T2);
        template <typename T1, typename T2> concept InclusiveSignedSuperOf = SignedIntegral<T1> && SignedIntegral<T2> && sizeof(T1) >= sizeof(T2);
        template <typename T1, typename T2> concept ExclusiveSignedSuperOf = SignedIntegral<T1> && SignedIntegral<T2> && sizeof(T1) > sizeof(T2);
        template <typename T1, typename T2> concept InclusiveSignedSubOf = SignedIntegral<T1> && SignedIntegral<T2> && sizeof(T1) <= sizeof(T2);
        template <typename T1, typename T2> concept ExclusiveSignedSubOf = SignedIntegral<T1> && SignedIntegral<T2> && sizeof(T1) < sizeof(T2);
        template <typename T1, typename T2> concept InclusiveFloatingSuperOf = Floating<T1> && Floating<T2> && sizeof(T1) >= sizeof(T2);
        template <typename T1, typename T2> concept ExclusiveFloatingSuperOf = Floating<T1> && Floating<T2> && sizeof(T1) > sizeof(T2);
        template <typename T1, typename T2> concept InclusiveFloatingSubOf = Floating<T1> && Floating<T2> && sizeof(T1) <= sizeof(T2);
        template <typename T1, typename T2> concept ExclusiveFloatingSubOf = Floating<T1> && Floating<T2> && sizeof(T1) < sizeof(T2);
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

    struct IKnowWhatImDoing {};

    // Forward declarations
    class Serializer;
    class Deserializer;

    template <bool condition, typename T1, typename T2>
    nodisc constexpr decltype(auto) ternary(T1 && v1, T2 && v2)
    {
        if constexpr (condition) return std::forward<T1>(v1);
        else return std::forward<T2>(v2);
    }

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
    /// Simple scope guard
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

    template <Numeric To, Numeric From> nodisc To checkedCast(From v);

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
    template <Numeric T1, InclusiveSubOf<T1> T2> T1 & minify(T1 & v1, T2 v2);
    template <typename T> T * & minify(T * & v1, T * v2);
    template <Numeric T, Numeric T1, Numeric T2, Numeric... Ts> T & minify(T & min, T1 v1, T2 v2, Ts... vs);
    template <typename T, typename... Ts> T * & minify(T * & min, T * v1, T * v2, Ts... vs);

    //
    // ...
    //
    template <Numeric T1, InclusiveSubOf<T1> T2> T1 & maxify(T1 & v1, T2 v2);
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
    MSVC_WARNING_SUPPRESS(4582)
    {}

    template <typename T>
    forceinline Result<T>::Result(T && v) :
        _val{std::move(v)},
        _success{true}
    {}

    template <typename T>
    forceinline Result<T>::~Result()
    MSVC_WARNING_SUPPRESS(4583)
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

    template <Numeric To, Numeric From>
    forceinline To checkedCast(const From v)
    {
        if constexpr (Floating<To>)
        {
            const To v_{To(v)};
            if constexpr (!Floating<From> || sizeof(From) > sizeof(To))
            {
                ABORT_IF(From(v_) != v);
            }
            return v_;
        }
        else if constexpr (SignedIntegral<To>)
        {
            if constexpr (Floating<From>)
            {
                const To v_{To(v)};
                const From v__{From(v_)};
                ABORT_IF(v__ != v);
                return v_;
            }
            else if constexpr (SignedIntegral<From>)
            {
                if constexpr (sizeof(From) > sizeof(To))
                {
                    ABORT_IF(v < std::numeric_limits<To>::min() || v > std::numeric_limits<To>::max());
                }
                return To(v);
            }
            else if constexpr (UnsignedIntegral<From>)
            {
                if constexpr (sizeof(From) >= sizeof(To))
                {
                    ABORT_IF(v > From(std::numeric_limits<To>::max()));
                }
                return To(v);
            }
        }
        else if constexpr (UnsignedIntegral<To>)
        {
            if constexpr (Floating<From>)
            {
                const To v_{To(v)};
                ABORT_IF(From(v_) != v);
                return v_;
            }
            else if constexpr (SignedIntegral<From>)
            {
                ABORT_IF(v < 0);
                if constexpr (sizeof(From) > sizeof(To))
                {
                    ABORT_IF(v > From(std::numeric_limits<To>::max()));
                }
                return To(v);
            }
            else if constexpr (UnsignedIntegral<From>)
            {
                if constexpr (sizeof(From) > sizeof(To))
                {
                    ABORT_IF(v > std::numeric_limits<To>::max());
                }
                return To(v);
            }
        }
    }

    template <Numeric To, Numeric From>
    forceinline To assertCast(const From v)
    {
        if constexpr (release)
        {
            return To(v);
        }
        else
        {
            return checkedCast<To>(v);
        }
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

    template <Numeric T1, InclusiveSubOf<T1> T2>
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

    template <typename T, typename... Ts>
    forceinline T * & minify(T * & min, T * const v1, T * const v2, Ts... vs)
    {
        return minify(minify(min, v1), v2, vs...);
    }

    template <Numeric T1, InclusiveSubOf<T1> T2>
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
