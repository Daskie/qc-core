#pragma once



// Column-major ordering
//
//  x1 x2 x3    00 03 06
//  y1 y2 y3    01 04 07
//  z1 z2 z3    02 05 08



#include "Vector.hpp"



namespace qc {



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Type Declarations ---------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Mat



template <typename T, int t_m, int t_n = t_m> struct mat;

template <typename T> using mat2 = mat<T, 2>;
template <typename T> using mat3 = mat<T, 3>;
template <typename T> using mat4 = mat<T, 4>;

template <int t_m, int t_n> using  fmat = mat<      float, t_m, t_n>;
template <int t_m, int t_n> using  dmat = mat<     double, t_m, t_n>;

using  fmat2 = mat<      float, 2>;
using  fmat3 = mat<      float, 3>;
using  fmat4 = mat<      float, 4>;
using  dmat2 = mat<     double, 2>;
using  dmat3 = mat<     double, 3>;
using  dmat4 = mat<     double, 4>;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Type Namespaces -----------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Mat



namespace  tmats { using qc::  mat; using qc::  mat2; using qc::  mat3; using qc::  mat4; }
namespace  fmats { using qc:: fmat; using qc:: fmat2; using qc:: fmat3; using qc:: fmat4; }
namespace  dmats { using qc:: dmat; using qc:: dmat2; using qc:: dmat3; using qc:: dmat4; }

namespace mats {

using namespace  tmats;
using namespace  fmats;
using namespace  dmats;

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT2 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct mat<T, 2, 2> {

    static_assert(std::is_floating_point_v<T>, "mat2<T> must have floating point T");

    using Type = T;
    static constexpr int M = 2, N = 2;

    T x1, y1;
    T x2, y2;

    //--- constructors ---

    constexpr mat();
    constexpr mat(const mat2<T> & m);
    constexpr mat(mat2<T> && m);

    template <typename U> constexpr explicit mat(const mat2<U> & m);

    constexpr mat(
        T x1, T y1,
        T x2, T y2
    );
    constexpr explicit mat(const mat3<T> & m);
    constexpr explicit mat(const mat4<T> & m);
    constexpr mat(
        const vec2<T> & v1,
        const vec2<T> & v2
    );

    //--- assignment ---

    inline mat2<T> & operator=(const mat2<T> & m);
    inline mat2<T> & operator=(mat2<T> && m);

    template <int t_m, int t_n> inline mat2<T> & operator=(const mat<T, t_m, t_n> & m);

    //--- access ---

    inline T & operator[](int i);
    inline T operator[](int i) const;

    template <int t_i, int t_j> inline T & at();
    template <int t_i, int t_j> constexpr T at() const;

    inline vec2<T> col(int i) const;
    inline vec2<T> row(int i) const;

    template <int t_i> constexpr vec2<T> row() const;
    template <int t_j> constexpr vec2<T> col() const;

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT3 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct mat<T, 3, 3> {

    static_assert(std::is_floating_point_v<T>, "mat3<T> must have floating point T");

    using Type = T;
    static constexpr int M = 3, N = 3;

    T x1, y1, z1;
    T x2, y2, z2;
    T x3, y3, z3;

    //--- constructors ---

    constexpr mat();
    constexpr mat(const mat3<T> & m);
    constexpr mat(mat3<T> && m);

    template <typename U> constexpr explicit mat(const mat3<U> & m);

    constexpr mat(
        T x1, T y1, T z1,
        T x2, T y2, T z2,
        T x3, T y3, T z3
    );
    constexpr explicit mat(const mat2<T> & m);
    constexpr explicit mat(const mat4<T> & m);
    constexpr mat(
        const vec3<T> & v1,
        const vec3<T> & v2,
        const vec3<T> & v3
    );

    //--- assignment ---

    inline mat3<T> & operator=(const mat3<T> & m);
    inline mat3<T> & operator=(mat3<T> && m);
    
    template <int t_m, int t_n> inline mat3<T> & operator=(const mat<T, t_m, t_n> & m);

    //--- access ---

    inline T & operator[](int i);
    inline T operator[](int i) const;

    template <int t_i, int t_j> inline T & at();
    template <int t_i, int t_j> constexpr T at() const;

    inline vec3<T> col(int i) const;
    inline vec3<T> row(int i) const;

    template <int t_i> constexpr vec3<T> row() const;
    template <int t_j> constexpr vec3<T> col() const;

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT4 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct mat<T, 4, 4> {

    static_assert(std::is_floating_point_v<T>, "mat4<T> must have floating point T");

    using Type = T;
    static constexpr int M = 4, N = 4;

    T x1, y1, z1, w1;
    T x2, y2, z2, w2;
    T x3, y3, z3, w3;
    T x4, y4, z4, w4;

    //--- constructors ---

    constexpr mat();
    constexpr mat(const mat4<T> & m);
    constexpr mat(mat4<T> && m);

    template <typename U> constexpr explicit mat(const mat4<U> & m);

    constexpr mat(
        T x1, T y1, T z1, T w1,
        T x2, T y2, T z2, T w2,
        T x3, T y3, T z3, T w3,
        T x4, T y4, T z4, T w4
    );
    constexpr explicit mat(const mat2<T> & m);
    constexpr explicit mat(const mat3<T> & m);
    constexpr mat(
        const vec4<T> & v1,
        const vec4<T> & v2,
        const vec4<T> & v3,
        const vec4<T> & v4
    );

    //--- assignment ---

    inline mat4<T> & operator=(const mat4<T> & m);
    inline mat4<T> & operator=(mat4<T> && m);
    
    template <int t_m, int t_n> mat4<T> & operator=(const mat<T, t_m, t_n> & m);

    //--- access ---

    inline T & operator[](int i);
    inline T operator[](int i) const;

    template <int t_i, int t_j> inline T & at();
    template <int t_i, int t_j> constexpr T at() const;

    inline vec4<T> col(int i) const;
    inline vec4<T> row(int i) const;

    template <int t_i> constexpr vec4<T> row() const;
    template <int t_j> constexpr vec4<T> col() const;

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT FUNCTIONS -------------------------------------------------------------------------------------------------------



//--- arithmetic assignment ---

template <typename T, int t_m, int t_n> inline mat<T, t_m, t_n> & operator+=(mat<T, t_m, t_n> & m, T v);
template <typename T, int t_m, int t_n> inline mat<T, t_m, t_n> & operator+=(mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2);

template <typename T, int t_m, int t_n> inline mat<T, t_m, t_n> & operator-=(mat<T, t_m, t_n> & m, T v);
template <typename T, int t_m, int t_n> inline mat<T, t_m, t_n> & operator-=(mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2);

template <typename T, int t_m, int t_n> inline mat<T, t_m, t_n> & operator*=(mat<T, t_m, t_n> & m, T v);
template <typename T, int t_m, int t_n, int t_o> inline mat<T, t_m, t_o> & operator*=(mat<T, t_m, t_n> & m1, const mat<T, t_n, t_o> & m2);

template <typename T, int t_m, int t_n> inline mat<T, t_m, t_n> & operator/=(mat<T, t_m, t_n> & m, T v);

//--- arithmetic operators ---

template <typename T, int t_m, int t_n> inline mat<T, t_m, t_n> operator+(const mat<T, t_m, t_n> & m);

template <typename T, int t_m, int t_n> inline mat<T, t_m, t_n> operator-(const mat<T, t_m, t_n> & m);

template <typename T, int t_m, int t_n> inline mat<T, t_m, t_n> operator+(const mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2);
template <typename T, int t_m, int t_n> inline mat<T, t_m, t_n> operator+(const mat<T, t_m, t_n> & m, T v);
template <typename T, int t_m, int t_n> inline mat<T, t_m, t_n> operator+(T v, const mat<T, t_m, t_n> & m);

template <typename T, int t_m, int t_n> inline mat<T, t_m, t_n> operator-(const mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2);
template <typename T, int t_m, int t_n> inline mat<T, t_m, t_n> operator-(const mat<T, t_m, t_n> & m, T v);
template <typename T, int t_m, int t_n> inline mat<T, t_m, t_n> operator-(T v, const mat<T, t_m, t_n> & m);

template <typename T, int t_m, int t_n, int t_o> inline mat<T, t_m, t_o> operator*(const mat<T, t_m, t_n> & m1, const mat<T, t_n, t_o> & m2);
template <typename T, int t_m, int t_n> inline mat<T, t_m, t_n> operator*(const mat<T, t_m, t_n> & m, T v);
template <typename T, int t_m, int t_n> inline mat<T, t_m, t_n> operator*(T v, const mat<T, t_m, t_n> & m);
template <typename T, int t_m, int t_n> inline vec<T, t_m> operator*(const mat<T, t_m, t_n> & m, const vec<T, t_n> & v);

template <typename T, int t_m, int t_n> inline mat<T, t_m, t_n> operator/(const mat<T, t_m, t_n> & m, T v);
template <typename T, int t_m, int t_n> inline mat<T, t_m, t_n> operator/(T v, const mat<T, t_m, t_n> & m);

//--- comparison operators ---

template <typename T, int t_m, int t_n> inline bool operator==(const mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2);

template <typename T, int t_m, int t_n> inline bool operator!=(const mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2);

//--- constants ---

template <typename T, int t_m, int t_n = t_m> constexpr mat<T, t_m, t_n> fullMat(T v);

template <typename T, int t_m, int t_n = t_m> constexpr mat<T, t_m, t_n> nullMat();



}



#include "Matrix.tpp"