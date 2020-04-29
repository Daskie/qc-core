#pragma once

#include <iostream>

#include "Vector.hpp"
#include "CoreFunc.hpp"

namespace qc {

    //==============================================================================
    // minmax
    //------------------------------------------------------------------------------

    template <typename T, int t_n> Q_CX_ABLE duo<T> minmax(const vec<T, t_n> & v);

    //==============================================================================
    // median
    //------------------------------------------------------------------------------

    template <typename T> Q_CX_ABLE T median(const vec3<T> & v);

    //==============================================================================
    // Stream Output
    //------------------------------------------------------------------------------

    template <typename T, int t_n> std::ostream & operator<<(std::ostream & os, const vec<T, t_n> & v);
    template <typename T, int t_n> std::ostream & operator<<(std::ostream & os, const span<T, t_n> & s);

    //==============================================================================
    // pow
    //------------------------------------------------------------------------------

    template <typename T, int t_n, typename = eif_floating_t<T>> vec<T, t_n> pow(const vec<T, t_n> & v, T p);
    template <typename T, int t_n, typename = eif_floating_t<T>> vec<T, t_n> pow(const vec<T, t_n> & v, const vec<T, t_n> & p);

    //==============================================================================
    // exp
    //------------------------------------------------------------------------------

    template <typename T, int t_n, typename = eif_floating_t<T>> vec<T, t_n> exp(const vec<T, t_n> & v);

    //==============================================================================
    // magnitude
    //------------------------------------------------------------------------------

    template <typename T, int t_n, typename = eif_floating_t<T>> T magnitude(const vec<T, t_n> & v);

    template <typename T, int t_n> T magnitude2(const vec<T, t_n> & v);

    //==============================================================================
    // normalize
    //------------------------------------------------------------------------------

    template <typename T, int t_n, typename = eif_floating_t<T>> vec<T, t_n> normalize(const vec<T, t_n> & v);

    //==============================================================================
    // normalizeAssign
    //------------------------------------------------------------------------------

    template <typename T, int t_n, typename = eif_floating_t<T>> vec<T, t_n> & normalizeAssign(vec<T, t_n> & v);

    //==============================================================================
    // dot
    //------------------------------------------------------------------------------

