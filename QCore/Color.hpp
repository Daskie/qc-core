#pragma once



#include "Vector.hpp"



namespace qc {



namespace color {

template <typename T, typename From> constexpr vec3<T> custom(const vec3<From> & color) { return transnorm<T>(color); }
template <typename T, typename From> constexpr vec3<T> custom(From r, From g, From b) { return custom<T>(vec3<From>(r, g, b)); }

template <typename T> constexpr vec3<T>     black = custom<T>(0.00, 0.00, 0.00);
template <typename T> constexpr vec3<T>  darkGray = custom<T>(0.25, 0.25, 0.25);
template <typename T> constexpr vec3<T>      gray = custom<T>(0.50, 0.50, 0.50);
template <typename T> constexpr vec3<T> lightGray = custom<T>(0.75, 0.75, 0.75);
template <typename T> constexpr vec3<T>     white = custom<T>(1.00, 1.00, 1.00);

template <typename T> constexpr vec3<T>       red = custom<T>(1.00, 0.00, 0.00);
template <typename T> constexpr vec3<T>    yellow = custom<T>(1.00, 1.00, 0.00);
template <typename T> constexpr vec3<T>     green = custom<T>(0.00, 1.00, 0.00);
template <typename T> constexpr vec3<T>      cyan = custom<T>(0.00, 1.00, 1.00);
template <typename T> constexpr vec3<T>      blue = custom<T>(0.00, 0.00, 1.00);
template <typename T> constexpr vec3<T>   magenta = custom<T>(1.00, 0.00, 1.00);

}



}