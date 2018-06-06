#pragma once



#include "Core.hpp"



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

template <int t_n> using   fvec = vec<               float, t_n>;
template <int t_n> using   dvec = vec<              double, t_n>;
template <int t_n> using  ldvec = vec<         long double, t_n>;
template <int t_n> using   cvec = vec<  signed        char, t_n>;
template <int t_n> using  ucvec = vec<unsigned        char, t_n>;
template <int t_n> using   svec = vec<  signed       short, t_n>;
template <int t_n> using  usvec = vec<unsigned       short, t_n>;
template <int t_n> using   ivec = vec<  signed         int, t_n>;
template <int t_n> using  uivec = vec<unsigned         int, t_n>;
template <int t_n> using   lvec = vec<  signed        long, t_n>;
template <int t_n> using  ulvec = vec<unsigned        long, t_n>;
template <int t_n> using  llvec = vec<  signed long   long, t_n>;
template <int t_n> using ullvec = vec<unsigned long   long, t_n>;
template <int t_n> using   nvec = vec<                 nat, t_n>;
template <int t_n> using  unvec = vec<                unat, t_n>;
template <int t_n> using   bvec = vec<                bool, t_n>;

using   fvec1 = vec<               float, 1>;
using   fvec2 = vec<               float, 2>;
using   fvec3 = vec<               float, 3>;
using   fvec4 = vec<               float, 4>;
using   dvec1 = vec<              double, 1>;
using   dvec2 = vec<              double, 2>;
using   dvec3 = vec<              double, 3>;
using   dvec4 = vec<              double, 4>;
using  ldvec1 = vec<         long double, 1>;
using  ldvec2 = vec<         long double, 2>;
using  ldvec3 = vec<         long double, 3>;
using  ldvec4 = vec<         long double, 4>;
using   cvec1 = vec<  signed        char, 1>;
using   cvec2 = vec<  signed        char, 2>;
using   cvec3 = vec<  signed        char, 3>;
using   cvec4 = vec<  signed        char, 4>;
using  ucvec1 = vec<unsigned        char, 1>;
using  ucvec2 = vec<unsigned        char, 2>;
using  ucvec3 = vec<unsigned        char, 3>;
using  ucvec4 = vec<unsigned        char, 4>;
using   svec1 = vec<  signed       short, 1>;
using   svec2 = vec<  signed       short, 2>;
using   svec3 = vec<  signed       short, 3>;
using   svec4 = vec<  signed       short, 4>;
using  usvec1 = vec<unsigned       short, 1>;
using  usvec2 = vec<unsigned       short, 2>;
using  usvec3 = vec<unsigned       short, 3>;
using  usvec4 = vec<unsigned       short, 4>;
using   ivec1 = vec<  signed         int, 1>;
using   ivec2 = vec<  signed         int, 2>;
using   ivec3 = vec<  signed         int, 3>;
using   ivec4 = vec<  signed         int, 4>;
using  uivec1 = vec<unsigned         int, 1>;
using  uivec2 = vec<unsigned         int, 2>;
using  uivec3 = vec<unsigned         int, 3>;
using  uivec4 = vec<unsigned         int, 4>;
using   lvec1 = vec<  signed        long, 1>;
using   lvec2 = vec<  signed        long, 2>;
using   lvec3 = vec<  signed        long, 3>;
using   lvec4 = vec<  signed        long, 4>;
using  ulvec1 = vec<unsigned        long, 1>;
using  ulvec2 = vec<unsigned        long, 2>;
using  ulvec3 = vec<unsigned        long, 3>;
using  ulvec4 = vec<unsigned        long, 4>;
using  llvec1 = vec<  signed long   long, 1>;
using  llvec2 = vec<  signed long   long, 2>;
using  llvec3 = vec<  signed long   long, 3>;
using  llvec4 = vec<  signed long   long, 4>;
using ullvec1 = vec<unsigned long   long, 1>;
using ullvec2 = vec<unsigned long   long, 2>;
using ullvec3 = vec<unsigned long   long, 3>;
using ullvec4 = vec<unsigned long   long, 4>;
using   nvec1 = vec<                 nat, 1>;
using   nvec2 = vec<                 nat, 2>;
using   nvec3 = vec<                 nat, 3>;
using   nvec4 = vec<                 nat, 4>;
using  unvec1 = vec<                unat, 1>;
using  unvec2 = vec<                unat, 2>;
using  unvec3 = vec<                unat, 3>;
using  unvec4 = vec<                unat, 4>;
using   bvec1 = vec<                bool, 1>;
using   bvec2 = vec<                bool, 2>;
using   bvec3 = vec<                bool, 3>;
using   bvec4 = vec<                bool, 4>;



