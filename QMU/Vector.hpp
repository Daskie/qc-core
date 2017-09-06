#pragma once



#include <iostream>
#include <string>
#include <sstream>

#include "Core.hpp"



namespace qmu {



//======================================================================================================================
// TYPES ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



//==============================================================================
// Vec Types
//------------------------------------------------------------------------------



template <typename T, nat t_n> struct vec;

template <typename T> using vec1 = vec<T, 1>;
template <typename T> using vec2 = vec<T, 2>;
template <typename T> using vec3 = vec<T, 3>;
template <typename T> using vec4 = vec<T, 4>;

template <nat t_n> using   fvec = vec<               float, t_n>;
template <nat t_n> using   dvec = vec<              double, t_n>;
template <nat t_n> using  ldvec = vec<         long double, t_n>;
template <nat t_n> using   cvec = vec<  signed        char, t_n>;
template <nat t_n> using  ucvec = vec<unsigned        char, t_n>;
template <nat t_n> using   svec = vec<  signed       short, t_n>;
template <nat t_n> using  usvec = vec<unsigned       short, t_n>;
template <nat t_n> using   ivec = vec<  signed         int, t_n>;
template <nat t_n> using  uivec = vec<unsigned         int, t_n>;
template <nat t_n> using   lvec = vec<  signed        long, t_n>;
template <nat t_n> using  ulvec = vec<unsigned        long, t_n>;
template <nat t_n> using  llvec = vec<  signed long   long, t_n>;
template <nat t_n> using ullvec = vec<unsigned long   long, t_n>;
template <nat t_n> using   nvec = vec<                 nat, t_n>;
template <nat t_n> using  unvec = vec<                unat, t_n>;
template <nat t_n> using   bvec = vec<                bool, t_n>;

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



template <typename T, nat t_n> struct span;

template <typename T> using span1 = span<T, 1>;
template <typename T> using span2 = span<T, 2>;
template <typename T> using span3 = span<T, 3>;
template <typename T> using span4 = span<T, 4>;

template <nat t_n> using   fspan = span<               float, t_n>;
template <nat t_n> using   dspan = span<              double, t_n>;
template <nat t_n> using  ldspan = span<         long double, t_n>;
template <nat t_n> using   cspan = span<  signed        char, t_n>;
template <nat t_n> using  ucspan = span<unsigned        char, t_n>;
template <nat t_n> using   sspan = span<  signed       short, t_n>;
template <nat t_n> using  usspan = span<unsigned       short, t_n>;
template <nat t_n> using   ispan = span<  signed         int, t_n>;
template <nat t_n> using  uispan = span<unsigned         int, t_n>;
template <nat t_n> using   lspan = span<  signed        long, t_n>;
template <nat t_n> using  ulspan = span<unsigned        long, t_n>;
template <nat t_n> using  llspan = span<  signed long   long, t_n>;
template <nat t_n> using ullspan = span<unsigned long   long, t_n>;
template <nat t_n> using   nspan = span<                 nat, t_n>;
template <nat t_n> using  unspan = span<                unat, t_n>;

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



template <typename T, nat t_n> using bound = span<T, t_n>;

template <typename T> using bound1 = span1<T>;
template <typename T> using bound2 = span2<T>;
template <typename T> using bound3 = span3<T>;
template <typename T> using bound4 = span4<T>;

template <nat t_n> using   fbound =   fspan<t_n>;
template <nat t_n> using   dbound =   dspan<t_n>;
template <nat t_n> using  ldbound =  ldspan<t_n>;
template <nat t_n> using   cbound =   cspan<t_n>;
template <nat t_n> using  ucbound =  ucspan<t_n>;
template <nat t_n> using   sbound =   sspan<t_n>;
template <nat t_n> using  usbound =  usspan<t_n>;
template <nat t_n> using   ibound =   ispan<t_n>;
template <nat t_n> using  uibound =  uispan<t_n>;
template <nat t_n> using   lbound =   lspan<t_n>;
template <nat t_n> using  ulbound =  ulspan<t_n>;
template <nat t_n> using  llbound =  llspan<t_n>;
template <nat t_n> using ullbound = ullspan<t_n>;
template <nat t_n> using   nbound =   nspan<t_n>;
template <nat t_n> using  unbound =  unspan<t_n>;

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



namespace   tvecs { using qmu::   vec; using qmu::   vec1; using qmu::   vec2; using qmu::   vec3; using qmu::   vec4; }
namespace   fvecs { using qmu::  fvec; using qmu::  fvec1; using qmu::  fvec2; using qmu::  fvec3; using qmu::  fvec4; }
namespace   dvecs { using qmu::  dvec; using qmu::  dvec1; using qmu::  dvec2; using qmu::  dvec3; using qmu::  dvec4; }
namespace  ldvecs { using qmu:: ldvec; using qmu:: ldvec1; using qmu:: ldvec2; using qmu:: ldvec3; using qmu:: ldvec4; }
namespace   cvecs { using qmu::  cvec; using qmu::  cvec1; using qmu::  cvec2; using qmu::  cvec3; using qmu::  cvec4; }
namespace  ucvecs { using qmu:: ucvec; using qmu:: ucvec1; using qmu:: ucvec2; using qmu:: ucvec3; using qmu:: ucvec4; }
namespace   svecs { using qmu::  svec; using qmu::  svec1; using qmu::  svec2; using qmu::  svec3; using qmu::  svec4; }
namespace  usvecs { using qmu:: usvec; using qmu:: usvec1; using qmu:: usvec2; using qmu:: usvec3; using qmu:: usvec4; }
namespace   ivecs { using qmu::  ivec; using qmu::  ivec1; using qmu::  ivec2; using qmu::  ivec3; using qmu::  ivec4; }
namespace  uivecs { using qmu:: uivec; using qmu:: uivec1; using qmu:: uivec2; using qmu:: uivec3; using qmu:: uivec4; }
namespace   lvecs { using qmu::  lvec; using qmu::  lvec1; using qmu::  lvec2; using qmu::  lvec3; using qmu::  lvec4; }
namespace  ulvecs { using qmu:: ulvec; using qmu:: ulvec1; using qmu:: ulvec2; using qmu:: ulvec3; using qmu:: ulvec4; }
namespace  llvecs { using qmu:: llvec; using qmu:: llvec1; using qmu:: llvec2; using qmu:: llvec3; using qmu:: llvec4; }
namespace ullvecs { using qmu::ullvec; using qmu::ullvec1; using qmu::ullvec2; using qmu::ullvec3; using qmu::ullvec4; }
namespace   nvecs { using qmu::  nvec; using qmu::  nvec1; using qmu::  nvec2; using qmu::  nvec3; using qmu::  nvec4; }
namespace  unvecs { using qmu:: unvec; using qmu:: unvec1; using qmu:: unvec2; using qmu:: unvec3; using qmu:: unvec4; }
namespace   bvecs { using qmu::  bvec; using qmu::  bvec1; using qmu::  bvec2; using qmu::  bvec3; using qmu::  bvec4; }

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



namespace   tspans { using qmu::   span; using qmu::   span1; using qmu::   span2; using qmu::   span3; using qmu::   span4; }
namespace   fspans { using qmu::  fspan; using qmu::  fspan1; using qmu::  fspan2; using qmu::  fspan3; using qmu::  fspan4; }
namespace   dspans { using qmu::  dspan; using qmu::  dspan1; using qmu::  dspan2; using qmu::  dspan3; using qmu::  dspan4; }
namespace  ldspans { using qmu:: ldspan; using qmu:: ldspan1; using qmu:: ldspan2; using qmu:: ldspan3; using qmu:: ldspan4; }
namespace   cspans { using qmu::  cspan; using qmu::  cspan1; using qmu::  cspan2; using qmu::  cspan3; using qmu::  cspan4; }
namespace  ucspans { using qmu:: ucspan; using qmu:: ucspan1; using qmu:: ucspan2; using qmu:: ucspan3; using qmu:: ucspan4; }
namespace   sspans { using qmu::  sspan; using qmu::  sspan1; using qmu::  sspan2; using qmu::  sspan3; using qmu::  sspan4; }
namespace  usspans { using qmu:: usspan; using qmu:: usspan1; using qmu:: usspan2; using qmu:: usspan3; using qmu:: usspan4; }
namespace   ispans { using qmu::  ispan; using qmu::  ispan1; using qmu::  ispan2; using qmu::  ispan3; using qmu::  ispan4; }
namespace  uispans { using qmu:: uispan; using qmu:: uispan1; using qmu:: uispan2; using qmu:: uispan3; using qmu:: uispan4; }
namespace   lspans { using qmu::  lspan; using qmu::  lspan1; using qmu::  lspan2; using qmu::  lspan3; using qmu::  lspan4; }
namespace  ulspans { using qmu:: ulspan; using qmu:: ulspan1; using qmu:: ulspan2; using qmu:: ulspan3; using qmu:: ulspan4; }
namespace  llspans { using qmu:: llspan; using qmu:: llspan1; using qmu:: llspan2; using qmu:: llspan3; using qmu:: llspan4; }
namespace ullspans { using qmu::ullspan; using qmu::ullspan1; using qmu::ullspan2; using qmu::ullspan3; using qmu::ullspan4; }
namespace   nspans { using qmu::  nspan; using qmu::  nspan1; using qmu::  nspan2; using qmu::  nspan3; using qmu::  nspan4; }
namespace  unspans { using qmu:: unspan; using qmu:: unspan1; using qmu:: unspan2; using qmu:: unspan3; using qmu:: unspan4; }

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



namespace   tbounds { using qmu::   bound; using qmu::   bound1; using qmu::   bound2; using qmu::   bound3; using qmu::   bound4; }
namespace   fbounds { using qmu::  fbound; using qmu::  fbound1; using qmu::  fbound2; using qmu::  fbound3; using qmu::  fbound4; }
namespace   dbounds { using qmu::  dbound; using qmu::  dbound1; using qmu::  dbound2; using qmu::  dbound3; using qmu::  dbound4; }
namespace  ldbounds { using qmu:: ldbound; using qmu:: ldbound1; using qmu:: ldbound2; using qmu:: ldbound3; using qmu:: ldbound4; }
namespace   cbounds { using qmu::  cbound; using qmu::  cbound1; using qmu::  cbound2; using qmu::  cbound3; using qmu::  cbound4; }
namespace  ucbounds { using qmu:: ucbound; using qmu:: ucbound1; using qmu:: ucbound2; using qmu:: ucbound3; using qmu:: ucbound4; }
namespace   sbounds { using qmu::  sbound; using qmu::  sbound1; using qmu::  sbound2; using qmu::  sbound3; using qmu::  sbound4; }
namespace  usbounds { using qmu:: usbound; using qmu:: usbound1; using qmu:: usbound2; using qmu:: usbound3; using qmu:: usbound4; }
namespace   ibounds { using qmu::  ibound; using qmu::  ibound1; using qmu::  ibound2; using qmu::  ibound3; using qmu::  ibound4; }
namespace  uibounds { using qmu:: uibound; using qmu:: uibound1; using qmu:: uibound2; using qmu:: uibound3; using qmu:: uibound4; }
namespace   lbounds { using qmu::  lbound; using qmu::  lbound1; using qmu::  lbound2; using qmu::  lbound3; using qmu::  lbound4; }
namespace  ulbounds { using qmu:: ulbound; using qmu:: ulbound1; using qmu:: ulbound2; using qmu:: ulbound3; using qmu:: ulbound4; }
namespace  llbounds { using qmu:: llbound; using qmu:: llbound1; using qmu:: llbound2; using qmu:: llbound3; using qmu:: llbound4; }
namespace ullbounds { using qmu::ullbound; using qmu::ullbound1; using qmu::ullbound2; using qmu::ullbound3; using qmu::ullbound4; }
namespace   nbounds { using qmu::  nbound; using qmu::  nbound1; using qmu::  nbound2; using qmu::  nbound3; using qmu::  nbound4; }
namespace  unbounds { using qmu:: unbound; using qmu:: unbound1; using qmu:: unbound2; using qmu:: unbound3; using qmu:: unbound4; }

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
    static constexpr nat N = 1;

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

    vec1<T> & operator=(const vec1<T> & v);
    vec1<T> & operator=(vec1<T> && v);

    vec1<T> & operator=(const T & v);
    vec1<T> & operator=(const vec2<T> & v);
    vec1<T> & operator=(const vec3<T> & v);
    vec1<T> & operator=(const vec4<T> & v);

    //--------------------------------------------------------------------------
    // Access

    T & operator[](nat i);
    const T & operator[](nat i) const;

    template <nat t_i> T & at();
    template <nat t_i> constexpr T at() const;

    //--------------------------------------------------------------------------
    // Other

    std::string toString() const;

};



//======================================================================================================================
// VEC2 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



template <typename T>
struct vec<T, 2> {

    //--------------------------------------------------------------------------
    // Static Members

    using Type = T;
    static constexpr nat N = 2;    

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

    constexpr vec(const       T & v1, const      T  & v2);
    constexpr vec(const vec1<T> & v1, const      T  & v2);
    constexpr vec(const       T & v1, const vec1<T> & v2);
    constexpr vec(const vec1<T> & v1, const vec1<T> & v2);

    //--------------------------------------------------------------------------
    // Assignment

    vec2<T> & operator=(const vec2<T> & v);
    vec2<T> & operator=(vec2<T> && v);
    
    vec2<T> & operator=(const T & v);
    vec2<T> & operator=(const vec1<T> & v);
    vec2<T> & operator=(const vec3<T> & v);
    vec2<T> & operator=(const vec4<T> & v);

