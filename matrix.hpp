#pragma once

// Column-major ordering
//
//  x1 x2 x3    00 03 06
//  y1 y2 y3    01 04 07
//  z1 z2 z3    02 05 08

#include "vector.hpp"

namespace qc::core {

    template <Floater T, int n> struct mat;

    inline namespace types {

        using qc::core::mat;

        template <Floater T> using mat2 = mat<T, 2>;
        template <Floater T> using mat3 = mat<T, 3>;
        template <Floater T> using mat4 = mat<T, 4>;

        template <int n> using fmat = mat< float, n>;
        template <int n> using dmat = mat<double, n>;

        using fmat2 = mat< float, 2>;
        using fmat3 = mat< float, 3>;
        using fmat4 = mat< float, 4>;
        using dmat2 = mat<double, 2>;
        using dmat3 = mat<double, 3>;
        using dmat4 = mat<double, 4>;

    }

    template <Floater T> struct mat<T, 2> {

        vec2<T> c1;
        vec2<T> c2;

        constexpr mat() noexcept;
        constexpr mat(const mat2<T> & m) noexcept = default;
        constexpr mat(mat2<T> && m) noexcept = default;

        constexpr mat(
            const vec2<T> & c1,
            const vec2<T> & c2
        ) noexcept;
        constexpr mat(
            T x1, T y1,
            T x2, T y2
        ) noexcept;

        template <Floater U> constexpr explicit mat(const mat2<U> & m) noexcept;
        template <Floater U> constexpr explicit mat(const mat3<U> & m) noexcept;
        template <Floater U> constexpr explicit mat(const mat4<U> & m) noexcept;

        mat2<T> & operator=(const mat2<T> & m) noexcept = default;
        mat2<T> & operator=(mat2<T> && m) noexcept = default;

        template <Floater U, int n> mat2<T> & operator=(const mat<U, n> & m) noexcept;

        vec2<T> & col(int i);
        const vec2<T> & col(int i) const;

        vec2<T> row(int i) const;

        template <int i> constexpr vec2<T> row() const noexcept;

        template <int i> constexpr const vec2<T> & col() const noexcept;

    };

    template <Floater T> struct mat<T, 3> {

        vec3<T> c1;
        vec3<T> c2;
        vec3<T> c3;

        constexpr mat() noexcept;
        constexpr mat(const mat3<T> & m) noexcept = default;
        constexpr mat(mat3<T> && m) noexcept = default;

        constexpr mat(
            const vec3<T> & c1,
            const vec3<T> & c2,
            const vec3<T> & c3
        ) noexcept;
        constexpr mat(
            T x1, T y1, T z1,
            T x2, T y2, T z2,
            T x3, T y3, T z3
        ) noexcept;

        template <Floater U> constexpr explicit mat(const mat2<U> & m) noexcept;
        template <Floater U> constexpr explicit mat(const mat3<U> & m) noexcept;
        template <Floater U> constexpr explicit mat(const mat4<U> & m) noexcept;

        mat3<T> & operator=(const mat3<T> & m) noexcept = default;
        mat3<T> & operator=(mat3<T> && m) noexcept = default;

        template <Floater U, int n> mat3<T> & operator=(const mat<U, n> & m) noexcept;

        vec3<T> & col(int i);
        const vec3<T> & col(int i) const;

        vec3<T> row(int i) const;

        template <int i> constexpr vec3<T> row() const noexcept;

        template <int i> constexpr const vec3<T> & col() const noexcept;

    };