//==============================================================================
// Span Types
//------------------------------------------------------------------------------



template <typename T, int t_n> struct span;

template <typename T> using span1 = span<T, 1>;
template <typename T> using span2 = span<T, 2>;
template <typename T> using span3 = span<T, 3>;
template <typename T> using span4 = span<T, 4>;

template <int t_n> using   fspan = span<               float, t_n>;
template <int t_n> using   dspan = span<              double, t_n>;
template <int t_n> using  ldspan = span<         long double, t_n>;
template <int t_n> using   cspan = span<  signed        char, t_n>;
template <int t_n> using  ucspan = span<unsigned        char, t_n>;
template <int t_n> using   sspan = span<  signed       short, t_n>;
template <int t_n> using  usspan = span<unsigned       short, t_n>;
template <int t_n> using   ispan = span<  signed         int, t_n>;
template <int t_n> using  uispan = span<unsigned         int, t_n>;
template <int t_n> using   lspan = span<  signed        long, t_n>;
template <int t_n> using  ulspan = span<unsigned        long, t_n>;
template <int t_n> using  llspan = span<  signed long   long, t_n>;
template <int t_n> using ullspan = span<unsigned long   long, t_n>;
template <int t_n> using   nspan = span<                 nat, t_n>;
template <int t_n> using  unspan = span<                unat, t_n>;

using   fspan1 = span1<               float>;
using   fspan2 = span2<               float>;
using   fspan3 = span3<               float>;
using   fspan4 = span4<               float>;
using   dspan1 = span1<              double>;
using   dspan2 = span2<              double>;
using   dspan3 = span3<              double>;
using   dspan4 = span4<              double>;
using  ldspan1 = span1<         long double>;
using  ldspan2 = span2<         long double>;
using  ldspan3 = span3<         long double>;
using  ldspan4 = span4<         long double>;
using   cspan1 = span1<  signed        char>;
using   cspan2 = span2<  signed        char>;
using   cspan3 = span3<  signed        char>;
using   cspan4 = span4<  signed        char>;
using  ucspan1 = span1<unsigned        char>;
using  ucspan2 = span2<unsigned        char>;
using  ucspan3 = span3<unsigned        char>;
using  ucspan4 = span4<unsigned        char>;
using   sspan1 = span1<  signed       short>;
using   sspan2 = span2<  signed       short>;
using   sspan3 = span3<  signed       short>;
using   sspan4 = span4<  signed       short>;
using  usspan1 = span1<unsigned       short>;
using  usspan2 = span2<unsigned       short>;
using  usspan3 = span3<unsigned       short>;
using  usspan4 = span4<unsigned       short>;
using   ispan1 = span1<  signed         int>;
using   ispan2 = span2<  signed         int>;
using   ispan3 = span3<  signed         int>;
using   ispan4 = span4<  signed         int>;
using  uispan1 = span1<unsigned         int>;
using  uispan2 = span2<unsigned         int>;
using  uispan3 = span3<unsigned         int>;
using  uispan4 = span4<unsigned         int>;
using   lspan1 = span1<  signed        long>;
using   lspan2 = span2<  signed        long>;
using   lspan3 = span3<  signed        long>;
using   lspan4 = span4<  signed        long>;
using  ulspan1 = span1<unsigned        long>;
using  ulspan2 = span2<unsigned        long>;
using  ulspan3 = span3<unsigned        long>;
using  ulspan4 = span4<unsigned        long>;
using  llspan1 = span1<  signed long   long>;
using  llspan2 = span2<  signed long   long>;
using  llspan3 = span3<  signed long   long>;
using  llspan4 = span4<  signed long   long>;
using ullspan1 = span1<unsigned long   long>;
using ullspan2 = span2<unsigned long   long>;
using ullspan3 = span3<unsigned long   long>;
using ullspan4 = span4<unsigned long   long>;
using   nspan1 = span1<                 nat>;
using   nspan2 = span2<                 nat>;
using   nspan3 = span3<                 nat>;
using   nspan4 = span4<                 nat>;
using  unspan1 = span1<                unat>;
using  unspan2 = span2<                unat>;
using  unspan3 = span3<                unat>;
using  unspan4 = span4<                unat>;



