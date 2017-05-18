#pragma once



#include <limits>
#include <iostream>
#include <string>
#include <sstream>

#include "QMU.hpp"



namespace qmu {



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Type Declarations ---------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Vec



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



//------------------------------------------------------------------------------
// Bound



template <typename T, nat t_n> using bound = vec<T, t_n * 2>;

template <typename T> using bound1 = vec<T, 2>;
template <typename T> using bound2 = vec<T, 4>;
template <typename T> using bound3 = vec<T, 6>;
template <typename T> using bound4 = vec<T, 8>;

template <nat t_n> using   fbound = vec<               float, t_n>;
template <nat t_n> using   dbound = vec<              double, t_n>;
template <nat t_n> using  ldbound = vec<         long double, t_n>;
template <nat t_n> using   cbound = vec<  signed        char, t_n>;
template <nat t_n> using  ucbound = vec<unsigned        char, t_n>;
template <nat t_n> using   sbound = vec<  signed       short, t_n>;
template <nat t_n> using  usbound = vec<unsigned       short, t_n>;
template <nat t_n> using   ibound = vec<  signed         int, t_n>;
template <nat t_n> using  uibound = vec<unsigned         int, t_n>;
template <nat t_n> using   lbound = vec<  signed        long, t_n>;
template <nat t_n> using  ulbound = vec<unsigned        long, t_n>;
template <nat t_n> using  llbound = vec<  signed long   long, t_n>;
template <nat t_n> using ullbound = vec<unsigned long   long, t_n>;
template <nat t_n> using   nbound = vec<                 nat, t_n>;
template <nat t_n> using  unbound = vec<                unat, t_n>;

using   fbound1 = bound1<               float>;
using   fbound2 = bound2<               float>;
using   fbound3 = bound3<               float>;
using   fbound4 = bound4<               float>;
using   dbound1 = bound1<              double>;
using   dbound2 = bound2<              double>;
using   dbound3 = bound3<              double>;
using   dbound4 = bound4<              double>;
using  ldbound1 = bound1<         long double>;
using  ldbound2 = bound2<         long double>;
using  ldbound3 = bound3<         long double>;
using  ldbound4 = bound4<         long double>;
using   cbound1 = bound1<  signed        char>;
using   cbound2 = bound2<  signed        char>;
using   cbound3 = bound3<  signed        char>;
using   cbound4 = bound4<  signed        char>;
using  ucbound1 = bound1<unsigned        char>;
using  ucbound2 = bound2<unsigned        char>;
using  ucbound3 = bound3<unsigned        char>;
using  ucbound4 = bound4<unsigned        char>;
using   sbound1 = bound1<  signed       short>;
using   sbound2 = bound2<  signed       short>;
using   sbound3 = bound3<  signed       short>;
using   sbound4 = bound4<  signed       short>;
using  usbound1 = bound1<unsigned       short>;
using  usbound2 = bound2<unsigned       short>;
using  usbound3 = bound3<unsigned       short>;
using  usbound4 = bound4<unsigned       short>;
using   ibound1 = bound1<  signed         int>;
using   ibound2 = bound2<  signed         int>;
using   ibound3 = bound3<  signed         int>;
using   ibound4 = bound4<  signed         int>;
using  uibound1 = bound1<unsigned         int>;
using  uibound2 = bound2<unsigned         int>;
using  uibound3 = bound3<unsigned         int>;
using  uibound4 = bound4<unsigned         int>;
using   lbound1 = bound1<  signed        long>;
using   lbound2 = bound2<  signed        long>;
using   lbound3 = bound3<  signed        long>;
using   lbound4 = bound4<  signed        long>;
using  ulbound1 = bound1<unsigned        long>;
using  ulbound2 = bound2<unsigned        long>;
using  ulbound3 = bound3<unsigned        long>;
using  ulbound4 = bound4<unsigned        long>;
using  llbound1 = bound1<  signed long   long>;
using  llbound2 = bound2<  signed long   long>;
using  llbound3 = bound3<  signed long   long>;
using  llbound4 = bound4<  signed long   long>;
using ullbound1 = bound1<unsigned long   long>;
using ullbound2 = bound2<unsigned long   long>;
using ullbound3 = bound3<unsigned long   long>;
using ullbound4 = bound4<unsigned long   long>;
using   nbound1 = bound1<                 nat>;
using   nbound2 = bound2<                 nat>;
using   nbound3 = bound3<                 nat>;
using   nbound4 = bound4<                 nat>;
using  unbound1 = bound1<                unat>;
using  unbound2 = bound2<                unat>;
using  unbound3 = bound3<                unat>;
using  unbound4 = bound4<                unat>;



//------------------------------------------------------------------------------
// Span



template <typename T, nat t_n> using span = bound<T, t_n>;

template <typename T> using span1 = bound1<T>;
template <typename T> using span2 = bound2<T>;
template <typename T> using span3 = bound3<T>;
template <typename T> using span4 = bound4<T>;

template <nat t_n> using   fspan =   fbound<t_n>;
template <nat t_n> using   dspan =   dbound<t_n>;
template <nat t_n> using  ldspan =  ldbound<t_n>;
template <nat t_n> using   cspan =   cbound<t_n>;
template <nat t_n> using  ucspan =  ucbound<t_n>;
template <nat t_n> using   sspan =   sbound<t_n>;
template <nat t_n> using  usspan =  usbound<t_n>;
template <nat t_n> using   ispan =   ibound<t_n>;
template <nat t_n> using  uispan =  uibound<t_n>;
template <nat t_n> using   lspan =   lbound<t_n>;
template <nat t_n> using  ulspan =  ulbound<t_n>;
template <nat t_n> using  llspan =  llbound<t_n>;
template <nat t_n> using ullspan = ullbound<t_n>;
template <nat t_n> using   nspan =   nbound<t_n>;
template <nat t_n> using  unspan =  unbound<t_n>;

using   fspan1 =   fbound1;
using   fspan2 =   fbound2;
using   fspan3 =   fbound3;
using   fspan4 =   fbound4;
using   dspan1 =   dbound1;
using   dspan2 =   dbound2;
using   dspan3 =   dbound3;
using   dspan4 =   dbound4;
using  ldspan1 =  ldbound1;
using  ldspan2 =  ldbound2;
using  ldspan3 =  ldbound3;
using  ldspan4 =  ldbound4;
using   cspan1 =   cbound1;
using   cspan2 =   cbound2;
using   cspan3 =   cbound3;
using   cspan4 =   cbound4;
using  ucspan1 =  ucbound1;
using  ucspan2 =  ucbound2;
using  ucspan3 =  ucbound3;
using  ucspan4 =  ucbound4;
using   sspan1 =   sbound1;
using   sspan2 =   sbound2;
using   sspan3 =   sbound3;
using   sspan4 =   sbound4;
using  usspan1 =  usbound1;
using  usspan2 =  usbound2;
using  usspan3 =  usbound3;
using  usspan4 =  usbound4;
using   ispan1 =   ibound1;
using   ispan2 =   ibound2;
using   ispan3 =   ibound3;
using   ispan4 =   ibound4;
using  uispan1 =  uibound1;
using  uispan2 =  uibound2;
using  uispan3 =  uibound3;
using  uispan4 =  uibound4;
using   lspan1 =   lbound1;
using   lspan2 =   lbound2;
using   lspan3 =   lbound3;
using   lspan4 =   lbound4;
using  ulspan1 =  ulbound1;
using  ulspan2 =  ulbound2;
using  ulspan3 =  ulbound3;
using  ulspan4 =  ulbound4;
using  llspan1 =  llbound1;
using  llspan2 =  llbound2;
using  llspan3 =  llbound3;
using  llspan4 =  llbound4;
using ullspan1 = ullbound1;
using ullspan2 = ullbound2;
using ullspan3 = ullbound3;
using ullspan4 = ullbound4;
using   nspan1 =   nbound1;
using   nspan2 =   nbound2;
using   nspan3 =   nbound3;
using   nspan4 =   nbound4;
using  unspan1 =  unbound1;
using  unspan2 =  unbound2;
using  unspan3 =  unbound3;
using  unspan4 =  unbound4;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Type Namespaces -----------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Vec



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



//------------------------------------------------------------------------------
// Bound



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



//------------------------------------------------------------------------------
// Span



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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC1 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct vec<T, 1> {

    using Type = T;
    static constexpr nat t_n = 1;

    union {
        T x;
        T r;
        T s;
    };

    //--- constructors ---

    constexpr vec();
    constexpr vec(const vec1<T> & v);
    constexpr vec(vec1<T> && v);

    template <typename U> constexpr explicit vec(const vec1<U> & v);

    constexpr explicit vec(const      T  & v);
    constexpr explicit vec(const vec2<T> & v);
    constexpr explicit vec(const vec3<T> & v);
    constexpr explicit vec(const vec4<T> & v);

    //--- assignment operators ---

    vec1<T> & operator=(const vec1<T> & v);
    vec1<T> & operator=(vec1<T> && v);

    vec1<T> & operator=(const      T  & v);
    vec1<T> & operator=(const vec2<T> & v);
    vec1<T> & operator=(const vec3<T> & v);
    vec1<T> & operator=(const vec4<T> & v);

    //--- access operators ---

    T & operator[](nat i);
    const T & operator[](nat i) const;

    //--- other ---

    std::string toString() const;
};

//--- arithmetic assignment operators ---

template <typename T> vec1<T> & operator+=(vec1<T> & v1, const vec1<T> & v2);
template <typename T> vec1<T> & operator+=(vec1<T> & v1, const      T  & v2);
template <typename T> vec1<T> & operator+=(vec1<T> & v1, const vec2<T> & v2);
template <typename T> vec1<T> & operator+=(vec1<T> & v1, const vec3<T> & v2);
template <typename T> vec1<T> & operator+=(vec1<T> & v1, const vec4<T> & v2);

template <typename T> vec1<T> & operator-=(vec1<T> & v1, const vec1<T> & v2);
template <typename T> vec1<T> & operator-=(vec1<T> & v1, const      T  & v2);
template <typename T> vec1<T> & operator-=(vec1<T> & v1, const vec2<T> & v2);
template <typename T> vec1<T> & operator-=(vec1<T> & v1, const vec3<T> & v2);
template <typename T> vec1<T> & operator-=(vec1<T> & v1, const vec4<T> & v2);

template <typename T> vec1<T> & operator*=(vec1<T> & v1, const vec1<T> & v2);
template <typename T> vec1<T> & operator*=(vec1<T> & v1, const      T  & v2);
template <typename T> vec1<T> & operator*=(vec1<T> & v1, const vec2<T> & v2);
template <typename T> vec1<T> & operator*=(vec1<T> & v1, const vec3<T> & v2);
template <typename T> vec1<T> & operator*=(vec1<T> & v1, const vec4<T> & v2);

template <typename T> vec1<T> & operator/=(vec1<T> & v1, const vec1<T> & v2);
template <typename T> vec1<T> & operator/=(vec1<T> & v1, const      T  & v2);
template <typename T> vec1<T> & operator/=(vec1<T> & v1, const vec2<T> & v2);
template <typename T> vec1<T> & operator/=(vec1<T> & v1, const vec3<T> & v2);
template <typename T> vec1<T> & operator/=(vec1<T> & v1, const vec4<T> & v2);

//--- arithmetic operators ---

template <typename T> vec1<T> & operator++(vec1<T> & v);
template <typename T> vec1<T>   operator++(vec1<T> & v, int);

template <typename T> vec1<T> & operator--(vec1<T> & v);
template <typename T> vec1<T>   operator--(vec1<T> & v, int);

template <typename T> vec1<T> operator+(const vec1<T> & v);

template <typename T> vec1<T> operator-(const vec1<T> & v);

template <typename T> vec1<T> operator+(const vec1<T> & v1, const vec1<T> & v2);
template <typename T> vec1<T> operator+(const vec1<T> & v1, const      T  & v2);
template <typename T> vec1<T> operator+(const      T  & v1, const vec1<T> & v2);

template <typename T> vec1<T> operator-(const vec1<T> & v1, const vec1<T> & v2);
template <typename T> vec1<T> operator-(const vec1<T> & v1, const      T  & v2);
template <typename T> vec1<T> operator-(const      T  & v1, const vec1<T> & v2);

template <typename T> vec1<T> operator*(const vec1<T> & v1, const vec1<T> & v2);
template <typename T> vec1<T> operator*(const vec1<T> & v1, const      T  & v2);
template <typename T> vec1<T> operator*(const      T  & v1, const vec1<T> & v2);

template <typename T> vec1<T> operator/(const vec1<T> & v1, const vec1<T> & v2);
template <typename T> vec1<T> operator/(const vec1<T> & v1, const      T  & v2);
template <typename T> vec1<T> operator/(const      T  & v1, const vec1<T> & v2);

//--- comparison operators ---

template <typename T>  bool operator==(const vec1<T> & v1, const vec1<T> & v2);
template <typename T> bvec1 operator==(const vec1<T> & v1, const      T  & v2);
template <typename T> bvec1 operator==(const      T  & v1, const vec1<T> & v2);

template <typename T>  bool operator!=(const vec1<T> & v1, const vec1<T> & v2);
template <typename T> bvec1 operator!=(const vec1<T> & v1, const      T  & v2);
template <typename T> bvec1 operator!=(const      T  & v1, const vec1<T> & v2);

template <typename T> bvec1 operator<(const vec1<T> & v1, const      T  & v2);
template <typename T> bvec1 operator<(const      T  & v1, const vec1<T> & v2);

template <typename T> bvec1 operator>(const vec1<T> & v1, const      T  & v2);
template <typename T> bvec1 operator>(const      T  & v1, const vec1<T> & v2);

template <typename T> bvec1 operator<=(const vec1<T> & v1, const      T  & v2);
template <typename T> bvec1 operator<=(const      T  & v1, const vec1<T> & v2);

template <typename T> bvec1 operator>=(const vec1<T> & v1, const      T  & v2);
template <typename T> bvec1 operator>=(const      T  & v1, const vec1<T> & v2);

//--- other ---

template <typename T> std::ostream & operator<<(std::ostream & os, const vec1<T> & v);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC2 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct vec<T, 2> {

    using Type = T;
    static constexpr nat t_n = 2;

    union {
        struct { T x, y; };
        struct { T r, g; };
        struct { T s, t; };
        struct { vec1<T> min, max; };
        struct { vec1<T> loc, size; };
    };

    //--- constructors ---

    constexpr vec();
    constexpr vec(const vec2<T> & v);
    constexpr vec(vec2<T> && v);

    template <typename U> constexpr explicit vec(const vec2<U> & v);

    constexpr explicit vec(const      T  & v);
    constexpr explicit vec(const vec1<T> & v);
    constexpr explicit vec(const vec3<T> & v);
    constexpr explicit vec(const vec4<T> & v);
    constexpr vec(const       T & v1, const      T  & v2);
    constexpr vec(const vec1<T> & v1, const      T  & v2);
    constexpr vec(const       T & v1, const vec1<T> & v2);
    constexpr vec(const vec1<T> & v1, const vec1<T> & v2);

    //--- assignment operators ---

    vec2<T> & operator=(const vec2<T> & v);
    vec2<T> & operator=(vec2<T> && v);

    vec2<T> & operator=(const      T  & v);
    vec2<T> & operator=(const vec1<T> & v);
    vec2<T> & operator=(const vec3<T> & v);
    vec2<T> & operator=(const vec4<T> & v);

    //--- access operators ---

    T & operator[](nat i);
    const T & operator[](nat i) const;

    //--- other ---

    std::string toString() const;

};

//--- arithmetic assignment operators ---

template <typename T> vec2<T> & operator+=(vec2<T> & v1, const vec2<T> & v2);
template <typename T> vec2<T> & operator+=(vec2<T> & v1, const      T  & v2);
template <typename T> vec2<T> & operator+=(vec2<T> & v1, const vec1<T> & v2);
template <typename T> vec2<T> & operator+=(vec2<T> & v1, const vec3<T> & v2);
template <typename T> vec2<T> & operator+=(vec2<T> & v1, const vec4<T> & v2);

template <typename T> vec2<T> & operator-=(vec2<T> & v1, const vec2<T> & v2);
template <typename T> vec2<T> & operator-=(vec2<T> & v1, const      T  & v2);
template <typename T> vec2<T> & operator-=(vec2<T> & v1, const vec1<T> & v2);
template <typename T> vec2<T> & operator-=(vec2<T> & v1, const vec3<T> & v2);
template <typename T> vec2<T> & operator-=(vec2<T> & v1, const vec4<T> & v2);

template <typename T> vec2<T> & operator*=(vec2<T> & v1, const vec2<T> & v2);
template <typename T> vec2<T> & operator*=(vec2<T> & v1, const      T  & v2);
template <typename T> vec2<T> & operator*=(vec2<T> & v1, const vec1<T> & v2);
template <typename T> vec2<T> & operator*=(vec2<T> & v1, const vec3<T> & v2);
template <typename T> vec2<T> & operator*=(vec2<T> & v1, const vec4<T> & v2);

template <typename T> vec2<T> & operator/=(vec2<T> & v1, const vec2<T> & v2);
template <typename T> vec2<T> & operator/=(vec2<T> & v1, const      T  & v2);
template <typename T> vec2<T> & operator/=(vec2<T> & v1, const vec1<T> & v2);
template <typename T> vec2<T> & operator/=(vec2<T> & v1, const vec3<T> & v2);
template <typename T> vec2<T> & operator/=(vec2<T> & v1, const vec4<T> & v2);

//--- arithmetic operators ---

template <typename T> vec2<T> & operator++(vec2<T> & v);
template <typename T> vec2<T>   operator++(vec2<T> & v, int);

template <typename T> vec2<T> & operator--(vec2<T> & v);
template <typename T> vec2<T>   operator--(vec2<T> & v, int);

template <typename T> vec2<T> operator+(const vec2<T> & v);

template <typename T> vec2<T> operator-(const vec2<T> & v);

template <typename T> vec2<T> operator+(const vec2<T> & v1, const vec2<T> & v2);
template <typename T> vec2<T> operator+(const vec2<T> & v1, const      T  & v2);
template <typename T> vec2<T> operator+(const      T  & v1, const vec2<T> & v2);
template <typename T> vec2<T> operator+(const vec2<T> & v1, const vec1<T> & v2);
template <typename T> vec2<T> operator+(const vec1<T> & v1, const vec2<T> & v2);

template <typename T> vec2<T> operator-(const vec2<T> & v1, const vec2<T> & v2);
template <typename T> vec2<T> operator-(const vec2<T> & v1, const      T  & v2);
template <typename T> vec2<T> operator-(const      T  & v1, const vec2<T> & v2);
template <typename T> vec2<T> operator-(const vec2<T> & v1, const vec1<T> & v2);
template <typename T> vec2<T> operator-(const vec1<T> & v1, const vec2<T> & v2);

template <typename T> vec2<T> operator*(const vec2<T> & v1, const vec2<T> & v2);
template <typename T> vec2<T> operator*(const vec2<T> & v1, const      T  & v2);
template <typename T> vec2<T> operator*(const      T  & v1, const vec2<T> & v2);
template <typename T> vec2<T> operator*(const vec2<T> & v1, const vec1<T> & v2);
template <typename T> vec2<T> operator*(const vec1<T> & v1, const vec2<T> & v2);

template <typename T> vec2<T> operator/(const vec2<T> & v1, const vec2<T> & v2);
template <typename T> vec2<T> operator/(const vec2<T> & v1, const      T  & v2);
template <typename T> vec2<T> operator/(const      T  & v1, const vec2<T> & v2);
template <typename T> vec2<T> operator/(const vec2<T> & v1, const vec1<T> & v2);
template <typename T> vec2<T> operator/(const vec1<T> & v1, const vec2<T> & v2);

//--- comparison operators ---

template <typename T>  bool operator==(const vec2<T> & v1, const vec2<T> & v2);
template <typename T> bvec2 operator==(const vec2<T> & v1, const      T  & v2);
template <typename T> bvec2 operator==(const      T  & v1, const vec2<T> & v2);

template <typename T>  bool operator!=(const vec2<T> & v1, const vec2<T> & v2);
template <typename T> bvec2 operator!=(const vec2<T> & v1, const      T  & v2);
template <typename T> bvec2 operator!=(const      T  & v1, const vec2<T> & v2);

template <typename T> bvec2 operator<(const vec2<T> & v1, const      T  & v2);
template <typename T> bvec2 operator<(const      T  & v1, const vec2<T> & v2);

template <typename T> bvec2 operator>(const vec2<T> & v1, const      T  & v2);
template <typename T> bvec2 operator>(const      T  & v1, const vec2<T> & v2);

template <typename T> bvec2 operator<=(const vec2<T> & v1, const      T  & v2);
template <typename T> bvec2 operator<=(const      T  & v1, const vec2<T> & v2);

template <typename T> bvec2 operator>=(const vec2<T> & v1, const      T  & v2);
template <typename T> bvec2 operator>=(const      T  & v1, const vec2<T> & v2);

//--- other ---

template <typename T> std::ostream & operator<<(std::ostream & os, const vec2<T> & v);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC3 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct vec<T, 3> {

    using Type = T;
    static constexpr nat t_n = 3;

    union {
        struct { T x, y, z; };
        struct { T r, g, b; };
        struct { T s, t, p; };
        struct { T rad, theta, phi; };
        struct { T alpha, beta, gamma; };
        struct { vec2<T> xy; T z; };
        struct { T x; vec2<T> yz; };
    };

    //--- constructors ---

    constexpr vec();
    constexpr vec(const vec3<T> & v);
    constexpr vec(vec3<T> && v);

    template <typename U> constexpr explicit vec(const vec3<U> & v);

    constexpr explicit vec(const      T  & v);
    constexpr explicit vec(const vec1<T> & v);
    constexpr explicit vec(const vec2<T> & v);
    constexpr explicit vec(const vec4<T> & v);
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

    //--- assignment operators ---

    vec3<T> & operator=(const vec3<T> & v);
    vec3<T> & operator=(vec3<T> && v);

    vec3<T> & operator=(const      T  & v);
    vec3<T> & operator=(const vec1<T> & v);
    vec3<T> & operator=(const vec2<T> & v);
    vec3<T> & operator=(const vec4<T> & v);

    //--- access operators ---

    T & operator[](nat i);
    const T & operator[](nat i) const;

    //--- other ---

    std::string toString() const;

};

//--- arithmetic assignment operators ---

template <typename T> vec3<T> & operator+=(vec3<T> & v1, const vec3<T> & v2);
template <typename T> vec3<T> & operator+=(vec3<T> & v1, const      T  & v2);
template <typename T> vec3<T> & operator+=(vec3<T> & v1, const vec1<T> & v2);
template <typename T> vec3<T> & operator+=(vec3<T> & v1, const vec2<T> & v2);
template <typename T> vec3<T> & operator+=(vec3<T> & v1, const vec4<T> & v2);

template <typename T> vec3<T> & operator-=(vec3<T> & v1, const vec3<T> & v2);
template <typename T> vec3<T> & operator-=(vec3<T> & v1, const      T  & v2);
template <typename T> vec3<T> & operator-=(vec3<T> & v1, const vec1<T> & v2);
template <typename T> vec3<T> & operator-=(vec3<T> & v1, const vec2<T> & v2);
template <typename T> vec3<T> & operator-=(vec3<T> & v1, const vec4<T> & v2);

template <typename T> vec3<T> & operator*=(vec3<T> & v1, const vec3<T> & v2);
template <typename T> vec3<T> & operator*=(vec3<T> & v1, const      T  & v2);
template <typename T> vec3<T> & operator*=(vec3<T> & v1, const vec1<T> & v2);
template <typename T> vec3<T> & operator*=(vec3<T> & v1, const vec2<T> & v2);
template <typename T> vec3<T> & operator*=(vec3<T> & v1, const vec4<T> & v2);

template <typename T> vec3<T> & operator/=(vec3<T> & v1, const vec3<T> & v2);
template <typename T> vec3<T> & operator/=(vec3<T> & v1, const      T  & v2);
template <typename T> vec3<T> & operator/=(vec3<T> & v1, const vec1<T> & v2);
template <typename T> vec3<T> & operator/=(vec3<T> & v1, const vec2<T> & v2);
template <typename T> vec3<T> & operator/=(vec3<T> & v1, const vec4<T> & v2);

//--- arithmetic operators ---

template <typename T> vec3<T> & operator++(vec3<T> & v);
template <typename T> vec3<T>   operator++(vec3<T> & v, int);

template <typename T> vec3<T> & operator--(vec3<T> & v);
template <typename T> vec3<T>   operator--(vec3<T> & v, int);

template <typename T> vec3<T> operator+(const vec3<T> & v);

template <typename T> vec3<T> operator-(const vec3<T> & v);

template <typename T> vec3<T> operator+(const vec3<T> & v1, const vec3<T> & v2);
template <typename T> vec3<T> operator+(const vec3<T> & v1, const      T  & v2);
template <typename T> vec3<T> operator+(const      T  & v1, const vec3<T> & v2);
template <typename T> vec3<T> operator+(const vec3<T> & v1, const vec1<T> & v2);
template <typename T> vec3<T> operator+(const vec1<T> & v1, const vec3<T> & v2);
template <typename T> vec3<T> operator+(const vec3<T> & v1, const vec2<T> & v2);
template <typename T> vec3<T> operator+(const vec2<T> & v1, const vec3<T> & v2);

template <typename T> vec3<T> operator-(const vec3<T> & v1, const vec3<T> & v2);
template <typename T> vec3<T> operator-(const vec3<T> & v1, const      T  & v2);
template <typename T> vec3<T> operator-(const      T  & v1, const vec3<T> & v2);
template <typename T> vec3<T> operator-(const vec3<T> & v1, const vec1<T> & v2);
template <typename T> vec3<T> operator-(const vec1<T> & v1, const vec3<T> & v2);
template <typename T> vec3<T> operator-(const vec3<T> & v1, const vec2<T> & v2);
template <typename T> vec3<T> operator-(const vec2<T> & v1, const vec3<T> & v2);

template <typename T> vec3<T> operator*(const vec3<T> & v1, const vec3<T> & v2);
template <typename T> vec3<T> operator*(const vec3<T> & v1, const      T  & v2);
template <typename T> vec3<T> operator*(const      T  & v1, const vec3<T> & v2);
template <typename T> vec3<T> operator*(const vec3<T> & v1, const vec1<T> & v2);
template <typename T> vec3<T> operator*(const vec1<T> & v1, const vec3<T> & v2);
template <typename T> vec3<T> operator*(const vec3<T> & v1, const vec2<T> & v2);
template <typename T> vec3<T> operator*(const vec2<T> & v1, const vec3<T> & v2);

template <typename T> vec3<T> operator/(const vec3<T> & v1, const vec3<T> & v2);
template <typename T> vec3<T> operator/(const vec3<T> & v1, const      T  & v2);
template <typename T> vec3<T> operator/(const      T  & v1, const vec3<T> & v2);
template <typename T> vec3<T> operator/(const vec3<T> & v1, const vec1<T> & v2);
template <typename T> vec3<T> operator/(const vec1<T> & v1, const vec3<T> & v2);
template <typename T> vec3<T> operator/(const vec3<T> & v1, const vec2<T> & v2);
template <typename T> vec3<T> operator/(const vec2<T> & v1, const vec3<T> & v2);

//--- comparison operators ---

template <typename T>  bool operator==(const vec3<T> & v1, const vec3<T> & v2);
template <typename T> bvec3 operator==(const vec3<T> & v1, const      T  & v2);
template <typename T> bvec3 operator==(const      T  & v1, const vec3<T> & v2);

template <typename T>  bool operator!=(const vec3<T> & v1, const vec3<T> & v2);
template <typename T> bvec3 operator!=(const vec3<T> & v1, const      T  & v2);
template <typename T> bvec3 operator!=(const      T  & v1, const vec3<T> & v2);

template <typename T> bvec3 operator<(const vec3<T> & v1, const      T  & v2);
template <typename T> bvec3 operator<(const      T  & v1, const vec3<T> & v2);

template <typename T> bvec3 operator>(const vec3<T> & v1, const      T  & v2);
template <typename T> bvec3 operator>(const      T  & v1, const vec3<T> & v2);

template <typename T> bvec3 operator<=(const vec3<T> & v1, const      T  & v2);
template <typename T> bvec3 operator<=(const      T  & v1, const vec3<T> & v2);

template <typename T> bvec3 operator>=(const vec3<T> & v1, const      T  & v2);
template <typename T> bvec3 operator>=(const      T  & v1, const vec3<T> & v2);

//--- other ---

template <typename T> std::ostream & operator<<(std::ostream & os, const vec3<T> & v);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC4 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct vec<T, 4> {

    using Type = T;
    static constexpr nat t_n = 4;
    
    union {
        struct { T x, y, z, w; };
        struct { T r, g, b, a; };
        struct { T s, t, p, q; };
        struct { vec2<T> min, max; };
        struct { vec2<T> loc, size; };
        struct { vec2<T> xy, zw; };
        struct { T x; vec2<T> yz; T w; };
        struct { vec3<T> xyz; T w; };
        struct { T x; vec3<T> yzw; };
    };
    
    //--- constructors ---

    constexpr vec();
    constexpr vec(const vec4<T> & v);
    constexpr vec(vec4<T> && v);

    template <typename U> constexpr explicit vec(const vec4<U> & v);

    constexpr explicit vec(const      T  & v);
    constexpr explicit vec(const vec1<T> & v);
    constexpr explicit vec(const vec2<T> & v);
    constexpr explicit vec(const vec3<T> & v);
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

    //--- assignment operators ---

    vec4<T> & operator=(const vec4<T> & v);
    vec4<T> & operator=(vec4<T> && v);

    vec4<T> & operator=(const      T  & v);
    vec4<T> & operator=(const vec1<T> & v);
    vec4<T> & operator=(const vec2<T> & v);
    vec4<T> & operator=(const vec3<T> & v);

    //--- access operators ---
    
    T & operator[](nat i);
    const T & operator[](nat i) const;

    //--- other ---

    std::string toString() const;

};

//--- arithmetic assignment operators ---

template <typename T> vec4<T> & operator+=(vec4<T> & v1, const vec4<T> & v2);
template <typename T> vec4<T> & operator+=(vec4<T> & v1, const      T  & v2);
template <typename T> vec4<T> & operator+=(vec4<T> & v1, const vec1<T> & v2);
template <typename T> vec4<T> & operator+=(vec4<T> & v1, const vec2<T> & v2);
template <typename T> vec4<T> & operator+=(vec4<T> & v1, const vec3<T> & v2);

template <typename T> vec4<T> & operator-=(vec4<T> & v1, const vec4<T> & v2);
template <typename T> vec4<T> & operator-=(vec4<T> & v1, const      T  & v2);
template <typename T> vec4<T> & operator-=(vec4<T> & v1, const vec1<T> & v2);
template <typename T> vec4<T> & operator-=(vec4<T> & v1, const vec2<T> & v2);
template <typename T> vec4<T> & operator-=(vec4<T> & v1, const vec3<T> & v2);

template <typename T> vec4<T> & operator*=(vec4<T> & v1, const vec4<T> & v2);
template <typename T> vec4<T> & operator*=(vec4<T> & v1, const      T  & v2);
template <typename T> vec4<T> & operator*=(vec4<T> & v1, const vec1<T> & v2);
template <typename T> vec4<T> & operator*=(vec4<T> & v1, const vec2<T> & v2);
template <typename T> vec4<T> & operator*=(vec4<T> & v1, const vec3<T> & v2);

template <typename T> vec4<T> & operator/=(vec4<T> & v1, const vec4<T> & v2);
template <typename T> vec4<T> & operator/=(vec4<T> & v1, const      T  & v2);
template <typename T> vec4<T> & operator/=(vec4<T> & v1, const vec1<T> & v2);
template <typename T> vec4<T> & operator/=(vec4<T> & v1, const vec2<T> & v2);
template <typename T> vec4<T> & operator/=(vec4<T> & v1, const vec3<T> & v2);

//--- arithmetic operators ---

template <typename T> vec4<T> & operator++(vec4<T> & v);
template <typename T> vec4<T>   operator++(vec4<T> & v, int);

template <typename T> vec4<T> & operator--(vec4<T> & v);
template <typename T> vec4<T>   operator--(vec4<T> & v, int);

template <typename T> vec4<T> operator+(const vec4<T> & v);

template <typename T> vec4<T> operator-(const vec4<T> & v);

template <typename T> vec4<T> operator+(const vec4<T> & v1, const vec4<T> & v2);
template <typename T> vec4<T> operator+(const vec4<T> & v1, const      T  & v2);
template <typename T> vec4<T> operator+(const      T  & v1, const vec4<T> & v2);
template <typename T> vec4<T> operator+(const vec4<T> & v1, const vec1<T> & v2);
template <typename T> vec4<T> operator+(const vec1<T> & v1, const vec4<T> & v2);
template <typename T> vec4<T> operator+(const vec4<T> & v1, const vec2<T> & v2);
template <typename T> vec4<T> operator+(const vec2<T> & v1, const vec4<T> & v2);
template <typename T> vec4<T> operator+(const vec4<T> & v1, const vec3<T> & v2);
template <typename T> vec4<T> operator+(const vec3<T> & v1, const vec4<T> & v2);

template <typename T> vec4<T> operator-(const vec4<T> & v1, const vec4<T> & v2);
template <typename T> vec4<T> operator-(const vec4<T> & v1, const      T  & v2);
template <typename T> vec4<T> operator-(const      T  & v1, const vec4<T> & v2);
template <typename T> vec4<T> operator-(const vec4<T> & v1, const vec1<T> & v2);
template <typename T> vec4<T> operator-(const vec1<T> & v1, const vec4<T> & v2);
template <typename T> vec4<T> operator-(const vec4<T> & v1, const vec2<T> & v2);
template <typename T> vec4<T> operator-(const vec2<T> & v1, const vec4<T> & v2);
template <typename T> vec4<T> operator-(const vec4<T> & v1, const vec3<T> & v2);
template <typename T> vec4<T> operator-(const vec3<T> & v1, const vec4<T> & v2);

template <typename T> vec4<T> operator*(const vec4<T> & v1, const vec4<T> & v2);
template <typename T> vec4<T> operator*(const vec4<T> & v1, const      T  & v2);
template <typename T> vec4<T> operator*(const      T  & v1, const vec4<T> & v2);
template <typename T> vec4<T> operator*(const vec4<T> & v1, const vec1<T> & v2);
template <typename T> vec4<T> operator*(const vec1<T> & v1, const vec4<T> & v2);
template <typename T> vec4<T> operator*(const vec4<T> & v1, const vec2<T> & v2);
template <typename T> vec4<T> operator*(const vec2<T> & v1, const vec4<T> & v2);
template <typename T> vec4<T> operator*(const vec4<T> & v1, const vec3<T> & v2);
template <typename T> vec4<T> operator*(const vec3<T> & v1, const vec4<T> & v2);

template <typename T> vec4<T> operator/(const vec4<T> & v1, const vec4<T> & v2);
template <typename T> vec4<T> operator/(const vec4<T> & v1, const      T  & v2);
template <typename T> vec4<T> operator/(const      T  & v1, const vec4<T> & v2);
template <typename T> vec4<T> operator/(const vec4<T> & v1, const vec1<T> & v2);
template <typename T> vec4<T> operator/(const vec1<T> & v1, const vec4<T> & v2);
template <typename T> vec4<T> operator/(const vec4<T> & v1, const vec2<T> & v2);
template <typename T> vec4<T> operator/(const vec2<T> & v1, const vec4<T> & v2);
template <typename T> vec4<T> operator/(const vec4<T> & v1, const vec3<T> & v2);
template <typename T> vec4<T> operator/(const vec3<T> & v1, const vec4<T> & v2);

//--- comparison operators ---

template <typename T>  bool operator==(const vec4<T> & v1, const vec4<T> & v2);
template <typename T> bvec4 operator==(const vec4<T> & v1, const      T  & v2);
template <typename T> bvec4 operator==(const      T  & v1, const vec4<T> & v2);

template <typename T>  bool operator!=(const vec4<T> & v1, const vec4<T> & v2);
template <typename T> bvec4 operator!=(const vec4<T> & v1, const      T  & v2);
template <typename T> bvec4 operator!=(const      T  & v1, const vec4<T> & v2);

template <typename T> bvec4 operator<(const vec4<T> & v1, const      T  & v2);
template <typename T> bvec4 operator<(const      T  & v1, const vec4<T> & v2);

template <typename T> bvec4 operator>(const vec4<T> & v1, const      T  & v2);
template <typename T> bvec4 operator>(const      T  & v1, const vec4<T> & v2);

template <typename T> bvec4 operator<=(const vec4<T> & v1, const      T  & v2);
template <typename T> bvec4 operator<=(const      T  & v1, const vec4<T> & v2);

template <typename T> bvec4 operator>=(const vec4<T> & v1, const      T  & v2);
template <typename T> bvec4 operator>=(const      T  & v1, const vec4<T> & v2);

//--- other ---

template <typename T> std::ostream & operator<<(std::ostream & os, const vec4<T> & v);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC6 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct vec<T, 6> {

    using Type = T;
    static constexpr nat t_n = 6;

    union {
        struct { vec3<T> min, max; };
        struct { vec3<T> loc, size; };
    };

    //--- constructors ---

    constexpr vec();
    constexpr vec(const vec<T, 6> & v);
    constexpr vec(vec<T, 6> && v);

    template <typename U> constexpr explicit vec(const vec<U, 6> & v);

    constexpr vec(const vec3<T> & v1, const vec3<T> & v2);
    constexpr vec(const T & v1, const T & v2, const T & v3, const T & v4, const T & v5, const T & v6);

    //--- assignment operators ---

    vec<T, 6> & operator=(const vec<T, 6> & v);
    vec<T, 6> & operator=(vec<T, 6> && v);

    //--- access operators ---

    T & operator[](nat i);
    const T & operator[](nat i) const;

    //--- other ---

    std::string toString() const;

};

//--- comparison operators ---

template <typename T> bool operator==(const vec<T, 6> & v1, const vec<T, 6> & v2);

template <typename T> bool operator!=(const vec<T, 6> & v1, const vec<T, 6> & v2);

//--- other ---

template <typename T> std::ostream & operator<<(std::ostream & os, const vec<T, 6> & v);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC8 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct vec<T, 8> {

    using Type = T;
    static constexpr nat t_n = 8;

    union {
        struct { vec4<T> min, max; };
        struct { vec4<T> loc, size; };
    };

    //--- constructors ---

    constexpr vec();
    constexpr vec(const vec<T, 8> & v);
    constexpr vec(vec<T, 8> && v);

    template <typename U> constexpr explicit vec(const vec<U, 8> & v);

    constexpr vec(const vec4<T> & v1, const vec4<T> & v2);
    constexpr vec(const T & v1, const T & v2, const T & v3, const T & v4, const T & v5, const T & v6, const T & v7, const T & v8);

    //--- assignment operators ---

    vec<T, 8> & operator=(const vec<T, 8> & v);
    vec<T, 8> & operator=(vec<T, 8> && v);

    //--- access operators ---

    T & operator[](nat i);
    const T & operator[](nat i) const;

    //--- other ---

    std::string toString() const;

};

//--- comparison operators ---

template <typename T> bool operator==(const vec<T, 8> & v1, const vec<T, 8> & v2);

template <typename T> bool operator!=(const vec<T, 8> & v1, const vec<T, 8> & v2);

//--- other ---

template <typename T> std::ostream & operator<<(std::ostream & os, const vec<T, 8> & v);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC FUNCTIONS -------------------------------------------------------------------------------------------------------




template <typename T, nat t_n, enable_if_floating_t<T> = 0>
T magnitude(const vec<T, t_n> & v);

template <typename T, nat t_n>
T magnitude2(const vec<T, t_n> & v);

template <typename T, nat t_n, enable_if_floating_t<T> = 0>
vec<T, t_n> normalize(const vec<T, t_n> & v);

template <typename T, nat t_n>
T dot(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

template <typename T, nat t_n>
vec<T, t_n> cross(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

template <typename T, nat t_n, enable_if_floating_t<T> = 0>
vec<T, t_n> reflect(const vec<T, t_n> & v, const vec<T, t_n> & n);
template <typename T, nat t_n, enable_if_floating_t<T> = 0>
vec<T, t_n> reflect_n(const vec<T, t_n> & v, const vec<T, t_n> & n);

template <typename T, nat t_n, enable_if_floating_t<T> = 0>
T angle(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, nat t_n, enable_if_floating_t<T> = 0>
T angle_n(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

template <typename T, nat t_n>
vec<T, t_n> orthogonal(const vec<T, t_n> & v);

template <typename T, nat t_n>
T min(const vec<T, t_n> & v);

template <typename T, nat t_n>
T max(const vec<T, t_n> & v);

template <typename T, nat t_n>
vec<T, t_n> min(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

template <typename T, nat t_n>
vec<T, t_n> max(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

template <typename T, nat t_n>
vec<T, t_n> clamp(const vec<T, t_n> & v, const T & min, const T & max);

template <typename T, nat t_n>
vec<T, t_n> clamp(const vec<T, t_n> & v, const vec<T, t_n> & min, const vec<T, t_n> & max);

template <typename T, nat t_n, enable_if_floating_t<T> = 0>
vec<T, t_n> mix(const vec<T, t_n> & v1, const vec <T, t_n> & v2, T t);

template <typename T, nat t_n>
span<T, t_n> toSpan(const bound<T, t_n> & b);

template <typename T, nat t_n>
bound<T, t_n> toBound(const span<T, t_n> & s);

template <typename T, nat t_n>
span<T, t_n> intersect(const span<T, t_n> & s1, const span<T, t_n> & s2);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC1 IMPLEMENTATION -------------------------------------------------------------------------------------------------



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
constexpr vec<T, 1>::vec(const T & v) :
    x(v)
{}

template <typename T>
constexpr vec<T, 1>::vec(const vec2<T> & v) :
    x(v.x)
{}

template <typename T>
constexpr vec<T, 1>::vec(const vec3<T> & v) :
    x(v.x)
{}

template <typename T>
constexpr vec<T, 1>::vec(const vec4<T> & v) :
    x(v.x)
{}



//------------------------------------------------------------------------------
// Assignment Operators



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
// Access Operators



template <typename T>
inline T & vec<T, 1>::operator[](nat i) {
    return *(&x + i);
}



template <typename T>
inline const T & vec<T, 1>::operator[](nat i) const {
    return *(&x + i);
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- add assign ---

template <typename T>
inline vec1<T> & operator+=(vec1<T> & v1, const vec1<T> & v2) {
    return v1 = v1 + v2;
}

template <typename T>
inline vec1<T> & operator+=(vec1<T> & v1, const T & v2) {
    return v1 = v1 + v2;
}

template <typename T>
inline vec1<T> & operator+=(vec1<T> & v1, const vec2<T> & v2) {
    return v1 = v1 + v2;
}

template <typename T>
inline vec1<T> & operator+=(vec1<T> & v1, const vec3<T> & v2) {
    return v1 = v1 + v2;
}

template <typename T>
inline vec1<T> & operator+=(vec1<T> & v1, const vec4<T> & v2) {
    return v1 = v1 + v2;
}

//--- subtract assign ---

template <typename T>
inline vec1<T> & operator-=(vec1<T> & v1, const vec1<T> & v2) {
    return v1 = v1 - v2;
}

template <typename T>
inline vec1<T> & operator-=(vec1<T> & v1, const T & v2) {
    return v1 = v1 - v2;
}

template <typename T>
inline vec1<T> & operator-=(vec1<T> & v1, const vec2<T> & v2) {
    return v1 = v1 - v2;
}

template <typename T>
inline vec1<T> & operator-=(vec1<T> & v1, const vec3<T> & v2) {
    return v1 = v1 - v2;
}

template <typename T>
inline vec1<T> & operator-=(vec1<T> & v1, const vec4<T> & v2) {
    return v1 = v1 - v2;
}

//--- multiply assign ---

template <typename T>
inline vec1<T> & operator*=(vec1<T> & v1, const vec1<T> & v2) {
    return v1 = v1 * v2;
}

template <typename T>
inline vec1<T> & operator*=(vec1<T> & v1, const T & v2) {
    return v1 = v1 * v2;
}

template <typename T>
inline vec1<T> & operator*=(vec1<T> & v1, const vec2<T> & v2) {
    return v1 = v1 * v2;
}

template <typename T>
inline vec1<T> & operator*=(vec1<T> & v1, const vec3<T> & v2) {
    return v1 = v1 * v2;
}

template <typename T>
inline vec1<T> & operator*=(vec1<T> & v1, const vec4<T> & v2) {
    return v1 = v1 * v2;
}

//--- divide assign ---

template <typename T>
inline vec1<T> & operator/=(vec1<T> & v1, const vec1<T> & v2) {
    return v1 = v1 / v2;
}

template <typename T>
inline vec1<T> & operator/=(vec1<T> & v1, const T & v2) {
    return v1 = v1 / v2;
}

template <typename T>
inline vec1<T> & operator/=(vec1<T> & v1, const vec2<T> & v2) {
    return v1 = v1 / v2;
}

template <typename T>
inline vec1<T> & operator/=(vec1<T> & v1, const vec3<T> & v2) {
    return v1 = v1 / v2;
}

template <typename T>
inline vec1<T> & operator/=(vec1<T> & v1, const vec4<T> & v2) {
    return v1 = v1 / v2;
}

//--- pre increment ---

template <typename T>
inline vec1<T> & operator++(vec1<T> & v) {
    ++v.x;
    return v;
}

//--- post increment ---

template <typename T>
inline vec1<T> operator++(vec1<T> & v, int) {
    return vec1<T>(v.x++);
}

//--- pre decrement ---

template <typename T>
inline vec1<T> & operator--(vec1<T> & v) {
    --v.x;
    return v;
}

//--- post decrement ---

template <typename T>
inline vec1<T> operator--(vec1<T> & v, int) {
    return vec1<T>(v.x--);
}

//--- positive ---

template <typename T>
inline vec1<T> operator+(const vec1<T> & v) {
    return v;
}

//--- negative ---

template <typename T>
inline vec1<T> operator-(const vec1<T> & v) {
    return v * static_cast<T>(-1);
}

//--- add ---

template <typename T>
inline vec1<T> operator+(const vec1<T> & v1, const vec1<T> & v2) {
    return vec1<T>(v1.x + v2.x);
}

template <typename T>
inline vec1<T> operator+(const vec1<T> & v1, const T & v2) {
    return vec1<T>(v1.x + v2);
}

template <typename T>
inline vec1<T> operator+(const T & v1, const vec1<T> & v2) {
    return vec1<T>(v1 + v2.x);
}

//--- subtract ---

template <typename T>
inline vec1<T> operator-(const vec1<T> & v1, const vec1<T> & v2) {
    return vec1<T>(v1.x - v2.x);
}

template <typename T>
inline vec1<T> operator-(const vec1<T> & v1, const T & v2) {
    return vec1<T>(v1.x - v2);
}

template <typename T>
inline vec1<T> operator-(const T & v1, const vec1<T> & v2) {
    return vec1<T>(v1 - v2.x);
}

//--- multiply ---

template <typename T>
inline vec1<T> operator*(const vec1<T> & v1, const vec1<T> & v2) {
    return vec1<T>(v1.x * v2.x);
}

template <typename T>
inline vec1<T> operator*(const vec1<T> & v1, const T & v2) {
    return vec1<T>(v1.x * v2);
}

template <typename T>
inline vec1<T> operator*(const T & v1, const vec1<T> & v2) {
    return vec1<T>(v1 * v2.x);
}

//--- divide ---

template <typename T>
inline vec1<T> operator/(const vec1<T> & v1, const vec1<T> & v2) {
    return vec1<T>(v1.x / v2.x);
}

template <typename T>
inline vec1<T> operator/(const vec1<T> & v1, const T & v2) {
    return vec1<T>(v1.x / v2);
}

template <typename T>
inline vec1<T> operator/(const T & v1, const vec1<T> & v2) {
    return vec1<T>(v1 / v2.x);
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T>
inline bool operator==(const vec1<T> & v1, const vec1<T> & v2) {
    return v1.x == v2.x;
}

template <typename T>
inline bvec1 operator==(const vec1<T> & v1, const T & v2) {
    return bvec1(v1.x == v2);
}

template <typename T>
inline bvec1 operator==(const T & v1, const vec1<T> & v2) {
    return bvec1(v1 == v2.x);
}

//--- not equal to ---

template <typename T>
inline bool operator!=(const vec1<T> & v1, const vec1<T> & v2) {
    return v1.x != v2.x;
}

template <typename T>
inline bvec1 operator!=(const vec1<T> & v1, const T & v2) {
    return bvec1(v1.x != v2);
}

template <typename T>
inline bvec1 operator!=(const T & v1, const vec1<T> & v2) {
    return bvec1(v1 != v2.x);
}

//--- less than ---

template <typename T>
inline bvec1 operator<(const vec1<T> & v1, const T & v2) {
    return bvec1(v1.x < v2);
}

template <typename T>
inline bvec1 operator<(const T & v1, const vec1<T> & v2) {
    return bvec1(v1 < v2.x);
}

//--- greater than ---

template <typename T>
inline bvec1 operator>(const vec1<T> & v1, const T & v2) {
    return bvec1(v1.x > v2);
}

template <typename T>
inline bvec1 operator>(const T & v1, const vec1<T> & v2) {
    return bvec1(v1 > v2.x);
}

//--- less than or equal to ---

template <typename T>
inline bvec1 operator<=(const vec1<T> & v1, const T & v2) {
    return bvec1(v1.x <= v2);
}

template <typename T>
inline bvec1 operator<=(const T & v1, const vec1<T> & v2) {
    return bvec1(v1 <= v2.x);
}

//--- greater than or equal to ---

template <typename T>
inline bvec1 operator>=(const vec1<T> & v1, const T & v2) {
    return bvec1(v1.x >= v2);
}

template <typename T>
inline bvec1 operator>=(const T & v1, const vec1<T> & v2) {
    return bvec1(v1 >= v2.x);
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string vec<T, 1>::toString() const {
    std::stringstream ss;
    ss << "(" << x << ")";
    return ss.str();
}



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const vec1<T> & v) {
    return os << v.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC2 IMPLEMENTATION -------------------------------------------------------------------------------------------------



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
constexpr vec<T, 2>::vec(const vec2<U> & v) :
    x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
{}

template <typename T>
constexpr vec<T, 2>::vec(const T & v) :
    x(v), y(v)
{}

template <typename T>
constexpr vec<T, 2>::vec(const vec1<T> & v) :
    x(v.x), y(static_cast<T>(0))
{}

template <typename T>
constexpr vec<T, 2>::vec(const vec3<T> & v) :
    x(v.x), y(v.y)
{}

template <typename T>
constexpr vec<T, 2>::vec(const vec4<T> & v) :
    x(v.x), y(v.y)
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
// Assignment Operators



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
// Access Operators



template <typename T>
inline T & vec<T, 2>::operator[](nat i) {
    return *(&x + i);
}



template <typename T>
inline const T & vec<T, 2>::operator[](nat i) const {
    return *(&x + i);
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- add assign ---

template <typename T>
inline vec2<T> & operator+=(vec2<T> & v1, const vec2<T> & v2) {
    return v1 = v1 + v2;
}

template <typename T>
inline vec2<T> & operator+=(vec2<T> & v1, const T & v2) {
    return v1 = v1 + v2;
}

template <typename T>
inline vec2<T> & operator+=(vec2<T> & v1, const vec1<T> & v2) {
    return v1 = v1 + v2;
}

template <typename T>
inline vec2<T> & operator+=(vec2<T> & v1, const vec3<T> & v2) {
    return v1 = v1 + v2;
}

template <typename T>
inline vec2<T> & operator+=(vec2<T> & v1, const vec4<T> & v2) {
    return v1 = v1 + v2;
}

//--- subtract assign ---

template <typename T>
inline vec2<T> & operator-=(vec2<T> & v1, const vec2<T> & v2) {
    return v1 = v1 - v2;
}

template <typename T>
inline vec2<T> & operator-=(vec2<T> & v1, const T & v2) {
    return v1 = v1 - v2;
}

template <typename T>
inline vec2<T> & operator-=(vec2<T> & v1, const vec1<T> & v2) {
    return v1 = v1 - v2;
}

template <typename T>
inline vec2<T> & operator-=(vec2<T> & v1, const vec3<T> & v2) {
    return v1 = v1 - v2;
}

template <typename T>
inline vec2<T> & operator-=(vec2<T> & v1, const vec4<T> & v2) {
    return v1 = v1 - v2;
}

//--- multiply assign ---

template <typename T>
inline vec2<T> & operator*=(vec2<T> & v1, const vec2<T> & v2) {
    return v1 = v1 * v2;
}

template <typename T>
inline vec2<T> & operator*=(vec2<T> & v1, const T & v2) {
    return v1 = v1 * v2;
}

template <typename T>
inline vec2<T> & operator*=(vec2<T> & v1, const vec1<T> & v2) {
    return v1 = v1 * v2;
}

template <typename T>
inline vec2<T> & operator*=(vec2<T> & v1, const vec3<T> & v2) {
    return v1 = v1 * v2;
}

template <typename T>
inline vec2<T> & operator*=(vec2<T> & v1, const vec4<T> & v2) {
    return v1 = v1 * v2;
}

//--- divide assign ---

template <typename T>
inline vec2<T> & operator/=(vec2<T> & v1, const vec2<T> & v2) {
    return v1 = v1 / v2;
}

template <typename T>
inline vec2<T> & operator/=(vec2<T> & v1, const T & v2) {
    return v1 = v1 / v2;
}

template <typename T>
inline vec2<T> & operator/=(vec2<T> & v1, const vec1<T> & v2) {
    return v1 = v1 / v2;
}

template <typename T>
inline vec2<T> & operator/=(vec2<T> & v1, const vec3<T> & v2) {
    return v1 = v1 / v2;
}

template <typename T>
inline vec2<T> & operator/=(vec2<T> & v1, const vec4<T> & v2) {
    return v1 = v1 / v2;
}

//--- pre increment ---

template <typename T>
inline vec2<T> & operator++(vec2<T> & v) {
    ++v.x; ++v.y;
    return v;
}

//--- post increment ---

template <typename T>
inline vec2<T> operator++(vec2<T> & v, int) {
    return vec2<T>(v.x++, v.y++);
}

//--- pre decrement ---

template <typename T>
inline vec2<T> & operator--(vec2<T> & v) {
    --v.x; --v.y;
    return v;
}

//--- post decrement ---

template <typename T>
inline vec2<T> operator--(vec2<T> & v, int) {
    return vec2<T>(v.x--, v.y--);
}

//--- positive ---

template <typename T>
inline vec2<T> operator+(const vec2<T> & v) {
    return v;
}

//--- negative ---

template <typename T>
inline vec2<T> operator-(const vec2<T> & v) {
    return v * static_cast<T>(-1);
}

//--- add ---

template <typename T>
inline vec2<T> operator+(const vec2<T> & v1, const vec2<T> & v2) {
    return vec2<T>(v1.x + v2.x, v1.y + v2.y);
}

template <typename T>
inline vec2<T> operator+(const vec2<T> & v1, const T & v2) {
    return vec2<T>(v1.x + v2, v1.y + v2);
}

template <typename T>
inline vec2<T> operator+(const T & v1, const vec2<T> & v2) {
    return vec2<T>(v1 + v2.x, v1 + v2.y);
}

template <typename T>
inline vec2<T> operator+(const vec2<T> & v1, const vec1<T> & v2) {
    return vec2<T>(v1.x + v2.x, v1.y);
}

template <typename T>
inline vec2<T> operator+(const vec1<T> & v1, const vec2<T> & v2) {
    return vec2<T>(v1.x + v2.x, v2.y);
}

//--- subtract ---

template <typename T>
inline vec2<T> operator-(const vec2<T> & v1, const vec2<T> & v2) {
    return vec2<T>(v1.x - v2.x, v1.y - v2.y);
}

template <typename T>
inline vec2<T> operator-(const vec2<T> & v1, const T & v2) {
    return vec2<T>(v1.x - v2, v1.y - v2);
}

template <typename T>
inline vec2<T> operator-(const T & v1, const vec2<T> & v2) {
    return vec2<T>(v1 - v2.x, v1 - v2.y);
}

template <typename T>
inline vec2<T> operator-(const vec2<T> & v1, const vec1<T> & v2) {
    return vec2<T>(v1.x - v2.x, v1.y);
}

template <typename T>
inline vec2<T> operator-(const vec1<T> & v1, const vec2<T> & v2) {
    return vec2<T>(v1.x - v2.x, v2.y);
}

//--- multiply ---

template <typename T>
inline vec2<T> operator*(const vec2<T> & v1, const vec2<T> & v2) {
    return vec2<T>(v1.x * v2.x, v1.y * v2.y);
}

template <typename T>
inline vec2<T> operator*(const vec2<T> & v1, const T & v2) {
    return vec2<T>(v1.x * v2, v1.y * v2);
}

template <typename T>
inline vec2<T> operator*(const T & v1, const vec2<T> & v2) {
    return vec2<T>(v1 * v2.x, v1 * v2.y);
}

template <typename T>
inline vec2<T> operator*(const vec2<T> & v1, const vec1<T> & v2) {
    return vec2<T>(v1.x * v2.x, v1.y);
}

template <typename T>
inline vec2<T> operator*(const vec1<T> & v1, const vec2<T> & v2) {
    return vec2<T>(v1.x * v2.x, v2.y);
}

//--- divide ---

template <typename T>
inline vec2<T> operator/(const vec2<T> & v1, const vec2<T> & v2) {
    return vec2<T>(v1.x / v2.x, v1.y / v2.y);
}

template <typename T>
inline vec2<T> operator/(const vec2<T> & v1, const T & v2) {
    return vec2<T>(v1.x / v2, v1.y / v2);
}

template <typename T>
inline vec2<T> operator/(const T & v1, const vec2<T> & v2) {
    return vec2<T>(v1 / v2.x, v1 / v2.y);
}

template <typename T>
inline vec2<T> operator/(const vec2<T> & v1, const vec1<T> & v2) {
    return vec2<T>(v1.x / v2.x, v1.y);
}

template <typename T>
inline vec2<T> operator/(const vec1<T> & v1, const vec2<T> & v2) {
    return vec2<T>(v1.x / v2.x, v2.y);
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T>
inline bool operator==(const vec2<T> & v1, const vec2<T> & v2) {
    return v1.x == v2.x && v1.y == v2.y;
}

template <typename T>
inline bvec2 operator==(const vec2<T> & v1, const T & v2) {
    return bvec2(v1.x == v2, v1.y == v2);
}

template <typename T>
inline bvec2 operator==(const T & v1, const vec2<T> & v2) {
    return bvec2(v1 == v2.x, v1 == v2.y);
}

//--- not equal to ---

template <typename T>
inline bool operator!=(const vec2<T> & v1, const vec2<T> & v2) {
    return v1.x != v2.x || v1.y != v2.y;
}

template <typename T>
inline bvec2 operator!=(const vec2<T> & v1, const T & v2) {
    return bvec2(v1.x != v2, v1.y != v2);
}

template <typename T>
inline bvec2 operator!=(const T & v1, const vec2<T> & v2) {
    return bvec2(v1 != v2.x, v1 != v2.y);
}

//--- less than ---

template <typename T>
inline bvec2 operator<(const vec2<T> & v1, const T & v2) {
    return bvec2(v1.x < v2, v1.y < v2);
}

template <typename T>
inline bvec2 operator<(const T & v1, const vec2<T> & v2) {
    return bvec2(v1 < v2.x, v1 < v2.y);
}

//--- greater than ---

template <typename T>
inline bvec2 operator>(const vec2<T> & v1, const T & v2) {
    return bvec2(v1.x > v2, v1.y > v2);
}

template <typename T>
inline bvec2 operator>(const T & v1, const vec2<T> & v2) {
    return bvec2(v1 > v2.x, v1 > v2.y);
}

//--- less than or equal to ---

template <typename T>
inline bvec2 operator<=(const vec2<T> & v1, const T & v2) {
    return bvec2(v1.x <= v2, v1.y <= v2);
}

template <typename T>
inline bvec2 operator<=(const T & v1, const vec2<T> & v2) {
    return bvec2(v1 <= v2.x, v1 <= v2.y);
}

//--- greater than or equal to ---

template <typename T>
inline bvec2 operator>=(const vec2<T> & v1, const T & v2) {
    return bvec2(v1.x >= v2, v1.y >= v2);
}

template <typename T>
inline bvec2 operator>=(const T & v1, const vec2<T> & v2) {
    return bvec2(v1 >= v2.x, v1 >= v2.y);
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string vec<T, 2>::toString() const {
    std::stringstream ss;
    ss << "(" << x << ", " << y << ")";
    return ss.str();
}



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const vec2<T> & v) {
    return os << v.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC3 IMPLEMENTATION -------------------------------------------------------------------------------------------------



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
constexpr vec<T, 3>::vec(const vec3<U> & v) :
    x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z))
{}

template <typename T>
constexpr vec<T, 3>::vec(const T & v) :
    x(v), y(v), z(v)
{}

template <typename T>
constexpr vec<T, 3>::vec(const vec1<T> & v) :
    x(v.x), y(static_cast<T>(0)), z(static_cast<T>(0))
{}

template <typename T>
constexpr vec<T, 3>::vec(const vec2<T> & v) :
    x(v.x), y(v.y), z(static_cast<T>(0))
{}

template <typename T>
constexpr vec<T, 3>::vec(const vec4<T> & v) :
    x(v.x), y(v.y), z(v.z)
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
// Assignment Operators



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
// Access Operators



template <typename T>
inline T & vec<T, 3>::operator[](nat i) {
    return *(&x + i);
}



template <typename T>
inline const T & vec<T, 3>::operator[](nat i) const {
    return *(&x + i);
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- add assign ---

template <typename T>
inline vec3<T> & operator+=(vec3<T> & v1, const vec3<T> & v2) {
    return v1 = v1 + v2;
}

template <typename T>
inline vec3<T> & operator+=(vec3<T> & v1, const T & v2) {
    return v1 = v1 + v2;
}

template <typename T>
inline vec3<T> & operator+=(vec3<T> & v1, const vec1<T> & v2) {
    return v1 = v1 + v2;
}

template <typename T>
inline vec3<T> & operator+=(vec3<T> & v1, const vec2<T> & v2) {
    return v1 = v1 + v2;
}

template <typename T>
inline vec3<T> & operator+=(vec3<T> & v1, const vec4<T> & v2) {
    return v1 = v1 + v2;
}

//--- subtract assign ---

template <typename T>
inline vec3<T> & operator-=(vec3<T> & v1, const vec3<T> & v2) {
    return v1 = v1 - v2;
}

template <typename T>
inline vec3<T> & operator-=(vec3<T> & v1, const T & v2) {
    return v1 = v1 - v2;
}

template <typename T>
inline vec3<T> & operator-=(vec3<T> & v1, const vec1<T> & v2) {
    return v1 = v1 - v2;
}

template <typename T>
inline vec3<T> & operator-=(vec3<T> & v1, const vec2<T> & v2) {
    return v1 = v1 - v2;
}

template <typename T>
inline vec3<T> & operator-=(vec3<T> & v1, const vec4<T> & v2) {
    return v1 = v1 - v2;
}

//--- multiply assign ---

template <typename T>
inline vec3<T> & operator*=(vec3<T> & v1, const vec3<T> & v2) {
    return v1 = v1 * v2;
}

template <typename T>
inline vec3<T> & operator*=(vec3<T> & v1, const T & v2) {
    return v1 = v1 * v2;
}

template <typename T>
inline vec3<T> & operator*=(vec3<T> & v1, const vec1<T> & v2) {
    return v1 = v1 * v2;
}

template <typename T>
inline vec3<T> & operator*=(vec3<T> & v1, const vec2<T> & v2) {
    return v1 = v1 * v2;
}

template <typename T>
inline vec3<T> & operator*=(vec3<T> & v1, const vec4<T> & v2) {
    return v1 = v1 * v2;
}

//--- divide assign ---

template <typename T>
inline vec3<T> & operator/=(vec3<T> & v1, const vec3<T> & v2) {
    return v1 = v1 / v2;
}

template <typename T>
inline vec3<T> & operator/=(vec3<T> & v1, const T & v2) {
    return v1 = v1 / v2;
}

template <typename T>
inline vec3<T> & operator/=(vec3<T> & v1, const vec1<T> & v2) {
    return v1 = v1 / v2;
}

template <typename T>
inline vec3<T> & operator/=(vec3<T> & v1, const vec2<T> & v2) {
    return v1 = v1 / v2;
}

template <typename T>
inline vec3<T> & operator/=(vec3<T> & v1, const vec4<T> & v2) {
    return v1 = v1 / v2;
}

//--- pre increment ---

template <typename T>
inline vec3<T> & operator++(vec3<T> & v) {
    ++v.x; ++v.y; ++v.z;
    return v;
}

//--- post increment ---

template <typename T>
inline vec3<T> operator++(vec3<T> & v, int) {
    return vec3<T>(v.x++, v.y++, v.z++);
}

//--- pre decrement ---

template <typename T>
inline vec3<T> & operator--(vec3<T> & v) {
    --v.x; --v.y; --v.z;
    return v;
}

//--- post decrement ---

template <typename T>
inline vec3<T> operator--(vec3<T> & v, int) {
    return vec3<T>(v.x--, v.y--, v.z--);
}

//--- positive ---

template <typename T>
inline vec3<T> operator+(const vec3<T> & v) {
    return v;
}

//--- negative ---

template <typename T>
inline vec3<T> operator-(const vec3<T> & v) {
    return v * static_cast<T>(-1);
}

//--- add ---

template <typename T>
inline vec3<T> operator+(const vec3<T> & v1, const vec3<T> & v2) {
    return vec3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

template <typename T>
inline vec3<T> operator+(const vec3<T> & v1, const T & v2) {
    return vec3<T>(v1.x + v2, v1.y + v2, v1.z + v2);
}

template <typename T>
inline vec3<T> operator+(const T & v1, const vec3<T> & v2) {
    return vec3<T>(v1 + v2.x, v1 + v2.y, v1 + v2.z);
}

template <typename T>
inline vec3<T> operator+(const vec3<T> & v1, const vec1<T> & v2) {
    return vec3<T>(v1.x + v2.x, v1.y, v1.z);
}

template <typename T>
inline vec3<T> operator+(const vec1<T> & v1, const vec3<T> & v2) {
    return vec3<T>(v1.x + v2.x, v2.y, v2.z);
}

template <typename T>
inline vec3<T> operator+(const vec3<T> & v1, const vec2<T> & v2) {
    return vec3<T>(v1.x + v2.x, v1.y + v2.y, v1.z);
}

template <typename T>
inline vec3<T> operator+(const vec2<T> & v1, const vec3<T> & v2) {
    return vec3<T>(v1.x + v2.x, v1.y + v2.y, v2.z);
}

//--- subtract ---

template <typename T>
inline vec3<T> operator-(const vec3<T> & v1, const vec3<T> & v2) {
    return vec3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

template <typename T>
inline vec3<T> operator-(const vec3<T> & v1, const T & v2) {
    return vec3<T>(v1.x - v2, v1.y - v2, v1.z - v2);
}

template <typename T>
inline vec3<T> operator-(const T & v1, const vec3<T> & v2) {
    return vec3<T>(v1 - v2.x, v1 - v2.y, v1 - v2.z);
}

template <typename T>
inline vec3<T> operator-(const vec3<T> & v1, const vec1<T> & v2) {
    return vec3<T>(v1.x - v2.x, v1.y, v1.z);
}

template <typename T>
inline vec3<T> operator-(const vec1<T> & v1, const vec3<T> & v2) {
    return vec3<T>(v1.x - v2.x, v2.y, v2.z);
}

template <typename T>
inline vec3<T> operator-(const vec3<T> & v1, const vec2<T> & v2) {
    return vec3<T>(v1.x - v2.x, v1.y - v2.y, v1.z);
}

template <typename T>
inline vec3<T> operator-(const vec2<T> & v1, const vec3<T> & v2) {
    return vec3<T>(v1.x - v2.x, v1.y - v2.y, v2.z);
}

//--- multiply ---

template <typename T>
inline vec3<T> operator*(const vec3<T> & v1, const vec3<T> & v2) {
    return vec3<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

template <typename T>
inline vec3<T> operator*(const vec3<T> & v1, const T & v2) {
    return vec3<T>(v1.x * v2, v1.y * v2, v1.z * v2);
}

template <typename T>
inline vec3<T> operator*(const T & v1, const vec3<T> & v2) {
    return vec3<T>(v1 * v2.x, v1 * v2.y, v1 * v2.z);
}

template <typename T>
inline vec3<T> operator*(const vec3<T> & v1, const vec1<T> & v2) {
    return vec3<T>(v1.x * v2.x, v1.y, v1.z);
}

template <typename T>
inline vec3<T> operator*(const vec1<T> & v1, const vec3<T> & v2) {
    return vec3<T>(v1.x * v2.x, v2.y, v2.z);
}

template <typename T>
inline vec3<T> operator*(const vec3<T> & v1, const vec2<T> & v2) {
    return vec3<T>(v1.x * v2.x, v1.y * v2.y, v1.z);
}

template <typename T>
inline vec3<T> operator*(const vec2<T> & v1, const vec3<T> & v2) {
    return vec3<T>(v1.x * v2.x, v1.y * v2.y, v2.z);
}

//--- divide ---

template <typename T>
inline vec3<T> operator/(const vec3<T> & v1, const vec3<T> & v2) {
    return vec3<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

template <typename T>
inline vec3<T> operator/(const vec3<T> & v1, const T & v2) {
    return vec3<T>(v1.x / v2, v1.y / v2, v1.z / v2);
}

template <typename T>
inline vec3<T> operator/(const T & v1, const vec3<T> & v2) {
    return vec3<T>(v1 / v2.x, v1 / v2.y, v1 / v2.z);
}

template <typename T>
inline vec3<T> operator/(const vec3<T> & v1, const vec1<T> & v2) {
    return vec3<T>(v1.x / v2.x, v1.y, v1.z);
}

template <typename T>
inline vec3<T> operator/(const vec1<T> & v1, const vec3<T> & v2) {
    return vec3<T>(v1.x / v2.x, v2.y, v2.z);
}

template <typename T>
inline vec3<T> operator/(const vec3<T> & v1, const vec2<T> & v2) {
    return vec3<T>(v1.x / v2.x, v1.y / v2.y, v1.z);
}

template <typename T>
inline vec3<T> operator/(const vec2<T> & v1, const vec3<T> & v2) {
    return vec3<T>(v1.x / v2.x, v1.y / v2.y, v2.z);
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T>
inline bool operator==(const vec3<T> & v1, const vec3<T> & v2) {
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

template <typename T>
inline bvec3 operator==(const vec3<T> & v1, const T & v2) {
    return bvec3(v1.x == v2, v1.y == v2, v1.z == v2);
}

template <typename T>
inline bvec3 operator==(const T & v1, const vec3<T> & v2) {
    return bvec3(v1 == v2.x, v1 == v2.y, v1 == v2.z);
}

//--- not equal to ---

template <typename T>
inline bool operator!=(const vec3<T> & v1, const vec3<T> & v2) {
    return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z;
}

template <typename T>
inline bvec3 operator!=(const vec3<T> & v1, const T & v2) {
    return bvec3(v1.x != v2, v1.y != v2, v1.z != v2);
}

template <typename T>
inline bvec3 operator!=(const T & v1, const vec3<T> & v2) {
    return bvec3(v1 != v2.x, v1 != v2.y, v1 != v2.z);
}

//--- less than ---

template <typename T>
inline bvec3 operator<(const vec3<T> & v1, const T & v2) {
    return bvec3(v1.x < v2, v1.y < v2, v1.z < v2);
}

template <typename T>
inline bvec3 operator<(const T & v1, const vec3<T> & v2) {
    return bvec3(v1 < v2.x, v1 < v2.y, v1 < v2.z);
}

//--- greater than ---

template <typename T>
inline bvec3 operator>(const vec3<T> & v1, const T & v2) {
    return bvec3(v1.x > v2, v1.y > v2, v1.z > v2);
}

template <typename T>
inline bvec3 operator>(const T & v1, const vec3<T> & v2) {
    return bvec3(v1 > v2.x, v1 > v2.y, v1 > v2.z);
}

//--- less than or equal to ---

template <typename T>
inline bvec3 operator<=(const vec3<T> & v1, const T & v2) {
    return bvec3(v1.x <= v2, v1.y <= v2, v1.z <= v2);
}

template <typename T>
inline bvec3 operator<=(const T & v1, const vec3<T> & v2) {
    return bvec3(v1 <= v2.x, v1 <= v2.y, v1 <= v2.z);
}

//--- greater than or equal to ---

template <typename T>
inline bvec3 operator>=(const vec3<T> & v1, const T & v2) {
    return bvec3(v1.x >= v2, v1.y >= v2, v1.z >= v2);
}

template <typename T>
inline bvec3 operator>=(const T & v1, const vec3<T> & v2) {
    return bvec3(v1 >= v2.x, v1 >= v2.y, v1 >= v2.z);
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string vec<T, 3>::toString() const {
    std::stringstream ss;
    ss << "(" << x << ", " << y << ", " << z << ")";
    return ss.str();
}



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const vec3<T> & v) {
    return os << v.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC4 IMPLEMENTATION -------------------------------------------------------------------------------------------------



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
constexpr vec<T, 4>::vec(const vec4<U> & v) :
    x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z)), w(static_cast<T>(v.w))
{}

template <typename T>
constexpr vec<T, 4>::vec(const T & v) :
    x(v), y(v), z(v), w(v)
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec1<T> & v) :
    x(v.x), y(static_cast<T>(0)), z(static_cast<T>(0)), w(static_cast<T>(0))
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec2<T> & v) :
    x(v.x), y(v.y), z(static_cast<T>(0)), w(static_cast<T>(0))
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec3<T> & v) :
    x(v.x), y(v.y), z(v.z), w(static_cast<T>(0))
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
// Assignment Operators



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
// Access Operators



template <typename T>
inline T & vec<T, 4>::operator[](nat i) {
    return *(&x + i);
}



template <typename T>
inline const T & vec<T, 4>::operator[](nat i) const {
    return *(&x + i);
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- add assign ---

template <typename T>
inline vec4<T> & operator+=(vec4<T> & v1, const vec4<T> & v2) {
    return v1 = v1 + v2;
}

template <typename T>
inline vec4<T> & operator+=(vec4<T> & v1, const T & v2) {
    return v1 = v1 + v2;
}

template <typename T>
inline vec4<T> & operator+=(vec4<T> & v1, const vec1<T> & v2) {
    return v1 = v1 + v2;
}

template <typename T>
inline vec4<T> & operator+=(vec4<T> & v1, const vec2<T> & v2) {
    return v1 = v1 + v2;
}

template <typename T>
inline vec4<T> & operator+=(vec4<T> & v1, const vec3<T> & v2) {
    return v1 = v1 + v2;
}

//--- subtract assign ---

template <typename T>
inline vec4<T> & operator-=(vec4<T> & v1, const vec4<T> & v2) {
    return v1 = v1 - v2;
}

template <typename T>
inline vec4<T> & operator-=(vec4<T> & v1, const T & v2) {
    return v1 = v1 - v2;
}

template <typename T>
inline vec4<T> & operator-=(vec4<T> & v1, const vec1<T> & v2) {
    return v1 = v1 - v2;
}

template <typename T>
inline vec4<T> & operator-=(vec4<T> & v1, const vec2<T> & v2) {
    return v1 = v1 - v2;
}

template <typename T>
inline vec4<T> & operator-=(vec4<T> & v1, const vec3<T> & v2) {
    return v1 = v1 - v2;
}

//--- multiply assign ---

template <typename T>
inline vec4<T> & operator*=(vec4<T> & v1, const vec4<T> & v2) {
    return v1 = v1 * v2;
}

template <typename T>
inline vec4<T> & operator*=(vec4<T> & v1, const T & v2) {
    return v1 = v1 * v2;
}

template <typename T>
inline vec4<T> & operator*=(vec4<T> & v1, const vec1<T> & v2) {
    return v1 = v1 * v2;
}

template <typename T>
inline vec4<T> & operator*=(vec4<T> & v1, const vec2<T> & v2) {
    return v1 = v1 * v2;
}

template <typename T>
inline vec4<T> & operator*=(vec4<T> & v1, const vec3<T> & v2) {
    return v1 = v1 * v2;
}

//--- divide assign ---

template <typename T>
inline vec4<T> & operator/=(vec4<T> & v1, const vec4<T> & v2) {
    return v1 = v1 / v2;
}

template <typename T>
inline vec4<T> & operator/=(vec4<T> & v1, const T & v2) {
    return v1 = v1 / v2;
}

template <typename T>
inline vec4<T> & operator/=(vec4<T> & v1, const vec1<T> & v2) {
    return v1 = v1 / v2;
}

template <typename T>
inline vec4<T> & operator/=(vec4<T> & v1, const vec2<T> & v2) {
    return v1 = v1 / v2;
}

template <typename T>
inline vec4<T> & operator/=(vec4<T> & v1, const vec3<T> & v2) {
    return v1 = v1 / v2;
}

//--- pre increment ---

template <typename T>
inline vec4<T> & operator++(vec4<T> & v) {
    ++v.x; ++v.y; ++v.z; ++v.w;
    return v;
}

//--- post increment ---

template <typename T>
inline vec4<T> operator++(vec4<T> & v, int) {
    return vec4<T>(v.x++, v.y++, v.z++, v.w++);
}

//--- pre decrement ---

template <typename T>
inline vec4<T> & operator--(vec4<T> & v) {
    --v.x; --v.y; --v.z; --v.w;
    return v;
}

//--- post decrement ---

template <typename T>
inline vec4<T> operator--(vec4<T> & v, int) {
    return vec4<T>(v.x--, v.y--, v.z--, v.w--);
}

//--- positive ---

template <typename T>
inline vec4<T> operator+(const vec4<T> & v) {
    return v;
}

//--- negative ---

template <typename T>
inline vec4<T> operator-(const vec4<T> & v) {
    return v * static_cast<T>(-1);
}

//--- add ---

template <typename T>
inline vec4<T> operator+(const vec4<T> & v1, const vec4<T> & v2) {
    return vec4<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

template <typename T>
inline vec4<T> operator+(const vec4<T> & v1, const T & v2) {
    return vec4<T>(v1.x + v2, v1.y + v2, v1.z + v2, v1.w + v2);
}

template <typename T>
inline vec4<T> operator+(const T & v1, const vec4<T> & v2) {
    return vec4<T>(v1 + v2.x, v1 + v2.y, v1 + v2.z, v1 + v2.w);
}

template <typename T>
inline vec4<T> operator+(const vec4<T> & v1, const vec1<T> & v2) {
    return vec4<T>(v1.x + v2.x, v1.y, v1.z, v1.w);
}

template <typename T>
inline vec4<T> operator+(const vec1<T> & v1, const vec4<T> & v2) {
    return vec4<T>(v1.x + v2.x, v2.y, v2.z, v2.w);
}

template <typename T>
inline vec4<T> operator+(const vec4<T> & v1, const vec2<T> & v2) {
    return vec4<T>(v1.x + v2.x, v1.y + v2.y, v1.z, v1.w);
}

template <typename T>
inline vec4<T> operator+(const vec2<T> & v1, const vec4<T> & v2) {
    return vec4<T>(v1.x + v2.x, v1.y + v2.y, v2.z, v2.w);
}

template <typename T>
inline vec4<T> operator+(const vec4<T> & v1, const vec3<T> & v2) {
    return vec4<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w);
}

template <typename T>
inline vec4<T> operator+(const vec3<T> & v1, const vec4<T> & v2) {
    return vec4<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v2.w);
}

//--- subtract ---

template <typename T>
inline vec4<T> operator-(const vec4<T> & v1, const vec4<T> & v2) {
    return vec4<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

template <typename T>
inline vec4<T> operator-(const vec4<T> & v1, const T & v2) {
    return vec4<T>(v1.x - v2, v1.y - v2, v1.z - v2, v1.w - v2);
}

template <typename T>
inline vec4<T> operator-(const T & v1, const vec4<T> & v2) {
    return vec4<T>(v1 - v2.x, v1 - v2.y, v1 - v2.z, v1 - v2.w);
}

template <typename T>
inline vec4<T> operator-(const vec4<T> & v1, const vec1<T> & v2) {
    return vec4<T>(v1.x - v2.x, v1.y, v1.z, v1.w);
}

template <typename T>
inline vec4<T> operator-(const vec1<T> & v1, const vec4<T> & v2) {
    return vec4<T>(v1.x - v2.x, v2.y, v2.z, v2.w);
}

template <typename T>
inline vec4<T> operator-(const vec4<T> & v1, const vec2<T> & v2) {
    return vec4<T>(v1.x - v2.x, v1.y - v2.y, v1.z, v1.w);
}

template <typename T>
inline vec4<T> operator-(const vec2<T> & v1, const vec4<T> & v2) {
    return vec4<T>(v1.x - v2.x, v1.y - v2.y, v2.z, v2.w);
}

template <typename T>
inline vec4<T> operator-(const vec4<T> & v1, const vec3<T> & v2) {
    return vec4<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w);
}

template <typename T>
inline vec4<T> operator-(const vec3<T> & v1, const vec4<T> & v2) {
    return vec4<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v2.w);
}

//--- multiply ---

template <typename T>
inline vec4<T> operator*(const vec4<T> & v1, const vec4<T> & v2) {
    return vec4<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

template <typename T>
inline vec4<T> operator*(const vec4<T> & v1, const T & v2) {
    return vec4<T>(v1.x * v2, v1.y * v2, v1.z * v2, v1.w * v2);
}

template <typename T>
inline vec4<T> operator*(const T & v1, const vec4<T> & v2) {
    return vec4<T>(v1 * v2.x, v1 * v2.y, v1 * v2.z, v1 * v2.w);
}

template <typename T>
inline vec4<T> operator*(const vec4<T> & v1, const vec1<T> & v2) {
    return vec4<T>(v1.x * v2.x, v1.y, v1.z, v1.w);
}

template <typename T>
inline vec4<T> operator*(const vec1<T> & v1, const vec4<T> & v2) {
    return vec4<T>(v1.x * v2.x, v2.y, v2.z, v2.w);
}

template <typename T>
inline vec4<T> operator*(const vec4<T> & v1, const vec2<T> & v2) {
    return vec4<T>(v1.x * v2.x, v1.y * v2.y, v1.z, v1.w);
}

template <typename T>
inline vec4<T> operator*(const vec2<T> & v1, const vec4<T> & v2) {
    return vec4<T>(v1.x * v2.x, v1.y * v2.y, v2.z, v2.w);
}

template <typename T>
inline vec4<T> operator*(const vec4<T> & v1, const vec3<T> & v2) {
    return vec4<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w);
}

template <typename T>
inline vec4<T> operator*(const vec3<T> & v1, const vec4<T> & v2) {
    return vec4<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v2.w);
}

//--- divide ---

template <typename T>
inline vec4<T> operator/(const vec4<T> & v1, const vec4<T> & v2) {
    return vec4<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
}

template <typename T>
inline vec4<T> operator/(const vec4<T> & v1, const T & v2) {
    return vec4<T>(v1.x / v2, v1.y / v2, v1.z / v2, v1.w / v2);
}

template <typename T>
inline vec4<T> operator/(const T & v1, const vec4<T> & v2) {
    return vec4<T>(v1 / v2.x, v1 / v2.y, v1 / v2.z, v1 / v2.w);
}

template <typename T>
inline vec4<T> operator/(const vec4<T> & v1, const vec1<T> & v2) {
    return vec4<T>(v1.x / v2.x, v1.y, v1.z, v1.w);
}

template <typename T>
inline vec4<T> operator/(const vec1<T> & v1, const vec4<T> & v2) {
    return vec4<T>(v1.x / v2.x, v2.y, v2.z, v2.w);
}

template <typename T>
inline vec4<T> operator/(const vec4<T> & v1, const vec2<T> & v2) {
    return vec4<T>(v1.x / v2.x, v1.y / v2.y, v1.z, v1.w);
}

template <typename T>
inline vec4<T> operator/(const vec2<T> & v1, const vec4<T> & v2) {
    return vec4<T>(v1.x / v2.x, v1.y / v2.y, v2.z, v2.w);
}

template <typename T>
inline vec4<T> operator/(const vec4<T> & v1, const vec3<T> & v2) {
    return vec4<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w);
}

template <typename T>
inline vec4<T> operator/(const vec3<T> & v1, const vec4<T> & v2) {
    return vec4<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v2.w);
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T>
inline bool operator==(const vec4<T> & v1, const vec4<T> & v2) {
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
}

template <typename T>
inline bvec4 operator==(const vec4<T> & v1, const T & v2) {
    return bvec4(v1.x == v2, v1.y == v2, v1.z == v2, v1.w == v2);
}

template <typename T>
inline bvec4 operator==(const T & v1, const vec4<T> & v2) {
    return bvec4(v1 == v2.x, v1 == v2.y, v1 == v2.z, v1 == v2.w);
}

//--- not equal to ---

template <typename T>
inline bool operator!=(const vec4<T> & v1, const vec4<T> & v2) {
    return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z || v1.w != v2.w;
}

template <typename T>
inline bvec4 operator!=(const vec4<T> & v1, const T & v2) {
    return bvec4(v1.x != v2, v1.y != v2, v1.z != v2, v1.w != v2);
}

template <typename T>
inline bvec4 operator!=(const T & v1, const vec4<T> & v2) {
    return bvec4(v1 != v2.x, v1 != v2.y, v1 != v2.z, v1 != v2.w);
}

//--- less than ---

template <typename T>
inline bvec4 operator<(const vec4<T> & v1, const T & v2) {
    return bvec4(v1.x < v2, v1.y < v2, v1.z < v2, v1.w < v2);
}

template <typename T>
inline bvec4 operator<(const T & v1, const vec4<T> & v2) {
    return bvec4(v1 < v2.x, v1 < v2.y, v1 < v2.z, v1 < v2.w);
}

//--- greater than ---

template <typename T>
inline bvec4 operator>(const vec4<T> & v1, const T & v2) {
    return bvec4(v1.x > v2, v1.y > v2, v1.z > v2, v1.w > v2);
}

template <typename T>
inline bvec4 operator>(const T & v1, const vec4<T> & v2) {
    return bvec4(v1 > v2.x, v1 > v2.y, v1 > v2.z, v1 > v2.w);
}

//--- less than or equal to ---

template <typename T>
inline bvec4 operator<=(const vec4<T> & v1, const T & v2) {
    return bvec4(v1.x <= v2, v1.y <= v2, v1.z <= v2, v1.w <= v2);
}

template <typename T>
inline bvec4 operator<=(const T & v1, const vec4<T> & v2) {
    return bvec4(v1 <= v2.x, v1 <= v2.y, v1 <= v2.z, v1 <= v2.w);
}

//--- greater than or equal to ---

template <typename T>
inline bvec4 operator>=(const vec4<T> & v1, const T & v2) {
    return bvec4(v1.x >= v2, v1.y >= v2, v1.z >= v2, v1.w >= v2);
}

template <typename T>
inline bvec4 operator>=(const T & v1, const vec4<T> & v2) {
    return bvec4(v1 >= v2.x, v1 >= v2.y, v1 >= v2.z, v1 >= v2.w);
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string vec<T, 4>::toString() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + ")";
}



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const vec4<T> & v) {
    return os << v.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC6 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr vec<T, 6>::vec() :
    min(), max()
{}

template <typename T>
constexpr vec<T, 6>::vec(const vec<T, 6> & v) :
    min(v.min), max(v.max)
{}

template <typename T>
constexpr vec<T, 6>::vec(vec<T, 6> && v) :
    min(v.min), max(v.max)
{}

template <typename T>
template <typename U>
constexpr vec<T, 6>::vec(const vec<U, 6> & v) :
    min(v.min), max(v.max)
{}

template <typename T>
constexpr vec<T, 6>::vec(const vec3<T> & v1, const vec3<T> & v2) :
    min(v1), max(v2)
{}

template <typename T>
constexpr vec<T, 6>::vec(const T & v1, const T & v2, const T & v3, const T & v4, const T & v5, const T & v6) :
    min(v1, v2, v3), max(v4, v5, v6)
{}



//------------------------------------------------------------------------------
// Assignment Operators



template <typename T>
inline vec<T, 6> & vec<T, 6>::operator=(const vec<T, 6> & v) {
    min = v.min; max = v.max;
    return *this;
}

template <typename T>
inline vec<T, 6> & vec<T, 6>::operator=(vec<T, 6> && v) {
    min = v.min; max = v.max;
    return *this;
}



//------------------------------------------------------------------------------
// Access Operators



template <typename T>
inline T & vec<T, 6>::operator[](nat i) {
    return *(&min.x + i);
}



template <typename T>
inline const T & vec<T, 6>::operator[](nat i) const {
    return *(&min.x + i);
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T>
inline bool operator==(const vec<T, 6> & v1, const vec<T, 6> & v2) {
    return v1.min == v2.min && v1.max == v2.max;
}

//--- not equal to ---

template <typename T>
inline bool operator!=(const vec<T, 6> & v1, const vec<T, 6> & v2) {
    return v1.min != v2.min || v1.max != v2.max;
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string vec<T, 6>::toString() const {
    std::stringstream ss;
    ss << "(" << min.x << ", " << min.y << ", " << min.z << ", " << max.x << ", " << max.y << ", " << max.z << ")";
    return ss.str();
}



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const vec<T, 6> & v) {
    return os << v.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC8 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr vec<T, 8>::vec() :
    min(), max()
{}

template <typename T>
constexpr vec<T, 8>::vec(const vec<T, 8> & v) :
    min(v.min), max(v.max)
{}

template <typename T>
constexpr vec<T, 8>::vec(vec<T, 8> && v) :
    min(v.min), max(v.max)
{}

template <typename T>
template <typename U>
constexpr vec<T, 8>::vec(const vec<U, 8> & v) :
    min(v.min), max(v.max)
{}

template <typename T>
constexpr vec<T, 8>::vec(const vec4<T> & v1, const vec4<T> & v2) :
    min(v1), max(v2)
{}

template <typename T>
constexpr vec<T, 8>::vec(const T & v1, const T & v2, const T & v3, const T & v4, const T & v5, const T & v6, const T & v7, const T & v8) :
    min(v1, v2, v3, v4), max(v5, v6, v7, v8)
{}



//------------------------------------------------------------------------------
// Assignment Operators



template <typename T>
inline vec<T, 8> & vec<T, 8>::operator=(const vec<T, 8> & v) {
    min = v.min; max = v.max;
    return *this;
}

template <typename T>
inline vec<T, 8> & vec<T, 8>::operator=(vec<T, 8> && v) {
    min = v.min; max = v.max;
    return *this;
}



//------------------------------------------------------------------------------
// Access Operators



template <typename T>
inline T & vec<T, 8>::operator[](nat i) {
    return *(&min.x + i);
}



template <typename T>
inline const T & vec<T, 8>::operator[](nat i) const {
    return *(&min.x + i);
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T>
inline bool operator==(const vec<T, 8> & v1, const vec<T, 8> & v2) {
    return v1.min == v2.min && v1.max == v2.max;
}

//--- not equal to ---

template <typename T>
inline bool operator!=(const vec<T, 8> & v1, const vec<T, 8> & v2) {
    return v1.min != v2.min || v1.max != v2.max;
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string vec<T, 8>::toString() const {
    std::stringstream ss;
    ss << "(" << min.x << ", " << min.y << ", " << min.z << ", " << min.w << ", " << max.x << ", " << max.y << ", " << max.z << ", " << max.w << ")";
    return ss.str();
}



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const vec<T, 8> & v) {
    return os << v.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC FUNCTIONS IMPLEMENTATION ----------------------------------------------------------------------------------------



template <typename T, nat t_n, enable_if_floating_t<T>>
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

template <typename T, nat t_n, enable_if_floating_t<T>>
inline vec<T, t_n> normalize(const vec<T, t_n> & v) {
    T m(magnitude(v));
    if (abs(m) < std::numeric_limits<T>::min()) {
        return vec<T, t_n>();
    }
    return v / m;
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

template <typename T, nat t_n, enable_if_floating_t<T>>
inline vec<T, t_n> reflect(const vec<T, t_n> & v, const vec<T, t_n> & n) {
    return reflect_n(v, normalize(n));
}

template <typename T, nat t_n, enable_if_floating_t<T>>
inline vec<T, t_n> reflect_n(const vec<T, t_n> & v, const vec<T, t_n> & n) {
    return static_cast<T>(2 * dot(v, n)) * n - v;
}

template <typename T, nat t_n, enable_if_floating_t<T>>
inline T angle(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    return angle_n(normalize(v1), normalize(v2));
}
template <typename T, nat t_n, enable_if_floating_t<T>>
inline T angle_n(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    return static_cast<T>(std::acos(dot(v1, v2)));
}

template <typename T>
inline vec2<T> orthogonal(const vec2<T> & v) {
    return vec2<T>(-v.y, v.x);
}

template <typename T>
inline vec3<T> orthogonal(const vec3<T> & v) {
    if (v.x < v.y) {
        if (v.x < v.z) {
            return vec3<T>(0, -v.z, v.y);
        }
        else {
            return vec3<T>(-v.y, v.x, 0);
        }
    }
    else {
        if (v.y < v.z) {
            return vec3<T>(v.z, 0, -v.x);
        }
        else {
            return vec3<T>(-v.y, v.x, 0);
        }
    }
}

template <typename T>
inline T min(const vec1<T> & v) {
    return v.x;
}

template <typename T>
inline T min(const vec2<T> & v) {
    return min(v.x, v.y);
}

template <typename T>
inline T min(const vec3<T> & v) {
    return min(v.x, v.y, v.z);
}

template <typename T>
inline T min(const vec4<T> & v) {
    return min(v.x, v.y, v.z, v.w);
}

template <typename T>
inline T max(const vec1<T> & v) {
    return v.x;
}

template <typename T>
inline T max(const vec2<T> & v) {
    return max(v.x, v.y);
}

template <typename T>
inline T max(const vec3<T> & v) {
    return max(v.x, v.y, v.z);
}

template <typename T>
inline T max(const vec4<T> & v) {
    return max(v.x, v.y, v.z, v.w);
}

template <typename T>
inline vec1<T> min(const vec1<T> & v1, const vec1<T> & v2) {
    return vec1<T>(min(v1.x, v2.x));
}

template <typename T>
inline vec2<T> min(const vec2<T> & v1, const vec2<T> & v2) {
    return vec2<T>(min(v1.x, v2.x), min(v1.y, v2.y));
}

template <typename T>
inline vec3<T> min(const vec3<T> & v1, const vec3<T> & v2) {
    return vec3<T>(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z));
}

template <typename T>
inline vec4<T> min(const vec4<T> & v1, const vec4<T> & v2) {
    return vec4<T>(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z), min(v1.w, v2.w));
}

template <typename T>
inline vec1<T> max(const vec1<T> & v1, const vec1<T> & v2) {
    return vec1<T>(max(v1.x, v2.x));
}

template <typename T>
inline vec2<T> max(const vec2<T> & v1, const vec2<T> & v2) {
    return vec2<T>(max(v1.x, v2.x), max(v1.y, v2.y));
}

template <typename T>
inline vec3<T> max(const vec3<T> & v1, const vec3<T> & v2) {
    return vec3<T>(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z));
}

template <typename T>
inline vec4<T> max(const vec4<T> & v1, const vec4<T> & v2) {
    return vec4<T>(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z), max(v1.w, v2.w));
}

template <typename T>
inline vec1<T> clamp(const vec1<T> & v, const T & min, const T & max) {
    return vec1<T>(
        clamp(v.x, min, max)
    );
}

template <typename T>
inline vec2<T> clamp(const vec2<T> & v, const T & min, const T & max) {
    return vec2<T>(
        clamp(v.x, min, max),
        clamp(v.y, min, max)
    );
}

template <typename T>
inline vec3<T> clamp(const vec3<T> & v, const T & min, const T & max) {
    return vec3<T>(
        clamp(v.x, min, max),
        clamp(v.y, min, max),
        clamp(v.z, min, max)
    );
}

template <typename T>
inline vec4<T> clamp(const vec4<T> & v, const T & min, const T & max) {
    return vec4<T>(
        clamp(v.x, min, max),
        clamp(v.y, min, max),
        clamp(v.z, min, max),
        clamp(v.w, min, max)
    );
}

template <typename T>
inline vec1<T> clamp(const vec1<T> & v, const vec1<T> & min, const vec1<T> & max) {
    return vec1<T>(
        clamp(v.x, min.x, max.x)
    );
}

template <typename T>
inline vec2<T> clamp(const vec2<T> & v, const vec2<T> & min, const vec2<T> & max) {
    return vec2<T>(
        clamp(v.x, min.x, max.x),
        clamp(v.y, min.y, max.y)
    );
}

template <typename T>
inline vec3<T> clamp(const vec3<T> & v, const vec3<T> & min, const vec3<T> & max) {
    return vec3<T>(
        clamp(v.x, min.x, max.x),
        clamp(v.y, min.y, max.y),
        clamp(v.z, min.z, max.z)
    );
}

template <typename T>
inline vec4<T> clamp(const vec4<T> & v, const vec4<T> & min, const vec4<T> & max) {
    return vec4<T>(
        clamp(v.x, min.x, max.x),
        clamp(v.y, min.y, max.y),
        clamp(v.z, min.z, max.z),
        clamp(v.w, min.w, max.w)
    );
}

template <typename T, nat t_n, enable_if_floating_t<T>>
inline vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, T t) {
    return (static_cast<T>(1) - t) * v1 + t * v2;
}

template <typename T>
inline span1<T> toSpan(const bound1<T> & b) {
    return span1<T>(b.loc, b.loc + b.size);
}

template <typename T>
inline span2<T> toSpan(const bound2<T> & b) {
    return span2<T>(b.loc, b.loc + b.size);
}

template <typename T>
inline span3<T> toSpan(const bound3<T> & b) {
    return span3<T>(b.loc, b.loc + b.size);
}

template <typename T>
inline span4<T> toSpan(const bound4<T> & b) {
    return span4<T>(b.loc, b.loc + b.size);
}

template <typename T>
inline bound1<T> toBound(const span1<T> & s) {
    return bound1<T>(s.min, s.max - s.min);
}

template <typename T>
inline bound2<T> toBound(const span2<T> & s) {
    return bound2<T>(s.min, s.max - s.min);
}

template <typename T>
inline bound3<T> toBound(const span3<T> & s) {
    return bound3<T>(s.min, s.max - s.min);
}

template <typename T>
inline bound4<T> toBound(const span4<T> & s) {
    return bound4<T>(s.min, s.max - s.min);
}

template <typename T>
inline span1<T> intersect(const span1<T> & s1, const span1<T> & s2) {
    return span1<T>(
        max(s1.min.x, s2.min.x),
        min(s1.max.x, s2.max.x)
    );
}

template <typename T>
inline span2<T> intersect(const span2<T> & s1, const span2<T> & s2) {
    return span2<T>(
        max(s1.min.x, s2.min.x),
        max(s1.min.y, s2.min.y),
        min(s1.max.x, s2.max.x),
        min(s1.max.y, s2.max.y)
    );
}

template <typename T>
inline span3<T> intersect(const span3<T> & s1, const span3<T> & s2) {
    return span3<T>(
        max(s1.min.x, s2.min.x),
        max(s1.min.y, s2.min.y),
        max(s1.min.z, s2.min.z),
        min(s1.max.x, s2.max.x),
        min(s1.max.y, s2.max.y),
        min(s1.max.z, s2.max.z)
    );
}

template <typename T>
inline span4<T> intersect(const span4<T> & s1, const span4<T> & s2) {
    return span4<T>(
        max(s1.min.x, s2.min.x),
        max(s1.min.y, s2.min.y),
        max(s1.min.z, s2.min.z),
        max(s1.min.w, s2.min.w),
        min(s1.max.x, s2.max.x),
        min(s1.max.y, s2.max.y),
        min(s1.max.z, s2.max.z),
        min(s1.max.w, s2.max.w)
    );
}




}