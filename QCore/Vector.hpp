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

    template <typename T> using vec1 = vec<T, 1>;
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

    using  fvec1 = vec< f32, 1>;
    using  fvec2 = vec< f32, 2>;
    using  fvec3 = vec< f32, 3>;
    using  fvec4 = vec< f32, 4>;
    using  dvec1 = vec< f64, 1>;
    using  dvec2 = vec< f64, 2>;
    using  dvec3 = vec< f64, 3>;
    using  dvec4 = vec< f64, 4>;
    using  cvec1 = vec< s08, 1>;
    using  cvec2 = vec< s08, 2>;
    using  cvec3 = vec< s08, 3>;
    using  cvec4 = vec< s08, 4>;
    using ucvec1 = vec< u08, 1>;
    using ucvec2 = vec< u08, 2>;
    using ucvec3 = vec< u08, 3>;
    using ucvec4 = vec< u08, 4>;
    using  svec1 = vec< s16, 1>;
    using  svec2 = vec< s16, 2>;
    using  svec3 = vec< s16, 3>;
    using  svec4 = vec< s16, 4>;
    using usvec1 = vec< u16, 1>;
    using usvec2 = vec< u16, 2>;
    using usvec3 = vec< u16, 3>;
    using usvec4 = vec< u16, 4>;
    using  ivec1 = vec< s32, 1>;
    using  ivec2 = vec< s32, 2>;
    using  ivec3 = vec< s32, 3>;
    using  ivec4 = vec< s32, 4>;
    using uivec1 = vec< u32, 1>;
    using uivec2 = vec< u32, 2>;
    using uivec3 = vec< u32, 3>;
    using uivec4 = vec< u32, 4>;
    using  lvec1 = vec< s64, 1>;
    using  lvec2 = vec< s64, 2>;
    using  lvec3 = vec< s64, 3>;
    using  lvec4 = vec< s64, 4>;
    using ulvec1 = vec< u64, 1>;
    using ulvec2 = vec< u64, 2>;
    using ulvec3 = vec< u64, 3>;
    using ulvec4 = vec< u64, 4>;
    using  nvec1 = vec< nat, 1>;
    using  nvec2 = vec< nat, 2>;
    using  nvec3 = vec< nat, 3>;
    using  nvec4 = vec< nat, 4>;
    using unvec1 = vec<unat, 1>;
    using unvec2 = vec<unat, 2>;
    using unvec3 = vec<unat, 3>;
    using unvec4 = vec<unat, 4>;
    using  bvec1 = vec<bool, 1>;
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



//==============================================================================
// Bound Types
//------------------------------------------------------------------------------



template <typename T, int t_n> using bound = span<T, t_n>;

namespace types {

    using qc::bound;

    template <typename T> using bound1 = span1<T>;
    template <typename T> using bound2 = span2<T>;
    template <typename T> using bound3 = span3<T>;
    template <typename T> using bound4 = span4<T>;

    template <int t_n> using  fbound = fspan<t_n>;
    template <int t_n> using  dbound = dspan<t_n>;
    template <int t_n> using  cbound = cspan<t_n>;
    template <int t_n> using ucbound = ucspan<t_n>;
    template <int t_n> using  sbound = sspan<t_n>;
    template <int t_n> using usbound = usspan<t_n>;
    template <int t_n> using  ibound = ispan<t_n>;
    template <int t_n> using uibound = uispan<t_n>;
    template <int t_n> using  lbound = lspan<t_n>;
    template <int t_n> using ulbound = ulspan<t_n>;
    template <int t_n> using  nbound = nspan<t_n>;
    template <int t_n> using unbound = unspan<t_n>;

