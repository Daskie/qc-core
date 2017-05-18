#include <iostream>
#include <sstream>

#include "QMU/QMU.hpp"
#include "QMU/Vector.hpp"
#include "QMU/Matrix.hpp"
#include "QMU/Quaternion.hpp"

using namespace qmu;

template <typename T>
void testVectorTCompilation() {
    T v;
    vec1<T> v1;
    vec2<T> v2;
    vec3<T> v3;
    vec4<T> v4;
    vec<T, 6> v6;
    vec<T, 8> v8;

    //--------------------------------------------------------------------------
    // Vec1
    
    // constructors
    vec1<T> v1_1;
    vec1<T> v1_2(v1);
    vec1<T> v1_3(std::move(v1));
    vec1<T> v1_4(v);
    vec1<T> v1_5(v2);
    vec1<T> v1_6(v3);
    vec1<T> v1_7(v4);
    
    // assignment operators
    v1 = v1;
    v1 = std::move(v1);
    v1 = v;
    v1 = v2;
    v1 = v3;
    v1 = v4;

    // access operators
    v1[0];
    static_cast<const vec1<T>>(v1)[0];

    // other
    v1.toString();

    //--------------------------------------------------------------------------
    // Vec2

    // constructors
    vec2<T> v2_01;
    vec2<T> v2_02(v2);
    vec2<T> v2_03(std::move(v2));
    vec2<T> v2_04(v);
    vec2<T> v2_05(v1);
    vec2<T> v2_06(v3);
    vec2<T> v2_07(v4);
    vec2<T> v2_08(v, v);
    vec2<T> v2_09(v1, v);
    vec2<T> v2_10(v, v1);
    vec2<T> v2_11(v1, v1);

    // assignment operators
    v2 = v2;
    v2 = std::move(v2);
    v2 = v;
    v2 = v1;
    v2 = v3;
    v2 = v4;

    // access operators
    v2[0];
    static_cast<const vec2<T>>(v2)[0];

    // other
    v2.toString();

    //--------------------------------------------------------------------------
    // Vec3

    // constructors
    vec3<T> v3_01;
    vec3<T> v3_02(v3);
    vec3<T> v3_03(std::move(v3));
    vec3<T> v3_04(v);
    vec3<T> v3_05(v1);
    vec3<T> v3_06(v2);
    vec3<T> v3_07(v4);
    vec3<T> v3_08(v, v, v);
    vec3<T> v3_09(v1, v, v);
    vec3<T> v3_10(v, v1, v);
    vec3<T> v3_11(v, v, v1);
    vec3<T> v3_12(v1, v1, v);
    vec3<T> v3_13(v1, v, v1);
    vec3<T> v3_14(v, v1, v1);
    vec3<T> v3_15(v1, v1, v1);
    vec3<T> v3_16(v2, v);
    vec3<T> v3_17(v2, v1);
    vec3<T> v3_18(v, v2);
    vec3<T> v3_19(v1, v2);

    // assignment operators
    v3 = v3;
    v3 = std::move(v3);
    v3 = v;
    v3 = v1;
    v3 = v2;
    v3 = v4;

    // access operators
    v3[0];
    static_cast<const vec3<T>>(v3)[0];

    // other
    v3.toString();

    //--------------------------------------------------------------------------
    // Vec4

    // constructors
    vec4<T> v4_01;
    vec4<T> v4_02(v4);
    vec4<T> v4_03(std::move(v4));
    vec4<T> v4_04(v);
    vec4<T> v4_05(v1);
    vec4<T> v4_06(v2);
    vec4<T> v4_07(v3);
    vec4<T> v4_08(v, v, v, v);
    vec4<T> v4_09(v1, v, v, v);
    vec4<T> v4_10(v, v1, v, v);
    vec4<T> v4_11(v, v, v1, v);
    vec4<T> v4_12(v, v, v, v1);
    vec4<T> v4_13(v1, v1, v, v);
    vec4<T> v4_14(v1, v, v1, v);
    vec4<T> v4_15(v1, v, v, v1);
    vec4<T> v4_16(v, v1, v, v1);
    vec4<T> v4_17(v, v, v1, v1);
    vec4<T> v4_18(v1, v1, v1, v);
    vec4<T> v4_19(v1, v1, v, v1);
    vec4<T> v4_20(v1, v, v1, v1);
    vec4<T> v4_21(v, v1, v1, v1);
    vec4<T> v4_22(v1, v1, v1, v1);
    vec4<T> v4_23(v2, v, v);
    vec4<T> v4_24(v2, v1, v);
    vec4<T> v4_25(v2, v, v1);
    vec4<T> v4_26(v2, v1, v1);
    vec4<T> v4_27(v, v2, v);
    vec4<T> v4_28(v1, v2, v);
    vec4<T> v4_29(v, v2, v1);
    vec4<T> v4_30(v1, v2, v1);
    vec4<T> v4_31(v, v, v2);
    vec4<T> v4_32(v1, v, v2);
    vec4<T> v4_33(v, v1, v2);
    vec4<T> v4_34(v1, v1, v2);
    vec4<T> v4_35(v2, v2);
    vec4<T> v4_36(v3, v);
    vec4<T> v4_37(v3, v1);
    vec4<T> v4_38(v, v3);
    vec4<T> v4_39(v1, v3);

    // assignment operators
    v4 = v4;
    v4 = std::move(v4);
    v4 = v;
    v4 = v1;
    v4 = v2;
    v4 = v3;

    // access operators
    v4[0];
    static_cast<const vec4<T>>(v4)[0];

    // other
    v4.toString();

    //--------------------------------------------------------------------------
    // Vec6

    // constructors
    vec<T, 6> v6_1;
    vec<T, 6> v6_2(v6);
    vec<T, 6> v6_3(std::move(v6));
    vec<T, 8> v6_4(v2);
    vec<T, 8> v6_5(v4);
    vec<T, 8> v6_6(v8);
    vec<T, 6> v6_7(v3, v3);
    vec<T, 6> v6_8(v, v, v, v, v, v);

    // asignment operators
    v6 = v6;
    v6 = std::move(v6);

    // access operators
    v6[0];
    static_cast<const vec<T, 6>>(v6)[0];

    // other
    v6.toString();

    //--------------------------------------------------------------------------
    // Vec8

    // constructors
    vec<T, 8> v8_1;
    vec<T, 8> v8_2(v8);
    vec<T, 8> v8_3(std::move(v8));
    vec<T, 8> v8_4(v2);
    vec<T, 8> v8_5(v4);
    vec<T, 8> v8_6(v6);
    vec<T, 8> v8_7(v4, v4);
    vec<T, 8> v8_8(v, v, v, v, v, v, v, v);

    // asignment operators
    v8 = v8;
    v8 = std::move(v8);

    // access operators
    v8[0];
    static_cast<const vec<T, 8>>(v8)[0];

    // other
    v8.toString();
}

