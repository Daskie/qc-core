#pragma once

#include <qc-core/vector.hpp>

namespace qc
{
    template <typename T, int n> struct span;

    inline namespace types
    {
        using qc::span;

        template <NumericOrPointer T> using span1 = span<T, 1>;
        template <Numeric T> using span2 = span<T, 2>;
        template <Numeric T> using span3 = span<T, 3>;
        template <Numeric T> using span4 = span<T, 4>;

        template <int n> using  fspan = span<f32, n>;
        template <int n> using  dspan = span<f64, n>;
        template <int n> using  cspan = span< s8, n>;
        template <int n> using ucspan = span< u8, n>;
        template <int n> using  sspan = span<s16, n>;
        template <int n> using usspan = span<u16, n>;
        template <int n> using  ispan = span<s32, n>;
        template <int n> using uispan = span<u32, n>;
        template <int n> using  lspan = span<s64, n>;
        template <int n> using ulspan = span<u64, n>;

        using  fspan1 = span1<f32>;
        using  fspan2 = span2<f32>;
        using  fspan3 = span3<f32>;
        using  fspan4 = span4<f32>;
        using  dspan1 = span1<f64>;
        using  dspan2 = span2<f64>;
        using  dspan3 = span3<f64>;
        using  dspan4 = span4<f64>;
        using  cspan1 = span1<s8>;
        using  cspan2 = span2<s8>;
        using  cspan3 = span3<s8>;
        using  cspan4 = span4<s8>;
        using ucspan1 = span1<u8>;
        using ucspan2 = span2<u8>;
        using ucspan3 = span3<u8>;
        using ucspan4 = span4<u8>;
        using  sspan1 = span1<s16>;
        using  sspan2 = span2<s16>;
        using  sspan3 = span3<s16>;
        using  sspan4 = span4<s16>;
        using usspan1 = span1<u16>;
        using usspan2 = span2<u16>;
        using usspan3 = span3<u16>;
        using usspan4 = span4<u16>;
        using  ispan1 = span1<s32>;
        using  ispan2 = span2<s32>;
        using  ispan3 = span3<s32>;
        using  ispan4 = span4<s32>;
        using uispan1 = span1<u32>;
        using uispan2 = span2<u32>;
        using uispan3 = span3<u32>;
        using uispan4 = span4<u32>;
        using  lspan1 = span1<s64>;
        using  lspan2 = span2<s64>;
        using  lspan3 = span3<s64>;
        using  lspan4 = span4<s64>;
        using ulspan1 = span1<u64>;
        using ulspan2 = span2<u64>;
        using ulspan3 = span3<u64>;
        using ulspan4 = span4<u64>;
    }

    template <NumericOrPointer T>
    struct span<T, 1>
    {
        T min;
        T max;

        constexpr span() noexcept = default;
        template <NumericOrPointer U> constexpr explicit span(const span1<U> & s) noexcept;
        template <Numeric U, int m> constexpr explicit span(const span<U, m> & s) noexcept;
        constexpr span(T v1, T v2) noexcept;

        constexpr span(const span & s) noexcept = default;
        constexpr span(span && s) noexcept = default;

        span & operator=(const span & s) noexcept = default;
        span & operator=(span && s) noexcept = default;

        ~span() noexcept = default;

        constexpr auto size() const noexcept;

        constexpr bool contains(T v) const noexcept;
    };

    template <Numeric T>
    struct span<T, 2>
    {
        vec2<T> min;
        vec2<T> max;

        constexpr span() noexcept = default;
        template <Numeric U, int m> constexpr explicit span(const span<U, m> & s) noexcept;
        constexpr span(T v1, T v2) noexcept;
        constexpr span(vec2<T> v1, vec2<T> v2) noexcept;
        constexpr span(const span1<T> & s1, const span1<T> & s2) noexcept;

        constexpr span(const span & s) noexcept = default;
        constexpr span(span && s) noexcept = default;

        span & operator=(const span & s) noexcept = default;
        span & operator=(span && s) noexcept = default;

