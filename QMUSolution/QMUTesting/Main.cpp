#include <iostream>
#include <sstream>

#include "QMU.hpp"
#include "QVector.hpp"
#include "QMatrix.hpp"
#include "QQuaternion.hpp"

using namespace qmu;

template <typename T>
void testVectorTCompilation() {
	T t;
	vec1<T> v1;
	vec2<T> v2;
	vec3<T> v3;
	vec4<T> v4;
	vec<T, 6> v6;
	std::stringstream os;

	//--------------------------------------------------------------------------
	// Vec1
	
	// constructors
	vec1<T> v1_1;
	vec1<T> v1_2(v1);
	vec1<T> v1_3(std::move(v1));
	vec1<T> v1_4(t);
	vec1<T> v1_5(v2);
	vec1<T> v1_6(v3);
	vec1<T> v1_7(v4);
	
	// assignment operators
	v1 = v1;
	v1 = std::move(v1);
	v1 = t;
	v1 = v2;
	v1 = v3;
	v1 = v4;

	// access operators
	v1[0];

	// arithmetic operators
	v1 += v1;
	v1 += t;
	v1 += v2;
	v1 += v3;
	v1 += v4;
	v1 -= v1;
	v1 -= t;
	v1 -= v2;
	v1 -= v3;
	v1 -= v4;
	v1 *= v1;
	v1 *= t;
	v1 *= v2;
	v1 *= v3;
	v1 *= v4;
	v1 /= vec1<T>(1);
	v1 /= T(1);
	v1 /= vec2<T>(1);
	v1 /= vec3<T>(1);
	v1 /= vec4<T>(1);
	++v1;
	v1++;
	--v1;
	v1--;
	+v1;
	-v1;
	v1 + v1;
	v1 + t;
	t + v1;
	v1 - v1;
	v1 - t;
	t - v1;
	v1 * v1;
	v1 * t;
	t * v1;
	v1 / vec1<T>(1);
	v1 / T(1);
	t / vec1<T>(1);

	// comparison operators
	v1 == v1;
	v1 == t;
	t == v1;
	v1 != v1;
	v1 != t;
	t != v1;
	v1 < t;
	t < v1;
	v1 > t;
	t > v1;
	v1 <= t;
	t <= v1;
	v1 >= t;
	t >= v1;

	// other
	v1.toString();
	os << v1;

	//--------------------------------------------------------------------------
	// Vec2

	// constructors
	vec2<T> v2_1;
	vec2<T> v2_2(v2);
	vec2<T> v2_3(std::move(v2));
	vec2<T> v2_4(t);
	vec2<T> v2_5(v1);
	vec2<T> v2_6(v3);
	vec2<T> v2_7(v4);
	vec2<T> v2_8(t, t);

	// assignment operators
	v2 = v2;
	v2 = std::move(v2);
	v2 = t;
	v2 = v1;
	v2 = v3;
	v2 = v4;

	// access operators
	v2[0];

	// arithmetic operators
	v2 += v2;
	v2 += t;
	v2 += v1;
	v2 += v3;
	v2 += v4;
	v2 -= v2;
	v2 -= t;
	v2 -= v1;
	v2 -= v3;
	v2 -= v4;
	v2 *= v2;
	v2 *= t;
	v2 *= v1;
	v2 *= v3;
	v2 *= v4;
	v2 /= vec2<T>(1);
	v2 /= T(1);
	v2 /= vec1<T>(1);
	v2 /= vec3<T>(1);
	v2 /= vec4<T>(1);
	++v2;
	v2++;
	--v2;
	v2--;
	+v2;
	-v2;
	v2 + v2;
	v2 + t;
	t + v2;
	v2 + v1;
	v1 + v2;
	v2 - v2;
	v2 - t;
	t - v2;
	v2 - v1;
	v1 - v2;
	v2 * v2;
	v2 * t;
	t * v2;
	v2 * v1;
	v1 * v2;
	v2 / vec2<T>(1);
	v2 / T(t);
	t / vec2<T>(1);
	v2 / vec1<T>(1);
	v1 / vec2<T>(1);

	// comparison operators
	v2 == v2;
	v2 == t;
	t == v2;
	v2 != v2;
	v2 != t;
	t != v2;
	v2 < t;
	t < v2;
	v2 > t;
	t > v2;
	v2 <= t;
	t <= v2;
	v2 >= t;
	t >= v2;

	// other
	v2.toString();
	os << v2;

	//--------------------------------------------------------------------------
	// Vec3

	// constructors
	vec3<T> v3_1;
	vec3<T> v3_2(v3);
	vec3<T> v3_3(std::move(v3));
	vec3<T> v3_4(t);
	vec3<T> v3_5(v1);
	vec3<T> v3_6(v2);
	vec3<T> v3_7(v4);
	vec3<T> v3_8(t, t, t);

	// assignment operators
	v3 = v3;
	v3 = std::move(v3);
	v3 = t;
	v3 = v1;
	v3 = v2;
	v3 = v4;

	// access operators
	v3[0];

	// arithmetic operators
	v3 += v3;
	v3 += t;
	v3 += v1;
	v3 += v2;
	v3 += v4;
	v3 -= v3;
	v3 -= t;
	v3 -= v1;
	v3 -= v2;
	v3 -= v4;
	v3 *= v3;
	v3 *= t;
	v3 *= v1;
	v3 *= v2;
	v3 *= v4;
	v3 /= vec3<T>(1);
	v3 /= T(1);
	v3 /= vec1<T>(1);
	v3 /= vec2<T>(1);
	v3 /= vec4<T>(1);
	++v3;
	v3++;
	--v3;
	v3--;
	+v3;
	-v3;
	v3 + v3;
	v3 + t;
	t + v3;
	v3 + v1;
	v1 + v3;
	v3 + v2;
	v2 + v3;
	v3 - v3;
	v3 - t;
	t - v3;
	v3 - v1;
	v1 - v3;
	v3 - v2;
	v2 - v3;
	v3 * v3;
	v3 * t;
	t * v3;
	v3 * v1;
	v1 * v3;
	v3 * v2;
	v2 * v3;
	v3 / vec3<T>(1);
	v3 / T(t);
	t / vec3<T>(1);
	v3 / vec1<T>(1);
	v1 / vec3<T>(1);
	v3 / vec2<T>(1);
	v2 / vec3<T>(1);

	// comparison operators
	v3 == v3;
	v3 == t;
	t == v3;
	v3 != v3;
	v3 != t;
	t != v3;
	v3 < t;
	t < v3;
	v3 > t;
	t > v3;
	v3 <= t;
	t <= v3;
	v3 >= t;
	t >= v3;

	// other
	v3.toString();
	os << v3;

	//--------------------------------------------------------------------------
	// Vec4

	// constructors
	vec4<T> v4_1;
	vec4<T> v4_2(v4);
	vec4<T> v4_3(std::move(v4));
	vec4<T> v4_4(t);
	vec4<T> v4_5(v1);
	vec4<T> v4_6(v2);
	vec4<T> v4_7(v3);
	vec4<T> v4_8(t, t, t, t);

	// assignment operators
	v4 = v4;
	v4 = std::move(v4);
	v4 = t;
	v4 = v1;
	v4 = v2;
	v4 = v3;

	// access operators
	v4[0];

	// arithmetic operators
	v4 += v4;
	v4 += t;
	v4 += v1;
	v4 += v2;
	v4 += v3;
	v4 -= v4;
	v4 -= t;
	v4 -= v1;
	v4 -= v2;
	v4 -= v3;
	v4 *= v4;
	v4 *= t;
	v4 *= v1;
	v4 *= v2;
	v4 *= v3;
	v4 /= vec4<T>(1);
	v4 /= T(1);
	v4 /= vec1<T>(1);
	v4 /= vec2<T>(1);
	v4 /= vec3<T>(1);
	++v4;
	v4++;
	--v4;
	v4--;
	+v4;
	-v4;
	v4 + v4;
	v4 + t;
	t + v4;
	v4 + v1;
	v1 + v4;
	v4 + v2;
	v2 + v4;
	v4 + v3;
	v3 + v4;
	v4 - v4;
	v4 - t;
	t - v4;
	v4 - v1;
	v1 - v4;
	v4 - v2;
	v2 - v4;
	v4 - v3;
	v3 - v4;
	v4 * v4;
	v4 * t;
	t * v4;
	v4 * v1;
	v1 * v4;
	v4 * v2;
	v2 * v4;
	v4 * v3;
	v3 * v4;
	v4 / vec4<T>(1);
	v4 / T(t);
	t / vec4<T>(1);
	v4 / vec1<T>(1);
	v1 / vec4<T>(1);
	v4 / vec2<T>(1);
	v2 / vec4<T>(1);
	v4 / vec3<T>(1);
	v3 / vec4<T>(1);

	// comparison operators
	v4 == v4;
	v4 == t;
	t == v4;
	v4 != v4;
	v4 != t;
	t != v4;
	v4 < t;
	t < v4;
	v4 > t;
	t > v4;
	v4 <= t;
	t <= v4;
	v4 >= t;
	t >= v4;

	// other
	v4.toString();
	os << v4;

	//--------------------------------------------------------------------------
	// Vec6

	// constructors
	vec<T, 6> v6_1;
	vec<T, 6> v6_2(v6);
	vec<T, 6> v6_3(std::move(v6));
	vec<T, 6> v6_4(v3, v3);
	vec<T, 6> v6_5(t, t, t, t, t, t);

	// asignment operators
	v6 = v6;
	v6 = std::move(v6);

	// access operators
	v6[0];

	// comparison operators
	v6 == v6;
	v6 != v6;

	// other
	v6.toString();
	os << v6;

	//--------------------------------------------------------------------------
	// Vec Functions

	v1 = vec1<T>(1);
	v2 = vec2<T>(1);
	v3 = vec3<T>(1);
	v4 = vec4<T>(1);

	magnitude(v1);
	magnitude(v2);
	magnitude(v3);
	magnitude(v4);
	
	magnitude2(v1);
	magnitude2(v2);
	magnitude2(v3);
	magnitude2(v4);

	normalize(v1);
	normalize(v2);
	normalize(v3);
	normalize(v4);

	dot(v1, v1);
	dot(v2, v2);
	dot(v3, v3);
	dot(v4, v4);

	cross(v2, v2);
	cross(v3, v3);

	reflect(v2, v2);
	reflect(v3, v3);

	angle(v1, v1);
	angle_n(v1, v1);
	angle(v2, v2);
	angle_n(v2, v2);
	angle(v3, v3);
	angle_n(v3, v3);
	angle(v4, v4);
	angle_n(v4, v4);

	lerp(v1, v1, t);
	lerp(v2, v2, t);
	lerp(v3, v3, t);
	lerp(v4, v4, t);

	orthogonal(v2);
	orthogonal(v3);
}

