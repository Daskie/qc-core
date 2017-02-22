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
struct tvec;



template <typename T> using tvec1 = tvec<T, 1>;
template <typename T> using tvec2 = tvec<T, 2>;
template <typename T> using tvec3 = tvec<T, 3>;
template <typename T> using tvec4 = tvec<T, 4>;

using   vec1 = tvec1<float>;
using   vec2 = tvec2<float>;
using   vec3 = tvec3<float>;
using   vec4 = tvec4<float>;

using  dvec1 = tvec1<double>;
using  dvec2 = tvec2<double>;
using  dvec3 = tvec3<double>;
using  dvec4 = tvec4<double>;

using  cvec1 = tvec1<s08>;
using  cvec2 = tvec2<s08>;
using  cvec3 = tvec3<s08>;
using  cvec4 = tvec4<s08>;
using ucvec1 = tvec1<u08>;
using ucvec2 = tvec2<u08>;
using ucvec3 = tvec3<u08>;
using ucvec4 = tvec4<u08>;

using  svec1 = tvec1<s16>;
using  svec2 = tvec2<s16>;
using  svec3 = tvec3<s16>;
using  svec4 = tvec4<s16>;
using usvec1 = tvec1<u16>;
using usvec2 = tvec2<u16>;
using usvec3 = tvec3<u16>;
using usvec4 = tvec4<u16>;

using  ivec1 = tvec1<s32>;
using  ivec2 = tvec2<s32>;
using  ivec3 = tvec3<s32>;
using  ivec4 = tvec4<s32>;
using uivec1 = tvec1<u32>;
using uivec2 = tvec2<u32>;
using uivec3 = tvec3<u32>;
using uivec4 = tvec4<u32>;

using  lvec1 = tvec1<s64>;
using  lvec2 = tvec2<s64>;
using  lvec3 = tvec3<s64>;
using  lvec4 = tvec4<s64>;
using ulvec1 = tvec1<u64>;
using ulvec2 = tvec2<u64>;
using ulvec3 = tvec3<u64>;
using ulvec4 = tvec4<u64>;

using  bvec1 = tvec1<bool>;
using  bvec2 = tvec2<bool>;
using  bvec3 = tvec3<bool>;
using  bvec4 = tvec4<bool>;