    using  fbound1 = fspan1;
    using  fbound2 = fspan2;
    using  fbound3 = fspan3;
    using  fbound4 = fspan4;
    using  dbound1 = dspan1;
    using  dbound2 = dspan2;
    using  dbound3 = dspan3;
    using  dbound4 = dspan4;
    using  cbound1 = cspan1;
    using  cbound2 = cspan2;
    using  cbound3 = cspan3;
    using  cbound4 = cspan4;
    using ucbound1 = ucspan1;
    using ucbound2 = ucspan2;
    using ucbound3 = ucspan3;
    using ucbound4 = ucspan4;
    using  sbound1 = sspan1;
    using  sbound2 = sspan2;
    using  sbound3 = sspan3;
    using  sbound4 = sspan4;
    using usbound1 = usspan1;
    using usbound2 = usspan2;
    using usbound3 = usspan3;
    using usbound4 = usspan4;
    using  ibound1 = ispan1;
    using  ibound2 = ispan2;
    using  ibound3 = ispan3;
    using  ibound4 = ispan4;
    using uibound1 = uispan1;
    using uibound2 = uispan2;
    using uibound3 = uispan3;
    using uibound4 = uispan4;
    using  lbound1 = lspan1;
    using  lbound2 = lspan2;
    using  lbound3 = lspan3;
    using  lbound4 = lspan4;
    using ulbound1 = ulspan1;
    using ulbound2 = ulspan2;
    using ulbound3 = ulspan3;
    using ulbound4 = ulspan4;
    using  nbound1 = nspan1;
    using  nbound2 = nspan2;
    using  nbound3 = nspan3;
    using  nbound4 = nspan4;
    using unbound1 = unspan1;
    using unbound2 = unspan2;
    using unbound3 = unspan3;
    using unbound4 = unspan4;

}



//======================================================================================================================
// VEC1 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



template <typename T>
struct vec<T, 1> {

    //--------------------------------------------------------------------------
    // Static Members

    using Type = T;
    static constexpr int N{1};

    //--------------------------------------------------------------------------
    // Instance Variables

    union { T x, r, s, i, _0; };

    //--------------------------------------------------------------------------
    // Construction

    constexpr vec() noexcept;
    constexpr vec(const vec1<T> & v) noexcept;
    constexpr vec(vec1<T> && v) noexcept;

    template <typename U> constexpr explicit vec(const vec1<U> & v) noexcept;
    template <typename U> constexpr explicit vec(const vec2<U> & v) noexcept;
    template <typename U> constexpr explicit vec(const vec3<U> & v) noexcept;
    template <typename U> constexpr explicit vec(const vec4<U> & v) noexcept;

    constexpr explicit vec(const T & v) noexcept;

    //--------------------------------------------------------------------------
    // Assignment

    vec1<T> & operator=(const vec1<T> & v) noexcept;
    vec1<T> & operator=(vec1<T> && v) noexcept;

    vec1<T> & operator=(const T & v) noexcept;
    template <int t_n> vec1<T> & operator=(const vec<T, t_n> & v) noexcept;

    //--------------------------------------------------------------------------
    // Access

    template <int t_i> T & at() noexcept;
    template <int t_i> constexpr const T & at() const noexcept;

    T & operator[](int i);
    const T & operator[](int i) const;

};



//======================================================================================================================
// VEC2 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



template <typename T>
struct vec<T, 2> {

    //--------------------------------------------------------------------------
    // Static Members

    using Type = T;
    static constexpr int N{2};

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
    //union { T x, r, s, radius; };
    //union { T y, g, t, theta; };

    //--------------------------------------------------------------------------
    // Construction

    constexpr vec() noexcept;
    constexpr vec(const vec2<T> & v) noexcept;
    constexpr vec(vec2<T> && v) noexcept;

    template <typename U> constexpr explicit vec(const vec1<U> & v) noexcept;
    template <typename U> constexpr explicit vec(const vec2<U> & v) noexcept;
    template <typename U> constexpr explicit vec(const vec3<U> & v) noexcept;
    template <typename U> constexpr explicit vec(const vec4<U> & v) noexcept;

    constexpr explicit vec(const T & v) noexcept;

    // only select constructors are constexpr because IntelliSense is sensitive
    constexpr vec(const       T & v1, const      T  & v2) noexcept;
    Q_CX_ABLE vec(const vec1<T> & v1, const      T  & v2) noexcept;
    Q_CX_ABLE vec(const       T & v1, const vec1<T> & v2) noexcept;
    Q_CX_ABLE vec(const vec1<T> & v1, const vec1<T> & v2) noexcept;

