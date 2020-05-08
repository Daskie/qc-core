#pragma once

#include "vector.hpp"

namespace qc {

    template <Number T, int t_n> struct span;

    namespace types {

        using qc::span;

        template <Number T> using span1 = span<T, 1>;
        template <Number T> using span2 = span<T, 2>;
        template <Number T> using span3 = span<T, 3>;
        template <Number T> using span4 = span<T, 4>;

        template <int t_n> using  fspan = span< f32, t_n>;
        template <int t_n> using  dspan = span< f64, t_n>;
        template <int t_n> using  cspan = span< s08, t_n>;
        template <int t_n> using ucspan = span< u08, t_n>;
        template <int t_n> using  sspan = span< s16, t_n>;
        template <int t_n> using usspan = span< u16, t_n>;
        template <int t_n> using  ispan = span< s32, t_n>;
        template <int t_n> using uispan = span< u32, t_n>;
        template <int t_n> using  lspan = span< s64, t_n>;
        template <int t_n> using ulspan = span< u64, t_n>;
        template <int t_n> using  nspan = span< nat, t_n>;
        template <int t_n> using unspan = span<unat, t_n>;

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
        using  nspan1 = span1< nat>;
        using  nspan2 = span2< nat>;
        using  nspan3 = span3< nat>;
        using  nspan4 = span4< nat>;
        using unspan1 = span1<unat>;
        using unspan2 = span2<unat>;
        using unspan3 = span3<unat>;
        using unspan4 = span4<unat>;

    }

    template <Number T> struct span<T, 1> {

        //--------------------------------------------------------------------------
        // Static Members

        using Type = T;

        static constexpr int n{1};

        //--------------------------------------------------------------------------
        // Instance Variables

        T min{};
        T max{};

        //--------------------------------------------------------------------------
        // Construction

        constexpr span() noexcept = default;
        constexpr span(const span & v) noexcept = default;
        constexpr span(span && v) noexcept = default;
        template <Number U> constexpr explicit span(const span1<U> & v) noexcept;
        template <Number U, int t_m> constexpr explicit span(const span<U, t_m> & v) noexcept;
        constexpr span(T v1, T v2) noexcept;

        //--------------------------------------------------------------------------
        // Assignment

        span & operator=(const span & v) noexcept = default;
        span & operator=(span && v) noexcept = default;

        template <int t_m> span & operator=(const span<T, t_m> & v) noexcept;

    };

    template <Number T> struct span<T, 2> {

        //--------------------------------------------------------------------------
        // Static Members

        using Type = T;

        static constexpr int n{2};

        //--------------------------------------------------------------------------
        // Instance Variables

        vec2<T> min{};
        vec2<T> max{};

        //--------------------------------------------------------------------------
        // Construction

        constexpr span() noexcept = default;
        constexpr span(const span & v) noexcept = default;
        constexpr span(span && v) noexcept = default;
        template <Number U, int t_m> constexpr explicit span(const span<U, t_m> & v) noexcept;
        constexpr span(T v1, T v2) noexcept;
        constexpr span(const vec2<T> & v1, const vec2<T> & v2) noexcept;
        Q_CONSTEX span(const span1<T> & v1, const span1<T> & v2) noexcept;

        //--------------------------------------------------------------------------
        // Assignment

        span & operator=(const span & v) noexcept = default;
        span & operator=(span && v) noexcept = default;

        template <int t_m> span & operator=(const span<T, t_m> & v) noexcept;

        //--------------------------------------------------------------------------
        // Other

        Q_CONSTEX span1<T> x() const noexcept;
        Q_CONSTEX span1<T> y() const noexcept;

    };

