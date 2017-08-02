#pragma once



// Column-major ordering
//
//  x1 x2 x3    00 03 06
//  y1 y2 y3    01 04 07
//  z1 z2 z3    02 05 08



#include "Vector.hpp"



namespace qmu {



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Type Declarations ---------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Mat



template <typename T, nat t_m, nat t_n = t_m> struct mat;

template <typename T> using mat2 = mat<T, 2>;
template <typename T> using mat3 = mat<T, 3>;
template <typename T> using mat4 = mat<T, 4>;

template <nat t_m, nat t_n> using  fmat = mat<      float, t_m, t_n>;
template <nat t_m, nat t_n> using  dmat = mat<     double, t_m, t_n>;
template <nat t_m, nat t_n> using ldmat = mat<long double, t_m, t_n>;

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



namespace  tmats { using qmu::  mat; using qmu::  mat2; using qmu::  mat3; using qmu::  mat4; }
namespace  fmats { using qmu:: fmat; using qmu:: fmat2; using qmu:: fmat3; using qmu:: fmat4; }
namespace  dmats { using qmu:: dmat; using qmu:: dmat2; using qmu:: dmat3; using qmu:: dmat4; }
namespace ldmats { using qmu::ldmat; using qmu::ldmat2; using qmu::ldmat3; using qmu::ldmat4; }

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

    static_assert(std::is_floating_point<T>::value, "mat2<T> must have floating point T");

    using Type = T;
    static constexpr nat M = 2, N = 2;

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

    mat2<T> & operator=(const mat2<T> & m);
    mat2<T> & operator=(mat2<T> && m);

    mat2<T> & operator=(const mat3<T> & m);
    mat2<T> & operator=(const mat4<T> & m);

    //--- access ---

    T & operator[](nat i);
    T operator[](nat i) const;

    template <nat t_i, nat t_j> T & at();
    template <nat t_i, nat t_j> T at() const;

    vec2<T> col(nat i) const;
    vec2<T> row(nat i) const;

    template <nat t_i> vec2<T> row() const;
    template <nat t_j> vec2<T> col() const;

    //--- other ---

