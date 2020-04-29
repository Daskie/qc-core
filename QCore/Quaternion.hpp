#pragma once

#include "Matrix.hpp"

namespace qc {

    template <typename T> struct quat;

    namespace types {

        using qc::quat;

        using fquat = quat< float>;
        using dquat = quat<double>;

    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // QUAT ------------------------------------------------------------------------------------------------------------

    template <typename T>
    struct quat {

        static_assert(is_floating_point_v<T>, "quat<T> must have floating point T");

        using type = T;

        vec3<T> a;
        T w;

        //--- constructors ---

        constexpr quat() noexcept;
        constexpr quat(const quat & q) noexcept = default;
        constexpr quat(quat && q) noexcept = default;

        template <typename U> constexpr explicit quat(const quat<U> & q) noexcept;

        constexpr quat(const vec3<T> & a, T w) noexcept;
        constexpr explicit quat(const vec3<T> & v) noexcept;
        constexpr explicit quat(const vec4<T> & v) noexcept;

        //--- assignment ---

        quat & operator=(const quat & q) noexcept = default;
        quat & operator=(quat && q) noexcept = default;

    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // QUAT FUNCTIONS --------------------------------------------------------------------------------------------------

    //--- arithmetic assignment ---

    template <typename T> quat<T> & operator+=(quat<T> & q1, const quat<T> & q2);

    template <typename T> quat<T> & operator-=(quat<T> & q1, const quat<T> & q2);

    template <typename T> quat<T> & operator*=(quat<T> & q1, const quat<T> & q2);
    template <typename T> quat<T> & operator*=(quat<T> &  q, T v);

    template <typename T> quat<T> & operator/=(quat<T> & q1, const quat<T> & q2);

    //--- arithmetic operators ---

    template <typename T> quat<T> operator+(const quat<T> & q);

    template <typename T> quat<T> operator-(const quat<T> & q);

    template <typename T> quat<T> operator+(const quat<T> & q1, const quat<T> & q2);

    template <typename T> quat<T> operator-(const quat<T> & q1, const quat<T> & q2);

    template <typename T> quat<T> operator*(const quat<T> & q1, const quat<T> & q2);
    template <typename T> quat<T> operator*(const quat<T> &  q, T v);
    template <typename T> quat<T> operator*(const T v, const quat<T> &  q);
    template <typename T> vec3<T> operator*(const quat<T> &  q, const vec3<T> &  v);

    template <typename T> quat<T> operator/(const quat<T> & q1, const quat<T> & q2);

    //--- comparison operators ---

    template <typename T> bool operator==(const quat<T> & q1, const quat<T> & q2);

    template <typename T> bool operator!=(const quat<T> & q1, const quat<T> & q2);

}

// INLINE IMPLEMENTATION ///////////////////////////////////////////////////////////////////////////////////////////////

namespace qc {

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // QUAT IMPLEMENTATION ---------------------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    // Constructors   


    template <typename T>
    constexpr quat<T>::quat() noexcept :
        a(T(0.0)), w(T(1.0))
    {}

    template <typename T> template <typename U>
    constexpr quat<T>::quat(const quat<U> & q) noexcept :
        a(q.a), w(T(q.w))
    {}

    template <typename T>
    constexpr quat<T>::quat(const vec3<T> & a, T w) noexcept :
        a(a), w(w)
    {}

    template <typename T>
    constexpr quat<T>::quat(const vec3<T> & v) noexcept :
        a(v), w(T(0.0))
    {}

    template <typename T>
    constexpr quat<T>::quat(const vec4<T> & v) noexcept :
        a(v), w(v.w)
    {}

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // QUAT FUNCTIONS IMPLEMENTATION -----------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    // Arithmetic Assignment

    template <typename T>
    inline quat<T> & operator+=(quat<T> & q1, const quat<T> & q2) {
        return q1 = q1 + q2;
    }

    template <typename T>
    inline quat<T> & operator-=(quat<T> & q1, const quat<T> & q2) {
        return q1 = q1 - q2;
    }

    template <typename T>
    inline quat<T> & operator*=(quat<T> & q1, const quat<T> & q2) {
        return q1 = q1 * q2;
    }

    template <typename T>
    inline quat<T> & operator*=(quat<T> & q, T v) {
        return q = q * v;
    }

    template <typename T>
    inline quat<T> & operator/=(quat<T> & q1, const quat<T> & q2) {
        return q1 = q1 / q2;
    }

    //------------------------------------------------------------------------------
    // Arithmetic Operators

    template <typename T>
    inline quat<T> operator+(const quat<T> & q) {
        return {+q.a, +q.w};
    }

    template <typename T>
    inline quat<T> operator-(const quat<T> & q) {
        return {-q.a, -q.w};
    }

    template <typename T>
    inline quat<T> operator+(const quat<T> & q1, const quat<T> & q2) {
        return {q1.a + q2.a, q1.w + q2.w};
    }

    template <typename T>
    inline quat<T> operator-(const quat<T> & q1, const quat<T> & q2) {
        return {q1.a - q2.a, q1.w - q2.w};
    }

    template <typename T>
    inline quat<T> operator*(const quat<T> & q1, const quat<T> & q2) {
        return {
            q1.w * q2.a + q2.w * q1.a + cross(q1.a, q2.a),
            q1.w * q2.w - dot(q1.a, q2.a)
        };
    }

    template <typename T>
    inline quat<T> operator*(const quat<T> & q, T v) {
        return {q.a * v, q.w * v};
    }

    template <typename T>
    inline quat<T> operator*(T v, const quat<T> & q) {
        return {v * q.a, v * q.w};
    }

    template <typename T>
    inline vec3<T> operator*(const quat<T> & q, const vec3<T> & v) {
        vec3<T> t(T(2.0) * cross(q.a, v));
        return v + q.w * t + cross(q.a, t);
    }

    template <typename T>
    inline quat<T> operator/(const quat<T> & q1, const quat<T> & q2) {
        return {q1.a * q2.w - q2.a * q1.w - cross(q1.a, q2.a), dot(q1, q2)};
    }

    //------------------------------------------------------------------------------
    // Comparison Operators

    template <typename T>
    inline bool operator==(const quat<T> & q1, const quat<T> & q2) {
        return q1.a == q2.a && q1.w == q2.w;
    }

    template <typename T>
    inline bool operator!=(const quat<T> & q1, const quat<T> & q2) {
        return q1.a != q2.a || q1.w != q2.w;
    }

}