template <typename T> using point = tvec2<T>;
template <typename T> using bound1 = tvec2<T>;
template <typename T> using bound2 = tvec4<T>;
template <typename T> using bound3 = tvec<T, 6>;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC1 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct tvec<T, 1> {

	using Type = T;
	static constexpr nat t_n = 1;

	union {
		struct { T x; };
		struct { T r; };
		struct { T s; };
	};

	//--- constructors ---

	constexpr tvec();
	constexpr tvec(const tvec1<T> & v);
	constexpr tvec(tvec1<T> && v);

	constexpr explicit tvec(const       T  & v);
	constexpr explicit tvec(const tvec2<T> & v);
	constexpr explicit tvec(const tvec3<T> & v);
	constexpr explicit tvec(const tvec4<T> & v);

	//--- assignment operators ---

	tvec1<T> & operator=(const tvec1<T> & v);
	tvec1<T> & operator=(tvec1<T> && v);

	tvec1<T> & operator=(const       T  & v);
	tvec1<T> & operator=(const tvec2<T> & v);
	tvec1<T> & operator=(const tvec3<T> & v);
	tvec1<T> & operator=(const tvec4<T> & v);

	//--- access operators ---

	T operator[](nat i);

	//--- arithmetic operators ---

	template <typename T> friend tvec1<T> & operator+=(tvec1<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec1<T> & operator+=(tvec1<T> & v1, const       T  & v2);
	template <typename T> friend tvec1<T> & operator+=(tvec1<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec1<T> & operator+=(tvec1<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec1<T> & operator+=(tvec1<T> & v1, const tvec4<T> & v2);

	template <typename T> friend tvec1<T> & operator-=(tvec1<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec1<T> & operator-=(tvec1<T> & v1, const       T  & v2);
	template <typename T> friend tvec1<T> & operator-=(tvec1<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec1<T> & operator-=(tvec1<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec1<T> & operator-=(tvec1<T> & v1, const tvec4<T> & v2);

	template <typename T> friend tvec1<T> & operator*=(tvec1<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec1<T> & operator*=(tvec1<T> & v1, const       T  & v2);
	template <typename T> friend tvec1<T> & operator*=(tvec1<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec1<T> & operator*=(tvec1<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec1<T> & operator*=(tvec1<T> & v1, const tvec4<T> & v2);

	template <typename T> friend tvec1<T> & operator/=(tvec1<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec1<T> & operator/=(tvec1<T> & v1, const       T  & v2);
	template <typename T> friend tvec1<T> & operator/=(tvec1<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec1<T> & operator/=(tvec1<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec1<T> & operator/=(tvec1<T> & v1, const tvec4<T> & v2);

	template <typename T> friend tvec1<T> & operator++(tvec1<T> & v);
	template <typename T> friend tvec1<T> operator++(tvec1<T> & v, int);

	template <typename T> friend tvec1<T> & operator--(tvec1<T> & v);
	template <typename T> friend tvec1<T> operator--(tvec1<T> & v, int);

	template <typename T> friend tvec1<T> operator+(const tvec1<T> & v);

	template <typename T> friend tvec1<T> operator-(const tvec1<T> & v);

	template <typename T> friend tvec1<T> operator+(const tvec1<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec1<T> operator+(const tvec1<T> & v1, const       T  & v2);
	template <typename T> friend tvec1<T> operator+(const       T  & v1, const tvec1<T> & v2);

	template <typename T> friend tvec1<T> operator-(const tvec1<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec1<T> operator-(const tvec1<T> & v1, const       T  & v2);
	template <typename T> friend tvec1<T> operator-(const       T  & v1, const tvec1<T> & v2);

	template <typename T> friend tvec1<T> operator*(const tvec1<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec1<T> operator*(const tvec1<T> & v1, const       T  & v2);
	template <typename T> friend tvec1<T> operator*(const       T  & v1, const tvec1<T> & v2);

	template <typename T> friend tvec1<T> operator/(const tvec1<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec1<T> operator/(const tvec1<T> & v1, const       T  & v2);
	template <typename T> friend tvec1<T> operator/(const       T  & v1, const tvec1<T> & v2);

	//--- comparison operators ---

	template <typename T> friend bool operator==(const tvec1<T> & v1, const tvec1<T> & v2);
	template <typename T> friend bool operator==(const tvec1<T> & v1, const       T  & v2);
	template <typename T> friend bool operator==(const       T  & v1, const tvec1<T> & v2);

	template <typename T> friend bool operator!=(const tvec1<T> & v1, const tvec1<T> & v2);
	template <typename T> friend bool operator!=(const tvec1<T> & v1, const       T  & v2);
	template <typename T> friend bool operator!=(const       T  & v1, const tvec1<T> & v2);

	template <typename T> friend bool operator<(const tvec1<T> & v1, const       T  & v2);
	template <typename T> friend bool operator<(const       T  & v1, const tvec1<T> & v2);

	template <typename T> friend bool operator>(const tvec1<T> & v1, const       T  & v2);
	template <typename T> friend bool operator>(const       T  & v1, const tvec1<T> & v2);

	template <typename T> friend bool operator<=(const tvec1<T> & v1, const       T  & v2);
	template <typename T> friend bool operator<=(const       T  & v1, const tvec1<T> & v2);

	template <typename T> friend bool operator>=(const tvec1<T> & v1, const       T  & v2);
	template <typename T> friend bool operator>=(const       T  & v1, const tvec1<T> & v2);

	//--- other ---

	std::string toString() const;

	template <typename T> friend std::ostream & operator<<(std::ostream & os, const tvec1<T> & v);

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC2 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct tvec<T, 2> {

	using Type = T;
	static constexpr nat t_n = 2;

	union {
		struct { T x, y; };
		struct { T r, g; };
		struct { T s, t; };
		struct { T x, width; };
	};

	//--- constructors ---

	constexpr tvec();
	constexpr tvec(const tvec2<T> & v);
	constexpr tvec(tvec2<T> && v);

	constexpr explicit tvec(const       T  & v);
	constexpr explicit tvec(const tvec1<T> & v);
	constexpr explicit tvec(const tvec3<T> & v);
	constexpr explicit tvec(const tvec4<T> & v);
	constexpr tvec(const T & v1, const T & v2);

	//--- assignment operators ---

	tvec2<T> & operator=(const tvec2<T> & v);
	tvec2<T> & operator=(tvec2<T> && v);

	tvec2<T> & operator=(const       T  & v);
	tvec2<T> & operator=(const tvec1<T> & v);
	tvec2<T> & operator=(const tvec3<T> & v);
	tvec2<T> & operator=(const tvec4<T> & v);

	//--- access operators ---

	T operator[](nat i);

	//--- arithmetic operators ---

	template <typename T> friend tvec2<T> & operator+=(tvec2<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec2<T> & operator+=(tvec2<T> & v1, const       T  & v2);
	template <typename T> friend tvec2<T> & operator+=(tvec2<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec2<T> & operator+=(tvec2<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec2<T> & operator+=(tvec2<T> & v1, const tvec4<T> & v2);

	template <typename T> friend tvec2<T> & operator-=(tvec2<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec2<T> & operator-=(tvec2<T> & v1, const       T  & v2);
	template <typename T> friend tvec2<T> & operator-=(tvec2<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec2<T> & operator-=(tvec2<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec2<T> & operator-=(tvec2<T> & v1, const tvec4<T> & v2);

	template <typename T> friend tvec2<T> & operator*=(tvec2<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec2<T> & operator*=(tvec2<T> & v1, const       T  & v2);
	template <typename T> friend tvec2<T> & operator*=(tvec2<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec2<T> & operator*=(tvec2<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec2<T> & operator*=(tvec2<T> & v1, const tvec4<T> & v2);

	template <typename T> friend tvec2<T> & operator/=(tvec2<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec2<T> & operator/=(tvec2<T> & v1, const       T  & v2);
	template <typename T> friend tvec2<T> & operator/=(tvec2<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec2<T> & operator/=(tvec2<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec2<T> & operator/=(tvec2<T> & v1, const tvec4<T> & v2);

	template <typename T> friend tvec2<T> & operator++(tvec2<T> & v);
	template <typename T> friend tvec2<T> operator++(tvec2<T> & v, int);

	template <typename T> friend tvec2<T> & operator--(tvec2<T> & v);
	template <typename T> friend tvec2<T> operator--(tvec2<T> & v, int);

	template <typename T> friend tvec2<T> operator+(const tvec2<T> & v);

	template <typename T> friend tvec2<T> operator-(const tvec2<T> & v);

	template <typename T> friend tvec2<T> operator+(const tvec2<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec2<T> operator+(const tvec2<T> & v1, const       T  & v2);
	template <typename T> friend tvec2<T> operator+(const       T  & v1, const tvec2<T> & v2);

	template <typename T> friend tvec2<T> operator-(const tvec2<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec2<T> operator-(const tvec2<T> & v1, const       T  & v2);
	template <typename T> friend tvec2<T> operator-(const       T  & v1, const tvec2<T> & v2);

	template <typename T> friend tvec2<T> operator*(const tvec2<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec2<T> operator*(const tvec2<T> & v1, const       T  & v2);
	template <typename T> friend tvec2<T> operator*(const       T  & v1, const tvec2<T> & v2);

	template <typename T> friend tvec2<T> operator/(const tvec2<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec2<T> operator/(const tvec2<T> & v1, const       T  & v2);
	template <typename T> friend tvec2<T> operator/(const       T  & v1, const tvec2<T> & v2);
	template <typename T> friend tvec2<T> operator/(const tvec2<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec2<T> operator/(const tvec1<T> & v1, const tvec2<T> & v2);

	//--- comparison operators ---

	template <typename T> friend bool operator==(const tvec2<T> & v1, const tvec2<T> & v2);
	template <typename T> friend bool operator==(const tvec2<T> & v1, const       T  & v2);
	template <typename T> friend bool operator==(const       T  & v1, const tvec2<T> & v2);

	template <typename T> friend bool operator!=(const tvec2<T> & v1, const tvec2<T> & v2);
	template <typename T> friend bool operator!=(const tvec2<T> & v1, const       T  & v2);
	template <typename T> friend bool operator!=(const       T  & v1, const tvec2<T> & v2);

	template <typename T> friend bool operator<(const tvec2<T> & v1, const       T  & v2);
	template <typename T> friend bool operator<(const       T  & v1, const tvec2<T> & v2);

	template <typename T> friend bool operator>(const tvec2<T> & v1, const       T  & v2);
	template <typename T> friend bool operator>(const       T  & v1, const tvec2<T> & v2);

	template <typename T> friend bool operator<=(const tvec2<T> & v1, const       T  & v2);
	template <typename T> friend bool operator<=(const       T  & v1, const tvec2<T> & v2);

	template <typename T> friend bool operator>=(const tvec2<T> & v1, const       T  & v2);
	template <typename T> friend bool operator>=(const       T  & v1, const tvec2<T> & v2);

	//--- other ---

	std::string toString() const;

	template <typename T> friend std::ostream & operator<<(std::ostream & os, const tvec2<T> & v);

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC3 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct tvec<T, 3> {

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

	constexpr tvec();
	constexpr tvec(const tvec3<T> & v);
	constexpr tvec(tvec3<T> && v);

	constexpr explicit tvec(const       T  & v);
	constexpr explicit tvec(const tvec1<T> & v);
	constexpr explicit tvec(const tvec2<T> & v);
	constexpr explicit tvec(const tvec4<T> & v);
	constexpr tvec(const T & v1, const T & v2, const T & v3);

	//--- assignment operators ---

	tvec3<T> & operator=(const tvec3<T> & v);
	tvec3<T> & operator=(tvec3<T> && v);

	tvec3<T> & operator=(const       T  & v);
	tvec3<T> & operator=(const tvec1<T> & v);
	tvec3<T> & operator=(const tvec2<T> & v);
	tvec3<T> & operator=(const tvec4<T> & v);

	//--- access operators ---

	T operator[](nat i);

	//--- arithmetic operators ---

	template <typename T> friend tvec3<T> & operator+=(tvec3<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec3<T> & operator+=(tvec3<T> & v1, const       T  & v2);
	template <typename T> friend tvec3<T> & operator+=(tvec3<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec3<T> & operator+=(tvec3<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec3<T> & operator+=(tvec3<T> & v1, const tvec4<T> & v2);

	template <typename T> friend tvec3<T> & operator-=(tvec3<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec3<T> & operator-=(tvec3<T> & v1, const       T  & v2);
	template <typename T> friend tvec3<T> & operator-=(tvec3<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec3<T> & operator-=(tvec3<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec3<T> & operator-=(tvec3<T> & v1, const tvec4<T> & v2);

	template <typename T> friend tvec3<T> & operator*=(tvec3<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec3<T> & operator*=(tvec3<T> & v1, const       T  & v2);
	template <typename T> friend tvec3<T> & operator*=(tvec3<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec3<T> & operator*=(tvec3<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec3<T> & operator*=(tvec3<T> & v1, const tvec4<T> & v2);

	template <typename T> friend tvec3<T> & operator/=(tvec3<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec3<T> & operator/=(tvec3<T> & v1, const       T  & v2);
	template <typename T> friend tvec3<T> & operator/=(tvec3<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec3<T> & operator/=(tvec3<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec3<T> & operator/=(tvec3<T> & v1, const tvec4<T> & v2);

	template <typename T> friend tvec3<T> & operator++(tvec3<T> & v);
	template <typename T> friend tvec3<T> operator++(tvec3<T> & v, int);

	template <typename T> friend tvec3<T> & operator--(tvec3<T> & v);
	template <typename T> friend tvec3<T> operator--(tvec3<T> & v, int);

	template <typename T> friend tvec3<T> operator+(const tvec3<T> & v);

	template <typename T> friend tvec3<T> operator-(const tvec3<T> & v);

	template <typename T> friend tvec3<T> operator+(const tvec3<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec3<T> operator+(const tvec3<T> & v1, const       T  & v2);
	template <typename T> friend tvec3<T> operator+(const       T  & v1, const tvec3<T> & v2);
	template <typename T> friend tvec3<T> operator+(const tvec3<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec3<T> operator+(const tvec1<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec3<T> operator+(const tvec3<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec3<T> operator+(const tvec2<T> & v1, const tvec3<T> & v2);

	template <typename T> friend tvec3<T> operator-(const tvec3<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec3<T> operator-(const tvec3<T> & v1, const       T  & v2);
	template <typename T> friend tvec3<T> operator-(const       T  & v1, const tvec3<T> & v2);
	template <typename T> friend tvec3<T> operator-(const tvec3<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec3<T> operator-(const tvec1<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec3<T> operator-(const tvec3<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec3<T> operator-(const tvec2<T> & v1, const tvec3<T> & v2);

	template <typename T> friend tvec3<T> operator*(const tvec3<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec3<T> operator*(const tvec3<T> & v1, const       T  & v2);
	template <typename T> friend tvec3<T> operator*(const       T  & v1, const tvec3<T> & v2);
	template <typename T> friend tvec3<T> operator*(const tvec3<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec3<T> operator*(const tvec1<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec3<T> operator*(const tvec3<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec3<T> operator*(const tvec2<T> & v1, const tvec3<T> & v2);

	template <typename T> friend tvec3<T> operator/(const tvec3<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec3<T> operator/(const tvec3<T> & v1, const       T  & v2);
	template <typename T> friend tvec3<T> operator/(const       T  & v1, const tvec3<T> & v2);
	template <typename T> friend tvec3<T> operator/(const tvec3<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec3<T> operator/(const tvec1<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec3<T> operator/(const tvec3<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec3<T> operator/(const tvec2<T> & v1, const tvec3<T> & v2);

	//--- comparison operators ---

	template <typename T> friend bool operator==(const tvec3<T> & v1, const tvec3<T> & v2);
	template <typename T> friend bool operator==(const tvec3<T> & v1, const       T  & v2);
	template <typename T> friend bool operator==(const       T  & v1, const tvec3<T> & v2);

	template <typename T> friend bool operator!=(const tvec3<T> & v1, const tvec3<T> & v2);
	template <typename T> friend bool operator!=(const tvec3<T> & v1, const       T  & v2);
	template <typename T> friend bool operator!=(const       T  & v1, const tvec3<T> & v2);

	template <typename T> friend bool operator<(const tvec3<T> & v1, const       T  & v2);
	template <typename T> friend bool operator<(const       T  & v1, const tvec3<T> & v2);

	template <typename T> friend bool operator>(const tvec3<T> & v1, const       T  & v2);
	template <typename T> friend bool operator>(const       T  & v1, const tvec3<T> & v2);

	template <typename T> friend bool operator<=(const tvec3<T> & v1, const       T  & v2);
	template <typename T> friend bool operator<=(const       T  & v1, const tvec3<T> & v2);

	template <typename T> friend bool operator>=(const tvec3<T> & v1, const       T  & v2);
	template <typename T> friend bool operator>=(const       T  & v1, const tvec3<T> & v2);

	//--- other ---

	std::string toString() const;

	template <typename T> friend std::ostream & operator<<(std::ostream & os, const tvec3<T> & v);

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC4 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct tvec<T, 4> {

	using Type = T;
	static constexpr nat t_n = 4;
	
	union {
		struct { T x, y, z, w; };
		struct { T r, g, b, a; };
		struct { T s, t, p, q; };
		struct { T x, y, width, height; };
	};
	
	//--- constructors ---

	constexpr tvec();
	constexpr tvec(const tvec4<T> & v);
	constexpr tvec(tvec4<T> && v);

	constexpr explicit tvec(const       T  & v);
	constexpr explicit tvec(const tvec1<T> & v);
	constexpr explicit tvec(const tvec2<T> & v);
	constexpr explicit tvec(const tvec3<T> & v);
	constexpr tvec(const T & v1, const T & v2, const T & v3, const T & v4);

	//--- assignment operators ---

	tvec4<T> & operator=(const tvec4<T> & v);
	tvec4<T> & operator=(tvec4<T> && v);

	tvec4<T> & operator=(const       T  & v);
	tvec4<T> & operator=(const tvec1<T> & v);
	tvec4<T> & operator=(const tvec2<T> & v);
	tvec4<T> & operator=(const tvec3<T> & v);

	//--- access operators ---
	
	T operator[](nat i);

	//--- arithmetic operators ---

	template <typename T> friend tvec4<T> & operator+=(tvec4<T> & v1, const tvec4<T> & v2);
	template <typename T> friend tvec4<T> & operator+=(tvec4<T> & v1, const       T  & v2);
	template <typename T> friend tvec4<T> & operator+=(tvec4<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec4<T> & operator+=(tvec4<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec4<T> & operator+=(tvec4<T> & v1, const tvec3<T> & v2);

	template <typename T> friend tvec4<T> & operator-=(tvec4<T> & v1, const tvec4<T> & v2);
	template <typename T> friend tvec4<T> & operator-=(tvec4<T> & v1, const       T  & v2);
	template <typename T> friend tvec4<T> & operator-=(tvec4<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec4<T> & operator-=(tvec4<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec4<T> & operator-=(tvec4<T> & v1, const tvec3<T> & v2);

	template <typename T> friend tvec4<T> & operator*=(tvec4<T> & v1, const tvec4<T> & v2);
	template <typename T> friend tvec4<T> & operator*=(tvec4<T> & v1, const       T  & v2);
	template <typename T> friend tvec4<T> & operator*=(tvec4<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec4<T> & operator*=(tvec4<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec4<T> & operator*=(tvec4<T> & v1, const tvec3<T> & v2);

	template <typename T> friend tvec4<T> & operator/=(tvec4<T> & v1, const tvec4<T> & v2);
	template <typename T> friend tvec4<T> & operator/=(tvec4<T> & v1, const       T  & v2);
	template <typename T> friend tvec4<T> & operator/=(tvec4<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec4<T> & operator/=(tvec4<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec4<T> & operator/=(tvec4<T> & v1, const tvec3<T> & v2);

	template <typename T> friend tvec4<T> & operator++(tvec4<T> & v);
	template <typename T> friend tvec4<T> operator++(tvec4<T> & v, int);

	template <typename T> friend tvec4<T> & operator--(tvec4<T> & v);
	template <typename T> friend tvec4<T> operator--(tvec4<T> & v, int);

	template <typename T> friend tvec4<T> operator+(const tvec4<T> & v);

	template <typename T> friend tvec4<T> operator-(const tvec4<T> & v);

	template <typename T> friend tvec4<T> operator+(const tvec4<T> & v1, const tvec4<T> & v2);
	template <typename T> friend tvec4<T> operator+(const tvec4<T> & v1, const       T  & v2);
	template <typename T> friend tvec4<T> operator+(const       T  & v1, const tvec4<T> & v2);
	template <typename T> friend tvec4<T> operator+(const tvec4<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec4<T> operator+(const tvec1<T> & v1, const tvec4<T> & v2);
	template <typename T> friend tvec4<T> operator+(const tvec4<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec4<T> operator+(const tvec2<T> & v1, const tvec4<T> & v2);
	template <typename T> friend tvec4<T> operator+(const tvec4<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec4<T> operator+(const tvec3<T> & v1, const tvec4<T> & v2);

	template <typename T> friend tvec4<T> operator-(const tvec4<T> & v1, const tvec4<T> & v2);
	template <typename T> friend tvec4<T> operator-(const tvec4<T> & v1, const       T  & v2);
	template <typename T> friend tvec4<T> operator-(const       T  & v1, const tvec4<T> & v2);
	template <typename T> friend tvec4<T> operator-(const tvec4<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec4<T> operator-(const tvec1<T> & v1, const tvec4<T> & v2);
	template <typename T> friend tvec4<T> operator-(const tvec4<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec4<T> operator-(const tvec2<T> & v1, const tvec4<T> & v2);
	template <typename T> friend tvec4<T> operator-(const tvec4<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec4<T> operator-(const tvec3<T> & v1, const tvec4<T> & v2);

	template <typename T> friend tvec4<T> operator*(const tvec4<T> & v1, const tvec4<T> & v2);
	template <typename T> friend tvec4<T> operator*(const tvec4<T> & v1, const       T  & v2);
	template <typename T> friend tvec4<T> operator*(const       T  & v1, const tvec4<T> & v2);
	template <typename T> friend tvec4<T> operator*(const tvec4<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec4<T> operator*(const tvec1<T> & v1, const tvec4<T> & v2);
	template <typename T> friend tvec4<T> operator*(const tvec4<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec4<T> operator*(const tvec2<T> & v1, const tvec4<T> & v2);
	template <typename T> friend tvec4<T> operator*(const tvec4<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec4<T> operator*(const tvec3<T> & v1, const tvec4<T> & v2);

	template <typename T> friend tvec4<T> operator/(const tvec4<T> & v1, const tvec4<T> & v2);
	template <typename T> friend tvec4<T> operator/(const tvec4<T> & v1, const       T  & v2);
	template <typename T> friend tvec4<T> operator/(const       T  & v1, const tvec4<T> & v2);
	template <typename T> friend tvec4<T> operator/(const tvec4<T> & v1, const tvec1<T> & v2);
	template <typename T> friend tvec4<T> operator/(const tvec1<T> & v1, const tvec4<T> & v2);
	template <typename T> friend tvec4<T> operator/(const tvec4<T> & v1, const tvec2<T> & v2);
	template <typename T> friend tvec4<T> operator/(const tvec2<T> & v1, const tvec4<T> & v2);
	template <typename T> friend tvec4<T> operator/(const tvec4<T> & v1, const tvec3<T> & v2);
	template <typename T> friend tvec4<T> operator/(const tvec3<T> & v1, const tvec4<T> & v2);

	//--- comparison operators ---

	template <typename T> friend bool operator==(const tvec4<T> & v1, const tvec4<T> & v2);
	template <typename T> friend bool operator==(const tvec4<T> & v1, const       T  & v2);
	template <typename T> friend bool operator==(const       T  & v1, const tvec4<T> & v2);

	template <typename T> friend bool operator!=(const tvec4<T> & v1, const tvec4<T> & v2);
	template <typename T> friend bool operator!=(const tvec4<T> & v1, const       T  & v2);
	template <typename T> friend bool operator!=(const       T  & v1, const tvec4<T> & v2);

	template <typename T> friend bool operator<(const tvec4<T> & v1, const       T  & v2);
	template <typename T> friend bool operator<(const       T  & v1, const tvec4<T> & v2);

	template <typename T> friend bool operator>(const tvec4<T> & v1, const       T  & v2);
	template <typename T> friend bool operator>(const       T  & v1, const tvec4<T> & v2);

	template <typename T> friend bool operator<=(const tvec4<T> & v1, const       T  & v2);
	template <typename T> friend bool operator<=(const       T  & v1, const tvec4<T> & v2);

	template <typename T> friend bool operator>=(const tvec4<T> & v1, const       T  & v2);
	template <typename T> friend bool operator>=(const       T  & v1, const tvec4<T> & v2);

	//--- other ---

	std::string toString() const;

	template <typename T> friend std::ostream & operator<<(std::ostream & os, const tvec4<T> & v);

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC6 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct tvec<T, 6> {

	using Type = T;
	static constexpr nat t_n = 6;

	T x, y, z, width, height, depth;

	//--- constructors ---

	constexpr tvec();
	constexpr tvec(const bound3<T> & v);
	constexpr tvec(bound3<T> && v);

	constexpr tvec(const tvec3<T> & v1, const tvec3<T> & v2);
	constexpr tvec(const T & v1, const T & v2, const T & v3, const T & v4, const T & v5, const T & v6);

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

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CONSTANTS -----------------------------------------------------------------------------------------------------------



// declared in implementation
//extern const vec3 POSX;
//extern const vec3 POSY;
//extern const vec3 POSZ;
//extern const vec3 NEGX;
//extern const vec3 NEGY;
//extern const vec3 NEGZ;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC FUNCTIONS -------------------------------------------------------------------------------------------------------



float mag(const vec2 & v);
float mag(const vec3 & v);
float mag(const vec4 & v);
double mag(const dvec2 & v);
double mag(const dvec3 & v);
double mag(const dvec4 & v);

float mag2(const vec2 & a);
float mag2(const vec3 & a);
float mag2(const vec4 & a);
double mag2(const dvec2 & a);
double mag2(const dvec3 & a);
double mag2(const dvec4 & a);

vec2 norm(const vec2 & a);
vec3 norm(const vec3 & a);
vec4 norm(const vec4 & a);
dvec2 norm(const dvec2 & a);
dvec3 norm(const dvec3 & a);
dvec4 norm(const dvec4 & a);

float dot(const vec2 & a, const vec2 & b);
float dot(const vec3 & a, const vec3 & b);
float dot(const vec4 & a, const vec4 & b);
double dot(const dvec2 & a, const dvec2 & b);
double dot(const dvec3 & a, const dvec3 & b);
double dot(const dvec4 & a, const dvec4 & b);

vec3 cross(const vec3 & a, const vec3 & b);
dvec3 cross(const dvec3 & a, const dvec3 & b);

float angle(const vec2 & a, const vec2 & b);
float angle(const vec3 & a, const vec3 & b);
float angle(const vec4 & a, const vec4 & b);
double angle(const dvec2 & a, const dvec2 & b);
double angle(const dvec3 & a, const dvec3 & b);
double angle(const dvec4 & a, const dvec4 & b);

vec2 lerp(const vec2 & v1, const vec2 & v2, float t);
vec3 lerp(const vec3 & v1, const vec3 & v2, float t);
vec4 lerp(const vec4 & v1, const vec4 & v2, float t);
dvec2 lerp(const dvec2 & v1, const dvec2 & v2, double t);
dvec3 lerp(const dvec3 & v1, const dvec3 & v2, double t);
dvec4 lerp(const dvec4 & v1, const dvec4 & v2, double t);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC1 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr tvec<T, 1>::tvec() :
	x(static_cast<T>(0))
{}

template <typename T>
constexpr tvec<T, 1>::tvec(const tvec1<T> & v) :
	x(v.x)
{}

template <typename T>
constexpr tvec<T, 1>::tvec(tvec1<T> && v) :
	x(v.x)
{}

template <typename T>
constexpr tvec<T, 1>::tvec(const T & v) :
	x(v)
{}

template <typename T>
constexpr tvec<T, 1>::tvec(const tvec2<T> & v) :
	x(v.x)
{}

template <typename T>
constexpr tvec<T, 1>::tvec(const tvec3<T> & v) :
	x(v.x)
{}

template <typename T>
constexpr tvec<T, 1>::tvec(const tvec4<T> & v) :
	x(v.x)
{}



//------------------------------------------------------------------------------
// Assignment Operators



template <typename T>
tvec1<T> & tvec<T, 1>::operator=(const tvec1<T> & v) {
	x = v.x;
	return *this;
}

template <typename T>
tvec1<T> & tvec<T, 1>::operator=(tvec1<T> && v) {
	x = v.x;
	return *this;
}

template <typename T>
tvec1<T> & tvec<T, 1>::operator=(const T & v) {
	x = v;
	return *this;
}

template <typename T>
tvec1<T> & tvec<T, 1>::operator=(const tvec2<T> & v) {
	x = v.x;
	return *this;
}

template <typename T>
tvec1<T> & tvec<T, 1>::operator=(const tvec3<T> & v) {
	x = v.x;
	return *this;
}

template <typename T>
tvec1<T> & tvec<T, 1>::operator=(const tvec4<T> & v) {
	x = v.x;
	return *this;
}



//------------------------------------------------------------------------------
// Access Operators



template <typename T>
T tvec<T, 1>::operator[](nat i) {
	return *(&x + i);
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- add assign ---

template <typename T>
inline tvec1<T> & operator+=(tvec1<T> & v1, const tvec1<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline tvec1<T> & operator+=(tvec1<T> & v1, const T & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline tvec1<T> & operator+=(tvec1<T> & v1, const tvec2<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline tvec1<T> & operator+=(tvec1<T> & v1, const tvec3<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline tvec1<T> & operator+=(tvec1<T> & v1, const tvec4<T> & v2) {
	return v1 = v1 + v2;
}

//--- subtract assign ---

template <typename T>
inline tvec1<T> & operator-=(tvec1<T> & v1, const tvec1<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline tvec1<T> & operator-=(tvec1<T> & v1, const T & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline tvec1<T> & operator-=(tvec1<T> & v1, const tvec2<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline tvec1<T> & operator-=(tvec1<T> & v1, const tvec3<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline tvec1<T> & operator-=(tvec1<T> & v1, const tvec4<T> & v2) {
	return v1 = v1 - v2;
}

//--- multiply assign ---

template <typename T>
inline tvec1<T> & operator*=(tvec1<T> & v1, const tvec1<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline tvec1<T> & operator*=(tvec1<T> & v1, const T & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline tvec1<T> & operator*=(tvec1<T> & v1, const tvec2<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline tvec1<T> & operator*=(tvec1<T> & v1, const tvec3<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline tvec1<T> & operator*=(tvec1<T> & v1, const tvec4<T> & v2) {
	return v1 = v1 * v2;
}

//--- divide assign ---

template <typename T>
inline tvec1<T> & operator/=(tvec1<T> & v1, const tvec1<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline tvec1<T> & operator/=(tvec1<T> & v1, const T & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline tvec1<T> & operator/=(tvec1<T> & v1, const tvec2<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline tvec1<T> & operator/=(tvec1<T> & v1, const tvec3<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline tvec1<T> & operator/=(tvec1<T> & v1, const tvec4<T> & v2) {
	return v1 = v1 / v2;
}

//--- pre increment ---

template <typename T>
inline tvec1<T> & operator++(tvec1<T> & v) {
	++v.x;
	return v;
}

//--- post increment ---

template <typename T>
inline tvec1<T> operator++(tvec1<T> & v, int) {
	return tvec1<T>(v.x++);
}

//--- pre decrement ---

template <typename T>
inline tvec1<T> & operator--(tvec1<T> & v) {
	--v.x;
	return v;
}

//--- post decrement ---

template <typename T>
inline tvec1<T> operator--(tvec1<T> & v, int) {
	return tvec1<T>(v.x--);
}

//--- positive ---

template <typename T>
inline tvec1<T> operator+(const tvec1<T> & v) {
	return v;
}

//--- negative ---

template <typename T>
inline tvec1<T> operator-(const tvec1<T> & v) {
	return v * static_cast<T>(-1);
}

//--- add ---

template <typename T>
inline tvec1<T> operator+(const tvec1<T> & v1, const tvec1<T> & v2) {
	return tvec1<T>(v1.x + v2.x);
}

template <typename T>
inline tvec1<T> operator+(const tvec1<T> & v1, const T & v2) {
	return tvec1<T>(v1.x + v2);
}

template <typename T>
inline tvec1<T> operator+(const T & v1, const tvec1<T> & v2) {
	return tvec1<T>(v1 + v2.x);
}

//--- subtract ---

template <typename T>
inline tvec1<T> operator-(const tvec1<T> & v1, const tvec1<T> & v2) {
	return tvec1<T>(v1.x - v2.x);
}

template <typename T>
inline tvec1<T> operator-(const tvec1<T> & v1, const T & v2) {
	return tvec1<T>(v1.x - v2);
}

template <typename T>
inline tvec1<T> operator-(const T & v1, const tvec1<T> & v2) {
	return tvec1<T>(v1 - v2.x);
}

//--- multiply ---

template <typename T>
inline tvec1<T> operator*(const tvec1<T> & v1, const tvec1<T> & v2) {
	return tvec1<T>(v1.x * v2.x);
}

template <typename T>
inline tvec1<T> operator*(const tvec1<T> & v1, const T & v2) {
	return tvec1<T>(v1.x * v2);
}

template <typename T>
inline tvec1<T> operator*(const T & v1, const tvec1<T> & v2) {
	return tvec1<T>(v1 * v2.x);
}

//--- divide ---

template <typename T>
inline tvec1<T> operator/(const tvec1<T> & v1, const tvec1<T> & v2) {
	return tvec1<T>(v1.x / v2.x);
}

template <typename T>
inline tvec1<T> operator/(const tvec1<T> & v1, const T & v2) {
	return tvec1<T>(v1.x / v2);
}

template <typename T>
inline tvec1<T> operator/(const T & v1, const tvec1<T> & v2) {
	return tvec1<T>(v1 / v2.x);
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T>
inline bool operator==(const tvec1<T> & v1, const tvec1<T> & v2) {
	return v1.x == v2.x;
}

template <typename T>
inline bool operator==(const tvec1<T> & v1, const T & v2) {
	return v1.x == v2;
}

template <typename T>
inline bool operator==(const T & v1, const tvec1<T> & v2) {
	return v1 == v2.x;
}

//--- not equal to ---

template <typename T>
inline bool operator!=(const tvec1<T> & v1, const tvec1<T> & v2) {
	return v1.x != v2.x;
}

template <typename T>
inline bool operator!=(const tvec1<T> & v1, const T & v2) {
	return v1.x != v2;
}

template <typename T>
inline bool operator!=(const T & v1, const tvec1<T> & v2) {
	return v1 != v2.x;
}

//--- less than ---

template <typename T>
inline bool operator<(const tvec1<T> & v1, const T & v2) {
	return v1.x < v2;
}

template <typename T>
inline bool operator<(const T & v1, const tvec1<T> & v2) {
	return  v1 < v2.x;
}

//--- greater than ---

template <typename T>
inline bool operator>(const tvec1<T> & v1, const T & v2) {
	return v1.x > v2;
}

template <typename T>
inline bool operator>(const T & v1, const tvec1<T> & v2) {
	return  v1 > v2.x;
}

//--- less than or equal to ---

template <typename T>
inline bool operator<=(const tvec1<T> & v1, const T & v2) {
	return v1.x <= v2;
}

template <typename T>
inline bool operator<=(const T & v1, const tvec1<T> & v2) {
	return  v1 <= v2.x;
}

//--- greater than or equal to ---

template <typename T>
inline bool operator>=(const tvec1<T> & v1, const T & v2) {
	return v1.x >= v2;
}

template <typename T>
inline bool operator>=(const T & v1, const tvec1<T> & v2) {
	return  v1 >= v2.x;
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string tvec<T, 1>::toString() const {
	std::stringstream ss;
	ss << "(" << x << ")";
	return ss.str();
}



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const tvec1<T> & v) {
	return os << v.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC2 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr tvec<T, 2>::tvec() :
	x(static_cast<T>(0)), y(static_cast<T>(0))
{}

template <typename T>
constexpr tvec<T, 2>::tvec(const tvec2<T> & v) :
	x(v.x), y(v.y)
{}

template <typename T>
constexpr tvec<T, 2>::tvec(tvec2<T> && v) :
	x(v.x), y(v.y)
{}

template <typename T>
constexpr tvec<T, 2>::tvec(const T & v) :
	x(v), y(v)
{}

template <typename T>
constexpr tvec<T, 2>::tvec(const tvec1<T> & v) :
	x(v.x), y(static_cast<T>(0))
{}

template <typename T>
constexpr tvec<T, 2>::tvec(const tvec3<T> & v) :
	x(v.x), y(v.y)
{}

template <typename T>
constexpr tvec<T, 2>::tvec(const tvec4<T> & v) :
	x(v.x), y(v.y)
{}

template <typename T>
constexpr tvec<T, 2>::tvec(const T & v1, const T & v2) :
	x(v1), y(v2)
{}



//------------------------------------------------------------------------------
// Assignment Operators



template <typename T>
tvec2<T> & tvec<T, 2>::operator=(const tvec2<T> & v) {
	x = v.x; y = v.y;
	return *this;
}

template <typename T>
tvec2<T> & tvec<T, 2>::operator=(tvec2<T> && v) {
	x = v.x; y = v.y;
	return *this;
}

template <typename T>
tvec2<T> & tvec<T, 2>::operator=(const T & v) {
	x = v; y = v;
	return *this;
}

template <typename T>
tvec2<T> & tvec<T, 2>::operator=(const tvec1<T> & v) {
	x = v.x; y = static_cast<T>(0);
	return *this;
}

template <typename T>
tvec2<T> & tvec<T, 2>::operator=(const tvec3<T> & v) {
	x = v.x; y = v.y;
	return *this;
}

template <typename T>
tvec2<T> & tvec<T, 2>::operator=(const tvec4<T> & v) {
	x = v.x; y = v.y;
	return *this;
}



//------------------------------------------------------------------------------
// Access Operators



template <typename T>
T tvec<T, 2>::operator[](nat i) {
	return *(&x + i);
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- add assign ---

template <typename T>
inline tvec2<T> & operator+=(tvec2<T> & v1, const tvec2<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline tvec2<T> & operator+=(tvec2<T> & v1, const T & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline tvec2<T> & operator+=(tvec2<T> & v1, const tvec1<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline tvec2<T> & operator+=(tvec2<T> & v1, const tvec3<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline tvec2<T> & operator+=(tvec2<T> & v1, const tvec4<T> & v2) {
	return v1 = v1 + v2;
}

//--- subtract assign ---

template <typename T>
inline tvec2<T> & operator-=(tvec2<T> & v1, const tvec2<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline tvec2<T> & operator-=(tvec2<T> & v1, const T & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline tvec2<T> & operator-=(tvec2<T> & v1, const tvec1<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline tvec2<T> & operator-=(tvec2<T> & v1, const tvec3<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline tvec2<T> & operator-=(tvec2<T> & v1, const tvec4<T> & v2) {
	return v1 = v1 - v2;
}

//--- multiply assign ---

template <typename T>
inline tvec2<T> & operator*=(tvec2<T> & v1, const tvec2<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline tvec2<T> & operator*=(tvec2<T> & v1, const T & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline tvec2<T> & operator*=(tvec2<T> & v1, const tvec1<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline tvec2<T> & operator*=(tvec2<T> & v1, const tvec3<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline tvec2<T> & operator*=(tvec2<T> & v1, const tvec4<T> & v2) {
	return v1 = v1 * v2;
}

//--- divide assign ---

template <typename T>
inline tvec2<T> & operator/=(tvec2<T> & v1, const tvec2<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline tvec2<T> & operator/=(tvec2<T> & v1, const T & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline tvec2<T> & operator/=(tvec2<T> & v1, const tvec1<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline tvec2<T> & operator/=(tvec2<T> & v1, const tvec3<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline tvec2<T> & operator/=(tvec2<T> & v1, const tvec4<T> & v2) {
	return v1 = v1 / v2;
}

//--- pre increment ---

template <typename T>
inline tvec2<T> & operator++(tvec2<T> & v) {
	++v.x; ++v.y;
	return v;
}

//--- post increment ---

template <typename T>
inline tvec2<T> operator++(tvec2<T> & v, int) {
	return tvec2<T>(v.x++, v.y++);
}

//--- pre decrement ---

template <typename T>
inline tvec2<T> & operator--(tvec2<T> & v) {
	--v.x; --v.y;
	return v;
}

//--- post decrement ---

template <typename T>
inline tvec2<T> operator--(tvec2<T> & v, int) {
	return tvec2<T>(v.x--, v.y--);
}

//--- positive ---

template <typename T>
inline tvec2<T> operator+(const tvec2<T> & v) {
	return v;
}

//--- negative ---

template <typename T>
inline tvec2<T> operator-(const tvec2<T> & v) {
	return v * static_cast<T>(-1);
}

//--- add ---

template <typename T>
inline tvec2<T> operator+(const tvec2<T> & v1, const tvec2<T> & v2) {
	return tvec2<T>(v1.x + v2.x, v1.y + v2.y);
}

template <typename T>
inline tvec2<T> operator+(const tvec2<T> & v1, const T & v2) {
	return tvec2<T>(v1.x + v2, v1.y + v2);
}

template <typename T>
inline tvec2<T> operator+(const T & v1, const tvec2<T> & v2) {
	return tvec2<T>(v1 + v2.x, v1 + v2.y);
}

template <typename T>
inline tvec2<T> operator+(const tvec2<T> & v1, const tvec1<T> & v2) {
	return tvec2<T>(v1.x + v2.x, v1.y);
}

template <typename T>
inline tvec2<T> operator+(const tvec1<T> & v1, const tvec2<T> & v2) {
	return tvec2<T>(v1.x + v2.x, v2.y);
}

//--- subtract ---

template <typename T>
inline tvec2<T> operator-(const tvec2<T> & v1, const tvec2<T> & v2) {
	return tvec2<T>(v1.x - v2.x, v1.y - v2.y);
}

template <typename T>
inline tvec2<T> operator-(const tvec2<T> & v1, const T & v2) {
	return tvec2<T>(v1.x - v2, v1.y - v2);
}

template <typename T>
inline tvec2<T> operator-(const T & v1, const tvec2<T> & v2) {
	return tvec2<T>(v1 - v2.x, v1 - v2.y);
}

template <typename T>
inline tvec2<T> operator-(const tvec2<T> & v1, const tvec1<T> & v2) {
	return tvec2<T>(v1.x - v2.x, v1.y);
}

template <typename T>
inline tvec2<T> operator-(const tvec1<T> & v1, const tvec2<T> & v2) {
	return tvec2<T>(v1.x - v2.x, v2.y);
}

//--- multiply ---

template <typename T>
inline tvec2<T> operator*(const tvec2<T> & v1, const tvec2<T> & v2) {
	return tvec2<T>(v1.x * v2.x, v1.y * v2.y);
}

template <typename T>
inline tvec2<T> operator*(const tvec2<T> & v1, const T & v2) {
	return tvec2<T>(v1.x * v2, v1.y * v2);
}

template <typename T>
inline tvec2<T> operator*(const T & v1, const tvec2<T> & v2) {
	return tvec2<T>(v1 * v2.x, v1 * v2.y);
}

template <typename T>
inline tvec2<T> operator*(const tvec2<T> & v1, const tvec1<T> & v2) {
	return tvec2<T>(v1.x * v2.x, v1.y);
}

template <typename T>
inline tvec2<T> operator*(const tvec1<T> & v1, const tvec2<T> & v2) {
	return tvec2<T>(v1.x * v2.x, v2.y);
}

//--- divide ---

template <typename T>
inline tvec2<T> operator/(const tvec2<T> & v1, const tvec2<T> & v2) {
	return tvec2<T>(v1.x / v2.x, v1.y / v2.y);
}

template <typename T>
inline tvec2<T> operator/(const tvec2<T> & v1, const T & v2) {
	return tvec2<T>(v1.x / v2, v1.y / v2);
}

template <typename T>
inline tvec2<T> operator/(const T & v1, const tvec2<T> & v2) {
	return tvec2<T>(v1 / v2.x, v1 / v2.y);
}

template <typename T>
inline tvec2<T> operator/(const tvec2<T> & v1, const tvec1<T> & v2) {
	return tvec2<T>(v1.x / v2.x, v1.y);
}

template <typename T>
inline tvec2<T> operator/(const tvec1<T> & v1, const tvec2<T> & v2) {
	return tvec2<T>(v1.x / v2.x, v2.y);
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T>
inline bool operator==(const tvec2<T> & v1, const tvec2<T> & v2) {
	return v1.x == v2.x && v1.y == v2.y;
}

template <typename T>
inline bool operator==(const tvec2<T> & v1, const T & v2) {
	return v1.x == v2 && v1.y == v2;
}

template <typename T>
inline bool operator==(const T & v1, const tvec2<T> & v2) {
	return v1 == v2.x && v1 == v2.y;
}

//--- not equal to ---

template <typename T>
inline bool operator!=(const tvec2<T> & v1, const tvec2<T> & v2) {
	return v1.x != v2.x || v1.y != v2.y;
}

template <typename T>
inline bool operator!=(const tvec2<T> & v1, const T & v2) {
	return v1.x != v2 || v1.y != v2;
}

template <typename T>
inline bool operator!=(const T & v1, const tvec2<T> & v2) {
	return v1 != v2.x || v1 != v2.y;
}

//--- less than ---

template <typename T>
inline bool operator<(const tvec2<T> & v1, const T & v2) {
	return v1.x < v2 && v1.y < v2;
}

template <typename T>
inline bool operator<(const T & v1, const tvec2<T> & v2) {
	return  v1 < v2.x && v1 < v2.y;
}

//--- greater than ---

template <typename T>
inline bool operator>(const tvec2<T> & v1, const T & v2) {
	return v1.x > v2 && v1.y > v2;
}

template <typename T>
inline bool operator>(const T & v1, const tvec2<T> & v2) {
	return  v1 > v2.x && v1 > v2.y;
}

//--- less than or equal to ---

template <typename T>
inline bool operator<=(const tvec2<T> & v1, const T & v2) {
	return v1.x <= v2 && v1.y <= v2;
}

template <typename T>
inline bool operator<=(const T & v1, const tvec2<T> & v2) {
	return  v1 <= v2.x && v1 <= v2.y;
}

//--- greater than or equal to ---

template <typename T>
inline bool operator>=(const tvec2<T> & v1, const T & v2) {
	return v1.x >= v2 && v1.y >= v2;
}

template <typename T>
inline bool operator>=(const T & v1, const tvec2<T> & v2) {
	return  v1 >= v2.x && v1 >= v2.y;
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string tvec<T, 2>::toString() const {
	std::stringstream ss;
	ss << "(" << x << ", " << y << ")";
	return ss.str();
}



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const tvec2<T> & v) {
	return os << v.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC3 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr tvec<T, 3>::tvec() :
	x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0))
{}

template <typename T>
constexpr tvec<T, 3>::tvec(const tvec3<T> & v) :
	x(v.x), y(v.y), z(v.z)
{}

template <typename T>
constexpr tvec<T, 3>::tvec(tvec3<T> && v) :
	x(v.x), y(v.y), z(v.z)
{}

template <typename T>
constexpr tvec<T, 3>::tvec(const T & v) :
	x(v), y(v), z(v)
{}

template <typename T>
constexpr tvec<T, 3>::tvec(const tvec1<T> & v) :
	x(v.x), y(static_cast<T>(0)), z(static_cast<T>(0))
{}

template <typename T>
constexpr tvec<T, 3>::tvec(const tvec2<T> & v) :
	x(v.x), y(v.y), z(static_cast<T>(0))
{}

template <typename T>
constexpr tvec<T, 3>::tvec(const tvec4<T> & v) :
	x(v.x), y(v.y), z(v.z)
{}

template <typename T>
constexpr tvec<T, 3>::tvec(const T & v1, const T & v2, const T & v3) :
	x(v1), y(v2), z(v3)
{}



//------------------------------------------------------------------------------
// Assignment Operators



template <typename T>
tvec3<T> & tvec<T, 3>::operator=(const tvec3<T> & v) {
	x = v.x; y = v.y; z = v.z;
	return *this;
}

template <typename T>
tvec3<T> & tvec<T, 3>::operator=(tvec3<T> && v) {
	x = v.x; y = v.y; z = v.z;
	return *this;
}

template <typename T>
tvec3<T> & tvec<T, 3>::operator=(const T & v) {
	x = v; y = v; z = v;
	return *this;
}

template <typename T>
tvec3<T> & tvec<T, 3>::operator=(const tvec1<T> & v) {
	x = v.x; y = static_cast<T>(0); z = static_cast<T>(0);
	return *this;
}

template <typename T>
tvec3<T> & tvec<T, 3>::operator=(const tvec2<T> & v) {
	x = v.x; y = v.y; z = static_cast<T>(0);
	return *this;
}

template <typename T>
tvec3<T> & tvec<T, 3>::operator=(const tvec4<T> & v) {
	x = v.x; y = v.y; z = v.z;
	return *this;
}



//------------------------------------------------------------------------------
// Access Operators



template <typename T>
T tvec<T, 3>::operator[](nat i) {
	return *(&x + i);
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- add assign ---

template <typename T>
inline tvec3<T> & operator+=(tvec3<T> & v1, const tvec3<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline tvec3<T> & operator+=(tvec3<T> & v1, const T & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline tvec3<T> & operator+=(tvec3<T> & v1, const tvec1<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline tvec3<T> & operator+=(tvec3<T> & v1, const tvec2<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline tvec3<T> & operator+=(tvec3<T> & v1, const tvec4<T> & v2) {
	return v1 = v1 + v2;
}

//--- subtract assign ---

template <typename T>
inline tvec3<T> & operator-=(tvec3<T> & v1, const tvec3<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline tvec3<T> & operator-=(tvec3<T> & v1, const T & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline tvec3<T> & operator-=(tvec3<T> & v1, const tvec1<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline tvec3<T> & operator-=(tvec3<T> & v1, const tvec2<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline tvec3<T> & operator-=(tvec3<T> & v1, const tvec4<T> & v2) {
	return v1 = v1 - v2;
}

//--- multiply assign ---

template <typename T>
inline tvec3<T> & operator*=(tvec3<T> & v1, const tvec3<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline tvec3<T> & operator*=(tvec3<T> & v1, const T & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline tvec3<T> & operator*=(tvec3<T> & v1, const tvec1<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline tvec3<T> & operator*=(tvec3<T> & v1, const tvec2<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline tvec3<T> & operator*=(tvec3<T> & v1, const tvec4<T> & v2) {
	return v1 = v1 * v2;
}

//--- divide assign ---

template <typename T>
inline tvec3<T> & operator/=(tvec3<T> & v1, const tvec3<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline tvec3<T> & operator/=(tvec3<T> & v1, const T & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline tvec3<T> & operator/=(tvec3<T> & v1, const tvec1<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline tvec3<T> & operator/=(tvec3<T> & v1, const tvec2<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline tvec3<T> & operator/=(tvec3<T> & v1, const tvec4<T> & v2) {
	return v1 = v1 / v2;
}

//--- pre increment ---

template <typename T>
inline tvec3<T> & operator++(tvec3<T> & v) {
	++v.x; ++v.y; ++v.z;
	return v;
}

//--- post increment ---

template <typename T>
inline tvec3<T> operator++(tvec3<T> & v, int) {
	return tvec3<T>(v.x++, v.y++, v.z++);
}

//--- pre decrement ---

template <typename T>
inline tvec3<T> & operator--(tvec3<T> & v) {
	--v.x; --v.y; --v.z;
	return v;
}

//--- post decrement ---

template <typename T>
inline tvec3<T> operator--(tvec3<T> & v, int) {
	return tvec3<T>(v.x--, v.y--, v.z--);
}

//--- positive ---

template <typename T>
inline tvec3<T> operator+(const tvec3<T> & v) {
	return v;
}

//--- negative ---

template <typename T>
inline tvec3<T> operator-(const tvec3<T> & v) {
	return v * static_cast<T>(-1);
}

//--- add ---

template <typename T>
inline tvec3<T> operator+(const tvec3<T> & v1, const tvec3<T> & v2) {
	return tvec3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

template <typename T>
inline tvec3<T> operator+(const tvec3<T> & v1, const T & v2) {
	return tvec3<T>(v1.x + v2, v1.y + v2, v1.z + v2);
}

template <typename T>
inline tvec3<T> operator+(const T & v1, const tvec3<T> & v2) {
	return tvec3<T>(v1 + v2.x, v1 + v2.y, v1 + v2.z);
}

template <typename T>
inline tvec3<T> operator+(const tvec3<T> & v1, const tvec1<T> & v2) {
	return tvec3<T>(v1.x + v2.x, v1.y, v1.z);
}

template <typename T>
inline tvec3<T> operator+(const tvec1<T> & v1, const tvec3<T> & v2) {
	return tvec3<T>(v1.x + v2.x, v2.y, v2.z);
}

template <typename T>
inline tvec3<T> operator+(const tvec3<T> & v1, const tvec2<T> & v2) {
	return tvec3<T>(v1.x + v2.x, v1.y + v2.y, v1.z);
}

template <typename T>
inline tvec3<T> operator+(const tvec2<T> & v1, const tvec3<T> & v2) {
	return tvec3<T>(v1.x + v2.x, v1.y + v2.y, v2.z);
}

//--- subtract ---

template <typename T>
inline tvec3<T> operator-(const tvec3<T> & v1, const tvec3<T> & v2) {
	return tvec3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

template <typename T>
inline tvec3<T> operator-(const tvec3<T> & v1, const T & v2) {
	return tvec3<T>(v1.x - v2, v1.y - v2, v1.z - v2);
}

template <typename T>
inline tvec3<T> operator-(const T & v1, const tvec3<T> & v2) {
	return tvec3<T>(v1 - v2.x, v1 - v2.y, v1 - v2.z);
}

template <typename T>
inline tvec3<T> operator-(const tvec3<T> & v1, const tvec1<T> & v2) {
	return tvec3<T>(v1.x - v2.x, v1.y, v1.z);
}

template <typename T>
inline tvec3<T> operator-(const tvec1<T> & v1, const tvec3<T> & v2) {
	return tvec3<T>(v1.x - v2.x, v2.y, v2.z);
}

template <typename T>
inline tvec3<T> operator-(const tvec3<T> & v1, const tvec2<T> & v2) {
	return tvec3<T>(v1.x - v2.x, v1.y - v2.y, v1.z);
}

template <typename T>
inline tvec3<T> operator-(const tvec2<T> & v1, const tvec3<T> & v2) {
	return tvec3<T>(v1.x - v2.x, v1.y - v2.y, v2.z);
}

//--- multiply ---

template <typename T>
inline tvec3<T> operator*(const tvec3<T> & v1, const tvec3<T> & v2) {
	return tvec3<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

template <typename T>
inline tvec3<T> operator*(const tvec3<T> & v1, const T & v2) {
	return tvec3<T>(v1.x * v2, v1.y * v2, v1.z * v2);
}

template <typename T>
inline tvec3<T> operator*(const T & v1, const tvec3<T> & v2) {
	return tvec3<T>(v1 * v2.x, v1 * v2.y, v1 * v2.z);
}

template <typename T>
inline tvec3<T> operator*(const tvec3<T> & v1, const tvec1<T> & v2) {
	return tvec3<T>(v1.x * v2.x, v1.y, v1.z);
}

template <typename T>
inline tvec3<T> operator*(const tvec1<T> & v1, const tvec3<T> & v2) {
	return tvec3<T>(v1.x * v2.x, v2.y, v2.z);
}

template <typename T>
inline tvec3<T> operator*(const tvec3<T> & v1, const tvec2<T> & v2) {
	return tvec3<T>(v1.x * v2.x, v1.y * v2.y, v1.z);
}

template <typename T>
inline tvec3<T> operator*(const tvec2<T> & v1, const tvec3<T> & v2) {
	return tvec3<T>(v1.x * v2.x, v1.y * v2.y, v2.z);
}

//--- divide ---

template <typename T>
inline tvec3<T> operator/(const tvec3<T> & v1, const tvec3<T> & v2) {
	return tvec3<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

template <typename T>
inline tvec3<T> operator/(const tvec3<T> & v1, const T & v2) {
	return tvec3<T>(v1.x / v2, v1.y / v2, v1.z / v2);
}

template <typename T>
inline tvec3<T> operator/(const T & v1, const tvec3<T> & v2) {
	return tvec3<T>(v1 / v2.x, v1 / v2.y, v1 / v2.z);
}

template <typename T>
inline tvec3<T> operator/(const tvec3<T> & v1, const tvec1<T> & v2) {
	return tvec3<T>(v1.x / v2.x, v1.y, v1.z);
}

template <typename T>
inline tvec3<T> operator/(const tvec1<T> & v1, const tvec3<T> & v2) {
	return tvec3<T>(v1.x / v2.x, v2.y, v2.z);
}

template <typename T>
inline tvec3<T> operator/(const tvec3<T> & v1, const tvec2<T> & v2) {
	return tvec3<T>(v1.x / v2.x, v1.y / v2.y, v1.z);
}

template <typename T>
inline tvec3<T> operator/(const tvec2<T> & v1, const tvec3<T> & v2) {
	return tvec3<T>(v1.x / v2.x, v1.y / v2.y, v2.z);
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T>
inline bool operator==(const tvec3<T> & v1, const tvec3<T> & v2) {
	return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

template <typename T>
inline bool operator==(const tvec3<T> & v1, const T & v2) {
	return v1.x == v2 && v1.y == v2 && v1.z == v2;
}

template <typename T>
inline bool operator==(const T & v1, const tvec3<T> & v2) {
	return v1 == v2.x && v1 == v2.y && v1 == v2.z;
}

//--- not equal to ---

template <typename T>
inline bool operator!=(const tvec3<T> & v1, const tvec3<T> & v2) {
	return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z;
}

template <typename T>
inline bool operator!=(const tvec3<T> & v1, const T & v2) {
	return v1.x != v2 || v1.y != v2 || v1.z != v2;
}

template <typename T>
inline bool operator!=(const T & v1, const tvec3<T> & v2) {
	return v1 != v2.x || v1 != v2.y || v1 != v2.z;
}

//--- less than ---

template <typename T>
inline bool operator<(const tvec3<T> & v1, const T & v2) {
	return v1.x < v2 && v1.y < v2 && v1.z < v2;
}

template <typename T>
inline bool operator<(const T & v1, const tvec3<T> & v2) {
	return  v1 < v2.x && v1 < v2.y && v1 < v2.z;
}

//--- greater than ---

template <typename T>
inline bool operator>(const tvec3<T> & v1, const T & v2) {
	return v1.x > v2 && v1.y > v2 && v1.z > v2;
}

template <typename T>
inline bool operator>(const T & v1, const tvec3<T> & v2) {
	return  v1 > v2.x && v1 > v2.y && v1 > v2.z;
}

//--- less than or equal to ---

template <typename T>
inline bool operator<=(const tvec3<T> & v1, const T & v2) {
	return v1.x <= v2 && v1.y <= v2 && v1.z <= v2;
}

template <typename T>
inline bool operator<=(const T & v1, const tvec3<T> & v2) {
	return  v1 <= v2.x && v1 <= v2.y && v1 <= v2.z;
}

//--- greater than or equal to ---

template <typename T>
inline bool operator>=(const tvec3<T> & v1, const T & v2) {
	return v1.x >= v2 && v1.y >= v2 && v1.z >= v2;
}

template <typename T>
inline bool operator>=(const T & v1, const tvec3<T> & v2) {
	return  v1 >= v2.x && v1 >= v2.y && v1 >= v2.z;
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string tvec<T, 3>::toString() const {
	std::stringstream ss;
	ss << "(" << x << ", " << y << ", " << z << ")";
	return ss.str();
}



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const tvec3<T> & v) {
	return os << v.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC4 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr tvec<T, 4>::tvec() :
	x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)), w(static_cast<T>(0))
{}

template <typename T>
constexpr tvec<T, 4>::tvec(const tvec4<T> & v) :
	x(v.x), y(v.y), z(v.z), w(v.w)
{}

template <typename T>
constexpr tvec<T, 4>::tvec(tvec4<T> && v) :
	x(v.x), y(v.y), z(v.z), w(v.w)
{}

template <typename T>
constexpr tvec<T, 4>::tvec(const T & v) :
	x(v), y(v), z(v), w(v)
{}

template <typename T>
constexpr tvec<T, 4>::tvec(const tvec1<T> & v) :
	x(v.x), y(static_cast<T>(0)), z(static_cast<T>(0)), w(static_cast<T>(0))
{}

template <typename T>
constexpr tvec<T, 4>::tvec(const tvec2<T> & v) :
	x(v.x), y(v.y), z(static_cast<T>(0)), w(static_cast<T>(0))
{}

template <typename T>
constexpr tvec<T, 4>::tvec(const tvec3<T> & v) :
	x(v.x), y(v.y), z(v.z), w(static_cast<T>(0))
{}

template <typename T>
constexpr tvec<T, 4>::tvec(const T & v1, const T & v2, const T & v3, const T & v4) :
	x(v1), y(v2), z(v3), w(v4)
{}



//------------------------------------------------------------------------------
// Assignment Operators



template <typename T>
tvec4<T> & tvec<T, 4>::operator=(const tvec4<T> & v) {
	x = v.x; y = v.y; z = v.z; w = v.w;
	return *this;
}

template <typename T>
tvec4<T> & tvec<T, 4>::operator=(tvec4<T> && v) {
	x = v.x; y = v.y; z = v.z; w = v.w;
	return *this;
}

template <typename T>
tvec4<T> & tvec<T, 4>::operator=(const T & v) {
	x = v; y = v; z = v; w = v;
	return *this;
}

template <typename T>
tvec4<T> & tvec<T, 4>::operator=(const tvec1<T> & v) {
	x = v.x; y = static_cast<T>(0); z = static_cast<T>(0); w = static_cast<T>(0);
	return *this;
}

template <typename T>
tvec4<T> & tvec<T, 4>::operator=(const tvec2<T> & v) {
	x = v.x; y = v.y; z = static_cast<T>(0); w = static_cast<T>(0);
	return *this;
}

template <typename T>
tvec4<T> & tvec<T, 4>::operator=(const tvec3<T> & v) {
	x = v.x; y = v.y; z = v.z; w = static_cast<T>(0);
	return *this;
}



//------------------------------------------------------------------------------
// Access Operators



template <typename T>
T tvec<T, 4>::operator[](nat i) {
	return *(&x + i);
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- add assign ---

template <typename T>
inline tvec4<T> & operator+=(tvec4<T> & v1, const tvec4<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline tvec4<T> & operator+=(tvec4<T> & v1, const T & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline tvec4<T> & operator+=(tvec4<T> & v1, const tvec1<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline tvec4<T> & operator+=(tvec4<T> & v1, const tvec2<T> & v2) {
	return v1 = v1 + v2;
}

template <typename T>
inline tvec4<T> & operator+=(tvec4<T> & v1, const tvec3<T> & v2) {
	return v1 = v1 + v2;
}

//--- subtract assign ---

template <typename T>
inline tvec4<T> & operator-=(tvec4<T> & v1, const tvec4<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline tvec4<T> & operator-=(tvec4<T> & v1, const T & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline tvec4<T> & operator-=(tvec4<T> & v1, const tvec1<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline tvec4<T> & operator-=(tvec4<T> & v1, const tvec2<T> & v2) {
	return v1 = v1 - v2;
}

template <typename T>
inline tvec4<T> & operator-=(tvec4<T> & v1, const tvec3<T> & v2) {
	return v1 = v1 - v2;
}

//--- multiply assign ---

template <typename T>
inline tvec4<T> & operator*=(tvec4<T> & v1, const tvec4<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline tvec4<T> & operator*=(tvec4<T> & v1, const T & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline tvec4<T> & operator*=(tvec4<T> & v1, const tvec1<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline tvec4<T> & operator*=(tvec4<T> & v1, const tvec2<T> & v2) {
	return v1 = v1 * v2;
}

template <typename T>
inline tvec4<T> & operator*=(tvec4<T> & v1, const tvec3<T> & v2) {
	return v1 = v1 * v2;
}

//--- divide assign ---

template <typename T>
inline tvec4<T> & operator/=(tvec4<T> & v1, const tvec4<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline tvec4<T> & operator/=(tvec4<T> & v1, const T & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline tvec4<T> & operator/=(tvec4<T> & v1, const tvec1<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline tvec4<T> & operator/=(tvec4<T> & v1, const tvec2<T> & v2) {
	return v1 = v1 / v2;
}

template <typename T>
inline tvec4<T> & operator/=(tvec4<T> & v1, const tvec3<T> & v2) {
	return v1 = v1 / v2;
}

//--- pre increment ---

template <typename T>
inline tvec4<T> & operator++(tvec4<T> & v) {
	++v.x; ++v.y; ++v.z; ++v.w;
	return v;
}

//--- post increment ---

template <typename T>
inline tvec4<T> operator++(tvec4<T> & v, int) {
	return tvec4<T>(v.x++, v.y++, v.z++, v.w++);
}

//--- pre decrement ---

template <typename T>
inline tvec4<T> & operator--(tvec4<T> & v) {
	--v.x; --v.y; --v.z; --v.w;
	return v;
}

//--- post decrement ---

template <typename T>
inline tvec4<T> operator--(tvec4<T> & v, int) {
	return tvec4<T>(v.x--, v.y--, v.z--, v.w--);
}

//--- positive ---

template <typename T>
inline tvec4<T> operator+(const tvec4<T> & v) {
	return v;
}

//--- negative ---

template <typename T>
inline tvec4<T> operator-(const tvec4<T> & v) {
	return v * static_cast<T>(-1);
}

//--- add ---

template <typename T>
inline tvec4<T> operator+(const tvec4<T> & v1, const tvec4<T> & v2) {
	return tvec4<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

template <typename T>
inline tvec4<T> operator+(const tvec4<T> & v1, const T & v2) {
	return tvec4<T>(v1.x + v2, v1.y + v2, v1.z + v2, v1.w + v2);
}

template <typename T>
inline tvec4<T> operator+(const T & v1, const tvec4<T> & v2) {
	return tvec4<T>(v1 + v2.x, v1 + v2.y, v1 + v2.z, v1 + v2.w);
}

template <typename T>
inline tvec4<T> operator+(const tvec4<T> & v1, const tvec1<T> & v2) {
	return tvec4<T>(v1.x + v2.x, v1.y, v1.z, v1.w);
}

template <typename T>
inline tvec4<T> operator+(const tvec1<T> & v1, const tvec4<T> & v2) {
	return tvec4<T>(v1.x + v2.x, v2.y, v2.z, v2.w);
}

template <typename T>
inline tvec4<T> operator+(const tvec4<T> & v1, const tvec2<T> & v2) {
	return tvec4<T>(v1.x + v2.x, v1.y + v2.y, v1.z, v1.w);
}

template <typename T>
inline tvec4<T> operator+(const tvec2<T> & v1, const tvec4<T> & v2) {
	return tvec4<T>(v1.x + v2.x, v1.y + v2.y, v2.z, v2.w);
}

template <typename T>
inline tvec4<T> operator+(const tvec4<T> & v1, const tvec3<T> & v2) {
	return tvec4<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w);
}

template <typename T>
inline tvec4<T> operator+(const tvec3<T> & v1, const tvec4<T> & v2) {
	return tvec4<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v2.w);
}

//--- subtract ---

template <typename T>
inline tvec4<T> operator-(const tvec4<T> & v1, const tvec4<T> & v2) {
	return tvec4<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

template <typename T>
inline tvec4<T> operator-(const tvec4<T> & v1, const T & v2) {
	return tvec4<T>(v1.x - v2, v1.y - v2, v1.z - v2, v1.w - v2);
}

template <typename T>
inline tvec4<T> operator-(const T & v1, const tvec4<T> & v2) {
	return tvec4<T>(v1 - v2.x, v1 - v2.y, v1 - v2.z, v1 - v2.w);
}

template <typename T>
inline tvec4<T> operator-(const tvec4<T> & v1, const tvec1<T> & v2) {
	return tvec4<T>(v1.x - v2.x, v1.y, v1.z, v1.w);
}

template <typename T>
inline tvec4<T> operator-(const tvec1<T> & v1, const tvec4<T> & v2) {
	return tvec4<T>(v1.x - v2.x, v2.y, v2.z, v2.w);
}

template <typename T>
inline tvec4<T> operator-(const tvec4<T> & v1, const tvec2<T> & v2) {
	return tvec4<T>(v1.x - v2.x, v1.y - v2.y, v1.z, v1.w);
}

template <typename T>
inline tvec4<T> operator-(const tvec2<T> & v1, const tvec4<T> & v2) {
	return tvec4<T>(v1.x - v2.x, v1.y - v2.y, v2.z, v2.w);
}

template <typename T>
inline tvec4<T> operator-(const tvec4<T> & v1, const tvec3<T> & v2) {
	return tvec4<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w);
}

template <typename T>
inline tvec4<T> operator-(const tvec3<T> & v1, const tvec4<T> & v2) {
	return tvec4<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v2.w);
}

//--- multiply ---

template <typename T>
inline tvec4<T> operator*(const tvec4<T> & v1, const tvec4<T> & v2) {
	return tvec4<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

template <typename T>
inline tvec4<T> operator*(const tvec4<T> & v1, const T & v2) {
	return tvec4<T>(v1.x * v2, v1.y * v2, v1.z * v2, v1.w * v2);
}

template <typename T>
inline tvec4<T> operator*(const T & v1, const tvec4<T> & v2) {
	return tvec4<T>(v1 * v2.x, v1 * v2.y, v1 * v2.z, v1 * v2.w);
}

template <typename T>
inline tvec4<T> operator*(const tvec4<T> & v1, const tvec1<T> & v2) {
	return tvec4<T>(v1.x * v2.x, v1.y, v1.z, v1.w);
}

template <typename T>
inline tvec4<T> operator*(const tvec1<T> & v1, const tvec4<T> & v2) {
	return tvec4<T>(v1.x * v2.x, v2.y, v2.z, v2.w);
}

template <typename T>
inline tvec4<T> operator*(const tvec4<T> & v1, const tvec2<T> & v2) {
	return tvec4<T>(v1.x * v2.x, v1.y * v2.y, v1.z, v1.w);
}

template <typename T>
inline tvec4<T> operator*(const tvec2<T> & v1, const tvec4<T> & v2) {
	return tvec4<T>(v1.x * v2.x, v1.y * v2.y, v2.z, v2.w);
}

template <typename T>
inline tvec4<T> operator*(const tvec4<T> & v1, const tvec3<T> & v2) {
	return tvec4<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w);
}

template <typename T>
inline tvec4<T> operator*(const tvec3<T> & v1, const tvec4<T> & v2) {
	return tvec4<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v2.w);
}

//--- divide ---

template <typename T>
inline tvec4<T> operator/(const tvec4<T> & v1, const tvec4<T> & v2) {
	return tvec4<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
}

template <typename T>
inline tvec4<T> operator/(const tvec4<T> & v1, const T & v2) {
	return tvec4<T>(v1.x / v2, v1.y / v2, v1.z / v2, v1.w / v2);
}

template <typename T>
inline tvec4<T> operator/(const T & v1, const tvec4<T> & v2) {
	return tvec4<T>(v1 / v2.x, v1 / v2.y, v1 / v2.z, v1 / v2.w);
}

template <typename T>
inline tvec4<T> operator/(const tvec4<T> & v1, const tvec1<T> & v2) {
	return tvec4<T>(v1.x / v2.x, v1.y, v1.z, v1.w);
}

template <typename T>
inline tvec4<T> operator/(const tvec1<T> & v1, const tvec4<T> & v2) {
	return tvec4<T>(v1.x / v2.x, v2.y, v2.z, v2.w);
}

template <typename T>
inline tvec4<T> operator/(const tvec4<T> & v1, const tvec2<T> & v2) {
	return tvec4<T>(v1.x / v2.x, v1.y / v2.y, v1.z, v1.w);
}

template <typename T>
inline tvec4<T> operator/(const tvec2<T> & v1, const tvec4<T> & v2) {
	return tvec4<T>(v1.x / v2.x, v1.y / v2.y, v2.z, v2.w);
}

template <typename T>
inline tvec4<T> operator/(const tvec4<T> & v1, const tvec3<T> & v2) {
	return tvec4<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w);
}

template <typename T>
inline tvec4<T> operator/(const tvec3<T> & v1, const tvec4<T> & v2) {
	return tvec4<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v2.w);
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T>
inline bool operator==(const tvec4<T> & v1, const tvec4<T> & v2) {
	return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
}

template <typename T>
inline bool operator==(const tvec4<T> & v1, const T & v2) {
	return v1.x == v2 && v1.y == v2 && v1.z == v2 && v1.w == v2;
}

template <typename T>
inline bool operator==(const T & v1, const tvec4<T> & v2) {
	return v1 == v2.x && v1 == v2.y && v1 == v2.z && v1 == v2.w;
}

//--- not equal to ---

template <typename T>
inline bool operator!=(const tvec4<T> & v1, const tvec4<T> & v2) {
	return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z || v1.w != v2.w;
}

template <typename T>
inline bool operator!=(const tvec4<T> & v1, const T & v2) {
	return v1.x != v2 || v1.y != v2 || v1.z != v2 || v1.w != v2;
}

template <typename T>
inline bool operator!=(const T & v1, const tvec4<T> & v2) {
	return v1 != v2.x || v1 != v2.y || v1 != v2.z || v1 != v2.w;
}

//--- less than ---

template <typename T>
inline bool operator<(const tvec4<T> & v1, const T & v2) {
	return v1.x < v2 && v1.y < v2 && v1.z < v2 && v1.w < v2;
}

template <typename T>
inline bool operator<(const T & v1, const tvec4<T> & v2) {
	return  v1 < v2.x && v1 < v2.y && v1 < v2.z && v1 < v2.w;
}

//--- greater than ---

template <typename T>
inline bool operator>(const tvec4<T> & v1, const T & v2) {
	return v1.x > v2 && v1.y > v2 && v1.z > v2 && v1.w > v2;
}

template <typename T>
inline bool operator>(const T & v1, const tvec4<T> & v2) {
	return  v1 > v2.x && v1 > v2.y && v1 > v2.z && v1 > v2.w;
}

//--- less than or equal to ---

template <typename T>
inline bool operator<=(const tvec4<T> & v1, const T & v2) {
	return v1.x <= v2 && v1.y <= v2 && v1.z <= v2 && v1.w <= v2;
}

template <typename T>
inline bool operator<=(const T & v1, const tvec4<T> & v2) {
	return  v1 <= v2.x && v1 <= v2.y && v1 <= v2.z && v1 <= v2.w;
}

//--- greater than or equal to ---

template <typename T>
inline bool operator>=(const tvec4<T> & v1, const T & v2) {
	return v1.x >= v2 && v1.y >= v2 && v1.z >= v2 && v1.w >= v2;
}

template <typename T>
inline bool operator>=(const T & v1, const tvec4<T> & v2) {
	return  v1 >= v2.x && v1 >= v2.y && v1 >= v2.z && v1 >= v2.w;
}



//------------------------------------------------------------------------------
// Other



template <typename T>
inline std::string tvec<T, 4>::toString() const {
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + ")";
}



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const tvec4<T> & v) {
	return os << v.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC6 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr tvec<T, 6>::tvec() :
	x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)), width(static_cast<T>(0)), height(static_cast<T>(0)), depth(static_cast<T>(0))
{}

template <typename T>
constexpr tvec<T, 6>::tvec(const bound3<T> & v) :
	x(v.x), y(v.y), z(v.z), width(v.width), height(v.height), depth(v.depth)
{}

template <typename T>
constexpr tvec<T, 6>::tvec(bound3<T> && v) :
	x(v.x), y(v.y), z(v.z), width(v.width), height(v.height), depth(v.depth)
{}

template <typename T>
constexpr tvec<T, 6>::tvec(const tvec3<T> & v1, const tvec3<T> & v2) :
	x(v1.x), y(v1.y), z(v1.z), width(v2.x), height(v2.y), depth(v2.z)
{}

template <typename T>
constexpr tvec<T, 6>::tvec(const T & v1, const T & v2, const T & v3, const T & v4, const T & v5, const T & v6) :
	x(v1), y(v2), z(v3), width(v4), height(v5), depth(v6)
{}



//------------------------------------------------------------------------------
// Assignment Operators



template <typename T>
bound3<T> & tvec<T, 6>::operator=(const bound3<T> & v) {
	x = v.x; y = v.y; z = v.z; width = v.width; height = v.height; depth = v.depth;
	return *this;
}

template <typename T>
bound3<T> & tvec<T, 6>::operator=(bound3<T> && v) {
	x = v.x; y = v.y; z = v.z; width = v.width; height = v.height; depth = v.depth;
	return *this;
}



//------------------------------------------------------------------------------
// Access Operators



template <typename T>
T tvec<T, 6>::operator[](nat i) {
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
inline std::string tvec<T, 6>::toString() const {
	std::stringstream ss;
	ss << "(" << x << ", " << y << ", " << z << ", " << width << ", " << height << ", " << depth << ")";
	return ss.str();
}



template <typename T>
inline std::ostream & operator<<(std::ostream & os, const bound3<T> & v) {
	return os << v.toString();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CONSTANTS IMPLEMENTATION --------------------------------------------------------------------------------------------



constexpr vec3 POSX( 1.0f,  0.0f,  0.0f);
constexpr vec3 POSY( 0.0f,  1.0f,  0.0f);
constexpr vec3 POSZ( 0.0f,  0.0f,  1.0f);
constexpr vec3 NEGX(-1.0f,  0.0f,  0.0f);
constexpr vec3 NEGY( 0.0f, -1.0f,  0.0f);
constexpr vec3 NEGZ( 0.0f,  0.0f, -1.0f);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VEC FUNCTIONS IMPLEMENTATION ----------------------------------------------------------------------------------------



inline float mag2(const vec2 & a) {
	return a.x * a.x + a.y * a.y;
}

inline float mag2(const vec3 & a) {
	return a.x * a.x + a.y * a.y + a.z * a.z;
}

inline float mag2(const vec4 & a) {
	return a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w;
}

inline double mag2(const dvec2 & a) {
	return a.x * a.x + a.y * a.y;
}

inline double mag2(const dvec3 & a) {
	return a.x * a.x + a.y * a.y + a.z * a.z;
}

inline double mag2(const dvec4 & a) {
	return a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w;
}

inline float mag(const vec2 & v) {
	return sqrt(mag2(v));
}

inline float mag(const vec3 & v) {
	return sqrt(mag2(v));
}

inline float mag(const vec4 & v) {
	return sqrt(mag2(v));
}

inline double mag(const dvec2 & v) {
	return sqrt(mag2(v));
}

inline double mag(const dvec3 & v) {
	return sqrt(mag2(v));
}

inline double mag(const dvec4 & v) {
	return sqrt(mag2(v));
}

inline vec2 norm(const vec2 & a) {
	float m = mag(a);
	if (abs(m) < std::numeric_limits<float>::min()) {
		return vec2();
	}
	return a / m;
}

inline vec3 norm(const vec3 & a) {
	float m = mag(a);
	if (abs(m) < std::numeric_limits<float>::min()) {
		return vec3();
	}
	return a / m;
}

inline vec4 norm(const vec4 & a) {
	float m = mag(a);
	if (abs(m) < std::numeric_limits<float>::min()) {
		return vec4();
	}
	return a / m;
}

inline dvec2 norm(const dvec2 & a) {
	double m = mag(a);
	if (abs(m) < std::numeric_limits<double>::min()) {
		return dvec2();
	}
	return a / m;
}

inline dvec3 norm(const dvec3 & a) {
	double m = mag(a);
	if (abs(m) < std::numeric_limits<double>::min()) {
		return dvec3();
	}
	return a / m;
}

inline dvec4 norm(const dvec4 & a) {
	double m = mag(a);
	if (abs(m) < std::numeric_limits<double>::min()) {
		return dvec4();
	}
	return a / m;
}

inline float dot(const vec2 & a, const vec2 & b) {
	return a.x * b.x + a.y * b.y;
}

inline float dot(const vec3 & a, const vec3 & b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float dot(const vec4 & a, const vec4 & b) {
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline double dot(const dvec2 & a, const dvec2 & b) {
	return a.x * b.x + a.y * b.y;
}

inline double dot(const dvec3 & a, const dvec3 & b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline double dot(const dvec4 & a, const dvec4 & b) {
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline vec3 cross(const vec3 & a, const vec3 & b) {
	return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

inline dvec3 cross(const dvec3 & a, const dvec3 & b) {
	return dvec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

inline float angle(const vec2 & a, const vec2 & b) {
	return acos(dot(norm(a), norm(b)));
}

inline float angle(const vec3 & a, const vec3 & b) {
	return acos(dot(norm(a), norm(b)));
}

inline float angle(const vec4 & a, const vec4 & b) {
	return acos(dot(norm(a), norm(b)));
}

inline double angle(const dvec2 & a, const dvec2 & b) {
	return acos(dot(norm(a), norm(b)));
}

inline double angle(const dvec3 & a, const dvec3 & b) {
	return acos(dot(norm(a), norm(b)));
}

inline double angle(const dvec4 & a, const dvec4 & b) {
	return acos(dot(norm(a), norm(b)));
}

inline vec2 lerp(const vec2 & v1, const vec2 & v2, float t) {
	return (1.0f - t) * v1 + t * v2;
}

inline vec3 lerp(const vec3 & v1, const vec3 & v2, float t) {
	return (1.0f - t) * v1 + t * v2;
}

inline vec4 lerp(const vec4 & v1, const vec4 & v2, float t) {
	return (1.0f - t) * v1 + t * v2;
}

inline dvec2 lerp(const dvec2 & v1, const dvec2 & v2, double t) {
	return (1.0 - t) * v1 + t * v2;
}

inline dvec3 lerp(const dvec3 & v1, const dvec3 & v2, double t) {
	return (1.0 - t) * v1 + t * v2;
}

inline dvec4 lerp(const dvec4 & v1, const dvec4 & v2, double t) {
	return (1.0 - t) * v1 + t * v2;
}



};