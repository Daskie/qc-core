#pragma once

#include <qc-core/vector.hpp>

namespace qc
{
    template <typename T, u32 n> struct span;

    inline namespace primitives
    {
        using qc::span;

        template <NumericOrPointer T> using span1 = span<T, 1>;
        template <Numeric          T> using span2 = span<T, 2>;
        template <Numeric          T> using span3 = span<T, 3>;
        template <Numeric          T> using span4 = span<T, 4>;

        template <u32 n> using fspan = span<f32, n>;
        template <u32 n> using dspan = span<f64, n>;
        template <u32 n> using cspan = span<s8, n>;
        template <u32 n> using ucspan = span<u8, n>;
        template <u32 n> using sspan = span<s16, n>;
        template <u32 n> using usspan = span<u16, n>;
        template <u32 n> using ispan = span<s32, n>;
        template <u32 n> using uispan = span<u32, n>;
        template <u32 n> using lspan = span<s64, n>;
        template <u32 n> using ulspan = span<u64, n>;

        using fspan1 = span<f32, 1>;
        using fspan2 = span<f32, 2>;
        using fspan3 = span<f32, 3>;
        using fspan4 = span<f32, 4>;
        using dspan1 = span<f64, 1>;
        using dspan2 = span<f64, 2>;
        using dspan3 = span<f64, 3>;
        using dspan4 = span<f64, 4>;
        using cspan1 = span<s8, 1>;
        using cspan2 = span<s8, 2>;
        using cspan3 = span<s8, 3>;
        using cspan4 = span<s8, 4>;
        using ucspan1 = span<u8, 1>;
        using ucspan2 = span<u8, 2>;
        using ucspan3 = span<u8, 3>;
        using ucspan4 = span<u8, 4>;
        using sspan1 = span<s16, 1>;
        using sspan2 = span<s16, 2>;
        using sspan3 = span<s16, 3>;
        using sspan4 = span<s16, 4>;
        using usspan1 = span<u16, 1>;
        using usspan2 = span<u16, 2>;
        using usspan3 = span<u16, 3>;
        using usspan4 = span<u16, 4>;
        using ispan1 = span<s32, 1>;
        using ispan2 = span<s32, 2>;
        using ispan3 = span<s32, 3>;
        using ispan4 = span<s32, 4>;
        using uispan1 = span<u32, 1>;
        using uispan2 = span<u32, 2>;
        using uispan3 = span<u32, 3>;
        using uispan4 = span<u32, 4>;
        using lspan1 = span<s64, 1>;
        using lspan2 = span<s64, 2>;
        using lspan3 = span<s64, 3>;
        using lspan4 = span<s64, 4>;
        using ulspan1 = span<u64, 1>;
        using ulspan2 = span<u64, 2>;
        using ulspan3 = span<u64, 3>;
        using ulspan4 = span<u64, 4>;
    }

    inline namespace types
    {
        template <typename T> concept Span = Same<T, span<typename T::Type, T::n>>;

        template <typename T> concept FloatingSpan = Span<T> && Floating<typename T::Type>;
        template <typename T> concept IntegralSpan = Span<T> && Integral<typename T::Type>;
        template <typename T> concept SignedIntegralSpan = Span<T> && SignedIntegral<typename T::Type>;
        template <typename T> concept UnsignedIntegralSpan = Span<T> && UnsignedIntegral<typename T::Type>;
        template <typename T> concept PointerSpan = Span<T> && Pointer<typename T::Type>;

        template <typename T> concept Span1 = Span<T> && T::n == 1;
        template <typename T> concept Span2 = Span<T> && T::n == 2;
        template <typename T> concept Span3 = Span<T> && T::n == 3;
        template <typename T> concept Span4 = Span<T> && T::n == 4;
    }

    template <typename T>
    struct span<T *, 1>
    {
        using Type = T *;
        inline static constexpr u32 n{1u};

        T * min;
        T * max;

        constexpr span() = default;
        constexpr span(T * v1, T * v2);
        constexpr span(std::remove_const_t<T> * v1, std::remove_const_t<T> * v2) requires (std::is_const_v<T>);
        constexpr span(const span<std::remove_const_t<T> *, n> & s) requires (std::is_const_v<T>);

        constexpr span(const span & s) = default;
        constexpr span(span && s) = default;

        span & operator=(const span & s) = default;
        span & operator=(span && s) = default;

        ~span() = default;

        nodisc constexpr explicit operator bool() const;

        nodisc constexpr auto size() const;

        nodisc constexpr bool contains(const T * v) const;

        nodisc constexpr bool operator==(const span &) const = default;
    };

    template <Numeric T>
    struct span<T, 1>
    {
        using Type = T;
        inline static constexpr u32 n{1u};

        SERIALIZABLE(2);

        T min;
        T max;

        constexpr span() = default;
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2> constexpr span(U1 v1, U2 v2);
        template <ExclusiveSubOf<T> U> constexpr span(const span1<U> & s);
        template <Numeric U> requires (!InclusiveSubOf<U, T>) constexpr explicit span(const span1<U> & s);

        constexpr span(const span & s) = default;
        constexpr span(span && s) = default;

        span & operator=(const span & s) = default;
        span & operator=(span && s) = default;

        template <ExclusiveSubOf<T> U> span & operator=(const span1<U> & s);

        ~span() = default;

        nodisc constexpr explicit operator bool() const;

        nodisc constexpr auto size() const;

        nodisc constexpr bool contains(T v) const;

        nodisc constexpr bool operator==(const span &) const = default;
    };

