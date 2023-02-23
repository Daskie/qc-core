#pragma once

#include <qc-core/vector.hpp>

namespace qc
{
    template <typename T, int n> struct span;

    inline namespace types
    {
        using qc::span;

        template <NumericOrPointer T> using span1 = span<T, 1>;
        template <Numeric          T> using span2 = span<T, 2>;
        template <Numeric          T> using span3 = span<T, 3>;
        template <Numeric          T> using span4 = span<T, 4>;

        template <int n> using  fspan = span< f32, n>;
        template <int n> using  dspan = span< f64, n>;
        template <int n> using  cspan = span<  s8, n>;
        template <int n> using ucspan = span<  u8, n>;
        template <int n> using  sspan = span< s16, n>;
        template <int n> using usspan = span< u16, n>;
        template <int n> using  ispan = span< s32, n>;
        template <int n> using uispan = span< u32, n>;
        template <int n> using  lspan = span< s64, n>;
        template <int n> using ulspan = span< u64, n>;
        template <int n> using  nspan = span< nat, n>;
        template <int n> using unspan = span<unat, n>;

        using  fspan1 = span< f32, 1>;
        using  fspan2 = span< f32, 2>;
        using  fspan3 = span< f32, 3>;
        using  fspan4 = span< f32, 4>;
        using  dspan1 = span< f64, 1>;
        using  dspan2 = span< f64, 2>;
        using  dspan3 = span< f64, 3>;
        using  dspan4 = span< f64, 4>;
        using  cspan1 = span<  s8, 1>;
        using  cspan2 = span<  s8, 2>;
        using  cspan3 = span<  s8, 3>;
        using  cspan4 = span<  s8, 4>;
        using ucspan1 = span<  u8, 1>;
        using ucspan2 = span<  u8, 2>;
        using ucspan3 = span<  u8, 3>;
        using ucspan4 = span<  u8, 4>;
        using  sspan1 = span< s16, 1>;
        using  sspan2 = span< s16, 2>;
        using  sspan3 = span< s16, 3>;
        using  sspan4 = span< s16, 4>;
        using usspan1 = span< u16, 1>;
        using usspan2 = span< u16, 2>;
        using usspan3 = span< u16, 3>;
        using usspan4 = span< u16, 4>;
        using  ispan1 = span< s32, 1>;
        using  ispan2 = span< s32, 2>;
        using  ispan3 = span< s32, 3>;
        using  ispan4 = span< s32, 4>;
        using uispan1 = span< u32, 1>;
        using uispan2 = span< u32, 2>;
        using uispan3 = span< u32, 3>;
        using uispan4 = span< u32, 4>;
        using  lspan1 = span< s64, 1>;
        using  lspan2 = span< s64, 2>;
        using  lspan3 = span< s64, 3>;
        using  lspan4 = span< s64, 4>;
        using ulspan1 = span< u64, 1>;
        using ulspan2 = span< u64, 2>;
        using ulspan3 = span< u64, 3>;
        using ulspan4 = span< u64, 4>;
        using  nspan1 = span< nat, 1>;
        using  nspan2 = span< nat, 2>;
        using  nspan3 = span< nat, 3>;
        using  nspan4 = span< nat, 4>;
        using unspan1 = span<unat, 1>;
        using unspan2 = span<unat, 2>;
        using unspan3 = span<unat, 3>;
        using unspan4 = span<unat, 4>;
    }

    template <NumericOrPointer T>
    struct span<T, 1>
    {
        T min;
        T max;

        constexpr span() = default;
        template <NumericOrPointer U> constexpr explicit span(const span1<U> & s);
        template <Numeric U, int m> constexpr explicit span(const span<U, m> & s);
        constexpr span(T v1, T v2);

        constexpr span(const span & s) = default;
        constexpr span(span && s) = default;

        span & operator=(const span & s) = default;
        span & operator=(span && s) = default;

        ~span() = default;

        constexpr explicit operator bool() const;

        constexpr auto size() const;

        constexpr bool contains(T v) const;
    };

    template <Numeric T>
    struct span<T, 2>
    {
        vec2<T> min;
        vec2<T> max;

        constexpr span() = default;
        template <Numeric U, int m> constexpr explicit span(const span<U, m> & s);
        template <Numeric U> constexpr explicit span(const span1<U> & s);
        constexpr span(T v1, T v2);
        constexpr span(vec2<T> v1, vec2<T> v2);
        constexpr span(const span1<T> & s1, const span1<T> & s2);

        constexpr span(const span & s) = default;
        constexpr span(span && s) = default;

        span & operator=(const span & s) = default;
        span & operator=(span && s) = default;

        ~span() = default;

        constexpr explicit operator bool() const;

        constexpr vec2<T> size() const;

        constexpr bool contains(const vec2<T> & v) const;