    template <Floater T> struct mat<T, 4> {

        vec4<T> c1;
        vec4<T> c2;
        vec4<T> c3;
        vec4<T> c4;

        constexpr mat() noexcept;
        constexpr mat(const mat4<T> & m) noexcept = default;
        constexpr mat(mat4<T> && m) noexcept = default;

        constexpr mat(
            const vec4<T> & c1,
            const vec4<T> & c2,
            const vec4<T> & c3,
            const vec4<T> & c4
        ) noexcept;
        constexpr mat(
            T x1, T y1, T z1, T w1,
            T x2, T y2, T z2, T w2,
            T x3, T y3, T z3, T w3,
            T x4, T y4, T z4, T w4
        ) noexcept;

        template <Floater U> constexpr explicit mat(const mat2<U> & m) noexcept;
        template <Floater U> constexpr explicit mat(const mat3<U> & m) noexcept;
        template <Floater U> constexpr explicit mat(const mat4<U> & m) noexcept;

        mat4<T> & operator=(const mat4<T> & m) noexcept = default;
        mat4<T> & operator=(mat4<T> && m) noexcept = default;

        template <Floater U, int n> mat4<T> & operator=(const mat<U, n> & m) noexcept;

        vec4<T> & col(int i);
        const vec4<T> & col(int i) const;

        vec4<T> row(int i) const;

        template <int i> constexpr vec4<T> row() const noexcept;

        template <int i> constexpr const vec4<T> & col() const noexcept;

    };

    template <typename T, int n> mat<T, n> & operator+=(mat<T, n> & m, T v);
    template <typename T, int n> mat<T, n> & operator+=(mat<T, n> & m1, const mat<T, n> & m2);

    template <typename T, int n> mat<T, n> & operator-=(mat<T, n> & m, T v);
    template <typename T, int n> mat<T, n> & operator-=(mat<T, n> & m1, const mat<T, n> & m2);

    template <typename T, int n> mat<T, n> & operator*=(mat<T, n> & m, T v);
    template <typename T, int n> mat<T, n> & operator*=(mat<T, n> & m1, const mat<T, n> & m2);

    template <typename T, int n> mat<T, n> & operator/=(mat<T, n> & m, T v);

    template <typename T, int n> mat<T, n> operator+(const mat<T, n> & m);

    template <typename T, int n> mat<T, n> operator-(const mat<T, n> & m);

    template <typename T, int n> mat<T, n> operator+(const mat<T, n> & m1, const mat<T, n> & m2);
    template <typename T, int n> mat<T, n> operator+(const mat<T, n> & m, T v);
    template <typename T, int n> mat<T, n> operator+(T v, const mat<T, n> & m);

    template <typename T, int n> mat<T, n> operator-(const mat<T, n> & m1, const mat<T, n> & m2);
    template <typename T, int n> mat<T, n> operator-(const mat<T, n> & m, T v);
    template <typename T, int n> mat<T, n> operator-(T v, const mat<T, n> & m);

    template <typename T, int n, int o> mat<T, o> operator*(const mat<T, n> & m1, const mat<T, n> & m2);
    template <typename T, int n> mat<T, n> operator*(const mat<T, n> & m, T v);
    template <typename T, int n> mat<T, n> operator*(T v, const mat<T, n> & m);
    template <typename T, int n> vec<T, n> operator*(const mat<T, n> & m, const vec<T, n> & v);

    template <typename T, int n> mat<T, n> operator/(const mat<T, n> & m, T v);
    template <typename T, int n> mat<T, n> operator/(T v, const mat<T, n> & m);

    template <typename T, int n> bool operator==(const mat<T, n> & m1, const mat<T, n> & m2);

    template <typename T, int n> bool operator!=(const mat<T, n> & m1, const mat<T, n> & m2);

    //
    // ...
    //
    template <typename T, int n> constexpr mat<T, n> fullMat(T v);

    //
    // ...
    //
    template <typename T, int n> constexpr mat<T, n> nullMat();

}

// INLINE IMPLEMENTATION ///////////////////////////////////////////////////////////////////////////////////////////////

namespace qc::core {

    template <Floater T>
    inline constexpr mat<T, 2>::mat() noexcept :
        c1(T(1.0), T(0.0)),
        c2(T(0.0), T(1.0))
    {}

    template <Floater T>
    inline constexpr mat<T, 2>::mat(
        const vec2<T> & c1,
        const vec2<T> & c2
    ) noexcept :
        c1(c1),
        c2(c2)
    {}