template <typename T>
void testVectorTFunctionCompilation() {
    T v;
    vec1<T> v1;
    vec2<T> v2;
    vec3<T> v3;
    vec4<T> v4;
    vec<T, 6> v6;
    vec<T, 8> v8;
    std::stringstream os;

    // arithmetic

    v1 += v1;
    v2 += v2;
    v3 += v3;
    v4 += v4;
    v1 += v;
    v2 += v;
    v3 += v;
    v4 += v;

    v1 -= v1;
    v2 -= v2;
    v3 -= v3;
    v4 -= v4;
    v1 -= v;
    v2 -= v;
    v3 -= v;
    v4 -= v;

    v1 *= v1;
    v2 *= v2;
    v3 *= v3;
    v4 *= v4;
    v1 *= v;
    v2 *= v;
    v3 *= v;
    v4 *= v;

    v1 /= vec1<T>(1);
    v2 /= vec2<T>(1);
    v3 /= vec3<T>(1);
    v4 /= vec4<T>(1);
    v1 /= T(1);
    v2 /= T(1);
    v3 /= T(1);
    v4 /= T(1);

    ++v1;
    ++v2;
    ++v3;
    ++v4;

    v1++;
    v2++;
    v3++;
    v4++;

    --v1;
    --v2;
    --v3;
    --v4;

    v1--;
    v2--;
    v3--;
    v4--;

    +v1;
    +v2;
    +v3;
    +v4;

    -v1;
    -v2;
    -v3;
    -v4;

    v1 + v1;
    v2 + v2;
    v3 + v3;
    v4 + v4;
    v1 + v;
    v2 + v;
    v3 + v;
    v4 + v;
    v + v1;
    v + v2;
    v + v3;
    v + v4;

    v1 - v1;
    v2 - v2;
    v3 - v3;
    v4 - v4;
    v1 - v;
    v2 - v;
    v3 - v;
    v4 - v;
    v - v1;
    v - v2;
    v - v3;
    v - v4;

    v1 * v1;
    v2 * v2;
    v3 * v3;
    v4 * v4;
    v1 * v;
    v2 * v;
    v3 * v;
    v4 * v;
    v * v1;
    v * v2;
    v * v3;
    v * v4;

    v1 / vec1<T>(1);
    v2 / vec2<T>(1);
    v3 / vec3<T>(1);
    v4 / vec4<T>(1);
    v1 / T(1);
    v2 / T(v);
    v3 / T(v);
    v4 / T(v);
    v / vec1<T>(1);
    v / vec2<T>(1);
    v / vec3<T>(1);
    v / vec4<T>(1);


    // comparison

    v1 == v1;
    v2 == v2;
    v3 == v3;
    v4 == v4;
    v6 == v6;
    v8 == v8;
    v1 == v;
    v2 == v;
    v3 == v;
    v4 == v;
    v == v1;
    v == v2;
    v == v3;
    v == v4;

    v1 != v1;
    v2 != v2;
    v3 != v3;
    v4 != v4;
    v6 != v6;
    v8 != v8;
    v1 != v;
    v2 != v;
    v3 != v;
    v4 != v;
    v != v1;
    v != v2;
    v != v3;
    v != v4;

    v1 < v1;
    v2 < v2;
    v3 < v3;
    v4 < v4;
    v1 < v;
    v2 < v;
    v3 < v;
    v4 < v;
    v < v1;
    v < v2;
    v < v3;
    v < v4;

    v1 > v1;
    v2 > v2;
    v3 > v3;
    v4 > v4;
    v1 > v;
    v2 > v;
    v3 > v;
    v4 > v;
    v > v1;
    v > v2;
    v > v3;
    v > v4;

    v1 <= v1;
    v2 <= v2;
    v3 <= v3;
    v4 <= v4;
    v1 <= v;
    v2 <= v;
    v3 <= v;
    v4 <= v;
    v <= v1;
    v <= v2;
    v <= v3;
    v <= v4;

    v1 >= v1;
    v2 >= v2;
    v3 >= v3;
    v4 >= v4;
    v1 >= v;
    v2 >= v;
    v3 >= v;
    v4 >= v;
    v >= v1;
    v >= v2;
    v >= v3;
    v >= v4;

    // other

    os << v1;
    os << v2;
    os << v3;
    os << v4;
    os << v6;
    os << v8;

    // uncategorized

    magnitude(v1);
    magnitude(v2);
    magnitude(v3);
    magnitude(v4);
    
    magnitude2(v1);
    magnitude2(v2);
    magnitude2(v3);
    magnitude2(v4);

    normalize(v1);
    normalize(v2);
    normalize(v3);
    normalize(v4);

    dot(v1, v1);
    dot(v2, v2);
    dot(v3, v3);
    dot(v4, v4);

    cross(v2, v2);
    cross(v3, v3);

    reflect(v2, v2);
    reflect(v3, v3);

    angle(v1, v1);
    angle_n(v1, v1);
    angle(v2, v2);
    angle_n(v2, v2);
    angle(v3, v3);
    angle_n(v3, v3);
    angle(v4, v4);
    angle_n(v4, v4);

    orthogonal(v2);
    orthogonal(v3);

    min(v1);
    min(v2);
    min(v3);
    min(v4);
    
    max(v1);
    max(v2);
    max(v3);
    max(v4);

    min(v1, v1);
    min(v2, v2);
    min(v3, v3);
    min(v4, v4);

    max(v1, v1);
    max(v2, v2);
    max(v3, v3);
    max(v4, v4);

    clamp(v1, v, v);
    clamp(v2, v, v);
    clamp(v3, v, v);
    clamp(v4, v, v);

    clamp(v1, v1, v1);
    clamp(v2, v2, v2);
    clamp(v3, v3, v3);
    clamp(v4, v4, v4);

    mix(v1, v1, v);
    mix(v2, v2, v);
    mix(v3, v3, v);
    mix(v4, v4, v);

    intersect(v2, v2);
    intersect(v4, v4);
    intersect(v6, v6);
    intersect(v8, v8);

    toSpan(v2);
    toSpan(v4);
    toSpan(v6);
    toSpan(v8);
    
    toBound(v2);
    toBound(v4);
    toBound(v6);
    toBound(v8);

    bvec1 b1;
    bvec2 b2;
    bvec3 b3;
    bvec4 b4;

    and(b1);
    and(b2);
    and(b3);
    and(b4);

    or(b1);
    or(b2);
    or(b3);
    or(b4);

    xor(b1);
    xor(b2);
    xor(b3);
    xor(b4);

    not(b1);
    not(b2);
    not(b3);
    not(b4);
}

