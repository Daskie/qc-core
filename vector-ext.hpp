#pragma once

#include <iostream>

#include "vector.hpp"
#include "core-ext.hpp"

namespace qc::core {

    //
    // ...
    //
    template <Number  T, int n> Q_CX_ABLE T sum(const vec<T, n> & v);

    //
    // ...
    //
    template <Number T, int n> Q_CX_ABLE T product(const vec<T, n> & v);

    //
    // ...
    //
    template <int n> Q_CX_ABLE bool any(const bvec<n> & v);

    //
    // ...
    //
    template <int n> Q_CX_ABLE bool all(const bvec<n> & v);

    //
    // ...
    //
    template <Number T, int n> Q_CX_ABLE         T min(const vec<T, n> & v);
    template <Number T, int n> Q_CX_ABLE vec<T, n> min(const vec<T, n> & v1, const vec<T, n> & v2);
    template <Number T, int n> Q_CX_ABLE vec<T, n> min(const vec<T, n> & v1, T v2);
    template <Number T, int n> Q_CX_ABLE vec<T, n> min(T v1, const vec<T, n> & v2);

    //
    // ...
    //
    template <Number T, int n> Q_CX_ABLE         T max(const vec<T, n> & v);
    template <Number T, int n> Q_CX_ABLE vec<T, n> max(const vec<T, n> & v1, const vec<T, n> & v2);
    template <Number T, int n> Q_CX_ABLE vec<T, n> max(const vec<T, n> & v1, T v2);
    template <Number T, int n> Q_CX_ABLE vec<T, n> max(T v1, const vec<T, n> & v2);

    //
    // ...
    //
    template <Number T, int n> vec<T, n> & minify(vec<T, n> & v1, const vec<T, n> & v2);
    template <Number T, int n> vec<T, n> & minify(vec<T, n> & v1, T v2);

    //
    // ...
    //
    template <Number T, int n> vec<T, n> & maxify(vec<T, n> & v1, const vec<T, n> & v2);
    template <Number T, int n> vec<T, n> & maxify(vec<T, n> & v1, T v2);

    //
    // ...
    //
    template <Number T, int n> Q_CX_ABLE std::pair<T, T> minmax(const vec<T, n> & v);

    //
    // ...
    //
    template <Number T> Q_CX_ABLE T median(const vec3<T> & v);

    //
    // ...
    //
    template <typename T, int n> std::ostream & operator<<(std::ostream & os, const vec<T, n> & v);

    //
    // ...
    //
    template <Floater T, int n> vec<T, n> pow(const vec<T, n> & v, T p);
    template <Floater T, int n> vec<T, n> pow(const vec<T, n> & v, const vec<T, n> & p);

    //
    // ...
    //
    template <Floater T, int n> vec<T, n> exp(const vec<T, n> & v);

    //
    // ...
    //
    template <Floater T, int n> T magnitude(const vec<T, n> & v);

    //
    // ...
    //
    template <Number T, int n> T magnitude2(const vec<T, n> & v);

    //
    // ...
    //
    template <Floater T, int n> vec<T, n> normalize(const vec<T, n> & v);

    //
    // ...
    //
    template <Floater T, int n> vec<T, n> & normalizeAssign(vec<T, n> & v);

    //
    // ...
    //
    template <Number T, int n> T dot(const vec<T, n> & v1, const vec<T, n> & v2);

    //
    // ...
    //
    template <Number T> T cross(const vec2<T> & v1, const vec2<T> & v2);
    template <Number T> vec3<T> cross(const vec3<T> & v1, const vec3<T> & v2);

    //
    // ...
    //
    template <Number T, int n> bool parallel(const vec<T, n> & v1, const vec<T, n> & v2);

    //
    // ...
    //
    template <Number T, int n> bool orthogonal(const vec<T, n> & v1, const vec<T, n> & v2);

    //
    // ...
    //
    template <Number T, int n> Q_CX_ABLE vec<T, n> ortho(const vec<T, n> & v);

    //
    // ...
    //
    template <Floater T, int n> void orthogonalize(const vec<T, n> & v1, vec<T, n> & v2);
    template <Floater T> void orthogonalize(const vec3<T> & v1, vec3<T> & v2, vec3<T> & v3);
    template <Floater T> void orthogonalize_n(const vec3<T> & v1, vec3<T> & v2, vec3<T> & v3);

