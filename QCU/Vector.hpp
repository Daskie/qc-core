#pragma once



#include <iostream>
#include <string>
#include <sstream>

#include "Core.hpp"



namespace qcu {



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



namespace   tvecs { using qcu::   vec; using qcu::   vec1; using qcu::   vec2; using qcu::   vec3; using qcu::   vec4; }
namespace   fvecs { using qcu::  fvec; using qcu::  fvec1; using qcu::  fvec2; using qcu::  fvec3; using qcu::  fvec4; }
namespace   dvecs { using qcu::  dvec; using qcu::  dvec1; using qcu::  dvec2; using qcu::  dvec3; using qcu::  dvec4; }
namespace  ldvecs { using qcu:: ldvec; using qcu:: ldvec1; using qcu:: ldvec2; using qcu:: ldvec3; using qcu:: ldvec4; }
namespace   cvecs { using qcu::  cvec; using qcu::  cvec1; using qcu::  cvec2; using qcu::  cvec3; using qcu::  cvec4; }
namespace  ucvecs { using qcu:: ucvec; using qcu:: ucvec1; using qcu:: ucvec2; using qcu:: ucvec3; using qcu:: ucvec4; }
namespace   svecs { using qcu::  svec; using qcu::  svec1; using qcu::  svec2; using qcu::  svec3; using qcu::  svec4; }
namespace  usvecs { using qcu:: usvec; using qcu:: usvec1; using qcu:: usvec2; using qcu:: usvec3; using qcu:: usvec4; }
namespace   ivecs { using qcu::  ivec; using qcu::  ivec1; using qcu::  ivec2; using qcu::  ivec3; using qcu::  ivec4; }
namespace  uivecs { using qcu:: uivec; using qcu:: uivec1; using qcu:: uivec2; using qcu:: uivec3; using qcu:: uivec4; }
namespace   lvecs { using qcu::  lvec; using qcu::  lvec1; using qcu::  lvec2; using qcu::  lvec3; using qcu::  lvec4; }
namespace  ulvecs { using qcu:: ulvec; using qcu:: ulvec1; using qcu:: ulvec2; using qcu:: ulvec3; using qcu:: ulvec4; }
namespace  llvecs { using qcu:: llvec; using qcu:: llvec1; using qcu:: llvec2; using qcu:: llvec3; using qcu:: llvec4; }
namespace ullvecs { using qcu::ullvec; using qcu::ullvec1; using qcu::ullvec2; using qcu::ullvec3; using qcu::ullvec4; }
namespace   nvecs { using qcu::  nvec; using qcu::  nvec1; using qcu::  nvec2; using qcu::  nvec3; using qcu::  nvec4; }
namespace  unvecs { using qcu:: unvec; using qcu:: unvec1; using qcu:: unvec2; using qcu:: unvec3; using qcu:: unvec4; }
namespace   bvecs { using qcu::  bvec; using qcu::  bvec1; using qcu::  bvec2; using qcu::  bvec3; using qcu::  bvec4; }

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



namespace   tspans { using qcu::   span; using qcu::   span1; using qcu::   span2; using qcu::   span3; using qcu::   span4; }
namespace   fspans { using qcu::  fspan; using qcu::  fspan1; using qcu::  fspan2; using qcu::  fspan3; using qcu::  fspan4; }
namespace   dspans { using qcu::  dspan; using qcu::  dspan1; using qcu::  dspan2; using qcu::  dspan3; using qcu::  dspan4; }
namespace  ldspans { using qcu:: ldspan; using qcu:: ldspan1; using qcu:: ldspan2; using qcu:: ldspan3; using qcu:: ldspan4; }
namespace   cspans { using qcu::  cspan; using qcu::  cspan1; using qcu::  cspan2; using qcu::  cspan3; using qcu::  cspan4; }
namespace  ucspans { using qcu:: ucspan; using qcu:: ucspan1; using qcu:: ucspan2; using qcu:: ucspan3; using qcu:: ucspan4; }
namespace   sspans { using qcu::  sspan; using qcu::  sspan1; using qcu::  sspan2; using qcu::  sspan3; using qcu::  sspan4; }
namespace  usspans { using qcu:: usspan; using qcu:: usspan1; using qcu:: usspan2; using qcu:: usspan3; using qcu:: usspan4; }
namespace   ispans { using qcu::  ispan; using qcu::  ispan1; using qcu::  ispan2; using qcu::  ispan3; using qcu::  ispan4; }
namespace  uispans { using qcu:: uispan; using qcu:: uispan1; using qcu:: uispan2; using qcu:: uispan3; using qcu:: uispan4; }
namespace   lspans { using qcu::  lspan; using qcu::  lspan1; using qcu::  lspan2; using qcu::  lspan3; using qcu::  lspan4; }
namespace  ulspans { using qcu:: ulspan; using qcu:: ulspan1; using qcu:: ulspan2; using qcu:: ulspan3; using qcu:: ulspan4; }
namespace  llspans { using qcu:: llspan; using qcu:: llspan1; using qcu:: llspan2; using qcu:: llspan3; using qcu:: llspan4; }
namespace ullspans { using qcu::ullspan; using qcu::ullspan1; using qcu::ullspan2; using qcu::ullspan3; using qcu::ullspan4; }
namespace   nspans { using qcu::  nspan; using qcu::  nspan1; using qcu::  nspan2; using qcu::  nspan3; using qcu::  nspan4; }
namespace  unspans { using qcu:: unspan; using qcu:: unspan1; using qcu:: unspan2; using qcu:: unspan3; using qcu:: unspan4; }

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



namespace   tbounds { using qcu::   bound; using qcu::   bound1; using qcu::   bound2; using qcu::   bound3; using qcu::   bound4; }
namespace   fbounds { using qcu::  fbound; using qcu::  fbound1; using qcu::  fbound2; using qcu::  fbound3; using qcu::  fbound4; }
namespace   dbounds { using qcu::  dbound; using qcu::  dbound1; using qcu::  dbound2; using qcu::  dbound3; using qcu::  dbound4; }
namespace  ldbounds { using qcu:: ldbound; using qcu:: ldbound1; using qcu:: ldbound2; using qcu:: ldbound3; using qcu:: ldbound4; }
namespace   cbounds { using qcu::  cbound; using qcu::  cbound1; using qcu::  cbound2; using qcu::  cbound3; using qcu::  cbound4; }
namespace  ucbounds { using qcu:: ucbound; using qcu:: ucbound1; using qcu:: ucbound2; using qcu:: ucbound3; using qcu:: ucbound4; }
namespace   sbounds { using qcu::  sbound; using qcu::  sbound1; using qcu::  sbound2; using qcu::  sbound3; using qcu::  sbound4; }
namespace  usbounds { using qcu:: usbound; using qcu:: usbound1; using qcu:: usbound2; using qcu:: usbound3; using qcu:: usbound4; }
namespace   ibounds { using qcu::  ibound; using qcu::  ibound1; using qcu::  ibound2; using qcu::  ibound3; using qcu::  ibound4; }
namespace  uibounds { using qcu:: uibound; using qcu:: uibound1; using qcu:: uibound2; using qcu:: uibound3; using qcu:: uibound4; }
namespace   lbounds { using qcu::  lbound; using qcu::  lbound1; using qcu::  lbound2; using qcu::  lbound3; using qcu::  lbound4; }
namespace  ulbounds { using qcu:: ulbound; using qcu:: ulbound1; using qcu:: ulbound2; using qcu:: ulbound3; using qcu:: ulbound4; }
namespace  llbounds { using qcu:: llbound; using qcu:: llbound1; using qcu:: llbound2; using qcu:: llbound3; using qcu:: llbound4; }
namespace ullbounds { using qcu::ullbound; using qcu::ullbound1; using qcu::ullbound2; using qcu::ullbound3; using qcu::ullbound4; }
namespace   nbounds { using qcu::  nbound; using qcu::  nbound1; using qcu::  nbound2; using qcu::  nbound3; using qcu::  nbound4; }
namespace  unbounds { using qcu:: unbound; using qcu:: unbound1; using qcu:: unbound2; using qcu:: unbound3; using qcu:: unbound4; }

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

    //--------------------------------------------------------------------------
    // Other

    inline std::string toString() const;

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

    union { T x, r, s,   rad; };
    union { T y, g, t, theta; };

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

    //--------------------------------------------------------------------------
    // Other

    std::string toString() const;

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

    union { T x, r, s,   rad, alpha; };
    union { T y, g, t, theta,  beta; };
    union { T z, b, p,   phi, gamma; };

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

    //--------------------------------------------------------------------------
    // Other

    inline std::string toString() const;

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
    
    union { T x, r, s; };
    union { T y, g, t; };
    union { T z, b, p; };
    union { T w, a, q; };
    
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

    //--------------------------------------------------------------------------
    // Other

    inline std::string toString() const;

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

    union { vec<T, t_n> min,  loc; };
    union { vec<T, t_n> max, size; };

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

    //--------------------------------------------------------------------------
    // Other