    template <Number T> struct span<T, 3> {

        //--------------------------------------------------------------------------
        // Static Members

        using Type = T;

        static constexpr int n{3};

        //--------------------------------------------------------------------------
        // Instance Variables

        vec3<T> min{};
        vec3<T> max{};

        //--------------------------------------------------------------------------
        // Construction

        constexpr span() noexcept = default;
        constexpr span(const span & v) noexcept = default;
        constexpr span(span && v) noexcept = default;
        template <Number U, int t_m> constexpr explicit span(const span<U, t_m> & v) noexcept;
        constexpr span(T v1, T v2) noexcept;
        constexpr span(const vec3<T> & v1, const vec3<T> & v2) noexcept;
        Q_CONSTEX span(const span1<T> & v1, const span1<T> & v2, const span1<T> & v3) noexcept;
        Q_CX_ABLE span(const span2<T> & v1, const span1<T> & v2) noexcept;
        Q_CX_ABLE span(const span1<T> & v1, const span2<T> & v2) noexcept;

        //--------------------------------------------------------------------------
        // Assignment

        span & operator=(const span & v) noexcept = default;
        span & operator=(span && v) noexcept = default;

        template <int t_m> span & operator=(const span<T, t_m> & v) noexcept;

        //--------------------------------------------------------------------------
        // Other

        Q_CONSTEX span1<T> x() const noexcept;
        Q_CONSTEX span1<T> y() const noexcept;
        Q_CONSTEX span1<T> z() const noexcept;

        Q_CX_ABLE span2<T> xy() const noexcept;
        Q_CX_ABLE span2<T> yz() const noexcept;

    };

    template <Number T> struct span<T, 4> {

        //--------------------------------------------------------------------------
        // Static Members

        using Type = T;

        static constexpr int n{4};

        //--------------------------------------------------------------------------
        // Instance Variables

        vec4<T> min{};
        vec4<T> max{};

        //--------------------------------------------------------------------------
        // Construction

        constexpr span() noexcept = default;
        constexpr span(const span & v) noexcept = default;
        constexpr span(span && v) noexcept = default;
        template <Number U, int t_m> constexpr explicit span(const span<U, t_m> & v) noexcept;
        constexpr span(T v1, T v2) noexcept;
        constexpr span(const vec4<T> & v1, const vec4<T> & v2) noexcept;
        Q_CONSTEX span(const span1<T> & v1, const span1<T> & v2, const span1<T> & v3, const span1<T> & v4) noexcept;
        Q_CX_ABLE span(const span2<T> & v1, const span1<T> & v2, const span1<T> & v3) noexcept;
        Q_CX_ABLE span(const span1<T> & v1, const span2<T> & v2, const span1<T> & v3) noexcept;
        Q_CX_ABLE span(const span1<T> & v1, const span1<T> & v2, const span2<T> & v3) noexcept;
        Q_CX_ABLE span(const span2<T> & v1, const span2<T> & v2) noexcept;
        Q_CX_ABLE span(const span3<T> & v1, const span1<T> & v2) noexcept;
        Q_CX_ABLE span(const span1<T> & v1, const span3<T> & v2) noexcept;

        //--------------------------------------------------------------------------
        // Assignment

        span & operator=(const span & v) noexcept = default;
        span & operator=(span && v) noexcept = default;

        template <int t_m> span & operator=(const span<T, t_m> & v) noexcept;

        //--------------------------------------------------------------------------
        // Other

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

    //==================================================================================================================
    // Constants ///////////////////////////////////////////////////////////////////////////////////////////////////////
    //------------------------------------------------------------------------------------------------------------------

    template <Floater T, int t_n> constexpr span<T, t_n>  infspan = span<T, t_n>(-infinity<T>, infinity<T>);
    template <Floater T, int t_n> constexpr span<T, t_n>  nanspan = span<T, t_n>(nan<T>, nan<T>);
    template <Floater T, int t_n> constexpr span<T, t_n> nullspan = span<T, t_n>(infinity<T>, -infinity<T>);

    //==================================================================================================================
    // Functions ///////////////////////////////////////////////////////////////////////////////////////////////////////
    //==================================================================================================================

    //==============================================================================
    // Arithmetic Assignment
    //------------------------------------------------------------------------------

    template <Number T, int t_n> Q_CX_ABLE span<T, t_n> & operator+=(span<T, t_n> & v1, T v2);
    template <Number T, int t_n> Q_CX_ABLE span<T, t_n> & operator+=(span<T, t_n> & v1, const vec<T, t_n> & v2);

    template <Number T, int t_n> Q_CX_ABLE span<T, t_n> & operator-=(span<T, t_n> & v1, T v2);
    template <Number T, int t_n> Q_CX_ABLE span<T, t_n> & operator-=(span<T, t_n> & v1, const vec<T, t_n> & v2);

    //==============================================================================
    // Arithmetic
    //------------------------------------------------------------------------------

    template <Number T, int t_n> Q_CX_ABLE span<T, t_n> operator+(const span<T, t_n> & v1, T v2);
    template <Number T, int t_n> Q_CX_ABLE span<T, t_n> operator+(T v1, const span<T, t_n> & v2);
    template <Number T, int t_n> Q_CX_ABLE span<T, t_n> operator+(const span<T, t_n> & v1, const vec<T, t_n> & v2);
    template <Number T, int t_n> Q_CX_ABLE span<T, t_n> operator+(const vec<T, t_n> & v1, const span<T, t_n> & v2);

    template <Number T, int t_n> Q_CX_ABLE span<T, t_n> operator-(const span<T, t_n> & v1, T v2);
    template <Number T, int t_n> Q_CX_ABLE span<T, t_n> operator-(T v1, const span<T, t_n> & v2);
    template <Number T, int t_n> Q_CX_ABLE span<T, t_n> operator-(const span<T, t_n> & v1, const vec<T, t_n> & v2);
    template <Number T, int t_n> Q_CX_ABLE span<T, t_n> operator-(const vec<T, t_n> & v1, const span<T, t_n> & v2);

    //==============================================================================
    // Comparison
    //------------------------------------------------------------------------------

    template <typename T, int t_n> Q_CX_ABLE bool operator==(const span<T, t_n> & v1, const span<T, t_n> & v2);

    template <typename T, int t_n> Q_CX_ABLE bool operator!=(const span<T, t_n> & v1, const span<T, t_n> & v2);

}

// INLINE IMPLEMENTATION ///////////////////////////////////////////////////////////////////////////////////////////////

namespace qc {

