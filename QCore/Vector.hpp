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



//==============================================================================
// Span Types
//------------------------------------------------------------------------------



template <typename T, int t_n> struct span;

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



//==============================================================================
// Bound Types
//------------------------------------------------------------------------------



template <typename T, int t_n> using bound = span<T, t_n>;

template <typename T> using bound1 = span1<T>;
template <typename T> using bound2 = span2<T>;
template <typename T> using bound3 = span3<T>;
template <typename T> using bound4 = span4<T>;

template <int t_n> using  fbound =  fspan<t_n>;
template <int t_n> using  dbound =  dspan<t_n>;
template <int t_n> using  cbound =  cspan<t_n>;
template <int t_n> using ucbound = ucspan<t_n>;
template <int t_n> using  sbound =  sspan<t_n>;
template <int t_n> using usbound = usspan<t_n>;
template <int t_n> using  ibound =  ispan<t_n>;
template <int t_n> using uibound = uispan<t_n>;
template <int t_n> using  lbound =  lspan<t_n>;
template <int t_n> using ulbound = ulspan<t_n>;
template <int t_n> using  nbound =  nspan<t_n>;
template <int t_n> using unbound = unspan<t_n>;

using  fbound1 =  fspan1;
using  fbound2 =  fspan2;
using  fbound3 =  fspan3;
using  fbound4 =  fspan4;
using  dbound1 =  dspan1;
using  dbound2 =  dspan2;
using  dbound3 =  dspan3;
using  dbound4 =  dspan4;
using  cbound1 =  cspan1;
using  cbound2 =  cspan2;
using  cbound3 =  cspan3;
using  cbound4 =  cspan4;
using ucbound1 = ucspan1;
using ucbound2 = ucspan2;
using ucbound3 = ucspan3;
using ucbound4 = ucspan4;
using  sbound1 =  sspan1;
using  sbound2 =  sspan2;
using  sbound3 =  sspan3;
using  sbound4 =  sspan4;
using usbound1 = usspan1;
using usbound2 = usspan2;
using usbound3 = usspan3;
using usbound4 = usspan4;
using  ibound1 =  ispan1;
using  ibound2 =  ispan2;
using  ibound3 =  ispan3;
using  ibound4 =  ispan4;
using uibound1 = uispan1;
using uibound2 = uispan2;
using uibound3 = uispan3;
using uibound4 = uispan4;
using  lbound1 =  lspan1;
using  lbound2 =  lspan2;
using  lbound3 =  lspan3;
using  lbound4 =  lspan4;
using ulbound1 = ulspan1;
using ulbound2 = ulspan2;
using ulbound3 = ulspan3;
using ulbound4 = ulspan4;
using  nbound1 =  nspan1;
using  nbound2 =  nspan2;
using  nbound3 =  nspan3;
using  nbound4 =  nspan4;
using unbound1 = unspan1;
using unbound2 = unspan2;
using unbound3 = unspan3;
using unbound4 = unspan4;



//==============================================================================
// Vec Namespaces
//------------------------------------------------------------------------------



namespace  tvecs { using qc::  vec; using qc::  vec1; using qc::  vec2; using qc::  vec3; using qc::  vec4; }
namespace  fvecs { using qc:: fvec; using qc:: fvec1; using qc:: fvec2; using qc:: fvec3; using qc:: fvec4; }
namespace  dvecs { using qc:: dvec; using qc:: dvec1; using qc:: dvec2; using qc:: dvec3; using qc:: dvec4; }
namespace  cvecs { using qc:: cvec; using qc:: cvec1; using qc:: cvec2; using qc:: cvec3; using qc:: cvec4; }
namespace ucvecs { using qc::ucvec; using qc::ucvec1; using qc::ucvec2; using qc::ucvec3; using qc::ucvec4; }
namespace  svecs { using qc:: svec; using qc:: svec1; using qc:: svec2; using qc:: svec3; using qc:: svec4; }
namespace usvecs { using qc::usvec; using qc::usvec1; using qc::usvec2; using qc::usvec3; using qc::usvec4; }
namespace  ivecs { using qc:: ivec; using qc:: ivec1; using qc:: ivec2; using qc:: ivec3; using qc:: ivec4; }
namespace uivecs { using qc::uivec; using qc::uivec1; using qc::uivec2; using qc::uivec3; using qc::uivec4; }
namespace  lvecs { using qc:: lvec; using qc:: lvec1; using qc:: lvec2; using qc:: lvec3; using qc:: lvec4; }
namespace ulvecs { using qc::ulvec; using qc::ulvec1; using qc::ulvec2; using qc::ulvec3; using qc::ulvec4; }
namespace  nvecs { using qc:: nvec; using qc:: nvec1; using qc:: nvec2; using qc:: nvec3; using qc:: nvec4; }
namespace unvecs { using qc::unvec; using qc::unvec1; using qc::unvec2; using qc::unvec3; using qc::unvec4; }
namespace  bvecs { using qc:: bvec; using qc:: bvec1; using qc:: bvec2; using qc:: bvec3; using qc:: bvec4; }

