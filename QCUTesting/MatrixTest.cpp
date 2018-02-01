#include "QCUTest.hpp"

#include "QCU/Matrix.hpp"



namespace {



template <typename T>
void compileClassesT() {
    T v(1.0);
    qcu::vec1<T> v1;
    qcu::vec2<T> v2;
    qcu::vec3<T> v3;
    qcu::vec4<T> v4;
    qcu::mat2<T> m2;
    qcu::mat3<T> m3;
    qcu::mat4<T> m4;
    std::stringstream os;

    //--------------------------------------------------------------------------
    // Mat2

    // constructors
    qcu::mat2<T> m2_1;
    qcu::mat2<T> m2_2(m2);
    qcu::mat2<T> m2_3(std::move(m2));
    qcu::mat2<T> m2_4(v, v, v, v);
    qcu::mat2<T> m2_5(m3);
    qcu::mat2<T> m2_6(m4);
    qcu::mat2<T> m2_7(v2, v2);

    // assignment
    m2 = m2;
    m2 = std::move(m2);
    m2 = m3;
    m2 = m4;

    // access
    m2[0];

    m2.at<0, 0>(); m2.at<0, 1>();
    m2.at<1, 0>(); m2.at<1, 1>();
    
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
    m2.toString();
    os << m2;

    //--------------------------------------------------------------------------
    // Mat3

    // constructors
    qcu::mat3<T> m3_1;
    qcu::mat3<T> m3_2(m3);
    qcu::mat3<T> m3_3(std::move(m3));
    qcu::mat3<T> m3_4(v, v, v, v, v, v, v, v, v);
    qcu::mat3<T> m3_5(m2);
    qcu::mat3<T> m3_6(m4);
    qcu::mat3<T> m3_7(v3, v3, v3);

    // assignment
    m3 = m3;
    m3 = std::move(m3);
    m3 = m2;
    m3 = m4;

    // access
    m3[0];

    m3.at<0, 0>(); m3.at<0, 1>(); m3.at<0, 2>();
    m3.at<1, 0>(); m3.at<1, 1>(); m3.at<1, 2>();
    m3.at<2, 0>(); m3.at<2, 1>(); m3.at<2, 2>();
    
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
    m3.toString();
    os << m3;

    //--------------------------------------------------------------------------
    // Mat4

    // constructors
    qcu::mat4<T> m4_1;
    qcu::mat4<T> m4_2(m4);
    qcu::mat4<T> m4_3(std::move(m4));
    qcu::mat4<T> m4_4(v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v);
    qcu::mat4<T> m4_5(m2);
    qcu::mat4<T> m4_6(m3);
    qcu::mat4<T> m4_7(v4, v4, v4, v4);

    // assignment
    m4 = m4;
    m4 = std::move(m4);
    m4 = m2;
    m4 = m3;

    // access
    m4[0];

    m4.at<0, 0>(); m4.at<0, 1>(); m4.at<0, 2>(); m4.at<0, 3>();
    m4.at<1, 0>(); m4.at<1, 1>(); m4.at<1, 2>(); m4.at<1, 3>();
    m4.at<2, 0>(); m4.at<2, 1>(); m4.at<2, 2>(); m4.at<2, 3>();
    m4.at<3, 0>(); m4.at<3, 1>(); m4.at<3, 2>(); m4.at<3, 3>();

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
    m4.toString();
    os << m4;
}

void compileClasses() {
    compileClassesT<      float>();
    compileClassesT<     double>();
    compileClassesT<long double>();
}

template <typename T>
constexpr void compileClassesConstexprT() {
    constexpr T v(T(1.0));
    constexpr qcu::vec1<T> v1(T(1.0));
    constexpr qcu::vec2<T> v2(T(1.0));
    constexpr qcu::vec3<T> v3(T(1.0));
    constexpr qcu::vec4<T> v4(T(1.0));
    constexpr qcu::mat2<T> m2(v2, v2);
    constexpr qcu::mat3<T> m3(v3, v3, v3);
    constexpr qcu::mat4<T> m4(v4, v4, v4, v4);

    //--------------------------------------------------------------------------
    // Mat2

    // constructors
    constexpr qcu::mat2<T> m2_1;
    constexpr qcu::mat2<T> m2_2(m2);
    constexpr qcu::mat2<T> m2_3(std::move(m2));
    constexpr qcu::mat2<T> m2_4(v, v, v, v);
    constexpr qcu::mat2<T> m2_5(m3);
    constexpr qcu::mat2<T> m2_6(m4);
    constexpr qcu::mat2<T> m2_7(v2, v2);

    // access

    m2.at<0, 0>(); m2.at<0, 1>();
    m2.at<1, 0>(); m2.at<1, 1>();

    //--------------------------------------------------------------------------
    // Mat3

    // constructors
    constexpr qcu::mat3<T> m3_1;
    constexpr qcu::mat3<T> m3_2(m3);
    constexpr qcu::mat3<T> m3_3(std::move(m3));
    constexpr qcu::mat3<T> m3_4(v, v, v, v, v, v, v, v, v);
    constexpr qcu::mat3<T> m3_5(m2);
    constexpr qcu::mat3<T> m3_6(m4);
    constexpr qcu::mat3<T> m3_7(v3, v3, v3);

    // access

    m3.at<0, 0>(); m3.at<0, 1>(); m3.at<0, 2>();
    m3.at<1, 0>(); m3.at<1, 1>(); m3.at<1, 2>();
    m3.at<2, 0>(); m3.at<2, 1>(); m3.at<2, 2>();

    //--------------------------------------------------------------------------
    // Mat4

    // constructors

    constexpr qcu::mat4<T> m4_1;
    constexpr qcu::mat4<T> m4_2(m4);
    constexpr qcu::mat4<T> m4_3(std::move(m4));
    constexpr qcu::mat4<T> m4_4(v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v);
    constexpr qcu::mat4<T> m4_5(m2);
    constexpr qcu::mat4<T> m4_6(m3);
    constexpr qcu::mat4<T> m4_7(v4, v4, v4, v4);

    // access

    m4.at<0, 0>(); m4.at<0, 1>(); m4.at<0, 2>(); m4.at<0, 3>();
    m4.at<1, 0>(); m4.at<1, 1>(); m4.at<1, 2>(); m4.at<1, 3>();
    m4.at<2, 0>(); m4.at<2, 1>(); m4.at<2, 2>(); m4.at<2, 3>();
    m4.at<3, 0>(); m4.at<3, 1>(); m4.at<3, 2>(); m4.at<3, 3>();

}

constexpr bool compileClassesConstexpr() {
    compileClassesConstexprT<      float>();
    compileClassesConstexprT<     double>();
    compileClassesConstexprT<long double>();

    return true;
}

template <typename T>
void compileFunctionsT() {
    T v(1.0);
    qcu::vec1<T> v1;
    qcu::vec2<T> v2;
    qcu::vec3<T> v3;
    qcu::vec4<T> v4;
    qcu::mat2<T> m2;
    qcu::mat3<T> m3;
    qcu::mat4<T> m4;

    qcu::isIdentity(m2);
    qcu::isIdentity(m3);
    qcu::isIdentity(m4);
    qcu::transpose(m2);
    qcu::transpose(m3);
    qcu::transpose(m4);
    qcu::cofactor(m2);
    qcu::cofactor(m3);
    qcu::cofactor(m4);
    qcu::adjoint(m2);
    qcu::adjoint(m3);
    qcu::adjoint(m4);
    qcu::determinant(m2);
    qcu::determinant(m3);
    qcu::determinant(m4);
    qcu::inverse(m2);
    qcu::inverse(m3);
    qcu::inverse(m4);
    qcu::fullMat<T, 2>(v);
    qcu::fullMat<T, 3>(v);
    qcu::fullMat<T, 4>(v);
    qcu::nullMat<T, 2>();
    qcu::nullMat<T, 3>();
    qcu::nullMat<T, 4>();

    qcu::translate(v1);
    qcu::translate(v2);
    qcu::translate(v3);
    qcu::translate(m2, v1);
    qcu::translate(m3, v2);
    qcu::translate(m4, v3);
    qcu::scale(v2);
    qcu::scale(v3);
    qcu::scale(m2, v1);
    qcu::scale(m2, v2);
    qcu::scale(m3, v2);
    qcu::scale(m3, v3);
    qcu::scale(m4, v3);
    qcu::rotate(v);
    qcu::rotateX(v);
    qcu::rotateY(v);
    qcu::rotateZ(v);
    qcu::rotate(v3, v, v);
    qcu::rotate_n(v3, v, v);
    qcu::rotate(v3, v);
    qcu::rotate_n(v3, v);
    qcu::euler(v3, v3, v, v, v);
    qcu::euler_n(v3, v3, v, v, v);
    qcu::align(v2, v2);
    qcu::align(v3, v3);
    qcu::align_n(v2, v2);
    qcu::align_n(v3, v3);
    qcu::align(v3, v3, v3, v3);
    qcu::align_n(v3, v3, v3, v3);
    qcu::map(v2, v2, v2, v2);
    qcu::map_o(v2, v2, v2, v2);
    qcu::map(v3, v3, v3, v3, v3, v3);
    qcu::map_o(v3, v3, v3, v3, v3, v3);
    qcu::mapTo(v2, v2);
    qcu::mapTo_o(v2, v2);
    qcu::mapTo(v3, v3, v3);
    qcu::mapTo_o(v3, v3, v3);
    qcu::mapFrom(v2, v2);
    qcu::mapFrom(v3, v3, v3);
    qcu::orthoProj(v, v, v, v);
    qcu::orthoProjAsym(v, v, v, v, v, v);
    qcu::perspProj(v, v, v, v);
    qcu::perspProjAsym(v, v, v, v, v, v);
    qcu::view(v3, v3, v3);
    qcu::view(v3, v3, v3, v3);
    qcu::view_n(v3, v3, v3, v3);
    qcu::view_o(v3, v3, v3, v3);
    qcu::view_on(v3, v3, v3, v3);
}

void compileFunctions() {
    compileFunctionsT<      float>();
    compileFunctionsT<     double>();
    compileFunctionsT<long double>();
}

template <typename T>
constexpr void compileFunctionsConstexprT() {
    constexpr T v(T(1.0));
    constexpr qcu::vec1<T> v1(T(1.0));
    constexpr qcu::vec2<T> v2(T(1.0));
    constexpr qcu::vec3<T> v3(T(1.0));
    constexpr qcu::vec4<T> v4(T(1.0));
    constexpr qcu::mat2<T> m2(v2, v2);
    constexpr qcu::mat3<T> m3(v3, v3, v3);
    constexpr qcu::mat4<T> m4(v4, v4, v4, v4);

    qcu::fullMat<T, 2>(v);
    qcu::fullMat<T, 3>(v);
    qcu::fullMat<T, 4>(v);
    qcu::nullMat<T, 2>();
    qcu::nullMat<T, 3>();
    qcu::nullMat<T, 4>();
}

constexpr bool compileFunctionsConstexpr() {
    compileFunctionsConstexprT<      float>();
    compileFunctionsConstexprT<     double>();
    compileFunctionsConstexprT<long double>();

    return true;
}

template <typename T, int t_n>
void testPropertiesTN() {
    static_assert(std::is_standard_layout_v<qcu::mat<T, t_n>>, "");
    static_assert(sizeof(qcu::mat<T, t_n>) == t_n * t_n * sizeof(T), "");
    static_assert(sizeof(qcu::mat<T, t_n>[4]) == 4 * t_n * t_n * sizeof(T));
    static_assert(alignof(qcu::mat<T, t_n>) == alignof(T));
    static_assert(alignof(qcu::mat<T, t_n>[4]) == alignof(T));
}

template <typename T>
void testPropertiesT() {
    testPropertiesTN<T, 2>();
    testPropertiesTN<T, 3>();
    testPropertiesTN<T, 4>();
}

void testProperties() {
    testPropertiesT<      float>();
    testPropertiesT<     double>();
    testPropertiesT<long double>();
}

template <typename T1, typename T2>
void compileCastsTT() {
    static_cast<qcu::mat2<T2>>(qcu::mat2<T1>());
    static_cast<qcu::mat3<T2>>(qcu::mat3<T1>());
    static_cast<qcu::mat4<T2>>(qcu::mat4<T1>());
}

template <typename T>
void compileCastsT() {
    compileCastsTT<T,      float>();
    compileCastsTT<T,      double>();
    compileCastsTT<T, long double>();
}

void compileCasts() {
    compileCastsT<      float>();
    compileCastsT<     double>();
    compileCastsT<long double>();
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