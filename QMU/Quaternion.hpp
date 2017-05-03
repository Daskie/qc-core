#pragma once



#include "Matrix.hpp"



namespace qmu {



template <typename T> struct quat;



using  fquat = quat< float>;
using  dquat = quat<double>;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUAT ----------------------------------------------------------------------------------------------------------------

template <typename T>
struct quat {

    union {
        struct {
            T x, y, z, w;
        };
        struct {
            vec3<T> v;
            T w;
        };
        vec4<T> v4;
    };

    //--- constructors ---

    constexpr quat();
    constexpr quat(const quat & q);
    constexpr quat(quat && q);

    template <typename U> constexpr explicit quat(const quat<U> & q);

    constexpr quat(const vec3<T> & v, const T & w);
    constexpr quat(const T & x, const T & y, const T & z, const T & w);
    constexpr explicit quat(const vec3<T> & v);
    constexpr explicit quat(const vec4<T> & v);

    //--- assignment operators ---

    quat & operator=(const quat & q);
    quat & operator=(quat && q);

    //--- access operators ---

    T operator[](nat i);

    //--- other ---

    std::string toString() const;

};

//--- arithmetic assignment operators ---

template <typename T> quat<T> & operator+=(quat<T> & q1, const quat<T> & q2);

template <typename T> quat<T> & operator-=(quat<T> & q1, const quat<T> & q2);

template <typename T> quat<T> & operator*=(quat<T> & q1, const quat<T> & q2);
template <typename T> quat<T> & operator*=(quat<T> &  q, const      T  &  v);

template <typename T> quat<T> & operator/=(quat<T> & q1, const quat<T> & q2);

//--- arithmetic operators ---

template <typename T> quat<T> operator+(const quat<T> & q);

template <typename T> quat<T> operator-(const quat<T> & q);

template <typename T> quat<T> operator+(const quat<T> & q1, const quat<T> & q2);

template <typename T> quat<T> operator-(const quat<T> & q1, const quat<T> & q2);

template <typename T> quat<T> operator*(const quat<T> & q1, const quat<T> & q2);
template <typename T> quat<T> operator*(const quat<T> &  q, const      T  &  v);
template <typename T> quat<T> operator*(const      T  &  v, const quat<T> &  q);
template <typename T> vec3<T> operator*(const quat<T> &  q, const vec3<T> &  v);

template <typename T> quat<T> operator/(const quat<T> & q1, const quat<T> & q2);

//--- comparison operators ---

template <typename T> bool operator==(const quat<T> & q1, const quat<T> & q2);

template <typename T> bool operator!=(const quat<T> & q1, const quat<T> & q2);


//--- other ---

template <typename T> std::ostream & operator<<(std::ostream & os, const quat<T> & q);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUAT FUNCTIONS ------------------------------------------------------------------------------------------------------



template <typename T> T magnitude(const quat<T> & q);

template <typename T> quat<T> normalize(const quat<T> & q);

template <typename T> quat<T> inverse(const quat<T> & q);

template <typename T> T angle(const quat<T> & q);

template <typename T> vec3<T> axis(const quat<T> & q);
template <typename T> vec3<T> axis_n(const quat<T> & q);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORMATIONS -----------------------------------------------------------------------------------------------------



//template <typename T>
//quat<T> pow(const quat<T> & q, T t);

template <typename T> quat<T> rotateQ(const vec3<T> & axis, const T & theta);
template <typename T> quat<T> rotateQ_n(const vec3<T> & axis, const T & theta);

template <typename T> quat<T> alignQ(const vec3<T> & v1, const vec3<T> & v2);
template <typename T> quat<T> alignQ_n(const vec3<T> & v1, const vec3<T> & v2);

//expects orthogonal fvectors
template <typename T> quat<T> alignQ(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2);
template <typename T> quat<T> alignQ_n(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2);

//theta: thumb points up, phi: right, psi: forward
template <typename T> quat<T> eulerQ(const vec3<T> & forward, const vec3<T> & up, const T & theta, const T & phi, const T & psi);
template <typename T> quat<T> eulerQ_n(const vec3<T> & forward, const vec3<T> & up, const T & theta, const T & phi, const T & psi);

template <typename T> mat3<T> toMat(const quat<T> & q);

//t is a "time" value between 0 and 1
template <typename T> quat<T> nlerp(const quat<T> & q1, const quat<T> & q2, const T & t);

template <typename T> quat<T> slerp(const quat<T> & q1, const quat<T> & q2, const T & t);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUAT IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors
    


template <typename T>
constexpr quat<T>::quat() :
    x(0), y(0), z(0), w(1)
{}

template <typename T>
constexpr quat<T>::quat(const quat<T> & q) :
    x(q.x), y(q.y), z(q.z), w(q.w)
{}

template <typename T>
constexpr quat<T>::quat(quat<T> && q) :
    x(q.x), y(q.y), z(q.z), w(q.w)
{}

template <typename T> template <typename U>
constexpr quat<T>::quat(const quat<U> & q) :
    x(static_cast<T>(q.x)), y(static_cast<T>(q.y)), z(static_cast<T>(q.z)), w(static_cast<T>(q.w))
{}

template <typename T>
constexpr quat<T>::quat(const vec3<T> & v, const T & w) :
    x(v.x), y(v.y), z(v.z), w(w)
{}

template <typename T>
constexpr quat<T>::quat(const T & x, const T & y, const T & z, const T & w) :
    x(x), y(y), z(z), w(w)
{}

template <typename T>
constexpr quat<T>::quat(const vec3<T> & v) :
    x(v.x), y(v.y), z(v.z), w(0)
{}

template <typename T>
constexpr quat<T>::quat(const vec4<T> & v) :
    x(v.x), y(v.y), z(v.z), w(v.w)
{}



//------------------------------------------------------------------------------
// Assignment Operators



template <typename T>
inline quat<T> & quat<T>::operator=(const quat<T> & q) {
    x = q.x; y = q.y; z = q.z; w = q.w;
    return *this;
}

template <typename T>
inline quat<T> & quat<T>::operator=(quat<T> && q) {
    x = q.x; y = q.y; z = q.z; w = q.w;
    return *this;
}



//------------------------------------------------------------------------------
// Access Operators



template <typename T>
inline T quat<T>::operator[](nat i) {
    return *(&x + i);
}



//------------------------------------------------------------------------------
// Arithmetic Assignment Operators



template <typename T>
inline quat<T> & operator+=(quat<T> & q1, const quat<T> & q2) {
    return q1 = q1 + q2;
}

template <typename T>
inline quat<T> & operator-=(quat<T> & q1, const quat<T> & q2) {
    return q1 = q1 - q2;
}

template <typename T>
inline quat<T> & operator*=(quat<T> & q1, const quat<T> & q2) {
    return q1 = q1 * q2;
}

template <typename T>
inline quat<T> & operator*=(quat<T> & q, const T & v) {
    return q = q * v;
}

template <typename T>
inline quat<T> & operator/=(quat<T> & q1, const quat<T> & q2) {
    return q1 = q1 / q2;
}



//------------------------------------------------------------------------------
// Arithmetic Operators



template <typename T>
inline quat<T> operator+(const quat<T> & q) {
    return quat<T>(+q.x, +q.y, +q.z, +q.w);
}

template <typename T>
inline quat<T> operator-(const quat<T> & q) {
    return quat<T>(-q.x, -q.y, -q.z, -q.w);
}

template <typename T>
inline quat<T> operator+(const quat<T> & q1, const quat<T> & q2) {
    return quat<T>(q1.x + q2.x, q1.y + q2.y, q1.z + q2.z, q1.w + q2.w);
}

template <typename T>
inline quat<T> operator-(const quat<T> & q1, const quat<T> & q2) {
    return quat<T>(q1.x - q2.x, q1.y - q2.y, q1.z - q2.z, q1.w - q2.w);
}

template <typename T>
inline quat<T> operator*(const quat<T> & q1, const quat<T> & q2) {
    return quat<T>(
        q1.w * q2.v + q2.w * q1.v + cross(q1.v, q2.v),
        q1.w * q2.w - dot(q1.v, q2.v)
    );
}

template <typename T>
inline quat<T> operator*(const quat<T> & q, const T & v) {
    return quat<T>(q.x * v, q.y * v, q.z * v, q.w * v);
}

template <typename T>
inline quat<T> operator*(const T & v, const quat<T> & q) {
    return quat<T>(v * q.x, v * q.y, v * q.z, v * q.w);
}

template <typename T>
inline vec3<T> operator*(const quat<T> & q, const vec3<T> & v) {
    vec3<T> t(static_cast<T>(2) * cross(q.v, v));
    return v + q.w * t + cross(q.v, t);
}

template <typename T>
inline quat<T> operator/(const quat<T> & q1, const quat<T> & q2) {
    return quat<T>(q1.v * q2.w - q2.v * q1.w - cross(q1.v, q2.v), dot(q1.v4, q2.v4));
}



//------------------------------------------------------------------------------
// Comparison Operators



template <typename T>
inline bool operator==(const quat<T> & q1, const quat<T> & q2) {
    return q1.x == q2.x && q1.y == q2.y && q1.z == q2.z && q1.w == q2.w;
}

template <typename T>
inline bool operator!=(const quat<T> & q1, const quat<T> & q2) {
    return q1.x != q2.x || q1.y != q2.y || q1.z != q2.z || q1.w != q2.w;
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string quat<T>::toString() const {
    return v4.toString();
}

template <typename T>
inline std::ostream & operator<<(std::ostream & os, const quat<T> & q) {
    return os << q.v4.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUAT FUNCTIONS IMPLEMENTATION ---------------------------------------------------------------------------------------



template <typename T>
inline T magnitude(const quat<T> & q) {
    return sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

template <typename T>
inline quat<T> normalize(const quat<T> & q) {
    T m(magnitude(q));
    if (std::abs(m - 1) < std::numeric_limits<T>::min()) return q;
    if (std::abs(m) < std::numeric_limits<T>::min()) return quat<T>(0, 0, 0, 1);
    m = 1 / m;
    return quat<T>(q.v * m, q.w * m);
}

template <typename T>
inline quat<T> inverse(const quat<T> & q) {
    return quat<T>(-q.v, q.w);
}

template <typename T>
inline T angle(const quat<T> & q) {
    return std::acos(q.w) * 2;
}

template <typename T>
inline vec3<T> axis(const quat<T> & q) {
    return axis_n(normalize(q));
}
template <typename T>
inline vec3<T> axis_n(const quat<T> & q) {
    if (q.w >= 1) return vec3<T>();
    return q.v * (1 / std::sqrt(1 - q.w * q.w));
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORMATIONS IMPLEMENTATION --------------------------------------------------------------------------------------



/*inline quat<T> pow(const quat<T> & q, const T & t) {
    return angleAxis(angle(q) * t, axis(q));
}*/

template <typename T>
inline quat<T> rotateQ(const vec3<T> & axis, const T & theta) {
    return rotateQ_n(normalize(axis), theta);
}
template <typename T>
inline quat<T> rotateQ_n(const vec3<T> & axis, const T & theta) {
    return quat<T>(
        std::sin(theta / 2) * axis,
        std::cos(theta / 2)
    );
}

template <typename T>
inline quat<T> alignQ(const vec3<T> & v1, const vec3<T> & v2) {
    return alignQ_n(normalize(v1), normalize(v2));
}
template <typename T>
inline quat<T> alignQ_n(const vec3<T> & v1, const vec3<T> & v2) {
    return rotateQ(cross(v1, v2), std::acos(dot(v1, v2)));
}

template <typename T>
inline quat<T> alignQ(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2) {
    return alignQ_n(normalize(forward1), normalize(up1), normalize(forward2), normalize(up2));
}
template <typename T>
inline quat<T> alignQ_n(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2) {
    quat<T> q(alignQ_n(forward1, forward2));
    return alignQ_n(q * up1, up2) * q;
}

template <typename T>
inline quat<T> eulerQ(const vec3<T> & forward, const vec3<T> & up, const T & theta, const T & phi, const T & psi) {
    return eulerQ_n(normalize(forward), normalize(up), theta, phi, psi);
}
template <typename T>
inline quat<T> eulerQ_n(const vec3<T> & forward, const vec3<T> & up, const T & theta, const T & phi, const T & psi) {
    return rotateQ_n(up, theta) * rotateQ_n(cross(forward, up), phi) * rotateQ_n(forward, psi);
}

template <typename T>
inline mat3<T> toMat(const quat<T> & q) {
    const T & wx(q.w * q.x);
    const T & wy(q.w * q.y);
    const T & wz(q.w * q.z);
    const T & xx(q.x * q.x);
    const T & xy(q.x * q.y);
    const T & xz(q.x * q.z);
    const T & yy(q.y * q.y);
    const T & yz(q.y * q.z);
    const T & zz(q.z * q.z);

    return mat3<T>(
        1 - 2 * (yy + zz), 2 * (xy + wz), 2 * (xz - wy),
        2 * (xy - wz), 1 - 2 * (xx + zz), 2 * (yz + wx),
        2 * (xz + wy), 2 * (yz - wx), 1 - 2 * (xx + yy)
    );
}

template <typename T>
inline quat<T> nlerp(const quat<T> & q1, const quat<T> & q2, const T & p) {
    return normalize(quat<T>(lerp(q1.v4, q2.v4, p)));
}

template <typename T>
inline quat<T> slerp(const quat<T> & q1, const quat<T> & q2_, const T & p) {
    quat<T> q2(q2_);

    T cosHalfTheta(dot(q1.v4, q2.v4));

    //make sure to take the shorter route
    if (cosHalfTheta < 0) {
        cosHalfTheta = -cosHalfTheta;
        q2 = -q2;
    }
    //if parallel, no interpolation necessary
    if (std::abs(std::abs(cosHalfTheta) - 1) < std::numeric_limits<T>::min()) {
        return q1;
    }

    T halfTheta(std::acos(cosHalfTheta));
    T sinHalfTheta(std::sqrt(1 - cosHalfTheta * cosHalfTheta));

    return (q1 * std::sin((1 - p) * halfTheta) + q2 * std::sin(p * halfTheta)) * (1 / sinHalfTheta);
}



}