#pragma once

/*
	The mat structs need to be of standard layout.
	std::is_standard_layout

	Column-major ordering
	x1 x2 x3	00 03 06
	y1 y2 y3	01 04 07
	z1 z2 z3	02 05 08
*/



#include "QVector.hpp"



namespace qmu {



template <typename T, nat t_m, nat t_n> struct mat;



template <typename T> using mat2 = mat<T, 2, 2>;
template <typename T> using mat3 = mat<T, 3, 3>;
template <typename T> using mat4 = mat<T, 4, 4>;

template <nat t_m, nat t_n> using  fmat = mat< float, t_m, t_n>;
template <nat t_m, nat t_n> using  dmat = mat<double, t_m, t_n>;
template <nat t_m, nat t_n> using fnmat = mat<  fnat, t_m, t_n>;

using  fmat2 = mat< float, 2, 2>;
using  fmat3 = mat< float, 3, 3>;
using  fmat4 = mat< float, 4, 4>;
using  dmat2 = mat<double, 2, 2>;
using  dmat3 = mat<double, 3, 3>;
using  dmat4 = mat<double, 4, 4>;
using fnmat2 = mat<  fnat, 2, 2>;
using fnmat3 = mat<  fnat, 3, 3>;
using fnmat4 = mat<  fnat, 4, 4>;




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT2 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct mat<T, 2, 2> {

	static constexpr nat t_m = 2, t_n = 2;

	union {
		struct {
			T x1, y1;
			T x2, y2;
		};
	};

	//--- constructors ---

	constexpr mat();
	constexpr mat(const mat2<T> & m);
	constexpr mat(mat2<T> && m);

	constexpr mat(
		const T & x1, const T & y1,
		const T & x2, const T & y2
	);
	constexpr explicit mat(const mat3<T> & m);
	constexpr explicit mat(const mat4<T> & m);
	constexpr mat(
		const vec2<T> & v1,
		const vec2<T> & v2
	);

	//--- destructor ---

	~mat() {
		static_assert(std::is_standard_layout<mat<T, 2, 2>>::value, "mat<T, 2, 2> must be of standard layout");
		static_assert(sizeof(mat<T, 2, 2>) == 4 * sizeof(T), "mat<T, 2, 2> must be equal in size to 4 Ts");
		static_assert(std::is_default_constructible<T>::value, "mat<T, 2, 2> must be default constructible");
		static_assert(std::is_copy_constructible<T>::value, "mat<T, 2, 2> must be copy constructable");
		static_assert(std::is_copy_assignable<T>::value, "mat<T, 2, 2> must be copy assignable");
	}

	//--- assignment operators ---

	mat2<T> & operator=(const mat2<T> & m);
	mat2<T> & operator=(mat2<T> && m);

	mat2<T> & operator=(const mat3<T> & m);
	mat2<T> & operator=(const mat4<T> & m);

	//--- access operators ---

	T & operator[](nat i);

	//--- arithmetic assignment operators ---

	template <typename T> friend mat2<T> & operator+=(mat2<T> &  m, const      T  &  v);
	template <typename T> friend mat2<T> & operator+=(mat2<T> & m1, const mat2<T> & m2);

	template <typename T> friend mat2<T> & operator-=(mat2<T> &  m, const      T  &  v);
	template <typename T> friend mat2<T> & operator-=(mat2<T> & m1, const mat2<T> & m2);

	template <typename T> friend mat2<T> & operator*=(mat2<T> &  m, const      T  &  v);
	template <typename T> friend mat2<T> & operator*=(mat2<T> & m1, const mat2<T> & m2);

	template <typename T> friend mat2<T> & operator/=(mat2<T> & m, const T & v);

	template <typename T> friend mat2<T> & operator++(mat2<T> & m);
	template <typename T> friend mat2<T>   operator++(mat2<T> & m, int);

	template <typename T> friend mat2<T> & operator--(mat2<T> & m);
	template <typename T> friend mat2<T>   operator--(mat2<T> & m, int);

	//--- arithmetic operators ---

	template <typename T> friend mat2<T> operator+(const mat2<T> & m);

	template <typename T> friend mat2<T> operator-(const mat2<T> & m);

	template <typename T> friend mat2<T> operator+(const mat2<T> & m1, const mat2<T> & m2);
	template <typename T> friend mat2<T> operator+(const mat2<T> &  m, const      T  &  v);
	template <typename T> friend mat2<T> operator+(const      T  &  v, const mat2<T> & m1);

	template <typename T> friend mat2<T> operator-(const mat2<T> & m1, const mat2<T> & m2);
	template <typename T> friend mat2<T> operator-(const mat2<T> &  m, const      T  &  v);
	template <typename T> friend mat2<T> operator-(const      T  &  v, const mat2<T> &  m);

	template <typename T> friend mat2<T> operator*(const mat2<T> & m1, const mat2<T> & m2);
	template <typename T> friend mat2<T> operator*(const mat2<T> &  m, const      T  &  v);
	template <typename T> friend mat2<T> operator*(const      T  &  v, const mat2<T> &  m);
	template <typename T> friend vec2<T> operator*(const mat2<T> &  m, const vec2<T> &  v);

	template <typename T> friend mat2<T> operator/(const mat2<T> &  m, const      T  & v);
	template <typename T> friend mat2<T> operator/(const      T  &  v, const mat2<T> & m);

	//--- comparison operators ---

	template <typename T> friend bool operator==(const mat2<T> & m1, const mat2<T> & m2);
	template <typename T> friend bool operator!=(const mat2<T> & m1, const mat2<T> & m2);

	//--- other ---

	std::string toString() const;

	template <typename T>
	friend std::ostream & operator<<(std::ostream & os, const mat2<T> & m);

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT3 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct mat<T, 3, 3> {

	static constexpr nat t_m = 3, t_n = 3;

	union {
		struct {
			T x1, y1, z1;
			T x2, y2, z2;
			T x3, y3, z3;
		};
	};

	//--- constructors ---

	constexpr mat();
	constexpr mat(const mat3<T> & m);
	constexpr mat(mat3<T> && m);

	constexpr mat(
		const T & x1, const T & y1, const T & z1,
		const T & x2, const T & y2, const T & z2,
		const T & x3, const T & y3, const T & z3
	);
	constexpr explicit mat(const mat2<T> & m);
	constexpr explicit mat(const mat4<T> & m);
	constexpr mat(
		const vec3<T> & v1,
		const vec3<T> & v2,
		const vec3<T> & v3
	);

	//--- destructor ---

	~mat() {
		static_assert(std::is_standard_layout<mat<T, 3, 3>>::value, "mat<T, 3, 3> must be of standard layout");
		static_assert(sizeof(mat<T, 3, 3>) == 9 * sizeof(T), "mat<T, 3, 3> must be equal in size to 9 Ts");
		static_assert(std::is_default_constructible<T>::value, "mat<T, 3, 3> must be default constructible");
		static_assert(std::is_copy_constructible<T>::value, "mat<T, 3, 3> must be copy constructable");
		static_assert(std::is_copy_assignable<T>::value, "mat<T, 3, 3> must be copy assignable");
	}

	//--- assignment operators ---

	mat3<T> & operator=(const mat3<T> & m);
	mat3<T> & operator=(mat3<T> && m);

	mat3<T> & operator=(const mat2<T> & m);
	mat3<T> & operator=(const mat4<T> & m);

	//--- access operators ---

	T & operator[](nat i);

	//--- arithmetic assignment operators ---

	template <typename T> friend mat3<T> & operator+=(mat3<T> &  m, const      T  &  v);
	template <typename T> friend mat3<T> & operator+=(mat3<T> & m1, const mat3<T> & m2);

	template <typename T> friend mat3<T> & operator-=(mat3<T> &  m, const      T  &  v);
	template <typename T> friend mat3<T> & operator-=(mat3<T> & m1, const mat3<T> & m2);

	template <typename T> friend mat3<T> & operator*=(mat3<T> &  m, const      T  &  v);
	template <typename T> friend mat3<T> & operator*=(mat3<T> & m1, const mat3<T> & m2);

	template <typename T> friend mat3<T> & operator/=(mat3<T> & m, const T & v);

	template <typename T> friend mat3<T> & operator++(mat3<T> & m);
	template <typename T> friend mat3<T>   operator++(mat3<T> & m, int);

	template <typename T> friend mat3<T> & operator--(mat3<T> & m);
	template <typename T> friend mat3<T>   operator--(mat3<T> & m, int);

	//--- arithmetic operators ---

	template <typename T> friend mat3<T> operator+(const mat3<T> & m);

	template <typename T> friend mat3<T> operator-(const mat3<T> & m);

	template <typename T> friend mat3<T> operator+(const mat3<T> & m1, const mat3<T> & m2);
	template <typename T> friend mat3<T> operator+(const mat3<T> &  m, const      T  &  v);
	template <typename T> friend mat3<T> operator+(const      T  &  v, const mat3<T> &  m);

	template <typename T> friend mat3<T> operator-(const mat3<T> & m1, const mat3<T> & m2);
	template <typename T> friend mat3<T> operator-(const mat3<T> &  m, const      T  &  v);
	template <typename T> friend mat3<T> operator-(const      T  &  v, const mat3<T> &  m);

	template <typename T> friend mat3<T> operator*(const mat3<T> & m1, const mat3<T> & m2);
	template <typename T> friend mat3<T> operator*(const mat3<T> &  m, const      T  &  v);
	template <typename T> friend mat3<T> operator*(const      T  &  v, const mat3<T> &  m);
	template <typename T> friend vec3<T> operator*(const mat3<T> & m1, const vec3<T> &  v);

	template <typename T> friend mat3<T> operator/(const mat3<T> & m1, const      T  & v);
	template <typename T> friend mat3<T> operator/(const      T  &  v, const mat3<T> & m);

	//--- comparison operators ---

	template <typename T> friend bool operator==(const mat3<T> & m1, const mat3<T> & m2);

	template <typename T> friend bool operator!=(const mat3<T> & m1, const mat3<T> & m2);

	//--- other ---

	std::string toString() const;

	template <typename T> friend std::ostream & operator<<(std::ostream & os, const mat3<T> & m);

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT4 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct mat<T, 4, 4> {

	static constexpr nat t_m = 4, t_n = 4;

	union {
		struct {
			T x1, y1, z1, w1;
			T x2, y2, z2, w2;
			T x3, y3, z3, w3;
			T x4, y4, z4, w4;
		};
	};

	//--- constructors ---

	constexpr mat();
	constexpr mat(const mat4<T> & m);
	constexpr mat(mat4<T> && m);

	constexpr mat(
		const T & x1, const T & y1, const T & z1, const T & w1,
		const T & x2, const T & y2, const T & z2, const T & w2,
		const T & x3, const T & y3, const T & z3, const T & w3,
		const T & x4, const T & y4, const T & z4, const T & w4
	);
	constexpr explicit mat(const mat2<T> & m);
	constexpr explicit mat(const mat3<T> & m);
	constexpr mat(
		const vec4<T> & v1,
		const vec4<T> & v2,
		const vec4<T> & v3,
		const vec4<T> & v4
	);

	//--- destructor ---

	~mat() {
		static_assert(std::is_standard_layout<mat<T, 4, 4>>::value, "mat<T, 4, 4> must be of standard layout");
		static_assert(sizeof(mat<T, 4, 4>) == 16 * sizeof(T), "mat<T, 4, 4> must be equal in size to 16 Ts");
		static_assert(std::is_default_constructible<T>::value, "mat<T, 4, 4> must be default constructible");
		static_assert(std::is_copy_constructible<T>::value, "mat<T, 4, 4> must be copy constructable");
		static_assert(std::is_copy_assignable<T>::value, "mat<T, 4, 4> must be copy assignable");
	}

	//--- assignment operators ---

	mat4<T> & operator=(const mat4<T> & m);
	mat4<T> & operator=(mat4<T> && m);

	mat4<T> & operator=(const mat2<T> & m);
	mat4<T> & operator=(const mat3<T> & m);

	//--- access operators ---

	T & operator[](nat i);

	//--- arithmetic assignment operators ---

	template <typename T> friend mat4<T> & operator+=(mat4<T> & m, const T & v);
	template <typename T> friend mat4<T> & operator+=(mat4<T> & m1, const mat4<T> & m2);

	template <typename T> friend mat4<T> & operator-=(mat4<T> & m, const T & v);
	template <typename T> friend mat4<T> & operator-=(mat4<T> & m1, const mat4<T> & m2);

	template <typename T> friend mat4<T> & operator*=(mat4<T> & m, const T & v);
	template <typename T> friend mat4<T> & operator*=(mat4<T> & m1, const mat4<T> & m2);

	template <typename T> friend mat4<T> & operator/=(mat4<T> & m, const T & v);

	template <typename T> friend mat4<T> & operator++(mat4<T> & m);
	template <typename T> friend mat4<T>   operator++(mat4<T> & m, int);

	template <typename T> friend mat4<T> & operator--(mat4<T> & m);
	template <typename T> friend mat4<T>   operator--(mat4<T> & m, int);

	//--- arithmetic operators ---

	template <typename T> friend mat4<T> operator+(const mat4<T> & m);

	template <typename T> friend mat4<T> operator-(const mat4<T> & m);

	template <typename T> friend mat4<T> operator+(const mat4<T> & m1, const mat4<T> & m2);
	template <typename T> friend mat4<T> operator+(const mat4<T> &  m, const      T  &  v);
	template <typename T> friend mat4<T> operator+(const      T  &  v, const mat4<T> &  m);

	template <typename T> friend mat4<T> operator-(const mat4<T> & m1, const mat4<T> & m2);
	template <typename T> friend mat4<T> operator-(const mat4<T> &  m, const      T  &  v);
	template <typename T> friend mat4<T> operator-(const      T  &  v, const mat4<T> &  m);

	template <typename T> friend mat4<T> operator*(const mat4<T> & m1, const mat4<T> & m2);
	template <typename T> friend mat4<T> operator*(const mat4<T> &  m, const      T  &  v);
	template <typename T> friend mat4<T> operator*(const      T  &  v, const mat4<T> &  m);
	template <typename T> friend vec4<T> operator*(const mat4<T> &  m, const vec4<T> &  v);

	template <typename T> friend mat4<T> operator/(const mat4<T> & m, const      T  & v);
	template <typename T> friend mat4<T> operator/(const      T  & v, const mat4<T> & m);

	//--- comparison operators ---

	template <typename T> friend bool operator==(const mat4<T> & m1, const mat4<T> & m2);

	template <typename T> friend bool operator!=(const mat4<T> & m1, const mat4<T> & m2);

	//--- other ---

	std::string toString() const;

	template <typename T> friend std::ostream & operator<<(std::ostream & os, const mat4<T> & m);

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT FUNCTIONS -------------------------------------------------------------------------------------------------------



template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> trans(const mat<T, t_m, t_n> & m);

template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> cof(const mat<T, t_m, t_n> & m);

template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> adj(const mat<T, t_m, t_n> & m);

template <typename T, nat t_m, nat t_n> T det(const mat<T, t_m, t_n> & m);

template <typename T, nat t_m, nat t_n> mat<T, t_m, t_n> inv(const mat<T, t_m, t_n> & m);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORMATIONS -----------------------------------------------------------------------------------------------------



template <typename T, nat t_n> mat<T, t_n + 1, t_n + 1> translate(const vec<T, t_n> & delta);

template <typename T, nat t_n> mat<T, t_n, t_n> scale(const vec<T, t_n> & scale);

template <typename T> mat2<T> rotate(const T & theta);

template <typename T> mat3<T> rotateX(const T & theta);

template <typename T> mat3<T> rotateY(const T & theta);

template <typename T> mat3<T> rotateZ(const T & theta);

template <typename T> mat3<T> rotate(const vec3<T> & axis, const T & sinTheta, const T & cosTheta);
template <typename T> mat3<T> rotate_n(const vec3<T> & axis, const T & sinTheta, const T & cosTheta);

template <typename T> mat3<T> rotate(const vec3<T> & axis, const T & theta);
template <typename T> mat3<T> rotate_n(const vec3<T> & axis, const T & theta);

//theta: thumb points up, phi: right, psi: forward
template <typename T> mat3<T> euler(const vec3<T> & forward, const vec3<T> & up, const T & theta, const T & phi, const T & psi);
template <typename T> mat3<T> euler_n(const vec3<T> & forward, const vec3<T> & up, const T & theta, const T & phi, const T & psi);

template <typename T> mat3<T> align(const vec3<T> & v1, const vec3<T> & v2);
template <typename T> mat3<T> align_n(const vec3<T> & v1, const vec3<T> & v2);

//expects orthogonal fvectors
template <typename T> mat3<T> align(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2);
template <typename T> mat3<T> align_n(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2);

//expects ortho-normal vectors!!! x, y, and z are the axes
template <typename T> mat3<T> map(const vec3<T> & x1, const vec3<T> & y1, const vec3<T> & z1, const vec3<T> & x2, const vec3<T> & y2, const vec3<T> & z2);
template <typename T> mat3<T> map_n(const vec3<T> & x1, const vec3<T> & y1, const vec3<T> & z1, const vec3<T> & x2, const vec3<T> & y2, const vec3<T> & z2);

template <typename T> mat3<T> mapTo(const vec3<T> & x, const vec3<T> & y, const vec3<T> & z);
template <typename T> mat3<T> mapTo_n(const vec3<T> & x, const vec3<T> & y, const vec3<T> & z);

template <typename T> mat3<T> mapFrom(const vec3<T> & x, const vec3<T> & y, const vec3<T> & z);
template <typename T> mat3<T> mapFrom_n(const vec3<T> & x, const vec3<T> & y, const vec3<T> & z);

template <typename T> mat3<T> mapAny(const vec3<T> & x1, const vec3<T> & y1, const vec3<T> & z1, const vec3<T> & x2, const vec3<T> & y2, const vec3<T> & z2);

template <typename T> mat4<T> ortho(const T & width, const T & height, const T & near, const T & far);
template <typename T> mat4<T> orthoAsym(const T & left, const T & right, const T & bottom, const T & top, const T & near, const T & far);

//fov is angle in radians between top and bottom planes, aspectRatio is screen width / height, zNear is distance to near plane, zFar is distance to far plane
template <typename T> mat4<T> perspective(const T & fov, const T & aspectRatio, const T & near, const T & far);
//fovNX is angle between center and left plane, fovPX between center and right, fovNY between center and bottom, fovPY between center and top
template <typename T> mat4<T> perspectiveAsym(const T & fovLeft, const T & fovRight, const T & fovBottom, const T & fovTop, const T & near, const T & far);

//camUp should be perpendicular to camDir!!!
template <typename T> mat4<T> view(const vec3<T> & camPos, const vec3<T> & camDir, const vec3<T> & camUp);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT2 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr mat<T, 2, 2>::mat() :
	x1(1), y1(0),
	x2(0), y2(1)
{}

template <typename T>
constexpr mat<T, 2, 2>::mat(const mat2<T> & m) :
	x1(m.x1), y1(m.y1),
	x2(m.x2), y2(m.y2)
{}

template <typename T>
constexpr mat<T, 2, 2>::mat(mat2<T> && m) :
	x1(m.x1), y1(m.y1),
	x2(m.x2), y2(m.y2)
{}

template <typename T>
constexpr mat<T, 2, 2>::mat(
	const T & x1, const T & y1,
	const T & x2, const T & y2
) :
	x1(x1), y1(y1),
	x2(x2), y2(y2)
{}

template <typename T>
constexpr mat<T, 2, 2>::mat(const mat3<T> & m) :
	x1(m.x1), y1(m.y1),
	x2(m.x2), y2(m.y2)
{}

template <typename T>
constexpr mat<T, 2, 2>::mat(const mat4<T> & m) :
	x1(m.x1), y1(m.y1),
	x2(m.x2), y2(m.y2)
{}

template <typename T>
constexpr mat<T, 2, 2>::mat(
	const vec2<T> & v1,
	const vec2<T> & v2
) :
	x1(v1.x), y1(v1.y),
	x2(v2.x), y2(v2.y)
{}



//------------------------------------------------------------------------------
// Assignment Operators



template <typename T>
inline mat2<T> & mat<T, 2, 2>::operator=(const mat2<T> & m) {
	x1 = m.x1; y1 = m.y1;
	x2 = m.x2; y2 = m.y2;
	return *this;
}

template <typename T>
inline mat2<T> & mat<T, 2, 2>::operator=(mat2<T> && m) {
	x1 = m.x1; y1 = m.y1;
	x2 = m.x2; y2 = m.y2;
	return *this;
}

template <typename T>
inline mat2<T> & mat<T, 2, 2>::operator=(const mat3<T> & m) {
	x1 = m.x1; y1 = m.y1;
	x2 = m.x2; y2 = m.y2;
	return *this;
}

template <typename T>
inline mat2<T> & mat<T, 2, 2>::operator=(const mat4<T> & m) {
	x1 = m.x1; y1 = m.y1;
	x2 = m.x2; y2 = m.y2;
	return *this;
}



//------------------------------------------------------------------------------
// Access Operators



template <typename T>
inline T & mat<T, 2, 2>::operator[](nat i) {
	return *(&x1 + i);
}



//------------------------------------------------------------------------------
// Arithmetic Assignment Operators



//--- add assign ---

template <typename T>
inline mat2<T> & operator+=(mat2<T> & m, const T & v) {
	return m = m + v;
}

template <typename T>
inline mat2<T> & operator+=(mat2<T> & m1, const mat2<T> & m2) {
	return m1 = m1 + m2;
}

//--- subtract assign ---

template <typename T>
inline mat2<T> & operator-=(mat2<T> & m, const T & v) {
	m = m - v;
}

template <typename T>
inline mat2<T> & operator-=(mat2<T> & m1, const mat2<T> & m2) {
	return m1 = m1 - m2;
}

//--- multiply assign ---

template <typename T>
inline mat2<T> & operator*=(mat2<T> & m, const T & v) {
	m = m * v;
}

template <typename T>
inline mat2<T> & operator*=(mat2<T> & m1, const mat2<T> & m2) {
	return m1 = m1 * m2;
}

//--- divide assign ---

template <typename T>
inline mat2<T> & operator/=(mat2<T> & m, const T & v) {
	m = m / v;
}

//--- pre increment ---

template <typename T>
inline mat2<T> & operator++(mat2<T> & m) {
	++m.x1; ++m.y1;
	++m.x2; ++m.y2;

	return m;
}

//--- post increment ---

template <typename T>
inline mat2<T> operator++(mat2<T> & m, int) {
	mat2 temp(m);
	++m;

	return temp;
}

//--- pre decrement ---

template <typename T>
inline mat2<T> & operator--(mat2<T> & m) {
	--m.x1; --m.y1;
	--m.x2; --m.y2;

	return m;
}

//--- post decrement ---

template <typename T>
inline mat2<T> operator--(mat2<T> & m, int) {
	mat2 temp(m);
	--m;

	return temp;
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- positive ---

template <typename T>
inline mat2<T> operator+(const mat2<T> & m) {
	return mat2<T>(
		+m.x1, +m.y1,
		+m.x2, +m.y2
	);
}

//--- negative ---

template <typename T>
inline mat2<T> operator-(const mat2<T> & m) {
	return mat2<T>(
		-m.x1, -m.y1,
		-m.x2, -m.y2
	);
}

//--- add ---

template <typename T>
inline mat2<T> operator+(const mat2<T> & m1, const mat2<T> & m2) {
	return mat2<T>(
		m1.x1 + m2.x1, m1.y1 + m2.y1,
		m1.x2 + m2.x2, m1.y2 + m2.y2
	);
}

template <typename T>
inline mat2<T> operator+(const mat2<T> & m, const T & v) {
	return mat2<T>(
		m.x1 + v, m.y1 + v,
		m.x2 + v, m.y2 + v
	);
}

template <typename T>
inline mat2<T> operator+(const T & v, const mat2<T> & m) {
	return mat2<T>(
		v + m.x1, v + m.y1,
		v + m.x2, v + m.y2
	);
}

//--- subtract ---

template <typename T>
inline mat2<T> operator-(const mat2<T> & m1, const mat2<T> & m2) {
	return mat2<T>(
		m1.x1 - m2.x1, m1.y1 - m2.y1,
		m1.x2 - m2.x2, m1.y2 - m2.y2
	);
}

template <typename T>
inline mat2<T> operator-(const mat2<T> & m, const T & v) {
	return mat2<T>(
		m.x1 - v, m.y1 - v,
		m.x2 - v, m.y2 - v
	);
}

template <typename T>
inline mat2<T> operator-(const T & v, const mat2<T> & m) {
	return mat2<T>(
		v - m.x1, v - m.y1,
		v - m.x2, v - m.y2
	);
}

//--- multiply ---

template <typename T>
inline mat2<T> operator*(const mat2<T> & m1, const mat2<T> & m2) {
	return mat2<T>(
		m1.x1 * m2.x1 + m1.x2 * m2.y1,
		m1.y1 * m2.x1 + m1.y2 * m2.y1,

		m1.x1 * m2.x2 + m1.x2 * m2.y2,
		m1.y1 * m2.x2 + m1.y2 * m2.y2
	);
}

template <typename T>
inline mat2<T> operator*(const mat2<T> & m, const T & v) {
	return mat2<T>(
		m.x1 * v, m.y1 * v,
		m.x2 * v, m.y2 * v
	);
}

template <typename T>
inline mat2<T> operator*(const T & v, const mat2<T> & m) {
	return mat2<T>(
		v * m.x1, v * m.y1,
		v * m.x2, v * m.y2
	);
}

template <typename T>
inline vec2<T> operator*(const mat2<T> & m, const vec2<T> & v) {
	return vec2<T>(
		v.x * m.x1 + v.y * m.x2,
		v.x * m.y1 + v.y * m.y2
	);
}

//--- divide ---

template <typename T>
inline mat2<T> operator/(const mat2<T> & m, const T & v) {
	return mat2<T>(
		m.x1 / v, m.y1 / v,
		m.x2 / v, m.y2 / v
	);
}

template <typename T>
inline mat2<T> operator/(const T & v, const mat2<T> & m) {
	return mat2<T>(
		v / m.x1, v / m.y1,
		v / m.x2, v / m.y2
	);
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T>
inline bool operator==(const mat2<T> & m1, const mat2<T> & m2) {
	return
		m1.x1 == m2.x1 && m1.y1 == m2.y1 &&
		m1.x2 == m2.x2 && m1.y2 == m2.y2;
}

//--- not equal to ---

template <typename T>
inline bool operator!=(const mat2<T> & m1, const mat2<T> & m2) {
	return
		m1.x1 != m2.x1 || m1.y1 != m2.y1 ||
		m1.x2 != m2.x2 || m1.y2 != m2.y2;
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string mat<T, 2, 2>::toString() const {
	return
		"[ " +
		std::to_string(x1) + " " + std::to_string(y1) +
		" | " +
		std::to_string(x2) + " " + std::to_string(y2) +
		" ]";
}



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const mat2<T> & m) {
	return os << m.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT3 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr mat<T, 3, 3>::mat() :
	x1(1), y1(0), z1(0),
	x2(0), y2(1), z2(0),
	x3(0), y3(0), z3(1)
{}

template <typename T>
constexpr mat<T, 3, 3>::mat(const mat3<T> & m) :
	x1(m.x1), y1(m.y1), z1(m.z1),
	x2(m.x2), y2(m.y2), z2(m.z2),
	x3(m.x3), y3(m.y3), z3(m.z3)
{}

template <typename T>
constexpr mat<T, 3, 3>::mat(mat3<T> && m) :
	x1(m.x1), y1(m.y1), z1(m.z1),
	x2(m.x2), y2(m.y2), z2(m.z2),
	x3(m.x3), y3(m.y3), z3(m.z3)
{}

template <typename T>
constexpr mat<T, 3, 3>::mat(
	const T & x1, const T & y1, const T & z1,
	const T & x2, const T & y2, const T & z2,
	const T & x3, const T & y3, const T & z3
) :
	x1(x1), y1(y1), z1(z1),
	x2(x2), y2(y2), z2(z2),
	x3(x3), y3(y3), z3(z3)
{}

template <typename T>
constexpr mat<T, 3, 3>::mat(const mat2<T> & m) :
	x1(m.x1), y1(m.y1), z1(0),
	x2(m.x2), y2(m.y2), z2(0),
	x3(0), y3(0), z3(1)
{}

template <typename T>
constexpr mat<T, 3, 3>::mat(const mat4<T> & m) :
	x1(m.x1), y1(m.y1), z1(m.z1),
	x2(m.x2), y2(m.y2), z2(m.z2),
	x3(m.x3), y3(m.y3), z3(m.z3)
{}

template <typename T>
constexpr mat<T, 3, 3>::mat(
	const vec3<T> & v1,
	const vec3<T> & v2,
	const vec3<T> & v3
) :
	x1(v1.x), y1(v1.y), z1(v1.z),
	x2(v2.x), y2(v2.y), z2(v2.z),
	x3(v3.x), y3(v3.y), z3(v3.z)
{}



//------------------------------------------------------------------------------
// Assignment Operators



template <typename T>
inline mat3<T> & mat<T, 3, 3>::operator=(const mat3<T> & m) {
	x1 = m.x1; y1 = m.y1; z1 = m.z1;
	x2 = m.x2; y2 = m.y2; z2 = m.z2;
	x3 = m.x3; y3 = m.y3; z3 = m.z3;

	return *this;
}

template <typename T>
inline mat3<T> & mat<T, 3, 3>::operator=(mat3<T> && m) {
	x1 = m.x1; y1 = m.y1; z1 = m.z1;
	x2 = m.x2; y2 = m.y2; z2 = m.z2;
	x3 = m.x3; y3 = m.y3; z3 = m.z3;

	return *this;
}

template <typename T>
inline mat3<T> & mat<T, 3, 3>::operator=(const mat2<T> & m) {
	x1 = m.x1; y1 = m.y1; z1 = 0;
	x2 = m.x2; y2 = m.y2; z2 = 0;
	x3 = 0; y3 = 0; z3 = 1;

	return *this;

}

template <typename T>
inline mat3<T> & mat<T, 3, 3>::operator=(const mat4<T> & m) {
	x1 = m.x1; y1 = m.y1; z1 = m.z1;
	x2 = m.x2; y2 = m.y2; z2 = m.z2;
	x3 = m.x3; y3 = m.y3; z3 = m.z3;

	return *this;
}



//------------------------------------------------------------------------------
// Access Operators



template <typename T>
inline T & mat<T, 3, 3>::operator[](nat i) {
	return *(&x1 + i);
}



//------------------------------------------------------------------------------
// Arithmetic Assignment Operators



//--- add assign ---

template <typename T>
inline mat3<T> & operator+=(mat3<T> & m, const T & v) {
	return m = m + v;
}

template <typename T>
inline mat3<T> & operator+=(mat3<T> & m1, const mat3<T> & m2) {
	return m1 = m1 + m2;
}

//--- subtract assign ---

template <typename T>
inline mat3<T> & operator-=(mat3<T> & m, const T & v) {
	m = m - v;
}

template <typename T>
inline mat3<T> & operator-=(mat3<T> & m1, const mat3<T> & m2) {
	return m1 = m1 - m2;
}

//--- multiply assign ---

template <typename T>
inline mat3<T> & operator*=(mat3<T> & m, const T & v) {
	m = m * v;
}

template <typename T>
inline mat3<T> & operator*=(mat3<T> & m1, const mat3<T> & m2) {
	return m1 = m1 * m2;
}

//--- divide assign ---

template <typename T>
inline mat3<T> & operator/=(mat3<T> & m, const T & v) {
	m = m / v;
}

//--- pre increment ---

template <typename T>
inline mat3<T> & operator++(mat3<T> & m) {
	++m.x1; ++m.y1; ++m.z1;
	++m.x2; ++m.y2; ++m.z2;
	++m.x3; ++m.y3; ++m.z3;

	return m;
}

//--- post increment ---

template <typename T>
inline mat3<T> operator++(mat3<T> & m, int) {
	mat3 temp(m);
	++m;

	return temp;
}

//--- pre decrement ---

template <typename T>
inline mat3<T> & operator--(mat3<T> & m) {
	--m.x1; --m.y1; --m.z1;
	--m.x2; --m.y2; --m.z2;
	--m.x3; --m.y3; --m.z3;

	return m;
}

//--- post decrement ---

template <typename T>
inline mat3<T> operator--(mat3<T> & m, int) {
	mat3 temp(m);
	--m;

	return temp;
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- positive ---

template <typename T>
inline mat3<T> operator+(const mat3<T> & m) {
	return mat3<T>(
		+m.x1, +m.y1, +m.z1,
		+m.x2, +m.y2, +m.z2,
		+m.x3, +m.y3, +m.z3
	);
}

//--- negative ---

template <typename T>
inline mat3<T> operator-(const mat3<T> & m) {
	return mat3<T>(
		-m.x1, -m.y1, -m.z1,
		-m.x2, -m.y2, -m.z2,
		-m.x3, -m.y3, -m.z3
	);
}

//--- add ---

template <typename T>
inline mat3<T> operator+(const mat3<T> & m1, const mat3<T> & m2) {
	return mat3<T>(
		m1.x1 + m2.x1, m1.y1 + m2.y1, m1.z1 + m2.z1,
		m1.x2 + m2.x2, m1.y2 + m2.y2, m1.z2 + m2.z2,
		m1.x3 + m2.x3, m1.y3 + m2.y3, m1.z3 + m2.z3
	);
}

template <typename T>
inline mat3<T> operator+(const mat3<T> & m, const T & v) {
	return mat3<T>(
		m.x1 + v, m.y1 + v, m.z1 + v,
		m.x2 + v, m.y2 + v, m.z2 + v,
		m.x3 + v, m.y3 + v, m.z3 + v
	);
}

template <typename T>
inline mat3<T> operator+(const T & v, const mat3<T> & m) {
	return mat3<T>(
		v + m.x1, v + m.y1, v + m.z1,
		v + m.x2, v + m.y2, v + m.z2,
		v + m.x3, v + m.y3, v + m.z3
	);
}

//--- subtract ---

template <typename T>
inline mat3<T> operator-(const mat3<T> & m1, const mat3<T> & m2) {
	return mat3<T>(
		m1.x1 - m2.x1, m1.y1 - m2.y1, m1.z1 - m2.z1,
		m1.x2 - m2.x2, m1.y2 - m2.y2, m1.z2 - m2.z2,
		m1.x3 - m2.x3, m1.y3 - m2.y3, m1.z3 - m2.z3
	);
}

template <typename T>
inline mat3<T> operator-(const mat3<T> & m, const T & v) {
	return mat3<T>(
		m.x1 - v, m.y1 - v, m.z1 - v,
		m.x2 - v, m.y2 - v, m.z2 - v,
		m.x3 - v, m.y3 - v, m.z3 - v
	);
}

template <typename T>
inline mat3<T> operator-(const T & v, const mat3<T> & m) {
	return mat3<T>(
		v - m.x1, v - m.y1, v - m.z1,
		v - m.x2, v - m.y2, v - m.z2,
		v - m.x3, v - m.y3, v - m.z3
	);
}

//--- multiply ---

template <typename T>
inline mat3<T> operator*(const mat3<T> & m1, const mat3<T> & m2) {
	return mat3<T>(
		m1.x1 * m2.x1 + m1.x2 * m2.y1 + m1.x3 * m2.z1,
		m1.y1 * m2.x1 + m1.y2 * m2.y1 + m1.y3 * m2.z1,
		m1.z1 * m2.x1 + m1.z2 * m2.y1 + m1.z3 * m2.z1,

		m1.x1 * m2.x2 + m1.x2 * m2.y2 + m1.x3 * m2.z2,
		m1.y1 * m2.x2 + m1.y2 * m2.y2 + m1.y3 * m2.z2,
		m1.z1 * m2.x2 + m1.z2 * m2.y2 + m1.z3 * m2.z2,

		m1.x1 * m2.x3 + m1.x2 * m2.y3 + m1.x3 * m2.z3,
		m1.y1 * m2.x3 + m1.y2 * m2.y3 + m1.y3 * m2.z3,
		m1.z1 * m2.x3 + m1.z2 * m2.y3 + m1.z3 * m2.z3
	);
}

template <typename T>
inline mat3<T> operator*(const mat3<T> & m, const T & v) {
	return mat3<T>(
		m.x1 * v, m.y1 * v, m.z1 * v,
		m.x2 * v, m.y2 * v, m.z2 * v,
		m.x3 * v, m.y3 * v, m.z3 * v
	);
}

template <typename T>
inline mat3<T> operator*(const T & v, const mat3<T> & m) {
	return mat3<T>(
		v * m.x1, v * m.y1, v * m.z1,
		v * m.x2, v * m.y2, v * m.z2,
		v * m.x3, v * m.y3, v * m.z3
	);
}

template <typename T>
inline vec3<T> operator*(const mat3<T> & m, const vec3<T> & v) {
	return vec3<T>(
		v.x * m.x1 + v.y * m.x2 + v.z * m.x3,
		v.x * m.y1 + v.y * m.y2 + v.z * m.y3,
		v.x * m.z1 + v.y * m.z2 + v.z * m.z3
	);
}

//--- divide ---

template <typename T>
inline mat3<T> operator/(const mat3<T> & m, const T & v) {
	return mat3<T>(
		m.x1 / v, m.y1 / v, m.z1 / v,
		m.x2 / v, m.y2 / v, m.z2 / v,
		m.x3 / v, m.y3 / v, m.z3 / v
	);
}

template <typename T>
inline mat3<T> operator/(const T & v, const mat3<T> & m) {
	return mat3<T>(
		v / m.x1, v / m.y1, v / m.z1,
		v / m.x2, v / m.y2, v / m.z2,
		v / m.x3, v / m.y3, v / m.z3
	);
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T>
inline bool operator==(const mat3<T> & m1, const mat3<T> & m2) {
	return
		m1.x1 == m2.x1 && m1.y1 == m2.y1 && m1.z1 == m2.z1 &&
		m1.x2 == m2.x2 && m1.y2 == m2.y2 && m1.z2 == m2.z2 &&
		m1.x3 == m2.x3 && m1.y3 == m2.y3 && m1.z3 == m2.z3;
}

//--- not equal to ---

template <typename T>
inline bool operator!=(const mat3<T> & m1, const mat3<T> & m2) {
	return
		m1.x1 != m2.x1 || m1.y1 != m2.y1 || m1.z1 != m2.z1 ||
		m1.x2 != m2.x2 || m1.y2 != m2.y2 || m1.z2 != m2.z2 ||
		m1.x3 != m2.x3 || m1.y3 != m2.y3 || m1.z3 != m2.z3;
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string mat<T, 3, 3>::toString() const {
	return
		"[ " +
		std::to_string(x1) + " " + std::to_string(y1) + " " + std::to_string(z1) +
		" | " +
		std::to_string(x2) + " " + std::to_string(y2) + " " + std::to_string(z2) +
		" | " +
		std::to_string(x3) + " " + std::to_string(y3) + " " + std::to_string(z3) +
		" ]";
}



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const mat3<T> & m) {
	return os << m.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT4 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr mat<T, 4, 4>::mat() :
	x1(1), y1(0), z1(0), w1(0),
	x2(0), y2(1), z2(0), w2(0),
	x3(0), y3(0), z3(1), w3(0),
	x4(0), y4(0), z4(0), w4(1)
{}

template <typename T>
constexpr mat<T, 4, 4>::mat(const mat4<T> & m) :
	x1(m.x1), y1(m.y1), z1(m.z1), w1(m.w1),
	x2(m.x2), y2(m.y2), z2(m.z2), w2(m.w2),
	x3(m.x3), y3(m.y3), z3(m.z3), w3(m.w3),
	x4(m.x4), y4(m.y4), z4(m.z4), w4(m.w4)
{}

template <typename T>
constexpr mat<T, 4, 4>::mat(mat4<T> && m) :
	x1(m.x1), y1(m.y1), z1(m.z1), w1(m.w1),
	x2(m.x2), y2(m.y2), z2(m.z2), w2(m.w2),
	x3(m.x3), y3(m.y3), z3(m.z3), w3(m.w3),
	x4(m.x4), y4(m.y4), z4(m.z4), w4(m.w4)
{}

template <typename T>
constexpr mat<T, 4, 4>::mat(
	const T & x1, const T & y1, const T & z1, const T & w1,
	const T & x2, const T & y2, const T & z2, const T & w2,
	const T & x3, const T & y3, const T & z3, const T & w3,
	const T & x4, const T & y4, const T & z4, const T & w4
) :
	x1(x1), y1(y1), z1(z1), w1(w1),
	x2(x2), y2(y2), z2(z2), w2(w2),
	x3(x3), y3(y3), z3(z3), w3(w3),
	x4(x4), y4(y4), z4(z4), w4(w4)
{}

template <typename T>
constexpr mat<T, 4, 4>::mat(const mat2<T> & m) :
	x1(m.x1), y1(m.y1), z1(0), w1(0),
	x2(m.x2), y2(m.y2), z2(0), w2(0),
	x3(0), y3(0), z3(1), w3(0),
	x4(0), y4(0), z4(0), w4(1)
{}

template <typename T>
constexpr mat<T, 4, 4>::mat(const mat3<T> & m) :
	x1(m.x1), y1(m.y1), z1(m.z1), w1(0),
	x2(m.x2), y2(m.y2), z2(m.z2), w2(0),
	x3(m.x3), y3(m.y3), z3(m.z3), w3(0),
	x4(0), y4(0), z4(0), w4(1)
{}

template <typename T>
constexpr mat<T, 4, 4>::mat(
	const vec4<T> & v1,
	const vec4<T> & v2,
	const vec4<T> & v3,
	const vec4<T> & v4
) :
	x1(v1.x), y1(v1.y), z1(v1.z), w1(v1.w),
	x2(v2.x), y2(v2.y), z2(v2.z), w2(v2.w),
	x3(v3.x), y3(v3.y), z3(v3.z), w3(v3.w),
	x4(v4.x), y4(v4.y), z4(v4.z), w4(v4.w)
{}



//------------------------------------------------------------------------------
// Assignment Operators



template <typename T>
inline mat4<T> & mat<T, 4, 4>::operator=(const mat4<T> & m) {
	x1 = m.x1; y1 = m.y1; z1 = m.z1; w1 = m.w1;
	x2 = m.x2; y2 = m.y2; z2 = m.z2; w2 = m.w2;
	x3 = m.x3; y3 = m.y3; z3 = m.z3; w3 = m.w3;
	x4 = m.x4; y4 = m.y4; z4 = m.z4; w4 = m.w4;

	return *this;
}

template <typename T>
inline mat4<T> & mat<T, 4, 4>::operator=(mat4<T> && m) {
	x1 = m.x1; y1 = m.y1; z1 = m.z1; w1 = m.w1;
	x2 = m.x2; y2 = m.y2; z2 = m.z2; w2 = m.w2;
	x3 = m.x3; y3 = m.y3; z3 = m.z3; w3 = m.w3;
	x4 = m.x4; y4 = m.y4; z4 = m.z4; w4 = m.w4;

	return *this;
}

template <typename T>
inline mat4<T> & mat<T, 4, 4>::operator=(const mat2<T> & m) {
	x1 = m.x1; y1 = m.y1; z1 = 0; w1 = 0;
	x2 = m.x2; y2 = m.y2; z2 = 0; w2 = 0;
	x3 = 0; y3 = 0; z3 = 1; w3 = 0;
	x4 = 0; y4 = 0; z4 = 0; w4 = 1;

	return *this;
}

template <typename T>
inline mat4<T> & mat<T, 4, 4>::operator=(const mat3<T> & m) {
	x1 = m.x1; y1 = m.y1; z1 = m.z1; w1 = 0;
	x2 = m.x2; y2 = m.y2; z2 = m.z2; w2 = 0;
	x3 = m.x3; y3 = m.y3; z3 = m.z3; w3 = 0;
	x4 = 0; y4 = 0; z4 = 0; w4 = 1;

	return *this;
}



//------------------------------------------------------------------------------
// Access Operators



template <typename T>
inline T & mat<T, 4, 4>::operator[](nat i) {
	return *(&x1 + i);
}



//------------------------------------------------------------------------------
// Arithmetic Assignment Operators



//--- add assign ---

template <typename T>
inline mat4<T> & operator+=(mat4<T> & m, const T & v) {
	return m = m + v;
}

template <typename T>
inline mat4<T> & operator+=(mat4<T> & m1, const mat4<T> & m2) {
	return m1 = m1 + m2;
}

//--- subtract assign ---

template <typename T>
inline mat4<T> & operator-=(mat4<T> & m, const T & v) {
	m = m - v;
}

template <typename T>
inline mat4<T> & operator-=(mat4<T> & m1, const mat4<T> & m2) {
	return m1 = m1 - m2;
}

//--- multiply assign ---

template <typename T>
inline mat4<T> & operator*=(mat4<T> & m, const T & v) {
	m = m * v;
}

template <typename T>
inline mat4<T> & operator*=(mat4<T> & m1, const mat4<T> & m2) {
	return m1 = m1 * m2;
}

//--- divide assign ---

template <typename T>
inline mat4<T> & operator/=(mat4<T> & m, const T & v) {
	m = m / v;
}

//--- pre increment ---

template <typename T>
inline mat4<T> & operator++(mat4<T> & m) {
	++m.x1; ++m.y1; ++m.z1; ++m.w1;
	++m.x2; ++m.y2; ++m.z2; ++m.w2;
	++m.x3; ++m.y3; ++m.z3; ++m.w3;
	++m.x4; ++m.y4; ++m.z4; ++m.w4;

	return m;
}

//--- post increment ---

template <typename T>
inline mat4<T> operator++(mat4<T> & m, int) {
	mat4 temp(m);
	++m;

	return temp;
}

//--- pre decrement ---

template <typename T>
inline mat4<T> & operator--(mat4<T> & m) {
	--m.x1; --m.y1; --m.z1; --m.w1;
	--m.x2; --m.y2; --m.z2; --m.w2;
	--m.x3; --m.y3; --m.z3; --m.w3;
	--m.x4; --m.y4; --m.z4; --m.w4;

	return m;
}

//--- post decrement ---

template <typename T>
inline mat4<T> operator--(mat4<T> & m, int) {
	mat4 temp(m);
	--m;

	return temp;
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- positive ---

template <typename T>
inline mat4<T> operator+(const mat4<T> & m) {
	return mat4<T>(
		+m.x1, +m.y1, +m.z1, +m.w1,
		+m.x2, +m.y2, +m.z2, +m.w2,
		+m.x3, +m.y3, +m.z3, +m.w3,
		+m.x4, +m.y4, +m.z4, +m.w4
	);
}

//--- negative ---

template <typename T>
inline mat4<T> operator-(const mat4<T> & m) {
	return mat4<T>(
		-m.x1, -m.y1, -m.z1, -m.w1,
		-m.x2, -m.y2, -m.z2, -m.w2,
		-m.x3, -m.y3, -m.z3, -m.w3,
		-m.x4, -m.y4, -m.z4, -m.w4
	);
}

//--- add ---

template <typename T>
inline mat4<T> operator+(const mat4<T> & m1, const mat4<T> & m2) {
	return mat4<T>(
		m1.x1 + m2.x1, m1.y1 + m2.y1, m1.z1 + m2.z1, m1.w1 + m2.w1,
		m1.x2 + m2.x2, m1.y2 + m2.y2, m1.z2 + m2.z2, m1.w2 + m2.w2,
		m1.x3 + m2.x3, m1.y3 + m2.y3, m1.z3 + m2.z3, m1.w3 + m2.w3,
		m1.x4 + m2.x4, m1.y4 + m2.y4, m1.z4 + m2.z4, m1.w4 + m2.w4
	);
}

template <typename T>
inline mat4<T> operator+(const mat4<T> & m, const T & v) {
	return mat4<T>(
		m.x1 + v, m.y1 + v, m.z1 + v, m.w1 + v,
		m.x2 + v, m.y2 + v, m.z2 + v, m.w2 + v,
		m.x3 + v, m.y3 + v, m.z3 + v, m.w3 + v,
		m.x4 + v, m.y4 + v, m.z4 + v, m.w4 + v
	);
}

template <typename T>
inline mat4<T> operator+(const T & v, const mat4<T> & m) {
	return mat4<T>(
		v + m.x1, v + m.y1, v + m.z1, v + m.w1,
		v + m.x2, v + m.y2, v + m.z2, v + m.w2,
		v + m.x3, v + m.y3, v + m.z3, v + m.w3,
		v + m.x4, v + m.y4, v + m.z4, v + m.w4
	);
}

//--- subtract ---

template <typename T>
inline mat4<T> operator-(const mat4<T> & m1, const mat4<T> & m2) {
	return mat4<T>(
		m1.x1 - m2.x1, m1.y1 - m2.y1, m1.z1 - m2.z1, m1.w1 - m2.w1,
		m1.x2 - m2.x2, m1.y2 - m2.y2, m1.z2 - m2.z2, m1.w2 - m2.w2,
		m1.x3 - m2.x3, m1.y3 - m2.y3, m1.z3 - m2.z3, m1.w3 - m2.w3,
		m1.x4 - m2.x4, m1.y4 - m2.y4, m1.z4 - m2.z4, m1.w4 - m2.w4
	);
}

template <typename T>
inline mat4<T> operator-(const mat4<T> & m, const T & v) {
	return mat4<T>(
		m.x1 - v, m.y1 - v, m.z1 - v, m.w1 - v,
		m.x2 - v, m.y2 - v, m.z2 - v, m.w2 - v,
		m.x3 - v, m.y3 - v, m.z3 - v, m.w3 - v,
		m.x4 - v, m.y4 - v, m.z4 - v, m.w4 - v
	);
}

template <typename T>
inline mat4<T> operator-(const T & v, const mat4<T> & m) {
	return mat4<T>(
		v - m.x1, v - m.y1, v - m.z1, v - m.w1,
		v - m.x2, v - m.y2, v - m.z2, v - m.w2,
		v - m.x3, v - m.y3, v - m.z3, v - m.w3,
		v - m.x4, v - m.y4, v - m.z4, v - m.w4
	);
}

//--- multiply ---

template <typename T>
inline mat4<T> operator*(const mat4<T> & m1, const mat4<T> & m2) {
	return mat4<T>(
		m1.x1 * m2.x1 + m1.x2 * m2.y1 + m1.x3 * m2.z1 + m1.x4 * m2.w1,
		m1.y1 * m2.x1 + m1.y2 * m2.y1 + m1.y3 * m2.z1 + m1.y4 * m2.w1,
		m1.z1 * m2.x1 + m1.z2 * m2.y1 + m1.z3 * m2.z1 + m1.z4 * m2.w1,
		m1.w1 * m2.x1 + m1.w2 * m2.y1 + m1.w3 * m2.z1 + m1.w4 * m2.w1,

		m1.x1 * m2.x2 + m1.x2 * m2.y2 + m1.x3 * m2.z2 + m1.x4 * m2.w2,
		m1.y1 * m2.x2 + m1.y2 * m2.y2 + m1.y3 * m2.z2 + m1.y4 * m2.w2,
		m1.z1 * m2.x2 + m1.z2 * m2.y2 + m1.z3 * m2.z2 + m1.z4 * m2.w2,
		m1.w1 * m2.x2 + m1.w2 * m2.y2 + m1.w3 * m2.z2 + m1.w4 * m2.w2,

		m1.x1 * m2.x3 + m1.x2 * m2.y3 + m1.x3 * m2.z3 + m1.x4 * m2.w3,
		m1.y1 * m2.x3 + m1.y2 * m2.y3 + m1.y3 * m2.z3 + m1.y4 * m2.w3,
		m1.z1 * m2.x3 + m1.z2 * m2.y3 + m1.z3 * m2.z3 + m1.z4 * m2.w3,
		m1.w1 * m2.x3 + m1.w2 * m2.y3 + m1.w3 * m2.z3 + m1.w4 * m2.w3,

		m1.x1 * m2.x4 + m1.x2 * m2.y4 + m1.x3 * m2.z4 + m1.x4 * m2.w4,
		m1.y1 * m2.x4 + m1.y2 * m2.y4 + m1.y3 * m2.z4 + m1.y4 * m2.w4,
		m1.z1 * m2.x4 + m1.z2 * m2.y4 + m1.z3 * m2.z4 + m1.z4 * m2.w4,
		m1.w1 * m2.x4 + m1.w2 * m2.y4 + m1.w3 * m2.z4 + m1.w4 * m2.w4
	);
}

template <typename T>
inline mat4<T> operator*(const mat4<T> & m, const T & v) {
	return mat4<T>(
		m.x1 * v, m.y1 * v, m.z1 * v, m.w1 * v,
		m.x2 * v, m.y2 * v, m.z2 * v, m.w2 * v,
		m.x3 * v, m.y3 * v, m.z3 * v, m.w3 * v,
		m.x4 * v, m.y4 * v, m.z4 * v, m.w4 * v
	);
}

template <typename T>
inline mat4<T> operator*(const T & v, const mat4<T> & m) {
	return mat4<T>(
		v * m.x1, v * m.y1, v * m.z1, v * m.w1,
		v * m.x2, v * m.y2, v * m.z2, v * m.w2,
		v * m.x3, v * m.y3, v * m.z3, v * m.w3,
		v * m.x4, v * m.y4, v * m.z4, v * m.w4
	);
}

template <typename T>
inline vec4<T> operator*(const mat4<T> & m, const vec4<T> & v) {
	return vec4<T>(
		v.x * m.x1 + v.y * m.x2 + v.z * m.x3 + v.w * m.x4,
		v.x * m.y1 + v.y * m.y2 + v.z * m.y3 + v.w * m.y4,
		v.x * m.z1 + v.y * m.z2 + v.z * m.z3 + v.w * m.z4,
		v.x * m.w1 + v.y * m.w2 + v.z * m.w3 + v.w * m.w4
	);
}

//--- divide ---

template <typename T>
inline mat4<T> operator/(const mat4<T> & m, const T & v) {
	return mat4<T>(
		m.x1 / v, m.y1 / v, m.z1 / v, m.w1 / v,
		m.x2 / v, m.y2 / v, m.z2 / v, m.w2 / v,
		m.x3 / v, m.y3 / v, m.z3 / v, m.w3 / v,
		m.x4 / v, m.y4 / v, m.z4 / v, m.w4 / v
	);
}

template <typename T>
inline mat4<T> operator/(const T & v, const mat4<T> & m) {
	return mat4<T>(
		v / m.x1, v / m.y1, v / m.z1, v / m.w1,
		v / m.x2, v / m.y2, v / m.z2, v / m.w2,
		v / m.x3, v / m.y3, v / m.z3, v / m.w3,
		v / m.x4, v / m.y4, v / m.z4, v / m.w4
	);
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T>
inline bool operator==(const mat4<T> & m1, const mat4<T> & m2) {
	return
		m1.x1 == m2.x1 && m1.y1 == m2.y1 && m1.z1 == m2.z1 && m1.w1 == m2.w1 &&
		m1.x2 == m2.x2 && m1.y2 == m2.y2 && m1.z2 == m2.z2 && m1.w2 == m2.w2 &&
		m1.x3 == m2.x3 && m1.y3 == m2.y3 && m1.z3 == m2.z3 && m1.w3 == m2.w3 &&
		m1.x4 == m2.x4 && m1.y4 == m2.y4 && m1.z4 == m2.z4 && m1.w4 == m2.w4;
}

//--- not equal to ---

template <typename T>
inline bool operator!=(const mat4<T> & m1, const mat4<T> & m2) {
	return
		m1.x1 != m2.x1 || m1.y1 != m2.y1 || m1.z1 != m2.z1 || m1.w1 != m2.w1 ||
		m1.x2 != m2.x2 || m1.y2 != m2.y2 || m1.z2 != m2.z2 || m1.w2 != m2.w2 ||
		m1.x3 != m2.x3 || m1.y3 != m2.y3 || m1.z3 != m2.z3 || m1.w3 != m2.w3 ||
		m1.x4 != m2.x4 || m1.y4 != m2.y4 || m1.z4 != m2.z4 || m1.w4 != m2.w4;
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string mat<T, 4, 4>::toString() const {
	return
		"[ " +
		std::to_string(x1) + " " + std::to_string(y1) + " " + std::to_string(z1) + " " + std::to_string(w1) +
		" | " +
		std::to_string(x2) + " " + std::to_string(y2) + " " + std::to_string(z2) + " " + std::to_string(w2) +
		" | " +
		std::to_string(x3) + " " + std::to_string(y3) + " " + std::to_string(z3) + " " + std::to_string(w3) +
		" | " +
		std::to_string(x4) + " " + std::to_string(y4) + " " + std::to_string(z4) + " " + std::to_string(w4) +
		" ]";
}



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const mat4<T> & m) {
	return os << m.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT FUNCTIONS IMPLEMENTATION ----------------------------------------------------------------------------------------



//--- transpose ---

template <typename T>
inline mat2<T> trans(const mat2<T> & m) {
	return mat2<T>(
		m.x1, m.x2,
		m.y1, m.y2
	);
}

template <typename T>
inline mat3<T> trans(const mat3<T> & m) {
	return mat3<T>(
		m.x1, m.x2, m.x3,
		m.y1, m.y2, m.y3,
		m.z1, m.z2, m.z3
	);
}

template <typename T>
inline mat4<T> trans(const mat4<T> & m) {
	return mat4<T>(
		m.x1, m.x2, m.x3, m.x4,
		m.y1, m.y2, m.y3, m.y4,
		m.z1, m.z2, m.z3, m.z4,
		m.w1, m.w2, m.w3, m.w4
	);
}

//--- cofactor ---

template <typename T>
inline mat2<T> cof(const mat2<T> & m) {
	return mat2<T>(
		m.y2, -m.x2,
		-m.y1, m.x1
	);
}

template <typename T>
inline mat3<T> cof(const mat3<T> & m) {
	return mat3<T>(
		+(m.y2 * m.z3 - m.y3 * m.z2), -(m.x2 * m.z3 - m.x3 * m.z2), +(m.x2 * m.y3 - m.x3 * m.y2),
		-(m.y1 * m.z3 - m.y3 * m.z1), +(m.x1 * m.z3 - m.x3 * m.z1), -(m.x1 * m.y3 - m.x3 * m.y1),
		+(m.y1 * m.z2 - m.y2 * m.z1), -(m.x1 * m.z2 - m.x2 * m.z1), +(m.x1 * m.y2 - m.x2 * m.y1)
	);
}

template <typename T>
inline mat4<T> cof(const mat4<T> & m) {
	//T xy12(m.x1 * m.y2 - m.x2 * m.y1);
	//T xy13(m.x1 * m.y3 - m.x3 * m.y1);
	//T xy14(m.x1 * m.y4 - m.x4 * m.y1);
	//T xz12(m.x1 * m.z2 - m.x2 * m.z1);
	//T xz13(m.x1 * m.z3 - m.x3 * m.z1);
	//T xz14(m.x1 * m.z4 - m.x4 * m.z1);
	//T xw12(m.x1 * m.w2 - m.x2 * m.w1);
	//T xw13(m.x1 * m.w3 - m.x3 * m.w1);
	//T xw14(m.x1 * m.w4 - m.x4 * m.w1);
	//T xy23(m.x2 * m.y3 - m.x3 * m.y2);
	//T xy24(m.x2 * m.y4 - m.x4 * m.y2);
	//T xz23(m.x2 * m.z3 - m.x3 * m.z2);
	//T xz24(m.x2 * m.z4 - m.x4 * m.z2);
	//T xw23(m.x2 * m.w3 - m.x3 * m.w2);
	//T xw24(m.x2 * m.w4 - m.x4 * m.w2);
	T yz12(m.y1 * m.z2 - m.y2 * m.z1);
	T yz13(m.y1 * m.z3 - m.y3 * m.z1);
	T yz14(m.y1 * m.z4 - m.y4 * m.z1);
	T yw12(m.y1 * m.w2 - m.y2 * m.w1);
	T yw13(m.y1 * m.w3 - m.y3 * m.w1);
	T yw14(m.y1 * m.w4 - m.y4 * m.w1);
	//T xy34(m.x3 * m.y4 - m.x4 * m.y3);
	//T xz34(m.x3 * m.z4 - m.x4 * m.z3);
	//T xw34(m.x3 * m.w4 - m.x4 * m.w3);
	T yz23(m.y2 * m.z3 - m.y3 * m.z2);
	T yz24(m.y2 * m.z4 - m.y4 * m.z2);
	T yw23(m.y2 * m.w3 - m.y3 * m.w2);
	T yw24(m.y2 * m.w4 - m.y4 * m.w2);
	T zw12(m.z1 * m.w2 - m.z2 * m.w1);
	T zw13(m.z1 * m.w3 - m.z3 * m.w1);
	T zw14(m.z1 * m.w4 - m.z4 * m.w1);
	T yz34(m.y3 * m.z4 - m.y4 * m.z3);
	T yw34(m.y3 * m.w4 - m.y4 * m.w3);
	T zw23(m.z2 * m.w3 - m.z3 * m.w2);
	T zw24(m.z2 * m.w4 - m.z4 * m.w2);
	T zw34(m.z3 * m.w4 - m.z4 * m.w3);

	T xyz123(m.x1 * yz23 - m.x2 * yz13 + m.x3 * yz12);
	T xyz124(m.x1 * yz24 - m.x2 * yz14 + m.x4 * yz12);
	T xyz134(m.x1 * yz34 - m.x3 * yz14 + m.x4 * yz13);
	T xyw123(m.x1 * yw23 - m.x2 * yw13 + m.x3 * yw12);
	T xyw124(m.x1 * yw24 - m.x2 * yw14 + m.x4 * yw12);
	T xyw134(m.x1 * yw34 - m.x3 * yw14 + m.x4 * yw13);
	T xzw123(m.x1 * zw23 - m.x2 * zw13 + m.x3 * zw12);
	T xzw124(m.x1 * zw24 - m.x2 * zw14 + m.x4 * zw12);
	T xzw134(m.x1 * zw34 - m.x3 * zw14 + m.x4 * zw13);
	T xyz234(m.x2 * yz34 - m.x3 * yz24 + m.x4 * yz23);
	T xyw234(m.x2 * yw34 - m.x3 * yw24 + m.x4 * yw23);
	T xzw234(m.x2 * zw34 - m.x3 * zw24 + m.x4 * zw23);
	T yzw123(m.y1 * zw23 - m.y2 * zw13 + m.y3 * zw12);
	T yzw124(m.y1 * zw24 - m.y2 * zw14 + m.y4 * zw12);
	T yzw134(m.y1 * zw34 - m.y3 * zw14 + m.y4 * zw13);
	T yzw234(m.y2 * zw34 - m.y3 * zw24 + m.y4 * zw23);

	return mat4<T>(
		+yzw234, -xzw234, +xyw234, -xyz234,
		-yzw134, +xzw134, -xyw134, +xyz134,
		+yzw124, -xzw124, +xyw124, -xyz124,
		-yzw123, +xzw123, -xyw123, +xyz123
	);
}

//-- adjoint ---

template <typename T>
inline mat2<T> adj(const mat2<T> & m) {
	return trans(cof(m));

}

template <typename T>
inline mat3<T> adj(const mat3<T> & m) {
	return trans(cof(m));

}

template <typename T>
inline mat4<T> adj(const mat4<T> & m) {
	return trans(cof(m));
}

//--- determinant ---

template <typename T>
inline T det(const mat2<T> & m) {
	return
		+m.x1 * m.y2
		- m.x2 * m.y1;
}

template <typename T>
inline T det(const mat3<T> & m) {
	return
		+m.x1 * (m.y2 * m.z3 - m.y3 * m.z2)
		- m.x2 * (m.y1 * m.z3 - m.y3 * m.z1)
		+ m.x3 * (m.y1 * m.z2 - m.y2 * m.z1);
}

template <typename T>
inline T det(const mat4<T> & m) {
	T zw12 = m.z1 * m.w2 - m.z2 * m.w1;
	T zw13 = m.z1 * m.w3 - m.z3 * m.w1;
	T zw14 = m.z1 * m.w4 - m.z4 * m.w1;
	T zw23 = m.z2 * m.w3 - m.z3 * m.w2;
	T zw24 = m.z2 * m.w4 - m.z4 * m.w2;
	T zw34 = m.z3 * m.w4 - m.z4 * m.w3;

	T yzw123 = m.y1 * zw23 - m.y2 * zw13 + m.y3 * zw12;
	T yzw124 = m.y1 * zw24 - m.y2 * zw14 + m.y4 * zw12;
	T yzw134 = m.y1 * zw34 - m.y3 * zw14 + m.y4 * zw13;
	T yzw234 = m.y2 * zw34 - m.y3 * zw24 + m.y4 * zw23;

	return m.x1 * yzw234 - m.x2 * yzw134 + m.x3 * yzw124 - m.x4 * yzw123;
}

//--- inverse ---

template <typename T>
inline mat2<T> inv(const mat2<T> & m) {
	return adj(m) / det(m);
}

template <typename T>
inline mat3<T> inv(const mat3<T> & m) {
	return adj(m) / det(m);
}

template <typename T>
inline mat4<T> inv(const mat4<T> & m) {
	return adj(m) / det(m);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORMATIONS IMPLEMENTATION --------------------------------------------------------------------------------------



template <typename T>
inline mat2<T> translate(const vec1<T> & delta) {
	return mat2<T>(
		1, 0,
		delta, 1
	);
}

template <typename T>
inline mat3<T> translate(const vec2<T> & delta) {
	return mat3<T>(
		1, 0, 0,
		0, 1, 0,
		delta.x, delta.y, 1
	);
}

template <typename T>
inline mat4<T> translate(const vec3<T> & delta) {
	return mat4<T>(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		delta.x, delta.y, delta.z, 1
	);
}

template <typename T>
inline mat2<T> scale(const vec2<T> & scale) {
	return mat2<T>(
		scale.x, 0,
		0, scale.y
	);
}

template <typename T>
inline mat3<T> scale(const vec3<T> & scale) {
	return mat3<T>(
		scale.x, 0, 0,
		0, scale.y, 0,
		0, 0, scale.z
	);
}

template <typename T>
inline mat4<T> scale(const vec4<T> & scale) {
	return mat4<T>(
		scale.x, 0, 0, 0,
		0, scale.y, 0, 0,
		0, 0, scale.z, 0,
		0, 0, 0, scale.w
	);
}

template <typename T>
inline mat2<T> rotate(const T & theta) {
	T s = std::sin(theta);
	T c = std::cos(theta);

	return mat2<T>(
		c, s,
		-s, c
	);
}

template <typename T>
inline mat3<T> rotateX(const T & theta) {
	T s = std::sin(theta);
	T c = std::cos(theta);

	return mat3<T>(
		1, 0, 0,
		0, c, s,
		0, -s, c
	);
}

template <typename T>
inline mat3<T> rotateY(const T & theta) {
	T s = std::sin(theta);
	T c = std::cos(theta);

	return mat3<T>(
		c, 0, -s,
		0, 1, 0,
		s, 0, c
	);
}

template <typename T>
inline mat3<T> rotateZ(const T & theta) {
	T s = std::sin(theta);
	T c = std::cos(theta);

	return mat3<T>(
		c, s, 0,
		-s, c, 0,
		0, 0, 1
	);
}

template <typename T>
inline mat3<T> rotate(const vec3<T> & axis, const T & sinTheta, const T & cosTheta) {
	if (mag2(axis) == 0) { //can't rotate around 0 length fvector
		return mat3<T>();
	}

	return rotate_n(norm(axis), sinTheta, cosTheta);
}
template <typename T>
inline mat3<T> rotate_n(const vec3<T> & axis, const T & s, const T & c) {
	T cm = 1 - c;

	return mat3<T>(
		c + axis.x * axis.x * cm, axis.y * axis.x * cm + axis.z * s, axis.z * axis.x * cm - axis.y * s,
		axis.x * axis.y * cm - axis.z * s, c + axis.y * axis.y * cm, axis.z * axis.y * cm + axis.x * s,
		axis.x * axis.z * cm + axis.y * s, axis.y * axis.z * cm - axis.x * s, c + axis.z * axis.z * cm
	);
}

template <typename T>
inline mat3<T> rotate(const vec3<T> & axis, const T & theta) {
	return rotate(axis, std::sin(theta), std::cos(theta));
}
template <typename T>
inline mat3<T> rotate_n(const vec3<T> & axis, const T & theta) {
	return rotate_n(axis, std::sin(theta), std::cos(theta));
}

template <typename T>
inline mat3<T> euler(const vec3<T> & forward, const vec3<T> & up, const T & theta, const T & phi, const T & psi) {
	return euler_n(norm(forward), norm(up), theta, phi, psi);
}
template <typename T>
inline mat3<T> euler_n(const vec3<T> & forward, const vec3<T> & up, const T & theta, const T & phi, const T & psi) {
	return rotate_n(theta, up) * rotate_n(phi, cross(forward, up)) * rotate_n(psi, forward);
}

template <typename T>
inline mat3<T> align(const vec3<T> & v1, const vec3<T> & v2) {
	return align_n(norm(v1), norm(v2));
}
template <typename T>
inline mat3<T> align_n(const vec3<T> & v1, const vec3<T> & v2) {
	vec3<T> c = cross(v1, v2);
	T d = dot(v1, v2);

	return rotate(mag(c), d, c);
}

template <typename T>
inline mat3<T> align(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2) {
	return align_n(norm(forward1), norm(up1), norm(forward2), norm(up2));
}
template <typename T>
inline mat3<T> align_n(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2) {
	mat3 m = align_n(forward1, forward2);
	return align_n(m * up1, up2) * m;
}

template <typename T>
inline mat3<T> map(const vec3<T> & x1, const vec3<T> & y1, const vec3<T> & z1, const vec3<T> & x2, const vec3<T> & y2, const vec3<T> & z2) {
	return map_n(norm(x1), norm(y1), norm(z1), norm(x2), norm(y2), norm(z2));
}
template <typename T>
inline mat3<T> map_n(const vec3<T> & x1, const vec3<T> & y1, const vec3<T> & z1, const vec3<T> & x2, const vec3<T> & y2, const vec3<T> & z2) {
	mat3 A(x1, y1, z1);
	mat3 B(x2, y2, z2);

	return trans(B) * A;
}

template <typename T>
inline mat3<T> mapTo(const vec3<T> & x, const vec3<T> & y, const vec3<T> & z) {
	return mapTo_n(norm(x), norm(y), norm(z));
}
template <typename T>
inline mat3<T> mapTo_n(const vec3<T> & x, const vec3<T> & y, const vec3<T> & z) {
	return trans(mat3<T>(x, y, z));
}

template <typename T>
inline mat3<T> mapFrom(const vec3<T> & x, const vec3<T> & y, const vec3<T> & z) {
	return mapFrom_n(norm(x), norm(y), norm(z));
}
template <typename T>
inline mat3<T> mapFrom_n(const vec3<T> & x, const vec3<T> & y, const vec3<T> & z) {
	return mat3<T>(x, y, z);
}

template <typename T>
inline mat3<T> mapAny(const vec3<T> & x1, const vec3<T> & y1, const vec3<T> & z1, const vec3<T> & x2, const vec3<T> & y2, const vec3<T> & z2) {
	mat3 A(x1, y1, z1);
	mat3 B(x2, y2, z2);

	return inv(B) * A;
}

template <typename T>
inline mat4<T> ortho(const T & width, const T & height, const T & near, const T & far) {
	return mat4<T>(
		2 / width, 0, 0, 0,
		0, 2 / height, 0, 0,
		0, 0, 2 / (near - far), 0,
		0, 0, (far + near) / (near - far), 1
	);
}

template <typename T>
inline mat4<T> orthoAsym(const T & left, const T & right, const T & bottom, const T & top, const T & near, const T & far) {
	return mat4<T>(
		2 / (right + left), 0, 0, 0,
		0, 2 / (top + bottom), 0, 0,
		0, 0, 2 / (near - far), 0,
		(right - left) / (-right - left), (top - bottom) / (-top - bottom), (far + near) / (near - far), 1
	);
}

template <typename T>
inline mat4<T> perspective(const T & fov, const T & aspectRatio, const T & near, const T & far) {
	T near_top = 1 / std::tan(fov / 2);

	return mat4<T>(
		near_top / aspectRatio, 0, 0, 0,
		0, near_top, 0, 0,
		0, 0, (far + near) / (near - far), -1,
		0, 0, 2 * far * near / (near - far), 0
	);
}

template <typename T>
inline mat4<T> perspectiveAsym(const T & fovLeft, const T & fovRight, const T & fovBottom, const T & fovTop, const T & near, const T & far) {
	T left = near * -std::tan(fovLeft);
	T right = near * std::tan(fovRight);
	T bottom = near * -std::tan(fovBottom);
	T top = near * std::tan(fovTop);

	return mat4<T>(
		2 * near / (right - left), 0, 0, 0,
		0, 2 * near / (top - bottom), 0, 0,
		(right + left) / (right - left), (top + bottom) / (top - bottom), (far + near) / (near - far), -1,
		0, 0, 2 * far * near / (near - far), 0
	);
}

template <typename T>
inline mat4<T> view(const vec3<T> & camPos, const vec3<T> & camDir, const vec3<T> & camUp) {
	vec3<T> Z = -norm(camDir);
	vec3<T> Y = norm(camUp);
	vec3<T> X = cross(Y, Z);
	vec3<T> P = -camPos;

	return mat4<T>(mapTo_n(X, Y, Z)) * translate(P);
}



}
