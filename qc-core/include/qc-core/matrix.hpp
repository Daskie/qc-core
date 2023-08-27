#pragma once

//
// Column-major ordering
//
//  x1 x2 x3    00 03 06
//  y1 y2 y3    01 04 07
//  z1 z2 z3    02 05 08
//

#include <qc-core/vector.hpp>

namespace qc
{
    template <Floating T, u32 n> struct mat;

    inline namespace primitives
    {
        using qc::mat;

        template <Floating T> using mat2 = mat<T, 2>;
        template <Floating T> using mat3 = mat<T, 3>;
        template <Floating T> using mat4 = mat<T, 4>;

        template <u32 n> using fmat = mat<float, n>;
        template <u32 n> using dmat = mat<double, n>;

        using fmat2 = mat<float, 2>;
        using fmat3 = mat<float, 3>;
        using fmat4 = mat<float, 4>;
        using dmat2 = mat<double, 2>;
        using dmat3 = mat<double, 3>;
        using dmat4 = mat<double, 4>;
    }

    inline namespace types
    {
        template <typename T> concept Matrix = Same<T, mat<typename T::Type, T::n>>;

        template <typename T> concept Matrix2 = Matrix<T> && T::n == 2;
        template <typename T> concept Matrix3 = Matrix<T> && T::n == 3;
        template <typename T> concept Matrix4 = Matrix<T> && T::n == 4;
    }

    template <Floating T>
    struct mat<T, 2>
    {
        SERIALIZABLE(2);

        using Type = T;
        static constexpr u32 n{2};

        vec2<T> c1{T(1.0), T(0.0)};
        vec2<T> c2{T(0.0), T(1.0)};

        constexpr mat() = default;
        template <InclusiveFloatingSubOf<T> U> constexpr mat(const vec2<U> & c1, const vec2<U> & c2);
        template <InclusiveFloatingSubOf<T> U> constexpr mat(
            U x1, U y1,
            U x2, U y2);
        template <ExclusiveFloatingSubOf<T> U> constexpr mat(const mat2<U> & m);
        template <ExclusiveFloatingSuperOf<T> U> constexpr explicit mat(const mat2<U> & m);
        template <Floating U> constexpr explicit mat(const mat3<U> & m);
        template <Floating U> constexpr explicit mat(const mat4<U> & m);

        constexpr mat(const mat & m) = default;
        constexpr mat(mat && m) = default;

        mat & operator=(const mat & m) = default;
        mat & operator=(mat && m) = default;

        template <ExclusiveFloatingSubOf<T> U> mat & operator=(const mat2<U> & m);

        ~mat() = default;

        nodisc vec2<T> & col(u32 i);
        nodisc vec2<T> col(u32 i) const;

        nodisc vec2<T> row(u32 i) const;

        template <u32 i> nodisc constexpr vec2<T> row() const;

        template <u32 i> nodisc constexpr vec2<T> col() const;

        nodisc constexpr bool operator==(const mat &) const = default;
    };

    template <Floating T>
    struct mat<T, 3>
    {
        using Type = T;
        static constexpr u32 n{3u};

        SERIALIZABLE(3);

        vec3<T> c1{T(1.0), T(0.0), T(0.0)};
        vec3<T> c2{T(0.0), T(1.0), T(0.0)};
        vec3<T> c3{T(0.0), T(0.0), T(1.0)};

        constexpr mat() = default;
        template <InclusiveFloatingSubOf<T> U> constexpr mat(const vec3<U> & c1, const vec3<U> & c2, const vec3<U> & c3);
        template <InclusiveFloatingSubOf<T> U> constexpr mat(
            U x1, U y1, U z1,
            U x2, U y2, U z2,
            U x3, U y3, U z3);
        template <Floating U> constexpr explicit mat(const mat2<U> & m);
        template <ExclusiveFloatingSubOf<T> U> constexpr mat(const mat3<U> & m);
        template <ExclusiveFloatingSuperOf<T> U> constexpr explicit mat(const mat3<U> & m);
        template <Floating U> constexpr explicit mat(const mat4<U> & m);

