#pragma once



#include <cmath>

#include "Matrix.hpp"



namespace qmu {


// 9 digits to uniquely identify float, 17 digits to uniquely identify double
template <typename T> constexpr T pi() { return static_cast<T>(3.1415926535897932); }

template <typename T> constexpr T e() { return static_cast<T>(2.7182818284590452); }

template <typename T> constexpr T sqrt2() { return static_cast<T>(1.4142135623730950); }
template <typename T> constexpr T sqrt3() { return static_cast<T>(1.7320508075688773); }
template <typename T> constexpr T sqrt5() { return static_cast<T>(2.2360679774997897); }
template <typename T> constexpr T sqrt7() { return static_cast<T>(2.6457513110645906); }



template <typename T>
constexpr T radians(T degrees) {
	return degrees * pi<T>() / static_cast<T>(180.0);
}

template <typename T>
constexpr T degrees(T radians) {
	return radians * 180.0f / pi<T>();
}

//r is radius, theta is angle on xy plane, phi is angle from z axis
template <typename T, enable_if_floating_t<T> = 0>
inline vec3<T> sphericalToCartesian(const vec3<T> & v) {
	T sinTheta = std::sin(v.theta);
	T cosTheta = std::cos(v.theta);
	T sinPhi = std::sin(v.phi);
	T cosPhi = std::cos(v.phi);

	return vec3<T>(
		v.rad * sinPhi * cosTheta,
		v.rad * sinPhi * sinTheta,
		v.rad * cosPhi
	);
}

template <typename T, enable_if_floating_t<T> = 0>
inline vec3<T> sphericalToCartesian(T rad, T theta, T phi) {
	T sinTheta = std::sin(theta);
	T cosTheta = std::cos(theta);
	T sinPhi = std::sin(phi);
	T cosPhi = std::cos(phi);

	return vec3<T>(
		rad * sinPhi * cosTheta,
		rad * sinPhi * sinTheta,
		rad * cosPhi
	);
}

template <typename T, enable_if_floating_t<T> = 0>
inline vec3<T> cartesianToSpherical(const vec3<T> & v) {
	T rad(std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
	return vec3<T>(
		rad,
		std::atan2(v.y, v.x),
		std::acos(v.z / rad)
	);
}

template <typename T, enable_if_floating_t<T> = 0>
inline vec3<T> cartesianToSpherical(T x, T y, T z) {
	T rad(std::sqrt(x * x + y * y + z * z));
	return vec3<T>(
		rad,
		std::atan2(y, x),
		std::acos(z / rad)
	);
}

//a is distance from vertex A in range [0, 1] (can be outside range and outside triangle), AX, AY, and AZ define cartesian location of A
inline fvec2 barycentricToCartesian(const fvec3 & v, const fvec2 & A, const fvec2 & B, const fvec2 & C) {
	return fvec2(
		v.alpha * A.x + v.beta * B.x + v.gamma * C.x,
		v.alpha * A.y + v.beta * B.y + v.gamma * C.y
	);
}

inline fvec3 cartesianToBarycentric(const fvec2 & v, const fvec2 & A, const fvec2 & B, const fvec2 & C) {
	fmat2 mat(
		A.x - C.x, A.y - C.y,
		B.x - C.x, B.y - C.y
	);
	mat = inverse(mat);
	fvec3 bary(mat * (v - C));
	bary.gamma = 1.0f - bary.alpha - bary.beta;
	return bary;
}

//maps a point in cartesian space to the surface of a sphere and returns cartesian coordinates
//the point's x and y components, along with thetaPerUnit, determine the distance in radians from the origin
//the point's z component determines the radius
inline fvec3 mapToSphere(const fvec3 & v, float thetaPerUnit) {
	static const fmat2 perpMat = rotate(pi<float>() / 2.0f);

	fvec2 perp = perpMat * fvec2(v);
	float theta = magnitude(fvec2(v)) * thetaPerUnit;
	fmat3 rot = rotate(fvec3(perp.x, perp.y, 0.0f), theta);

	return rot * fvec3(0.0f, 0.0f, v.z);
}

//draw a line from v to A; gets the angle of this line w/ respect to the A bisector
//possible angles range from -1 (along AB side) to 1 (along AC side), w/ linear-ness
inline float baryToAngleA(const fvec3 & v) {
	return (v.gamma - v.beta) / v.alpha;
}

inline float baryToAngleB(const fvec3 & v) {
	return (v.alpha - v.gamma) / v.beta;
}

inline float baryToAngleC(const fvec3 & v) {
	return (v.beta - v.alpha) / v.gamma;
}

//given a bary angle, return point along given a corresponding to angle
inline fvec3 baryFromAngleA(float angle, float a) {
	fvec3 v;
	v.alpha = a;
	v.gamma = (angle - 1) * (a - 1);
	v.beta = 1 - v.alpha - v.gamma;
	return v;
}

inline fvec3 baryFromAngleB(float angle, float b) {
	fvec3 v;
	v.beta = b;
	v.alpha = (angle - 1) * (b - 1);
	v.gamma = 1 - v.beta - v.alpha;
	return v;
}

inline fvec3 baryFromAngleC(float angle, float c) {
	fvec3 v;
	v.gamma = c;
	v.beta = (angle - 1) * (c - 1);
	v.alpha = 1 - v.gamma - v.beta;
	return v;
}

}