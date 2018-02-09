#pragma once



// Column-major ordering
//
//  x1 x2 x3    00 03 06
//  y1 y2 y3    01 04 07
//  z1 z2 z3    02 05 08



#include "Vector.hpp"



namespace qcu {



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
template <int t_m, int t_n> using ldmat = mat<long double, t_m, t_n>;

using  fmat2 = mat<      float, 2>;
using  fmat3 = mat<      float, 3>;
using  fmat4 = mat<      float, 4>;
using  dmat2 = mat<     double, 2>;
using  dmat3 = mat<     double, 3>;
using  dmat4 = mat<     double, 4>;
using ldmat2 = mat<long double, 2>;
using ldmat3 = mat<long double, 3>;
using ldmat4 = mat<long double, 4>;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Type Namespaces -----------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Mat



namespace  tmats { using qcu::  mat; using qcu::  mat2; using qcu::  mat3; using qcu::  mat4; }
namespace  fmats { using qcu:: fmat; using qcu:: fmat2; using qcu:: fmat3; using qcu:: fmat4; }
namespace  dmats { using qcu:: dmat; using qcu:: dmat2; using qcu:: dmat3; using qcu:: dmat4; }
namespace ldmats { using qcu::ldmat; using qcu::ldmat2; using qcu::ldmat3; using qcu::ldmat4; }

namespace mats {

using namespace  tmats;
using namespace  fmats;
using namespace  dmats;
using namespace ldmats;

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



//==============================================================================================================================================================
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================================================



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT2 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr mat<T, 2, 2>::mat() :
    x1(T(1.0)), y1(T(0.0)),
    x2(T(0.0)), y2(T(1.0))
{}

template <typename T>
constexpr mat<T, 2, 2>::mat(const mat2<T> & m) :
    x1(m.x1), y1(m.y1),
    x2(m.x2), y2(m.y2)
{}

template <typename T>
constexpr mat<T, 2, 2>::mat(mat2<T> && m) :
    x1(m.x1), y1(m.y1),
    x2(m.x2), y2(m.y2)
{}

template <typename T> template <typename U>
constexpr mat<T, 2, 2>::mat(const mat2<U> & m) :
    x1(T(m.x1)), y1(T(m.y1)),
    x2(T(m.x2)), y2(T(m.y2))
{}

template <typename T>
constexpr mat<T, 2, 2>::mat(
    T x1, T y1,
    T x2, T y2
) :
    x1(x1), y1(y1),
    x2(x2), y2(y2)
{}

template <typename T>
constexpr mat<T, 2, 2>::mat(const mat3<T> & m) :
    x1(m.x1), y1(m.y1),
    x2(m.x2), y2(m.y2)
{}

template <typename T>
constexpr mat<T, 2, 2>::mat(const mat4<T> & m) :
    x1(m.x1), y1(m.y1),
    x2(m.x2), y2(m.y2)
{}

template <typename T>
constexpr mat<T, 2, 2>::mat(
    const vec2<T> & v1,
    const vec2<T> & v2
) :
    x1(v1.x), y1(v1.y),
    x2(v2.x), y2(v2.y)
{}



//------------------------------------------------------------------------------
// Assignment



template <typename T>
inline mat2<T> & mat<T, 2, 2>::operator=(const mat2<T> & m) {
    x1 = m.x1; y1 = m.y1;
    x2 = m.x2; y2 = m.y2;
    return *this;
}

template <typename T>
inline mat2<T> & mat<T, 2, 2>::operator=(mat2<T> && m) {
    x1 = m.x1; y1 = m.y1;
    x2 = m.x2; y2 = m.y2;
    return *this;
}

template <typename T>
template <int t_m, int t_n>
inline mat2<T> & mat<T, 2, 2>::operator=(const mat<T, t_m, t_n> & m) {
    if constexpr (t_n >= 1) {
        if constexpr (t_m >= 1) x1 = m.x1; if constexpr (t_m < 1) x1 = T(1);
        if constexpr (t_m >= 2) y1 = m.y1; if constexpr (t_m < 2) y1 = T(0);
    }
    if constexpr (t_n >= 2) {
        if constexpr (t_m >= 1) x2 = m.x2; if constexpr (t_m < 1) x2 = T(0);
        if constexpr (t_m >= 2) y2 = m.y2; if constexpr (t_m < 2) y2 = T(1);
    }
    return *this;
}



//------------------------------------------------------------------------------
// Access



template <typename T>
inline T & mat<T, 2, 2>::operator[](int i) {
    return *(&x1 + i);
}

template <typename T>
inline T mat<T, 2, 2>::operator[](int i) const {
    return *(&x1 + i);
}

template <typename T>
template <int t_i, int t_j>
inline T & mat<T, 2, 2>::at() {
    static_assert(t_i >= 0 && t_i <= 1 && t_j >= 0 && t_j <= 1, "index out of bounds");
    if constexpr (t_i == 0) {
        if constexpr (t_j == 0) return x1;
        if constexpr (t_j == 1) return x2;
    }
    if constexpr (t_i == 1) {
        if constexpr (t_j == 0) return y1;
        if constexpr (t_j == 1) return y2;
    }
}

template <typename T>
template <int t_i, int t_j>
constexpr T mat<T, 2, 2>::at() const {
    static_assert(t_i >= 0 && t_i <= 1 && t_j >= 0 && t_j <= 1, "index out of bounds");
    if constexpr (t_i == 0) {
        if constexpr (t_j == 0) return x1;
        if constexpr (t_j == 1) return x2;
    }
    if constexpr (t_i == 1) {
        if constexpr (t_j == 0) return y1;
        if constexpr (t_j == 1) return y2;
    }
}

template <typename T>
inline vec2<T> mat<T, 2, 2>::row(int i) const {
    return vec2<T>(*(&x1 + i), *(&y1 + i));
}

template <typename T>
inline vec2<T> mat<T, 2, 2>::col(int i) const {
    int stride(i * 2);
    return vec2<T>(*(&x1 + stride), *(&y1 + stride));
}

template <typename T>
template <int t_i>
constexpr vec2<T> mat<T, 2, 2>::row() const {
    return vec2<T>(at<t_i, 0>(), at<t_i, 1>());
}

template <typename T>
template <int t_j>
constexpr vec2<T> mat<T, 2, 2>::col() const {
    return vec2<T>(at<0, t_j>(), at<1, t_j>());
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT3 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr mat<T, 3, 3>::mat() :
    x1(T(1.0)), y1(T(0.0)), z1(T(0.0)),
    x2(T(0.0)), y2(T(1.0)), z2(T(0.0)),
    x3(T(0.0)), y3(T(0.0)), z3(T(1.0))
{}

template <typename T>
constexpr mat<T, 3, 3>::mat(const mat3<T> & m) :
    x1(m.x1), y1(m.y1), z1(m.z1),
    x2(m.x2), y2(m.y2), z2(m.z2),
    x3(m.x3), y3(m.y3), z3(m.z3)
{}

template <typename T>
constexpr mat<T, 3, 3>::mat(mat3<T> && m) :
    x1(m.x1), y1(m.y1), z1(m.z1),
    x2(m.x2), y2(m.y2), z2(m.z2),
    x3(m.x3), y3(m.y3), z3(m.z3)
{}

template <typename T> template <typename U>
constexpr mat<T, 3, 3>::mat(const mat3<U> & m) :
    x1(T(m.x1)), y1(T(m.y1)), z1(T(m.z1)),
    x2(T(m.x2)), y2(T(m.y2)), z2(T(m.z2)),
    x3(T(m.x3)), y3(T(m.y3)), z3(T(m.z3))
{}

template <typename T>
constexpr mat<T, 3, 3>::mat(
    T x1, T y1, T z1,
    T x2, T y2, T z2,
    T x3, T y3, T z3
) :
    x1(x1), y1(y1), z1(z1),
    x2(x2), y2(y2), z2(z2),
    x3(x3), y3(y3), z3(z3)
{}

template <typename T>
constexpr mat<T, 3, 3>::mat(const mat2<T> & m) :
    x1(  m.x1), y1(  m.y1), z1(T(0.0)),
    x2(  m.x2), y2(  m.y2), z2(T(0.0)),
    x3(T(0.0)), y3(T(0.0)), z3(T(1.0))
{}

template <typename T>
constexpr mat<T, 3, 3>::mat(const mat4<T> & m) :
    x1(m.x1), y1(m.y1), z1(m.z1),
    x2(m.x2), y2(m.y2), z2(m.z2),
    x3(m.x3), y3(m.y3), z3(m.z3)
{}

template <typename T>
constexpr mat<T, 3, 3>::mat(
    const vec3<T> & v1,
    const vec3<T> & v2,
    const vec3<T> & v3
) :
    x1(v1.x), y1(v1.y), z1(v1.z),
    x2(v2.x), y2(v2.y), z2(v2.z),
    x3(v3.x), y3(v3.y), z3(v3.z)
{}



//------------------------------------------------------------------------------
// Assignment



template <typename T>
inline mat3<T> & mat<T, 3, 3>::operator=(const mat3<T> & m) {
    x1 = m.x1; y1 = m.y1; z1 = m.z1;
    x2 = m.x2; y2 = m.y2; z2 = m.z2;
    x3 = m.x3; y3 = m.y3; z3 = m.z3;
    return *this;
}

template <typename T>
inline mat3<T> & mat<T, 3, 3>::operator=(mat3<T> && m) {
    x1 = m.x1; y1 = m.y1; z1 = m.z1;
    x2 = m.x2; y2 = m.y2; z2 = m.z2;
    x3 = m.x3; y3 = m.y3; z3 = m.z3;
    return *this;
}

template <typename T>
template <int t_m, int t_n>
inline mat3<T> & mat<T, 3, 3>::operator=(const mat<T, t_m, t_n> & m) {
    if constexpr (t_n >= 1) {
        if constexpr (t_m >= 1) x1 = m.x1; if constexpr (t_m < 1) x1 = T(1);
        if constexpr (t_m >= 2) y1 = m.y1; if constexpr (t_m < 2) y1 = T(0);
        if constexpr (t_m >= 3) z1 = m.z1; if constexpr (t_m < 3) z1 = T(0);
    }
    if constexpr (t_n >= 2) {
        if constexpr (t_m >= 1) x2 = m.x2; if constexpr (t_m < 1) x2 = T(0);
        if constexpr (t_m >= 2) y2 = m.y2; if constexpr (t_m < 2) y2 = T(1);
        if constexpr (t_m >= 3) z2 = m.z2; if constexpr (t_m < 3) z2 = T(0);
    }
    if constexpr (t_n >= 3) {
        if constexpr (t_m >= 1) x3 = m.x3; if constexpr (t_m < 1) x3 = T(0);
        if constexpr (t_m >= 2) y3 = m.y3; if constexpr (t_m < 2) y3 = T(0);
        if constexpr (t_m >= 3) z3 = m.z3; if constexpr (t_m < 3) z3 = T(1);
    }
    return *this;
}



//------------------------------------------------------------------------------
// Access



template <typename T>
inline T & mat<T, 3, 3>::operator[](int i) {
    return *(&x1 + i);
}

template <typename T>
inline T mat<T, 3, 3>::operator[](int i) const {
    return *(&x1 + i);
}

template <typename T>
template <int t_i, int t_j>
inline T & mat<T, 3, 3>::at() {
    static_assert(t_i >= 0 && t_i <= 2 && t_j >= 0 && t_j <= 2, "index out of bounds");
    if constexpr (t_i == 0) {
        if constexpr (t_j == 0) return x1;
        if constexpr (t_j == 1) return x2;
        if constexpr (t_j == 2) return x3;
    }
    if constexpr (t_i == 1) {
        if constexpr (t_j == 0) return y1;
        if constexpr (t_j == 1) return y2;
        if constexpr (t_j == 2) return y3;
    }
    if constexpr (t_i == 2) {
        if constexpr (t_j == 0) return z1;
        if constexpr (t_j == 1) return z2;
        if constexpr (t_j == 2) return z3;
    }
}

template <typename T>
template <int t_i, int t_j>
constexpr T mat<T, 3, 3>::at() const {
    static_assert(t_i >= 0 && t_i <= 2 && t_j >= 0 && t_j <= 2, "index out of bounds");
    if constexpr (t_i == 0) {
        if constexpr (t_j == 0) return x1;
        if constexpr (t_j == 1) return x2;
        if constexpr (t_j == 2) return x3;
    }
    if constexpr (t_i == 1) {
        if constexpr (t_j == 0) return y1;
        if constexpr (t_j == 1) return y2;
        if constexpr (t_j == 2) return y3;
    }
    if constexpr (t_i == 2) {
        if constexpr (t_j == 0) return z1;
        if constexpr (t_j == 1) return z2;
        if constexpr (t_j == 2) return z3;
    }
}

template <typename T>
inline vec3<T> mat<T, 3, 3>::row(int i) const {
    return vec3<T>(*(&x1 + i), *(&y1 + i), *(&z1 + i));
}

template <typename T>
inline vec3<T> mat<T, 3, 3>::col(int i) const {
    int stride(i * 3);
    return vec3<T>(*(&x1 + stride), *(&y1 + stride), *(&z1 + stride));
}

template <typename T>
template <int t_i>
constexpr vec3<T> mat<T, 3, 3>::row() const {
    return vec3<T>(at<t_i, 0>(), at<t_i, 1>(), at<t_i, 2>());
}

template <typename T>
template <int t_j>
constexpr vec3<T> mat<T, 3, 3>::col() const {
    return vec3<T>(at<0, t_j>(), at<1, t_j>(), at<2, t_j>());
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT4 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr mat<T, 4, 4>::mat() :
    x1(T(1.0)), y1(T(0.0)), z1(T(0.0)), w1(T(0.0)),
    x2(T(0.0)), y2(T(1.0)), z2(T(0.0)), w2(T(0.0)),
    x3(T(0.0)), y3(T(0.0)), z3(T(1.0)), w3(T(0.0)),
    x4(T(0.0)), y4(T(0.0)), z4(T(0.0)), w4(T(1.0))
{}

template <typename T>
constexpr mat<T, 4, 4>::mat(const mat4<T> & m) :
    x1(m.x1), y1(m.y1), z1(m.z1), w1(m.w1),
    x2(m.x2), y2(m.y2), z2(m.z2), w2(m.w2),
    x3(m.x3), y3(m.y3), z3(m.z3), w3(m.w3),
    x4(m.x4), y4(m.y4), z4(m.z4), w4(m.w4)
{}

template <typename T>
constexpr mat<T, 4, 4>::mat(mat4<T> && m) :
    x1(m.x1), y1(m.y1), z1(m.z1), w1(m.w1),
    x2(m.x2), y2(m.y2), z2(m.z2), w2(m.w2),
    x3(m.x3), y3(m.y3), z3(m.z3), w3(m.w3),
    x4(m.x4), y4(m.y4), z4(m.z4), w4(m.w4)
{}

template <typename T> template <typename U>
constexpr mat<T, 4, 4>::mat(const mat4<U> & m) :
    x1(T(m.x1)), y1(T(m.y1)), z1(T(m.z1)), w1(T(m.w1)),
    x2(T(m.x2)), y2(T(m.y2)), z2(T(m.z2)), w2(T(m.w2)),
    x3(T(m.x3)), y3(T(m.y3)), z3(T(m.z3)), w3(T(m.w3)),
    x4(T(m.x4)), y4(T(m.y4)), z4(T(m.z4)), w4(T(m.w4))
{}

template <typename T>
constexpr mat<T, 4, 4>::mat(
    T x1, T y1, T z1, T w1,
    T x2, T y2, T z2, T w2,
    T x3, T y3, T z3, T w3,
    T x4, T y4, T z4, T w4
) :
    x1(x1), y1(y1), z1(z1), w1(w1),
    x2(x2), y2(y2), z2(z2), w2(w2),
    x3(x3), y3(y3), z3(z3), w3(w3),
    x4(x4), y4(y4), z4(z4), w4(w4)
{}

template <typename T>
constexpr mat<T, 4, 4>::mat(const mat2<T> & m) :
    x1(  m.x1), y1(  m.y1), z1(T(0.0)), w1(T(0.0)),
    x2(  m.x2), y2(  m.y2), z2(T(0.0)), w2(T(0.0)),
    x3(T(0.0)), y3(T(0.0)), z3(T(1.0)), w3(T(0.0)),
    x4(T(0.0)), y4(T(0.0)), z4(T(0.0)), w4(T(1.0))
{}

template <typename T>
constexpr mat<T, 4, 4>::mat(const mat3<T> & m) :
    x1(  m.x1), y1(  m.y1), z1(  m.z1), w1(T(0.0)),
    x2(  m.x2), y2(  m.y2), z2(  m.z2), w2(T(0.0)),
    x3(  m.x3), y3(  m.y3), z3(  m.z3), w3(T(0.0)),
    x4(T(0.0)), y4(T(0.0)), z4(T(0.0)), w4(T(1.0))
{}

template <typename T>
constexpr mat<T, 4, 4>::mat(
    const vec4<T> & v1,
    const vec4<T> & v2,
    const vec4<T> & v3,
    const vec4<T> & v4
) :
    x1(v1.x), y1(v1.y), z1(v1.z), w1(v1.w),
    x2(v2.x), y2(v2.y), z2(v2.z), w2(v2.w),
    x3(v3.x), y3(v3.y), z3(v3.z), w3(v3.w),
    x4(v4.x), y4(v4.y), z4(v4.z), w4(v4.w)
{}



//------------------------------------------------------------------------------
// Assignment



template <typename T>
inline mat4<T> & mat<T, 4, 4>::operator=(const mat4<T> & m) {
    x1 = m.x1; y1 = m.y1; z1 = m.z1; w1 = m.w1;
    x2 = m.x2; y2 = m.y2; z2 = m.z2; w2 = m.w2;
    x3 = m.x3; y3 = m.y3; z3 = m.z3; w3 = m.w3;
    x4 = m.x4; y4 = m.y4; z4 = m.z4; w4 = m.w4;

    return *this;
}

template <typename T>
inline mat4<T> & mat<T, 4, 4>::operator=(mat4<T> && m) {
    x1 = m.x1; y1 = m.y1; z1 = m.z1; w1 = m.w1;
    x2 = m.x2; y2 = m.y2; z2 = m.z2; w2 = m.w2;
    x3 = m.x3; y3 = m.y3; z3 = m.z3; w3 = m.w3;
    x4 = m.x4; y4 = m.y4; z4 = m.z4; w4 = m.w4;

    return *this;
}

template <typename T>
template <int t_m, int t_n>
inline mat4<T> & mat<T, 4, 4>::operator=(const mat<T, t_m, t_n> & m) {
    if constexpr (t_n >= 1) {
        if constexpr (t_m >= 1) x1 = m.x1; if constexpr (t_m < 1) x1 = T(1);
        if constexpr (t_m >= 2) y1 = m.y1; if constexpr (t_m < 2) y1 = T(0);
        if constexpr (t_m >= 3) z1 = m.z1; if constexpr (t_m < 3) z1 = T(0);
        if constexpr (t_m >= 4) w1 = m.w1; if constexpr (t_m < 4) w1 = T(0);
    }
    if constexpr (t_n >= 2) {
        if constexpr (t_m >= 1) x2 = m.x2; if constexpr (t_m < 1) x2 = T(0);
        if constexpr (t_m >= 2) y2 = m.y2; if constexpr (t_m < 2) y2 = T(1);
        if constexpr (t_m >= 3) z2 = m.z2; if constexpr (t_m < 3) z2 = T(0);
        if constexpr (t_m >= 4) w2 = m.w2; if constexpr (t_m < 4) w2 = T(0);
    }
    if constexpr (t_n >= 3) {
        if constexpr (t_m >= 1) x3 = m.x3; if constexpr (t_m < 1) x3 = T(0);
        if constexpr (t_m >= 2) y3 = m.y3; if constexpr (t_m < 2) y3 = T(0);
        if constexpr (t_m >= 3) z3 = m.z3; if constexpr (t_m < 3) z3 = T(1);
        if constexpr (t_m >= 4) w3 = m.w3; if constexpr (t_m < 4) w3 = T(0);
    }
    if constexpr (t_n >= 4) {
        if constexpr (t_m >= 1) x4 = m.x4; if constexpr (t_m < 1) x4 = T(0);
        if constexpr (t_m >= 2) y4 = m.y4; if constexpr (t_m < 2) y4 = T(0);
        if constexpr (t_m >= 3) z4 = m.z4; if constexpr (t_m < 3) z4 = T(0);
        if constexpr (t_m >= 4) w4 = m.w4; if constexpr (t_m < 4) w4 = T(1);
    }
    return *this;
}



//------------------------------------------------------------------------------
// Access



template <typename T>
inline T & mat<T, 4, 4>::operator[](int i) {
    return *(&x1 + i);
}

template <typename T>
inline T mat<T, 4, 4>::operator[](int i) const {
    return *(&x1 + i);
}

template <typename T>
template <int t_i, int t_j>
inline T & mat<T, 4, 4>::at() {
    static_assert(t_i >= 0 && t_i <= 3 && t_j >= 0 && t_j <= 3, "index out of bounds");
    if constexpr (t_i == 0) {
        if constexpr (t_j == 0) return x1;
        if constexpr (t_j == 1) return x2;
        if constexpr (t_j == 2) return x3;
        if constexpr (t_j == 3) return x4;
    }
    if constexpr (t_i == 1) {
        if constexpr (t_j == 0) return y1;
        if constexpr (t_j == 1) return y2;
        if constexpr (t_j == 2) return y3;
        if constexpr (t_j == 3) return y4;
    }
    if constexpr (t_i == 2) {
        if constexpr (t_j == 0) return z1;
        if constexpr (t_j == 1) return z2;
        if constexpr (t_j == 2) return z3;
        if constexpr (t_j == 3) return z4;
    }
    if constexpr (t_i == 3) {
        if constexpr (t_j == 0) return w1;
        if constexpr (t_j == 1) return w2;
        if constexpr (t_j == 2) return w3;
        if constexpr (t_j == 3) return w4;
    }
}

template <typename T>
template <int t_i, int t_j>
constexpr T mat<T, 4, 4>::at() const {
    static_assert(t_i >= 0 && t_i <= 3 && t_j >= 0 && t_j <= 3, "index out of bounds");
    if constexpr (t_i == 0) {
        if constexpr (t_j == 0) return x1;
        if constexpr (t_j == 1) return x2;
        if constexpr (t_j == 2) return x3;
        if constexpr (t_j == 3) return x4;
    }
    if constexpr (t_i == 1) {
        if constexpr (t_j == 0) return y1;
        if constexpr (t_j == 1) return y2;
        if constexpr (t_j == 2) return y3;
        if constexpr (t_j == 3) return y4;
    }
    if constexpr (t_i == 2) {
        if constexpr (t_j == 0) return z1;
        if constexpr (t_j == 1) return z2;
        if constexpr (t_j == 2) return z3;
        if constexpr (t_j == 3) return z4;
    }
    if constexpr (t_i == 3) {
        if constexpr (t_j == 0) return w1;
        if constexpr (t_j == 1) return w2;
        if constexpr (t_j == 2) return w3;
        if constexpr (t_j == 3) return w4;
    }
}

template <typename T>
inline vec4<T> mat<T, 4, 4>::row(int i) const {
    return vec4<T>(*(&x1 + i), *(&y1 + i), *(&z1 + i), *(&w1 + i));
}

template <typename T>
inline vec4<T> mat<T, 4, 4>::col(int i) const {
    int stride(i * 4);
    return vec4<T>(*(&x1 + stride), *(&y1 + stride), *(&z1 + stride), *(&w1 + stride));
}

template <typename T>
template <int t_i>
constexpr vec4<T> mat<T, 4, 4>::row() const {
    return vec4<T>(at<t_i, 0>(), at<t_i, 1>(), at<t_i, 2>(), at<t_i, 3>());
}

template <typename T>
template <int t_j>
constexpr vec4<T> mat<T, 4, 4>::col() const {
    return vec4<T>(at<0, t_j>(), at<1, t_j>(), at<2, t_j>(), at<3, t_j>());
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT FUNCTIONS IMPLEMENTATION ----------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Arithmetic Assignment



//--- add assign ---

template <typename T, int t_m, int t_n>
inline mat<T, t_m, t_n> & operator+=(mat<T, t_m, t_n> & m, T v) {
    if constexpr (t_n >= 1) {
        if constexpr (t_m >= 1) m.x1 += v;
        if constexpr (t_m >= 2) m.y1 += v;
        if constexpr (t_m >= 3) m.z1 += v;
        if constexpr (t_m >= 4) m.w1 += v;
    }
    if constexpr (t_n >= 2) {
        if constexpr (t_m >= 1) m.x2 += v;
        if constexpr (t_m >= 2) m.y2 += v;
        if constexpr (t_m >= 3) m.z2 += v;
        if constexpr (t_m >= 4) m.w2 += v;
    }
    if constexpr (t_n >= 3) {
        if constexpr (t_m >= 1) m.x3 += v;
        if constexpr (t_m >= 2) m.y3 += v;
        if constexpr (t_m >= 3) m.z3 += v;
        if constexpr (t_m >= 4) m.w3 += v;
    }
    if constexpr (t_n >= 4) {
        if constexpr (t_m >= 1) m.x4 += v;
        if constexpr (t_m >= 2) m.y4 += v;
        if constexpr (t_m >= 3) m.z4 += v;
        if constexpr (t_m >= 4) m.w4 += v;
    }
    return m;
}

template <typename T, int t_m, int t_n>
inline mat<T, t_m, t_n> & operator+=(mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2) {
    if constexpr (t_n >= 1) {
        if constexpr (t_m >= 1) m1.x1 += m2.x1;
        if constexpr (t_m >= 2) m1.y1 += m2.y1;
        if constexpr (t_m >= 3) m1.z1 += m2.z1;
        if constexpr (t_m >= 4) m1.w1 += m2.w1;
    }
    if constexpr (t_n >= 2) {
        if constexpr (t_m >= 1) m1.x2 += m2.x2;
        if constexpr (t_m >= 2) m1.y2 += m2.y2;
        if constexpr (t_m >= 3) m1.z2 += m2.z2;
        if constexpr (t_m >= 4) m1.w2 += m2.w2;
    }
    if constexpr (t_n >= 3) {
        if constexpr (t_m >= 1) m1.x3 += m2.x3;
        if constexpr (t_m >= 2) m1.y3 += m2.y3;
        if constexpr (t_m >= 3) m1.z3 += m2.z3;
        if constexpr (t_m >= 4) m1.w3 += m2.w3;
    }
    if constexpr (t_n >= 4) {
        if constexpr (t_m >= 1) m1.x4 += m2.x4;
        if constexpr (t_m >= 2) m1.y4 += m2.y4;
        if constexpr (t_m >= 3) m1.z4 += m2.z4;
        if constexpr (t_m >= 4) m1.w4 += m2.w4;
    }
    return m1;
}

//--- subtract assign ---

template <typename T, int t_m, int t_n>
inline mat<T, t_m, t_n> & operator-=(mat<T, t_m, t_n> & m, T v) {
    if constexpr (t_n >= 1) {
        if constexpr (t_m >= 1) m.x1 -= v;
        if constexpr (t_m >= 2) m.y1 -= v;
        if constexpr (t_m >= 3) m.z1 -= v;
        if constexpr (t_m >= 4) m.w1 -= v;
    }
    if constexpr (t_n >= 2) {
        if constexpr (t_m >= 1) m.x2 -= v;
        if constexpr (t_m >= 2) m.y2 -= v;
        if constexpr (t_m >= 3) m.z2 -= v;
        if constexpr (t_m >= 4) m.w2 -= v;
    }
    if constexpr (t_n >= 3) {
        if constexpr (t_m >= 1) m.x3 -= v;
        if constexpr (t_m >= 2) m.y3 -= v;
        if constexpr (t_m >= 3) m.z3 -= v;
        if constexpr (t_m >= 4) m.w3 -= v;
    }
    if constexpr (t_n >= 4) {
        if constexpr (t_m >= 1) m.x4 -= v;
        if constexpr (t_m >= 2) m.y4 -= v;
        if constexpr (t_m >= 3) m.z4 -= v;
        if constexpr (t_m >= 4) m.w4 -= v;
    }
    return m;
}

template <typename T, int t_m, int t_n>
inline mat<T, t_m, t_n> & operator-=(mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2) {
    if constexpr (t_n >= 1) {
        if constexpr (t_m >= 1) m1.x1 -= m2.x1;
        if constexpr (t_m >= 2) m1.y1 -= m2.y1;
        if constexpr (t_m >= 3) m1.z1 -= m2.z1;
        if constexpr (t_m >= 4) m1.w1 -= m2.w1;
    }
    if constexpr (t_n >= 2) {
        if constexpr (t_m >= 1) m1.x2 -= m2.x2;
        if constexpr (t_m >= 2) m1.y2 -= m2.y2;
        if constexpr (t_m >= 3) m1.z2 -= m2.z2;
        if constexpr (t_m >= 4) m1.w2 -= m2.w2;
    }
    if constexpr (t_n >= 3) {
        if constexpr (t_m >= 1) m1.x3 -= m2.x3;
        if constexpr (t_m >= 2) m1.y3 -= m2.y3;
        if constexpr (t_m >= 3) m1.z3 -= m2.z3;
        if constexpr (t_m >= 4) m1.w3 -= m2.w3;
    }
    if constexpr (t_n >= 4) {
        if constexpr (t_m >= 1) m1.x4 -= m2.x4;
        if constexpr (t_m >= 2) m1.y4 -= m2.y4;
        if constexpr (t_m >= 3) m1.z4 -= m2.z4;
        if constexpr (t_m >= 4) m1.w4 -= m2.w4;
    }
    return m1;
}

//--- multiply assign ---

template <typename T, int t_m, int t_n>
inline mat<T, t_m, t_n> & operator*=(mat<T, t_m, t_n> & m, T v) {
    if constexpr (t_n >= 1) {
        if constexpr (t_m >= 1) m.x1 *= v;
        if constexpr (t_m >= 2) m.y1 *= v;
        if constexpr (t_m >= 3) m.z1 *= v;
        if constexpr (t_m >= 4) m.w1 *= v;
    }
    if constexpr (t_n >= 2) {
        if constexpr (t_m >= 1) m.x2 *= v;
        if constexpr (t_m >= 2) m.y2 *= v;
        if constexpr (t_m >= 3) m.z2 *= v;
        if constexpr (t_m >= 4) m.w2 *= v;
    }
    if constexpr (t_n >= 3) {
        if constexpr (t_m >= 1) m.x3 *= v;
        if constexpr (t_m >= 2) m.y3 *= v;
        if constexpr (t_m >= 3) m.z3 *= v;
        if constexpr (t_m >= 4) m.w3 *= v;
    }
    if constexpr (t_n >= 4) {
        if constexpr (t_m >= 1) m.x4 *= v;
        if constexpr (t_m >= 2) m.y4 *= v;
        if constexpr (t_m >= 3) m.z4 *= v;
        if constexpr (t_m >= 4) m.w4 *= v;
    }
    return m;
}

namespace detail {

template <int t_i, int t_j, typename T, int t_m, int t_n, int t_o>
inline T mult(const mat<T, t_m, t_n> & m1, const mat<T, t_n, t_o> & m2) {
    if constexpr (t_n == 1) return m1.at<t_i, 0>() * m2.at<0, t_j>();
    if constexpr (t_n == 2) return m1.at<t_i, 0>() * m2.at<0, t_j>() + m1.at<t_i, 1>() * m2.at<1, t_j>();
    if constexpr (t_n == 3) return m1.at<t_i, 0>() * m2.at<0, t_j>() + m1.at<t_i, 1>() * m2.at<1, t_j>() + m1.at<t_i, 2>() * m2.at<2, t_j>();
    if constexpr (t_n == 4) return m1.at<t_i, 0>() * m2.at<0, t_j>() + m1.at<t_i, 1>() * m2.at<1, t_j>() + m1.at<t_i, 2>() * m2.at<2, t_j>() + m1.at<t_i, 3>() * m2.at<3, t_j>();
}

}

template <typename T, int t_m, int t_n, int t_o>
inline mat<T, t_m, t_o> & operator*=(mat<T, t_m, t_n> & m1, const mat<T, t_n, t_o> & m2) {
    if constexpr (t_o >= 1) {
        if constexpr (t_m >= 1) m1.x1 = detail::mult<0, 0>(m1, m2);
        if constexpr (t_m >= 2) m1.y1 = detail::mult<1, 0>(m1, m2);
        if constexpr (t_m >= 3) m1.z1 = detail::mult<2, 0>(m1, m2);
        if constexpr (t_m >= 4) m1.w1 = detail::mult<3, 0>(m1, m2);
    }
    if constexpr (t_o >= 2) {
        if constexpr (t_m >= 1) m1.x2 = detail::mult<0, 1>(m1, m2);
        if constexpr (t_m >= 2) m1.y2 = detail::mult<1, 1>(m1, m2);
        if constexpr (t_m >= 3) m1.z2 = detail::mult<2, 1>(m1, m2);
        if constexpr (t_m >= 4) m1.w2 = detail::mult<3, 1>(m1, m2);
    }
    if constexpr (t_o >= 3) {
        if constexpr (t_m >= 1) m1.x3 = detail::mult<0, 2>(m1, m2);
        if constexpr (t_m >= 2) m1.y3 = detail::mult<1, 2>(m1, m2);
        if constexpr (t_m >= 3) m1.z3 = detail::mult<2, 2>(m1, m2);
        if constexpr (t_m >= 4) m1.w3 = detail::mult<3, 2>(m1, m2);
    }
    if constexpr (t_o >= 4) {
        if constexpr (t_m >= 1) m1.x4 = detail::mult<0, 3>(m1, m2);
        if constexpr (t_m >= 2) m1.y4 = detail::mult<1, 3>(m1, m2);
        if constexpr (t_m >= 3) m1.z4 = detail::mult<2, 3>(m1, m2);
        if constexpr (t_m >= 4) m1.w4 = detail::mult<3, 3>(m1, m2);
    }
    return m1;
}

//--- divide assign ---

template <typename T, int t_m, int t_n>
inline mat<T, t_m, t_n> & operator/=(mat<T, t_m, t_n> & m, T v) {
    return m *= T(1.0) / v;
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- positive ---

template <typename T, int t_m, int t_n>
inline mat<T, t_m, t_n> operator+(const mat<T, t_m, t_n> & m) {
    return m;
}

//--- negative ---

template <typename T, int t_m, int t_n>
inline mat<T, t_m, t_n> operator-(const mat<T, t_m, t_n> & m) {
    return m * T(-1.0);
}

namespace detail {

template <int t_j, typename T, int t_m, int t_n>
inline vec<T, t_m> addCol(const mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2) {
    if constexpr (t_m == 1) return vec1<T>(m1.at<0, t_j>() + m2.at<0, t_j>());
    if constexpr (t_m == 2) return vec2<T>(m1.at<0, t_j>() + m2.at<0, t_j>(), m1.at<1, t_j>() + m2.at<1, t_j>());
    if constexpr (t_m == 3) return vec3<T>(m1.at<0, t_j>() + m2.at<0, t_j>(), m1.at<1, t_j>() + m2.at<1, t_j>(), m1.at<2, t_j>() + m2.at<2, t_j>());
    if constexpr (t_m == 4) return vec4<T>(m1.at<0, t_j>() + m2.at<0, t_j>(), m1.at<1, t_j>() + m2.at<1, t_j>(), m1.at<2, t_j>() + m2.at<2, t_j>(), m1.at<3, t_j>() + m2.at<3, t_j>());
}

template <int t_j, typename T, int t_m, int t_n>
inline vec<T, t_m> addCol(const mat<T, t_m, t_n> & m, T v) {
    if constexpr (t_m == 1) return vec1<T>(m.at<0, t_j>() + v);
    if constexpr (t_m == 2) return vec2<T>(m.at<0, t_j>() + v, m.at<1, t_j>() + v);
    if constexpr (t_m == 3) return vec3<T>(m.at<0, t_j>() + v, m.at<1, t_j>() + v, m.at<2, t_j>() + v);
    if constexpr (t_m == 4) return vec4<T>(m.at<0, t_j>() + v, m.at<1, t_j>() + v, m.at<2, t_j>() + v, m.at<3, t_j>() + v);
}

template <int t_j, typename T, int t_m, int t_n, int t_o>
inline vec<T, t_m> multCol(const mat<T, t_m, t_n> & m1, const mat<T, t_n, t_o> & m2) {
    if constexpr (t_m == 1) return vec1<T>(mult<0, t_j>(m1, m2));
    if constexpr (t_m == 2) return vec2<T>(mult<0, t_j>(m1, m2), mult<1, t_j>(m1, m2));
    if constexpr (t_m == 3) return vec3<T>(mult<0, t_j>(m1, m2), mult<1, t_j>(m1, m2), mult<2, t_j>(m1, m2));
    if constexpr (t_m == 4) return vec4<T>(mult<0, t_j>(m1, m2), mult<1, t_j>(m1, m2), mult<2, t_j>(m1, m2), mult<3, t_j>(m1, m2));
}

template <int t_j, typename T, int t_m, int t_n>
inline vec<T, t_m> multCol(const mat<T, t_m, t_n> & m, T v) {
    if constexpr (t_m == 1) return vec1<T>(m.at<0, t_j>() * v);
    if constexpr (t_m == 2) return vec2<T>(m.at<0, t_j>() * v, m.at<1, t_j>() * v);
    if constexpr (t_m == 3) return vec3<T>(m.at<0, t_j>() * v, m.at<1, t_j>() * v, m.at<2, t_j>() * v);
    if constexpr (t_m == 4) return vec4<T>(m.at<0, t_j>() * v, m.at<1, t_j>() * v, m.at<2, t_j>() * v, m.at<3, t_j>() * v);
}

template <int t_i, typename T, int t_m, int t_n>
inline T multRow(const mat<T, t_m, t_n> & m, const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return m.at<t_i, 0>() * v.x;
    if constexpr (t_n == 2) return m.at<t_i, 0>() * v.x + m.at<t_i, 1>() * v.y;
    if constexpr (t_n == 3) return m.at<t_i, 0>() * v.x + m.at<t_i, 1>() * v.y + m.at<t_i, 2>() * v.z;
    if constexpr (t_n == 4) return m.at<t_i, 0>() * v.x + m.at<t_i, 1>() * v.y + m.at<t_i, 2>() * v.z + m.at<t_i, 3>() * v.w;
}

template <int t_j, typename T, int t_m, int t_n>
inline vec<T, t_m> divCol(T v, const mat<T, t_m, t_n> & m) {
    if constexpr (t_m == 1) return vec1<T>(v / m.at<0, t_j>());
    if constexpr (t_m == 2) return vec2<T>(v / m.at<0, t_j>(), v / m.at<1, t_j>());
    if constexpr (t_m == 3) return vec3<T>(v / m.at<0, t_j>(), v / m.at<1, t_j>(), v / m.at<2, t_j>());
    if constexpr (t_m == 4) return vec4<T>(v / m.at<0, t_j>(), v / m.at<1, t_j>(), v / m.at<2, t_j>(), v / m.at<3, t_j>());
}

}

//--- add ---

template <typename T, int t_m, int t_n>
inline mat<T, t_m, t_n> operator+(const mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2) {
    if constexpr (t_n == 1) return mat<T, t_m, t_n>(detail::addCol<0>(m1, m2));
    if constexpr (t_n == 2) return mat<T, t_m, t_n>(detail::addCol<0>(m1, m2), detail::addCol<1>(m1, m2));
    if constexpr (t_n == 3) return mat<T, t_m, t_n>(detail::addCol<0>(m1, m2), detail::addCol<1>(m1, m2), detail::addCol<2>(m1, m2));
    if constexpr (t_n == 4) return mat<T, t_m, t_n>(detail::addCol<0>(m1, m2), detail::addCol<1>(m1, m2), detail::addCol<2>(m1, m2), detail::addCol<3>(m1, m2));
}

template <typename T, int t_m, int t_n>
inline mat<T, t_m, t_n> operator+(const mat<T, t_m, t_n> & m, T v) {
    if constexpr (t_n == 1) return mat<T, t_m, t_n>(detail::addCol<0>(m, v));
    if constexpr (t_n == 2) return mat<T, t_m, t_n>(detail::addCol<0>(m, v), detail::addCol<1>(m, v));
    if constexpr (t_n == 3) return mat<T, t_m, t_n>(detail::addCol<0>(m, v), detail::addCol<1>(m, v), detail::addCol<2>(m, v));
    if constexpr (t_n == 4) return mat<T, t_m, t_n>(detail::addCol<0>(m, v), detail::addCol<1>(m, v), detail::addCol<2>(m, v), detail::addCol<3>(m, v));
}

template <typename T, int t_m, int t_n>
inline mat<T, t_m, t_n> operator+(T v, const mat<T, t_m, t_n> & m) {
    return m + v;
}

//--- subtract ---

template <typename T, int t_m, int t_n>
inline mat<T, t_m, t_n> operator-(const mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2) {
    return m1 + -m2;
}

template <typename T, int t_m, int t_n>
inline mat<T, t_m, t_n> operator-(const mat<T, t_m, t_n> & m, T v) {
    return m + -v;
}

template <typename T, int t_m, int t_n>
inline mat<T, t_m, t_n> operator-(T v, const mat<T, t_m, t_n> & m) {
    return v + -m;
}

//--- multiply ---

template <typename T, int t_m, int t_n, int t_o>
inline mat<T, t_m, t_o> operator*(const mat<T, t_m, t_n> & m1, const mat<T, t_n, t_o> & m2) {
    if constexpr (t_o == 1) return mat<T, t_m, 1>(detail::multCol<0>(m1, m2));
    if constexpr (t_o == 2) return mat<T, t_m, 2>(detail::multCol<0>(m1, m2), detail::multCol<1>(m1, m2));
    if constexpr (t_o == 3) return mat<T, t_m, 3>(detail::multCol<0>(m1, m2), detail::multCol<1>(m1, m2), detail::multCol<2>(m1, m2));
    if constexpr (t_o == 4) return mat<T, t_m, 4>(detail::multCol<0>(m1, m2), detail::multCol<1>(m1, m2), detail::multCol<2>(m1, m2), detail::multCol<3>(m1, m2));
}

template <typename T, int t_m, int t_n>
inline mat<T, t_m, t_n> operator*(const mat<T, t_m, t_n> & m, T v) {
    if constexpr (t_n == 1) return mat<T, t_m, t_n>(detail::multCol<0>(m, v));
    if constexpr (t_n == 2) return mat<T, t_m, t_n>(detail::multCol<0>(m, v), detail::multCol<1>(m, v));
    if constexpr (t_n == 3) return mat<T, t_m, t_n>(detail::multCol<0>(m, v), detail::multCol<1>(m, v), detail::multCol<2>(m, v));
    if constexpr (t_n == 4) return mat<T, t_m, t_n>(detail::multCol<0>(m, v), detail::multCol<1>(m, v), detail::multCol<2>(m, v), detail::multCol<3>(m, v));
}

template <typename T, int t_m, int t_n>
inline mat<T, t_m, t_n> operator*(T v, const mat<T, t_m, t_n> & m) {
    return m * v;
}

template <typename T, int t_m, int t_n>
inline vec<T, t_m> operator*(const mat<T, t_m, t_n> & m, const vec<T, t_n> & v) {
    if constexpr (t_m == 1) return vec1<T>(detail::multRow<0>(m, v));
    if constexpr (t_m == 2) return vec2<T>(detail::multRow<0>(m, v), detail::multRow<1>(m, v));
    if constexpr (t_m == 3) return vec3<T>(detail::multRow<0>(m, v), detail::multRow<1>(m, v), detail::multRow<2>(m, v));
    if constexpr (t_m == 4) return vec4<T>(detail::multRow<0>(m, v), detail::multRow<1>(m, v), detail::multRow<2>(m, v), detail::multRow<3>(m, v));
}

//--- divide ---

template <typename T, int t_m, int t_n>
inline mat<T, t_m, t_n> operator/(const mat<T, t_m, t_n> & m, T v) {
    return m * (T(1.0) / v);
}

template <typename T, int t_m, int t_n>
inline mat<T, t_m, t_n> operator/(T v, const mat<T, t_m, t_n> & m) {
    if constexpr (t_n == 1) return mat<T, t_m, t_n>(detail::divCol<0>(v, m));
    if constexpr (t_n == 2) return mat<T, t_m, t_n>(detail::divCol<0>(v, m), detail::divCol<1>(v, m));
    if constexpr (t_n == 3) return mat<T, t_m, t_n>(detail::divCol<0>(v, m), detail::divCol<1>(v, m), detail::divCol<2>(v, m));
    if constexpr (t_n == 4) return mat<T, t_m, t_n>(detail::divCol<0>(v, m), detail::divCol<1>(v, m), detail::divCol<2>(v, m), detail::divCol<3>(v, m));
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T, int t_m, int t_n>
inline bool operator==(const mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2) {
    if constexpr (t_n == 1) return m1.col<0>() == m2.col<0>();
    if constexpr (t_n == 2) return m1.col<0>() == m2.col<0>() && m1.col<1>() == m2.col<1>();
    if constexpr (t_n == 3) return m1.col<0>() == m2.col<0>() && m1.col<1>() == m2.col<1>() && m1.col<2>() == m2.col<2>();
    if constexpr (t_n == 4) return m1.col<0>() == m2.col<0>() && m1.col<1>() == m2.col<1>() && m1.col<2>() == m2.col<2>() && m1.col<3>() == m2.col<3>();
}

//--- not equal to ---

template <typename T, int t_m, int t_n>
inline bool operator!=(const mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2) {
    return !(m1 == m2);
}



//------------------------------------------------------------------------------
// Constants



template <typename T, int t_m, int t_n>
constexpr mat<T, t_m, t_n> fullMat(T v) {
    if constexpr (t_n == 1) return mat<T, t_m, 1>(vec<T, t_m>(v));
    if constexpr (t_n == 2) return mat<T, t_m, 2>(vec<T, t_m>(v), vec<T, t_m>(v));
    if constexpr (t_n == 3) return mat<T, t_m, 3>(vec<T, t_m>(v), vec<T, t_m>(v), vec<T, t_m>(v));
    if constexpr (t_n == 4) return mat<T, t_m, 4>(vec<T, t_m>(v), vec<T, t_m>(v), vec<T, t_m>(v), vec<T, t_m>(v));
}

template <typename T, int t_m, int t_n>
constexpr mat<T, t_m, t_n> nullMat() {
    return fullMat<T, t_m, t_n>(T(0.0));
}



}