    //--------------------------------------------------------------------------
    // Access

    T & operator[](nat i);
    const T & operator[](nat i) const;

    template <nat t_i> T & at();
    template <nat t_i> constexpr T at() const;

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
    static constexpr nat N = 3;

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

    constexpr vec(const      T  & v1, const      T  & v2, const      T  & v3);
    constexpr vec(const vec1<T> & v1, const      T  & v2, const      T  & v3);
    constexpr vec(const      T  & v1, const vec1<T> & v2, const      T  & v3);
    constexpr vec(const      T  & v1, const      T  & v2, const vec1<T> & v3);
    constexpr vec(const vec1<T> & v1, const vec1<T> & v2, const      T  & v3);
    constexpr vec(const vec1<T> & v1, const      T  & v2, const vec1<T> & v3);
    constexpr vec(const      T  & v1, const vec1<T> & v2, const vec1<T> & v3);
    constexpr vec(const vec1<T> & v1, const vec1<T> & v2, const vec1<T> & v3);
    constexpr vec(const vec2<T> & v1, const      T  & v2);
    constexpr vec(const vec2<T> & v1, const vec1<T> & v2);
    constexpr vec(const      T  & v1, const vec2<T> & v2);
    constexpr vec(const vec1<T> & v1, const vec2<T> & v2);

    //--------------------------------------------------------------------------
    // Assignment

    vec3<T> & operator=(const vec3<T> & v);
    vec3<T> & operator=(vec3<T> && v);

    vec3<T> & operator=(const T & v);
    vec3<T> & operator=(const vec1<T> & v);
    vec3<T> & operator=(const vec2<T> & v);
    vec3<T> & operator=(const vec4<T> & v);

    //--------------------------------------------------------------------------
    // Access

    T & operator[](nat i);
    const T & operator[](nat i) const;

    template <nat t_i> T & at();
    template <nat t_i> constexpr T at() const;

    vec2<T> & xy();
    vec2<T> & yz();
    const vec2<T> & xy() const;
    const vec2<T> & yz() const;
    
    vec2<T> & rg();
    vec2<T> & gb();
    const vec2<T> & rg() const;
    const vec2<T> & gb() const;
    
    vec2<T> & st();
    vec2<T> & tp();
    const vec2<T> & st() const;
    const vec2<T> & tp() const;

    //--------------------------------------------------------------------------
    // Other

    std::string toString() const;

};



//======================================================================================================================
// VEC4 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



template <typename T>
struct vec<T, 4> {

    //--------------------------------------------------------------------------
    // Static Members

    using Type = T;
    static constexpr nat N = 4;

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

    constexpr vec(const      T  & v1, const      T  & v2, const      T  & v3, const      T  & v4);
    constexpr vec(const vec1<T> & v1, const      T  & v2, const      T  & v3, const      T  & v4);
    constexpr vec(const      T  & v1, const vec1<T> & v2, const      T  & v3, const      T  & v4);
    constexpr vec(const      T  & v1, const      T  & v2, const vec1<T> & v3, const      T  & v4);
    constexpr vec(const      T  & v1, const      T  & v2, const      T  & v3, const vec1<T> & v4);
    constexpr vec(const vec1<T> & v1, const vec1<T> & v2, const      T  & v3, const      T  & v4);
    constexpr vec(const vec1<T> & v1, const      T  & v2, const vec1<T> & v3, const      T  & v4);
    constexpr vec(const vec1<T> & v1, const      T  & v2, const      T  & v3, const vec1<T> & v4);
    constexpr vec(const      T  & v1, const vec1<T> & v2, const vec1<T> & v3, const      T  & v4);
    constexpr vec(const      T  & v1, const vec1<T> & v2, const      T  & v3, const vec1<T> & v4);
    constexpr vec(const      T  & v1, const      T  & v2, const vec1<T> & v3, const vec1<T> & v4);
    constexpr vec(const vec1<T> & v1, const vec1<T> & v2, const vec1<T> & v3, const      T  & v4);
    constexpr vec(const vec1<T> & v1, const vec1<T> & v2, const      T  & v3, const vec1<T> & v4);
    constexpr vec(const vec1<T> & v1, const      T  & v2, const vec1<T> & v3, const vec1<T> & v4);
    constexpr vec(const      T  & v1, const vec1<T> & v2, const vec1<T> & v3, const vec1<T> & v4);
    constexpr vec(const vec1<T> & v1, const vec1<T> & v2, const vec1<T> & v3, const vec1<T> & v4);
    constexpr vec(const vec2<T> & v1, const      T  & v2, const      T  & v3);
    constexpr vec(const vec2<T> & v1, const vec1<T> & v2, const      T  & v3);
    constexpr vec(const vec2<T> & v1, const      T  & v2, const vec1<T> & v3);
    constexpr vec(const vec2<T> & v1, const vec1<T> & v2, const vec1<T> & v3);
    constexpr vec(const      T  & v1, const vec2<T> & v2, const      T  & v3);
    constexpr vec(const vec1<T> & v1, const vec2<T> & v2, const      T  & v3);
    constexpr vec(const      T  & v1, const vec2<T> & v2, const vec1<T> & v3);
    constexpr vec(const vec1<T> & v1, const vec2<T> & v2, const vec1<T> & v3);
    constexpr vec(const      T  & v1, const      T  & v2, const vec2<T> & v3);
    constexpr vec(const vec1<T> & v1, const      T  & v2, const vec2<T> & v3);
    constexpr vec(const      T  & v1, const vec1<T> & v2, const vec2<T> & v3);
    constexpr vec(const vec1<T> & v1, const vec1<T> & v2, const vec2<T> & v3);
    constexpr vec(const vec2<T> & v1, const vec2<T> & v2);
    constexpr vec(const vec3<T> & v1, const      T  & v2);
    constexpr vec(const vec3<T> & v1, const vec1<T> & v2);
    constexpr vec(const      T  & v1, const vec3<T> & v2);
    constexpr vec(const vec1<T> & v1, const vec3<T> & v2);

    //--------------------------------------------------------------------------
    // Assignment

    vec4<T> & operator=(const vec4<T> & v);
    vec4<T> & operator=(vec4<T> && v);

    vec4<T> & operator=(const T & v);
    vec4<T> & operator=(const vec1<T> & v);
    vec4<T> & operator=(const vec2<T> & v);
    vec4<T> & operator=(const vec3<T> & v);

    //--------------------------------------------------------------------------
    // Access
    
    T & operator[](nat i);
    const T & operator[](nat i) const;

    template <nat t_i> T & at();
    template <nat t_i> constexpr T at() const;

    vec2<T> & xy();
    vec2<T> & yz();
    vec2<T> & zw();
    vec3<T> & xyz();
    vec3<T> & yzw();
    const vec2<T> & xy() const;
    const vec2<T> & yz() const;
    const vec2<T> & zw() const;
    const vec3<T> & xyz() const;
    const vec3<T> & yzw() const;

    vec2<T> & rg();
    vec2<T> & gb();
    vec2<T> & ba();
    vec3<T> & rgb();
    vec3<T> & gba();
    const vec2<T> & rg() const;
    const vec2<T> & gb() const;
    const vec2<T> & ba() const;
    const vec3<T> & rgb() const;
    const vec3<T> & gba() const;

    vec2<T> & st();
    vec2<T> & tp();
    vec2<T> & pq();
    vec3<T> & stp();
    vec3<T> & tpq();
    const vec2<T> & st() const;
    const vec2<T> & tp() const;
    const vec2<T> & pq() const;
    const vec3<T> & stp() const;
    const vec3<T> & tpq() const;

    //--------------------------------------------------------------------------
    // Other

    std::string toString() const;

};



//======================================================================================================================
// SPAN ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



template <typename T, nat t_n>
struct span {

    //--------------------------------------------------------------------------
    // Static Members

    using Type = T;
    static constexpr nat N = t_n;

    //--------------------------------------------------------------------------
    // Instance Variables

    union { vec<T, t_n> min,  loc; };
    union { vec<T, t_n> max, size; };

    //--------------------------------------------------------------------------
    // Construction

    constexpr span();
    constexpr span(const span<T, t_n> & s);
    constexpr span(span<T, t_n> && s);

    template <typename U, nat u_n> constexpr explicit span(const span<U, u_n> & s);

    constexpr span(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
    constexpr span(const T & v1, const T & v2);

    //--------------------------------------------------------------------------
    // Assignment

    span<T, t_n> & operator=(const span<T, t_n> & s);
    span<T, t_n> & operator=(span<T, t_n> && s);

    template <nat u_n> span<T, t_n> & operator=(const span<T, u_n> & s);

    //--------------------------------------------------------------------------
    // Other

    std::string toString() const;

};



//======================================================================================================================
// Constants ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------------------------



template <typename T, nat t_n, nat t_d> constexpr vec<T, t_n> axis = vec<T, t_n>();
template <typename T> constexpr vec<T, 1> axis<T, 1, 0> = vec1<T>(static_cast<T>(1));
template <typename T> constexpr vec<T, 2> axis<T, 2, 0> = vec2<T>(static_cast<T>(1), static_cast<T>(0));
template <typename T> constexpr vec<T, 2> axis<T, 2, 1> = vec2<T>(static_cast<T>(0), static_cast<T>(1));
template <typename T> constexpr vec<T, 3> axis<T, 3, 0> = vec3<T>(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));
template <typename T> constexpr vec<T, 3> axis<T, 3, 1> = vec3<T>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));
template <typename T> constexpr vec<T, 3> axis<T, 3, 2> = vec3<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
template <typename T> constexpr vec<T, 4> axis<T, 4, 0> = vec4<T>(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
template <typename T> constexpr vec<T, 4> axis<T, 4, 1> = vec4<T>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));
template <typename T> constexpr vec<T, 4> axis<T, 4, 2> = vec4<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));
template <typename T> constexpr vec<T, 4> axis<T, 4, 2> = vec4<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));

template <typename T, nat t_n> constexpr vec<T, t_n> axisX = axis<T, t_n, 0>;
template <typename T, nat t_n> constexpr vec<T, t_n> axisY = axis<T, t_n, 1>;
template <typename T, nat t_n> constexpr vec<T, t_n> axisZ = axis<T, t_n, 2>;
template <typename T, nat t_n> constexpr vec<T, t_n> axisW = axis<T, t_n, 3>;

template <typename T> constexpr vec1<T> axis1X = axisX<T, 1>;
template <typename T> constexpr vec2<T> axis2X = axisX<T, 2>;
template <typename T> constexpr vec2<T> axis2Y = axisY<T, 2>;
template <typename T> constexpr vec3<T> axis3X = axisX<T, 3>;
template <typename T> constexpr vec3<T> axis3Y = axisY<T, 3>;
template <typename T> constexpr vec3<T> axis3Z = axisZ<T, 3>;
template <typename T> constexpr vec4<T> axis4X = axisX<T, 4>;
template <typename T> constexpr vec4<T> axis4Y = axisY<T, 4>;
template <typename T> constexpr vec4<T> axis4Z = axisZ<T, 4>;
template <typename T> constexpr vec4<T> axis4W = axisW<T, 4>;

template <typename T, nat t_n> constexpr   vec<T, t_n>   nanvec =   vec<T, t_n>(nan<T>);
template <typename T, nat t_n> constexpr  span<T, t_n>  nanspan =  span<T, t_n>(nan<T>, nan<T>);
template <typename T, nat t_n> constexpr bound<T, t_n> nanbound = bound<T, t_n>(nan<T>, nan<T>);

template <typename T, nat t_n> constexpr  vec<T, t_n>  infvec =  vec<T, t_n>(infinity<T>);
template <typename T, nat t_n> constexpr span<T, t_n> infspan = span<T, t_n>(-infinity<T>, infinity<T>);

template <typename T, nat t_n> constexpr span<T, t_n> nullspan = span<T, t_n>(infinity<T>, -infinity<T>);



//======================================================================================================================
// Functions ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



//==============================================================================
// Arithmetic Assignment
//------------------------------------------------------------------------------

template <typename T, nat t_n> vec<T, t_n> & operator++(vec<T, t_n> & v);
template <typename T, nat t_n> vec<T, t_n>   operator++(vec<T, t_n> & v, int);

template <typename T, nat t_n> vec<T, t_n> & operator--(vec<T, t_n> & v);
template <typename T, nat t_n> vec<T, t_n>   operator--(vec<T, t_n> & v, int);

template <typename T, nat t_n> vec<T, t_n> & operator+=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, nat t_n> vec<T, t_n> & operator+=(vec<T, t_n> & v1, const           T & v2);

template <typename T, nat t_n> vec<T, t_n> & operator-=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, nat t_n> vec<T, t_n> & operator-=(vec<T, t_n> & v1, const           T & v2);

template <typename T, nat t_n> vec<T, t_n> & operator*=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, nat t_n> vec<T, t_n> & operator*=(vec<T, t_n> & v1, const           T & v2);

template <typename T, nat t_n> vec<T, t_n> & operator/=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, nat t_n> vec<T, t_n> & operator/=(vec<T, t_n> & v1, const           T & v2);

template <typename T, nat t_n> vec<T, t_n> & operator%=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, nat t_n> vec<T, t_n> & operator%=(vec<T, t_n> & v1, const           T & v2);



//==============================================================================
// Arithmetic
//------------------------------------------------------------------------------

template <typename T, nat t_n> vec<T, t_n> constexpr operator+(const vec<T, t_n> & v);