template <typename T, nat t_n>
void testVectorTNProperties() {
    static_assert(std::is_standard_layout<vec<T, t_n>>::value, "");
    static_assert(sizeof(vec<T, t_n>) == t_n * sizeof(T), "");
}

template <typename T>
void testVectorTProperties() {
    testVectorTNProperties<T, 1>();
    testVectorTNProperties<T, 2>();
    testVectorTNProperties<T, 3>();
    testVectorTNProperties<T, 4>();
    testVectorTNProperties<T, 6>();
    testVectorTNProperties<T, 8>();
}

void testVectorCompilation() {
    testVectorTCompilation<    float>();
    testVectorTCompilation<   double>();
    testVectorTCompilation<     char>();
    testVectorTCompilation<    short>();
    testVectorTCompilation<      int>();
    testVectorTCompilation<     long>();
    testVectorTCompilation<long long>();

    testVectorTFunctionCompilation< float>();
    testVectorTFunctionCompilation<double>();

    testVectorTProperties<    float>();
    testVectorTProperties<   double>();
    testVectorTProperties<     char>();
    testVectorTProperties<    short>();
    testVectorTProperties<      int>();
    testVectorTProperties<     long>();
    testVectorTProperties<long long>();
}

template <typename T>
void testMatrixTCompilation() {
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
void testMatrixTNProperties() {
    static_assert(std::is_standard_layout<mat<T, t_n>>::value, "");
    static_assert(sizeof(mat<T, t_n>) == t_n * t_n * sizeof(T), "");
}

template <typename T>
void testMatrixTProperties() {
    testMatrixTNProperties<T, 2>();
    testMatrixTNProperties<T, 3>();
    testMatrixTNProperties<T, 4>();
}

void testMatrixCompilation() {
    testMatrixTCompilation<float>();
    testMatrixTCompilation<double>();

    testMatrixTProperties<float>();
    testMatrixTProperties<double>();
}

template <typename T>
void testQuaternionTCompilation() {
    T v;
    vec3<T> v3;
    vec4<T> v4;
    mat3<T> m3;
    quat<T> q;
    std::stringstream os;

    //--------------------------------------------------------------------------
    // Quat

    // constructors
    quat<T> q_1;
    quat<T> q_2(q);
    quat<T> q_3(std::move(q));
    quat<T> q_4(v3, v);
    quat<T> q_5(v, v, v, v);
    quat<T> q_6(v3);
    quat<T> q_7(v4);

    // assignment operators
    q = q;
    q = std::move(q);

    // access operators
    q[0];

    // arithmetic assignment operators
    q += q;
    q -= q;
    q *= q;
    q *= v;
    q /= quat<T>(1, 1, 1, 1);

    // arithmetic operators
    +q;
    -q;
    q + q;
    q - q;
    q * q;
    q * v;
    v * q;
    q * v3;
    q / quat<T>(1, 1, 1, 1);

    // comparison operators
    q == q;
    q != q;

    // other
    q.toString();
    os << q;

    //--------------------------------------------------------------------------
    // Quat Functions

    q = quat<T>(1, 1, 1, 1);

    magnitude(q);
    normalize(q);
    inverse(q);
    angle(q);
    axis(q);
    axis_n(q);

    //--------------------------------------------------------------------------
    // Transformations

    rotateQ(v3, v);
    rotateQ_n(v3, v);
    alignQ(v3, v3);
    alignQ_n(v3, v3);
    alignQ(v3, v3, v3, v3);
    alignQ_n(v3, v3, v3, v3);
    eulerQ(v3, v3, v, v, v);
    eulerQ_n(v3, v3, v, v, v);
    toMat(q);
    nlerp(q, q, v);
    slerp(q, q, v);
}

template <typename T>
void testQuaternionTProperties() {
    static_assert(std::is_standard_layout<quat<T>>::value, "");
    static_assert(sizeof(quat<T>) == 4 * sizeof(T), "");
}

void testQuaternionCompilation() {
    testQuaternionTCompilation<float>();
    testQuaternionTCompilation<double>();

    testQuaternionTProperties<float>();
    testQuaternionTProperties<double>();
}

template <typename T1, typename T2>
void testVectorTTCasts() {
    static_cast<vec1<T2>>(vec1<T1>());
    static_cast<vec2<T2>>(vec2<T1>());
    static_cast<vec3<T2>>(vec3<T1>());
    static_cast<vec4<T2>>(vec4<T1>());
    static_cast<vec<T2, 6>>(vec<T1, 6>());
    static_cast<vec<T2, 8>>(vec<T1, 8>());
}

template <typename T>
void testVectorTCasts() {
    testVectorTTCasts<T,     float>();
    testVectorTTCasts<T,    double>();
    testVectorTTCasts<T,      char>();
    testVectorTTCasts<T,     short>();
    testVectorTTCasts<T,       int>();
    testVectorTTCasts<T,      long>();
    testVectorTTCasts<T, long long>();
}

void testVectorCasts() {
    testVectorTCasts<    float>();
    testVectorTCasts<   double>();
    testVectorTCasts<     char>();
    testVectorTCasts<    short>();
    testVectorTCasts<      int>();
    testVectorTCasts<     long>();
    testVectorTCasts<long long>();
}

template <typename T1, typename T2>
void testMatrixTTCasts() {
    static_cast<mat2<T2>>(mat2<T1>());
    static_cast<mat3<T2>>(mat3<T1>());
    static_cast<mat4<T2>>(mat4<T1>());
}

template <typename T>
void testMatrixTCasts() {
    testMatrixTTCasts<T,  float>();
    testMatrixTTCasts<T, double>();
}

void testMatrixCasts() {
    testMatrixTCasts< float>();
    testMatrixTCasts<double>();
}

template <typename T1, typename T2>
void testQuaternionTTCasts() {
    static_cast<mat2<T2>>(mat2<T1>());
    static_cast<mat3<T2>>(mat3<T1>());
    static_cast<mat4<T2>>(mat4<T1>());
}

template <typename T>
void testQuaternionTCasts() {
    testQuaternionTTCasts<T,  float>();
    testQuaternionTTCasts<T, double>();
}

void testQuaternionCasts() {
    testQuaternionTCasts< float>();
    testQuaternionTCasts<double>();
}

void testVectorMembers() {
    int v;
    vec1<int> v1;
    vec2<int> v2;
    vec3<int> v3;
    vec4<int> v4;
    vec<int, 6> v6;
    vec<int, 8> v8;

    v = v1.x;
    v = v1.r;
    v = v1.s;

    v = v2.x; v = v2.y;
    v = v2.r; v = v2.g;
    v = v2.s; v = v2.t;
    v1 = v2.min; v1 = v2.max;
    v1 = v2.loc; v1 = v2.size;

    v = v3.x; v = v3.y; v = v3.z;
    v = v3.r; v = v3.g; v = v3.b;
    v = v3.s; v = v3.t; v = v3.p;
    v = v3.rad; v = v3.theta; v = v3.phi;
    v = v3.alpha; v = v3.beta; v = v3.gamma;
    v2 = v3.xy; v2 = v3.yz;

    v = v4.x; v = v4.y; v = v4.z; v = v4.w;
    v = v4.r; v = v4.g; v = v4.b; v = v4.a;
    v = v4.s; v = v4.t; v = v4.p; v = v4.q;
    v2 = v4.min; v2 = v4.max;
    v2 = v4.loc; v2 = v4.size;
    v2 = v4.xy; v2 = v4.yz; v2 = v4.zw;
    v3 = v4.xyz; v3 = v4.yzw;
}

int main(void) {
    testVectorCompilation();
    testMatrixCompilation();
    testQuaternionCompilation();

    testVectorCasts();
    testMatrixCasts();
    testQuaternionCasts();

    testVectorMembers();

    std::cin.get();
    return 0;
}