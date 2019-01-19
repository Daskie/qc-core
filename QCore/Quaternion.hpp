#pragma once



#include "Matrix.hpp"



namespace qc {



template <typename T> struct quat;

namespace types {

    using qc::quat;

    using fquat = quat< float>;
    using dquat = quat<double>;

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUAT ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct quat {

    static_assert(std::is_floating_point_v<T>, "quat<T> must have floating point T");

    using type = T;

    vec3<T> a;
    T w;

    //--- constructors ---

    constexpr quat() noexcept;
    constexpr quat(const quat & q) noexcept;
    constexpr quat(quat && q) noexcept;

    template <typename U> constexpr explicit quat(const quat<U> & q) noexcept;

    constexpr quat(const vec3<T> & a, T w) noexcept;
    constexpr explicit quat(const vec3<T> & v) noexcept;
    constexpr explicit quat(const vec4<T> & v) noexcept;

    //--- assignment ---

    quat & operator=(const quat & q) noexcept;
    quat & operator=(quat && q) noexcept;

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



}



#include "Quaternion.tpp"