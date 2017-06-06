#include "QMUTest.hpp"

#include "QMU/Vector.hpp"



using namespace qmu;



namespace {



template <typename T>
void testTCompilation() {
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
    // Span1

    // constructors
    span<T, 1> s1_1;
    span<T, 1> s1_2(s1);
    span<T, 1> s1_3(std::move(s1));
    span<T, 1> s1_7(v1, v1);

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

    // asignment operators
    s4 = s4;
    s4 = std::move(s4);

    // other
    s4.toString();
}

template <typename T>
void testTFunctionCompilation() {
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
void testTNProperties() {
    static_assert(std::is_standard_layout<vec<T, t_n>>::value, "");
    static_assert(sizeof(vec<T, t_n>) == t_n * sizeof(T), "");
}

template <typename T>
void testTProperties() {
    testTNProperties<T, 1>();
    testTNProperties<T, 2>();
    testTNProperties<T, 3>();
    testTNProperties<T, 4>();
}

void testCompilation() {
    testTCompilation<    float>();
    testTCompilation<   double>();
    testTCompilation<     char>();
    testTCompilation<    short>();
    testTCompilation<      int>();
    testTCompilation<     long>();
    testTCompilation<long long>();

    testTFunctionCompilation< float>();
    testTFunctionCompilation<double>();

    testTProperties<    float>();
    testTProperties<   double>();
    testTProperties<     char>();
    testTProperties<    short>();
    testTProperties<      int>();
    testTProperties<     long>();
    testTProperties<long long>();
}

template <typename T1, typename T2, nat t_n>
void castTTNCasts() {
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
void testTTCasts() {
    castTTNCasts<T1, T2, 1>();
    castTTNCasts<T1, T2, 2>();
    castTTNCasts<T1, T2, 3>();
    castTTNCasts<T1, T2, 4>();
}

template <typename T>
void testTCasts() {
    testTTCasts<T,     float>();
    testTTCasts<T,    double>();
    testTTCasts<T,      char>();
    testTTCasts<T,     short>();
    testTTCasts<T,       int>();
    testTTCasts<T,      long>();
    testTTCasts<T, long long>();
}

void testCasts() {
    testTCasts<    float>();
    testTCasts<   double>();
    testTCasts<     char>();
    testTCasts<    short>();
    testTCasts<      int>();
    testTCasts<     long>();
    testTCasts<long long>();
}

void testMembers() {
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

void testAxes() {
    fvec3 px(posX<float>);
    fvec3 nx(posX<float>);
    fvec3 py(posY<float>);
    fvec3 ny(posY<float>);
    fvec3 pz(posZ<float>);
    fvec3 nz(negZ<float>);
}



}



void testVector() {
    testCompilation();
    testCasts();
    testMembers();
    testAxes();
}