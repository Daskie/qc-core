#include "QMUTest.hpp"

#include "QMU/Matrix.hpp"



using namespace qmu;



namespace {



template <typename T>
void testTCompilation() {
    T v;
    vec1<T> v1;
    vec2<T> v2;
    vec3<T> v3;
    vec4<T> v4;
    mat2<T> m2;
    mat3<T> m3;
    mat4<T> m4;
    std::stringstream os;

    //--------------------------------------------------------------------------
    // Mav2

    // constructors
    mat2<T> m2_1;
    mat2<T> m2_2(m2);
    mat2<T> m2_3(std::move(m2));
    mat2<T> m2_4(v, v, v, v);
    mat2<T> m2_5(m3);
    mat2<T> m2_6(m4);
    mat2<T> m2_7(v2, v2);

    // assignment operators
    m2 = m2;
    m2 = std::move(m2);
    m2 = m3;
    m2 = m4;

    // access operators
    m2[0];
    static_cast<const mat2<T>>(m2)[0];

    // arithmetic assignment operators
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
    m2.col(0);
    m2.row(0);

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

    // assignment operators
    m3 = m3;
    m3 = std::move(m3);
    m3 = m2;
    m3 = m4;

    // access operators
    m3[0];
    static_cast<const mat3<T>>(m3)[0];

    // arithmetic assignment operators
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
    m3.col(0);
    m3.row(0);

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

    // assignment operators
    m4 = m4;
    m4 = std::move(m4);
    m4 = m2;
    m4 = m3;

    // access operators
    m4[0];
    static_cast<const mat4<T>>(m4)[0];

    // arithmetic assignment operators
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
    m4.col(0);
    m4.row(0);

    //--------------------------------------------------------------------------
    // Mat Functions

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

    //--------------------------------------------------------------------------
    // Transformations

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

template <typename T, nat t_n>
void testTNProperties() {
    static_assert(std::is_standard_layout<mat<T, t_n>>::value, "");
    static_assert(sizeof(mat<T, t_n>) == t_n * t_n * sizeof(T), "");
}

template <typename T>
void testTProperties() {
    testTNProperties<T, 2>();
    testTNProperties<T, 3>();
    testTNProperties<T, 4>();
}

void testCompilation() {
    testTCompilation<float>();
    testTCompilation<double>();

    testTProperties<float>();
    testTProperties<double>();
}

template <typename T1, typename T2>
void testTTCasts() {
    static_cast<mat2<T2>>(mat2<T1>());
    static_cast<mat3<T2>>(mat3<T1>());
    static_cast<mat4<T2>>(mat4<T1>());
}

template <typename T>
void testTCasts() {
    testTTCasts<T,  float>();
    testTTCasts<T, double>();
}

void testCasts() {
    testTCasts< float>();
    testTCasts<double>();
}



}



void testMatrix() {
    testCompilation();
    testCasts();
}