        ~span() noexcept = default;

        constexpr vec2<T> size() const noexcept;

        constexpr bool contains(const vec2<T> & v) const noexcept;

        constexpr span1<T> x() const noexcept;
        constexpr span1<T> y() const noexcept;
    };

    template <Numeric T>
    struct span<T, 3>
    {
        vec3<T> min;
        vec3<T> max;

        constexpr span() noexcept = default;
        template <Numeric U, int m> constexpr explicit span(const span<U, m> & s) noexcept;
        constexpr span(T v1, T v2) noexcept;
        constexpr span(vec3<T> v1, vec3<T> v2) noexcept;
        constexpr span(const span1<T> & s1, const span1<T> & s2, const span1<T> & s3) noexcept;
        constexpr span(const span2<T> & s1, const span1<T> & s2) noexcept;
        constexpr span(const span1<T> & s1, const span2<T> & s2) noexcept;

        constexpr span(const span & s) noexcept = default;
        constexpr span(span && s) noexcept = default;

        span & operator=(const span & s) noexcept = default;
        span & operator=(span && s) noexcept = default;

        ~span() noexcept = default;

        constexpr vec3<T> size() const noexcept;

        constexpr bool contains(const vec3<T> & v) const noexcept;

        constexpr span1<T> x() const noexcept;
        constexpr span1<T> y() const noexcept;
        constexpr span1<T> z() const noexcept;

        constexpr span2<T> xy() const noexcept;
        constexpr span2<T> yz() const noexcept;
    };

    template <Numeric T>
    struct span<T, 4>
    {
        vec4<T> min;
        vec4<T> max;

        constexpr span() noexcept = default;
        template <Numeric U, int m> constexpr explicit span(const span<U, m> & s) noexcept;
        constexpr span(T v1, T v2) noexcept;
        constexpr span(vec4<T> v1, vec4<T> v2) noexcept;
        constexpr span(const span1<T> & s1, const span1<T> & s2, const span1<T> & s3, const span1<T> & s4) noexcept;
        constexpr span(const span2<T> & s1, const span1<T> & s2, const span1<T> & s3) noexcept;
        constexpr span(const span1<T> & s1, const span2<T> & s2, const span1<T> & s3) noexcept;
        constexpr span(const span1<T> & s1, const span1<T> & s2, const span2<T> & s3) noexcept;
        constexpr span(const span2<T> & s1, const span2<T> & s2) noexcept;
        constexpr span(const span3<T> & s1, const span1<T> & s2) noexcept;
        constexpr span(const span1<T> & s1, const span3<T> & s2) noexcept;

        constexpr span(const span & s) noexcept = default;
        constexpr span(span && s) noexcept = default;

        span & operator=(const span & s) noexcept = default;
        span & operator=(span && s) noexcept = default;

        ~span() noexcept = default;

        constexpr vec4<T> size() const noexcept;

        constexpr bool contains(const vec4<T> & v) const noexcept;

        constexpr span1<T> x() const noexcept;
        constexpr span1<T> y() const noexcept;
        constexpr span1<T> z() const noexcept;
        constexpr span1<T> w() const noexcept;

        constexpr span2<T> xy() const noexcept;
        constexpr span2<T> yz() const noexcept;
        constexpr span2<T> zw() const noexcept;

        constexpr span3<T> xyz() const noexcept;
        constexpr span3<T> yzw() const noexcept;
    };

    namespace _internal
    {
        // Prevents warnings for using a negative sign in a ternary for unsigned types
        template <typename T> struct FullSpanHelper;

        template <Floating T>
        struct FullSpanHelper<T>
        {
            inline static constexpr T minimum{-std::numeric_limits<T>::infinity()};
            inline static constexpr T maximum{+std::numeric_limits<T>::infinity()};
        };

        template <Integral T>
        struct FullSpanHelper<T>
        {
            inline static constexpr T minimum{std::numeric_limits<T>::min()};
            inline static constexpr T maximum{std::numeric_limits<T>::max()};
        };
    }

