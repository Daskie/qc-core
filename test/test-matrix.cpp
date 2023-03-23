#include <qc-core/matrix-ext.hpp>

#include <sstream>

#include <gtest/gtest.h>

using namespace qc::types;
using namespace qc::primitives;

template <typename T>
static void compileClassesT()
{
    T v{T(1.0)};
    vec2<T> v2{};
    vec3<T> v3{};
    vec4<T> v4{};
    mat2<T> m2{};
    mat3<T> m3{};
    mat4<T> m4{};
    std::stringstream os{};

    //--------------------------------------------------------------------------
    // Mat2

    // constructors

    mat2<T> m2_1{};
    mat2<T> m2_2{m2};
    mat2<T> m2_3{std::move(m2)};
    mat2<T> m2_4{v, v, v, v};
    mat2<T> m2_6{m3};
    mat2<T> m2_7{m4};
    mat2<T> m2_8{v2, v2};

    // assignment

    m2 = m2;
    m2 = std::move(m2);

    // access

    static_cast<void>(m2.col(0));
    static_cast<void>(m2.row(0));

    static_cast<void>(m2.template row<0>());
    static_cast<void>(m2.template row<1>());

    static_cast<void>(m2.template col<0>());
    static_cast<void>(m2.template col<1>());

    // arithmetic assignment

    m2 += v;
    m2 += m2;
    m2 -= v;
    m2 -= m2;
    m2 *= v;
    m2 *= m2;
    v2 *= m2;
    m2 /= T(1);

    // arithmetic operators

    +m2;
    -m2;
    static_cast<void>(m2 + m2);
    static_cast<void>(m2 + v);
    static_cast<void>(v + m2);
    static_cast<void>(m2 - m2);
    static_cast<void>(m2 - v);
    static_cast<void>(v - m2);
    static_cast<void>(m2 * m2);
    static_cast<void>(m2 * v);
    static_cast<void>(v * m2);
    static_cast<void>(m2 * v2);
    static_cast<void>(m2 / T(1));
    static_cast<void>(T(1) / m2);

    // comparison operators

    static_cast<void>(m2 == m2);
    static_cast<void>(m2 != m2);

    // other

    os << m2;

    //--------------------------------------------------------------------------
    // Mat3

    // constructors

    mat3<T> m3_1{};
    mat3<T> m3_2{m3};
    mat3<T> m3_3{std::move(m3)};
    mat3<T> m3_4{v, v, v, v, v, v, v, v, v};
    mat3<T> m3_6{m2};
    mat3<T> m3_7{m4};
    mat3<T> m3_8{v3, v3, v3};

    // assignment

    m3 = m3;
    m3 = std::move(m3);
    m3 = m2;

    // access

    static_cast<void>(m3.col(0));
    static_cast<void>(m3.row(0));

    static_cast<void>(m3.template row<0>());
    static_cast<void>(m3.template row<1>());
    static_cast<void>(m3.template row<2>());

    static_cast<void>(m3.template col<0>());
    static_cast<void>(m3.template col<1>());
    static_cast<void>(m3.template col<2>());

    // arithmetic assignment

    m3 += v;
    m3 += m3;
    m3 -= v;
    m3 -= m3;
    m3 *= v;
    m3 *= m3;
    v3 *= m3;
    m3 /= T(1);

    // arithmetic operators

    +m3;
    -m3;
    static_cast<void>(m3 + m3);
    static_cast<void>(m3 + v);
    static_cast<void>(v + m3);
    static_cast<void>(m3 - m3);
    static_cast<void>(m3 - v);
    static_cast<void>(v - m3);
    static_cast<void>(m3 * m3);
    static_cast<void>(m3 * v);
    static_cast<void>(v * m3);
    static_cast<void>(m3 * v3);
    static_cast<void>(m3 / T(1));
    static_cast<void>(T(1) / m3);

    // comparison operators

    static_cast<void>(m3 == m3);
    static_cast<void>(m3 != m3);

    // other
    os << m3;

    //--------------------------------------------------------------------------
    // Mat4

    // constructors

    mat4<T> m4_1{};
    mat4<T> m4_2{m4};
    mat4<T> m4_3{std::move(m4)};
    mat4<T> m4_4{v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v};
    mat4<T> m4_6{m2};
    mat4<T> m4_7{m3};
    mat4<T> m4_8{v4, v4, v4, v4};

    // assignment

    m4 = m4;
    m4 = std::move(m4);
    m4 = m2;
    m4 = m3;

    // access

    static_cast<void>(m4.col(0));
    static_cast<void>(m4.row(0));

    static_cast<void>(m4.template row<0>());
    static_cast<void>(m4.template row<1>());
    static_cast<void>(m4.template row<2>());
    static_cast<void>(m4.template row<3>());

    static_cast<void>(m4.template col<0>());
    static_cast<void>(m4.template col<1>());
    static_cast<void>(m4.template col<2>());
    static_cast<void>(m4.template col<3>());

    // arithmetic assignment

    m4 += v;
    m4 += m4;
    m4 -= v;
    m4 -= m4;
    m4 *= v;
    m4 *= m4;
    v4 *= m4;
    m4 /= T(1);

    // arithmetic operators

    +m4;
    -m4;
    static_cast<void>(m4 + m4);
    static_cast<void>(m4 + v);
    static_cast<void>(v + m4);
    static_cast<void>(m4 - m4);
    static_cast<void>(m4 - v);
    static_cast<void>(v - m4);
    static_cast<void>(m4 * m4);
    static_cast<void>(m4 * v);
    static_cast<void>(v * m4);
    static_cast<void>(m4 * v4);
    static_cast<void>(m4 / T(1));
    static_cast<void>(T(1) / m4);

    // comparison operators

    static_cast<void>(m4 == m4);
    static_cast<void>(m4 != m4);

    // other
    os << m4;
}