    template <typename T, int t_n> T dot(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

    //==============================================================================
    // cross
    //------------------------------------------------------------------------------

    template <typename T> T cross(const vec2<T> & v1, const vec2<T> & v2);
    template <typename T> vec3<T> cross(const vec3<T> & v1, const vec3<T> & v2);

    //==============================================================================
    // parallel
    //------------------------------------------------------------------------------

    template <typename T, int t_n> bool parallel(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

    //==============================================================================
    // orthogonal
    //------------------------------------------------------------------------------

    template <typename T, int t_n> bool orthogonal(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

    //==============================================================================
    // ortho
    //------------------------------------------------------------------------------

    template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> ortho(const vec<T, t_n> & v);

    //==============================================================================
    // orthogonalize
    //------------------------------------------------------------------------------

    template <typename T, int t_n, typename = eif_floating_t<T>> void orthogonalize(const vec<T, t_n> & v1, vec<T, t_n> & v2);
    template <typename T, typename = eif_floating_t<T>> void orthogonalize(const vec3<T> & v1, vec3<T> & v2, vec3<T> & v3);
    template <typename T, typename = eif_floating_t<T>> void orthogonalize_n(const vec3<T> & v1, vec3<T> & v2, vec3<T> & v3);

    //==============================================================================
    // reflect
    //------------------------------------------------------------------------------

    template <typename T, int t_n, typename = eif_floating_t<T>> vec<T, t_n> reflect(const vec<T, t_n> & v, const vec<T, t_n> & n);
    template <typename T, int t_n, typename = eif_floating_t<T>> vec<T, t_n> reflect_n(const vec<T, t_n> & v, const vec<T, t_n> & n);

    //==============================================================================
    // angle
    //------------------------------------------------------------------------------

    template <typename T, int t_n, typename = eif_floating_t<T>> T angle(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
    template <typename T, int t_n, typename = eif_floating_t<T>> T angle_n(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

    //==============================================================================
    // sort
    //------------------------------------------------------------------------------

    template <typename T, int t_n> void sort(const vec<T, t_n> & v);

    //==============================================================================
    // clamp
    //------------------------------------------------------------------------------

    template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> clamp(const vec<T, t_n> & v, T min, T max);
    template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> clamp(const vec<T, t_n> & v, const vec<T, t_n> & min, const vec<T, t_n> & max);
    template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> clamp(const vec<T, t_n> & v, const span<T, t_n> & span);
    template <typename T> Q_CX_ABLE T clamp(T v, const span1<T> & span);

    //==============================================================================
    // abs
    //------------------------------------------------------------------------------

    template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> abs(const vec<T, t_n> & v);

    //==============================================================================
    // zero
    //------------------------------------------------------------------------------

    template <typename T, int t_n> Q_CX_ABLE bool zero(const vec<T, t_n> & v, T e = std::numeric_limits<T>::epsilon());

    //==============================================================================
    // equal
    //------------------------------------------------------------------------------

    template <typename T, int t_n> Q_CX_ABLE bool equal(const vec<T, t_n> & v);

    template <typename T, int t_n, typename = eif_floating_t<T>> Q_CX_ABLE bool equal_e(const vec<T, t_n> & v1, const vec<T, t_n> & v2, T e = std::numeric_limits<T>::epsilon());
    template <typename T, int t_n, typename = eif_floating_t<T>> Q_CX_ABLE bool equal_e(const vec<T, t_n> & v, T e = std::numeric_limits<T>::epsilon());

    //==============================================================================
    // round
    //------------------------------------------------------------------------------

    template <int t_n> Q_CX_ABLE lvec<t_n> round(const dvec<t_n> & v);
    template <int t_n> Q_CX_ABLE ivec<t_n> round(const fvec<t_n> & v);
    template <typename T, int t_n, typename = eif_integral_t<T>> Q_CX_ABLE vec<T, t_n> round(const vec<T, t_n> & v);
    template <int t_n> Q_CX_ABLE lspan<t_n> round(const dspan<t_n> & v);
    template <int t_n> Q_CX_ABLE ispan<t_n> round(const fspan<t_n> & v);
    template <typename T, int t_n, typename = eif_integral_t<T>> Q_CX_ABLE span<T, t_n> round(const span<T, t_n> & v);

    //==============================================================================
    // floor
    //------------------------------------------------------------------------------

    template <typename T, int t_n, typename = eif_floating_t<T>> Q_CX_ABLE vec<nat, t_n> floor(const vec<T, t_n> & v);
    template <typename T, int t_n, typename = eif_integral_t<T>> Q_CX_ABLE vec<T, t_n> floor(const vec<T, t_n> & v);

    //==============================================================================
    // ceil
    //------------------------------------------------------------------------------

    template <typename T, int t_n, typename = eif_floating_t<T>> Q_CX_ABLE vec<nat, t_n> ceil(const vec<T, t_n> & v);
    template <typename T, int t_n, typename = eif_integral_t<T>> Q_CX_ABLE vec<T, t_n> ceil(const vec<T, t_n> & v);

    //==============================================================================
    // mix
    //------------------------------------------------------------------------------

    template <typename T, int t_n, typename = eif_floating_t<T>> Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, T t);
    template <typename T, int t_n, typename = eif_floating_t<T>> Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec2<T> & weights);
    template <typename T, int t_n, typename = eif_floating_t<T>> Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & v3, const vec3<T> & weights);
    template <typename T, int t_n, typename = eif_floating_t<T>> Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & v3, const vec<T, t_n> & v4, const vec4<T> & weights);
    template <typename T, typename = eif_floating_t<T>> Q_CX_ABLE T mix(T v1, T v2, const vec2<T> & weights);
    template <typename T, typename = eif_floating_t<T>> Q_CX_ABLE T mix(T v1, T v2, T v3, const vec3<T> & weights);
    template <typename T, typename = eif_floating_t<T>> Q_CX_ABLE T mix(T v1, T v2, T v3, T v4, const vec4<T> & weights);

    //==============================================================================
    // smoothstep
    //------------------------------------------------------------------------------

    template <typename T, int t_n, typename = eif_floating_t<T>> Q_CX_ABLE vec<T, t_n> smoothstep(const vec<T, t_n> & v1, const vec<T, t_n> & v2, T t);

    //==============================================================================
    // transnorm
    //------------------------------------------------------------------------------
    // converts between normalized types
    // works with floats, signed, and unsigned integers
    //------------------------------------------------------------------------------

    template <typename To, typename From, int t_n, typename = eif_arithmetic_t<To, From>> Q_CONSTEX vec<To, t_n> transnorm(const vec<From, t_n> & v);

    //==============================================================================
    // intersect
    //------------------------------------------------------------------------------

    template <typename T, int t_n> Q_CX_ABLE span<T, t_n> intersect(const span<T, t_n> & v1, const span<T, t_n> & v2);

    //==============================================================================
    // join
    //------------------------------------------------------------------------------

    template <typename T, int t_n> Q_CX_ABLE span<T, t_n> join(const span<T, t_n> & v1, const span<T, t_n> & v2);

    //==============================================================================
    // join
    //------------------------------------------------------------------------------

    template <typename T, int t_n> span<T, t_n> & joinify(span<T, t_n> & v1, const span<T, t_n> & v2);

    //==============================================================================
    // mipmaps
    //------------------------------------------------------------------------------

    template <typename T, int t_n, typename = eif_integral_t<T>> Q_CX_ABLE T mipmaps(const vec<T, t_n> & size);

    //==============================================================================
    // composite
    //------------------------------------------------------------------------------

    template <typename T, int t_n> Q_CX_ABLE vec<T, t_n> composite(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

}

// INLINE IMPLEMENTATION ///////////////////////////////////////////////////////////////////////////////////////////////

namespace qc {

    template <typename T, int t_n>
    Q_CX_ABLE duo<T> minmax(const vec<T, t_n> & v) {
        if constexpr (t_n == 2) return minmax(v.x, v.y);
        if constexpr (t_n == 3) return minmax(v.x, v.y, v.z);
        if constexpr (t_n == 4) return minmax(v.x, v.y, v.z, v.w);
    }

    template <typename T>
    Q_CX_ABLE T median(const vec3<T> & v) {
        return median(v.x, v.y, v.z);
    }

    template <typename T, int t_n>
    inline std::ostream & operator<<(std::ostream & os, const vec<T, t_n> & v) {
        os << "[";
        if constexpr (t_n >= 1) os << v.x << " ";
        if constexpr (t_n >= 2) os << " " << v.y;
        if constexpr (t_n >= 3) os << " " << v.z;
        if constexpr (t_n >= 4) os << " " << v.w;
        os << "]";
        return os;
    }

    template <typename T, int t_n>
    inline std::ostream & operator<<(std::ostream & os, const span<T, t_n> & s) {
        return os << "[" << s.min << s.max << "]";
    }

    template <typename T, int t_n, typename>
    inline vec<T, t_n> pow(const vec<T, t_n> & v, T p) {
        if constexpr (t_n == 2) return {std::pow(v.x, p), std::pow(v.y, p)};
        if constexpr (t_n == 3) return {std::pow(v.x, p), std::pow(v.y, p), std::pow(v.z, p)};
        if constexpr (t_n == 4) return {std::pow(v.x, p), std::pow(v.y, p), std::pow(v.z, p), std::pow(v.w, p)};
    }

    template <typename T, int t_n, typename>
    inline vec<T, t_n> pow(const vec<T, t_n> & v, const vec<T, t_n> & p) {
        if constexpr (t_n == 2) return {std::pow(v.x, p.x), std::pow(v.y, p.y)};
        if constexpr (t_n == 3) return {std::pow(v.x, p.x), std::pow(v.y, p.y), std::pow(v.z, p.z)};
        if constexpr (t_n == 4) return {std::pow(v.x, p.x), std::pow(v.y, p.y), std::pow(v.z, p.z), std::pow(v.w, p.w)};
    }

    template <typename T, int t_n, typename>
    inline vec<T, t_n> exp(const vec<T, t_n> & v) {
        if constexpr (t_n == 2) return {std::exp(v.x), std::exp(v.y)};
        if constexpr (t_n == 3) return {std::exp(v.x), std::exp(v.y), std::exp(v.z)};
        if constexpr (t_n == 4) return {std::exp(v.x), std::exp(v.y), std::exp(v.z), std::exp(v.w)};
    }

    template <typename T, int t_n, typename>
    inline T magnitude(const vec<T, t_n> & v) {
        return T(std::sqrt(magnitude2(v)));
    }

    template <typename T, int t_n>
    inline T magnitude2(const vec<T, t_n> & v) {
        if constexpr (t_n == 2) return v.x * v.x + v.y * v.y;
        if constexpr (t_n == 3) return v.x * v.x + v.y * v.y + v.z * v.z;
        if constexpr (t_n == 4) return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
    }

    template <typename T, int t_n, typename>
    inline vec<T, t_n> normalize(const vec<T, t_n> & v) {
        T m2(magnitude2(v));
        if (zero(m2)) {
            return {};
        }
        return v / std::sqrt(m2);
    }

    template <typename T, int t_n, typename>
    inline vec<T, t_n> & normalizeAssign(vec<T, t_n> & v) {
        T m2(magnitude2(v));
        if (zero(m2)) {
            return v;
        }
        return v /= std::sqrt(m2);
    }

    template <typename T, int t_n>
    inline T dot(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
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
        return {T(v1.y * v2.z - v1.z * v2.y), T(v1.z * v2.x - v1.x * v2.z), T(v1.x * v2.y - v1.y * v2.x)};
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

    template <typename T, int t_n>
    Q_CX_ABLE vec<T, t_n> ortho(const vec<T, t_n> & v) {
        if constexpr (t_n == 2) {
            return {-v.y, v.x};
        }
        else if constexpr (t_n  == 3) {
            if (abs(v.x) < abs(v.y)) {
                if (abs(v.x) <= abs(v.z)) { // x or z is smallest
                    return {T(0), -v.z, v.y}; // rotate around x
                }
                else { // z is smallest
                    return {-v.y, v.x, T(0)}; // rotate around z
                }
            }
            else {
                if (abs(v.y) < abs(v.z)) { // y or x is smallest
                    return {v.z, T(0), -v.x}; // rotate around y
                }
                else { // z or y is smallest
                    return {-v.y, v.x, T(0)}; // rotate around z
                }
            }
        }
        else {
            static_assert(false);
        }
    }

    template <typename T, int t_n, typename>
    inline void orthogonalize(const vec<T, t_n> & v1, vec<T, t_n> & v2) {
        v2 = normalize(v2 - dot(v1, v2) * v1);
    }

    // in order of priority
    template <typename T, typename>
    inline void orthogonalize(const vec3<T> & v1, vec3<T> & v2, vec3<T> & v3) {
        orthogonalize_n(v1, v2, v3);
        v2 = normalize(v2);
        v3 = normalize(v3);
    }

    // in order of priority
    template <typename T, typename>
    inline void orthogonalize_n(const vec3<T> & v1, vec3<T> & v2, vec3<T> & v3) {
        orthogonalize(v1, v2);
        v3 = cross(v2, v1);
    }

    template <typename T, int t_n, typename>
    inline vec<T, t_n> reflect(const vec<T, t_n> & v, const vec<T, t_n> & n) {
        return reflect_n(v, normalize(n));
    }

    template <typename T, int t_n, typename>
    inline vec<T, t_n> reflect_n(const vec<T, t_n> & v, const vec<T, t_n> & n) {
        return (T(2.0) * dot(v, n)) * n - v;
    }

    template <typename T, int t_n, typename>
    inline T angle(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
        return angle_n(normalize(v1), normalize(v2));
    }
    template <typename T, int t_n, typename>
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
    Q_CX_ABLE vec<T, t_n> clamp(const vec<T, t_n> & v, T min, T max) {
        if constexpr (t_n == 2) return {clamp(v.x, min, max), clamp(v.y, min, max)};
        if constexpr (t_n == 3) return {clamp(v.x, min, max), clamp(v.y, min, max), clamp(v.z, min, max)};
        if constexpr (t_n == 4) return {clamp(v.x, min, max), clamp(v.y, min, max), clamp(v.z, min, max), clamp(v.w, min, max)};
    }

    template <typename T, int t_n>
    Q_CX_ABLE vec<T, t_n> clamp(const vec<T, t_n> & v, const vec<T, t_n> & min, const vec<T, t_n> & max) {
        if constexpr (t_n == 2) return {clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y)};
        if constexpr (t_n == 3) return {clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y), clamp(v.z, min.z, max.z)};
        if constexpr (t_n == 4) return {clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y), clamp(v.z, min.z, max.z), clamp(v.w, min.w, max.w)};
    }

