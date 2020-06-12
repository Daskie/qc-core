#include <sstream>

#include <CppUnitTest.h>

#include <qc-core/matrix-ext.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace qc::core::types;

template <typename T>
static void compileClassesT() {
    T v{T(1.0)};
    vec2<T> v2;
    vec3<T> v3;
    vec4<T> v4;
    mat2<T> m2;
    mat3<T> m3;
    mat4<T> m4;
    std::stringstream os;

    //--------------------------------------------------------------------------
    // Mat2

    // constructors

    mat2<T> m2_1;
    mat2<T> m2_2(m2);
    mat2<T> m2_3(std::move(m2));
    mat2<T> m2_4(v, v, v, v);
    mat2<T> m2_6(m3);
    mat2<T> m2_7(m4);
    mat2<T> m2_8(v2, v2);

    // assignment

    m2 = m2;
    m2 = std::move(m2);

    // conversion

    static_cast<bool>(m2);

    // access

    m2.col(0);
    m2.row(0);

    m2.row<0>(); m2.row<1>();
    m2.col<0>(); m2.col<1>();

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
    m2 + m2;
    m2 + v;
    v + m2;
    m2 - m2;
    m2 - v;
    v - m2;
    m2 * m2;
    m2 * v;
    v * m2;
    m2 * v2;
    m2 / T(1);
    T(1) / m2;

    // comparison operators

    m2 == m2;
    m2 != m2;

    // other

    os << m2;

    //--------------------------------------------------------------------------
    // Mat3

    // constructors

    mat3<T> m3_1;
    mat3<T> m3_2(m3);
    mat3<T> m3_3(std::move(m3));
    mat3<T> m3_4(v, v, v, v, v, v, v, v, v);
    mat3<T> m3_6(m2);
    mat3<T> m3_7(m4);
    mat3<T> m3_8(v3, v3, v3);

    // assignment

    m3 = m3;
    m3 = std::move(m3);

    // conversion

    static_cast<bool>(m3);

    // access

    m3.col(0);
    m3.row(0);

    m3.row<0>(); m3.row<1>(); m3.row<2>();
    m3.col<0>(); m3.col<1>(); m3.col<2>();

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
    m3 + m3;
    m3 + v;
    v + m3;
    m3 - m3;
    m3 - v;
    v - m3;
    m3 * m3;
    m3 * v;
    v * m3;
    m3 * v3;
    m3 / T(1);
    T(1) / m3;

    // comparison operators

    m3 == m3;
    m3 != m3;

    // other
    os << m3;

    //--------------------------------------------------------------------------
    // Mat4

    // constructors

    mat4<T> m4_1;
    mat4<T> m4_2(m4);
    mat4<T> m4_3(std::move(m4));
    mat4<T> m4_4(v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v);
    mat4<T> m4_6(m2);
    mat4<T> m4_7(m3);
    mat4<T> m4_8(v4, v4, v4, v4);

    // assignment

    m4 = m4;
    m4 = std::move(m4);

    // conversion

    static_cast<bool>(m4);

    // access

    m4.col(0);
    m4.row(0);

    m4.row<0>(); m4.row<1>(); m4.row<2>(); m4.row<3>();
    m4.col<0>(); m4.col<1>(); m4.col<2>(); m4.col<3>();

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
    m4 + m4;
    m4 + v;
    v + m4;
    m4 - m4;
    m4 - v;
    v - m4;
    m4 * m4;
    m4 * v;
    v * m4;
    m4 * v4;
    m4 / T(1);
    T(1) / m4;

    // comparison operators

    m4 == m4;
    m4 != m4;

    // other
    os << m4;
}

static void compileClasses() {
    compileClassesT< float>();
    compileClassesT<double>();
}