    template <Numeric T>
    struct span<T, 2>
    {
        using Type = T;
        inline static constexpr u32 n{2u};

        SERIALIZABLE(2);

        vec2<T> min;
        vec2<T> max;

        constexpr span() = default;
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2> constexpr span(U1 v1, U2 v2);
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2> constexpr span(const vec2<U1> & v1, U2 v2);
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2> constexpr span(U1 v1, const vec2<U2> & v2);
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2> constexpr span(const vec2<U1> & v1, const vec2<U2> & v2);
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2> constexpr span(const span1<U1> & s1, const span1<U2> & s2);
        template <ExclusiveSubOf<T> U> constexpr span(const span2<U> & s);
        template <Numeric U> requires (!InclusiveSubOf<U, T>) constexpr explicit span(const span2<U> & s);

        constexpr span(const span & s) = default;
        constexpr span(span && s) = default;

        span & operator=(const span & s) = default;
        span & operator=(span && s) = default;

        template <ExclusiveSubOf<T> U> span & operator=(const span2<U> & s);

        ~span() = default;

        nodisc constexpr explicit operator bool() const;

        nodisc constexpr vec2<T> size() const;

        nodisc constexpr bool contains(const vec2<T> & v) const;

        nodisc constexpr span1<T> x() const;
        nodisc constexpr span1<T> y() const;

        nodisc constexpr bool operator==(const span &) const = default;
    };

    template <Numeric T>
    struct span<T, 3>
    {
        using Type = T;
        inline static constexpr u32 n{3u};

        SERIALIZABLE(2);

        vec3<T> min;
        vec3<T> max;

        constexpr span() = default;
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2> constexpr span(U1 v1, U2 v2);
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2> constexpr span(const vec3<U1> & v1, U2 v2);
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2> constexpr span(U1 v1, const vec3<U2> & v2);
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2> constexpr span(const vec3<U1> & v1, const vec3<U2> & v2);
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2, InclusiveSubOf<T> U3> constexpr span(const span1<U1> & s1, const span1<U2> & s2, const span1<U3> & s3);
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2> constexpr span(const span2<U1> & s1, const span1<U2> & s2);
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2> constexpr span(const span1<U1> & s1, const span2<U2> & s2);
        template <ExclusiveSubOf<T> U> constexpr span(const span3<U> & s);
        template <Numeric U> requires (!InclusiveSubOf<U, T>) constexpr explicit span(const span3<U> & s);

        constexpr span(const span & s) = default;
        constexpr span(span && s) = default;

        span & operator=(const span & s) = default;
        span & operator=(span && s) = default;

        template <ExclusiveSubOf<T> U> span & operator=(const span3<U> & s);

        ~span() = default;

        nodisc constexpr explicit operator bool() const;

        nodisc constexpr vec3<T> size() const;

        nodisc constexpr bool contains(const vec3<T> & v) const;

        nodisc constexpr span1<T> x() const;
        nodisc constexpr span1<T> y() const;
        nodisc constexpr span1<T> z() const;

        nodisc constexpr span2<T> xy() const;
        nodisc constexpr span2<T> yz() const;

        nodisc constexpr bool operator==(const span &) const = default;
    };

    template <Numeric T>
    struct span<T, 4>
    {
        using Type = T;
        inline static constexpr u32 n{4u};

        SERIALIZABLE(2);

        vec4<T> min;
        vec4<T> max;

        constexpr span() = default;
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2> constexpr span(U1 v1, U2 v2);
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2> constexpr span(const vec4<U1> & v1, U2 v2);
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2> constexpr span(U1 v1, const vec4<U2> & v2);
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2> constexpr span(const vec4<U1> & v1, const vec4<U2> & v2);
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2, InclusiveSubOf<T> U3, InclusiveSubOf<T> U4> constexpr span(const span1<U1> & s1, const span1<U2> & s2, const span1<U3> & s3, const span1<U4> & s4);
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2, InclusiveSubOf<T> U3> constexpr span(const span2<U1> & s1, const span1<U2> & s2, const span1<U3> & s3);
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2, InclusiveSubOf<T> U3> constexpr span(const span1<U1> & s1, const span2<U2> & s2, const span1<U3> & s3);
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2, InclusiveSubOf<T> U3> constexpr span(const span1<U1> & s1, const span1<U2> & s2, const span2<U3> & s3);
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2> constexpr span(const span2<U1> & s1, const span2<U2> & s2);
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2> constexpr span(const span3<U1> & s1, const span1<U2> & s2);
        template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2> constexpr span(const span1<U1> & s1, const span3<U2> & s2);
        template <ExclusiveSubOf<T> U> constexpr span(const span4<U> & s);
        template <Numeric U> requires (!InclusiveSubOf<U, T>) constexpr explicit span(const span4<U> & s);

        constexpr span(const span & s) = default;
        constexpr span(span && s) = default;

        span & operator=(const span & s) = default;
        span & operator=(span && s) = default;

        template <ExclusiveSubOf<T> U> span & operator=(const span4<U> & s);

        ~span() = default;

        nodisc constexpr explicit operator bool() const;

        nodisc constexpr vec4<T> size() const;

        nodisc constexpr bool contains(const vec4<T> & v) const;

        nodisc constexpr span1<T> x() const;
        nodisc constexpr span1<T> y() const;
        nodisc constexpr span1<T> z() const;
        nodisc constexpr span1<T> w() const;

        nodisc constexpr span2<T> xy() const;
        nodisc constexpr span2<T> yz() const;
        nodisc constexpr span2<T> zw() const;