    template <Numeric T, int n> constexpr span<T, n> fullSpan{_internal::FullSpanHelper<T>::minimum, _internal::FullSpanHelper<T>::maximum};
    template <Numeric T, int n> constexpr span<T, n> nullSpan{fullSpan<T, n>.max, fullSpan<T, n>.min};

    template <NumericOrPointer T, int n> span<T, n> & operator+=(span<T, n> & s, T v);
    template <Numeric          T, int n> span<T, n> & operator+=(span<T, n> & s, const vec<T, n> & v);

    template <NumericOrPointer T, int n> span<T, n> & operator-=(span<T, n> & s, T v2);
    template <Numeric          T, int n> span<T, n> & operator-=(span<T, n> & s, const vec<T, n> & v);

    template <Numeric T, int n> span<T, n> & operator*=(span<T, n> & s, T v);
    template <Numeric T, int n> span<T, n> & operator*=(span<T, n> & s, const vec<T, n> & v);

    template <Numeric T, int n> span<T, n> & operator/=(span<T, n> & s, T v);
    template <Numeric T, int n> span<T, n> & operator/=(span<T, n> & s, const vec<T, n> & v);

    template <Numeric T, int n> span<T, n> & operator&=(span<T, n> & s1, const span<T, n> & s2);

    template <Numeric T, int n> span<T, n> & operator|=(span<T, n> & s1, const span<T, n> & s2);

    template <NumericOrPointer T, int n> constexpr span<T, n> operator+(const span<T, n> & s, T v);
    template <Numeric          T, int n> constexpr span<T, n> operator+(T v, const span<T, n> & s);
    template <Numeric          T, int n> constexpr span<T, n> operator+(const span<T, n> & s, const vec<T, n> & v);
    template <Numeric          T, int n> constexpr span<T, n> operator+(const vec<T, n> & v, const span<T, n> & s);

    template <NumericOrPointer T, int n> constexpr span<T, n> operator-(const span<T, n> & s, T v);
    template <Numeric          T, int n> constexpr span<T, n> operator-(T v1, const span<T, n> & s);
    template <Numeric          T, int n> constexpr span<T, n> operator-(const span<T, n> & s, const vec<T, n> & v);
    template <Numeric          T, int n> constexpr span<T, n> operator-(const vec<T, n> & v, const span<T, n> & s);

    template <Numeric T, int n> constexpr span<T, n> operator*(const span<T, n> & s, T v);
    template <Numeric T, int n> constexpr span<T, n> operator*(T v, const span<T, n> & s);
    template <Numeric T, int n> constexpr span<T, n> operator*(const span<T, n> & s, const vec<T, n> & v);
    template <Numeric T, int n> constexpr span<T, n> operator*(const vec<T, n> & v, const span<T, n> & s);

    template <Numeric T, int n> constexpr span<T, n> operator/(const span<T, n> & s, T v);
    template <Numeric T, int n> constexpr span<T, n> operator/(const span<T, n> & s, const vec<T, n> & v);

    template <NumericOrPointer T, int n> constexpr bool operator==(const span<T, n> & s1, const span<T, n> & s2);

    template <NumericOrPointer T, int n> constexpr bool operator!=(const span<T, n> & s1, const span<T, n> & s2);

    template <Numeric T, int n> constexpr span<T, n> operator&(const span<T, n> & s1, const span<T, n> & s2);

    template <Numeric T, int n> constexpr span<T, n> operator|(const span<T, n> & s1, const span<T, n> & s2);

    template <NumericOrPointer T, int n> constexpr span<T, n> min(const span<T, n> & s1, T v);
    template <Numeric          T, int n> constexpr span<T, n> min(const span<T, n> & s, const vec<T, n> & v);

    template <NumericOrPointer T, int n> constexpr span<T, n> max(const span<T, n> & s, T v);
    template <Numeric          T, int n> constexpr span<T, n> max(const span<T, n> & s, const vec<T, n> & v);