        constexpr mat(const mat & m) = default;
        constexpr mat(mat && m) = default;

        mat & operator=(const mat & m) = default;
        mat & operator=(mat && m) = default;

        template <ExclusiveFloatingSubOf<T> U> mat & operator=(const mat3<U> & m);

        ~mat() = default;

        nodisc vec3<T> & col(u32 i);
        nodisc vec3<T> col(u32 i) const;

        nodisc vec3<T> row(u32 i) const;

        template <u32 i> nodisc constexpr vec3<T> row() const;

        template <u32 i> nodisc constexpr vec3<T> col() const;

        nodisc constexpr bool operator==(const mat &) const = default;
    };

    template <Floating T>
    struct mat<T, 4>
    {
        using Type = T;
        static constexpr u32 n{4u};

        SERIALIZABLE(4);

        vec4<T> c1{T(1.0), T(0.0), T(0.0), T(0.0)};
        vec4<T> c2{T(0.0), T(1.0), T(0.0), T(0.0)};
        vec4<T> c3{T(0.0), T(0.0), T(1.0), T(0.0)};
        vec4<T> c4{T(0.0), T(0.0), T(0.0), T(1.0)};

        constexpr mat() = default;
        template <InclusiveFloatingSubOf<T> U> constexpr mat(const vec4<U> & c1, const vec4<U> & c2, const vec4<U> & c3, const vec4<U> & c4);
        template <InclusiveFloatingSubOf<T> U> constexpr mat(
            U x1, U y1, U z1, U w1,
            U x2, U y2, U z2, U w2,
            U x3, U y3, U z3, U w3,
            U x4, U y4, U z4, U w4);
        template <Floating U> constexpr explicit mat(const mat2<U> & m);
        template <Floating U> constexpr explicit mat(const mat3<U> & m);
        template <ExclusiveFloatingSubOf<T> U> constexpr mat(const mat4<U> & m);
        template <ExclusiveFloatingSuperOf<T> U> constexpr explicit mat(const mat4<U> & m);

        constexpr mat(const mat & m) = default;
        constexpr mat(mat && m) = default;

        mat & operator=(const mat & m) = default;
        mat & operator=(mat && m) = default;

        template <ExclusiveFloatingSubOf<T> U> mat & operator=(const mat4<U> & m);

        ~mat() = default;

        nodisc vec4<T> & col(u32 i);
        nodisc vec4<T> col(u32 i) const;

        nodisc vec4<T> row(u32 i) const;

        template <u32 i> nodisc constexpr vec4<T> row() const;

        template <u32 i> nodisc constexpr vec4<T> col() const;

        nodisc constexpr bool operator==(const mat &) const = default;
    };

    template <Floating T1, InclusiveFloatingSubOf<T1> T2, u32 n> mat<T1, n> & operator+=(mat<T1, n> & m, T2 v);
    template <Floating T1, InclusiveFloatingSubOf<T1> T2, u32 n> mat<T1, n> & operator+=(mat<T1, n> & m1, const mat<T2, n> & m2);

    template <Floating T1, InclusiveFloatingSubOf<T1> T2, u32 n> mat<T1, n> & operator-=(mat<T1, n> & m, T2 v);
    template <Floating T1, InclusiveFloatingSubOf<T1> T2, u32 n> mat<T1, n> & operator-=(mat<T1, n> & m1, const mat<T2, n> & m2);

    template <Floating T1, InclusiveFloatingSubOf<T1> T2, u32 n> mat<T1, n> & operator*=(mat<T1, n> & m, T2 v);
    template <Floating T1, InclusiveFloatingSubOf<T1> T2, u32 n> mat<T1, n> & operator*=(mat<T1, n> & m1, const mat<T2, n> & m2); // THIS IS EQUIVALENT TO m1 = m2 * m1 !!!
    template <Floating T1, InclusiveFloatingSubOf<T1> T2, u32 n> vec<T1, n> & operator*=(vec<T1, n> & v, const mat<T2, n> & m); // THIS IS EQUIVALENT TO v = m * v !!!

