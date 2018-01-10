#include "QMUTest.hpp"

#include "QMU/Vector.hpp"



namespace {



template <typename T>
void compileClassesT() {
    T v;
    qmu::vec1<T> v1;
    qmu::vec2<T> v2;
    qmu::vec3<T> v3;
    qmu::vec4<T> v4;
    qmu::span1<T> s1;
    qmu::span2<T> s2;
    qmu::span3<T> s3;
    qmu::span4<T> s4;

    //--------------------------------------------------------------------------
    // Vec1
    
    // constructors
    qmu::vec1<T> v1_1;
    qmu::vec1<T> v1_2(v1);
    qmu::vec1<T> v1_3(std::move(v1));
    qmu::vec1<T> v1_4(v);
    qmu::vec1<T> v1_5(v2);
    qmu::vec1<T> v1_6(v3);
    qmu::vec1<T> v1_7(v4);
    
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
    qmu::vec2<T> v2_01;
    qmu::vec2<T> v2_02(v2);
    qmu::vec2<T> v2_03(std::move(v2));
    qmu::vec2<T> v2_04(v);
    qmu::vec2<T> v2_05(v1);
    qmu::vec2<T> v2_06(v3);
    qmu::vec2<T> v2_07(v4);
    qmu::vec2<T> v2_08(v, v);
    qmu::vec2<T> v2_09(v1, v);
    qmu::vec2<T> v2_10(v, v1);
    qmu::vec2<T> v2_11(v1, v1);

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
    qmu::vec3<T> v3_01;
    qmu::vec3<T> v3_02(v3);
    qmu::vec3<T> v3_03(std::move(v3));
    qmu::vec3<T> v3_04(v);
    qmu::vec3<T> v3_05(v1);
    qmu::vec3<T> v3_06(v2);
    qmu::vec3<T> v3_07(v4);
    qmu::vec3<T> v3_08(v, v, v);
    qmu::vec3<T> v3_09(v1, v, v);
    qmu::vec3<T> v3_10(v, v1, v);
    qmu::vec3<T> v3_11(v, v, v1);
    qmu::vec3<T> v3_12(v1, v1, v);
    qmu::vec3<T> v3_13(v1, v, v1);
    qmu::vec3<T> v3_14(v, v1, v1);
    qmu::vec3<T> v3_15(v1, v1, v1);
    qmu::vec3<T> v3_16(v2, v);
    qmu::vec3<T> v3_17(v2, v1);
    qmu::vec3<T> v3_18(v, v2);
    qmu::vec3<T> v3_19(v1, v2);

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

    v3.xy(); v3.rg(); v3.st();
    v3.yz(); v3.gb(); v3.tp();

    // other
    v3.toString();

    //--------------------------------------------------------------------------
    // Vec4

    // constructors
    qmu::vec4<T> v4_01;
    qmu::vec4<T> v4_02(v4);
    qmu::vec4<T> v4_03(std::move(v4));
    qmu::vec4<T> v4_04(v);
    qmu::vec4<T> v4_05(v1);
    qmu::vec4<T> v4_06(v2);
    qmu::vec4<T> v4_07(v3);
    qmu::vec4<T> v4_08(v, v, v, v);
    qmu::vec4<T> v4_09(v1, v, v, v);
    qmu::vec4<T> v4_10(v, v1, v, v);
    qmu::vec4<T> v4_11(v, v, v1, v);
    qmu::vec4<T> v4_12(v, v, v, v1);
    qmu::vec4<T> v4_13(v1, v1, v, v);
    qmu::vec4<T> v4_14(v1, v, v1, v);
    qmu::vec4<T> v4_15(v1, v, v, v1);
    qmu::vec4<T> v4_16(v, v1, v, v1);
    qmu::vec4<T> v4_17(v, v, v1, v1);
    qmu::vec4<T> v4_18(v1, v1, v1, v);
    qmu::vec4<T> v4_19(v1, v1, v, v1);
    qmu::vec4<T> v4_20(v1, v, v1, v1);
    qmu::vec4<T> v4_21(v, v1, v1, v1);
    qmu::vec4<T> v4_22(v1, v1, v1, v1);
    qmu::vec4<T> v4_23(v2, v, v);
    qmu::vec4<T> v4_24(v2, v1, v);
    qmu::vec4<T> v4_25(v2, v, v1);
    qmu::vec4<T> v4_26(v2, v1, v1);
    qmu::vec4<T> v4_27(v, v2, v);
    qmu::vec4<T> v4_28(v1, v2, v);
    qmu::vec4<T> v4_29(v, v2, v1);
    qmu::vec4<T> v4_30(v1, v2, v1);
    qmu::vec4<T> v4_31(v, v, v2);
    qmu::vec4<T> v4_32(v1, v, v2);
    qmu::vec4<T> v4_33(v, v1, v2);
    qmu::vec4<T> v4_34(v1, v1, v2);
    qmu::vec4<T> v4_35(v2, v2);
    qmu::vec4<T> v4_36(v3, v);
    qmu::vec4<T> v4_37(v3, v1);
    qmu::vec4<T> v4_38(v, v3);
    qmu::vec4<T> v4_39(v1, v3);

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

    v4.xy(); v4.rg(); v4.st();
    v4.yz(); v4.gb(); v4.tp();
    v4.zw(); v4.ba(); v4.pq();
    v4.xyz(); v4.rgb(); v4.stp();
    v4.yzw(); v4.gba(); v4.tpq();

    // other
    v4.toString();

    //--------------------------------------------------------------------------
    // Span1

    // constructors
    qmu::span<T, 1> s1_1;
    qmu::span<T, 1> s1_2(s1);
    qmu::span<T, 1> s1_3(std::move(s1));
    qmu::span<T, 1> s1_7(v1, v1);
    qmu::span<T, 1> s1_8(v, v);

    // asignment operators
    s1 = s1;
    s1 = std::move(s1);

    // other
    s1.toString();

    //--------------------------------------------------------------------------
    // Span2

    // constructors
    qmu::span<T, 2> s2_1;
    qmu::span<T, 2> s2_2(s2);
    qmu::span<T, 2> s2_3(std::move(s2));
    qmu::span<T, 2> s2_7(v2, v2);
    qmu::span<T, 2> s2_8(v, v);

    // asignment operators
    s2 = s2;
    s2 = std::move(s2);

    // other
    s2.toString();

    //--------------------------------------------------------------------------
    // Span3

    // constructors
    qmu::span<T, 3> s3_1;
    qmu::span<T, 3> s3_2(s3);
    qmu::span<T, 3> s3_3(std::move(s3));
    qmu::span<T, 3> s3_7(v3, v3);
    qmu::span<T, 3> s3_8(v, v);

    // asignment operators
    s3 = s3;
    s3 = std::move(s3);

    // other
    s3.toString();

    //--------------------------------------------------------------------------
    // Span4

    // constructors
    qmu::span<T, 4> s4_1;
    qmu::span<T, 4> s4_2(s4);
    qmu::span<T, 4> s4_3(std::move(s4));
    qmu::span<T, 4> s4_7(v4, v4);
    qmu::span<T, 4> s4_8(v, v);

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
    constexpr T v(T(0));
    constexpr qmu::vec1<T> v1;
    constexpr qmu::vec2<T> v2;
    constexpr qmu::vec3<T> v3;
    constexpr qmu::vec4<T> v4;
    constexpr qmu::span1<T> s1;
    constexpr qmu::span2<T> s2;
    constexpr qmu::span3<T> s3;
    constexpr qmu::span4<T> s4;

    //--------------------------------------------------------------------------
    // Vec1
    
    // constructors
    constexpr qmu::vec1<T> v1_1;
    constexpr qmu::vec1<T> v1_2(v1);
    constexpr qmu::vec1<T> v1_3(std::move(v1));
    constexpr qmu::vec1<T> v1_4(v);
    constexpr qmu::vec1<T> v1_5(v2);
    constexpr qmu::vec1<T> v1_6(v3);
    constexpr qmu::vec1<T> v1_7(v4);

    // access
    v1.at<0>();

    //--------------------------------------------------------------------------
    // Vec2

    // constructors
    constexpr qmu::vec2<T> v2_01;
    constexpr qmu::vec2<T> v2_02(v2);
    constexpr qmu::vec2<T> v2_03(std::move(v2));
    constexpr qmu::vec2<T> v2_04(v);
    constexpr qmu::vec2<T> v2_05(v1);
    constexpr qmu::vec2<T> v2_06(v3);
    constexpr qmu::vec2<T> v2_07(v4);
    constexpr qmu::vec2<T> v2_08(v, v);
    //constexpr qmu::vec2<T> v2_09(v1, v);
    //constexpr qmu::vec2<T> v2_10(v, v1);
    //constexpr qmu::vec2<T> v2_11(v1, v1);

    // access
    v2.at<0>();
    v2.at<1>();

    //--------------------------------------------------------------------------
    // Vec3

    // constructors
    constexpr qmu::vec3<T> v3_01;
    constexpr qmu::vec3<T> v3_02(v3);
    constexpr qmu::vec3<T> v3_03(std::move(v3));
    constexpr qmu::vec3<T> v3_04(v);
    constexpr qmu::vec3<T> v3_05(v1);
    constexpr qmu::vec3<T> v3_06(v2);
    constexpr qmu::vec3<T> v3_07(v4);
    constexpr qmu::vec3<T> v3_08(v, v, v);
    //constexpr qmu::vec3<T> v3_09(v1, v, v);
    //constexpr qmu::vec3<T> v3_10(v, v1, v);
    //constexpr qmu::vec3<T> v3_11(v, v, v1);
    //constexpr qmu::vec3<T> v3_12(v1, v1, v);
    //constexpr qmu::vec3<T> v3_13(v1, v, v1);
    //constexpr qmu::vec3<T> v3_14(v, v1, v1);
    //constexpr qmu::vec3<T> v3_15(v1, v1, v1);
    //constexpr qmu::vec3<T> v3_16(v2, v);
    //constexpr qmu::vec3<T> v3_17(v2, v1);
    //constexpr qmu::vec3<T> v3_18(v, v2);
    //constexpr qmu::vec3<T> v3_19(v1, v2);

    // access
    v3.at<0>();
    v3.at<1>();
    v3.at<2>();

    //--------------------------------------------------------------------------
    // Vec4

    // constructors
    constexpr qmu::vec4<T> v4_01;
    constexpr qmu::vec4<T> v4_02(v4);
    constexpr qmu::vec4<T> v4_03(std::move(v4));
    constexpr qmu::vec4<T> v4_04(v);
    constexpr qmu::vec4<T> v4_05(v1);
    constexpr qmu::vec4<T> v4_06(v2);
    constexpr qmu::vec4<T> v4_07(v3);
    constexpr qmu::vec4<T> v4_08(v, v, v, v);
    //constexpr qmu::vec4<T> v4_09(v1, v, v, v);
    //constexpr qmu::vec4<T> v4_10(v, v1, v, v);
    //constexpr qmu::vec4<T> v4_11(v, v, v1, v);
    //constexpr qmu::vec4<T> v4_12(v, v, v, v1);
    //constexpr qmu::vec4<T> v4_13(v1, v1, v, v);
    //constexpr qmu::vec4<T> v4_14(v1, v, v1, v);
    //constexpr qmu::vec4<T> v4_15(v1, v, v, v1);
    //constexpr qmu::vec4<T> v4_16(v, v1, v, v1);
    //constexpr qmu::vec4<T> v4_17(v, v, v1, v1);
    //constexpr qmu::vec4<T> v4_18(v1, v1, v1, v);
    //constexpr qmu::vec4<T> v4_19(v1, v1, v, v1);
    //constexpr qmu::vec4<T> v4_20(v1, v, v1, v1);
    //constexpr qmu::vec4<T> v4_21(v, v1, v1, v1);
    //constexpr qmu::vec4<T> v4_22(v1, v1, v1, v1);
    //constexpr qmu::vec4<T> v4_23(v2, v, v);
    //constexpr qmu::vec4<T> v4_24(v2, v1, v);
    //constexpr qmu::vec4<T> v4_25(v2, v, v1);
    //constexpr qmu::vec4<T> v4_26(v2, v1, v1);
    //constexpr qmu::vec4<T> v4_27(v, v2, v);
    //constexpr qmu::vec4<T> v4_28(v1, v2, v);
    //constexpr qmu::vec4<T> v4_29(v, v2, v1);
    //constexpr qmu::vec4<T> v4_30(v1, v2, v1);
    //constexpr qmu::vec4<T> v4_31(v, v, v2);
    //constexpr qmu::vec4<T> v4_32(v1, v, v2);
    //constexpr qmu::vec4<T> v4_33(v, v1, v2);
    //constexpr qmu::vec4<T> v4_34(v1, v1, v2);
    //constexpr qmu::vec4<T> v4_35(v2, v2);
    //constexpr qmu::vec4<T> v4_36(v3, v);
    //constexpr qmu::vec4<T> v4_37(v3, v1);
    //constexpr qmu::vec4<T> v4_38(v, v3);
    //constexpr qmu::vec4<T> v4_39(v1, v3);

    // access
    v4.at<0>();
    v4.at<1>();
    v4.at<2>();
    v4.at<3>();

    //--------------------------------------------------------------------------
    // Span1

    // constructors
    constexpr qmu::span<T, 1> s1_1;
    constexpr qmu::span<T, 1> s1_2(s1);
    constexpr qmu::span<T, 1> s1_3(std::move(s1));
    constexpr qmu::span<T, 1> s1_7(v1, v1);
    constexpr qmu::span<T, 1> s1_8(v, v);

    //--------------------------------------------------------------------------
    // Span2

    // constructors
    constexpr qmu::span<T, 2> s2_1;
    constexpr qmu::span<T, 2> s2_2(s2);
    constexpr qmu::span<T, 2> s2_3(std::move(s2));
    constexpr qmu::span<T, 2> s2_7(v2, v2);
    constexpr qmu::span<T, 2> s2_8(v, v);

    //--------------------------------------------------------------------------
    // Span3

    // constructors
    constexpr qmu::span<T, 3> s3_1;
    constexpr qmu::span<T, 3> s3_2(s3);
    constexpr qmu::span<T, 3> s3_3(std::move(s3));
    constexpr qmu::span<T, 3> s3_7(v3, v3);
    constexpr qmu::span<T, 3> s3_8(v, v);

    //--------------------------------------------------------------------------
    // Span4

    // constructors
    constexpr qmu::span<T, 4> s4_1;
    constexpr qmu::span<T, 4> s4_2(s4);
    constexpr qmu::span<T, 4> s4_3(std::move(s4));
    constexpr qmu::span<T, 4> s4_7(v4, v4);
    constexpr qmu::span<T, 4> s4_8(v, v);
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

template <typename T1, typename T2>
void compileFunctionsTT() {
    T1 v; v;
    qmu::vec1<T1> v1; v1;
    qmu::vec2<T1> v2; v2;
    qmu::vec3<T1> v3; v3;
    qmu::vec4<T1> v4; v4;
    qmu::span1<T1> s1; s1;
    qmu::span2<T1> s2; s2;
    qmu::span3<T1> s3; s3;
    qmu::span4<T1> s4; s4;
    
    qmu::transnorm<T2>(v1);
    qmu::transnorm<T2>(v2);
    qmu::transnorm<T2>(v3);
    qmu::transnorm<T2>(v4);
}

template <typename T>
void compileFunctionsT() {
    compileFunctionsTT<T,                float>();
    compileFunctionsTT<T,               double>();
    compileFunctionsTT<T,          long double>();
    compileFunctionsTT<T,   signed        char>();
    compileFunctionsTT<T, unsigned        char>();
    compileFunctionsTT<T,   signed       short>();
    compileFunctionsTT<T, unsigned       short>();
    compileFunctionsTT<T,   signed         int>();
    compileFunctionsTT<T, unsigned         int>();
    compileFunctionsTT<T,   signed        long>();
    compileFunctionsTT<T, unsigned        long>();
    compileFunctionsTT<T,   signed long   long>();
    compileFunctionsTT<T, unsigned long   long>();

    T v;
    qmu::vec1<T> v1;
    qmu::vec2<T> v2;
    qmu::vec3<T> v3;
    qmu::vec4<T> v4;
    qmu::span1<T> s1;
    qmu::span2<T> s2;
    qmu::span3<T> s3;
    qmu::span4<T> s4;
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

    v1 /= qmu::vec1<T>(1);
    v2 /= qmu::vec2<T>(1);
    v3 /= qmu::vec3<T>(1);
    v4 /= qmu::vec4<T>(1);
    v1 /= T(1);
    v2 /= T(1);
    v3 /= T(1);
    v4 /= T(1);

    v1 %= qmu::vec1<T>(1);
    v2 %= qmu::vec2<T>(1);
    v3 %= qmu::vec3<T>(1);
    v4 %= qmu::vec4<T>(1);
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

    v1 / qmu::vec1<T>(1);
    v2 / qmu::vec2<T>(1);
    v3 / qmu::vec3<T>(1);
    v4 / qmu::vec4<T>(1);
    v1 / T(1);
    v2 / T(v);
    v3 / T(v);
    v4 / T(v);
    v / qmu::vec1<T>(1);
    v / qmu::vec2<T>(1);
    v / qmu::vec3<T>(1);
    v / qmu::vec4<T>(1);

    v1 % qmu::vec1<T>(1);
    v2 % qmu::vec2<T>(1);
    v3 % qmu::vec3<T>(1);
    v4 % qmu::vec4<T>(1);
    v1 % T(1);
    v2 % T(v);
    v3 % T(v);
    v4 % T(v);
    v % qmu::vec1<T>(1);
    v % qmu::vec2<T>(1);
    v % qmu::vec3<T>(1);
    v % qmu::vec4<T>(1);


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

    // condensation

    qmu::sum(v1);
    qmu::sum(v2);
    qmu::sum(v3);
    qmu::sum(v4);

    qmu::product(v1);
    qmu::product(v2);
    qmu::product(v3);
    qmu::product(v4);

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

    qmu::magnitude2(v1);
    qmu::magnitude2(v2);
    qmu::magnitude2(v3);
    qmu::magnitude2(v4);

    qmu::dot(v1, v1);
    qmu::dot(v2, v2);
    qmu::dot(v3, v3);
    qmu::dot(v4, v4);

    qmu::cross(v2, v2);
    qmu::cross(v3, v3);

    qmu::parallel(v1, v1);
    qmu::parallel(v2, v2);
    qmu::parallel(v3, v3);
    qmu::parallel(v4, v4);

    qmu::orthogonal(v1, v1);
    qmu::orthogonal(v2, v2);
    qmu::orthogonal(v3, v3);
    qmu::orthogonal(v4, v4);

    if constexpr (!std::is_unsigned_v<T>) {
        qmu::ortho(v2);
        qmu::ortho(v3);
    }

    qmu::min(v1);
    qmu::min(v2);
    qmu::min(v3);
    qmu::min(v4);

    qmu::min(v1, v1);
    qmu::min(v2, v2);
    qmu::min(v3, v3);
    qmu::min(v4, v4);

    qmu::min(v1, v1, v1, v1, v1);
    qmu::min(v2, v2, v2, v2, v2);
    qmu::min(v3, v3, v3, v3, v3);
    qmu::min(v4, v4, v4, v4, v4);

    qmu::min(v1, v);
    qmu::min(v2, v);
    qmu::min(v3, v);
    qmu::min(v4, v);
    qmu::min(v, v1);
    qmu::min(v, v2);
    qmu::min(v, v3);
    qmu::min(v, v4);
    
    qmu::max(v1);
    qmu::max(v2);
    qmu::max(v3);
    qmu::max(v4);

    qmu::max(v1, v1);
    qmu::max(v2, v2);
    qmu::max(v3, v3);
    qmu::max(v4, v4);

    qmu::max(v1, v1, v1, v1, v1);
    qmu::max(v2, v2, v2, v2, v2);
    qmu::max(v3, v3, v3, v3, v3);
    qmu::max(v4, v4, v4, v4, v4);

    qmu::max(v1, v);
    qmu::max(v2, v);
    qmu::max(v3, v);
    qmu::max(v4, v);
    qmu::max(v, v1);
    qmu::max(v, v2);
    qmu::max(v, v3);
    qmu::max(v, v4);

    qmu::minmax(v1);
    qmu::minmax(v2);
    qmu::minmax(v3);
    qmu::minmax(v4);

    qmu::sort(v1);
    qmu::sort(v2);
    qmu::sort(v3);
    qmu::sort(v4);

    qmu::clamp(v1, v, v);
    qmu::clamp(v2, v, v);
    qmu::clamp(v3, v, v);
    qmu::clamp(v4, v, v);

    qmu::clamp(v1, v1, v1);
    qmu::clamp(v2, v2, v2);
    qmu::clamp(v3, v3, v3);
    qmu::clamp(v4, v4, v4);

    qmu::abs(v1);
    qmu::abs(v2);
    qmu::abs(v3);
    qmu::abs(v4);

    qmu::floor(v1);
    qmu::floor(v2);
    qmu::floor(v3);
    qmu::floor(v4);

    qmu::ceil(v1);
    qmu::ceil(v2);
    qmu::ceil(v3);
    qmu::ceil(v4);

    qmu::intersect(s1, s1);
    qmu::intersect(s2, s2);
    qmu::intersect(s3, s3);
    qmu::intersect(s4, s4);

    qmu::toSpan(s1);
    qmu::toSpan(s2);
    qmu::toSpan(s3);
    qmu::toSpan(s4);
    
    qmu::toBound(s1);
    qmu::toBound(s2);
    qmu::toBound(s3);
    qmu::toBound(s4);
}

template <typename T>
void compileFunctionsFT() {
    T v(1);
    qmu::vec1<T> v1;
    qmu::vec2<T> v2;
    qmu::vec3<T> v3;
    qmu::vec4<T> v4;
    qmu::span1<T> s1;
    qmu::span2<T> s2;
    qmu::span3<T> s3;
    qmu::span4<T> s4;

    qmu::pow(v1, v);
    qmu::pow(v2, v);
    qmu::pow(v3, v);
    qmu::pow(v4, v);

    qmu::pow(v1, v1);
    qmu::pow(v2, v2);
    qmu::pow(v3, v3);
    qmu::pow(v4, v4);

    qmu::exp(v1);
    qmu::exp(v2);
    qmu::exp(v3);
    qmu::exp(v4);

    qmu::magnitude(v1);
    qmu::magnitude(v2);
    qmu::magnitude(v3);
    qmu::magnitude(v4);

    qmu::norm(v1);
    qmu::norm(v2);
    qmu::norm(v3);
    qmu::norm(v4);

    qmu::orthogonalize(v1, v1);
    qmu::orthogonalize(v2, v2);
    qmu::orthogonalize(v3, v3);
    qmu::orthogonalize(v4, v4);
    qmu::orthogonalize(v3, v3, v3);
    qmu::orthogonalize_n(v3, v3, v3);

    qmu::reflect(v2, v2);
    qmu::reflect(v3, v3);

    qmu::angle(v1, v1);
    qmu::angle_n(v1, v1);
    qmu::angle(v2, v2);
    qmu::angle_n(v2, v2);
    qmu::angle(v3, v3);
    qmu::angle_n(v3, v3);
    qmu::angle(v4, v4);
    qmu::angle_n(v4, v4);

    qmu::mix(v1, v1, v);
    qmu::mix(v2, v2, v);
    qmu::mix(v3, v3, v);
    qmu::mix(v4, v4, v);
    
    qmu::mix(v, v, v2);
    qmu::mix(v1, v1, v2);
    qmu::mix(v2, v2, v2);
    qmu::mix(v3, v3, v2);
    qmu::mix(v4, v4, v2);
    qmu::mix(v, v, v, v3);
    qmu::mix(v1, v1, v1, v3);
    qmu::mix(v2, v2, v2, v3);
    qmu::mix(v3, v3, v3, v3);
    qmu::mix(v4, v4, v4, v3);
    qmu::mix(v, v, v, v, v4);
    qmu::mix(v1, v1, v1, v1, v4);
    qmu::mix(v2, v2, v2, v2, v4);
    qmu::mix(v3, v3, v3, v3, v4);
    qmu::mix(v4, v4, v4, v4, v4);
}

template <typename T>
void compileFunctionsIT() {
    T v; v;
    qmu::vec1<T> v1; v1;
    qmu::vec2<T> v2; v2;
    qmu::vec3<T> v3; v3;
    qmu::vec4<T> v4; v4;
    qmu::span1<T> s1; s1;
    qmu::span2<T> s2; s2;
    qmu::span3<T> s3; s3;
    qmu::span4<T> s4; s4;

}

void compileFunctionsBT() {
    qmu::bvec1 b1;
    qmu::bvec2 b2;
    qmu::bvec3 b3;
    qmu::bvec4 b4;

    b1 && b1;
    b2 && b2;
    b3 && b3;
    b4 && b4;

    b1 || b1;
    b2 || b2;
    b3 || b3;
    b4 || b4;

    !b1;
    !b2;
    !b3;
    !b4;
    
    qmu::conjunction(b1);
    qmu::conjunction(b2);
    qmu::conjunction(b3);
    qmu::conjunction(b4);

    qmu::disjunction(b1);
    qmu::disjunction(b2);
    qmu::disjunction(b3);
    qmu::disjunction(b4);
}

void compileFunctions() {
    compileFunctionsT<               float>();
    compileFunctionsT<              double>();
    compileFunctionsT<         long double>();
    compileFunctionsT<  signed        char>();
    compileFunctionsT<unsigned        char>();
    compileFunctionsT<  signed       short>();
    compileFunctionsT<unsigned       short>();
    compileFunctionsT<  signed         int>();
    compileFunctionsT<unsigned         int>();
    compileFunctionsT<  signed        long>();
    compileFunctionsT<unsigned        long>();
    compileFunctionsT<  signed long   long>();
    compileFunctionsT<unsigned long   long>();
    
    compileFunctionsFT<      float>();
    compileFunctionsFT<     double>();
    compileFunctionsFT<long double>();

    compileFunctionsIT<  signed       char>();
    compileFunctionsIT<unsigned       char>();
    compileFunctionsIT<  signed      short>();
    compileFunctionsIT<unsigned      short>();
    compileFunctionsIT<  signed        int>();
    compileFunctionsIT<unsigned        int>();
    compileFunctionsIT<  signed       long>();
    compileFunctionsIT<unsigned       long>();
    compileFunctionsIT<  signed long  long>();
    compileFunctionsIT<unsigned long  long>();

    compileFunctionsBT();
}

template <typename T1, typename T2>
constexpr void compileFunctionsConstexprTT() {
    constexpr T1 v(T1(1.0));
    constexpr qmu::vec1<T1> v1(T1(1.0));
    constexpr qmu::vec2<T1> v2(T1(1.0));
    constexpr qmu::vec3<T1> v3(T1(1.0));
    constexpr qmu::vec4<T1> v4(T1(1.0));
    constexpr qmu::span1<T1> s1(v1, v1);
    constexpr qmu::span2<T1> s2(v2, v2);
    constexpr qmu::span3<T1> s3(v3, v3);
    constexpr qmu::span4<T1> s4(v4, v4);


}

template <typename T>
constexpr void compileFunctionsConstexprT() {
    compileFunctionsConstexprTT<T,                float>();
    compileFunctionsConstexprTT<T,               double>();
    compileFunctionsConstexprTT<T,          long double>();
    compileFunctionsConstexprTT<T,   signed        char>();
    compileFunctionsConstexprTT<T, unsigned        char>();
    compileFunctionsConstexprTT<T,   signed       short>();
    compileFunctionsConstexprTT<T, unsigned       short>();
    compileFunctionsConstexprTT<T,   signed         int>();
    compileFunctionsConstexprTT<T, unsigned         int>();
    compileFunctionsConstexprTT<T,   signed        long>();
    compileFunctionsConstexprTT<T, unsigned        long>();
    compileFunctionsConstexprTT<T,   signed long   long>();
    compileFunctionsConstexprTT<T, unsigned long   long>();

    constexpr T v(T(1.0));
    constexpr qmu::vec1<T> v1(T(1.0));
    constexpr qmu::vec2<T> v2(T(1.0));
    constexpr qmu::vec3<T> v3(T(1.0));
    constexpr qmu::vec4<T> v4(T(1.0));
    constexpr qmu::span1<T> s1(v1, v1);
    constexpr qmu::span2<T> s2(v2, v2);
    constexpr qmu::span3<T> s3(v3, v3);
    constexpr qmu::span4<T> s4(v4, v4);

    // uncategorized

    qmu::min(v1);
    qmu::min(v2);
    qmu::min(v3);
    qmu::min(v4);

    qmu::min(v1, v1);
    qmu::min(v2, v2);
    qmu::min(v3, v3);
    qmu::min(v4, v4);

    qmu::min(v1, v1, v1, v1, v1);
    qmu::min(v2, v2, v2, v2, v2);
    qmu::min(v3, v3, v3, v3, v3);
    qmu::min(v4, v4, v4, v4, v4);

    qmu::min(v1, v);
    qmu::min(v2, v);
    qmu::min(v3, v);
    qmu::min(v4, v);
    qmu::min(v, v1);
    qmu::min(v, v2);
    qmu::min(v, v3);
    qmu::min(v, v4);
    
    qmu::max(v1);
    qmu::max(v2);
    qmu::max(v3);
    qmu::max(v4);

    qmu::max(v1, v1);
    qmu::max(v2, v2);
    qmu::max(v3, v3);
    qmu::max(v4, v4);

    qmu::max(v1, v1, v1, v1, v1);
    qmu::max(v2, v2, v2, v2, v2);
    qmu::max(v3, v3, v3, v3, v3);
    qmu::max(v4, v4, v4, v4, v4);

    qmu::max(v1, v);
    qmu::max(v2, v);
    qmu::max(v3, v);
    qmu::max(v4, v);
    qmu::max(v, v1);
    qmu::max(v, v2);
    qmu::max(v, v3);
    qmu::max(v, v4);

    qmu::minmax(v1);
    qmu::minmax(v2);
    qmu::minmax(v3);
    qmu::minmax(v4);
}

template <typename T>
constexpr void compileFunctionsConstexprFT() {
    constexpr T v(T(1.0));
    constexpr qmu::vec1<T> v1(T(1.0));
    constexpr qmu::vec2<T> v2(T(1.0));
    constexpr qmu::vec3<T> v3(T(1.0));
    constexpr qmu::vec4<T> v4(T(1.0));
    constexpr qmu::span1<T> s1(v1, v1);
    constexpr qmu::span2<T> s2(v2, v2);
    constexpr qmu::span3<T> s3(v3, v3);
    constexpr qmu::span4<T> s4(v4, v4);
}

template <typename T>
constexpr void compileFunctionsConstexprIT() {
    constexpr T v(T(1.0));
    constexpr qmu::vec1<T> v1(T(1.0));
    constexpr qmu::vec2<T> v2(T(1.0));
    constexpr qmu::vec3<T> v3(T(1.0));
    constexpr qmu::vec4<T> v4(T(1.0));
    constexpr qmu::span1<T> s1(v1, v1);
    constexpr qmu::span2<T> s2(v2, v2);
    constexpr qmu::span3<T> s3(v3, v3);
    constexpr qmu::span4<T> s4(v4, v4);
}

constexpr void compileBoolFunctionsConstexpr() {
    qmu::bvec1 b1;
    qmu::bvec2 b2;
    qmu::bvec3 b3;
    qmu::bvec4 b4;
}

constexpr bool compileFunctionsConstexpr() {
    compileFunctionsConstexprT<      float>();
    compileFunctionsConstexprT<     double>();
    compileFunctionsConstexprT<long double>();
    compileBoolFunctionsConstexpr();

    return true;
}

template <typename T, qmu::nat t_n>
void testPropertiesTN() {
    static_assert(std::is_standard_layout_v<qmu::vec<T, t_n>>, "");
    static_assert(sizeof(qmu::vec<T, t_n>) == t_n * sizeof(T), "");
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

template <typename T1, typename T2, qmu::nat t_n>
void castCastsTTN() {
    static_cast<qmu::vec<T2, t_n>>(qmu::vec1<T1>());
    static_cast<qmu::vec<T2, t_n>>(qmu::vec2<T1>());
    static_cast<qmu::vec<T2, t_n>>(qmu::vec3<T1>());
    static_cast<qmu::vec<T2, t_n>>(qmu::vec4<T1>());

    static_cast<qmu::span<T2, t_n>>(qmu::span1<T1>());
    static_cast<qmu::span<T2, t_n>>(qmu::span2<T1>());
    static_cast<qmu::span<T2, t_n>>(qmu::span3<T1>());
    static_cast<qmu::span<T2, t_n>>(qmu::span4<T1>());
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
    compileCastsTT<T, long   long>();
}

void compileCasts() {
    compileCastsT<      float>();
    compileCastsT<     double>();
    compileCastsT<long double>();
    compileCastsT<       char>();
    compileCastsT<      short>();
    compileCastsT<        int>();
    compileCastsT<       long>();
    compileCastsT<long   long>();
}

void compileMembers() {
    int v;
    qmu::vec1<int> v1;
    qmu::vec2<int> v2;
    qmu::vec3<int> v3;
    qmu::vec4<int> v4;
    qmu::span1<int> s1;
    qmu::span2<int> s2;
    qmu::span3<int> s3;
    qmu::span4<int> s4;

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
    constexpr qmu::vec1<T> ax1(qmu::axis1X<T>);
    constexpr qmu::vec2<T> ax2(qmu::axis2X<T>);
    constexpr qmu::vec3<T> ax3(qmu::axis3X<T>);
    constexpr qmu::vec4<T> ax4(qmu::axis4X<T>);
    constexpr qmu::vec2<T> ay2(qmu::axis2Y<T>);
    constexpr qmu::vec3<T> ay3(qmu::axis3Y<T>);
    constexpr qmu::vec4<T> ay4(qmu::axis4Y<T>);
    constexpr qmu::vec3<T> az3(qmu::axis3Z<T>);
    constexpr qmu::vec4<T> az4(qmu::axis4Z<T>);
    constexpr qmu::vec4<T> aw4(qmu::axis4W<T>);
}

template <typename T>
constexpr void compileConstantsFT() {
    constexpr qmu::vec1<T> nv1(qmu::nanvec<T, 1>);
    constexpr qmu::vec2<T> nv2(qmu::nanvec<T, 2>);
    constexpr qmu::vec3<T> nv3(qmu::nanvec<T, 3>);
    constexpr qmu::vec4<T> nv4(qmu::nanvec<T, 4>);

    constexpr qmu::span1<T> ns1(qmu::nanspan<T, 1>);
    constexpr qmu::span2<T> ns2(qmu::nanspan<T, 2>);
    constexpr qmu::span3<T> ns3(qmu::nanspan<T, 3>);
    constexpr qmu::span4<T> ns4(qmu::nanspan<T, 4>);

    constexpr qmu::bound1<T> nb1(qmu::nanbound<T, 1>);
    constexpr qmu::bound2<T> nb2(qmu::nanbound<T, 2>);
    constexpr qmu::bound3<T> nb3(qmu::nanbound<T, 3>);
    constexpr qmu::bound4<T> nb4(qmu::nanbound<T, 4>);

    constexpr qmu::vec1<T> iv1(qmu::infvec<T, 1>);
    constexpr qmu::vec2<T> iv2(qmu::infvec<T, 2>);
    constexpr qmu::vec3<T> iv3(qmu::infvec<T, 3>);
    constexpr qmu::vec4<T> iv4(qmu::infvec<T, 4>);

    constexpr qmu::span1<T> is1(qmu::infspan<T, 1>);
    constexpr qmu::span2<T> is2(qmu::infspan<T, 2>);
    constexpr qmu::span3<T> is3(qmu::infspan<T, 3>);
    constexpr qmu::span4<T> is4(qmu::infspan<T, 4>);

    constexpr qmu::span1<T> nulls1(qmu::nullspan<T, 1>);
    constexpr qmu::span2<T> nulls2(qmu::nullspan<T, 2>);
    constexpr qmu::span3<T> nulls3(qmu::nullspan<T, 3>);
    constexpr qmu::span4<T> nulls4(qmu::nullspan<T, 4>);
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