        nodisc constexpr span3<T> xyz() const;
        nodisc constexpr span3<T> yzw() const;

        nodisc constexpr bool operator==(const span &) const = default;
    };

    MSVC_WARNING_SUPPRESS(4146)
    template <Numeric T, u32 n> inline constexpr span<T, n> fullSpan{Floating<T> ? T(-std::numeric_limits<T>::infinity()) : std::numeric_limits<T>::min(), Floating<T> ? std::numeric_limits<T>::infinity() : std::numeric_limits<T>::max()};
    template <Numeric T> inline constexpr span1<T> fullSpan1{fullSpan<T, 1>};
    template <Numeric T> inline constexpr span2<T> fullSpan2{fullSpan<T, 2>};
    template <Numeric T> inline constexpr span3<T> fullSpan3{fullSpan<T, 3>};
    template <Numeric T> inline constexpr span4<T> fullSpan4{fullSpan<T, 4>};

    template <Numeric T, u32 n> inline constexpr span<T, n> nullSpan{fullSpan<T, n>.max, fullSpan<T, n>.min};
    template <Numeric T> inline constexpr span1<T> nullSpan1{nullSpan<T, 1>};
    template <Numeric T> inline constexpr span2<T> nullSpan2{nullSpan<T, 2>};
    template <Numeric T> inline constexpr span3<T> nullSpan3{nullSpan<T, 3>};
    template <Numeric T> inline constexpr span4<T> nullSpan4{nullSpan<T, 4>};

    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n> span<T1, n> & operator+=(span<T1, n> & s, T2 v);
    template <Pointer T, u32 n> span<T, n> & operator+=(span<T, n> & s, s64 v);
    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n> span<T1, n> & operator+=(span<T1, n> & s, const vec<T2, n> & v);

    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n> span<T1, n> & operator-=(span<T1, n> & s, T2 v);
    template <Pointer T, u32 n> span<T, n> & operator-=(span<T, n> & s, s64 v);
    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n> span<T1, n> & operator-=(span<T1, n> & s, const vec<T2, n> & v);

    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n> span<T1, n> & operator*=(span<T1, n> & s, T2 v);
    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n> span<T1, n> & operator*=(span<T1, n> & s, const vec<T2, n> & v);

    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n> span<T1, n> & operator/=(span<T1, n> & s, T2 v);
    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n> span<T1, n> & operator/=(span<T1, n> & s, const vec<T2, n> & v);

    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n> span<T1, n> & operator&=(span<T1, n> & s1, const span<T2, n> & s2);

    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n> span<T1, n> & operator|=(span<T1, n> & s1, const span<T2, n> & s2);

    template <Numeric T1, Numeric T2, u32 n> nodisc constexpr span<Common<T1, T2>, n> operator+(const span<T1, n> & s, T2 v);
    template <Pointer T, u32 n> nodisc constexpr span<T, n> operator+(const span<T, n> & s, s64 v);
    template <Numeric T1, Numeric T2, u32 n> nodisc constexpr span<Common<T1, T2>, n> operator+(T1 v, const span<T2, n> & s);
    template <Numeric T1, Numeric T2, u32 n> nodisc constexpr span<Common<T1, T2>, n> operator+(const span<T1, n> & s, const vec<T2, n> & v);
    template <Numeric T1, Numeric T2, u32 n> nodisc constexpr span<Common<T1, T2>, n> operator+(const vec<T1, n> & v, const span<T2, n> & s);

    template <Numeric T1, Numeric T2, u32 n> nodisc constexpr span<Common<T1, T2>, n> operator-(const span<T1, n> & s, T2 v);
    template <Pointer T, u32 n> nodisc constexpr span<T, n> operator-(const span<T, n> & s, s64 v);
    template <Numeric T1, Numeric T2, u32 n> nodisc constexpr span<Common<T1, T2>, n> operator-(T1 v1, const span<T2, n> & s);
    template <Numeric T1, Numeric T2, u32 n> nodisc constexpr span<Common<T1, T2>, n> operator-(const span<T1, n> & s, const vec<T2, n> & v);
    template <Numeric T1, Numeric T2, u32 n> nodisc constexpr span<Common<T1, T2>, n> operator-(const vec<T1, n> & v, const span<T2, n> & s);

    template <Numeric T1, Numeric T2, u32 n> nodisc constexpr span<Common<T1, T2>, n> operator*(const span<T1, n> & s, T2 v);
    template <Numeric T1, Numeric T2, u32 n> nodisc constexpr span<Common<T1, T2>, n> operator*(T1 v, const span<T2, n> & s);
    template <Numeric T1, Numeric T2, u32 n> nodisc constexpr span<Common<T1, T2>, n> operator*(const span<T1, n> & s, const vec<T2, n> & v);
    template <Numeric T1, Numeric T2, u32 n> nodisc constexpr span<Common<T1, T2>, n> operator*(const vec<T1, n> & v, const span<T2, n> & s);

    template <Numeric T1, Numeric T2, u32 n> nodisc constexpr span<Common<T1, T2>, n> operator/(const span<T1, n> & s, T2 v);
    template <Numeric T1, Numeric T2, u32 n> nodisc constexpr span<Common<T1, T2>, n> operator/(const span<T1, n> & s, const vec<T2, n> & v);

    template <Numeric T1, Numeric T2, u32 n> nodisc constexpr span<Common<T1, T2>, n> operator&(const span<T1, n> & s1, const span<T2, n> & s2);

    template <Numeric T1, Numeric T2, u32 n> nodisc constexpr span<Common<T1, T2>, n> operator|(const span<T1, n> & s1, const span<T2, n> & s2);