//==============================================================================
// Bound Types
//------------------------------------------------------------------------------



template <typename T, int t_n> using bound = span<T, t_n>;

template <typename T> using bound1 = span1<T>;
template <typename T> using bound2 = span2<T>;
template <typename T> using bound3 = span3<T>;
template <typename T> using bound4 = span4<T>;

template <int t_n> using   fbound =   fspan<t_n>;
template <int t_n> using   dbound =   dspan<t_n>;
template <int t_n> using  ldbound =  ldspan<t_n>;
template <int t_n> using   cbound =   cspan<t_n>;
template <int t_n> using  ucbound =  ucspan<t_n>;
template <int t_n> using   sbound =   sspan<t_n>;
template <int t_n> using  usbound =  usspan<t_n>;
template <int t_n> using   ibound =   ispan<t_n>;
template <int t_n> using  uibound =  uispan<t_n>;
template <int t_n> using   lbound =   lspan<t_n>;
template <int t_n> using  ulbound =  ulspan<t_n>;
template <int t_n> using  llbound =  llspan<t_n>;
template <int t_n> using ullbound = ullspan<t_n>;
template <int t_n> using   nbound =   nspan<t_n>;
template <int t_n> using  unbound =  unspan<t_n>;

using   fbound1 =   fspan1;
using   fbound2 =   fspan2;
using   fbound3 =   fspan3;
using   fbound4 =   fspan4;
using   dbound1 =   dspan1;
using   dbound2 =   dspan2;
using   dbound3 =   dspan3;
using   dbound4 =   dspan4;
using  ldbound1 =  ldspan1;
using  ldbound2 =  ldspan2;
using  ldbound3 =  ldspan3;
using  ldbound4 =  ldspan4;
using   cbound1 =   cspan1;
using   cbound2 =   cspan2;
using   cbound3 =   cspan3;
using   cbound4 =   cspan4;
using  ucbound1 =  ucspan1;
using  ucbound2 =  ucspan2;
using  ucbound3 =  ucspan3;
using  ucbound4 =  ucspan4;
using   sbound1 =   sspan1;
using   sbound2 =   sspan2;
using   sbound3 =   sspan3;
using   sbound4 =   sspan4;
using  usbound1 =  usspan1;
using  usbound2 =  usspan2;
using  usbound3 =  usspan3;
using  usbound4 =  usspan4;
using   ibound1 =   ispan1;
using   ibound2 =   ispan2;
using   ibound3 =   ispan3;
using   ibound4 =   ispan4;
using  uibound1 =  uispan1;
using  uibound2 =  uispan2;
using  uibound3 =  uispan3;
using  uibound4 =  uispan4;
using   lbound1 =   lspan1;
using   lbound2 =   lspan2;
using   lbound3 =   lspan3;
using   lbound4 =   lspan4;
using  ulbound1 =  ulspan1;
using  ulbound2 =  ulspan2;
using  ulbound3 =  ulspan3;
using  ulbound4 =  ulspan4;
using  llbound1 =  llspan1;
using  llbound2 =  llspan2;
using  llbound3 =  llspan3;
using  llbound4 =  llspan4;
using ullbound1 = ullspan1;
using ullbound2 = ullspan2;
using ullbound3 = ullspan3;
using ullbound4 = ullspan4;
using   nbound1 =   nspan1;
using   nbound2 =   nspan2;
using   nbound3 =   nspan3;
using   nbound4 =   nspan4;
using  unbound1 =  unspan1;
using  unbound2 =  unspan2;
using  unbound3 =  unspan3;
using  unbound4 =  unspan4;