static void compileClasses()
{
    compileClassesT<float>();
    compileClassesT<double>();
}

template <typename T>
static void compileFunctionsT()
{
    T v{1.0};
    vec2<T> v2{};
    vec3<T> v3{};
    vec4<T> v4{};
    mat2<T> m2{};
    mat3<T> m3{};
    mat4<T> m4{};

    static_cast<void>(qc::isIdentity(m2));
    static_cast<void>(qc::isIdentity(m3));
    static_cast<void>(qc::isIdentity(m4));
    static_cast<void>(qc::transpose(m2));
    static_cast<void>(qc::transpose(m3));
    static_cast<void>(qc::transpose(m4));
    static_cast<void>(qc::cofactor(m2));
    static_cast<void>(qc::cofactor(m3));
    static_cast<void>(qc::cofactor(m4));
    static_cast<void>(qc::adjoint(m2));
    static_cast<void>(qc::adjoint(m3));
    static_cast<void>(qc::adjoint(m4));
    static_cast<void>(qc::determinant(m2));
    static_cast<void>(qc::determinant(m3));
    static_cast<void>(qc::determinant(m4));
    static_cast<void>(qc::inverse(m2));
    static_cast<void>(qc::inverse(m3));
    static_cast<void>(qc::inverse(m4));
    qc::fullMat<T, 2>(v);
    qc::fullMat<T, 3>(v);
    qc::fullMat<T, 4>(v);
    qc::nullMat<T, 2>();
    qc::nullMat<T, 3>();
    qc::nullMat<T, 4>();

    static_cast<void>(qc::translate(v2));
    static_cast<void>(qc::translate(v3));
    qc::translate(m3, v2);
    qc::translate(m4, v3);
    static_cast<void>(qc::scale(v2));
    static_cast<void>(qc::scale(v3));
    static_cast<void>(qc::scale(v4));
    qc::scale(m2, v2);
    qc::scale(m3, v2);
    qc::scale(m3, v3);
    qc::scale(m4, v3);
    static_cast<void>(qc::rotate(v));
    static_cast<void>(qc::rotateX(v));
    static_cast<void>(qc::rotateY(v));
    static_cast<void>(qc::rotateZ(v));
    static_cast<void>(qc::rotate(v3, v));
    static_cast<void>(qc::rotate_n(v3, v));
    static_cast<void>(qc::euler(v3, v3, v, v, v));
    static_cast<void>(qc::euler_n(v3, v3, v, v, v));
    static_cast<void>(qc::align(v2, v2));
    static_cast<void>(qc::align(v3, v3));
    qc::align_n(v2, v2);
    qc::align_n(v3, v3);
    static_cast<void>(qc::align(v3, v3, v3, v3));
    static_cast<void>(qc::align_n(v3, v3, v3, v3));
    static_cast<void>(qc::map(v2, v2, v2, v2));
    static_cast<void>(qc::map_o(v2, v2, v2, v2));
    static_cast<void>(qc::map(v3, v3, v3, v3, v3, v3));
    static_cast<void>(qc::map_o(v3, v3, v3, v3, v3, v3));
    static_cast<void>(qc::mapTo(v2, v2));
    static_cast<void>(qc::mapTo_o(v2, v2));
    static_cast<void>(qc::mapTo(v3, v3, v3));
    static_cast<void>(qc::mapTo_o(v3, v3, v3));
    static_cast<void>(qc::mapFrom(v2, v2));
    static_cast<void>(qc::mapFrom(v3, v3, v3));
    static_cast<void>(qc::orthoProj<true>(v, v, v, v));
    static_cast<void>(qc::orthoProj<false>(v, v, v, v));
    static_cast<void>(qc::perspProj<true>(v, v, v, v));
    static_cast<void>(qc::perspProj<false>(v, v, v, v));
    static_cast<void>(qc::view(v3, v3, v3));
    static_cast<void>(qc::view(v3, v3, v3, v3));
    static_cast<void>(qc::view_n(v3, v3, v3, v3));
    static_cast<void>(qc::view_o(v3, v3, v3, v3));
    static_cast<void>(qc::view_on(v3, v3, v3, v3));
}

