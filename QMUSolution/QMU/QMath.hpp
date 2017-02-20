#pragma once



#include <cmath>

#include "QMatrix.hpp"



namespace qmu {



constexpr float PI =		3.14159265f; //9 digits to uniquely identify float
constexpr float PI_2 =		PI / 2.0f;
constexpr float E =			2.71828182f;
constexpr float SQRT2 =		1.41421356f;
constexpr float SQRT3 =		1.73205081f;
constexpr float SQRT5 =		2.23606798f;
constexpr float SQRT7 =		2.64575131f;

constexpr double PI_D =		3.1415926535897932; //17 digits to uniquely identify double
constexpr double E_D =		2.7182818284590452;
constexpr double SQRT2_D =	1.4142135623730950;
constexpr double SQRT3_D =	1.7320508075688773;
constexpr double SQRT5_D =	2.2360679774997897;
constexpr double SQRT7_D =	2.6457513110645906;



constexpr float radians(float degrees) {
	return degrees * PI / 180.0f;
}

constexpr double radians(double degrees) {
	return degrees * PI_D / 180.0;
}

constexpr float degrees(float radians) {
	return radians * 180.0f / PI;
}

constexpr double degrees(double radians) {
	return radians * 180.0 / PI_D;
}

//r is radius, theta is angle on xy plane, phi is angle from z axis
inline vec3 sphericalToCartesian(const vec3 & v) {
	float sinTheta = sin(v.theta);
	float cosTheta = cos(v.theta);
	float sinPhi = sin(v.phi);
	float cosPhi = cos(v.phi);

	return vec3(
		v.rad * sinPhi * cosTheta,
		v.rad * sinPhi * sinTheta,
		v.rad * cosPhi
	);
}

inline vec3 sphericalToCartesian(float rad, float theta, float phi) {
	float sinTheta = sin(theta);
	float cosTheta = cos(theta);
	float sinPhi = sin(phi);
	float cosPhi = cos(phi);

	return vec3(
		rad * sinPhi * cosTheta,
		rad * sinPhi * sinTheta,
		rad * cosPhi
	);
}

//r is radius, theta is angle on xy plane, phi is angle from z axis
inline vec3 cartesianToSpherical(const vec3 & v) {
	float rad = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return vec3(
		rad,
		atan2(v.y, v.x),
		acos(v.z / rad)
	);
}

//a is distance from vertex A in range [0, 1] (can be outside range and outside triangle), AX, AY, and AZ define cartesian location of A
inline vec2 barycentricToCartesian(const vec3 & v, const vec2 & A, const vec2 & B, const vec2 & C) {
	return vec2(
		v.lamA * A.x + v.lamB * B.x + v.lamC * C.x,
		v.lamA * A.y + v.lamB * B.y + v.lamC * C.y
	);
}

inline vec3 cartesianToBarycentric(const vec2 & v, const vec2 & A, const vec2 & B, const vec2 & C) {
	mat2 mat(
		A.x - C.x, A.y - C.y,
		B.x - C.x, B.y - C.y
	);
	mat = inv(mat);
	vec3 bary(mat * (v - C));
	bary.lamC = 1.0f - bary.lamA - bary.lamB;
	return bary;
}

//maps a point in cartesian space to the surface of a sphere and returns cartesian coordinates
//the point's x and y components, along with thetaPerUnit, determine the distance in radians from the origin
//the point's z component determines the radius
inline vec3 mapToSphere(const vec3 & v, float thetaPerUnit) {
	static const mat2 perpMat = rotate(PI_2);

	vec2 perp = perpMat * vec2(v);
	float theta = mag(vec2(v)) * thetaPerUnit;
	mat3 rot = rotate(theta, vec3(perp.x, perp.y, 0.0f));

	return rot * vec3(0.0f, 0.0f, v.z);
}

//draw a line from v to A; gets the angle of this line w/ respect to the A bisector
//possible angles range from -1 (along AB side) to 1 (along AC side), w/ linear-ness
inline float baryToAngleA(const vec3 & v) {
	return (v.lamC - v.lamB) / v.lamA;
}

inline float baryToAngleB(const vec3 & v) {
	return (v.lamA - v.lamC) / v.lamB;
}

inline float baryToAngleC(const vec3 & v) {
	return (v.lamB - v.lamA) / v.lamC;
}

//given a bary angle, return point along given a corresponding to angle
inline vec3 baryFromAngleA(float angle, float a) {
	vec3 v;
	v.lamA = a;
	v.lamC = (angle - 1) * (a - 1);
	v.lamB = 1 - v.lamA - v.lamC;
	return v;
}

inline vec3 baryFromAngleB(float angle, float b) {
	vec3 v;
	v.lamB = b;
	v.lamA = (angle - 1) * (b - 1);
	v.lamC = 1 - v.lamB - v.lamA;
	return v;
}

inline vec3 baryFromAngleC(float angle, float c) {
	vec3 v;
	v.lamC = c;
	v.lamB = (angle - 1) * (c - 1);
	v.lamA = 1 - v.lamC - v.lamB;
	return v;
}

}