    //--------------------------------------------------------------------------
    // Assignment

    vec2<T> & operator=(const vec2<T> & v) noexcept;
    vec2<T> & operator=(vec2<T> && v) noexcept;
    
    vec2<T> & operator=(const T & v) noexcept;
    template <int t_n> vec2<T> & operator=(const vec<T, t_n> & v) noexcept;

    //--------------------------------------------------------------------------
    // Access

    template <int t_i> T & at() noexcept;
    template <int t_i> constexpr const T & at() const noexcept;

    T & operator[](int i);
    const T & operator[](int i) const;


};



//======================================================================================================================
// VEC3 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



template <typename T>
struct vec<T, 3> {

    //--------------------------------------------------------------------------
    // Static Members

    using Type = T;
    static constexpr int N{3};

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
    //union { T x, r, s,   rad, alpha; };
    //union { T y, g, t, theta,  beta; };
    //union { T z, b, p,   phi, gamma; };

    //--------------------------------------------------------------------------
    // Construction

    constexpr vec() noexcept;
    constexpr vec(const vec3<T> & v) noexcept;
    constexpr vec(vec3<T> && v) noexcept;

    template <typename U> constexpr explicit vec(const vec1<U> & v) noexcept;
    template <typename U> constexpr explicit vec(const vec2<U> & v) noexcept;
    template <typename U> constexpr explicit vec(const vec3<U> & v) noexcept;
    template <typename U> constexpr explicit vec(const vec4<U> & v) noexcept;

    constexpr explicit vec(const T & v) noexcept;
    
    // only select constructors are constexpr because IntelliSense is sensitive
    constexpr vec(const      T  & v1, const      T  & v2, const      T  & v3) noexcept;
    Q_CX_ABLE vec(const vec1<T> & v1, const      T  & v2, const      T  & v3) noexcept;
    Q_CX_ABLE vec(const      T  & v1, const vec1<T> & v2, const      T  & v3) noexcept;
    Q_CX_ABLE vec(const      T  & v1, const      T  & v2, const vec1<T> & v3) noexcept;
    Q_CX_ABLE vec(const vec1<T> & v1, const vec1<T> & v2, const      T  & v3) noexcept;
    Q_CX_ABLE vec(const vec1<T> & v1, const      T  & v2, const vec1<T> & v3) noexcept;
    Q_CX_ABLE vec(const      T  & v1, const vec1<T> & v2, const vec1<T> & v3) noexcept;
    Q_CX_ABLE vec(const vec1<T> & v1, const vec1<T> & v2, const vec1<T> & v3) noexcept;
    Q_CONSTEX vec(const vec2<T> & v1, const      T  & v2) noexcept;
    Q_CX_ABLE vec(const vec2<T> & v1, const vec1<T> & v2) noexcept;
    Q_CX_ABLE vec(const      T  & v1, const vec2<T> & v2) noexcept;
    Q_CX_ABLE vec(const vec1<T> & v1, const vec2<T> & v2) noexcept;

    //--------------------------------------------------------------------------
    // Assignment

    vec3<T> & operator=(const vec3<T> & v) noexcept;
    vec3<T> & operator=(vec3<T> && v) noexcept;

    vec3<T> & operator=(const T & v) noexcept;
    template <int t_n> vec3<T> & operator=(const vec<T, t_n> & v) noexcept;

    //--------------------------------------------------------------------------
    // Access

    template <int t_i> T & at() noexcept;
    template <int t_i> constexpr const T & at() const noexcept;

    T & operator[](int i);
    const T & operator[](int i) const;

    vec2<T> & xy() noexcept;
    vec2<T> & rg() noexcept { return xy(); }
    vec2<T> & st() noexcept { return xy(); }
    const vec2<T> & xy() const noexcept { return xy(); }
    const vec2<T> & rg() const noexcept { return rg(); }
    const vec2<T> & st() const noexcept { return st(); }

    vec2<T> & yz() noexcept;
    vec2<T> & gb() noexcept { return yz(); }
    vec2<T> & tp() noexcept { return yz(); }
    const vec2<T> & yz() const noexcept { return yz(); }
    const vec2<T> & gb() const noexcept { return gb(); }
    const vec2<T> & tp() const noexcept { return tp(); }

};