    template <typename T, int t_n>
    Q_CX_ABLE vec<T, t_n> clamp(const vec<T, t_n> & v, const span<T, t_n> & span) {
        return clamp(v, span.min, span.max);
    }

    template <typename T>
    Q_CX_ABLE T clamp(T v, const span1<T> & span) {
        return clamp(v, span.min, span.max);
    }

    template <typename T, int t_n>
    Q_CX_ABLE vec<T, t_n> abs(const vec<T, t_n> & v) {
        if constexpr (t_n == 2) return {abs(v.x), abs(v.y)};
        if constexpr (t_n == 3) return {abs(v.x), abs(v.y), abs(v.z)};
        if constexpr (t_n == 4) return {abs(v.x), abs(v.y), abs(v.z), abs(v.w)};
    }

    template <typename T, int t_n>
    Q_CX_ABLE bool zero(const vec<T, t_n> & v, T e) {
        if constexpr (t_n == 2) return zero(v.x, e) && zero(v.y, e);
        if constexpr (t_n == 3) return zero(v.x, e) && zero(v.y, e) && zero(v.z, e);
        if constexpr (t_n == 4) return zero(v.x, e) && zero(v.y, e) && zero(v.z, e) && zero(v.w, e);
    }

    template <typename T, int t_n>
    Q_CX_ABLE bool equal(const vec<T, t_n> & v) {
        if constexpr (t_n == 2) return v.x == v.y;
        if constexpr (t_n == 3) return v.x == v.y && v.x == v.z;
        if constexpr (t_n == 4) return v.x == v.y && v.x == v.z && v.x == v.w;
    }