namespace vecs {

using namespace  tvecs;
using namespace  fvecs;
using namespace  dvecs;
using namespace  cvecs;
using namespace ucvecs;
using namespace  svecs;
using namespace usvecs;
using namespace  ivecs;
using namespace uivecs;
using namespace  lvecs;
using namespace ulvecs;
using namespace  nvecs;
using namespace unvecs;
using namespace  bvecs;

}



//==============================================================================
// Span Namespaces
//------------------------------------------------------------------------------



namespace  tspans { using qc::  span; using qc::  span1; using qc::  span2; using qc::  span3; using qc::  span4; }
namespace  fspans { using qc:: fspan; using qc:: fspan1; using qc:: fspan2; using qc:: fspan3; using qc:: fspan4; }
namespace  dspans { using qc:: dspan; using qc:: dspan1; using qc:: dspan2; using qc:: dspan3; using qc:: dspan4; }
namespace  cspans { using qc:: cspan; using qc:: cspan1; using qc:: cspan2; using qc:: cspan3; using qc:: cspan4; }
namespace ucspans { using qc::ucspan; using qc::ucspan1; using qc::ucspan2; using qc::ucspan3; using qc::ucspan4; }
namespace  sspans { using qc:: sspan; using qc:: sspan1; using qc:: sspan2; using qc:: sspan3; using qc:: sspan4; }
namespace usspans { using qc::usspan; using qc::usspan1; using qc::usspan2; using qc::usspan3; using qc::usspan4; }
namespace  ispans { using qc:: ispan; using qc:: ispan1; using qc:: ispan2; using qc:: ispan3; using qc:: ispan4; }
namespace uispans { using qc::uispan; using qc::uispan1; using qc::uispan2; using qc::uispan3; using qc::uispan4; }
namespace  lspans { using qc:: lspan; using qc:: lspan1; using qc:: lspan2; using qc:: lspan3; using qc:: lspan4; }
namespace ulspans { using qc::ulspan; using qc::ulspan1; using qc::ulspan2; using qc::ulspan3; using qc::ulspan4; }
namespace  nspans { using qc:: nspan; using qc:: nspan1; using qc:: nspan2; using qc:: nspan3; using qc:: nspan4; }
namespace unspans { using qc::unspan; using qc::unspan1; using qc::unspan2; using qc::unspan3; using qc::unspan4; }

namespace spans {

using namespace  tspans;
using namespace  fspans;
using namespace  dspans;
using namespace  cspans;
using namespace ucspans;
using namespace  sspans;
using namespace usspans;
using namespace  ispans;
using namespace uispans;
using namespace  lspans;
using namespace ulspans;
using namespace  nspans;
using namespace unspans;

}



//==============================================================================
// Bound Namespaces
//------------------------------------------------------------------------------



namespace  tbounds { using qc::  bound; using qc::  bound1; using qc::  bound2; using qc::  bound3; using qc::  bound4; }
namespace  fbounds { using qc:: fbound; using qc:: fbound1; using qc:: fbound2; using qc:: fbound3; using qc:: fbound4; }
namespace  dbounds { using qc:: dbound; using qc:: dbound1; using qc:: dbound2; using qc:: dbound3; using qc:: dbound4; }
namespace  cbounds { using qc:: cbound; using qc:: cbound1; using qc:: cbound2; using qc:: cbound3; using qc:: cbound4; }
namespace ucbounds { using qc::ucbound; using qc::ucbound1; using qc::ucbound2; using qc::ucbound3; using qc::ucbound4; }
namespace  sbounds { using qc:: sbound; using qc:: sbound1; using qc:: sbound2; using qc:: sbound3; using qc:: sbound4; }
namespace usbounds { using qc::usbound; using qc::usbound1; using qc::usbound2; using qc::usbound3; using qc::usbound4; }
namespace  ibounds { using qc:: ibound; using qc:: ibound1; using qc:: ibound2; using qc:: ibound3; using qc:: ibound4; }
namespace uibounds { using qc::uibound; using qc::uibound1; using qc::uibound2; using qc::uibound3; using qc::uibound4; }
namespace  lbounds { using qc:: lbound; using qc:: lbound1; using qc:: lbound2; using qc:: lbound3; using qc:: lbound4; }
namespace ulbounds { using qc::ulbound; using qc::ulbound1; using qc::ulbound2; using qc::ulbound3; using qc::ulbound4; }
namespace  nbounds { using qc:: nbound; using qc:: nbound1; using qc:: nbound2; using qc:: nbound3; using qc:: nbound4; }
namespace unbounds { using qc::unbound; using qc::unbound1; using qc::unbound2; using qc::unbound3; using qc::unbound4; }