    inline std::string toString() const;

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
// Stream Output
//------------------------------------------------------------------------------

template <typename T, int t_n> inline std::ostream & operator<<(std::ostream & os, const vec<T, t_n> & v);

template <typename T, int t_n> inline std::ostream & operator<<(std::ostream & os, const span<T, t_n> & s);



//==============================================================================
// pow
//------------------------------------------------------------------------------

template <typename T, int t_n, eif_floating_t<T> = 0>
inline vec<T, t_n> pow(const vec<T, t_n> & v, T p);

template <typename T, int t_n, eif_floating_t<T> = 0>
inline vec<T, t_n> pow(const vec<T, t_n> & v, const vec<T, t_n> & p);



//==============================================================================
// exp
//------------------------------------------------------------------------------

template <typename T, int t_n, eif_t<std::is_floating_point_v<T>> = 0>
inline vec<T, t_n> exp(const vec<T, t_n> & v);



//==============================================================================
// magnitude
//------------------------------------------------------------------------------

template <typename T, int t_n, eif_floating_t<T> = 0>
inline T magnitude(const vec<T, t_n> & v);

template <typename T, int t_n>
inline T magnitude2(const vec<T, t_n> & v);



//==============================================================================
// norm
//------------------------------------------------------------------------------

template <typename T, int t_n, eif_floating_t<T> = 0>
inline vec<T, t_n> norm(const vec<T, t_n> & v);



//==============================================================================
// dot
//------------------------------------------------------------------------------

template <typename T, int t_n>
inline T dot(const vec<T, t_n> & v1, const vec<T, t_n> & v2);



//==============================================================================
// cross
//------------------------------------------------------------------------------

template <typename T>
inline T cross(const vec2<T> & v1, const vec2<T> & v2);

template <typename T>
inline vec3<T> cross(const vec3<T> & v1, const vec3<T> & v2);



//==============================================================================
// parallel
//------------------------------------------------------------------------------

template <typename T, int t_n>
inline bool parallel(const vec<T, t_n> & v1, const vec<T, t_n> & v2);



//==============================================================================
// orthogonal
//------------------------------------------------------------------------------

template <typename T, int t_n>
inline bool orthogonal(const vec<T, t_n> & v1, const vec<T, t_n> & v2);



//==============================================================================
// ortho
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> ortho(const vec<T, t_n> & v);



//==============================================================================
// orthogonalize
//------------------------------------------------------------------------------

template <typename T, int t_n, eif_floating_t<T> = 0>
inline void orthogonalize(const vec<T, t_n> & v1, vec<T, t_n> & v2);

template <typename T, eif_floating_t<T> = 0>
inline void orthogonalize(const vec3<T> & v1, vec3<T> & v2, vec3<T> & v3);
template <typename T, eif_floating_t<T> = 0>
inline void orthogonalize_n(const vec3<T> & v1, vec3<T> & v2, vec3<T> & v3);



//==============================================================================
// reflect
//------------------------------------------------------------------------------

template <typename T, int t_n, eif_floating_t<T> = 0>
inline vec<T, t_n> reflect(const vec<T, t_n> & v, const vec<T, t_n> & n);
template <typename T, int t_n, eif_floating_t<T> = 0>
inline vec<T, t_n> reflect_n(const vec<T, t_n> & v, const vec<T, t_n> & n);



//==============================================================================
// angle
//------------------------------------------------------------------------------

template <typename T, int t_n, eif_floating_t<T> = 0>
inline T angle(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n, eif_floating_t<T> = 0>
inline T angle_n(const vec<T, t_n> & v1, const vec<T, t_n> & v2);



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
// sort
//------------------------------------------------------------------------------

template <typename T, int t_n>
inline void sort(const vec<T, t_n> & v);



//==============================================================================
// clamp
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> clamp(const vec<T, t_n> & v, const T & min, const T & max);

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> clamp(const vec<T, t_n> & v, const vec<T, t_n> & min, const vec<T, t_n> & max);



//==============================================================================
// abs
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> abs(const vec<T, t_n> & v);



//==============================================================================
// zero
//------------------------------------------------------------------------------

template <typename T, int t_n, eif_arithmetic_t<T> = 0>
Q_CX_ABLE bool zero(const vec<T, t_n> & v, T e = std::numeric_limits<T>::min());



//==============================================================================
// equal
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE bool equal(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

template <typename T, int t_n, eif_floating_t<T> = 0>
Q_CX_ABLE bool equalE(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & e = vec<T, t_n>(std::numeric_limits<T>::min()));

template <typename T, int t_n>
Q_CX_ABLE bool equal(const vec<T, t_n> & v);



//==============================================================================
// floor
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE vec<nat, t_n> floor(const vec<T, t_n> & v);



//==============================================================================
// ceil
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE vec<nat, t_n> ceil(const vec<T, t_n> & v);



//==============================================================================
// mix
//------------------------------------------------------------------------------

template <typename T, int t_n, eif_floating_t<T> = 0>
Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, T t);

template <typename T, eif_floating_t<T> = 0>
Q_CX_ABLE T mix(T v1, T v2, const vec2<T> & weights);
template <typename T, int t_n, eif_floating_t<T> = 0>
Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec2<T> & weights);

template <typename T, eif_floating_t<T> = 0>
Q_CX_ABLE T mix(T v1, T v2, T v3, const vec3<T> & weights);
template <typename T, int t_n, eif_floating_t<T> = 0>
Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & v3, const vec3<T> & weights);

template <typename T, eif_floating_t<T> = 0>
Q_CX_ABLE T mix(T v1, T v2, T v3, T v4, const vec4<T> & weights);
template <typename T, int t_n, eif_floating_t<T> = 0>
Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & v3, const vec<T, t_n> & v4, const vec4<T> & weights);



//==============================================================================
// transnorm
//------------------------------------------------------------------------------
// converts between normalized types
// works with floats, signed, and unsigned integers
//------------------------------------------------------------------------------

template <typename To, typename From, int t_n, eif_t<std::is_arithmetic_v<To> && std::is_arithmetic_v<From>> = 0>
Q_CONSTEX vec<To, t_n> transnorm(const vec<From, t_n> & v);



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



//==============================================================================
// intersect
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE span<T, t_n> intersect(const span<T, t_n> & s1, const span<T, t_n> & s2);



//==============================================================================
// mipmaps
//------------------------------------------------------------------------------

template <typename T, int t_n, eif_integral_t<T> = 0>
Q_CX_ABLE T mipmaps(const vec<T, t_n> & size);



//==============================================================================================================================================================
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================================================
//#ifndef __INTELLISENSE__



//======================================================================================================================
// VEC1 IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr vec<T, 1>::vec() :
    x(T(0))
{}

template <typename T>
constexpr vec<T, 1>::vec(const vec1<T> & v) :
    x(v.x)
{}

template <typename T>
constexpr vec<T, 1>::vec(vec1<T> && v) :
    x(v.x)
{}

template <typename T>
template <typename U>
constexpr vec<T, 1>::vec(const vec1<U> & v) :
    x(T(v.x))
{}

template <typename T>
template <typename U>
constexpr vec<T, 1>::vec(const vec2<U> & v) :
    x(T(v.x))
{}

template <typename T>
template <typename U>
constexpr vec<T, 1>::vec(const vec3<U> & v) :
    x(T(v.x))
{}

template <typename T>
template <typename U>
constexpr vec<T, 1>::vec(const vec4<U> & v) :
    x(T(v.x))
{}

template <typename T>
constexpr vec<T, 1>::vec(const T & v) :
    x(v)
{}



//------------------------------------------------------------------------------
// Assignment



template <typename T>
inline vec1<T> & vec<T, 1>::operator=(const vec1<T> & v) {
    x = v.x;
    return *this;
}

template <typename T>
inline vec1<T> & vec<T, 1>::operator=(vec1<T> && v) {
    x = v.x;
    return *this;
}

template <typename T>
inline vec1<T> & vec<T, 1>::operator=(const T & v) {
    x = v;
    return *this;
}

template <typename T>
template <int t_n>
inline vec1<T> & vec<T, 1>::operator=(const vec<T, t_n> & v) {
    if constexpr (t_n >= 1) x = v.x;
    if constexpr (t_n < 1) x = T(0);
    return *this;
}



//------------------------------------------------------------------------------
// Access



template <typename T>
inline T & vec<T, 1>::operator[](int i) {
    return *(&x + i);
}

template <typename T>
inline const T & vec<T, 1>::operator[](int i) const {
    return *(&x + i);
}



template <typename T>
template <int t_i>
inline T & vec<T, 1>::at() {
    static_assert(t_i == 0, "index out of bounds");
    if constexpr (t_i == 0) return x;
}

template <typename T>
template <int t_i>
constexpr T vec<T, 1>::at() const {
    static_assert(t_i == 0, "index out of bounds");
    if constexpr (t_i == 0) return x;
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string vec<T, 1>::toString() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}



//======================================================================================================================
// VEC2 IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr vec<T, 2>::vec() :
    x(T(0)), y(T(0))
{}

template <typename T>
constexpr vec<T, 2>::vec(const vec2<T> & v) :
    x(v.x), y(v.y)
{}

template <typename T>
constexpr vec<T, 2>::vec(vec2<T> && v) :
    x(v.x), y(v.y)
{}

template <typename T>
template <typename U>
constexpr vec<T, 2>::vec(const vec1<U> & v) :
    x(T(v.x)), y(T(0))
{}

template <typename T>
template <typename U>
constexpr vec<T, 2>::vec(const vec2<U> & v) :
    x(T(v.x)), y(T(v.y))
{}

template <typename T>
template <typename U>
constexpr vec<T, 2>::vec(const vec3<U> & v) :
    x(T(v.x)), y(T(v.y))
{}

template <typename T>
template <typename U>
constexpr vec<T, 2>::vec(const vec4<U> & v) :
    x(T(v.x)), y(T(v.y))
{}

template <typename T>
constexpr vec<T, 2>::vec(const T & v) :
    x(v), y(v)
{}

template <typename T>
constexpr vec<T, 2>::vec(const T & v1, const T & v2) :
    x(v1), y(v2)
{}

template <typename T>
Q_CX_ABLE vec<T, 2>::vec(const vec1<T> & v1, const T & v2) :
    x(v1.x), y(v2)
{}