template <typename T>
static constexpr void compileClassesConstexprT() {
    constexpr T v{T(1.0)};
    constexpr vec2<T> v2;
    constexpr vec3<T> v3;
    constexpr vec4<T> v4;
    constexpr mat2<T> m2;
    constexpr mat3<T> m3;
    constexpr mat4<T> m4;

    //--------------------------------------------------------------------------
    // Mat2

    // constructors

    constexpr mat2<T> m2_1;
    constexpr mat2<T> m2_2(m2);
    constexpr mat2<T> m2_3(std::move(m2));
    constexpr mat2<T> m2_4(v, v, v, v);
    constexpr mat2<T> m2_6(m3);
    constexpr mat2<T> m2_7(m4);
    constexpr mat2<T> m2_8(v2, v2);

    // access

    m2.col<0>(); m2.col<1>();
    m2.row<0>(); m2.row<1>();

    //--------------------------------------------------------------------------
    // Mat3

    // constructors

    constexpr mat3<T> m3_1;
    constexpr mat3<T> m3_2(m3);
    constexpr mat3<T> m3_3(std::move(m3));
    constexpr mat3<T> m3_4(v, v, v, v, v, v, v, v, v);
    constexpr mat3<T> m3_6(m2);
    constexpr mat3<T> m3_7(m4);
    constexpr mat3<T> m3_8(v3, v3, v3);

    // access

    m3.col<0>(); m3.col<1>(); m3.col<2>();
    m3.row<0>(); m3.row<1>(); m3.row<2>();

    //--------------------------------------------------------------------------
    // Mat4

    // constructors

    constexpr mat4<T> m4_1;
    constexpr mat4<T> m4_2(m4);
    constexpr mat4<T> m4_3(std::move(m4));
    constexpr mat4<T> m4_4(v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v);
    constexpr mat4<T> m4_6(m2);
    constexpr mat4<T> m4_7(m3);
    constexpr mat4<T> m4_8(v4, v4, v4, v4);

    // access

    m4.col<0>(); m4.col<1>(); m4.col<2>(); m4.col<3>();
    m4.row<0>(); m4.row<1>(); m4.row<2>(); m4.row<3>();

}

static constexpr bool compileClassesConstexpr() {
    compileClassesConstexprT< float>();
    compileClassesConstexprT<double>();

    return true;
}

template <typename T>
static void compileFunctionsT() {
    T v{1.0};
    vec2<T> v2;
    vec3<T> v3;
    vec4<T> v4;
    mat2<T> m2;
    mat3<T> m3;
    mat4<T> m4;

    qc::core::isIdentity(m2);
    qc::core::isIdentity(m3);
    qc::core::isIdentity(m4);
    qc::core::transpose(m2);
    qc::core::transpose(m3);
    qc::core::transpose(m4);
    qc::core::cofactor(m2);
    qc::core::cofactor(m3);
    qc::core::cofactor(m4);
    qc::core::adjoint(m2);
    qc::core::adjoint(m3);
    qc::core::adjoint(m4);
    qc::core::determinant(m2);
    qc::core::determinant(m3);
    qc::core::determinant(m4);
    qc::core::inverse(m2);
    qc::core::inverse(m3);
    qc::core::inverse(m4);
    qc::core::fullMat<T, 2>(v);
    qc::core::fullMat<T, 3>(v);
    qc::core::fullMat<T, 4>(v);
    qc::core::nullMat<T, 2>();
    qc::core::nullMat<T, 3>();
    qc::core::nullMat<T, 4>();

    qc::core::translate(v2);
    qc::core::translate(v3);
    qc::core::translate(m3, v2);
    qc::core::translate(m4, v3);
    qc::core::scale(v2);
    qc::core::scale(v3);
    qc::core::scale(v4);
    qc::core::scale(m2, v2);
    qc::core::scale(m3, v2);
    qc::core::scale(m3, v3);
    qc::core::scale(m4, v3);
    qc::core::rotate(v);
    qc::core::rotateX(v);
    qc::core::rotateY(v);
    qc::core::rotateZ(v);
    qc::core::rotate(v3, v, v);
    qc::core::rotate_n(v3, v, v);
    qc::core::rotate(v3, v);
    qc::core::rotate_n(v3, v);
    qc::core::euler(v3, v3, v, v, v);
    qc::core::euler_n(v3, v3, v, v, v);
    qc::core::align(v2, v2);
    qc::core::align(v3, v3);
    qc::core::align_n(v2, v2);
    qc::core::align_n(v3, v3);
    qc::core::align(v3, v3, v3, v3);
    qc::core::align_n(v3, v3, v3, v3);
    qc::core::map(v2, v2, v2, v2);
    qc::core::map_o(v2, v2, v2, v2);
    qc::core::map(v3, v3, v3, v3, v3, v3);
    qc::core::map_o(v3, v3, v3, v3, v3, v3);
    qc::core::mapTo(v2, v2);
    qc::core::mapTo_o(v2, v2);
    qc::core::mapTo(v3, v3, v3);
    qc::core::mapTo_o(v3, v3, v3);
    qc::core::mapFrom(v2, v2);
    qc::core::mapFrom(v3, v3, v3);
    qc::core::orthoProj<true>(v, v, v, v);
    qc::core::orthoProj<false>(v, v, v, v);
    qc::core::perspProj<true>(v, v, v, v);
    qc::core::perspProj<false>(v, v, v, v);
    qc::core::view(v3, v3, v3);
    qc::core::view(v3, v3, v3, v3);
    qc::core::view_n(v3, v3, v3, v3);
    qc::core::view_o(v3, v3, v3, v3);
    qc::core::view_on(v3, v3, v3, v3);
}