    template <Floating T1, InclusiveFloatingSubOf<T1> T2, u32 n> mat<T1, n> & operator/=(mat<T1, n> & m, T2 v);

    template <typename T, u32 n> nodisc constexpr mat<T, n> operator+(const mat<T, n> & m);

    template <typename T, u32 n> nodisc constexpr mat<T, n> operator-(const mat<T, n> & m);

    template <Floating T1, Floating T2, u32 n> nodisc constexpr mat<LargerOf<T1, T2>, n> operator+(const mat<T1, n> & m1, const mat<T2, n> & m2);
    template <Floating T1, Floating T2, u32 n> nodisc constexpr mat<LargerOf<T1, T2>, n> operator+(const mat<T1, n> & m, T2 v);
    template <Floating T1, Floating T2, u32 n> nodisc constexpr mat<LargerOf<T1, T2>, n> operator+(T1 v, const mat<T2, n> & m);

    template <Floating T1, Floating T2, u32 n> nodisc constexpr mat<LargerOf<T1, T2>, n> operator-(const mat<T1, n> & m1, const mat<T2, n> & m2);
    template <Floating T1, Floating T2, u32 n> nodisc constexpr mat<LargerOf<T1, T2>, n> operator-(const mat<T1, n> & m, T2 v);
    template <Floating T1, Floating T2, u32 n> nodisc constexpr mat<LargerOf<T1, T2>, n> operator-(T1 v, const mat<T2, n> & m);

    template <Floating T1, Floating T2, u32 n> nodisc constexpr mat<LargerOf<T1, T2>, n> operator*(const mat<T1, n> & m1, const mat<T2, n> & m2);
    template <Floating T1, Floating T2, u32 n> nodisc constexpr mat<LargerOf<T1, T2>, n> operator*(const mat<T1, n> & m, T2 v);
    template <Floating T1, Floating T2, u32 n> nodisc constexpr mat<LargerOf<T1, T2>, n> operator*(T1 v, const mat<T2, n> & m);
    template <Floating T1, Floating T2, u32 n> nodisc constexpr vec<LargerOf<T1, T2>, n> operator*(const mat<T1, n> & m, const vec<T2, n> & v);

    template <Floating T1, Floating T2, u32 n> nodisc constexpr mat<LargerOf<T1, T2>, n> operator/(const mat<T1, n> & m, T2 v);
    template <Floating T1, Floating T2, u32 n> nodisc constexpr mat<LargerOf<T1, T2>, n> operator/(T1 v, const mat<T2, n> & m);

    //
    // ...
    //
    template <Floating T, u32 n> nodisc constexpr mat<T, n> fullMat(T v);

    //
    // ...
    //
    template <Floating T, u32 n> nodisc constexpr mat<T, n> nullMat();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <Floating T>
    template <InclusiveFloatingSubOf<T> U>
    finline constexpr mat<T, 2>::mat(const vec2<U> & c1_, const vec2<U> & c2_) :
        c1{c1_},
        c2{c2_}
    {}

    template <Floating T>
    template <InclusiveFloatingSubOf<T> U>
    finline constexpr mat<T, 2>::mat(
        const U x1, const U y1,
        const U x2, const U y2
    ) :
        c1{x1, y1},
        c2{x2, y2}
    {}

    template <Floating T>
    template <ExclusiveFloatingSubOf<T> U>
    finline constexpr mat<T, 2>::mat(const mat2<U> & m) :
        c1{m.c1},
        c2{m.c2}
    {}

