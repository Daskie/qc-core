#pragma once



#include "Quaternion.hpp"
#include "MatrixFunc.hpp"



namespace qc {



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

template <typename T> Q_CX_ABLE mat3<T> toMat(const quat<T> & q);

//t is a "time" value between 0 and 1
template <typename T> quat<T> nlerp(const quat<T> & q1, const quat<T> & q2, T t);

template <typename T> quat<T> slerp(const quat<T> & q1, const quat<T> & q2, T t);



}



#include "QuaternionFunc.tpp"