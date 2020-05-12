#pragma once
#pragma once

#include <iostream>

#include "span.hpp"
#include "vector-func.hpp"

namespace qc::core {

    //==============================================================================
    // Stream Output
    //------------------------------------------------------------------------------

    template <Number T, int t_n> std::ostream & operator<<(std::ostream & os, const span<T, t_n> & s);

    //==============================================================================
    // clamp
    //------------------------------------------------------------------------------

    template <Number T, int t_n> Q_CX_ABLE vec<T, t_n> clamp(const vec<T, t_n> & v, const span<T, t_n> & span);
    template <Number T> Q_CX_ABLE T clamp(T v, const span1<T> & span);

    //==============================================================================
    // intersect
    //------------------------------------------------------------------------------

    template <Number T, int t_n> Q_CX_ABLE span<T, t_n> intersect(const span<T, t_n> & v1, const span<T, t_n> & v2);

    //==============================================================================
    // join
    //------------------------------------------------------------------------------

    template <Number T, int t_n> Q_CX_ABLE span<T, t_n> join(const span<T, t_n> & v1, const span<T, t_n> & v2);

    //==============================================================================
    // joinify
    //------------------------------------------------------------------------------

    template <Number T, int t_n> span<T, t_n> & joinify(span<T, t_n> & v1, const span<T, t_n> & v2);

}

// INLINE IMPLEMENTATION ///////////////////////////////////////////////////////////////////////////////////////////////

namespace qc::core {

    template <Number T, int t_n>
    inline std::ostream & operator<<(std::ostream & os, const span<T, t_n> & s) {
        os << "[";
        if constexpr (t_n == 1) os << "[";
        os << s.min;
        if constexpr (t_n == 1) os << "][";
        os << s.max;
        if constexpr (t_n == 1) os << "]";
        os << "]";
        return os;
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> clamp(const vec<T, t_n> & v, const span<T, t_n> & span) {
        return clamp(v, span.min, span.max);
    }

    template <Number T>
    inline Q_CX_ABLE T clamp(T v, const span1<T> & span) {
        return clamp(v, span.min, span.max);
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE span<T, t_n> intersect(const span<T, t_n> & v1, const span<T, t_n> & v2) {
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

    template <Number T, int t_n>
    inline Q_CX_ABLE span<T, t_n> join(const span<T, t_n> & v1, const span<T, t_n> & v2) {
        return {min(v1.min, v2.min), max(v1.max, v2.max)};
    }

    template <Number T, int t_n>
    inline span<T, t_n> & joinify(span<T, t_n> & v1, const span<T, t_n> & v2) {
        minify(v1.min, v2.min);
        maxify(v1.max, v2.max);
        return v1;
    }

}
