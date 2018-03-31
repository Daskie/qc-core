#pragma once



#include <iostream>

#include "Vector.hpp"
#include "CoreFunc.hpp"



namespace qcu {


//==============================================================================
// Stream Output
//------------------------------------------------------------------------------

template <typename T, int t_n> inline std::ostream & operator<<(std::ostream & os, const vec<T, t_n> & v);

template <typename T, int t_n> inline std::ostream & operator<<(std::ostream & os, const span<T, t_n> & s);



//==============================================================================
// pow
//------------------------------------------------------------------------------

template <typename T, int t_n, eif_floating_t<T> = 0>
inline vec<T, t_n> pow(const vec<T, t_n> & v, T p);

template <typename T, int t_n, eif_floating_t<T> = 0>
inline vec<T, t_n> pow(const vec<T, t_n> & v, const vec<T, t_n> & p);



//==============================================================================
// exp
//------------------------------------------------------------------------------

template <typename T, int t_n, eif_t<std::is_floating_point_v<T>> = 0>
inline vec<T, t_n> exp(const vec<T, t_n> & v);



//==============================================================================
// magnitude
//------------------------------------------------------------------------------

template <typename T, int t_n, eif_floating_t<T> = 0>
inline T magnitude(const vec<T, t_n> & v);

template <typename T, int t_n>
inline T magnitude2(const vec<T, t_n> & v);



//==============================================================================
// norm
//------------------------------------------------------------------------------

template <typename T, int t_n, eif_floating_t<T> = 0>
inline vec<T, t_n> norm(const vec<T, t_n> & v);



//==============================================================================
// dot
//------------------------------------------------------------------------------

template <typename T, int t_n>
inline T dot(const vec<T, t_n> & v1, const vec<T, t_n> & v2);



//==============================================================================
// cross
//------------------------------------------------------------------------------

template <typename T>
inline T cross(const vec2<T> & v1, const vec2<T> & v2);

template <typename T>
inline vec3<T> cross(const vec3<T> & v1, const vec3<T> & v2);



//==============================================================================
// parallel
//------------------------------------------------------------------------------

template <typename T, int t_n>
inline bool parallel(const vec<T, t_n> & v1, const vec<T, t_n> & v2);



//==============================================================================
// orthogonal
//------------------------------------------------------------------------------

template <typename T, int t_n>
inline bool orthogonal(const vec<T, t_n> & v1, const vec<T, t_n> & v2);



//==============================================================================
// ortho
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> ortho(const vec<T, t_n> & v);



//==============================================================================
// orthogonalize
//------------------------------------------------------------------------------

template <typename T, int t_n, eif_floating_t<T> = 0>
inline void orthogonalize(const vec<T, t_n> & v1, vec<T, t_n> & v2);

template <typename T, eif_floating_t<T> = 0>
inline void orthogonalize(const vec3<T> & v1, vec3<T> & v2, vec3<T> & v3);
template <typename T, eif_floating_t<T> = 0>
inline void orthogonalize_n(const vec3<T> & v1, vec3<T> & v2, vec3<T> & v3);



//==============================================================================
// reflect
//------------------------------------------------------------------------------

template <typename T, int t_n, eif_floating_t<T> = 0>
inline vec<T, t_n> reflect(const vec<T, t_n> & v, const vec<T, t_n> & n);
template <typename T, int t_n, eif_floating_t<T> = 0>
inline vec<T, t_n> reflect_n(const vec<T, t_n> & v, const vec<T, t_n> & n);



//==============================================================================
// angle
//------------------------------------------------------------------------------

template <typename T, int t_n, eif_floating_t<T> = 0>
inline T angle(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n, eif_floating_t<T> = 0>
inline T angle_n(const vec<T, t_n> & v1, const vec<T, t_n> & v2);



//==============================================================================
// sort
//------------------------------------------------------------------------------

template <typename T, int t_n>
inline void sort(const vec<T, t_n> & v);



//==============================================================================
// clamp
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> clamp(const vec<T, t_n> & v, const T & min, const T & max);

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> clamp(const vec<T, t_n> & v, const vec<T, t_n> & min, const vec<T, t_n> & max);

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> clamp(const vec<T, t_n> & v, const span<T, t_n> & span);



//==============================================================================
// abs
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> abs(const vec<T, t_n> & v);



//==============================================================================
// zero
//------------------------------------------------------------------------------

template <typename T, int t_n, eif_arithmetic_t<T> = 0>
Q_CX_ABLE bool zero(const vec<T, t_n> & v, T e = std::numeric_limits<T>::min());



//==============================================================================
// equal
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE bool equal(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

template <typename T, int t_n, eif_floating_t<T> = 0>
Q_CX_ABLE bool equalE(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & e = vec<T, t_n>(std::numeric_limits<T>::min()));

template <typename T, int t_n>
Q_CX_ABLE bool equal(const vec<T, t_n> & v);



//==============================================================================
// floor
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE vec<nat, t_n> floor(const vec<T, t_n> & v);



//==============================================================================
// ceil
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE vec<nat, t_n> ceil(const vec<T, t_n> & v);



//==============================================================================
// mix
//------------------------------------------------------------------------------

template <typename T, int t_n, eif_floating_t<T> = 0>
Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, T t);

template <typename T, eif_floating_t<T> = 0>
Q_CX_ABLE T mix(T v1, T v2, const vec2<T> & weights);
template <typename T, int t_n, eif_floating_t<T> = 0>
Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec2<T> & weights);

template <typename T, eif_floating_t<T> = 0>
Q_CX_ABLE T mix(T v1, T v2, T v3, const vec3<T> & weights);
template <typename T, int t_n, eif_floating_t<T> = 0>
Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & v3, const vec3<T> & weights);