    //
    // ...
    //
    template <Floater T, int n> vec<T, n> reflect(const vec<T, n> & v, const vec<T, n> & norm);
    template <Floater T, int n> vec<T, n> reflect_n(const vec<T, n> & v, const vec<T, n> & norm);

    //
    // ...
    //
    template <Floater T, int n> T angle(const vec<T, n> & v1, const vec<T, n> & v2);
    template <Floater T, int n> T angle_n(const vec<T, n> & v1, const vec<T, n> & v2);

    //
    // ...
    //
    template <Number  T, int n> void sort(const vec<T, n> & v);

    //
    // ...
    //
    template <Number T, int n> Q_CX_ABLE vec<T, n> clamp(const vec<T, n> & v, T min, T max);
    template <Number T, int n> Q_CX_ABLE vec<T, n> clamp(const vec<T, n> & v, const vec<T, n> & min, const vec<T, n> & max);

    //
    // ...
    //
    template <Number T, int n> Q_CX_ABLE vec<T, n> abs(const vec<T, n> & v);

    //
    // ...
    //
    template <Number T, int n> Q_CX_ABLE bool zero(const vec<T, n> & v, T e = std::numeric_limits<T>::epsilon());

    //
    // ...
    //
    template <Number T, int n> Q_CX_ABLE bool equal(const vec<T, n> & v);

    //
    // ...
    //
    template <Floater T, int n> Q_CX_ABLE bool equal_e(const vec<T, n> & v1, const vec<T, n> & v2, T e = std::numeric_limits<T>::epsilon());
    template <Floater T, int n> Q_CX_ABLE bool equal_e(const vec<T, n> & v, T e = std::numeric_limits<T>::epsilon());

    //
    // ...
    //
    template <Number T, int n> Q_CX_ABLE ivec<n> sign(const vec<T, n> & v);

    //
    // ...
    //
    template <Floater T, int n> Q_CX_ABLE vec<stype<sizeof(T)>, n> round(const vec<T, n> & v);
    template <Integer T, int n> Q_CX_ABLE vec<T, n> round(const vec<T, n> & v);

    //
    // ...
    //
    template <Floater T, int n> Q_CX_ABLE vec<stype<sizeof(T)>, n> floor(const vec<T, n> & v);
    template <Integer T, int n> Q_CX_ABLE vec<T, n> floor(const vec<T, n> & v);

    //
    // ...
    //
    template <Floater T, int n> Q_CX_ABLE vec<stype<sizeof(T)>, n> ceil(const vec<T, n> & v);
    template <Integer T, int n> Q_CX_ABLE vec<T, n> ceil(const vec<T, n> & v);

    //
    // ...
    //
    template <Floater T, int n> Q_CX_ABLE vec<T, n> mix(const vec<T, n> & v1, const vec<T, n> & v2, T t);
    template <Floater T, int n> Q_CX_ABLE vec<T, n> mix(const vec<T, n> & v1, const vec<T, n> & v2, const vec2<T> & weights);
    template <Floater T, int n> Q_CX_ABLE vec<T, n> mix(const vec<T, n> & v1, const vec<T, n> & v2, const vec<T, n> & v3, const vec3<T> & weights);
    template <Floater T, int n> Q_CX_ABLE vec<T, n> mix(const vec<T, n> & v1, const vec<T, n> & v2, const vec<T, n> & v3, const vec<T, n> & v4, const vec4<T> & weights);
    template <Floater T> Q_CX_ABLE T mix(T v1, T v2, const vec2<T> & weights);
    template <Floater T> Q_CX_ABLE T mix(T v1, T v2, T v3, const vec3<T> & weights);
    template <Floater T> Q_CX_ABLE T mix(T v1, T v2, T v3, T v4, const vec4<T> & weights);

    //
    // ...
    //
    template <Floater T, int n> Q_CX_ABLE vec<T, n> smoothstep(const vec<T, n> & v1, const vec<T, n> & v2, T t);

    //
    // Converts between normalized types.
    // Works with floats, signed, and unsigned integers.
    //
    template <Number To, Number From, int n> Q_CONSTEX vec<To, n> transnorm(const vec<From, n> & v);

