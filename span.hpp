#pragma once

#include "vector.hpp"

namespace qc::core {

    template <Number T, int n> struct span;

    inline namespace types {

        using qc::core::span;

        template <Number T> using span1 = span<T, 1>;
        template <Number T> using span2 = span<T, 2>;
        template <Number T> using span3 = span<T, 3>;
        template <Number T> using span4 = span<T, 4>;

        template <int n> using  fspan = span< f32, n>;
        template <int n> using  dspan = span< f64, n>;
        template <int n> using  cspan = span< s08, n>;
        template <int n> using ucspan = span< u08, n>;
        template <int n> using  sspan = span< s16, n>;
        template <int n> using usspan = span< u16, n>;
        template <int n> using  ispan = span< s32, n>;
        template <int n> using uispan = span< u32, n>;
        template <int n> using  lspan = span< s64, n>;
        template <int n> using ulspan = span< u64, n>;

        using  fspan1 = span1< f32>;
        using  fspan2 = span2< f32>;
        using  fspan3 = span3< f32>;
        using  fspan4 = span4< f32>;
        using  dspan1 = span1< f64>;
        using  dspan2 = span2< f64>;
        using  dspan3 = span3< f64>;
        using  dspan4 = span4< f64>;
        using  cspan1 = span1< s08>;
        using  cspan2 = span2< s08>;
        using  cspan3 = span3< s08>;
        using  cspan4 = span4< s08>;
        using ucspan1 = span1< u08>;
        using ucspan2 = span2< u08>;
        using ucspan3 = span3< u08>;
        using ucspan4 = span4< u08>;
        using  sspan1 = span1< s16>;
        using  sspan2 = span2< s16>;
        using  sspan3 = span3< s16>;
        using  sspan4 = span4< s16>;
        using usspan1 = span1< u16>;
        using usspan2 = span2< u16>;
        using usspan3 = span3< u16>;
        using usspan4 = span4< u16>;
        using  ispan1 = span1< s32>;
        using  ispan2 = span2< s32>;
        using  ispan3 = span3< s32>;
        using  ispan4 = span4< s32>;
        using uispan1 = span1< u32>;
        using uispan2 = span2< u32>;
        using uispan3 = span3< u32>;
        using uispan4 = span4< u32>;
        using  lspan1 = span1< s64>;
        using  lspan2 = span2< s64>;
        using  lspan3 = span3< s64>;
        using  lspan4 = span4< s64>;
        using ulspan1 = span1< u64>;
        using ulspan2 = span2< u64>;
        using ulspan3 = span3< u64>;
        using ulspan4 = span4< u64>;

    }

    template <Number T> struct span<T, 1> {

        T min{};
        T max{};

        constexpr span() noexcept = default;
        template <Number U> constexpr explicit span(const span1<U> & v) noexcept;
        template <Number U, int m> constexpr explicit span(const span<U, m> & v) noexcept;
        constexpr span(T v1, T v2) noexcept;

        constexpr span(const span & v) noexcept = default;
        constexpr span(span && v) noexcept = default;

        span & operator=(const span & v) noexcept = default;
        span & operator=(span && v) noexcept = default;

        ~span() noexcept = default;

    };

    template <Number T> struct span<T, 2> {

        vec2<T> min;
        vec2<T> max;

        constexpr span() noexcept = default;
        template <Number U, int m> constexpr explicit span(const span<U, m> & v) noexcept;
        constexpr span(T v1, T v2) noexcept;
        constexpr span(const vec2<T> & v1, const vec2<T> & v2) noexcept;
        Q_CONSTEX span(const span1<T> & v1, const span1<T> & v2) noexcept;

        constexpr span(const span & v) noexcept = default;
        constexpr span(span && v) noexcept = default;

        span & operator=(const span & v) noexcept = default;
        span & operator=(span && v) noexcept = default;

        ~span() noexcept = default;

        Q_CONSTEX span1<T> x() const noexcept;
        Q_CONSTEX span1<T> y() const noexcept;

    };