template <typename T>
Q_CX_ABLE vec<T, 2>::vec(const T & v1, const vec1<T> & v2) :
    x(v1), y(v2.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 2>::vec(const vec1<T> & v1, const vec1<T> & v2) :
    x(v1.x), y(v2.x)
{}



//------------------------------------------------------------------------------
// Assignment



template <typename T>
inline vec2<T> & vec<T, 2>::operator=(const vec2<T> & v) {
    x = v.x; y = v.y;
    return *this;
}

template <typename T>
inline vec2<T> & vec<T, 2>::operator=(vec2<T> && v) {
    x = v.x; y = v.y;
    return *this;
}

template <typename T>
inline vec2<T> & vec<T, 2>::operator=(const T & v) {
    x = v; y = v;
    return *this;
}

template <typename T>
template <int t_n>
inline vec2<T> & vec<T, 2>::operator=(const vec<T, t_n> & v) {
    if constexpr (t_n >= 1) x = v.x; if constexpr (t_n < 1) x = T(0);
    if constexpr (t_n >= 2) y = v.y; if constexpr (t_n < 2) y = T(0);
    return *this;
}



//------------------------------------------------------------------------------
// Access



template <typename T>
inline T & vec<T, 2>::operator[](int i) {
    return *(&x + i);
}

template <typename T>
inline const T & vec<T, 2>::operator[](int i) const {
    return *(&x + i);
}



template <typename T>
template <int t_i>
inline T & vec<T, 2>::at() {
    static_assert(t_i >= 0 && t_i <= 1, "index out of bounds");
    if constexpr (t_i == 0) return x;
    if constexpr (t_i == 1) return y;
}

template <typename T>
template <int t_i>
constexpr T vec<T, 2>::at() const {
    static_assert(t_i >= 0 && t_i <= 1, "index out of bounds");
    if constexpr (t_i == 0) return x;
    if constexpr (t_i == 1) return y;
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string vec<T, 2>::toString() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}



//======================================================================================================================
// VEC3 IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr vec<T, 3>::vec() :
    x(T(0)), y(T(0)), z(T(0))
{}

template <typename T>
constexpr vec<T, 3>::vec(const vec3<T> & v) :
    x(v.x), y(v.y), z(v.z)
{}

template <typename T>
constexpr vec<T, 3>::vec(vec3<T> && v) :
    x(v.x), y(v.y), z(v.z)
{}

template <typename T>
template <typename U>
constexpr vec<T, 3>::vec(const vec1<U> & v) :
    x(T(v.x)), y(T(0)), z(T(0))
{}

template <typename T>
template <typename U>
constexpr vec<T, 3>::vec(const vec2<U> & v) :
    x(T(v.x)), y(T(v.y)), z(T(0))
{}

template <typename T>
template <typename U>
constexpr vec<T, 3>::vec(const vec3<U> & v) :
    x(T(v.x)), y(T(v.y)), z(T(v.z))
{}

template <typename T>
template <typename U>
constexpr vec<T, 3>::vec(const vec4<U> & v) :
    x(T(v.x)), y(T(v.y)), z(T(v.z))
{}

template <typename T>
constexpr vec<T, 3>::vec(const T & v) :
    x(v), y(v), z(v)
{}

template <typename T>
constexpr vec<T, 3>::vec(const T & v1, const T & v2, const T & v3) :
    x(v1), y(v2), z(v3)
{}

template <typename T>
Q_CX_ABLE vec<T, 3>::vec(const vec1<T> & v1, const T & v2, const T & v3) :
    x(v1.x), y(v2), z(v3)
{}

template <typename T>
Q_CX_ABLE vec<T, 3>::vec(const T & v1, const vec1<T> & v2, const T & v3) :
    x(v1), y(v2.x), z(v3)
{}

template <typename T>
Q_CX_ABLE vec<T, 3>::vec(const T & v1, const T & v2, const vec1<T> & v3) :
    x(v1), y(v2), z(v3.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 3>::vec(const vec1<T> & v1, const vec1<T> & v2, const T & v3) :
    x(v1.x), y(v2.x), z(v3)
{}

template <typename T>
Q_CX_ABLE vec<T, 3>::vec(const vec1<T> & v1, const T & v2, const vec1<T> & v3) :
    x(v1.x), y(v2), z(v3.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 3>::vec(const T & v1, const vec1<T> & v2, const vec1<T> & v3) :
    x(v1), y(v2.x), z(v3.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 3>::vec(const vec1<T> & v1, const vec1<T> & v2, const vec1<T> & v3) :
    x(v1.x), y(v2.x), z(v3.x)
{}

template <typename T>
Q_CONSTEX vec<T, 3>::vec(const vec2<T> & v1, const T & v2) :
    x(v1.x), y(v1.y), z(v2)
{}

template <typename T>
Q_CX_ABLE vec<T, 3>::vec(const vec2<T> & v1, const vec1<T> & v2) :
    x(v1.x), y(v1.y), z(v2.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 3>::vec(const T & v1, const vec2<T> & v2) :
    x(v1), y(v2.x), z(v2.y)
{}

template <typename T>
Q_CX_ABLE vec<T, 3>::vec(const vec1<T> & v1, const vec2<T> & v2) :
    x(v1.x), y(v2.x), z(v2.y)
{}



//------------------------------------------------------------------------------
// Assignment



template <typename T>
inline vec3<T> & vec<T, 3>::operator=(const vec3<T> & v) {
    x = v.x; y = v.y; z = v.z;
    return *this;
}

template <typename T>
inline vec3<T> & vec<T, 3>::operator=(vec3<T> && v) {
    x = v.x; y = v.y; z = v.z;
    return *this;
}

template <typename T>
inline vec3<T> & vec<T, 3>::operator=(const T & v) {
    x = v; y = v; z = v;
    return *this;
}

template <typename T>
template <int t_n>
inline vec3<T> & vec<T, 3>::operator=(const vec<T, t_n> & v) {
    if constexpr (t_n >= 1) x = v.x; if constexpr (t_n < 1) x = T(0);
    if constexpr (t_n >= 2) y = v.y; if constexpr (t_n < 2) y = T(0);
    if constexpr (t_n >= 3) z = v.z; if constexpr (t_n < 3) z = T(0);
    return *this;
}



//------------------------------------------------------------------------------
// Access



template <typename T>
inline T & vec<T, 3>::operator[](int i) {
    return *(&x + i);
}

template <typename T>
inline const T & vec<T, 3>::operator[](int i) const {
    return *(&x + i);
}

template <typename T>
template <int t_i>
inline T & vec<T, 3>::at() {
    static_assert(t_i >= 0 && t_i <= 2, "index out of bounds");
    if constexpr (t_i == 0) return x;
    if constexpr (t_i == 1) return y;
    if constexpr (t_i == 2) return z;
}

template <typename T>
template <int t_i>
constexpr T vec<T, 3>::at() const {
    static_assert(t_i >= 0 && t_i <= 2, "index out of bounds");
    if constexpr (t_i == 0) return x;
    if constexpr (t_i == 1) return y;
    if constexpr (t_i == 2) return z;
}

template <typename T>
inline vec2<T> & vec<T, 3>::xy() {
    return *reinterpret_cast<vec2<T> *>(&x);
}

template <typename T>
inline vec2<T> & vec<T, 3>::rg() {
    return *reinterpret_cast<vec2<T> *>(&r);
}

template <typename T>
inline vec2<T> & vec<T, 3>::st() {
    return *reinterpret_cast<vec2<T> *>(&s);
}

template <typename T>
inline vec2<T> & vec<T, 3>::yz() {
    return *reinterpret_cast<vec2<T> *>(&y);
}

template <typename T>
inline vec2<T> & vec<T, 3>::gb() {
    return *reinterpret_cast<vec2<T> *>(&g);
}

template <typename T>
inline vec2<T> & vec<T, 3>::tp() {
    return *reinterpret_cast<vec2<T> *>(&t);
}

template <typename T>
inline const vec2<T> & vec<T, 3>::xy() const {
    return *reinterpret_cast<vec2<T> *>(&x);
}

template <typename T>
inline const vec2<T> & vec<T, 3>::rg() const {
    return *reinterpret_cast<vec2<T> *>(&r);
}

template <typename T>
inline const vec2<T> & vec<T, 3>::st() const {
    return *reinterpret_cast<vec2<T> *>(&s);
}

template <typename T>
inline const vec2<T> & vec<T, 3>::yz() const {
    return *reinterpret_cast<vec2<T> *>(&y);
}

template <typename T>
inline const vec2<T> & vec<T, 3>::gb() const {
    return *reinterpret_cast<vec2<T> *>(&g);
}

template <typename T>
inline const vec2<T> & vec<T, 3>::tp() const {
    return *reinterpret_cast<vec2<T> *>(&t);
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string vec<T, 3>::toString() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}



//======================================================================================================================
// VEC4 IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr vec<T, 4>::vec() :
    x(T(0)), y(T(0)), z(T(0)), w(T(0))
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec4<T> & v) :
    x(v.x), y(v.y), z(v.z), w(v.w)
{}

template <typename T>
constexpr vec<T, 4>::vec(vec4<T> && v) :
    x(v.x), y(v.y), z(v.z), w(v.w)
{}

template <typename T>
template <typename U>
constexpr vec<T, 4>::vec(const vec1<U> & v) :
    x(T(v.x)), y(T(0)), z(T(0)), w(T(0))
{}

template <typename T>
template <typename U>
constexpr vec<T, 4>::vec(const vec2<U> & v) :
    x(T(v.x)), y(T(v.y)), z(T(0)), w(T(0))
{}

template <typename T>
template <typename U>
constexpr vec<T, 4>::vec(const vec3<U> & v) :
    x(T(v.x)), y(T(v.y)), z(T(v.z)), w(T(0))
{}

template <typename T>
template <typename U>
constexpr vec<T, 4>::vec(const vec4<U> & v) :
    x(T(v.x)), y(T(v.y)), z(T(v.z)), w(T(v.w))
{}

template <typename T>
constexpr vec<T, 4>::vec(const T & v) :
    x(v), y(v), z(v), w(v)
{}

template <typename T>
constexpr vec<T, 4>::vec(const T & v1, const T & v2, const T & v3, const T & v4) :
    x(v1), y(v2), z(v3), w(v4)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const T & v2, const T & v3, const T & v4) :
    x(v1.x), y(v2), z(v3), w(v4)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const vec1<T> & v2, const T & v3, const T & v4) :
    x(v1), y(v2.x), z(v3), w(v4)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const T & v2, const vec1<T> & v3, const T & v4) :
    x(v1), y(v2), z(v3.x), w(v4)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const T & v2, const T & v3, const vec1<T> & v4) :
    x(v1), y(v2), z(v3), w(v4.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const vec1<T> & v2, const T & v3, const T & v4) :
    x(v1.x), y(v2.x), z(v3), w(v4)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const T & v2, const vec1<T> & v3, const T & v4) :
    x(v1.x), y(v2), z(v3.x), w(v4)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const T & v2, const T & v3, const vec1<T> & v4) :
    x(v1.x), y(v2), z(v3), w(v4.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const vec1<T> & v2, const vec1<T> & v3, const T & v4) :
    x(v1), y(v2.x), z(v3.x), w(v4)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const vec1<T> & v2, const T & v3, const vec1<T> & v4) :
    x(v1), y(v2.x), z(v3), w(v4.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const T & v2, const vec1<T> & v3, const vec1<T> & v4) :
    x(v1), y(v2), z(v3.x), w(v4.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const vec1<T> & v2, const vec1<T> & v3, const T & v4) :
    x(v1.x), y(v2.x), z(v3.x), w(v4)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const vec1<T> & v2, const T & v3, const vec1<T> & v4) :
    x(v1.x), y(v2.x), z(v3), w(v4.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const T & v2, const vec1<T> & v3, const vec1<T> & v4) :
    x(v1.x), y(v2), z(v3.x), w(v4.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const vec1<T> & v2, const vec1<T> & v3, const vec1<T> & v4) :
    x(v1), y(v2.x), z(v3.x), w(v4.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const vec1<T> & v2, const vec1<T> & v3, const vec1<T> & v4) :
    x(v1.x), y(v2.x), z(v3.x), w(v4.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec2<T> & v1, const T & v2, const T & v3) :
    x(v1.x), y(v1.y), z(v2), w(v3)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec2<T> & v1, const vec1<T> & v2, const T & v3) :
    x(v1.x), y(v1.y), z(v2.x), w(v3)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec2<T> & v1, const T & v2, const vec1<T> & v3) :
    x(v1.x), y(v1.y), z(v2), w(v3.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec2<T> & v1, const vec1<T> & v2, const vec1<T> & v3) :
    x(v1.x), y(v1.y), z(v2.x), w(v3.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const vec2<T> & v2, const T & v3) :
    x(v1), y(v2.x), z(v2.y), w(v3)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const vec2<T> & v2, const T & v3) :
    x(v1.x), y(v2.x), z(v2.y), w(v3)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const vec2<T> & v2, const vec1<T> & v3) :
    x(v1), y(v2.x), z(v2.y), w(v3.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const vec2<T> & v2, const vec1<T> & v3) :
    x(v1.x), y(v2.x), z(v2.y), w(v3.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const T & v2, const vec2<T> & v3) :
    x(v1), y(v2), z(v3.x), w(v3.y)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const T & v2, const vec2<T> & v3) :
    x(v1.x), y(v2), z(v3.x), w(v3.y)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const vec1<T> & v2, const vec2<T> & v3) :
    x(v1), y(v2.x), z(v3.x), w(v3.y)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const vec1<T> & v2, const vec2<T> & v3) :
    x(v1.x), y(v2.x), z(v3.x), w(v3.y)
{}