//==============================================================================
// Vec Namespaces
//------------------------------------------------------------------------------



namespace   tvecs { using qc::   vec; using qc::   vec1; using qc::   vec2; using qc::   vec3; using qc::   vec4; }
namespace   fvecs { using qc::  fvec; using qc::  fvec1; using qc::  fvec2; using qc::  fvec3; using qc::  fvec4; }
namespace   dvecs { using qc::  dvec; using qc::  dvec1; using qc::  dvec2; using qc::  dvec3; using qc::  dvec4; }
namespace  ldvecs { using qc:: ldvec; using qc:: ldvec1; using qc:: ldvec2; using qc:: ldvec3; using qc:: ldvec4; }
namespace   cvecs { using qc::  cvec; using qc::  cvec1; using qc::  cvec2; using qc::  cvec3; using qc::  cvec4; }
namespace  ucvecs { using qc:: ucvec; using qc:: ucvec1; using qc:: ucvec2; using qc:: ucvec3; using qc:: ucvec4; }
namespace   svecs { using qc::  svec; using qc::  svec1; using qc::  svec2; using qc::  svec3; using qc::  svec4; }
namespace  usvecs { using qc:: usvec; using qc:: usvec1; using qc:: usvec2; using qc:: usvec3; using qc:: usvec4; }
namespace   ivecs { using qc::  ivec; using qc::  ivec1; using qc::  ivec2; using qc::  ivec3; using qc::  ivec4; }
namespace  uivecs { using qc:: uivec; using qc:: uivec1; using qc:: uivec2; using qc:: uivec3; using qc:: uivec4; }
namespace   lvecs { using qc::  lvec; using qc::  lvec1; using qc::  lvec2; using qc::  lvec3; using qc::  lvec4; }
namespace  ulvecs { using qc:: ulvec; using qc:: ulvec1; using qc:: ulvec2; using qc:: ulvec3; using qc:: ulvec4; }
namespace  llvecs { using qc:: llvec; using qc:: llvec1; using qc:: llvec2; using qc:: llvec3; using qc:: llvec4; }
namespace ullvecs { using qc::ullvec; using qc::ullvec1; using qc::ullvec2; using qc::ullvec3; using qc::ullvec4; }
namespace   nvecs { using qc::  nvec; using qc::  nvec1; using qc::  nvec2; using qc::  nvec3; using qc::  nvec4; }
namespace  unvecs { using qc:: unvec; using qc:: unvec1; using qc:: unvec2; using qc:: unvec3; using qc:: unvec4; }
namespace   bvecs { using qc::  bvec; using qc::  bvec1; using qc::  bvec2; using qc::  bvec3; using qc::  bvec4; }

namespace vecs {

using namespace   tvecs;
using namespace   fvecs;
using namespace   dvecs;
using namespace  ldvecs;
using namespace   cvecs;
using namespace  ucvecs;
using namespace   svecs;
using namespace  usvecs;
using namespace   ivecs;
using namespace  uivecs;
using namespace   lvecs;
using namespace  ulvecs;
using namespace  llvecs;
using namespace ullvecs;
using namespace   nvecs;
using namespace  unvecs;
using namespace   bvecs;

}



//==============================================================================
// Span Namespaces
//------------------------------------------------------------------------------



