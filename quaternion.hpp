#pragma once

#include "matrix.hpp"

namespace qc::core {

    template <Floater T> struct quat;

    inline namespace types {

        using qc::core::quat;

        using fquat = quat< float>;
        using dquat = quat<double>;

    }

    template <Floater T> struct quat {

        vec3<T> a;
        T w;

        constexpr quat() noexcept;
        constexpr quat(const quat & q) noexcept = default;
        constexpr quat(quat && q) noexcept = default;

        template <Floater U> constexpr explicit quat(const quat<U> & q) noexcept;

        constexpr quat(const vec3<T> & a, T w) noexcept;
        constexpr explicit quat(const vec3<T> & v) noexcept;
        constexpr explicit quat(const vec4<T> & v) noexcept;

        quat & operator=(const quat & q) noexcept = default;
        quat & operator=(quat && q) noexcept = default;

    };

    template <Floater T> quat<T> & operator+=(quat<T> & q1, const quat<T> & q2);

    template <Floater T> quat<T> & operator-=(quat<T> & q1, const quat<T> & q2);

    template <Floater T> quat<T> & operator*=(quat<T> & q1, const quat<T> & q2);
    template <Floater T> quat<T> & operator*=(quat<T> &  q, T v);

    template <Floater T> quat<T> & operator/=(quat<T> & q1, const quat<T> & q2);

    template <Floater T> quat<T> operator+(const quat<T> & q);

    template <Floater T> quat<T> operator-(const quat<T> & q);

    template <Floater T> quat<T> operator+(const quat<T> & q1, const quat<T> & q2);

    template <Floater T> quat<T> operator-(const quat<T> & q1, const quat<T> & q2);

    template <Floater T> quat<T> operator*(const quat<T> & q1, const quat<T> & q2);
    template <Floater T> quat<T> operator*(const quat<T> &  q, T v);
    template <Floater T> quat<T> operator*(const T v, const quat<T> &  q);
    template <Floater T> vec3<T> operator*(const quat<T> &  q, const vec3<T> &  v);

    template <Floater T> quat<T> operator/(const quat<T> & q1, const quat<T> & q2);

    template <Floater T> bool operator==(const quat<T> & q1, const quat<T> & q2);

    template <Floater T> bool operator!=(const quat<T> & q1, const quat<T> & q2);

}

// INLINE IMPLEMENTATION ///////////////////////////////////////////////////////////////////////////////////////////////

namespace qc::core {

    template <Floater T>
    inline constexpr quat<T>::quat() noexcept :
        a(T(0.0)), w(T(1.0))
    {}

    template <Floater T>
    template <Floater U>
    inline constexpr quat<T>::quat(const quat<U> & q) noexcept :
        a(q.a), w(T(q.w))
    {}

    template <Floater T>
    inline constexpr quat<T>::quat(const vec3<T> & a, T w) noexcept :
        a(a), w(w)
    {}

    template <Floater T>
    inline constexpr quat<T>::quat(const vec3<T> & v) noexcept :
        a(v), w(T(0.0))
    {}

    template <Floater T>
    inline constexpr quat<T>::quat(const vec4<T> & v) noexcept :
        a(v), w(v.w)
    {}

    template <Floater T>
    inline quat<T> & operator+=(quat<T> & q1, const quat<T> & q2) {
        return q1 = q1 + q2;
    }

    template <Floater T>
    inline quat<T> & operator-=(quat<T> & q1, const quat<T> & q2) {
        return q1 = q1 - q2;
    }

    template <Floater T>
    inline quat<T> & operator*=(quat<T> & q1, const quat<T> & q2) {
        return q1 = q1 * q2;
    }

    template <Floater T>
    inline quat<T> & operator*=(quat<T> & q, T v) {
        return q = q * v;
    }

    template <Floater T>
    inline quat<T> & operator/=(quat<T> & q1, const quat<T> & q2) {
        return q1 = q1 / q2;
    }

    template <Floater T>
    inline quat<T> operator+(const quat<T> & q) {
        return {+q.a, +q.w};
    }

    template <Floater T>
    inline quat<T> operator-(const quat<T> & q) {
        return {-q.a, -q.w};
    }

    template <Floater T>
    inline quat<T> operator+(const quat<T> & q1, const quat<T> & q2) {
        return {q1.a + q2.a, q1.w + q2.w};
    }

    template <Floater T>
    inline quat<T> operator-(const quat<T> & q1, const quat<T> & q2) {
        return {q1.a - q2.a, q1.w - q2.w};
    }

    template <Floater T>
    inline quat<T> operator*(const quat<T> & q1, const quat<T> & q2) {
        return {
            q1.w * q2.a + q2.w * q1.a + cross(q1.a, q2.a),
            q1.w * q2.w - dot(q1.a, q2.a)
        };
    }

    template <Floater T>
    inline quat<T> operator*(const quat<T> & q, T v) {
        return {q.a * v, q.w * v};
    }

    template <Floater T>
    inline quat<T> operator*(T v, const quat<T> & q) {
        return {v * q.a, v * q.w};
    }

    template <Floater T>
    inline vec3<T> operator*(const quat<T> & q, const vec3<T> & v) {
        const vec3<T> t(T(2.0) * cross(q.a, v));
        return v + q.w * t + cross(q.a, t);
    }

    template <Floater T>
    inline quat<T> operator/(const quat<T> & q1, const quat<T> & q2) {
        return {q1.a * q2.w - q2.a * q1.w - cross(q1.a, q2.a), dot(q1, q2)};
    }

    template <Floater T>
    inline bool operator==(const quat<T> & q1, const quat<T> & q2) {
        return q1.a == q2.a && q1.w == q2.w;
    }

    template <Floater T>
    inline bool operator!=(const quat<T> & q1, const quat<T> & q2) {
        return q1.a != q2.a || q1.w != q2.w;
    }

}
