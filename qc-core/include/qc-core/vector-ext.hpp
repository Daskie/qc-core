#pragma once

#include <iostream>

#include <qc-core/vector.hpp>
#include <qc-core/core-ext.hpp>

namespace qc
{
    template <Numeric T, u32 n> vec<T, n> & sort(vec<T, n> & v);

    //
    // ...
    //
    template <Numeric  T, u32 n> nodisc constexpr T sum(const vec<T, n> & v);

    //
    // ...
    //
    template <Numeric T, u32 n> nodisc constexpr T product(const vec<T, n> & v);

    //
    // ...
    //
    template <u32 n> nodisc constexpr bool any(bvec<n> v);
    nodisc constexpr bool any(const bool v) { return v; }

    //
    // ...
    //
    template <u32 n> nodisc constexpr bool all(bvec<n> v);
    nodisc constexpr bool all(const bool v) { return v; }

    //
    // ...
    //
    template <typename T, u32 n> std::ostream & operator<<(std::ostream & os, const vec<T, n> & v);

    //
    // ...
    //
    template <Floating T, u32 n> nodisc vec<T, n> pow(const vec<T, n> & v, T p);
    template <Floating T, u32 n> nodisc vec<T, n> pow(const vec<T, n> & v, const vec<T, n> & p);

    //
    // ...
    //
    template <Floating T, u32 n> nodisc vec<T, n> exp(const vec<T, n> & v);

    //
    // ...
    //
    template <Floating T, u32 n> nodisc T magnitude(const vec<T, n> & v);

    //
    // ...
    //
    template <Numeric T, u32 n> nodisc T magnitude2(const vec<T, n> & v);

    //
    // ...
    //
    template <Floating T1, Floating T2, u32 n> nodisc LargerOf<T1, T2> distance(const vec<T1, n> & v1, const vec<T2, n> & v2);

    //
    // ...
    //
    template <Numeric T1, Numeric T2, u32 n> nodisc Common<T1, T2> distance2(const vec<T1, n> & v1, const vec<T2, n> & v2);

    //
    // ...
    //
    template <Floating T, u32 n> nodisc vec<T, n> normalize(const vec<T, n> & v);

    //
    // ...
    //
    template <Floating T, u32 n> vec<T, n> & normalizeAssign(vec<T, n> & v);

    //
    // ...
    //
    template <Numeric T1, Numeric T2, u32 n> nodisc Common<T1, T2> dot(const vec<T1, n> & v1, const vec<T2, n> & v2);

    //
    // ...
    //
    template <Numeric T1, Numeric T2> nodisc Common<T1, T2> cross(vec2<T1> v1, vec2<T2> v2);
    template <Numeric T1, Numeric T2> nodisc vec3<Common<T1, T2>> cross(vec3<T1> v1, vec3<T2> v2);

    //
    // ...
    //
    template <Numeric T, u32 n> nodisc bool parallel(const vec<T, n> & v1, const vec<T, n> & v2);

    //
    // ...
    //
    template <Numeric T, u32 n> nodisc bool orthogonal(const vec<T, n> & v1, const vec<T, n> & v2);

    //
    // ...
    //
    template <Signed T> nodisc vec2<T> ortho(const vec2<T> & v);
    template <Signed T> nodisc vec3<T> ortho(const vec3<T> & v);

    //
    // ...
    //
    template <Floating T, u32 n> void orthogonalize(const vec<T, n> & v1, vec<T, n> & v2);
    template <Floating T> void orthogonalize(vec3<T> v1, vec3<T> & v2, vec3<T> & v3);
    template <Floating T> void orthogonalize_n(vec3<T> v1, vec3<T> & v2, vec3<T> & v3);

    //
    // ...
    //
    template <Floating T, u32 n> nodisc vec<T, n> reflect(const vec<T, n> & v, const vec<T, n> & norm);
    template <Floating T, u32 n> nodisc vec<T, n> reflect_n(const vec<T, n> & v, const vec<T, n> & norm);

    //
    // ...
    //
    template <Floating T, u32 n> nodisc T angle(const vec<T, n> & v1, const vec<T, n> & v2);
    template <Floating T, u32 n> nodisc T angle_n(const vec<T, n> & v1, const vec<T, n> & v2);

