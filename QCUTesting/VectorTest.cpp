#include "QCUTest.hpp"

#include "QCU/Vector.hpp"



namespace {



template <typename T>
void compileClassesT() {
    T v;
    qcu::vec1<T> v1;
    qcu::vec2<T> v2;
    qcu::vec3<T> v3;
    qcu::vec4<T> v4;
    qcu::span1<T> s1;
    qcu::span2<T> s2;
    qcu::span3<T> s3;
    qcu::span4<T> s4;

    //--------------------------------------------------------------------------
    // Vec1
    
    // constructors
    qcu::vec1<T> v1_1;
    qcu::vec1<T> v1_2(v1);
    qcu::vec1<T> v1_3(std::move(v1));
    qcu::vec1<T> v1_4(v);
    qcu::vec1<T> v1_5(v2);
    qcu::vec1<T> v1_6(v3);
    qcu::vec1<T> v1_7(v4);
    
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
    qcu::vec2<T> v2_01;
    qcu::vec2<T> v2_02(v2);
    qcu::vec2<T> v2_03(std::move(v2));
    qcu::vec2<T> v2_04(v);
    qcu::vec2<T> v2_05(v1);
    qcu::vec2<T> v2_06(v3);
    qcu::vec2<T> v2_07(v4);
    qcu::vec2<T> v2_08(v, v);
    qcu::vec2<T> v2_09(v1, v);
    qcu::vec2<T> v2_10(v, v1);
    qcu::vec2<T> v2_11(v1, v1);

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
    qcu::vec3<T> v3_01;
    qcu::vec3<T> v3_02(v3);
    qcu::vec3<T> v3_03(std::move(v3));
    qcu::vec3<T> v3_04(v);
    qcu::vec3<T> v3_05(v1);
    qcu::vec3<T> v3_06(v2);
    qcu::vec3<T> v3_07(v4);
    qcu::vec3<T> v3_08(v, v, v);
    qcu::vec3<T> v3_09(v1, v, v);
    qcu::vec3<T> v3_10(v, v1, v);
    qcu::vec3<T> v3_11(v, v, v1);
    qcu::vec3<T> v3_12(v1, v1, v);
    qcu::vec3<T> v3_13(v1, v, v1);
    qcu::vec3<T> v3_14(v, v1, v1);
    qcu::vec3<T> v3_15(v1, v1, v1);
    qcu::vec3<T> v3_16(v2, v);
    qcu::vec3<T> v3_17(v2, v1);
    qcu::vec3<T> v3_18(v, v2);
    qcu::vec3<T> v3_19(v1, v2);

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
    qcu::vec4<T> v4_01;
    qcu::vec4<T> v4_02(v4);
    qcu::vec4<T> v4_03(std::move(v4));
    qcu::vec4<T> v4_04(v);
    qcu::vec4<T> v4_05(v1);
    qcu::vec4<T> v4_06(v2);
    qcu::vec4<T> v4_07(v3);
    qcu::vec4<T> v4_08(v, v, v, v);
    qcu::vec4<T> v4_09(v1, v, v, v);
    qcu::vec4<T> v4_10(v, v1, v, v);
    qcu::vec4<T> v4_11(v, v, v1, v);
    qcu::vec4<T> v4_12(v, v, v, v1);
    qcu::vec4<T> v4_13(v1, v1, v, v);
    qcu::vec4<T> v4_14(v1, v, v1, v);
    qcu::vec4<T> v4_15(v1, v, v, v1);
    qcu::vec4<T> v4_16(v, v1, v, v1);
    qcu::vec4<T> v4_17(v, v, v1, v1);
    qcu::vec4<T> v4_18(v1, v1, v1, v);
    qcu::vec4<T> v4_19(v1, v1, v, v1);
    qcu::vec4<T> v4_20(v1, v, v1, v1);
    qcu::vec4<T> v4_21(v, v1, v1, v1);
    qcu::vec4<T> v4_22(v1, v1, v1, v1);
    qcu::vec4<T> v4_23(v2, v, v);
    qcu::vec4<T> v4_24(v2, v1, v);
    qcu::vec4<T> v4_25(v2, v, v1);
    qcu::vec4<T> v4_26(v2, v1, v1);
    qcu::vec4<T> v4_27(v, v2, v);
    qcu::vec4<T> v4_28(v1, v2, v);
    qcu::vec4<T> v4_29(v, v2, v1);
    qcu::vec4<T> v4_30(v1, v2, v1);
    qcu::vec4<T> v4_31(v, v, v2);
    qcu::vec4<T> v4_32(v1, v, v2);
    qcu::vec4<T> v4_33(v, v1, v2);
    qcu::vec4<T> v4_34(v1, v1, v2);
    qcu::vec4<T> v4_35(v2, v2);
    qcu::vec4<T> v4_36(v3, v);
    qcu::vec4<T> v4_37(v3, v1);
    qcu::vec4<T> v4_38(v, v3);
    qcu::vec4<T> v4_39(v1, v3);

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
    qcu::span<T, 1> s1_1;
    qcu::span<T, 1> s1_2(s1);
    qcu::span<T, 1> s1_3(std::move(s1));
    qcu::span<T, 1> s1_7(v1, v1);
    qcu::span<T, 1> s1_8(v, v);

    // asignment operators
    s1 = s1;
    s1 = std::move(s1);

    // other
    s1.toString();

    //--------------------------------------------------------------------------
    // Span2

    // constructors
    qcu::span<T, 2> s2_1;
    qcu::span<T, 2> s2_2(s2);
    qcu::span<T, 2> s2_3(std::move(s2));
    qcu::span<T, 2> s2_7(v2, v2);
    qcu::span<T, 2> s2_8(v, v);

    // asignment operators
    s2 = s2;
    s2 = std::move(s2);

    // other
    s2.toString();

    //--------------------------------------------------------------------------
    // Span3

    // constructors
    qcu::span<T, 3> s3_1;
    qcu::span<T, 3> s3_2(s3);
    qcu::span<T, 3> s3_3(std::move(s3));
    qcu::span<T, 3> s3_7(v3, v3);
    qcu::span<T, 3> s3_8(v, v);

    // asignment operators
    s3 = s3;
    s3 = std::move(s3);

    // other
    s3.toString();

    //--------------------------------------------------------------------------
    // Span4

    // constructors
    qcu::span<T, 4> s4_1;
    qcu::span<T, 4> s4_2(s4);
    qcu::span<T, 4> s4_3(std::move(s4));
    qcu::span<T, 4> s4_7(v4, v4);
    qcu::span<T, 4> s4_8(v, v);

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
    constexpr qcu::vec1<T> v1;
    constexpr qcu::vec2<T> v2;
    constexpr qcu::vec3<T> v3;
    constexpr qcu::vec4<T> v4;
    constexpr qcu::span1<T> s1;
    constexpr qcu::span2<T> s2;
    constexpr qcu::span3<T> s3;
    constexpr qcu::span4<T> s4;

    //--------------------------------------------------------------------------
    // Vec1
    
    // constructors
    constexpr qcu::vec1<T> v1_1;
    constexpr qcu::vec1<T> v1_2(v1);
    constexpr qcu::vec1<T> v1_3(std::move(v1));
    constexpr qcu::vec1<T> v1_4(v);
    constexpr qcu::vec1<T> v1_5(v2);
    constexpr qcu::vec1<T> v1_6(v3);
    constexpr qcu::vec1<T> v1_7(v4);

    // access
    v1.at<0>();

    //--------------------------------------------------------------------------
    // Vec2

    // constructors
    constexpr qcu::vec2<T> v2_01;
    constexpr qcu::vec2<T> v2_02(v2);
    constexpr qcu::vec2<T> v2_03(std::move(v2));
    constexpr qcu::vec2<T> v2_04(v);
    constexpr qcu::vec2<T> v2_05(v1);
    constexpr qcu::vec2<T> v2_06(v3);
    constexpr qcu::vec2<T> v2_07(v4);
    constexpr qcu::vec2<T> v2_08(v, v);
    //constexpr qcu::vec2<T> v2_09(v1, v);
    //constexpr qcu::vec2<T> v2_10(v, v1);
    //constexpr qcu::vec2<T> v2_11(v1, v1);

    // access
    v2.at<0>();
    v2.at<1>();

    //--------------------------------------------------------------------------
    // Vec3

    // constructors
    constexpr qcu::vec3<T> v3_01;
    constexpr qcu::vec3<T> v3_02(v3);
    constexpr qcu::vec3<T> v3_03(std::move(v3));
    constexpr qcu::vec3<T> v3_04(v);
    constexpr qcu::vec3<T> v3_05(v1);
    constexpr qcu::vec3<T> v3_06(v2);
    constexpr qcu::vec3<T> v3_07(v4);
    constexpr qcu::vec3<T> v3_08(v, v, v);
    //constexpr qcu::vec3<T> v3_09(v1, v, v);
    //constexpr qcu::vec3<T> v3_10(v, v1, v);
    //constexpr qcu::vec3<T> v3_11(v, v, v1);
    //constexpr qcu::vec3<T> v3_12(v1, v1, v);
    //constexpr qcu::vec3<T> v3_13(v1, v, v1);
    //constexpr qcu::vec3<T> v3_14(v, v1, v1);
    //constexpr qcu::vec3<T> v3_15(v1, v1, v1);
    constexpr qcu::vec3<T> v3_16(v2, v);
    //constexpr qcu::vec3<T> v3_17(v2, v1);
    //constexpr qcu::vec3<T> v3_18(v, v2);
    //constexpr qcu::vec3<T> v3_19(v1, v2);

    // access
    v3.at<0>();
    v3.at<1>();
    v3.at<2>();

    //--------------------------------------------------------------------------
    // Vec4

    // constructors
    constexpr qcu::vec4<T> v4_01;
    constexpr qcu::vec4<T> v4_02(v4);
    constexpr qcu::vec4<T> v4_03(std::move(v4));
    constexpr qcu::vec4<T> v4_04(v);
    constexpr qcu::vec4<T> v4_05(v1);
    constexpr qcu::vec4<T> v4_06(v2);
    constexpr qcu::vec4<T> v4_07(v3);
    constexpr qcu::vec4<T> v4_08(v, v, v, v);
    //constexpr qcu::vec4<T> v4_09(v1, v, v, v);
    //constexpr qcu::vec4<T> v4_10(v, v1, v, v);
    //constexpr qcu::vec4<T> v4_11(v, v, v1, v);
    //constexpr qcu::vec4<T> v4_12(v, v, v, v1);
    //constexpr qcu::vec4<T> v4_13(v1, v1, v, v);
    //constexpr qcu::vec4<T> v4_14(v1, v, v1, v);
    //constexpr qcu::vec4<T> v4_15(v1, v, v, v1);
    //constexpr qcu::vec4<T> v4_16(v, v1, v, v1);
    //constexpr qcu::vec4<T> v4_17(v, v, v1, v1);
    //constexpr qcu::vec4<T> v4_18(v1, v1, v1, v);
    //constexpr qcu::vec4<T> v4_19(v1, v1, v, v1);
    //constexpr qcu::vec4<T> v4_20(v1, v, v1, v1);
    //constexpr qcu::vec4<T> v4_21(v, v1, v1, v1);
    //constexpr qcu::vec4<T> v4_22(v1, v1, v1, v1);
    //constexpr qcu::vec4<T> v4_23(v2, v, v);
    //constexpr qcu::vec4<T> v4_24(v2, v1, v);
    //constexpr qcu::vec4<T> v4_25(v2, v, v1);
    //constexpr qcu::vec4<T> v4_26(v2, v1, v1);
    //constexpr qcu::vec4<T> v4_27(v, v2, v);
    //constexpr qcu::vec4<T> v4_28(v1, v2, v);
    //constexpr qcu::vec4<T> v4_29(v, v2, v1);
    //constexpr qcu::vec4<T> v4_30(v1, v2, v1);
    //constexpr qcu::vec4<T> v4_31(v, v, v2);
    //constexpr qcu::vec4<T> v4_32(v1, v, v2);
    //constexpr qcu::vec4<T> v4_33(v, v1, v2);
    //constexpr qcu::vec4<T> v4_34(v1, v1, v2);
    constexpr qcu::vec4<T> v4_35(v2, v2);
    constexpr qcu::vec4<T> v4_36(v3, v);
    //constexpr qcu::vec4<T> v4_37(v3, v1);
    //constexpr qcu::vec4<T> v4_38(v, v3);
    //constexpr qcu::vec4<T> v4_39(v1, v3);

    // access
    v4.at<0>();
    v4.at<1>();
    v4.at<2>();
    v4.at<3>();

    //--------------------------------------------------------------------------
    // Span1

    // constructors
    constexpr qcu::span<T, 1> s1_1;
    constexpr qcu::span<T, 1> s1_2(s1);
    constexpr qcu::span<T, 1> s1_3(std::move(s1));
    constexpr qcu::span<T, 1> s1_7(v1, v1);
    constexpr qcu::span<T, 1> s1_8(v, v);

    //--------------------------------------------------------------------------
    // Span2

    // constructors
    constexpr qcu::span<T, 2> s2_1;
    constexpr qcu::span<T, 2> s2_2(s2);
    constexpr qcu::span<T, 2> s2_3(std::move(s2));
    constexpr qcu::span<T, 2> s2_7(v2, v2);
    constexpr qcu::span<T, 2> s2_8(v, v);

    //--------------------------------------------------------------------------
    // Span3

    // constructors
    constexpr qcu::span<T, 3> s3_1;
    constexpr qcu::span<T, 3> s3_2(s3);
    constexpr qcu::span<T, 3> s3_3(std::move(s3));
    constexpr qcu::span<T, 3> s3_7(v3, v3);
    constexpr qcu::span<T, 3> s3_8(v, v);

    //--------------------------------------------------------------------------
    // Span4

    // constructors
    constexpr qcu::span<T, 4> s4_1;
    constexpr qcu::span<T, 4> s4_2(s4);
    constexpr qcu::span<T, 4> s4_3(std::move(s4));
    constexpr qcu::span<T, 4> s4_7(v4, v4);
    constexpr qcu::span<T, 4> s4_8(v, v);
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
    qcu::vec1<T1> v1; v1;
    qcu::vec2<T1> v2; v2;
    qcu::vec3<T1> v3; v3;
    qcu::vec4<T1> v4; v4;
    qcu::span1<T1> s1; s1;
    qcu::span2<T1> s2; s2;
    qcu::span3<T1> s3; s3;
    qcu::span4<T1> s4; s4;
    
    qcu::transnorm<T2>(v1);
    qcu::transnorm<T2>(v2);
    qcu::transnorm<T2>(v3);
    qcu::transnorm<T2>(v4);
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
    qcu::vec1<T> v1;
    qcu::vec2<T> v2;
    qcu::vec3<T> v3;
    qcu::vec4<T> v4;
    qcu::span1<T> s1;
    qcu::span2<T> s2;
    qcu::span3<T> s3;
    qcu::span4<T> s4;
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

    v1 /= qcu::vec1<T>(1);
    v2 /= qcu::vec2<T>(1);
    v3 /= qcu::vec3<T>(1);
    v4 /= qcu::vec4<T>(1);
    v1 /= T(1);
    v2 /= T(1);
    v3 /= T(1);
    v4 /= T(1);

    v1 %= qcu::vec1<T>(1);
    v2 %= qcu::vec2<T>(1);
    v3 %= qcu::vec3<T>(1);
    v4 %= qcu::vec4<T>(1);
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

    v1 / qcu::vec1<T>(1);
    v2 / qcu::vec2<T>(1);
    v3 / qcu::vec3<T>(1);
    v4 / qcu::vec4<T>(1);
    v1 / T(1);
    v2 / T(v);
    v3 / T(v);
    v4 / T(v);
    v / qcu::vec1<T>(1);
    v / qcu::vec2<T>(1);
    v / qcu::vec3<T>(1);
    v / qcu::vec4<T>(1);

    v1 % qcu::vec1<T>(1);
    v2 % qcu::vec2<T>(1);
    v3 % qcu::vec3<T>(1);
    v4 % qcu::vec4<T>(1);
    v1 % T(1);
    v2 % T(v);
    v3 % T(v);
    v4 % T(v);
    v % qcu::vec1<T>(1);
    v % qcu::vec2<T>(1);
    v % qcu::vec3<T>(1);
    v % qcu::vec4<T>(1);


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

    qcu::sum(v1);
    qcu::sum(v2);
    qcu::sum(v3);
    qcu::sum(v4);

    qcu::product(v1);
    qcu::product(v2);
    qcu::product(v3);
    qcu::product(v4);

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

    qcu::magnitude2(v1);
    qcu::magnitude2(v2);
    qcu::magnitude2(v3);
    qcu::magnitude2(v4);

    qcu::dot(v1, v1);
    qcu::dot(v2, v2);
    qcu::dot(v3, v3);
    qcu::dot(v4, v4);

    qcu::cross(v2, v2);
    qcu::cross(v3, v3);

    qcu::parallel(v1, v1);
    qcu::parallel(v2, v2);
    qcu::parallel(v3, v3);
    qcu::parallel(v4, v4);

    qcu::orthogonal(v1, v1);
    qcu::orthogonal(v2, v2);
    qcu::orthogonal(v3, v3);
    qcu::orthogonal(v4, v4);

    if constexpr (!std::is_unsigned_v<T>) {
        qcu::ortho(v2);
        qcu::ortho(v3);
    }

    qcu::min(v1);
    qcu::min(v2);
    qcu::min(v3);
    qcu::min(v4);

    qcu::min(v1, v1);
    qcu::min(v2, v2);
    qcu::min(v3, v3);
    qcu::min(v4, v4);

    qcu::min(v1, v1, v1, v1, v1);
    qcu::min(v2, v2, v2, v2, v2);
    qcu::min(v3, v3, v3, v3, v3);
    qcu::min(v4, v4, v4, v4, v4);

    qcu::min(v1, v);
    qcu::min(v2, v);
    qcu::min(v3, v);
    qcu::min(v4, v);
    qcu::min(v, v1);
    qcu::min(v, v2);
    qcu::min(v, v3);
    qcu::min(v, v4);
    
    qcu::max(v1);
    qcu::max(v2);
    qcu::max(v3);
    qcu::max(v4);

    qcu::max(v1, v1);
    qcu::max(v2, v2);
    qcu::max(v3, v3);
    qcu::max(v4, v4);

    qcu::max(v1, v1, v1, v1, v1);
    qcu::max(v2, v2, v2, v2, v2);
    qcu::max(v3, v3, v3, v3, v3);
    qcu::max(v4, v4, v4, v4, v4);

    qcu::max(v1, v);
    qcu::max(v2, v);
    qcu::max(v3, v);
    qcu::max(v4, v);
    qcu::max(v, v1);
    qcu::max(v, v2);
    qcu::max(v, v3);
    qcu::max(v, v4);

    qcu::minmax(v1);
    qcu::minmax(v2);
    qcu::minmax(v3);
    qcu::minmax(v4);

    qcu::sort(v1);
    qcu::sort(v2);
    qcu::sort(v3);
    qcu::sort(v4);

    qcu::clamp(v1, v, v);
    qcu::clamp(v2, v, v);
    qcu::clamp(v3, v, v);
    qcu::clamp(v4, v, v);

    qcu::clamp(v1, v1, v1);
    qcu::clamp(v2, v2, v2);
    qcu::clamp(v3, v3, v3);
    qcu::clamp(v4, v4, v4);

    qcu::abs(v1);
    qcu::abs(v2);
    qcu::abs(v3);
    qcu::abs(v4);

    qcu::zero(v1);
    qcu::zero(v2);
    qcu::zero(v3);
    qcu::zero(v4);

    qcu::equal(v1, v1);
    qcu::equal(v2, v2);
    qcu::equal(v3, v3);
    qcu::equal(v4, v4);

    qcu::equal(v1);
    qcu::equal(v2);
    qcu::equal(v3);
    qcu::equal(v4);

    qcu::floor(v1);
    qcu::floor(v2);
    qcu::floor(v3);
    qcu::floor(v4);

    qcu::ceil(v1);
    qcu::ceil(v2);
    qcu::ceil(v3);
    qcu::ceil(v4);

    qcu::intersect(s1, s1);
    qcu::intersect(s2, s2);
    qcu::intersect(s3, s3);
    qcu::intersect(s4, s4);

    qcu::toSpan(s1);
    qcu::toSpan(s2);
    qcu::toSpan(s3);
    qcu::toSpan(s4);
    
    qcu::toBound(s1);
    qcu::toBound(s2);
    qcu::toBound(s3);
    qcu::toBound(s4);
}

template <typename T>
void compileFunctionsFT() {
    T v(1);
    qcu::vec1<T> v1;
    qcu::vec2<T> v2;
    qcu::vec3<T> v3;
    qcu::vec4<T> v4;
    qcu::span1<T> s1;
    qcu::span2<T> s2;
    qcu::span3<T> s3;
    qcu::span4<T> s4;

    qcu::equalE(v1, v1);
    qcu::equalE(v2, v2);
    qcu::equalE(v3, v3);
    qcu::equalE(v4, v4);
    qcu::equalE(v1, v1, v1);
    qcu::equalE(v2, v2, v2);
    qcu::equalE(v3, v3, v3);
    qcu::equalE(v4, v4, v4);

    qcu::pow(v1, v);
    qcu::pow(v2, v);
    qcu::pow(v3, v);
    qcu::pow(v4, v);

    qcu::pow(v1, v1);
    qcu::pow(v2, v2);
    qcu::pow(v3, v3);
    qcu::pow(v4, v4);

    qcu::exp(v1);
    qcu::exp(v2);
    qcu::exp(v3);
    qcu::exp(v4);

    qcu::magnitude(v1);
    qcu::magnitude(v2);
    qcu::magnitude(v3);
    qcu::magnitude(v4);

    qcu::norm(v1);
    qcu::norm(v2);
    qcu::norm(v3);
    qcu::norm(v4);

    qcu::orthogonalize(v1, v1);
    qcu::orthogonalize(v2, v2);
    qcu::orthogonalize(v3, v3);
    qcu::orthogonalize(v4, v4);
    qcu::orthogonalize(v3, v3, v3);
    qcu::orthogonalize_n(v3, v3, v3);

    qcu::reflect(v2, v2);
    qcu::reflect(v3, v3);

    qcu::angle(v1, v1);
    qcu::angle_n(v1, v1);
    qcu::angle(v2, v2);
    qcu::angle_n(v2, v2);
    qcu::angle(v3, v3);
    qcu::angle_n(v3, v3);
    qcu::angle(v4, v4);
    qcu::angle_n(v4, v4);

    qcu::mix(v1, v1, v);
    qcu::mix(v2, v2, v);
    qcu::mix(v3, v3, v);
    qcu::mix(v4, v4, v);
    
    qcu::mix(v, v, v2);
    qcu::mix(v1, v1, v2);
    qcu::mix(v2, v2, v2);
    qcu::mix(v3, v3, v2);
    qcu::mix(v4, v4, v2);
    qcu::mix(v, v, v, v3);
    qcu::mix(v1, v1, v1, v3);
    qcu::mix(v2, v2, v2, v3);
    qcu::mix(v3, v3, v3, v3);
    qcu::mix(v4, v4, v4, v3);
    qcu::mix(v, v, v, v, v4);
    qcu::mix(v1, v1, v1, v1, v4);
    qcu::mix(v2, v2, v2, v2, v4);
    qcu::mix(v3, v3, v3, v3, v4);
    qcu::mix(v4, v4, v4, v4, v4);
}

template <typename T>
void compileFunctionsIT() {
    T v; v;
    qcu::vec1<T> v1; v1;
    qcu::vec2<T> v2; v2;
    qcu::vec3<T> v3; v3;
    qcu::vec4<T> v4; v4;
    qcu::span1<T> s1; s1;
    qcu::span2<T> s2; s2;
    qcu::span3<T> s3; s3;
    qcu::span4<T> s4; s4;
    
    qcu::mipmaps(v1);
    qcu::mipmaps(v2);
    qcu::mipmaps(v3);
    qcu::mipmaps(v4);
}

void compileFunctionsBT() {
    qcu::bvec1 b1;
    qcu::bvec2 b2;
    qcu::bvec3 b3;
    qcu::bvec4 b4;

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
    
    qcu::conjunction(b1);
    qcu::conjunction(b2);
    qcu::conjunction(b3);
    qcu::conjunction(b4);

    qcu::disjunction(b1);
    qcu::disjunction(b2);
    qcu::disjunction(b3);
    qcu::disjunction(b4);
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
    constexpr qcu::vec1<T1> v1(T1(1.0));
    constexpr qcu::vec2<T1> v2(T1(1.0));
    constexpr qcu::vec3<T1> v3(T1(1.0));
    constexpr qcu::vec4<T1> v4(T1(1.0));
    constexpr qcu::span1<T1> s1(v1, v1);
    constexpr qcu::span2<T1> s2(v2, v2);
    constexpr qcu::span3<T1> s3(v3, v3);
    constexpr qcu::span4<T1> s4(v4, v4);


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
    constexpr qcu::vec1<T> v1(T(1.0));
    constexpr qcu::vec2<T> v2(T(1.0));
    constexpr qcu::vec3<T> v3(T(1.0));
    constexpr qcu::vec4<T> v4(T(1.0));
    constexpr qcu::span1<T> s1(v1, v1);
    constexpr qcu::span2<T> s2(v2, v2);
    constexpr qcu::span3<T> s3(v3, v3);
    constexpr qcu::span4<T> s4(v4, v4);

    // arithmetic

    //+v1;
    //+v2;
    //+v3;
    //+v4;

    //-v1;
    //-v2;
    //-v3;
    //-v4;

    //v1 + v1;
    //v2 + v2;
    //v3 + v3;
    //v4 + v4;
    //v1 + v;
    //v2 + v;
    //v3 + v;
    //v4 + v;
    //v + v1;
    //v + v2;
    //v + v3;
    //v + v4;

    //v1 - v1;
    //v2 - v2;
    //v3 - v3;
    //v4 - v4;
    //v1 - v;
    //v2 - v;
    //v3 - v;
    //v4 - v;
    //v - v1;
    //v - v2;
    //v - v3;
    //v - v4;

    //v1 * v1;
    //v2 * v2;
    //v3 * v3;
    //v4 * v4;
    //v1 * v;
    //v2 * v;
    //v3 * v;
    //v4 * v;
    //v * v1;
    //v * v2;
    //v * v3;
    //v * v4;

    //v1 / qcu::vec1<T>(1);
    //v2 / qcu::vec2<T>(1);
    //v3 / qcu::vec3<T>(1);
    //v4 / qcu::vec4<T>(1);
    //v1 / T(1);
    //v2 / T(v);
    //v3 / T(v);
    //v4 / T(v);
    //v / qcu::vec1<T>(1);
    //v / qcu::vec2<T>(1);
    //v / qcu::vec3<T>(1);
    //v / qcu::vec4<T>(1);

    //v1 % qcu::vec1<T>(1);
    //v2 % qcu::vec2<T>(1);
    //v3 % qcu::vec3<T>(1);
    //v4 % qcu::vec4<T>(1);
    //v1 % T(1);
    //v2 % T(v);
    //v3 % T(v);
    //v4 % T(v);
    //v % qcu::vec1<T>(1);
    //v % qcu::vec2<T>(1);
    //v % qcu::vec3<T>(1);
    //v % qcu::vec4<T>(1);


    // comparison

    //v1 == v1;
    //v2 == v2;
    //v3 == v3;
    //v4 == v4;
    //v1 == v;
    //v2 == v;
    //v3 == v;
    //v4 == v;
    //v == v1;
    //v == v2;
    //v == v3;
    //v == v4;
    //s1 == s1;
    //s2 == s2;
    //s3 == s3;
    //s4 == s4;

    //v1 != v1;
    //v2 != v2;
    //v3 != v3;
    //v4 != v4;
    //v1 != v;
    //v2 != v;
    //v3 != v;
    //v4 != v;
    //v != v1;
    //v != v2;
    //v != v3;
    //v != v4;
    //s1 != s1;
    //s2 != s2;
    //s3 != s3;
    //s4 != s4;

    //v1 < v1;
    //v2 < v2;
    //v3 < v3;
    //v4 < v4;
    //v1 < v;
    //v2 < v;
    //v3 < v;
    //v4 < v;
    //v < v1;
    //v < v2;
    //v < v3;
    //v < v4;

    //v1 > v1;
    //v2 > v2;
    //v3 > v3;
    //v4 > v4;
    //v1 > v;
    //v2 > v;
    //v3 > v;
    //v4 > v;
    //v > v1;
    //v > v2;
    //v > v3;
    //v > v4;

    //v1 <= v1;
    //v2 <= v2;
    //v3 <= v3;
    //v4 <= v4;
    //v1 <= v;
    //v2 <= v;
    //v3 <= v;
    //v4 <= v;
    //v <= v1;
    //v <= v2;
    //v <= v3;
    //v <= v4;

    //v1 >= v1;
    //v2 >= v2;
    //v3 >= v3;
    //v4 >= v4;
    //v1 >= v;
    //v2 >= v;
    //v3 >= v;
    //v4 >= v;
    //v >= v1;
    //v >= v2;
    //v >= v3;
    //v >= v4;

    // condensation

    //qcu::sum(v1);
    //qcu::sum(v2);
    //qcu::sum(v3);
    //qcu::sum(v4);

    //qcu::product(v1);
    //qcu::product(v2);
    //qcu::product(v3);
    //qcu::product(v4);

    // uncategorized

    //qcu::min(v1);
    //qcu::min(v2);
    //qcu::min(v3);
    //qcu::min(v4);

    //qcu::min(v1, v1);
    //qcu::min(v2, v2);
    //qcu::min(v3, v3);
    //qcu::min(v4, v4);

    //qcu::min(v1, v1, v1, v1, v1);
    //qcu::min(v2, v2, v2, v2, v2);
    //qcu::min(v3, v3, v3, v3, v3);
    //qcu::min(v4, v4, v4, v4, v4);

    //qcu::min(v1, v);
    //qcu::min(v2, v);
    //qcu::min(v3, v);
    //qcu::min(v4, v);
    //qcu::min(v, v1);
    //qcu::min(v, v2);
    //qcu::min(v, v3);
    //qcu::min(v, v4);
    
    //qcu::max(v1);
    //qcu::max(v2);
    //qcu::max(v3);
    //qcu::max(v4);

    //qcu::max(v1, v1);
    //qcu::max(v2, v2);
    //qcu::max(v3, v3);
    //qcu::max(v4, v4);

    //qcu::max(v1, v1, v1, v1, v1);
    //qcu::max(v2, v2, v2, v2, v2);
    //qcu::max(v3, v3, v3, v3, v3);
    //qcu::max(v4, v4, v4, v4, v4);

    //qcu::max(v1, v);
    //qcu::max(v2, v);
    //qcu::max(v3, v);
    //qcu::max(v4, v);
    //qcu::max(v, v1);
    //qcu::max(v, v2);
    //qcu::max(v, v3);
    //qcu::max(v, v4);

    //qcu::minmax(v1);
    //qcu::minmax(v2);
    //qcu::minmax(v3);
    //qcu::minmax(v4);

    //qcu::clamp(v1, v, v);
    //qcu::clamp(v2, v, v);
    //qcu::clamp(v3, v, v);
    //qcu::clamp(v4, v, v);

    //qcu::clamp(v1, v1, v1);
    //qcu::clamp(v2, v2, v2);
    //qcu::clamp(v3, v3, v3);
    //qcu::clamp(v4, v4, v4);

    //qcu::abs(v1);
    //qcu::abs(v2);
    //qcu::abs(v3);
    //qcu::abs(v4);

    //qcu::zero(v1);
    //qcu::zero(v2);
    //qcu::zero(v3);
    //qcu::zero(v4);

    //qcu::equal(v1, v1);
    //qcu::equal(v2, v2);
    //qcu::equal(v3, v3);
    //qcu::equal(v4, v4);

    //qcu::equal(v1);
    //qcu::equal(v2);
    //qcu::equal(v3);
    //qcu::equal(v4);

    //qcu::floor(v1);
    //qcu::floor(v2);
    //qcu::floor(v3);
    //qcu::floor(v4);

    //qcu::ceil(v1);
    //qcu::ceil(v2);
    //qcu::ceil(v3);
    //qcu::ceil(v4);

    //qcu::toSpan(s1);
    //qcu::toSpan(s2);
    //qcu::toSpan(s3);
    //qcu::toSpan(s4);
    
    //qcu::toBound(s1);
    //qcu::toBound(s2);
    //qcu::toBound(s3);
    //qcu::toBound(s4);

    //qcu::intersect(s1, s1);
    //qcu::intersect(s2, s2);
    //qcu::intersect(s3, s3);
    //qcu::intersect(s4, s4);
}

template <typename T>
constexpr void compileFunctionsConstexprFT() {
    constexpr T v(T(1.0));
    constexpr qcu::vec1<T> v1(T(1.0));
    constexpr qcu::vec2<T> v2(T(1.0));
    constexpr qcu::vec3<T> v3(T(1.0));
    constexpr qcu::vec4<T> v4(T(1.0));
    constexpr qcu::span1<T> s1(v1, v1);
    constexpr qcu::span2<T> s2(v2, v2);
    constexpr qcu::span3<T> s3(v3, v3);
    constexpr qcu::span4<T> s4(v4, v4);

    //qcu::equalE(v1, v1);
    //qcu::equalE(v2, v2);
    //qcu::equalE(v3, v3);
    //qcu::equalE(v4, v4);
    //qcu::equalE(v1, v1, v1);
    //qcu::equalE(v2, v2, v2);
    //qcu::equalE(v3, v3, v3);
    //qcu::equalE(v4, v4. v4);

    //qcu::mix(v1, v1, v);
    //qcu::mix(v2, v2, v);
    //qcu::mix(v3, v3, v);
    //qcu::mix(v4, v4, v);

    //qcu::mix(v, v, v2);
    //qcu::mix(v1, v1, v2);
    //qcu::mix(v2, v2, v2);
    //qcu::mix(v3, v3, v2);
    //qcu::mix(v4, v4, v2);
    //qcu::mix(v, v, v, v3);
    //qcu::mix(v1, v1, v1, v3);
    //qcu::mix(v2, v2, v2, v3);
    //qcu::mix(v3, v3, v3, v3);
    //qcu::mix(v4, v4, v4, v3);
    //qcu::mix(v, v, v, v, v4);
    //qcu::mix(v1, v1, v1, v1, v4);
    //qcu::mix(v2, v2, v2, v2, v4);
    //qcu::mix(v3, v3, v3, v3, v4);
    //qcu::mix(v4, v4, v4, v4, v4);
}

template <typename T>
constexpr void compileFunctionsConstexprIT() {
    constexpr T v(T(1.0));
    constexpr qcu::vec1<T> v1(T(1.0));
    constexpr qcu::vec2<T> v2(T(1.0));
    constexpr qcu::vec3<T> v3(T(1.0));
    constexpr qcu::vec4<T> v4(T(1.0));
    constexpr qcu::span1<T> s1(v1, v1);
    constexpr qcu::span2<T> s2(v2, v2);
    constexpr qcu::span3<T> s3(v3, v3);
    constexpr qcu::span4<T> s4(v4, v4);
    
    //qcu::mipmaps(v1);
    //qcu::mipmaps(v2);
    //qcu::mipmaps(v3);
    //qcu::mipmaps(v4);
}

constexpr void compileBoolFunctionsConstexpr() {
    qcu::bvec1 b1;
    qcu::bvec2 b2;
    qcu::bvec3 b3;
    qcu::bvec4 b4;

    //b1 && b1;
    //b2 && b2;
    //b3 && b3;
    //b4 && b4;

    //b1 || b1;
    //b2 || b2;
    //b3 || b3;
    //b4 || b4;

    //!b1;
    //!b2;
    //!b3;
    //!b4;

    //qcu::conjunction(b1);
    //qcu::conjunction(b2);
    //qcu::conjunction(b3);
    //qcu::conjunction(b4);

    //qcu::disjunction(b1);
    //qcu::disjunction(b2);
    //qcu::disjunction(b3);
    //qcu::disjunction(b4);
}

constexpr bool compileFunctionsConstexpr() {
    compileFunctionsConstexprT<      float>();
    compileFunctionsConstexprT<     double>();
    compileFunctionsConstexprT<long double>();
    compileBoolFunctionsConstexpr();

    return true;
}

template <typename T, int t_n>
void testPropertiesTN() {
    static_assert(std::is_standard_layout_v<qcu::vec<T, t_n>>);
    static_assert(sizeof(qcu::vec<T, t_n>) == t_n * sizeof(T));
    static_assert(sizeof(qcu::vec<T, t_n>[4]) == 4 * t_n * sizeof(T));
    static_assert(alignof(qcu::vec<T, t_n>) == alignof(T));
    static_assert(alignof(qcu::vec<T, t_n>[4]) == alignof(T));
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

template <typename T1, typename T2, int t_n>
void castCastsTTN() {
    static_cast<qcu::vec<T2, t_n>>(qcu::vec1<T1>());
    static_cast<qcu::vec<T2, t_n>>(qcu::vec2<T1>());
    static_cast<qcu::vec<T2, t_n>>(qcu::vec3<T1>());
    static_cast<qcu::vec<T2, t_n>>(qcu::vec4<T1>());

    static_cast<qcu::span<T2, t_n>>(qcu::span1<T1>());
    static_cast<qcu::span<T2, t_n>>(qcu::span2<T1>());
    static_cast<qcu::span<T2, t_n>>(qcu::span3<T1>());
    static_cast<qcu::span<T2, t_n>>(qcu::span4<T1>());
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
    qcu::vec1<int> v1;
    qcu::vec2<int> v2;
    qcu::vec3<int> v3;
    qcu::vec4<int> v4;
    qcu::span1<int> s1;
    qcu::span2<int> s2;
    qcu::span3<int> s3;
    qcu::span4<int> s4;

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
    constexpr qcu::vec1<T> ax1(qcu::xAxis1<T>);
    constexpr qcu::vec2<T> ax2(qcu::xAxis2<T>);
    constexpr qcu::vec3<T> ax3(qcu::xAxis3<T>);
    constexpr qcu::vec4<T> ax4(qcu::xAxis4<T>);
    constexpr qcu::vec2<T> ay2(qcu::yAxis2<T>);
    constexpr qcu::vec3<T> ay3(qcu::yAxis3<T>);
    constexpr qcu::vec4<T> ay4(qcu::yAxis4<T>);
    constexpr qcu::vec3<T> az3(qcu::zAxis3<T>);
    constexpr qcu::vec4<T> az4(qcu::zAxis4<T>);
    constexpr qcu::vec4<T> aw4(qcu::wAxis4<T>);
}

template <typename T>
constexpr void compileConstantsFT() {
    constexpr qcu::vec1<T> nv1(qcu::nanvec<T, 1>);
    constexpr qcu::vec2<T> nv2(qcu::nanvec<T, 2>);
    constexpr qcu::vec3<T> nv3(qcu::nanvec<T, 3>);
    constexpr qcu::vec4<T> nv4(qcu::nanvec<T, 4>);

    constexpr qcu::span1<T> ns1(qcu::nanspan<T, 1>);
    constexpr qcu::span2<T> ns2(qcu::nanspan<T, 2>);
    constexpr qcu::span3<T> ns3(qcu::nanspan<T, 3>);
    constexpr qcu::span4<T> ns4(qcu::nanspan<T, 4>);

    constexpr qcu::bound1<T> nb1(qcu::nanbound<T, 1>);
    constexpr qcu::bound2<T> nb2(qcu::nanbound<T, 2>);
    constexpr qcu::bound3<T> nb3(qcu::nanbound<T, 3>);
    constexpr qcu::bound4<T> nb4(qcu::nanbound<T, 4>);

    constexpr qcu::vec1<T> iv1(qcu::infvec<T, 1>);
    constexpr qcu::vec2<T> iv2(qcu::infvec<T, 2>);
    constexpr qcu::vec3<T> iv3(qcu::infvec<T, 3>);
    constexpr qcu::vec4<T> iv4(qcu::infvec<T, 4>);

    constexpr qcu::span1<T> is1(qcu::infspan<T, 1>);
    constexpr qcu::span2<T> is2(qcu::infspan<T, 2>);
    constexpr qcu::span3<T> is3(qcu::infspan<T, 3>);
    constexpr qcu::span4<T> is4(qcu::infspan<T, 4>);

    constexpr qcu::span1<T> nulls1(qcu::nullspan<T, 1>);
    constexpr qcu::span2<T> nulls2(qcu::nullspan<T, 2>);
    constexpr qcu::span3<T> nulls3(qcu::nullspan<T, 3>);
    constexpr qcu::span4<T> nulls4(qcu::nullspan<T, 4>);
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