void testVectorCompilation() {
	testVectorTCompilation<    float>();
	testVectorTCompilation<   double>();
	testVectorTCompilation<     fnat>();
	testVectorTCompilation<     char>();
	testVectorTCompilation<    short>();
	testVectorTCompilation<      int>();
	testVectorTCompilation<     long>();
	testVectorTCompilation<long long>();
	testVectorTCompilation<      nat>();
}

template <typename T>
void testMatrixTCompilation() {
	T t;
	vec1<T> v1;
	vec2<T> v2;
	vec3<T> v3;
	vec4<T> v4;
	mat2<T> m2;
	mat3<T> m3;
	mat4<T> m4;
	std::stringstream os;

	//--------------------------------------------------------------------------
	// Mat2

	// constructors
	mat2<T> m2_1;
	mat2<T> m2_2(m2);
	mat2<T> m2_3(std::move(m2));
	mat2<T> m2_4(t, t, t, t);
	mat2<T> m2_5(m3);
	mat2<T> m2_6(m4);
	mat2<T> m2_7(v2, v2);

	// assignment operators
	m2 = m2;
	m2 = std::move(m2);
	m2 = m3;
	m2 = m4;

	// access operators
	m2[0];

	// arithmetic assignment operators
	m2 += t;
	m2 += m2;
	m2 -= t;
	m2 -= m2;
	m2 *= t;
	m2 *= m2;
	m2 /= T(1);
	++m2;
	m2++;
	--m2;
	m2--;

	// arithmetic operators
	+m2;
	-m2;
	m2 + m2;
	m2 + t;
	t + m2;
	m2 - m2;
	m2 - t;
	t - m2;
	m2 * m2;
	m2 * t;
	t * m2;
	m2 * v2;
	m2 / T(1);
	T(1) / m2;

	// comparison operators
	m2 == m2;
	m2 != m2;

	// other
	m2.toString();
	os << m2;

	//--------------------------------------------------------------------------
	// Mat3

	// constructors
	mat3<T> m3_1;
	mat3<T> m3_2(m3);
	mat3<T> m3_3(std::move(m3));
	mat3<T> m3_4(t, t, t, t, t, t, t, t, t);
	mat3<T> m3_5(m2);
	mat3<T> m3_6(m4);
	mat3<T> m3_7(v3, v3, v3);

	// assignment operators
	m3 = m3;
	m3 = std::move(m3);
	m3 = m2;
	m3 = m4;

	// access operators
	m3[0];

	// arithmetic assignment operators
	m3 += t;
	m3 += m3;
	m3 -= t;
	m3 -= m3;
	m3 *= t;
	m3 *= m3;
	m3 /= T(1);
	++m3;
	m3++;
	--m3;
	m3--;

	// arithmetic operators
	+m3;
	-m3;
	m3 + m3;
	m3 + t;
	t + m3;
	m3 - m3;
	m3 - t;
	t - m3;
	m3 * m3;
	m3 * t;
	t * m3;
	m3 * v3;
	m3 / T(1);
	T(1) / m3;

	// comparison operators
	m3 == m3;
	m3 != m3;

	// other
	m3.toString();
	os << m3;

	//--------------------------------------------------------------------------
	// Mat4

	// constructors
	mat4<T> m4_1;
	mat4<T> m4_2(m4);
	mat4<T> m4_3(std::move(m4));
	mat4<T> m4_4(t, t, t, t, t, t, t, t, t, t, t, t, t, t, t, t);
	mat4<T> m4_5(m2);
	mat4<T> m4_6(m3);
	mat4<T> m4_7(v4, v4, v4, v4);

	// assignment operators
	m4 = m4;
	m4 = std::move(m4);
	m4 = m2;
	m4 = m3;

	// access operators
	m4[0];

	// arithmetic assignment operators
	m4 += t;
	m4 += m4;
	m4 -= t;
	m4 -= m4;
	m4 *= t;
	m4 *= m4;
	m4 /= T(1);
	++m4;
	m4++;
	--m4;
	m4--;

	// arithmetic operators
	+m4;
	-m4;
	m4 + m4;
	m4 + t;
	t + m4;
	m4 - m4;
	m4 - t;
	t - m4;
	m4 * m4;
	m4 * t;
	t * m4;
	m4 * v4;
	m4 / T(1);
	T(1) / m4;

	// comparison operators
	m4 == m4;
	m4 != m4;

	// other
	m4.toString();
	os << m4;

	//--------------------------------------------------------------------------
	// Mat Functions

	transpose(m2);
	transpose(m3);
	transpose(m4);
	cofactor(m2);
	cofactor(m3);
	cofactor(m4);
	adjoint(m2);
	adjoint(m3);
	adjoint(m4);
	determinant(m2);
	determinant(m3);
	determinant(m4);
	inverse(m2);
	inverse(m3);
	inverse(m4);

	//--------------------------------------------------------------------------
	// Transformations

	translate(v1);
	translate(v2);
	translate(v3);
	translate(m2, v1);
	translate(m3, v2);
	translate(m4, v3);
	scale(v2);
	scale(v3);
	scale(m2, v1);
	scale(m2, v2);
	scale(m3, v2);
	scale(m3, v3);
	scale(m4, v3);
	scale(m4, v4);
	rotate(t);
	rotateX(t);
	rotateY(t);
	rotateZ(t);
	rotate(v3, t, t);
	rotate_n(v3, t, t);
	rotate(v3, t);
	rotate_n(v3, t);
	euler(v3, v3, t, t, t);
	euler_n(v3, v3, t, t, t);
	align(v2, v2);
	align(v3, v3);
	align_n(v2, v2);
	align_n(v3, v3);
	map(v2, v2, v2, v2);
	map_o(v2, v2, v2, v2);
	map(v3, v3, v3, v3, v3, v3);
	map_o(v3, v3, v3, v3, v3, v3);
	mapTo(v2, v2);
	mapTo_o(v2, v2);
	mapTo(v3, v3, v3);
	mapTo_o(v3, v3, v3);
	mapFrom(v2, v2);
	mapFrom(v3, v3, v3);
	orthoProj(t, t, t, t);
	orthoProjAsym(t, t, t, t, t, t);
	perspProj(t, t, t, t);
	perspProjAsym(t, t, t, t, t, t);
	view(v3, v3, v3);
	view(v3, v3, v3, v3);
	view_n(v3, v3, v3, v3);
	view_o(v3, v3, v3, v3);
	view_on(v3, v3, v3, v3);
}