        constexpr span1<T> x() const;
        constexpr span1<T> y() const;
    };

    template <Numeric T>
    struct span<T, 3>
    {
        vec3<T> min;
        vec3<T> max;

        constexpr span() = default;
        template <Numeric U, int m> constexpr explicit span(const span<U, m> & s);
        template <Numeric U> constexpr explicit span(const span1<U> & s);
        constexpr span(T v1, T v2);
        constexpr span(vec3<T> v1, vec3<T> v2);
        constexpr span(const span1<T> & s1, const span1<T> & s2, const span1<T> & s3);
        constexpr span(const span2<T> & s1, const span1<T> & s2);
        constexpr span(const span1<T> & s1, const span2<T> & s2);

        constexpr span(const span & s) = default;
        constexpr span(span && s) = default;

        span & operator=(const span & s) = default;
        span & operator=(span && s) = default;

        ~span() = default;

        constexpr explicit operator bool() const;

        constexpr vec3<T> size() const;

        constexpr bool contains(const vec3<T> & v) const;

        constexpr span1<T> x() const;
        constexpr span1<T> y() const;
        constexpr span1<T> z() const;

        constexpr span2<T> xy() const;
        constexpr span2<T> yz() const;
    };

    template <Numeric T>
    struct span<T, 4>
    {
        vec4<T> min;
        vec4<T> max;

        constexpr span() = default;
        template <Numeric U, int m> constexpr explicit span(const span<U, m> & s);
        template <Numeric U> constexpr explicit span(const span1<U> & s);
        constexpr span(T v1, T v2);
        constexpr span(vec4<T> v1, vec4<T> v2);
        constexpr span(const span1<T> & s1, const span1<T> & s2, const span1<T> & s3, const span1<T> & s4);
        constexpr span(const span2<T> & s1, const span1<T> & s2, const span1<T> & s3);
        constexpr span(const span1<T> & s1, const span2<T> & s2, const span1<T> & s3);
        constexpr span(const span1<T> & s1, const span1<T> & s2, const span2<T> & s3);
        constexpr span(const span2<T> & s1, const span2<T> & s2);
        constexpr span(const span3<T> & s1, const span1<T> & s2);
        constexpr span(const span1<T> & s1, const span3<T> & s2);

        constexpr span(const span & s) = default;
        constexpr span(span && s) = default;

        span & operator=(const span & s) = default;
        span & operator=(span && s) = default;

        ~span() = default;

        constexpr explicit operator bool() const;

        constexpr vec4<T> size() const;

        constexpr bool contains(const vec4<T> & v) const;

        constexpr span1<T> x() const;
        constexpr span1<T> y() const;
        constexpr span1<T> z() const;
        constexpr span1<T> w() const;

        constexpr span2<T> xy() const;
        constexpr span2<T> yz() const;
        constexpr span2<T> zw() const;

        constexpr span3<T> xyz() const;
        constexpr span3<T> yzw() const;
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

    template <Numeric T, int n> span<T, n> & operator+=(span<T, n> & s, T v);
    template <Pointer T, int n> span<T, n> & operator+=(span<T, n> & s, nat v);
    template <Numeric T, int n> span<T, n> & operator+=(span<T, n> & s, const vec<T, n> & v);

    template <Numeric T, int n> span<T, n> & operator-=(span<T, n> & s, T v);
    template <Pointer T, int n> span<T, n> & operator-=(span<T, n> & s, nat v);
    template <Numeric T, int n> span<T, n> & operator-=(span<T, n> & s, const vec<T, n> & v);

    template <Numeric T, int n> span<T, n> & operator*=(span<T, n> & s, T v);
    template <Numeric T, int n> span<T, n> & operator*=(span<T, n> & s, const vec<T, n> & v);

    template <Numeric T, int n> span<T, n> & operator/=(span<T, n> & s, T v);
    template <Numeric T, int n> span<T, n> & operator/=(span<T, n> & s, const vec<T, n> & v);

    template <Numeric T, int n> span<T, n> & operator&=(span<T, n> & s1, const span<T, n> & s2);

    template <Numeric T, int n> span<T, n> & operator|=(span<T, n> & s1, const span<T, n> & s2);

    template <Numeric T, int n> constexpr span<T, n> operator+(const span<T, n> & s, T v);
    template <Pointer T, int n> constexpr span<T, n> operator+(const span<T, n> & s, nat v);
    template <Numeric T, int n> constexpr span<T, n> operator+(T v, const span<T, n> & s);
    template <Numeric T, int n> constexpr span<T, n> operator+(const span<T, n> & s, const vec<T, n> & v);
    template <Numeric T, int n> constexpr span<T, n> operator+(const vec<T, n> & v, const span<T, n> & s);