    template <Floating T>
    template <ExclusiveFloatingSuperOf<T> U>
    finline constexpr mat<T, 2>::mat(const mat2<U> & m) :
        c1{m.c1},
        c2{m.c2}
    {}

    template <Floating T>
    template <Floating U>
    finline constexpr mat<T, 2>::mat(const mat3<U> & m) :
        c1{m.c1},
        c2{m.c2}
    {}

    template <Floating T>
    template <Floating U>
    finline constexpr mat<T, 2>::mat(const mat4<U> & m) :
        c1{m.c1},
        c2{m.c2}
    {}

    template <Floating T>
    template <ExclusiveFloatingSubOf<T> U>
    finline mat2<T> & mat<T, 2>::operator=(const mat2<U> & m)
    {
        c1 = m.c1;
        c2 = m.c2;

        return *this;
    }

    template <Floating T>
    finline vec2<T> & mat<T, 2>::col(const u32 i)
    {
        return *(&c1 + i);
    }

    template <Floating T>
    finline vec2<T> mat<T, 2>::col(const u32 i) const
    {
        return *(&c1 + i);
    }

    template <Floating T>
    finline vec2<T> mat<T, 2>::row(const u32 i) const
    {
        return {c1[i], c2[i]};
    }

    template <Floating T>
    template <u32 i>
    finline constexpr vec2<T> mat<T, 2>::col() const
    {
        if constexpr (i == 0) return c1;
        if constexpr (i == 1) return c2;
    }

    template <Floating T>
    template <u32 i>
    finline constexpr vec2<T> mat<T, 2>::row() const
    {
        return {c1.template at<i>(), c2.template at<i>()};
    }

    template <Floating T>
    template <InclusiveFloatingSubOf<T> U>
    finline constexpr mat<T, 3>::mat(const vec3<U> & c1_, const vec3<U> & c2_, const vec3<U> & c3_) :
        c1{c1_},
        c2{c2_},
        c3{c3_}
    {}

    template <Floating T>
    template <InclusiveFloatingSubOf<T> U>
    finline constexpr mat<T, 3>::mat(
        const U x1, const U y1, const U z1,
        const U x2, const U y2, const U z2,
        const U x3, const U y3, const U z3
    ) :
        c1{x1, y1, z1},
        c2{x2, y2, z2},
        c3{x3, y3, z3}
    {}

    template <Floating T>
    template <Floating U>
    finline constexpr mat<T, 3>::mat(const mat2<U> & m) :
        c1{m.c1},
        c2{m.c2},
        c3{T(0.0), T(0.0), T(1.0)}
    {}

    template <Floating T>
    template <ExclusiveFloatingSubOf<T> U>
    finline constexpr mat<T, 3>::mat(const mat3<U> & m) :
        c1{m.c1},
        c2{m.c2},
        c3{m.c3}
    {}

    template <Floating T>
    template <ExclusiveFloatingSuperOf<T> U>
    finline constexpr mat<T, 3>::mat(const mat3<U> & m) :
        c1{m.c1},
        c2{m.c2},
        c3{m.c3}
    {}

    template <Floating T>
    template <Floating U>
    finline constexpr mat<T, 3>::mat(const mat4<U> & m) :
        c1{m.c1},
        c2{m.c2},
        c3{m.c3}
    {}

    template <Floating T>
    template <ExclusiveFloatingSubOf<T> U>
    finline mat3<T> & mat<T, 3>::operator=(const mat3<U> & m)
    {
        c1 = m.c1;
        c2 = m.c2;
        c3 = m.c3;

        return *this;
    }

    template <Floating T>
    finline vec3<T> & mat<T, 3>::col(const u32 i)
    {
        return *(&c1 + i);
    }

    template <Floating T>
    finline vec3<T> mat<T, 3>::col(const u32 i) const
    {
        return *(&c1 + i);
    }

    template <Floating T>
    finline vec3<T> mat<T, 3>::row(const u32 i) const
    {
        return {c1[i], c2[i], c3[i]};
    }