    //------------------------------------------------------------------------------
    // Constructors

    template <Number T>
    template <Number U>
    inline constexpr span<T, 1>::span(const span1<U> & v) noexcept :
        min(T(v.min)),
        max(T(v.max))
    {}

    template <Number T>
    template <Number U, int t_m>
    inline constexpr span<T, 1>::span(const span<U, t_m> & v) noexcept :
        min(T(v.min.x)),
        max(T(v.max.x))
    {}

    template <Number T>
    inline constexpr span<T, 1>::span(T v1, T v2) noexcept :
        min(v1),
        max(v2)
    {}

    //------------------------------------------------------------------------------
    // Assignment

    template <Number T>
    template <int t_m>
    inline span1<T> & span<T, 1>::operator=(const span<T, t_m> & v) noexcept {
        min = v.min.x;
        max = v.max.x;
        return *this;
    }

    //------------------------------------------------------------------------------
    // Constructors

    template <Number T>
    template <Number U, int t_m>
    inline constexpr span<T, 2>::span(const span<U, t_m> & v) noexcept :
        min(v.min),
        max(v.max)
    {}

    template <Number T>
    inline constexpr span<T, 2>::span(T v1, T v2) noexcept :
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

    //------------------------------------------------------------------------------
    // Assignment

    template <Number T>
    template <int t_m>
    inline span2<T> & span<T, 2>::operator=(const span<T, t_m> & v) noexcept {
        min = v.min;
        max = v.max;
        return *this;
    }

    //------------------------------------------------------------------------------
    // Other

    template <Number T>
    inline Q_CONSTEX span1<T> span<T, 2>::x() const noexcept {
        return {min.x, max.x};
    }

    template <Number T>
    inline Q_CONSTEX span1<T> span<T, 2>::y() const noexcept {
        return {min.y, max.y};
    }

    //------------------------------------------------------------------------------
    // Constructors

    template <Number T>
    template <Number U, int t_m>
    inline constexpr span<T, 3>::span(const span<U, t_m> & v) noexcept :
        min(v.min),
        max(v.max)
    {}

    template <Number T>
    inline constexpr span<T, 3>::span(T v1, T v2) noexcept :
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

    //------------------------------------------------------------------------------
    // Assignment