template <typename T, eif_floating_t<T> = 0>
Q_CX_ABLE T mix(T v1, T v2, T v3, T v4, const vec4<T> & weights);
template <typename T, int t_n, eif_floating_t<T> = 0>
Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & v3, const vec<T, t_n> & v4, const vec4<T> & weights);



//==============================================================================
// transnorm
//------------------------------------------------------------------------------
// converts between normalized types
// works with floats, signed, and unsigned integers
//------------------------------------------------------------------------------

template <typename To, typename From, int t_n, eif_t<std::is_arithmetic_v<To> && std::is_arithmetic_v<From>> = 0>
Q_CONSTEX vec<To, t_n> transnorm(const vec<From, t_n> & v);



//==============================================================================
// intersect
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE span<T, t_n> intersect(const span<T, t_n> & s1, const span<T, t_n> & s2);



//==============================================================================
// mipmaps
//------------------------------------------------------------------------------

template <typename T, int t_n, eif_integral_t<T> = 0>
Q_CX_ABLE T mipmaps(const vec<T, t_n> & size);



//==============================================================================
// composite
//------------------------------------------------------------------------------

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> composite(const vec<T, t_n> & v1, const vec<T, t_n> & v2);



//==============================================================================================================================================================
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================================================



template <typename T, int t_n>
inline std::ostream & operator<<(std::ostream & os, const vec<T, t_n> & v) {
    os << "[";
    if constexpr (t_n >= 1) os << " " << v.x << " ";
    if constexpr (t_n >= 2) os << v.y << " ";
    if constexpr (t_n >= 3) os << v.z << " ";
    if constexpr (t_n >= 4) os << v.w << " ";
    os << "]";
    return os;
}

template <typename T, int t_n>
inline std::ostream & operator<<(std::ostream & os, const span<T, t_n> & s) {
    return os << "[" << s.min << s.max << "]";
}

template <typename T, int t_n, eif_floating_t<T>>
inline vec<T, t_n> pow(const vec<T, t_n> & v, T p) {
    if constexpr (t_n == 1) return vec1<T>(std::pow(v.x, p));
    if constexpr (t_n == 2) return vec2<T>(std::pow(v.x, p), std::pow(v.y, p));
    if constexpr (t_n == 3) return vec3<T>(std::pow(v.x, p), std::pow(v.y, p), std::pow(v.z, p));
    if constexpr (t_n == 4) return vec4<T>(std::pow(v.x, p), std::pow(v.y, p), std::pow(v.z, p), std::pow(v.w, p));
}