    //
    // ...
    //
    template <UnsignedInteger T, int n> Q_CX_ABLE T mipmaps(const vec<T, n> & size);

    //
    // ...
    //
    template <Number T, int n> Q_CX_ABLE vec<T, n> composite(const vec<T, n> & v1, const vec<T, n> & v2);

}

// INLINE IMPLEMENTATION ///////////////////////////////////////////////////////////////////////////////////////////////

namespace qc::core {

    template <Number T, int n>
    inline Q_CX_ABLE T sum(const vec<T, n> & v) {
        if constexpr (n == 2) return v.x + v.y;
        if constexpr (n == 3) return v.x + v.y + v.z;
        if constexpr (n == 4) return v.x + v.y + v.z + v.w;
    }

    template <Number T, int n>
    inline Q_CX_ABLE T product(const vec<T, n> & v) {
        if constexpr (n == 2) return v.x * v.y;
        if constexpr (n == 3) return v.x * v.y * v.z;
        if constexpr (n == 4) return v.x * v.y * v.z * v.w;
    }

    template <int n>
    inline Q_CX_ABLE bool all(const bvec<n> & v) {
        if constexpr (n == 2) return v.x && v.y;
        if constexpr (n == 3) return v.x && v.y && v.z;
        if constexpr (n == 4) return v.x && v.y && v.z && v.w;
    }

    template <int n>
    inline Q_CX_ABLE bool any(const bvec<n> & v) {
        if constexpr (n == 2) return v.x || v.y;
        if constexpr (n == 3) return v.x || v.y || v.z;
        if constexpr (n == 4) return v.x || v.y || v.z || v.w;
    }

    template <Number T, int n>
    inline Q_CX_ABLE T min(const vec<T, n> & v) {
        if constexpr (n == 2) return min(v.x, v.y);
        if constexpr (n == 3) return min(v.x, v.y, v.z);
        if constexpr (n == 4) return min(v.x, v.y, v.z, v.w);
    }