    template <Number T> struct span<T, 3> {

        vec3<T> min;
        vec3<T> max;

        constexpr span() noexcept = default;
        template <Number U, int m> constexpr explicit span(const span<U, m> & v) noexcept;
        constexpr span(T v1, T v2) noexcept;
        constexpr span(const vec3<T> & v1, const vec3<T> & v2) noexcept;
        Q_CONSTEX span(const span1<T> & v1, const span1<T> & v2, const span1<T> & v3) noexcept;
        Q_CX_ABLE span(const span2<T> & v1, const span1<T> & v2) noexcept;
        Q_CX_ABLE span(const span1<T> & v1, const span2<T> & v2) noexcept;

        constexpr span(const span & v) noexcept = default;
        constexpr span(span && v) noexcept = default;

        span & operator=(const span & v) noexcept = default;
        span & operator=(span && v) noexcept = default;

        ~span() noexcept = default;

        Q_CONSTEX span1<T> x() const noexcept;
        Q_CONSTEX span1<T> y() const noexcept;
        Q_CONSTEX span1<T> z() const noexcept;

        Q_CX_ABLE span2<T> xy() const noexcept;
        Q_CX_ABLE span2<T> yz() const noexcept;

    };

    template <Number T> struct span<T, 4> {

        vec4<T> min;
        vec4<T> max;

        constexpr span() noexcept = default;
        template <Number U, int m> constexpr explicit span(const span<U, m> & v) noexcept;
        constexpr span(T v1, T v2) noexcept;
        constexpr span(const vec4<T> & v1, const vec4<T> & v2) noexcept;
        Q_CONSTEX span(const span1<T> & v1, const span1<T> & v2, const span1<T> & v3, const span1<T> & v4) noexcept;
        Q_CX_ABLE span(const span2<T> & v1, const span1<T> & v2, const span1<T> & v3) noexcept;
        Q_CX_ABLE span(const span1<T> & v1, const span2<T> & v2, const span1<T> & v3) noexcept;
        Q_CX_ABLE span(const span1<T> & v1, const span1<T> & v2, const span2<T> & v3) noexcept;
        Q_CX_ABLE span(const span2<T> & v1, const span2<T> & v2) noexcept;
        Q_CX_ABLE span(const span3<T> & v1, const span1<T> & v2) noexcept;
        Q_CX_ABLE span(const span1<T> & v1, const span3<T> & v2) noexcept;

        constexpr span(const span & v) noexcept = default;
        constexpr span(span && v) noexcept = default;

        span & operator=(const span & v) noexcept = default;
        span & operator=(span && v) noexcept = default;

        ~span() noexcept = default;

        Q_CONSTEX span1<T> x() const noexcept;
        Q_CONSTEX span1<T> y() const noexcept;
        Q_CONSTEX span1<T> z() const noexcept;
        Q_CONSTEX span1<T> w() const noexcept;

        Q_CX_ABLE span2<T> xy() const noexcept;
        Q_CX_ABLE span2<T> yz() const noexcept;
        Q_CX_ABLE span2<T> zw() const noexcept;

        Q_CX_ABLE span3<T> xyz() const noexcept;
        Q_CX_ABLE span3<T> yzw() const noexcept;

    };

    template <Floater T, int n> constexpr span<T, n>  infspan = span<T, n>(-infinity<T>, infinity<T>);
    template <Floater T, int n> constexpr span<T, n>  nanspan = span<T, n>(nan<T>, nan<T>);
    template <Floater T, int n> constexpr span<T, n> nullspan = span<T, n>(infinity<T>, -infinity<T>);

    template <Number T, int n> Q_CX_ABLE span<T, n> & operator+=(span<T, n> & v1, T v2);
    template <Number T, int n> Q_CX_ABLE span<T, n> & operator+=(span<T, n> & v1, const vec<T, n> & v2);

