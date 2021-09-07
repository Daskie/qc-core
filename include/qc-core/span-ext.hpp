#pragma once
#pragma once

#include <iostream>

#include <qc-core/span.hpp>
#include <qc-core/vector-ext.hpp>

namespace qc
{
    //
    // ...
    //
    template <Numeric T, int n> std::ostream & operator<<(std::ostream & os, const span<T, n> & s);

    //
    // ...
    //
    template <Numeric T, int n> span<T, n> min(const span<T, n> & v1, T v2);
    template <Numeric T, int n> span<T, n> min(const span<T, n> & v1, const vec<T, n> & v2);

    //
    // ...
    //
    template <Numeric T, int n> span<T, n> max(const span<T, n> & v1, T v2);
    template <Numeric T, int n> span<T, n> max(const span<T, n> & v1, const vec<T, n> & v2);

    //
    // ...
    //
    template <Numeric T, int n> span<T, n> & minify(span<T, n> & v1, T v2);
    template <Numeric T, int n> span<T, n> & minify(span<T, n> & v1, const vec<T, n> & v2);

    //
    // ...
    //
    template <Numeric T, int n> span<T, n> & maxify(span<T, n> & v1, T v2);
    template <Numeric T, int n> span<T, n> & maxify(span<T, n> & v1, const vec<T, n> & v2);

    //
    // ...
    //
    template <Floating T, int n> span<stype<T>, n> round(const span<T, n> & v);
    template <Integral T, int n> span<T, n> round(const span<T, n> & v);

    //
    // ...
    //
    template <Numeric T, int n> vec<T, n> clamp(const vec<T, n> & v, const span<T, n> & span);
    template <Numeric T> T clamp(T v, const span1<T> & span);

    //
    // ...
    //
    template <Numeric T, int n> span<T, n> intersect(const span<T, n> & v1, const span<T, n> & v2);

    //
    // ...
    //
    template <Numeric T, int n> span<T, n> join(const span<T, n> & v1, const span<T, n> & v2);

    //
    // ...
    //
    template <Numeric T, int n> span<T, n> & joinify(span<T, n> & v1, const span<T, n> & v2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <Numeric T, int n>
    inline std::ostream & operator<<(std::ostream & os, const span<T, n> & s)
    {
        os << "[";
        if constexpr (n == 1) os << "[";
        os << s.min;
        if constexpr (n == 1) os << "][";
        os << s.max;
        if constexpr (n == 1) os << "]";
        os << "]";
        return os;
    }

    template <Numeric T, int n>
    inline span<T, n> min(const span<T, n> & v1, const T v2)
    {
        return {min(v1.min, v2), min(v1.max, v2)};
    }

    template <Numeric T, int n>
    inline span<T, n> min(const span<T, n> & v1, const vec<T, n> & v2)
    {
        return {min(v1.min, v2), min(v1.max, v2)};
    }

    template <Numeric T, int n>
    inline span<T, n> max(const span<T, n> & v1, const T v2)
    {
        return {max(v1.min, v2), max(v1.max, v2)};
    }

    template <Numeric T, int n>
    inline span<T, n> max(const span<T, n> & v1, const vec<T, n> & v2)
    {
        return {max(v1.min, v2), max(v1.max, v2)};
    }

    template <Numeric T, int n>
    inline span<T, n> & minify(span<T, n> & v1, const T v2)
    {
        minify(v1.min, v2);
        minify(v1.max, v2);
        return v1;
    }

    template <Numeric T, int n>
    inline span<T, n> & minify(span<T, n> & v1, const vec<T, n> & v2)
    {
        minify(v1.min, v2);
        minify(v1.max, v2);
        return v1;
    }

    template <Numeric T, int n>
    inline span<T, n> & maxify(span<T, n> & v1, const T v2)
    {
        maxify(v1.min, v2);
        maxify(v1.max, v2);
        return v1;
    }

    template <Numeric T, int n>
    inline span<T, n> & maxify(span<T, n> & v1, const vec<T, n> & v2)
    {
        maxify(v1.min, v2);
        maxify(v1.max, v2);
        return v1;
    }

    template <Floating T, int n>
    inline span<stype<T>, n> round(const span<T, n> & v)
    {
        return {round(v.min), round(v.max)};
    }

    template <Integral T, int n>
    inline span<T, n> round(const span<T, n> & v)
    {
        return v;
    }

    template <Numeric T, int n>
    inline vec<T, n> clamp(const vec<T, n> & v, const span<T, n> & span)
    {
        return clamp(v, span.min, span.max);
    }

    template <Numeric T>
    inline T clamp(const T v, const span1<T> & span)
    {
        return clamp(v, span.min, span.max);
    }

    template <Numeric T, int n>
    inline span<T, n> intersect(const span<T, n> & v1, const span<T, n> & v2)
    {
        if constexpr (n == 1) return {
            max(v1.min, v2.min),
            min(v1.max, v2.max)
        };
        if constexpr (n == 2) return {
            vec2<T>(max(v1.min.x, v2.min.x), max(v1.min.y, v2.min.y)),
            vec2<T>(min(v1.max.x, v2.max.x), min(v1.max.y, v2.max.y))
        };
        if constexpr (n == 3) return {
            vec3<T>(max(v1.min.x, v2.min.x), max(v1.min.y, v2.min.y), max(v1.min.z, v2.min.z)),
            vec3<T>(min(v1.max.x, v2.max.x), min(v1.max.y, v2.max.y), min(v1.max.z, v2.max.z))
        };
        if constexpr (n == 4) return {
            vec4<T>(max(v1.min.x, v2.min.x), max(v1.min.y, v2.min.y), max(v1.min.z, v2.min.z), max(v1.min.w, v2.min.w)),
            vec4<T>(min(v1.max.x, v2.max.x), min(v1.max.y, v2.max.y), min(v1.max.z, v2.max.z), min(v1.max.w, v2.max.w))
        };
    }

    template <Numeric T, int n>
    inline span<T, n> join(const span<T, n> & v1, const span<T, n> & v2)
    {
        return {min(v1.min, v2.min), max(v1.max, v2.max)};
    }

    template <Numeric T, int n>
    inline span<T, n> & joinify(span<T, n> & v1, const span<T, n> & v2)
    {
        minify(v1.min, v2.min);
        maxify(v1.max, v2.max);
        return v1;
    }
}