    template <Floater T>
    inline constexpr mat<T, 2>::mat(
        T x1, T y1,
        T x2, T y2
    ) noexcept :
        c1(x1, y1),
        c2(x2, y2)
    {}

    template <Floater T>
    template <Floater U>
    inline constexpr mat<T, 2>::mat(const mat2<U> & m) noexcept :
        c1(m.c1),
        c2(m.c2)
    {}

    template <Floater T>
    template <Floater U>
    inline constexpr mat<T, 2>::mat(const mat3<U> & m) noexcept :
        c1(m.c1),
        c2(m.c2)
    {}

    template <Floater T>
    template <Floater U>
    constexpr mat<T, 2>::mat(const mat4<U> & m) noexcept :
        c1(m.c1),
        c2(m.c2)
    {}

    template <Floater T>
    template <Floater U, int n>
    inline mat2<T> & mat<T, 2>::operator=(const mat<U, n> & m) noexcept {
        if constexpr (n >= 1) c1 = m.c1; else c1 = vec2<T>(T(1.0), T(0.0));
        if constexpr (n >= 2) c2 = m.c2; else c2 = vec2<T>(T(0.0), T(1.0));

        return *this;
    }

    template <Floater T>
    inline vec2<T> & mat<T, 2>::col(int i) {
        return *(&c1 + i);
    }

    template <Floater T>
    inline const vec2<T> & mat<T, 2>::col(int i) const {
        return *(&c1 + i);
    }

    template <Floater T>
    inline vec2<T> mat<T, 2>::row(int i) const {
        return {c1[i], c2[i]};
    }

    template <Floater T>
    template <int i>
    inline constexpr const vec2<T> & mat<T, 2>::col() const noexcept {
        if constexpr (i == 0) return c1;
        if constexpr (i == 1) return c2;
    }

    template <Floater T>
    template <int i>
    inline constexpr vec2<T> mat<T, 2>::row() const noexcept {
        return {c1.at<i>(), c2.at<i>()};
    }

    template <Floater T>
    inline constexpr mat<T, 3>::mat() noexcept :
        c1(T(1.0), T(0.0), T(0.0)),
        c2(T(0.0), T(1.0), T(0.0)),
        c3(T(0.0), T(0.0), T(1.0))
    {}

    template <Floater T>
    inline constexpr mat<T, 3>::mat(
        const vec3<T> & c1,
        const vec3<T> & c2,
        const vec3<T> & c3
    ) noexcept :
        c1(c1),
        c2(c2),
        c3(c3)
    {}

    template <Floater T>
    inline constexpr mat<T, 3>::mat(
        T x1, T y1, T z1,
        T x2, T y2, T z2,
        T x3, T y3, T z3
    ) noexcept :
        c1(x1, y1, z1),
        c2(x2, y2, z2),
        c3(x3, y3, z3)
    {}

    template <Floater T>
    template <Floater U>
    inline constexpr mat<T, 3>::mat(const mat2<U> & m) noexcept :
        c1(m.c1),
        c2(m.c2),
        c3(T(0.0), T(0.0), T(1.0))
    {}

    template <Floater T>
    template <Floater U>
    inline constexpr mat<T, 3>::mat(const mat3<U> & m) noexcept :
        c1(m.c1),
        c2(m.c2),
        c3(m.c3)
    {}

    template <Floater T>
    template <Floater U>
    inline constexpr mat<T, 3>::mat(const mat4<U> & m) noexcept :
        c1(m.c1),
        c2(m.c2),
        c3(m.c3)
    {}

    template <Floater T>
    template <Floater U, int n>
    inline mat3<T> & mat<T, 3>::operator=(const mat<U, n> & m) noexcept {
        if constexpr (n >= 1) c1 = m.c1; else c1 = vec3<T>(T(1.0), T(0.0), T(0.0));
        if constexpr (n >= 2) c2 = m.c2; else c2 = vec3<T>(T(0.0), T(1.0), T(0.0));
        if constexpr (n >= 3) c3 = m.c3; else c3 = vec3<T>(T(0.0), T(0.0), T(1.0));

        return *this;
    }