template <typename T>
Q_CONSTEX vec<T, 4>::vec(const vec2<T> & v1, const vec2<T> & v2) :
    x(v1.x), y(v1.y), z(v2.x), w(v2.y)
{}

template <typename T>
Q_CONSTEX vec<T, 4>::vec(const vec3<T> & v1, const T & v2) :
    x(v1.x), y(v1.y), z(v1.z), w(v2)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec3<T> & v1, const vec1<T> & v2) :
    x(v1.x), y(v1.y), z(v1.z), w(v2.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const vec3<T> & v2) :
    x(v1), y(v2.x), z(v2.y), w(v2.z)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const vec3<T> & v2) :
    x(v1.x), y(v2.x), z(v2.y), w(v2.z)
{}



//------------------------------------------------------------------------------
// Assignment



template <typename T>
inline vec4<T> & vec<T, 4>::operator=(const vec4<T> & v) {
    x = v.x; y = v.y; z = v.z; w = v.w;
    return *this;
}

template <typename T>
inline vec4<T> & vec<T, 4>::operator=(vec4<T> && v) {
    x = v.x; y = v.y; z = v.z; w = v.w;
    return *this;
}

template <typename T>
inline vec4<T> & vec<T, 4>::operator=(const T & v) {
    x = v; y = v; z = v; w = v;
    return *this;
}

template <typename T>
template <int t_n>
inline vec4<T> & vec<T, 4>::operator=(const vec<T, t_n> & v) {
    if constexpr (t_n >= 1) x = v.x; if constexpr (t_n < 1) x = T(0);
    if constexpr (t_n >= 2) y = v.y; if constexpr (t_n < 2) y = T(0);
    if constexpr (t_n >= 3) z = v.z; if constexpr (t_n < 3) z = T(0);
    if constexpr (t_n >= 4) w = v.w; if constexpr (t_n < 4) w = T(0);
    return *this;
}



//------------------------------------------------------------------------------
// Access



template <typename T>
inline T & vec<T, 4>::operator[](int i) {
    return *(&x + i);
}

template <typename T>
inline const T & vec<T, 4>::operator[](int i) const {
    return *(&x + i);
}

template <typename T>
template <int t_i>
inline T & vec<T, 4>::at() {
    static_assert(t_i >= 0 && t_i <= 3, "index out of bounds");
    if constexpr (t_i == 0) return x;
    if constexpr (t_i == 1) return y;
    if constexpr (t_i == 2) return z;
    if constexpr (t_i == 3) return w;
}

template <typename T>
template <int t_i>
constexpr T vec<T, 4>::at() const {
    static_assert(t_i >= 0 && t_i <= 3, "index out of bounds");
    if constexpr (t_i == 0) return x;
    if constexpr (t_i == 1) return y;
    if constexpr (t_i == 2) return z;
    if constexpr (t_i == 3) return w;
}

template <typename T>
inline vec2<T> & vec<T, 4>::xy() {
    return *reinterpret_cast<vec2<T> *>(&x);
}

template <typename T>
inline vec2<T> & vec<T, 4>::rg() {
    return *reinterpret_cast<vec2<T> *>(&r);
}

template <typename T>
inline vec2<T> & vec<T, 4>::st() {
    return *reinterpret_cast<vec2<T> *>(&s);
}

template <typename T>
inline vec2<T> & vec<T, 4>::yz() {
    return *reinterpret_cast<vec2<T> *>(&y);
}

template <typename T>
inline vec2<T> & vec<T, 4>::gb() {
    return *reinterpret_cast<vec2<T> *>(&g);
}

template <typename T>
inline vec2<T> & vec<T, 4>::tp() {
    return *reinterpret_cast<vec2<T> *>(&t);
}

template <typename T>
inline vec2<T> & vec<T, 4>::zw() {
    return *reinterpret_cast<vec2<T> *>(&z);
}

template <typename T>
inline vec2<T> & vec<T, 4>::ba() {
    return *reinterpret_cast<vec2<T> *>(&b);
}

template <typename T>
inline vec2<T> & vec<T, 4>::pq() {
    return *reinterpret_cast<vec2<T> *>(&p);
}

template <typename T>
inline vec3<T> & vec<T, 4>::xyz() {
    return *reinterpret_cast<vec3<T> *>(&x);
}

template <typename T>
inline vec3<T> & vec<T, 4>::rgb() {
    return *reinterpret_cast<vec3<T> *>(&r);
}

template <typename T>
inline vec3<T> & vec<T, 4>::stp() {
    return *reinterpret_cast<vec3<T> *>(&s);
}

template <typename T>
inline vec3<T> & vec<T, 4>::yzw() {
    return *reinterpret_cast<vec3<T> *>(&y);
}

template <typename T>
inline vec3<T> & vec<T, 4>::gba() {
    return *reinterpret_cast<vec3<T> *>(&g);
}