template <u32 n>
static void compileNonMatching()
{
    float _f{};
    fvec<n> _fvec{};
    dvec<n> _dvec{};
    fmat<n> _fmat{};
    dmat<n> _dmat{};

    {
        dmat<n> m{_fmat};
    }
    if constexpr (n == 2u)
    {
        dmat<n> m1{
            _f, _f,
            _f, _f};
        dmat<n> m2{_fvec, _fvec};
    }
    if constexpr (n == 3u)
    {
        dmat<n> m1{
            _f, _f, _f,
            _f, _f, _f,
            _f, _f, _f};
        dmat<n> m2{_fvec, _fvec, _fvec};
    }
    if constexpr (n == 4u)
    {
        dmat<n> m1{
            _f, _f, _f, _f,
            _f, _f, _f, _f,
            _f, _f, _f, _f,
            _f, _f, _f, _f};
        dmat<n> m2{_fvec, _fvec, _fvec, _fvec};
    }
    {
        fmat<n> m{_dmat};
    }

    _dmat = _fmat;

    _dmat += _f;
    _dmat += _fmat;

    _dmat -= _f;
    _dmat -= _fmat;

    _dmat *= _f;
    _dvec *= _fmat;
    _dmat *= _fmat;

    _dmat /= _f;

    static_cast<void>(_dmat + _f);
    static_cast<void>(_dmat + _fmat);
    static_cast<void>(_f + _dmat);
    static_cast<void>(_fmat + _dmat );

    static_cast<void>(_dmat - _f);
    static_cast<void>(_dmat - _fmat);
    static_cast<void>(_f - _dmat);
    static_cast<void>(_fmat - _dmat);

    static_cast<void>(_dmat * _f);
    static_cast<void>(_dmat * _fvec);
    static_cast<void>(_dmat * _fmat);
    static_cast<void>(_f * _dmat);
    static_cast<void>(_fmat * _dmat);

    static_cast<void>(_dmat / _f);
}

static void compileFunctions()
{
    compileFunctionsT<float>();
    compileFunctionsT<double>();
    compileNonMatching<2>();
    compileNonMatching<3>();
    compileNonMatching<4>();
}

template <typename T, u32 n>
static void testPropertiesTN()
{
    static_assert(std::is_standard_layout_v<mat<T, n>>);
    static_assert(std::is_trivially_copyable_v<mat<T, n>>);
    static_assert(std::is_trivially_copy_constructible_v<mat<T, n>>);
    static_assert(std::is_trivially_move_constructible_v<mat<T, n>>);
    static_assert(std::is_trivially_copy_assignable_v<mat<T, n>>);
    static_assert(std::is_trivially_move_assignable_v<mat<T, n>>);
    static_assert(std::is_trivially_destructible_v<mat<T, n>>);
    static_assert(sizeof(mat<T, n>) == n * n * sizeof(T));
    static_assert(sizeof(mat<T, n>[4]) == 4 * n * n * sizeof(T));
    static_assert(alignof(mat<T, n>) == alignof(T));
    static_assert(alignof(mat<T, n>[4]) == alignof(T));
}

template <typename T>
static void testPropertiesT()
{
    testPropertiesTN<T, 2>();
    testPropertiesTN<T, 3>();
    testPropertiesTN<T, 4>();
}

static void testProperties()
{
    testPropertiesT<float>();
    testPropertiesT<double>();
}

template <typename T1, typename T2>
static void compileCastsTT()
{
    static_cast<void>(static_cast<mat2<T2>>(mat2<T1>{}));
    static_cast<void>(static_cast<mat3<T2>>(mat3<T1>{}));
    static_cast<void>(static_cast<mat4<T2>>(mat4<T1>{}));
}

template <typename T>
static void compileCastsT()
{
    compileCastsTT<T, float>();
    compileCastsTT<T, double>();
}

static void compileCasts()
{
    compileCastsT<float>();
    compileCastsT<double>();
}

TEST(Matrix, compilation)
{
    compileClasses();
    compileFunctions();
    testProperties();
    compileCasts();
}

template <typename T>
static void testMatrixConceptT()
{
    static_assert(Matrix<mat2<T>>);
    static_assert(Matrix<mat3<T>>);
    static_assert(Matrix<mat4<T>>);

    static_assert(Matrix2<mat2<T>>);
    static_assert(!Matrix2<mat3<T>>);
    static_assert(!Matrix2<mat4<T>>);

    static_assert(Matrix3<mat3<T>>);
    static_assert(!Matrix3<mat2<T>>);
    static_assert(!Matrix3<mat4<T>>);

    static_assert(Matrix4<mat4<T>>);
    static_assert(!Matrix4<mat2<T>>);
    static_assert(!Matrix4<mat3<T>>);
}

TEST(Matrix, types)
{
    testMatrixConceptT<f32>();
    testMatrixConceptT<f64>();
    static_assert(!Matrix<float>);
}