namespace bounds {

using namespace  tbounds;
using namespace  fbounds;
using namespace  dbounds;
using namespace  cbounds;
using namespace ucbounds;
using namespace  sbounds;
using namespace usbounds;
using namespace  ibounds;
using namespace uibounds;
using namespace  lbounds;
using namespace ulbounds;
using namespace  nbounds;
using namespace unbounds;

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

    union { T x, r, s, _0; };

    //--------------------------------------------------------------------------
    // Construction

    constexpr vec();
    constexpr vec(const vec1<T> & v);
    constexpr vec(vec1<T> && v);

    template <typename U> constexpr explicit vec(const vec1<U> & v);
    template <typename U> constexpr explicit vec(const vec2<U> & v);
    template <typename U> constexpr explicit vec(const vec3<U> & v);
    template <typename U> constexpr explicit vec(const vec4<U> & v);

    constexpr explicit vec(const T & v);

    //--------------------------------------------------------------------------
    // Assignment

    vec1<T> & operator=(const vec1<T> & v);
    vec1<T> & operator=(vec1<T> && v);

    vec1<T> & operator=(const T & v);
    template <int t_n> vec1<T> & operator=(const vec<T, t_n> & v);

    //--------------------------------------------------------------------------
    // Access

    T & operator[](int i);
    const T & operator[](int i) const;