namespace   tspans { using qc::   span; using qc::   span1; using qc::   span2; using qc::   span3; using qc::   span4; }
namespace   fspans { using qc::  fspan; using qc::  fspan1; using qc::  fspan2; using qc::  fspan3; using qc::  fspan4; }
namespace   dspans { using qc::  dspan; using qc::  dspan1; using qc::  dspan2; using qc::  dspan3; using qc::  dspan4; }
namespace  ldspans { using qc:: ldspan; using qc:: ldspan1; using qc:: ldspan2; using qc:: ldspan3; using qc:: ldspan4; }
namespace   cspans { using qc::  cspan; using qc::  cspan1; using qc::  cspan2; using qc::  cspan3; using qc::  cspan4; }
namespace  ucspans { using qc:: ucspan; using qc:: ucspan1; using qc:: ucspan2; using qc:: ucspan3; using qc:: ucspan4; }
namespace   sspans { using qc::  sspan; using qc::  sspan1; using qc::  sspan2; using qc::  sspan3; using qc::  sspan4; }
namespace  usspans { using qc:: usspan; using qc:: usspan1; using qc:: usspan2; using qc:: usspan3; using qc:: usspan4; }
namespace   ispans { using qc::  ispan; using qc::  ispan1; using qc::  ispan2; using qc::  ispan3; using qc::  ispan4; }
namespace  uispans { using qc:: uispan; using qc:: uispan1; using qc:: uispan2; using qc:: uispan3; using qc:: uispan4; }
namespace   lspans { using qc::  lspan; using qc::  lspan1; using qc::  lspan2; using qc::  lspan3; using qc::  lspan4; }
namespace  ulspans { using qc:: ulspan; using qc:: ulspan1; using qc:: ulspan2; using qc:: ulspan3; using qc:: ulspan4; }
namespace  llspans { using qc:: llspan; using qc:: llspan1; using qc:: llspan2; using qc:: llspan3; using qc:: llspan4; }
namespace ullspans { using qc::ullspan; using qc::ullspan1; using qc::ullspan2; using qc::ullspan3; using qc::ullspan4; }
namespace   nspans { using qc::  nspan; using qc::  nspan1; using qc::  nspan2; using qc::  nspan3; using qc::  nspan4; }
namespace  unspans { using qc:: unspan; using qc:: unspan1; using qc:: unspan2; using qc:: unspan3; using qc:: unspan4; }

namespace spans {

using namespace   tspans;
using namespace   fspans;
using namespace   dspans;
using namespace  ldspans;
using namespace   cspans;
using namespace  ucspans;
using namespace   sspans;
using namespace  usspans;
using namespace   ispans;
using namespace  uispans;
using namespace   lspans;
using namespace  ulspans;
using namespace  llspans;
using namespace ullspans;
using namespace   nspans;
using namespace  unspans;

}



//==============================================================================
// Bound Namespaces
//------------------------------------------------------------------------------



namespace   tbounds { using qc::   bound; using qc::   bound1; using qc::   bound2; using qc::   bound3; using qc::   bound4; }
namespace   fbounds { using qc::  fbound; using qc::  fbound1; using qc::  fbound2; using qc::  fbound3; using qc::  fbound4; }
namespace   dbounds { using qc::  dbound; using qc::  dbound1; using qc::  dbound2; using qc::  dbound3; using qc::  dbound4; }
namespace  ldbounds { using qc:: ldbound; using qc:: ldbound1; using qc:: ldbound2; using qc:: ldbound3; using qc:: ldbound4; }
namespace   cbounds { using qc::  cbound; using qc::  cbound1; using qc::  cbound2; using qc::  cbound3; using qc::  cbound4; }
namespace  ucbounds { using qc:: ucbound; using qc:: ucbound1; using qc:: ucbound2; using qc:: ucbound3; using qc:: ucbound4; }
namespace   sbounds { using qc::  sbound; using qc::  sbound1; using qc::  sbound2; using qc::  sbound3; using qc::  sbound4; }
namespace  usbounds { using qc:: usbound; using qc:: usbound1; using qc:: usbound2; using qc:: usbound3; using qc:: usbound4; }
namespace   ibounds { using qc::  ibound; using qc::  ibound1; using qc::  ibound2; using qc::  ibound3; using qc::  ibound4; }
namespace  uibounds { using qc:: uibound; using qc:: uibound1; using qc:: uibound2; using qc:: uibound3; using qc:: uibound4; }
namespace   lbounds { using qc::  lbound; using qc::  lbound1; using qc::  lbound2; using qc::  lbound3; using qc::  lbound4; }
namespace  ulbounds { using qc:: ulbound; using qc:: ulbound1; using qc:: ulbound2; using qc:: ulbound3; using qc:: ulbound4; }
namespace  llbounds { using qc:: llbound; using qc:: llbound1; using qc:: llbound2; using qc:: llbound3; using qc:: llbound4; }
namespace ullbounds { using qc::ullbound; using qc::ullbound1; using qc::ullbound2; using qc::ullbound3; using qc::ullbound4; }
namespace   nbounds { using qc::  nbound; using qc::  nbound1; using qc::  nbound2; using qc::  nbound3; using qc::  nbound4; }
namespace  unbounds { using qc:: unbound; using qc:: unbound1; using qc:: unbound2; using qc:: unbound3; using qc:: unbound4; }