    template <Numeric T, int n> constexpr span<T, n> operator-(const span<T, n> & s, T v);
    template <Pointer T, int n> constexpr span<T, n> operator-(const span<T, n> & s, nat v);
    template <Numeric T, int n> constexpr span<T, n> operator-(T v1, const span<T, n> & s);
    template <Numeric T, int n> constexpr span<T, n> operator-(const span<T, n> & s, const vec<T, n> & v);
    template <Numeric T, int n> constexpr span<T, n> operator-(const vec<T, n> & v, const span<T, n> & s);

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
    inline constexpr span<T, 1>::span(const span1<U> & s) :
        min{T(s.min)},
        max{T(s.max)}
    {}

    template <NumericOrPointer T>
    template <Numeric U, int m>
    inline constexpr span<T, 1>::span(const span<U, m> & s) :
        min{T(s.min.x)},
        max{T(s.max.x)}
    {}

    template <NumericOrPointer T>
    inline constexpr span<T, 1>::span(const T v1, const T v2) :
        min{v1},
        max{v2}
    {}

    template <NumericOrPointer T>
    inline constexpr span<T, 1>::operator bool() const
    {
        return min || max;
    }

    template <NumericOrPointer T>
    inline constexpr auto span<T, 1>::size() const
    {
        return max - min;
    }

    template <NumericOrPointer T>
    inline constexpr bool span<T, 1>::contains(const T v) const
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
    template <Numeric U, int m>
    inline constexpr span<T, 2>::span(const span<U, m> & s) :
        min{s.min},
        max{s.max}
    {}

    template <Numeric T>
    template <Numeric U>
    inline constexpr span<T, 2>::span(const span1<U> & s) :
        min{T(s.min)},
        max{T(s.max)}
    {}

    template <Numeric T>
    inline constexpr span<T, 2>::span(const T v1, const T v2) :
        min{v1},
        max{v2}
    {}

    template <Numeric T>
    inline constexpr span<T, 2>::span(const vec2<T> v1, const vec2<T> v2) :
        min{v1},
        max{v2}
    {}

    template <Numeric T>
    inline constexpr span<T, 2>::span(const span1<T> & s1, const span1<T> & s2) :
        min{s1.min, s2.min},
        max{s1.max, s2.max}
    {}

    template <Numeric T>
    inline constexpr span<T, 2>::operator bool() const
    {
        return min || max;
    }

    template <Numeric T>
    inline constexpr vec2<T> span<T, 2>::size() const
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
    inline constexpr span1<T> span<T, 2>::x() const
    {
        return {min.x, max.x};
    }

    template <Numeric T>
    inline constexpr span1<T> span<T, 2>::y() const
    {
        return {min.y, max.y};
    }

    template <Numeric T>
    template <Numeric U, int m>
    inline constexpr span<T, 3>::span(const span<U, m> & s) :
        min{s.min},
        max{s.max}
    {}

    template <Numeric T>
    template <Numeric U>
    inline constexpr span<T, 3>::span(const span1<U> & s) :
        min{T(s.min)},
        max{T(s.max)}
    {}

    template <Numeric T>
    inline constexpr span<T, 3>::span(const T v1, const T v2) :
        min{v1},
        max{v2}
    {}

    template <Numeric T>
    inline constexpr span<T, 3>::span(const vec3<T> v1, const vec3<T> v2) :
        min{v1},
        max{v2}
    {}

    template <Numeric T>
    inline constexpr span<T, 3>::span(const span1<T> & s1, const span1<T> & s2, const span1<T> & s3) :
        min(s1.min, s2.min, s3.min),
        max(s1.max, s2.max, s3.max)
    {}

    template <Numeric T>
    inline constexpr span<T, 3>::span(const span2<T> & s1, const span1<T> & s2) :
        min(s1.min, s2.min),
        max(s1.max, s2.max)
    {}

    template <Numeric T>
    inline constexpr span<T, 3>::span(const span1<T> & s1, const span2<T> & s2) :
        min(s1.min, s2.min),
        max(s1.max, s2.max)
    {}

    template <Numeric T>
    inline constexpr span<T, 3>::operator bool() const
    {
        return min || max;
    }

    template <Numeric T>
    inline constexpr vec3<T> span<T, 3>::size() const
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
    inline constexpr span1<T> span<T, 3>::x() const
    {
        return {min.x, max.x};
    }

    template <Numeric T>
    inline constexpr span1<T> span<T, 3>::y() const
    {
        return {min.y, max.y};
    }

    template <Numeric T>
    inline constexpr span1<T> span<T, 3>::z() const
    {
        return {min.z, max.z};
    }

    template <Numeric T>
    inline constexpr span2<T> span<T, 3>::xy() const
    {
        return {min.xy(), max.xy()};
    }

    template <Numeric T>
    inline constexpr span2<T> span<T, 3>::yz() const
    {
        return {min.yz(), max.yz()};
    }