    //
    // ...
    //
    template <Numeric  T, u32 n> void sort(const vec<T, n> & v);

    //
    // ...
    //
    template <Numeric T, u32 n> nodisc constexpr vec<T, n> abs(const vec<T, n> & v);

    //
    // ...
    //
    template <Numeric T, u32 n> vec<T, n> & absify(vec<T, n> & v);

    //
    // ...
    //
    template <Numeric T, u32 n> nodisc bool zeroish(const vec<T, n> & v, T e = std::numeric_limits<T>::epsilon());

    //
    // ...
    //
    template <Numeric T, u32 n> nodisc bool equalish(const vec<T, n> & v1, const vec<T, n> & v2, T e = std::numeric_limits<T>::epsilon());
    template <Numeric T, u32 n> nodisc bool equalish(const vec<T, n> & v1, const T v2, T e = std::numeric_limits<T>::epsilon());

    //
    // ...
    //
    template <Numeric T, u32 n> nodisc constexpr vec<T, n> sign(const vec<T, n> & v);

    //
    // ...
    //
    template <Numeric R, Numeric T, u32 n> nodisc constexpr vec<R, n> round(const vec<T, n> & v);

    //
    // ...
    //
    template <Numeric R, Numeric T, u32 n> nodisc constexpr vec<R, n> floor(const vec<T, n> & v);

    //
    // ...
    //
    template <Numeric R, Numeric T, u32 n> nodisc constexpr vec<R, n> ceil(const vec<T, n> & v);

    //
    // ...
    //
    template <Floating T, u32 n> nodisc vec<T, n> mix(const vec<T, n> & v1, const vec<T, n> & v2, T t);
    template <Floating T, u32 n> nodisc vec<T, n> mix(const vec<T, n> & v1, const vec<T, n> & v2, vec2<T> weights);
    template <Floating T, u32 n> nodisc vec<T, n> mix(const vec<T, n> & v1, const vec<T, n> & v2, const vec<T, n> & v3, vec3<T> weights);
    template <Floating T, u32 n> nodisc vec<T, n> mix(const vec<T, n> & v1, const vec<T, n> & v2, const vec<T, n> & v3, const vec<T, n> & v4, vec4<T> weights);
    template <Floating T> nodisc T mix(T v1, T v2, vec2<T> weights);
    template <Floating T> nodisc T mix(T v1, T v2, T v3, vec3<T> weights);
    template <Floating T> nodisc T mix(T v1, T v2, T v3, T v4, vec4<T> weights);

    //
    // ...
    //
    template <Floating T, u32 n> nodisc vec<T, n> smoothstep(const vec<T, n> & v1, const vec<T, n> & v2, T t);

    //
    // Converts between normalized types.
    // Works with floats, signed, and unsigned integers.
    //
    template <Numeric To, Numeric From, u32 n> nodisc constexpr vec<To, n> transnorm(const vec<From, n> & v);

    //
    // ...
    //
    template <UnsignedIntegral T, u32 n> nodisc constexpr T mipmaps(const vec<T, n> & size);

    //
    // ...
    //
    template <Numeric T, u32 n> nodisc vec<T, n> composite(const vec<T, n> & v1, const vec<T, n> & v2);

