#pragma once



#include "QMatrix.hpp"



namespace qmu {



template <typename T> struct quat;



using  fquat = quat< float>;
using  dquat = quat<double>;
using fnquat = quat<  fnat>;



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
	constexpr quat(const quat & o);
	constexpr quat(quat && o);

	constexpr quat(const vec3<T> & v, const T & w);
	constexpr quat(const T & x, const T & y, const T & z, const T & w);
	constexpr explicit quat(const vec3<T> & v);
	constexpr explicit quat(const vec4<T> & v);

	//--- destructor ---

	~quat() {
		static_assert(std::is_standard_layout<quat>::value, "quat<T> must be of standard layout");
		static_assert(sizeof(quat) == 4 * sizeof(T), "quat<T> must be equal in size to 4 Ts");
		static_assert(std::is_default_constructible<T>::value, "quat<T> must be default constructible");
		static_assert(std::is_copy_constructible<T>::value, "quat<T> must be copy constructable");
		static_assert(std::is_copy_assignable<T>::value, "quat<T> must be copy assignable");
	}

	//--- assignment operators ---

	quat & operator=(const quat & o);
	quat & operator=(quat && o);

	//--- access operators ---

	T operator[](nat i);

	//--- arithmetic assignment operators ---

	template <typename T> friend quat<T> & operator+=(quat<T> & q1, const quat<T> & q2);

	template <typename T> friend quat<T> & operator-=(quat<T> & q1, const quat<T> & q2);

	template <typename T> friend quat<T> & operator*=(quat<T> & q1, const quat<T> & q2);

	template <typename T> friend quat<T> & operator/=(quat<T> & q1, const quat<T> & q2);

	//--- arithmetic operators ---

	template <typename T> friend quat<T> operator+(const quat<T> & q);

	template <typename T> friend quat<T> operator-(const quat<T> & q);

	template <typename T> friend quat<T> operator+(const quat<T> & q1, const quat<T> & q2);

	template <typename T> friend quat<T> operator-(const quat<T> & q1, const quat<T> & q2);

	template <typename T> friend quat<T> operator*(const quat<T> & q1, const quat<T> & q2);
	template <typename T> friend quat<T> operator*(const quat<T> &  q, const      T  &  v);
	template <typename T> friend quat<T> operator*(const      T  &  v, const quat<T> &  q);
	template <typename T> friend vec3<T> operator*(const quat<T> &  q, const vec3<T> &  v);

	template <typename T> friend quat<T> operator/(const quat<T> & q1, const quat<T> & q2);

	//--- comparison operators ---

	template <typename T> friend bool operator==(const quat<T> & q1, const quat<T> & q2);

	template <typename T> friend bool operator!=(const quat<T> & q1, const quat<T> & q2);

	//--- other ---

	std::string toString() const;

	template <typename T> friend std::ostream & operator<<(std::ostream & os, const quat<T> & q);

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUAT FUNCTIONS ------------------------------------------------------------------------------------------------------



template <typename T> T mag(const quat<T> & q);

template <typename T> quat<T> norm(const quat<T> & q);

template <typename T> quat<T> inv(const quat<T> & q);

template <typename T> T angle(const quat<T> & q);

template <typename T> vec3<T> axis(const quat<T> & q);
template <typename T> vec3<T> axis_n(const quat<T> & q);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORMATIONS -----------------------------------------------------------------------------------------------------



//template <typename T>
//quat<T> pow(const quat<T> & q, T t);

template <typename T> quat<T> rotateQ(const T & theta, const vec3<T> & axis);
template <typename T> quat<T> rotateQ_n(const T & theta, const vec3<T> & axis);

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
constexpr quat<T>::quat(const quat<T> & o) :
	x(o.x), y(o.y), z(o.z), w(o.w)
{}

template <typename T>
constexpr quat<T>::quat(quat<T> && o) :
	x(o.x), y(o.y), z(o.z), w(o.w)
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
inline quat<T> & quat<T>::operator=(const quat<T> & o) {
	x = o.x; y = o.y; z = o.z; w = o.w;
	return *this;
}

template <typename T>
inline quat<T> & quat<T>::operator=(quat<T> && o) {
	x = o.x; y = o.y; z = o.z; w = o.w;
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
	vec3<T> t(2 * cross(q.v, v));
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
inline T mag(const quat<T> & q) {
	return sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

template <typename T>
inline quat<T> norm(const quat<T> & q) {
	T m(mag(q));
	if (std::abs(m - 1) < std::numeric_limits<T>::min()) return q;
	if (std::abs(m) < std::numeric_limits<T>::min()) return quat<T>(0, 0, 0, 1);
	m = 1 / m;
	return quat<T>(q.v * m, q.w * m);
}

template <typename T>
inline quat<T> inv(const quat<T> & q) {
	return quat<T>(-q.v, q.w);
}

template <typename T>
inline T angle(const quat<T> & q) {
	return std::acos(q.w) * 2;
}

template <typename T>
inline vec3<T> axis(const quat<T> & q) {
	return axis_n(norm(q));
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
inline quat<T> rotateQ(const T & theta, const vec3<T> & axis) {
	return rotateQ_n(theta, norm(axis));
}
template <typename T>
inline quat<T> rotateQ_n(const T & theta, const vec3<T> & axis) {
	return quat<T>(
		std::sin(theta / 2) * axis,
		std::cos(theta / 2)
	);
}

template <typename T>
inline quat<T> alignQ(const vec3<T> & v1, const vec3<T> & v2) {
	return alignQ_n(norm(v1), norm(v2));
}
template <typename T>
inline quat<T> alignQ_n(const vec3<T> & v1, const vec3<T> & v2) {
	return rotateQ(std::acos(dot(v1, v2)), cross(v1, v2));
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
inline quat<T> eulerQ(const vec3<T> & forward, const vec3<T> & up, const T & theta, const T & phi, const T & psi) {
	return eulerQ_n(norm(forward), norm(up), theta, phi, psi);
}
template <typename T>
inline quat<T> eulerQ_n(const vec3<T> & forward, const vec3<T> & up, const T & theta, const T & phi, const T & psi) {
	return rotateQ_n(theta, up) * rotateQ_n(phi, cross(forward, up)) * rotateQ_n(psi, forward);
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

	return mat3(
		1 - 2 * (yy + zz), 2 * (xy + wz), 2 * (xz - wy),
		2 * (xy - wz), 1 - 2 * (xx + zz), 2 * (yz + wx),
		2 * (xz + wy), 2 * (yz - wx), 1 - 2 * (xx + yy)
	);
}

template <typename T>
inline quat<T> nlerp(const quat<T> & q1, const quat<T> & q2, const T & t) {
	return norm(quat<T>(lerp(q1.v4, q2.v4, t)));
}

template <typename T>
inline quat<T> slerp(const quat<T> & q1, const quat<T> & q2_, const T & t) {
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

	return (q1 * std::sin((1 - t) * halfTheta) + q2 * std::sin(t * halfTheta)) * (1 / sinHalfTheta);
}



}