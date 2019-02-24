#include "QCoreTest.hpp"

#include <sstream>

#include "QCore/MatrixFunc.hpp"



namespace {



template <typename T>
void compileClassesT() {
    T v(1.0);
    qc::vec2<T> v2;
    qc::vec3<T> v3;
    qc::vec4<T> v4;
    qc::mat2<T> m2;
    qc::mat3<T> m3;
    qc::mat4<T> m4;
    std::stringstream os;

    //--------------------------------------------------------------------------
    // Mat2

    // constructors

    qc::mat2<T> m2_1;
    qc::mat2<T> m2_2(m2);
    qc::mat2<T> m2_3(std::move(m2));
    qc::mat2<T> m2_4(v, v, v, v);
    qc::mat2<T> m2_6(m3);
    qc::mat2<T> m2_7(m4);
    qc::mat2<T> m2_8(v2, v2);

    // assignment

    m2 = m2;
    m2 = std::move(m2);
    m2 = m3;
    m2 = m4;

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

    qc::mat3<T> m3_1;
    qc::mat3<T> m3_2(m3);
    qc::mat3<T> m3_3(std::move(m3));
    qc::mat3<T> m3_4(v, v, v, v, v, v, v, v, v);
    qc::mat3<T> m3_6(m2);
    qc::mat3<T> m3_7(m4);
    qc::mat3<T> m3_8(v3, v3, v3);

    // assignment

    m3 = m3;
    m3 = std::move(m3);
    m3 = m2;
    m3 = m4;

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

    qc::mat4<T> m4_1;
    qc::mat4<T> m4_2(m4);
    qc::mat4<T> m4_3(std::move(m4));
    qc::mat4<T> m4_4(v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v);
    qc::mat4<T> m4_6(m2);
    qc::mat4<T> m4_7(m3);
    qc::mat4<T> m4_8(v4, v4, v4, v4);

    // assignment

    m4 = m4;
    m4 = std::move(m4);
    m4 = m2;
    m4 = m3;

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

void compileClasses() {
    compileClassesT< float>();
    compileClassesT<double>();
}

template <typename T>
constexpr void compileClassesConstexprT() {
    constexpr T v(T(1.0));
    constexpr qc::vec2<T> v2(T(1.0));
    constexpr qc::vec3<T> v3(T(1.0));
    constexpr qc::vec4<T> v4(T(1.0));
    constexpr qc::mat2<T> m2(v2, v2);
    constexpr qc::mat3<T> m3(v3, v3, v3);
    constexpr qc::mat4<T> m4(v4, v4, v4, v4);

    //--------------------------------------------------------------------------
    // Mat2

    // constructors

    constexpr qc::mat2<T> m2_1;
    constexpr qc::mat2<T> m2_2(m2);
    constexpr qc::mat2<T> m2_3(std::move(m2));
    constexpr qc::mat2<T> m2_4(v, v, v, v);
    constexpr qc::mat2<T> m2_6(m3);
    constexpr qc::mat2<T> m2_7(m4);
    constexpr qc::mat2<T> m2_8(v2, v2);

    // access

    m2.col<0>(); m2.col<1>();
    m2.row<0>(); m2.row<1>();

    //--------------------------------------------------------------------------
    // Mat3

    // constructors

    constexpr qc::mat3<T> m3_1;
    constexpr qc::mat3<T> m3_2(m3);
    constexpr qc::mat3<T> m3_3(std::move(m3));
    constexpr qc::mat3<T> m3_4(v, v, v, v, v, v, v, v, v);
    constexpr qc::mat3<T> m3_6(m2);
    constexpr qc::mat3<T> m3_7(m4);
    constexpr qc::mat3<T> m3_8(v3, v3, v3);

    // access

    m3.col<0>(); m3.col<1>(); m3.col<2>();
    m3.row<0>(); m3.row<1>(); m3.row<2>();

    //--------------------------------------------------------------------------
    // Mat4

    // constructors

    constexpr qc::mat4<T> m4_1;
    constexpr qc::mat4<T> m4_2(m4);
    constexpr qc::mat4<T> m4_3(std::move(m4));
    constexpr qc::mat4<T> m4_4(v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v);
    constexpr qc::mat4<T> m4_6(m2);
    constexpr qc::mat4<T> m4_7(m3);
    constexpr qc::mat4<T> m4_8(v4, v4, v4, v4);

    // access

    m4.col<0>(); m4.col<1>(); m4.col<2>(); m4.col<3>();
    m4.row<0>(); m4.row<1>(); m4.row<2>(); m4.row<3>();

}

constexpr bool compileClassesConstexpr() {
    compileClassesConstexprT< float>();
    compileClassesConstexprT<double>();

    return true;
}

template <typename T>
void compileFunctionsT() {
    T v(1.0);
    qc::vec2<T> v2;
    qc::vec3<T> v3;
    qc::vec4<T> v4;
    qc::mat2<T> m2;
    qc::mat3<T> m3;
    qc::mat4<T> m4;
    
    qc::isIdentity(m2);
    qc::isIdentity(m3);
    qc::isIdentity(m4);
    qc::transpose(m2);
    qc::transpose(m3);
    qc::transpose(m4);
    qc::cofactor(m2);
    qc::cofactor(m3);
    qc::cofactor(m4);
    qc::adjoint(m2);
    qc::adjoint(m3);
    qc::adjoint(m4);
    qc::determinant(m2);
    qc::determinant(m3);
    qc::determinant(m4);
    qc::inverse(m2);
    qc::inverse(m3);
    qc::inverse(m4);
    qc::fullMat<T, 2>(v);
    qc::fullMat<T, 3>(v);
    qc::fullMat<T, 4>(v);
    qc::nullMat<T, 2>();
    qc::nullMat<T, 3>();
    qc::nullMat<T, 4>();

    qc::translate(v2);
    qc::translate(v3);
    qc::translate(m3, v2);
    qc::translate(m4, v3);
    qc::scale(v2);
    qc::scale(v3);
    qc::scale(v4);
    qc::scale(m2, v2);
    qc::scale(m3, v2);
    qc::scale(m3, v3);
    qc::scale(m4, v3);
    qc::rotate(v);
    qc::rotateX(v);
    qc::rotateY(v);
    qc::rotateZ(v);
    qc::rotate(v3, v, v);
    qc::rotate_n(v3, v, v);
    qc::rotate(v3, v);
    qc::rotate_n(v3, v);
    qc::euler(v3, v3, v, v, v);
    qc::euler_n(v3, v3, v, v, v);
    qc::align(v2, v2);
    qc::align(v3, v3);
    qc::align_n(v2, v2);
    qc::align_n(v3, v3);
    qc::align(v3, v3, v3, v3);
    qc::align_n(v3, v3, v3, v3);
    qc::map(v2, v2, v2, v2);
    qc::map_o(v2, v2, v2, v2);
    qc::map(v3, v3, v3, v3, v3, v3);
    qc::map_o(v3, v3, v3, v3, v3, v3);
    qc::mapTo(v2, v2);
    qc::mapTo_o(v2, v2);
    qc::mapTo(v3, v3, v3);
    qc::mapTo_o(v3, v3, v3);
    qc::mapFrom(v2, v2);
    qc::mapFrom(v3, v3, v3);
    qc::orthoProj(v, v, v, v);
    qc::orthoProjAsym(v, v, v, v, v, v);
    qc::perspProj(v, v, v, v);
    qc::perspProjAsym(v, v, v, v, v, v);
    qc::view(v3, v3, v3);
    qc::view(v3, v3, v3, v3);
    qc::view_n(v3, v3, v3, v3);
    qc::view_o(v3, v3, v3, v3);
    qc::view_on(v3, v3, v3, v3);
}

void compileFunctions() {
    compileFunctionsT< float>();
    compileFunctionsT<double>();
}

template <typename T>
constexpr void compileFunctionsConstexprT() {
    constexpr T v(T(1.0));
    constexpr qc::vec2<T> v2(T(1.0));
    constexpr qc::vec3<T> v3(T(1.0));
    constexpr qc::vec4<T> v4(T(1.0));
    constexpr qc::mat2<T> m2(v2, v2);
    constexpr qc::mat3<T> m3(v3, v3, v3);
    constexpr qc::mat4<T> m4(v4, v4, v4, v4);
    
    qc::fullMat<T, 2>(v);
    qc::fullMat<T, 3>(v);
    qc::fullMat<T, 4>(v);
    qc::nullMat<T, 2>();
    qc::nullMat<T, 3>();
    qc::nullMat<T, 4>();
}

constexpr bool compileFunctionsConstexpr() {
    compileFunctionsConstexprT< float>();
    compileFunctionsConstexprT<double>();

    return true;
}

template <typename T, int t_n>
void testPropertiesTN() {
    static_assert(std::             is_standard_layout_v<qc::mat<T, t_n>>);
    static_assert(std::          is_trivially_copyable_v<qc::mat<T, t_n>>);
    static_assert(std::is_trivially_copy_constructible_v<qc::mat<T, t_n>>);
    static_assert(std::is_trivially_move_constructible_v<qc::mat<T, t_n>>);
    static_assert(std::   is_trivially_copy_assignable_v<qc::mat<T, t_n>>);
    static_assert(std::   is_trivially_move_assignable_v<qc::mat<T, t_n>>);
    static_assert(std::      is_trivially_destructible_v<qc::mat<T, t_n>>);
    static_assert(sizeof(qc::mat<T, t_n>) == t_n * t_n * sizeof(T));
    static_assert(sizeof(qc::mat<T, t_n>[4]) == 4 * t_n * t_n * sizeof(T));
    static_assert(alignof(qc::mat<T, t_n>) == alignof(T));
    static_assert(alignof(qc::mat<T, t_n>[4]) == alignof(T));
}

template <typename T>
void testPropertiesT() {
    testPropertiesTN<T, 2>();
    testPropertiesTN<T, 3>();
    testPropertiesTN<T, 4>();
}

void testProperties() {
    testPropertiesT< float>();
    testPropertiesT<double>();
}

template <typename T1, typename T2>
void compileCastsTT() {
    static_cast<qc::mat2<T2>>(qc::mat2<T1>());
    static_cast<qc::mat3<T2>>(qc::mat3<T1>());
    static_cast<qc::mat4<T2>>(qc::mat4<T1>());
}

template <typename T>
void compileCastsT() {
    compileCastsTT<T,  float>();
    compileCastsTT<T, double>();
}

void compileCasts() {
    compileCastsT< float>();
    compileCastsT<double>();
}



}



void testMatrix() {
    compileClasses();
    static_assert(compileClassesConstexpr(), "");
    compileFunctions();
    static_assert(compileFunctionsConstexpr(), "");
    testProperties();
    compileCasts();
}