    template <Floater T>
    inline vec3<T> & mat<T, 3>::col(int i) {
        return *(&c1 + i);
    }

    template <Floater T>
    inline const vec3<T> & mat<T, 3>::col(int i) const {
        return *(&c1 + i);
    }

    template <Floater T>
    inline vec3<T> mat<T, 3>::row(int i) const {
        return {c1[i], c2[i], c3[i]};
    }

    template <Floater T>
    template <int i>
    inline constexpr const vec3<T> & mat<T, 3>::col() const noexcept {
        if constexpr (i == 0) return c1;
        if constexpr (i == 1) return c2;
        if constexpr (i == 2) return c3;
    }

    template <Floater T>
    template <int i>
    inline constexpr vec3<T> mat<T, 3>::row() const noexcept {
        return {c1.at<i>(), c2.at<i>(), c3.at<i>()};
    }

    template <Floater T>
    inline constexpr mat<T, 4>::mat() noexcept :
        c1(T(1.0), T(0.0), T(0.0), T(0.0)),
        c2(T(0.0), T(1.0), T(0.0), T(0.0)),
        c3(T(0.0), T(0.0), T(1.0), T(0.0)),
        c4(T(0.0), T(0.0), T(0.0), T(1.0))
    {}

    template <Floater T>
    inline constexpr mat<T, 4>::mat(
        const vec4<T> & c1,
        const vec4<T> & c2,
        const vec4<T> & c3,
        const vec4<T> & c4
    ) noexcept :
        c1(c1),
        c2(c2),
        c3(c3),
        c4(c4)
    {}

    template <Floater T>
    inline constexpr mat<T, 4>::mat(
        T x1, T y1, T z1, T w1,
        T x2, T y2, T z2, T w2,
        T x3, T y3, T z3, T w3,
        T x4, T y4, T z4, T w4
    ) noexcept :
        c1(x1, y1, z1, w1),
        c2(x2, y2, z2, w2),
        c3(x3, y3, z3, w3),
        c4(x4, y4, z4, w4)
    {}

    template <Floater T>
    template <Floater U>
    inline constexpr mat<T, 4>::mat(const mat2<U> & m) noexcept :
        c1(m.c1),
        c2(m.c2),
        c3(T(0.0), T(0.0), T(1.0), T(0.0)),
        c4(T(0.0), T(0.0), T(0.0), T(1.0))
    {}

    template <Floater T>
    template <Floater U>
    inline constexpr mat<T, 4>::mat(const mat3<U> & m) noexcept :
        c1(m.c1),
        c2(m.c2),
        c3(m.c3),
        c4(T(0.0), T(0.0), T(0.0), T(1.0))
    {}

    template <Floater T>
    template <Floater U>
    inline constexpr mat<T, 4>::mat(const mat4<U> & m) noexcept :
        c1(m.c1),
        c2(m.c2),
        c3(m.c3),
        c4(m.c4)
    {}

    template <Floater T>
    template <Floater U, int n>
    inline mat4<T> & mat<T, 4>::operator=(const mat<U, n> & m) noexcept {
        if constexpr (n >= 1) c1 = m.c1; else c1 = vec4<T>(T(1.0), T(0.0), T(0.0), T(0.0));
        if constexpr (n >= 2) c2 = m.c2; else c2 = vec4<T>(T(0.0), T(1.0), T(0.0), T(0.0));
        if constexpr (n >= 3) c3 = m.c3; else c3 = vec4<T>(T(0.0), T(0.0), T(1.0), T(0.0));
        if constexpr (n >= 4) c4 = m.c4; else c4 = vec4<T>(T(0.0), T(0.0), T(0.0), T(1.0));

        return *this;
    }