    template <Numeric T1, Numeric T2, u32 n> nodisc constexpr span<Common<T1, T2>, n> min(const span<T1, n> & s1, T2 v);
    template <typename T, u32 n> nodisc constexpr span<T *, n> min(const span<T *, n> & s1, T * v);
    template <Numeric T1, Numeric T2, u32 n> nodisc constexpr span<Common<T1, T2>, n> min(const span<T1, n> & s, const vec<T2, n> & v);

    template <Numeric T1, Numeric T2, u32 n> nodisc constexpr span<Common<T1, T2>, n> max(const span<T1, n> & s1, T2 v);
    template <typename T, u32 n> nodisc constexpr span<T *, n> max(const span<T *, n> & s1, T * v);
    template <Numeric T1, Numeric T2, u32 n> nodisc constexpr span<Common<T1, T2>, n> max(const span<T1, n> & s, const vec<T2, n> & v);

    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n> span<T1, n> & minify(span<T1, n> & s, T2 v);
    template <typename T, u32 n> span<T *, n> & minify(span<T *, n> & s, T * v);
    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n> span<T1, n> & minify(span<T1, n> & s, const vec<T2, n> & v);

    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n> span<T1, n> & maxify(span<T1, n> & s, T2 v);
    template <typename T, u32 n> span<T *, n> & maxify(span<T *, n> & s, T * v);
    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n> span<T1, n> & maxify(span<T1, n> & s, const vec<T2, n> & v);

    template <NumericOrPointer T, u32 n> nodisc constexpr span<T, n> clamp(const span<T, n> & s, T min, T max);
    template <Numeric T, u32 n> nodisc constexpr span<T, n> clamp(const span<T, n> & s, const vec<T, n> & min, const vec<T, n> & max);
    template <NumericOrPointer T> nodisc constexpr T clamp(T v, const span1<T> & span);
    template <Numeric T, u32 n> nodisc constexpr vec<T, n> clamp(const vec<T, n> & v, const span<T, n> & s);

