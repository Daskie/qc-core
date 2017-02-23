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



template <nat t_m, nat t_n>
struct mat;



using mat2 = mat<2, 2>;
using mat3 = mat<3, 3>;
using mat4 = mat<4, 4>;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT2 ----------------------------------------------------------------------------------------------------------------



template <>
struct mat<2, 2> {

	static constexpr nat t_m = 2, t_n = 2;

	union {
		struct {
			float x1, y1;
			float x2, y2;
		};
	};

	//--- constructors ---

	constexpr mat();
	constexpr mat(const mat2 & m);
	constexpr mat(mat2 && m);

	constexpr mat(
		float x1, float y1,
		float x2, float y2
	);
	constexpr explicit mat(const mat3 & m);
	constexpr explicit mat(const mat4 & m);
	constexpr mat(
		const fvec2 & v1,
		const fvec2 & v2
	);

	//--- destructor ---

	~mat() {
		static_assert(std::is_standard_layout<mat<2, 2>>::value, "mat<2, 2> must be of standard layout");
		static_assert(sizeof(mat<2, 2>) == 4 * sizeof(float), "mat<2, 2> must be equal in size to 4 floats");
	}

	//--- assignment operators ---

	mat2 & operator=(const mat2 & m);
	mat2 & operator=(mat2 && m);

	mat2 & operator=(const mat3 & m);
	mat2 & operator=(const mat4 & m);

	//--- access operators ---

	float & operator[](nat i);

	//--- arithmetic assignment operators ---

	friend mat2 & operator+=(mat2 & m, float v);
	friend mat2 & operator+=(mat2 & m1, const mat2 & m2);

	friend mat2 & operator-=(mat2 & m, float v);
	friend mat2 & operator-=(mat2 & m1, const mat2 & m2);

	friend mat2 & operator*=(mat2 & m, float v);
	friend mat2 & operator*=(mat2 & m1, const mat2 & m2);

	friend mat2 & operator/=(mat2 & m, float v);

	friend mat2 & operator++(mat2 & m);
	friend mat2 operator++(mat2 & m, int);

	friend mat2 & operator--(mat2 & m);
	friend mat2 operator--(mat2 & m, int);

	//--- arithmetic operators ---

	friend mat2 operator+(const mat2 & m);

	friend mat2 operator-(const mat2 & m);

	friend mat2 operator+(const mat2 & m1, const mat2 & m2);
	friend mat2 operator+(const mat2 & m1, float v);
	friend mat2 operator+(float v, const mat2 & m1);

	friend mat2 operator-(const mat2 & m1, const mat2 & m2);
	friend mat2 operator-(const mat2 & m1, float v);
	friend mat2 operator-(float v, const mat2 & m1);

	friend mat2 operator*(const mat2 & m1, const mat2 & m2);
	friend mat2 operator*(const mat2 & m1, float v);
	friend mat2 operator*(float v, const mat2 & m1);
	friend fvec2 operator*(const mat2 & m1, const fvec2 & v);

	friend mat2 operator/(const mat2 & m1, float v);
	friend mat2 operator/(float v, const mat2 & m);

	//--- comparison operators ---

	friend bool operator==(const mat2 & m1, const mat2 & m2);
	friend bool operator!=(const mat2 & m1, const mat2 & m2);

	//--- other ---

	std::string toString() const;

	friend std::ostream & operator<<(std::ostream & os, const mat2 & m);

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT3 ----------------------------------------------------------------------------------------------------------------



template <>
struct mat<3, 3> {

	static constexpr nat t_m = 3, t_n = 3;

	union {
		struct {
			float x1, y1, z1;
			float x2, y2, z2;
			float x3, y3, z3;
		};
	};

	//--- constructors ---

	constexpr mat();
	constexpr mat(const mat3 & m);
	constexpr mat(mat3 && m);

	constexpr mat(
		float x1, float y1, float z1,
		float x2, float y2, float z2,
		float x3, float y3, float z3
	);
	constexpr explicit mat(const mat2 & m);
	constexpr explicit mat(const mat4 & m);
	constexpr mat(
		const fvec3 & v1,
		const fvec3 & v2,
		const fvec3 & v
	);

	//--- destructor ---

	~mat() {
		static_assert(std::is_standard_layout<mat<3, 3>>::value, "mat<3, 3> must be of standard layout");
		static_assert(sizeof(mat<3, 3>) == 9 * sizeof(float), "mat<3, 3> must be equal in size to 9 floats");
	}

	//--- assignment operators ---

	mat3 & operator=(const mat3 & m);
	mat3 & operator=(mat3 && m);

	mat3 & operator=(const mat2 & m);
	mat3 & operator=(const mat4 & m);

	//--- access operators ---

	float & operator[](nat i);

	//--- arithmetic assignment operators ---

	friend mat3 & operator+=(mat3 & m, float v);
	friend mat3 & operator+=(mat3 & m1, const mat3 & m2);

	friend mat3 & operator-=(mat3 & m, float v);
	friend mat3 & operator-=(mat3 & m1, const mat3 & m2);

	friend mat3 & operator*=(mat3 & m, float v);
	friend mat3 & operator*=(mat3 & m1, const mat3 & m2);

	friend mat3 & operator/=(mat3 & m, float v);

	friend mat3 & operator++(mat3 & m);
	friend mat3 operator++(mat3 & m, int);

	friend mat3 & operator--(mat3 & m);
	friend mat3 operator--(mat3 & m, int);

	//--- arithmetic operators ---

	friend mat3 operator+(const mat3 & m);

	friend mat3 operator-(const mat3 & m);

	friend mat3 operator+(const mat3 & m1, const mat3 & m2);
	friend mat3 operator+(const mat3 & m1, float v);
	friend mat3 operator+(float v, const mat3 & m1);

	friend mat3 operator-(const mat3 & m1, const mat3 & m2);
	friend mat3 operator-(const mat3 & m1, float v);
	friend mat3 operator-(float v, const mat3 & m1);

	friend mat3 operator*(const mat3 & m1, const mat3 & m2);
	friend mat3 operator*(const mat3 & m1, float v);
	friend mat3 operator*(float v, const mat3 & m1);
	friend fvec3 operator*(const mat3 & m1, const fvec3 & v);

	friend mat3 operator/(const mat3 & m1, float v);
	friend mat3 operator/(float v, const mat3 & m1);

	//--- comparison operators ---

	friend bool operator==(const mat3 & m1, const mat3 & m2);

	friend bool operator!=(const mat3 & m1, const mat3 & m2);

	//--- other ---

	std::string toString() const;

	friend std::ostream & operator<<(std::ostream & os, const mat3 & m);

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT4 ----------------------------------------------------------------------------------------------------------------



template <>
struct mat<4, 4> {

	static constexpr nat t_m = 4, t_n = 4;

	union {
		struct {
			float x1, y1, z1, w1;
			float x2, y2, z2, w2;
			float x3, y3, z3, w3;
			float x4, y4, z4, w4;
		};
	};

	//--- constructors ---

	constexpr mat();
	constexpr mat(const mat4 & m);
	constexpr mat(mat4 && m);

	constexpr mat(
		float x1, float y1, float z1, float w1,
		float x2, float y2, float z2, float w2,
		float x3, float y3, float z3, float w3,
		float x4, float y4, float z4, float w4
	);
	constexpr explicit mat(const mat2 & m);
	constexpr explicit mat(const mat3 & m);
	constexpr mat(
		const fvec4 & v1,
		const fvec4 & v2,
		const fvec4 & v3,
		const fvec4 & v4
	);

	//--- destructor ---

	~mat() {
		static_assert(std::is_standard_layout<mat<4, 4>>::value, "mat<4, 4> must be of standard layout");
		static_assert(sizeof(mat<4, 4>) == 16 * sizeof(float), "mat<4, 4> must be equal in size to 16 floats");
	}

	//--- assignment operators ---

	mat4 & operator=(const mat4 & m);
	mat4 & operator=(mat4 && m);