    template <Floater T>
    inline vec4<T> & mat<T, 4>::col(int i) {
        return *(&c1 + i);
    }

    template <Floater T>
    inline const vec4<T> & mat<T, 4>::col(int i) const {
        return *(&c1 + i);
    }

    template <Floater T>
    inline vec4<T> mat<T, 4>::row(int i) const {
        return {c1[i], c2[i], c3[i], c4[i]};
    }

    template <Floater T>
    template <int i>
    inline constexpr const vec4<T> & mat<T, 4>::col() const noexcept {
        if constexpr (i == 0) return c1;
        if constexpr (i == 1) return c2;
        if constexpr (i == 2) return c3;
        if constexpr (i == 3) return c4;
    }

    template <Floater T>
    template <int i>
    inline constexpr vec4<T> mat<T, 4>::row() const noexcept {
        return {c1.at<i>(), c2.at<i>(), c3.at<i>(), c4.at<i>()};
    }

    template <Floater T, int n>
    inline mat<T, n> & operator+=(mat<T, n> & m, T v) {
        if constexpr (n >= 1) m.c1 += v;
        if constexpr (n >= 2) m.c2 += v;
        if constexpr (n >= 3) m.c3 += v;
        if constexpr (n >= 4) m.c4 += v;

        return m;
    }

    template <Floater T, int n>
    inline mat<T, n> & operator+=(mat<T, n> & m1, const mat<T, n> & m2) {
        if constexpr (n >= 1) m1.c1 += m2.c1;
        if constexpr (n >= 2) m1.c2 += m2.c2;
        if constexpr (n >= 3) m1.c3 += m2.c3;
        if constexpr (n >= 4) m1.c4 += m2.c4;

        return m1;
    }

    template <Floater T, int n>
    inline mat<T, n> & operator-=(mat<T, n> & m, T v) {
        if constexpr (n >= 1) m.c1 -= v;
        if constexpr (n >= 2) m.c2 -= v;
        if constexpr (n >= 3) m.c3 -= v;
        if constexpr (n >= 4) m.c4 -= v;

        return m;
    }

    template <Floater T, int n>
    inline mat<T, n> & operator-=(mat<T, n> & m1, const mat<T, n> & m2) {
        if constexpr (n >= 1) m1.c1 -= m2.c1;
        if constexpr (n >= 2) m1.c2 -= m2.c2;
        if constexpr (n >= 3) m1.c3 -= m2.c3;
        if constexpr (n >= 4) m1.c4 -= m2.c4;

        return m1;
    }

    template <Floater T, int n>
    inline mat<T, n> & operator*=(mat<T, n> & m, T v) {
        if constexpr (n >= 1) m.c1 *= v;
        if constexpr (n >= 2) m.c2 *= v;
        if constexpr (n >= 3) m.c3 *= v;
        if constexpr (n >= 4) m.c4 *= v;

        return m;
    }

    template <Floater T, int n>
    inline mat<T, n> & operator*=(mat<T, n> & m1, const mat<T, n> & m2) {
        vec<T, n> temp;
        if constexpr (n >= 1) {
            temp = m1.row<0>();
            if constexpr (n >= 1) m1.c1.x = dot(temp, m2.col<0>());
            if constexpr (n >= 2) m1.c2.x = dot(temp, m2.col<1>());
            if constexpr (n >= 3) m1.c3.x = dot(temp, m2.col<2>());
            if constexpr (n >= 4) m1.c4.x = dot(temp, m2.col<3>());
        }
        if constexpr (n >= 2) {
            temp = (m1.row<1>());
            if constexpr (n >= 1) m1.c1.y = dot(temp, m2.col<0>());
            if constexpr (n >= 2) m1.c2.y = dot(temp, m2.col<1>());
            if constexpr (n >= 3) m1.c3.y = dot(temp, m2.col<2>());
            if constexpr (n >= 4) m1.c4.y = dot(temp, m2.col<3>());
        }
        if constexpr (n >= 3) {
            temp = (m1.row<2>());
            if constexpr (n >= 1) m1.c1.z = dot(temp, m2.col<0>());
            if constexpr (n >= 2) m1.c2.z = dot(temp, m2.col<1>());
            if constexpr (n >= 3) m1.c3.z = dot(temp, m2.col<2>());
            if constexpr (n >= 4) m1.c4.z = dot(temp, m2.col<3>());
        }
        if constexpr (n >= 4) {
            temp = (m1.row<3>());
            if constexpr (n >= 1) m1.c1.w = dot(temp, m2.col<0>());
            if constexpr (n >= 2) m1.c2.w = dot(temp, m2.col<1>());
            if constexpr (n >= 3) m1.c3.w = dot(temp, m2.col<2>());
            if constexpr (n >= 4) m1.c4.w = dot(temp, m2.col<3>());
        }

        return m1;
    }