template <typename T>
inline vec3<T> & vec<T, 4>::tpq() {
    return *reinterpret_cast<vec3<T> *>(&t);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::xy() const {
    return *reinterpret_cast<vec2<T> *>(&x);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::rg() const {
    return *reinterpret_cast<vec2<T> *>(&r);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::st() const {
    return *reinterpret_cast<vec2<T> *>(&s);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::yz() const {
    return *reinterpret_cast<vec2<T> *>(&y);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::gb() const {
    return *reinterpret_cast<vec2<T> *>(&g);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::tp() const {
    return *reinterpret_cast<vec2<T> *>(&t);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::zw() const {
    return *reinterpret_cast<vec2<T> *>(&z);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::ba() const {
    return *reinterpret_cast<vec2<T> *>(&b);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::pq() const {
    return *reinterpret_cast<vec2<T> *>(&p);
}

template <typename T>
inline const vec3<T> & vec<T, 4>::xyz() const {
    return *reinterpret_cast<vec3<T> *>(&x);
}

template <typename T>
inline const vec3<T> & vec<T, 4>::yzw() const {
    return *reinterpret_cast<vec3<T> *>(&y);
}

template <typename T>
inline const vec3<T> & vec<T, 4>::rgb() const {
    return *reinterpret_cast<vec3<T> *>(&r);
}

template <typename T>
inline const vec3<T> & vec<T, 4>::gba() const {
    return *reinterpret_cast<vec3<T> *>(&g);
}

template <typename T>
inline const vec3<T> & vec<T, 4>::stp() const {
    return *reinterpret_cast<vec3<T> *>(&s);
}

template <typename T>
inline const vec3<T> & vec<T, 4>::tpq() const {
    return *reinterpret_cast<vec3<T> *>(&t);
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string vec<T, 4>::toString() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}



//======================================================================================================================
// SPAN IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



//------------------------------------------------------------------------------
// Constructors



template <typename T, int t_n>
constexpr span<T, t_n>::span() :
    min(),
    max()
{}

template <typename T, int t_n>
constexpr span<T, t_n>::span(const span<T, t_n> & s) :
    min(s.min),
    max(s.max)
{}

template <typename T, int t_n>
constexpr span<T, t_n>::span(span<T, t_n> && s) :
    min(s.min),
    max(s.max)
{}

template <typename T, int t_n>
template <typename U, int u_n>
constexpr span<T, t_n>::span(const span<U, u_n> & s) :
    min(s.min),
    max(s.max)
{}

template <typename T, int t_n>
constexpr span<T, t_n>::span(const vec<T, t_n> & v1, const vec<T, t_n> & v2) :
    min(v1),
    max(v2)
{}

template <typename T, int t_n>
constexpr span<T, t_n>::span(const T & v1, const T & v2) :
    min(v1),
    max(v2)
{}



//------------------------------------------------------------------------------
// Assignment



template <typename T, int t_n>
inline span<T, t_n> & span<T, t_n>::operator=(const span<T, t_n> & s) {
    min = s.min;
    max = s.max;
    return *this;
}

template <typename T, int t_n>
inline span<T, t_n> & span<T, t_n>::operator=(span<T, t_n> && s) {
    min = s.min;
    max = s.max;
    return *this;
}

template <typename T, int t_n>
template <int u_n>
inline span<T, t_n> & span<T, t_n>::operator=(const span<T, u_n> & s) {
    min = s.min;
    max = s.max;
    return *this;
}



//------------------------------------------------------------------------------
// Other



template <typename T, int t_n>
inline std::string span<T, t_n>::toString() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}



//======================================================================================================================
// FUNCTION IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



//------------------------------------------------------------------------------
// Arithmetic Assignment



//--- pre increment ---

template <typename T, int t_n>
inline vec<T, t_n> & operator++(vec<T, t_n> & v) {
    if constexpr (t_n >= 1) ++v.x;
    if constexpr (t_n >= 2) ++v.y;
    if constexpr (t_n >= 3) ++v.z;
    if constexpr (t_n >= 4) ++v.w;
    return v;
}

//--- post increment ---

template <typename T, int t_n>
inline vec<T, t_n> operator++(vec<T, t_n> & v, int) {
    if constexpr (t_n == 1) return vec1<T>(v.x++);
    if constexpr (t_n == 2) return vec2<T>(v.x++, v.y++);
    if constexpr (t_n == 3) return vec3<T>(v.x++, v.y++, v.z++);
    if constexpr (t_n == 4) return vec4<T>(v.x++, v.y++, v.z++, v.w++);
}

//--- pre decrement ---

template <typename T, int t_n>
inline vec<T, t_n> & operator--(vec<T, t_n> & v) {
    if constexpr (t_n >= 1) --v.x;
    if constexpr (t_n >= 2) --v.y;
    if constexpr (t_n >= 3) --v.z;
    if constexpr (t_n >= 4) --v.w;
    return v;
}

//--- post decrement ---

template <typename T, int t_n>
inline vec<T, t_n> operator--(vec<T, t_n> & v, int) {
    if constexpr (t_n == 1) return vec1<T>(v.x--);
    if constexpr (t_n == 2) return vec2<T>(v.x--, v.y--);
    if constexpr (t_n == 3) return vec3<T>(v.x--, v.y--, v.z--);
    if constexpr (t_n == 4) return vec4<T>(v.x--, v.y--, v.z--, v.w--);
}

//--- add assign ---

template <typename T, int t_n>
inline vec<T, t_n> & operator+=(vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n >= 1) v1.x += v2.x;
    if constexpr (t_n >= 2) v1.y += v2.y;
    if constexpr (t_n >= 3) v1.z += v2.z;
    if constexpr (t_n >= 4) v1.w += v2.w;
    return v1;
}

template <typename T, int t_n>
inline vec<T, t_n> & operator+=(vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n >= 1) v1.x += v2;
    if constexpr (t_n >= 2) v1.y += v2;
    if constexpr (t_n >= 3) v1.z += v2;
    if constexpr (t_n >= 4) v1.w += v2;
    return v1;
}

//--- subtract assign ---

template <typename T, int t_n>
inline vec<T, t_n> & operator-=(vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n >= 1) v1.x -= v2.x;
    if constexpr (t_n >= 2) v1.y -= v2.y;
    if constexpr (t_n >= 3) v1.z -= v2.z;
    if constexpr (t_n >= 4) v1.w -= v2.w;
    return v1;
}

template <typename T, int t_n>
inline vec<T, t_n> & operator-=(vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n >= 1) v1.x -= v2;
    if constexpr (t_n >= 2) v1.y -= v2;
    if constexpr (t_n >= 3) v1.z -= v2;
    if constexpr (t_n >= 4) v1.w -= v2;
    return v1;
}

//--- multiply assign ---

template <typename T, int t_n>
inline vec<T, t_n> & operator*=(vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n >= 1) v1.x *= v2.x;
    if constexpr (t_n >= 2) v1.y *= v2.y;
    if constexpr (t_n >= 3) v1.z *= v2.z;
    if constexpr (t_n >= 4) v1.w *= v2.w;
    return v1;
}

template <typename T, int t_n>
inline vec<T, t_n> & operator*=(vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n >= 1) v1.x *= v2;
    if constexpr (t_n >= 2) v1.y *= v2;
    if constexpr (t_n >= 3) v1.z *= v2;
    if constexpr (t_n >= 4) v1.w *= v2;
    return v1;
}

//--- divide assign ---

template <typename T, int t_n>
inline vec<T, t_n> & operator/=(vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n >= 1) v1.x /= v2.x;
    if constexpr (t_n >= 2) v1.y /= v2.y;
    if constexpr (t_n >= 3) v1.z /= v2.z;
    if constexpr (t_n >= 4) v1.w /= v2.w;
    return v1;
}

template <typename T, int t_n>
inline vec<T, t_n> & operator/=(vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n > 1 && std::is_floating_point_v<T>) return v1 *= T(1.0) / v2;
    if constexpr (t_n >= 1) v1.x /= v2;
    if constexpr (t_n >= 2) v1.y /= v2;
    if constexpr (t_n >= 3) v1.z /= v2;
    if constexpr (t_n >= 4) v1.w /= v2;
    return v1;
}

//--- modulus assign ---

template <typename T, int t_n>
inline vec<T, t_n> & operator%=(vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n >= 1) v1.x = mod(v1.x, v2.x);
    if constexpr (t_n >= 2) v1.y = mod(v1.y, v2.y);
    if constexpr (t_n >= 3) v1.z = mod(v1.z, v2.z);
    if constexpr (t_n >= 4) v1.w = mod(v1.w, v2.w);
    return v1;
}

template <typename T, int t_n>
inline vec<T, t_n> & operator%=(vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n >= 1) v1.x = mod(v1.x, v2);
    if constexpr (t_n >= 2) v1.y = mod(v1.y, v2);
    if constexpr (t_n >= 3) v1.z = mod(v1.z, v2);
    if constexpr (t_n >= 4) v1.w = mod(v1.w, v2);
    return v1;
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- positive ---

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator+(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return vec1<T>(+v.x);
    if constexpr (t_n == 2) return vec2<T>(+v.x, +v.y);
    if constexpr (t_n == 3) return vec3<T>(+v.x, +v.y, +v.z);
    if constexpr (t_n == 4) return vec4<T>(+v.x, +v.y, +v.z, +v.w);
}

//--- negative ---

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator-(const vec<T, t_n> & v) {
    if constexpr (std::is_unsigned_v<T>) return v;
    if constexpr (!std::is_unsigned_v<T>) {
        if constexpr (t_n == 1) return vec1<T>(-v.x);
        if constexpr (t_n == 2) return vec2<T>(-v.x, -v.y);
        if constexpr (t_n == 3) return vec3<T>(-v.x, -v.y, -v.z);
        if constexpr (t_n == 4) return vec4<T>(-v.x, -v.y, -v.z, -v.w);
    }
}