    template <typename T, int t_n, typename>
    Q_CX_ABLE bool equal_e(const vec<T, t_n> & v1, const vec<T, t_n> & v2, T e) {
        return zero(v1 - v2, e);
    }

    template <typename T, int t_n, typename>
    Q_CX_ABLE bool equal_e(const vec<T, t_n> & v, T e) {
        return zero(v - v.x, e);
    }

    template <int t_n>
    Q_CX_ABLE lvec<t_n> round(const dvec<t_n> & v) {
        if constexpr (t_n == 2) return {round(v.x), round(v.y)};
        if constexpr (t_n == 3) return {round(v.x), round(v.y), round(v.z)};
        if constexpr (t_n == 4) return {round(v.x), round(v.y), round(v.z), round(v.w)};
    }

    template <int t_n>
    Q_CX_ABLE ivec<t_n> round(const fvec<t_n> & v) {
        if constexpr (t_n == 2) return {round(v.x), round(v.y)};
        if constexpr (t_n == 3) return {round(v.x), round(v.y), round(v.z)};
        if constexpr (t_n == 4) return {round(v.x), round(v.y), round(v.z), round(v.w)};
    }

    template <typename T, int t_n, typename>
    Q_CX_ABLE vec<T, t_n> round(const vec<T, t_n> & v) {
        return v;
    }