    template <NumericOrPointer T, int n> span<T, n> & minify(span<T, n> & s, T v);
    template <Numeric          T, int n> span<T, n> & minify(span<T, n> & s, const vec<T, n> & v);

    template <NumericOrPointer T, int n> span<T, n> & maxify(span<T, n> & s, T v);
    template <Numeric          T, int n> span<T, n> & maxify(span<T, n> & s, const vec<T, n> & v);

    template <NumericOrPointer T, int n> constexpr span<T, n> clamp(const span<T, n> & s, T min, T max);
    template <Numeric T, int n> constexpr span<T, n> clamp(const span<T, n> & s, const vec<T, n> & min, const vec<T, n> & max);
    template <NumericOrPointer T> constexpr T clamp(T v, const span1<T> & span);
    template <Numeric T, int n> constexpr vec<T, n> clamp(const vec<T, n> & v, const span<T, n> & s);

    template <NumericOrPointer T, int n> span<T, n> & clampify(span<T, n> & s, T min, T max);
    template <Numeric T, int n> span<T, n> & clampify(span<T, n> & s, const vec<T, n> & min, const vec<T, n> & max);
    template <NumericOrPointer T> T & clampify(T & v, const span1<T> & span);
    template <Numeric T, int n> vec<T, n> & clampify(vec<T, n> & v, const span<T, n> & s);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <NumericOrPointer T>
    template <NumericOrPointer U>
    inline constexpr span<T, 1>::span(const span1<U> & s) noexcept :
        min(T(s.min)),
        max(T(s.max))
    {}

    template <NumericOrPointer T>
    template <Numeric U, int m>
    inline constexpr span<T, 1>::span(const span<U, m> & s) noexcept :
        min(T(s.min.x)),
        max(T(s.max.x))
    {}

    template <NumericOrPointer T>
    inline constexpr span<T, 1>::span(const T v1, const T v2) noexcept :
        min(v1),
        max(v2)
    {}

    template <NumericOrPointer T>
    inline constexpr auto span<T, 1>::size() const noexcept
    {
        return max - min;
    }

    template <NumericOrPointer T>
    inline constexpr bool span<T, 1>::contains(const T v) const noexcept
    {
        return v >= min && v < max;
    }

    template <Numeric T>
    template <Numeric U, int m>
    inline constexpr span<T, 2>::span(const span<U, m> & s) noexcept :
        min(s.min),
        max(s.max)
    {}

    template <Numeric T>
    inline constexpr span<T, 2>::span(const T v1, const T v2) noexcept :
        min(v1),
        max(v2)
    {}

    template <Numeric T>
    inline constexpr span<T, 2>::span(const vec2<T> v1, const vec2<T> v2) noexcept :
        min(v1),
        max(v2)
    {}

    template <Numeric T>
    inline constexpr span<T, 2>::span(const span1<T> & s1, const span1<T> & s2) noexcept :
        min(s1.min, s2.min),
        max(s1.max, s2.max)
    {}

    template <Numeric T>
    inline constexpr vec2<T> span<T, 2>::size() const noexcept
    {
        return max - min;
    }

    template <Numeric T>
    inline constexpr bool span<T, 2>::contains(const vec2<T> & v) const noexcept
    {
        return v.x >= min.x && v.y >= min.y && v.x < max.x && v.y < max.y;
    }

    template <Numeric T>
    inline constexpr span1<T> span<T, 2>::x() const noexcept
    {
        return {min.x, max.x};
    }

    template <Numeric T>
    inline constexpr span1<T> span<T, 2>::y() const noexcept
    {
        return {min.y, max.y};
    }

    template <Numeric T>
    template <Numeric U, int m>
    inline constexpr span<T, 3>::span(const span<U, m> & s) noexcept :
        min(s.min),
        max(s.max)
    {}

    template <Numeric T>
    inline constexpr span<T, 3>::span(const T v1, const T v2) noexcept :
        min(v1),
        max(v2)
    {}

