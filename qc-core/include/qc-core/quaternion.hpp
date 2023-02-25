#pragma once

#include <qc-core/matrix.hpp>

namespace qc
{
    template <Floating T> struct quat;

    inline namespace types
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

        vec3<T> a{};
        T w{T(1.0)};

        constexpr quat() = default;
        template <Floating U> constexpr explicit quat(const quat<U> & q);
        constexpr quat(vec3<T> a, T w);
        constexpr explicit quat(vec3<T> v);
        constexpr explicit quat(vec4<T> v);

        constexpr quat(const quat & q) = default;
        constexpr quat(quat && q) = default;

        quat & operator=(const quat & q) = default;
        quat & operator=(quat && q) = default;

        ~quat() = default;

        nodisc constexpr explicit operator bool() const;

        nodisc constexpr bool operator==(const quat &) const = default;
    };

    template <Floating T> quat<T> & operator+=(quat<T> & q1, const quat<T> & q2);

    template <Floating T> quat<T> & operator-=(quat<T> & q1, const quat<T> & q2);

    template <Floating T> quat<T> & operator*=(quat<T> & q1, const quat<T> & q2);
    template <Floating T> quat<T> & operator*=(quat<T> & q, T v);
    template <Floating T> vec3<T> & operator*=(vec3<T> & v, const quat<T> & q); // THIS IS EQUIVALENT TO v = q * v !!!

    template <Floating T> quat<T> & operator/=(quat<T> & q1, const quat<T> & q2);

    template <Floating T> nodisc constexpr quat<T> operator+(const quat<T> & q);

    template <Floating T> nodisc constexpr quat<T> operator-(const quat<T> & q);

    template <Floating T> nodisc constexpr quat<T> operator+(const quat<T> & q1, const quat<T> & q2);

    template <Floating T> nodisc constexpr quat<T> operator-(const quat<T> & q1, const quat<T> & q2);

    template <Floating T> nodisc constexpr quat<T> operator*(const quat<T> & q1, const quat<T> & q2);
    template <Floating T> nodisc constexpr quat<T> operator*(const quat<T> & q, T v);
    template <Floating T> nodisc constexpr quat<T> operator*(T v, const quat<T> & q);
    template <Floating T> nodisc constexpr vec3<T> operator*(const quat<T> & q, vec3<T> v);

    template <Floating T> nodisc constexpr quat<T> operator/(const quat<T> & q1, const quat<T> & q2);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <Floating T>
    template <Floating U>
    forceinline constexpr quat<T>::quat(const quat<U> & q) :
        a(q.a), w(T(q.w))
    {}

    template <Floating T>
    forceinline constexpr quat<T>::quat(const vec3<T> a, T w) :
        a(a), w(w)
    {}

    template <Floating T>
    forceinline constexpr quat<T>::quat(const vec3<T> v) :
        a(v), w(T(0.0))
    {}

    template <Floating T>
    forceinline constexpr quat<T>::quat(const vec4<T> v) :
        a(v), w(v.w)
    {}

    template <Floating T>
    forceinline constexpr quat<T>::operator bool() const
    {
        return !a && w == T(1.0);
    }

    template <Floating T>
    forceinline quat<T> & operator+=(quat<T> & q1, const quat<T> & q2)
    {
        return q1 = q1 + q2;
    }

    template <Floating T>
    forceinline quat<T> & operator-=(quat<T> & q1, const quat<T> & q2)
    {
        return q1 = q1 - q2;
    }

    template <Floating T>
    forceinline quat<T> & operator*=(quat<T> & q1, const quat<T> & q2)
    {
        return q1 = q1 * q2;
    }

    template <Floating T>
    forceinline quat<T> & operator*=(quat<T> & q, const T v)
    {
        return q = q * v;
    }

    template <Floating T>
    forceinline vec3<T> & operator*=(vec3<T> & v, const quat<T> & q)
    {
        return v = q * v;
    }

    template <Floating T>
    forceinline quat<T> & operator/=(quat<T> & q1, const quat<T> & q2)
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

    template <Floating T>
    forceinline constexpr quat<T> operator+(const quat<T> & q1, const quat<T> & q2)
    {
        return {q1.a + q2.a, q1.w + q2.w};
    }

    template <Floating T>
    forceinline constexpr quat<T> operator-(const quat<T> & q1, const quat<T> & q2)
    {
        return {q1.a - q2.a, q1.w - q2.w};
    }

    template <Floating T>
    forceinline constexpr quat<T> operator*(const quat<T> & q1, const quat<T> & q2)
    {
        return {
            q1.w * q2.a + q2.w * q1.a + cross(q1.a, q2.a),
            q1.w * q2.w - dot(q1.a, q2.a)};
    }

    template <Floating T>
    forceinline constexpr quat<T> operator*(const quat<T> & q, const T v)
    {
        return {q.a * v, q.w * v};
    }

    template <Floating T>
    forceinline constexpr quat<T> operator*(const T v, const quat<T> & q)
    {
        return {v * q.a, v * q.w};
    }

    template <Floating T>
    forceinline constexpr vec3<T> operator*(const quat<T> & q, const vec3<T> v)
    {
        return v + cross(T(2.0) * q.a, cross(q.a, v) + q.w * v);
    }

    template <Floating T>
    forceinline constexpr quat<T> operator/(const quat<T> & q1, const quat<T> & q2)
    {
        return {q1.a * q2.w - q2.a * q1.w - cross(q1.a, q2.a), dot(q1, q2)};
    }
}