    template <int t_n>
    Q_CX_ABLE lspan<t_n> round(const dspan<t_n> & v) {
        return {round(v.min), round(v.max)};
    }

    template <int t_n>
    Q_CX_ABLE ispan<t_n> round(const fspan<t_n> & v) {
        return {round(v.min), round(v.max)};
    }

    template <typename T, int t_n, typename>
    Q_CX_ABLE span<T, t_n> round(const span<T, t_n> & v) {
        return v;
    }

    template <typename T, int t_n, typename>
    Q_CX_ABLE vec<nat, t_n> floor(const vec<T, t_n> & v) {
        if constexpr (t_n == 2) return {floor(v.x), floor(v.y)};
        if constexpr (t_n == 3) return {floor(v.x), floor(v.y), floor(v.z)};
        if constexpr (t_n == 4) return {floor(v.x), floor(v.y), floor(v.z), floor(v.w)};
    }

    template <typename T, int t_n, typename>
    Q_CX_ABLE vec<T, t_n> floor(const vec<T, t_n> & v) {
        if constexpr (t_n == 2) return {floor(v.x), floor(v.y)};
        if constexpr (t_n == 3) return {floor(v.x), floor(v.y), floor(v.z)};
        if constexpr (t_n == 4) return {floor(v.x), floor(v.y), floor(v.z), floor(v.w)};
    }