    template <Numeric T>
    inline constexpr span<T, 3>::span(const vec3<T> v1, const vec3<T> v2) noexcept :
        min(v1),
        max(v2)
    {}

    template <Numeric T>
    inline constexpr span<T, 3>::span(const span1<T> & s1, const span1<T> & s2, const span1<T> & s3) noexcept :
        min(s1.min, s2.min, s3.min),
        max(s1.max, s2.max, s3.max)
    {}

    template <Numeric T>
    inline constexpr span<T, 3>::span(const span2<T> & s1, const span1<T> & s2) noexcept :
        min(s1.min, s2.min),
        max(s1.max, s2.max)
    {}

    template <Numeric T>
    inline constexpr span<T, 3>::span(const span1<T> & s1, const span2<T> & s2) noexcept :
        min(s1.min, s2.min),
        max(s1.max, s2.max)
    {}

    template <Numeric T>
    inline constexpr vec3<T> span<T, 3>::size() const noexcept
    {
        return max - min;
    }

    template <Numeric T>
    inline constexpr bool span<T, 3>::contains(const vec3<T> & v) const noexcept
    {
        return v.x >= min.x && v.y >= min.y && v.z >= min.z && v.x < max.x && v.y < max.y && v.z < max.z;
    }

    template <Numeric T>
    inline constexpr span1<T> span<T, 3>::x() const noexcept
    {
        return {min.x, max.x};
    }

    template <Numeric T>
    inline constexpr span1<T> span<T, 3>::y() const noexcept
    {
        return {min.y, max.y};
    }

    template <Numeric T>
    inline constexpr span1<T> span<T, 3>::z() const noexcept
    {
        return {min.z, max.z};
    }

    template <Numeric T>
    inline constexpr span2<T> span<T, 3>::xy() const noexcept
    {
        return {min.xy(), max.xy()};
    }

    template <Numeric T>
    inline constexpr span2<T> span<T, 3>::yz() const noexcept
    {
        return {min.yz(), max.yz()};
    }

    template <Numeric T>
    template <Numeric U, int m>
    inline constexpr span<T, 4>::span(const span<U, m> & s) noexcept :
        min(s.min),
        max(s.max)
    {}

    template <Numeric T>
    inline constexpr span<T, 4>::span(const T v1, const T v2) noexcept :
        min(v1),
        max(v2)
    {}

    template <Numeric T>
    inline constexpr span<T, 4>::span(const vec4<T> v1, const vec4<T> v2) noexcept :
        min(v1),
        max(v2)
    {}

    template <Numeric T>
    inline constexpr span<T, 4>::span(const span1<T> & s1, const span1<T> & s2, const span1<T> & s3, const span1<T> & s4) noexcept :
        min(s1.min, s2.min, s3.min, s4.min),
        max(s1.max, s2.max, s3.max, s4.max)
    {}

    template <Numeric T>
    inline constexpr span<T, 4>::span(const span2<T> & s1, const span1<T> & s2, const span1<T> & s3) noexcept :
        min(s1.min, s2.min, s3.min),
        max(s1.max, s2.max, s3.max)
    {}

    template <Numeric T>
    inline constexpr span<T, 4>::span(const span1<T> & s1, const span2<T> & s2, const span1<T> & s3) noexcept :
        min(s1.min, s2.min, s3.min),
        max(s1.max, s2.max, s3.max)
    {}

    template <Numeric T>
    inline constexpr span<T, 4>::span(const span1<T> & s1, const span1<T> & s2, const span2<T> & s3) noexcept :
        min(s1.min, s2.min, s3.min),
        max(s1.max, s2.max, s3.max)
    {}

    template <Numeric T>
    inline constexpr span<T, 4>::span(const span2<T> & s1, const span2<T> & s2) noexcept :
        min(s1.min, s2.min),
        max(s1.max, s2.max)
    {}