template <typename T, int t_n, eif_floating_t<T>>
inline vec<T, t_n> pow(const vec<T, t_n> & v, const vec<T, t_n> & p) {
    if constexpr (t_n == 1) return vec1<T>(std::pow(v.x, p.x));
    if constexpr (t_n == 2) return vec2<T>(std::pow(v.x, p.x), std::pow(v.y, p.y));
    if constexpr (t_n == 3) return vec3<T>(std::pow(v.x, p.x), std::pow(v.y, p.y), std::pow(v.z, p.z));
    if constexpr (t_n == 4) return vec4<T>(std::pow(v.x, p.x), std::pow(v.y, p.y), std::pow(v.z, p.z), std::pow(v.w, p.w));
}

template <typename T, int t_n, eif_floating_t<T>>
inline vec<T, t_n> exp(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return vec1<T>(std::exp(v.x));
    if constexpr (t_n == 2) return vec2<T>(std::exp(v.x), std::exp(v.y));
    if constexpr (t_n == 3) return vec3<T>(std::exp(v.x), std::exp(v.y), std::exp(v.z));
    if constexpr (t_n == 4) return vec4<T>(std::exp(v.x), std::exp(v.y), std::exp(v.z), std::exp(v.w));
}

template <typename T, int t_n, eif_floating_t<T>>
inline T magnitude(const vec<T, t_n> & v) {
    return T(std::sqrt(magnitude2(v)));
}

template <typename T, int t_n>
inline T magnitude2(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return v.x * v.x;
    if constexpr (t_n == 2) return v.x * v.x + v.y * v.y;
    if constexpr (t_n == 3) return v.x * v.x + v.y * v.y + v.z * v.z;
    if constexpr (t_n == 4) return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}

template <typename T, int t_n, eif_floating_t<T>>
inline vec<T, t_n> norm(const vec<T, t_n> & v) {
    T m2(magnitude2(v));
    if (zero(m2)) {
        return vec<T, t_n>();
    }
    return v * (T(1.0) / std::sqrt(m2));
}