    ///
    /// ...
    ///
    template <Signed T> nodisc vec2<T> rotateCW(const vec2<T> & v);
    template <Signed T> nodisc vec2<T> rotateCCW(const vec2<T> & v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <Numeric T, u32 n>
    inline vec<T, n> & sort(vec<T, n> & v)
    {
        if (v.x < v.y)
        {
            std::swap(v.x, v.y);
        }
        if constexpr (n >= 3)
        {
            if (v.y < v.z)
            {
                std::swap(v.y, v.z);

                if (v.x < v.y)
                {
                    std::swap(v.x, v.y);
                }
            }
        }
        if constexpr (n >= 4)
        {
            if (v.z < v.w)
            {
                std::swap(v.z, v.w);

                if (v.y < v.z)
                {
                    std::swap(v.y, v.z);

                    if (v.x < v.y)
                    {
                        std::swap(v.x, v.y);
                    }
                }
            }
        }

        return v;
    }

    template <Numeric T, u32 n>
    forceinline constexpr T sum(const vec<T, n> & v)
    {
        if constexpr (n == 2) return T(v.x + v.y);
        if constexpr (n == 3) return T(v.x + v.y + v.z);
        if constexpr (n == 4) return T(v.x + v.y + v.z + v.w);
    }

    template <Numeric T, u32 n>
    forceinline constexpr T product(const vec<T, n> & v)
    {
        if constexpr (n == 2) return T(v.x * v.y);
        if constexpr (n == 3) return T(v.x * v.y * v.z);
        if constexpr (n == 4) return T(v.x * v.y * v.z * v.w);
    }

    template <u32 n>
    forceinline constexpr bool all(const bvec<n> v)
    {
        if constexpr (n == 2) return v.x && v.y;
        if constexpr (n == 3) return v.x && v.y && v.z;
        if constexpr (n == 4) return v.x && v.y && v.z && v.w;
    }

    template <u32 n>
    forceinline constexpr bool any(const bvec<n> v)
    {
        return bool(v);
    }

    template <typename T, u32 n>
    inline std::ostream & operator<<(std::ostream & os, const vec<T, n> & v)
    {
        os << '[';
        if constexpr (n >= 1) os << v.x;
        if constexpr (n >= 2) os << ", " << v.y;
        if constexpr (n >= 3) os << ", " << v.z;
        if constexpr (n >= 4) os << ", " << v.w;
        os << ']';
        return os;
    }

    template <Floating T, u32 n>
    forceinline vec<T, n> pow(const vec<T, n> & v, const T p)
    {
        if constexpr (n == 2) return {std::pow(v.x, p), std::pow(v.y, p)};
        if constexpr (n == 3) return {std::pow(v.x, p), std::pow(v.y, p), std::pow(v.z, p)};
        if constexpr (n == 4) return {std::pow(v.x, p), std::pow(v.y, p), std::pow(v.z, p), std::pow(v.w, p)};
    }

    template <Floating T, u32 n>
    forceinline vec<T, n> pow(const vec<T, n> & v, const vec<T, n> & p)
    {
        if constexpr (n == 2) return {std::pow(v.x, p.x), std::pow(v.y, p.y)};
        if constexpr (n == 3) return {std::pow(v.x, p.x), std::pow(v.y, p.y), std::pow(v.z, p.z)};
        if constexpr (n == 4) return {std::pow(v.x, p.x), std::pow(v.y, p.y), std::pow(v.z, p.z), std::pow(v.w, p.w)};
    }

    template <Floating T, u32 n>
    forceinline vec<T, n> exp(const vec<T, n> & v)
    {
        if constexpr (n == 2) return {std::exp(v.x), std::exp(v.y)};
        if constexpr (n == 3) return {std::exp(v.x), std::exp(v.y), std::exp(v.z)};
        if constexpr (n == 4) return {std::exp(v.x), std::exp(v.y), std::exp(v.z), std::exp(v.w)};
    }

    template <Floating T, u32 n>
    forceinline T magnitude(const vec<T, n> & v)
    {
        return std::sqrt(magnitude2(v));
    }

    template <Numeric T, u32 n>
    forceinline T magnitude2(const vec<T, n> & v)
    {
        if constexpr (n == 2) return T(v.x * v.x + v.y * v.y);
        if constexpr (n == 3) return T(v.x * v.x + v.y * v.y + v.z * v.z);
        if constexpr (n == 4) return T(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    }

    template <Floating T1, Floating T2, u32 n>
    forceinline LargerOf<T1, T2> distance(const vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        return std::sqrt(distance2(v1, v2));
    }

    template <Numeric T1, Numeric T2, u32 n>
    forceinline Common<T1, T2> distance2(const vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        if constexpr (Signed<Common<T1, T2>>)
        {
            return magnitude2(v2 - v1);
        }
        else
        {
            return magnitude2(max(v1, v2) - min(v1, v2));
        }
    }

    template <Floating T, u32 n>
    forceinline vec<T, n> normalize(const vec<T, n> & v)
    {
        const T m2{magnitude2(v)};

        if (zeroish(m2))
        {
            return {};
        }

        return v / std::sqrt(m2);
    }

    template <Floating T, u32 n>
    forceinline vec<T, n> & normalizeAssign(vec<T, n> & v)
    {
        const T m2{magnitude2(v)};

        if (zeroish(m2))
        {
            return v = {};
        }

        return v /= std::sqrt(m2);
    }

    template <Numeric T1, Numeric T2, u32 n>
    forceinline Common<T1, T2> dot(const vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        using T = Common<T1, T2>;
        if constexpr (n == 2) return T(v1.x * v2.x + v1.y * v2.y);
        if constexpr (n == 3) return T(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
        if constexpr (n == 4) return T(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
    }

    template <Numeric T1, Numeric T2>
    forceinline Common<T1, T2> cross(const vec2<T1> v1, const vec2<T2> v2)
    {
        return Common<T1, T2>(v1.x * v2.y - v1.y * v2.x);
    }

    template <Numeric T1, Numeric T2>
    forceinline vec3<Common<T1, T2>> cross(const vec3<T1> v1, const vec3<T2> v2)
    {
        using T = Common<T1, T2>;
        return {
            T(v1.y * v2.z - v1.z * v2.y),
            T(v1.z * v2.x - v1.x * v2.z),
            T(v1.x * v2.y - v1.y * v2.x)};
    }

    template <Numeric T, u32 n>
    inline bool parallel(const vec<T, n> & v1, const vec<T, n> & v2)
    {
        const T d{dot(v1, v2)};
        return equalish(d * d, magnitude2(v1) * magnitude2(v2));
    }

    template <Numeric T, u32 n>
    inline bool orthogonal(const vec<T, n> & v1, const vec<T, n> & v2)
    {
        return zeroish(dot(v1, v2));
    }

    template <Signed T>
    inline vec2<T> ortho(const vec2<T> & v)
    {
        return {T(-v.y), v.x};
    }

    template <Signed T>
    inline vec3<T> ortho(const vec3<T> & v)
    {
        const vec3<T> absV(abs(v));

        if (absV.x < absV.y && absV.x < absV.z)
        {
            return {T(0), T(-v.z), v.y}; // rotate around x
        }
        else if (absV.y < absV.z)
        {
            return {v.z, T(0), T(-v.x)}; // rotate around y
        }
        else
        {
            return {T(-v.y), v.x, T(0)}; // rotate around z
        }
    }

    template <Floating T, u32 n>
    inline void orthogonalize(const vec<T, n> & v1, vec<T, n> & v2)
    {
        v2 = normalize(v2 - dot(v1, v2) * v1);
    }

    // in order of priority
    template <Floating T>
    inline void orthogonalize(const vec3<T> v1, vec3<T> & v2, vec3<T> & v3)
    {
        orthogonalize_n(v1, v2, v3);
        v2 = normalize(v2);
        v3 = normalize(v3);
    }

    // in order of priority
    template <Floating T>
    inline void orthogonalize_n(const vec3<T> v1, vec3<T> & v2, vec3<T> & v3)
    {
        orthogonalize(v1, v2);
        v3 = cross(v2, v1);
    }

    template <Floating T, u32 n>
    inline vec<T, n> reflect(const vec<T, n> & v, const vec<T, n> & norm)
    {
        return reflect_n(v, normalize(norm));
    }

    template <Floating T, u32 n>
    inline vec<T, n> reflect_n(const vec<T, n> & v, const vec<T, n> & norm)
    {
        return (T(2.0) * dot(v, norm)) * norm - v;
    }

    template <Floating T, u32 n>
    inline T angle(const vec<T, n> & v1, const vec<T, n> & v2)
    {
        return angle_n(normalize(v1), normalize(v2));
    }

    template <Floating T, u32 n>
    inline T angle_n(const vec<T, n> & v1, const vec<T, n> & v2)
    {
        return T(std::acos(dot(v1, v2)));
    }

    template <Numeric T, u32 n>
    forceinline constexpr vec<T, n> abs(const vec<T, n> & v)
    {
        if constexpr (n == 2) return {abs(v.x), abs(v.y)};
        if constexpr (n == 3) return {abs(v.x), abs(v.y), abs(v.z)};
        if constexpr (n == 4) return {abs(v.x), abs(v.y), abs(v.z), abs(v.w)};
    }

    template <Numeric T, u32 n>
    forceinline vec<T, n> & absify(vec<T, n> & v)
    {
        if constexpr (n >= 1) absify(v.x);
        if constexpr (n >= 2) absify(v.y);
        if constexpr (n >= 3) absify(v.z);
        if constexpr (n >= 4) absify(v.w);
        return v;
    }

    template <Numeric T, u32 n>
    forceinline bool zeroish(const vec<T, n> & v, T e)
    {
        if constexpr (n == 2) return zeroish(v.x, e) && zeroish(v.y, e);
        if constexpr (n == 3) return zeroish(v.x, e) && zeroish(v.y, e) && zeroish(v.z, e);
        if constexpr (n == 4) return zeroish(v.x, e) && zeroish(v.y, e) && zeroish(v.z, e) && zeroish(v.w, e);
    }

    template <Numeric T, u32 n>
    forceinline bool equalish(const vec<T, n> & v1, const vec<T, n> & v2, const T e)
    {
        return zeroish(v1 - v2, e);
    }

    template <Numeric T, u32 n>
    forceinline bool equalish(const vec<T, n> & v1, const T v2, const T e)
    {
        return zeroish(v1 - v2, e);
    }

    template <Numeric T, u32 n>
    forceinline constexpr vec<T, n> sign(const vec<T, n> & v)
    {
        if constexpr (n == 2) return {sign(v.x), sign(v.y)};
        if constexpr (n == 3) return {sign(v.x), sign(v.y), sign(v.z)};
        if constexpr (n == 4) return {sign(v.x), sign(v.y), sign(v.z), sign(v.w)};
    }

    template <Numeric R, Numeric T, u32 n>
    forceinline vec<R, n> constexpr round(const vec<T, n> & v)
    {
        if constexpr (Integral<T>)
        {
            if constexpr (Same<T, R>)
            {
                return v;
            }
            else
            {
                return vec<R, n>(v);
            }
        }
        else
        {
            if constexpr (n == 2) return {round<R>(v.x), round<R>(v.y)};
            if constexpr (n == 3) return {round<R>(v.x), round<R>(v.y), round<R>(v.z)};
            if constexpr (n == 4) return {round<R>(v.x), round<R>(v.y), round<R>(v.z), round<R>(v.w)};
        }
    }

    template <Numeric R, Numeric T, u32 n>
    forceinline constexpr vec<R, n> floor(const vec<T, n> & v)
    {
        if constexpr (Integral<T>)
        {
            if constexpr (Same<T, R>)
            {
                return v;
            }
            else
            {
                return vec<R, n>(v);
            }
        }
        else
        {
            if constexpr (n == 2) return {floor<R>(v.x), floor<R>(v.y)};
            if constexpr (n == 3) return {floor<R>(v.x), floor<R>(v.y), floor<R>(v.z)};
            if constexpr (n == 4) return {floor<R>(v.x), floor<R>(v.y), floor<R>(v.z), floor<R>(v.w)};
        }
    }

    template <Numeric R, Numeric T, u32 n>
    forceinline constexpr vec<R, n> ceil(const vec<T, n> & v)
    {
        if constexpr (Integral<T>)
        {
            if constexpr (Same<T, R>)
            {
                return v;
            }
            else
            {
                return vec<R, n>(v);
            }
        }
        else
        {
            if constexpr (n == 2) return {ceil<R>(v.x), ceil<R>(v.y)};
            if constexpr (n == 3) return {ceil<R>(v.x), ceil<R>(v.y), ceil<R>(v.z)};
            if constexpr (n == 4) return {ceil<R>(v.x), ceil<R>(v.y), ceil<R>(v.z), ceil<R>(v.w)};
        }
    }

    template <Floating T, u32 n>
    forceinline vec<T, n> mix(const vec<T, n> & v1, const vec<T, n> & v2, const T t)
    {
        return (T(1.0) - t) * v1 + t * v2;
    }

    template <Floating T, u32 n>
    forceinline vec<T, n> mix(const vec<T, n> & v1, const vec<T, n> & v2, const vec2<T> weights)
    {
        return weights.x * v1 + weights.y * v2;
    }

    template <Floating T, u32 n>
    forceinline vec<T, n> mix(const vec<T, n> & v1, const vec<T, n> & v2, const vec<T, n> & v3, const vec3<T> weights)
    {
        return weights.x * v1 + weights.y * v2 + weights.z * v3;
    }

    template <Floating T, u32 n>
    forceinline vec<T, n> mix(const vec<T, n> & v1, const vec<T, n> & v2, const vec<T, n> & v3, const vec<T, n> & v4, const vec4<T> weights)
    {
        return weights.x * v1 + weights.y * v2 + weights.z * v3 + weights.w * v4;
    }

    template <Floating T>
    forceinline T mix(const T v1, const T v2, const vec2<T> weights)
    {
        return weights.x * v1 + weights.y * v2;
    }

    template <Floating T>
    forceinline T mix(const T v1, const T v2, const T v3, const vec3<T> weights)
    {
        return weights.x * v1 + weights.y * v2 + weights.z * v3;
    }

    template <Floating T>
    forceinline T mix(const T v1, const T v2, const T v3, const T v4, const vec4<T> weights)
    {
        return weights.x * v1 + weights.y * v2 + weights.z * v3 + weights.w * v4;
    }

    template <Floating T, u32 n>
    forceinline vec<T, n> smoothstep(const vec<T, n> & v1, const vec<T, n> & v2, const T t)
    {
        return mix(v1, v2, t * t * (T(3.0) - T(2.0) * t));
    }

    template <Numeric To, Numeric From, u32 n>
    forceinline constexpr vec<To, n> transnorm(const vec<From, n> & v)
    {
        if constexpr (n == 2) return {transnorm<To>(v.x), transnorm<To>(v.y)};
        if constexpr (n == 3) return {transnorm<To>(v.x), transnorm<To>(v.y), transnorm<To>(v.z)};
        if constexpr (n == 4) return {transnorm<To>(v.x), transnorm<To>(v.y), transnorm<To>(v.z), transnorm<To>(v.w)};
    }

    template <UnsignedIntegral T, u32 n>
    forceinline constexpr T mipmaps(const vec<T, n> & size)
    {
        return mipmaps(max(size));
    }

    template <Numeric T, u32 n>
    inline vec<T, n> composite(const vec<T, n> & v1, const vec<T, n> & v2)
    {
        vec<T, n> v;

        if constexpr (n >= 1)
        {
            if      (v1.x > T(0) && v2.x > T(0)) v.x = max(v1.x, v2.x);
            else if (v1.x < T(0) && v2.x < T(0)) v.x = min(v1.x, v2.x);
            else                                 v.x = T(v1.x + v2.x);
        }
        if constexpr (n >= 2)
        {
            if      (v1.y > T(0) && v2.y > T(0)) v.y = max(v1.y, v2.y);
            else if (v1.y < T(0) && v2.y < T(0)) v.y = min(v1.y, v2.y);
            else                                 v.y = T(v1.y + v2.y);
        }
        if constexpr (n >= 3)
        {
            if      (v1.z > T(0) && v2.z > T(0)) v.z = max(v1.z, v2.z);
            else if (v1.z < T(0) && v2.z < T(0)) v.z = min(v1.z, v2.z);
            else                                 v.z = T(v1.z + v2.z);
        }
        if constexpr (n >= 4)
        {
            if      (v1.w > T(0) && v2.w > T(0)) v.w = max(v1.w, v2.w);
            else if (v1.w < T(0) && v2.w < T(0)) v.w = min(v1.w, v2.w);
            else                                 v.w = T(v1.w + v2.w);
        }

        return v;
    }

    template <Signed T>
    forceinline vec2<T> rotateCW(const vec2<T> & v)
    {
        return vec2<T>{v.y, T(-v.x)};
    }

    template <Signed T>
    forceinline vec2<T> rotateCCW(const vec2<T> & v)
    {
        return vec2<T>{T(-v.y), v.x};
    }
}