    template <Floating T>
    template <u32 i>
    finline constexpr vec3<T> mat<T, 3>::col() const
    {
        if constexpr (i == 0) return c1;
        if constexpr (i == 1) return c2;
        if constexpr (i == 2) return c3;
    }

    template <Floating T>
    template <u32 i>
    finline constexpr vec3<T> mat<T, 3>::row() const
    {
        return {c1.template at<i>(), c2.template at<i>(), c3.template at<i>()};
    }

    template <Floating T>
    template <InclusiveFloatingSubOf<T> U>
    finline constexpr mat<T, 4>::mat(const vec4<U> & c1_, const vec4<U> & c2_, const vec4<U> & c3_, const vec4<U> & c4_) :
        c1{c1_},
        c2{c2_},
        c3{c3_},
        c4{c4_}
    {}

    template <Floating T>
    template <InclusiveFloatingSubOf<T> U>
    finline constexpr mat<T, 4>::mat(
        const U x1, const U y1, const U z1, const U w1,
        const U x2, const U y2, const U z2, const U w2,
        const U x3, const U y3, const U z3, const U w3,
        const U x4, const U y4, const U z4, const U w4
    ) :
        c1{x1, y1, z1, w1},
        c2{x2, y2, z2, w2},
        c3{x3, y3, z3, w3},
        c4{x4, y4, z4, w4}
    {}

    template <Floating T>
    template <Floating U>
    finline constexpr mat<T, 4>::mat(const mat2<U> & m) :
        c1{m.c1},
        c2{m.c2},
        c3{T(0.0), T(0.0), T(1.0), T(0.0)},
        c4{T(0.0), T(0.0), T(0.0), T(1.0)}
    {}

    template <Floating T>
    template <Floating U>
    finline constexpr mat<T, 4>::mat(const mat3<U> & m) :
        c1{m.c1},
        c2{m.c2},
        c3{m.c3},
        c4{T(0.0), T(0.0), T(0.0), T(1.0)}
    {}

    template <Floating T>
    template <ExclusiveFloatingSubOf<T> U>
    finline constexpr mat<T, 4>::mat(const mat4<U> & m) :
        c1{m.c1},
        c2{m.c2},
        c3{m.c3},
        c4{m.c4}
    {}

    template <Floating T>
    template <ExclusiveFloatingSuperOf<T> U>
    finline constexpr mat<T, 4>::mat(const mat4<U> & m) :
        c1{m.c1},
        c2{m.c2},
        c3{m.c3},
        c4{m.c4}
    {}

    template <Floating T>
    template <ExclusiveFloatingSubOf<T> U>
    finline mat4<T> & mat<T, 4>::operator=(const mat4<U> & m)
    {
        c1 = m.c1;
        c2 = m.c2;
        c3 = m.c3;
        c4 = m.c4;

        return *this;
    }

    template <Floating T>
    finline vec4<T> & mat<T, 4>::col(const u32 i)
    {
        return *(&c1 + i);
    }

    template <Floating T>
    finline vec4<T> mat<T, 4>::col(const u32 i) const
    {
        return *(&c1 + i);
    }

    template <Floating T>
    finline vec4<T> mat<T, 4>::row(const u32 i) const
    {
        return {c1[i], c2[i], c3[i], c4[i]};
    }

    template <Floating T>
    template <u32 i>
    finline constexpr vec4<T> mat<T, 4>::col() const
    {
        if constexpr (i == 0) return c1;
        if constexpr (i == 1) return c2;
        if constexpr (i == 2) return c3;
        if constexpr (i == 3) return c4;
    }

    template <Floating T>
    template <u32 i>
    finline constexpr vec4<T> mat<T, 4>::row() const
    {
        return {c1.template at<i>(), c2.template at<i>(), c3.template at<i>(), c4.template at<i>()};
    }

