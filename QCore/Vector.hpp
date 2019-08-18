#pragma once

#include "CoreFunc.hpp"

namespace qc {

//======================================================================================================================
// TYPES ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================

//==============================================================================
// Vec Types
//------------------------------------------------------------------------------

template <typename T, int t_n> struct vec;

namespace types {

    using qc::vec;

    template <typename T> using vec2 = vec<T, 2>;
    template <typename T> using vec3 = vec<T, 3>;
    template <typename T> using vec4 = vec<T, 4>;

    template <int t_n> using  fvec = vec< f32, t_n>;
    template <int t_n> using  dvec = vec< f64, t_n>;
    template <int t_n> using  cvec = vec< s08, t_n>;
    template <int t_n> using ucvec = vec< u08, t_n>;
    template <int t_n> using  svec = vec< s16, t_n>;
    template <int t_n> using usvec = vec< u16, t_n>;
    template <int t_n> using  ivec = vec< s32, t_n>;
    template <int t_n> using uivec = vec< u32, t_n>;
    template <int t_n> using  lvec = vec< s64, t_n>;
    template <int t_n> using ulvec = vec< u64, t_n>;
    template <int t_n> using  nvec = vec< nat, t_n>;
    template <int t_n> using unvec = vec<unat, t_n>;
    template <int t_n> using  bvec = vec<bool, t_n>;

    using  fvec2 = vec< f32, 2>;
    using  fvec3 = vec< f32, 3>;
    using  fvec4 = vec< f32, 4>;
    using  dvec2 = vec< f64, 2>;
    using  dvec3 = vec< f64, 3>;
    using  dvec4 = vec< f64, 4>;
    using  cvec2 = vec< s08, 2>;
    using  cvec3 = vec< s08, 3>;
    using  cvec4 = vec< s08, 4>;
    using ucvec2 = vec< u08, 2>;
    using ucvec3 = vec< u08, 3>;
    using ucvec4 = vec< u08, 4>;
    using  svec2 = vec< s16, 2>;
    using  svec3 = vec< s16, 3>;
    using  svec4 = vec< s16, 4>;
    using usvec2 = vec< u16, 2>;
    using usvec3 = vec< u16, 3>;
    using usvec4 = vec< u16, 4>;
    using  ivec2 = vec< s32, 2>;
    using  ivec3 = vec< s32, 3>;
    using  ivec4 = vec< s32, 4>;
    using uivec2 = vec< u32, 2>;
    using uivec3 = vec< u32, 3>;
    using uivec4 = vec< u32, 4>;
    using  lvec2 = vec< s64, 2>;
    using  lvec3 = vec< s64, 3>;
    using  lvec4 = vec< s64, 4>;
    using ulvec2 = vec< u64, 2>;
    using ulvec3 = vec< u64, 3>;
    using ulvec4 = vec< u64, 4>;
    using  nvec2 = vec< nat, 2>;
    using  nvec3 = vec< nat, 3>;
    using  nvec4 = vec< nat, 4>;
    using unvec2 = vec<unat, 2>;
    using unvec3 = vec<unat, 3>;
    using unvec4 = vec<unat, 4>;
    using  bvec2 = vec<bool, 2>;
    using  bvec3 = vec<bool, 3>;
    using  bvec4 = vec<bool, 4>;

}

//==============================================================================
// Span Types
//------------------------------------------------------------------------------

template <typename T, int t_n> struct span;

namespace types {

    using qc::span;