void testMatrixCompilation() {
	testMatrixTCompilation<float>();
	testMatrixTCompilation<double>();
	testMatrixTCompilation<fnat>();
}

template <typename T>
void testQuaternionTCompilation() {
	T t;
	vec3<T> v3;
	vec4<T> v4;
	mat3<T> m3;
	quat<T> q;
	std::stringstream os;

	//--------------------------------------------------------------------------
	// Quat

	// constructors
	quat<T> q_1;
	quat<T> q_2(q);
	quat<T> q_3(std::move(q));
	quat<T> q_4(v3, t);
	quat<T> q_5(t, t, t, t);
	quat<T> q_6(v3);
	quat<T> q_7(v4);

	// assignment operators
	q = q;
	q = std::move(q);

	// access operators
	q[0];

	// arithmetic assignment operators
	q += q;
	q -= q;
	q *= q;
	q *= t;
	q /= quat<T>(1, 1, 1, 1);

	// arithmetic operators
	+q;
	-q;
	q + q;
	q - q;
	q * q;
	q * t;
	t * q;
	q * v3;
	q / quat<T>(1, 1, 1, 1);

	// comparison operators
	q == q;
	q != q;

	// other
	q.toString();
	os << q;

	//--------------------------------------------------------------------------
	// Quat Functions

	q = quat<T>(1, 1, 1, 1);

	magnitude(q);
	normalize(q);
	inverse(q);
	angle(q);
	axis(q);
	axis_n(q);

	//--------------------------------------------------------------------------
	// Transformations

	rotateQ(v3, t);
	rotateQ_n(v3, t);
	alignQ(v3, v3);
	alignQ_n(v3, v3);
	alignQ(v3, v3, v3, v3);
	alignQ_n(v3, v3, v3, v3);
	eulerQ(v3, v3, t, t, t);
	eulerQ_n(v3, v3, t, t, t);
	toMat(q);
	nlerp(q, q, t);
	slerp(q, q, t);
}

void testQuaternionCompilation() {
	testQuaternionTCompilation<float>();
	testQuaternionTCompilation<double>();
	testQuaternionTCompilation<fnat>();
}

int main(void) {
	testVectorCompilation();
	testMatrixCompilation();
	testQuaternionCompilation();

	std::cin.get();
	return 0;
}