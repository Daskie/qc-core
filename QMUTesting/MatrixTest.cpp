#include "QMUTest.hpp"

#include "QMU/Matrix.hpp"



using namespace qmu;



namespace {



template <typename T>
void compileClassesT() {
    T v(1.0);
    vec1<T> v1;
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
    mat2<T> m2_5(m3);
    mat2<T> m2_6(m4);
    mat2<T> m2_7(v2, v2);

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
    ++m2;
    m2++;
    --m2;
    m2--;

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
    mat3<T> m3_1;
    mat3<T> m3_2(m3);
    mat3<T> m3_3(std::move(m3));
    mat3<T> m3_4(v, v, v, v, v, v, v, v, v);
    mat3<T> m3_5(m2);
    mat3<T> m3_6(m4);
    mat3<T> m3_7(v3, v3, v3);

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
    ++m3;
    m3++;
    --m3;
    m3--;

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
    mat4<T> m4_1;
    mat4<T> m4_2(m4);
    mat4<T> m4_3(std::move(m4));
    mat4<T> m4_4(v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v);
    mat4<T> m4_5(m2);
    mat4<T> m4_6(m3);
    mat4<T> m4_7(v4, v4, v4, v4);

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
    ++m4;
    m4++;
    --m4;
    m4--;

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
    constexpr T v(static_cast<T>(1.0));
    constexpr vec1<T> v1(static_cast<T>(1.0));
    constexpr vec2<T> v2(static_cast<T>(1.0));
    constexpr vec3<T> v3(static_cast<T>(1.0));
    constexpr vec4<T> v4(static_cast<T>(1.0));
    constexpr mat2<T> m2(v2, v2);
    constexpr mat3<T> m3(v3, v3, v3);
    constexpr mat4<T> m4(v4, v4, v4, v4);

    //--------------------------------------------------------------------------
    // Mat2

    // constructors
    constexpr mat2<T> m2_1;
    constexpr mat2<T> m2_2(m2);
    constexpr mat2<T> m2_3(std::move(m2));
    constexpr mat2<T> m2_4(v, v, v, v);
    constexpr mat2<T> m2_5(m3);
    constexpr mat2<T> m2_6(m4);
    constexpr mat2<T> m2_7(v2, v2);

    // access

    m2.at<0, 0>(); m2.at<0, 1>();
    m2.at<1, 0>(); m2.at<1, 1>();

    m2.row<0>(); m2.row<1>();
    m2.col<0>(); m2.col<1>();

    //--------------------------------------------------------------------------
    // Mat3

    // constructors
    constexpr mat3<T> m3_1;
    constexpr mat3<T> m3_2(m3);
    constexpr mat3<T> m3_3(std::move(m3));
    constexpr mat3<T> m3_4(v, v, v, v, v, v, v, v, v);
    constexpr mat3<T> m3_5(m2);
    constexpr mat3<T> m3_6(m4);
    constexpr mat3<T> m3_7(v3, v3, v3);

    // access

    m3.at<0, 0>(); m3.at<0, 1>(); m3.at<0, 2>();
    m3.at<1, 0>(); m3.at<1, 1>(); m3.at<1, 2>();
    m3.at<2, 0>(); m3.at<2, 1>(); m3.at<2, 2>();

    m3.row<0>(); m3.row<1>(); m3.row<2>();
    m3.col<0>(); m3.col<1>(); m3.col<2>();

    //--------------------------------------------------------------------------
    // Mat4

    // constructors
    constexpr mat4<T> m4_1;
    constexpr mat4<T> m4_2(m4);
    constexpr mat4<T> m4_3(std::move(m4));
    constexpr mat4<T> m4_4(v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v);
    constexpr mat4<T> m4_5(m2);
    constexpr mat4<T> m4_6(m3);
    constexpr mat4<T> m4_7(v4, v4, v4, v4);

    // access

    m4.at<0, 0>(); m4.at<0, 1>(); m4.at<0, 2>(); m4.at<0, 3>();
    m4.at<1, 0>(); m4.at<1, 1>(); m4.at<1, 2>(); m4.at<1, 3>();
    m4.at<2, 0>(); m4.at<2, 1>(); m4.at<2, 2>(); m4.at<2, 3>();
    m4.at<3, 0>(); m4.at<3, 1>(); m4.at<3, 2>(); m4.at<3, 3>();

    m4.row<0>(); m4.row<1>(); m4.row<2>(); m4.row<3>();
    m4.col<0>(); m4.col<1>(); m4.col<2>(); m4.col<3>();
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
    vec1<T> v1;
    vec2<T> v2;
    vec3<T> v3;
    vec4<T> v4;
    mat2<T> m2;
    mat3<T> m3;
    mat4<T> m4;

    transpose(m2);
    transpose(m3);
    transpose(m4);
    cofactor(m2);
    cofactor(m3);
    cofactor(m4);
    adjoint(m2);
    adjoint(m3);
    adjoint(m4);
    determinant(m2);
    determinant(m3);
    determinant(m4);
    inverse(m2);
    inverse(m3);
    inverse(m4);
    fullMat<T, 2>(v);
    fullMat<T, 3>(v);
    fullMat<T, 4>(v);
    nullMat<T, 2>();
    nullMat<T, 3>();
    nullMat<T, 4>();

    translate(v1);
    translate(v2);
    translate(v3);
    translate(m2, v1);
    translate(m3, v2);
    translate(m4, v3);
    scale(v2);
    scale(v3);
    scale(m2, v1);
    scale(m2, v2);
    scale(m3, v2);
    scale(m3, v3);
    scale(m4, v3);
    scale(m4, v4);
    rotate(v);
    rotateX(v);
    rotateY(v);
    rotateZ(v);
    rotate(v3, v, v);
    rotate_n(v3, v, v);
    rotate(v3, v);
    rotate_n(v3, v);
    euler(v3, v3, v, v, v);
    euler_n(v3, v3, v, v, v);
    align(v2, v2);
    align(v3, v3);
    align_n(v2, v2);
    align_n(v3, v3);
    align(v3, v3, v3, v3);
    align_n(v3, v3, v3, v3);
    map(v2, v2, v2, v2);
    map_o(v2, v2, v2, v2);
    map(v3, v3, v3, v3, v3, v3);
    map_o(v3, v3, v3, v3, v3, v3);
    mapTo(v2, v2);
    mapTo_o(v2, v2);
    mapTo(v3, v3, v3);
    mapTo_o(v3, v3, v3);
    mapFrom(v2, v2);
    mapFrom(v3, v3, v3);
    orthoProj(v, v, v, v);
    orthoProjAsym(v, v, v, v, v, v);
    perspProj(v, v, v, v);
    perspProjAsym(v, v, v, v, v, v);
    view(v3, v3, v3);
    view(v3, v3, v3, v3);
    view_n(v3, v3, v3, v3);
    view_o(v3, v3, v3, v3);
    view_on(v3, v3, v3, v3);
}

void compileFunctions() {
    compileFunctionsT<      float>();
    compileFunctionsT<     double>();
    compileFunctionsT<long double>();
}

template <typename T>
constexpr void compileFunctionsConstexprT() {
    constexpr T v(static_cast<T>(1.0));
    constexpr vec1<T> v1(static_cast<T>(1.0));
    constexpr vec2<T> v2(static_cast<T>(1.0));
    constexpr vec3<T> v3(static_cast<T>(1.0));
    constexpr vec4<T> v4(static_cast<T>(1.0));
    constexpr mat2<T> m2(v2, v2);
    constexpr mat3<T> m3(v3, v3, v3);
    constexpr mat4<T> m4(v4, v4, v4, v4);

    fullMat<T, 2>(v);
    fullMat<T, 3>(v);
    fullMat<T, 4>(v);
    nullMat<T, 2>();
    nullMat<T, 3>();
    nullMat<T, 4>();
}

constexpr bool compileFunctionsConstexpr() {
    compileFunctionsConstexprT<      float>();
    compileFunctionsConstexprT<     double>();
    compileFunctionsConstexprT<long double>();

    return true;
}

template <typename T, nat t_n>
void testPropertiesTN() {
    static_assert(std::is_standard_layout<mat<T, t_n>>::value, "");
    static_assert(sizeof(mat<T, t_n>) == t_n * t_n * sizeof(T), "");
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
    static_cast<mat2<T2>>(mat2<T1>());
    static_cast<mat3<T2>>(mat3<T1>());
    static_cast<mat4<T2>>(mat4<T1>());
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