    template <Floating T1, InclusiveFloatingSubOf<T1> T2, u32 n>
    finline mat<T1, n> & operator+=(mat<T1, n> & m, const T2 v)
    {
        if constexpr (n >= 1) m.c1 += v;
        if constexpr (n >= 2) m.c2 += v;
        if constexpr (n >= 3) m.c3 += v;
        if constexpr (n >= 4) m.c4 += v;

        return m;
    }

    template <Floating T1, InclusiveFloatingSubOf<T1> T2, u32 n>
    finline mat<T1, n> & operator+=(mat<T1, n> & m1, const mat<T2, n> & m2)
    {
        if constexpr (n >= 1) m1.c1 += m2.c1;
        if constexpr (n >= 2) m1.c2 += m2.c2;
        if constexpr (n >= 3) m1.c3 += m2.c3;
        if constexpr (n >= 4) m1.c4 += m2.c4;

        return m1;
    }

    template <Floating T1, InclusiveFloatingSubOf<T1> T2, u32 n>
    finline mat<T1, n> & operator-=(mat<T1, n> & m, const T2 v)
    {
        if constexpr (n >= 1) m.c1 -= v;
        if constexpr (n >= 2) m.c2 -= v;
        if constexpr (n >= 3) m.c3 -= v;
        if constexpr (n >= 4) m.c4 -= v;

        return m;
    }

    template <Floating T1, InclusiveFloatingSubOf<T1> T2, u32 n>
    finline mat<T1, n> & operator-=(mat<T1, n> & m1, const mat<T2, n> & m2)
    {
        if constexpr (n >= 1) m1.c1 -= m2.c1;
        if constexpr (n >= 2) m1.c2 -= m2.c2;
        if constexpr (n >= 3) m1.c3 -= m2.c3;
        if constexpr (n >= 4) m1.c4 -= m2.c4;

        return m1;
    }

    template <Floating T1, InclusiveFloatingSubOf<T1> T2, u32 n>
    finline mat<T1, n> & operator*=(mat<T1, n> & m, const T2 v)
    {
        if constexpr (n >= 1) m.c1 *= v;
        if constexpr (n >= 2) m.c2 *= v;
        if constexpr (n >= 3) m.c3 *= v;
        if constexpr (n >= 4) m.c4 *= v;

        return m;
    }

    template <Floating T1, InclusiveFloatingSubOf<T1> T2, u32 n>
    finline mat<T1, n> & operator*=(mat<T1, n> & m1, const mat<T2, n> & m2)
    {
        if constexpr (n >= 1) m1.c1 *= m2;
        if constexpr (n >= 2) m1.c2 *= m2;
        if constexpr (n >= 3) m1.c3 *= m2;
        if constexpr (n >= 4) m1.c4 *= m2;

        return m1;
    }

    template <Floating T1, InclusiveFloatingSubOf<T1> T2, u32 n>
    finline vec<T1, n> & operator*=(vec<T1, n> & v, const mat<T2, n> & m)
    {
        return v = m * v;
    }

    template <Floating T1, InclusiveFloatingSubOf<T1> T2, u32 n>
    finline mat<T1, n> & operator/=(mat<T1, n> & m, const T2 v)
    {
        return m *= T2(1.0) / v;
    }

    template <Floating T, u32 n>
    finline constexpr mat<T, n> operator+(const mat<T, n> & m)
    {
        return m;
    }

    template <Floating T, u32 n>
    finline constexpr mat<T, n> operator-(const mat<T, n> & m)
    {
        if constexpr (n == 2) return {-m.c1, -m.c2};
        if constexpr (n == 3) return {-m.c1, -m.c2, -m.c3};
        if constexpr (n == 4) return {-m.c1, -m.c2, -m.c3, -m.c4};
    }