template <typename T, nat t_n> vec<T, t_n> constexpr operator-(const vec<T, t_n> & v);

template <typename T, nat t_n> vec<T, t_n> constexpr operator+(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, nat t_n> vec<T, t_n> constexpr operator+(const vec<T, t_n> & v1, const           T & v2);
template <typename T, nat t_n> vec<T, t_n> constexpr operator+(const           T & v1, const vec<T, t_n> & v2);

template <typename T, nat t_n> vec<T, t_n> constexpr operator-(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, nat t_n> vec<T, t_n> constexpr operator-(const vec<T, t_n> & v1, const           T & v2);
template <typename T, nat t_n> vec<T, t_n> constexpr operator-(const           T & v1, const vec<T, t_n> & v2);

template <typename T, nat t_n> vec<T, t_n> constexpr operator*(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, nat t_n> vec<T, t_n> constexpr operator*(const vec<T, t_n> & v1, const           T & v2);
template <typename T, nat t_n> vec<T, t_n> constexpr operator*(const           T & v1, const vec<T, t_n> & v2);

template <typename T, nat t_n> vec<T, t_n> constexpr operator/(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, nat t_n> vec<T, t_n> constexpr operator/(const vec<T, t_n> & v1, const           T & v2);
template <typename T, nat t_n> vec<T, t_n> constexpr operator/(const           T & v1, const vec<T, t_n> & v2);

template <typename T, nat t_n> vec<T, t_n> constexpr operator%(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, nat t_n> vec<T, t_n> constexpr operator%(const vec<T, t_n> & v1, const           T & v2);
template <typename T, nat t_n> vec<T, t_n> constexpr operator%(const           T & v1, const vec<T, t_n> & v2);



//==============================================================================
// Comparison
//------------------------------------------------------------------------------

template <typename T, nat t_n> constexpr bool operator==(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, nat t_n> constexpr bvec<t_n> operator==(const vec<T, t_n> & v1, const           T & v2);
template <typename T, nat t_n> constexpr bvec<t_n> operator==(const           T & v1, const vec<T, t_n> & v2);

template <typename T, nat t_n> constexpr bool operator!=(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, nat t_n> constexpr bvec<t_n> operator!=(const vec<T, t_n> & v1, const           T & v2);
template <typename T, nat t_n> constexpr bvec<t_n> operator!=(const           T & v1, const vec<T, t_n> & v2);

template <typename T, nat t_n> constexpr bvec<t_n> operator<(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, nat t_n> constexpr bvec<t_n> operator<(const vec<T, t_n> & v1, const           T & v2);
template <typename T, nat t_n> constexpr bvec<t_n> operator<(const           T & v1, const vec<T, t_n> & v2);

template <typename T, nat t_n> constexpr bvec<t_n> operator>(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, nat t_n> constexpr bvec<t_n> operator>(const vec<T, t_n> & v1, const           T & v2);
template <typename T, nat t_n> constexpr bvec<t_n> operator>(const           T & v1, const vec<T, t_n> & v2);

template <typename T, nat t_n> constexpr bvec<t_n> operator<=(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, nat t_n> constexpr bvec<t_n> operator<=(const vec<T, t_n> & v1, const           T & v2);
template <typename T, nat t_n> constexpr bvec<t_n> operator<=(const           T & v1, const vec<T, t_n> & v2);

template <typename T, nat t_n> constexpr bvec<t_n> operator>=(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, nat t_n> constexpr bvec<t_n> operator>=(const vec<T, t_n> & v1, const           T & v2);
template <typename T, nat t_n> constexpr bvec<t_n> operator>=(const           T & v1, const vec<T, t_n> & v2);

template <typename T, nat t_n> constexpr bool operator==(const span<T, t_n> & s1, const span<T, t_n> & s2);

template <typename T, nat t_n> constexpr bool operator!=(const span<T, t_n> & s1, const span<T, t_n> & s2);



//==============================================================================
// Stream Output
//------------------------------------------------------------------------------

template <typename T, nat t_n> std::ostream & operator<<(std::ostream & os, const vec<T, t_n> & v);

template <typename T, nat t_n> std::ostream & operator<<(std::ostream & os, const span<T, t_n> & s);



//==============================================================================
// pow
//------------------------------------------------------------------------------

template <typename T, nat t_n, eif_floating_t<T> = 0>
vec<T, t_n> pow(const vec<T, t_n> & v, T p);

template <typename T, nat t_n, eif_floating_t<T> = 0>
vec<T, t_n> pow(const vec<T, t_n> & v, const vec<T, t_n> & p);



//==============================================================================
// exp
//------------------------------------------------------------------------------

template <typename T, nat t_n, eif_t<std::is_floating_point_v<T>> = 0>
vec<T, t_n> exp(const vec<T, t_n> & v);



//==============================================================================
// magnitude
//------------------------------------------------------------------------------

template <typename T, nat t_n, eif_floating_t<T> = 0>
T magnitude(const vec<T, t_n> & v);

template <typename T, nat t_n>
T magnitude2(const vec<T, t_n> & v);



//==============================================================================
// norm
//------------------------------------------------------------------------------

template <typename T, nat t_n, eif_floating_t<T> = 0>
vec<T, t_n> norm(const vec<T, t_n> & v);



//==============================================================================
// dot
//------------------------------------------------------------------------------

template <typename T, nat t_n>
T dot(const vec<T, t_n> & v1, const vec<T, t_n> & v2);



//==============================================================================
// cross
//------------------------------------------------------------------------------

template <typename T, nat t_n>
vec<T, t_n> cross(const vec<T, t_n> & v1, const vec<T, t_n> & v2);



//==============================================================================
// parallel
//------------------------------------------------------------------------------

template <typename T, nat t_n>
bool parallel(const vec<T, t_n> & v1, const vec<T, t_n> & v2);



//==============================================================================
// orthogonal
//------------------------------------------------------------------------------

template <typename T, nat t_n>
bool orthogonal(const vec<T, t_n> & v1, const vec<T, t_n> & v2);



//==============================================================================
// ortho
//------------------------------------------------------------------------------

template <typename T, nat t_n>
vec<T, t_n> ortho(const vec<T, t_n> & v);



//==============================================================================
// orthogonalize
//------------------------------------------------------------------------------

template <typename T, nat t_n, eif_floating_t<T> = 0>
void orthogonalize(const vec<T, t_n> & v1, vec<T, t_n> & v2);

template <typename T, eif_floating_t<T> = 0>
void orthogonalize(const vec3<T> & v1, vec3<T> & v2, vec3<T> & v3);
template <typename T, eif_floating_t<T> = 0>
void orthogonalize_n(const vec3<T> & v1, vec3<T> & v2, vec3<T> & v3);



//==============================================================================
// reflect
//------------------------------------------------------------------------------

template <typename T, nat t_n, eif_floating_t<T> = 0>
vec<T, t_n> reflect(const vec<T, t_n> & v, const vec<T, t_n> & n);
template <typename T, nat t_n, eif_floating_t<T> = 0>
vec<T, t_n> reflect_n(const vec<T, t_n> & v, const vec<T, t_n> & n);



//==============================================================================
// angle
//------------------------------------------------------------------------------

template <typename T, nat t_n, eif_floating_t<T> = 0>
T angle(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, nat t_n, eif_floating_t<T> = 0>
T angle_n(const vec<T, t_n> & v1, const vec<T, t_n> & v2);



//==============================================================================
// min
//------------------------------------------------------------------------------

template <typename T, nat t_n>
constexpr const T & min(const vec<T, t_n> & v);

template <typename T, nat t_n>
constexpr vec<T, t_n> min(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

template <typename T, nat t_n, typename... Ts>
constexpr vec<T, t_n> min(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<Ts, t_n> &... rest);



//==============================================================================
// max
//------------------------------------------------------------------------------

template <typename T, nat t_n>
constexpr const T & max(const vec<T, t_n> & v);

template <typename T, nat t_n>
constexpr vec<T, t_n> max(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

template <typename T, nat t_n, typename... Ts>
constexpr vec<T, t_n> max(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<Ts, t_n> &... rest);



//==============================================================================
// minmax
//------------------------------------------------------------------------------

template <typename T, nat t_n>
constexpr std::pair<const T &, const T &> minmax(const vec<T, t_n> & v);



//==============================================================================
// sort
//------------------------------------------------------------------------------

template <typename T, nat t_n>
void sort(const vec<T, t_n> & v);



//==============================================================================
// clamp
//------------------------------------------------------------------------------

template <typename T, nat t_n>
constexpr vec<T, t_n> clamp(const vec<T, t_n> & v, const T & min, const T & max);

template <typename T, nat t_n>
constexpr vec<T, t_n> clamp(const vec<T, t_n> & v, const vec<T, t_n> & min, const vec<T, t_n> & max);



//==============================================================================
// abs
//------------------------------------------------------------------------------

template <typename T, nat t_n>
constexpr vec<T, t_n> abs(const vec<T, t_n> & v);



//==============================================================================
// floor
//------------------------------------------------------------------------------

template <typename T, nat t_n>
constexpr nvec<t_n> floor(const vec<T, t_n> & v);



//==============================================================================
// ceil
//------------------------------------------------------------------------------

template <typename T, nat t_n>
constexpr nvec<t_n> ceil(const vec<T, t_n> & v);



//==============================================================================
// mix
//------------------------------------------------------------------------------

template <typename T, nat t_n, eif_floating_t<T> = 0>
constexpr vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, T t);

template <typename T, nat t_n, eif_floating_t<T> = 0>
constexpr vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec2<T> & weights);

template <typename T, nat t_n, eif_floating_t<T> = 0>
constexpr vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & v3, const vec3<T> & weights);

template <typename T, nat t_n, eif_floating_t<T> = 0>
constexpr vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & v3, const vec<T, t_n> & v4, const vec4<T> & weights);



//==============================================================================
// toSpan
//------------------------------------------------------------------------------

template <typename T, nat t_n>
constexpr span<T, t_n> toSpan(const bound<T, t_n> & b);



//==============================================================================
// toBound
//------------------------------------------------------------------------------

template <typename T, nat t_n>
constexpr bound<T, t_n> toBound(const span<T, t_n> & s);



//==============================================================================
// intersect
//------------------------------------------------------------------------------

template <typename T, nat t_n>
span<T, t_n> intersect(const span<T, t_n> & s1, const span<T, t_n> & s2);



//==============================================================================
// Logical Operators
//------------------------------------------------------------------------------

template <nat t_n> constexpr bvec<t_n> operator&&(const bvec<t_n> & v1, const bvec<t_n> & v2);
template <nat t_n> constexpr bool vand(const bvec<t_n> & v);

template <nat t_n> constexpr bvec<t_n> operator||(const bvec<t_n> & v1, const bvec<t_n> & v2);
template <nat t_n> constexpr bool vor(const bvec<t_n> & v);

template <nat t_n> constexpr bvec<t_n> operator!(const bvec<t_n> & v1);



}



//==============================================================================================================================================================
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================================================



namespace qmu {



//======================================================================================================================
// VEC1 IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr vec<T, 1>::vec() :
    x(static_cast<T>(0))
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
    x(static_cast<T>(v.x))
{}

template <typename T>
template <typename U>
constexpr vec<T, 1>::vec(const vec2<U> & v) :
    x(static_cast<T>(v.x))
{}

template <typename T>
template <typename U>
constexpr vec<T, 1>::vec(const vec3<U> & v) :
    x(static_cast<T>(v.x))
{}

template <typename T>
template <typename U>
constexpr vec<T, 1>::vec(const vec4<U> & v) :
    x(static_cast<T>(v.x))
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
inline vec1<T> & vec<T, 1>::operator=(const vec2<T> & v) {
    x = v.x;
    return *this;
}

template <typename T>
inline vec1<T> & vec<T, 1>::operator=(const vec3<T> & v) {
    x = v.x;
    return *this;
}

template <typename T>
inline vec1<T> & vec<T, 1>::operator=(const vec4<T> & v) {
    x = v.x;
    return *this;
}



//------------------------------------------------------------------------------
// Access



template <typename T>
inline T & vec<T, 1>::operator[](nat i) {
    return *(&x + i);
}

template <typename T>
inline const T & vec<T, 1>::operator[](nat i) const {
    return *(&x + i);
}



template <typename T>
template <nat t_i>
inline T & vec<T, 1>::at() {
    static_assert(t_i == 0, "index out of bounds");
    if constexpr (t_i == 0) return x;
}

template <typename T>
template <nat t_i>
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
    x(static_cast<T>(0)), y(static_cast<T>(0))
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
    x(static_cast<T>(v.x)), y(static_cast<T>(0))
{}

template <typename T>
template <typename U>
constexpr vec<T, 2>::vec(const vec2<U> & v) :
    x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
{}

template <typename T>
template <typename U>
constexpr vec<T, 2>::vec(const vec3<U> & v) :
    x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
{}

template <typename T>
template <typename U>
constexpr vec<T, 2>::vec(const vec4<U> & v) :
    x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
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
constexpr vec<T, 2>::vec(const vec1<T> & v1, const T & v2) :
    x(v1.x), y(v2)
{}

template <typename T>
constexpr vec<T, 2>::vec(const T & v1, const vec1<T> & v2) :
    x(v1), y(v2.x)
{}

template <typename T>
constexpr vec<T, 2>::vec(const vec1<T> & v1, const vec1<T> & v2) :
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
inline vec2<T> & vec<T, 2>::operator=(const vec1<T> & v) {
    x = v.x; y = static_cast<T>(0);
    return *this;
}

template <typename T>
inline vec2<T> & vec<T, 2>::operator=(const vec3<T> & v) {
    x = v.x; y = v.y;
    return *this;
}

template <typename T>
inline vec2<T> & vec<T, 2>::operator=(const vec4<T> & v) {
    x = v.x; y = v.y;
    return *this;
}



//------------------------------------------------------------------------------
// Access



template <typename T>
inline T & vec<T, 2>::operator[](nat i) {
    return *(&x + i);
}

template <typename T>
inline const T & vec<T, 2>::operator[](nat i) const {
    return *(&x + i);
}



template <typename T>
template <nat t_i>
inline T & vec<T, 2>::at() {
    static_assert(t_i >= 0 && t_i <= 1, "index out of bounds");
    if constexpr (t_i == 0) return x;
    if constexpr (t_i == 1) return y;
}

template <typename T>
template <nat t_i>
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
    x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0))
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
    x(static_cast<T>(v.x)), y(static_cast<T>(0)), z(static_cast<T>(0))
{}

template <typename T>
template <typename U>
constexpr vec<T, 3>::vec(const vec2<U> & v) :
    x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(0))
{}

template <typename T>
template <typename U>
constexpr vec<T, 3>::vec(const vec3<U> & v) :
    x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z))
{}

template <typename T>
template <typename U>
constexpr vec<T, 3>::vec(const vec4<U> & v) :
    x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z))
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
constexpr vec<T, 3>::vec(const vec1<T> & v1, const T & v2, const T & v3) :
    x(v1.x), y(v2), z(v3)
{}

template <typename T>
constexpr vec<T, 3>::vec(const T & v1, const vec1<T> & v2, const T & v3) :
    x(v1), y(v2.x), z(v3)
{}

template <typename T>
constexpr vec<T, 3>::vec(const T & v1, const T & v2, const vec1<T> & v3) :
    x(v1), y(v2), z(v3.x)
{}

template <typename T>
constexpr vec<T, 3>::vec(const vec1<T> & v1, const vec1<T> & v2, const T & v3) :
    x(v1.x), y(v2.x), z(v3)
{}

template <typename T>
constexpr vec<T, 3>::vec(const vec1<T> & v1, const T & v2, const vec1<T> & v3) :
    x(v1.x), y(v2), z(v3.x)
{}

template <typename T>
constexpr vec<T, 3>::vec(const T & v1, const vec1<T> & v2, const vec1<T> & v3) :
    x(v1), y(v2.x), z(v3.x)
{}

template <typename T>
constexpr vec<T, 3>::vec(const vec1<T> & v1, const vec1<T> & v2, const vec1<T> & v3) :
    x(v1.x), y(v2.x), z(v3.x)
{}

template <typename T>
constexpr vec<T, 3>::vec(const vec2<T> & v1, const T & v2) :
    x(v1.x), y(v1.y), z(v2)
{}

template <typename T>
constexpr vec<T, 3>::vec(const vec2<T> & v1, const vec1<T> & v2) :
    x(v1.x), y(v1.y), z(v2.x)
{}

template <typename T>
constexpr vec<T, 3>::vec(const T & v1, const vec2<T> & v2) :
    x(v1), y(v2.x), z(v2.y)
{}

template <typename T>
constexpr vec<T, 3>::vec(const vec1<T> & v1, const vec2<T> & v2) :
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
inline vec3<T> & vec<T, 3>::operator=(const vec1<T> & v) {
    x = v.x; y = static_cast<T>(0); z = static_cast<T>(0);
    return *this;
}

template <typename T>
inline vec3<T> & vec<T, 3>::operator=(const vec2<T> & v) {
    x = v.x; y = v.y; z = static_cast<T>(0);
    return *this;
}

template <typename T>
inline vec3<T> & vec<T, 3>::operator=(const vec4<T> & v) {
    x = v.x; y = v.y; z = v.z;
    return *this;
}



//------------------------------------------------------------------------------
// Access



template <typename T>
inline T & vec<T, 3>::operator[](nat i) {
    return *(&x + i);
}

template <typename T>
inline const T & vec<T, 3>::operator[](nat i) const {
    return *(&x + i);
}

template <typename T>
template <nat t_i>
inline T & vec<T, 3>::at() {
    static_assert(t_i >= 0 && t_i <= 2, "index out of bounds");
    if constexpr (t_i == 0) return x;
    if constexpr (t_i == 1) return y;
    if constexpr (t_i == 2) return z;
}

template <typename T>
template <nat t_i>
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
inline vec2<T> & vec<T, 3>::yz() {
    return *reinterpret_cast<vec2<T> *>(&y);
}

template <typename T>
inline const vec2<T> & vec<T, 3>::xy() const {
    return *reinterpret_cast<vec2<T> *>(&x);
}

template <typename T>
inline const vec2<T> & vec<T, 3>::yz() const {
    return *reinterpret_cast<vec2<T> *>(&y);
}

template <typename T>
inline vec2<T> & vec<T, 3>::rg() {
    return *reinterpret_cast<vec2<T> *>(&r);
}

template <typename T>
inline vec2<T> & vec<T, 3>::gb() {
    return *reinterpret_cast<vec2<T> *>(&g);
}

template <typename T>
inline const vec2<T> & vec<T, 3>::rg() const {
    return *reinterpret_cast<vec2<T> *>(&r);
}

template <typename T>
inline const vec2<T> & vec<T, 3>::gb() const {
    return *reinterpret_cast<vec2<T> *>(&g);
}

template <typename T>
inline vec2<T> & vec<T, 3>::st() {
    return *reinterpret_cast<vec2<T> *>(&s);
}

template <typename T>
inline vec2<T> & vec<T, 3>::tp() {
    return *reinterpret_cast<vec2<T> *>(&t);
}

template <typename T>
inline const vec2<T> & vec<T, 3>::st() const {
    return *reinterpret_cast<vec2<T> *>(&s);
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
    x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)), w(static_cast<T>(0))
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
    x(static_cast<T>(v.x)), y(static_cast<T>(0)), z(static_cast<T>(0)), w(static_cast<T>(0))
{}

template <typename T>
template <typename U>
constexpr vec<T, 4>::vec(const vec2<U> & v) :
    x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(0)), w(static_cast<T>(0))
{}

template <typename T>
template <typename U>
constexpr vec<T, 4>::vec(const vec3<U> & v) :
    x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z)), w(static_cast<T>(0))
{}