template <typename T, int t_n>
inline T dot(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return v1.x * v2.x;
    if constexpr (t_n == 2) return v1.x * v2.x + v1.y * v2.y;
    if constexpr (t_n == 3) return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    if constexpr (t_n == 4) return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

template <typename T>
inline T cross(const vec2<T> & v1, const vec2<T> & v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

template <typename T>
inline vec3<T> cross(const vec3<T> & v1, const vec3<T> & v2) {
    return vec3<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

template <typename T, int t_n>
inline bool parallel(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    T d(dot(v1, v2));
    return equal(d * d, magnitude2(v1) * magnitude2(v2));
}

template <typename T, int t_n>
inline bool orthogonal(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    return zero(dot(v1, v2));
}

template <typename T>
Q_CX_ABLE vec2<T> ortho(const vec2<T> & v) {
    return vec2<T>(-v.y, v.x);
}

template <typename T>
inline vec3<T> ortho(const vec3<T> & v) {    
    if (abs(v.x) < abs(v.y)) {
        if (abs(v.x) <= abs(v.z)) {   // x or z is smallest
            return vec3<T>(0, -v.z, v.y);       // rotate around x
        }
        else {                                  // z is smallest
            return vec3<T>(-v.y, v.x, 0);       // rotate around z
        }
    }
    else {
        if (abs(v.y) < abs(v.z)) {    // y or x is smallest
            return vec3<T>(v.z, 0, -v.x);       // rotate around y
        }
        else {                                  // z or y is smallest
            return vec3<T>(-v.y, v.x, 0);       // rotate around z
        }
    }
}

template <typename T, int t_n, eif_floating_t<T>>
inline void orthogonalize(const vec<T, t_n> & v1, vec<T, t_n> & v2) {
    if constexpr (t_n == 1) {
        v2 = vec1<T>();
    }
    if constexpr (t_n > 1) {
        v2 = norm(v2 - dot(v1, v2) * v1);
    }
}

// in order of priority
template <typename T, eif_floating_t<T>>
inline void orthogonalize(const vec3<T> & v1, vec3<T> & v2, vec3<T> & v3) {
    orthogonalize_n(v1, v2, v3);
    v2 = norm(v2);
    v3 = norm(v3);
}

// in order of priority
template <typename T, eif_floating_t<T>>
inline void orthogonalize_n(const vec3<T> & v1, vec3<T> & v2, vec3<T> & v3) {
    orthogonalize(v1, v2);
    v3 = cross(v2, v1);
}

template <typename T, int t_n, eif_floating_t<T>>
inline vec<T, t_n> reflect(const vec<T, t_n> & v, const vec<T, t_n> & n) {
    return reflect_n(v, norm(n));
}

template <typename T, int t_n, eif_floating_t<T>>
inline vec<T, t_n> reflect_n(const vec<T, t_n> & v, const vec<T, t_n> & n) {
    return (T(2.0) * dot(v, n)) * n - v;
}

template <typename T, int t_n, eif_floating_t<T>>
inline T angle(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    return angle_n(norm(v1), norm(v2));
}
template <typename T, int t_n, eif_floating_t<T>>
inline T angle_n(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    return T(std::acos(dot(v1, v2)));
}

template <typename T, int t_n>
inline void sort(vec<T, t_n> & v) {
    if constexpr (t_n >= 2) {
        if (v.x > v.y) std::swap(v.x, v.y);
    }
    if constexpr (t_n >= 3) {
        if (v.y > v.z) std::swap(v.y, v.z);
        if (v.x > v.y) std::swap(v.x, v.y);
    }
    if constexpr (t_n >= 4) {
        if (v.z > v.w) std::swap(v.z, v.w);
        if (v.y > v.z) std::swap(v.y, v.z);
        if (v.x > v.y) std::swap(v.x, v.y);
    }
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> clamp(const vec<T, t_n> & v, const T & min, const T & max) {
    if constexpr (t_n == 1) return vec1<T>(clamp(v.x, min, max));
    if constexpr (t_n == 2) return vec2<T>(clamp(v.x, min, max), clamp(v.y, min, max));
    if constexpr (t_n == 3) return vec3<T>(clamp(v.x, min, max), clamp(v.y, min, max), clamp(v.z, min, max));
    if constexpr (t_n == 4) return vec4<T>(clamp(v.x, min, max), clamp(v.y, min, max), clamp(v.z, min, max), clamp(v.w, min, max));
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> clamp(const vec<T, t_n> & v, const vec<T, t_n> & min, const vec<T, t_n> & max) {
    if constexpr (t_n == 1) return vec1<T>(clamp(v.x, min.x, max.x));
    if constexpr (t_n == 2) return vec2<T>(clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y));
    if constexpr (t_n == 3) return vec3<T>(clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y), clamp(v.z, min.z, max.z));
    if constexpr (t_n == 4) return vec4<T>(clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y), clamp(v.z, min.z, max.z), clamp(v.w, min.w, max.w));
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> clamp(const vec<T, t_n> & v, const span<T, t_n> & span) {
    return clamp(v, span.min, span.max);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> abs(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return vec1<T>(abs(v.x));
    if constexpr (t_n == 2) return vec2<T>(abs(v.x), abs(v.y));
    if constexpr (t_n == 3) return vec3<T>(abs(v.x), abs(v.y), abs(v.z));
    if constexpr (t_n == 4) return vec4<T>(abs(v.x), abs(v.y), abs(v.z), abs(v.w));
}

template <typename T, int t_n, eif_arithmetic_t<T>>
Q_CX_ABLE bool zero(const vec<T, t_n> & v, T e) {
    if constexpr (t_n == 1) return zero(v.x, e);
    if constexpr (t_n == 2) return zero(v.x, e) && zero(v.y, e);
    if constexpr (t_n == 3) return zero(v.x, e) && zero(v.y, e) && zero(v.z, e);
    if constexpr (t_n == 4) return zero(v.x, e) && zero(v.y, e) && zero(v.z, e) && zero(v.w, e);
}

template <typename T, int t_n>
Q_CX_ABLE bool equal(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return equal(v1.x, v2.x);
    if constexpr (t_n == 2) return equal(v1.x, v2.x) && equal(v1.y, v2.y);
    if constexpr (t_n == 3) return equal(v1.x, v2.x) && equal(v1.y, v2.y) && equal(v1.z, v2.z);
    if constexpr (t_n == 4) return equal(v1.x, v2.x) && equal(v1.y, v2.y) && equal(v1.z, v2.z) && equal(v1.w, v2.w);
}

template <typename T, int t_n, eif_floating_t<T>>
Q_CX_ABLE bool equalE(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & e) {
    if constexpr (t_n == 1) return equalE(v1.x, v2.x, e.x);
    if constexpr (t_n == 2) return equalE(v1.x, v2.x, e.x) && equalE(v1.y, v2.y, e.y);
    if constexpr (t_n == 3) return equalE(v1.x, v2.x, e.x) && equalE(v1.y, v2.y, e.y) && equalE(v1.z, v2.z, e.z);
    if constexpr (t_n == 4) return equalE(v1.x, v2.x, e.x) && equalE(v1.y, v2.y, e.y) && equalE(v1.z, v2.z, e.z) && equalE(v1.w, v2.w, e.w);
}

template <typename T, int t_n>
Q_CX_ABLE bool equal(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return true;
    if constexpr (t_n == 2) return v.x == v.y;
    if constexpr (t_n == 3) return v.x == v.y && v.x == v.z;
    if constexpr (t_n == 4) return v.x == v.y && v.x == v.z && v.x == v.w;
}

template <typename T, int t_n>
Q_CX_ABLE vec<nat, t_n> floor(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return vec1<nat>(floor(v.x));
    if constexpr (t_n == 2) return vec2<nat>(floor(v.x), floor(v.y));
    if constexpr (t_n == 3) return vec3<nat>(floor(v.x), floor(v.y), floor(v.z));
    if constexpr (t_n == 4) return vec4<nat>(floor(v.x), floor(v.y), floor(v.z), floor(v.w));
}

template <typename T, int t_n>
Q_CX_ABLE vec<nat, t_n> ceil(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return vec1<nat>(ceil(v.x));
    if constexpr (t_n == 2) return vec2<nat>(ceil(v.x), ceil(v.y));
    if constexpr (t_n == 3) return vec3<nat>(ceil(v.x), ceil(v.y), ceil(v.z));
    if constexpr (t_n == 4) return vec4<nat>(ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w));
}

template <typename T, int t_n, eif_floating_t<T>>
Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, T t) {
    return (T(1.0) - t) * v1 + t * v2;
}


template <typename T, eif_floating_t<T>>
Q_CX_ABLE T mix(T v1, T v2, const vec2<T> & weights) {
    return weights.x * v1 + weights.y * v2;
}

template <typename T, int t_n, eif_floating_t<T>>
Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec2<T> & weights) {
    return weights.x * v1 + weights.y * v2;
}

template <typename T, eif_floating_t<T>>
Q_CX_ABLE T mix(T v1, T v2, T v3, const vec3<T> & weights) {
    return weights.x * v1 + weights.y * v2 + weights.z * v3;
}

template <typename T, int t_n, eif_floating_t<T>>
Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & v3, const vec3<T> & weights) {
    return weights.x * v1 + weights.y * v2 + weights.z * v3;
}

