#pragma once



#include "QMatrix.hpp"



namespace qmu {



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUAT ----------------------------------------------------------------------------------------------------------------

struct quat {

	union {
		struct {
			float x, y, z, w;
		};
		struct {
			fvec3 v;
			float w;
		};
		fvec4 v4;
	};

	//--- constructors ---

	constexpr quat();
	constexpr quat(const quat & o);
	constexpr quat(quat && o);

	constexpr quat(const fvec3 & v, float w);
	constexpr quat(float x, float y, float z, float w);
	constexpr explicit quat(const fvec3 & v);
	constexpr explicit quat(const fvec4 & v);

	//--- destructor ---

	~quat() {
		static_assert(std::is_standard_layout<quat>::value, "quat must be of standard layout");
		static_assert(sizeof(quat) == 4 * sizeof(float), "quat must be equal in size to 4 floats");
	}

	//--- assignment operators ---

	quat & operator=(const quat & o);
	quat & operator=(quat && o);

	//--- access operators ---

	float operator[](nat i);

	//--- arithmetic assignment operators ---

	friend quat & operator+=(quat & q1, const quat & q2);

	friend quat & operator-=(quat & q1, const quat & q2);

	friend quat & operator*=(quat & q1, const quat & q2);

	friend quat & operator/=(quat & q1, const quat & q2);

	//--- arithmetic operators ---

	friend quat operator+(const quat & q);

	friend quat operator-(const quat & q);

	friend quat operator+(const quat & q1, const quat & q2);

	friend quat operator-(const quat & q1, const quat & q2);

	friend quat operator*(const quat & q1, const quat & q2);
	friend quat operator*(const quat & q, float v);
	friend quat operator*(float v, const quat & q);
	friend fvec3 operator*(const quat & q, const fvec3 & v);

	friend quat operator/(const quat & q1, const quat & q2);

	//--- comparison operators ---

	friend bool operator==(const quat & q1, const quat & q2);

	friend bool operator!=(const quat & q1, const quat & q2);

	//--- other ---