    template <Number T, int n> Q_CX_ABLE span<T, n> & operator-=(span<T, n> & v1, T v2);
    template <Number T, int n> Q_CX_ABLE span<T, n> & operator-=(span<T, n> & v1, const vec<T, n> & v2);

    template <Number T, int n> Q_CX_ABLE span<T, n> operator+(const span<T, n> & v1, T v2);
    template <Number T, int n> Q_CX_ABLE span<T, n> operator+(T v1, const span<T, n> & v2);
    template <Number T, int n> Q_CX_ABLE span<T, n> operator+(const span<T, n> & v1, const vec<T, n> & v2);
    template <Number T, int n> Q_CX_ABLE span<T, n> operator+(const vec<T, n> & v1, const span<T, n> & v2);

    template <Number T, int n> Q_CX_ABLE span<T, n> operator-(const span<T, n> & v1, T v2);
    template <Number T, int n> Q_CX_ABLE span<T, n> operator-(T v1, const span<T, n> & v2);
    template <Number T, int n> Q_CX_ABLE span<T, n> operator-(const span<T, n> & v1, const vec<T, n> & v2);
    template <Number T, int n> Q_CX_ABLE span<T, n> operator-(const vec<T, n> & v1, const span<T, n> & v2);

    template <typename T, int n> Q_CX_ABLE bool operator==(const span<T, n> & v1, const span<T, n> & v2);

    template <typename T, int n> Q_CX_ABLE bool operator!=(const span<T, n> & v1, const span<T, n> & v2);

} // namespace qc::core

// INLINE IMPLEMENTATION ///////////////////////////////////////////////////////////////////////////////////////////////

namespace qc::core {

    template <Number T>
    template <Number U>
    inline constexpr span<T, 1>::span(const span1<U> & v) noexcept :
        min(T(v.min)),
        max(T(v.max))
    {}

    template <Number T>
    template <Number U, int m>
    inline constexpr span<T, 1>::span(const span<U, m> & v) noexcept :
        min(T(v.min.x)),
        max(T(v.max.x))
    {}

    template <Number T>
    inline constexpr span<T, 1>::span(const T v1, const T v2) noexcept :
        min(v1),
        max(v2)
    {}

    template <Number T>
    template <Number U, int m>
    inline constexpr span<T, 2>::span(const span<U, m> & v) noexcept :
        min(v.min),
        max(v.max)
    {}

    template <Number T>
    inline constexpr span<T, 2>::span(const T v1, const T v2) noexcept :
        min(v1),
        max(v2)
    {}

    template <Number T>
    inline constexpr span<T, 2>::span(const vec2<T> & v1, const vec2<T> & v2) noexcept :
        min(v1),
        max(v2)
    {}

    template <Number T>
    inline Q_CONSTEX span<T, 2>::span(const span1<T> & v1, const span1<T> & v2) noexcept :
        min(v1.min, v2.min),
        max(v1.max, v2.max)
    {}

    template <Number T>
    inline Q_CONSTEX span1<T> span<T, 2>::x() const noexcept {
        return {min.x, max.x};
    }

    template <Number T>
    inline Q_CONSTEX span1<T> span<T, 2>::y() const noexcept {
        return {min.y, max.y};
    }

    template <Number T>
    template <Number U, int m>
    inline constexpr span<T, 3>::span(const span<U, m> & v) noexcept :
        min(v.min),
        max(v.max)
    {}

    template <Number T>
    inline constexpr span<T, 3>::span(const T v1, const T v2) noexcept :
        min(v1),
        max(v2)
    {}

    template <Number T>
    inline constexpr span<T, 3>::span(const vec3<T> & v1, const vec3<T> & v2) noexcept :
        min(v1),
        max(v2)
    {}

    template <Number T>
    inline Q_CONSTEX span<T, 3>::span(const span1<T> & v1, const span1<T> & v2, const span1<T> & v3) noexcept :
        min(v1.min, v2.min, v3.min),
        max(v1.max, v2.max, v3.max)
    {}