	mat4 & operator=(const mat2 & m);
	mat4 & operator=(const mat3 & m);

	//--- access operators ---

	float & operator[](nat i);

	//--- arithmetic assignment operators ---

	friend mat4 & operator+=(mat4 & m, float v);
	friend mat4 & operator+=(mat4 & m1, const mat4 & m2);

	friend mat4 & operator-=(mat4 & m, float v);
	friend mat4 & operator-=(mat4 & m1, const mat4 & m2);

	friend mat4 & operator*=(mat4 & m, float v);
	friend mat4 & operator*=(mat4 & m1, const mat4 & m2);

	friend mat4 & operator/=(mat4 & m, float v);

	friend mat4 & operator++(mat4 & m);
	friend mat4 operator++(mat4 & m, int);

	friend mat4 & operator--(mat4 & m);
	friend mat4 operator--(mat4 & m, int);

	//--- arithmetic operators ---

	friend mat4 operator+(const mat4 & m);

	friend mat4 operator-(const mat4 & m);

	friend mat4 operator+(const mat4 & m1, const mat4 & m2);
	friend mat4 operator+(const mat4 & m1, float v);
	friend mat4 operator+(float v, const mat4 & m1);

	friend mat4 operator-(const mat4 & m1, const mat4 & m2);
	friend mat4 operator-(const mat4 & m1, float v);
	friend mat4 operator-(float v, const mat4 & m1);

	friend mat4 operator*(const mat4 & m1, const mat4 & m2);
	friend mat4 operator*(const mat4 & m1, float v);
	friend mat4 operator*(float v, const mat4 & m1);
	friend fvec4 operator*(const mat4 & m1, const fvec4 & v);

	friend mat4 operator/(const mat4 & m1, float v);
	friend mat4 operator/(float v, const mat4 & m1);

	//--- comparison operators ---

	friend bool operator==(const mat4 & m1, const mat4 & m2);

	friend bool operator!=(const mat4 & m1, const mat4 & m2);

	//--- other ---

	std::string toString() const;