    template <NumericOrPointer T, u32 n> span<T, n> & clampify(span<T, n> & s, T min, T max);
    template <Numeric T, u32 n> span<T, n> & clampify(span<T, n> & s, const vec<T, n> & min, const vec<T, n> & max);
    template <NumericOrPointer T> T & clampify(T & v, const span1<T> & span);
    template <Numeric T, u32 n> vec<T, n> & clampify(vec<T, n> & v, const span<T, n> & s);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{

    template <typename T>
    finline constexpr span<T *, 1>::span(T * const v1, T * const v2) :
        min{v1},
        max{v2}
    {}

    template <typename T>
    finline constexpr span<T *, 1>::span(std::remove_const_t<T> * const v1, std::remove_const_t<T> * const v2) requires (std::is_const_v<T>) :
        min{v1},
        max{v2}
    {}

    template <typename T>
    finline constexpr span<T *, 1>::span(const span<std::remove_const_t<T> *, n> & s) requires (std::is_const_v<T>) :
        min{s.min},
        max{s.max}
    {}

    template <typename T>
    finline constexpr span<T *, 1>::operator bool() const
    {
        return bool(min) || bool(max);
    }

    template <typename T>
    finline constexpr auto span<T *, 1>::size() const
    {
        return max - min;
    }

    template <typename T>
    finline constexpr bool span<T *, 1>::contains(const T * const v) const
    {
        return v >= min && v < max;
    }

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2>
    finline constexpr span<T, 1>::span(const U1 v1, const U2 v2) :
        min{v1},
        max{v2}
    {}

    template <Numeric T>
    template <ExclusiveSubOf<T> U>
    finline constexpr span<T, 1>::span(const span1<U> & s) :
        min{s.min},
        max{s.max}
    {}

    template <Numeric T>
    template <Numeric U> requires (!InclusiveSubOf<U, T>)
    finline constexpr span<T, 1>::span(const span1<U> & s) :
        min{T(s.min)},
        max{T(s.max)}
    {}

    template <Numeric T>
    template <ExclusiveSubOf<T> U>
    finline span1<T> & span<T, 1>::operator=(const span1<U> & s)
    {
        min = s.min;
        max = s.max;
        return *this;
    }

    template <Numeric T>
    finline constexpr span<T, 1>::operator bool() const
    {
        return bool(min) || bool(max);
    }

    template <Numeric T>
    finline constexpr auto span<T, 1>::size() const
    {
        return max - min;
    }

    template <Numeric T>
    finline constexpr bool span<T, 1>::contains(const T v) const
    {
        if constexpr (Integral<T>)
        {
            return v >= min && v < max;
        }
        else
        {
            return v >= min && v <= max;
        }
    }

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2>
    finline constexpr span<T, 2>::span(const U1 v1, const U2 v2) :
        min{v1},
        max{v2}
    {}

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2>
    finline constexpr span<T, 2>::span(const vec2<U1> & v1, const U2 v2) :
        min{v1},
        max{v2}
    {}

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2>
    finline constexpr span<T, 2>::span(const U1 v1, const vec2<U2> & v2) :
        min{v1},
        max{v2}
    {}

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2>
    finline constexpr span<T, 2>::span(const vec2<U1> & v1, const vec2<U2> & v2) :
        min{v1},
        max{v2}
    {}

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2>
    finline constexpr span<T, 2>::span(const span1<U1> & s1, const span1<U2> & s2) :
        min{s1.min, s2.min},
        max{s1.max, s2.max}
    {}

    template <Numeric T>
    template <ExclusiveSubOf<T> U>
    finline constexpr span<T, 2>::span(const span2<U> & s) :
        min{s.min},
        max{s.max}
    {}

    template <Numeric T>
    template <Numeric U> requires (!InclusiveSubOf<U, T>)
    finline constexpr span<T, 2>::span(const span2<U> & s) :
        min{s.min},
        max{s.max}
    {}

    template <Numeric T>
    template <ExclusiveSubOf<T> U>
    finline span2<T> & span<T, 2>::operator=(const span2<U> & s)
    {
        min = s.min;
        max = s.max;
        return *this;
    }

    template <Numeric T>
    finline constexpr span<T, 2>::operator bool() const
    {
        return bool(min) || bool(max);
    }

    template <Numeric T>
    finline constexpr vec2<T> span<T, 2>::size() const
    {
        return max - min;
    }

    template <Numeric T>
    inline constexpr bool span<T, 2>::contains(const vec2<T> & v) const
    {
        const bool inMin{v.x >= min.x && v.y >= min.y};

        if constexpr (Integral<T>)
        {
            return inMin && v.x < max.x && v.y < max.y;
        }
        else
        {
            return inMin && v.x <= max.x && v.y <= max.y;
        }
    }

    template <Numeric T>
    finline constexpr span1<T> span<T, 2>::x() const
    {
        return {min.x, max.x};
    }

    template <Numeric T>
    finline constexpr span1<T> span<T, 2>::y() const
    {
        return {min.y, max.y};
    }

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2>
    finline constexpr span<T, 3>::span(const U1 v1, const U2 v2) :
        min{v1},
        max{v2}
    {}

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2>
    finline constexpr span<T, 3>::span(const vec3<U1> & v1, const U2 v2) :
        min{v1},
        max{v2}
    {}

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2>
    finline constexpr span<T, 3>::span(const U1 v1, const vec3<U2> & v2) :
        min{v1},
        max{v2}
    {}

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2>
    finline constexpr span<T, 3>::span(const vec3<U1> & v1, const vec3<U2> & v2) :
        min{v1},
        max{v2}
    {}

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2, InclusiveSubOf<T> U3>
    finline constexpr span<T, 3>::span(const span1<U1> & s1, const span1<U2> & s2, const span1<U3> & s3) :
        min(s1.min, s2.min, s3.min),
        max(s1.max, s2.max, s3.max)
    {}

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2>
    finline constexpr span<T, 3>::span(const span2<U1> & s1, const span1<U2> & s2) :
        min(s1.min, s2.min),
        max(s1.max, s2.max)
    {}

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2>
    finline constexpr span<T, 3>::span(const span1<U1> & s1, const span2<U2> & s2) :
        min(s1.min, s2.min),
        max(s1.max, s2.max)
    {}

    template <Numeric T>
    template <ExclusiveSubOf<T> U>
    finline constexpr span<T, 3>::span(const span3<U> & s) :
        min{s.min},
        max{s.max}
    {}

    template <Numeric T>
    template <Numeric U> requires (!InclusiveSubOf<U, T>)
    finline constexpr span<T, 3>::span(const span3<U> & s) :
        min{s.min},
        max{s.max}
    {}

    template <Numeric T>
    template <ExclusiveSubOf<T> U>
    finline span3<T> & span<T, 3>::operator=(const span3<U> & s)
    {
        min = s.min;
        max = s.max;
        return *this;
    }

    template <Numeric T>
    finline constexpr span<T, 3>::operator bool() const
    {
        return bool(min) || bool(max);
    }

    template <Numeric T>
    finline constexpr vec3<T> span<T, 3>::size() const
    {
        return max - min;
    }

    template <Numeric T>
    inline constexpr bool span<T, 3>::contains(const vec3<T> & v) const
    {
        const bool inMin{v.x >= min.x && v.y >= min.y && v.z >= min.z};

        if constexpr (Integral<T>)
        {
            return inMin && v.x < max.x && v.y < max.y && v.z < max.z;
        }
        else
        {
            return inMin && v.x <= max.x && v.y <= max.y && v.z <= max.z;
        }
    }

    template <Numeric T>
    finline constexpr span1<T> span<T, 3>::x() const
    {
        return {min.x, max.x};
    }

    template <Numeric T>
    finline constexpr span1<T> span<T, 3>::y() const
    {
        return {min.y, max.y};
    }

    template <Numeric T>
    finline constexpr span1<T> span<T, 3>::z() const
    {
        return {min.z, max.z};
    }

    template <Numeric T>
    finline constexpr span2<T> span<T, 3>::xy() const
    {
        return {min.xy(), max.xy()};
    }

    template <Numeric T>
    finline constexpr span2<T> span<T, 3>::yz() const
    {
        return {min.yz(), max.yz()};
    }

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2>
    finline constexpr span<T, 4>::span(const U1 v1, const U2 v2) :
        min{v1},
        max{v2}
    {}

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2>
    finline constexpr span<T, 4>::span(const vec4<U1> & v1, const U2 v2) :
        min{v1},
        max{v2}
    {}

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2>
    finline constexpr span<T, 4>::span(const U1 v1, const vec4<U2> & v2) :
        min{v1},
        max{v2}
    {}

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2>
    finline constexpr span<T, 4>::span(const vec4<U1> & v1, const vec4<U2> & v2) :
        min{v1},
        max{v2}
    {}

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2, InclusiveSubOf<T> U3, InclusiveSubOf<T> U4>
    finline constexpr span<T, 4>::span(const span1<U1> & s1, const span1<U2> & s2, const span1<U3> & s3, const span1<U4> & s4) :
        min{s1.min, s2.min, s3.min, s4.min},
        max{s1.max, s2.max, s3.max, s4.max}
    {}

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2, InclusiveSubOf<T> U3>
    finline constexpr span<T, 4>::span(const span2<U1> & s1, const span1<U2> & s2, const span1<U3> & s3) :
        min{s1.min, s2.min, s3.min},
        max{s1.max, s2.max, s3.max}
    {}

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2, InclusiveSubOf<T> U3>
    finline constexpr span<T, 4>::span(const span1<U1> & s1, const span2<U2> & s2, const span1<U3> & s3) :
        min{s1.min, s2.min, s3.min},
        max{s1.max, s2.max, s3.max}
    {}

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2, InclusiveSubOf<T> U3>
    finline constexpr span<T, 4>::span(const span1<U1> & s1, const span1<U2> & s2, const span2<U3> & s3) :
        min{s1.min, s2.min, s3.min},
        max{s1.max, s2.max, s3.max}
    {}

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2>
    finline constexpr span<T, 4>::span(const span2<U1> & s1, const span2<U2> & s2) :
        min{s1.min, s2.min},
        max{s1.max, s2.max}
    {}

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2>
    finline constexpr span<T, 4>::span(const span3<U1> & s1, const span1<U2> & s2) :
        min{s1.min, s2.min},
        max{s1.max, s2.max}
    {}

    template <Numeric T>
    template <InclusiveSubOf<T> U1, InclusiveSubOf<T> U2>
    finline constexpr span<T, 4>::span(const span1<U1> & s1, const span3<U2> & s2) :
        min{s1.min, s2.min},
        max{s1.max, s2.max}
    {}

    template <Numeric T>
    template <ExclusiveSubOf<T> U>
    finline constexpr span<T, 4>::span(const span4<U> & s) :
        min{s.min},
        max{s.max}
    {}

    template <Numeric T>
    template <Numeric U> requires (!InclusiveSubOf<U, T>)
    finline constexpr span<T, 4>::span(const span4<U> & s) :
        min{s.min},
        max{s.max}
    {}

    template <Numeric T>
    template <ExclusiveSubOf<T> U>
    finline span4<T> & span<T, 4>::operator=(const span4<U> & s)
    {
        min = s.min;
        max = s.max;
        return *this;
    }

    template <Numeric T>
    finline constexpr span<T, 4>::operator bool() const
    {
        return bool(min) || bool(max);
    }

    template <Numeric T>
    finline constexpr vec4<T> span<T, 4>::size() const
    {
        return max - min;
    }

    template <Numeric T>
    inline constexpr bool span<T, 4>::contains(const vec4<T> & v) const
    {
        const bool inMin{v.x >= min.x && v.y >= min.y && v.z >= min.z && v.w >= min.w};

        if constexpr (Integral<T>)
        {
            return inMin && v.x < max.x && v.y < max.y && v.z < max.z && v.w < max.w;
        }
        else
        {
            return inMin && v.x <= max.x && v.y <= max.y && v.z <= max.z && v.w <= max.w;
        }
    }

    template <Numeric T>
    finline constexpr span1<T> span<T, 4>::x() const
    {
        return {min.x, max.x};
    }

    template <Numeric T>
    finline constexpr span1<T> span<T, 4>::y() const
    {
        return {min.y, max.y};
    }

    template <Numeric T>
    finline constexpr span1<T> span<T, 4>::z() const
    {
        return {min.z, max.z};
    }

    template <Numeric T>
    finline constexpr span1<T> span<T, 4>::w() const
    {
        return {min.w, max.w};
    }

    template <Numeric T>
    finline constexpr span2<T> span<T, 4>::xy() const
    {
        return {min.xy(), max.xy()};
    }

    template <Numeric T>
    finline constexpr span2<T> span<T, 4>::yz() const
    {
        return {min.yz(), max.yz()};
    }

    template <Numeric T>
    finline constexpr span2<T> span<T, 4>::zw() const
    {
        return {min.zw(), max.zw()};
    }

    template <Numeric T>
    finline constexpr span3<T> span<T, 4>::xyz() const
    {
        return {min.xyz(), max.xyz()};
    }

    template <Numeric T>
    finline constexpr span3<T> span<T, 4>::yzw() const
    {
        return {min.yzw(), max.yzw()};
    }

    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n>
    finline span<T1, n> & operator+=(span<T1, n> & s, const T2 v)
    {
        s.min += v;
        s.max += v;
        return s;
    }

    template <Pointer T, u32 n>
    finline span<T, n> & operator+=(span<T, n> & s, const s64 v)
    {
        s.min += v;
        s.max += v;
        return s;
    }

    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n>
    finline span<T1, n> & operator+=(span<T1, n> & s, const vec<T2, n> & v)
    {
        s.min += v;
        s.max += v;
        return s;
    }

    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n>
    finline span<T1, n> & operator-=(span<T1, n> & s, const T2 v)
    {
        s.min -= v;
        s.max -= v;
        return s;
    }

    template <Pointer T, u32 n>
    finline span<T, n> & operator-=(span<T, n> & s, const s64 v)
    {
        s.min -= v;
        s.max -= v;
        return s;
    }

    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n>
    finline span<T1, n> & operator-=(span<T1, n> & s, const vec<T2, n> & v)
    {
        s.min -= v;
        s.max -= v;
        return s;
    }

    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n>
    finline span<T1, n> & operator*=(span<T1, n> & s, const T2 v)
    {
        s.min *= v;
        s.max *= v;
        return s;
    }

    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n>
    finline span<T1, n> & operator*=(span<T1, n> & s, const vec<T2, n> & v)
    {
        s.min *= v;
        s.max *= v;
        return s;
    }

    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n>
    finline span<T1, n> & operator/=(span<T1, n> & s, const T2 v)
    {
        if constexpr (Floating<T1>)
        {
            return s *= T2(1.0) / v;
        }
        else
        {
            s.min /= v;
            s.max /= v;
            return s;
        }
    }

    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n>
    finline span<T1, n> & operator/=(span<T1, n> & s, const vec<T2, n> & v)
    {
        if constexpr (Floating<T1>)
        {
            return s *= T2(1.0) / v;
        }
        else
        {
            s.min /= v;
            s.max /= v;
            return s;
        }
    }

    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n>
    finline span<T1, n> & operator&=(span<T1, n> & s1, const span<T2, n> & s2)
    {
        maxify(s1.min, s2.min);
        minify(s1.max, s2.max);
        return s1;
    }

    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n>
    finline span<T1, n> & operator|=(span<T1, n> & s1, const span<T2, n> & s2)
    {
        minify(s1.min, s2.min);
        maxify(s1.max, s2.max);
        return s1;
    }

    template <Numeric T1, Numeric T2, u32 n>
    finline constexpr span<Common<T1, T2>, n> operator+(const span<T1, n> & s, const T2 v)
    {
        using T = Common<T1, T2>;
        if constexpr (n == 1)
        {
            return {T(T(s.min) + T(v)), T(T(s.max) + T(v))};
        }
        else
        {
            return {s.min + v, s.max + v};
        }
    }

    template <Pointer T, u32 n>
    finline constexpr span<T, n> operator+(const span<T, n> & s, const s64 v)
    {
        return {s.min + v, s.max + v};
    }

    template <Numeric T1, Numeric T2, u32 n>
    finline constexpr span<Common<T1, T2>, n> operator+(const T1 v, const span<T2, n> & s)
    {
        using T = Common<T1, T2>;
        if constexpr (n == 1)
        {
            return {T(T(v) + T(s.min)), T(T(v) + T(s.max))};
        }
        else
        {
            return {v + s.min, v + s.max};
        }
    }

    template <Numeric T1, Numeric T2, u32 n>
    finline constexpr span<Common<T1, T2>, n> operator+(const span<T1, n> & s, const vec<T2, n> & v)
    {
        return {s.min + v, s.max + v};
    }

    template <Numeric T1, Numeric T2, u32 n>
    finline constexpr span<Common<T1, T2>, n> operator+(const vec<T1, n> & v, const span<T2, n> & s)
    {
        return {v + s.min, v + s.max};
    }

    template <Numeric T1, Numeric T2, u32 n>
    finline constexpr span<Common<T1, T2>, n> operator-(const span<T1, n> & s, const T2 v)
    {
        using T = Common<T1, T2>;
        if constexpr (n == 1)
        {
            return {T(T(s.min) - T(v)), T(T(s.max) - T(v))};
        }
        else
        {
            return {s.min - v, s.max - v};
        }
    }

    template <Pointer T, u32 n>
    finline constexpr span<T, n> operator-(const span<T, n> & s, const s64 v)
    {
        if constexpr (n == 1)
        {
            return {T(T(s.min) - T(v)), T(T(s.max) - T(v))};
        }
        else
        {
            return {s.min - v, s.max - v};
        }
    }

    template <Numeric T1, Numeric T2, u32 n>
    finline constexpr span<Common<T1, T2>, n> operator-(const T1 v, const span<T2, n> & s)
    {
        using T = Common<T1, T2>;
        if constexpr (n == 1)
        {
            return {T(T(v) - T(s.min)), T(T(v) - T(s.max))};
        }
        else
        {
            return {v - s.min, v - s.max};
        }
    }

    template <Numeric T1, Numeric T2, u32 n>
    finline constexpr span<Common<T1, T2>, n> operator-(const span<T1, n> & s, const vec<T2, n> & v)
    {
        return {s.min - v, s.max - v};
    }

    template <Numeric T1, Numeric T2, u32 n>
    finline constexpr span<Common<T1, T2>, n> operator-(const vec<T1, n> & v, const span<T2, n> & s)
    {
        return {v - s.min, v - s.max};
    }

    template <Numeric T1, Numeric T2, u32 n>
    finline constexpr span<Common<T1, T2>, n> operator*(const span<T1, n> & s, const T2 v)
    {
        using T = Common<T1, T2>;
        if constexpr (n == 1)
        {
            return {T(T(s.min) * T(v)), T(T(s.max) * T(v))};
        }
        else
        {
            return {s.min * v, s.max * v};
        }
    }

    template <Numeric T1, Numeric T2, u32 n>
    finline constexpr span<Common<T1, T2>, n> operator*(const T1 v, const span<T2, n> & s)
    {
        using T = Common<T1, T2>;
        if constexpr (n == 1)
        {
            return {T(T(v) * T(s.min)), T(T(v) * T(s.max))};
        }
        else
        {
            return {v * s.min, v * s.max};
        }
    }

    template <Numeric T1, Numeric T2, u32 n>
    finline constexpr span<Common<T1, T2>, n> operator*(const span<T1, n> & s, const vec<T2, n> & v)
    {
        return {s.min * v, s.max * v};
    }

    template <Numeric T1, Numeric T2, u32 n>
    finline constexpr span<Common<T1, T2>, n> operator*(const vec<T1, n> & v, const span<T2, n> & s)
    {
        return {v * s.min, v * s.max};
    }

    template <Numeric T1, Numeric T2, u32 n>
    finline constexpr span<Common<T1, T2>, n> operator/(const span<T1, n> & s, const T2 v)
    {
        using T = Common<T1, T2>;
        if constexpr (Floating<T1>)
        {
            return s * (T2(1.0) / v);
        }
        else
        {
            if constexpr (n == 1)
            {
                return {T(T(s.min) / T(v)), T(T(s.max) / T(v))};
            }
            else
            {
                return {s.min / v, s.max / v};
            }
        }
    }

    template <Numeric T1, Numeric T2, u32 n>
    finline constexpr span<Common<T1, T2>, n> operator/(const span<T1, n> & s, const vec<T2, n> & v)
    {
        if constexpr (Floating<T1>)
        {
            return s * (T2(1.0) / v);
        }
        else
        {
            return {s.min / v, s.max / v};
        }
    }

    template <Numeric T1, Numeric T2, u32 n>
    finline constexpr span<Common<T1, T2>, n> operator&(const span<T1, n> & s1, const span<T2, n> & s2)
    {
        return {max(s1.min, s2.min), min(s1.max, s2.max)};
    }

    template <Numeric T1, Numeric T2, u32 n>
    finline constexpr span<Common<T1, T2>, n> operator|(const span<T1, n> & s1, const span<T2, n> & s2)
    {
        return {min(s1.min, s2.min), max(s1.max, s2.max)};
    }

    template <Numeric T1, Numeric T2, u32 n>
    finline constexpr span<Common<T1, T2>, n> min(const span<T1, n> & s, const T2 v)
    {
        return {min(s.min, v), min(s.max, v)};
    }

    template <typename T, u32 n>
    finline constexpr span<T *, n> min(const span<T *, n> & s, T * const v)
    {
        return {min(s.min, v), min(s.max, v)};
    }

    template <Numeric T1, Numeric T2, u32 n>
    finline constexpr span<Common<T1, T2>, n> min(const span<T1, n> & s, const vec<T2, n> & v)
    {
        return {min(s.min, v), min(s.max, v)};
    }

    template <Numeric T1, Numeric T2, u32 n>
    finline constexpr span<Common<T1, T2>, n> max(const span<T1, n> & s, const T2 v)
    {
        return {max(s.min, v), max(s.max, v)};
    }

    template <typename T, u32 n>
    finline constexpr span<T *, n> max(const span<T *, n> & s, T * const v)
    {
        return {max(s.min, v), max(s.max, v)};
    }

    template <Numeric T1, Numeric T2, u32 n>
    finline constexpr span<Common<T1, T2>, n> max(const span<T1, n> & s, const vec<T2, n> & v)
    {
        return {max(s.min, v), max(s.max, v)};
    }

    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n>
    finline span<T1, n> & minify(span<T1, n> & s, const T2 v)
    {
        minify(s.min, v);
        minify(s.max, v);
        return s;
    }

    template <typename T, u32 n>
    finline span<T *, n> & minify(span<T *, n> & s, T * const v)
    {
        minify(s.min, v);
        minify(s.max, v);
        return s;
    }

    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n>
    finline span<T1, n> & minify(span<T1, n> & s, const vec<T2, n> & v)
    {
        minify(s.min, v);
        minify(s.max, v);
        return s;
    }

    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n>
    finline span<T1, n> & maxify(span<T1, n> & s, const T2 v)
    {
        maxify(s.min, v);
        maxify(s.max, v);
        return s;
    }

    template <typename T, u32 n>
    finline span<T *, n> & maxify(span<T *, n> & s, T * const v)
    {
        maxify(s.min, v);
        maxify(s.max, v);
        return s;
    }

    template <Numeric T1, InclusiveSubOf<T1> T2, u32 n>
    finline span<T1, n> & maxify(span<T1, n> & s, const vec<T2, n> & v)
    {
        maxify(s.min, v);
        maxify(s.max, v);
        return s;
    }

    template <NumericOrPointer T, u32 n>
    finline constexpr span<T, n> clamp(const span<T, n> & s, const T min, const T max)
    {
        return {clamp(s.min, min, max), clamp(s.max, min, max)};
    }

    template <Numeric T, u32 n>
    finline constexpr span<T, n> clamp(const span<T, n> & s, const vec<T, n> & min, const vec<T, n> & max)
    {
        return {clamp(s.min, min, max), clamp(s.max, min, max)};
    }

    template <NumericOrPointer T>
    finline constexpr T clamp(const T v, const span1<T> & s)
    {
        return clamp(v, s.min, s.max);
    }

    template <Numeric T, u32 n>
    finline constexpr vec<T, n> clamp(const vec<T, n> & v, const span<T, n> & s)
    {
        return clamp(v, s.min, s.max);
    }

    template <NumericOrPointer T, u32 n>
    finline span<T, n> & clampify(span<T, n> & s, const T min, const T max)
    {
        clampify(s.min, min, max);
        clampify(s.max, min, max);
        return s;
    }

    template <Numeric T, u32 n>
    finline span<T, n> & clampify(span<T, n> & s, const vec<T, n> & min, const vec<T, n> & max)
    {
        clampify(s.min, min, max);
        clampify(s.max, min, max);
        return s;
    }

    template <NumericOrPointer T>
    finline T & clampify(T & v, const span1<T> & s)
    {
        return clampify(v, s.min, s.max);
    }

    template <Numeric T, u32 n>
    finline vec<T, n> & clampify(vec<T, n> & v, const span<T, n> & s)
    {
        return clampify(v, s.min, s.max);
    }
}