    template <Floater T, int n>
    inline mat<T, n> & operator/=(mat<T, n> & m, T v) {
        return m *= T(1.0) / v;
    }

    template <Floater T, int n>
    inline mat<T, n> operator+(const mat<T, n> & m) {
        return m;
    }

    template <Floater T, int n>
    inline mat<T, n> operator-(const mat<T, n> & m) {
        if constexpr (n == 2) return {-m.c1, -m.c2};
        if constexpr (n == 3) return {-m.c1, -m.c2, -m.c3};
        if constexpr (n == 4) return {-m.c1, -m.c2, -m.c3, -m.c4};
    }

    template <Floater T, int n>
    inline mat<T, n> operator+(const mat<T, n> & m1, const mat<T, n> & m2) {
        if constexpr (n == 2) return {m1.c1 + m2.c1, m1.c2 + m2.c2};
        if constexpr (n == 3) return {m1.c1 + m2.c1, m1.c2 + m2.c2, m1.c3 + m2.c3};
        if constexpr (n == 4) return {m1.c1 + m2.c1, m1.c2 + m2.c2, m1.c3 + m2.c3, m1.c4 + m2.c4};
    }

    template <Floater T, int n>
    inline mat<T, n> operator+(const mat<T, n> & m, T v) {
        if constexpr (n == 2) return {m.c1 + v, m.c2 + v};
        if constexpr (n == 3) return {m.c1 + v, m.c2 + v, m.c3 + v};
        if constexpr (n == 4) return {m.c1 + v, m.c2 + v, m.c3 + v, m.c4 + v};
    }

    template <Floater T, int n>
    inline mat<T, n> operator+(T v, const mat<T, n> & m) {
        return m + v;
    }

    template <Floater T, int n>
    inline mat<T, n> operator-(const mat<T, n> & m1, const mat<T, n> & m2) {
        if constexpr (n == 2) return {m1.c1 - m2.c1, m1.c2 - m2.c2};
        if constexpr (n == 3) return {m1.c1 - m2.c1, m1.c2 - m2.c2, m1.c3 - m2.c3};
        if constexpr (n == 4) return {m1.c1 - m2.c1, m1.c2 - m2.c2, m1.c3 - m2.c3, m1.c4 - m2.c4};
    }

    template <Floater T, int n>
    inline mat<T, n> operator-(const mat<T, n> & m, T v) {
        if constexpr (n == 2) return {m.c1 - v, m.c2 - v};
        if constexpr (n == 3) return {m.c1 - v, m.c2 - v, m.c3 - v};
        if constexpr (n == 4) return {m.c1 - v, m.c2 - v, m.c3 - v, m.c4 - v};
    }

    template <Floater T, int n>
    inline mat<T, n> operator-(T v, const mat<T, n> & m) {
        if constexpr (n == 2) return {v - m.c1, v - m.c2};
        if constexpr (n == 3) return {v - m.c1, v - m.c2, v - m.c3};
        if constexpr (n == 4) return {v - m.c1, v - m.c2, v - m.c3, v - m.c4};
    }