    template <Numeric T>
    inline constexpr span<T, 4>::span(const span3<T> & s1, const span1<T> & s2) noexcept :
        min(s1.min, s2.min),
        max(s1.max, s2.max)
    {}

    template <Numeric T>
    inline constexpr span<T, 4>::span(const span1<T> & s1, const span3<T> & s2) noexcept :
        min(s1.min, s2.min),
        max(s1.max, s2.max)
    {}

    template <Numeric T>
    inline constexpr vec4<T> span<T, 4>::size() const noexcept
    {
        return max - min;
    }

    template <Numeric T>
    inline constexpr bool span<T, 4>::contains(const vec4<T> & v) const noexcept
    {
        return v.x >= min.x && v.y >= min.y && v.z >= min.z && v.w >= min.w && v.x < max.x && v.y < max.y && v.z < max.z && v.w < max.w;
    }

    template <Numeric T>
    inline constexpr span1<T> span<T, 4>::x() const noexcept
    {
        return {min.x, max.x};
    }

    template <Numeric T>
    inline constexpr span1<T> span<T, 4>::y() const noexcept
    {
        return {min.y, max.y};
    }

    template <Numeric T>
    inline constexpr span1<T> span<T, 4>::z() const noexcept
    {
        return {min.z, max.z};
    }

    template <Numeric T>
    inline constexpr span1<T> span<T, 4>::w() const noexcept
    {
        return {min.w, max.w};
    }

    template <Numeric T>
    inline constexpr span2<T> span<T, 4>::xy() const noexcept
    {
        return {min.xy(), max.xy()};
    }

    template <Numeric T>
    inline constexpr span2<T> span<T, 4>::yz() const noexcept
    {
        return {min.yz(), max.yz()};
    }

    template <Numeric T>
    inline constexpr span2<T> span<T, 4>::zw() const noexcept
    {
        return {min.zw(), max.zw()};
    }

    template <Numeric T>
    inline constexpr span3<T> span<T, 4>::xyz() const noexcept
    {
        return {min.xyz(), max.xyz()};
    }

    template <Numeric T>
    inline constexpr span3<T> span<T, 4>::yzw() const noexcept
    {
        return {min.yzw(), max.yzw()};
    }

    template <NumericOrPointer T, int n>
    inline span<T, n> & operator+=(span<T, n> & s, const T v)
    {
        s.min += v;
        s.max += v;
        return s;
    }

    template <Numeric T, int n>
    inline span<T, n> & operator+=(span<T, n> & s, const vec<T, n> & v)
    {
        s.min += v;
        s.max += v;
        return s;
    }

    template <NumericOrPointer T, int n>
    inline span<T, n> & operator-=(span<T, n> & s, const T v)
    {
        s.min -= v;
        s.max -= v;
        return s;
    }

    template <Numeric T, int n>
    inline span<T, n> & operator-=(span<T, n> & s, const vec<T, n> & v)
    {
        s.min -= v;
        s.max -= v;
        return s;
    }

    template <Numeric T, int n>
    inline span<T, n> & operator*=(span<T, n> & s, const T v)
    {
        s.min *= v;
        s.max *= v;
        return s;
    }

    template <Numeric T, int n>
    inline span<T, n> & operator*=(span<T, n> & s, const vec<T, n> & v)
    {
        s.min *= v;
        s.max *= v;
        return s;
    }

    template <Numeric T, int n>
    inline span<T, n> & operator/=(span<T, n> & s, const T v)
    {
        if constexpr (Floating<T>)
        {
            return s *= (T(1.0) / v);
        }
        else
        {
            s.min /= v;
            s.max /= v;
            return s;
        }
    }

    template <Numeric T, int n>
    inline span<T, n> & operator/=(span<T, n> & s, const vec<T, n> & v)
    {
        if constexpr (Floating<T>)
        {
            return s *= T(1.0) / v;
        }
        else
        {
            s.min /= v;
            s.max /= v;
            return s;
        }
    }