namespace bounds {

using namespace   tbounds;
using namespace   fbounds;
using namespace   dbounds;
using namespace  ldbounds;
using namespace   cbounds;
using namespace  ucbounds;
using namespace   sbounds;
using namespace  usbounds;
using namespace   ibounds;
using namespace  uibounds;
using namespace   lbounds;
using namespace  ulbounds;
using namespace  llbounds;
using namespace ullbounds;
using namespace   nbounds;
using namespace  unbounds;

}



//======================================================================================================================
// VEC1 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



template <typename T>
struct vec<T, 1> {

    //--------------------------------------------------------------------------
    // Static Members

    using Type = T;
    static constexpr int N = 1;

    //--------------------------------------------------------------------------
    // Instance Variables

    union { T x, r, s; };

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

    inline vec1<T> & operator=(const vec1<T> & v);
    inline vec1<T> & operator=(vec1<T> && v);

    inline vec1<T> & operator=(const T & v);
    template <int t_n> inline vec1<T> & operator=(const vec<T, t_n> & v);

    //--------------------------------------------------------------------------
    // Access

    inline T & operator[](int i);
    inline const T & operator[](int i) const;

    template <int t_i> inline T & at();
    template <int t_i> constexpr T at() const;

};



//======================================================================================================================
// VEC2 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



template <typename T>
struct vec<T, 2> {

    //--------------------------------------------------------------------------
    // Static Members

    using Type = T;
    static constexpr int N = 2;    

    //--------------------------------------------------------------------------
    // Instance Variables

    union {
        struct { T x, y; };
        struct { T r, g; };
        struct { T s, t; };
        struct { T rad, theta; };
    };
    //union { T x, r, s,   rad; };
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

    inline vec2<T> & operator=(const vec2<T> & v);
    inline vec2<T> & operator=(vec2<T> && v);
    
    inline vec2<T> & operator=(const T & v);
    template <int t_n> inline vec2<T> & operator=(const vec<T, t_n> & v);

    //--------------------------------------------------------------------------
    // Access

    inline T & operator[](int i);
    inline const T & operator[](int i) const;

    template <int t_i> inline T & at();
    template <int t_i> constexpr T at() const;


};



//======================================================================================================================
// VEC3 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



template <typename T>
struct vec<T, 3> {

    //--------------------------------------------------------------------------
    // Static Members

    using Type = T;
    static constexpr int N = 3;

    //--------------------------------------------------------------------------
    // Instance Variables

    union {
        struct { T x, y, z; };
        struct { T r, g, b; };
        struct { T s, t, p; };
        struct { T rad, theta, phi; };
        struct { T alpha, beta, gamma; };
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

    inline vec3<T> & operator=(const vec3<T> & v);
    inline vec3<T> & operator=(vec3<T> && v);

    inline vec3<T> & operator=(const T & v);
    template <int t_n> inline vec3<T> & operator=(const vec<T, t_n> & v);

    //--------------------------------------------------------------------------
    // Access

    inline T & operator[](int i);
    inline const T & operator[](int i) const;

    template <int t_i> inline T & at();
    template <int t_i> constexpr T at() const;

    inline vec2<T> & xy(); inline vec2<T> & rg(); inline vec2<T> & st();
    inline vec2<T> & yz(); inline vec2<T> & gb(); inline vec2<T> & tp();

    inline const vec2<T> & xy() const; inline const vec2<T> & rg() const; inline const vec2<T> & st() const;
    inline const vec2<T> & yz() const; inline const vec2<T> & gb() const; inline const vec2<T> & tp() const;

};



//======================================================================================================================
// VEC4 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



template <typename T>
struct vec<T, 4> {