    template <Number T>
    inline Q_CX_ABLE span<T, 3>::span(const span2<T> & v1, const span1<T> & v2) noexcept :
        min(v1.min, v2.min),
        max(v1.max, v2.max)
    {}

    template <Number T>
    inline Q_CX_ABLE span<T, 3>::span(const span1<T> & v1, const span2<T> & v2) noexcept :
        min(v1.min, v2.min),
        max(v1.max, v2.max)
    {}

    template <Number T>
    inline Q_CONSTEX span1<T> span<T, 3>::x() const noexcept {
        return {min.x, max.x};
    }

    template <Number T>
    inline Q_CONSTEX span1<T> span<T, 3>::y() const noexcept {
        return {min.y, max.y};
    }

    template <Number T>
    inline Q_CONSTEX span1<T> span<T, 3>::z() const noexcept {
        return {min.z, max.z};
    }

    template <Number T>
    inline Q_CX_ABLE span2<T> span<T, 3>::xy() const noexcept {
        return {min.xy(), max.xy()};
    }

    template <Number T>
    inline Q_CX_ABLE span2<T> span<T, 3>::yz() const noexcept {
        return {min.yz(), max.yz()};
    }

    template <Number T>
    template <Number U, int m>
    inline constexpr span<T, 4>::span(const span<U, m> & v) noexcept :
        min(v.min),
        max(v.max)
    {}

    template <Number T>
    inline constexpr span<T, 4>::span(const T v1, const T v2) noexcept :
        min(v1),
        max(v2)
    {}

    template <Number T>
    inline constexpr span<T, 4>::span(const vec4<T> & v1, const vec4<T> & v2) noexcept :
        min(v1),
        max(v2)
    {}

    template <Number T>
    inline Q_CONSTEX span<T, 4>::span(const span1<T> & v1, const span1<T> & v2, const span1<T> & v3, const span1<T> & v4) noexcept :
        min(v1.min, v2.min, v3.min, v4.min),
        max(v1.max, v2.max, v3.max, v4.max)
    {}

    template <Number T>
    inline Q_CX_ABLE span<T, 4>::span(const span2<T> & v1, const span1<T> & v2, const span1<T> & v3) noexcept :
        min(v1.min, v2.min, v3.min),
        max(v1.max, v2.max, v3.max)
    {}

    template <Number T>
    inline Q_CX_ABLE span<T, 4>::span(const span1<T> & v1, const span2<T> & v2, const span1<T> & v3) noexcept :
        min(v1.min, v2.min, v3.min),
        max(v1.max, v2.max, v3.max)
    {}

    template <Number T>
    inline Q_CX_ABLE span<T, 4>::span(const span1<T> & v1, const span1<T> & v2, const span2<T> & v3) noexcept :
        min(v1.min, v2.min, v3.min),
        max(v1.max, v2.max, v3.max)
    {}

    template <Number T>
    inline Q_CX_ABLE span<T, 4>::span(const span2<T> & v1, const span2<T> & v2) noexcept :
        min(v1.min, v2.min),
        max(v1.max, v2.max)
    {}

    template <Number T>
    inline Q_CX_ABLE span<T, 4>::span(const span3<T> & v1, const span1<T> & v2) noexcept :
        min(v1.min, v2.min),
        max(v1.max, v2.max)
    {}

    template <Number T>
    inline Q_CX_ABLE span<T, 4>::span(const span1<T> & v1, const span3<T> & v2) noexcept :
        min(v1.min, v2.min),
        max(v1.max, v2.max)
    {}

    template <Number T>
    inline Q_CONSTEX span1<T> span<T, 4>::x() const noexcept {
        return {min.x, max.x};
    }

    template <Number T>
    inline Q_CONSTEX span1<T> span<T, 4>::y() const noexcept {
        return {min.y, max.y};
    }

    template <Number T>
    inline Q_CONSTEX span1<T> span<T, 4>::z() const noexcept {
        return {min.z, max.z};
    }

    template <Number T>
    inline Q_CONSTEX span1<T> span<T, 4>::w() const noexcept {
        return {min.w, max.w};
    }