    template <Floating T1, Floating T2, u32 n>
    finline constexpr mat<LargerOf<T1, T2>, n> operator+(const mat<T1, n> & m1, const mat<T2, n> & m2)
    {
        if constexpr (n == 2) return {m1.c1 + m2.c1, m1.c2 + m2.c2};
        if constexpr (n == 3) return {m1.c1 + m2.c1, m1.c2 + m2.c2, m1.c3 + m2.c3};
        if constexpr (n == 4) return {m1.c1 + m2.c1, m1.c2 + m2.c2, m1.c3 + m2.c3, m1.c4 + m2.c4};
    }

    template <Floating T1, Floating T2, u32 n>
    finline constexpr mat<LargerOf<T1, T2>, n> operator+(const mat<T1, n> & m, const T2 v)
    {
        if constexpr (n == 2) return {m.c1 + v, m.c2 + v};
        if constexpr (n == 3) return {m.c1 + v, m.c2 + v, m.c3 + v};
        if constexpr (n == 4) return {m.c1 + v, m.c2 + v, m.c3 + v, m.c4 + v};
    }

    template <Floating T1, Floating T2, u32 n>
    finline constexpr mat<LargerOf<T1, T2>, n> operator+(const T1 v, const mat<T2, n> & m)
    {
        return m + v;
    }

    template <Floating T1, Floating T2, u32 n>
    finline constexpr mat<LargerOf<T1, T2>, n> operator-(const mat<T1, n> & m1, const mat<T2, n> & m2)
    {
        if constexpr (n == 2) return {m1.c1 - m2.c1, m1.c2 - m2.c2};
        if constexpr (n == 3) return {m1.c1 - m2.c1, m1.c2 - m2.c2, m1.c3 - m2.c3};
        if constexpr (n == 4) return {m1.c1 - m2.c1, m1.c2 - m2.c2, m1.c3 - m2.c3, m1.c4 - m2.c4};
    }

    template <Floating T1, Floating T2, u32 n>
    finline constexpr mat<LargerOf<T1, T2>, n> operator-(const mat<T1, n> & m, const T2 v)
    {
        if constexpr (n == 2) return {m.c1 - v, m.c2 - v};
        if constexpr (n == 3) return {m.c1 - v, m.c2 - v, m.c3 - v};
        if constexpr (n == 4) return {m.c1 - v, m.c2 - v, m.c3 - v, m.c4 - v};
    }

    template <Floating T1, Floating T2, u32 n>
    finline constexpr mat<LargerOf<T1, T2>, n> operator-(const T1 v, const mat<T2, n> & m)
    {
        if constexpr (n == 2) return {v - m.c1, v - m.c2};
        if constexpr (n == 3) return {v - m.c1, v - m.c2, v - m.c3};
        if constexpr (n == 4) return {v - m.c1, v - m.c2, v - m.c3, v - m.c4};
    }