	std::string toString() const;
	friend std::ostream & operator<<(std::ostream & os, const quat & q);

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUAT FUNCTIONS ------------------------------------------------------------------------------------------------------



float mag(const quat & q);

quat norm(const quat & q);

quat inv(const quat & q);

float angle(const quat & q);

fvec3 axis(const quat & q);
fvec3 axis_n(const quat & q);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORMATIONS -----------------------------------------------------------------------------------------------------



/*quat pow(const quat & q, float t);*/

quat rotateQ(float theta, const fvec3 & axis);
quat rotateQ_n(float theta, const fvec3 & axis);

quat alignQ(const fvec3 & v1, const fvec3 & v2);
quat alignQ_n(const fvec3 & v1, const fvec3 & v2);

//expects orthogonal fvectors
quat alignQ(const fvec3 & forward1, const fvec3 & up1, const fvec3 & forward2, const fvec3 & up2);
quat alignQ_n(const fvec3 & forward1, const fvec3 & up1, const fvec3 & forward2, const fvec3 & up2);

//theta: thumb points up, phi: right, psi: forward
quat eulerQ(const fvec3 & forward, const fvec3 & up, float theta, float phi, float psi);
quat eulerQ_n(const fvec3 & forward, const fvec3 & up, float theta, float phi, float psi);

mat3 toMat(const quat & q);

//t is a "time" value between 0 and 1
quat nlerp(const quat & q1, const quat & q2, float t);

quat slerp(const quat & q1, const quat & q2__, float t);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUAT IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors
	


constexpr quat::quat() :
	x(0), y(0), z(0), w(1)
{}

constexpr quat::quat(const quat & o) :
	x(o.x), y(o.y), z(o.z), w(o.w)
{}

constexpr quat::quat(quat && o) :
	x(o.x), y(o.y), z(o.z), w(o.w)
{}

constexpr quat::quat(const fvec3 & v, float w) :
	x(v.x), y(v.y), z(v.z), w(w)
{}

constexpr quat::quat(float x, float y, float z, float w) :
	x(x), y(y), z(z), w(w)
{}

constexpr quat::quat(const fvec3 & v) :
	x(v.x), y(v.y), z(v.z), w(0)
{}

constexpr quat::quat(const fvec4 & v) :
	x(v.x), y(v.y), z(v.z), w(v.w)
{}



//------------------------------------------------------------------------------
// Assignment Operators



inline quat & quat::operator=(const quat & o) {
	x = o.x; y = o.y; z = o.z; w = o.w;
	return *this;
}

inline quat & quat::operator=(quat && o) {
	x = o.x; y = o.y; z = o.z; w = o.w;
	return *this;
}



//------------------------------------------------------------------------------
// Access Operators



inline float quat::operator[](nat i) {
	return *(&x + i);
}



//------------------------------------------------------------------------------
// Arithmetic Assignment Operators



inline quat & operator+=(quat & q1, const quat & q2) {
	return q1 = q1 + q2;
}

inline quat & operator-=(quat & q1, const quat & q2) {
	return q1 = q1 - q2;
}

inline quat & operator*=(quat & q1, const quat & q2) {
	return q1 = q1 * q2;
}

inline quat & operator/=(quat & q1, const quat & q2) {
	return q1 = q1 / q2;
}



//------------------------------------------------------------------------------
// Arithmetic Operators



inline quat operator+(const quat & q) {
	return quat(+q.x, +q.y, +q.z, +q.w);
}

inline quat operator-(const quat & q) {
	return quat(-q.x, -q.y, -q.z, -q.w);
}

inline quat operator+(const quat & q1, const quat & q2) {
	return quat(q1.x + q2.x, q1.y + q2.y, q1.z + q2.z, q1.w + q2.w);
}

inline quat operator-(const quat & q1, const quat & q2) {
	return quat(q1.x - q2.x, q1.y - q2.y, q1.z - q2.z, q1.w - q2.w);
}

inline quat operator*(const quat & q1, const quat & q2) {
	return quat(
		q1.w * q2.v + q2.w * q1.v + cross(q1.v, q2.v),
		q1.w * q2.w - dot(q1.v, q2.v)
	);
}

inline quat operator*(const quat & q, float v) {
	return quat(q.x * v, q.y * v, q.z * v, q.w * v);
}

inline quat operator*(float v, const quat & q) {
	return quat(v * q.x, v * q.y, v * q.z, v * q.w);
}

inline fvec3 operator*(const quat & q, const fvec3 & v) {
	fvec3 t = 2.0f * cross(q.v, v);
	return v + q.w * t + cross(q.v, t);
}

inline quat operator/(const quat & q1, const quat & q2) {
	return quat(q1.v * q2.w - q2.v * q1.w - cross(q1.v, q2.v), dot(q1.v4, q2.v4));
}



//------------------------------------------------------------------------------
// Comparison Operators



inline bool operator==(const quat & q1, const quat & q2) {
	return q1.x == q2.x && q1.y == q2.y && q1.z == q2.z && q1.w == q2.w;
}

inline bool operator!=(const quat & q1, const quat & q2) {
	return q1.x != q2.x || q1.y != q2.y || q1.z != q2.z || q1.w != q2.w;
}



//------------------------------------------------------------------------------
// Other



inline std::string quat::toString() const {
	return v4.toString();
}

inline std::ostream & operator<<(std::ostream & os, const quat & q) {
	return os << q.v4.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUAT FUNCTIONS IMPLEMENTATION ---------------------------------------------------------------------------------------



inline float mag(const quat & q) {
	return sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

inline quat norm(const quat & q) {
	float m = mag(q);
	if (abs(m - 1.0f) < std::numeric_limits<float>::min()) return q;
	if (abs(m) < std::numeric_limits<float>::min()) return quat(0, 0, 0, 1);
	m = 1.0f / m;
	return quat(q.v * m, q.w * m);
}

inline quat inv(const quat & q) {
	return quat(-q.v, q.w);
}

inline float angle(const quat & q) {
	return acos(q.w) * 2.0f;
}

inline fvec3 axis(const quat & q) {
	return axis_n(norm(q));
}
inline fvec3 axis_n(const quat & q) {
	if (q.w >= 1.0f) return fvec3();
	return q.v * (1.0f / sqrt(1.0f - q.w * q.w));
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORMATIONS IMPLEMENTATION --------------------------------------------------------------------------------------



/*inline quat pow(const quat & q, float t) {
	return angleAxis(angle(q) * t, axis(q));
}*/

inline quat rotateQ(float theta, const fvec3 & axis) {
	return rotateQ_n(theta, norm(axis));
}
inline quat rotateQ_n(float theta, const fvec3 & axis) {
	return quat(
		sin(theta / 2.0f) * axis,
		cos(theta / 2.0f)
	);
}

inline quat alignQ(const fvec3 & v1, const fvec3 & v2) {
	return alignQ_n(norm(v1), norm(v2));
}
inline quat alignQ_n(const fvec3 & v1, const fvec3 & v2) {
	return rotateQ(acos(dot(v1, v2)), cross(v1, v2));
}

inline quat alignQ(const fvec3 & forward1, const fvec3 & up1, const fvec3 & forward2, const fvec3 & up2) {
	return alignQ_n(norm(forward1), norm(up1), norm(forward2), norm(up2));
}
inline quat alignQ_n(const fvec3 & forward1, const fvec3 & up1, const fvec3 & forward2, const fvec3 & up2) {
	quat q = alignQ_n(forward1, forward2);
	return alignQ_n(q * up1, up2) * q;
}

inline quat eulerQ(const fvec3 & forward, const fvec3 & up, float theta, float phi, float psi) {
	return eulerQ_n(norm(forward), norm(up), theta, phi, psi);
}
inline quat eulerQ_n(const fvec3 & forward, const fvec3 & up, float theta, float phi, float psi) {
	return rotateQ_n(theta, up) * rotateQ_n(phi, cross(forward, up)) * rotateQ_n(psi, forward);
}

inline mat3 toMat(const quat & q) {
	float wx = q.w * q.x;
	float wy = q.w * q.y;
	float wz = q.w * q.z;
	float xx = q.x * q.x;
	float xy = q.x * q.y;
	float xz = q.x * q.z;
	float yy = q.y * q.y;
	float yz = q.y * q.z;
	float zz = q.z * q.z;

	return mat3(
		1.0f - 2.0f * (yy + zz), 2.0f * (xy + wz), 2.0f * (xz - wy),
		2.0f * (xy - wz), 1.0f - 2.0f * (xx + zz), 2.0f * (yz + wx),
		2.0f * (xz + wy), 2.0f * (yz - wx), 1.0f - 2.0f * (xx + yy)
	);
}

inline quat nlerp(const quat & q1, const quat & q2, float t) {
	return norm(quat(lerp(q1.v4, q2.v4, t)));
}

inline quat slerp(const quat & q1, const quat & q2__, float t) {
	quat q2 = q2__;

	float cosHalfTheta = dot(q1.v4, q2.v4);

	//make sure to take the shorter route
	if (cosHalfTheta < 0) {
		cosHalfTheta = -cosHalfTheta;
		q2 = -q2;
	}
	//if parallel, no interpolation necessary
	if (abs(abs(cosHalfTheta) - 1) < std::numeric_limits<float>::min()) {
		return q1;
	}

	float halfTheta = acos(cosHalfTheta);
	float sinHalfTheta = sqrt(1.0f - cosHalfTheta * cosHalfTheta);

	return (q1 * sin((1.0f - t) * halfTheta) + q2 * sin(t * halfTheta)) * (1.0f / sinHalfTheta);
}



}