//======================================================================================================================
// VEC4 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



template <typename T>
struct vec<T, 4> {

    //--------------------------------------------------------------------------
    // Static Members

    using Type = T;
    static constexpr int N{4};

    //--------------------------------------------------------------------------
    // Instance Variables
    
    union {
        struct { T x, y, z, w; };
        struct { T r, g, b, a; };
        struct { T s, t, p, q; };
        struct { T _0, _1, _2, _3; };
    };
    //union { T x, r, s; };
    //union { T y, g, t; };
    //union { T z, b, p; };
    //union { T w, a, q; };
    
    //--------------------------------------------------------------------------
    // Construction

    constexpr vec() noexcept;
    constexpr vec(const vec4<T> & v) noexcept;
    constexpr vec(vec4<T> && v) noexcept;
    
    template <typename U> constexpr explicit vec(const vec1<U> & v) noexcept;
    template <typename U> constexpr explicit vec(const vec2<U> & v) noexcept;
    template <typename U> constexpr explicit vec(const vec3<U> & v) noexcept;
    template <typename U> constexpr explicit vec(const vec4<U> & v) noexcept;

    constexpr explicit vec(const T & v) noexcept;
    
    // only select constructors are constexpr because IntelliSense is sensitive
    constexpr vec(const      T  & v1, const      T  & v2, const      T  & v3, const      T  & v4) noexcept;
    Q_CX_ABLE vec(const vec1<T> & v1, const      T  & v2, const      T  & v3, const      T  & v4) noexcept;
    Q_CX_ABLE vec(const      T  & v1, const vec1<T> & v2, const      T  & v3, const      T  & v4) noexcept;
    Q_CX_ABLE vec(const      T  & v1, const      T  & v2, const vec1<T> & v3, const      T  & v4) noexcept;
    Q_CX_ABLE vec(const      T  & v1, const      T  & v2, const      T  & v3, const vec1<T> & v4) noexcept;
    Q_CX_ABLE vec(const vec1<T> & v1, const vec1<T> & v2, const      T  & v3, const      T  & v4) noexcept;
    Q_CX_ABLE vec(const vec1<T> & v1, const      T  & v2, const vec1<T> & v3, const      T  & v4) noexcept;
    Q_CX_ABLE vec(const vec1<T> & v1, const      T  & v2, const      T  & v3, const vec1<T> & v4) noexcept;
    Q_CX_ABLE vec(const      T  & v1, const vec1<T> & v2, const vec1<T> & v3, const      T  & v4) noexcept;
    Q_CX_ABLE vec(const      T  & v1, const vec1<T> & v2, const      T  & v3, const vec1<T> & v4) noexcept;
    Q_CX_ABLE vec(const      T  & v1, const      T  & v2, const vec1<T> & v3, const vec1<T> & v4) noexcept;
    Q_CX_ABLE vec(const vec1<T> & v1, const vec1<T> & v2, const vec1<T> & v3, const      T  & v4) noexcept;
    Q_CX_ABLE vec(const vec1<T> & v1, const vec1<T> & v2, const      T  & v3, const vec1<T> & v4) noexcept;
    Q_CX_ABLE vec(const vec1<T> & v1, const      T  & v2, const vec1<T> & v3, const vec1<T> & v4) noexcept;
    Q_CX_ABLE vec(const      T  & v1, const vec1<T> & v2, const vec1<T> & v3, const vec1<T> & v4) noexcept;
    Q_CX_ABLE vec(const vec1<T> & v1, const vec1<T> & v2, const vec1<T> & v3, const vec1<T> & v4) noexcept;
    Q_CX_ABLE vec(const vec2<T> & v1, const      T  & v2, const      T  & v3) noexcept;
    Q_CX_ABLE vec(const vec2<T> & v1, const vec1<T> & v2, const      T  & v3) noexcept;
    Q_CX_ABLE vec(const vec2<T> & v1, const      T  & v2, const vec1<T> & v3) noexcept;
    Q_CX_ABLE vec(const vec2<T> & v1, const vec1<T> & v2, const vec1<T> & v3) noexcept;
    Q_CX_ABLE vec(const      T  & v1, const vec2<T> & v2, const      T  & v3) noexcept;
    Q_CX_ABLE vec(const vec1<T> & v1, const vec2<T> & v2, const      T  & v3) noexcept;
    Q_CX_ABLE vec(const      T  & v1, const vec2<T> & v2, const vec1<T> & v3) noexcept;
    Q_CX_ABLE vec(const vec1<T> & v1, const vec2<T> & v2, const vec1<T> & v3) noexcept;
    Q_CX_ABLE vec(const      T  & v1, const      T  & v2, const vec2<T> & v3) noexcept;
    Q_CX_ABLE vec(const vec1<T> & v1, const      T  & v2, const vec2<T> & v3) noexcept;
    Q_CX_ABLE vec(const      T  & v1, const vec1<T> & v2, const vec2<T> & v3) noexcept;
    Q_CX_ABLE vec(const vec1<T> & v1, const vec1<T> & v2, const vec2<T> & v3) noexcept;
    Q_CONSTEX vec(const vec2<T> & v1, const vec2<T> & v2) noexcept;
    Q_CONSTEX vec(const vec3<T> & v1, const      T  & v2) noexcept;
    Q_CX_ABLE vec(const vec3<T> & v1, const vec1<T> & v2) noexcept;
    Q_CX_ABLE vec(const      T  & v1, const vec3<T> & v2) noexcept;
    Q_CX_ABLE vec(const vec1<T> & v1, const vec3<T> & v2) noexcept;