    template <Floater T, int n>
    inline mat<T, n> operator*(const mat<T, n> & m1, const mat<T, n> & m2) {
        if constexpr (n == 2) return {
            m1.c1.x * m2.c1.x + m1.c2.x * m2.c1.y,
            m1.c1.y * m2.c1.x + m1.c2.y * m2.c1.y,

            m1.c1.x * m2.c2.x + m1.c2.x * m2.c2.y,
            m1.c1.y * m2.c2.x + m1.c2.y * m2.c2.y
        };
        if constexpr (n == 3) return {
            m1.c1.x * m2.c1.x + m1.c2.x * m2.c1.y + m1.c3.x * m2.c1.z,
            m1.c1.y * m2.c1.x + m1.c2.y * m2.c1.y + m1.c3.y * m2.c1.z,
            m1.c1.z * m2.c1.x + m1.c2.z * m2.c1.y + m1.c3.z * m2.c1.z,

            m1.c1.x * m2.c2.x + m1.c2.x * m2.c2.y + m1.c3.x * m2.c2.z,
            m1.c1.y * m2.c2.x + m1.c2.y * m2.c2.y + m1.c3.y * m2.c2.z,
            m1.c1.z * m2.c2.x + m1.c2.z * m2.c2.y + m1.c3.z * m2.c2.z,

            m1.c1.x * m2.c3.x + m1.c2.x * m2.c3.y + m1.c3.x * m2.c3.z,
            m1.c1.y * m2.c3.x + m1.c2.y * m2.c3.y + m1.c3.y * m2.c3.z,
            m1.c1.z * m2.c3.x + m1.c2.z * m2.c3.y + m1.c3.z * m2.c3.z
        };
        if constexpr (n == 4) return {
            m1.c1.x * m2.c1.x + m1.c2.x * m2.c1.y + m1.c3.x * m2.c1.z + m1.c4.x * m2.c1.w,
            m1.c1.y * m2.c1.x + m1.c2.y * m2.c1.y + m1.c3.y * m2.c1.z + m1.c4.y * m2.c1.w,
            m1.c1.z * m2.c1.x + m1.c2.z * m2.c1.y + m1.c3.z * m2.c1.z + m1.c4.z * m2.c1.w,
            m1.c1.w * m2.c1.x + m1.c2.w * m2.c1.y + m1.c3.w * m2.c1.z + m1.c4.w * m2.c1.w,

            m1.c1.x * m2.c2.x + m1.c2.x * m2.c2.y + m1.c3.x * m2.c2.z + m1.c4.x * m2.c2.w,
            m1.c1.y * m2.c2.x + m1.c2.y * m2.c2.y + m1.c3.y * m2.c2.z + m1.c4.y * m2.c2.w,
            m1.c1.z * m2.c2.x + m1.c2.z * m2.c2.y + m1.c3.z * m2.c2.z + m1.c4.z * m2.c2.w,
            m1.c1.w * m2.c2.x + m1.c2.w * m2.c2.y + m1.c3.w * m2.c2.z + m1.c4.w * m2.c2.w,

            m1.c1.x * m2.c3.x + m1.c2.x * m2.c3.y + m1.c3.x * m2.c3.z + m1.c4.x * m2.c3.w,
            m1.c1.y * m2.c3.x + m1.c2.y * m2.c3.y + m1.c3.y * m2.c3.z + m1.c4.y * m2.c3.w,
            m1.c1.z * m2.c3.x + m1.c2.z * m2.c3.y + m1.c3.z * m2.c3.z + m1.c4.z * m2.c3.w,
            m1.c1.w * m2.c3.x + m1.c2.w * m2.c3.y + m1.c3.w * m2.c3.z + m1.c4.w * m2.c3.w,

            m1.c1.x * m2.c4.x + m1.c2.x * m2.c4.y + m1.c3.x * m2.c4.z + m1.c4.x * m2.c4.w,
            m1.c1.y * m2.c4.x + m1.c2.y * m2.c4.y + m1.c3.y * m2.c4.z + m1.c4.y * m2.c4.w,
            m1.c1.z * m2.c4.x + m1.c2.z * m2.c4.y + m1.c3.z * m2.c4.z + m1.c4.z * m2.c4.w,
            m1.c1.w * m2.c4.x + m1.c2.w * m2.c4.y + m1.c3.w * m2.c4.z + m1.c4.w * m2.c4.w
        };
    }

