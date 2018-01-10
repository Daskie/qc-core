#pragma once



#include "Matrix.hpp"



namespace qcu {



template <typename T> struct quat;

using  fquat = quat<      float>;
using  dquat = quat<     double>;
using ldquat = quat<long double>;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUAT ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct quat {

    static_assert(std::is_floating_point_v<T>, "quat<T> must have floating point T");

    vec3<T> a;
    T w;

    //--- constructors ---

    constexpr quat();
    constexpr quat(const quat & q);
    constexpr quat(quat && q);

    template <typename U> constexpr explicit quat(const quat<U> & q);

    constexpr quat(const vec3<T> & a, T w);
    constexpr explicit quat(const vec3<T> & v);
    constexpr explicit quat(const vec4<T> & v);

    //--- assignment ---

    inline quat & operator=(const quat & q);
    inline quat & operator=(quat && q);

    //--- other ---

    inline std::string toString() const;

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUAT FUNCTIONS ------------------------------------------------------------------------------------------------------



//--- arithmetic assignment ---

template <typename T> quat<T> & operator+=(quat<T> & q1, const quat<T> & q2);

template <typename T> quat<T> & operator-=(quat<T> & q1, const quat<T> & q2);

template <typename T> quat<T> & operator*=(quat<T> & q1, const quat<T> & q2);
template <typename T> quat<T> & operator*=(quat<T> &  q, T v);

template <typename T> quat<T> & operator/=(quat<T> & q1, const quat<T> & q2);

//--- arithmetic operators ---

template <typename T> quat<T> operator+(const quat<T> & q);

template <typename T> quat<T> operator-(const quat<T> & q);

template <typename T> quat<T> operator+(const quat<T> & q1, const quat<T> & q2);

template <typename T> quat<T> operator-(const quat<T> & q1, const quat<T> & q2);

template <typename T> quat<T> operator*(const quat<T> & q1, const quat<T> & q2);
template <typename T> quat<T> operator*(const quat<T> &  q, T v);
template <typename T> quat<T> operator*(const T v, const quat<T> &  q);
template <typename T> vec3<T> operator*(const quat<T> &  q, const vec3<T> &  v);

template <typename T> quat<T> operator/(const quat<T> & q1, const quat<T> & q2);

//--- comparison operators ---

template <typename T> bool operator==(const quat<T> & q1, const quat<T> & q2);

template <typename T> bool operator!=(const quat<T> & q1, const quat<T> & q2);

//--- other ---

template <typename T> std::ostream & operator<<(std::ostream & os, const quat<T> & q);

//--- uncategorized ---

template <typename T> T dot(const quat<T> & q1, const quat<T> & q2);

template <typename T> T magnitude(const quat<T> & q);

template <typename T> T magnitude2(const quat<T> & q);

template <typename T> quat<T> norm(const quat<T> & q);

template <typename T> quat<T> inverse(const quat<T> & q);

template <typename T> T quatAngle(const quat<T> & q);

template <typename T> vec3<T> quatAxis(const quat<T> & q);
template <typename T> vec3<T> quatAxis_n(const quat<T> & q);

template <typename T> quat<T> mix(const quat<T> & q1, const quat<T> & q2, T t);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORMATIONS -----------------------------------------------------------------------------------------------------



//template <typename T>
//quat<T> pow(const quat<T> & q, T t);

template <typename T> quat<T> rotateQ(const vec3<T> & axis, T angle);
template <typename T> quat<T> rotateQ_n(const vec3<T> & axis, T angle);

template <typename T> quat<T> alignQ(const vec3<T> & v1, const vec3<T> & v2);
template <typename T> quat<T> alignQ_n(const vec3<T> & v1, const vec3<T> & v2);

//expects orthogonal fvectors
template <typename T> quat<T> alignQ(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2);
template <typename T> quat<T> alignQ_n(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2);

//theta: thumb points up, phi: right, psi: forward
template <typename T> quat<T> eulerQ(const vec3<T> & forward, const vec3<T> & up, T theta, T phi, T psi);
template <typename T> quat<T> eulerQ_n(const vec3<T> & forward, const vec3<T> & up, T theta, T phi, T psi);

template <typename T> constexpr mat3<T> toMat(const quat<T> & q);

//t is a "time" value between 0 and 1
template <typename T> quat<T> nlerp(const quat<T> & q1, const quat<T> & q2, T t);

template <typename T> quat<T> slerp(const quat<T> & q1, const quat<T> & q2, T t);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUAT IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors
    


template <typename T>
constexpr quat<T>::quat() :
    a(T(0.0)), w(T(1.0))
{}

template <typename T>
constexpr quat<T>::quat(const quat<T> & q) :
    a(q.a), w(q.w)
{}

template <typename T>
constexpr quat<T>::quat(quat<T> && q) :
    a(q.a), w(q.w)
{}

template <typename T> template <typename U>
constexpr quat<T>::quat(const quat<U> & q) :
    a(q.a), w(T(q.w))
{}

template <typename T>
constexpr quat<T>::quat(const vec3<T> & a, T w) :
    a(a), w(w)
{}

template <typename T>
constexpr quat<T>::quat(const vec3<T> & v) :
    a(v), w(T(0.0))
{}

template <typename T>
constexpr quat<T>::quat(const vec4<T> & v) :
    a(v.x, v.y, v.z), w(v.w)
{}



//------------------------------------------------------------------------------
// Assignment



template <typename T>
inline quat<T> & quat<T>::operator=(const quat<T> & q) {
    a = q.a; w = q.w;
    return *this;
}

template <typename T>
inline quat<T> & quat<T>::operator=(quat<T> && q) {
    a = q.a; w = q.w;
    return *this;
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string quat<T>::toString() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUAT FUNCTIONS IMPLEMENTATION ---------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Arithmetic Assignment



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
inline quat<T> & operator*=(quat<T> & q, T v) {
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
    return quat<T>(+q.a, +q.w);
}

template <typename T>
inline quat<T> operator-(const quat<T> & q) {
    return quat<T>(-q.a, -q.w);
}

template <typename T>
inline quat<T> operator+(const quat<T> & q1, const quat<T> & q2) {
    return quat<T>(q1.a + q2.a, q1.w + q2.w);
}

template <typename T>
inline quat<T> operator-(const quat<T> & q1, const quat<T> & q2) {
    return quat<T>(q1.a - q2.a, q1.w - q2.w);
}

template <typename T>
inline quat<T> operator*(const quat<T> & q1, const quat<T> & q2) {
    return quat<T>(
        q1.w * q2.a + q2.w * q1.a + cross(q1.a, q2.a),
        q1.w * q2.w - dot(q1.a, q2.a)
    );
}

template <typename T>
inline quat<T> operator*(const quat<T> & q, T v) {
    return quat<T>(q.a * v, q.w * v);
}

template <typename T>
inline quat<T> operator*(T v, const quat<T> & q) {
    return quat<T>(v * q.a, v * q.w);
}

template <typename T>
inline vec3<T> operator*(const quat<T> & q, const vec3<T> & v) {
    vec3<T> t(T(2.0) * cross(q.a, v));
    return v + q.w * t + cross(q.a, t);
}

template <typename T>
inline quat<T> operator/(const quat<T> & q1, const quat<T> & q2) {
    return quat<T>(q1.a * q2.w - q2.a * q1.w - cross(q1.a, q2.a), dot(q1, q2));
}



//------------------------------------------------------------------------------
// Comparison Operators



template <typename T>
inline bool operator==(const quat<T> & q1, const quat<T> & q2) {
    return q1.a == q2.a && q1.w == q2.w;
}

template <typename T>
inline bool operator!=(const quat<T> & q1, const quat<T> & q2) {
    return q1.a != q2.a || q1.w != q2.w;
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const quat<T> & q) {
    return os << "[ " << q.a.x << " " << q.a.y << " " << q.a.z << " | " << q.w << " ]";
}



//------------------------------------------------------------------------------
// Uncategorized



template <typename T>
inline T dot(const quat<T> & q1, const quat<T> & q2) {
    return dot(q1.a, q2.a) + q1.w * q2.w;
}

template <typename T>
inline T magnitude(const quat<T> & q) {
    return std::sqrt(magnitude2(q));
}

template <typename T>
inline T magnitude2(const quat<T> & q) {
    return magnitude2(q.a) + q.w * q.w;
}

template <typename T>
inline quat<T> norm(const quat<T> & q) {
    T m2(magnitude2(q));
    if (zero(m2)) {
        return quat<T>();
    }
    T m_inv(T(1.0) / std::sqrt(m2));
    return quat<T>(q.a * m_inv, q.w * m_inv);
}

template <typename T>
inline quat<T> inverse(const quat<T> & q) {
    return quat<T>(-q.a, q.w);
}

template <typename T>
inline T quatAngle(const quat<T> & q) {
    return std::acos(q.w) * T(2.0);
}

template <typename T>
inline vec3<T> quatAxis(const quat<T> & q) {
    return quatAxis_n(norm(q));
}

template <typename T>
inline vec3<T> quatAxis_n(const quat<T> & q) {
    T d2(T(1.0) - q.w * q.w);
    if (zero(d2)) {
        return vec3<T>();
    }
    return q.a * (T(1.0) / std::sqrt(d2));
}

template <typename T>
inline quat<T> mix(const quat<T> & q1, const quat<T> & q2, T t) {
    T s(T(1.0) - t);
    return quat<T>(s * q1.a + t * q2.a, s * q1.w + t * q2.w);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORMATIONS IMPLEMENTATION --------------------------------------------------------------------------------------



/*inline quat<T> pow(const quat<T> & q, T t) {
    return angleAxis(angle(q) * t, axis(q));
}*/

template <typename T>
inline quat<T> rotateQ(const vec3<T> & axis, T angle) {
    return rotateQ_n(norm(axis), angle);
}
template <typename T>
inline quat<T> rotateQ_n(const vec3<T> & axis, T angle) {
    return quat<T>(
        std::sin(angle * T(0.5)) * axis,
        std::cos(angle * T(0.5))
    );
}

template <typename T>
inline quat<T> alignQ(const vec3<T> & v1, const vec3<T> & v2) {
    return alignQ_n(norm(v1), norm(v2));
}
template <typename T>
inline quat<T> alignQ_n(const vec3<T> & v1, const vec3<T> & v2) {
    return rotateQ(cross(v1, v2), std::acos(dot(v1, v2)));
}

template <typename T>
inline quat<T> alignQ(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2) {
    return alignQ_n(norm(forward1), norm(up1), norm(forward2), norm(up2));
}
template <typename T>
inline quat<T> alignQ_n(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2) {
    quat<T> q(alignQ_n(forward1, forward2));
    return alignQ_n(q * up1, up2) * q;
}

template <typename T>
inline quat<T> eulerQ(const vec3<T> & forward, const vec3<T> & up, T theta, T phi, T psi) {
    return eulerQ_n(norm(forward), norm(up), theta, phi, psi);
}
template <typename T>
inline quat<T> eulerQ_n(const vec3<T> & forward, const vec3<T> & up, T theta, T phi, T psi) {
    return rotateQ_n(up, theta) * rotateQ_n(cross(forward, up), phi) * rotateQ_n(forward, psi);
}

template <typename T>
constexpr mat3<T> toMat(const quat<T> & q) {
    T wx(q.w   * q.a.x);
    T wy(q.w   * q.a.y);
    T wz(q.w   * q.a.z);
    T xx(q.a.x * q.a.x);
    T xy(q.a.x * q.a.y);
    T xz(q.a.x * q.a.z);
    T yy(q.a.y * q.a.y);
    T yz(q.a.y * q.a.z);
    T zz(q.a.z * q.a.z);

    constexpr T t_1(1.0), t_2(2.0);

    return mat3<T>(
        t_1 - t_2 * (yy + zz), t_2       * (xy + wz), t_2       * (xz - wy),
        t_2       * (xy - wz), t_1 - t_2 * (xx + zz), t_2       * (yz + wx),
        t_2       * (xz + wy), t_2       * (yz - wx), t_1 - t_2 * (xx + yy)
    );
}

template <typename T>
inline quat<T> nlerp(const quat<T> & q1, const quat<T> & q2, T t) {
    return norm(quat<T>(mix(q1, q2, t)));
}

template <typename T>
inline quat<T> slerp(const quat<T> & q1, const quat<T> & q2_, T t) {
    quat<T> q2(q2_);

    T cosHalfTheta(dot(q1, q2));

    //make sure to take the shorter route
    if (cosHalfTheta < T(0.0)) {
        cosHalfTheta = -cosHalfTheta;
        q2 = -q2;
    }
    //if parallel, no interpolation necessary
    if (equal(cosHalfTheta, T(1.0))) {
        return q1;
    }

    T halfTheta(std::acos(cosHalfTheta));
    T sinHalfTheta(std::sqrt(T(1.0) - cosHalfTheta * cosHalfTheta));

    return (q1 * std::sin((T(1.0) - t) * halfTheta) + q2 * std::sin(t * halfTheta)) * (T(1.0) / sinHalfTheta);
}



}