    std::string toString() const;

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT3 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct mat<T, 3, 3> {

    static_assert(std::is_floating_point<T>::value, "mat3<T> must have floating point T");

    using Type = T;
    static constexpr nat M = 3, N = 3;

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

    mat3<T> & operator=(const mat3<T> & m);
    mat3<T> & operator=(mat3<T> && m);

    mat3<T> & operator=(const mat2<T> & m);
    mat3<T> & operator=(const mat4<T> & m);

    //--- access ---

    T & operator[](nat i);
    T operator[](nat i) const;

    template <nat t_i, nat t_j> T & at();
    template <nat t_i, nat t_j> T at() const;

    vec3<T> col(nat i) const;
    vec3<T> row(nat i) const;

    template <nat t_i> vec3<T> row() const;
    template <nat t_j> vec3<T> col() const;

    //--- other ---

    std::string toString() const;

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT4 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct mat<T, 4, 4> {

    static_assert(std::is_floating_point<T>::value, "mat4<T> must have floating point T");

    using Type = T;
    static constexpr nat M = 4, N = 4;

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

    mat4<T> & operator=(const mat4<T> & m);
    mat4<T> & operator=(mat4<T> && m);

    mat4<T> & operator=(const mat2<T> & m);
    mat4<T> & operator=(const mat3<T> & m);

    //--- access ---

    T & operator[](nat i);
    T operator[](nat i) const;

    template <nat t_i, nat t_j> T & at();
    template <nat t_i, nat t_j> T at() const;

    vec4<T> col(nat i) const;
    vec4<T> row(nat i) const;

    template <nat t_i> vec4<T> row() const;
    template <nat t_j> vec4<T> col() const;

    //--- other ---

    std::string toString() const;

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT FUNCTIONS -------------------------------------------------------------------------------------------------------



//--- arithmetic assignment ---

template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> & operator+=(mat<T, t_m, t_n> & m, T v);
template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> & operator+=(mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2);

template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> & operator-=(mat<T, t_m, t_n> & m, T v);
template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> & operator-=(mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2);

template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> & operator*=(mat<T, t_m, t_n> & m, T v);
template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> & operator*=(mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2);

template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> & operator/=(mat<T, t_m, t_n> & m, T v);

template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> & operator++(mat<T, t_m, t_n> & m);
template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n>   operator++(mat<T, t_m, t_n> & m, int);

template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> & operator--(mat<T, t_m, t_n> & m);
template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n>   operator--(mat<T, t_m, t_n> & m, int);

//--- arithmetic operators ---

template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> operator+(const mat<T, t_m, t_n> & m);

template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> operator-(const mat<T, t_m, t_n> & m);

template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> operator+(const mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2);
template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> operator+(const mat<T, t_m, t_n> & m, T v);
template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> operator+(T v, const mat<T, t_m, t_n> & m);

template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> operator-(const mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2);
template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> operator-(const mat<T, t_m, t_n> & m, T v);
template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> operator-(T v, const mat<T, t_m, t_n> & m);

template <typename T, nat t_m1, nat t_n1m2, nat t_n2> mat<T, t_m1, t_n2> operator*(const mat<T, t_m1, t_n1m2> & m1, const mat<T, t_n1m2, t_n2> & m2);
template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> operator*(const mat<T, t_m, t_n> & m, T v);
template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> operator*(T v, const mat<T, t_m, t_n> & m);
template <typename T, nat t_m, nat t_n> vec<T, t_m> operator*(const mat<T, t_m, t_n> & m, const vec<T, t_n> & v);

template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> operator/(const mat<T, t_m, t_n> & m, T v);
template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> operator/(T v, const mat<T, t_m, t_n> & m);

//--- comparison operators ---

template <typename T, nat t_m, nat t_n> bool operator==(const mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2);

template <typename T, nat t_m, nat t_n> bool operator!=(const mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2);

//--- other ---

template <typename T, nat t_m, nat t_n> std::ostream & operator<<(std::ostream & os, const mat<T, t_m, t_n> & m);

//--- uncategorized ---

template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> transpose(const mat<T, t_m, t_n> & m);

template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> cofactor(const mat<T, t_m, t_n> & m);

template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> adjoint(const mat<T, t_m, t_n> & m);

template <typename T, nat t_m, nat t_n> T determinant(const mat<T, t_m, t_n> & m);

template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> inverse(const mat<T, t_m, t_n> & m);

template <typename T, nat t_m, nat t_n = t_m> constexpr mat<T, t_m, t_n> fullMat(T v);

template <typename T, nat t_m, nat t_n = t_m> constexpr mat<T, t_m, t_n> nullMat();



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORMATIONS -----------------------------------------------------------------------------------------------------



template <typename T, nat t_n> mat<T, t_n + 1> translate(const vec<T, t_n> & delta);
template <typename T, nat t_n> mat<T, t_n + 1> & translate(mat<T, t_n + 1> & mat, const vec<T, t_n> & delta);

template <typename T, nat t_n> mat<T, t_n> scale(const vec<T, t_n> & scale);
template <typename T, nat t_n> mat<T, t_n> & scale(mat<T, t_n> & mat, const vec<T, t_n> & scale);
template <typename T, nat t_n> mat<T, t_n + 1> & scale(mat<T, t_n + 1> & mat, const vec<T, t_n> & scale);

template <typename T> mat2<T> rotate(T theta);

template <typename T> mat3<T> rotateX(T theta);

template <typename T> mat3<T> rotateY(T theta);

template <typename T> mat3<T> rotateZ(T theta);

template <typename T> mat3<T> rotate(const vec3<T> & axis, T sinTheta, T cosTheta);
template <typename T> mat3<T> rotate_n(const vec3<T> & axis, T sinTheta, T cosTheta);

template <typename T> mat3<T> rotate(const vec3<T> & axis, T theta);
template <typename T> mat3<T> rotate_n(const vec3<T> & axis, T theta);

//theta: thumb points up, phi: right, psi: forward
template <typename T> mat3<T> euler(const vec3<T> & forward, const vec3<T> & up, T theta, T phi, T psi);
template <typename T> mat3<T> euler_n(const vec3<T> & forward, const vec3<T> & up, T theta, T phi, T psi);

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

template <typename T> mat4<T> orthoProj(T width, T height, T near, T far);
template <typename T> mat4<T> orthoProjAsym(T left, T right, T bottom, T top, T near, T far);

//fov is angle in radians between top and bottom planes, aspectRatio is screen width / height, zNear is distance to near plane, zFar is distance to far plane
template <typename T> mat4<T> perspProj(T fov, T aspectRatio, T near, T far);
//fovNX is angle between center and left plane, fovPX between center and right, fovNY between center and bottom, fovPY between center and top
template <typename T> mat4<T> perspProjAsym(T fovLeft, T fovRight, T fovBottom, T fovTop, T near, T far);

//forward and up must not be parallel
template <typename T> mat4<T> view(const vec3<T> & camLoc, const vec3<T> & camForward, const vec3<T> & up);

template <typename T> mat4<T> view(const vec3<T> & camLoc, const vec3<T> & camX, const vec3<T> & camY, const vec3<T> & camZ);
template <typename T> mat4<T> view_n(const vec3<T> & camLoc, const vec3<T> & camX, const vec3<T> & camY, const vec3<T> & camZ);
//basis vectors are orthonormal (optimization)
template <typename T> mat4<T> view_o(const vec3<T> & camLoc, const vec3<T> & camX, const vec3<T> & camY, const vec3<T> & camZ);
template <typename T> mat4<T> view_on(const vec3<T> & camLoc, const vec3<T> & camX, const vec3<T> & camY, const vec3<T> & camZ);



}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



namespace qmu {



namespace detail {



template <nat t_i, nat t_j>
struct MatAccessor;

template <>
struct MatAccessor<0, 0> {
    template <typename T, nat t_m, nat t_n>
    static T & access(mat<T, t_m, t_n> & m) {
        return m.x1;
    }
    template <typename T, nat t_m, nat t_n>
    static T access(const mat<T, t_m, t_n> & m) {
        return m.x1;
    }
};

template <>
struct MatAccessor<0, 1> {
    template <typename T, nat t_m, nat t_n>
    static T & access(mat<T, t_m, t_n> & m) {
        return m.x2;
    }
    template <typename T, nat t_m, nat t_n>
    static T access(const mat<T, t_m, t_n> & m) {
        return m.x2;
    }
};

template <>
struct MatAccessor<0, 2> {
    template <typename T, nat t_m, nat t_n>
    static T & access(mat<T, t_m, t_n> & m) {
        return m.x3;
    }
    template <typename T, nat t_m, nat t_n>
    static T access(const mat<T, t_m, t_n> & m) {
        return m.x3;
    }
};

template <>
struct MatAccessor<0, 3> {
    template <typename T, nat t_m, nat t_n>
    static T & access(mat<T, t_m, t_n> & m) {
        return m.x4;
    }
    template <typename T, nat t_m, nat t_n>
    static T access(const mat<T, t_m, t_n> & m) {
        return m.x4;
    }
};
template <>
struct MatAccessor<1, 0> {
    template <typename T, nat t_m, nat t_n>
    static T & access(mat<T, t_m, t_n> & m) {
        return m.y1;
    }
    template <typename T, nat t_m, nat t_n>
    static T access(const mat<T, t_m, t_n> & m) {
        return m.y1;
    }
};

template <>
struct MatAccessor<1, 1> {
    template <typename T, nat t_m, nat t_n>
    static T & access(mat<T, t_m, t_n> & m) {
        return m.y2;
    }
    template <typename T, nat t_m, nat t_n>
    static T access(const mat<T, t_m, t_n> & m) {
        return m.y2;
    }
};

template <>
struct MatAccessor<1, 2> {
    template <typename T, nat t_m, nat t_n>
    static T & access(mat<T, t_m, t_n> & m) {
        return m.y3;
    }
    template <typename T, nat t_m, nat t_n>
    static T access(const mat<T, t_m, t_n> & m) {
        return m.y3;
    }
};

template <>
struct MatAccessor<1, 3> {
    template <typename T, nat t_m, nat t_n>
    static T & access(mat<T, t_m, t_n> & m) {
        return m.y4;
    }
    template <typename T, nat t_m, nat t_n>
    static T access(const mat<T, t_m, t_n> & m) {
        return m.y4;
    }
};
template <>
struct MatAccessor<2, 0> {
    template <typename T, nat t_m, nat t_n>
    static T & access(mat<T, t_m, t_n> & m) {
        return m.z1;
    }
    template <typename T, nat t_m, nat t_n>
    static T access(const mat<T, t_m, t_n> & m) {
        return m.z1;
    }
};

template <>
struct MatAccessor<2, 1> {
    template <typename T, nat t_m, nat t_n>
    static T & access(mat<T, t_m, t_n> & m) {
        return m.z2;
    }
    template <typename T, nat t_m, nat t_n>
    static T access(const mat<T, t_m, t_n> & m) {
        return m.z2;
    }
};

template <>
struct MatAccessor<2, 2> {
    template <typename T, nat t_m, nat t_n>
    static T & access(mat<T, t_m, t_n> & m) {
        return m.z3;
    }
    template <typename T, nat t_m, nat t_n>
    static T access(const mat<T, t_m, t_n> & m) {
        return m.z3;
    }
};

template <>
struct MatAccessor<2, 3> {
    template <typename T, nat t_m, nat t_n>
    static T & access(mat<T, t_m, t_n> & m) {
        return m.z4;
    }
    template <typename T, nat t_m, nat t_n>
    static T access(const mat<T, t_m, t_n> & m) {
        return m.z4;
    }
};
template <>
struct MatAccessor<3, 0> {
    template <typename T, nat t_m, nat t_n>
    static T & access(mat<T, t_m, t_n> & m) {
        return m.w1;
    }
    template <typename T, nat t_m, nat t_n>
    static T access(const mat<T, t_m, t_n> & m) {
        return m.w1;
    }
};

template <>
struct MatAccessor<3, 1> {
    template <typename T, nat t_m, nat t_n>
    static T & access(mat<T, t_m, t_n> & m) {
        return m.w2;
    }
    template <typename T, nat t_m, nat t_n>
    static T access(const mat<T, t_m, t_n> & m) {
        return m.w2;
    }
};

template <>
struct MatAccessor<3, 2> {
    template <typename T, nat t_m, nat t_n>
    static T & access(mat<T, t_m, t_n> & m) {
        return m.w3;
    }
    template <typename T, nat t_m, nat t_n>
    static T access(const mat<T, t_m, t_n> & m) {
        return m.w3;
    }
};

template <>
struct MatAccessor<3, 3> {
    template <typename T, nat t_m, nat t_n>
    static T & access(mat<T, t_m, t_n> & m) {
        return m.w4;
    }
    template <typename T, nat t_m, nat t_n>
    static T access(const mat<T, t_m, t_n> & m) {
        return m.w4;
    }
};



}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT2 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr mat<T, 2, 2>::mat() :
    x1(static_cast<T>(1.0)), y1(static_cast<T>(0.0)),
    x2(static_cast<T>(0.0)), y2(static_cast<T>(1.0))
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
// Access



template <typename T>
inline T & mat<T, 2, 2>::operator[](nat i) {
    return *(&x1 + i);
}

template <typename T>
inline T mat<T, 2, 2>::operator[](nat i) const {
    return *(&x1 + i);
}

template <typename T>
template <nat t_i, nat t_j>
inline T & mat<T, 2, 2>::at() {
    return detail::MatAccessor<t_i, t_j>::access(*this);
}

template <typename T>
template <nat t_i, nat t_j>
inline T mat<T, 2, 2>::at() const {
    return detail::MatAccessor<t_i, t_j>::access(*this);
}

template <typename T>
inline vec2<T> mat<T, 2, 2>::col(nat i) const {
    nat stride(i * 2);
    return vec2<T>(*(&x1 + stride), *(&y1 + stride));
}

template <typename T>
inline vec2<T> mat<T, 2, 2>::row(nat i) const {
    return vec2<T>(*(&x1 + i), *(&y1 + i));
}

template <typename T>
template <nat t_i>
inline vec2<T> mat<T, 2, 2>::row() const {
    return vec2<T>(at<t_i, 0>(), at<t_i, 1>());
}

template <typename T>
template <nat t_j>
inline vec2<T> mat<T, 2, 2>::col() const {
    return vec2<T>(at<0, t_j>(), at<1, t_j>());
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string mat<T, 2, 2>::toString() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT3 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr mat<T, 3, 3>::mat() :
    x1(static_cast<T>(1.0)), y1(static_cast<T>(0.0)), z1(static_cast<T>(0.0)),
    x2(static_cast<T>(0.0)), y2(static_cast<T>(1.0)), z2(static_cast<T>(0.0)),
    x3(static_cast<T>(0.0)), y3(static_cast<T>(0.0)), z3(static_cast<T>(1.0))
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
    x1(m.x1),                y1(m.y1),                z1(static_cast<T>(0.0)),
    x2(m.x2),                y2(m.y2),                z2(static_cast<T>(0.0)),
    x3(static_cast<T>(0.0)), y3(static_cast<T>(0.0)), z3(static_cast<T>(1.0))
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
inline mat3<T> & mat<T, 3, 3>::operator=(const mat2<T> & m) {
    x1 = m.x1;                y1 = m.y1;                z1 = static_cast<T>(0.0);
    x2 = m.x2;                y2 = m.y2;                z2 = static_cast<T>(0.0);
    x3 = static_cast<T>(0.0); y3 = static_cast<T>(0.0); z3 = static_cast<T>(1.0);

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
// Access



template <typename T>
inline T & mat<T, 3, 3>::operator[](nat i) {
    return *(&x1 + i);
}

template <typename T>
inline T mat<T, 3, 3>::operator[](nat i) const {
    return *(&x1 + i);
}

template <typename T>
template <nat t_i, nat t_j>
inline T & mat<T, 3, 3>::at() {
    return detail::MatAccessor<t_i, t_j>::access(*this);
}

template <typename T>
template <nat t_i, nat t_j>
inline T mat<T, 3, 3>::at() const {
    return detail::MatAccessor<t_i, t_j>::access(*this);
}

template <typename T>
inline vec3<T> mat<T, 3, 3>::col(nat i) const {
    nat stride(i * 3);
    return vec3<T>(*(&x1 + stride), *(&y1 + stride), *(&z1 + stride));
}

template <typename T>
inline vec3<T> mat<T, 3, 3>::row(nat i) const {
    return vec3<T>(*(&x1 + i), *(&y1 + i), *(&z1 + i));
}

template <typename T>
template <nat t_i>
inline vec3<T> mat<T, 3, 3>::row() const {
    return vec3<T>(at<t_i, 0>(), at<t_i, 1>(), at<t_i, 2>());
}

template <typename T>
template <nat t_j>
inline vec3<T> mat<T, 3, 3>::col() const {
    return vec3<T>(at<0, t_j>(), at<1, t_j>(), at<2, t_j>());
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string mat<T, 3, 3>::toString() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT4 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr mat<T, 4, 4>::mat() :
    x1(static_cast<T>(1.0)), y1(static_cast<T>(0.0)), z1(static_cast<T>(0.0)), w1(static_cast<T>(0.0)),
    x2(static_cast<T>(0.0)), y2(static_cast<T>(1.0)), z2(static_cast<T>(0.0)), w2(static_cast<T>(0.0)),
    x3(static_cast<T>(0.0)), y3(static_cast<T>(0.0)), z3(static_cast<T>(1.0)), w3(static_cast<T>(0.0)),
    x4(static_cast<T>(0.0)), y4(static_cast<T>(0.0)), z4(static_cast<T>(0.0)), w4(static_cast<T>(1.0))
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
    x1(m.x1),                y1(m.y1),                z1(static_cast<T>(0.0)), w1(static_cast<T>(0.0)),
    x2(m.x2),                y2(m.y2),                z2(static_cast<T>(0.0)), w2(static_cast<T>(0.0)),
    x3(static_cast<T>(0.0)), y3(static_cast<T>(0.0)), z3(static_cast<T>(1.0)), w3(static_cast<T>(0.0)),
    x4(static_cast<T>(0.0)), y4(static_cast<T>(0.0)), z4(static_cast<T>(0.0)), w4(static_cast<T>(1.0))
{}

template <typename T>
constexpr mat<T, 4, 4>::mat(const mat3<T> & m) :
    x1(m.x1),                y1(m.y1),                z1(m.z1),                w1(static_cast<T>(0.0)),
    x2(m.x2),                y2(m.y2),                z2(m.z2),                w2(static_cast<T>(0.0)),
    x3(m.x3),                y3(m.y3),                z3(m.z3),                w3(static_cast<T>(0.0)),
    x4(static_cast<T>(0.0)), y4(static_cast<T>(0.0)), z4(static_cast<T>(0.0)), w4(static_cast<T>(1.0))
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
inline mat4<T> & mat<T, 4, 4>::operator=(const mat2<T> & m) {
    x1 = m.x1;                y1 = m.y1;                z1 = static_cast<T>(0.0); w1 = static_cast<T>(0.0);
    x2 = m.x2;                y2 = m.y2;                z2 = static_cast<T>(0.0); w2 = static_cast<T>(0.0);
    x3 = static_cast<T>(0.0); y3 = static_cast<T>(0.0); z3 = static_cast<T>(1.0); w3 = static_cast<T>(0.0);
    x4 = static_cast<T>(0.0); y4 = static_cast<T>(0.0); z4 = static_cast<T>(0.0); w4 = static_cast<T>(1.0);

    return *this;
}

template <typename T>
inline mat4<T> & mat<T, 4, 4>::operator=(const mat3<T> & m) {
    x1 = m.x1;                y1 = m.y1;                z1 = m.z1;                w1 = static_cast<T>(0.0);
    x2 = m.x2;                y2 = m.y2;                z2 = m.z2;                w2 = static_cast<T>(0.0);
    x3 = m.x3;                y3 = m.y3;                z3 = m.z3;                w3 = static_cast<T>(0.0);
    x4 = static_cast<T>(0.0); y4 = static_cast<T>(0.0); z4 = static_cast<T>(0.0); w4 = static_cast<T>(1.0);

    return *this;
}



//------------------------------------------------------------------------------
// Access



template <typename T>
inline T & mat<T, 4, 4>::operator[](nat i) {
    return *(&x1 + i);
}

template <typename T>
inline T mat<T, 4, 4>::operator[](nat i) const {
    return *(&x1 + i);
}

template <typename T>
template <nat t_i, nat t_j>
inline T & mat<T, 4, 4>::at() {
    return detail::MatAccessor<t_i, t_j>::access(*this);
}

template <typename T>
template <nat t_i, nat t_j>
inline T mat<T, 4, 4>::at() const {
    return detail::MatAccessor<t_i, t_j>::access(*this);
}

template <typename T>
inline vec4<T> mat<T, 4, 4>::col(nat i) const {
    nat stride(i * 4);
    return vec4<T>(*(&x1 + stride), *(&y1 + stride), *(&z1 + stride), *(&w1 + stride));
}

template <typename T>
inline vec4<T> mat<T, 4, 4>::row(nat i) const {
    return vec4<T>(*(&x1 + i), *(&y1 + i), *(&z1 + i), *(&w1 + i));
}

template <typename T>
template <nat t_i>
inline vec4<T> mat<T, 4, 4>::row() const {
    return vec4<T>(at<t_i, 0>(), at<t_i, 1>(), at<t_i, 2>(), at<t_i, 3>());
}

template <typename T>
template <nat t_j>
inline vec4<T> mat<T, 4, 4>::col() const {
    return vec4<T>(at<0, t_j>(), at<1, t_j>(), at<2, t_j>(), at<3, t_j>());
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string mat<T, 4, 4>::toString() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT FUNCTIONS IMPLEMENTATION ----------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Arithmetic Assignment



//--- add assign ---

template <typename T, nat t_m, nat t_n>
inline mat<T, t_m, t_n> & operator+=(mat<T, t_m, t_n> & m, T v) {
    return m = m + v;
}

template <typename T, nat t_m, nat t_n>
inline mat<T, t_m, t_n> & operator+=(mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2) {
    return m1 = m1 + m2;
}

//--- subtract assign ---

template <typename T, nat t_m, nat t_n>
inline mat<T, t_m, t_n> & operator-=(mat<T, t_m, t_n> & m, T v) {
    return m = m - v;
}

template <typename T, nat t_m, nat t_n>
inline mat<T, t_m, t_n> & operator-=(mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2) {
    return m1 = m1 - m2;
}

//--- multiply assign ---

template <typename T, nat t_m, nat t_n>
inline mat<T, t_m, t_n> & operator*=(mat<T, t_m, t_n> & m, T v) {
    return m = m * v;
}

template <typename T, nat t_m, nat t_n>
inline mat<T, t_m, t_n> & operator*=(mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2) {
    return m1 = m1 * m2;
}

//--- divide assign ---

template <typename T, nat t_m, nat t_n>
inline mat<T, t_m, t_n> & operator/=(mat<T, t_m, t_n> & m, T v) {
    return m = m / v;
}

//--- pre increment ---

template <typename T>
inline mat2<T> & operator++(mat2<T> & m) {
    ++m.x1; ++m.y1;
    ++m.x2; ++m.y2;

    return m;
}

template <typename T>
inline mat3<T> & operator++(mat3<T> & m) {
    ++m.x1; ++m.y1; ++m.z1;
    ++m.x2; ++m.y2; ++m.z2;
    ++m.x3; ++m.y3; ++m.z3;

    return m;
}

template <typename T>
inline mat4<T> & operator++(mat4<T> & m) {
    ++m.x1; ++m.y1; ++m.z1; ++m.w1;
    ++m.x2; ++m.y2; ++m.z2; ++m.w2;
    ++m.x3; ++m.y3; ++m.z3; ++m.w3;
    ++m.x4; ++m.y4; ++m.z4; ++m.w4;

    return m;
}

//--- post increment ---

template <typename T, nat t_m, nat t_n>
inline mat<T, t_m, t_n> operator++(mat<T, t_m, t_n> & m, int) {
    mat<T, t_m, t_n> temp(m);
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

template <typename T>
inline mat3<T> & operator--(mat3<T> & m) {
    --m.x1; --m.y1; --m.z1;
    --m.x2; --m.y2; --m.z2;
    --m.x3; --m.y3; --m.z3;

    return m;
}

template <typename T>
inline mat4<T> & operator--(mat4<T> & m) {
    --m.x1; --m.y1; --m.z1; --m.w1;
    --m.x2; --m.y2; --m.z2; --m.w2;
    --m.x3; --m.y3; --m.z3; --m.w3;
    --m.x4; --m.y4; --m.z4; --m.w4;

    return m;
}

//--- post decrement ---

template <typename T, nat t_m, nat t_n>
inline mat<T, t_m, t_n> operator--(mat<T, t_m, t_n> & m, int) {
    mat<T, t_m, t_n> temp(m);
    --m;

    return temp;
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- positive ---

template <typename T, nat t_m, nat t_n>
inline mat<T, t_m, t_n> operator+(const mat<T, t_m, t_n> & m) {
    return m;
}

//--- negative ---

template <typename T>
inline mat2<T> operator-(const mat2<T> & m) {
    return mat2<T>(
        -m.x1, -m.y1,
        -m.x2, -m.y2
    );
}

template <typename T>
inline mat3<T> operator-(const mat3<T> & m) {
    return mat3<T>(
        -m.x1, -m.y1, -m.z1,
        -m.x2, -m.y2, -m.z2,
        -m.x3, -m.y3, -m.z3
    );
}

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
inline mat2<T> operator+(const mat2<T> & m1, const mat2<T> & m2) {
    return mat2<T>(
        m1.x1 + m2.x1, m1.y1 + m2.y1,
        m1.x2 + m2.x2, m1.y2 + m2.y2
    );
}

template <typename T>
inline mat3<T> operator+(const mat3<T> & m1, const mat3<T> & m2) {
    return mat3<T>(
        m1.x1 + m2.x1, m1.y1 + m2.y1, m1.z1 + m2.z1,
        m1.x2 + m2.x2, m1.y2 + m2.y2, m1.z2 + m2.z2,
        m1.x3 + m2.x3, m1.y3 + m2.y3, m1.z3 + m2.z3
    );
}

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
inline mat2<T> operator+(const mat2<T> & m, T v) {
    return mat2<T>(
        m.x1 + v, m.y1 + v,
        m.x2 + v, m.y2 + v
    );
}

template <typename T>
inline mat3<T> operator+(const mat3<T> & m, T v) {
    return mat3<T>(
        m.x1 + v, m.y1 + v, m.z1 + v,
        m.x2 + v, m.y2 + v, m.z2 + v,
        m.x3 + v, m.y3 + v, m.z3 + v
    );
}

template <typename T>
inline mat4<T> operator+(const mat4<T> & m, T v) {
    return mat4<T>(
        m.x1 + v, m.y1 + v, m.z1 + v, m.w1 + v,
        m.x2 + v, m.y2 + v, m.z2 + v, m.w2 + v,
        m.x3 + v, m.y3 + v, m.z3 + v, m.w3 + v,
        m.x4 + v, m.y4 + v, m.z4 + v, m.w4 + v
    );
}

template <typename T>
inline mat2<T> operator+(T v, const mat2<T> & m) {
    return mat2<T>(
        v + m.x1, v + m.y1,
        v + m.x2, v + m.y2
    );
}

template <typename T>
inline mat3<T> operator+(T v, const mat3<T> & m) {
    return mat3<T>(
        v + m.x1, v + m.y1, v + m.z1,
        v + m.x2, v + m.y2, v + m.z2,
        v + m.x3, v + m.y3, v + m.z3
    );
}

template <typename T>
inline mat4<T> operator+(T v, const mat4<T> & m) {
    return mat4<T>(
        v + m.x1, v + m.y1, v + m.z1, v + m.w1,
        v + m.x2, v + m.y2, v + m.z2, v + m.w2,
        v + m.x3, v + m.y3, v + m.z3, v + m.w3,
        v + m.x4, v + m.y4, v + m.z4, v + m.w4
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
inline mat3<T> operator-(const mat3<T> & m1, const mat3<T> & m2) {
    return mat3<T>(
        m1.x1 - m2.x1, m1.y1 - m2.y1, m1.z1 - m2.z1,
        m1.x2 - m2.x2, m1.y2 - m2.y2, m1.z2 - m2.z2,
        m1.x3 - m2.x3, m1.y3 - m2.y3, m1.z3 - m2.z3
    );
}

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
inline mat2<T> operator-(const mat2<T> & m, T v) {
    return mat2<T>(
        m.x1 - v, m.y1 - v,
        m.x2 - v, m.y2 - v
    );
}

template <typename T>
inline mat3<T> operator-(const mat3<T> & m, T v) {
    return mat3<T>(
        m.x1 - v, m.y1 - v, m.z1 - v,
        m.x2 - v, m.y2 - v, m.z2 - v,
        m.x3 - v, m.y3 - v, m.z3 - v
    );
}

template <typename T>
inline mat4<T> operator-(const mat4<T> & m, T v) {
    return mat4<T>(
        m.x1 - v, m.y1 - v, m.z1 - v, m.w1 - v,
        m.x2 - v, m.y2 - v, m.z2 - v, m.w2 - v,
        m.x3 - v, m.y3 - v, m.z3 - v, m.w3 - v,
        m.x4 - v, m.y4 - v, m.z4 - v, m.w4 - v
    );
}

template <typename T>
inline mat2<T> operator-(T v, const mat2<T> & m) {
    return mat2<T>(
        v - m.x1, v - m.y1,
        v - m.x2, v - m.y2
    );
}

template <typename T>
inline mat3<T> operator-(T v, const mat3<T> & m) {
    return mat3<T>(
        v - m.x1, v - m.y1, v - m.z1,
        v - m.x2, v - m.y2, v - m.z2,
        v - m.x3, v - m.y3, v - m.z3
    );
}

template <typename T>
inline mat4<T> operator-(T v, const mat4<T> & m) {
    return mat4<T>(
        v - m.x1, v - m.y1, v - m.z1, v - m.w1,
        v - m.x2, v - m.y2, v - m.z2, v - m.w2,
        v - m.x3, v - m.y3, v - m.z3, v - m.w3,
        v - m.x4, v - m.y4, v - m.z4, v - m.w4
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
inline mat2<T> operator*(const mat2<T> & m, T v) {
    return mat2<T>(
        m.x1 * v, m.y1 * v,
        m.x2 * v, m.y2 * v
    );
}

template <typename T>
inline mat3<T> operator*(const mat3<T> & m, T v) {
    return mat3<T>(
        m.x1 * v, m.y1 * v, m.z1 * v,
        m.x2 * v, m.y2 * v, m.z2 * v,
        m.x3 * v, m.y3 * v, m.z3 * v
    );
}

template <typename T>
inline mat4<T> operator*(const mat4<T> & m, T v) {
    return mat4<T>(
        m.x1 * v, m.y1 * v, m.z1 * v, m.w1 * v,
        m.x2 * v, m.y2 * v, m.z2 * v, m.w2 * v,
        m.x3 * v, m.y3 * v, m.z3 * v, m.w3 * v,
        m.x4 * v, m.y4 * v, m.z4 * v, m.w4 * v
    );
}

template <typename T>
inline mat2<T> operator*(T v, const mat2<T> & m) {
    return mat2<T>(
        v * m.x1, v * m.y1,
        v * m.x2, v * m.y2
    );
}

template <typename T>
inline mat3<T> operator*(T v, const mat3<T> & m) {
    return mat3<T>(
        v * m.x1, v * m.y1, v * m.z1,
        v * m.x2, v * m.y2, v * m.z2,
        v * m.x3, v * m.y3, v * m.z3
    );
}

template <typename T>
inline mat4<T> operator*(T v, const mat4<T> & m) {
    return mat4<T>(
        v * m.x1, v * m.y1, v * m.z1, v * m.w1,
        v * m.x2, v * m.y2, v * m.z2, v * m.w2,
        v * m.x3, v * m.y3, v * m.z3, v * m.w3,
        v * m.x4, v * m.y4, v * m.z4, v * m.w4
    );
}

template <typename T>
inline vec2<T> operator*(const mat2<T> & m, const vec2<T> & v) {
    return vec2<T>(
        v.x * m.x1 + v.y * m.x2,
        v.x * m.y1 + v.y * m.y2
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
inline mat2<T> operator/(const mat2<T> & m, T v) {
    return mat2<T>(
        m.x1 / v, m.y1 / v,
        m.x2 / v, m.y2 / v
    );
}

template <typename T>
inline mat3<T> operator/(const mat3<T> & m, T v) {
    return mat3<T>(
        m.x1 / v, m.y1 / v, m.z1 / v,
        m.x2 / v, m.y2 / v, m.z2 / v,
        m.x3 / v, m.y3 / v, m.z3 / v
    );
}

template <typename T>
inline mat4<T> operator/(const mat4<T> & m, T v) {
    return mat4<T>(
        m.x1 / v, m.y1 / v, m.z1 / v, m.w1 / v,
        m.x2 / v, m.y2 / v, m.z2 / v, m.w2 / v,
        m.x3 / v, m.y3 / v, m.z3 / v, m.w3 / v,
        m.x4 / v, m.y4 / v, m.z4 / v, m.w4 / v
    );
}

template <typename T>
inline mat2<T> operator/(T v, const mat2<T> & m) {
    return mat2<T>(
        v / m.x1, v / m.y1,
        v / m.x2, v / m.y2
    );
}

template <typename T>
inline mat3<T> operator/(T v, const mat3<T> & m) {
    return mat3<T>(
        v / m.x1, v / m.y1, v / m.z1,
        v / m.x2, v / m.y2, v / m.z2,
        v / m.x3, v / m.y3, v / m.z3
    );
}

template <typename T>
inline mat4<T> operator/(T v, const mat4<T> & m) {
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
inline bool operator==(const mat2<T> & m1, const mat2<T> & m2) {
    return
        m1.x1 == m2.x1 && m1.y1 == m2.y1 &&
        m1.x2 == m2.x2 && m1.y2 == m2.y2;
}

template <typename T>
inline bool operator==(const mat3<T> & m1, const mat3<T> & m2) {
    return
        m1.x1 == m2.x1 && m1.y1 == m2.y1 && m1.z1 == m2.z1 &&
        m1.x2 == m2.x2 && m1.y2 == m2.y2 && m1.z2 == m2.z2 &&
        m1.x3 == m2.x3 && m1.y3 == m2.y3 && m1.z3 == m2.z3;
}

template <typename T>
inline bool operator==(const mat4<T> & m1, const mat4<T> & m2) {
    return
        m1.x1 == m2.x1 && m1.y1 == m2.y1 && m1.z1 == m2.z1 && m1.w1 == m2.w1 &&
        m1.x2 == m2.x2 && m1.y2 == m2.y2 && m1.z2 == m2.z2 && m1.w2 == m2.w2 &&
        m1.x3 == m2.x3 && m1.y3 == m2.y3 && m1.z3 == m2.z3 && m1.w3 == m2.w3 &&
        m1.x4 == m2.x4 && m1.y4 == m2.y4 && m1.z4 == m2.z4 && m1.w4 == m2.w4;
}

//--- not equal to ---

template <typename T, nat t_m, nat t_n>
inline bool operator!=(const mat<T, t_m, t_n> & m1, const mat<T, t_m, t_n> & m2) {
    return !(m1 == m2);
}



//------------------------------------------------------------------------------
// Other

template <typename T>
inline std::ostream & operator<<(std::ostream & os, const mat2<T> & m) {
    return os
        << "[ "
        << m.x1 << " " << m.y1
        << " | "
        << m.x2 << " " << m.y2
        << " ]";
}

template <typename T>
inline std::ostream & operator<<(std::ostream & os, const mat3<T> & m) {
    return os
        << "[ "
        << m.x1 << " " << m.y1 << " " << m.z1
        << " | "
        << m.x2 << " " << m.y2 << " " << m.z2
        << " | "
        << m.x3 << " " << m.y3 << " " << m.z3
        << " ]";
}

template <typename T>
inline std::ostream & operator<<(std::ostream & os, const mat4<T> & m) {
    return os
        << "[ "
        << m.x1 << " " << m.y1 << " " << m.z1 << " " << m.w1
        << " | "
        << m.x2 << " " << m.y2 << " " << m.z2 << " " << m.w2
        << " | "
        << m.x3 << " " << m.y3 << " " << m.z3 << " " << m.w3
        << " | "
        << m.x4 << " " << m.y4 << " " << m.z4 << " " << m.w4
        << " ]";
}



//------------------------------------------------------------------------------
// Other



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
    T det(determinant(m));
    if (zero(det)) {
        return nullMat<T, 2>();
    }

    return adjoint(m) * (static_cast<T>(1.0) / determinant(m));
}

template <typename T>
inline mat3<T> inverse(const mat3<T> & m) {
    T det(determinant(m));
    if (zero(det)) {
        return nullMat<T, 3>();
    }

    return adjoint(m) * (static_cast<T>(1.0) / determinant(m));
}

template <typename T>
inline mat4<T> inverse(const mat4<T> & m) {
    T det(determinant(m));
    if (zero(det)) {
        return nullMat<T, 4>();
    }

    return adjoint(m) * (static_cast<T>(1.0) / determinant(m));
}

namespace detail {

template <nat t_m, nat t_n>
struct MatFiller;

template <>
struct MatFiller<2, 2> {
    template <typename T>
    static constexpr mat2<T> fill(T v) {
        return mat2<T>(
            v, v,
            v, v
        );
    }
};

template <>
struct MatFiller<3, 3> {
    template <typename T>
    static constexpr mat3<T> fill(T v) {
        return mat3<T>(
            v, v, v,
            v, v, v,
            v, v, v
        );
    }
};

template <>
struct MatFiller<4, 4> {
    template <typename T>
    static constexpr mat4<T> fill(T v) {
        return mat4<T>(
            v, v, v, v,
            v, v, v, v,
            v, v, v, v,
            v, v, v, v
        );
    }
};

}

template <typename T, nat t_m, nat t_n>
constexpr mat<T, t_m, t_n> fullMat(T v) {
    return detail::MatFiller<t_m, t_n>::fill(v);
}

template <typename T, nat t_m, nat t_n>
constexpr mat<T, t_m, t_n> nullMat() {
    return fullMat<T, t_m, t_n>(static_cast<T>(0.0));
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORMATIONS IMPLEMENTATION --------------------------------------------------------------------------------------



template <typename T>
inline mat2<T> translate(const vec1<T> & delta) {
    return mat2<T>(
        static_cast<T>(1.0), static_cast<T>(0.0),
        delta.x,             static_cast<T>(1.0)
    );
}

template <typename T>
inline mat3<T> translate(const vec2<T> & delta) {
    return mat3<T>(
        static_cast<T>(1.0), static_cast<T>(0.0), static_cast<T>(0.0),
        static_cast<T>(0.0), static_cast<T>(1.0), static_cast<T>(0.0),
        delta.x,             delta.y,             static_cast<T>(1.0)
    );
}

template <typename T>
inline mat4<T> translate(const vec3<T> & delta) {
    return mat4<T>(
        static_cast<T>(1.0), static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(0.0),
        static_cast<T>(0.0), static_cast<T>(1.0), static_cast<T>(0.0), static_cast<T>(0.0),
        static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(1.0), static_cast<T>(0.0),
        delta.x,             delta.y,             delta.z,             static_cast<T>(1.0)
    );
}

template <typename T>
inline mat2<T> & translate(mat2<T> & mat, const vec1<T> & delta) {
    mat.x1 += delta.x * mat.y1;
    mat.x2 += delta.x * mat.y2;
    return mat;
}

template <typename T>
inline mat3<T> & translate(mat3<T> & mat, const vec2<T> & delta) {
    mat.x1 += delta.x * mat.z1;
    mat.x2 += delta.x * mat.z2;
    mat.x3 += delta.x * mat.z3;
    mat.y1 += delta.y * mat.z1;
    mat.y2 += delta.y * mat.z2;
    mat.y3 += delta.y * mat.z3;
    return mat;
}

template <typename T>
inline mat4<T> & translate(mat4<T> & mat, const vec3<T> & delta) {
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
        scale.x,             static_cast<T>(0.0),
        static_cast<T>(0.0), scale.y
    );
}

template <typename T>
inline mat3<T> scale(const vec3<T> & scale) {
    return mat3<T>(
        scale.x,             static_cast<T>(0.0), static_cast<T>(0.0),
        static_cast<T>(0.0), scale.y,             static_cast<T>(0.0),
        static_cast<T>(0.0), static_cast<T>(0.0), scale.z
    );
}

template <typename T>
inline mat2<T> & scale(mat2<T> & mat, const vec1<T> & scale) {
    mat.x1 *= scale.x;
    mat.x2 *= scale.x;
    return mat;
}

template <typename T>
inline mat2<T> & scale(mat2<T> & mat, const vec2<T> & scale) {
    mat.x1 *= scale.x;
    mat.x2 *= scale.x;
    mat.y1 *= scale.y;
    mat.y2 *= scale.y;
    return mat;
}

template <typename T>
inline mat3<T> & scale(mat3<T> & mat, const vec2<T> & scale) {
    mat.x1 *= scale.x;
    mat.x2 *= scale.x;
    mat.x3 *= scale.x;
    mat.y1 *= scale.y;
    mat.y2 *= scale.y;
    mat.y3 *= scale.y;
    return mat;
}

template <typename T>
inline mat3<T> & scale(mat3<T> & mat, const vec3<T> & scale) {
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
inline mat4<T> & scale(mat4<T> & mat, const vec3<T> & scale) {
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
inline mat4<T> & scale(mat4<T> & mat, const vec4<T> & scale) {
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
inline mat2<T> rotate(T theta) {
    T s(std::sin(theta));
    T c(std::cos(theta));

    return mat2<T>(
        c, s,
        -s, c
    );
}

template <typename T>
inline mat3<T> rotateX(T theta) {
    T s(std::sin(theta));
    T c(std::cos(theta));

    return mat3<T>(
        static_cast<T>(1.0), static_cast<T>(0.0), static_cast<T>(0.0),
        static_cast<T>(0.0), c,                   s,
        static_cast<T>(0.0), -s,                  c
    );
}

template <typename T>
inline mat3<T> rotateY(T theta) {
    T s(std::sin(theta));
    T c(std::cos(theta));

    return mat3<T>(
        c,                   static_cast<T>(0.0), -s,
        static_cast<T>(0.0), static_cast<T>(1.0), static_cast<T>(0.0),
        s,                   static_cast<T>(0.0), c
    );
}

template <typename T>
inline mat3<T> rotateZ(T theta) {
    T s(std::sin(theta));
    T c(std::cos(theta));

    return mat3<T>(
        c,                   s,                   static_cast<T>(0.0),
        -s,                  c,                   static_cast<T>(0.0),
        static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(1.0)
    );
}

template <typename T>
inline mat3<T> rotate(const vec3<T> & axis, T sinTheta, T cosTheta) {
    if (zero(magnitude2(axis))) { //can't rotate around 0 length fvector
        return nullMat<T, 3>();
    }

    return rotate_n(norm(axis), sinTheta, cosTheta);
}
template <typename T>
inline mat3<T> rotate_n(const vec3<T> & axis, T s, T c) {
    T cm(static_cast<T>(1.0) - c);
    T xs(axis.x * s);
    T ys(axis.y * s);
    T zs(axis.z * s);
    T xcm(axis.x * cm);
    T ycm(axis.y * cm);
    T zcm(axis.z * cm);
    T xycm(xcm * axis.y);
    T yzcm(ycm * axis.z);
    T zxcm(xcm * axis.x);

    return mat3<T>(
        c + xcm * axis.x, xycm + zs,        zxcm - ys,
        xycm - zs,        c + ycm * axis.y, yzcm + xs,
        zxcm + ys,        yzcm - xs,        c + zcm * axis.z
    );
}

template <typename T>
inline mat3<T> rotate(const vec3<T> & axis, T theta) {
    return rotate(axis, std::sin(theta), std::cos(theta));
}
template <typename T>
inline mat3<T> rotate_n(const vec3<T> & axis, T theta) {
    return rotate_n(axis, std::sin(theta), std::cos(theta));
}

template <typename T>
inline mat3<T> euler(const vec3<T> & forward, const vec3<T> & up, T theta, T phi, T psi) {
    return euler_n(norm(forward), norm(up), theta, phi, psi);
}
template <typename T>
inline mat3<T> euler_n(const vec3<T> & forward, const vec3<T> & up, T theta, T phi, T psi) {
    return rotate_n(up, theta) * rotate_n(cross(forward, up), phi) * rotate_n(forward, psi);
}

template <typename T, nat t_n>
inline mat<T, t_n> align(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    return align_n(norm(v1), norm(v2));
}
template <typename T>
inline mat2<T> align_n(const vec2<T> & v1, const vec2<T> & v2) {
    T c(cross(v1, v2));
    T d(dot(v1, v2));

    return rotate(c < static_cast<T>(0.0) ? -std::acos(d) : std::acos(d));
}
template <typename T>
inline mat3<T> align_n(const vec3<T> & v1, const vec3<T> & v2) {
    T d(dot(v1, v2));
    if (equal(d, static_cast<T>(1.0))) { // already aligned, and would break rotation
        return mat3<T>();
    }
    if (equal(d, static_cast<T>(-1.0))) { // opposite direction, pick arbitrary axis to rotate around
        return rotate_n(ortho(v1), pi<T>);
    }

    vec3<T> c(cross(v1, v2));
    T m(magnitude(c));

    return rotate_n(c * (static_cast<T>(1.0) / m), m, d);
}

template <typename T>
inline mat3<T> align(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2) {
    return align_n(norm(forward1), norm(up1), norm(forward2), norm(up2));
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
inline mat4<T> orthoProj(T width, T height, T near, T far) {
    return mat4<T>(
        static_cast<T>(2.0) / width, static_cast<T>(0.0),          static_cast<T>(0.0),                static_cast<T>(0.0),
        static_cast<T>(0.0),         static_cast<T>(2.0) / height, static_cast<T>(0.0),                static_cast<T>(0.0),
        static_cast<T>(0.0),         static_cast<T>(0.0),          static_cast<T>(2.0) / (near - far), static_cast<T>(0.0),
        static_cast<T>(0.0),         static_cast<T>(0.0),          (far + near) / (near - far),        static_cast<T>(1.0)
    );
}

template <typename T>
inline mat4<T> orthoProjAsym(T left, T right, T bottom, T top, T near, T far) {
    return mat4<T>(
        static_cast<T>(2.0) / (right - left), static_cast<T>(0.0),                  static_cast<T>(0.0),                static_cast<T>(0.0),
        static_cast<T>(0.0),                  static_cast<T>(2.0) / (top - bottom), static_cast<T>(0.0),                static_cast<T>(0.0),
        static_cast<T>(0.0),                  static_cast<T>(0.0),                  static_cast<T>(2.0) / (near - far), static_cast<T>(0.0),
        (right + left) / (left - right),      (top + bottom) / (bottom - top),      (far + near) / (near - far),        static_cast<T>(1.0)
    );
}

template <typename T>
inline mat4<T> perspProj(T fov, T aspectRatio, T near, T far) {
    T near_right(static_cast<T>(1.0) / std::tan(fov / static_cast<T>(2.0)));

    return mat4<T>(
        near_right,          static_cast<T>(0.0),      static_cast<T>(0.0),                             static_cast<T>(0.0),
        static_cast<T>(0.0), near_right / aspectRatio, static_cast<T>(0.0),                             static_cast<T>(0.0),
        static_cast<T>(0.0), static_cast<T>(0.0),      (far + near) / (near - far),                     static_cast<T>(-1.0),
        static_cast<T>(0.0), static_cast<T>(0.0),      static_cast<T>(2.0) * far * near / (near - far), static_cast<T>(0.0)
    );
}

template <typename T>
inline mat4<T> perspProjAsym(T fovLeft, T fovRight, T fovBottom, T fovTop, T near, T far) {
    T left(near * -std::tan(fovLeft));
    T right(near * std::tan(fovRight));
    T bottom(near * -std::tan(fovBottom));
    T top(near * std::tan(fovTop));

    return mat4<T>(
        static_cast<T>(2.0) * near / (right - left), static_cast<T>(0.0),                         static_cast<T>(0.0),                             static_cast<T>(0.0),
        static_cast<T>(0.0),                         static_cast<T>(2.0) * near / (top - bottom), static_cast<T>(0.0),                             static_cast<T>(0.0),
        (right + left) / (right - left),             (top + bottom) / (top - bottom),             (far + near) / (near - far),                     static_cast<T>(-1.0),
        static_cast<T>(0.0),                         static_cast<T>(0.0),                         static_cast<T>(2.0) * far * near / (near - far), static_cast<T>(0.0)
    );
}

template <typename T>
inline mat4<T> view(const vec3<T> & camLoc, const vec3<T> & camForward, const vec3<T> & up) {
    vec3<T> z(norm(-camForward));
    vec3<T> x(norm(cross(up, z)));
    vec3<T> y(norm(cross(z, x)));

    return mat4<T>(mapTo_o(x, y, z)) * translate(-camLoc);
}

template <typename T>
inline mat4<T> view(const vec3<T> & camLoc, const vec3<T> & camX, const vec3<T> & camY, const vec3<T> & camZ) {
    return view_n(camLoc, norm(camX), norm(camY), norm(camZ));
}

template <typename T>
inline mat4<T> view_n(const vec3<T> & camLoc, const vec3<T> & camX, const vec3<T> & camY, const vec3<T> & camZ) {
    return mat4<T>(mapTo(camX, camY, camZ)) * translate(-camLoc);
}

template <typename T>
inline mat4<T> view_o(const vec3<T> & camLoc, const vec3<T> & camX, const vec3<T> & camY, const vec3<T> & camZ) {
    return view_on(camLoc, norm(camX), norm(camY), norm(camZ));
}

template <typename T>
inline mat4<T> view_on(const vec3<T> & camLoc, const vec3<T> & camX, const vec3<T> & camY, const vec3<T> & camZ) {
    return mat4<T>(mapTo_o(camX, camY, camZ)) * translate(-camLoc);
}



}