template <typename T, eif_floating_t<T>>
Q_CX_ABLE T mix(T v1, T v2, T v3, T v4, const vec4<T> & weights) {
    return weights.x * v1 + weights.y * v2 + weights.z * v3 + weights.w * v4;
}

template <typename T, int t_n, eif_floating_t<T>>
Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & v3, const vec<T, t_n> & v4, const vec4<T> & weights) {
    return weights.x * v1 + weights.y * v2 + weights.z * v3 + weights.w * v4;
}

template <typename To, typename From, int t_n, eif_t<std::is_arithmetic_v<To> && std::is_arithmetic_v<From>>>
Q_CONSTEX vec<To, t_n> transnorm(const vec<From, t_n> & v) {
    if constexpr (t_n == 1) return vec1<To>(transnorm<To>(v.x));
    if constexpr (t_n == 2) return vec2<To>(transnorm<To>(v.x), transnorm<To>(v.y));
    if constexpr (t_n == 3) return vec3<To>(transnorm<To>(v.x), transnorm<To>(v.y), transnorm<To>(v.z));
    if constexpr (t_n == 4) return vec4<To>(transnorm<To>(v.x), transnorm<To>(v.y), transnorm<To>(v.z), transnorm<To>(v.w));
}

template <typename T, int t_n>
Q_CX_ABLE span<T, t_n> toSpan(const bound<T, t_n> & b) {
    return span<T, t_n>(b.min, b.min + b.max);
}