    template <Numeric T, int n>
    inline span<T, n> & operator&=(span<T, n> & s1, const span<T, n> & s2)
    {
        maxify(s1.min, s2.min);
        minify(s1.max, s2.max);
        return s1;
    }

    template <Numeric T, int n>
    inline span<T, n> & operator|=(span<T, n> & s1, const span<T, n> & s2)
    {
        minify(s1.min, s2.min);
        maxify(s1.max, s2.max);
        return s1;
    }

    template <NumericOrPointer T, int n>
    inline constexpr span<T, n> operator+(const span<T, n> & s, const T v)
    {
        if constexpr (n == 1)
        {
            return {T(s.min + v), T(s.max + v)};
        }
        else
        {
            return {s.min + v, s.max + v};
        }
    }

    template <Numeric T, int n>
    inline constexpr span<T, n> operator+(const T v, const span<T, n> & s)
    {
        if constexpr (n == 1)
        {
            return {T(v + s.min), T(v + s.max)};
        }
        else
        {
            return {v + s.min, v + s.max};
        }
    }

    template <Numeric T, int n>
    inline constexpr span<T, n> operator+(const span<T, n> & s, const vec<T, n> & v)
    {
        return {s.min + v, s.max + v};
    }

    template <Numeric T, int n>
    inline constexpr span<T, n> operator+(const vec<T, n> & v, const span<T, n> & s)
    {
        return {v + s.min, v + s.max};
    }

    template <NumericOrPointer T, int n>
    inline constexpr span<T, n> operator-(const span<T, n> & s, const T v)
    {
        if constexpr (n == 1)
        {
            return {T(s.min - v), T(s.max - v)};
        }
        else
        {
            return {s.min - v, s.max - v};
        }
    }

    template <Numeric T, int n>
    inline constexpr span<T, n> operator-(const T v, const span<T, n> & s)
    {
        if constexpr (n == 1)
        {
            return {T(v - s.min), T(v - s.max)};
        }
        else
        {
            return {v - s.min, v - s.max};
        }
    }

    template <Numeric T, int n>
    inline constexpr span<T, n> operator-(const span<T, n> & s, const vec<T, n> & v)
    {
        return {s.min - v, s.max - v};
    }

    template <Numeric T, int n>
    inline constexpr span<T, n> operator-(const vec<T, n> & v, const span<T, n> & s)
    {
        return {v - s.min, v - s.max};
    }

    template <Numeric T, int n>
    inline constexpr span<T, n> operator*(const span<T, n> & s, const T v)
    {
        if constexpr (n == 1)
        {
            return {T(s.min * v), T(s.max * v)};
        }
        else
        {
            return {s.min * v, s.max * v};
        }
    }

    template <Numeric T, int n>
    inline constexpr span<T, n> operator*(const T v, const span<T, n> & s)
    {
        if constexpr (n == 1)
        {
            return {T(v * s.min), T(v * s.max)};
        }
        else
        {
            return {v * s.min, v * s.max};
        }
    }

    template <Numeric T, int n>
    inline constexpr span<T, n> operator*(const span<T, n> & s, const vec<T, n> & v)
    {
        return {s.min * v, s.max * v};
    }

    template <Numeric T, int n>
    inline constexpr span<T, n> operator*(const vec<T, n> & v, const span<T, n> & s)
    {
        return {v * s.min, v * s.max};
    }

    template <Numeric T, int n>
    inline constexpr span<T, n> operator/(const span<T, n> & s, const T v)
    {
        if constexpr (Floating<T>)
        {
            return s * (T(1.0) / v);
        }
        else
        {
            if constexpr (n == 1)
            {
                return {T(s.min / v), T(s.max / v)};
            }
            else
            {
                return {s.min / v, s.max / v};
            }
        }
    }

    template <Numeric T, int n>
    inline constexpr span<T, n> operator/(const span<T, n> & s, const vec<T, n> & v)
    {
        if constexpr (Floating<T>)
        {
            return s * (T(1.0) / v);
        }
        else
        {
            return {s.min / v, s.max / v};
        }
    }