    template <Floater T, int n>
    inline mat<T, n> operator*(const mat<T, n> & m, T v) {
        if constexpr (n == 2) return {m.c1 * v, m.c2 * v};
        if constexpr (n == 3) return {m.c1 * v, m.c2 * v, m.c3 * v};
        if constexpr (n == 4) return {m.c1 * v, m.c2 * v, m.c3 * v, m.c4 * v};
    }

    template <Floater T, int n>
    inline mat<T, n> operator*(T v, const mat<T, n> & m) {
        return m * v;
    }

    template <Floater T, int n>
    inline vec<T, n> operator*(const mat<T, n> & m, const vec<T, n> & v) {
        if constexpr (n == 2) return {
            m.c1.x * v.x + m.c2.x * v.y,
            m.c1.y * v.x + m.c2.y * v.y
        };
        if constexpr (n == 3) return {
            m.c1.x * v.x + m.c2.x * v.y + m.c3.x * v.z,
            m.c1.y * v.x + m.c2.y * v.y + m.c3.y * v.z,
            m.c1.z * v.x + m.c2.z * v.y + m.c3.z * v.z
        };
        if constexpr (n == 4) return {
            m.c1.x * v.x + m.c2.x * v.y + m.c3.x * v.z + m.c4.x * v.w,
            m.c1.y * v.x + m.c2.y * v.y + m.c3.y * v.z + m.c4.y * v.w,
            m.c1.z * v.x + m.c2.z * v.y + m.c3.z * v.z + m.c4.z * v.w,
            m.c1.w * v.x + m.c2.w * v.y + m.c3.w * v.z + m.c4.w * v.w
        };
    }

    template <Floater T, int n>
    inline mat<T, n> operator/(const mat<T, n> & m, T v) {
        return m * (T(1.0) / v);
    }

    template <Floater T, int n>
    inline mat<T, n> operator/(T v, const mat<T, n> & m) {
        if constexpr (n == 2) return {v / m.c1, v / m.c2};
        if constexpr (n == 3) return {v / m.c1, v / m.c2, v / m.c3};
        if constexpr (n == 4) return {v / m.c1, v / m.c2, v / m.c3, v / m.c4};
    }

    template <Floater T, int n>
    inline bool operator==(const mat<T, n> & m1, const mat<T, n> & m2) {
        if constexpr (n == 2) return m1.c1 == m2.c1 && m1.c2 == m2.c2;
        if constexpr (n == 3) return m1.c1 == m2.c1 && m1.c2 == m2.c2 && m1.c3 == m2.c3;
        if constexpr (n == 4) return m1.c1 == m2.c1 && m1.c2 == m2.c2 && m1.c3 == m2.c3 && m1.c4 == m2.c4;
    }

    template <Floater T, int n>
    inline bool operator!=(const mat<T, n> & m1, const mat<T, n> & m2) {
        return !(m1 == m2);
    }

    template <Floater T, int n>
    inline constexpr mat<T, n> fullMat(T v) {
        if constexpr (n == 2) return {vec2<T>(v), vec2<T>(v)};
        if constexpr (n == 3) return {vec3<T>(v), vec3<T>(v), vec3<T>(v)};
        if constexpr (n == 4) return {vec4<T>(v), vec4<T>(v), vec4<T>(v), vec4<T>(v)};
    }

    template <Floater T, int n>
    inline constexpr mat<T, n> nullMat() {
        return fullMat<T, n>(T(0.0));
    }

}