	friend std::ostream & operator<<(std::ostream & os, const mat4 & m);

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT FUNCTIONS -------------------------------------------------------------------------------------------------------



mat2 trans(const mat2 & m1);
mat3 trans(const mat3 & m1);
mat4 trans(const mat4 & m1);

mat2 cof(const mat2 & m1);
mat3 cof(const mat3 & m1);
mat4 cof(const mat4 & m1);

mat2 adj(const mat2 & m1);
mat3 adj(const mat3 & m1);
mat4 adj(const mat4 & m1);

float det(const mat2 & m1);
float det(const mat3 & m1);
float det(const mat4 & m1);

mat2 inv(const mat2 & m1);
mat3 inv(const mat3 & m1);
mat4 inv(const mat4 & m1);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORMATIONS -----------------------------------------------------------------------------------------------------



mat2 translate(float delta);
mat3 translate(const fvec2 & delta);
mat4 translate(const fvec3 & delta);

mat2 scale(const fvec2 & scale);
mat3 scale(const fvec3 & scale);
mat4 scale(const fvec4 & scale);

mat2 rotate(float theta);
mat3 rotateX(float theta);
mat3 rotateY(float theta);
mat3 rotateZ(float theta);

mat3 rotate(float sinTheta, float cosTheta, const fvec3 & axis);
mat3 rotate_n(float s, float c, const fvec3 & m1);

mat3 rotate(float theta, const fvec3 & axis);
mat3 rotate_n(float theta, const fvec3 & axis);

//theta: thumb points up, phi: right, psi: forward
mat3 euler(const fvec3 & forward, const fvec3 & up, float theta, float phi, float psi);
mat3 euler_n(const fvec3 & forward, const fvec3 & up, float theta, float phi, float psi);

mat3 align(const fvec3 & v1, const fvec3 & v2);
mat3 align_n(const fvec3 & v1, const fvec3 & v2);

//expects orthogonal fvectors
mat3 align(const fvec3 & forward1, const fvec3 & up1, const fvec3 & forward2, const fvec3 & up2);
mat3 align_n(const fvec3 & forward1, const fvec3 & up1, const fvec3 & forward2, const fvec3 & up2);

//expects ortho-normal fvectors!!! x, y, and z are the axes
mat3 map(const fvec3 & x1, const fvec3 & y1, const fvec3 & z1, const fvec3 & x2, const fvec3 & y2, const fvec3 & z2);
mat3 map_n(const fvec3 & x1, const fvec3 & y1, const fvec3 & z1, const fvec3 & x2, const fvec3 & y2, const fvec3 & z2);

mat3 mapTo(const fvec3 & x, const fvec3 & y, const fvec3 & z);
mat3 mapTo_n(const fvec3 & x, const fvec3 & y, const fvec3 & z);

mat3 mapFrom(const fvec3 & x, const fvec3 & y, const fvec3 & z);
mat3 mapFrom_n(const fvec3 & x, const fvec3 & y, const fvec3 & z);

mat3 mapAny(const fvec3 & x1, const fvec3 & y1, const fvec3 & z1, const fvec3 & x2, const fvec3 & y2, const fvec3 & z2);

mat4 ortho(float w, float h, float n, float f);
mat4 orthoAsym(float l, float r, float b, float t, float n, float f);

//fov is angle in radians between top and bottom planes, aspectRatio is screen width / height, zNear is distance to near plane, zFar is distance to far plane
mat4 perspective(float fov, float a, float n, float f);
//fovNX is angle between center and left plane, fovPX between center and right, fovNY between center and bottom, fovPY between center and top
mat4 perspectiveAsym(float fovNX, float fovPX, float fovNY, float fovPY, float n, float f);

//camUp should be perpendicular to camDir!!!
mat4 view(const fvec3 & camPos, const fvec3 & camDir, const fvec3 & camUp);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT2 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



constexpr mat<2, 2>::mat() :
	x1(1.0f), y1(0.0f),
	x2(0.0f), y2(1.0f)
{}

constexpr mat<2, 2>::mat(const mat2 & m) :
	x1(m.x1), y1(m.y1),
	x2(m.x2), y2(m.y2)
{}

constexpr mat<2, 2>::mat(mat2 && m) :
	x1(m.x1), y1(m.y1),
	x2(m.x2), y2(m.y2)
{}

constexpr mat<2, 2>::mat(
	float x1, float y1,
	float x2, float y2
) :
	x1(x1), y1(y1),
	x2(x2), y2(y2)
{}

constexpr mat<2, 2>::mat(const mat3 & m) :
	x1(m.x1), y1(m.y1),
	x2(m.x2), y2(m.y2)
{}

constexpr mat<2, 2>::mat(const mat4 & m) :
	x1(m.x1), y1(m.y1),
	x2(m.x2), y2(m.y2)
{}

constexpr mat<2, 2>::mat(
	const fvec2 & v1,
	const fvec2 & v2
) :
	x1(v1.x), y1(v1.y),
	x2(v2.x), y2(v2.y)
{}



//------------------------------------------------------------------------------
// Assignment Operators



inline mat2 & mat<2, 2>::operator=(const mat2 & m) {
	x1 = m.x1; y1 = m.y1;
	x2 = m.x2; y2 = m.y2;
	return *this;
}

inline mat2 & mat<2, 2>::operator=(mat2 && m) {
	x1 = m.x1; y1 = m.y1;
	x2 = m.x2; y2 = m.y2;
	return *this;
}

inline mat2 & mat<2, 2>::operator=(const mat3 & m) {
	x1 = m.x1; y1 = m.y1;
	x2 = m.x2; y2 = m.y2;
	return *this;
}

inline mat2 & mat<2, 2>::operator=(const mat4 & m) {
	x1 = m.x1; y1 = m.y1;
	x2 = m.x2; y2 = m.y2;
	return *this;
}



//------------------------------------------------------------------------------
// Access Operators



inline float & mat<2, 2>::operator[](nat i) {
	return *(&x1 + i);
}



//------------------------------------------------------------------------------
// Arithmetic Assignment Operators



//--- add assign ---

inline mat2 & operator+=(mat2 & m, float v) {
	return m = m + v;
}

inline mat2 & operator+=(mat2 & m1, const mat2 & m2) {
	return m1 = m1 + m2;
}

//--- subtract assign ---

inline mat2 & operator-=(mat2 & m, float v) {
	m = m - v;
}

inline mat2 & operator-=(mat2 & m1, const mat2 & m2) {
	return m1 = m1 - m2;
}

//--- multiply assign ---

inline mat2 & operator*=(mat2 & m, float v) {
	m = m * v;
}

inline mat2 & operator*=(mat2 & m1, const mat2 & m2) {
	return m1 = m1 * m2;
}

//--- divide assign ---

inline mat2 & operator/=(mat2 & m, float v) {
	m = m / v;
}

//--- pre increment ---

inline mat2 & operator++(mat2 & m) {
	++m.x1; ++m.y1;
	++m.x2; ++m.y2;

	return m;
}

//--- post increment ---

inline mat2 operator++(mat2 & m, int) {
	mat2 temp(m);
	++m;

	return temp;
}

//--- pre decrement ---

inline mat2 & operator--(mat2 & m) {
	--m.x1; --m.y1;
	--m.x2; --m.y2;

	return m;
}

//--- post decrement ---

inline mat2 operator--(mat2 & m, int) {
	mat2 temp(m);
	--m;

	return temp;
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- positive ---

inline mat2 operator+(const mat2 & m) {
	return mat2(
		+m.x1, +m.y1,
		+m.x2, +m.y2
	);
}

//--- negative ---

inline mat2 operator-(const mat2 & m) {
	return mat2(
		-m.x1, -m.y1,
		-m.x2, -m.y2
	);
}

//--- add ---

inline mat2 operator+(const mat2 & m1, const mat2 & m2) {
	return mat2(
		m1.x1 + m2.x1, m1.y1 + m2.y1,
		m1.x2 + m2.x2, m1.y2 + m2.y2
	);
}

inline mat2 operator+(const mat2 & m1, float v) {
	return mat2(
		m1.x1 + v, m1.y1 + v,
		m1.x2 + v, m1.y2 + v
	);
}

inline mat2 operator+(float v, const mat2 & m1) {
	return mat2(
		v + m1.x1, v + m1.y1,
		v + m1.x2, v + m1.y2
	);
}

//--- subtract ---

inline mat2 operator-(const mat2 & m1, const mat2 & m2) {
	return mat2(
		m1.x1 - m2.x1, m1.y1 - m2.y1,
		m1.x2 - m2.x2, m1.y2 - m2.y2
	);
}

inline mat2 operator-(const mat2 & m1, float v) {
	return mat2(
		m1.x1 - v, m1.y1 - v,
		m1.x2 - v, m1.y2 - v
	);
}

inline mat2 operator-(float v, const mat2 & m1) {
	return mat2(
		v - m1.x1, v - m1.y1,
		v - m1.x2, v - m1.y2
	);
}

//--- multiply ---

inline mat2 operator*(const mat2 & m1, const mat2 & m2) {
	return mat2(
		m1.x1 * m2.x1 + m1.x2 * m2.y1,
		m1.y1 * m2.x1 + m1.y2 * m2.y1,

		m1.x1 * m2.x2 + m1.x2 * m2.y2,
		m1.y1 * m2.x2 + m1.y2 * m2.y2
	);
}

inline mat2 operator*(const mat2 & m1, float v) {
	return mat2(
		m1.x1 * v, m1.y1 * v,
		m1.x2 * v, m1.y2 * v
	);
}

inline mat2 operator*(float v, const mat2 & m1) {
	return mat2(
		v * m1.x1, v * m1.y1,
		v * m1.x2, v * m1.y2
	);
}

inline fvec2 operator*(const mat2 & m1, const fvec2 & v) {
	return fvec2(
		v.x * m1.x1 + v.y * m1.x2,
		v.x * m1.y1 + v.y * m1.y2
	);
}

//--- divide ---

inline mat2 operator/(const mat2 & m1, float v) {
	return mat2(
		m1.x1 / v, m1.y1 / v,
		m1.x2 / v, m1.y2 / v
	);
}

inline mat2 operator/(float v, const mat2 & m) {
	return mat2(
		v / m.x1, v / m.y1,
		v / m.x2, v / m.y2
	);
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

inline bool operator==(const mat2 & m1, const mat2 & m2) {
	return
		m1.x1 == m2.x1 && m1.y1 == m2.y1 &&
		m1.x2 == m2.x2 && m1.y2 == m2.y2;
}

//--- not equal to ---

inline bool operator!=(const mat2 & m1, const mat2 & m2) {
	return
		m1.x1 != m2.x1 || m1.y1 != m2.y1 ||
		m1.x2 != m2.x2 || m1.y2 != m2.y2;
}



//------------------------------------------------------------------------------
// Other



inline std::string mat<2, 2>::toString() const {
	return
		"[ " +
		std::to_string(x1) + " " + std::to_string(y1) +
		" | " +
		std::to_string(x2) + " " + std::to_string(y2) +
		" ]";
}



inline std::ostream & operator<<(std::ostream & os, const mat2 & m) {
	return os << m.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT3 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



constexpr mat<3, 3>::mat() :
	x1(1.0f), y1(0.0f), z1(0.0f),
	x2(0.0f), y2(1.0f), z2(0.0f),
	x3(0.0f), y3(0.0f), z3(1.0f)
{}

constexpr mat<3, 3>::mat(const mat3 & m) :
	x1(m.x1), y1(m.y1), z1(m.z1),
	x2(m.x2), y2(m.y2), z2(m.z2),
	x3(m.x3), y3(m.y3), z3(m.z3)
{}

constexpr mat<3, 3>::mat(mat3 && m) :
	x1(m.x1), y1(m.y1), z1(m.z1),
	x2(m.x2), y2(m.y2), z2(m.z2),
	x3(m.x3), y3(m.y3), z3(m.z3)
{}

constexpr mat<3, 3>::mat(
	float x1, float y1, float z1,
	float x2, float y2, float z2,
	float x3, float y3, float z3
) :
	x1(x1), y1(y1), z1(z1),
	x2(x2), y2(y2), z2(z2),
	x3(x3), y3(y3), z3(z3)
{}

constexpr mat<3, 3>::mat(const mat2 & m) :
	x1(m.x1), y1(m.y1), z1(0.0f),
	x2(m.x2), y2(m.y2), z2(0.0f),
	x3(0.0f), y3(0.0f), z3(1.0f)
{}

constexpr mat<3, 3>::mat(const mat4 & m) :
	x1(m.x1), y1(m.y1), z1(m.z1),
	x2(m.x2), y2(m.y2), z2(m.z2),
	x3(m.x3), y3(m.y3), z3(m.z3)
{}

constexpr mat<3, 3>::mat(
	const fvec3 & v1,
	const fvec3 & v2,
	const fvec3 & v3
) :
	x1(v1.x), y1(v1.y), z1(v1.z),
	x2(v2.x), y2(v2.y), z2(v2.z),
	x3(v3.x), y3(v3.y), z3(v3.z)
{}



//------------------------------------------------------------------------------
// Assignment Operators



inline mat3 & mat<3, 3>::operator=(const mat3 & m) {
	x1 = m.x1; y1 = m.y1; z1 = m.z1;
	x2 = m.x2; y2 = m.y2; z2 = m.z2;
	x3 = m.x3; y3 = m.y3; z3 = m.z3;

	return *this;
}

inline mat3 & mat<3, 3>::operator=(mat3 && m) {
	x1 = m.x1; y1 = m.y1; z1 = m.z1;
	x2 = m.x2; y2 = m.y2; z2 = m.z2;
	x3 = m.x3; y3 = m.y3; z3 = m.z3;

	return *this;
}

inline mat3 & mat<3, 3>::operator=(const mat2 & m) {
	x1 = m.x1; y1 = m.y1; z1 = 0.0f;
	x2 = m.x2; y2 = m.y2; z2 = 0.0f;
	x3 = 0.0f; y3 = 0.0f; z3 = 1.0f;

	return *this;

}

inline mat3 & mat<3, 3>::operator=(const mat4 & m) {
	x1 = m.x1; y1 = m.y1; z1 = m.z1;
	x2 = m.x2; y2 = m.y2; z2 = m.z2;
	x3 = m.x3; y3 = m.y3; z3 = m.z3;

	return *this;
}



//------------------------------------------------------------------------------
// Access Operators



inline float & mat<3, 3>::operator[](nat i) {
	return *(&x1 + i);
}



//------------------------------------------------------------------------------
// Arithmetic Assignment Operators



//--- add assign ---

inline mat3 & operator+=(mat3 & m, float v) {
	return m = m + v;
}

inline mat3 & operator+=(mat3 & m1, const mat3 & m2) {
	return m1 = m1 + m2;
}

//--- subtract assign ---

inline mat3 & operator-=(mat3 & m, float v) {
	m = m - v;
}

inline mat3 & operator-=(mat3 & m1, const mat3 & m2) {
	return m1 = m1 - m2;
}

//--- multiply assign ---

inline mat3 & operator*=(mat3 & m, float v) {
	m = m * v;
}

inline mat3 & operator*=(mat3 & m1, const mat3 & m2) {
	return m1 = m1 * m2;
}

//--- divide assign ---

inline mat3 & operator/=(mat3 & m, float v) {
	m = m / v;
}

//--- pre increment ---

inline mat3 & operator++(mat3 & m) {
	++m.x1; ++m.y1; ++m.z1;
	++m.x2; ++m.y2; ++m.z2;
	++m.x3; ++m.y3; ++m.z3;

	return m;
}

//--- post increment ---

inline mat3 operator++(mat3 & m, int) {
	mat3 temp(m);
	++m;

	return temp;
}

//--- pre decrement ---

inline mat3 & operator--(mat3 & m) {
	--m.x1; --m.y1; --m.z1;
	--m.x2; --m.y2; --m.z2;
	--m.x3; --m.y3; --m.z3;

	return m;
}

//--- post decrement ---

inline mat3 operator--(mat3 & m, int) {
	mat3 temp(m);
	--m;

	return temp;
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- positive ---

inline mat3 operator+(const mat3 & m) {
	return mat3(
		+m.x1, +m.y1, +m.z1,
		+m.x2, +m.y2, +m.z2,
		+m.x3, +m.y3, +m.z3
	);
}

//--- negative ---

inline mat3 operator-(const mat3 & m) {
	return mat3(
		-m.x1, -m.y1, -m.z1,
		-m.x2, -m.y2, -m.z2,
		-m.x3, -m.y3, -m.z3
	);
}

//--- add ---

inline mat3 operator+(const mat3 & m1, const mat3 & m2) {
	return mat3(
		m1.x1 + m2.x1, m1.y1 + m2.y1, m1.z1 + m2.z1,
		m1.x2 + m2.x2, m1.y2 + m2.y2, m1.z2 + m2.z2,
		m1.x3 + m2.x3, m1.y3 + m2.y3, m1.z3 + m2.z3
	);
}

inline mat3 operator+(const mat3 & m1, float v) {
	return mat3(
		m1.x1 + v, m1.y1 + v, m1.z1 + v,
		m1.x2 + v, m1.y2 + v, m1.z2 + v,
		m1.x3 + v, m1.y3 + v, m1.z3 + v
	);
}

inline mat3 operator+(float v, const mat3 & m1) {
	return mat3(
		v + m1.x1, v + m1.y1, v + m1.z1,
		v + m1.x2, v + m1.y2, v + m1.z2,
		v + m1.x3, v + m1.y3, v + m1.z3
	);
}

//--- subtract ---

inline mat3 operator-(const mat3 & m1, const mat3 & m2) {
	return mat3(
		m1.x1 - m2.x1, m1.y1 - m2.y1, m1.z1 - m2.z1,
		m1.x2 - m2.x2, m1.y2 - m2.y2, m1.z2 - m2.z2,
		m1.x3 - m2.x3, m1.y3 - m2.y3, m1.z3 - m2.z3
	);
}

inline mat3 operator-(const mat3 & m1, float v) {
	return mat3(
		m1.x1 - v, m1.y1 - v, m1.z1 - v,
		m1.x2 - v, m1.y2 - v, m1.z2 - v,
		m1.x3 - v, m1.y3 - v, m1.z3 - v
	);
}

inline mat3 operator-(float v, const mat3 & m1) {
	return mat3(
		v - m1.x1, v - m1.y1, v - m1.z1,
		v - m1.x2, v - m1.y2, v - m1.z2,
		v - m1.x3, v - m1.y3, v - m1.z3
	);
}

//--- multiply ---

inline mat3 operator*(const mat3 & m1, const mat3 & m2) {
	return mat3(
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

inline mat3 operator*(const mat3 & m1, float v) {
	return mat3(
		m1.x1 * v, m1.y1 * v, m1.z1 * v,
		m1.x2 * v, m1.y2 * v, m1.z2 * v,
		m1.x3 * v, m1.y3 * v, m1.z3 * v
	);
}

inline mat3 operator*(float v, const mat3 & m1) {
	return mat3(
		v * m1.x1, v * m1.y1, v * m1.z1,
		v * m1.x2, v * m1.y2, v * m1.z2,
		v * m1.x3, v * m1.y3, v * m1.z3
	);
}

inline fvec3 operator*(const mat3 & m1, const fvec3 & v) {
	return fvec3(
		v.x * m1.x1 + v.y * m1.x2 + v.z * m1.x3,
		v.x * m1.y1 + v.y * m1.y2 + v.z * m1.y3,
		v.x * m1.z1 + v.y * m1.z2 + v.z * m1.z3
	);
}

//--- divide ---

inline mat3 operator/(const mat3 & m1, float v) {
	return mat3(
		m1.x1 / v, m1.y1 / v, m1.z1 / v,
		m1.x2 / v, m1.y2 / v, m1.z2 / v,
		m1.x3 / v, m1.y3 / v, m1.z3 / v
	);
}

inline mat3 operator/(float v, const mat3 & m1) {
	return mat3(
		v / m1.x1, v / m1.y1, v / m1.z1,
		v / m1.x2, v / m1.y2, v / m1.z2,
		v / m1.x3, v / m1.y3, v / m1.z3
	);
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

inline bool operator==(const mat3 & m1, const mat3 & m2) {
	return
		m1.x1 == m2.x1 && m1.y1 == m2.y1 && m1.z1 == m2.z1 &&
		m1.x2 == m2.x2 && m1.y2 == m2.y2 && m1.z2 == m2.z2 &&
		m1.x3 == m2.x3 && m1.y3 == m2.y3 && m1.z3 == m2.z3;
}

//--- not equal to ---

inline bool operator!=(const mat3 & m1, const mat3 & m2) {
	return
		m1.x1 != m2.x1 || m1.y1 != m2.y1 || m1.z1 != m2.z1 ||
		m1.x2 != m2.x2 || m1.y2 != m2.y2 || m1.z2 != m2.z2 ||
		m1.x3 != m2.x3 || m1.y3 != m2.y3 || m1.z3 != m2.z3;
}



//------------------------------------------------------------------------------
// Other



inline std::string mat<3, 3>::toString() const {
	return
		"[ " +
		std::to_string(x1) + " " + std::to_string(y1) + " " + std::to_string(z1) +
		" | " +
		std::to_string(x2) + " " + std::to_string(y2) + " " + std::to_string(z2) +
		" | " +
		std::to_string(x3) + " " + std::to_string(y3) + " " + std::to_string(z3) +
		" ]";
}



inline std::ostream & operator<<(std::ostream & os, const mat3 & m) {
	return os << m.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT4 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



constexpr mat<4, 4>::mat() :
	x1(1.0f), y1(0.0f), z1(0.0f), w1(0.0f),
	x2(0.0f), y2(1.0f), z2(0.0f), w2(0.0f),
	x3(0.0f), y3(0.0f), z3(1.0f), w3(0.0f),
	x4(0.0f), y4(0.0f), z4(0.0f), w4(1.0f)
{}

constexpr mat<4, 4>::mat(const mat4 & m) :
	x1(m.x1), y1(m.y1), z1(m.z1), w1(m.w1),
	x2(m.x2), y2(m.y2), z2(m.z2), w2(m.w2),
	x3(m.x3), y3(m.y3), z3(m.z3), w3(m.w3),
	x4(m.x4), y4(m.y4), z4(m.z4), w4(m.w4)
{}

constexpr mat<4, 4>::mat(mat4 && m) :
	x1(m.x1), y1(m.y1), z1(m.z1), w1(m.w1),
	x2(m.x2), y2(m.y2), z2(m.z2), w2(m.w2),
	x3(m.x3), y3(m.y3), z3(m.z3), w3(m.w3),
	x4(m.x4), y4(m.y4), z4(m.z4), w4(m.w4)
{}

constexpr mat<4, 4>::mat(
	float x1, float y1, float z1, float w1,
	float x2, float y2, float z2, float w2,
	float x3, float y3, float z3, float w3,
	float x4, float y4, float z4, float w4
) :
	x1(x1), y1(y1), z1(z1), w1(w1),
	x2(x2), y2(y2), z2(z2), w2(w2),
	x3(x3), y3(y3), z3(z3), w3(w3),
	x4(x4), y4(y4), z4(z4), w4(w4)
{}

constexpr mat<4, 4>::mat(const mat2 & m) :
	x1(m.x1), y1(m.y1), z1(0.0f), w1(0.0f),
	x2(m.x2), y2(m.y2), z2(0.0f), w2(0.0f),
	x3(0.0f), y3(0.0f), z3(1.0f), w3(0.0f),
	x4(0.0f), y4(0.0f), z4(0.0f), w4(1.0f)
{}

constexpr mat<4, 4>::mat(const mat3 & m) :
	x1(m.x1), y1(m.y1), z1(m.z1), w1(0.0f),
	x2(m.x2), y2(m.y2), z2(m.z2), w2(0.0f),
	x3(m.x3), y3(m.y3), z3(m.z3), w3(0.0f),
	x4(0.0f), y4(0.0f), z4(0.0f), w4(1.0f)
{}

constexpr mat<4, 4>::mat(
	const fvec4 & v1,
	const fvec4 & v2,
	const fvec4 & v3,
	const fvec4 & v4
) :
	x1(v1.x), y1(v1.y), z1(v1.z), w1(v1.w),
	x2(v2.x), y2(v2.y), z2(v2.z), w2(v2.w),
	x3(v3.x), y3(v3.y), z3(v3.z), w3(v3.w),
	x4(v4.x), y4(v4.y), z4(v4.z), w4(v4.w)
{}



//------------------------------------------------------------------------------
// Assignment Operators



inline mat4 & mat<4, 4>::operator=(const mat4 & m) {
	x1 = m.x1; y1 = m.y1; z1 = m.z1; w1 = m.w1;
	x2 = m.x2; y2 = m.y2; z2 = m.z2; w2 = m.w2;
	x3 = m.x3; y3 = m.y3; z3 = m.z3; w3 = m.w3;
	x4 = m.x4; y4 = m.y4; z4 = m.z4; w4 = m.w4;

	return *this;
}

inline mat4 & mat<4, 4>::operator=(mat4 && m) {
	x1 = m.x1; y1 = m.y1; z1 = m.z1; w1 = m.w1;
	x2 = m.x2; y2 = m.y2; z2 = m.z2; w2 = m.w2;
	x3 = m.x3; y3 = m.y3; z3 = m.z3; w3 = m.w3;
	x4 = m.x4; y4 = m.y4; z4 = m.z4; w4 = m.w4;

	return *this;
}

inline mat4 & mat<4, 4>::operator=(const mat2 & m) {
	x1 = m.x1; y1 = m.y1; z1 = 0.0f; w1 = 0.0f;
	x2 = m.x2; y2 = m.y2; z2 = 0.0f; w2 = 0.0f;
	x3 = 0.0f; y3 = 0.0f; z3 = 1.0f; w3 = 0.0f;
	x4 = 0.0f; y4 = 0.0f; z4 = 0.0f; w4 = 1.0f;

	return *this;
}

inline mat4 & mat<4, 4>::operator=(const mat3 & m) {
	x1 = m.x1; y1 = m.y1; z1 = m.z1; w1 = 0.0f;
	x2 = m.x2; y2 = m.y2; z2 = m.z2; w2 = 0.0f;
	x3 = m.x3; y3 = m.y3; z3 = m.z3; w3 = 0.0f;
	x4 = 0.0f; y4 = 0.0f; z4 = 0.0f; w4 = 1.0f;

	return *this;
}



//------------------------------------------------------------------------------
// Access Operators



inline float & mat<4, 4>::operator[](nat i) {
	return *(&x1 + i);
}



//------------------------------------------------------------------------------
// Arithmetic Assignment Operators



//--- add assign ---

inline mat4 & operator+=(mat4 & m, float v) {
	return m = m + v;
}

inline mat4 & operator+=(mat4 & m1, const mat4 & m2) {
	return m1 = m1 + m2;
}

//--- subtract assign ---

inline mat4 & operator-=(mat4 & m, float v) {
	m = m - v;
}

inline mat4 & operator-=(mat4 & m1, const mat4 & m2) {
	return m1 = m1 - m2;
}

//--- multiply assign ---

inline mat4 & operator*=(mat4 & m, float v) {
	m = m * v;
}

inline mat4 & operator*=(mat4 & m1, const mat4 & m2) {
	return m1 = m1 * m2;
}

//--- divide assign ---

inline mat4 & operator/=(mat4 & m, float v) {
	m = m / v;
}

//--- pre increment ---

inline mat4 & operator++(mat4 & m) {
	++m.x1; ++m.y1; ++m.z1; ++m.w1;
	++m.x2; ++m.y2; ++m.z2; ++m.w2;
	++m.x3; ++m.y3; ++m.z3; ++m.w3;
	++m.x4; ++m.y4; ++m.z4; ++m.w4;

	return m;
}

//--- post increment ---

inline mat4 operator++(mat4 & m, int) {
	mat4 temp(m);
	++m;

	return temp;
}

//--- pre decrement ---

inline mat4 & operator--(mat4 & m) {
	--m.x1; --m.y1; --m.z1; --m.w1;
	--m.x2; --m.y2; --m.z2; --m.w2;
	--m.x3; --m.y3; --m.z3; --m.w3;
	--m.x4; --m.y4; --m.z4; --m.w4;

	return m;
}

//--- post decrement ---

inline mat4 operator--(mat4 & m, int) {
	mat4 temp(m);
	--m;

	return temp;
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- positive ---

inline mat4 operator+(const mat4 & m) {
	return mat4(
		+m.x1, +m.y1, +m.z1, +m.w1,
		+m.x2, +m.y2, +m.z2, +m.w2,
		+m.x3, +m.y3, +m.z3, +m.w3,
		+m.x4, +m.y4, +m.z4, +m.w4
	);
}

//--- negative ---

inline mat4 operator-(const mat4 & m) {
	return mat4(
		-m.x1, -m.y1, -m.z1, -m.w1,
		-m.x2, -m.y2, -m.z2, -m.w2,
		-m.x3, -m.y3, -m.z3, -m.w3,
		-m.x4, -m.y4, -m.z4, -m.w4
	);
}

//--- add ---

inline mat4 operator+(const mat4 & m1, const mat4 & m2) {
	return mat4(
		m1.x1 + m2.x1, m1.y1 + m2.y1, m1.z1 + m2.z1, m1.w1 + m2.w1,
		m1.x2 + m2.x2, m1.y2 + m2.y2, m1.z2 + m2.z2, m1.w2 + m2.w2,
		m1.x3 + m2.x3, m1.y3 + m2.y3, m1.z3 + m2.z3, m1.w3 + m2.w3,
		m1.x4 + m2.x4, m1.y4 + m2.y4, m1.z4 + m2.z4, m1.w4 + m2.w4
	);
}

inline mat4 operator+(const mat4 & m1, float v) {
	return mat4(
		m1.x1 + v, m1.y1 + v, m1.z1 + v, m1.w1 + v,
		m1.x2 + v, m1.y2 + v, m1.z2 + v, m1.w2 + v,
		m1.x3 + v, m1.y3 + v, m1.z3 + v, m1.w3 + v,
		m1.x4 + v, m1.y4 + v, m1.z4 + v, m1.w4 + v
	);
}

inline mat4 operator+(float v, const mat4 & m1) {
	return mat4(
		v + m1.x1, v + m1.y1, v + m1.z1, v + m1.w1,
		v + m1.x2, v + m1.y2, v + m1.z2, v + m1.w2,
		v + m1.x3, v + m1.y3, v + m1.z3, v + m1.w3,
		v + m1.x4, v + m1.y4, v + m1.z4, v + m1.w4
	);
}

//--- subtract ---

inline mat4 operator-(const mat4 & m1, const mat4 & m2) {
	return mat4(
		m1.x1 - m2.x1, m1.y1 - m2.y1, m1.z1 - m2.z1, m1.w1 - m2.w1,
		m1.x2 - m2.x2, m1.y2 - m2.y2, m1.z2 - m2.z2, m1.w2 - m2.w2,
		m1.x3 - m2.x3, m1.y3 - m2.y3, m1.z3 - m2.z3, m1.w3 - m2.w3,
		m1.x4 - m2.x4, m1.y4 - m2.y4, m1.z4 - m2.z4, m1.w4 - m2.w4
	);
}

inline mat4 operator-(const mat4 & m1, float v) {
	return mat4(
		m1.x1 - v, m1.y1 - v, m1.z1 - v, m1.w1 - v,
		m1.x2 - v, m1.y2 - v, m1.z2 - v, m1.w2 - v,
		m1.x3 - v, m1.y3 - v, m1.z3 - v, m1.w3 - v,
		m1.x4 - v, m1.y4 - v, m1.z4 - v, m1.w4 - v
	);
}

inline mat4 operator-(float v, const mat4 & m1) {
	return mat4(
		v - m1.x1, v - m1.y1, v - m1.z1, v - m1.w1,
		v - m1.x2, v - m1.y2, v - m1.z2, v - m1.w2,
		v - m1.x3, v - m1.y3, v - m1.z3, v - m1.w3,
		v - m1.x4, v - m1.y4, v - m1.z4, v - m1.w4
	);
}

//--- multiply ---

inline mat4 operator*(const mat4 & m1, const mat4 & m2) {
	return mat4(
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

inline mat4 operator*(const mat4 & m1, float v) {
	return mat4(
		m1.x1 * v, m1.y1 * v, m1.z1 * v, m1.w1 * v,
		m1.x2 * v, m1.y2 * v, m1.z2 * v, m1.w2 * v,
		m1.x3 * v, m1.y3 * v, m1.z3 * v, m1.w3 * v,
		m1.x4 * v, m1.y4 * v, m1.z4 * v, m1.w4 * v
	);
}

inline mat4 operator*(float v, const mat4 & m1) {
	return mat4(
		v * m1.x1, v * m1.y1, v * m1.z1, v * m1.w1,
		v * m1.x2, v * m1.y2, v * m1.z2, v * m1.w2,
		v * m1.x3, v * m1.y3, v * m1.z3, v * m1.w3,
		v * m1.x4, v * m1.y4, v * m1.z4, v * m1.w4
	);
}

inline fvec4 operator*(const mat4 & m1, const fvec4 & v) {
	return fvec4(
		v.x * m1.x1 + v.y * m1.x2 + v.z * m1.x3 + v.w * m1.x4,
		v.x * m1.y1 + v.y * m1.y2 + v.z * m1.y3 + v.w * m1.y4,
		v.x * m1.z1 + v.y * m1.z2 + v.z * m1.z3 + v.w * m1.z4,
		v.x * m1.w1 + v.y * m1.w2 + v.z * m1.w3 + v.w * m1.w4
	);
}

//--- divide ---

inline mat4 operator/(const mat4 & m1, float v) {
	return mat4(
		m1.x1 / v, m1.y1 / v, m1.z1 / v, m1.w1 / v,
		m1.x2 / v, m1.y2 / v, m1.z2 / v, m1.w2 / v,
		m1.x3 / v, m1.y3 / v, m1.z3 / v, m1.w3 / v,
		m1.x4 / v, m1.y4 / v, m1.z4 / v, m1.w4 / v
	);
}

inline mat4 operator/(float v, const mat4 & m1) {
	return mat4(
		v / m1.x1, v / m1.y1, v / m1.z1, v / m1.w1,
		v / m1.x2, v / m1.y2, v / m1.z2, v / m1.w2,
		v / m1.x3, v / m1.y3, v / m1.z3, v / m1.w3,
		v / m1.x4, v / m1.y4, v / m1.z4, v / m1.w4
	);
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

inline bool operator==(const mat4 & m1, const mat4 & m2) {
	return
		m1.x1 == m2.x1 && m1.y1 == m2.y1 && m1.z1 == m2.z1 && m1.w1 == m2.w1 &&
		m1.x2 == m2.x2 && m1.y2 == m2.y2 && m1.z2 == m2.z2 && m1.w2 == m2.w2 &&
		m1.x3 == m2.x3 && m1.y3 == m2.y3 && m1.z3 == m2.z3 && m1.w3 == m2.w3 &&
		m1.x4 == m2.x4 && m1.y4 == m2.y4 && m1.z4 == m2.z4 && m1.w4 == m2.w4;
}

//--- not equal to ---

inline bool operator!=(const mat4 & m1, const mat4 & m2) {
	return
		m1.x1 != m2.x1 || m1.y1 != m2.y1 || m1.z1 != m2.z1 || m1.w1 != m2.w1 ||
		m1.x2 != m2.x2 || m1.y2 != m2.y2 || m1.z2 != m2.z2 || m1.w2 != m2.w2 ||
		m1.x3 != m2.x3 || m1.y3 != m2.y3 || m1.z3 != m2.z3 || m1.w3 != m2.w3 ||
		m1.x4 != m2.x4 || m1.y4 != m2.y4 || m1.z4 != m2.z4 || m1.w4 != m2.w4;
}



//------------------------------------------------------------------------------
// Other



inline std::string mat<4, 4>::toString() const {
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



inline std::ostream & operator<<(std::ostream & os, const mat4 & m) {
	return os << m.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT FUNCTIONS IMPLEMENTATION ----------------------------------------------------------------------------------------



//--- transpose ---

inline mat2 trans(const mat2 & m1) {
	return mat2(
		m1.x1, m1.x2,
		m1.y1, m1.y2
	);
}

inline mat3 trans(const mat3 & m1) {
	return mat3(
		m1.x1, m1.x2, m1.x3,
		m1.y1, m1.y2, m1.y3,
		m1.z1, m1.z2, m1.z3
	);
}

inline mat4 trans(const mat4 & m1) {
	return mat4(
		m1.x1, m1.x2, m1.x3, m1.x4,
		m1.y1, m1.y2, m1.y3, m1.y4,
		m1.z1, m1.z2, m1.z3, m1.z4,
		m1.w1, m1.w2, m1.w3, m1.w4
	);
}

//--- cofactor ---

inline mat2 cof(const mat2 & m1) {
	return mat2(
		m1.y2, -m1.x2,
		-m1.y1, m1.x1
	);
}

inline mat3 cof(const mat3 & m1) {
	return mat3(
		+(m1.y2 * m1.z3 - m1.y3 * m1.z2), -(m1.x2 * m1.z3 - m1.x3 * m1.z2), +(m1.x2 * m1.y3 - m1.x3 * m1.y2),
		-(m1.y1 * m1.z3 - m1.y3 * m1.z1), +(m1.x1 * m1.z3 - m1.x3 * m1.z1), -(m1.x1 * m1.y3 - m1.x3 * m1.y1),
		+(m1.y1 * m1.z2 - m1.y2 * m1.z1), -(m1.x1 * m1.z2 - m1.x2 * m1.z1), +(m1.x1 * m1.y2 - m1.x2 * m1.y1)
	);
}

inline mat4 cof(const mat4 & m1) {
	//float xy12 = m1.x1 * m1.y2 - m1.x2 * m1.y1;
	//float xy13 = m1.x1 * m1.y3 - m1.x3 * m1.y1;
	//float xy14 = m1.x1 * m1.y4 - m1.x4 * m1.y1;
	//float xz12 = m1.x1 * m1.z2 - m1.x2 * m1.z1;
	//float xz13 = m1.x1 * m1.z3 - m1.x3 * m1.z1;
	//float xz14 = m1.x1 * m1.z4 - m1.x4 * m1.z1;
	//float xw12 = m1.x1 * m1.w2 - m1.x2 * m1.w1;
	//float xw13 = m1.x1 * m1.w3 - m1.x3 * m1.w1;
	//float xw14 = m1.x1 * m1.w4 - m1.x4 * m1.w1;
	//float xy23 = m1.x2 * m1.y3 - m1.x3 * m1.y2;
	//float xy24 = m1.x2 * m1.y4 - m1.x4 * m1.y2;
	//float xz23 = m1.x2 * m1.z3 - m1.x3 * m1.z2;
	//float xz24 = m1.x2 * m1.z4 - m1.x4 * m1.z2;
	//float xw23 = m1.x2 * m1.w3 - m1.x3 * m1.w2;
	//float xw24 = m1.x2 * m1.w4 - m1.x4 * m1.w2;
	float yz12 = m1.y1 * m1.z2 - m1.y2 * m1.z1;
	float yz13 = m1.y1 * m1.z3 - m1.y3 * m1.z1;
	float yz14 = m1.y1 * m1.z4 - m1.y4 * m1.z1;
	float yw12 = m1.y1 * m1.w2 - m1.y2 * m1.w1;
	float yw13 = m1.y1 * m1.w3 - m1.y3 * m1.w1;
	float yw14 = m1.y1 * m1.w4 - m1.y4 * m1.w1;
	//float xy34 = m1.x3 * m1.y4 - m1.x4 * m1.y3;
	//float xz34 = m1.x3 * m1.z4 - m1.x4 * m1.z3;
	//float xw34 = m1.x3 * m1.w4 - m1.x4 * m1.w3;
	float yz23 = m1.y2 * m1.z3 - m1.y3 * m1.z2;
	float yz24 = m1.y2 * m1.z4 - m1.y4 * m1.z2;
	float yw23 = m1.y2 * m1.w3 - m1.y3 * m1.w2;
	float yw24 = m1.y2 * m1.w4 - m1.y4 * m1.w2;
	float zw12 = m1.z1 * m1.w2 - m1.z2 * m1.w1;
	float zw13 = m1.z1 * m1.w3 - m1.z3 * m1.w1;
	float zw14 = m1.z1 * m1.w4 - m1.z4 * m1.w1;
	float yz34 = m1.y3 * m1.z4 - m1.y4 * m1.z3;
	float yw34 = m1.y3 * m1.w4 - m1.y4 * m1.w3;
	float zw23 = m1.z2 * m1.w3 - m1.z3 * m1.w2;
	float zw24 = m1.z2 * m1.w4 - m1.z4 * m1.w2;
	float zw34 = m1.z3 * m1.w4 - m1.z4 * m1.w3;

	float xyz123 = m1.x1 * yz23 - m1.x2 * yz13 + m1.x3 * yz12;
	float xyz124 = m1.x1 * yz24 - m1.x2 * yz14 + m1.x4 * yz12;
	float xyz134 = m1.x1 * yz34 - m1.x3 * yz14 + m1.x4 * yz13;
	float xyw123 = m1.x1 * yw23 - m1.x2 * yw13 + m1.x3 * yw12;
	float xyw124 = m1.x1 * yw24 - m1.x2 * yw14 + m1.x4 * yw12;
	float xyw134 = m1.x1 * yw34 - m1.x3 * yw14 + m1.x4 * yw13;
	float xzw123 = m1.x1 * zw23 - m1.x2 * zw13 + m1.x3 * zw12;
	float xzw124 = m1.x1 * zw24 - m1.x2 * zw14 + m1.x4 * zw12;
	float xzw134 = m1.x1 * zw34 - m1.x3 * zw14 + m1.x4 * zw13;
	float xyz234 = m1.x2 * yz34 - m1.x3 * yz24 + m1.x4 * yz23;
	float xyw234 = m1.x2 * yw34 - m1.x3 * yw24 + m1.x4 * yw23;
	float xzw234 = m1.x2 * zw34 - m1.x3 * zw24 + m1.x4 * zw23;
	float yzw123 = m1.y1 * zw23 - m1.y2 * zw13 + m1.y3 * zw12;
	float yzw124 = m1.y1 * zw24 - m1.y2 * zw14 + m1.y4 * zw12;
	float yzw134 = m1.y1 * zw34 - m1.y3 * zw14 + m1.y4 * zw13;
	float yzw234 = m1.y2 * zw34 - m1.y3 * zw24 + m1.y4 * zw23;

	return mat4(
		+yzw234, -xzw234, +xyw234, -xyz234,
		-yzw134, +xzw134, -xyw134, +xyz134,
		+yzw124, -xzw124, +xyw124, -xyz124,
		-yzw123, +xzw123, -xyw123, +xyz123
	);
}

//-- adjoint ---

inline mat2 adj(const mat2 & m1) {
	return trans(cof(m1));

}

inline mat3 adj(const mat3 & m1) {
	return trans(cof(m1));

}

inline mat4 adj(const mat4 & m1) {
	return trans(cof(m1));
}

//--- determinant ---

inline float det(const mat2 & m1) {
	return
		+m1.x1 * m1.y2
		- m1.x2 * m1.y1;
}

inline float det(const mat3 & m1) {
	return
		+m1.x1 * (m1.y2 * m1.z3 - m1.y3 * m1.z2)
		- m1.x2 * (m1.y1 * m1.z3 - m1.y3 * m1.z1)
		+ m1.x3 * (m1.y1 * m1.z2 - m1.y2 * m1.z1);
}

inline float det(const mat4 & m1) {
	float zw12 = m1.z1 * m1.w2 - m1.z2 * m1.w1;
	float zw13 = m1.z1 * m1.w3 - m1.z3 * m1.w1;
	float zw14 = m1.z1 * m1.w4 - m1.z4 * m1.w1;
	float zw23 = m1.z2 * m1.w3 - m1.z3 * m1.w2;
	float zw24 = m1.z2 * m1.w4 - m1.z4 * m1.w2;
	float zw34 = m1.z3 * m1.w4 - m1.z4 * m1.w3;

	float yzw123 = m1.y1 * zw23 - m1.y2 * zw13 + m1.y3 * zw12;
	float yzw124 = m1.y1 * zw24 - m1.y2 * zw14 + m1.y4 * zw12;
	float yzw134 = m1.y1 * zw34 - m1.y3 * zw14 + m1.y4 * zw13;
	float yzw234 = m1.y2 * zw34 - m1.y3 * zw24 + m1.y4 * zw23;

	return m1.x1 * yzw234 - m1.x2 * yzw134 + m1.x3 * yzw124 - m1.x4 * yzw123;
}

//--- inverse ---

inline mat2 inv(const mat2 & m1) {
	return adj(m1) / det(m1);
}

inline mat3 inv(const mat3 & m1) {
	return adj(m1) / det(m1);
}

inline mat4 inv(const mat4 & m1) {
	return adj(m1) / det(m1);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORMATIONS IMPLEMENTATION --------------------------------------------------------------------------------------



inline mat2 translate(float delta) {
	return mat2(
		1.0f, 0.0f,
		delta, 1.0f
	);
}

inline mat3 translate(const fvec2 & delta) {
	return mat3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		delta.x, delta.y, 1.0f
	);
}

inline mat4 translate(const fvec3 & delta) {
	return mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		delta.x, delta.y, delta.z, 1.0f
	);
}

inline mat2 scale(const fvec2 & scale) {
	return mat2(
		scale.x, 0.0f,
		0.0f, scale.y
	);
}

inline mat3 scale(const fvec3 & scale) {
	return mat3(
		scale.x, 0.0f, 0.0f,
		0.0f, scale.y, 0.0f,
		0.0f, 0.0f, scale.z
	);
}

inline mat4 scale(const fvec4 & scale) {
	return mat4(
		scale.x, 0.0f, 0.0f, 0.0f,
		0.0f, scale.y, 0.0f, 0.0f,
		0.0f, 0.0f, scale.z, 0.0f,
		0.0f, 0.0f, 0.0f, scale.w
	);
}

inline mat2 rotate(float theta) {
	float s = sin(theta);
	float c = cos(theta);

	return mat2(
		c, s,
		-s, c
	);
}

inline mat3 rotateX(float theta) {
	float s = sin(theta);
	float c = cos(theta);

	return mat3(
		1.0f, 0.0f, 0.0f,
		0.0f, c, s,
		0.0f, -s, c
	);
}

inline mat3 rotateY(float theta) {
	float s = sin(theta);
	float c = cos(theta);

	return mat3(
		c, 0.0f, -s,
		0.0f, 1.0f, 0.0f,
		s, 0.0f, c
	);
}

inline mat3 rotateZ(float theta) {
	float s = sin(theta);
	float c = cos(theta);

	return mat3(
		c, s, 0.0f,
		-s, c, 0.0f,
		0.0f, 0.0f, 1.0f
	);
}

inline mat3 rotate(float sinTheta, float cosTheta, const fvec3 & axis) {
	if (mag2(axis) == 0) { //can't rotate around 0 length fvector
		return mat3();
	}

	return rotate_n(sinTheta, cosTheta, norm(axis));
}
inline mat3 rotate_n(float s, float c, const fvec3 & m1) {
	float cm = 1.0f - c;

	return mat3(
		c + m1.x * m1.x * cm, m1.y * m1.x * cm + m1.z * s, m1.z * m1.x * cm - m1.y * s,
		m1.x * m1.y * cm - m1.z * s, c + m1.y * m1.y * cm, m1.z * m1.y * cm + m1.x * s,
		m1.x * m1.z * cm + m1.y * s, m1.y * m1.z * cm - m1.x * s, c + m1.z * m1.z * cm
	);
}

inline mat3 rotate(float theta, const fvec3 & axis) {
	return rotate(sin(theta), cos(theta), axis);
}
inline mat3 rotate_n(float theta, const fvec3 & axis) {
	return rotate_n(sin(theta), cos(theta), axis);
}

inline mat3 euler(const fvec3 & forward, const fvec3 & up, float theta, float phi, float psi) {
	return euler_n(norm(forward), norm(up), theta, phi, psi);
}
inline mat3 euler_n(const fvec3 & forward, const fvec3 & up, float theta, float phi, float psi) {
	return rotate_n(theta, up) * rotate_n(phi, cross(forward, up)) * rotate_n(psi, forward);
}

inline mat3 align(const fvec3 & v1, const fvec3 & v2) {
	return align_n(norm(v1), norm(v2));
}
inline mat3 align_n(const fvec3 & v1, const fvec3 & v2) {
	fvec3 c = cross(v1, v2);
	float d = dot(v1, v2);

	return rotate(mag(c), d, c);
}

inline mat3 align(const fvec3 & forward1, const fvec3 & up1, const fvec3 & forward2, const fvec3 & up2) {
	return align_n(norm(forward1), norm(up1), norm(forward2), norm(up2));
}
inline mat3 align_n(const fvec3 & forward1, const fvec3 & up1, const fvec3 & forward2, const fvec3 & up2) {
	mat3 m = align_n(forward1, forward2);
	return align_n(m * up1, up2) * m;
}

inline mat3 map(const fvec3 & x1, const fvec3 & y1, const fvec3 & z1, const fvec3 & x2, const fvec3 & y2, const fvec3 & z2) {
	return map_n(norm(x1), norm(y1), norm(z1), norm(x2), norm(y2), norm(z2));
}
inline mat3 map_n(const fvec3 & x1, const fvec3 & y1, const fvec3 & z1, const fvec3 & x2, const fvec3 & y2, const fvec3 & z2) {
	mat3 A(x1, y1, z1);
	mat3 B(x2, y2, z2);

	return trans(B) * A;
}

inline mat3 mapTo(const fvec3 & x, const fvec3 & y, const fvec3 & z) {
	return mapTo_n(norm(x), norm(y), norm(z));
}
inline mat3 mapTo_n(const fvec3 & x, const fvec3 & y, const fvec3 & z) {
	return trans(mat3(x, y, z));
}

inline mat3 mapFrom(const fvec3 & x, const fvec3 & y, const fvec3 & z) {
	return mapFrom_n(norm(x), norm(y), norm(z));
}
inline mat3 mapFrom_n(const fvec3 & x, const fvec3 & y, const fvec3 & z) {
	return mat3(x, y, z);
}

inline mat3 mapAny(const fvec3 & x1, const fvec3 & y1, const fvec3 & z1, const fvec3 & x2, const fvec3 & y2, const fvec3 & z2) {
	mat3 A(x1, y1, z1);
	mat3 B(x2, y2, z2);

	return inv(B) * A;
}

inline mat4 ortho(float w, float h, float n, float f) {
	return mat4(
		2.0f / w, 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / h, 0.0f, 0.0f,
		0.0f, 0.0f, 2.0f / (n - f), 0.0f,
		0.0f, 0.0f, (f + n) / (n - f), 1.0f
	);
}

inline mat4 orthoAsym(float l, float r, float b, float t, float n, float f) {
	l *= -1.0f;
	b *= -1.0f;
	return mat4(
		2.0f / (r - l), 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / (t - b), 0.0f, 0.0f,
		0.0f, 0.0f, 2.0f / (n - f), 0.0f,
		(r + l) / (l - r), (t + b) / (b - t), (f + n) / (n - f), 1.0f
	);
}

inline mat4 perspective(float fov, float a, float n, float f) {
	float t_n = tan(fov / 2.0f);

	return mat4(
		1.0f / (a * t_n), 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f / t_n, 0.0f, 0.0f,
		0.0f, 0.0f, (f + n) / (n - f), -1.0f,
		0.0f, 0.0f, 2.0f * f * n / (n - f), 0.0f
	);
}

inline mat4 perspectiveAsym(float fovNX, float fovPX, float fovNY, float fovPY, float n, float f) {
	float l = n * tan(fovNX) * -1.0f;
	float r = n * tan(fovPX);
	float m2 = n * tan(fovNY) * -1.0f;
	float t = n * tan(fovPY);

	return mat4(
		2.0f * n / (r - l), 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f * n / (t - m2), 0.0f, 0.0f,
		(r + l) / (r - l), (t + m2) / (t - m2), (f + n) / (n - f), -1.0f,
		0.0f, 0.0f, 2.0f * f * n / (n - f), 0.0f
	);
}

inline mat4 view(const fvec3 & camPos, const fvec3 & camDir, const fvec3 & camUp) {
	fvec3 Z = -norm(camDir);
	fvec3 Y = norm(camUp);
	fvec3 X = cross(Y, Z);
	fvec3 P = -camPos;

	return mat4(mapTo_n(X, Y, Z)) * translate(P);
}



}