    template <Number T>
    inline Q_CX_ABLE span2<T> span<T, 4>::xy() const noexcept {
        return {min.xy(), max.xy()};
    }

    template <Number T>
    inline Q_CX_ABLE span2<T> span<T, 4>::yz() const noexcept {
        return {min.yz(), max.yz()};
    }

    template <Number T>
    inline Q_CX_ABLE span2<T> span<T, 4>::zw() const noexcept {
        return {min.zw(), max.zw()};
    }

    template <Number T>
    inline Q_CX_ABLE span3<T> span<T, 4>::xyz() const noexcept {
        return {min.xyz(), max.xyz()};
    }

    template <Number T>
    inline Q_CX_ABLE span3<T> span<T, 4>::yzw() const noexcept {
        return {min.yzw(), max.yzw()};
    }

    template <Number T, int n>
    inline Q_CX_ABLE span<T, n> & operator+=(span<T, n> & v1, const T v2) {
        v1.min += v2;
        v1.max += v2;
        return v1;
    }

    template <Number T, int n>
    inline Q_CX_ABLE span<T, n> & operator+=(span<T, n> & v1, const vec<T, n> & v2) {
        v1.min += v2;
        v1.max += v2;
        return v1;
    }

    template <Number T, int n>
    inline Q_CX_ABLE span<T, n> & operator-=(span<T, n> & v1, const T v2) {
        v1.min -= v2;
        v1.max -= v2;
        return v1;
    }

    template <Number T, int n>
    inline Q_CX_ABLE span<T, n> & operator-=(span<T, n> & v1, const vec<T, n> & v2) {
        v1.min -= v2;
        v1.max -= v2;
        return v1;
    }

    template <Number T, int n>
    inline Q_CX_ABLE span<T, n> operator+(const span<T, n> & v1, const T v2) {
        if constexpr (n == 1) return {T(v1.min + v2), T(v1.max + v2)};
        else return {v1.min + v2, v1.max + v2};
    }

    template <Number T, int n>
    inline Q_CX_ABLE span<T, n> operator+(const T v1, const span<T, n> & v2) {
        return v2 + v1;
    }

    template <Number T, int n>
    inline Q_CX_ABLE span<T, n> operator+(const span<T, n> & v1, const vec<T, n> & v2) {
        return {v1.min + v2, v1.max + v2};
    }

    template <Number T, int n>
    inline Q_CX_ABLE span<T, n> operator+(const vec<T, n> & v1, const span<T, n> & v2) {
        return v2 + v1;
    }

    template <Number T, int n>
    inline Q_CX_ABLE span<T, n> operator-(const span<T, n> & v1, const T v2) {
        if constexpr (n == 1) return {T(v1.min - v2), T(v1.max - v2)};
        else return {v1.min - v2, v1.max - v2};
    }

    template <Number T, int n>
    inline Q_CX_ABLE span<T, n> operator-(const T v1, const span<T, n> & v2) {
        if constexpr (n == 1) return {T(v1 - v2.min), T(v1 - v2.max)};
        else return {v1 - v2.min, v1 - v2.max};
    }

    template <Number T, int n>
    inline Q_CX_ABLE span<T, n> operator-(const span<T, n> & v1, const vec<T, n> & v2) {
        return {v1.min - v2, v1.max - v2};
    }

    template <Number T, int n>
    inline Q_CX_ABLE span<T, n> operator-(const vec<T, n> & v1, const span<T, n> & v2) {
        return {v1 - v2.min, v1 - v2.max};
    }

    template <typename T, int n>
    inline Q_CX_ABLE bool operator==(const span<T, n> & v1, const span<T, n> & v2) {
        return v1.min == v2.min && v1.max == v2.max;
    }

    template <typename T, int n>
    inline Q_CX_ABLE bool operator!=(const span<T, n> & v1, const span<T, n> & v2) {
        return !(v1 == v2);
    }

} // namespace qc::core