    template <Number T>
    template <int t_m>
    inline span3<T> & span<T, 3>::operator=(const span<T, t_m> & v) noexcept {
        min = v.min;
        max = v.max;
        return *this;
    }

    //------------------------------------------------------------------------------
    // Other

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

    //------------------------------------------------------------------------------
    // Constructors

    template <Number T>
    template <Number U, int t_m>
    inline constexpr span<T, 4>::span(const span<U, t_m> & v) noexcept :
        min(v.min),
        max(v.max)
    {}

    template <Number T>
    inline constexpr span<T, 4>::span(T v1, T v2) noexcept :
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

    //------------------------------------------------------------------------------
    // Assignment

    template <Number T>
    template <int t_m>
    inline span4<T> & span<T, 4>::operator=(const span<T, t_m> & v) noexcept {
        min = v.min;
        max = v.max;
        return *this;
    }

    //------------------------------------------------------------------------------
    // Other

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

    //==================================================================================================================
    // FUNCTION IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////
    //==================================================================================================================

    //------------------------------------------------------------------------------
    // Arithmetic Assignment

    //--- add assign ---

    template <Number T, int t_n>
    inline Q_CX_ABLE span<T, t_n> & operator+=(span<T, t_n> & v1, T v2) {
        v1.min += v2;
        v1.max += v2;
        return v1;
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE span<T, t_n> & operator+=(span<T, t_n> & v1, const vec<T, t_n> & v2) {
        v1.min += v2;
        v1.max += v2;
        return v1;
    }

    //--- subtract assign ---

    template <Number T, int t_n>
    inline Q_CX_ABLE span<T, t_n> & operator-=(span<T, t_n> & v1, T v2) {
        v1.min -= v2;
        v1.max -= v2;
        return v1;
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE span<T, t_n> & operator-=(span<T, t_n> & v1, const vec<T, t_n> & v2) {
        v1.min -= v2;
        v1.max -= v2;
        return v1;
    }

    //------------------------------------------------------------------------------
    // Arithmetic Operators

    //--- add ---

    template <Number T, int t_n>
    inline Q_CX_ABLE span<T, t_n> operator+(const span<T, t_n> & v1, T v2) {
        if constexpr (t_n == 1) return {T(v1.min + v2), T(v1.max + v2)};
        else return {v1.min + v2, v1.max + v2};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE span<T, t_n> operator+(T v1, const span<T, t_n> & v2) {
        return v2 + v1;
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE span<T, t_n> operator+(const span<T, t_n> & v1, const vec<T, t_n> & v2) {
        return {v1.min + v2, v1.max + v2};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE span<T, t_n> operator+(const vec<T, t_n> & v1, const span<T, t_n> & v2) {
        return v2 + v1;
    }

    //--- subtract ---

    template <Number T, int t_n>
    inline Q_CX_ABLE span<T, t_n> operator-(const span<T, t_n> & v1, T v2) {
        if constexpr (t_n == 1) return {T(v1.min - v2), T(v1.max - v2)};
        else return {v1.min - v2, v1.max - v2};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE span<T, t_n> operator-(T v1, const span<T, t_n> & v2) {
        if constexpr (t_n == 1) return {T(v1 - v2.min), T(v1 - v2.max)};
        else return {v1 - v2.min, v1 - v2.max};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE span<T, t_n> operator-(const span<T, t_n> & v1, const vec<T, t_n> & v2) {
        return {v1.min - v2, v1.max - v2};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE span<T, t_n> operator-(const vec<T, t_n> & v1, const span<T, t_n> & v2) {
        return {v1 - v2.min, v1 - v2.max};
    }

    //------------------------------------------------------------------------------
    // Comparison Operators

    //--- equal to ---

    template <typename T, int t_n>
    inline Q_CX_ABLE bool operator==(const span<T, t_n> & v1, const span<T, t_n> & v2) {
        return v1.min == v2.min && v1.max == v2.max;
    }

    //--- not equal to ---

    template <typename T, int t_n>
    inline Q_CX_ABLE bool operator!=(const span<T, t_n> & v1, const span<T, t_n> & v2) {
        return !(v1 == v2);
    }

}