template <typename T>
template <typename U>
constexpr vec<T, 4>::vec(const vec4<U> & v) :
    x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z)), w(static_cast<T>(v.w))
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
constexpr vec<T, 4>::vec(const vec1<T> & v1, const T & v2, const T & v3, const T & v4) :
    x(v1.x), y(v2), z(v3), w(v4)
{}

template <typename T>
constexpr vec<T, 4>::vec(const T & v1, const vec1<T> & v2, const T & v3, const T & v4) :
    x(v1), y(v2.x), z(v3), w(v4)
{}

template <typename T>
constexpr vec<T, 4>::vec(const T & v1, const T & v2, const vec1<T> & v3, const T & v4) :
    x(v1), y(v2), z(v3.x), w(v4)
{}

template <typename T>
constexpr vec<T, 4>::vec(const T & v1, const T & v2, const T & v3, const vec1<T> & v4) :
    x(v1), y(v2), z(v3), w(v4.x)
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec1<T> & v1, const vec1<T> & v2, const T & v3, const T & v4) :
    x(v1.x), y(v2.x), z(v3), w(v4)
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec1<T> & v1, const T & v2, const vec1<T> & v3, const T & v4) :
    x(v1.x), y(v2), z(v3.x), w(v4)
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec1<T> & v1, const T & v2, const T & v3, const vec1<T> & v4) :
    x(v1.x), y(v2), z(v3), w(v4.x)
{}

template <typename T>
constexpr vec<T, 4>::vec(const T & v1, const vec1<T> & v2, const vec1<T> & v3, const T & v4) :
    x(v1), y(v2.x), z(v3.x), w(v4)
{}

template <typename T>
constexpr vec<T, 4>::vec(const T & v1, const vec1<T> & v2, const T & v3, const vec1<T> & v4) :
    x(v1), y(v2.x), z(v3), w(v4.x)
{}

template <typename T>
constexpr vec<T, 4>::vec(const T & v1, const T & v2, const vec1<T> & v3, const vec1<T> & v4) :
    x(v1), y(v2), z(v3.x), w(v4.x)
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec1<T> & v1, const vec1<T> & v2, const vec1<T> & v3, const T & v4) :
    x(v1.x), y(v2.x), z(v3.x), w(v4)
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec1<T> & v1, const vec1<T> & v2, const T & v3, const vec1<T> & v4) :
    x(v1.x), y(v2.x), z(v3), w(v4.x)
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec1<T> & v1, const T & v2, const vec1<T> & v3, const vec1<T> & v4) :
    x(v1.x), y(v2), z(v3.x), w(v4.x)
{}

template <typename T>
constexpr vec<T, 4>::vec(const T & v1, const vec1<T> & v2, const vec1<T> & v3, const vec1<T> & v4) :
    x(v1), y(v2.x), z(v3.x), w(v4.x)
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec1<T> & v1, const vec1<T> & v2, const vec1<T> & v3, const vec1<T> & v4) :
    x(v1.x), y(v2.x), z(v3.x), w(v4.x)
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec2<T> & v1, const T & v2, const T & v3) :
    x(v1.x), y(v1.y), z(v2), w(v3)
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec2<T> & v1, const vec1<T> & v2, const T & v3) :
    x(v1.x), y(v1.y), z(v2.x), w(v3)
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec2<T> & v1, const T & v2, const vec1<T> & v3) :
    x(v1.x), y(v1.y), z(v2), w(v3.x)
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec2<T> & v1, const vec1<T> & v2, const vec1<T> & v3) :
    x(v1.x), y(v1.y), z(v2.x), w(v3.x)
{}

template <typename T>
constexpr vec<T, 4>::vec(const T & v1, const vec2<T> & v2, const T & v3) :
    x(v1), y(v2.x), z(v2.y), w(v3)
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec1<T> & v1, const vec2<T> & v2, const T & v3) :
    x(v1.x), y(v2.x), z(v2.y), w(v3)
{}

template <typename T>
constexpr vec<T, 4>::vec(const T & v1, const vec2<T> & v2, const vec1<T> & v3) :
    x(v1), y(v2.x), z(v2.y), w(v3.x)
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec1<T> & v1, const vec2<T> & v2, const vec1<T> & v3) :
    x(v1.x), y(v2.x), z(v2.y), w(v3.x)
{}

template <typename T>
constexpr vec<T, 4>::vec(const T & v1, const T & v2, const vec2<T> & v3) :
    x(v1), y(v2), z(v3.x), w(v3.y)
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec1<T> & v1, const T & v2, const vec2<T> & v3) :
    x(v1.x), y(v2), z(v3.x), w(v3.y)
{}

template <typename T>
constexpr vec<T, 4>::vec(const T & v1, const vec1<T> & v2, const vec2<T> & v3) :
    x(v1), y(v2.x), z(v3.x), w(v3.y)
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec1<T> & v1, const vec1<T> & v2, const vec2<T> & v3) :
    x(v1.x), y(v2.x), z(v3.x), w(v3.y)
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec2<T> & v1, const vec2<T> & v2) :
    x(v1.x), y(v1.y), z(v2.x), w(v2.y)
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec3<T> & v1, const T & v2) :
    x(v1.x), y(v1.y), z(v1.z), w(v2)
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec3<T> & v1, const vec1<T> & v2) :
    x(v1.x), y(v1.y), z(v1.z), w(v2.x)
{}

template <typename T>
constexpr vec<T, 4>::vec(const T & v1, const vec3<T> & v2) :
    x(v1), y(v2.x), z(v2.y), w(v2.z)
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec1<T> & v1, const vec3<T> & v2) :
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
inline vec4<T> & vec<T, 4>::operator=(const vec1<T> & v) {
    x = v.x; y = static_cast<T>(0); z = static_cast<T>(0); w = static_cast<T>(0);
    return *this;
}

template <typename T>
inline vec4<T> & vec<T, 4>::operator=(const vec2<T> & v) {
    x = v.x; y = v.y; z = static_cast<T>(0); w = static_cast<T>(0);
    return *this;
}

template <typename T>
inline vec4<T> & vec<T, 4>::operator=(const vec3<T> & v) {
    x = v.x; y = v.y; z = v.z; w = static_cast<T>(0);
    return *this;
}



//------------------------------------------------------------------------------
// Access



template <typename T>
inline T & vec<T, 4>::operator[](nat i) {
    return *(&x + i);
}

template <typename T>
inline const T & vec<T, 4>::operator[](nat i) const {
    return *(&x + i);
}

template <typename T>
template <nat t_i>
inline T & vec<T, 4>::at() {
    static_assert(t_i >= 0 && t_i <= 3, "index out of bounds");
    if constexpr (t_i == 0) return x;
    if constexpr (t_i == 1) return y;
    if constexpr (t_i == 2) return z;
    if constexpr (t_i == 3) return w;
}

template <typename T>
template <nat t_i>
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
inline vec2<T> & vec<T, 4>::yz() {
    return *reinterpret_cast<vec2<T> *>(&y);
}

template <typename T>
inline vec2<T> & vec<T, 4>::zw() {
    return *reinterpret_cast<vec2<T> *>(&z);
}