    template <NumericOrPointer T, int n>
    inline constexpr bool operator==(const span<T, n> & s1, const span<T, n> & s2)
    {
        return s1.min == s2.min && s1.max == s2.max;
    }

    template <NumericOrPointer T, int n>
    inline constexpr bool operator!=(const span<T, n> & s1, const span<T, n> & s2)
    {
        return !(s1 == s2);
    }

    template <Numeric T, int n>
    inline constexpr span<T, n> operator&(const span<T, n> & s1, const span<T, n> & s2)
    {
        return {max(s1.min, s2.min), min(s1.max, s2.max)};
    }

    template <Numeric T, int n>
    inline constexpr span<T, n> operator|(const span<T, n> & s1, const span<T, n> & s2)
    {
        return {min(s1.min, s2.min), max(s1.max, s2.max)};
    }

    template <NumericOrPointer T, int n>
    inline constexpr span<T, n> min(const span<T, n> & s, const T v)
    {
        return {min(s.min, v), min(s.max, v)};
    }

    template <Numeric T, int n>
    inline constexpr span<T, n> min(const span<T, n> & s, const vec<T, n> & v)
    {
        return {min(s.min, v), min(s.max, v)};
    }

    template <NumericOrPointer T, int n>
    inline constexpr span<T, n> max(const span<T, n> & s, const T v)
    {
        return {max(s.min, v), max(s.max, v)};
    }

    template <Numeric T, int n>
    inline constexpr span<T, n> max(const span<T, n> & s, const vec<T, n> & v)
    {
        return {max(s.min, v), max(s.max, v)};
    }

    template <NumericOrPointer T, int n>
    inline span<T, n> & minify(span<T, n> & s, const T v)
    {
        minify(s.min, v);
        minify(s.max, v);
        return s;
    }

    template <Numeric T, int n>
    inline span<T, n> & minify(span<T, n> & s, const vec<T, n> & v)
    {
        minify(s.min, v);
        minify(s.max, v);
        return s;
    }

    template <NumericOrPointer T, int n>
    inline span<T, n> & maxify(span<T, n> & s, const T v)
    {
        maxify(s.min, v);
        maxify(s.max, v);
        return s;
    }

    template <Numeric T, int n>
    inline span<T, n> & maxify(span<T, n> & s, const vec<T, n> & v)
    {
        maxify(s.min, v);
        maxify(s.max, v);
        return s;
    }

    template <Numeric T, int n>
    inline constexpr span<T, n> clamp(const span<T, n> & s, const T min, const T max)
    {
        return {clamp(s.min, min, max), clamp(s.max, min, max)};
    }

    template <Numeric T, int n>
    inline constexpr span<T, n> clamp(const span<T, n> & s, const vec<T, n> & min, const vec<T, n> & max)
    {
        return {clamp(s.min, min, max), clamp(s.max, min, max)};
    }

    template <Numeric T>
    inline constexpr T clamp(const T v, const span1<T> & s)
    {
        return clamp(v, s.min, s.max);
    }

    template <Numeric T, int n>
    inline constexpr vec<T, n> clamp(const vec<T, n> & v, const span<T, n> & s)
    {
        return clamp(v, s.min, s.max);
    }

    template <Numeric T, int n>
    inline span<T, n> & clampify(span<T, n> & s, const T min, const T max)
    {
        clampify(s.min, min, max);
        clampify(s.max, min, max);
        return s;
    }

    template <Numeric T, int n>
    inline span<T, n> & clampify(span<T, n> & s, const vec<T, n> & min, const vec<T, n> & max)
    {
        clampify(s.min, min, max);
        clampify(s.max, min, max);
        return s;
    }

    template <Numeric T>
    inline T & clampify(T & v, const span1<T> & s)
    {
        return clampify(v, s.min, s.max);
    }

    template <Numeric T, int n>
    inline vec<T, n> & clampify(vec<T, n> & v, const span<T, n> & s)
    {
        return clampify(v, s.min, s.max);
    }
}