    template <Floating T1, Floating T2, u32 n>
    finline constexpr mat<LargerOf<T1, T2>, n> operator*(const mat<T1, n> & m1, const mat<T2, n> & m2)
    {
        // TODO: SIMD
        if constexpr (n == 2) return {
            m1.c1.x * m2.c1.x + m1.c2.x * m2.c1.y,
            m1.c1.y * m2.c1.x + m1.c2.y * m2.c1.y,

            m1.c1.x * m2.c2.x + m1.c2.x * m2.c2.y,
            m1.c1.y * m2.c2.x + m1.c2.y * m2.c2.y};

        if constexpr (n == 3) return {
            m1.c1.x * m2.c1.x + m1.c2.x * m2.c1.y + m1.c3.x * m2.c1.z,
            m1.c1.y * m2.c1.x + m1.c2.y * m2.c1.y + m1.c3.y * m2.c1.z,
            m1.c1.z * m2.c1.x + m1.c2.z * m2.c1.y + m1.c3.z * m2.c1.z,

            m1.c1.x * m2.c2.x + m1.c2.x * m2.c2.y + m1.c3.x * m2.c2.z,
            m1.c1.y * m2.c2.x + m1.c2.y * m2.c2.y + m1.c3.y * m2.c2.z,
            m1.c1.z * m2.c2.x + m1.c2.z * m2.c2.y + m1.c3.z * m2.c2.z,

            m1.c1.x * m2.c3.x + m1.c2.x * m2.c3.y + m1.c3.x * m2.c3.z,
            m1.c1.y * m2.c3.x + m1.c2.y * m2.c3.y + m1.c3.y * m2.c3.z,
            m1.c1.z * m2.c3.x + m1.c2.z * m2.c3.y + m1.c3.z * m2.c3.z};

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
            m1.c1.w * m2.c4.x + m1.c2.w * m2.c4.y + m1.c3.w * m2.c4.z + m1.c4.w * m2.c4.w};
    }

    template <Floating T1, Floating T2, u32 n>
    finline constexpr mat<LargerOf<T1, T2>, n> operator*(const mat<T1, n> & m, const T2 v)
    {
        if constexpr (n == 2) return {m.c1 * v, m.c2 * v};
        if constexpr (n == 3) return {m.c1 * v, m.c2 * v, m.c3 * v};
        if constexpr (n == 4) return {m.c1 * v, m.c2 * v, m.c3 * v, m.c4 * v};
    }

    template <Floating T1, Floating T2, u32 n>
    finline constexpr mat<LargerOf<T1, T2>, n> operator*(const T1 v, const mat<T2, n> & m)
    {
        return m * v;
    }

    template <Floating T1, Floating T2, u32 n>
    finline constexpr vec<LargerOf<T1, T2>, n> operator*(const mat<T1, n> & m, const vec<T2, n> & v)
    {
        if constexpr (n == 2) return {
            m.c1.x * v.x + m.c2.x * v.y,
            m.c1.y * v.x + m.c2.y * v.y};

        if constexpr (n == 3) return {
            m.c1.x * v.x + m.c2.x * v.y + m.c3.x * v.z,
            m.c1.y * v.x + m.c2.y * v.y + m.c3.y * v.z,
            m.c1.z * v.x + m.c2.z * v.y + m.c3.z * v.z};

        if constexpr (n == 4) return {
            m.c1.x * v.x + m.c2.x * v.y + m.c3.x * v.z + m.c4.x * v.w,
            m.c1.y * v.x + m.c2.y * v.y + m.c3.y * v.z + m.c4.y * v.w,
            m.c1.z * v.x + m.c2.z * v.y + m.c3.z * v.z + m.c4.z * v.w,
            m.c1.w * v.x + m.c2.w * v.y + m.c3.w * v.z + m.c4.w * v.w};
    }

    template <Floating T1, Floating T2, u32 n>
    finline constexpr mat<LargerOf<T1, T2>, n> operator/(const mat<T1, n> & m, const T2 v)
    {
        return m * (T2(1.0) / v);
    }

    template <Floating T1, Floating T2, u32 n>
    finline constexpr mat<LargerOf<T1, T2>, n> operator/(const T1 v, const mat<T2, n> & m)
    {
        if constexpr (n == 2) return {v / m.c1, v / m.c2};
        if constexpr (n == 3) return {v / m.c1, v / m.c2, v / m.c3};
        if constexpr (n == 4) return {v / m.c1, v / m.c2, v / m.c3, v / m.c4};
    }

    template <Floating T, u32 n>
    finline constexpr mat<T, n> fullMat(const T v)
    {
        if constexpr (n == 2) return {vec2<T>{v}, vec2<T>{v}};
        if constexpr (n == 3) return {vec3<T>{v}, vec3<T>{v}, vec3<T>{v}};
        if constexpr (n == 4) return {vec4<T>{v}, vec4<T>{v}, vec4<T>{v}, vec4<T>{v}};
    }

    template <Floating T, u32 n>
    finline constexpr mat<T, n> nullMat()
    {
        return fullMat<T, n>(T(0.0));
    }
}