template <typename T>
inline vec3<T> & vec<T, 4>::xyz() {
    return *reinterpret_cast<vec3<T> *>(&x);
}

template <typename T>
inline vec3<T> & vec<T, 4>::yzw() {
    return *reinterpret_cast<vec3<T> *>(&y);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::xy() const {
    return *reinterpret_cast<vec2<T> *>(&x);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::yz() const {
    return *reinterpret_cast<vec2<T> *>(&y);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::zw() const {
    return *reinterpret_cast<vec2<T> *>(&z);
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
inline vec2<T> & vec<T, 4>::rg() {
    return *reinterpret_cast<vec2<T> *>(&r);
}

template <typename T>
inline vec2<T> & vec<T, 4>::gb() {
    return *reinterpret_cast<vec2<T> *>(&g);
}

template <typename T>
inline vec2<T> & vec<T, 4>::ba() {
    return *reinterpret_cast<vec2<T> *>(&b);
}

template <typename T>
inline vec3<T> & vec<T, 4>::rgb() {
    return *reinterpret_cast<vec3<T> *>(&r);
}

template <typename T>
inline vec3<T> & vec<T, 4>::gba() {
    return *reinterpret_cast<vec3<T> *>(&g);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::rg() const {
    return *reinterpret_cast<vec2<T> *>(&r);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::gb() const {
    return *reinterpret_cast<vec2<T> *>(&g);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::ba() const {
    return *reinterpret_cast<vec2<T> *>(&b);
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
inline vec2<T> & vec<T, 4>::st() {
    return *reinterpret_cast<vec2<T> *>(&s);
}

template <typename T>
inline vec2<T> & vec<T, 4>::tp() {
    return *reinterpret_cast<vec2<T> *>(&t);
}

template <typename T>
inline vec2<T> & vec<T, 4>::pq() {
    return *reinterpret_cast<vec2<T> *>(&p);
}

template <typename T>
inline vec3<T> & vec<T, 4>::stp() {
    return *reinterpret_cast<vec3<T> *>(&s);
}

template <typename T>
inline vec3<T> & vec<T, 4>::tpq() {
    return *reinterpret_cast<vec3<T> *>(&t);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::st() const {
    return *reinterpret_cast<vec2<T> *>(&s);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::tp() const {
    return *reinterpret_cast<vec2<T> *>(&t);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::pq() const {
    return *reinterpret_cast<vec2<T> *>(&p);
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



template <typename T, nat t_n>
constexpr span<T, t_n>::span() :
    min(),
    max()
{}

template <typename T, nat t_n>
constexpr span<T, t_n>::span(const span<T, t_n> & s) :
    min(s.min),
    max(s.max)
{}

template <typename T, nat t_n>
constexpr span<T, t_n>::span(span<T, t_n> && s) :
    min(s.min),
    max(s.max)
{}

template <typename T, nat t_n>
template <typename U, nat u_n>
constexpr span<T, t_n>::span(const span<U, u_n> & s) :
    min(s.min),
    max(s.max)
{}

template <typename T, nat t_n>
constexpr span<T, t_n>::span(const vec<T, t_n> & v1, const vec<T, t_n> & v2) :
    min(v1),
    max(v2)
{}

template <typename T, nat t_n>
constexpr span<T, t_n>::span(const T & v1, const T & v2) :
    min(v1),
    max(v2)
{}



//------------------------------------------------------------------------------
// Assignment



template <typename T, nat t_n>
inline span<T, t_n> & span<T, t_n>::operator=(const span<T, t_n> & s) {
    min = s.min;
    max = s.max;
    return *this;
}

template <typename T, nat t_n>
inline span<T, t_n> & span<T, t_n>::operator=(span<T, t_n> && s) {
    min = s.min;
    max = s.max;
    return *this;
}

template <typename T, nat t_n>
template <nat u_n>
inline span<T, t_n> & span<T, t_n>::operator=(const span<T, u_n> & s) {
    min = s.min;
    max = s.max;
    return *this;
}



//------------------------------------------------------------------------------
// Other



template <typename T, nat t_n>
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

template <typename T>
inline vec1<T> & operator++(vec1<T> & v) {
    ++v.x;
    return v;
}

template <typename T>
inline vec2<T> & operator++(vec2<T> & v) {
    ++v.x; ++v.y;
    return v;
}

template <typename T>
inline vec3<T> & operator++(vec3<T> & v) {
    ++v.x; ++v.y; ++v.z;
    return v;
}

template <typename T>
inline vec4<T> & operator++(vec4<T> & v) {
    ++v.x; ++v.y; ++v.z; ++v.w;
    return v;
}

//--- post increment ---

template <typename T>
inline vec1<T> operator++(vec1<T> & v, int) {
    return vec1<T>(v.x++);
}

template <typename T>
inline vec2<T> operator++(vec2<T> & v, int) {
    return vec2<T>(v.x++, v.y++);
}

template <typename T>
inline vec3<T> operator++(vec3<T> & v, int) {
    return vec3<T>(v.x++, v.y++, v.z++);
}

template <typename T>
inline vec4<T> operator++(vec4<T> & v, int) {
    return vec4<T>(v.x++, v.y++, v.z++, v.w++);
}

//--- pre decrement ---

template <typename T>
inline vec1<T> & operator--(vec1<T> & v) {
    --v.x;
    return v;
}

template <typename T>
inline vec2<T> & operator--(vec2<T> & v) {
    --v.x; --v.y;
    return v;
}

template <typename T>
inline vec3<T> & operator--(vec3<T> & v) {
    --v.x; --v.y; --v.z;
    return v;
}

template <typename T>
inline vec4<T> & operator--(vec4<T> & v) {
    --v.x; --v.y; --v.z; --v.w;
    return v;
}

//--- post decrement ---

template <typename T>
inline vec1<T> operator--(vec1<T> & v, int) {
    return vec1<T>(v.x--);
}

template <typename T>
inline vec2<T> operator--(vec2<T> & v, int) {
    return vec2<T>(v.x--, v.y--);
}

template <typename T>
inline vec3<T> operator--(vec3<T> & v, int) {
    return vec3<T>(v.x--, v.y--, v.z--);
}

template <typename T>
inline vec4<T> operator--(vec4<T> & v, int) {
    return vec4<T>(v.x--, v.y--, v.z--, v.w--);
}

//--- add assign ---

template <typename T, nat t_n>
inline vec<T, t_n> & operator+=(vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    return v1 = v1 + v2;
}

template <typename T, nat t_n>
inline vec<T, t_n> & operator+=(vec<T, t_n> & v1, const T & v2) {
    return v1 = v1 + v2;
}

//--- subtract assign ---

template <typename T, nat t_n>
inline vec<T, t_n> & operator-=(vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    return v1 = v1 - v2;
}

template <typename T, nat t_n>
inline vec<T, t_n> & operator-=(vec<T, t_n> & v1, const T & v2) {
    return v1 = v1 - v2;
}

//--- multiply assign ---

template <typename T, nat t_n>
inline vec<T, t_n> & operator*=(vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    return v1 = v1 * v2;
}

template <typename T, nat t_n>
inline vec<T, t_n> & operator*=(vec<T, t_n> & v1, const T & v2) {
    return v1 = v1 * v2;
}

//--- divide assign ---

template <typename T, nat t_n>
inline vec<T, t_n> & operator/=(vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    return v1 = v1 / v2;
}

template <typename T, nat t_n>
inline vec<T, t_n> & operator/=(vec<T, t_n> & v1, const T & v2) {
    return v1 = v1 / v2;
}

//--- modulus assign ---

template <typename T, nat t_n>
inline vec<T, t_n> & operator%=(vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    return v1 = v1 % v2;
}

template <typename T, nat t_n>
inline vec<T, t_n> & operator%=(vec<T, t_n> & v1, const T & v2) {
    return v1 = v1 % v2;
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- positive ---

template <typename T>
constexpr vec1<T> operator+(const vec1<T> & v) {
    return vec1<T>(+v.x);
}

template <typename T>
constexpr vec2<T> operator+(const vec2<T> & v) {
    return vec2<T>(+v.x, +v.y);
}

template <typename T>
constexpr vec3<T> operator+(const vec3<T> & v) {
    return vec3<T>(+v.x, +v.y, +v.z);
}

template <typename T>
constexpr vec4<T> operator+(const vec4<T> & v) {
    return vec4<T>(+v.x, +v.y, +v.z, +v.w);
}

//--- negative ---

template <typename T>
constexpr vec1<T> operator-(const vec1<T> & v) {
    return vec1<T>(-v.x);
}

template <typename T>
constexpr vec2<T> operator-(const vec2<T> & v) {
    return vec2<T>(-v.x, -v.y);
}

template <typename T>
constexpr vec3<T> operator-(const vec3<T> & v) {
    return vec3<T>(-v.x, -v.y, -v.z);
}

template <typename T>
constexpr vec4<T> operator-(const vec4<T> & v) {
    return vec4<T>(-v.x, -v.y, -v.z, -v.w);
}

//--- add ---

template <typename T>
constexpr vec1<T> operator+(const vec1<T> & v1, const vec1<T> & v2) {
    return vec1<T>(v1.x + v2.x);
}

template <typename T>
constexpr vec2<T> operator+(const vec2<T> & v1, const vec2<T> & v2) {
    return vec2<T>(v1.x + v2.x, v1.y + v2.y);
}

template <typename T>
constexpr vec3<T> operator+(const vec3<T> & v1, const vec3<T> & v2) {
    return vec3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

template <typename T>
constexpr vec4<T> operator+(const vec4<T> & v1, const vec4<T> & v2) {
    return vec4<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

template <typename T>
constexpr vec1<T> operator+(const vec1<T> & v1, const T & v2) {
    return vec1<T>(v1.x + v2);
}

template <typename T>
constexpr vec2<T> operator+(const vec2<T> & v1, const T & v2) {
    return vec2<T>(v1.x + v2, v1.y + v2);
}

template <typename T>
constexpr vec3<T> operator+(const vec3<T> & v1, const T & v2) {
    return vec3<T>(v1.x + v2, v1.y + v2, v1.z + v2);
}

template <typename T>
constexpr vec4<T> operator+(const vec4<T> & v1, const T & v2) {
    return vec4<T>(v1.x + v2, v1.y + v2, v1.z + v2, v1.w + v2);
}

template <typename T>
constexpr vec1<T> operator+(const T & v1, const vec1<T> & v2) {
    return vec1<T>(v1 + v2.x);
}

template <typename T>
constexpr vec2<T> operator+(const T & v1, const vec2<T> & v2) {
    return vec2<T>(v1 + v2.x, v1 + v2.y);
}

template <typename T>
constexpr vec3<T> operator+(const T & v1, const vec3<T> & v2) {
    return vec3<T>(v1 + v2.x, v1 + v2.y, v1 + v2.z);
}

template <typename T>
constexpr vec4<T> operator+(const T & v1, const vec4<T> & v2) {
    return vec4<T>(v1 + v2.x, v1 + v2.y, v1 + v2.z, v1 + v2.w);
}

//--- subtract ---

template <typename T>
constexpr vec1<T> operator-(const vec1<T> & v1, const vec1<T> & v2) {
    return vec1<T>(v1.x - v2.x);
}

template <typename T>
constexpr vec2<T> operator-(const vec2<T> & v1, const vec2<T> & v2) {
    return vec2<T>(v1.x - v2.x, v1.y - v2.y);
}

template <typename T>
constexpr vec3<T> operator-(const vec3<T> & v1, const vec3<T> & v2) {
    return vec3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

template <typename T>
constexpr vec4<T> operator-(const vec4<T> & v1, const vec4<T> & v2) {
    return vec4<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

template <typename T>
constexpr vec1<T> operator-(const vec1<T> & v1, const T & v2) {
    return vec1<T>(v1.x - v2);
}

template <typename T>
constexpr vec2<T> operator-(const vec2<T> & v1, const T & v2) {
    return vec2<T>(v1.x - v2, v1.y - v2);
}

template <typename T>
constexpr vec3<T> operator-(const vec3<T> & v1, const T & v2) {
    return vec3<T>(v1.x - v2, v1.y - v2, v1.z - v2);
}

template <typename T>
constexpr vec4<T> operator-(const vec4<T> & v1, const T & v2) {
    return vec4<T>(v1.x - v2, v1.y - v2, v1.z - v2, v1.w - v2);
}

template <typename T>
constexpr vec1<T> operator-(const T & v1, const vec1<T> & v2) {
    return vec1<T>(v1 - v2.x);
}

template <typename T>
constexpr vec2<T> operator-(const T & v1, const vec2<T> & v2) {
    return vec2<T>(v1 - v2.x, v1 - v2.y);
}

template <typename T>
constexpr vec3<T> operator-(const T & v1, const vec3<T> & v2) {
    return vec3<T>(v1 - v2.x, v1 - v2.y, v1 - v2.z);
}

template <typename T>
constexpr vec4<T> operator-(const T & v1, const vec4<T> & v2) {
    return vec4<T>(v1 - v2.x, v1 - v2.y, v1 - v2.z, v1 - v2.w);
}

//--- multiply ---

template <typename T>
constexpr vec1<T> operator*(const vec1<T> & v1, const vec1<T> & v2) {
    return vec1<T>(v1.x * v2.x);
}

template <typename T>
constexpr vec2<T> operator*(const vec2<T> & v1, const vec2<T> & v2) {
    return vec2<T>(v1.x * v2.x, v1.y * v2.y);
}

template <typename T>
constexpr vec3<T> operator*(const vec3<T> & v1, const vec3<T> & v2) {
    return vec3<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

template <typename T>
constexpr vec4<T> operator*(const vec4<T> & v1, const vec4<T> & v2) {
    return vec4<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

template <typename T>
constexpr vec1<T> operator*(const vec1<T> & v1, const T & v2) {
    return vec1<T>(v1.x * v2);
}

template <typename T>
constexpr vec2<T> operator*(const vec2<T> & v1, const T & v2) {
    return vec2<T>(v1.x * v2, v1.y * v2);
}

template <typename T>
constexpr vec3<T> operator*(const vec3<T> & v1, const T & v2) {
    return vec3<T>(v1.x * v2, v1.y * v2, v1.z * v2);
}

template <typename T>
constexpr vec4<T> operator*(const vec4<T> & v1, const T & v2) {
    return vec4<T>(v1.x * v2, v1.y * v2, v1.z * v2, v1.w * v2);
}

template <typename T>
constexpr vec1<T> operator*(const T & v1, const vec1<T> & v2) {
    return vec1<T>(v1 * v2.x);
}

template <typename T>
constexpr vec2<T> operator*(const T & v1, const vec2<T> & v2) {
    return vec2<T>(v1 * v2.x, v1 * v2.y);
}

template <typename T>
constexpr vec3<T> operator*(const T & v1, const vec3<T> & v2) {
    return vec3<T>(v1 * v2.x, v1 * v2.y, v1 * v2.z);
}

template <typename T>
constexpr vec4<T> operator*(const T & v1, const vec4<T> & v2) {
    return vec4<T>(v1 * v2.x, v1 * v2.y, v1 * v2.z, v1 * v2.w);
}

//--- divide ---

template <typename T>
constexpr vec1<T> operator/(const vec1<T> & v1, const vec1<T> & v2) {
    return vec1<T>(v1.x / v2.x);
}

template <typename T>
constexpr vec2<T> operator/(const vec2<T> & v1, const vec2<T> & v2) {
    return vec2<T>(v1.x / v2.x, v1.y / v2.y);
}

template <typename T>
constexpr vec3<T> operator/(const vec3<T> & v1, const vec3<T> & v2) {
    return vec3<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

template <typename T>
constexpr vec4<T> operator/(const vec4<T> & v1, const vec4<T> & v2) {
    return vec4<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
}

template <typename T>
constexpr vec1<T> operator/(const vec1<T> & v1, const T & v2) {
    return vec1<T>(v1.x / v2);
}

template <typename T>
constexpr vec2<T> operator/(const vec2<T> & v1, const T & v2) {
    if constexpr (std::is_floating_point_v<T>) {
        T inv(static_cast<T>(1.0) / v2);
        return vec2<T>(v1.x * inv, v1.y * inv);
    }
    else {
        return vec2<T>(v1.x / v2, v1.y / v2);
    }
}

template <typename T>
constexpr vec3<T> operator/(const vec3<T> & v1, const T & v2) {
    if constexpr (std::is_floating_point_v<T>) {
        T inv(static_cast<T>(1.0) / v2);
        return vec3<T>(v1.x * inv, v1.y * inv, v1.z * inv);
    }
    else {
        return vec3<T>(v1.x / v2, v1.y / v2, v1.z / v2);
    }
}

template <typename T>
constexpr vec4<T> operator/(const vec4<T> & v1, const T & v2) {
    if constexpr (std::is_floating_point_v<T>) {
        T inv(static_cast<T>(1.0) / v2);
        return vec4<T>(v1.x * inv, v1.y * inv, v1.z * inv, v1.w * inv);
    }
    else {
        return vec4<T>(v1.x / v2, v1.y / v2, v1.z / v2, v1.w / v2);
    }
}

template <typename T>
constexpr vec1<T> operator/(const T & v1, const vec1<T> & v2) {
    return vec1<T>(v1 / v2.x);
}

template <typename T>
constexpr vec2<T> operator/(const T & v1, const vec2<T> & v2) {
    return vec2<T>(v1 / v2.x, v1 / v2.y);
}

template <typename T>
constexpr vec3<T> operator/(const T & v1, const vec3<T> & v2) {
    return vec3<T>(v1 / v2.x, v1 / v2.y, v1 / v2.z);
}

template <typename T>
constexpr vec4<T> operator/(const T & v1, const vec4<T> & v2) {
    return vec4<T>(v1 / v2.x, v1 / v2.y, v1 / v2.z, v1 / v2.w);
}

//--- modulus ---

template <typename T>
constexpr vec1<T> operator%(const vec1<T> & v1, const vec1<T> & v2) {
    return vec1<T>(mod(v1.x, v2.x));
}

template <typename T>
constexpr vec2<T> operator%(const vec2<T> & v1, const vec2<T> & v2) {
    return vec2<T>(mod(v1.x, v2.x), mod(v1.y, v2.y));
}

template <typename T>
constexpr vec3<T> operator%(const vec3<T> & v1, const vec3<T> & v2) {
    return vec3<T>(mod(v1.x, v2.x), mod(v1.y, v2.y), mod(v1.z, v2.z));
}

template <typename T>
constexpr vec4<T> operator%(const vec4<T> & v1, const vec4<T> & v2) {
    return vec4<T>(mod(v1.x, v2.x), mod(v1.y, v2.y), mod(v1.z, v2.z), mod(v1.w, v2.w));
}

template <typename T>
constexpr vec1<T> operator%(const vec1<T> & v1, const T & v2) {
    return vec1<T>(mod(v1.x, v2));
}

template <typename T>
constexpr vec2<T> operator%(const vec2<T> & v1, const T & v2) {
    return vec2<T>(mod(v1.x, v2), mod(v1.y, v2));
}

template <typename T>
constexpr vec3<T> operator%(const vec3<T> & v1, const T & v2) {
    return vec3<T>(mod(v1.x, v2), mod(v1.y, v2), mod(v1.z, v2));
}

template <typename T>
constexpr vec4<T> operator%(const vec4<T> & v1, const T & v2) {
    return vec4<T>(mod(v1.x, v2), mod(v1.y, v2), mod(v1.z, v2), mod(v1.w, v2));
}

template <typename T>
constexpr vec1<T> operator%(const T & v1, const vec1<T> & v2) {
    return vec1<T>(mod(v1, v2.x));
}

template <typename T>
constexpr vec2<T> operator%(const T & v1, const vec2<T> & v2) {
    return vec2<T>(mod(v1, v2.x), mod(v1, v2.y));
}

template <typename T>
constexpr vec3<T> operator%(const T & v1, const vec3<T> & v2) {
    return vec3<T>(mod(v1, v2.x), mod(v1, v2.y), mod(v1, v2.z));
}

template <typename T>
constexpr vec4<T> operator%(const T & v1, const vec4<T> & v2) {
    return vec4<T>(mod(v1, v2.x), mod(v1, v2.y), mod(v1, v2.z), mod(v1, v2.w));
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T>
constexpr bool operator==(const vec1<T> & v1, const vec1<T> & v2) {
    return v1.x == v2.x;
}

template <typename T>
constexpr bool operator==(const vec2<T> & v1, const vec2<T> & v2) {
    return v1.x == v2.x && v1.y == v2.y;
}

template <typename T>
constexpr bool operator==(const vec3<T> & v1, const vec3<T> & v2) {
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

template <typename T>
constexpr bool operator==(const vec4<T> & v1, const vec4<T> & v2) {
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
}

template <typename T>
constexpr bool operator==(const vec<T, 6> & v1, const vec<T, 6> & v2) {
    return v1.min == v2.min && v1.max == v2.max;
}

template <typename T>
constexpr bool operator==(const vec<T, 8> & v1, const vec<T, 8> & v2) {
    return v1.min == v2.min && v1.max == v2.max;
}

template <typename T>
constexpr bvec1 operator==(const vec1<T> & v1, const T & v2) {
    return bvec1(v1.x == v2);
}

template <typename T>
constexpr bvec2 operator==(const vec2<T> & v1, const T & v2) {
    return bvec2(v1.x == v2, v1.y == v2);
}

template <typename T>
constexpr bvec3 operator==(const vec3<T> & v1, const T & v2) {
    return bvec3(v1.x == v2, v1.y == v2, v1.z == v2);
}

template <typename T>
constexpr bvec4 operator==(const vec4<T> & v1, const T & v2) {
    return bvec4(v1.x == v2, v1.y == v2, v1.z == v2, v1.w == v2);
}

template <typename T>
constexpr bvec1 operator==(const T & v1, const vec1<T> & v2) {
    return bvec1(v1 == v2.x);
}

template <typename T>
constexpr bvec2 operator==(const T & v1, const vec2<T> & v2) {
    return bvec2(v1 == v2.x, v1 == v2.y);
}

template <typename T>
constexpr bvec3 operator==(const T & v1, const vec3<T> & v2) {
    return bvec3(v1 == v2.x, v1 == v2.y, v1 == v2.z);
}

template <typename T>
constexpr bvec4 operator==(const T & v1, const vec4<T> & v2) {
    return bvec4(v1 == v2.x, v1 == v2.y, v1 == v2.z, v1 == v2.w);
}

template <typename T, nat t_n>
constexpr bool operator==(const span<T, t_n> & s1, const span<T, t_n> & s2) {
    return s1.min == s2.min && s1.max == s2.max;
}

//--- not equal to ---

template <typename T>
constexpr bool operator!=(const vec1<T> & v1, const vec1<T> & v2) {
    return v1.x != v2.x;
}

template <typename T>
constexpr bool operator!=(const vec2<T> & v1, const vec2<T> & v2) {
    return v1.x != v2.x || v1.y != v2.y;
}

template <typename T>
constexpr bool operator!=(const vec3<T> & v1, const vec3<T> & v2) {
    return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z;
}

template <typename T>
constexpr bool operator!=(const vec4<T> & v1, const vec4<T> & v2) {
    return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z || v1.w != v2.w;
}

template <typename T>
constexpr bool operator!=(const vec<T, 6> & v1, const vec<T, 6> & v2) {
    return v1.min != v2.min || v1.max != v2.max;
}

template <typename T>
constexpr bool operator!=(const vec<T, 8> & v1, const vec<T, 8> & v2) {
    return v1.min != v2.min || v1.max != v2.max;
}

template <typename T>
constexpr bvec1 operator!=(const vec1<T> & v1, const T & v2) {
    return bvec1(v1.x != v2);
}

template <typename T>
constexpr bvec2 operator!=(const vec2<T> & v1, const T & v2) {
    return bvec2(v1.x != v2, v1.y != v2);
}

template <typename T>
constexpr bvec3 operator!=(const vec3<T> & v1, const T & v2) {
    return bvec3(v1.x != v2, v1.y != v2, v1.z != v2);
}

template <typename T>
constexpr bvec4 operator!=(const vec4<T> & v1, const T & v2) {
    return bvec4(v1.x != v2, v1.y != v2, v1.z != v2, v1.w != v2);
}

template <typename T>
constexpr bvec1 operator!=(const T & v1, const vec1<T> & v2) {
    return bvec1(v1 != v2.x);
}

template <typename T>
constexpr bvec2 operator!=(const T & v1, const vec2<T> & v2) {
    return bvec2(v1 != v2.x, v1 != v2.y);
}

template <typename T>
constexpr bvec3 operator!=(const T & v1, const vec3<T> & v2) {
    return bvec3(v1 != v2.x, v1 != v2.y, v1 != v2.z);
}

template <typename T>
constexpr bvec4 operator!=(const T & v1, const vec4<T> & v2) {
    return bvec4(v1 != v2.x, v1 != v2.y, v1 != v2.z, v1 != v2.w);
}

template <typename T, nat t_n>
constexpr bool operator!=(const span<T, t_n> & s1, const span<T, t_n> & s2) {
    return s1.min != s2.min || s1.max != s2.max;
}

//--- less than ---

template <typename T>
constexpr bvec1 operator<(const vec1<T> & v1, const vec1<T> & v2) {
    return bvec1(v1.x < v2.x);
}

template <typename T>
constexpr bvec2 operator<(const vec2<T> & v1, const vec2<T> & v2) {
    return bvec2(v1.x < v2.x, v1.y < v2.y);
}

template <typename T>
constexpr bvec3 operator<(const vec3<T> & v1, const vec3<T> & v2) {
    return bvec3(v1.x < v2.x, v1.y < v2.y, v1.z < v2.z);
}

template <typename T>
constexpr bvec4 operator<(const vec4<T> & v1, const vec4<T> & v2) {
    return bvec4(v1.x < v2.x, v1.y < v2.y, v1.z < v2.z, v1.w < v2.w);
}

template <typename T>
constexpr bvec1 operator<(const vec1<T> & v1, const T & v2) {
    return bvec1(v1.x < v2);
}

template <typename T>
constexpr bvec2 operator<(const vec2<T> & v1, const T & v2) {
    return bvec2(v1.x < v2, v1.y < v2);
}

template <typename T>
constexpr bvec3 operator<(const vec3<T> & v1, const T & v2) {
    return bvec3(v1.x < v2, v1.y < v2, v1.z < v2);
}

template <typename T>
constexpr bvec4 operator<(const vec4<T> & v1, const T & v2) {
    return bvec4(v1.x < v2, v1.y < v2, v1.z < v2, v1.w < v2);
}

template <typename T>
constexpr bvec1 operator<(const T & v1, const vec1<T> & v2) {
    return bvec1(v1 < v2.x);
}

template <typename T>
constexpr bvec2 operator<(const T & v1, const vec2<T> & v2) {
    return bvec2(v1 < v2.x, v1 < v2.y);
}

template <typename T>
constexpr bvec3 operator<(const T & v1, const vec3<T> & v2) {
    return bvec3(v1 < v2.x, v1 < v2.y, v1 < v2.z);
}

template <typename T>
constexpr bvec4 operator<(const T & v1, const vec4<T> & v2) {
    return bvec4(v1 < v2.x, v1 < v2.y, v1 < v2.z, v1 < v2.w);
}

//--- greater than ---

template <typename T>
constexpr bvec1 operator>(const vec1<T> & v1, const vec1<T> & v2) {
    return bvec1(v1.x > v2.x);
}

template <typename T>
constexpr bvec2 operator>(const vec2<T> & v1, const vec2<T> & v2) {
    return bvec2(v1.x > v2.x, v1.y > v2.y);
}

template <typename T>
constexpr bvec3 operator>(const vec3<T> & v1, const vec3<T> & v2) {
    return bvec3(v1.x > v2.x, v1.y > v2.y, v1.z > v2.z);
}

template <typename T>
constexpr bvec4 operator>(const vec4<T> & v1, const vec4<T> & v2) {
    return bvec4(v1.x > v2.x, v1.y > v2.y, v1.z > v2.z, v1.w > v2.w);
}

template <typename T>
constexpr bvec1 operator>(const vec1<T> & v1, const T & v2) {
    return bvec1(v1.x > v2);
}

template <typename T>
constexpr bvec2 operator>(const vec2<T> & v1, const T & v2) {
    return bvec2(v1.x > v2, v1.y > v2);
}

template <typename T>
constexpr bvec3 operator>(const vec3<T> & v1, const T & v2) {
    return bvec3(v1.x > v2, v1.y > v2, v1.z > v2);
}

template <typename T>
constexpr bvec4 operator>(const vec4<T> & v1, const T & v2) {
    return bvec4(v1.x > v2, v1.y > v2, v1.z > v2, v1.w > v2);
}

template <typename T>
constexpr bvec1 operator>(const T & v1, const vec1<T> & v2) {
    return bvec1(v1 > v2.x);
}

template <typename T>
constexpr bvec2 operator>(const T & v1, const vec2<T> & v2) {
    return bvec2(v1 > v2.x, v1 > v2.y);
}

template <typename T>
constexpr bvec3 operator>(const T & v1, const vec3<T> & v2) {
    return bvec3(v1 > v2.x, v1 > v2.y, v1 > v2.z);
}

template <typename T>
constexpr bvec4 operator>(const T & v1, const vec4<T> & v2) {
    return bvec4(v1 > v2.x, v1 > v2.y, v1 > v2.z, v1 > v2.w);
}

//--- less than or equal to ---

template <typename T>
constexpr bvec1 operator<=(const vec1<T> & v1, const vec1<T> & v2) {
    return bvec1(v1.x <= v2.x);
}

template <typename T>
constexpr bvec2 operator<=(const vec2<T> & v1, const vec2<T> & v2) {
    return bvec2(v1.x <= v2.x, v1.y <= v2.y);
}

template <typename T>
constexpr bvec3 operator<=(const vec3<T> & v1, const vec3<T> & v2) {
    return bvec3(v1.x <= v2.x, v1.y <= v2.y, v1.z <= v2.z);
}

template <typename T>
constexpr bvec4 operator<=(const vec4<T> & v1, const vec4<T> & v2) {
    return bvec4(v1.x <= v2.x, v1.y <= v2.y, v1.z <= v2.z, v1.w <= v2.w);
}

template <typename T>
constexpr bvec1 operator<=(const vec1<T> & v1, const T & v2) {
    return bvec1(v1.x <= v2);
}

template <typename T>
constexpr bvec2 operator<=(const vec2<T> & v1, const T & v2) {
    return bvec2(v1.x <= v2, v1.y <= v2);
}

template <typename T>
constexpr bvec3 operator<=(const vec3<T> & v1, const T & v2) {
    return bvec3(v1.x <= v2, v1.y <= v2, v1.z <= v2);
}

template <typename T>
constexpr bvec4 operator<=(const vec4<T> & v1, const T & v2) {
    return bvec4(v1.x <= v2, v1.y <= v2, v1.z <= v2, v1.w <= v2);
}

template <typename T>
constexpr bvec1 operator<=(const T & v1, const vec1<T> & v2) {
    return bvec1(v1 <= v2.x);
}

template <typename T>
constexpr bvec2 operator<=(const T & v1, const vec2<T> & v2) {
    return bvec2(v1 <= v2.x, v1 <= v2.y);
}

template <typename T>
constexpr bvec3 operator<=(const T & v1, const vec3<T> & v2) {
    return bvec3(v1 <= v2.x, v1 <= v2.y, v1 <= v2.z);
}

template <typename T>
constexpr bvec4 operator<=(const T & v1, const vec4<T> & v2) {
    return bvec4(v1 <= v2.x, v1 <= v2.y, v1 <= v2.z, v1 <= v2.w);
}

//--- greater than or equal to ---

template <typename T>
constexpr bvec1 operator>=(const vec1<T> & v1, const vec1<T> & v2) {
    return bvec1(v1.x >= v2.x);
}

template <typename T>
constexpr bvec2 operator>=(const vec2<T> & v1, const vec2<T> & v2) {
    return bvec2(v1.x >= v2.x, v1.y >= v2.y);
}

template <typename T>
constexpr bvec3 operator>=(const vec3<T> & v1, const vec3<T> & v2) {
    return bvec3(v1.x >= v2.x, v1.y >= v2.y, v1.z >= v2.z);
}

template <typename T>
constexpr bvec4 operator>=(const vec4<T> & v1, const vec4<T> & v2) {
    return bvec4(v1.x >= v2.x, v1.y >= v2.y, v1.z >= v2.z, v1.w >= v2.w);
}

template <typename T>
constexpr bvec1 operator>=(const vec1<T> & v1, const T & v2) {
    return bvec1(v1.x >= v2);
}

template <typename T>
constexpr bvec2 operator>=(const vec2<T> & v1, const T & v2) {
    return bvec2(v1.x >= v2, v1.y >= v2);
}

template <typename T>
constexpr bvec3 operator>=(const vec3<T> & v1, const T & v2) {
    return bvec3(v1.x >= v2, v1.y >= v2, v1.z >= v2);
}

template <typename T>
constexpr bvec4 operator>=(const vec4<T> & v1, const T & v2) {
    return bvec4(v1.x >= v2, v1.y >= v2, v1.z >= v2, v1.w >= v2);
}

template <typename T>
constexpr bvec1 operator>=(const T & v1, const vec1<T> & v2) {
    return bvec1(v1 >= v2.x);
}

template <typename T>
constexpr bvec2 operator>=(const T & v1, const vec2<T> & v2) {
    return bvec2(v1 >= v2.x, v1 >= v2.y);
}

template <typename T>
constexpr bvec3 operator>=(const T & v1, const vec3<T> & v2) {
    return bvec3(v1 >= v2.x, v1 >= v2.y, v1 >= v2.z);
}

template <typename T>
constexpr bvec4 operator>=(const T & v1, const vec4<T> & v2) {
    return bvec4(v1 >= v2.x, v1 >= v2.y, v1 >= v2.z, v1 >= v2.w);
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const vec1<T> & v) {
    return os << "[ " << v.x << " ]";
}

template <typename T>
inline std::ostream & operator<<(std::ostream & os, const vec2<T> & v) {
    return os << "[ " << v.x << " " << v.y << " ]";
}

template <typename T>
inline std::ostream & operator<<(std::ostream & os, const vec3<T> & v) {
    return os << "[ " << v.x << " " << v.y << " " << v.z << " ]";
}

template <typename T>
inline std::ostream & operator<<(std::ostream & os, const vec4<T> & v) {
    return os << "[ " << v.x << " " << v.y << " " << v.z << " " << v.w << " ]";
}

template <typename T, nat t_n>
inline std::ostream & operator<<(std::ostream & os, const span<T, t_n> & s) {
    return os << "[ " << s.min << " " << s.max << " ]";
}



//------------------------------------------------------------------------------
// Uncategorized



template <typename T, eif_floating_t<T> = 0>
inline vec1<T> pow(const vec1<T> & v, T p) {
    return vec1<T>(std::pow(v.x, p));
}

template <typename T, eif_floating_t<T> = 0>
inline vec2<T> pow(const vec2<T> & v, T p) {
    return vec2<T>(std::pow(v.x, p), std::pow(v.y, p));
}

template <typename T, eif_floating_t<T> = 0>
inline vec3<T> pow(const vec3<T> & v, T p) {
    return vec3<T>(std::pow(v.x, p), std::pow(v.y, p), std::pow(v.z, p));
}

template <typename T, eif_floating_t<T> = 0>
inline vec4<T> pow(const vec4<T> & v, T p) {
    return vec4<T>(std::pow(v.x, p), std::pow(v.y, p), std::pow(v.z, p), std::pow(v.w, p));
}

template <typename T, eif_floating_t<T> = 0>
inline vec1<T> pow(const vec1<T> & v, const vec1<T> & p) {
    return vec1<T>(std::pow(v.x, p.x));
}

template <typename T, eif_floating_t<T> = 0>
inline vec2<T> pow(const vec2<T> & v, const vec2<T> & p) {
    return vec2<T>(std::pow(v.x, p.x), std::pow(v.y, p.y));
}

template <typename T, eif_floating_t<T> = 0>
inline vec3<T> pow(const vec3<T> & v, const vec3<T> & p) {
    return vec3<T>(std::pow(v.x, p.x), std::pow(v.y, p.y), std::pow(v.z, p.z));
}

template <typename T, eif_floating_t<T> = 0>
inline vec4<T> pow(const vec4<T> & v, const vec4<T> & p) {
    return vec4<T>(std::pow(v.x, p.x), std::pow(v.y, p.y), std::pow(v.z, p.z), std::pow(v.w, p.w));
}

template <typename T, eif_floating_t<T> = 0>
inline vec1<T> exp(const vec1<T> & v) {
    return vec1<T>(std::exp(v.x));
}

template <typename T, eif_floating_t<T> = 0>
inline vec2<T> exp(const vec2<T> & v) {
    return vec2<T>(std::exp(v.x), std::exp(v.y));
}

template <typename T, eif_floating_t<T> = 0>
inline vec3<T> exp(const vec3<T> & v) {
    return vec3<T>(std::exp(v.x), std::exp(v.y), std::exp(v.z));
}

template <typename T, eif_floating_t<T> = 0>
inline vec4<T> exp(const vec4<T> & v) {
    return vec4<T>(std::exp(v.x), std::exp(v.y), std::exp(v.z), std::exp(v.w));
}

template <typename T, nat t_n, eif_floating_t<T>>
inline T magnitude(const vec<T, t_n> & v) {
    return static_cast<T>(std::sqrt(magnitude2(v)));
}

template <typename T>
inline T magnitude2(const vec1<T> & v) {
    return v.x * v.x;
}

template <typename T>
inline T magnitude2(const vec2<T> & v) {
    return v.x * v.x + v.y * v.y;
}

template <typename T>
inline T magnitude2(const vec3<T> & v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

template <typename T>
inline T magnitude2(const vec4<T> & v) {
    return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}

template <typename T, nat t_n, eif_floating_t<T>>
inline vec<T, t_n> norm(const vec<T, t_n> & v) {
    T m(magnitude(v));
    if (zero(m)) {
        return vec<T, t_n>();
    }
    return v * (static_cast<T>(1.0) / m);
}

template <typename T>
inline T dot(const vec1<T> & v1, const vec1<T> & v2) {
    return v1.x * v2.x;
}

template <typename T>
inline T dot(const vec2<T> & v1, const vec2<T> & v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

template <typename T>
inline T dot(const vec3<T> & v1, const vec3<T> & v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T>
inline T dot(const vec4<T> & v1, const vec4<T> & v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

template <typename T>
inline T cross(const vec2<T> & v1, const vec2<T> & v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

template <typename T>
inline vec3<T> cross(const vec3<T> & v1, const vec3<T> & v2) {
    return vec3<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

template <typename T, nat t_n>
inline bool parallel(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    T d(dot(v1, v2));
    return equal(d * d, magnitude2(v1) * magnitude2(v2));
}

template <typename T, nat t_n>
inline bool orthogonal(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    return zero(dot(v1, v2));
}

template <typename T>
inline vec2<T> ortho(const vec2<T> & v) {
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

template <typename T, nat t_n, eif_floating_t<T>>
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

template <typename T, nat t_n, eif_floating_t<T>>
inline vec<T, t_n> reflect(const vec<T, t_n> & v, const vec<T, t_n> & n) {
    return reflect_n(v, norm(n));
}

template <typename T, nat t_n, eif_floating_t<T>>
inline vec<T, t_n> reflect_n(const vec<T, t_n> & v, const vec<T, t_n> & n) {
    return (static_cast<T>(2.0) * dot(v, n)) * n - v;
}

template <typename T, nat t_n, eif_floating_t<T>>
inline T angle(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    return angle_n(norm(v1), norm(v2));
}
template <typename T, nat t_n, eif_floating_t<T>>
inline T angle_n(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    return static_cast<T>(std::acos(dot(v1, v2)));
}

template <typename T>
constexpr const T & min(const vec1<T> & v) {
    return v.x;
}

template <typename T>
constexpr const T & min(const vec2<T> & v) {
    return min(v.x, v.y);
}

template <typename T>
constexpr const T & min(const vec3<T> & v) {
    return min(v.x, v.y, v.z);
}

template <typename T>
constexpr const T & min(const vec4<T> & v) {
    return min(v.x, v.y, v.z, v.w);
}

template <typename T>
constexpr vec1<T> min(const vec1<T> & v1, const vec1<T> & v2) {
    return vec1<T>(min(v1.x, v2.x));
}

template <typename T>
constexpr vec2<T> min(const vec2<T> & v1, const vec2<T> & v2) {
    return vec2<T>(min(v1.x, v2.x), min(v1.y, v2.y));
}

template <typename T>
constexpr vec3<T> min(const vec3<T> & v1, const vec3<T> & v2) {
    return vec3<T>(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z));
}

template <typename T>
constexpr vec4<T> min(const vec4<T> & v1, const vec4<T> & v2) {
    return vec4<T>(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z), min(v1.w, v2.w));
}

template <typename T, nat t_n, typename... Ts>
constexpr vec<T, t_n> min(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<Ts, t_n> &... rest) {
    return min(min(v1, v2), rest...);
}

template <typename T>
constexpr const T & max(const vec1<T> & v) {
    return v.x;
}

template <typename T>
constexpr const T & max(const vec2<T> & v) {
    return max(v.x, v.y);
}

template <typename T>
constexpr const T & max(const vec3<T> & v) {
    return max(v.x, v.y, v.z);
}

template <typename T>
constexpr const T & max(const vec4<T> & v) {
    return max(v.x, v.y, v.z, v.w);
}

template <typename T>
constexpr vec1<T> max(const vec1<T> & v1, const vec1<T> & v2) {
    return vec1<T>(max(v1.x, v2.x));
}

template <typename T>
constexpr vec2<T> max(const vec2<T> & v1, const vec2<T> & v2) {
    return vec2<T>(max(v1.x, v2.x), max(v1.y, v2.y));
}

template <typename T>
constexpr vec3<T> max(const vec3<T> & v1, const vec3<T> & v2) {
    return vec3<T>(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z));
}

template <typename T>
constexpr vec4<T> max(const vec4<T> & v1, const vec4<T> & v2) {
    return vec4<T>(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z), max(v1.w, v2.w));
}

template <typename T, nat t_n, typename... Ts>
constexpr vec<T, t_n> max(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<Ts, t_n> &... rest) {
    return max(max(v1, v2), rest...);
}

template <typename T, nat t_n>
constexpr std::pair<const T &, const T &> minmax(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return minmax(v.x);
    if constexpr (t_n == 2) return minmax(v.x, v.y);
    if constexpr (t_n == 3) return minmax(v.x, v.y, v.z);
    if constexpr (t_n == 4) return minmax(v.x, v.y, v.z, v.w);
}

template <typename T>
inline void sort(vec1<T> & v) {
    
}

template <typename T>
inline void sort(vec2<T> & v) {
    if (v.x > v.y) std::swap(v.x, v.y);
}

template <typename T>
inline void sort(vec3<T> & v) {
    if (v.x > v.y) std::swap(v.x, v.y);
    if (v.y > v.z) std::swap(v.y, v.z);
    if (v.x > v.y) std::swap(v.x, v.y);
}

template <typename T>
inline void sort(vec4<T> & v) {
    if (v.x > v.y) std::swap(v.x, v.y);
    if (v.z > v.w) std::swap(v.z, v.w);
    if (v.y > v.z) std::swap(v.y, v.z);
    if (v.x > v.y) std::swap(v.x, v.y);
    if (v.z > v.w) std::swap(v.z, v.w);
}

template <typename T>
constexpr vec1<T> clamp(const vec1<T> & v, const T & min, const T & max) {
    return vec1<T>(
        clamp(v.x, min, max)
    );
}

template <typename T>
constexpr vec2<T> clamp(const vec2<T> & v, const T & min, const T & max) {
    return vec2<T>(
        clamp(v.x, min, max),
        clamp(v.y, min, max)
    );
}

template <typename T>
constexpr vec3<T> clamp(const vec3<T> & v, const T & min, const T & max) {
    return vec3<T>(
        clamp(v.x, min, max),
        clamp(v.y, min, max),
        clamp(v.z, min, max)
    );
}

template <typename T>
constexpr vec4<T> clamp(const vec4<T> & v, const T & min, const T & max) {
    return vec4<T>(
        clamp(v.x, min, max),
        clamp(v.y, min, max),
        clamp(v.z, min, max),
        clamp(v.w, min, max)
    );
}

template <typename T>
constexpr vec1<T> clamp(const vec1<T> & v, const vec1<T> & min, const vec1<T> & max) {
    return vec1<T>(
        clamp(v.x, min.x, max.x)
    );
}

template <typename T>
constexpr vec2<T> clamp(const vec2<T> & v, const vec2<T> & min, const vec2<T> & max) {
    return vec2<T>(
        clamp(v.x, min.x, max.x),
        clamp(v.y, min.y, max.y)
    );
}

template <typename T>
constexpr vec3<T> clamp(const vec3<T> & v, const vec3<T> & min, const vec3<T> & max) {
    return vec3<T>(
        clamp(v.x, min.x, max.x),
        clamp(v.y, min.y, max.y),
        clamp(v.z, min.z, max.z)
    );
}

template <typename T>
constexpr vec4<T> clamp(const vec4<T> & v, const vec4<T> & min, const vec4<T> & max) {
    return vec4<T>(
        clamp(v.x, min.x, max.x),
        clamp(v.y, min.y, max.y),
        clamp(v.z, min.z, max.z),
        clamp(v.w, min.w, max.w)
    );
}

template <typename T>
constexpr vec1<T> abs(const vec1<T> & v) {
    return vec1<T>(abs(v.x));
}

template <typename T>
constexpr vec2<T> abs(const vec2<T> & v) {
    return vec2<T>(abs(v.x), abs(v.y));
}

template <typename T>
constexpr vec3<T> abs(const vec3<T> & v) {
    return vec3<T>(abs(v.x), abs(v.y), abs(v.z));
}

template <typename T>
constexpr vec4<T> abs(const vec4<T> & v) {
    return vec4<T>(abs(v.x), abs(v.y), abs(v.z), abs(v.w));
}

template <typename T>
constexpr nvec1 floor(const vec1<T> & v) {
    return nvec1(floor(v.x));
}

template <typename T>
constexpr nvec2 floor(const vec2<T> & v) {
    return nvec2(floor(v.x), floor(v.y));
}

template <typename T>
constexpr nvec3 floor(const vec3<T> & v) {
    return nvec3(floor(v.x), floor(v.y), floor(v.z));
}

template <typename T>
constexpr nvec4 floor(const vec4<T> & v) {
    return nvec4(floor(v.x), floor(v.y), floor(v.z), floor(v.w));
}

template <typename T>
constexpr nvec1 ceil(const vec1<T> & v) {
    return nvec1(ceil(v.x));
}

template <typename T>
constexpr nvec2 ceil(const vec2<T> & v) {
    return nvec2(ceil(v.x), ceil(v.y));
}

template <typename T>
constexpr nvec3 ceil(const vec3<T> & v) {
    return nvec3(ceil(v.x), ceil(v.y), ceil(v.z));
}

template <typename T>
constexpr nvec4 ceil(const vec4<T> & v) {
    return nvec4(ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w));
}

template <typename T, nat t_n, eif_floating_t<T>>
constexpr vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, T t) {
    return (static_cast<T>(1) - t) * v1 + t * v2;
}

template <typename T, nat t_n, eif_floating_t<T>>
constexpr vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec2<T> & weights) {
    return weights.x * v1 + weights.y * v2;
}

template <typename T, nat t_n, eif_floating_t<T>>
constexpr vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & v3, const vec3<T> & weights) {
    return weights.x * v1 + weights.y * v2 + weights.z * v3;
}

template <typename T, nat t_n, eif_floating_t<T>>
constexpr vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & v3, const vec<T, t_n> & v4, const vec4<T> & weights) {
    return weights.x * v1 + weights.y * v2 + weights.z * v3 + weights.w * v4;
}

template <typename T>
constexpr span1<T> toSpan(const bound1<T> & b) {
    return span1<T>(b.min, b.min + b.max); // using min/max rather than loc/size for constexpr union issues
}

template <typename T>
constexpr span2<T> toSpan(const bound2<T> & b) {
    return span2<T>(b.min, b.min + b.max);
}

template <typename T>
constexpr span3<T> toSpan(const bound3<T> & b) {
    return span3<T>(b.min, b.min + b.max);
}

template <typename T>
constexpr span4<T> toSpan(const bound4<T> & b) {
    return span4<T>(b.min, b.min + b.max);
}

template <typename T>
constexpr bound1<T> toBound(const span1<T> & s) {
    return bound1<T>(s.min, s.max - s.min);
}

template <typename T>
constexpr bound2<T> toBound(const span2<T> & s) {
    return bound2<T>(s.min, s.max - s.min);
}

template <typename T>
constexpr bound3<T> toBound(const span3<T> & s) {
    return bound3<T>(s.min, s.max - s.min);
}

template <typename T>
constexpr bound4<T> toBound(const span4<T> & s) {
    return bound4<T>(s.min, s.max - s.min);
}

template <typename T>
inline span1<T> intersect(const span1<T> & s1, const span1<T> & s2) {
    return span1<T>(
        vec1<T>(
            max(s1.min.x, s2.min.x)
        ),
        vec1<T>(
            min(s1.max.x, s2.max.x)
        )
    );
}

template <typename T>
inline span2<T> intersect(const span2<T> & s1, const span2<T> & s2) {
    return span2<T>(
        vec2<T>(
            max(s1.min.x, s2.min.x),
            max(s1.min.y, s2.min.y)
        ),
        vec2<T>(
            min(s1.max.x, s2.max.x),
            min(s1.max.y, s2.max.y)
        )
    );
}

template <typename T>
inline span3<T> intersect(const span3<T> & s1, const span3<T> & s2) {
    return span3<T>(
        vec3<T>(
            max(s1.min.x, s2.min.x),
            max(s1.min.y, s2.min.y),
            max(s1.min.z, s2.min.z)
        ),
        vec3<T>(
            min(s1.max.x, s2.max.x),
            min(s1.max.y, s2.max.y),
            min(s1.max.z, s2.max.z)
        )
    );
}

template <typename T>
inline span4<T> intersect(const span4<T> & s1, const span4<T> & s2) {
    return span4<T>(
        vec4<T>(
            max(s1.min.x, s2.min.x),
            max(s1.min.y, s2.min.y),
            max(s1.min.z, s2.min.z),
            max(s1.min.w, s2.min.w)
        ),
        vec4<T>(
            min(s1.max.x, s2.max.x),
            min(s1.max.y, s2.max.y),
            min(s1.max.z, s2.max.z),
            min(s1.max.w, s2.max.w)
        )
    );
}

constexpr bvec1 operator&&(const bvec1 & v1, const bvec1 & v2) {
    return bvec1(v1.x && v2.x);
}

constexpr bvec2 operator&&(const bvec2 & v1, const bvec2 & v2) {
    return bvec2(v1.x && v2.x, v1.y && v2.y);
}

constexpr bvec3 operator&&(const bvec3 & v1, const bvec3 & v2) {
    return bvec3(v1.x && v2.x, v1.y && v2.y, v1.z && v2.z);
}

constexpr bvec4 operator&&(const bvec4 & v1, const bvec4 & v2) {
    return bvec4(v1.x && v2.x, v1.y && v2.y, v1.z && v2.z, v1.w && v2.w);
}

constexpr bool vand(const bvec1 & v) {
    return v.x;
}

constexpr bool vand(const bvec2 & v) {
    return v.x && v.y;
}

constexpr bool vand(const bvec3 & v) {
    return v.x && v.y && v.z;
}

constexpr bool vand(const bvec4 & v) {
    return v.x && v.y && v.z && v.w;
}

constexpr bvec1 operator||(const bvec1 & v1, const bvec1 & v2) {
    return bvec1(v1.x || v2.x);
}

constexpr bvec2 operator||(const bvec2 & v1, const bvec2 & v2) {
    return bvec2(v1.x || v2.x, v1.y || v2.y);
}

constexpr bvec3 operator||(const bvec3 & v1, const bvec3 & v2) {
    return bvec3(v1.x || v2.x, v1.y || v2.y, v1.z || v2.z);
}

constexpr bvec4 operator||(const bvec4 & v1, const bvec4 & v2) {
    return bvec4(v1.x || v2.x, v1.y || v2.y, v1.z || v2.z, v1.w || v2.w);
}

constexpr bool vor(const bvec1 & v) {
    return v.x;
}

constexpr bool vor(const bvec2 & v) {
    return v.x || v.y;
}

constexpr bool vor(const bvec3 & v) {
    return v.x || v.y || v.z;
}

constexpr bool vor(const bvec4 & v) {
    return v.x || v.y || v.z || v.w;
}

constexpr bvec1 operator!(const bvec1 & v) {
    return bvec1(!v.x);
}

constexpr bvec2 operator!(const bvec2 & v) {
    return bvec2(!v.x, !v.y);
}

constexpr bvec3 operator!(const bvec3 & v) {
    return bvec3(!v.x, !v.y, !v.z);
}

constexpr bvec4 operator!(const bvec4 & v) {
    return bvec4(!v.x, !v.y, !v.z, !v.w);
}



}