    template <int t_i> T & at();
    template <int t_i> constexpr const T & at() const;

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
        struct { T radius, theta; };
        struct { T _0, _1; };
    };
    //union { T x, r, s, radius; };
    //union { T y, g, t, theta; };

    //--------------------------------------------------------------------------
    // Construction

    constexpr vec();
    constexpr vec(const vec2<T> & v);
    constexpr vec(vec2<T> && v);

    template <typename U> constexpr explicit vec(const vec1<U> & v);
    template <typename U> constexpr explicit vec(const vec2<U> & v);
    template <typename U> constexpr explicit vec(const vec3<U> & v);
    template <typename U> constexpr explicit vec(const vec4<U> & v);

    constexpr explicit vec(const T & v);

    // only select constructors are constexpr because IntelliSense is sensitive
    constexpr vec(const       T & v1, const      T  & v2);
    Q_CX_ABLE vec(const vec1<T> & v1, const      T  & v2);
    Q_CX_ABLE vec(const       T & v1, const vec1<T> & v2);
    Q_CX_ABLE vec(const vec1<T> & v1, const vec1<T> & v2);

    //--------------------------------------------------------------------------
    // Assignment

    vec2<T> & operator=(const vec2<T> & v);
    vec2<T> & operator=(vec2<T> && v);
    
    vec2<T> & operator=(const T & v);
    template <int t_n> vec2<T> & operator=(const vec<T, t_n> & v);

    //--------------------------------------------------------------------------
    // Access

    T & operator[](int i);
    const T & operator[](int i) const;

    template <int t_i> T & at();
    template <int t_i> constexpr const T & at() const;


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
        struct { T radius, theta, phi; };
        struct { T alpha, beta, gamma; };
        struct { T hue, saturation, value; };
        struct { T _0, _1, _2; };
    };
    //union { T x, r, s,   rad, alpha; };
    //union { T y, g, t, theta,  beta; };
    //union { T z, b, p,   phi, gamma; };

    //--------------------------------------------------------------------------
    // Construction

    constexpr vec();
    constexpr vec(const vec3<T> & v);
    constexpr vec(vec3<T> && v);

    template <typename U> constexpr explicit vec(const vec1<U> & v);
    template <typename U> constexpr explicit vec(const vec2<U> & v);
    template <typename U> constexpr explicit vec(const vec3<U> & v);
    template <typename U> constexpr explicit vec(const vec4<U> & v);

    constexpr explicit vec(const T & v);
    
    // only select constructors are constexpr because IntelliSense is sensitive
    constexpr vec(const      T  & v1, const      T  & v2, const      T  & v3);
    Q_CX_ABLE vec(const vec1<T> & v1, const      T  & v2, const      T  & v3);
    Q_CX_ABLE vec(const      T  & v1, const vec1<T> & v2, const      T  & v3);
    Q_CX_ABLE vec(const      T  & v1, const      T  & v2, const vec1<T> & v3);
    Q_CX_ABLE vec(const vec1<T> & v1, const vec1<T> & v2, const      T  & v3);
    Q_CX_ABLE vec(const vec1<T> & v1, const      T  & v2, const vec1<T> & v3);
    Q_CX_ABLE vec(const      T  & v1, const vec1<T> & v2, const vec1<T> & v3);
    Q_CX_ABLE vec(const vec1<T> & v1, const vec1<T> & v2, const vec1<T> & v3);
    Q_CONSTEX vec(const vec2<T> & v1, const      T  & v2);
    Q_CX_ABLE vec(const vec2<T> & v1, const vec1<T> & v2);
    Q_CX_ABLE vec(const      T  & v1, const vec2<T> & v2);
    Q_CX_ABLE vec(const vec1<T> & v1, const vec2<T> & v2);

    //--------------------------------------------------------------------------
    // Assignment

    vec3<T> & operator=(const vec3<T> & v);
    vec3<T> & operator=(vec3<T> && v);

    vec3<T> & operator=(const T & v);
    template <int t_n> vec3<T> & operator=(const vec<T, t_n> & v);

    //--------------------------------------------------------------------------
    // Access

    T & operator[](int i);
    const T & operator[](int i) const;

    template <int t_i> T & at();
    template <int t_i> constexpr const T & at() const;

    vec2<T> & xy(); vec2<T> & rg(); vec2<T> & st();
    vec2<T> & yz(); vec2<T> & gb(); vec2<T> & tp();

    const vec2<T> & xy() const; const vec2<T> & rg() const; const vec2<T> & st() const;
    const vec2<T> & yz() const; const vec2<T> & gb() const; const vec2<T> & tp() const;

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

    constexpr vec();
    constexpr vec(const vec4<T> & v);
    constexpr vec(vec4<T> && v);
    
    template <typename U> constexpr explicit vec(const vec1<U> & v);
    template <typename U> constexpr explicit vec(const vec2<U> & v);
    template <typename U> constexpr explicit vec(const vec3<U> & v);
    template <typename U> constexpr explicit vec(const vec4<U> & v);

    constexpr explicit vec(const T & v);
    
    // only select constructors are constexpr because IntelliSense is sensitive
    constexpr vec(const      T  & v1, const      T  & v2, const      T  & v3, const      T  & v4);
    Q_CX_ABLE vec(const vec1<T> & v1, const      T  & v2, const      T  & v3, const      T  & v4);
    Q_CX_ABLE vec(const      T  & v1, const vec1<T> & v2, const      T  & v3, const      T  & v4);
    Q_CX_ABLE vec(const      T  & v1, const      T  & v2, const vec1<T> & v3, const      T  & v4);
    Q_CX_ABLE vec(const      T  & v1, const      T  & v2, const      T  & v3, const vec1<T> & v4);
    Q_CX_ABLE vec(const vec1<T> & v1, const vec1<T> & v2, const      T  & v3, const      T  & v4);
    Q_CX_ABLE vec(const vec1<T> & v1, const      T  & v2, const vec1<T> & v3, const      T  & v4);
    Q_CX_ABLE vec(const vec1<T> & v1, const      T  & v2, const      T  & v3, const vec1<T> & v4);
    Q_CX_ABLE vec(const      T  & v1, const vec1<T> & v2, const vec1<T> & v3, const      T  & v4);
    Q_CX_ABLE vec(const      T  & v1, const vec1<T> & v2, const      T  & v3, const vec1<T> & v4);
    Q_CX_ABLE vec(const      T  & v1, const      T  & v2, const vec1<T> & v3, const vec1<T> & v4);
    Q_CX_ABLE vec(const vec1<T> & v1, const vec1<T> & v2, const vec1<T> & v3, const      T  & v4);
    Q_CX_ABLE vec(const vec1<T> & v1, const vec1<T> & v2, const      T  & v3, const vec1<T> & v4);
    Q_CX_ABLE vec(const vec1<T> & v1, const      T  & v2, const vec1<T> & v3, const vec1<T> & v4);
    Q_CX_ABLE vec(const      T  & v1, const vec1<T> & v2, const vec1<T> & v3, const vec1<T> & v4);
    Q_CX_ABLE vec(const vec1<T> & v1, const vec1<T> & v2, const vec1<T> & v3, const vec1<T> & v4);
    Q_CX_ABLE vec(const vec2<T> & v1, const      T  & v2, const      T  & v3);
    Q_CX_ABLE vec(const vec2<T> & v1, const vec1<T> & v2, const      T  & v3);
    Q_CX_ABLE vec(const vec2<T> & v1, const      T  & v2, const vec1<T> & v3);
    Q_CX_ABLE vec(const vec2<T> & v1, const vec1<T> & v2, const vec1<T> & v3);
    Q_CX_ABLE vec(const      T  & v1, const vec2<T> & v2, const      T  & v3);
    Q_CX_ABLE vec(const vec1<T> & v1, const vec2<T> & v2, const      T  & v3);
    Q_CX_ABLE vec(const      T  & v1, const vec2<T> & v2, const vec1<T> & v3);
    Q_CX_ABLE vec(const vec1<T> & v1, const vec2<T> & v2, const vec1<T> & v3);
    Q_CX_ABLE vec(const      T  & v1, const      T  & v2, const vec2<T> & v3);
    Q_CX_ABLE vec(const vec1<T> & v1, const      T  & v2, const vec2<T> & v3);
    Q_CX_ABLE vec(const      T  & v1, const vec1<T> & v2, const vec2<T> & v3);
    Q_CX_ABLE vec(const vec1<T> & v1, const vec1<T> & v2, const vec2<T> & v3);
    Q_CONSTEX vec(const vec2<T> & v1, const vec2<T> & v2);
    Q_CONSTEX vec(const vec3<T> & v1, const      T  & v2);
    Q_CX_ABLE vec(const vec3<T> & v1, const vec1<T> & v2);
    Q_CX_ABLE vec(const      T  & v1, const vec3<T> & v2);
    Q_CX_ABLE vec(const vec1<T> & v1, const vec3<T> & v2);

    //--------------------------------------------------------------------------
    // Assignment

    vec4<T> & operator=(const vec4<T> & v);
    vec4<T> & operator=(vec4<T> && v);

    vec4<T> & operator=(const T & v);
    template <int t_n> vec4<T> & operator=(const vec<T, t_n> & v);

    //--------------------------------------------------------------------------
    // Access
    
    T & operator[](int i);
    const T & operator[](int i) const;

    template <int t_i> T & at();
    template <int t_i> constexpr const T & at() const;

    vec2<T> &  xy(); vec2<T> &  rg(); vec2<T> &  st();
    vec2<T> &  yz(); vec2<T> &  gb(); vec2<T> &  tp();
    vec2<T> &  zw(); vec2<T> &  ba(); vec2<T> &  pq();
    vec3<T> & xyz(); vec3<T> & rgb(); vec3<T> & stp();
    vec3<T> & yzw(); vec3<T> & gba(); vec3<T> & tpq();

    const vec2<T> &  xy() const; const vec2<T> &  rg() const; const vec2<T> &  st() const;
    const vec2<T> &  yz() const; const vec2<T> &  gb() const; const vec2<T> &  tp() const;
    const vec2<T> &  zw() const; const vec2<T> &  ba() const; const vec2<T> &  pq() const;
    const vec3<T> & xyz() const; const vec3<T> & rgb() const; const vec3<T> & stp() const;
    const vec3<T> & yzw() const; const vec3<T> & gba() const; const vec3<T> & tpq() const;

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

    constexpr span();
    constexpr span(const span<T, t_n> & s);
    constexpr span(span<T, t_n> && s);

    template <typename U, int u_n> constexpr explicit span(const span<U, u_n> & s);

    constexpr span(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
    constexpr span(const T & v1, const T & v2);

    //--------------------------------------------------------------------------
    // Assignment

    span<T, t_n> & operator=(const span<T, t_n> & s);
    span<T, t_n> & operator=(span<T, t_n> && s);

    template <int u_n> span<T, t_n> & operator=(const span<T, u_n> & s);

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

template <typename T, int t_n> Q_CX_ABLE bool disjunct(const vec<T, t_n> & v);

template <typename T, int t_n> Q_CX_ABLE bool conjunct(const vec<T, t_n> & v);



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