    template <typename T> using span1 = span<T, 1>;
    template <typename T> using span2 = span<T, 2>;
    template <typename T> using span3 = span<T, 3>;
    template <typename T> using span4 = span<T, 4>;

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

//======================================================================================================================
// VEC2 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================

template <typename T> struct vec<T, 2> {

    static_assert(is_arithmetic_v<T>, "`qc::vec2<T>` must have arithmetic `T`");

    //--------------------------------------------------------------------------
    // Static Members

    using type = T;

    static constexpr int n{2};

    //--------------------------------------------------------------------------
    // Instance Variables

    union {
        struct { T x, y; };
        struct { T r, g; };
        struct { T s, t; };
        struct { T i, j; };
        struct { T rad, theta; };
        struct { T _0, _1; };
    };

    //--------------------------------------------------------------------------
    // Construction

    constexpr vec() noexcept;
    constexpr vec(const vec2<T> & v) noexcept = default;
    constexpr vec(vec2<T> && v) noexcept = default;
    
    constexpr explicit vec(T v) noexcept;
    template <typename U> constexpr explicit vec(const U & v) noexcept;

    template <typename U> constexpr explicit vec(const vec2<U> & v) noexcept;
    template <typename U> constexpr explicit vec(const vec3<U> & v) noexcept;
    template <typename U> constexpr explicit vec(const vec4<U> & v) noexcept;

    constexpr vec(T v1, T v2) noexcept;

    //--------------------------------------------------------------------------
    // Assignment

    vec2<T> & operator=(const vec2<T> & v) noexcept = default;
    vec2<T> & operator=(vec2<T> && v) noexcept = default;
    
    vec2<T> & operator=(T v) noexcept;
    template <int t_n> vec2<T> & operator=(const vec<T, t_n> & v) noexcept;

    //--------------------------------------------------------------------------
    // Conversion

    template <typename U, typename = eif_arithmetic_t<U>> constexpr explicit operator U() const noexcept { return U(x); }

    //--------------------------------------------------------------------------
    // Access

    template <int t_i> T & at() noexcept;
    template <int t_i> constexpr T at() const noexcept;

    T & operator[](int i);
    T operator[](int i) const;

};

//======================================================================================================================
// VEC3 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================

template <typename T> struct vec<T, 3> {

    static_assert(is_arithmetic_v<T>, "`qc::vec3<T>` must have arithmetic `T`");

    //--------------------------------------------------------------------------
    // Static Members

    using type = T;

    static constexpr int n{3};

    //--------------------------------------------------------------------------
    // Instance Variables

    union {
        struct { T x, y, z; };
        struct { T r, g, b; };
        struct { T s, t, p; };
        struct { T i, j, k; };
        struct { T rad, theta, phi; };
        struct { T alpha, beta, gamma; };
        struct { T hue, sat, val; };
        struct { T _0, _1, _2; };
    };

    //--------------------------------------------------------------------------
    // Construction

    constexpr vec() noexcept;
    constexpr vec(const vec3<T> & v) noexcept = default;
    constexpr vec(vec3<T> && v) noexcept = default;
    
    constexpr explicit vec(T v) noexcept;
    template <typename U> constexpr explicit vec(const U & v) noexcept;

    template <typename U> constexpr explicit vec(const vec2<U> & v) noexcept;
    template <typename U> constexpr explicit vec(const vec3<U> & v) noexcept;
    template <typename U> constexpr explicit vec(const vec4<U> & v) noexcept;
    
    constexpr vec(T v1, T v2, T v3) noexcept;
    Q_CONSTEX vec(const vec2<T> & v1, T v2) noexcept;
    Q_CX_ABLE vec(T v1, const vec2<T> & v2) noexcept;

    //--------------------------------------------------------------------------
    // Assignment

    vec3<T> & operator=(const vec3<T> & v) noexcept = default;
    vec3<T> & operator=(vec3<T> && v) noexcept = default;

    vec3<T> & operator=(T v) noexcept;
    template <int t_n> vec3<T> & operator=(const vec<T, t_n> & v) noexcept;

    //--------------------------------------------------------------------------
    // Conversion

    template <typename U, typename = eif_arithmetic_t<U>> constexpr explicit operator U() const noexcept { return U(x); }

    //--------------------------------------------------------------------------
    // Access

    template <int t_i> T & at() noexcept;
    template <int t_i> constexpr T at() const noexcept;

    T & operator[](int i);
    T operator[](int i) const;

    vec2<T> & xy() noexcept;
    vec2<T> & rg() noexcept { return xy(); }
    vec2<T> & st() noexcept { return xy(); }
    Q_CX_ABLE const vec2<T> & xy() const noexcept;
    Q_CX_ABLE const vec2<T> & rg() const noexcept { return rg(); }
    Q_CX_ABLE const vec2<T> & st() const noexcept { return st(); }

    vec2<T> & yz() noexcept;
    vec2<T> & gb() noexcept { return yz(); }
    vec2<T> & tp() noexcept { return yz(); }
    Q_CX_ABLE const vec2<T> & yz() const noexcept;
    Q_CX_ABLE const vec2<T> & gb() const noexcept { return gb(); }
    Q_CX_ABLE const vec2<T> & tp() const noexcept { return tp(); }

};

//======================================================================================================================
// VEC4 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================

template <typename T> struct vec<T, 4> {

    static_assert(is_arithmetic_v<T>, "`qc::vec4<T>` must have arithmetic `T`");

    //--------------------------------------------------------------------------
    // Static Members

    using type = T;

    static constexpr int n{4};

    //--------------------------------------------------------------------------
    // Instance Variables
    
    union {
        struct { T x, y, z, w; };
        struct { T r, g, b, a; };
        struct { T s, t, p, q; };
        struct { T _0, _1, _2, _3; };
    };
    
    //--------------------------------------------------------------------------
    // Construction

    constexpr vec() noexcept;
    constexpr vec(const vec4<T> & v) noexcept = default;
    constexpr vec(vec4<T> && v) noexcept = default;
    
    constexpr explicit vec(T v) noexcept;
    template <typename U> constexpr explicit vec(const U & v) noexcept;

    template <typename U> constexpr explicit vec(const vec2<U> & v) noexcept;
    template <typename U> constexpr explicit vec(const vec3<U> & v) noexcept;
    template <typename U> constexpr explicit vec(const vec4<U> & v) noexcept;
    
    constexpr vec(T v1, T v2, T v3, T v4) noexcept;
    Q_CONSTEX vec(const vec2<T> & v1, T v2, T v3) noexcept;
    Q_CX_ABLE vec(T v1, const vec2<T> & v2, T v3) noexcept;
    Q_CX_ABLE vec(T v1, T v2, const vec2<T> & v3) noexcept;
    Q_CONSTEX vec(const vec2<T> & v1, const vec2<T> & v2) noexcept;
    Q_CONSTEX vec(const vec3<T> & v1, T v2) noexcept;
    Q_CX_ABLE vec(T v1, const vec3<T> & v2) noexcept;

    //--------------------------------------------------------------------------
    // Assignment

    vec4<T> & operator=(const vec4<T> & v) noexcept = default;
    vec4<T> & operator=(vec4<T> && v) noexcept = default;

    vec4<T> & operator=(T v) noexcept;
    template <int t_n> vec4<T> & operator=(const vec<T, t_n> & v) noexcept;

    //--------------------------------------------------------------------------
    // Conversion

    template <typename U, typename = eif_arithmetic_t<U>> constexpr explicit operator U() const noexcept { return U(x); }

    //--------------------------------------------------------------------------
    // Access

    template <int t_i> T & at() noexcept;
    template <int t_i> constexpr T at() const noexcept;
    
    T & operator[](int i);
    T operator[](int i) const;

    vec2<T> & xy() noexcept;
    vec2<T> & rg() noexcept { return xy(); }
    vec2<T> & st() noexcept { return xy(); }
    Q_CX_ABLE const vec2<T> & xy() const noexcept;
    Q_CX_ABLE const vec2<T> & rg() const noexcept { return rg(); }
    Q_CX_ABLE const vec2<T> & st() const noexcept { return st(); }

    vec2<T> & yz() noexcept;
    vec2<T> & gb() noexcept { return yz(); }
    vec2<T> & tp() noexcept { return yz(); }
    Q_CX_ABLE const vec2<T> & yz() const noexcept;
    Q_CX_ABLE const vec2<T> & gb() const noexcept { return gb(); }
    Q_CX_ABLE const vec2<T> & tp() const noexcept { return tp(); }

    vec2<T> & zw() noexcept;
    vec2<T> & ba() noexcept { return zw(); }
    vec2<T> & pq() noexcept { return zw(); }
    Q_CX_ABLE const vec2<T> & zw() const noexcept;
    Q_CX_ABLE const vec2<T> & ba() const noexcept { return ba(); }
    Q_CX_ABLE const vec2<T> & pq() const noexcept { return pq(); }

    vec3<T> & xyz() noexcept;
    vec3<T> & rgb() noexcept { return xyz(); }
    vec3<T> & stp() noexcept { return xyz(); }
    Q_CX_ABLE const vec3<T> & xyz() const noexcept;
    Q_CX_ABLE const vec3<T> & rgb() const noexcept { return rgb(); }
    Q_CX_ABLE const vec3<T> & stp() const noexcept { return stp(); }

    vec3<T> & yzw() noexcept;
    vec3<T> & gba() noexcept { return yzw(); }
    vec3<T> & tpq() noexcept { return yzw(); }
    Q_CX_ABLE const vec3<T> & yzw() const noexcept;
    Q_CX_ABLE const vec3<T> & gba() const noexcept { return gba(); }
    Q_CX_ABLE const vec3<T> & tpq() const noexcept { return tpq(); }

};

//======================================================================================================================
// SPAN ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================

template <typename T, int t_n> struct span {

    static_assert(is_arithmetic_v<T>, "`qc::span<T, t_n>` must have arithmetic `T`");
    static_assert(t_n >= 1 && t_n <= 4, "`qc::span<T, t_n>` must have `t_n` in range [1, 4]");

    //--------------------------------------------------------------------------
    // Static Members

    using type = T;
    using V = std::conditional_t<t_n == 1, T, vec<T, t_n>>;

    static constexpr int n{t_n};

    //--------------------------------------------------------------------------
    // Instance Variables

    V min, max;

    //--------------------------------------------------------------------------
    // Construction

    constexpr span() noexcept;
    constexpr span(const span<T, t_n> & v) noexcept = default;
    constexpr span(span<T, t_n> && v) noexcept = default;
    template <typename U, int t_m> constexpr explicit span(const span<U, t_m> & v) noexcept;
    constexpr span(const V & v1, const V & v2) noexcept;
    template <typename = eif_t<(t_n > 1)>> constexpr span(T v1, T v2) noexcept;
    template <typename = eif_t<t_n == 2>> Q_CONSTEX span(const span1<T> & v1, const span1<T> & v2) noexcept;
    template <typename = eif_t<t_n == 3>> Q_CONSTEX span(const span1<T> & v1, const span1<T> & v2, const span1<T> & v3) noexcept;
    template <typename = eif_t<t_n == 3>> Q_CX_ABLE span(const span2<T> & v1, const span1<T> & v2) noexcept;
    template <typename = eif_t<t_n == 3>> Q_CX_ABLE span(const span1<T> & v1, const span2<T> & v2) noexcept;
    template <typename = eif_t<t_n == 4>> Q_CONSTEX span(const span1<T> & v1, const span1<T> & v2, const span1<T> & v3, const span1<T> & v4) noexcept;
    template <typename = eif_t<t_n == 4>> Q_CX_ABLE span(const span2<T> & v1, const span1<T> & v2, const span1<T> & v3) noexcept;
    template <typename = eif_t<t_n == 4>> Q_CX_ABLE span(const span1<T> & v1, const span2<T> & v2, const span1<T> & v3) noexcept;
    template <typename = eif_t<t_n == 4>> Q_CX_ABLE span(const span1<T> & v1, const span1<T> & v2, const span2<T> & v3) noexcept;
    template <typename = eif_t<t_n == 4>> Q_CX_ABLE span(const span2<T> & v1, const span2<T> & v2) noexcept;
    template <typename = eif_t<t_n == 4>> Q_CX_ABLE span(const span3<T> & v1, const span1<T> & v2) noexcept;
    template <typename = eif_t<t_n == 4>> Q_CX_ABLE span(const span1<T> & v1, const span3<T> & v2) noexcept;

    //--------------------------------------------------------------------------
    // Assignment

    span<T, t_n> & operator=(const span<T, t_n> & v) noexcept = default;
    span<T, t_n> & operator=(span<T, t_n> && v) noexcept = default;

    template <int t_m> span<T, t_n> & operator=(const span<T, t_m> & v) noexcept;

    //--------------------------------------------------------------------------
    // Other

    template <typename = eif_t<(t_n >= 2)>> Q_CONSTEX span1<T> x() const noexcept;
    template <typename = eif_t<(t_n >= 2)>> Q_CONSTEX span1<T> y() const noexcept;
    template <typename = eif_t<(t_n >= 3)>> Q_CONSTEX span1<T> z() const noexcept;
    template <typename = eif_t<(t_n >= 4)>> Q_CONSTEX span1<T> w() const noexcept;

    template <typename = eif_t<(t_n >= 3)>> Q_CX_ABLE span2<T> xy() const noexcept;
    template <typename = eif_t<(t_n >= 3)>> Q_CX_ABLE span2<T> yz() const noexcept;
    template <typename = eif_t<(t_n >= 4)>> Q_CX_ABLE span2<T> zw() const noexcept;

    template <typename = eif_t<(t_n >= 4)>> Q_CX_ABLE span3<T> xyz() const noexcept;
    template <typename = eif_t<(t_n >= 4)>> Q_CX_ABLE span3<T> yzw() const noexcept;

    Q_CX_ABLE V size() const noexcept;

};

//======================================================================================================================
// Constants ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------------------------

template <typename T, int t_n> constexpr vec<T, t_n> px{};
template <typename T, int t_n> constexpr vec<T, t_n> nx{};
template <typename T, int t_n> constexpr vec<T, t_n> py{};
template <typename T, int t_n> constexpr vec<T, t_n> ny{};
template <typename T, int t_n> constexpr vec<T, t_n> pz{};
template <typename T, int t_n> constexpr vec<T, t_n> nz{};
template <typename T, int t_n> constexpr vec<T, t_n> pw{};
template <typename T, int t_n> constexpr vec<T, t_n> nw{};
template <typename T> constexpr vec2<T> px<T, 2> = vec2<T>(T( 1), T( 0));
template <typename T> constexpr vec2<T> nx<T, 2> = vec2<T>(T(-1), T( 0));
template <typename T> constexpr vec3<T> px<T, 3> = vec3<T>(T( 1), T( 0), T( 0));
template <typename T> constexpr vec3<T> nx<T, 3> = vec3<T>(T(-1), T( 0), T( 0));
template <typename T> constexpr vec4<T> px<T, 4> = vec4<T>(T( 1), T( 0), T( 0), T( 0));
template <typename T> constexpr vec4<T> nx<T, 4> = vec4<T>(T(-1), T( 0), T( 0), T( 0));
template <typename T> constexpr vec2<T> py<T, 2> = vec2<T>(T( 0), T( 1));
template <typename T> constexpr vec2<T> ny<T, 2> = vec2<T>(T( 0), T(-1));
template <typename T> constexpr vec3<T> py<T, 3> = vec3<T>(T( 0), T( 1), T( 0));
template <typename T> constexpr vec3<T> ny<T, 3> = vec3<T>(T( 0), T(-1), T( 0));
template <typename T> constexpr vec4<T> py<T, 4> = vec4<T>(T( 0), T( 1), T( 0), T( 0));
template <typename T> constexpr vec4<T> ny<T, 4> = vec4<T>(T( 0), T(-1), T( 0), T( 0));
template <typename T> constexpr vec3<T> pz<T, 3> = vec3<T>(T( 0), T( 0), T( 1));
template <typename T> constexpr vec3<T> nz<T, 3> = vec3<T>(T( 0), T( 0), T(-1));
template <typename T> constexpr vec4<T> pz<T, 4> = vec4<T>(T( 0), T( 0), T( 1), T( 0));
template <typename T> constexpr vec4<T> nz<T, 4> = vec4<T>(T( 0), T( 0), T(-1), T( 0));
template <typename T> constexpr vec4<T> pw<T, 4> = vec4<T>(T( 0), T( 0), T( 0), T( 1));
template <typename T> constexpr vec4<T> nw<T, 4> = vec4<T>(T( 0), T( 0), T( 0), T(-1));
template <typename T> constexpr vec2<T> px2 = px<T, 2>;
template <typename T> constexpr vec2<T> nx2 = nx<T, 2>;
template <typename T> constexpr vec3<T> px3 = px<T, 3>;
template <typename T> constexpr vec3<T> nx3 = nx<T, 3>;
template <typename T> constexpr vec4<T> px4 = px<T, 4>;
template <typename T> constexpr vec4<T> nx4 = nx<T, 4>;
template <typename T> constexpr vec2<T> py2 = py<T, 2>;
template <typename T> constexpr vec2<T> ny2 = ny<T, 2>;
template <typename T> constexpr vec3<T> py3 = py<T, 3>;
template <typename T> constexpr vec3<T> ny3 = ny<T, 3>;
template <typename T> constexpr vec4<T> py4 = py<T, 4>;
template <typename T> constexpr vec4<T> ny4 = ny<T, 4>;
template <typename T> constexpr vec3<T> pz3 = pz<T, 3>;
template <typename T> constexpr vec3<T> nz3 = nz<T, 3>;
template <typename T> constexpr vec4<T> pz4 = pz<T, 4>;
template <typename T> constexpr vec4<T> nz4 = nz<T, 4>;
template <typename T> constexpr vec4<T> pw4 = pw<T, 4>;
template <typename T> constexpr vec4<T> nw4 = nw<T, 4>;

template <typename T, int t_n> constexpr vec<T, t_n> infvec = vec<T, t_n>(infinity<T>);
template <typename T, int t_n> constexpr vec<T, t_n> nanvec = vec<T, t_n>(     nan<T>);

template <typename T, int t_n, typename = eif_signed_t<T>> constexpr span<T, t_n>  infspan = span<T, t_n>(-infinity<T>, infinity<T>);
template <typename T, int t_n>                             constexpr span<T, t_n>  nanspan = span<T, t_n>(     nan<T>,       nan<T>);
template <typename T, int t_n, typename = eif_signed_t<T>> constexpr span<T, t_n> nullspan = span<T, t_n>(infinity<T>, -infinity<T>);

//======================================================================================================================
// Functions ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================

//==============================================================================
// Arithmetic Assignment
//------------------------------------------------------------------------------

template <typename T, int t_n> vec<T, t_n> & operator++(vec<T, t_n> & v);
template <typename T, int t_n> vec<T, t_n>   operator++(vec<T, t_n> & v, int);

template <typename T, int t_n> vec<T, t_n> & operator--(vec<T, t_n> & v);
template <typename T, int t_n> vec<T, t_n>   operator--(vec<T, t_n> & v, int);

template <typename T, int t_n> vec<T, t_n> & operator+=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> vec<T, t_n> & operator+=(vec<T, t_n> & v1, T v2);

template <typename T, int t_n> vec<T, t_n> & operator-=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> vec<T, t_n> & operator-=(vec<T, t_n> & v1, T v2);

template <typename T, int t_n> vec<T, t_n> & operator*=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> vec<T, t_n> & operator*=(vec<T, t_n> & v1, T v2);

template <typename T, int t_n> vec<T, t_n> & operator/=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> vec<T, t_n> & operator/=(vec<T, t_n> & v1, T v2);

template <typename T, int t_n> vec<T, t_n> & operator%=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> vec<T, t_n> & operator%=(vec<T, t_n> & v1, T v2);

//==============================================================================
// Arithmetic
//------------------------------------------------------------------------------

template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator+(const vec<T, t_n> & v);

template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator-(const vec<T, t_n> & v);

template <typename T, int t_n> Q_CX_ABLE  vec<T, t_n> operator+(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE  vec<T, t_n> operator+(const vec<T, t_n> & v1, T v2);
template <typename T, int t_n> Q_CX_ABLE  vec<T, t_n> operator+(T v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE span<T, t_n> operator+(const span<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE span<T, t_n> operator+(const vec<T, t_n> & v1, const span<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE span<T, t_n> operator+(const span<T, t_n> & v1, T v2);
template <typename T, int t_n> Q_CX_ABLE span<T, t_n> operator+(T v1, const span<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE  vec<T, t_n> operator-(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE  vec<T, t_n> operator-(const vec<T, t_n> & v1, T v2);
template <typename T, int t_n> Q_CX_ABLE  vec<T, t_n> operator-(T v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE span<T, t_n> operator-(const span<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE span<T, t_n> operator-(const vec<T, t_n> & v1, const span<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE span<T, t_n> operator-(const span<T, t_n> & v1, T v2);
template <typename T, int t_n> Q_CX_ABLE span<T, t_n> operator-(T v1, const span<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator*(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator*(const vec<T, t_n> & v1, T v2);
template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator*(T v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE span<T, t_n> operator*(const span<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE span<T, t_n> operator*(const vec<T, t_n> & v1, const span<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE span<T, t_n> operator*(const span<T, t_n> & v1, T v2);
template <typename T, int t_n> Q_CX_ABLE span<T, t_n> operator*(T v1, const span<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator/(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator/(const vec<T, t_n> & v1, T v2);
template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator/(T v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE span<T, t_n> operator/(const span<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE span<T, t_n> operator/(const vec<T, t_n> & v1, const span<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE span<T, t_n> operator/(const span<T, t_n> & v1, T v2);
template <typename T, int t_n> Q_CX_ABLE span<T, t_n> operator/(T v1, const span<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator%(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator%(const vec<T, t_n> & v1, T v2);
template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator%(T v1, const vec<T, t_n> & v2);

//==============================================================================
// Comparison
//------------------------------------------------------------------------------

template <typename T, int t_n> Q_CX_ABLE      bool operator==(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator==(const vec<T, t_n> & v1, T v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator==(T v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE      bool operator==(const span<T, t_n> & v1, const span<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE      bool operator!=(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator!=(const vec<T, t_n> & v1, T v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator!=(T v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE      bool operator!=(const span<T, t_n> & v1, const span<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator<(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator<(const vec<T, t_n> & v1, T v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator<(T v1, const vec<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator>(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator>(const vec<T, t_n> & v1, T v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator>(T v1, const vec<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator<=(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator<=(const vec<T, t_n> & v1, T v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator<=(T v1, const vec<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator>=(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator>=(const vec<T, t_n> & v1, T v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator>=(T v1, const vec<T, t_n> & v2);

//==============================================================================
// Logic
//------------------------------------------------------------------------------

template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator&&(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator||(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator!(const vec<T, t_n> & v1);

//==============================================================================
// Condensation
//------------------------------------------------------------------------------

template <typename T, int t_n> Q_CX_ABLE T sum(const vec<T, t_n> & v);

template <typename T, int t_n> Q_CX_ABLE T product(const vec<T, t_n> & v);

template <typename T, int t_n> Q_CX_ABLE bool any(const vec<T, t_n> & v);

template <typename T, int t_n> Q_CX_ABLE bool all(const vec<T, t_n> & v);

//==============================================================================
// min
//------------------------------------------------------------------------------

template <typename T, int t_n> Q_CX_ABLE T min(const vec<T, t_n> & v);

template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> min(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> min(const vec<T, t_n> & v1, T v2);

template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> min(T v1, const vec<T, t_n> & v2);

//==============================================================================
// max
//------------------------------------------------------------------------------

template <typename T, int t_n> Q_CX_ABLE T max(const vec<T, t_n> & v);

template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> max(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> max(const vec<T, t_n> & v1, T v2);

template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> max(T v1, const vec<T, t_n> & v2);

//==============================================================================
// minify
//------------------------------------------------------------------------------

template <typename T, int t_n> vec<T, t_n> & minify(vec<T, t_n> & min, const vec<T, t_n> & v);

template <typename T, int t_n> vec<T, t_n> & minify(vec<T, t_n> & min, T v);

//==============================================================================
// maxify
//------------------------------------------------------------------------------

template <typename T, int t_n> vec<T, t_n> & maxify(vec<T, t_n> & max, const vec<T, t_n> & v);

template <typename T, int t_n> vec<T, t_n> & maxify(vec<T, t_n> & max, T v);

}

#include "Vector.tpp"