    template <Numeric T>
    template <Numeric U, int m>
    inline constexpr span<T, 4>::span(const span<U, m> & s) :
        min{s.min},
        max{s.max}
    {}

    template <Numeric T>
    template <Numeric U>
    inline constexpr span<T, 4>::span(const span1<U> & s) :
        min{T(s.min)},
        max{T(s.max)}
    {}

    template <Numeric T>
    inline constexpr span<T, 4>::span(const T v1, const T v2) :
        min{v1},
        max{v2}
    {}

    template <Numeric T>
    inline constexpr span<T, 4>::span(const vec4<T> v1, const vec4<T> v2) :
        min{v1},
        max{v2}
    {}

    template <Numeric T>
    inline constexpr span<T, 4>::span(const span1<T> & s1, const span1<T> & s2, const span1<T> & s3, const span1<T> & s4) :
        min{s1.min, s2.min, s3.min, s4.min},
        max{s1.max, s2.max, s3.max, s4.max}
    {}

    template <Numeric T>
    inline constexpr span<T, 4>::span(const span2<T> & s1, const span1<T> & s2, const span1<T> & s3) :
        min{s1.min, s2.min, s3.min},
        max{s1.max, s2.max, s3.max}
    {}

    template <Numeric T>
    inline constexpr span<T, 4>::span(const span1<T> & s1, const span2<T> & s2, const span1<T> & s3) :
        min{s1.min, s2.min, s3.min},
        max{s1.max, s2.max, s3.max}
    {}

    template <Numeric T>
    inline constexpr span<T, 4>::span(const span1<T> & s1, const span1<T> & s2, const span2<T> & s3) :
        min{s1.min, s2.min, s3.min},
        max{s1.max, s2.max, s3.max}
    {}

    template <Numeric T>
    inline constexpr span<T, 4>::span(const span2<T> & s1, const span2<T> & s2) :
        min{s1.min, s2.min},
        max{s1.max, s2.max}
    {}

    template <Numeric T>
    inline constexpr span<T, 4>::span(const span3<T> & s1, const span1<T> & s2) :
        min{s1.min, s2.min},
        max{s1.max, s2.max}
    {}

    template <Numeric T>
    inline constexpr span<T, 4>::span(const span1<T> & s1, const span3<T> & s2) :
        min{s1.min, s2.min},
        max{s1.max, s2.max}
    {}

    template <Numeric T>
    inline constexpr span<T, 4>::operator bool() const
    {
        return min || max;
    }

    template <Numeric T>
    inline constexpr vec4<T> span<T, 4>::size() const
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
    inline constexpr span1<T> span<T, 4>::x() const
    {
        return {min.x, max.x};
    }

    template <Numeric T>
    inline constexpr span1<T> span<T, 4>::y() const
    {
        return {min.y, max.y};
    }

    template <Numeric T>
    inline constexpr span1<T> span<T, 4>::z() const
    {
        return {min.z, max.z};
    }

    template <Numeric T>
    inline constexpr span1<T> span<T, 4>::w() const
    {
        return {min.w, max.w};
    }

    template <Numeric T>
    inline constexpr span2<T> span<T, 4>::xy() const
    {
        return {min.xy(), max.xy()};
    }

    template <Numeric T>
    inline constexpr span2<T> span<T, 4>::yz() const
    {
        return {min.yz(), max.yz()};
    }

    template <Numeric T>
    inline constexpr span2<T> span<T, 4>::zw() const
    {
        return {min.zw(), max.zw()};
    }

    template <Numeric T>
    inline constexpr span3<T> span<T, 4>::xyz() const
    {
        return {min.xyz(), max.xyz()};
    }

    template <Numeric T>
    inline constexpr span3<T> span<T, 4>::yzw() const
    {
        return {min.yzw(), max.yzw()};
    }

    template <Numeric T, int n>
    inline span<T, n> & operator+=(span<T, n> & s, const T v)
    {
        s.min += v;
        s.max += v;
        return s;
    }

    template <Pointer T, int n>
    inline span<T, n> & operator+=(span<T, n> & s, const nat v)
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

    template <Numeric T, int n>
    inline span<T, n> & operator-=(span<T, n> & s, const T v)
    {
        s.min -= v;
        s.max -= v;
        return s;
    }

    template <Pointer T, int n>
    inline span<T, n> & operator-=(span<T, n> & s, const nat v)
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

    template <Numeric T, int n>
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

    template <Pointer T, int n>
    inline constexpr span<T, n> operator+(const span<T, n> & s, const nat v)
    {
        return {s.min + v, s.max + v};
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

    template <Numeric T, int n>
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

    template <Pointer T, int n>
    inline constexpr span<T, n> operator-(const span<T, n> & s, const nat v)
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
