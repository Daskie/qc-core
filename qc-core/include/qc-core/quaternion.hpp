#pragma once

#include <qc-core/matrix.hpp>

namespace qc
{
    template <Floating T> struct quat;

    inline namespace primitives
    {
        using qc::quat;

        using fquat = quat<float>;
        using dquat = quat<double>;

        template <typename T> concept Quaternion = Same<T, quat<typename T::Type>>;
    }

    template <Floating T>
    struct quat
    {
        using Type = T;

        SERIALIZABLE(2);

        vec3<T> a{};
        T w{T(1.0)};

        constexpr quat() = default;
        template <FloatingSubOf<T> U> constexpr quat(const vec3<U> & a, U w);
        template <FloatingSubOf<T> U> constexpr explicit quat(const vec3<U> & v);
        template <FloatingSubOf<T> U> constexpr explicit quat(const vec4<U> & v);
        template <Floating U> constexpr explicit quat(const quat<U> & q);

        constexpr quat(const quat & q) = default;
        constexpr quat(quat && q) = default;

        quat & operator=(const quat & q) = default;
        quat & operator=(quat && q) = default;

        template <FloatingSubOf<T> U> quat & operator=(const quat<U> & q);

        ~quat() = default;

        nodisc constexpr explicit operator bool() const;

        nodisc constexpr bool operator==(const quat &) const = default;
    };

    template <Floating T1, FloatingSubOf<T1> T2> quat<T1> & operator+=(quat<T1> & q1, const quat<T2> & q2);

    template <Floating T1, FloatingSubOf<T1> T2> quat<T1> & operator-=(quat<T1> & q1, const quat<T2> & q2);

    template <Floating T1, FloatingSubOf<T1> T2> quat<T1> & operator*=(quat<T1> & q1, const quat<T2> & q2);
    template <Floating T1, FloatingSubOf<T1> T2> quat<T1> & operator*=(quat<T1> & q, T2 v);
    template <Floating T1, FloatingSubOf<T1> T2> vec3<T1> & operator*=(vec3<T1> & v, const quat<T2> & q); // THIS IS EQUIVALENT TO v = q * v !!!

    template <Floating T1, FloatingSubOf<T1> T2> quat<T1> & operator/=(quat<T1> & q1, const quat<T2> & q2);

    template <Floating T> nodisc constexpr quat<T> operator+(const quat<T> & q);

    template <Floating T> nodisc constexpr quat<T> operator-(const quat<T> & q);

    template <Floating T1, Floating T2> nodisc constexpr quat<LargerOf<T1, T2>> operator+(const quat<T1> & q1, const quat<T2> & q2);

    template <Floating T1, Floating T2> nodisc constexpr quat<LargerOf<T1, T2>> operator-(const quat<T1> & q1, const quat<T2> & q2);

    template <Floating T1, Floating T2> nodisc constexpr quat<LargerOf<T1, T2>> operator*(const quat<T1> & q1, const quat<T2> & q2);
    template <Floating T1, Floating T2> nodisc constexpr quat<LargerOf<T1, T2>> operator*(const quat<T1> & q, T2 v);
    template <Floating T1, Floating T2> nodisc constexpr quat<LargerOf<T1, T2>> operator*(T1 v, const quat<T2> & q);
    template <Floating T1, Floating T2> nodisc constexpr vec3<LargerOf<T1, T2>> operator*(const quat<T1> & q, vec3<T2> v);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <Floating T>
    template <FloatingSubOf<T> U>
    forceinline constexpr quat<T>::quat(const vec3<U> & a_, const U w_) :
        a{a_},
        w{w_}
    {}

    template <Floating T>
    template <FloatingSubOf<T> U>
    forceinline constexpr quat<T>::quat(const vec3<U> & v) :
        a{v},
        w{T(0.0)}
    {}

    template <Floating T>
    template <FloatingSubOf<T> U>
    forceinline constexpr quat<T>::quat(const vec4<U> & v) :
        a{v},
        w{v.w}
    {}

    template <Floating T>
    template <Floating U>
    forceinline constexpr quat<T>::quat(const quat<U> & q) :
        a{q.a},
        w{T(q.w)}
    {}

    template <Floating T>
    template <FloatingSubOf<T> U>
    forceinline quat<T> & quat<T>::operator=(const quat<U> & q)
    {
        a = q.a;
        w = q.w;
        return *this;
    }

    template <Floating T>
    forceinline constexpr quat<T>::operator bool() const
    {
        return !a && w == T(1.0);
    }

    template <Floating T1, FloatingSubOf<T1> T2>
    forceinline quat<T1> & operator+=(quat<T1> & q1, const quat<T2> & q2)
    {
        return q1 = q1 + q2;
    }

    template <Floating T1, FloatingSubOf<T1> T2>
    forceinline quat<T1> & operator-=(quat<T1> & q1, const quat<T2> & q2)
    {
        return q1 = q1 - q2;
    }

    template <Floating T1, FloatingSubOf<T1> T2>
    forceinline quat<T1> & operator*=(quat<T1> & q1, const quat<T2> & q2)
    {
        return q1 = q1 * q2;
    }

    template <Floating T1, FloatingSubOf<T1> T2>
    forceinline quat<T1> & operator*=(quat<T1> & q, const T2 v)
    {
        return q = q * v;
    }

    template <Floating T1, FloatingSubOf<T1> T2>
    forceinline vec3<T1> & operator*=(vec3<T1> & v, const quat<T2> & q)
    {
        return v = q * v;
    }

    template <Floating T1, FloatingSubOf<T1> T2>
    forceinline quat<T1> & operator/=(quat<T1> & q1, const quat<T2> & q2)
    {
        return q1 = q1 / q2;
    }

    template <Floating T>
    forceinline constexpr quat<T> operator+(const quat<T> & q)
    {
        return {+q.a, +q.w};
    }

    template <Floating T>
    forceinline constexpr quat<T> operator-(const quat<T> & q)
    {
        return {-q.a, -q.w};
    }

    template <Floating T1, Floating T2>
    forceinline constexpr quat<LargerOf<T1, T2>> operator+(const quat<T1> & q1, const quat<T2> & q2)
    {
        return {q1.a + q2.a, q1.w + q2.w};
    }

    template <Floating T1, Floating T2>
    forceinline constexpr quat<LargerOf<T1, T2>> operator-(const quat<T1> & q1, const quat<T2> & q2)
    {
        return {q1.a - q2.a, q1.w - q2.w};
    }

    template <Floating T1, Floating T2>
    forceinline constexpr quat<LargerOf<T1, T2>> operator*(const quat<T1> & q1, const quat<T2> & q2)
    {
        return {
            q1.w * q2.a + q2.w * q1.a + cross(q1.a, q2.a),
            q1.w * q2.w - dot(q1.a, q2.a)};
    }

    template <Floating T1, Floating T2>
    forceinline constexpr quat<LargerOf<T1, T2>> operator*(const quat<T1> & q, const T2 v)
    {
        return {q.a * v, q.w * v};
    }

    template <Floating T1, Floating T2>
    forceinline constexpr quat<LargerOf<T1, T2>> operator*(const T1 v, const quat<T2> & q)
    {
        return {v * q.a, v * q.w};
    }

    template <Floating T1, Floating T2>
    forceinline constexpr vec3<LargerOf<T1, T2>> operator*(const quat<T1> & q, const vec3<T2> v)
    {
        return v + cross(T1(2.0) * q.a, cross(q.a, v) + q.w * v);
    }
}