    //--------------------------------------------------------------------------
    // Assignment

    vec4<T> & operator=(const vec4<T> & v) noexcept;
    vec4<T> & operator=(vec4<T> && v) noexcept;

    vec4<T> & operator=(const T & v) noexcept;
    template <int t_n> vec4<T> & operator=(const vec<T, t_n> & v) noexcept;

    //--------------------------------------------------------------------------
    // Access

    template <int t_i> T & at() noexcept;
    template <int t_i> constexpr const T & at() const noexcept;
    
    T & operator[](int i);
    const T & operator[](int i) const;

    vec2<T> & xy() noexcept;
    vec2<T> & rg() { return xy(); }
    vec2<T> & st() { return xy(); }
    const vec2<T> & xy() const { return xy(); }
    const vec2<T> & rg() const { return rg(); }
    const vec2<T> & st() const { return st(); }

    vec2<T> & yz() noexcept;
    vec2<T> & gb() { return yz(); }
    vec2<T> & tp() { return yz(); }
    const vec2<T> & yz() const { return yz(); }
    const vec2<T> & gb() const { return gb(); }
    const vec2<T> & tp() const { return tp(); }

    vec2<T> & zw() noexcept;
    vec2<T> & ba() { return zw(); }
    vec2<T> & pq() { return zw(); }
    const vec2<T> & zw() const { return zw(); }
    const vec2<T> & ba() const { return ba(); }
    const vec2<T> & pq() const { return pq(); }

    vec3<T> & xyz() noexcept;
    vec3<T> & rgb() { return xyz(); }
    vec3<T> & stp() { return xyz(); }
    const vec3<T> & xyz() const { return xyz(); }
    const vec3<T> & rgb() const { return rgb(); }
    const vec3<T> & stp() const { return stp(); }

    vec3<T> & yzw() noexcept;
    vec3<T> & gba() { return yzw(); }
    vec3<T> & tpq() { return yzw(); }
    const vec3<T> & yzw() const { return yzw(); }
    const vec3<T> & gba() const { return gba(); }
    const vec3<T> & tpq() const { return tpq(); }

};



//======================================================================================================================
// SPAN ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



template <typename T, int t_n>
struct span {

    //--------------------------------------------------------------------------
    // Static Members

    using Type = T;
    static constexpr int N{t_n};

    //--------------------------------------------------------------------------
    // Instance Variables