    template <Number T, int n>
    inline Q_CX_ABLE vec<T, n> min(const vec<T, n> & v1, const vec<T, n> & v2) {
        if constexpr (n == 2) return {min(v1.x, v2.x), min(v1.y, v2.y)};
        if constexpr (n == 3) return {min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z)};
        if constexpr (n == 4) return {min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z), min(v1.w, v2.w)};
    }

    template <Number T, int n>
    inline Q_CX_ABLE vec<T, n> min(const vec<T, n> & v1, T v2) {
        if constexpr (n == 2) return {min(v1.x, v2), min(v1.y, v2)};
        if constexpr (n == 3) return {min(v1.x, v2), min(v1.y, v2), min(v1.z, v2)};
        if constexpr (n == 4) return {min(v1.x, v2), min(v1.y, v2), min(v1.z, v2), min(v1.w, v2)};
    }

    template <Number T, int n>
    inline Q_CX_ABLE vec<T, n> min(T v1, const vec<T, n> & v2) {
        return min(v2, v1);
    }

    template <Number T, int n>
    inline Q_CX_ABLE T max(const vec<T, n> & v) {
        if constexpr (n == 2) return max(v.x, v.y);
        if constexpr (n == 3) return max(v.x, v.y, v.z);
        if constexpr (n == 4) return max(v.x, v.y, v.z, v.w);
    }

    template <Number T, int n>
    inline Q_CX_ABLE vec<T, n> max(const vec<T, n> & v1, const vec<T, n> & v2) {
        if constexpr (n == 2) return {max(v1.x, v2.x), max(v1.y, v2.y)};
        if constexpr (n == 3) return {max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z)};
        if constexpr (n == 4) return {max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z), max(v1.w, v2.w)};
    }

    template <Number T, int n>
    inline Q_CX_ABLE vec<T, n> max(const vec<T, n> & v1, T v2) {
        if constexpr (n == 2) return {max(v1.x, v2), max(v1.y, v2)};
        if constexpr (n == 3) return {max(v1.x, v2), max(v1.y, v2), max(v1.z, v2)};
        if constexpr (n == 4) return {max(v1.x, v2), max(v1.y, v2), max(v1.z, v2), max(v1.w, v2)};
    }

    template <Number T, int n>
    inline Q_CX_ABLE vec<T, n> max(T v1, const vec<T, n> & v2) {
        return max(v2, v1);
    }

    template <Number T, int n>
    inline vec<T, n> & minify(vec<T, n> & v1, const vec<T, n> & v2) {
        if constexpr (n >= 1) minify(v1.x, v2.x);
        if constexpr (n >= 2) minify(v1.y, v2.y);
        if constexpr (n >= 3) minify(v1.z, v2.z);
        if constexpr (n >= 4) minify(v1.w, v2.w);
        return v1;
    }

    template <Number T, int n>
    inline vec<T, n> & minify(vec<T, n> & v1, T v2) {
        if constexpr (n >= 1) minify(v1.x, v2);
        if constexpr (n >= 2) minify(v1.y, v2);
        if constexpr (n >= 3) minify(v1.z, v2);
        if constexpr (n >= 4) minify(v1.w, v2);
        return v1;
    }

    template <Number T, int n>
    inline vec<T, n> & maxify(vec<T, n> & v1, const vec<T, n> & v2) {
        if constexpr (n >= 1) maxify(v1.x, v2.x);
        if constexpr (n >= 2) maxify(v1.y, v2.y);
        if constexpr (n >= 3) maxify(v1.z, v2.z);
        if constexpr (n >= 4) maxify(v1.w, v2.w);
        return v1;
    }

    template <Number T, int n>
    inline vec<T, n> & maxify(vec<T, n> & v1, T v2) {
        if constexpr (n >= 1) maxify(v1.x, v2);
        if constexpr (n >= 2) maxify(v1.y, v2);
        if constexpr (n >= 3) maxify(v1.z, v2);
        if constexpr (n >= 4) maxify(v1.w, v2);
        return v1;
    }

    template <Number T, int n>
    inline Q_CX_ABLE std::pair<T, T> minmax(const vec<T, n> & v) {
        if constexpr (n == 2) return minmax(v.x, v.y);
        if constexpr (n == 3) return minmax(v.x, v.y, v.z);
        if constexpr (n == 4) return minmax(v.x, v.y, v.z, v.w);
    }

    template <Number T>
    inline Q_CX_ABLE T median(const vec3<T> & v) {
        return median(v.x, v.y, v.z);
    }

    template <typename T, int n>
    inline std::ostream & operator<<(std::ostream & os, const vec<T, n> & v) {
        os << "[";
        if constexpr (n >= 1) os << v.x << " ";
        if constexpr (n >= 2) os << " " << v.y;
        if constexpr (n >= 3) os << " " << v.z;
        if constexpr (n >= 4) os << " " << v.w;
        os << "]";
        return os;
    }

    template <Floater T, int n>
    inline vec<T, n> pow(const vec<T, n> & v, T p) {
        if constexpr (n == 2) return {std::pow(v.x, p), std::pow(v.y, p)};
        if constexpr (n == 3) return {std::pow(v.x, p), std::pow(v.y, p), std::pow(v.z, p)};
        if constexpr (n == 4) return {std::pow(v.x, p), std::pow(v.y, p), std::pow(v.z, p), std::pow(v.w, p)};
    }

    template <Floater T, int n>
    inline vec<T, n> pow(const vec<T, n> & v, const vec<T, n> & p) {
        if constexpr (n == 2) return {std::pow(v.x, p.x), std::pow(v.y, p.y)};
        if constexpr (n == 3) return {std::pow(v.x, p.x), std::pow(v.y, p.y), std::pow(v.z, p.z)};
        if constexpr (n == 4) return {std::pow(v.x, p.x), std::pow(v.y, p.y), std::pow(v.z, p.z), std::pow(v.w, p.w)};
    }

    template <Floater T, int n>
    inline vec<T, n> exp(const vec<T, n> & v) {
        if constexpr (n == 2) return {std::exp(v.x), std::exp(v.y)};
        if constexpr (n == 3) return {std::exp(v.x), std::exp(v.y), std::exp(v.z)};
        if constexpr (n == 4) return {std::exp(v.x), std::exp(v.y), std::exp(v.z), std::exp(v.w)};
    }

    template <Floater T, int n>
    inline T magnitude(const vec<T, n> & v) {
        return T(std::sqrt(magnitude2(v)));
    }

    template <Number T, int n>
    inline T magnitude2(const vec<T, n> & v) {
        if constexpr (n == 2) return v.x * v.x + v.y * v.y;
        if constexpr (n == 3) return v.x * v.x + v.y * v.y + v.z * v.z;
        if constexpr (n == 4) return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
    }

    template <Floater T, int n>
    inline vec<T, n> normalize(const vec<T, n> & v) {
        T m2(magnitude2(v));
        if (zero(m2)) {
            return {};
        }
        return v / std::sqrt(m2);
    }

    template <Floater T, int n>
    inline vec<T, n> & normalizeAssign(vec<T, n> & v) {
        T m2(magnitude2(v));
        if (zero(m2)) {
            return v;
        }
        return v /= std::sqrt(m2);
    }

    template <Number T, int n>
    inline T dot(const vec<T, n> & v1, const vec<T, n> & v2) {
        if constexpr (n == 2) return v1.x * v2.x + v1.y * v2.y;
        if constexpr (n == 3) return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
        if constexpr (n == 4) return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
    }

    template <Number T>
    inline T cross(const vec2<T> & v1, const vec2<T> & v2) {
        return v1.x * v2.y - v1.y * v2.x;
    }

    template <Number T>
    inline vec3<T> cross(const vec3<T> & v1, const vec3<T> & v2) {
        return {T(v1.y * v2.z - v1.z * v2.y), T(v1.z * v2.x - v1.x * v2.z), T(v1.x * v2.y - v1.y * v2.x)};
    }

    template <Number T, int n>
    inline bool parallel(const vec<T, n> & v1, const vec<T, n> & v2) {
        T d(dot(v1, v2));
        return equal(d * d, magnitude2(v1) * magnitude2(v2));
    }

    template <Number T, int n>
    inline bool orthogonal(const vec<T, n> & v1, const vec<T, n> & v2) {
        return zero(dot(v1, v2));
    }

    template <Number T, int n>
    inline Q_CX_ABLE vec<T, n> ortho(const vec<T, n> & v) {
        if constexpr (n == 2) {
            return {-v.y, v.x};
        }
        else if constexpr (n  == 3) {
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

    template <Floater T, int n>
    inline void orthogonalize(const vec<T, n> & v1, vec<T, n> & v2) {
        v2 = normalize(v2 - dot(v1, v2) * v1);
    }

    // in order of priority
    template <Floater T>
    inline void orthogonalize(const vec3<T> & v1, vec3<T> & v2, vec3<T> & v3) {
        orthogonalize_n(v1, v2, v3);
        v2 = normalize(v2);
        v3 = normalize(v3);
    }

    // in order of priority
    template <Floater T>
    inline void orthogonalize_n(const vec3<T> & v1, vec3<T> & v2, vec3<T> & v3) {
        orthogonalize(v1, v2);
        v3 = cross(v2, v1);
    }

    template <Floater T, int n>
    inline vec<T, n> reflect(const vec<T, n> & v, const vec<T, n> & norm) {
        return reflect_n(v, normalize(norm));
    }

    template <Floater T, int n>
    inline vec<T, n> reflect_n(const vec<T, n> & v, const vec<T, n> & norm) {
        return (T(2.0) * dot(v, norm)) * norm - v;
    }

    template <Floater T, int n>
    inline T angle(const vec<T, n> & v1, const vec<T, n> & v2) {
        return angle_n(normalize(v1), normalize(v2));
    }
    template <Floater T, int n>
    inline T angle_n(const vec<T, n> & v1, const vec<T, n> & v2) {
        return T(std::acos(dot(v1, v2)));
    }

    template <Number T, int n>
    inline void sort(vec<T, n> & v) {
        if constexpr (n >= 2) {
            if (v.x > v.y) std::swap(v.x, v.y);
        }
        if constexpr (n >= 3) {
            if (v.y > v.z) std::swap(v.y, v.z);
            if (v.x > v.y) std::swap(v.x, v.y);
        }
        if constexpr (n >= 4) {
            if (v.z > v.w) std::swap(v.z, v.w);
            if (v.y > v.z) std::swap(v.y, v.z);
            if (v.x > v.y) std::swap(v.x, v.y);
        }
    }

    template <Number T, int n>
    inline Q_CX_ABLE vec<T, n> clamp(const vec<T, n> & v, T min, T max) {
        if constexpr (n == 2) return {clamp(v.x, min, max), clamp(v.y, min, max)};
        if constexpr (n == 3) return {clamp(v.x, min, max), clamp(v.y, min, max), clamp(v.z, min, max)};
        if constexpr (n == 4) return {clamp(v.x, min, max), clamp(v.y, min, max), clamp(v.z, min, max), clamp(v.w, min, max)};
    }

    template <Number T, int n>
    inline Q_CX_ABLE vec<T, n> clamp(const vec<T, n> & v, const vec<T, n> & min, const vec<T, n> & max) {
        if constexpr (n == 2) return {clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y)};
        if constexpr (n == 3) return {clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y), clamp(v.z, min.z, max.z)};
        if constexpr (n == 4) return {clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y), clamp(v.z, min.z, max.z), clamp(v.w, min.w, max.w)};
    }

    template <Number T, int n>
    inline Q_CX_ABLE vec<T, n> abs(const vec<T, n> & v) {
        if constexpr (n == 2) return {abs(v.x), abs(v.y)};
        if constexpr (n == 3) return {abs(v.x), abs(v.y), abs(v.z)};
        if constexpr (n == 4) return {abs(v.x), abs(v.y), abs(v.z), abs(v.w)};
    }

    template <Number T, int n>
    inline Q_CX_ABLE bool zero(const vec<T, n> & v, T e) {
        if constexpr (n == 2) return zero(v.x, e) && zero(v.y, e);
        if constexpr (n == 3) return zero(v.x, e) && zero(v.y, e) && zero(v.z, e);
        if constexpr (n == 4) return zero(v.x, e) && zero(v.y, e) && zero(v.z, e) && zero(v.w, e);
    }

    template <Number T, int n>
    inline Q_CX_ABLE bool equal(const vec<T, n> & v) {
        if constexpr (n == 2) return v.x == v.y;
        if constexpr (n == 3) return v.x == v.y && v.x == v.z;
        if constexpr (n == 4) return v.x == v.y && v.x == v.z && v.x == v.w;
    }

    template <Floater T, int n>
    inline Q_CX_ABLE bool equal_e(const vec<T, n> & v1, const vec<T, n> & v2, T e) {
        return zero(v1 - v2, e);
    }

    template <Floater T, int n>
    inline Q_CX_ABLE bool equal_e(const vec<T, n> & v, T e) {
        return zero(v - v.x, e);
    }

    template <Number T, int n>
    inline Q_CX_ABLE ivec<n> sign(const vec<T, n> & v) {
        if constexpr (n == 2) return {sign(v.x), sign(v.y)};
        if constexpr (n == 3) return {sign(v.x), sign(v.y), sign(v.z)};
        if constexpr (n == 4) return {sign(v.x), sign(v.y), sign(v.z), sign(v.w)};
    }

    template <Floater T, int n>
    inline Q_CX_ABLE vec<stype<sizeof(T)>, n> floor(const vec<T, n> & v) {
        if constexpr (n == 2) return {floor(v.x), floor(v.y)};
        if constexpr (n == 3) return {floor(v.x), floor(v.y), floor(v.z)};
        if constexpr (n == 4) return {floor(v.x), floor(v.y), floor(v.z), floor(v.w)};
    }

    template <Integer T, int n>
    inline Q_CX_ABLE vec<T, n> floor(const vec<T, n> & v) {
        return v;
    }

    template <Floater T, int n>
    inline Q_CX_ABLE vec<stype<sizeof(T)>, n> ceil(const vec<T, n> & v) {
        if constexpr (n == 2) return {ceil(v.x), ceil(v.y)};
        if constexpr (n == 3) return {ceil(v.x), ceil(v.y), ceil(v.z)};
        if constexpr (n == 4) return {ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w)};
    }

    template <Integer T, int n>
    inline Q_CX_ABLE vec<T, n> ceil(const vec<T, n> & v) {
        return v;
    }

    template <Floater T, int n>
    inline Q_CX_ABLE vec<stype<sizeof(T)>, n> round(const vec<T, n> & v) {
        if constexpr (n == 2) return {round(v.x), round(v.y)};
        if constexpr (n == 3) return {round(v.x), round(v.y), round(v.z)};
        if constexpr (n == 4) return {round(v.x), round(v.y), round(v.z), round(v.w)};
    }

    template <Integer T, int n>
    inline Q_CX_ABLE vec<T, n> round(const vec<T, n> & v) {
        return v;
    }

    template <Floater T, int n>
    inline Q_CX_ABLE vec<T, n> mix(const vec<T, n> & v1, const vec<T, n> & v2, T t) {
        return (T(1.0) - t) * v1 + t * v2;
    }

    template <Floater T, int n>
    inline Q_CX_ABLE vec<T, n> mix(const vec<T, n> & v1, const vec<T, n> & v2, const vec2<T> & weights) {
        return weights.x * v1 + weights.y * v2;
    }

    template <Floater T, int n>
    inline Q_CX_ABLE vec<T, n> mix(const vec<T, n> & v1, const vec<T, n> & v2, const vec<T, n> & v3, const vec3<T> & weights) {
        return weights.x * v1 + weights.y * v2 + weights.z * v3;
    }

    template <Floater T, int n>
    inline Q_CX_ABLE vec<T, n> mix(const vec<T, n> & v1, const vec<T, n> & v2, const vec<T, n> & v3, const vec<T, n> & v4, const vec4<T> & weights) {
        return weights.x * v1 + weights.y * v2 + weights.z * v3 + weights.w * v4;
    }

    template <Floater T>
    inline Q_CX_ABLE T mix(T v1, T v2, const vec2<T> & weights) {
        return weights.x * v1 + weights.y * v2;
    }

    template <Floater T>
    inline Q_CX_ABLE T mix(T v1, T v2, T v3, const vec3<T> & weights) {
        return weights.x * v1 + weights.y * v2 + weights.z * v3;
    }

    template <Floater T>
    inline Q_CX_ABLE T mix(T v1, T v2, T v3, T v4, const vec4<T> & weights) {
        return weights.x * v1 + weights.y * v2 + weights.z * v3 + weights.w * v4;
    }

    template <Floater T, int n>
    inline Q_CX_ABLE vec<T, n> smoothstep(const vec<T, n> & v1, const vec<T, n> & v2, T t) {
        return mix(v1, v2, t * t * (T(3.0) - T(2.0) * t));
    }

    template <Number To, Number From, int n>
    inline Q_CONSTEX vec<To, n> transnorm(const vec<From, n> & v) {
        if constexpr (n == 2) return {transnorm<To>(v.x), transnorm<To>(v.y)};
        if constexpr (n == 3) return {transnorm<To>(v.x), transnorm<To>(v.y), transnorm<To>(v.z)};
        if constexpr (n == 4) return {transnorm<To>(v.x), transnorm<To>(v.y), transnorm<To>(v.z), transnorm<To>(v.w)};
    }

    template <UnsignedInteger T, int n>
    inline Q_CX_ABLE T mipmaps(const vec<T, n> & size) {
        return mipmaps(max(size));
    }

    template <Number T, int n>
    inline Q_CX_ABLE vec<T, n> composite(const vec<T, n> & v1, const vec<T, n> & v2) {
        vec<T, n> v;

        if constexpr (n >= 1) {
            if      (v1.x > T(0) && v2.x > T(0)) v.x = max(v1.x, v2.x);
            else if (v1.x < T(0) && v2.x < T(0)) v.x = min(v1.x, v2.x);
            else                                 v.x = v1.x + v2.x;
        }
        if constexpr (n >= 2) {
            if      (v1.y > T(0) && v2.y > T(0)) v.y = max(v1.y, v2.y);
            else if (v1.y < T(0) && v2.y < T(0)) v.y = min(v1.y, v2.y);
            else                                 v.y = v1.y + v2.y;
        }
        if constexpr (n >= 3) {
            if      (v1.z > T(0) && v2.z > T(0)) v.z = max(v1.z, v2.z);
            else if (v1.z < T(0) && v2.z < T(0)) v.z = min(v1.z, v2.z);
            else                                 v.z = v1.z + v2.z;
        }
        if constexpr (n >= 4) {
            if      (v1.w > T(0) && v2.w > T(0)) v.w = max(v1.w, v2.w);
            else if (v1.w < T(0) && v2.w < T(0)) v.w = min(v1.w, v2.w);
            else                                 v.w = v1.w + v2.w;
        }

        return v;
    }

}
