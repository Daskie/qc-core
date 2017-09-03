#include "QMUTest.hpp"

#include "QMU/Vector.hpp"



using namespace qmu;



namespace {



template <typename T>
void compileClassesT() {
    T v;
    vec1<T> v1;
    vec2<T> v2;
    vec3<T> v3;
    vec4<T> v4;
    span1<T> s1;
    span2<T> s2;
    span3<T> s3;
    span4<T> s4;

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
    
    // assignment
    v1 = v1;
    v1 = std::move(v1);
    v1 = v;
    v1 = v2;
    v1 = v3;
    v1 = v4;

    // access
    v1[0];

    v1.at<0>();

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

    // assignment
    v2 = v2;
    v2 = std::move(v2);
    v2 = v;
    v2 = v1;
    v2 = v3;
    v2 = v4;

    // access
    v2[0];

    v2.at<0>();
    v2.at<1>();

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

    // assignment
    v3 = v3;
    v3 = std::move(v3);
    v3 = v;
    v3 = v1;
    v3 = v2;
    v3 = v4;

    // access
    v3[0];

    v3.at<0>();
    v3.at<1>();
    v3.at<2>();

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

    // assignment
    v4 = v4;
    v4 = std::move(v4);
    v4 = v;
    v4 = v1;
    v4 = v2;
    v4 = v3;

    // access
    v4[0];

    v4.at<0>();
    v4.at<1>();
    v4.at<2>();
    v4.at<3>();

    // other
    v4.toString();

    //--------------------------------------------------------------------------
    // Span1

    // constructors
    span<T, 1> s1_1;
    span<T, 1> s1_2(s1);
    span<T, 1> s1_3(std::move(s1));
    span<T, 1> s1_7(v1, v1);
    span<T, 1> s1_8(v, v);

    // asignment operators
    s1 = s1;
    s1 = std::move(s1);

    // other
    s1.toString();

    //--------------------------------------------------------------------------
    // Span2

    // constructors
    span<T, 2> s2_1;
    span<T, 2> s2_2(s2);
    span<T, 2> s2_3(std::move(s2));
    span<T, 2> s2_7(v2, v2);
    span<T, 2> s2_8(v, v);

    // asignment operators
    s2 = s2;
    s2 = std::move(s2);

    // other
    s2.toString();

    //--------------------------------------------------------------------------
    // Span3

    // constructors
    span<T, 3> s3_1;
    span<T, 3> s3_2(s3);
    span<T, 3> s3_3(std::move(s3));
    span<T, 3> s3_7(v3, v3);
    span<T, 3> s3_8(v, v);

    // asignment operators
    s3 = s3;
    s3 = std::move(s3);

    // other
    s3.toString();

    //--------------------------------------------------------------------------
    // Span4

    // constructors
    span<T, 4> s4_1;
    span<T, 4> s4_2(s4);
    span<T, 4> s4_3(std::move(s4));
    span<T, 4> s4_7(v4, v4);
    span<T, 4> s4_8(v, v);

    // asignment operators
    s4 = s4;
    s4 = std::move(s4);

    // other
    s4.toString();
}

void compileClasses() {
    compileClassesT<      float>();
    compileClassesT<     double>();
    compileClassesT<long double>();
    compileClassesT<       char>();
    compileClassesT<      short>();
    compileClassesT<        int>();
    compileClassesT<       long>();
    compileClassesT<  long long>();
}

template <typename T>
constexpr void compileClassesConstexprT() {
    constexpr T v(static_cast<T>(0));
    constexpr vec1<T> v1;
    constexpr vec2<T> v2;
    constexpr vec3<T> v3;
    constexpr vec4<T> v4;
    constexpr span1<T> s1;
    constexpr span2<T> s2;
    constexpr span3<T> s3;
    constexpr span4<T> s4;

    //--------------------------------------------------------------------------
    // Vec1
    
    // constructors
    constexpr vec1<T> v1_1;
    constexpr vec1<T> v1_2(v1);
    constexpr vec1<T> v1_3(std::move(v1));
    constexpr vec1<T> v1_4(v);
    constexpr vec1<T> v1_5(v2);
    constexpr vec1<T> v1_6(v3);
    constexpr vec1<T> v1_7(v4);

    // access
    v1.at<0>();

    //--------------------------------------------------------------------------
    // Vec2

    // constructors
    constexpr vec2<T> v2_01;
    constexpr vec2<T> v2_02(v2);
    constexpr vec2<T> v2_03(std::move(v2));
    constexpr vec2<T> v2_04(v);
    constexpr vec2<T> v2_05(v1);
    constexpr vec2<T> v2_06(v3);
    constexpr vec2<T> v2_07(v4);
    constexpr vec2<T> v2_08(v, v);
    constexpr vec2<T> v2_09(v1, v);
    constexpr vec2<T> v2_10(v, v1);
    constexpr vec2<T> v2_11(v1, v1);

    // access
    v2.at<0>();
    v2.at<1>();

    //--------------------------------------------------------------------------
    // Vec3

    // constructors
    constexpr vec3<T> v3_01;
    constexpr vec3<T> v3_02(v3);
    constexpr vec3<T> v3_03(std::move(v3));
    constexpr vec3<T> v3_04(v);
    constexpr vec3<T> v3_05(v1);
    constexpr vec3<T> v3_06(v2);
    constexpr vec3<T> v3_07(v4);
    constexpr vec3<T> v3_08(v, v, v);
    constexpr vec3<T> v3_09(v1, v, v);
    constexpr vec3<T> v3_10(v, v1, v);
    constexpr vec3<T> v3_11(v, v, v1);
    constexpr vec3<T> v3_12(v1, v1, v);
    constexpr vec3<T> v3_13(v1, v, v1);
    constexpr vec3<T> v3_14(v, v1, v1);
    constexpr vec3<T> v3_15(v1, v1, v1);
    constexpr vec3<T> v3_16(v2, v);
    constexpr vec3<T> v3_17(v2, v1);
    constexpr vec3<T> v3_18(v, v2);
    constexpr vec3<T> v3_19(v1, v2);

    // access
    v3.at<0>();
    v3.at<1>();
    v3.at<2>();

    //--------------------------------------------------------------------------
    // Vec4

    // constructors
    constexpr vec4<T> v4_01;
    constexpr vec4<T> v4_02(v4);
    constexpr vec4<T> v4_03(std::move(v4));
    constexpr vec4<T> v4_04(v);
    constexpr vec4<T> v4_05(v1);
    constexpr vec4<T> v4_06(v2);
    constexpr vec4<T> v4_07(v3);
    constexpr vec4<T> v4_08(v, v, v, v);
    constexpr vec4<T> v4_09(v1, v, v, v);
    constexpr vec4<T> v4_10(v, v1, v, v);
    constexpr vec4<T> v4_11(v, v, v1, v);
    constexpr vec4<T> v4_12(v, v, v, v1);
    constexpr vec4<T> v4_13(v1, v1, v, v);
    constexpr vec4<T> v4_14(v1, v, v1, v);
    constexpr vec4<T> v4_15(v1, v, v, v1);
    constexpr vec4<T> v4_16(v, v1, v, v1);
    constexpr vec4<T> v4_17(v, v, v1, v1);
    constexpr vec4<T> v4_18(v1, v1, v1, v);
    constexpr vec4<T> v4_19(v1, v1, v, v1);
    constexpr vec4<T> v4_20(v1, v, v1, v1);
    constexpr vec4<T> v4_21(v, v1, v1, v1);
    constexpr vec4<T> v4_22(v1, v1, v1, v1);
    constexpr vec4<T> v4_23(v2, v, v);
    constexpr vec4<T> v4_24(v2, v1, v);
    constexpr vec4<T> v4_25(v2, v, v1);
    constexpr vec4<T> v4_26(v2, v1, v1);
    constexpr vec4<T> v4_27(v, v2, v);
    constexpr vec4<T> v4_28(v1, v2, v);
    constexpr vec4<T> v4_29(v, v2, v1);
    constexpr vec4<T> v4_30(v1, v2, v1);
    constexpr vec4<T> v4_31(v, v, v2);
    constexpr vec4<T> v4_32(v1, v, v2);
    constexpr vec4<T> v4_33(v, v1, v2);
    constexpr vec4<T> v4_34(v1, v1, v2);
    constexpr vec4<T> v4_35(v2, v2);
    constexpr vec4<T> v4_36(v3, v);
    constexpr vec4<T> v4_37(v3, v1);
    constexpr vec4<T> v4_38(v, v3);
    constexpr vec4<T> v4_39(v1, v3);

    // access
    v4.at<0>();
    v4.at<1>();
    v4.at<2>();
    v4.at<3>();

    //--------------------------------------------------------------------------
    // Span1

    // constructors
    constexpr span<T, 1> s1_1;
    constexpr span<T, 1> s1_2(s1);
    constexpr span<T, 1> s1_3(std::move(s1));
    constexpr span<T, 1> s1_7(v1, v1);
    constexpr span<T, 1> s1_8(v, v);

    //--------------------------------------------------------------------------
    // Span2

    // constructors
    constexpr span<T, 2> s2_1;
    constexpr span<T, 2> s2_2(s2);
    constexpr span<T, 2> s2_3(std::move(s2));
    constexpr span<T, 2> s2_7(v2, v2);
    constexpr span<T, 2> s2_8(v, v);

    //--------------------------------------------------------------------------
    // Span3

    // constructors
    constexpr span<T, 3> s3_1;
    constexpr span<T, 3> s3_2(s3);
    constexpr span<T, 3> s3_3(std::move(s3));
    constexpr span<T, 3> s3_7(v3, v3);
    constexpr span<T, 3> s3_8(v, v);

    //--------------------------------------------------------------------------
    // Span4

    // constructors
    constexpr span<T, 4> s4_1;
    constexpr span<T, 4> s4_2(s4);
    constexpr span<T, 4> s4_3(std::move(s4));
    constexpr span<T, 4> s4_7(v4, v4);
    constexpr span<T, 4> s4_8(v, v);
}

constexpr bool compileClassesConstexpr() {
    compileClassesConstexprT<      float>();
    compileClassesConstexprT<     double>();
    compileClassesConstexprT<long double>();
    compileClassesConstexprT<       char>();
    compileClassesConstexprT<      short>();
    compileClassesConstexprT<        int>();
    compileClassesConstexprT<       long>();
    compileClassesConstexprT<  long long>();

    return true;
}

template <typename T>
void compileFunctionsT() {
    T v;
    vec1<T> v1;
    vec2<T> v2;
    vec3<T> v3;
    vec4<T> v4;
    span1<T> s1;
    span2<T> s2;
    span3<T> s3;
    span4<T> s4;
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

    v1 %= vec1<T>(1);
    v2 %= vec2<T>(1);
    v3 %= vec3<T>(1);
    v4 %= vec4<T>(1);
    v1 %= T(1);
    v2 %= T(1);
    v3 %= T(1);
    v4 %= T(1);

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

    v1 % vec1<T>(1);
    v2 % vec2<T>(1);
    v3 % vec3<T>(1);
    v4 % vec4<T>(1);
    v1 % T(1);
    v2 % T(v);
    v3 % T(v);
    v4 % T(v);
    v % vec1<T>(1);
    v % vec2<T>(1);
    v % vec3<T>(1);
    v % vec4<T>(1);


    // comparison

    v1 == v1;
    v2 == v2;
    v3 == v3;
    v4 == v4;
    v1 == v;
    v2 == v;
    v3 == v;
    v4 == v;
    v == v1;
    v == v2;
    v == v3;
    v == v4;
    s1 == s1;
    s2 == s2;
    s3 == s3;
    s4 == s4;

    v1 != v1;
    v2 != v2;
    v3 != v3;
    v4 != v4;
    v1 != v;
    v2 != v;
    v3 != v;
    v4 != v;
    v != v1;
    v != v2;
    v != v3;
    v != v4;
    s1 != s1;
    s2 != s2;
    s3 != s3;
    s4 != s4;

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
    os << s1;
    os << s2;
    os << s3;
    os << s4;

    // uncategorized

    pow(v1, v);
    pow(v2, v);
    pow(v3, v);
    pow(v4, v);

    pow(v1, v1);
    pow(v2, v2);
    pow(v3, v3);
    pow(v4, v4);

    exp(v1);
    exp(v2);
    exp(v3);
    exp(v4);

    magnitude(v1);
    magnitude(v2);
    magnitude(v3);
    magnitude(v4);

    norm(v1);
    norm(v2);
    norm(v3);
    norm(v4);

    dot(v1, v1);
    dot(v2, v2);
    dot(v3, v3);
    dot(v4, v4);

    cross(v2, v2);
    cross(v3, v3);

    parallel(v1, v1);
    parallel(v2, v2);
    parallel(v3, v3);
    parallel(v4, v4);

    orthogonal(v1, v1);
    orthogonal(v2, v2);
    orthogonal(v3, v3);
    orthogonal(v4, v4);

    ortho(v2);
    ortho(v3);

    orthogonalize(v2, v2);
    orthogonalize(v3, v3, v3);

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

    min(v1, v1, v1, v1, v1);
    min(v2, v2, v2, v2, v2);
    min(v3, v3, v3, v3, v3);
    min(v4, v4, v4, v4, v4);

    max(v1, v1, v1, v1, v1);
    max(v2, v2, v2, v2, v2);
    max(v3, v3, v3, v3, v3);
    max(v4, v4, v4, v4, v4);

    clamp(v1, v, v);
    clamp(v2, v, v);
    clamp(v3, v, v);
    clamp(v4, v, v);

    clamp(v1, v1, v1);
    clamp(v2, v2, v2);
    clamp(v3, v3, v3);
    clamp(v4, v4, v4);

    abs(v1);
    abs(v2);
    abs(v3);
    abs(v4);

    floor(v1);
    floor(v2);
    floor(v3);
    floor(v4);

    ceil(v1);
    ceil(v2);
    ceil(v3);
    ceil(v4);

    mix(v1, v1, v);
    mix(v2, v2, v);
    mix(v3, v3, v);
    mix(v4, v4, v);

    intersect(s1, s1);
    intersect(s2, s2);
    intersect(s3, s3);
    intersect(s4, s4);

    toSpan(s1);
    toSpan(s2);
    toSpan(s3);
    toSpan(s4);
    
    toBound(s1);
    toBound(s2);
    toBound(s3);
    toBound(s4);
}

void compileBoolFunctions() {
    bvec1 b1;
    bvec2 b2;
    bvec3 b3;
    bvec4 b4;

    b1 && b1;
    b2 && b2;
    b3 && b3;
    b4 && b4;

    vand(b1);
    vand(b2);
    vand(b3);
    vand(b4);

    b1 || b1;
    b2 || b2;
    b3 || b3;
    b4 || b4;

    vor(b1);
    vor(b2);
    vor(b3);
    vor(b4);

    !b1;
    !b2;
    !b3;
    !b4;
}

void compileFunctions() {
    compileFunctionsT<      float>();
    compileFunctionsT<     double>();
    compileFunctionsT<long double>();
    compileBoolFunctions();
}

template <typename T>
constexpr void compileFunctionsConstexprT() {
    constexpr T v(static_cast<T>(1.0));
    constexpr vec1<T> v1(static_cast<T>(1.0));
    constexpr vec2<T> v2(static_cast<T>(1.0));
    constexpr vec3<T> v3(static_cast<T>(1.0));
    constexpr vec4<T> v4(static_cast<T>(1.0));
    constexpr span1<T> s1(v1, v1);
    constexpr span2<T> s2(v2, v2);
    constexpr span3<T> s3(v3, v3);
    constexpr span4<T> s4(v4, v4);

    // arithmetic

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

    v1 % vec1<T>(1);
    v2 % vec2<T>(1);
    v3 % vec3<T>(1);
    v4 % vec4<T>(1);
    v1 % T(1);
    v2 % T(v);
    v3 % T(v);
    v4 % T(v);
    v % vec1<T>(1);
    v % vec2<T>(1);
    v % vec3<T>(1);
    v % vec4<T>(1);


    // comparison

    v1 == v1;
    v2 == v2;
    v3 == v3;
    v4 == v4;
    v1 == v;
    v2 == v;
    v3 == v;
    v4 == v;
    v == v1;
    v == v2;
    v == v3;
    v == v4;
    s1 == s1;
    s2 == s2;
    s3 == s3;
    s4 == s4;

    v1 != v1;
    v2 != v2;
    v3 != v3;
    v4 != v4;
    v1 != v;
    v2 != v;
    v3 != v;
    v4 != v;
    v != v1;
    v != v2;
    v != v3;
    v != v4;
    s1 != s1;
    s2 != s2;
    s3 != s3;
    s4 != s4;

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

    // uncategorized

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

    min(v1, v1, v1, v1, v1);
    min(v2, v2, v2, v2, v2);
    min(v3, v3, v3, v3, v3);
    min(v4, v4, v4, v4, v4);

    max(v1, v1, v1, v1, v1);
    max(v2, v2, v2, v2, v2);
    max(v3, v3, v3, v3, v3);
    max(v4, v4, v4, v4, v4);

    clamp(v1, v, v);
    clamp(v2, v, v);
    clamp(v3, v, v);
    clamp(v4, v, v);

    clamp(v1, v1, v1);
    clamp(v2, v2, v2);
    clamp(v3, v3, v3);
    clamp(v4, v4, v4);

    abs(v1);
    abs(v2);
    abs(v3);
    abs(v4);

    floor(v1);
    floor(v2);
    floor(v3);
    floor(v4);

    ceil(v1);
    ceil(v2);
    ceil(v3);
    ceil(v4);

    mix(v1, v1, v);
    mix(v2, v2, v);
    mix(v3, v3, v);
    mix(v4, v4, v);

    toSpan(s1);
    toSpan(s2);
    toSpan(s3);
    toSpan(s4);
    
    toBound(s1);
    toBound(s2);
    toBound(s3);
    toBound(s4);
}

constexpr void compileBoolFunctionsConstexpr() {
    bvec1 b1;
    bvec2 b2;
    bvec3 b3;
    bvec4 b4;

    b1 && b1;
    b2 && b2;
    b3 && b3;
    b4 && b4;

    vand(b1);
    vand(b2);
    vand(b3);
    vand(b4);

    b1 || b1;
    b2 || b2;
    b3 || b3;
    b4 || b4;

    vor(b1);
    vor(b2);
    vor(b3);
    vor(b4);

    !b1;
    !b2;
    !b3;
    !b4;
}

constexpr bool compileFunctionsConstexpr() {
    compileFunctionsConstexprT<      float>();
    compileFunctionsConstexprT<     double>();
    compileFunctionsConstexprT<long double>();
    compileBoolFunctionsConstexpr();

    return true;
}

template <typename T, nat t_n>
void testPropertiesTN() {
    static_assert(std::is_standard_layout_v<vec<T, t_n>>, "");
    static_assert(sizeof(vec<T, t_n>) == t_n * sizeof(T), "");
}

template <typename T>
void testPropertiesT() {
    testPropertiesTN<T, 1>();
    testPropertiesTN<T, 2>();
    testPropertiesTN<T, 3>();
    testPropertiesTN<T, 4>();
}

void testProperties() {
    testPropertiesT<      float>();
    testPropertiesT<     double>();
    testPropertiesT<long double>();
    testPropertiesT<       char>();
    testPropertiesT<      short>();
    testPropertiesT<        int>();
    testPropertiesT<       long>();
    testPropertiesT<  long long>();
}

template <typename T1, typename T2, nat t_n>
void castCastsTTN() {
    static_cast<vec<T2, t_n>>(vec1<T1>());
    static_cast<vec<T2, t_n>>(vec2<T1>());
    static_cast<vec<T2, t_n>>(vec3<T1>());
    static_cast<vec<T2, t_n>>(vec4<T1>());

    static_cast<span<T2, t_n>>(span1<T1>());
    static_cast<span<T2, t_n>>(span2<T1>());
    static_cast<span<T2, t_n>>(span3<T1>());
    static_cast<span<T2, t_n>>(span4<T1>());
}

template <typename T1, typename T2>
void compileCastsTT() {
    castCastsTTN<T1, T2, 1>();
    castCastsTTN<T1, T2, 2>();
    castCastsTTN<T1, T2, 3>();
    castCastsTTN<T1, T2, 4>();
}

template <typename T>
void compileCastsT() {
    compileCastsTT<T,       float>();
    compileCastsTT<T,      double>();
    compileCastsTT<T, long double>();
    compileCastsTT<T,        char>();
    compileCastsTT<T,       short>();
    compileCastsTT<T,         int>();
    compileCastsTT<T,        long>();
    compileCastsTT<T,   long long>();
}

void compileCasts() {
    compileCastsT<      float>();
    compileCastsT<     double>();
    compileCastsT<long double>();
    compileCastsT<       char>();
    compileCastsT<      short>();
    compileCastsT<        int>();
    compileCastsT<       long>();
    compileCastsT<  long long>();
}

void compileMembers() {
    int v;
    vec1<int> v1;
    vec2<int> v2;
    vec3<int> v3;
    vec4<int> v4;
    span1<int> s1;
    span2<int> s2;
    span3<int> s3;
    span4<int> s4;

    v = v1.x;
    v = v1.r;
    v = v1.s;

    v = v2.x; v = v2.y;
    v = v2.r; v = v2.g;
    v = v2.s; v = v2.t;

    v = v3.x; v = v3.y; v = v3.z;
    v = v3.r; v = v3.g; v = v3.b;
    v = v3.s; v = v3.t; v = v3.p;
    v = v3.rad; v = v3.theta; v = v3.phi;
    v = v3.alpha; v = v3.beta; v = v3.gamma;

    v = v4.x; v = v4.y; v = v4.z; v = v4.w;
    v = v4.r; v = v4.g; v = v4.b; v = v4.a;
    v = v4.s; v = v4.t; v = v4.p; v = v4.q;

    v1 = s1.min; v1 = s1.max;
    v1 = s1.loc; v1 = s1.size;
    v2 = s2.min; v2 = s2.max;
    v2 = s2.loc; v2 = s2.size;
    v3 = s3.min; v3 = s3.max;
    v3 = s3.loc; v3 = s3.size;
    v4 = s4.min; v4 = s4.max;
    v4 = s4.loc; v4 = s4.size;
}

template <typename T>
constexpr void compileConstantsT() {
    constexpr vec1<T> ax1(axis1X<T>);
    constexpr vec2<T> ax2(axis2X<T>);
    constexpr vec3<T> ax3(axis3X<T>);
    constexpr vec4<T> ax4(axis4X<T>);
    constexpr vec2<T> ay2(axis2Y<T>);
    constexpr vec3<T> ay3(axis3Y<T>);
    constexpr vec4<T> ay4(axis4Y<T>);
    constexpr vec3<T> az3(axis3Z<T>);
    constexpr vec4<T> az4(axis4Z<T>);
    constexpr vec4<T> aw4(axis4W<T>);
}

template <typename T>
constexpr void compileConstantsFT() {
    constexpr vec1<T> nv1(nanvec<T, 1>);
    constexpr vec2<T> nv2(nanvec<T, 2>);
    constexpr vec3<T> nv3(nanvec<T, 3>);
    constexpr vec4<T> nv4(nanvec<T, 4>);

    constexpr span1<T> ns1(nanspan<T, 1>);
    constexpr span2<T> ns2(nanspan<T, 2>);
    constexpr span3<T> ns3(nanspan<T, 3>);
    constexpr span4<T> ns4(nanspan<T, 4>);

    constexpr bound1<T> nb1(nanbound<T, 1>);
    constexpr bound2<T> nb2(nanbound<T, 2>);
    constexpr bound3<T> nb3(nanbound<T, 3>);
    constexpr bound4<T> nb4(nanbound<T, 4>);

    constexpr vec1<T> iv1(infvec<T, 1>);
    constexpr vec2<T> iv2(infvec<T, 2>);
    constexpr vec3<T> iv3(infvec<T, 3>);
    constexpr vec4<T> iv4(infvec<T, 4>);

    constexpr span1<T> is1(infspan<T, 1>);
    constexpr span2<T> is2(infspan<T, 2>);
    constexpr span3<T> is3(infspan<T, 3>);
    constexpr span4<T> is4(infspan<T, 4>);

    constexpr span1<T> nulls1(nullspan<T, 1>);
    constexpr span2<T> nulls2(nullspan<T, 2>);
    constexpr span3<T> nulls3(nullspan<T, 3>);
    constexpr span4<T> nulls4(nullspan<T, 4>);
}

constexpr bool compileConstants() {
    compileConstantsT<      float>();
    compileConstantsT<     double>();
    compileConstantsT<long double>();
    compileConstantsT<       char>();
    compileConstantsT<      short>();
    compileConstantsT<        int>();
    compileConstantsT<       long>();
    compileConstantsT<  long long>();

    compileConstantsFT<      float>();
    compileConstantsFT<     double>();
    compileConstantsFT<long double>();

    return true;
}



}



void testVector() {
    compileClasses();
    static_assert(compileClassesConstexpr(), "");
    compileFunctions();
    static_assert(compileFunctionsConstexpr(), "");
    testProperties();
    compileCasts();
    compileMembers();
    static_assert(compileConstants(), "");
}