static void compileFunctions() {
    compileFunctionsT< float>();
    compileFunctionsT<double>();
}

template <typename T>
static constexpr void compileFunctionsConstexprT() {
    constexpr T v{T(1.0)};
    constexpr vec2<T> v2(T(1.0));
    constexpr vec3<T> v3(T(1.0));
    constexpr vec4<T> v4(T(1.0));
    constexpr mat2<T> m2(v2, v2);
    constexpr mat3<T> m3(v3, v3, v3);
    constexpr mat4<T> m4(v4, v4, v4, v4);

    qc::core::fullMat<T, 2>(v);
    qc::core::fullMat<T, 3>(v);
    qc::core::fullMat<T, 4>(v);
    qc::core::nullMat<T, 2>();
    qc::core::nullMat<T, 3>();
    qc::core::nullMat<T, 4>();
}

static constexpr bool compileFunctionsConstexpr() {
    compileFunctionsConstexprT< float>();
    compileFunctionsConstexprT<double>();

    return true;
}

template <typename T, int n>
static void testPropertiesTN() {
    static_assert(std::             is_standard_layout_v<mat<T, n>>);
    static_assert(std::          is_trivially_copyable_v<mat<T, n>>);
    static_assert(std::is_trivially_copy_constructible_v<mat<T, n>>);
    static_assert(std::is_trivially_move_constructible_v<mat<T, n>>);
    static_assert(std::   is_trivially_copy_assignable_v<mat<T, n>>);
    static_assert(std::   is_trivially_move_assignable_v<mat<T, n>>);
    static_assert(std::      is_trivially_destructible_v<mat<T, n>>);
    static_assert(sizeof(mat<T, n>) == n * n * sizeof(T));
    static_assert(sizeof(mat<T, n>[4]) == 4 * n * n * sizeof(T));
    static_assert(alignof(mat<T, n>) == alignof(T));
    static_assert(alignof(mat<T, n>[4]) == alignof(T));
}

template <typename T>
static void testPropertiesT() {
    testPropertiesTN<T, 2>();
    testPropertiesTN<T, 3>();
    testPropertiesTN<T, 4>();
}

static void testProperties() {
    testPropertiesT< float>();
    testPropertiesT<double>();
}

template <typename T1, typename T2>
static void compileCastsTT() {
    static_cast<mat2<T2>>(mat2<T1>());
    static_cast<mat3<T2>>(mat3<T1>());
    static_cast<mat4<T2>>(mat4<T1>());
}

template <typename T>
static void compileCastsT() {
    compileCastsTT<T,  float>();
    compileCastsTT<T, double>();
}

static void compileCasts() {
    compileCastsT< float>();
    compileCastsT<double>();
}

TEST_CLASS(TestMatrix) {

    public:

    TEST_METHOD(testCompilation) {
        compileClasses();
        static_assert(compileClassesConstexpr(), "");
        compileFunctions();
        static_assert(compileFunctionsConstexpr(), "");
        testProperties();
        compileCasts();
    }

    TEST_METHOD(testConcepts) {
        static_assert(Matrix<fmat2>);
        static_assert(Matrix<fmat3>);
        static_assert(Matrix<fmat4>);
        static_assert(Matrix<dmat2>);
        static_assert(Matrix<dmat3>);
        static_assert(Matrix<dmat4>);
        static_assert(!Matrix<int>);

        static_assert(Matrix2<fmat2>);
        static_assert(Matrix2<dmat2>);
        static_assert(!Matrix2<fmat3>);

        static_assert(Matrix3<fmat3>);
        static_assert(Matrix3<dmat3>);
        static_assert(!Matrix3<fmat4>);

        static_assert(Matrix4<fmat4>);
        static_assert(Matrix4<dmat4>);
        static_assert(!Matrix4<fmat2>);
    }

};