    //--------------------------------------------------------------------------
    // Static Members

    using Type = T;
    static constexpr int N = 4;

    //--------------------------------------------------------------------------
    // Instance Variables
    
    union {
        struct { T x, y, z, w; };
        struct { T r, g, b, a; };
        struct { T s, t, p, q; };
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

    inline vec4<T> & operator=(const vec4<T> & v);
    inline vec4<T> & operator=(vec4<T> && v);

    inline vec4<T> & operator=(const T & v);
    template <int t_n> inline vec4<T> & operator=(const vec<T, t_n> & v);

    //--------------------------------------------------------------------------
    // Access
    
    inline T & operator[](int i);
    inline const T & operator[](int i) const;

    template <int t_i> inline T & at();
    template <int t_i> constexpr T at() const;

    inline vec2<T> &  xy(); inline vec2<T> &  rg(); inline vec2<T> &  st();
    inline vec2<T> &  yz(); inline vec2<T> &  gb(); inline vec2<T> &  tp();
    inline vec2<T> &  zw(); inline vec2<T> &  ba(); inline vec2<T> &  pq();
    inline vec3<T> & xyz(); inline vec3<T> & rgb(); inline vec3<T> & stp();
    inline vec3<T> & yzw(); inline vec3<T> & gba(); inline vec3<T> & tpq();

    inline const vec2<T> &  xy() const; inline const vec2<T> &  rg() const; inline const vec2<T> &  st() const;
    inline const vec2<T> &  yz() const; inline const vec2<T> &  gb() const; inline const vec2<T> &  tp() const;
    inline const vec2<T> &  zw() const; inline const vec2<T> &  ba() const; inline const vec2<T> &  pq() const;
    inline const vec3<T> & xyz() const; inline const vec3<T> & rgb() const; inline const vec3<T> & stp() const;
    inline const vec3<T> & yzw() const; inline const vec3<T> & gba() const; inline const vec3<T> & tpq() const;

};



//======================================================================================================================
// SPAN ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



template <typename T, int t_n>
struct span {

    //--------------------------------------------------------------------------
    // Static Members

    using Type = T;
    static constexpr int N = t_n;

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

    inline span<T, t_n> & operator=(const span<T, t_n> & s);
    inline span<T, t_n> & operator=(span<T, t_n> && s);

    template <int u_n> inline span<T, t_n> & operator=(const span<T, u_n> & s);

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

template <typename T, int t_n> inline vec<T, t_n> & operator++(vec<T, t_n> & v);
template <typename T, int t_n> inline vec<T, t_n>   operator++(vec<T, t_n> & v, int);

template <typename T, int t_n> inline vec<T, t_n> & operator--(vec<T, t_n> & v);
template <typename T, int t_n> inline vec<T, t_n>   operator--(vec<T, t_n> & v, int);

template <typename T, int t_n> inline vec<T, t_n> & operator+=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> inline vec<T, t_n> & operator+=(vec<T, t_n> & v1, const           T & v2);

template <typename T, int t_n> inline vec<T, t_n> & operator-=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> inline vec<T, t_n> & operator-=(vec<T, t_n> & v1, const           T & v2);

template <typename T, int t_n> inline vec<T, t_n> & operator*=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> inline vec<T, t_n> & operator*=(vec<T, t_n> & v1, const           T & v2);

template <typename T, int t_n> inline vec<T, t_n> & operator/=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> inline vec<T, t_n> & operator/=(vec<T, t_n> & v1, const           T & v2);

template <typename T, int t_n> inline vec<T, t_n> & operator%=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> inline vec<T, t_n> & operator%=(vec<T, t_n> & v1, const           T & v2);



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

template <typename T, int t_n> Q_CX_ABLE bool operator==(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator==(const vec<T, t_n> & v1, const           T & v2);
template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator==(const           T & v1, const vec<T, t_n> & v2);

template <typename T, int t_n> Q_CX_ABLE bool operator!=(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
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