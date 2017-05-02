#pragma once



/*
    The mat structs need to be of standard layout.
    std::is_standard_layout

    Column-major ordering
    x1 x2 x3	00 03 06
    y1 y2 y3	01 04 07
    z1 z2 z3	02 05 08
*/



#include "QVector.hpp"



namespace qmu {



template <typename T, nat t_m, nat t_n = t_m> struct mat;



template <typename T> using mat2 = mat<T, 2>;
template <typename T> using mat3 = mat<T, 3>;
template <typename T> using mat4 = mat<T, 4>;

template <nat t_m, nat t_n> using  fmat = mat< float, t_m, t_n>;
template <nat t_m, nat t_n> using  dmat = mat<double, t_m, t_n>;

using  fmat2 = mat< float, 2>;
using  fmat3 = mat< float, 3>;
using  fmat4 = mat< float, 4>;
using  dmat2 = mat<double, 2>;
using  dmat3 = mat<double, 3>;
using  dmat4 = mat<double, 4>;




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT2 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct mat<T, 2, 2> {

    static constexpr nat t_m = 2, t_n = 2;

    union {
        struct {
            T x1, y1;
            T x2, y2;
        };
    };

    //--- constructors ---

    constexpr mat();
    constexpr mat(const mat2<T> & m);
    constexpr mat(mat2<T> && m);

    template <typename U> constexpr explicit mat(const mat2<U> & m);

    constexpr mat(
        const T & x1, const T & y1,
        const T & x2, const T & y2
    );
    constexpr explicit mat(const mat3<T> & m);
    constexpr explicit mat(const mat4<T> & m);
    constexpr mat(
        const vec2<T> & v1,
        const vec2<T> & v2
    );

    //--- assignment operators ---

    mat2<T> & operator=(const mat2<T> & m);
    mat2<T> & operator=(mat2<T> && m);

    mat2<T> & operator=(const mat3<T> & m);
    mat2<T> & operator=(const mat4<T> & m);

    //--- access operators ---

    T & operator[](nat i);
    const T & operator[](nat i) const;

    //--- other ---

    std::string toString() const;

};

//--- arithmetic assignment operators ---

template <typename T> mat2<T> & operator+=(mat2<T> &  m, const      T  &  v);
template <typename T> mat2<T> & operator+=(mat2<T> & m1, const mat2<T> & m2);

template <typename T> mat2<T> & operator-=(mat2<T> &  m, const      T  &  v);
template <typename T> mat2<T> & operator-=(mat2<T> & m1, const mat2<T> & m2);

template <typename T> mat2<T> & operator*=(mat2<T> &  m, const      T  &  v);
template <typename T> mat2<T> & operator*=(mat2<T> & m1, const mat2<T> & m2);

template <typename T> mat2<T> & operator/=(mat2<T> & m, const T & v);

template <typename T> mat2<T> & operator++(mat2<T> & m);
template <typename T> mat2<T>   operator++(mat2<T> & m, int);

template <typename T> mat2<T> & operator--(mat2<T> & m);
template <typename T> mat2<T>   operator--(mat2<T> & m, int);

//--- arithmetic operators ---

template <typename T> mat2<T> operator+(const mat2<T> & m);

template <typename T> mat2<T> operator-(const mat2<T> & m);

template <typename T> mat2<T> operator+(const mat2<T> & m1, const mat2<T> & m2);
template <typename T> mat2<T> operator+(const mat2<T> &  m, const      T  &  v);
template <typename T> mat2<T> operator+(const      T  &  v, const mat2<T> & m1);

template <typename T> mat2<T> operator-(const mat2<T> & m1, const mat2<T> & m2);
template <typename T> mat2<T> operator-(const mat2<T> &  m, const      T  &  v);
template <typename T> mat2<T> operator-(const      T  &  v, const mat2<T> &  m);

template <typename T> mat2<T> operator*(const mat2<T> & m1, const mat2<T> & m2);
template <typename T> mat2<T> operator*(const mat2<T> &  m, const      T  &  v);
template <typename T> mat2<T> operator*(const      T  &  v, const mat2<T> &  m);
template <typename T> vec2<T> operator*(const mat2<T> &  m, const vec2<T> &  v);

template <typename T> mat2<T> operator/(const mat2<T> &  m, const      T  & v);
template <typename T> mat2<T> operator/(const      T  &  v, const mat2<T> & m);

//--- comparison operators ---

template <typename T> bool operator==(const mat2<T> & m1, const mat2<T> & m2);
template <typename T> bool operator!=(const mat2<T> & m1, const mat2<T> & m2);

//--- other ---

template <typename T>
std::ostream & operator<<(std::ostream & os, const mat2<T> & m);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT3 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct mat<T, 3, 3> {

    static constexpr nat t_m = 3, t_n = 3;

    union {
        struct {
            T x1, y1, z1;
            T x2, y2, z2;
            T x3, y3, z3;
        };
    };

    //--- constructors ---

    constexpr mat();
    constexpr mat(const mat3<T> & m);
    constexpr mat(mat3<T> && m);

    template <typename U> constexpr explicit mat(const mat3<U> & m);

    constexpr mat(
        const T & x1, const T & y1, const T & z1,
        const T & x2, const T & y2, const T & z2,
        const T & x3, const T & y3, const T & z3
    );
    constexpr explicit mat(const mat2<T> & m);
    constexpr explicit mat(const mat4<T> & m);
    constexpr mat(
        const vec3<T> & v1,
        const vec3<T> & v2,
        const vec3<T> & v3
    );

    //--- assignment operators ---

    mat3<T> & operator=(const mat3<T> & m);
    mat3<T> & operator=(mat3<T> && m);

    mat3<T> & operator=(const mat2<T> & m);
    mat3<T> & operator=(const mat4<T> & m);

    //--- access operators ---

    T & operator[](nat i);
    const T & operator[](nat i) const;

    //--- other ---

    std::string toString() const;

};

//--- arithmetic assignment operators ---

template <typename T> mat3<T> & operator+=(mat3<T> &  m, const      T  &  v);
template <typename T> mat3<T> & operator+=(mat3<T> & m1, const mat3<T> & m2);

template <typename T> mat3<T> & operator-=(mat3<T> &  m, const      T  &  v);
template <typename T> mat3<T> & operator-=(mat3<T> & m1, const mat3<T> & m2);

template <typename T> mat3<T> & operator*=(mat3<T> &  m, const      T  &  v);
template <typename T> mat3<T> & operator*=(mat3<T> & m1, const mat3<T> & m2);

template <typename T> mat3<T> & operator/=(mat3<T> & m, const T & v);

template <typename T> mat3<T> & operator++(mat3<T> & m);
template <typename T> mat3<T>   operator++(mat3<T> & m, int);

template <typename T> mat3<T> & operator--(mat3<T> & m);
template <typename T> mat3<T>   operator--(mat3<T> & m, int);

//--- arithmetic operators ---

template <typename T> mat3<T> operator+(const mat3<T> & m);

template <typename T> mat3<T> operator-(const mat3<T> & m);

template <typename T> mat3<T> operator+(const mat3<T> & m1, const mat3<T> & m2);
template <typename T> mat3<T> operator+(const mat3<T> &  m, const      T  &  v);
template <typename T> mat3<T> operator+(const      T  &  v, const mat3<T> &  m);

template <typename T> mat3<T> operator-(const mat3<T> & m1, const mat3<T> & m2);
template <typename T> mat3<T> operator-(const mat3<T> &  m, const      T  &  v);
template <typename T> mat3<T> operator-(const      T  &  v, const mat3<T> &  m);

template <typename T> mat3<T> operator*(const mat3<T> & m1, const mat3<T> & m2);
template <typename T> mat3<T> operator*(const mat3<T> &  m, const      T  &  v);
template <typename T> mat3<T> operator*(const      T  &  v, const mat3<T> &  m);
template <typename T> vec3<T> operator*(const mat3<T> & m1, const vec3<T> &  v);

template <typename T> mat3<T> operator/(const mat3<T> & m1, const      T  & v);
template <typename T> mat3<T> operator/(const      T  &  v, const mat3<T> & m);

//--- comparison operators ---

template <typename T> bool operator==(const mat3<T> & m1, const mat3<T> & m2);

template <typename T> bool operator!=(const mat3<T> & m1, const mat3<T> & m2);

//--- other ---

template <typename T> std::ostream & operator<<(std::ostream & os, const mat3<T> & m);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT4 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct mat<T, 4, 4> {

    static constexpr nat t_m = 4, t_n = 4;

    union {
        struct {
            T x1, y1, z1, w1;
            T x2, y2, z2, w2;
            T x3, y3, z3, w3;
            T x4, y4, z4, w4;
        };
    };

    //--- constructors ---

    constexpr mat();
    constexpr mat(const mat4<T> & m);
    constexpr mat(mat4<T> && m);

    template <typename U> constexpr explicit mat(const mat4<U> & m);

    constexpr mat(
        const T & x1, const T & y1, const T & z1, const T & w1,
        const T & x2, const T & y2, const T & z2, const T & w2,
        const T & x3, const T & y3, const T & z3, const T & w3,
        const T & x4, const T & y4, const T & z4, const T & w4
    );
    constexpr explicit mat(const mat2<T> & m);
    constexpr explicit mat(const mat3<T> & m);
    constexpr mat(
        const vec4<T> & v1,
        const vec4<T> & v2,
        const vec4<T> & v3,
        const vec4<T> & v4
    );

    //--- assignment operators ---

    mat4<T> & operator=(const mat4<T> & m);
    mat4<T> & operator=(mat4<T> && m);

    mat4<T> & operator=(const mat2<T> & m);
    mat4<T> & operator=(const mat3<T> & m);

    //--- access operators ---

    T & operator[](nat i);
    const T & operator[](nat i) const;

    //--- other ---

    std::string toString() const;

};

//--- arithmetic assignment operators ---

template <typename T> mat4<T> & operator+=(mat4<T> & m, const T & v);
template <typename T> mat4<T> & operator+=(mat4<T> & m1, const mat4<T> & m2);

template <typename T> mat4<T> & operator-=(mat4<T> & m, const T & v);
template <typename T> mat4<T> & operator-=(mat4<T> & m1, const mat4<T> & m2);

template <typename T> mat4<T> & operator*=(mat4<T> & m, const T & v);
template <typename T> mat4<T> & operator*=(mat4<T> & m1, const mat4<T> & m2);

template <typename T> mat4<T> & operator/=(mat4<T> & m, const T & v);

template <typename T> mat4<T> & operator++(mat4<T> & m);
template <typename T> mat4<T>   operator++(mat4<T> & m, int);

template <typename T> mat4<T> & operator--(mat4<T> & m);
template <typename T> mat4<T>   operator--(mat4<T> & m, int);

//--- arithmetic operators ---

template <typename T> mat4<T> operator+(const mat4<T> & m);

template <typename T> mat4<T> operator-(const mat4<T> & m);

template <typename T> mat4<T> operator+(const mat4<T> & m1, const mat4<T> & m2);
template <typename T> mat4<T> operator+(const mat4<T> &  m, const      T  &  v);
template <typename T> mat4<T> operator+(const      T  &  v, const mat4<T> &  m);

template <typename T> mat4<T> operator-(const mat4<T> & m1, const mat4<T> & m2);
template <typename T> mat4<T> operator-(const mat4<T> &  m, const      T  &  v);
template <typename T> mat4<T> operator-(const      T  &  v, const mat4<T> &  m);

template <typename T> mat4<T> operator*(const mat4<T> & m1, const mat4<T> & m2);
template <typename T> mat4<T> operator*(const mat4<T> &  m, const      T  &  v);
template <typename T> mat4<T> operator*(const      T  &  v, const mat4<T> &  m);
template <typename T> vec4<T> operator*(const mat4<T> &  m, const vec4<T> &  v);

template <typename T> mat4<T> operator/(const mat4<T> & m, const      T  & v);
template <typename T> mat4<T> operator/(const      T  & v, const mat4<T> & m);

//--- comparison operators ---

template <typename T> bool operator==(const mat4<T> & m1, const mat4<T> & m2);

template <typename T> bool operator!=(const mat4<T> & m1, const mat4<T> & m2);

//--- other ---

template <typename T> std::ostream & operator<<(std::ostream & os, const mat4<T> & m);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT FUNCTIONS -------------------------------------------------------------------------------------------------------



template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> transpose(const mat<T, t_m, t_n> & m);

template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> cofactor(const mat<T, t_m, t_n> & m);

template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> adjoint(const mat<T, t_m, t_n> & m);

template <typename T, nat t_m, nat t_n> T determinant(const mat<T, t_m, t_n> & m);

template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> inverse(const mat<T, t_m, t_n> & m);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORMATIONS -----------------------------------------------------------------------------------------------------



template <typename T, nat t_n> mat<T, t_n + 1> translate(const vec<T, t_n> & delta);
template <typename T, nat t_n> mat<T, t_n + 1> translate(mat<T, t_n + 1> mat, const vec<T, t_n> & delta);

template <typename T, nat t_n> mat<T, t_n> scale(const vec<T, t_n> & scale);
template <typename T, nat t_n> mat<T, t_n> scale(mat<T, t_n> mat, const vec<T, t_n> & scale);
template <typename T, nat t_n> mat<T, t_n + 1> scale(mat<T, t_n + 1> mat, const vec<T, t_n> & scale);

template <typename T> mat2<T> rotate(const T & theta);

template <typename T> mat3<T> rotateX(const T & theta);

template <typename T> mat3<T> rotateY(const T & theta);

template <typename T> mat3<T> rotateZ(const T & theta);

template <typename T> mat3<T> rotate(const vec3<T> & axis, const T & sinTheta, const T & cosTheta);
template <typename T> mat3<T> rotate_n(const vec3<T> & axis, const T & sinTheta, const T & cosTheta);

template <typename T> mat3<T> rotate(const vec3<T> & axis, const T & theta);
template <typename T> mat3<T> rotate_n(const vec3<T> & axis, const T & theta);

//theta: thumb points up, phi: right, psi: forward
template <typename T> mat3<T> euler(const vec3<T> & forward, const vec3<T> & up, const T & theta, const T & phi, const T & psi);
template <typename T> mat3<T> euler_n(const vec3<T> & forward, const vec3<T> & up, const T & theta, const T & phi, const T & psi);

template <typename T, nat t_n> mat<T, t_n> align(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, nat t_n> mat<T, t_n> align_n(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

//expects orthogonal fvectors
template <typename T> mat3<T> align(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2);
template <typename T> mat3<T> align_n(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2);

// _o variants (orthogonal) usable when the transformation matrix, T, from basis
// A to B is orthogonal i.e. A's basis vectors don't need to be orthogonal, nor
// B's, but the angles between A's basis vectors must be the same as B's
template <typename T> mat2<T> map(const vec2<T> & x1, const vec2<T> & y1, const vec2<T> & x2, const vec2<T> & y2);
template <typename T> mat2<T> map_o(const vec2<T> & x1, const vec2<T> & y1, const vec2<T> & x2, const vec2<T> & y2);
template <typename T> mat3<T> map(const vec3<T> & x1, const vec3<T> & y1, const vec3<T> & z1, const vec3<T> & x2, const vec3<T> & y2, const vec3<T> & z2);
template <typename T> mat3<T> map_o(const vec3<T> & x1, const vec3<T> & y1, const vec3<T> & z1, const vec3<T> & x2, const vec3<T> & y2, const vec3<T> & z2);

template <typename T> mat2<T> mapTo(const vec2<T> & x, const vec2<T> & y);
template <typename T> mat2<T> mapTo_o(const vec2<T> & x, const vec2<T> & y);
template <typename T> mat3<T> mapTo(const vec3<T> & x, const vec3<T> & y, const vec3<T> & z);
template <typename T> mat3<T> mapTo_o(const vec3<T> & x, const vec3<T> & y, const vec3<T> & z);

template <typename T> mat2<T> mapFrom(const vec2<T> & x, const vec2<T> & y);
template <typename T> mat3<T> mapFrom(const vec3<T> & x, const vec3<T> & y, const vec3<T> & z);

template <typename T> mat4<T> orthoProj(const T & width, const T & height, const T & near, const T & far);
template <typename T> mat4<T> orthoProjAsym(const T & left, const T & right, const T & bottom, const T & top, const T & near, const T & far);

//fov is angle in radians between top and bottom planes, aspectRatio is screen width / height, zNear is distance to near plane, zFar is distance to far plane
template <typename T> mat4<T> perspProj(const T & fov, const T & aspectRatio, const T & near, const T & far);
//fovNX is angle between center and left plane, fovPX between center and right, fovNY between center and bottom, fovPY between center and top
template <typename T> mat4<T> perspProjAsym(const T & fovLeft, const T & fovRight, const T & fovBottom, const T & fovTop, const T & near, const T & far);

//forward and up must not be parallel
template <typename T> mat4<T> view(const vec3<T> & camLoc, const vec3<T> & camForward, const vec3<T> & up);

template <typename T> mat4<T> view(const vec3<T> & camLoc, const vec3<T> & camX, const vec3<T> & camY, const vec3<T> & camZ);
template <typename T> mat4<T> view_n(const vec3<T> & camLoc, const vec3<T> & camX, const vec3<T> & camY, const vec3<T> & camZ);
//basis vectors are orthonormal (optimization)
template <typename T> mat4<T> view_o(const vec3<T> & camLoc, const vec3<T> & camX, const vec3<T> & camY, const vec3<T> & camZ);
template <typename T> mat4<T> view_on(const vec3<T> & camLoc, const vec3<T> & camX, const vec3<T> & camY, const vec3<T> & camZ);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT2 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr mat<T, 2, 2>::mat() :
    x1(1), y1(0),
    x2(0), y2(1)
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
    x1(static_cast<T>(m.x1)), y1(static_cast<T>(m.y1)),
    x2(static_cast<T>(m.x2)), y2(static_cast<T>(m.y2))
{}

template <typename T>
constexpr mat<T, 2, 2>::mat(
    const T & x1, const T & y1,
    const T & x2, const T & y2
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
// Assignment Operators



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
inline mat2<T> & mat<T, 2, 2>::operator=(const mat3<T> & m) {
    x1 = m.x1; y1 = m.y1;
    x2 = m.x2; y2 = m.y2;
    return *this;
}

template <typename T>
inline mat2<T> & mat<T, 2, 2>::operator=(const mat4<T> & m) {
    x1 = m.x1; y1 = m.y1;
    x2 = m.x2; y2 = m.y2;
    return *this;
}



//------------------------------------------------------------------------------
// Access Operators



template <typename T>
inline T & mat<T, 2, 2>::operator[](nat i) {
    return *(&x1 + i);
}



template <typename T>
inline const T & mat<T, 2, 2>::operator[](nat i) const {
    return *(&x1 + i);
}



//------------------------------------------------------------------------------
// Arithmetic Assignment Operators



//--- add assign ---

template <typename T>
inline mat2<T> & operator+=(mat2<T> & m, const T & v) {
    return m = m + v;
}

template <typename T>
inline mat2<T> & operator+=(mat2<T> & m1, const mat2<T> & m2) {
    return m1 = m1 + m2;
}

//--- subtract assign ---

template <typename T>
inline mat2<T> & operator-=(mat2<T> & m, const T & v) {
    return m = m - v;
}

template <typename T>
inline mat2<T> & operator-=(mat2<T> & m1, const mat2<T> & m2) {
    return m1 = m1 - m2;
}

//--- multiply assign ---

template <typename T>
inline mat2<T> & operator*=(mat2<T> & m, const T & v) {
    return m = m * v;
}

template <typename T>
inline mat2<T> & operator*=(mat2<T> & m1, const mat2<T> & m2) {
    return m1 = m1 * m2;
}

//--- divide assign ---

template <typename T>
inline mat2<T> & operator/=(mat2<T> & m, const T & v) {
    return m = m / v;
}

//--- pre increment ---

template <typename T>
inline mat2<T> & operator++(mat2<T> & m) {
    ++m.x1; ++m.y1;
    ++m.x2; ++m.y2;

    return m;
}

//--- post increment ---

template <typename T>
inline mat2<T> operator++(mat2<T> & m, int) {
    mat2<T> temp(m);
    ++m;

    return temp;
}

//--- pre decrement ---

template <typename T>
inline mat2<T> & operator--(mat2<T> & m) {
    --m.x1; --m.y1;
    --m.x2; --m.y2;

    return m;
}

//--- post decrement ---

template <typename T>
inline mat2<T> operator--(mat2<T> & m, int) {
    mat2<T> temp(m);
    --m;

    return temp;
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- positive ---

template <typename T>
inline mat2<T> operator+(const mat2<T> & m) {
    return mat2<T>(
        +m.x1, +m.y1,
        +m.x2, +m.y2
    );
}

//--- negative ---

template <typename T>
inline mat2<T> operator-(const mat2<T> & m) {
    return mat2<T>(
        -m.x1, -m.y1,
        -m.x2, -m.y2
    );
}

//--- add ---

template <typename T>
inline mat2<T> operator+(const mat2<T> & m1, const mat2<T> & m2) {
    return mat2<T>(
        m1.x1 + m2.x1, m1.y1 + m2.y1,
        m1.x2 + m2.x2, m1.y2 + m2.y2
    );
}

template <typename T>
inline mat2<T> operator+(const mat2<T> & m, const T & v) {
    return mat2<T>(
        m.x1 + v, m.y1 + v,
        m.x2 + v, m.y2 + v
    );
}

template <typename T>
inline mat2<T> operator+(const T & v, const mat2<T> & m) {
    return mat2<T>(
        v + m.x1, v + m.y1,
        v + m.x2, v + m.y2
    );
}

//--- subtract ---

template <typename T>
inline mat2<T> operator-(const mat2<T> & m1, const mat2<T> & m2) {
    return mat2<T>(
        m1.x1 - m2.x1, m1.y1 - m2.y1,
        m1.x2 - m2.x2, m1.y2 - m2.y2
    );
}

template <typename T>
inline mat2<T> operator-(const mat2<T> & m, const T & v) {
    return mat2<T>(
        m.x1 - v, m.y1 - v,
        m.x2 - v, m.y2 - v
    );
}

template <typename T>
inline mat2<T> operator-(const T & v, const mat2<T> & m) {
    return mat2<T>(
        v - m.x1, v - m.y1,
        v - m.x2, v - m.y2
    );
}

//--- multiply ---

template <typename T>
inline mat2<T> operator*(const mat2<T> & m1, const mat2<T> & m2) {
    return mat2<T>(
        m1.x1 * m2.x1 + m1.x2 * m2.y1,
        m1.y1 * m2.x1 + m1.y2 * m2.y1,

        m1.x1 * m2.x2 + m1.x2 * m2.y2,
        m1.y1 * m2.x2 + m1.y2 * m2.y2
    );
}

template <typename T>
inline mat2<T> operator*(const mat2<T> & m, const T & v) {
    return mat2<T>(
        m.x1 * v, m.y1 * v,
        m.x2 * v, m.y2 * v
    );
}

template <typename T>
inline mat2<T> operator*(const T & v, const mat2<T> & m) {
    return mat2<T>(
        v * m.x1, v * m.y1,
        v * m.x2, v * m.y2
    );
}

template <typename T>
inline vec2<T> operator*(const mat2<T> & m, const vec2<T> & v) {
    return vec2<T>(
        v.x * m.x1 + v.y * m.x2,
        v.x * m.y1 + v.y * m.y2
    );
}

//--- divide ---

template <typename T>
inline mat2<T> operator/(const mat2<T> & m, const T & v) {
    return mat2<T>(
        m.x1 / v, m.y1 / v,
        m.x2 / v, m.y2 / v
    );
}

template <typename T>
inline mat2<T> operator/(const T & v, const mat2<T> & m) {
    return mat2<T>(
        v / m.x1, v / m.y1,
        v / m.x2, v / m.y2
    );
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T>
inline bool operator==(const mat2<T> & m1, const mat2<T> & m2) {
    return
        m1.x1 == m2.x1 && m1.y1 == m2.y1 &&
        m1.x2 == m2.x2 && m1.y2 == m2.y2;
}

//--- not equal to ---

template <typename T>
inline bool operator!=(const mat2<T> & m1, const mat2<T> & m2) {
    return
        m1.x1 != m2.x1 || m1.y1 != m2.y1 ||
        m1.x2 != m2.x2 || m1.y2 != m2.y2;
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string mat<T, 2, 2>::toString() const {
    return
        "[ " +
        std::to_string(x1) + " " + std::to_string(y1) +
        " | " +
        std::to_string(x2) + " " + std::to_string(y2) +
        " ]";
}



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const mat2<T> & m) {
    return os << m.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT3 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr mat<T, 3, 3>::mat() :
    x1(1), y1(0), z1(0),
    x2(0), y2(1), z2(0),
    x3(0), y3(0), z3(1)
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
    x1(static_cast<T>(m.x1)), y1(static_cast<T>(m.y1)), z1(static_cast<T>(m.z1)),
    x2(static_cast<T>(m.x2)), y2(static_cast<T>(m.y2)), z2(static_cast<T>(m.z2)),
    x3(static_cast<T>(m.x3)), y3(static_cast<T>(m.y3)), z3(static_cast<T>(m.z3))
{}

template <typename T>
constexpr mat<T, 3, 3>::mat(
    const T & x1, const T & y1, const T & z1,
    const T & x2, const T & y2, const T & z2,
    const T & x3, const T & y3, const T & z3
) :
    x1(x1), y1(y1), z1(z1),
    x2(x2), y2(y2), z2(z2),
    x3(x3), y3(y3), z3(z3)
{}

template <typename T>
constexpr mat<T, 3, 3>::mat(const mat2<T> & m) :
    x1(m.x1), y1(m.y1), z1(0),
    x2(m.x2), y2(m.y2), z2(0),
    x3(0), y3(0), z3(1)
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
// Assignment Operators



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
inline mat3<T> & mat<T, 3, 3>::operator=(const mat2<T> & m) {
    x1 = m.x1; y1 = m.y1; z1 = 0;
    x2 = m.x2; y2 = m.y2; z2 = 0;
    x3 = 0; y3 = 0; z3 = 1;

    return *this;

}

template <typename T>
inline mat3<T> & mat<T, 3, 3>::operator=(const mat4<T> & m) {
    x1 = m.x1; y1 = m.y1; z1 = m.z1;
    x2 = m.x2; y2 = m.y2; z2 = m.z2;
    x3 = m.x3; y3 = m.y3; z3 = m.z3;

    return *this;
}



//------------------------------------------------------------------------------
// Access Operators



template <typename T>
inline T & mat<T, 3, 3>::operator[](nat i) {
    return *(&x1 + i);
}



template <typename T>
inline const T & mat<T, 3, 3>::operator[](nat i) const {
    return *(&x1 + i);
}



//------------------------------------------------------------------------------
// Arithmetic Assignment Operators



//--- add assign ---

template <typename T>
inline mat3<T> & operator+=(mat3<T> & m, const T & v) {
    return m = m + v;
}

template <typename T>
inline mat3<T> & operator+=(mat3<T> & m1, const mat3<T> & m2) {
    return m1 = m1 + m2;
}

//--- subtract assign ---

template <typename T>
inline mat3<T> & operator-=(mat3<T> & m, const T & v) {
    return m = m - v;
}

template <typename T>
inline mat3<T> & operator-=(mat3<T> & m1, const mat3<T> & m2) {
    return m1 = m1 - m2;
}

//--- multiply assign ---

template <typename T>
inline mat3<T> & operator*=(mat3<T> & m, const T & v) {
    return m = m * v;
}

template <typename T>
inline mat3<T> & operator*=(mat3<T> & m1, const mat3<T> & m2) {
    return m1 = m1 * m2;
}

//--- divide assign ---

template <typename T>
inline mat3<T> & operator/=(mat3<T> & m, const T & v) {
    return m = m / v;
}

//--- pre increment ---

template <typename T>
inline mat3<T> & operator++(mat3<T> & m) {
    ++m.x1; ++m.y1; ++m.z1;
    ++m.x2; ++m.y2; ++m.z2;
    ++m.x3; ++m.y3; ++m.z3;

    return m;
}

//--- post increment ---

template <typename T>
inline mat3<T> operator++(mat3<T> & m, int) {
    mat3<T> temp(m);
    ++m;

    return temp;
}

//--- pre decrement ---

template <typename T>
inline mat3<T> & operator--(mat3<T> & m) {
    --m.x1; --m.y1; --m.z1;
    --m.x2; --m.y2; --m.z2;
    --m.x3; --m.y3; --m.z3;

    return m;
}

//--- post decrement ---

template <typename T>
inline mat3<T> operator--(mat3<T> & m, int) {
    mat3<T> temp(m);
    --m;

    return temp;
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- positive ---

template <typename T>
inline mat3<T> operator+(const mat3<T> & m) {
    return mat3<T>(
        +m.x1, +m.y1, +m.z1,
        +m.x2, +m.y2, +m.z2,
        +m.x3, +m.y3, +m.z3
    );
}

//--- negative ---

template <typename T>
inline mat3<T> operator-(const mat3<T> & m) {
    return mat3<T>(
        -m.x1, -m.y1, -m.z1,
        -m.x2, -m.y2, -m.z2,
        -m.x3, -m.y3, -m.z3
    );
}

//--- add ---

template <typename T>
inline mat3<T> operator+(const mat3<T> & m1, const mat3<T> & m2) {
    return mat3<T>(
        m1.x1 + m2.x1, m1.y1 + m2.y1, m1.z1 + m2.z1,
        m1.x2 + m2.x2, m1.y2 + m2.y2, m1.z2 + m2.z2,
        m1.x3 + m2.x3, m1.y3 + m2.y3, m1.z3 + m2.z3
    );
}

template <typename T>
inline mat3<T> operator+(const mat3<T> & m, const T & v) {
    return mat3<T>(
        m.x1 + v, m.y1 + v, m.z1 + v,
        m.x2 + v, m.y2 + v, m.z2 + v,
        m.x3 + v, m.y3 + v, m.z3 + v
    );
}

template <typename T>
inline mat3<T> operator+(const T & v, const mat3<T> & m) {
    return mat3<T>(
        v + m.x1, v + m.y1, v + m.z1,
        v + m.x2, v + m.y2, v + m.z2,
        v + m.x3, v + m.y3, v + m.z3
    );
}

//--- subtract ---

template <typename T>
inline mat3<T> operator-(const mat3<T> & m1, const mat3<T> & m2) {
    return mat3<T>(
        m1.x1 - m2.x1, m1.y1 - m2.y1, m1.z1 - m2.z1,
        m1.x2 - m2.x2, m1.y2 - m2.y2, m1.z2 - m2.z2,
        m1.x3 - m2.x3, m1.y3 - m2.y3, m1.z3 - m2.z3
    );
}

template <typename T>
inline mat3<T> operator-(const mat3<T> & m, const T & v) {
    return mat3<T>(
        m.x1 - v, m.y1 - v, m.z1 - v,
        m.x2 - v, m.y2 - v, m.z2 - v,
        m.x3 - v, m.y3 - v, m.z3 - v
    );
}

template <typename T>
inline mat3<T> operator-(const T & v, const mat3<T> & m) {
    return mat3<T>(
        v - m.x1, v - m.y1, v - m.z1,
        v - m.x2, v - m.y2, v - m.z2,
        v - m.x3, v - m.y3, v - m.z3
    );
}

//--- multiply ---

template <typename T>
inline mat3<T> operator*(const mat3<T> & m1, const mat3<T> & m2) {
    return mat3<T>(
        m1.x1 * m2.x1 + m1.x2 * m2.y1 + m1.x3 * m2.z1,
        m1.y1 * m2.x1 + m1.y2 * m2.y1 + m1.y3 * m2.z1,
        m1.z1 * m2.x1 + m1.z2 * m2.y1 + m1.z3 * m2.z1,

        m1.x1 * m2.x2 + m1.x2 * m2.y2 + m1.x3 * m2.z2,
        m1.y1 * m2.x2 + m1.y2 * m2.y2 + m1.y3 * m2.z2,
        m1.z1 * m2.x2 + m1.z2 * m2.y2 + m1.z3 * m2.z2,

        m1.x1 * m2.x3 + m1.x2 * m2.y3 + m1.x3 * m2.z3,
        m1.y1 * m2.x3 + m1.y2 * m2.y3 + m1.y3 * m2.z3,
        m1.z1 * m2.x3 + m1.z2 * m2.y3 + m1.z3 * m2.z3
    );
}

template <typename T>
inline mat3<T> operator*(const mat3<T> & m, const T & v) {
    return mat3<T>(
        m.x1 * v, m.y1 * v, m.z1 * v,
        m.x2 * v, m.y2 * v, m.z2 * v,
        m.x3 * v, m.y3 * v, m.z3 * v
    );
}

template <typename T>
inline mat3<T> operator*(const T & v, const mat3<T> & m) {
    return mat3<T>(
        v * m.x1, v * m.y1, v * m.z1,
        v * m.x2, v * m.y2, v * m.z2,
        v * m.x3, v * m.y3, v * m.z3
    );
}

template <typename T>
inline vec3<T> operator*(const mat3<T> & m, const vec3<T> & v) {
    return vec3<T>(
        v.x * m.x1 + v.y * m.x2 + v.z * m.x3,
        v.x * m.y1 + v.y * m.y2 + v.z * m.y3,
        v.x * m.z1 + v.y * m.z2 + v.z * m.z3
    );
}

//--- divide ---

template <typename T>
inline mat3<T> operator/(const mat3<T> & m, const T & v) {
    return mat3<T>(
        m.x1 / v, m.y1 / v, m.z1 / v,
        m.x2 / v, m.y2 / v, m.z2 / v,
        m.x3 / v, m.y3 / v, m.z3 / v
    );
}

template <typename T>
inline mat3<T> operator/(const T & v, const mat3<T> & m) {
    return mat3<T>(
        v / m.x1, v / m.y1, v / m.z1,
        v / m.x2, v / m.y2, v / m.z2,
        v / m.x3, v / m.y3, v / m.z3
    );
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T>
inline bool operator==(const mat3<T> & m1, const mat3<T> & m2) {
    return
        m1.x1 == m2.x1 && m1.y1 == m2.y1 && m1.z1 == m2.z1 &&
        m1.x2 == m2.x2 && m1.y2 == m2.y2 && m1.z2 == m2.z2 &&
        m1.x3 == m2.x3 && m1.y3 == m2.y3 && m1.z3 == m2.z3;
}

//--- not equal to ---

template <typename T>
inline bool operator!=(const mat3<T> & m1, const mat3<T> & m2) {
    return
        m1.x1 != m2.x1 || m1.y1 != m2.y1 || m1.z1 != m2.z1 ||
        m1.x2 != m2.x2 || m1.y2 != m2.y2 || m1.z2 != m2.z2 ||
        m1.x3 != m2.x3 || m1.y3 != m2.y3 || m1.z3 != m2.z3;
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string mat<T, 3, 3>::toString() const {
    return
        "[ " +
        std::to_string(x1) + " " + std::to_string(y1) + " " + std::to_string(z1) +
        " | " +
        std::to_string(x2) + " " + std::to_string(y2) + " " + std::to_string(z2) +
        " | " +
        std::to_string(x3) + " " + std::to_string(y3) + " " + std::to_string(z3) +
        " ]";
}



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const mat3<T> & m) {
    return os << m.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT4 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr mat<T, 4, 4>::mat() :
    x1(1), y1(0), z1(0), w1(0),
    x2(0), y2(1), z2(0), w2(0),
    x3(0), y3(0), z3(1), w3(0),
    x4(0), y4(0), z4(0), w4(1)
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
    x1(static_cast<T>(m.x1)), y1(static_cast<T>(m.y1)), z1(static_cast<T>(m.z1)), w1(static_cast<T>(m.w1)),
    x2(static_cast<T>(m.x2)), y2(static_cast<T>(m.y2)), z2(static_cast<T>(m.z2)), w2(static_cast<T>(m.w2)),
    x3(static_cast<T>(m.x3)), y3(static_cast<T>(m.y3)), z3(static_cast<T>(m.z3)), w3(static_cast<T>(m.w3)),
    x4(static_cast<T>(m.x4)), y4(static_cast<T>(m.y4)), z4(static_cast<T>(m.z4)), w4(static_cast<T>(m.w4))
{}

template <typename T>
constexpr mat<T, 4, 4>::mat(
    const T & x1, const T & y1, const T & z1, const T & w1,
    const T & x2, const T & y2, const T & z2, const T & w2,
    const T & x3, const T & y3, const T & z3, const T & w3,
    const T & x4, const T & y4, const T & z4, const T & w4
) :
    x1(x1), y1(y1), z1(z1), w1(w1),
    x2(x2), y2(y2), z2(z2), w2(w2),
    x3(x3), y3(y3), z3(z3), w3(w3),
    x4(x4), y4(y4), z4(z4), w4(w4)
{}

template <typename T>
constexpr mat<T, 4, 4>::mat(const mat2<T> & m) :
    x1(m.x1), y1(m.y1), z1(0), w1(0),
    x2(m.x2), y2(m.y2), z2(0), w2(0),
    x3(0), y3(0), z3(1), w3(0),
    x4(0), y4(0), z4(0), w4(1)
{}

template <typename T>
constexpr mat<T, 4, 4>::mat(const mat3<T> & m) :
    x1(m.x1), y1(m.y1), z1(m.z1), w1(0),
    x2(m.x2), y2(m.y2), z2(m.z2), w2(0),
    x3(m.x3), y3(m.y3), z3(m.z3), w3(0),
    x4(0), y4(0), z4(0), w4(1)
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
// Assignment Operators



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
inline mat4<T> & mat<T, 4, 4>::operator=(const mat2<T> & m) {
    x1 = m.x1; y1 = m.y1; z1 = 0; w1 = 0;
    x2 = m.x2; y2 = m.y2; z2 = 0; w2 = 0;
    x3 = 0; y3 = 0; z3 = 1; w3 = 0;
    x4 = 0; y4 = 0; z4 = 0; w4 = 1;

    return *this;
}

template <typename T>
inline mat4<T> & mat<T, 4, 4>::operator=(const mat3<T> & m) {
    x1 = m.x1; y1 = m.y1; z1 = m.z1; w1 = 0;
    x2 = m.x2; y2 = m.y2; z2 = m.z2; w2 = 0;
    x3 = m.x3; y3 = m.y3; z3 = m.z3; w3 = 0;
    x4 = 0; y4 = 0; z4 = 0; w4 = 1;

    return *this;
}



//------------------------------------------------------------------------------
// Access Operators



template <typename T>
inline T & mat<T, 4, 4>::operator[](nat i) {
    return *(&x1 + i);
}



template <typename T>
inline const T & mat<T, 4, 4>::operator[](nat i) const {
    return *(&x1 + i);
}



//------------------------------------------------------------------------------
// Arithmetic Assignment Operators



//--- add assign ---

template <typename T>
inline mat4<T> & operator+=(mat4<T> & m, const T & v) {
    return m = m + v;
}

template <typename T>
inline mat4<T> & operator+=(mat4<T> & m1, const mat4<T> & m2) {
    return m1 = m1 + m2;
}

//--- subtract assign ---

template <typename T>
inline mat4<T> & operator-=(mat4<T> & m, const T & v) {
    return m = m - v;
}

template <typename T>
inline mat4<T> & operator-=(mat4<T> & m1, const mat4<T> & m2) {
    return m1 = m1 - m2;
}

//--- multiply assign ---

template <typename T>
inline mat4<T> & operator*=(mat4<T> & m, const T & v) {
    return m = m * v;
}

template <typename T>
inline mat4<T> & operator*=(mat4<T> & m1, const mat4<T> & m2) {
    return m1 = m1 * m2;
}

//--- divide assign ---

template <typename T>
inline mat4<T> & operator/=(mat4<T> & m, const T & v) {
    return m = m / v;
}

//--- pre increment ---

template <typename T>
inline mat4<T> & operator++(mat4<T> & m) {
    ++m.x1; ++m.y1; ++m.z1; ++m.w1;
    ++m.x2; ++m.y2; ++m.z2; ++m.w2;
    ++m.x3; ++m.y3; ++m.z3; ++m.w3;
    ++m.x4; ++m.y4; ++m.z4; ++m.w4;

    return m;
}

//--- post increment ---

template <typename T>
inline mat4<T> operator++(mat4<T> & m, int) {
    mat4<T> temp(m);
    ++m;

    return temp;
}

//--- pre decrement ---

template <typename T>
inline mat4<T> & operator--(mat4<T> & m) {
    --m.x1; --m.y1; --m.z1; --m.w1;
    --m.x2; --m.y2; --m.z2; --m.w2;
    --m.x3; --m.y3; --m.z3; --m.w3;
    --m.x4; --m.y4; --m.z4; --m.w4;

    return m;
}

//--- post decrement ---

template <typename T>
inline mat4<T> operator--(mat4<T> & m, int) {
    mat4<T> temp(m);
    --m;

    return temp;
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- positive ---

template <typename T>
inline mat4<T> operator+(const mat4<T> & m) {
    return mat4<T>(
        +m.x1, +m.y1, +m.z1, +m.w1,
        +m.x2, +m.y2, +m.z2, +m.w2,
        +m.x3, +m.y3, +m.z3, +m.w3,
        +m.x4, +m.y4, +m.z4, +m.w4
    );
}

//--- negative ---

template <typename T>
inline mat4<T> operator-(const mat4<T> & m) {
    return mat4<T>(
        -m.x1, -m.y1, -m.z1, -m.w1,
        -m.x2, -m.y2, -m.z2, -m.w2,
        -m.x3, -m.y3, -m.z3, -m.w3,
        -m.x4, -m.y4, -m.z4, -m.w4
    );
}

//--- add ---

template <typename T>
inline mat4<T> operator+(const mat4<T> & m1, const mat4<T> & m2) {
    return mat4<T>(
        m1.x1 + m2.x1, m1.y1 + m2.y1, m1.z1 + m2.z1, m1.w1 + m2.w1,
        m1.x2 + m2.x2, m1.y2 + m2.y2, m1.z2 + m2.z2, m1.w2 + m2.w2,
        m1.x3 + m2.x3, m1.y3 + m2.y3, m1.z3 + m2.z3, m1.w3 + m2.w3,
        m1.x4 + m2.x4, m1.y4 + m2.y4, m1.z4 + m2.z4, m1.w4 + m2.w4
    );
}

template <typename T>
inline mat4<T> operator+(const mat4<T> & m, const T & v) {
    return mat4<T>(
        m.x1 + v, m.y1 + v, m.z1 + v, m.w1 + v,
        m.x2 + v, m.y2 + v, m.z2 + v, m.w2 + v,
        m.x3 + v, m.y3 + v, m.z3 + v, m.w3 + v,
        m.x4 + v, m.y4 + v, m.z4 + v, m.w4 + v
    );
}

template <typename T>
inline mat4<T> operator+(const T & v, const mat4<T> & m) {
    return mat4<T>(
        v + m.x1, v + m.y1, v + m.z1, v + m.w1,
        v + m.x2, v + m.y2, v + m.z2, v + m.w2,
        v + m.x3, v + m.y3, v + m.z3, v + m.w3,
        v + m.x4, v + m.y4, v + m.z4, v + m.w4
    );
}

//--- subtract ---

template <typename T>
inline mat4<T> operator-(const mat4<T> & m1, const mat4<T> & m2) {
    return mat4<T>(
        m1.x1 - m2.x1, m1.y1 - m2.y1, m1.z1 - m2.z1, m1.w1 - m2.w1,
        m1.x2 - m2.x2, m1.y2 - m2.y2, m1.z2 - m2.z2, m1.w2 - m2.w2,
        m1.x3 - m2.x3, m1.y3 - m2.y3, m1.z3 - m2.z3, m1.w3 - m2.w3,
        m1.x4 - m2.x4, m1.y4 - m2.y4, m1.z4 - m2.z4, m1.w4 - m2.w4
    );
}

template <typename T>
inline mat4<T> operator-(const mat4<T> & m, const T & v) {
    return mat4<T>(
        m.x1 - v, m.y1 - v, m.z1 - v, m.w1 - v,
        m.x2 - v, m.y2 - v, m.z2 - v, m.w2 - v,
        m.x3 - v, m.y3 - v, m.z3 - v, m.w3 - v,
        m.x4 - v, m.y4 - v, m.z4 - v, m.w4 - v
    );
}

template <typename T>
inline mat4<T> operator-(const T & v, const mat4<T> & m) {
    return mat4<T>(
        v - m.x1, v - m.y1, v - m.z1, v - m.w1,
        v - m.x2, v - m.y2, v - m.z2, v - m.w2,
        v - m.x3, v - m.y3, v - m.z3, v - m.w3,
        v - m.x4, v - m.y4, v - m.z4, v - m.w4
    );
}

//--- multiply ---

template <typename T>
inline mat4<T> operator*(const mat4<T> & m1, const mat4<T> & m2) {
    return mat4<T>(
        m1.x1 * m2.x1 + m1.x2 * m2.y1 + m1.x3 * m2.z1 + m1.x4 * m2.w1,
        m1.y1 * m2.x1 + m1.y2 * m2.y1 + m1.y3 * m2.z1 + m1.y4 * m2.w1,
        m1.z1 * m2.x1 + m1.z2 * m2.y1 + m1.z3 * m2.z1 + m1.z4 * m2.w1,
        m1.w1 * m2.x1 + m1.w2 * m2.y1 + m1.w3 * m2.z1 + m1.w4 * m2.w1,

        m1.x1 * m2.x2 + m1.x2 * m2.y2 + m1.x3 * m2.z2 + m1.x4 * m2.w2,
        m1.y1 * m2.x2 + m1.y2 * m2.y2 + m1.y3 * m2.z2 + m1.y4 * m2.w2,
        m1.z1 * m2.x2 + m1.z2 * m2.y2 + m1.z3 * m2.z2 + m1.z4 * m2.w2,
        m1.w1 * m2.x2 + m1.w2 * m2.y2 + m1.w3 * m2.z2 + m1.w4 * m2.w2,

        m1.x1 * m2.x3 + m1.x2 * m2.y3 + m1.x3 * m2.z3 + m1.x4 * m2.w3,
        m1.y1 * m2.x3 + m1.y2 * m2.y3 + m1.y3 * m2.z3 + m1.y4 * m2.w3,
        m1.z1 * m2.x3 + m1.z2 * m2.y3 + m1.z3 * m2.z3 + m1.z4 * m2.w3,
        m1.w1 * m2.x3 + m1.w2 * m2.y3 + m1.w3 * m2.z3 + m1.w4 * m2.w3,

        m1.x1 * m2.x4 + m1.x2 * m2.y4 + m1.x3 * m2.z4 + m1.x4 * m2.w4,
        m1.y1 * m2.x4 + m1.y2 * m2.y4 + m1.y3 * m2.z4 + m1.y4 * m2.w4,
        m1.z1 * m2.x4 + m1.z2 * m2.y4 + m1.z3 * m2.z4 + m1.z4 * m2.w4,
        m1.w1 * m2.x4 + m1.w2 * m2.y4 + m1.w3 * m2.z4 + m1.w4 * m2.w4
    );
}

template <typename T>
inline mat4<T> operator*(const mat4<T> & m, const T & v) {
    return mat4<T>(
        m.x1 * v, m.y1 * v, m.z1 * v, m.w1 * v,
        m.x2 * v, m.y2 * v, m.z2 * v, m.w2 * v,
        m.x3 * v, m.y3 * v, m.z3 * v, m.w3 * v,
        m.x4 * v, m.y4 * v, m.z4 * v, m.w4 * v
    );
}

template <typename T>
inline mat4<T> operator*(const T & v, const mat4<T> & m) {
    return mat4<T>(
        v * m.x1, v * m.y1, v * m.z1, v * m.w1,
        v * m.x2, v * m.y2, v * m.z2, v * m.w2,
        v * m.x3, v * m.y3, v * m.z3, v * m.w3,
        v * m.x4, v * m.y4, v * m.z4, v * m.w4
    );
}

template <typename T>
inline vec4<T> operator*(const mat4<T> & m, const vec4<T> & v) {
    return vec4<T>(
        v.x * m.x1 + v.y * m.x2 + v.z * m.x3 + v.w * m.x4,
        v.x * m.y1 + v.y * m.y2 + v.z * m.y3 + v.w * m.y4,
        v.x * m.z1 + v.y * m.z2 + v.z * m.z3 + v.w * m.z4,
        v.x * m.w1 + v.y * m.w2 + v.z * m.w3 + v.w * m.w4
    );
}

//--- divide ---

template <typename T>
inline mat4<T> operator/(const mat4<T> & m, const T & v) {
    return mat4<T>(
        m.x1 / v, m.y1 / v, m.z1 / v, m.w1 / v,
        m.x2 / v, m.y2 / v, m.z2 / v, m.w2 / v,
        m.x3 / v, m.y3 / v, m.z3 / v, m.w3 / v,
        m.x4 / v, m.y4 / v, m.z4 / v, m.w4 / v
    );
}

template <typename T>
inline mat4<T> operator/(const T & v, const mat4<T> & m) {
    return mat4<T>(
        v / m.x1, v / m.y1, v / m.z1, v / m.w1,
        v / m.x2, v / m.y2, v / m.z2, v / m.w2,
        v / m.x3, v / m.y3, v / m.z3, v / m.w3,
        v / m.x4, v / m.y4, v / m.z4, v / m.w4
    );
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T>
inline bool operator==(const mat4<T> & m1, const mat4<T> & m2) {
    return
        m1.x1 == m2.x1 && m1.y1 == m2.y1 && m1.z1 == m2.z1 && m1.w1 == m2.w1 &&
        m1.x2 == m2.x2 && m1.y2 == m2.y2 && m1.z2 == m2.z2 && m1.w2 == m2.w2 &&
        m1.x3 == m2.x3 && m1.y3 == m2.y3 && m1.z3 == m2.z3 && m1.w3 == m2.w3 &&
        m1.x4 == m2.x4 && m1.y4 == m2.y4 && m1.z4 == m2.z4 && m1.w4 == m2.w4;
}

//--- not equal to ---

template <typename T>
inline bool operator!=(const mat4<T> & m1, const mat4<T> & m2) {
    return
        m1.x1 != m2.x1 || m1.y1 != m2.y1 || m1.z1 != m2.z1 || m1.w1 != m2.w1 ||
        m1.x2 != m2.x2 || m1.y2 != m2.y2 || m1.z2 != m2.z2 || m1.w2 != m2.w2 ||
        m1.x3 != m2.x3 || m1.y3 != m2.y3 || m1.z3 != m2.z3 || m1.w3 != m2.w3 ||
        m1.x4 != m2.x4 || m1.y4 != m2.y4 || m1.z4 != m2.z4 || m1.w4 != m2.w4;
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string mat<T, 4, 4>::toString() const {
    return
        "[ " +
        std::to_string(x1) + " " + std::to_string(y1) + " " + std::to_string(z1) + " " + std::to_string(w1) +
        " | " +
        std::to_string(x2) + " " + std::to_string(y2) + " " + std::to_string(z2) + " " + std::to_string(w2) +
        " | " +
        std::to_string(x3) + " " + std::to_string(y3) + " " + std::to_string(z3) + " " + std::to_string(w3) +
        " | " +
        std::to_string(x4) + " " + std::to_string(y4) + " " + std::to_string(z4) + " " + std::to_string(w4) +
        " ]";
}



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const mat4<T> & m) {
    return os << m.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT FUNCTIONS IMPLEMENTATION ----------------------------------------------------------------------------------------



//--- transpose ---

template <typename T>
inline mat2<T> transpose(const mat2<T> & m) {
    return mat2<T>(
        m.x1, m.x2,
        m.y1, m.y2
    );
}

template <typename T>
inline mat3<T> transpose(const mat3<T> & m) {
    return mat3<T>(
        m.x1, m.x2, m.x3,
        m.y1, m.y2, m.y3,
        m.z1, m.z2, m.z3
    );
}

template <typename T>
inline mat4<T> transpose(const mat4<T> & m) {
    return mat4<T>(
        m.x1, m.x2, m.x3, m.x4,
        m.y1, m.y2, m.y3, m.y4,
        m.z1, m.z2, m.z3, m.z4,
        m.w1, m.w2, m.w3, m.w4
    );
}

//--- cofactor ---

template <typename T>
inline mat2<T> cofactor(const mat2<T> & m) {
    return mat2<T>(
        m.y2, -m.x2,
        -m.y1, m.x1
    );
}

template <typename T>
inline mat3<T> cofactor(const mat3<T> & m) {
    return mat3<T>(
        +(m.y2 * m.z3 - m.y3 * m.z2), -(m.x2 * m.z3 - m.x3 * m.z2), +(m.x2 * m.y3 - m.x3 * m.y2),
        -(m.y1 * m.z3 - m.y3 * m.z1), +(m.x1 * m.z3 - m.x3 * m.z1), -(m.x1 * m.y3 - m.x3 * m.y1),
        +(m.y1 * m.z2 - m.y2 * m.z1), -(m.x1 * m.z2 - m.x2 * m.z1), +(m.x1 * m.y2 - m.x2 * m.y1)
    );
}

template <typename T>
inline mat4<T> cofactor(const mat4<T> & m) {
    //T xy12(m.x1 * m.y2 - m.x2 * m.y1);
    //T xy13(m.x1 * m.y3 - m.x3 * m.y1);
    //T xy14(m.x1 * m.y4 - m.x4 * m.y1);
    //T xz12(m.x1 * m.z2 - m.x2 * m.z1);
    //T xz13(m.x1 * m.z3 - m.x3 * m.z1);
    //T xz14(m.x1 * m.z4 - m.x4 * m.z1);
    //T xw12(m.x1 * m.w2 - m.x2 * m.w1);
    //T xw13(m.x1 * m.w3 - m.x3 * m.w1);
    //T xw14(m.x1 * m.w4 - m.x4 * m.w1);
    //T xy23(m.x2 * m.y3 - m.x3 * m.y2);
    //T xy24(m.x2 * m.y4 - m.x4 * m.y2);
    //T xz23(m.x2 * m.z3 - m.x3 * m.z2);
    //T xz24(m.x2 * m.z4 - m.x4 * m.z2);
    //T xw23(m.x2 * m.w3 - m.x3 * m.w2);
    //T xw24(m.x2 * m.w4 - m.x4 * m.w2);
    T yz12(m.y1 * m.z2 - m.y2 * m.z1);
    T yz13(m.y1 * m.z3 - m.y3 * m.z1);
    T yz14(m.y1 * m.z4 - m.y4 * m.z1);
    T yw12(m.y1 * m.w2 - m.y2 * m.w1);
    T yw13(m.y1 * m.w3 - m.y3 * m.w1);
    T yw14(m.y1 * m.w4 - m.y4 * m.w1);
    //T xy34(m.x3 * m.y4 - m.x4 * m.y3);
    //T xz34(m.x3 * m.z4 - m.x4 * m.z3);
    //T xw34(m.x3 * m.w4 - m.x4 * m.w3);
    T yz23(m.y2 * m.z3 - m.y3 * m.z2);
    T yz24(m.y2 * m.z4 - m.y4 * m.z2);
    T yw23(m.y2 * m.w3 - m.y3 * m.w2);
    T yw24(m.y2 * m.w4 - m.y4 * m.w2);
    T zw12(m.z1 * m.w2 - m.z2 * m.w1);
    T zw13(m.z1 * m.w3 - m.z3 * m.w1);
    T zw14(m.z1 * m.w4 - m.z4 * m.w1);
    T yz34(m.y3 * m.z4 - m.y4 * m.z3);
    T yw34(m.y3 * m.w4 - m.y4 * m.w3);
    T zw23(m.z2 * m.w3 - m.z3 * m.w2);
    T zw24(m.z2 * m.w4 - m.z4 * m.w2);
    T zw34(m.z3 * m.w4 - m.z4 * m.w3);

    T xyz123(m.x1 * yz23 - m.x2 * yz13 + m.x3 * yz12);
    T xyz124(m.x1 * yz24 - m.x2 * yz14 + m.x4 * yz12);
    T xyz134(m.x1 * yz34 - m.x3 * yz14 + m.x4 * yz13);
    T xyw123(m.x1 * yw23 - m.x2 * yw13 + m.x3 * yw12);
    T xyw124(m.x1 * yw24 - m.x2 * yw14 + m.x4 * yw12);
    T xyw134(m.x1 * yw34 - m.x3 * yw14 + m.x4 * yw13);
    T xzw123(m.x1 * zw23 - m.x2 * zw13 + m.x3 * zw12);
    T xzw124(m.x1 * zw24 - m.x2 * zw14 + m.x4 * zw12);
    T xzw134(m.x1 * zw34 - m.x3 * zw14 + m.x4 * zw13);
    T xyz234(m.x2 * yz34 - m.x3 * yz24 + m.x4 * yz23);
    T xyw234(m.x2 * yw34 - m.x3 * yw24 + m.x4 * yw23);
    T xzw234(m.x2 * zw34 - m.x3 * zw24 + m.x4 * zw23);
    T yzw123(m.y1 * zw23 - m.y2 * zw13 + m.y3 * zw12);
    T yzw124(m.y1 * zw24 - m.y2 * zw14 + m.y4 * zw12);
    T yzw134(m.y1 * zw34 - m.y3 * zw14 + m.y4 * zw13);
    T yzw234(m.y2 * zw34 - m.y3 * zw24 + m.y4 * zw23);

    return mat4<T>(
        +yzw234, -xzw234, +xyw234, -xyz234,
        -yzw134, +xzw134, -xyw134, +xyz134,
        +yzw124, -xzw124, +xyw124, -xyz124,
        -yzw123, +xzw123, -xyw123, +xyz123
    );
}

//-- adjoint ---

template <typename T>
inline mat2<T> adjoint(const mat2<T> & m) {
    return transpose(cofactor(m));

}

template <typename T>
inline mat3<T> adjoint(const mat3<T> & m) {
    return transpose(cofactor(m));

}

template <typename T>
inline mat4<T> adjoint(const mat4<T> & m) {
    return transpose(cofactor(m));
}

//--- determinant ---

template <typename T>
inline T determinant(const mat2<T> & m) {
    return
        + m.x1 * m.y2
        - m.x2 * m.y1;
}

template <typename T>
inline T determinant(const mat3<T> & m) {
    return
        + m.x1 * (m.y2 * m.z3 - m.y3 * m.z2)
        - m.x2 * (m.y1 * m.z3 - m.y3 * m.z1)
        + m.x3 * (m.y1 * m.z2 - m.y2 * m.z1);
}

template <typename T>
inline T determinant(const mat4<T> & m) {
    T zw12 = m.z1 * m.w2 - m.z2 * m.w1;
    T zw13 = m.z1 * m.w3 - m.z3 * m.w1;
    T zw14 = m.z1 * m.w4 - m.z4 * m.w1;
    T zw23 = m.z2 * m.w3 - m.z3 * m.w2;
    T zw24 = m.z2 * m.w4 - m.z4 * m.w2;
    T zw34 = m.z3 * m.w4 - m.z4 * m.w3;

    T yzw123 = m.y1 * zw23 - m.y2 * zw13 + m.y3 * zw12;
    T yzw124 = m.y1 * zw24 - m.y2 * zw14 + m.y4 * zw12;
    T yzw134 = m.y1 * zw34 - m.y3 * zw14 + m.y4 * zw13;
    T yzw234 = m.y2 * zw34 - m.y3 * zw24 + m.y4 * zw23;

    return m.x1 * yzw234 - m.x2 * yzw134 + m.x3 * yzw124 - m.x4 * yzw123;
}

//--- inverse ---

template <typename T>
inline mat2<T> inverse(const mat2<T> & m) {
    return adjoint(m) / determinant(m);
}

template <typename T>
inline mat3<T> inverse(const mat3<T> & m) {
    return adjoint(m) / determinant(m);
}

template <typename T>
inline mat4<T> inverse(const mat4<T> & m) {
    return adjoint(m) / determinant(m);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORMATIONS IMPLEMENTATION --------------------------------------------------------------------------------------



template <typename T>
inline mat2<T> translate(const vec1<T> & delta) {
    return mat2<T>(
        1, 0,
        delta.x, 1
    );
}

template <typename T>
inline mat3<T> translate(const vec2<T> & delta) {
    return mat3<T>(
        1, 0, 0,
        0, 1, 0,
        delta.x, delta.y, 1
    );
}

template <typename T>
inline mat4<T> translate(const vec3<T> & delta) {
    return mat4<T>(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        delta.x, delta.y, delta.z, 1
    );
}

template <typename T>
inline mat2<T> translate(mat2<T> mat, const vec1<T> & delta) {
    mat.x1 += delta.x * mat.y1;
    mat.x2 += delta.x * mat.y2;
    return mat;
}

template <typename T>
inline mat3<T> translate(mat3<T> mat, const vec2<T> & delta) {
    mat.x1 += delta.x * mat.z1;
    mat.x2 += delta.x * mat.z2;
    mat.x3 += delta.x * mat.z3;
    mat.y1 += delta.y * mat.z1;
    mat.y2 += delta.y * mat.z2;
    mat.y3 += delta.y * mat.z3;
    return mat;
}

template <typename T>
inline mat4<T> translate(mat4<T> mat, const vec3<T> & delta) {
    mat.x1 += delta.x * mat.w1;
    mat.x2 += delta.x * mat.w2;
    mat.x3 += delta.x * mat.w3;
    mat.x4 += delta.x * mat.w4;
    mat.y1 += delta.y * mat.w1;
    mat.y2 += delta.y * mat.w2;
    mat.y3 += delta.y * mat.w3;
    mat.y4 += delta.y * mat.w4;
    mat.z1 += delta.z * mat.w1;
    mat.z2 += delta.z * mat.w2;
    mat.z3 += delta.z * mat.w3;
    mat.z4 += delta.z * mat.w4;
    return mat;
}

template <typename T>
inline mat2<T> scale(const vec2<T> & scale) {
    return mat2<T>(
        scale.x, 0,
        0, scale.y
    );
}

template <typename T>
inline mat3<T> scale(const vec3<T> & scale) {
    return mat3<T>(
        scale.x, 0, 0,
        0, scale.y, 0,
        0, 0, scale.z
    );
}

template <typename T>
inline mat2<T> scale(mat2<T> mat, const vec1<T> & scale) {
    mat.x1 *= scale.x;
    mat.x2 *= scale.x;
    return mat;
}

template <typename T>
inline mat2<T> scale(mat2<T> mat, const vec2<T> & scale) {
    mat.x1 *= scale.x;
    mat.x2 *= scale.x;
    mat.y1 *= scale.y;
    mat.y2 *= scale.y;
    return mat;
}

template <typename T>
inline mat3<T> scale(mat3<T> mat, const vec2<T> & scale) {
    mat.x1 *= scale.x;
    mat.x2 *= scale.x;
    mat.x3 *= scale.x;
    mat.y1 *= scale.y;
    mat.y2 *= scale.y;
    mat.y3 *= scale.y;
    return mat;
}

template <typename T>
inline mat3<T> scale(mat3<T> mat, const vec3<T> & scale) {
    mat.x1 *= scale.x;
    mat.x2 *= scale.x;
    mat.x3 *= scale.x;
    mat.y1 *= scale.y;
    mat.y2 *= scale.y;
    mat.y3 *= scale.y;
    mat.z1 *= scale.z;
    mat.z2 *= scale.z;
    mat.z3 *= scale.z;
    return mat;
}

template <typename T>
inline mat4<T> scale(mat4<T> mat, const vec3<T> & scale) {
    mat.x1 *= scale.x;
    mat.x2 *= scale.x;
    mat.x3 *= scale.x;
    mat.x4 *= scale.x;
    mat.y1 *= scale.y;
    mat.y2 *= scale.y;
    mat.y3 *= scale.y;
    mat.y4 *= scale.y;
    mat.z1 *= scale.z;
    mat.z2 *= scale.z;
    mat.z3 *= scale.z;
    mat.z4 *= scale.z;
    return mat;
}

template <typename T>
inline mat4<T> scale(mat4<T> mat, const vec4<T> & scale) {
    mat.x1 *= scale.x;
    mat.x2 *= scale.x;
    mat.x3 *= scale.x;
    mat.x4 *= scale.x;
    mat.y1 *= scale.y;
    mat.y2 *= scale.y;
    mat.y3 *= scale.y;
    mat.y4 *= scale.y;
    mat.z1 *= scale.z;
    mat.z2 *= scale.z;
    mat.z3 *= scale.z;
    mat.z4 *= scale.z;
    mat.w1 *= scale.w;
    mat.w2 *= scale.w;
    mat.w3 *= scale.w;
    mat.w4 *= scale.w;
    return mat;
}

template <typename T>
inline mat2<T> rotate(const T & theta) {
    T s = std::sin(theta);
    T c = std::cos(theta);

    return mat2<T>(
        c, s,
        -s, c
    );
}

template <typename T>
inline mat3<T> rotateX(const T & theta) {
    T s = std::sin(theta);
    T c = std::cos(theta);

    return mat3<T>(
        1, 0, 0,
        0, c, s,
        0, -s, c
    );
}

template <typename T>
inline mat3<T> rotateY(const T & theta) {
    T s = std::sin(theta);
    T c = std::cos(theta);

    return mat3<T>(
        c, 0, -s,
        0, 1, 0,
        s, 0, c
    );
}

template <typename T>
inline mat3<T> rotateZ(const T & theta) {
    T s = std::sin(theta);
    T c = std::cos(theta);

    return mat3<T>(
        c, s, 0,
        -s, c, 0,
        0, 0, 1
    );
}

template <typename T>
inline mat3<T> rotate(const vec3<T> & axis, const T & sinTheta, const T & cosTheta) {
    if (magnitude2(axis) == 0) { //can't rotate around 0 length fvector
        return mat3<T>();
    }

    return rotate_n(normalize(axis), sinTheta, cosTheta);
}
template <typename T>
inline mat3<T> rotate_n(const vec3<T> & axis, const T & s, const T & c) {
    T cm = 1 - c;

    return mat3<T>(
        c + axis.x * axis.x * cm, axis.y * axis.x * cm + axis.z * s, axis.z * axis.x * cm - axis.y * s,
        axis.x * axis.y * cm - axis.z * s, c + axis.y * axis.y * cm, axis.z * axis.y * cm + axis.x * s,
        axis.x * axis.z * cm + axis.y * s, axis.y * axis.z * cm - axis.x * s, c + axis.z * axis.z * cm
    );
}

template <typename T>
inline mat3<T> rotate(const vec3<T> & axis, const T & theta) {
    return rotate(axis, std::sin(theta), std::cos(theta));
}
template <typename T>
inline mat3<T> rotate_n(const vec3<T> & axis, const T & theta) {
    return rotate_n(axis, std::sin(theta), std::cos(theta));
}

template <typename T>
inline mat3<T> euler(const vec3<T> & forward, const vec3<T> & up, const T & theta, const T & phi, const T & psi) {
    return euler_n(normalize(forward), normalize(up), theta, phi, psi);
}
template <typename T>
inline mat3<T> euler_n(const vec3<T> & forward, const vec3<T> & up, const T & theta, const T & phi, const T & psi) {
    return rotate_n(up, theta) * rotate_n(cross(forward, up), phi) * rotate_n(forward, psi);
}

template <typename T, nat t_n>
inline mat<T, t_n> align(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    return align_n(normalize(v1), normalize(v2));
}
template <typename T>
inline mat2<T> align_n(const vec2<T> & v1, const vec2<T> & v2) {
    T c(cross(v1, v2));
    T d(dot(v1, v2));

    return rotate(c < 0 ? -std::acos(d) : std::acos(d));
}
template <typename T>
inline mat3<T> align_n(const vec3<T> & v1, const vec3<T> & v2) {
    vec3<T> c(cross(v1, v2));
    T d(dot(v1, v2));

    return rotate(c, magnitude(c), d);
}

template <typename T>
inline mat3<T> align(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2) {
    return align_n(normalize(forward1), normalize(up1), normalize(forward2), normalize(up2));
}
template <typename T>
inline mat3<T> align_n(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2) {
    mat3<T> m = align_n(forward1, forward2);
    return align_n(m * up1, up2) * m;
}

template <typename T>
inline mat2<T> map(const vec2<T> & x1, const vec2<T> & y1, const vec2<T> & x2, const vec2<T> & y2) {
    mat2<T> a(x1, y1);
    mat2<T> b(x2, y2);

    return inverse(b) * a;
}

template <typename T>
inline mat2<T> map_o(const vec2<T> & x1, const vec2<T> & y1, const vec2<T> & x2, const vec2<T> & y2) {
    mat2<T> a(x1, y1);
    mat2<T> b(x2, y2);

    return transpose(b) * a;
}

template <typename T>
inline mat3<T> map(const vec3<T> & x1, const vec3<T> & y1, const vec3<T> & z1, const vec3<T> & x2, const vec3<T> & y2, const vec3<T> & z2) {
    mat3<T> a(x1, y1, z1);
    mat3<T> b(x2, y2, z2);

    return inverse(b) * a;
}

template <typename T>
inline mat3<T> map_o(const vec3<T> & x1, const vec3<T> & y1, const vec3<T> & z1, const vec3<T> & x2, const vec3<T> & y2, const vec3<T> & z2) {
    mat3<T> a(x1, y1, z1);
    mat3<T> b(x2, y2, z2);

    return transpose(b) * a;
}

template <typename T>
inline mat2<T> mapTo(const vec2<T> & x, const vec2<T> & y) {
    return inverse(mat2<T>(x, y));
}

template <typename T>
inline mat2<T> mapTo_o(const vec2<T> & x, const vec2<T> & y) {
    return transpose(mat2<T>(x, y));
}

template <typename T>
inline mat3<T> mapTo(const vec3<T> & x, const vec3<T> & y, const vec3<T> & z) {
    return inverse(mat3<T>(x, y, z));
}

template <typename T>
inline mat3<T> mapTo_o(const vec3<T> & x, const vec3<T> & y, const vec3<T> & z) {
    return transpose(mat3<T>(x, y, z));
}

template <typename T>
inline mat2<T> mapFrom(const vec2<T> & x, const vec2<T> & y) {
    return mat2<T>(x, y);
}

template <typename T>
inline mat3<T> mapFrom(const vec3<T> & x, const vec3<T> & y, const vec3<T> & z) {
    return mat3<T>(x, y, z);
}

template <typename T>
inline mat4<T> orthoProj(const T & width, const T & height, const T & near, const T & far) {
    return mat4<T>(
        2 / width, 0, 0, 0,
        0, 2 / height, 0, 0,
        0, 0, 2 / (near - far), 0,
        0, 0, (far + near) / (near - far), 1
    );
}

template <typename T>
inline mat4<T> orthoProjAsym(const T & left, const T & right, const T & bottom, const T & top, const T & near, const T & far) {
    return mat4<T>(
        2 / (right + left), 0, 0, 0,
        0, 2 / (top + bottom), 0, 0,
        0, 0, 2 / (near - far), 0,
        (right - left) / (-right - left), (top - bottom) / (-top - bottom), (far + near) / (near - far), 1
    );
}

template <typename T>
inline mat4<T> perspProj(const T & fov, const T & aspectRatio, const T & near, const T & far) {
    T near_right = 1 / std::tan(fov / 2);

    return mat4<T>(
        near_right, 0, 0, 0,
        0, near_right / aspectRatio, 0, 0,
        0, 0, (far + near) / (near - far), -1,
        0, 0, 2 * far * near / (near - far), 0
    );
}

template <typename T>
inline mat4<T> perspProjAsym(const T & fovLeft, const T & fovRight, const T & fovBottom, const T & fovTop, const T & near, const T & far) {
    T left = near * -std::tan(fovLeft);
    T right = near * std::tan(fovRight);
    T bottom = near * -std::tan(fovBottom);
    T top = near * std::tan(fovTop);

    return mat4<T>(
        2 * near / (right - left), 0, 0, 0,
        0, 2 * near / (top - bottom), 0, 0,
        (right + left) / (right - left), (top + bottom) / (top - bottom), (far + near) / (near - far), -1,
        0, 0, 2 * far * near / (near - far), 0
    );
}

template <typename T>
inline mat4<T> view(const vec3<T> & camLoc, const vec3<T> & camForward, const vec3<T> & up) {
    vec3<T> z(normalize(-camForward));
    vec3<T> x(normalize(cross(up, z)));
    vec3<T> y(normalize(cross(z, x)));

    return mat4<T>(mapTo_o(x, y, z)) * translate(-camLoc);
}

template <typename T>
inline mat4<T> view(const vec3<T> & camLoc, const vec3<T> & camX, const vec3<T> & camY, const vec3<T> & camZ) {
    return view_n(camLoc, normalize(camX), normalize(camY), normalize(camZ));
}

template <typename T>
inline mat4<T> view_n(const vec3<T> & camLoc, const vec3<T> & camX, const vec3<T> & camY, const vec3<T> & camZ) {
    return mat4<T>(mapTo(camX, camY, camZ)) * translate(-camLoc);
}

template <typename T>
inline mat4<T> view_o(const vec3<T> & camLoc, const vec3<T> & camX, const vec3<T> & camY, const vec3<T> & camZ) {
    return view_on(camLoc, normalize(camX), normalize(camY), normalize(camZ));
}

template <typename T>
inline mat4<T> view_on(const vec3<T> & camLoc, const vec3<T> & camX, const vec3<T> & camY, const vec3<T> & camZ) {
    return mat4<T>(mapTo_o(camX, camY, camZ)) * translate(-camLoc);
}



}
