#pragma once

/*
	The vec structs need to be of standard layout.
	std::is_standard_layout
*/



#include <limits>
#include <iostream>
#include <string>
#include <sstream>

#include "QMU.hpp"



namespace qmu {



template <typename T, nat t_n>
struct vec;



template <typename T> using vec1 = vec<T, 1>;
template <typename T> using vec2 = vec<T, 2>;
template <typename T> using vec3 = vec<T, 3>;
template <typename T> using vec4 = vec<T, 4>;

template <nat t_n> using   fvec = vec<             float, t_n>;
template <nat t_n> using   dvec = vec<            double, t_n>;
template <nat t_n> using   cvec = vec<  signed      char, t_n>;
template <nat t_n> using  ucvec = vec<unsigned      char, t_n>;
template <nat t_n> using   svec = vec<  signed     short, t_n>;
template <nat t_n> using  usvec = vec<unsigned     short, t_n>;
template <nat t_n> using   ivec = vec<  signed       int, t_n>;
template <nat t_n> using  uivec = vec<unsigned       int, t_n>;
template <nat t_n> using   lvec = vec<  signed      long, t_n>;
template <nat t_n> using  ulvec = vec<unsigned      long, t_n>;
template <nat t_n> using  llvec = vec<  signed long long, t_n>;
template <nat t_n> using ullvec = vec<unsigned long long, t_n>;
template <nat t_n> using   bvec = vec<              bool, t_n>;
template <nat t_n> using   nvec = vec<               nat, t_n>;
template <nat t_n> using  fnvec = vec<              fnat, t_n>;

using   fvec1 = vec<             float, 1>;
using   fvec2 = vec<             float, 2>;
using   fvec3 = vec<             float, 3>;
using   fvec4 = vec<             float, 4>;

using   dvec1 = vec<            double, 1>;
using   dvec2 = vec<            double, 2>;
using   dvec3 = vec<            double, 3>;
using   dvec4 = vec<            double, 4>;

using   cvec1 = vec<       signed char, 1>;
using   cvec2 = vec<       signed char, 2>;
using   cvec3 = vec<       signed char, 3>;
using   cvec4 = vec<       signed char, 4>;
using  ucvec1 = vec<     unsigned char, 1>;
using  ucvec2 = vec<     unsigned char, 2>;
using  ucvec3 = vec<     unsigned char, 3>;
using  ucvec4 = vec<     unsigned char, 4>;

using   svec1 = vec<      signed short, 1>;
using   svec2 = vec<      signed short, 2>;
using   svec3 = vec<      signed short, 3>;
using   svec4 = vec<      signed short, 4>;
using  usvec1 = vec<    unsigned short, 1>;
using  usvec2 = vec<    unsigned short, 2>;
using  usvec3 = vec<    unsigned short, 3>;
using  usvec4 = vec<    unsigned short, 4>;

using   ivec1 = vec<        signed int, 1>;
using   ivec2 = vec<        signed int, 2>;
using   ivec3 = vec<        signed int, 3>;
using   ivec4 = vec<        signed int, 4>;
using  uivec1 = vec<      unsigned int, 1>;
using  uivec2 = vec<      unsigned int, 2>;
using  uivec3 = vec<      unsigned int, 3>;
using  uivec4 = vec<      unsigned int, 4>;

using   lvec1 = vec<       signed long, 1>;
using   lvec2 = vec<       signed long, 2>;
using   lvec3 = vec<       signed long, 3>;
using   lvec4 = vec<       signed long, 4>;
using  ulvec1 = vec<     unsigned long, 1>;
using  ulvec2 = vec<     unsigned long, 2>;
using  ulvec3 = vec<     unsigned long, 3>;
using  ulvec4 = vec<     unsigned long, 4>;

using  llvec1 = vec<  signed long long, 1>;
using  llvec2 = vec<  signed long long, 2>;
using  llvec3 = vec<  signed long long, 3>;
using  llvec4 = vec<  signed long long, 4>;
using ullvec1 = vec<unsigned long long, 1>;
using ullvec2 = vec<unsigned long long, 2>;
using ullvec3 = vec<unsigned long long, 3>;
using ullvec4 = vec<unsigned long long, 4>;

using   bvec1 = vec<              bool, 1>;
using   bvec2 = vec<              bool, 2>;
using   bvec3 = vec<              bool, 3>;
using   bvec4 = vec<              bool, 4>;

using   nvec1 = vec<               nat, 1>;
using   nvec2 = vec<               nat, 2>;
using   nvec3 = vec<               nat, 3>;
using   nvec4 = vec<               nat, 4>;

using  fnvec1 = vec<              fnat, 1>;
using  fnvec2 = vec<              fnat, 2>;
using  fnvec3 = vec<              fnat, 3>;
using  fnvec4 = vec<              fnat, 4>;

template <typename T> using point = vec<T, 2>;

template <typename T> using bound1 = vec<T, 2>;
template <typename T> using bound2 = vec<T, 4>;
template <typename T> using bound3 = vec<T, 6>;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC1 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct vec<T, 1> {

	using Type = T;
	static constexpr nat t_n = 1;

	union {
		struct { T x; };
		struct { T r; };
		struct { T s; };
	};

	//--- constructors ---

	constexpr vec();
	constexpr vec(const vec1<T> & v);
	constexpr vec(vec1<T> && v);

	constexpr explicit vec(const       T  & v);
	constexpr explicit vec(const vec2<T> & v);
	constexpr explicit vec(const vec3<T> & v);
	constexpr explicit vec(const vec4<T> & v);

	//--- destructor ---

	~vec() {
		static_assert(std::is_standard_layout<vec<T, 1>>::value, "vec<T, 1> must be of standard layout");
		static_assert(sizeof(vec<T, 1>) == 1 * sizeof(T), "vec<T, 1> must be equal in size to one T");
	}

	//--- assignment operators ---

	vec1<T> & operator=(const vec1<T> & v);
	vec1<T> & operator=(vec1<T> && v);

	vec1<T> & operator=(const       T  & v);
	vec1<T> & operator=(const vec2<T> & v);
	vec1<T> & operator=(const vec3<T> & v);
	vec1<T> & operator=(const vec4<T> & v);

	//--- access operators ---

	T operator[](nat i);

	//--- arithmetic operators ---

	template <typename T> friend vec1<T> & operator+=(vec1<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec1<T> & operator+=(vec1<T> & v1, const       T  & v2);
	template <typename T> friend vec1<T> & operator+=(vec1<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec1<T> & operator+=(vec1<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec1<T> & operator+=(vec1<T> & v1, const vec4<T> & v2);

	template <typename T> friend vec1<T> & operator-=(vec1<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec1<T> & operator-=(vec1<T> & v1, const       T  & v2);
	template <typename T> friend vec1<T> & operator-=(vec1<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec1<T> & operator-=(vec1<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec1<T> & operator-=(vec1<T> & v1, const vec4<T> & v2);

	template <typename T> friend vec1<T> & operator*=(vec1<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec1<T> & operator*=(vec1<T> & v1, const       T  & v2);
	template <typename T> friend vec1<T> & operator*=(vec1<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec1<T> & operator*=(vec1<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec1<T> & operator*=(vec1<T> & v1, const vec4<T> & v2);

	template <typename T> friend vec1<T> & operator/=(vec1<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec1<T> & operator/=(vec1<T> & v1, const       T  & v2);
	template <typename T> friend vec1<T> & operator/=(vec1<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec1<T> & operator/=(vec1<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec1<T> & operator/=(vec1<T> & v1, const vec4<T> & v2);

	template <typename T> friend vec1<T> & operator++(vec1<T> & v);
	template <typename T> friend vec1<T> operator++(vec1<T> & v, int);

	template <typename T> friend vec1<T> & operator--(vec1<T> & v);
	template <typename T> friend vec1<T> operator--(vec1<T> & v, int);

	template <typename T> friend vec1<T> operator+(const vec1<T> & v);

	template <typename T> friend vec1<T> operator-(const vec1<T> & v);

	template <typename T> friend vec1<T> operator+(const vec1<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec1<T> operator+(const vec1<T> & v1, const       T  & v2);
	template <typename T> friend vec1<T> operator+(const       T  & v1, const vec1<T> & v2);

	template <typename T> friend vec1<T> operator-(const vec1<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec1<T> operator-(const vec1<T> & v1, const       T  & v2);
	template <typename T> friend vec1<T> operator-(const       T  & v1, const vec1<T> & v2);

	template <typename T> friend vec1<T> operator*(const vec1<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec1<T> operator*(const vec1<T> & v1, const       T  & v2);
	template <typename T> friend vec1<T> operator*(const       T  & v1, const vec1<T> & v2);

	template <typename T> friend vec1<T> operator/(const vec1<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec1<T> operator/(const vec1<T> & v1, const       T  & v2);
	template <typename T> friend vec1<T> operator/(const       T  & v1, const vec1<T> & v2);

	//--- comparison operators ---

	template <typename T> friend bool operator==(const vec1<T> & v1, const vec1<T> & v2);
	template <typename T> friend bool operator==(const vec1<T> & v1, const       T  & v2);
	template <typename T> friend bool operator==(const       T  & v1, const vec1<T> & v2);

	template <typename T> friend bool operator!=(const vec1<T> & v1, const vec1<T> & v2);
	template <typename T> friend bool operator!=(const vec1<T> & v1, const       T  & v2);
	template <typename T> friend bool operator!=(const       T  & v1, const vec1<T> & v2);

	template <typename T> friend bool operator<(const vec1<T> & v1, const       T  & v2);
	template <typename T> friend bool operator<(const       T  & v1, const vec1<T> & v2);

	template <typename T> friend bool operator>(const vec1<T> & v1, const       T  & v2);
	template <typename T> friend bool operator>(const       T  & v1, const vec1<T> & v2);

	template <typename T> friend bool operator<=(const vec1<T> & v1, const       T  & v2);
	template <typename T> friend bool operator<=(const       T  & v1, const vec1<T> & v2);

	template <typename T> friend bool operator>=(const vec1<T> & v1, const       T  & v2);
	template <typename T> friend bool operator>=(const       T  & v1, const vec1<T> & v2);

	//--- other ---

	std::string toString() const;

	template <typename T> friend std::ostream & operator<<(std::ostream & os, const vec1<T> & v);

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC2 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct vec<T, 2> {

	using Type = T;
	static constexpr nat t_n = 2;

	union {
		struct { T x, y; };
		struct { T r, g; };
		struct { T s, t; };
		struct { T x, width; };
	};

	//--- constructors ---

	constexpr vec();
	constexpr vec(const vec2<T> & v);
	constexpr vec(vec2<T> && v);

	constexpr explicit vec(const       T  & v);
	constexpr explicit vec(const vec1<T> & v);
	constexpr explicit vec(const vec3<T> & v);
	constexpr explicit vec(const vec4<T> & v);
	constexpr vec(const T & v1, const T & v2);

	//--- destructor ---

	~vec() {
		static_assert(std::is_standard_layout<vec<T, 2>>::value, "vec<T, 2> must be of standard layout");
		static_assert(sizeof(vec<T, 2>) == 2 * sizeof(T), "vec<T, 2> must be equal in size to 2 Ts");
	}

	//--- assignment operators ---

	vec2<T> & operator=(const vec2<T> & v);
	vec2<T> & operator=(vec2<T> && v);

	vec2<T> & operator=(const       T  & v);
	vec2<T> & operator=(const vec1<T> & v);
	vec2<T> & operator=(const vec3<T> & v);
	vec2<T> & operator=(const vec4<T> & v);

	//--- access operators ---

	T operator[](nat i);

	//--- arithmetic operators ---

	template <typename T> friend vec2<T> & operator+=(vec2<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec2<T> & operator+=(vec2<T> & v1, const       T  & v2);
	template <typename T> friend vec2<T> & operator+=(vec2<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec2<T> & operator+=(vec2<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec2<T> & operator+=(vec2<T> & v1, const vec4<T> & v2);

	template <typename T> friend vec2<T> & operator-=(vec2<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec2<T> & operator-=(vec2<T> & v1, const       T  & v2);
	template <typename T> friend vec2<T> & operator-=(vec2<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec2<T> & operator-=(vec2<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec2<T> & operator-=(vec2<T> & v1, const vec4<T> & v2);

	template <typename T> friend vec2<T> & operator*=(vec2<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec2<T> & operator*=(vec2<T> & v1, const       T  & v2);
	template <typename T> friend vec2<T> & operator*=(vec2<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec2<T> & operator*=(vec2<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec2<T> & operator*=(vec2<T> & v1, const vec4<T> & v2);

	template <typename T> friend vec2<T> & operator/=(vec2<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec2<T> & operator/=(vec2<T> & v1, const       T  & v2);
	template <typename T> friend vec2<T> & operator/=(vec2<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec2<T> & operator/=(vec2<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec2<T> & operator/=(vec2<T> & v1, const vec4<T> & v2);

	template <typename T> friend vec2<T> & operator++(vec2<T> & v);
	template <typename T> friend vec2<T> operator++(vec2<T> & v, int);

	template <typename T> friend vec2<T> & operator--(vec2<T> & v);
	template <typename T> friend vec2<T> operator--(vec2<T> & v, int);

	template <typename T> friend vec2<T> operator+(const vec2<T> & v);

	template <typename T> friend vec2<T> operator-(const vec2<T> & v);

	template <typename T> friend vec2<T> operator+(const vec2<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec2<T> operator+(const vec2<T> & v1, const       T  & v2);
	template <typename T> friend vec2<T> operator+(const       T  & v1, const vec2<T> & v2);

	template <typename T> friend vec2<T> operator-(const vec2<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec2<T> operator-(const vec2<T> & v1, const       T  & v2);
	template <typename T> friend vec2<T> operator-(const       T  & v1, const vec2<T> & v2);

	template <typename T> friend vec2<T> operator*(const vec2<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec2<T> operator*(const vec2<T> & v1, const       T  & v2);
	template <typename T> friend vec2<T> operator*(const       T  & v1, const vec2<T> & v2);

	template <typename T> friend vec2<T> operator/(const vec2<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec2<T> operator/(const vec2<T> & v1, const       T  & v2);
	template <typename T> friend vec2<T> operator/(const       T  & v1, const vec2<T> & v2);
	template <typename T> friend vec2<T> operator/(const vec2<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec2<T> operator/(const vec1<T> & v1, const vec2<T> & v2);

	//--- comparison operators ---

	template <typename T> friend bool operator==(const vec2<T> & v1, const vec2<T> & v2);
	template <typename T> friend bool operator==(const vec2<T> & v1, const       T  & v2);
	template <typename T> friend bool operator==(const       T  & v1, const vec2<T> & v2);

	template <typename T> friend bool operator!=(const vec2<T> & v1, const vec2<T> & v2);
	template <typename T> friend bool operator!=(const vec2<T> & v1, const       T  & v2);
	template <typename T> friend bool operator!=(const       T  & v1, const vec2<T> & v2);

	template <typename T> friend bool operator<(const vec2<T> & v1, const       T  & v2);
	template <typename T> friend bool operator<(const       T  & v1, const vec2<T> & v2);

	template <typename T> friend bool operator>(const vec2<T> & v1, const       T  & v2);
	template <typename T> friend bool operator>(const       T  & v1, const vec2<T> & v2);

	template <typename T> friend bool operator<=(const vec2<T> & v1, const       T  & v2);
	template <typename T> friend bool operator<=(const       T  & v1, const vec2<T> & v2);

	template <typename T> friend bool operator>=(const vec2<T> & v1, const       T  & v2);
	template <typename T> friend bool operator>=(const       T  & v1, const vec2<T> & v2);

	//--- other ---

	std::string toString() const;

	template <typename T> friend std::ostream & operator<<(std::ostream & os, const vec2<T> & v);

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC3 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct vec<T, 3> {

	using Type = T;
	static constexpr nat t_n = 3;

	union {
		struct { T x, y, z; };
		struct { T r, g, b; };
		struct { T s, t, p; };
		struct { T rad, theta, phi; };
		struct { T lamA, lamB, lamC; };
	};

	//--- constructors ---

	constexpr vec();
	constexpr vec(const vec3<T> & v);
	constexpr vec(vec3<T> && v);

	constexpr explicit vec(const       T  & v);
	constexpr explicit vec(const vec1<T> & v);
	constexpr explicit vec(const vec2<T> & v);
	constexpr explicit vec(const vec4<T> & v);
	constexpr vec(const T & v1, const T & v2, const T & v3);

	//--- destructor ---

	~vec() {
		static_assert(std::is_standard_layout<vec<T, 3>>::value, "vec<T, 3> must be of standard layout");
		static_assert(sizeof(vec<T, 3>) == 3 * sizeof(T), "vec<T, 3> must be equal in size to 3 Ts");
	}

	//--- assignment operators ---

	vec3<T> & operator=(const vec3<T> & v);
	vec3<T> & operator=(vec3<T> && v);

	vec3<T> & operator=(const       T  & v);
	vec3<T> & operator=(const vec1<T> & v);
	vec3<T> & operator=(const vec2<T> & v);
	vec3<T> & operator=(const vec4<T> & v);

	//--- access operators ---

	T operator[](nat i);

	//--- arithmetic operators ---

	template <typename T> friend vec3<T> & operator+=(vec3<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec3<T> & operator+=(vec3<T> & v1, const       T  & v2);
	template <typename T> friend vec3<T> & operator+=(vec3<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec3<T> & operator+=(vec3<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec3<T> & operator+=(vec3<T> & v1, const vec4<T> & v2);

	template <typename T> friend vec3<T> & operator-=(vec3<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec3<T> & operator-=(vec3<T> & v1, const       T  & v2);
	template <typename T> friend vec3<T> & operator-=(vec3<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec3<T> & operator-=(vec3<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec3<T> & operator-=(vec3<T> & v1, const vec4<T> & v2);

	template <typename T> friend vec3<T> & operator*=(vec3<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec3<T> & operator*=(vec3<T> & v1, const       T  & v2);
	template <typename T> friend vec3<T> & operator*=(vec3<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec3<T> & operator*=(vec3<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec3<T> & operator*=(vec3<T> & v1, const vec4<T> & v2);

	template <typename T> friend vec3<T> & operator/=(vec3<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec3<T> & operator/=(vec3<T> & v1, const       T  & v2);
	template <typename T> friend vec3<T> & operator/=(vec3<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec3<T> & operator/=(vec3<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec3<T> & operator/=(vec3<T> & v1, const vec4<T> & v2);

	template <typename T> friend vec3<T> & operator++(vec3<T> & v);
	template <typename T> friend vec3<T> operator++(vec3<T> & v, int);

	template <typename T> friend vec3<T> & operator--(vec3<T> & v);
	template <typename T> friend vec3<T> operator--(vec3<T> & v, int);

	template <typename T> friend vec3<T> operator+(const vec3<T> & v);

	template <typename T> friend vec3<T> operator-(const vec3<T> & v);

	template <typename T> friend vec3<T> operator+(const vec3<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec3<T> operator+(const vec3<T> & v1, const       T  & v2);
	template <typename T> friend vec3<T> operator+(const       T  & v1, const vec3<T> & v2);
	template <typename T> friend vec3<T> operator+(const vec3<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec3<T> operator+(const vec1<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec3<T> operator+(const vec3<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec3<T> operator+(const vec2<T> & v1, const vec3<T> & v2);

	template <typename T> friend vec3<T> operator-(const vec3<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec3<T> operator-(const vec3<T> & v1, const       T  & v2);
	template <typename T> friend vec3<T> operator-(const       T  & v1, const vec3<T> & v2);
	template <typename T> friend vec3<T> operator-(const vec3<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec3<T> operator-(const vec1<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec3<T> operator-(const vec3<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec3<T> operator-(const vec2<T> & v1, const vec3<T> & v2);

	template <typename T> friend vec3<T> operator*(const vec3<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec3<T> operator*(const vec3<T> & v1, const       T  & v2);
	template <typename T> friend vec3<T> operator*(const       T  & v1, const vec3<T> & v2);
	template <typename T> friend vec3<T> operator*(const vec3<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec3<T> operator*(const vec1<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec3<T> operator*(const vec3<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec3<T> operator*(const vec2<T> & v1, const vec3<T> & v2);

	template <typename T> friend vec3<T> operator/(const vec3<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec3<T> operator/(const vec3<T> & v1, const       T  & v2);
	template <typename T> friend vec3<T> operator/(const       T  & v1, const vec3<T> & v2);
	template <typename T> friend vec3<T> operator/(const vec3<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec3<T> operator/(const vec1<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec3<T> operator/(const vec3<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec3<T> operator/(const vec2<T> & v1, const vec3<T> & v2);

	//--- comparison operators ---

	template <typename T> friend bool operator==(const vec3<T> & v1, const vec3<T> & v2);
	template <typename T> friend bool operator==(const vec3<T> & v1, const       T  & v2);
	template <typename T> friend bool operator==(const       T  & v1, const vec3<T> & v2);

	template <typename T> friend bool operator!=(const vec3<T> & v1, const vec3<T> & v2);
	template <typename T> friend bool operator!=(const vec3<T> & v1, const       T  & v2);
	template <typename T> friend bool operator!=(const       T  & v1, const vec3<T> & v2);

	template <typename T> friend bool operator<(const vec3<T> & v1, const       T  & v2);
	template <typename T> friend bool operator<(const       T  & v1, const vec3<T> & v2);

	template <typename T> friend bool operator>(const vec3<T> & v1, const       T  & v2);
	template <typename T> friend bool operator>(const       T  & v1, const vec3<T> & v2);

	template <typename T> friend bool operator<=(const vec3<T> & v1, const       T  & v2);
	template <typename T> friend bool operator<=(const       T  & v1, const vec3<T> & v2);

	template <typename T> friend bool operator>=(const vec3<T> & v1, const       T  & v2);
	template <typename T> friend bool operator>=(const       T  & v1, const vec3<T> & v2);

	//--- other ---

	std::string toString() const;

	template <typename T> friend std::ostream & operator<<(std::ostream & os, const vec3<T> & v);

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC4 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct vec<T, 4> {

	using Type = T;
	static constexpr nat t_n = 4;
	
	union {
		struct { T x, y, z, w; };
		struct { T r, g, b, a; };
		struct { T s, t, p, q; };
		struct { T x, y, width, height; };
	};
	
	//--- constructors ---

	constexpr vec();
	constexpr vec(const vec4<T> & v);
	constexpr vec(vec4<T> && v);

	constexpr explicit vec(const       T  & v);
	constexpr explicit vec(const vec1<T> & v);
	constexpr explicit vec(const vec2<T> & v);
	constexpr explicit vec(const vec3<T> & v);
	constexpr vec(const T & v1, const T & v2, const T & v3, const T & v4);

	//--- destructor ---

	~vec() {
		static_assert(std::is_standard_layout<vec<T, 4>>::value, "vec<T, 4> must be of standard layout");
		static_assert(sizeof(vec<T, 4>) == 4 * sizeof(T), "vec<T, 4> must be equal in size to 4 Ts");
	}

	//--- assignment operators ---

	vec4<T> & operator=(const vec4<T> & v);
	vec4<T> & operator=(vec4<T> && v);

	vec4<T> & operator=(const       T  & v);
	vec4<T> & operator=(const vec1<T> & v);
	vec4<T> & operator=(const vec2<T> & v);
	vec4<T> & operator=(const vec3<T> & v);

	//--- access operators ---
	
	T operator[](nat i);

	//--- arithmetic operators ---

	template <typename T> friend vec4<T> & operator+=(vec4<T> & v1, const vec4<T> & v2);
	template <typename T> friend vec4<T> & operator+=(vec4<T> & v1, const       T  & v2);
	template <typename T> friend vec4<T> & operator+=(vec4<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec4<T> & operator+=(vec4<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec4<T> & operator+=(vec4<T> & v1, const vec3<T> & v2);

	template <typename T> friend vec4<T> & operator-=(vec4<T> & v1, const vec4<T> & v2);
	template <typename T> friend vec4<T> & operator-=(vec4<T> & v1, const       T  & v2);
	template <typename T> friend vec4<T> & operator-=(vec4<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec4<T> & operator-=(vec4<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec4<T> & operator-=(vec4<T> & v1, const vec3<T> & v2);

	template <typename T> friend vec4<T> & operator*=(vec4<T> & v1, const vec4<T> & v2);
	template <typename T> friend vec4<T> & operator*=(vec4<T> & v1, const       T  & v2);
	template <typename T> friend vec4<T> & operator*=(vec4<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec4<T> & operator*=(vec4<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec4<T> & operator*=(vec4<T> & v1, const vec3<T> & v2);

	template <typename T> friend vec4<T> & operator/=(vec4<T> & v1, const vec4<T> & v2);
	template <typename T> friend vec4<T> & operator/=(vec4<T> & v1, const       T  & v2);
	template <typename T> friend vec4<T> & operator/=(vec4<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec4<T> & operator/=(vec4<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec4<T> & operator/=(vec4<T> & v1, const vec3<T> & v2);

	template <typename T> friend vec4<T> & operator++(vec4<T> & v);
	template <typename T> friend vec4<T> operator++(vec4<T> & v, int);

	template <typename T> friend vec4<T> & operator--(vec4<T> & v);
	template <typename T> friend vec4<T> operator--(vec4<T> & v, int);

	template <typename T> friend vec4<T> operator+(const vec4<T> & v);

	template <typename T> friend vec4<T> operator-(const vec4<T> & v);

	template <typename T> friend vec4<T> operator+(const vec4<T> & v1, const vec4<T> & v2);
	template <typename T> friend vec4<T> operator+(const vec4<T> & v1, const       T  & v2);
	template <typename T> friend vec4<T> operator+(const       T  & v1, const vec4<T> & v2);
	template <typename T> friend vec4<T> operator+(const vec4<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec4<T> operator+(const vec1<T> & v1, const vec4<T> & v2);
	template <typename T> friend vec4<T> operator+(const vec4<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec4<T> operator+(const vec2<T> & v1, const vec4<T> & v2);
	template <typename T> friend vec4<T> operator+(const vec4<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec4<T> operator+(const vec3<T> & v1, const vec4<T> & v2);

	template <typename T> friend vec4<T> operator-(const vec4<T> & v1, const vec4<T> & v2);
	template <typename T> friend vec4<T> operator-(const vec4<T> & v1, const       T  & v2);
	template <typename T> friend vec4<T> operator-(const       T  & v1, const vec4<T> & v2);
	template <typename T> friend vec4<T> operator-(const vec4<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec4<T> operator-(const vec1<T> & v1, const vec4<T> & v2);
	template <typename T> friend vec4<T> operator-(const vec4<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec4<T> operator-(const vec2<T> & v1, const vec4<T> & v2);
	template <typename T> friend vec4<T> operator-(const vec4<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec4<T> operator-(const vec3<T> & v1, const vec4<T> & v2);

	template <typename T> friend vec4<T> operator*(const vec4<T> & v1, const vec4<T> & v2);
	template <typename T> friend vec4<T> operator*(const vec4<T> & v1, const       T  & v2);
	template <typename T> friend vec4<T> operator*(const       T  & v1, const vec4<T> & v2);
	template <typename T> friend vec4<T> operator*(const vec4<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec4<T> operator*(const vec1<T> & v1, const vec4<T> & v2);
	template <typename T> friend vec4<T> operator*(const vec4<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec4<T> operator*(const vec2<T> & v1, const vec4<T> & v2);
	template <typename T> friend vec4<T> operator*(const vec4<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec4<T> operator*(const vec3<T> & v1, const vec4<T> & v2);

	template <typename T> friend vec4<T> operator/(const vec4<T> & v1, const vec4<T> & v2);
	template <typename T> friend vec4<T> operator/(const vec4<T> & v1, const       T  & v2);
	template <typename T> friend vec4<T> operator/(const       T  & v1, const vec4<T> & v2);
	template <typename T> friend vec4<T> operator/(const vec4<T> & v1, const vec1<T> & v2);
	template <typename T> friend vec4<T> operator/(const vec1<T> & v1, const vec4<T> & v2);
	template <typename T> friend vec4<T> operator/(const vec4<T> & v1, const vec2<T> & v2);
	template <typename T> friend vec4<T> operator/(const vec2<T> & v1, const vec4<T> & v2);
	template <typename T> friend vec4<T> operator/(const vec4<T> & v1, const vec3<T> & v2);
	template <typename T> friend vec4<T> operator/(const vec3<T> & v1, const vec4<T> & v2);

	//--- comparison operators ---

	template <typename T> friend bool operator==(const vec4<T> & v1, const vec4<T> & v2);
	template <typename T> friend bool operator==(const vec4<T> & v1, const       T  & v2);
	template <typename T> friend bool operator==(const       T  & v1, const vec4<T> & v2);

	template <typename T> friend bool operator!=(const vec4<T> & v1, const vec4<T> & v2);
	template <typename T> friend bool operator!=(const vec4<T> & v1, const       T  & v2);
	template <typename T> friend bool operator!=(const       T  & v1, const vec4<T> & v2);

	template <typename T> friend bool operator<(const vec4<T> & v1, const       T  & v2);
	template <typename T> friend bool operator<(const       T  & v1, const vec4<T> & v2);

	template <typename T> friend bool operator>(const vec4<T> & v1, const       T  & v2);
	template <typename T> friend bool operator>(const       T  & v1, const vec4<T> & v2);

	template <typename T> friend bool operator<=(const vec4<T> & v1, const       T  & v2);
	template <typename T> friend bool operator<=(const       T  & v1, const vec4<T> & v2);

	template <typename T> friend bool operator>=(const vec4<T> & v1, const       T  & v2);
	template <typename T> friend bool operator>=(const       T  & v1, const vec4<T> & v2);

	//--- other ---

	std::string toString() const;

	template <typename T> friend std::ostream & operator<<(std::ostream & os, const vec4<T> & v);

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC6 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct vec<T, 6> {

	using Type = T;
	static constexpr nat t_n = 6;

	T x, y, z, width, height, depth;

	//--- constructors ---

	constexpr vec();
	constexpr vec(const bound3<T> & v);
	constexpr vec(bound3<T> && v);

	constexpr vec(const vec3<T> & v1, const vec3<T> & v2);
	constexpr vec(const T & v1, const T & v2, const T & v3, const T & v4, const T & v5, const T & v6);

	//--- destructor ---

	~vec() {
		static_assert(std::is_standard_layout<vec<T, 6>>::value, "vec<T, 6> must be of standard layout");
		static_assert(sizeof(vec<T, 6>) == 6 * sizeof(T), "vec<T, 6> must be equal in size to 6 Ts");
	}

	//--- assignment operators ---

	bound3<T> & operator=(const bound3<T> & v);
	bound3<T> & operator=(bound3<T> && v);

	//--- access operators ---

	T operator[](nat i);

	//--- comparison operators ---

	template <typename T> friend bool operator==(const bound3<T> & v1, const bound3<T> & v2);

	template <typename T> friend bool operator!=(const bound3<T> & v1, const bound3<T> & v2);

	//--- other ---

	std::string toString() const;

	template <typename T> friend std::ostream & operator<<(std::ostream & os, const bound3<T> & v);

	static_assert(     std::is_pod<vec<T, 6>>::value, "vec6<T> must be P.O.D.");
	static_assert(sizeof(vec<T, 6>) == 3 * sizeof(T), "vec6<T> must be equal in size to six Ts");

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC FUNCTIONS -------------------------------------------------------------------------------------------------------



template <typename T, nat t_n>
T mag(const vec<T, t_n> & v);

template <typename T, nat t_n>
T mag2(const vec<T, t_n> & a);

template <typename T, nat t_n>
vec<T, t_n> norm(const vec<T, t_n> & a);

template <typename T, nat t_n>
T dot(const vec<T, t_n> & a, const vec<T, t_n> & b);

template <typename T>
vec3<T> cross(const vec3<T> & a, const vec3<T> & b);

template <typename T, nat t_n>
T angle(const vec<T, t_n> & a, const vec<T, t_n> & b);

template <typename T, nat t_n>
vec<T, t_n> lerp(const vec<T, t_n> & v1, const vec<T, t_n> & v2, T t);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC1 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr vec<T, 1>::vec() :
	x(static_cast<T>(0))
{}

template <typename T>
constexpr vec<T, 1>::vec(const vec1<T> & v) :
	x(v.x)
{}

template <typename T>
constexpr vec<T, 1>::vec(vec1<T> && v) :
	x(v.x)
{}

template <typename T>
constexpr vec<T, 1>::vec(const T & v) :
	x(v)
{}

template <typename T>
constexpr vec<T, 1>::vec(const vec2<T> & v) :
	x(v.x)
{}

template <typename T>
constexpr vec<T, 1>::vec(const vec3<T> & v) :
	x(v.x)
{}

template <typename T>
constexpr vec<T, 1>::vec(const vec4<T> & v) :
	x(v.x)
{}



//------------------------------------------------------------------------------
// Assignment Operators



template <typename T>
vec1<T> & vec<T, 1>::operator=(const vec1<T> & v) {
	x = v.x;
	return *this;
}

template <typename T>
vec1<T> & vec<T, 1>::operator=(vec1<T> && v) {
	x = v.x;
	return *this;
}

template <typename T>
vec1<T> & vec<T, 1>::operator=(const T & v) {
	x = v;
	return *this;
}

template <typename T>
vec1<T> & vec<T, 1>::operator=(const vec2<T> & v) {
	x = v.x;
	return *this;
}

template <typename T>
vec1<T> & vec<T, 1>::operator=(const vec3<T> & v) {
	x = v.x;
	return *this;
}

template <typename T>
vec1<T> & vec<T, 1>::operator=(const vec4<T> & v) {
	x = v.x;
	return *this;
}



//------------------------------------------------------------------------------
// Access Operators



template <typename T>
T vec<T, 1>::operator[](nat i) {
	return *(&x + i);
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- add assign ---

template <typename T>
inline vec1<T> & operator+=(vec1<T> & v1, const vec1<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline vec1<T> & operator+=(vec1<T> & v1, const T & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline vec1<T> & operator+=(vec1<T> & v1, const vec2<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline vec1<T> & operator+=(vec1<T> & v1, const vec3<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline vec1<T> & operator+=(vec1<T> & v1, const vec4<T> & v2) {
	return v1 = v1 + v2;
}

//--- subtract assign ---

template <typename T>
inline vec1<T> & operator-=(vec1<T> & v1, const vec1<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline vec1<T> & operator-=(vec1<T> & v1, const T & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline vec1<T> & operator-=(vec1<T> & v1, const vec2<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline vec1<T> & operator-=(vec1<T> & v1, const vec3<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline vec1<T> & operator-=(vec1<T> & v1, const vec4<T> & v2) {
	return v1 = v1 - v2;
}

//--- multiply assign ---

template <typename T>
inline vec1<T> & operator*=(vec1<T> & v1, const vec1<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline vec1<T> & operator*=(vec1<T> & v1, const T & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline vec1<T> & operator*=(vec1<T> & v1, const vec2<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline vec1<T> & operator*=(vec1<T> & v1, const vec3<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline vec1<T> & operator*=(vec1<T> & v1, const vec4<T> & v2) {
	return v1 = v1 * v2;
}

//--- divide assign ---

template <typename T>
inline vec1<T> & operator/=(vec1<T> & v1, const vec1<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline vec1<T> & operator/=(vec1<T> & v1, const T & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline vec1<T> & operator/=(vec1<T> & v1, const vec2<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline vec1<T> & operator/=(vec1<T> & v1, const vec3<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline vec1<T> & operator/=(vec1<T> & v1, const vec4<T> & v2) {
	return v1 = v1 / v2;
}

//--- pre increment ---

template <typename T>
inline vec1<T> & operator++(vec1<T> & v) {
	++v.x;
	return v;
}

//--- post increment ---

template <typename T>
inline vec1<T> operator++(vec1<T> & v, int) {
	return vec1<T>(v.x++);
}

//--- pre decrement ---

template <typename T>
inline vec1<T> & operator--(vec1<T> & v) {
	--v.x;
	return v;
}

//--- post decrement ---

template <typename T>
inline vec1<T> operator--(vec1<T> & v, int) {
	return vec1<T>(v.x--);
}

//--- positive ---

template <typename T>
inline vec1<T> operator+(const vec1<T> & v) {
	return v;
}

//--- negative ---

template <typename T>
inline vec1<T> operator-(const vec1<T> & v) {
	return v * static_cast<T>(-1);
}

//--- add ---

template <typename T>
inline vec1<T> operator+(const vec1<T> & v1, const vec1<T> & v2) {
	return vec1<T>(v1.x + v2.x);
}

template <typename T>
inline vec1<T> operator+(const vec1<T> & v1, const T & v2) {
	return vec1<T>(v1.x + v2);
}

template <typename T>
inline vec1<T> operator+(const T & v1, const vec1<T> & v2) {
	return vec1<T>(v1 + v2.x);
}

//--- subtract ---

template <typename T>
inline vec1<T> operator-(const vec1<T> & v1, const vec1<T> & v2) {
	return vec1<T>(v1.x - v2.x);
}

template <typename T>
inline vec1<T> operator-(const vec1<T> & v1, const T & v2) {
	return vec1<T>(v1.x - v2);
}

template <typename T>
inline vec1<T> operator-(const T & v1, const vec1<T> & v2) {
	return vec1<T>(v1 - v2.x);
}

//--- multiply ---

template <typename T>
inline vec1<T> operator*(const vec1<T> & v1, const vec1<T> & v2) {
	return vec1<T>(v1.x * v2.x);
}

template <typename T>
inline vec1<T> operator*(const vec1<T> & v1, const T & v2) {
	return vec1<T>(v1.x * v2);
}

template <typename T>
inline vec1<T> operator*(const T & v1, const vec1<T> & v2) {
	return vec1<T>(v1 * v2.x);
}

//--- divide ---

template <typename T>
inline vec1<T> operator/(const vec1<T> & v1, const vec1<T> & v2) {
	return vec1<T>(v1.x / v2.x);
}

template <typename T>
inline vec1<T> operator/(const vec1<T> & v1, const T & v2) {
	return vec1<T>(v1.x / v2);
}

template <typename T>
inline vec1<T> operator/(const T & v1, const vec1<T> & v2) {
	return vec1<T>(v1 / v2.x);
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T>
inline bool operator==(const vec1<T> & v1, const vec1<T> & v2) {
	return v1.x == v2.x;
}

template <typename T>
inline bool operator==(const vec1<T> & v1, const T & v2) {
	return v1.x == v2;
}

template <typename T>
inline bool operator==(const T & v1, const vec1<T> & v2) {
	return v1 == v2.x;
}

//--- not equal to ---

template <typename T>
inline bool operator!=(const vec1<T> & v1, const vec1<T> & v2) {
	return v1.x != v2.x;
}

template <typename T>
inline bool operator!=(const vec1<T> & v1, const T & v2) {
	return v1.x != v2;
}

template <typename T>
inline bool operator!=(const T & v1, const vec1<T> & v2) {
	return v1 != v2.x;
}

//--- less than ---

template <typename T>
inline bool operator<(const vec1<T> & v1, const T & v2) {
	return v1.x < v2;
}

template <typename T>
inline bool operator<(const T & v1, const vec1<T> & v2) {
	return  v1 < v2.x;
}

//--- greater than ---

template <typename T>
inline bool operator>(const vec1<T> & v1, const T & v2) {
	return v1.x > v2;
}

template <typename T>
inline bool operator>(const T & v1, const vec1<T> & v2) {
	return  v1 > v2.x;
}

//--- less than or equal to ---

template <typename T>
inline bool operator<=(const vec1<T> & v1, const T & v2) {
	return v1.x <= v2;
}

template <typename T>
inline bool operator<=(const T & v1, const vec1<T> & v2) {
	return  v1 <= v2.x;
}

//--- greater than or equal to ---

template <typename T>
inline bool operator>=(const vec1<T> & v1, const T & v2) {
	return v1.x >= v2;
}

template <typename T>
inline bool operator>=(const T & v1, const vec1<T> & v2) {
	return  v1 >= v2.x;
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string vec<T, 1>::toString() const {
	std::stringstream ss;
	ss << "(" << x << ")";
	return ss.str();
}



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const vec1<T> & v) {
	return os << v.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC2 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr vec<T, 2>::vec() :
	x(static_cast<T>(0)), y(static_cast<T>(0))
{}

template <typename T>
constexpr vec<T, 2>::vec(const vec2<T> & v) :
	x(v.x), y(v.y)
{}

template <typename T>
constexpr vec<T, 2>::vec(vec2<T> && v) :
	x(v.x), y(v.y)
{}

template <typename T>
constexpr vec<T, 2>::vec(const T & v) :
	x(v), y(v)
{}

template <typename T>
constexpr vec<T, 2>::vec(const vec1<T> & v) :
	x(v.x), y(static_cast<T>(0))
{}

template <typename T>
constexpr vec<T, 2>::vec(const vec3<T> & v) :
	x(v.x), y(v.y)
{}

template <typename T>
constexpr vec<T, 2>::vec(const vec4<T> & v) :
	x(v.x), y(v.y)
{}

template <typename T>
constexpr vec<T, 2>::vec(const T & v1, const T & v2) :
	x(v1), y(v2)
{}



//------------------------------------------------------------------------------
// Assignment Operators



template <typename T>
vec2<T> & vec<T, 2>::operator=(const vec2<T> & v) {
	x = v.x; y = v.y;
	return *this;
}

template <typename T>
vec2<T> & vec<T, 2>::operator=(vec2<T> && v) {
	x = v.x; y = v.y;
	return *this;
}

template <typename T>
vec2<T> & vec<T, 2>::operator=(const T & v) {
	x = v; y = v;
	return *this;
}

template <typename T>
vec2<T> & vec<T, 2>::operator=(const vec1<T> & v) {
	x = v.x; y = static_cast<T>(0);
	return *this;
}

template <typename T>
vec2<T> & vec<T, 2>::operator=(const vec3<T> & v) {
	x = v.x; y = v.y;
	return *this;
}

template <typename T>
vec2<T> & vec<T, 2>::operator=(const vec4<T> & v) {
	x = v.x; y = v.y;
	return *this;
}



//------------------------------------------------------------------------------
// Access Operators



template <typename T>
T vec<T, 2>::operator[](nat i) {
	return *(&x + i);
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- add assign ---

template <typename T>
inline vec2<T> & operator+=(vec2<T> & v1, const vec2<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline vec2<T> & operator+=(vec2<T> & v1, const T & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline vec2<T> & operator+=(vec2<T> & v1, const vec1<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline vec2<T> & operator+=(vec2<T> & v1, const vec3<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline vec2<T> & operator+=(vec2<T> & v1, const vec4<T> & v2) {
	return v1 = v1 + v2;
}

//--- subtract assign ---

template <typename T>
inline vec2<T> & operator-=(vec2<T> & v1, const vec2<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline vec2<T> & operator-=(vec2<T> & v1, const T & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline vec2<T> & operator-=(vec2<T> & v1, const vec1<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline vec2<T> & operator-=(vec2<T> & v1, const vec3<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline vec2<T> & operator-=(vec2<T> & v1, const vec4<T> & v2) {
	return v1 = v1 - v2;
}

//--- multiply assign ---

template <typename T>
inline vec2<T> & operator*=(vec2<T> & v1, const vec2<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline vec2<T> & operator*=(vec2<T> & v1, const T & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline vec2<T> & operator*=(vec2<T> & v1, const vec1<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline vec2<T> & operator*=(vec2<T> & v1, const vec3<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline vec2<T> & operator*=(vec2<T> & v1, const vec4<T> & v2) {
	return v1 = v1 * v2;
}

//--- divide assign ---

template <typename T>
inline vec2<T> & operator/=(vec2<T> & v1, const vec2<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline vec2<T> & operator/=(vec2<T> & v1, const T & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline vec2<T> & operator/=(vec2<T> & v1, const vec1<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline vec2<T> & operator/=(vec2<T> & v1, const vec3<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline vec2<T> & operator/=(vec2<T> & v1, const vec4<T> & v2) {
	return v1 = v1 / v2;
}

//--- pre increment ---

template <typename T>
inline vec2<T> & operator++(vec2<T> & v) {
	++v.x; ++v.y;
	return v;
}

//--- post increment ---

template <typename T>
inline vec2<T> operator++(vec2<T> & v, int) {
	return vec2<T>(v.x++, v.y++);
}

//--- pre decrement ---

template <typename T>
inline vec2<T> & operator--(vec2<T> & v) {
	--v.x; --v.y;
	return v;
}

//--- post decrement ---

template <typename T>
inline vec2<T> operator--(vec2<T> & v, int) {
	return vec2<T>(v.x--, v.y--);
}

//--- positive ---

template <typename T>
inline vec2<T> operator+(const vec2<T> & v) {
	return v;
}

//--- negative ---

template <typename T>
inline vec2<T> operator-(const vec2<T> & v) {
	return v * static_cast<T>(-1);
}

//--- add ---

template <typename T>
inline vec2<T> operator+(const vec2<T> & v1, const vec2<T> & v2) {
	return vec2<T>(v1.x + v2.x, v1.y + v2.y);
}

template <typename T>
inline vec2<T> operator+(const vec2<T> & v1, const T & v2) {
	return vec2<T>(v1.x + v2, v1.y + v2);
}

template <typename T>
inline vec2<T> operator+(const T & v1, const vec2<T> & v2) {
	return vec2<T>(v1 + v2.x, v1 + v2.y);
}

template <typename T>
inline vec2<T> operator+(const vec2<T> & v1, const vec1<T> & v2) {
	return vec2<T>(v1.x + v2.x, v1.y);
}

template <typename T>
inline vec2<T> operator+(const vec1<T> & v1, const vec2<T> & v2) {
	return vec2<T>(v1.x + v2.x, v2.y);
}

//--- subtract ---

template <typename T>
inline vec2<T> operator-(const vec2<T> & v1, const vec2<T> & v2) {
	return vec2<T>(v1.x - v2.x, v1.y - v2.y);
}

template <typename T>
inline vec2<T> operator-(const vec2<T> & v1, const T & v2) {
	return vec2<T>(v1.x - v2, v1.y - v2);
}

template <typename T>
inline vec2<T> operator-(const T & v1, const vec2<T> & v2) {
	return vec2<T>(v1 - v2.x, v1 - v2.y);
}

template <typename T>
inline vec2<T> operator-(const vec2<T> & v1, const vec1<T> & v2) {
	return vec2<T>(v1.x - v2.x, v1.y);
}

template <typename T>
inline vec2<T> operator-(const vec1<T> & v1, const vec2<T> & v2) {
	return vec2<T>(v1.x - v2.x, v2.y);
}

//--- multiply ---

template <typename T>
inline vec2<T> operator*(const vec2<T> & v1, const vec2<T> & v2) {
	return vec2<T>(v1.x * v2.x, v1.y * v2.y);
}

template <typename T>
inline vec2<T> operator*(const vec2<T> & v1, const T & v2) {
	return vec2<T>(v1.x * v2, v1.y * v2);
}

template <typename T>
inline vec2<T> operator*(const T & v1, const vec2<T> & v2) {
	return vec2<T>(v1 * v2.x, v1 * v2.y);
}

template <typename T>
inline vec2<T> operator*(const vec2<T> & v1, const vec1<T> & v2) {
	return vec2<T>(v1.x * v2.x, v1.y);
}

template <typename T>
inline vec2<T> operator*(const vec1<T> & v1, const vec2<T> & v2) {
	return vec2<T>(v1.x * v2.x, v2.y);
}

//--- divide ---

template <typename T>
inline vec2<T> operator/(const vec2<T> & v1, const vec2<T> & v2) {
	return vec2<T>(v1.x / v2.x, v1.y / v2.y);
}

template <typename T>
inline vec2<T> operator/(const vec2<T> & v1, const T & v2) {
	return vec2<T>(v1.x / v2, v1.y / v2);
}

template <typename T>
inline vec2<T> operator/(const T & v1, const vec2<T> & v2) {
	return vec2<T>(v1 / v2.x, v1 / v2.y);
}

template <typename T>
inline vec2<T> operator/(const vec2<T> & v1, const vec1<T> & v2) {
	return vec2<T>(v1.x / v2.x, v1.y);
}

template <typename T>
inline vec2<T> operator/(const vec1<T> & v1, const vec2<T> & v2) {
	return vec2<T>(v1.x / v2.x, v2.y);
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T>
inline bool operator==(const vec2<T> & v1, const vec2<T> & v2) {
	return v1.x == v2.x && v1.y == v2.y;
}

template <typename T>
inline bool operator==(const vec2<T> & v1, const T & v2) {
	return v1.x == v2 && v1.y == v2;
}

template <typename T>
inline bool operator==(const T & v1, const vec2<T> & v2) {
	return v1 == v2.x && v1 == v2.y;
}

//--- not equal to ---

template <typename T>
inline bool operator!=(const vec2<T> & v1, const vec2<T> & v2) {
	return v1.x != v2.x || v1.y != v2.y;
}

template <typename T>
inline bool operator!=(const vec2<T> & v1, const T & v2) {
	return v1.x != v2 || v1.y != v2;
}

template <typename T>
inline bool operator!=(const T & v1, const vec2<T> & v2) {
	return v1 != v2.x || v1 != v2.y;
}

//--- less than ---

template <typename T>
inline bool operator<(const vec2<T> & v1, const T & v2) {
	return v1.x < v2 && v1.y < v2;
}

template <typename T>
inline bool operator<(const T & v1, const vec2<T> & v2) {
	return  v1 < v2.x && v1 < v2.y;
}

//--- greater than ---

template <typename T>
inline bool operator>(const vec2<T> & v1, const T & v2) {
	return v1.x > v2 && v1.y > v2;
}

template <typename T>
inline bool operator>(const T & v1, const vec2<T> & v2) {
	return  v1 > v2.x && v1 > v2.y;
}

//--- less than or equal to ---

template <typename T>
inline bool operator<=(const vec2<T> & v1, const T & v2) {
	return v1.x <= v2 && v1.y <= v2;
}

template <typename T>
inline bool operator<=(const T & v1, const vec2<T> & v2) {
	return  v1 <= v2.x && v1 <= v2.y;
}

//--- greater than or equal to ---

template <typename T>
inline bool operator>=(const vec2<T> & v1, const T & v2) {
	return v1.x >= v2 && v1.y >= v2;
}

template <typename T>
inline bool operator>=(const T & v1, const vec2<T> & v2) {
	return  v1 >= v2.x && v1 >= v2.y;
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string vec<T, 2>::toString() const {
	std::stringstream ss;
	ss << "(" << x << ", " << y << ")";
	return ss.str();
}



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const vec2<T> & v) {
	return os << v.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC3 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr vec<T, 3>::vec() :
	x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0))
{}

template <typename T>
constexpr vec<T, 3>::vec(const vec3<T> & v) :
	x(v.x), y(v.y), z(v.z)
{}

template <typename T>
constexpr vec<T, 3>::vec(vec3<T> && v) :
	x(v.x), y(v.y), z(v.z)
{}

template <typename T>
constexpr vec<T, 3>::vec(const T & v) :
	x(v), y(v), z(v)
{}

template <typename T>
constexpr vec<T, 3>::vec(const vec1<T> & v) :
	x(v.x), y(static_cast<T>(0)), z(static_cast<T>(0))
{}

template <typename T>
constexpr vec<T, 3>::vec(const vec2<T> & v) :
	x(v.x), y(v.y), z(static_cast<T>(0))
{}

template <typename T>
constexpr vec<T, 3>::vec(const vec4<T> & v) :
	x(v.x), y(v.y), z(v.z)
{}

template <typename T>
constexpr vec<T, 3>::vec(const T & v1, const T & v2, const T & v3) :
	x(v1), y(v2), z(v3)
{}



//------------------------------------------------------------------------------
// Assignment Operators



template <typename T>
vec3<T> & vec<T, 3>::operator=(const vec3<T> & v) {
	x = v.x; y = v.y; z = v.z;
	return *this;
}

template <typename T>
vec3<T> & vec<T, 3>::operator=(vec3<T> && v) {
	x = v.x; y = v.y; z = v.z;
	return *this;
}

template <typename T>
vec3<T> & vec<T, 3>::operator=(const T & v) {
	x = v; y = v; z = v;
	return *this;
}

template <typename T>
vec3<T> & vec<T, 3>::operator=(const vec1<T> & v) {
	x = v.x; y = static_cast<T>(0); z = static_cast<T>(0);
	return *this;
}

template <typename T>
vec3<T> & vec<T, 3>::operator=(const vec2<T> & v) {
	x = v.x; y = v.y; z = static_cast<T>(0);
	return *this;
}

template <typename T>
vec3<T> & vec<T, 3>::operator=(const vec4<T> & v) {
	x = v.x; y = v.y; z = v.z;
	return *this;
}



//------------------------------------------------------------------------------
// Access Operators



template <typename T>
T vec<T, 3>::operator[](nat i) {
	return *(&x + i);
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- add assign ---

template <typename T>
inline vec3<T> & operator+=(vec3<T> & v1, const vec3<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline vec3<T> & operator+=(vec3<T> & v1, const T & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline vec3<T> & operator+=(vec3<T> & v1, const vec1<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline vec3<T> & operator+=(vec3<T> & v1, const vec2<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline vec3<T> & operator+=(vec3<T> & v1, const vec4<T> & v2) {
	return v1 = v1 + v2;
}

//--- subtract assign ---

template <typename T>
inline vec3<T> & operator-=(vec3<T> & v1, const vec3<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline vec3<T> & operator-=(vec3<T> & v1, const T & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline vec3<T> & operator-=(vec3<T> & v1, const vec1<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline vec3<T> & operator-=(vec3<T> & v1, const vec2<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline vec3<T> & operator-=(vec3<T> & v1, const vec4<T> & v2) {
	return v1 = v1 - v2;
}

//--- multiply assign ---

template <typename T>
inline vec3<T> & operator*=(vec3<T> & v1, const vec3<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline vec3<T> & operator*=(vec3<T> & v1, const T & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline vec3<T> & operator*=(vec3<T> & v1, const vec1<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline vec3<T> & operator*=(vec3<T> & v1, const vec2<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline vec3<T> & operator*=(vec3<T> & v1, const vec4<T> & v2) {
	return v1 = v1 * v2;
}

//--- divide assign ---

template <typename T>
inline vec3<T> & operator/=(vec3<T> & v1, const vec3<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline vec3<T> & operator/=(vec3<T> & v1, const T & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline vec3<T> & operator/=(vec3<T> & v1, const vec1<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline vec3<T> & operator/=(vec3<T> & v1, const vec2<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline vec3<T> & operator/=(vec3<T> & v1, const vec4<T> & v2) {
	return v1 = v1 / v2;
}

//--- pre increment ---

template <typename T>
inline vec3<T> & operator++(vec3<T> & v) {
	++v.x; ++v.y; ++v.z;
	return v;
}

//--- post increment ---

template <typename T>
inline vec3<T> operator++(vec3<T> & v, int) {
	return vec3<T>(v.x++, v.y++, v.z++);
}

//--- pre decrement ---

template <typename T>
inline vec3<T> & operator--(vec3<T> & v) {
	--v.x; --v.y; --v.z;
	return v;
}

//--- post decrement ---

template <typename T>
inline vec3<T> operator--(vec3<T> & v, int) {
	return vec3<T>(v.x--, v.y--, v.z--);
}

//--- positive ---

template <typename T>
inline vec3<T> operator+(const vec3<T> & v) {
	return v;
}

//--- negative ---

template <typename T>
inline vec3<T> operator-(const vec3<T> & v) {
	return v * static_cast<T>(-1);
}

//--- add ---

template <typename T>
inline vec3<T> operator+(const vec3<T> & v1, const vec3<T> & v2) {
	return vec3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

template <typename T>
inline vec3<T> operator+(const vec3<T> & v1, const T & v2) {
	return vec3<T>(v1.x + v2, v1.y + v2, v1.z + v2);
}

template <typename T>
inline vec3<T> operator+(const T & v1, const vec3<T> & v2) {
	return vec3<T>(v1 + v2.x, v1 + v2.y, v1 + v2.z);
}

template <typename T>
inline vec3<T> operator+(const vec3<T> & v1, const vec1<T> & v2) {
	return vec3<T>(v1.x + v2.x, v1.y, v1.z);
}

template <typename T>
inline vec3<T> operator+(const vec1<T> & v1, const vec3<T> & v2) {
	return vec3<T>(v1.x + v2.x, v2.y, v2.z);
}

template <typename T>
inline vec3<T> operator+(const vec3<T> & v1, const vec2<T> & v2) {
	return vec3<T>(v1.x + v2.x, v1.y + v2.y, v1.z);
}

template <typename T>
inline vec3<T> operator+(const vec2<T> & v1, const vec3<T> & v2) {
	return vec3<T>(v1.x + v2.x, v1.y + v2.y, v2.z);
}

//--- subtract ---

template <typename T>
inline vec3<T> operator-(const vec3<T> & v1, const vec3<T> & v2) {
	return vec3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

template <typename T>
inline vec3<T> operator-(const vec3<T> & v1, const T & v2) {
	return vec3<T>(v1.x - v2, v1.y - v2, v1.z - v2);
}

template <typename T>
inline vec3<T> operator-(const T & v1, const vec3<T> & v2) {
	return vec3<T>(v1 - v2.x, v1 - v2.y, v1 - v2.z);
}

template <typename T>
inline vec3<T> operator-(const vec3<T> & v1, const vec1<T> & v2) {
	return vec3<T>(v1.x - v2.x, v1.y, v1.z);
}

template <typename T>
inline vec3<T> operator-(const vec1<T> & v1, const vec3<T> & v2) {
	return vec3<T>(v1.x - v2.x, v2.y, v2.z);
}

template <typename T>
inline vec3<T> operator-(const vec3<T> & v1, const vec2<T> & v2) {
	return vec3<T>(v1.x - v2.x, v1.y - v2.y, v1.z);
}

template <typename T>
inline vec3<T> operator-(const vec2<T> & v1, const vec3<T> & v2) {
	return vec3<T>(v1.x - v2.x, v1.y - v2.y, v2.z);
}

//--- multiply ---

template <typename T>
inline vec3<T> operator*(const vec3<T> & v1, const vec3<T> & v2) {
	return vec3<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

template <typename T>
inline vec3<T> operator*(const vec3<T> & v1, const T & v2) {
	return vec3<T>(v1.x * v2, v1.y * v2, v1.z * v2);
}

template <typename T>
inline vec3<T> operator*(const T & v1, const vec3<T> & v2) {
	return vec3<T>(v1 * v2.x, v1 * v2.y, v1 * v2.z);
}

template <typename T>
inline vec3<T> operator*(const vec3<T> & v1, const vec1<T> & v2) {
	return vec3<T>(v1.x * v2.x, v1.y, v1.z);
}

template <typename T>
inline vec3<T> operator*(const vec1<T> & v1, const vec3<T> & v2) {
	return vec3<T>(v1.x * v2.x, v2.y, v2.z);
}

template <typename T>
inline vec3<T> operator*(const vec3<T> & v1, const vec2<T> & v2) {
	return vec3<T>(v1.x * v2.x, v1.y * v2.y, v1.z);
}

template <typename T>
inline vec3<T> operator*(const vec2<T> & v1, const vec3<T> & v2) {
	return vec3<T>(v1.x * v2.x, v1.y * v2.y, v2.z);
}

//--- divide ---

template <typename T>
inline vec3<T> operator/(const vec3<T> & v1, const vec3<T> & v2) {
	return vec3<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

template <typename T>
inline vec3<T> operator/(const vec3<T> & v1, const T & v2) {
	return vec3<T>(v1.x / v2, v1.y / v2, v1.z / v2);
}

template <typename T>
inline vec3<T> operator/(const T & v1, const vec3<T> & v2) {
	return vec3<T>(v1 / v2.x, v1 / v2.y, v1 / v2.z);
}

template <typename T>
inline vec3<T> operator/(const vec3<T> & v1, const vec1<T> & v2) {
	return vec3<T>(v1.x / v2.x, v1.y, v1.z);
}

template <typename T>
inline vec3<T> operator/(const vec1<T> & v1, const vec3<T> & v2) {
	return vec3<T>(v1.x / v2.x, v2.y, v2.z);
}

template <typename T>
inline vec3<T> operator/(const vec3<T> & v1, const vec2<T> & v2) {
	return vec3<T>(v1.x / v2.x, v1.y / v2.y, v1.z);
}

template <typename T>
inline vec3<T> operator/(const vec2<T> & v1, const vec3<T> & v2) {
	return vec3<T>(v1.x / v2.x, v1.y / v2.y, v2.z);
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T>
inline bool operator==(const vec3<T> & v1, const vec3<T> & v2) {
	return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

template <typename T>
inline bool operator==(const vec3<T> & v1, const T & v2) {
	return v1.x == v2 && v1.y == v2 && v1.z == v2;
}

template <typename T>
inline bool operator==(const T & v1, const vec3<T> & v2) {
	return v1 == v2.x && v1 == v2.y && v1 == v2.z;
}

//--- not equal to ---

template <typename T>
inline bool operator!=(const vec3<T> & v1, const vec3<T> & v2) {
	return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z;
}

template <typename T>
inline bool operator!=(const vec3<T> & v1, const T & v2) {
	return v1.x != v2 || v1.y != v2 || v1.z != v2;
}

template <typename T>
inline bool operator!=(const T & v1, const vec3<T> & v2) {
	return v1 != v2.x || v1 != v2.y || v1 != v2.z;
}

//--- less than ---

template <typename T>
inline bool operator<(const vec3<T> & v1, const T & v2) {
	return v1.x < v2 && v1.y < v2 && v1.z < v2;
}

template <typename T>
inline bool operator<(const T & v1, const vec3<T> & v2) {
	return  v1 < v2.x && v1 < v2.y && v1 < v2.z;
}

//--- greater than ---

template <typename T>
inline bool operator>(const vec3<T> & v1, const T & v2) {
	return v1.x > v2 && v1.y > v2 && v1.z > v2;
}

template <typename T>
inline bool operator>(const T & v1, const vec3<T> & v2) {
	return  v1 > v2.x && v1 > v2.y && v1 > v2.z;
}

//--- less than or equal to ---

template <typename T>
inline bool operator<=(const vec3<T> & v1, const T & v2) {
	return v1.x <= v2 && v1.y <= v2 && v1.z <= v2;
}

template <typename T>
inline bool operator<=(const T & v1, const vec3<T> & v2) {
	return  v1 <= v2.x && v1 <= v2.y && v1 <= v2.z;
}

//--- greater than or equal to ---

template <typename T>
inline bool operator>=(const vec3<T> & v1, const T & v2) {
	return v1.x >= v2 && v1.y >= v2 && v1.z >= v2;
}

template <typename T>
inline bool operator>=(const T & v1, const vec3<T> & v2) {
	return  v1 >= v2.x && v1 >= v2.y && v1 >= v2.z;
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string vec<T, 3>::toString() const {
	std::stringstream ss;
	ss << "(" << x << ", " << y << ", " << z << ")";
	return ss.str();
}



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const vec3<T> & v) {
	return os << v.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC4 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr vec<T, 4>::vec() :
	x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)), w(static_cast<T>(0))
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec4<T> & v) :
	x(v.x), y(v.y), z(v.z), w(v.w)
{}

template <typename T>
constexpr vec<T, 4>::vec(vec4<T> && v) :
	x(v.x), y(v.y), z(v.z), w(v.w)
{}

template <typename T>
constexpr vec<T, 4>::vec(const T & v) :
	x(v), y(v), z(v), w(v)
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec1<T> & v) :
	x(v.x), y(static_cast<T>(0)), z(static_cast<T>(0)), w(static_cast<T>(0))
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec2<T> & v) :
	x(v.x), y(v.y), z(static_cast<T>(0)), w(static_cast<T>(0))
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec3<T> & v) :
	x(v.x), y(v.y), z(v.z), w(static_cast<T>(0))
{}

template <typename T>
constexpr vec<T, 4>::vec(const T & v1, const T & v2, const T & v3, const T & v4) :
	x(v1), y(v2), z(v3), w(v4)
{}



//------------------------------------------------------------------------------
// Assignment Operators



template <typename T>
vec4<T> & vec<T, 4>::operator=(const vec4<T> & v) {
	x = v.x; y = v.y; z = v.z; w = v.w;
	return *this;
}

template <typename T>
vec4<T> & vec<T, 4>::operator=(vec4<T> && v) {
	x = v.x; y = v.y; z = v.z; w = v.w;
	return *this;
}

template <typename T>
vec4<T> & vec<T, 4>::operator=(const T & v) {
	x = v; y = v; z = v; w = v;
	return *this;
}

template <typename T>
vec4<T> & vec<T, 4>::operator=(const vec1<T> & v) {
	x = v.x; y = static_cast<T>(0); z = static_cast<T>(0); w = static_cast<T>(0);
	return *this;
}

template <typename T>
vec4<T> & vec<T, 4>::operator=(const vec2<T> & v) {
	x = v.x; y = v.y; z = static_cast<T>(0); w = static_cast<T>(0);
	return *this;
}

template <typename T>
vec4<T> & vec<T, 4>::operator=(const vec3<T> & v) {
	x = v.x; y = v.y; z = v.z; w = static_cast<T>(0);
	return *this;
}



//------------------------------------------------------------------------------
// Access Operators



template <typename T>
T vec<T, 4>::operator[](nat i) {
	return *(&x + i);
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- add assign ---

template <typename T>
inline vec4<T> & operator+=(vec4<T> & v1, const vec4<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline vec4<T> & operator+=(vec4<T> & v1, const T & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline vec4<T> & operator+=(vec4<T> & v1, const vec1<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline vec4<T> & operator+=(vec4<T> & v1, const vec2<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline vec4<T> & operator+=(vec4<T> & v1, const vec3<T> & v2) {
	return v1 = v1 + v2;
}

//--- subtract assign ---

template <typename T>
inline vec4<T> & operator-=(vec4<T> & v1, const vec4<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline vec4<T> & operator-=(vec4<T> & v1, const T & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline vec4<T> & operator-=(vec4<T> & v1, const vec1<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline vec4<T> & operator-=(vec4<T> & v1, const vec2<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline vec4<T> & operator-=(vec4<T> & v1, const vec3<T> & v2) {
	return v1 = v1 - v2;
}

//--- multiply assign ---

template <typename T>
inline vec4<T> & operator*=(vec4<T> & v1, const vec4<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline vec4<T> & operator*=(vec4<T> & v1, const T & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline vec4<T> & operator*=(vec4<T> & v1, const vec1<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline vec4<T> & operator*=(vec4<T> & v1, const vec2<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline vec4<T> & operator*=(vec4<T> & v1, const vec3<T> & v2) {
	return v1 = v1 * v2;
}

//--- divide assign ---

template <typename T>
inline vec4<T> & operator/=(vec4<T> & v1, const vec4<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline vec4<T> & operator/=(vec4<T> & v1, const T & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline vec4<T> & operator/=(vec4<T> & v1, const vec1<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline vec4<T> & operator/=(vec4<T> & v1, const vec2<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline vec4<T> & operator/=(vec4<T> & v1, const vec3<T> & v2) {
	return v1 = v1 / v2;
}

//--- pre increment ---

template <typename T>
inline vec4<T> & operator++(vec4<T> & v) {
	++v.x; ++v.y; ++v.z; ++v.w;
	return v;
}

//--- post increment ---

template <typename T>
inline vec4<T> operator++(vec4<T> & v, int) {
	return vec4<T>(v.x++, v.y++, v.z++, v.w++);
}

//--- pre decrement ---

template <typename T>
inline vec4<T> & operator--(vec4<T> & v) {
	--v.x; --v.y; --v.z; --v.w;
	return v;
}

//--- post decrement ---

template <typename T>
inline vec4<T> operator--(vec4<T> & v, int) {
	return vec4<T>(v.x--, v.y--, v.z--, v.w--);
}

//--- positive ---

template <typename T>
inline vec4<T> operator+(const vec4<T> & v) {
	return v;
}

//--- negative ---

template <typename T>
inline vec4<T> operator-(const vec4<T> & v) {
	return v * static_cast<T>(-1);
}

//--- add ---

template <typename T>
inline vec4<T> operator+(const vec4<T> & v1, const vec4<T> & v2) {
	return vec4<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

template <typename T>
inline vec4<T> operator+(const vec4<T> & v1, const T & v2) {
	return vec4<T>(v1.x + v2, v1.y + v2, v1.z + v2, v1.w + v2);
}

template <typename T>
inline vec4<T> operator+(const T & v1, const vec4<T> & v2) {
	return vec4<T>(v1 + v2.x, v1 + v2.y, v1 + v2.z, v1 + v2.w);
}

template <typename T>
inline vec4<T> operator+(const vec4<T> & v1, const vec1<T> & v2) {
	return vec4<T>(v1.x + v2.x, v1.y, v1.z, v1.w);
}

template <typename T>
inline vec4<T> operator+(const vec1<T> & v1, const vec4<T> & v2) {
	return vec4<T>(v1.x + v2.x, v2.y, v2.z, v2.w);
}

template <typename T>
inline vec4<T> operator+(const vec4<T> & v1, const vec2<T> & v2) {
	return vec4<T>(v1.x + v2.x, v1.y + v2.y, v1.z, v1.w);
}

template <typename T>
inline vec4<T> operator+(const vec2<T> & v1, const vec4<T> & v2) {
	return vec4<T>(v1.x + v2.x, v1.y + v2.y, v2.z, v2.w);
}

template <typename T>
inline vec4<T> operator+(const vec4<T> & v1, const vec3<T> & v2) {
	return vec4<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w);
}

template <typename T>
inline vec4<T> operator+(const vec3<T> & v1, const vec4<T> & v2) {
	return vec4<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v2.w);
}

//--- subtract ---

template <typename T>
inline vec4<T> operator-(const vec4<T> & v1, const vec4<T> & v2) {
	return vec4<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

template <typename T>
inline vec4<T> operator-(const vec4<T> & v1, const T & v2) {
	return vec4<T>(v1.x - v2, v1.y - v2, v1.z - v2, v1.w - v2);
}

template <typename T>
inline vec4<T> operator-(const T & v1, const vec4<T> & v2) {
	return vec4<T>(v1 - v2.x, v1 - v2.y, v1 - v2.z, v1 - v2.w);
}

template <typename T>
inline vec4<T> operator-(const vec4<T> & v1, const vec1<T> & v2) {
	return vec4<T>(v1.x - v2.x, v1.y, v1.z, v1.w);
}

template <typename T>
inline vec4<T> operator-(const vec1<T> & v1, const vec4<T> & v2) {
	return vec4<T>(v1.x - v2.x, v2.y, v2.z, v2.w);
}

template <typename T>
inline vec4<T> operator-(const vec4<T> & v1, const vec2<T> & v2) {
	return vec4<T>(v1.x - v2.x, v1.y - v2.y, v1.z, v1.w);
}

template <typename T>
inline vec4<T> operator-(const vec2<T> & v1, const vec4<T> & v2) {
	return vec4<T>(v1.x - v2.x, v1.y - v2.y, v2.z, v2.w);
}

template <typename T>
inline vec4<T> operator-(const vec4<T> & v1, const vec3<T> & v2) {
	return vec4<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w);
}

template <typename T>
inline vec4<T> operator-(const vec3<T> & v1, const vec4<T> & v2) {
	return vec4<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v2.w);
}

//--- multiply ---

template <typename T>
inline vec4<T> operator*(const vec4<T> & v1, const vec4<T> & v2) {
	return vec4<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

template <typename T>
inline vec4<T> operator*(const vec4<T> & v1, const T & v2) {
	return vec4<T>(v1.x * v2, v1.y * v2, v1.z * v2, v1.w * v2);
}

template <typename T>
inline vec4<T> operator*(const T & v1, const vec4<T> & v2) {
	return vec4<T>(v1 * v2.x, v1 * v2.y, v1 * v2.z, v1 * v2.w);
}

template <typename T>
inline vec4<T> operator*(const vec4<T> & v1, const vec1<T> & v2) {
	return vec4<T>(v1.x * v2.x, v1.y, v1.z, v1.w);
}

template <typename T>
inline vec4<T> operator*(const vec1<T> & v1, const vec4<T> & v2) {
	return vec4<T>(v1.x * v2.x, v2.y, v2.z, v2.w);
}

template <typename T>
inline vec4<T> operator*(const vec4<T> & v1, const vec2<T> & v2) {
	return vec4<T>(v1.x * v2.x, v1.y * v2.y, v1.z, v1.w);
}

template <typename T>
inline vec4<T> operator*(const vec2<T> & v1, const vec4<T> & v2) {
	return vec4<T>(v1.x * v2.x, v1.y * v2.y, v2.z, v2.w);
}

template <typename T>
inline vec4<T> operator*(const vec4<T> & v1, const vec3<T> & v2) {
	return vec4<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w);
}

template <typename T>
inline vec4<T> operator*(const vec3<T> & v1, const vec4<T> & v2) {
	return vec4<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v2.w);
}

//--- divide ---

template <typename T>
inline vec4<T> operator/(const vec4<T> & v1, const vec4<T> & v2) {
	return vec4<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
}

template <typename T>
inline vec4<T> operator/(const vec4<T> & v1, const T & v2) {
	return vec4<T>(v1.x / v2, v1.y / v2, v1.z / v2, v1.w / v2);
}

template <typename T>
inline vec4<T> operator/(const T & v1, const vec4<T> & v2) {
	return vec4<T>(v1 / v2.x, v1 / v2.y, v1 / v2.z, v1 / v2.w);
}

template <typename T>
inline vec4<T> operator/(const vec4<T> & v1, const vec1<T> & v2) {
	return vec4<T>(v1.x / v2.x, v1.y, v1.z, v1.w);
}

template <typename T>
inline vec4<T> operator/(const vec1<T> & v1, const vec4<T> & v2) {
	return vec4<T>(v1.x / v2.x, v2.y, v2.z, v2.w);
}

template <typename T>
inline vec4<T> operator/(const vec4<T> & v1, const vec2<T> & v2) {
	return vec4<T>(v1.x / v2.x, v1.y / v2.y, v1.z, v1.w);
}

template <typename T>
inline vec4<T> operator/(const vec2<T> & v1, const vec4<T> & v2) {
	return vec4<T>(v1.x / v2.x, v1.y / v2.y, v2.z, v2.w);
}

template <typename T>
inline vec4<T> operator/(const vec4<T> & v1, const vec3<T> & v2) {
	return vec4<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w);
}

template <typename T>
inline vec4<T> operator/(const vec3<T> & v1, const vec4<T> & v2) {
	return vec4<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v2.w);
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T>
inline bool operator==(const vec4<T> & v1, const vec4<T> & v2) {
	return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
}

template <typename T>
inline bool operator==(const vec4<T> & v1, const T & v2) {
	return v1.x == v2 && v1.y == v2 && v1.z == v2 && v1.w == v2;
}

template <typename T>
inline bool operator==(const T & v1, const vec4<T> & v2) {
	return v1 == v2.x && v1 == v2.y && v1 == v2.z && v1 == v2.w;
}

//--- not equal to ---

template <typename T>
inline bool operator!=(const vec4<T> & v1, const vec4<T> & v2) {
	return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z || v1.w != v2.w;
}

template <typename T>
inline bool operator!=(const vec4<T> & v1, const T & v2) {
	return v1.x != v2 || v1.y != v2 || v1.z != v2 || v1.w != v2;
}

template <typename T>
inline bool operator!=(const T & v1, const vec4<T> & v2) {
	return v1 != v2.x || v1 != v2.y || v1 != v2.z || v1 != v2.w;
}

//--- less than ---

template <typename T>
inline bool operator<(const vec4<T> & v1, const T & v2) {
	return v1.x < v2 && v1.y < v2 && v1.z < v2 && v1.w < v2;
}

template <typename T>
inline bool operator<(const T & v1, const vec4<T> & v2) {
	return  v1 < v2.x && v1 < v2.y && v1 < v2.z && v1 < v2.w;
}

//--- greater than ---

template <typename T>
inline bool operator>(const vec4<T> & v1, const T & v2) {
	return v1.x > v2 && v1.y > v2 && v1.z > v2 && v1.w > v2;
}

template <typename T>
inline bool operator>(const T & v1, const vec4<T> & v2) {
	return  v1 > v2.x && v1 > v2.y && v1 > v2.z && v1 > v2.w;
}

//--- less than or equal to ---

template <typename T>
inline bool operator<=(const vec4<T> & v1, const T & v2) {
	return v1.x <= v2 && v1.y <= v2 && v1.z <= v2 && v1.w <= v2;
}

template <typename T>
inline bool operator<=(const T & v1, const vec4<T> & v2) {
	return  v1 <= v2.x && v1 <= v2.y && v1 <= v2.z && v1 <= v2.w;
}

//--- greater than or equal to ---

template <typename T>
inline bool operator>=(const vec4<T> & v1, const T & v2) {
	return v1.x >= v2 && v1.y >= v2 && v1.z >= v2 && v1.w >= v2;
}

template <typename T>
inline bool operator>=(const T & v1, const vec4<T> & v2) {
	return  v1 >= v2.x && v1 >= v2.y && v1 >= v2.z && v1 >= v2.w;
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string vec<T, 4>::toString() const {
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + ")";
}



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const vec4<T> & v) {
	return os << v.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC6 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr vec<T, 6>::vec() :
	x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)), width(static_cast<T>(0)), height(static_cast<T>(0)), depth(static_cast<T>(0))
{}

template <typename T>
constexpr vec<T, 6>::vec(const bound3<T> & v) :
	x(v.x), y(v.y), z(v.z), width(v.width), height(v.height), depth(v.depth)
{}

template <typename T>
constexpr vec<T, 6>::vec(bound3<T> && v) :
	x(v.x), y(v.y), z(v.z), width(v.width), height(v.height), depth(v.depth)
{}

template <typename T>
constexpr vec<T, 6>::vec(const vec3<T> & v1, const vec3<T> & v2) :
	x(v1.x), y(v1.y), z(v1.z), width(v2.x), height(v2.y), depth(v2.z)
{}

template <typename T>
constexpr vec<T, 6>::vec(const T & v1, const T & v2, const T & v3, const T & v4, const T & v5, const T & v6) :
	x(v1), y(v2), z(v3), width(v4), height(v5), depth(v6)
{}



//------------------------------------------------------------------------------
// Assignment Operators



template <typename T>
bound3<T> & vec<T, 6>::operator=(const bound3<T> & v) {
	x = v.x; y = v.y; z = v.z; width = v.width; height = v.height; depth = v.depth;
	return *this;
}

template <typename T>
bound3<T> & vec<T, 6>::operator=(bound3<T> && v) {
	x = v.x; y = v.y; z = v.z; width = v.width; height = v.height; depth = v.depth;
	return *this;
}



//------------------------------------------------------------------------------
// Access Operators



template <typename T>
T vec<T, 6>::operator[](nat i) {
	return *(&x + i);
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T>
inline bool operator==(const bound3<T> & v1, const bound3<T> & v2) {
	return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.width = v2.width && v1.height == v2.height;
}

//--- not equal to ---

template <typename T>
inline bool operator!=(const bound3<T> & v1, const bound3<T> & v2) {
	return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z || v1.width != v2.width || v1.height != v2.height || v1.depth != v2.depth;
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string vec<T, 6>::toString() const {
	std::stringstream ss;
	ss << "(" << x << ", " << y << ", " << z << ", " << width << ", " << height << ", " << depth << ")";
	return ss.str();
}



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const bound3<T> & v) {
	return os << v.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC FUNCTIONS IMPLEMENTATION ----------------------------------------------------------------------------------------



template <typename T>
inline T mag2(const vec1<T> & a) {
	return a.x * a.x;
}

template <typename T>
inline T mag2(const vec2<T> & a) {
	return a.x * a.x + a.y * a.y;
}

template <typename T>
inline T mag2(const vec3<T> & a) {
	return a.x * a.x + a.y * a.y + a.z * a.z;
}

template <typename T>
inline T mag2(const vec4<T> & a) {
	return a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w;
}

template <typename T, nat t_n>
inline T mag(const vec<T, t_n> & v) {
	return sqrt(mag2(v));
}

template <typename T, nat t_n>
inline vec<T, t_n> norm(const vec<T, t_n> & a) {
	T m = mag(a);
	if (abs(m) < std::numeric_limits<T>::min()) {
		return vec<T, t_n>();
	}
	return a / m;
}

template <typename T>
inline T dot(const vec1<T> & a, const vec1<T> & b) {
	return a.x * b.x;
}

template <typename T>
inline T dot(const vec2<T> & a, const vec2<T> & b) {
	return a.x * b.x + a.y * b.y;
}

template <typename T>
inline T dot(const vec3<T> & a, const vec3<T> & b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename T>
inline T dot(const vec4<T> & a, const vec4<T> & b) {
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

template <typename T>
inline vec3<T> cross(const vec3<T> & a, const vec3<T> & b) {
	return vec3<T>(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

template <typename T, nat t_n>
inline T angle(const vec<T, t_n> & a, const vec<T, t_n> & b) {
	return acos(dot(norm(a), norm(b)));
}

template <typename T, nat t_n>
inline vec<T, t_n> lerp(const vec<T, t_n> & v1, const vec<T, t_n> & v2, T t) {
	return (1 - t) * v1 + t * v2;
}



};