    union {
        struct { vec<T, t_n> min, max; };
        struct { vec<T, t_n> loc, size; };
    };
    //union { vec<T, t_n> min,  loc; };
    //union { vec<T, t_n> max, size; };

    //--------------------------------------------------------------------------
    // Construction

    constexpr span() noexcept;
    constexpr span(const span<T, t_n> & s) noexcept;
    constexpr span(span<T, t_n> && s) noexcept;

    template <typename U, int u_n> constexpr explicit span(const span<U, u_n> & s) noexcept;

    constexpr span(const vec<T, t_n> & v1, const vec<T, t_n> & v2) noexcept;
    constexpr span(const T & v1, const T & v2) noexcept;

    //--------------------------------------------------------------------------
    // Assignment

    span<T, t_n> & operator=(const span<T, t_n> & s) noexcept;
    span<T, t_n> & operator=(span<T, t_n> && s) noexcept;

    template <int u_n> span<T, t_n> & operator=(const span<T, u_n> & s) noexcept;

};



//======================================================================================================================
// Constants ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------------------------



template <typename T, int t_n, int t_d> constexpr vec<T, t_n> axis = vec<T, t_n>();
template <typename T> constexpr vec<T, 1> axis<T, 1, 0> = vec1<T>(T(1));
template <typename T> constexpr vec<T, 2> axis<T, 2, 0> = vec2<T>(T(1), T(0));
template <typename T> constexpr vec<T, 2> axis<T, 2, 1> = vec2<T>(T(0), T(1));
template <typename T> constexpr vec<T, 3> axis<T, 3, 0> = vec3<T>(T(1), T(0), T(0));
template <typename T> constexpr vec<T, 3> axis<T, 3, 1> = vec3<T>(T(0), T(1), T(0));
template <typename T> constexpr vec<T, 3> axis<T, 3, 2> = vec3<T>(T(0), T(0), T(1));
template <typename T> constexpr vec<T, 4> axis<T, 4, 0> = vec4<T>(T(1), T(0), T(0), T(0));
template <typename T> constexpr vec<T, 4> axis<T, 4, 1> = vec4<T>(T(0), T(1), T(0), T(0));
template <typename T> constexpr vec<T, 4> axis<T, 4, 2> = vec4<T>(T(0), T(0), T(1), T(0));
template <typename T> constexpr vec<T, 4> axis<T, 4, 3> = vec4<T>(T(0), T(0), T(0), T(1));

template <typename T, int t_n> constexpr vec<T, t_n> xAxis = axis<T, t_n, 0>;
template <typename T, int t_n> constexpr vec<T, t_n> yAxis = axis<T, t_n, 1>;
template <typename T, int t_n> constexpr vec<T, t_n> zAxis = axis<T, t_n, 2>;
template <typename T, int t_n> constexpr vec<T, t_n> wAxis = axis<T, t_n, 3>;

template <typename T> constexpr vec1<T> xAxis1 = xAxis<T, 1>;
template <typename T> constexpr vec2<T> xAxis2 = xAxis<T, 2>;
template <typename T> constexpr vec3<T> xAxis3 = xAxis<T, 3>;
template <typename T> constexpr vec4<T> xAxis4 = xAxis<T, 4>;
template <typename T> constexpr vec2<T> yAxis2 = yAxis<T, 2>;
template <typename T> constexpr vec3<T> yAxis3 = yAxis<T, 3>;
template <typename T> constexpr vec4<T> yAxis4 = yAxis<T, 4>;
template <typename T> constexpr vec3<T> zAxis3 = zAxis<T, 3>;
template <typename T> constexpr vec4<T> zAxis4 = zAxis<T, 4>;
template <typename T> constexpr vec4<T> wAxis4 = wAxis<T, 4>;

template <typename T, int t_n> constexpr   vec<T, t_n>   nanvec =   vec<T, t_n>(nan<T>);
template <typename T, int t_n> constexpr  span<T, t_n>  nanspan =  span<T, t_n>(nan<T>, nan<T>);
template <typename T, int t_n> constexpr bound<T, t_n> nanbound = bound<T, t_n>(nan<T>, nan<T>);