template <typename T, int t_n>
Q_CX_ABLE bound<T, t_n> toBound(const span<T, t_n> & s) {
    return bound<T, t_n>(s.min, s.max - s.min);
}

template <typename T, int t_n>
Q_CX_ABLE span<T, t_n> intersect(const span<T, t_n> & s1, const span<T, t_n> & s2) {
    if constexpr (t_n == 1) return span1<T>(
        vec1<T>(max(s1.min.x, s2.min.x)),
        vec1<T>(min(s1.max.x, s2.max.x))
    );
    if constexpr (t_n == 2) return span2<T>(
        vec2<T>(max(s1.min.x, s2.min.x), max(s1.min.y, s2.min.y)),
        vec2<T>(min(s1.max.x, s2.max.x), min(s1.max.y, s2.max.y))
    );
    if constexpr (t_n == 3) return span3<T>(
        vec3<T>(max(s1.min.x, s2.min.x), max(s1.min.y, s2.min.y), max(s1.min.z, s2.min.z)),
        vec3<T>(min(s1.max.x, s2.max.x), min(s1.max.y, s2.max.y), min(s1.max.z, s2.max.z))
    );
    if constexpr (t_n == 4) return span4<T>(
        vec4<T>(max(s1.min.x, s2.min.x), max(s1.min.y, s2.min.y), max(s1.min.z, s2.min.z), max(s1.min.w, s2.min.w)),
        vec4<T>(min(s1.max.x, s2.max.x), min(s1.max.y, s2.max.y), min(s1.max.z, s2.max.z), min(s1.max.w, s2.max.w))
    );
}

template <typename T, int t_n, eif_integral_t<T>>
Q_CX_ABLE T mipmaps(const vec<T, t_n> & size) {
    return mipmaps(max(size));
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> composite(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {    
    vec<T, t_n> v;

    if constexpr (t_n >= 1) {
        if      (v1.x > T(0) && v2.x > T(0)) v.x = qcu::max(v1.x, v2.x);
        else if (v1.x < T(0) && v2.x < T(0)) v.x = qcu::min(v1.x, v2.x);
        else                                 v.x = v1.x + v2.x;
    }
    if constexpr (t_n >= 2) {
        if      (v1.y > T(0) && v2.y > T(0)) v.y = qcu::max(v1.y, v2.y);
        else if (v1.y < T(0) && v2.y < T(0)) v.y = qcu::min(v1.y, v2.y);
        else                                 v.y = v1.y + v2.y;
    }
    if constexpr (t_n >= 3) {
        if      (v1.z > T(0) && v2.z > T(0)) v.z = qcu::max(v1.z, v2.z);
        else if (v1.z < T(0) && v2.z < T(0)) v.z = qcu::min(v1.z, v2.z);
        else                                 v.z = v1.z + v2.z;
    }
    if constexpr (t_n >= 4) {
        if      (v1.w > T(0) && v2.w > T(0)) v.w = qcu::max(v1.w, v2.w);
        else if (v1.w < T(0) && v2.w < T(0)) v.w = qcu::min(v1.w, v2.w);
        else                                 v.w = v1.w + v2.w;
    }

    return v;
}



}