//--- add ---

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator+(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(v1.x + v2.x);
    if constexpr (t_n == 2) return vec2<T>(v1.x + v2.x, v1.y + v2.y);
    if constexpr (t_n == 3) return vec3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
    if constexpr (t_n == 4) return vec4<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator+(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return vec1<T>(v1.x + v2);
    if constexpr (t_n == 2) return vec2<T>(v1.x + v2, v1.y + v2);
    if constexpr (t_n == 3) return vec3<T>(v1.x + v2, v1.y + v2, v1.z + v2);
    if constexpr (t_n == 4) return vec4<T>(v1.x + v2, v1.y + v2, v1.z + v2, v1.w + v2);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator+(const T & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(v1 + v2.x);
    if constexpr (t_n == 2) return vec2<T>(v1 + v2.x, v1 + v2.y);
    if constexpr (t_n == 3) return vec3<T>(v1 + v2.x, v1 + v2.y, v1 + v2.z);
    if constexpr (t_n == 4) return vec4<T>(v1 + v2.x, v1 + v2.y, v1 + v2.z, v1 + v2.w);
}

//--- subtract ---

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator-(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(v1.x - v2.x);
    if constexpr (t_n == 2) return vec2<T>(v1.x - v2.x, v1.y - v2.y);
    if constexpr (t_n == 3) return vec3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
    if constexpr (t_n == 4) return vec4<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator-(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return vec1<T>(v1.x - v2);
    if constexpr (t_n == 2) return vec2<T>(v1.x - v2, v1.y - v2);
    if constexpr (t_n == 3) return vec3<T>(v1.x - v2, v1.y - v2, v1.z - v2);
    if constexpr (t_n == 4) return vec4<T>(v1.x - v2, v1.y - v2, v1.z - v2, v1.w - v2);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator-(const T & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(v1 - v2.x);
    if constexpr (t_n == 2) return vec2<T>(v1 - v2.x, v1 - v2.y);
    if constexpr (t_n == 3) return vec3<T>(v1 - v2.x, v1 - v2.y, v1 - v2.z);
    if constexpr (t_n == 4) return vec4<T>(v1 - v2.x, v1 - v2.y, v1 - v2.z, v1 - v2.w);
}

//--- multiply ---

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator*(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(v1.x * v2.x);
    if constexpr (t_n == 2) return vec2<T>(v1.x * v2.x, v1.y * v2.y);
    if constexpr (t_n == 3) return vec3<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
    if constexpr (t_n == 4) return vec4<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator*(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return vec1<T>(v1.x * v2);
    if constexpr (t_n == 2) return vec2<T>(v1.x * v2, v1.y * v2);
    if constexpr (t_n == 3) return vec3<T>(v1.x * v2, v1.y * v2, v1.z * v2);
    if constexpr (t_n == 4) return vec4<T>(v1.x * v2, v1.y * v2, v1.z * v2, v1.w * v2);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator*(const T & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(v1 * v2.x);
    if constexpr (t_n == 2) return vec2<T>(v1 * v2.x, v1 * v2.y);
    if constexpr (t_n == 3) return vec3<T>(v1 * v2.x, v1 * v2.y, v1 * v2.z);
    if constexpr (t_n == 4) return vec4<T>(v1 * v2.x, v1 * v2.y, v1 * v2.z, v1 * v2.w);
}

//--- divide ---

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator/(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(v1.x / v2.x);
    if constexpr (t_n == 2) return vec2<T>(v1.x / v2.x, v1.y / v2.y);
    if constexpr (t_n == 3) return vec3<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
    if constexpr (t_n == 4) return vec4<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator/(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n > 1 && std::is_floating_point_v<T>) return v1 * (T(1.0) / v2);
    if constexpr (t_n == 1) return vec1<T>(v1.x / v2);
    if constexpr (t_n == 2) return vec2<T>(v1.x / v2, v1.y / v2);
    if constexpr (t_n == 3) return vec3<T>(v1.x / v2, v1.y / v2, v1.z / v2);
    if constexpr (t_n == 4) return vec4<T>(v1.x / v2, v1.y / v2, v1.z / v2, v1.w / v2);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator/(const T & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(v1 / v2.x);
    if constexpr (t_n == 2) return vec2<T>(v1 / v2.x, v1 / v2.y);
    if constexpr (t_n == 3) return vec3<T>(v1 / v2.x, v1 / v2.y, v1 / v2.z);
    if constexpr (t_n == 4) return vec4<T>(v1 / v2.x, v1 / v2.y, v1 / v2.z, v1 / v2.w);
}

//--- modulus ---

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator%(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(mod(v1.x, v2.x));
    if constexpr (t_n == 2) return vec2<T>(mod(v1.x, v2.x), mod(v1.y, v2.y));
    if constexpr (t_n == 3) return vec3<T>(mod(v1.x, v2.x), mod(v1.y, v2.y), mod(v1.z, v2.z));
    if constexpr (t_n == 4) return vec4<T>(mod(v1.x, v2.x), mod(v1.y, v2.y), mod(v1.z, v2.z), mod(v1.w, v2.w));
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator%(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return vec1<T>(mod(v1.x, v2));
    if constexpr (t_n == 2) return vec2<T>(mod(v1.x, v2), mod(v1.y, v2));
    if constexpr (t_n == 3) return vec3<T>(mod(v1.x, v2), mod(v1.y, v2), mod(v1.z, v2));
    if constexpr (t_n == 4) return vec4<T>(mod(v1.x, v2), mod(v1.y, v2), mod(v1.z, v2), mod(v1.w, v2));
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator%(const T & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(mod(v1, v2.x));
    if constexpr (t_n == 2) return vec2<T>(mod(v1, v2.x), mod(v1, v2.y));
    if constexpr (t_n == 3) return vec3<T>(mod(v1, v2.x), mod(v1, v2.y), mod(v1, v2.z));
    if constexpr (t_n == 4) return vec4<T>(mod(v1, v2.x), mod(v1, v2.y), mod(v1, v2.z), mod(v1, v2.w));
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T, int t_n>
Q_CX_ABLE bool operator==(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return v1.x == v2.x;
    if constexpr (t_n == 2) return v1.x == v2.x && v1.y == v2.y;
    if constexpr (t_n == 3) return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
    if constexpr (t_n == 4) return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator==(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x == v2);
    if constexpr (t_n == 2) return bvec2(v1.x == v2, v1.y == v2);
    if constexpr (t_n == 3) return bvec3(v1.x == v2, v1.y == v2, v1.z == v2);
    if constexpr (t_n == 4) return bvec4(v1.x == v2, v1.y == v2, v1.z == v2, v1.w == v2);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator==(const T & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1 == v2.x);
    if constexpr (t_n == 2) return bvec2(v1 == v2.x, v1 == v2.y);
    if constexpr (t_n == 3) return bvec3(v1 == v2.x, v1 == v2.y, v1 == v2.z);
    if constexpr (t_n == 4) return bvec4(v1 == v2.x, v1 == v2.y, v1 == v2.z, v1 == v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE bool operator==(const span<T, t_n> & s1, const span<T, t_n> & s2) {
    return s1.min == s2.min && s1.max == s2.max;
}

//--- not equal to ---

template <typename T, int t_n>
Q_CX_ABLE bool operator!=(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return v1.x != v2.x;
    if constexpr (t_n == 2) return v1.x != v2.x || v1.y != v2.y;
    if constexpr (t_n == 3) return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z;
    if constexpr (t_n == 4) return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z || v1.w != v2.w;
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator!=(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x != v2);
    if constexpr (t_n == 2) return bvec2(v1.x != v2, v1.y != v2);
    if constexpr (t_n == 3) return bvec3(v1.x != v2, v1.y != v2, v1.z != v2);
    if constexpr (t_n == 4) return bvec4(v1.x != v2, v1.y != v2, v1.z != v2, v1.w != v2);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator!=(const T & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1 != v2.x);
    if constexpr (t_n == 2) return bvec2(v1 != v2.x, v1 != v2.y);
    if constexpr (t_n == 3) return bvec3(v1 != v2.x, v1 != v2.y, v1 != v2.z);
    if constexpr (t_n == 4) return bvec4(v1 != v2.x, v1 != v2.y, v1 != v2.z, v1 != v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE bool operator!=(const span<T, t_n> & s1, const span<T, t_n> & s2) {
    return s1.min != s2.min || s1.max != s2.max;
}

//--- less than ---

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator<(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x < v2.x);
    if constexpr (t_n == 2) return bvec2(v1.x < v2.x, v1.y < v2.y);
    if constexpr (t_n == 3) return bvec3(v1.x < v2.x, v1.y < v2.y, v1.z < v2.z);
    if constexpr (t_n == 4) return bvec4(v1.x < v2.x, v1.y < v2.y, v1.z < v2.z, v1.w < v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator<(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x < v2);
    if constexpr (t_n == 2) return bvec2(v1.x < v2, v1.y < v2);
    if constexpr (t_n == 3) return bvec3(v1.x < v2, v1.y < v2, v1.z < v2);
    if constexpr (t_n == 4) return bvec4(v1.x < v2, v1.y < v2, v1.z < v2, v1.w < v2);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator<(const T & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1 < v2.x);
    if constexpr (t_n == 2) return bvec2(v1 < v2.x, v1 < v2.y);
    if constexpr (t_n == 3) return bvec3(v1 < v2.x, v1 < v2.y, v1 < v2.z);
    if constexpr (t_n == 4) return bvec4(v1 < v2.x, v1 < v2.y, v1 < v2.z, v1 < v2.w);
}

//--- greater than ---

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator>(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x > v2.x);
    if constexpr (t_n == 2) return bvec2(v1.x > v2.x, v1.y > v2.y);
    if constexpr (t_n == 3) return bvec3(v1.x > v2.x, v1.y > v2.y, v1.z > v2.z);
    if constexpr (t_n == 4) return bvec4(v1.x > v2.x, v1.y > v2.y, v1.z > v2.z, v1.w > v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator>(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x > v2);
    if constexpr (t_n == 2) return bvec2(v1.x > v2, v1.y > v2);
    if constexpr (t_n == 3) return bvec3(v1.x > v2, v1.y > v2, v1.z > v2);
    if constexpr (t_n == 4) return bvec4(v1.x > v2, v1.y > v2, v1.z > v2, v1.w > v2);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator>(const T & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1 > v2.x);
    if constexpr (t_n == 2) return bvec2(v1 > v2.x, v1 > v2.y);
    if constexpr (t_n == 3) return bvec3(v1 > v2.x, v1 > v2.y, v1 > v2.z);
    if constexpr (t_n == 4) return bvec4(v1 > v2.x, v1 > v2.y, v1 > v2.z, v1 > v2.w);
}

//--- less than or equal to ---

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator<=(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x <= v2.x);
    if constexpr (t_n == 2) return bvec2(v1.x <= v2.x, v1.y <= v2.y);
    if constexpr (t_n == 3) return bvec3(v1.x <= v2.x, v1.y <= v2.y, v1.z <= v2.z);
    if constexpr (t_n == 4) return bvec4(v1.x <= v2.x, v1.y <= v2.y, v1.z <= v2.z, v1.w <= v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator<=(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x <= v2);
    if constexpr (t_n == 2) return bvec2(v1.x <= v2, v1.y <= v2);
    if constexpr (t_n == 3) return bvec3(v1.x <= v2, v1.y <= v2, v1.z <= v2);
    if constexpr (t_n == 4) return bvec4(v1.x <= v2, v1.y <= v2, v1.z <= v2, v1.w <= v2);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator<=(const T & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1 <= v2.x);
    if constexpr (t_n == 2) return bvec2(v1 <= v2.x, v1 <= v2.y);
    if constexpr (t_n == 3) return bvec3(v1 <= v2.x, v1 <= v2.y, v1 <= v2.z);
    if constexpr (t_n == 4) return bvec4(v1 <= v2.x, v1 <= v2.y, v1 <= v2.z, v1 <= v2.w);
}

//--- greater than or equal to ---

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator>=(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x >= v2.x);
    if constexpr (t_n == 2) return bvec2(v1.x >= v2.x, v1.y >= v2.y);
    if constexpr (t_n == 3) return bvec3(v1.x >= v2.x, v1.y >= v2.y, v1.z >= v2.z);
    if constexpr (t_n == 4) return bvec4(v1.x >= v2.x, v1.y >= v2.y, v1.z >= v2.z, v1.w >= v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator>=(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x >= v2);
    if constexpr (t_n == 2) return bvec2(v1.x >= v2, v1.y >= v2);
    if constexpr (t_n == 3) return bvec3(v1.x >= v2, v1.y >= v2, v1.z >= v2);
    if constexpr (t_n == 4) return bvec4(v1.x >= v2, v1.y >= v2, v1.z >= v2, v1.w >= v2);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator>=(const T & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1 >= v2.x);
    if constexpr (t_n == 2) return bvec2(v1 >= v2.x, v1 >= v2.y);
    if constexpr (t_n == 3) return bvec3(v1 >= v2.x, v1 >= v2.y, v1 >= v2.z);
    if constexpr (t_n == 4) return bvec4(v1 >= v2.x, v1 >= v2.y, v1 >= v2.z, v1 >= v2.w);
}



//------------------------------------------------------------------------------
// Logic Operators



template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator&&(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x && v2.x);
    if constexpr (t_n == 2) return bvec2(v1.x && v2.x, v1.y && v2.y);
    if constexpr (t_n == 3) return bvec3(v1.x && v2.x, v1.y && v2.y, v1.z && v2.z);
    if constexpr (t_n == 4) return bvec4(v1.x && v2.x, v1.y && v2.y, v1.z && v2.z, v1.w && v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator||(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x || v2.x);
    if constexpr (t_n == 2) return bvec2(v1.x || v2.x, v1.y || v2.y);
    if constexpr (t_n == 3) return bvec3(v1.x || v2.x, v1.y || v2.y, v1.z || v2.z);
    if constexpr (t_n == 4) return bvec4(v1.x || v2.x, v1.y || v2.y, v1.z || v2.z, v1.w || v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator!(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return bvec1(!v.x);
    if constexpr (t_n == 2) return bvec2(!v.x, !v.y);
    if constexpr (t_n == 3) return bvec3(!v.x, !v.y, !v.z);
    if constexpr (t_n == 4) return bvec4(!v.x, !v.y, !v.z, !v.w);
}



//------------------------------------------------------------------------------
// Condensation



template <typename T, int t_n>
Q_CX_ABLE T sum(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return v.x;
    if constexpr (t_n == 2) return v.x + v.y;
    if constexpr (t_n == 3) return v.x + v.y + v.z;
    if constexpr (t_n == 4) return v.x + v.y + v.z + v.w;
}

template <typename T, int t_n>
Q_CX_ABLE T product(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return v.x;
    if constexpr (t_n == 2) return v.x * v.y;
    if constexpr (t_n == 3) return v.x * v.y * v.z;
    if constexpr (t_n == 4) return v.x * v.y * v.z * v.w;
}

template <typename T, int t_n>
Q_CX_ABLE bool conjunct(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return v.x;
    if constexpr (t_n == 2) return v.x && v.y;
    if constexpr (t_n == 3) return v.x && v.y && v.z;
    if constexpr (t_n == 4) return v.x && v.y && v.z && v.w;
}

template <typename T, int t_n>
Q_CX_ABLE bool disjunct(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return v.x;
    if constexpr (t_n == 2) return v.x || v.y;
    if constexpr (t_n == 3) return v.x || v.y || v.z;
    if constexpr (t_n == 4) return v.x || v.y || v.z || v.w;
}



//------------------------------------------------------------------------------
// Other



template <typename T, int t_n>
inline std::ostream & operator<<(std::ostream & os, const vec<T, t_n> & v) {
    os << "[";
    if constexpr (t_n >= 1) os << " " << v.x << " ";
    if constexpr (t_n >= 2) os << v.y << " ";
    if constexpr (t_n >= 3) os << v.z << " ";
    if constexpr (t_n >= 4) os << v.w << " ";
    os << "]";
    return os;
}

template <typename T, int t_n>
inline std::ostream & operator<<(std::ostream & os, const span<T, t_n> & s) {
    return os << "[" << s.min << s.max << "]";
}



//------------------------------------------------------------------------------
// Uncategorized



template <typename T, int t_n, eif_floating_t<T>>
inline vec<T, t_n> pow(const vec<T, t_n> & v, T p) {
    if constexpr (t_n == 1) return vec1<T>(std::pow(v.x, p));
    if constexpr (t_n == 2) return vec2<T>(std::pow(v.x, p), std::pow(v.y, p));
    if constexpr (t_n == 3) return vec3<T>(std::pow(v.x, p), std::pow(v.y, p), std::pow(v.z, p));
    if constexpr (t_n == 4) return vec4<T>(std::pow(v.x, p), std::pow(v.y, p), std::pow(v.z, p), std::pow(v.w, p));
}

template <typename T, int t_n, eif_floating_t<T>>
inline vec<T, t_n> pow(const vec<T, t_n> & v, const vec<T, t_n> & p) {
    if constexpr (t_n == 1) return vec1<T>(std::pow(v.x, p.x));
    if constexpr (t_n == 2) return vec2<T>(std::pow(v.x, p.x), std::pow(v.y, p.y));
    if constexpr (t_n == 3) return vec3<T>(std::pow(v.x, p.x), std::pow(v.y, p.y), std::pow(v.z, p.z));
    if constexpr (t_n == 4) return vec4<T>(std::pow(v.x, p.x), std::pow(v.y, p.y), std::pow(v.z, p.z), std::pow(v.w, p.w));
}

template <typename T, int t_n, eif_floating_t<T>>
inline vec<T, t_n> exp(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return vec1<T>(std::exp(v.x));
    if constexpr (t_n == 2) return vec2<T>(std::exp(v.x), std::exp(v.y));
    if constexpr (t_n == 3) return vec3<T>(std::exp(v.x), std::exp(v.y), std::exp(v.z));
    if constexpr (t_n == 4) return vec4<T>(std::exp(v.x), std::exp(v.y), std::exp(v.z), std::exp(v.w));
}

template <typename T, int t_n, eif_floating_t<T>>
inline T magnitude(const vec<T, t_n> & v) {
    return T(std::sqrt(magnitude2(v)));
}

template <typename T, int t_n>
inline T magnitude2(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return v.x * v.x;
    if constexpr (t_n == 2) return v.x * v.x + v.y * v.y;
    if constexpr (t_n == 3) return v.x * v.x + v.y * v.y + v.z * v.z;
    if constexpr (t_n == 4) return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}

template <typename T, int t_n, eif_floating_t<T>>
inline vec<T, t_n> norm(const vec<T, t_n> & v) {
    T m2(magnitude2(v));
    if (zero(m2)) {
        return vec<T, t_n>();
    }
    return v * (T(1.0) / std::sqrt(m2));
}

template <typename T, int t_n>
inline T dot(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return v1.x * v2.x;
    if constexpr (t_n == 2) return v1.x * v2.x + v1.y * v2.y;
    if constexpr (t_n == 3) return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    if constexpr (t_n == 4) return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

template <typename T>
inline T cross(const vec2<T> & v1, const vec2<T> & v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

template <typename T>
inline vec3<T> cross(const vec3<T> & v1, const vec3<T> & v2) {
    return vec3<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

template <typename T, int t_n>
inline bool parallel(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    T d(dot(v1, v2));
    return equal(d * d, magnitude2(v1) * magnitude2(v2));
}

template <typename T, int t_n>
inline bool orthogonal(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    return zero(dot(v1, v2));
}

template <typename T>
Q_CX_ABLE vec2<T> ortho(const vec2<T> & v) {
    return vec2<T>(-v.y, v.x);
}

template <typename T>
inline vec3<T> ortho(const vec3<T> & v) {    
    if (abs(v.x) < abs(v.y)) {
        if (abs(v.x) <= abs(v.z)) {   // x or z is smallest
            return vec3<T>(0, -v.z, v.y);       // rotate around x
        }
        else {                                  // z is smallest
            return vec3<T>(-v.y, v.x, 0);       // rotate around z
        }
    }
    else {
        if (abs(v.y) < abs(v.z)) {    // y or x is smallest
            return vec3<T>(v.z, 0, -v.x);       // rotate around y
        }
        else {                                  // z or y is smallest
            return vec3<T>(-v.y, v.x, 0);       // rotate around z
        }
    }
}

template <typename T, int t_n, eif_floating_t<T>>
inline void orthogonalize(const vec<T, t_n> & v1, vec<T, t_n> & v2) {
    if constexpr (t_n == 1) {
        v2 = vec1<T>();
    }
    if constexpr (t_n > 1) {
        v2 = norm(v2 - dot(v1, v2) * v1);
    }
}

// in order of priority
template <typename T, eif_floating_t<T>>
inline void orthogonalize(const vec3<T> & v1, vec3<T> & v2, vec3<T> & v3) {
    orthogonalize_n(v1, v2, v3);
    v2 = norm(v2);
    v3 = norm(v3);
}

// in order of priority
template <typename T, eif_floating_t<T>>
inline void orthogonalize_n(const vec3<T> & v1, vec3<T> & v2, vec3<T> & v3) {
    orthogonalize(v1, v2);
    v3 = cross(v2, v1);
}

template <typename T, int t_n, eif_floating_t<T>>
inline vec<T, t_n> reflect(const vec<T, t_n> & v, const vec<T, t_n> & n) {
    return reflect_n(v, norm(n));
}

template <typename T, int t_n, eif_floating_t<T>>
inline vec<T, t_n> reflect_n(const vec<T, t_n> & v, const vec<T, t_n> & n) {
    return (T(2.0) * dot(v, n)) * n - v;
}

template <typename T, int t_n, eif_floating_t<T>>
inline T angle(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    return angle_n(norm(v1), norm(v2));
}
template <typename T, int t_n, eif_floating_t<T>>
inline T angle_n(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    return T(std::acos(dot(v1, v2)));
}

template <typename T, int t_n>
Q_CX_ABLE const T & min(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return v.x;
    if constexpr (t_n == 2) return min(v.x, v.y);
    if constexpr (t_n == 3) return min(v.x, v.y, v.z);
    if constexpr (t_n == 4) return min(v.x, v.y, v.z, v.w);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> min(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(min(v1.x, v2.x));
    if constexpr (t_n == 2) return vec2<T>(min(v1.x, v2.x), min(v1.y, v2.y));
    if constexpr (t_n == 3) return vec3<T>(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z));
    if constexpr (t_n == 4) return vec4<T>(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z), min(v1.w, v2.w));
}

template <typename T, int t_n, typename... Ts>
Q_CX_ABLE vec<T, t_n> min(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<Ts, t_n> &... rest) {
    return min(min(v1, v2), rest...);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> min(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return vec1<T>(min(v1.x, v2));
    if constexpr (t_n == 2) return vec2<T>(min(v1.x, v2), min(v1.y, v2));
    if constexpr (t_n == 3) return vec3<T>(min(v1.x, v2), min(v1.y, v2), min(v1.z, v2));
    if constexpr (t_n == 4) return vec4<T>(min(v1.x, v2), min(v1.y, v2), min(v1.z, v2), min(v1.w, v2));
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> min(const T & v1, const vec<T, t_n> & v2) {
    return min(v2, v1);
}

template <typename T, int t_n>
Q_CX_ABLE const T & max(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return v.x;
    if constexpr (t_n == 2) return max(v.x, v.y);
    if constexpr (t_n == 3) return max(v.x, v.y, v.z);
    if constexpr (t_n == 4) return max(v.x, v.y, v.z, v.w);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> max(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(max(v1.x, v2.x));
    if constexpr (t_n == 2) return vec2<T>(max(v1.x, v2.x), max(v1.y, v2.y));
    if constexpr (t_n == 3) return vec3<T>(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z));
    if constexpr (t_n == 4) return vec4<T>(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z), max(v1.w, v2.w));
}

template <typename T, int t_n, typename... Ts>
Q_CX_ABLE vec<T, t_n> max(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<Ts, t_n> &... rest) {
    return max(max(v1, v2), rest...);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> max(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return vec1<T>(max(v1.x, v2));
    if constexpr (t_n == 2) return vec2<T>(max(v1.x, v2), max(v1.y, v2));
    if constexpr (t_n == 3) return vec3<T>(max(v1.x, v2), max(v1.y, v2), max(v1.z, v2));
    if constexpr (t_n == 4) return vec4<T>(max(v1.x, v2), max(v1.y, v2), max(v1.z, v2), max(v1.w, v2));
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> max(const T & v1, const vec<T, t_n> & v2) {
    return max(v2, v1);
}

template <typename T, int t_n>
Q_CX_ABLE std::pair<const T &, const T &> minmax(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return minmax(v.x);
    if constexpr (t_n == 2) return minmax(v.x, v.y);
    if constexpr (t_n == 3) return minmax(v.x, v.y, v.z);
    if constexpr (t_n == 4) return minmax(v.x, v.y, v.z, v.w);
}

template <typename T, int t_n>
inline void sort(vec<T, t_n> & v) {
    if constexpr (t_n >= 2) {
        if (v.x > v.y) std::swap(v.x, v.y);
    }
    if constexpr (t_n >= 3) {
        if (v.y > v.z) std::swap(v.y, v.z);
        if (v.x > v.y) std::swap(v.x, v.y);
    }
    if constexpr (t_n >= 4) {
        if (v.z > v.w) std::swap(v.z, v.w);
        if (v.y > v.z) std::swap(v.y, v.z);
        if (v.x > v.y) std::swap(v.x, v.y);
    }
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> clamp(const vec<T, t_n> & v, const T & min, const T & max) {
    if constexpr (t_n == 1) return vec1<T>(clamp(v.x, min, max));
    if constexpr (t_n == 2) return vec2<T>(clamp(v.x, min, max), clamp(v.y, min, max));
    if constexpr (t_n == 3) return vec3<T>(clamp(v.x, min, max), clamp(v.y, min, max), clamp(v.z, min, max));
    if constexpr (t_n == 4) return vec4<T>(clamp(v.x, min, max), clamp(v.y, min, max), clamp(v.z, min, max), clamp(v.w, min, max));
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> clamp(const vec<T, t_n> & v, const vec<T, t_n> & min, const vec<T, t_n> & max) {
    if constexpr (t_n == 1) return vec1<T>(clamp(v.x, min.x, max.x));
    if constexpr (t_n == 2) return vec2<T>(clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y));
    if constexpr (t_n == 3) return vec3<T>(clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y), clamp(v.z, min.z, max.z));
    if constexpr (t_n == 4) return vec4<T>(clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y), clamp(v.z, min.z, max.z), clamp(v.w, min.w, max.w));
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> abs(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return vec1<T>(abs(v.x));
    if constexpr (t_n == 2) return vec2<T>(abs(v.x), abs(v.y));
    if constexpr (t_n == 3) return vec3<T>(abs(v.x), abs(v.y), abs(v.z));
    if constexpr (t_n == 4) return vec4<T>(abs(v.x), abs(v.y), abs(v.z), abs(v.w));
}

template <typename T, int t_n, eif_arithmetic_t<T>>
Q_CX_ABLE bool zero(const vec<T, t_n> & v, T e) {
    if constexpr (t_n == 1) return zero(v.x, e);
    if constexpr (t_n == 2) return zero(v.x, e) && zero(v.y, e);
    if constexpr (t_n == 3) return zero(v.x, e) && zero(v.y, e) && zero(v.z, e);
    if constexpr (t_n == 4) return zero(v.x, e) && zero(v.y, e) && zero(v.z, e) && zero(v.w, e);
}

template <typename T, int t_n>
Q_CX_ABLE bool equal(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return equal(v1.x, v2.x);
    if constexpr (t_n == 2) return equal(v1.x, v2.x) && equal(v1.y, v2.y);
    if constexpr (t_n == 3) return equal(v1.x, v2.x) && equal(v1.y, v2.y) && equal(v1.z, v2.z);
    if constexpr (t_n == 4) return equal(v1.x, v2.x) && equal(v1.y, v2.y) && equal(v1.z, v2.z) && equal(v1.w, v2.w);
}

template <typename T, int t_n, eif_floating_t<T>>
Q_CX_ABLE bool equalE(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & e) {
    if constexpr (t_n == 1) return equalE(v1.x, v2.x, e.x);
    if constexpr (t_n == 2) return equalE(v1.x, v2.x, e.x) && equalE(v1.y, v2.y, e.y);
    if constexpr (t_n == 3) return equalE(v1.x, v2.x, e.x) && equalE(v1.y, v2.y, e.y) && equalE(v1.z, v2.z, e.z);
    if constexpr (t_n == 4) return equalE(v1.x, v2.x, e.x) && equalE(v1.y, v2.y, e.y) && equalE(v1.z, v2.z, e.z) && equalE(v1.w, v2.w, e.w);
}

template <typename T, int t_n>
Q_CX_ABLE bool equal(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return true;
    if constexpr (t_n == 2) return v.x == v.y;
    if constexpr (t_n == 3) return v.x == v.y && v.x == v.z;
    if constexpr (t_n == 4) return v.x == v.y && v.x == v.z && v.x == v.w;
}

template <typename T, int t_n>
Q_CX_ABLE vec<nat, t_n> floor(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return vec1<nat>(floor(v.x));
    if constexpr (t_n == 2) return vec2<nat>(floor(v.x), floor(v.y));
    if constexpr (t_n == 3) return vec3<nat>(floor(v.x), floor(v.y), floor(v.z));
    if constexpr (t_n == 4) return vec4<nat>(floor(v.x), floor(v.y), floor(v.z), floor(v.w));
}

template <typename T, int t_n>
Q_CX_ABLE vec<nat, t_n> ceil(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return vec1<nat>(ceil(v.x));
    if constexpr (t_n == 2) return vec2<nat>(ceil(v.x), ceil(v.y));
    if constexpr (t_n == 3) return vec3<nat>(ceil(v.x), ceil(v.y), ceil(v.z));
    if constexpr (t_n == 4) return vec4<nat>(ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w));
}

template <typename T, int t_n, eif_floating_t<T>>
Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, T t) {
    return (T(1.0) - t) * v1 + t * v2;
}


template <typename T, eif_floating_t<T>>
Q_CX_ABLE T mix(T v1, T v2, const vec2<T> & weights) {
    return weights.x * v1 + weights.y * v2;
}

template <typename T, int t_n, eif_floating_t<T>>
Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec2<T> & weights) {
    return weights.x * v1 + weights.y * v2;
}

template <typename T, eif_floating_t<T>>
Q_CX_ABLE T mix(T v1, T v2, T v3, const vec3<T> & weights) {
    return weights.x * v1 + weights.y * v2 + weights.z * v3;
}

template <typename T, int t_n, eif_floating_t<T>>
Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & v3, const vec3<T> & weights) {
    return weights.x * v1 + weights.y * v2 + weights.z * v3;
}

template <typename T, eif_floating_t<T>>
Q_CX_ABLE T mix(T v1, T v2, T v3, T v4, const vec4<T> & weights) {
    return weights.x * v1 + weights.y * v2 + weights.z * v3 + weights.w * v4;
}

template <typename T, int t_n, eif_floating_t<T>>
Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & v3, const vec<T, t_n> & v4, const vec4<T> & weights) {
    return weights.x * v1 + weights.y * v2 + weights.z * v3 + weights.w * v4;
}

template <typename To, typename From, int t_n, eif_t<std::is_arithmetic_v<To> && std::is_arithmetic_v<From>>>
Q_CONSTEX vec<To, t_n> transnorm(const vec<From, t_n> & v) {
    if constexpr (t_n == 1) return vec1<To>(transnorm<To>(v.x));
    if constexpr (t_n == 2) return vec2<To>(transnorm<To>(v.x), transnorm<To>(v.y));
    if constexpr (t_n == 3) return vec3<To>(transnorm<To>(v.x), transnorm<To>(v.y), transnorm<To>(v.z));
    if constexpr (t_n == 4) return vec4<To>(transnorm<To>(v.x), transnorm<To>(v.y), transnorm<To>(v.z), transnorm<To>(v.w));
}

template <typename T, int t_n>
Q_CX_ABLE span<T, t_n> toSpan(const bound<T, t_n> & b) {
    return span<T, t_n>(b.min, b.min + b.max);
}

template <typename T, int t_n>
Q_CX_ABLE bound<T, t_n> toBound(const span<T, t_n> & s) {
    return bound<T, t_n>(s.min, s.max - s.min);
}

template <typename T, int t_n>
Q_CX_ABLE span<T, t_n> intersect(const span<T, t_n> & s1, const span<T, t_n> & s2) {
    if constexpr (t_n == 1) return span1<T>(
        vec1<T>(max(s1.min.x, s2.min.x)),
        vec1<T>(min(s1.max.x, s2.max.x))
    );
    if constexpr (t_n == 2) return span2<T>(
        vec2<T>(max(s1.min.x, s2.min.x), max(s1.min.y, s2.min.y)),
        vec2<T>(min(s1.max.x, s2.max.x), min(s1.max.y, s2.max.y))
    );
    if constexpr (t_n == 3) return span3<T>(
        vec3<T>(max(s1.min.x, s2.min.x), max(s1.min.y, s2.min.y), max(s1.min.z, s2.min.z)),
        vec3<T>(min(s1.max.x, s2.max.x), min(s1.max.y, s2.max.y), min(s1.max.z, s2.max.z))
    );
    if constexpr (t_n == 4) return span4<T>(
        vec4<T>(max(s1.min.x, s2.min.x), max(s1.min.y, s2.min.y), max(s1.min.z, s2.min.z), max(s1.min.w, s2.min.w)),
        vec4<T>(min(s1.max.x, s2.max.x), min(s1.max.y, s2.max.y), min(s1.max.z, s2.max.z), min(s1.max.w, s2.max.w))
    );
}

template <typename T, int t_n, eif_integral_t<T>>
Q_CX_ABLE T mipmaps(const vec<T, t_n> & size) {
    return mipmaps(max(size));
}



//#endif



}