template <typename T, int t_n> constexpr  vec<T, t_n>  infvec =  vec<T, t_n>(infinity<T>);
template <typename T, int t_n> constexpr span<T, t_n> infspan = span<T, t_n>(-infinity<T>, infinity<T>);

template <typename T, int t_n> constexpr span<T, t_n> nullspan = span<T, t_n>(infinity<T>, -infinity<T>);



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
template <typename T, int t_n> vec<T, t_n> & operator+=(vec<T, t_n> & v1, const           T & v2);

template <typename T, int t_n> vec<T, t_n> & operator-=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> vec<T, t_n> & operator-=(vec<T, t_n> & v1, const           T & v2);

template <typename T, int t_n> vec<T, t_n> & operator*=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> vec<T, t_n> & operator*=(vec<T, t_n> & v1, const           T & v2);

template <typename T, int t_n> vec<T, t_n> & operator/=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> vec<T, t_n> & operator/=(vec<T, t_n> & v1, const           T & v2);

template <typename T, int t_n> vec<T, t_n> & operator%=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> vec<T, t_n> & operator%=(vec<T, t_n> & v1, const           T & v2);



//==============================================================================
// Arithmetic
//------------------------------------------------------------------------------

template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator+(const vec<T, t_n> & v);

template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator-(const vec<T, t_n> & v);

template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator+(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator+(const vec<T, t_n> & v1, const           T & v2);
template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator+(const           T & v1, const vec<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator-(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator-(const vec<T, t_n> & v1, const           T & v2);
template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator-(const           T & v1, const vec<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator*(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator*(const vec<T, t_n> & v1, const           T & v2);
template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator*(const           T & v1, const vec<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator/(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator/(const vec<T, t_n> & v1, const           T & v2);
template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator/(const           T & v1, const vec<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator%(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator%(const vec<T, t_n> & v1, const           T & v2);
template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> operator%(const           T & v1, const vec<T, t_n> & v2);



//==============================================================================
// Comparison
//------------------------------------------------------------------------------

template <typename T, int t_n> Q_CX_ABLE      bool operator==(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator==(const vec<T, t_n> & v1, const           T & v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator==(const           T & v1, const vec<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE      bool operator!=(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator!=(const vec<T, t_n> & v1, const           T & v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator!=(const           T & v1, const vec<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator<(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator<(const vec<T, t_n> & v1, const           T & v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator<(const           T & v1, const vec<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator>(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator>(const vec<T, t_n> & v1, const           T & v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator>(const           T & v1, const vec<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator<=(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator<=(const vec<T, t_n> & v1, const           T & v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator<=(const           T & v1, const vec<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator>=(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator>=(const vec<T, t_n> & v1, const           T & v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator>=(const           T & v1, const vec<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE bool operator==(const span<T, t_n> & s1, const span<T, t_n> & s2);

template <typename T, int t_n> Q_CX_ABLE bool operator!=(const span<T, t_n> & s1, const span<T, t_n> & s2);



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

template <typename T, int t_n>
Q_CX_ABLE const T & min(const vec<T, t_n> & v);

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> min(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

template <typename T, int t_n, typename... Ts>
Q_CX_ABLE vec<T, t_n> min(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<Ts, t_n> &... rest);

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> min(const vec<T, t_n> & v1, const T & v2);

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> min(const T & v1, const vec<T, t_n> & v2);



//==============================================================================
// max
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE const T & max(const vec<T, t_n> & v);

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> max(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

template <typename T, int t_n, typename... Ts>
Q_CX_ABLE vec<T, t_n> max(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<Ts, t_n> &... rest);

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> max(const vec<T, t_n> & v1, const T & v2);

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> max(const T & v1, const vec<T, t_n> & v2);



//==============================================================================
// minmax
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE std::pair<const T &, const T &> minmax(const vec<T, t_n> & v);



//==============================================================================
// toSpan
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE span<T, t_n> toSpan(const bound<T, t_n> & b);



//==============================================================================
// toBound
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE bound<T, t_n> toBound(const span<T, t_n> & s);



}



#include "Vector.tpp"