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

	mag(v1);
	mag(v2);
	mag(v3);
	mag(v4);
	
	mag2(v1);
	mag2(v2);
	mag2(v3);
	mag2(v4);

	norm(v1);
	norm(v2);
	norm(v3);
	norm(v4);

	dot(v1, v1);
	dot(v2, v2);
	dot(v3, v3);
	dot(v4, v4);

	cross(v3, v3);

	angle(v1, v1);
	angle(v2, v2);
	angle(v3, v3);
	angle(v4, v4);

	lerp(v1, v1, t);
	lerp(v2, v2, t);
	lerp(v3, v3, t);
	lerp(v4, v4, t);
}

void testVectorCompilation() {
	testVectorTCompilation<             float>();
	testVectorTCompilation<            double>();
	testVectorTCompilation<              fnat>();
	testVectorTCompilation<  signed      char>();
	testVectorTCompilation<unsigned      char>();
	testVectorTCompilation<  signed     short>();
	testVectorTCompilation<unsigned     short>();
	testVectorTCompilation<  signed       int>();
	testVectorTCompilation<unsigned       int>();
	testVectorTCompilation<  signed      long>();
	testVectorTCompilation<unsigned      long>();
	testVectorTCompilation<  signed long long>();
	testVectorTCompilation<unsigned long long>();
	testVectorTCompilation<               nat>();
	testVectorTCompilation<              unat>();
}

int main(void) {
	testVectorCompilation();

	std::cin.get();
	return 0;
}