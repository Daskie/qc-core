#pragma once

#include <iostream>

#include "Vector.hpp"
#include "CoreFunc.hpp"

namespace qc {

//==============================================================================
// minmax
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE duo<T> minmax(const vec<T, t_n> & v);

//==============================================================================
// median
//------------------------------------------------------------------------------

template <typename T>
Q_CX_ABLE T median(const vec3<T> & v);

//==============================================================================
// Stream Output
//------------------------------------------------------------------------------

template <typename T, int t_n> std::ostream & operator<<(std::ostream & os, const vec<T, t_n> & v);

template <typename T, int t_n> std::ostream & operator<<(std::ostream & os, const span<T, t_n> & s);

//==============================================================================
// pow
//------------------------------------------------------------------------------

template <typename T, int t_n, typename = eif_floating_t<T>>
vec<T, t_n> pow(const vec<T, t_n> & v, T p);

template <typename T, int t_n, typename = eif_floating_t<T>>
vec<T, t_n> pow(const vec<T, t_n> & v, const vec<T, t_n> & p);

//==============================================================================
// exp
//------------------------------------------------------------------------------

template <typename T, int t_n, typename = eif_t<is_floating_point_v<T>>>
vec<T, t_n> exp(const vec<T, t_n> & v);

//==============================================================================
// magnitude
//------------------------------------------------------------------------------

template <typename T, int t_n, typename = eif_floating_t<T>>
T magnitude(const vec<T, t_n> & v);

template <typename T, int t_n>
T magnitude2(const vec<T, t_n> & v);

//==============================================================================
// normalize
//------------------------------------------------------------------------------

template <typename T, int t_n, typename = eif_floating_t<T>>
vec<T, t_n> normalize(const vec<T, t_n> & v);

//==============================================================================
// normalizeAssign
//------------------------------------------------------------------------------

template <typename T, int t_n, typename = eif_floating_t<T>>
vec<T, t_n> & normalizeAssign(vec<T, t_n> & v);

//==============================================================================
// dot
//------------------------------------------------------------------------------

template <typename T, int t_n>
T dot(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

//==============================================================================
// cross
//------------------------------------------------------------------------------

template <typename T>
T cross(const vec2<T> & v1, const vec2<T> & v2);

template <typename T>
vec3<T> cross(const vec3<T> & v1, const vec3<T> & v2);

//==============================================================================
// parallel
//------------------------------------------------------------------------------

template <typename T, int t_n>
bool parallel(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

//==============================================================================
// orthogonal
//------------------------------------------------------------------------------

template <typename T, int t_n>
bool orthogonal(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

//==============================================================================
// ortho
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> ortho(const vec<T, t_n> & v);

//==============================================================================
// orthogonalize
//------------------------------------------------------------------------------

template <typename T, int t_n, typename = eif_floating_t<T>>
void orthogonalize(const vec<T, t_n> & v1, vec<T, t_n> & v2);

template <typename T, typename = eif_floating_t<T>>
void orthogonalize(const vec3<T> & v1, vec3<T> & v2, vec3<T> & v3);
template <typename T, typename = eif_floating_t<T>>
void orthogonalize_n(const vec3<T> & v1, vec3<T> & v2, vec3<T> & v3);

//==============================================================================
// reflect
//------------------------------------------------------------------------------

template <typename T, int t_n, typename = eif_floating_t<T>>
vec<T, t_n> reflect(const vec<T, t_n> & v, const vec<T, t_n> & n);
template <typename T, int t_n, typename = eif_floating_t<T>>
vec<T, t_n> reflect_n(const vec<T, t_n> & v, const vec<T, t_n> & n);

//==============================================================================
// angle
//------------------------------------------------------------------------------

template <typename T, int t_n, typename = eif_floating_t<T>>
T angle(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n, typename = eif_floating_t<T>>
T angle_n(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

//==============================================================================
// sort
//------------------------------------------------------------------------------

template <typename T, int t_n>
void sort(const vec<T, t_n> & v);

//==============================================================================
// clamp
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> clamp(const vec<T, t_n> & v, T min, T max);

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> clamp(const vec<T, t_n> & v, const vec<T, t_n> & min, const vec<T, t_n> & max);

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> clamp(const vec<T, t_n> & v, const span<T, t_n> & span);
template <typename T>
Q_CX_ABLE T clamp(T v, const span1<T> & span);

//==============================================================================
// abs
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> abs(const vec<T, t_n> & v);

//==============================================================================
// zero
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE bool zero(const vec<T, t_n> & v, T e = std::numeric_limits<T>::min());

//==============================================================================
// equal
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE bool equal(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

template <typename T, int t_n, typename = eif_floating_t<T>>
Q_CX_ABLE bool equal_e(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & e = vec<T, t_n>(std::numeric_limits<T>::min()));

template <typename T, int t_n>
Q_CX_ABLE bool equal(const vec<T, t_n> & v);

//==============================================================================
// round
//------------------------------------------------------------------------------

template <int t_n>
Q_CX_ABLE vec<s64, t_n> round(const dvec<t_n> & v);

template <int t_n>
Q_CX_ABLE vec<s32, t_n> round(const fvec<t_n> & v);

template <typename T, int t_n, typename = eif_integral_t<T>>
Q_CX_ABLE vec<T, t_n> round(const vec<T, t_n> & v);

//==============================================================================
// floor
//------------------------------------------------------------------------------

template <typename T, int t_n, typename = eif_floating_t<T>>
Q_CX_ABLE vec<nat, t_n> floor(const vec<T, t_n> & v);

template <typename T, int t_n, typename = eif_integral_t<T>>
Q_CX_ABLE vec<T, t_n> floor(const vec<T, t_n> & v);

//==============================================================================
// ceil
//------------------------------------------------------------------------------

template <typename T, int t_n, typename = eif_floating_t<T>>
Q_CX_ABLE vec<nat, t_n> ceil(const vec<T, t_n> & v);

template <typename T, int t_n, typename = eif_integral_t<T>>
Q_CX_ABLE vec<T, t_n> ceil(const vec<T, t_n> & v);

//==============================================================================
// mix
//------------------------------------------------------------------------------

template <typename T, int t_n, typename = eif_floating_t<T>>
Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, T t);

template <typename T, typename = eif_floating_t<T>>
Q_CX_ABLE T mix(T v1, T v2, const vec2<T> & weights);
template <typename T, int t_n, typename = eif_floating_t<T>>
Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec2<T> & weights);

template <typename T, typename = eif_floating_t<T>>
Q_CX_ABLE T mix(T v1, T v2, T v3, const vec3<T> & weights);
template <typename T, int t_n, typename = eif_floating_t<T>>
Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & v3, const vec3<T> & weights);

template <typename T, typename = eif_floating_t<T>>
Q_CX_ABLE T mix(T v1, T v2, T v3, T v4, const vec4<T> & weights);
template <typename T, int t_n, typename = eif_floating_t<T>>
Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & v3, const vec<T, t_n> & v4, const vec4<T> & weights);

//==============================================================================
// transnorm
//------------------------------------------------------------------------------
// converts between normalized types
// works with floats, signed, and unsigned integers
//------------------------------------------------------------------------------

template <typename To, typename From, int t_n, typename = eif_t<is_arithmetic_v<To> && is_arithmetic_v<From>>>
Q_CONSTEX vec<To, t_n> transnorm(const vec<From, t_n> & v);

//==============================================================================
// intersect
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE span<T, t_n> intersect(const span<T, t_n> & s1, const span<T, t_n> & s2);

//==============================================================================
// join
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE span<T, t_n> join(const span<T, t_n> & s1, const span<T, t_n> & s2);

//==============================================================================
// mipmaps
//------------------------------------------------------------------------------

template <typename T, int t_n, typename = eif_integral_t<T>>
Q_CX_ABLE T mipmaps(const vec<T, t_n> & size);

//==============================================================================
// composite
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> composite(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

}

#include "VectorFunc.tpp"