    template <typename T, int t_n, typename>
    Q_CX_ABLE vec<nat, t_n> ceil(const vec<T, t_n> & v) {
        if constexpr (t_n == 2) return {ceil(v.x), ceil(v.y)};
        if constexpr (t_n == 3) return {ceil(v.x), ceil(v.y), ceil(v.z)};
        if constexpr (t_n == 4) return {ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w)};
    }

    template <typename T, int t_n, typename>
    Q_CX_ABLE vec<T, t_n> ceil(const vec<T, t_n> & v) {
        if constexpr (t_n == 2) return {ceil(v.x), ceil(v.y)};
        if constexpr (t_n == 3) return {ceil(v.x), ceil(v.y), ceil(v.z)};
        if constexpr (t_n == 4) return {ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w)};
    }

    template <typename T, int t_n, typename>
    Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, T t) {
        return (T(1.0) - t) * v1 + t * v2;
    }

    template <typename T, int t_n, typename>
    Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec2<T> & weights) {
        return weights.x * v1 + weights.y * v2;
    }

    template <typename T, int t_n, typename>
    Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & v3, const vec3<T> & weights) {
        return weights.x * v1 + weights.y * v2 + weights.z * v3;
    }

    template <typename T, int t_n, typename>
    Q_CX_ABLE vec<T, t_n> mix(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<T, t_n> & v3, const vec<T, t_n> & v4, const vec4<T> & weights) {
        return weights.x * v1 + weights.y * v2 + weights.z * v3 + weights.w * v4;
    }

    template <typename T, typename>
    Q_CX_ABLE T mix(T v1, T v2, const vec2<T> & weights) {
        return weights.x * v1 + weights.y * v2;
    }

    template <typename T, typename>
    Q_CX_ABLE T mix(T v1, T v2, T v3, const vec3<T> & weights) {
        return weights.x * v1 + weights.y * v2 + weights.z * v3;
    }

    template <typename T, typename>
    Q_CX_ABLE T mix(T v1, T v2, T v3, T v4, const vec4<T> & weights) {
        return weights.x * v1 + weights.y * v2 + weights.z * v3 + weights.w * v4;
    }

    template <typename T, int t_n, typename>
    Q_CX_ABLE vec<T, t_n> smoothstep(const vec<T, t_n> & v1, const vec<T, t_n> & v2, T t) {
        return mix(v1, v2, t * t * (T(3.0) - T(2.0) * t));
    }

    template <typename To, typename From, int t_n, typename>
    Q_CONSTEX vec<To, t_n> transnorm(const vec<From, t_n> & v) {
        if constexpr (t_n == 2) return {transnorm<To>(v.x), transnorm<To>(v.y)};
        if constexpr (t_n == 3) return {transnorm<To>(v.x), transnorm<To>(v.y), transnorm<To>(v.z)};
        if constexpr (t_n == 4) return {transnorm<To>(v.x), transnorm<To>(v.y), transnorm<To>(v.z), transnorm<To>(v.w)};
    }

    template <typename T, int t_n>
    Q_CX_ABLE span<T, t_n> intersect(const span<T, t_n> & v1, const span<T, t_n> & v2) {
        if constexpr (t_n == 1) return {
            max(v1.min, v2.min),
            min(v1.max, v2.max)
        };
        if constexpr (t_n == 2) return {
            vec2<T>(max(v1.min.x, v2.min.x), max(v1.min.y, v2.min.y)),
            vec2<T>(min(v1.max.x, v2.max.x), min(v1.max.y, v2.max.y))
        };
        if constexpr (t_n == 3) return {
            vec3<T>(max(v1.min.x, v2.min.x), max(v1.min.y, v2.min.y), max(v1.min.z, v2.min.z)),
            vec3<T>(min(v1.max.x, v2.max.x), min(v1.max.y, v2.max.y), min(v1.max.z, v2.max.z))
        };
        if constexpr (t_n == 4) return {
            vec4<T>(max(v1.min.x, v2.min.x), max(v1.min.y, v2.min.y), max(v1.min.z, v2.min.z), max(v1.min.w, v2.min.w)),
            vec4<T>(min(v1.max.x, v2.max.x), min(v1.max.y, v2.max.y), min(v1.max.z, v2.max.z), min(v1.max.w, v2.max.w))
        };
    }

    template <typename T, int t_n>
    Q_CX_ABLE span<T, t_n> join(const span<T, t_n> & v1, const span<T, t_n> & v2) {
        return { min(v1.min, v2.min), max(v1.max, v2.max) };
    }

    template <typename T, int t_n>
    inline span<T, t_n> & joinify(span<T, t_n> & v1, const span<T, t_n> & v2) {
        minify(v1.min, v2.min);
        maxify(v1.max, v2.max);
        return v1;
    }

    template <typename T, int t_n, typename>
    Q_CX_ABLE T mipmaps(const vec<T, t_n> & size) {
        return mipmaps(max(size));
    }

    template <typename T, int t_n>
    Q_CX_ABLE vec<T, t_n> composite(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
        vec<T, t_n> v;

        if constexpr (t_n >= 1) {
            if      (v1.x > T(0) && v2.x > T(0)) v.x = qc::max(v1.x, v2.x);
            else if (v1.x < T(0) && v2.x < T(0)) v.x = qc::min(v1.x, v2.x);
            else                                 v.x = v1.x + v2.x;
        }
        if constexpr (t_n >= 2) {
            if      (v1.y > T(0) && v2.y > T(0)) v.y = qc::max(v1.y, v2.y);
            else if (v1.y < T(0) && v2.y < T(0)) v.y = qc::min(v1.y, v2.y);
            else                                 v.y = v1.y + v2.y;
        }
        if constexpr (t_n >= 3) {
            if      (v1.z > T(0) && v2.z > T(0)) v.z = qc::max(v1.z, v2.z);
            else if (v1.z < T(0) && v2.z < T(0)) v.z = qc::min(v1.z, v2.z);
            else                                 v.z = v1.z + v2.z;
        }
        if constexpr (t_n >= 4) {
            if      (v1.w > T(0) && v2.w > T(0)) v.w = qc::max(v1.w, v2.w);
            else if (v1.w < T(0) && v2.w < T(0)) v.w = qc::min(v1.w, v2.w);
            else                                 v.w = v1.w + v2.w;
        }

        return v;
    }

}
