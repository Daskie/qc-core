#include "QCoreTest.hpp"

#include <sstream>

#include "QCore/VectorFunc.hpp"

namespace {

template <typename T>
void compileClassesT() {
    T v{};
    qc::vec2<T> v2;
    qc::vec3<T> v3;
    qc::vec4<T> v4;
    qc::span1<T> s1;
    qc::span2<T> s2;
    qc::span3<T> s3;
    qc::span4<T> s4;

    //--------------------------------------------------------------------------
    // Vec2

    // constructors
    qc::vec2<T> v2_01;
    qc::vec2<T> v2_02(v2);
    qc::vec2<T> v2_03(std::move(v2));
    qc::vec2<T> v2_04(v);
    qc::vec2<T> v2_06(v3);
    qc::vec2<T> v2_07(v4);
    qc::vec2<T> v2_08(v, v);

    // assignment
    v2 = v2;
    v2 = std::move(v2);
    v2 = v;
    v2 = v3;
    v2 = v4;

    // access
    v2[0];

    v2.at<0>();
    v2.at<1>();

    //--------------------------------------------------------------------------
    // Vec3

    // constructors
    qc::vec3<T> v3_01;
    qc::vec3<T> v3_02(v3);
    qc::vec3<T> v3_03(std::move(v3));
    qc::vec3<T> v3_04(v);
    qc::vec3<T> v3_06(v2);
    qc::vec3<T> v3_07(v4);
    qc::vec3<T> v3_08(v, v, v);
    qc::vec3<T> v3_16(v2, v);
    qc::vec3<T> v3_18(v, v2);

    // assignment
    v3 = v3;
    v3 = std::move(v3);
    v3 = v;
    v3 = v2;
    v3 = v4;

    // access
    v3[0];

    v3.at<0>();
    v3.at<1>();
    v3.at<2>();

    v3.xy(); v3.rg(); v3.st();
    v3.yz(); v3.gb(); v3.tp();

    //--------------------------------------------------------------------------
    // Vec4

    // constructors
    qc::vec4<T> v4_01;
    qc::vec4<T> v4_02(v4);
    qc::vec4<T> v4_03(std::move(v4));
    qc::vec4<T> v4_04(v);
    qc::vec4<T> v4_06(v2);
    qc::vec4<T> v4_07(v3);
    qc::vec4<T> v4_08(v, v, v, v);
    qc::vec4<T> v4_23(v2, v, v);
    qc::vec4<T> v4_27(v, v2, v);
    qc::vec4<T> v4_31(v, v, v2);
    qc::vec4<T> v4_35(v2, v2);
    qc::vec4<T> v4_36(v3, v);
    qc::vec4<T> v4_38(v, v3);

    // assignment
    v4 = v4;
    v4 = std::move(v4);
    v4 = v;
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

    //--------------------------------------------------------------------------
    // Span1

    // constructors
    qc::span<T, 1> s1_1;
    qc::span<T, 1> s1_2(s1);
    qc::span<T, 1> s1_3(std::move(s1));
    qc::span<T, 1> s1_4(v, v);

    // asignment operators
    s1 = s1;
    s1 = std::move(s1);

    // other
    s1.size();

    //--------------------------------------------------------------------------
    // Span2

    // constructors
    qc::span<T, 2> s2_1;
    qc::span<T, 2> s2_2(s2);
    qc::span<T, 2> s2_3(std::move(s2));
    qc::span<T, 2> s2_4(v2, v2);
    qc::span<T, 2> s2_5(v, v);
    qc::span<T, 2> s2_6(s1, s1);

    // asignment operators
    s2 = s2;
    s2 = std::move(s2);

    // other
    s2.x();
    s2.y();

    s2.size();

    //--------------------------------------------------------------------------
    // Span3

    // constructors
    qc::span<T, 3> s3_1;
    qc::span<T, 3> s3_2(s3);
    qc::span<T, 3> s3_3(std::move(s3));
    qc::span<T, 3> s3_4(v3, v3);
    qc::span<T, 3> s3_5(v, v);
    qc::span<T, 3> s3_6(s1, s1, s1);
    qc::span<T, 3> s3_7(s2, s1);
    qc::span<T, 3> s3_8(s1, s2);

    // asignment operators
    s3 = s3;
    s3 = std::move(s3);

    // other
    s3.x();
    s3.y();
    s3.z();
    s3.xy();
    s3.yz();

    s3.size();

    //--------------------------------------------------------------------------
    // Span4

    // constructors
    qc::span<T, 4> s4_1;
    qc::span<T, 4> s4_2(s4);
    qc::span<T, 4> s4_3(std::move(s4));
    qc::span<T, 4> s4_4(v4, v4);
    qc::span<T, 4> s4_5(v, v);
    qc::span<T, 4> s4_6(s1, s1, s1, s1);
    qc::span<T, 4> s4_7(s2, s1, s1);
    qc::span<T, 4> s4_8(s1, s2, s1);
    qc::span<T, 4> s4_9(s1, s1, s2);
    qc::span<T, 4> s4_10(s2, s2);
    qc::span<T, 4> s4_11(s3, s1);
    qc::span<T, 4> s4_12(s1, s3);

    // asignment operators
    s4 = s4;
    s4 = std::move(s4);

    // other
    s4.x();
    s4.y();
    s4.z();
    s4.w();
    s4.xy();
    s4.yz();
    s4.xyz();
    s4.yzw();

    s4.size();
}

void compileClasses() {
    compileClassesT<qc::f32>();
    compileClassesT<qc::f64>();
    compileClassesT<qc::s08>();
    compileClassesT<qc::s16>();
    compileClassesT<qc::s32>();
    compileClassesT<qc::s64>();
    compileClassesT<qc::u08>();
    compileClassesT<qc::u16>();
    compileClassesT<qc::u32>();
    compileClassesT<qc::u64>();
}

template <typename T>
constexpr void compileClassesConstexprT() {
    constexpr T v{};
    constexpr qc::vec2<T> v2;
    constexpr qc::vec3<T> v3;
    constexpr qc::vec4<T> v4;
    constexpr qc::span1<T> s1;
    constexpr qc::span2<T> s2;
    constexpr qc::span3<T> s3;
    constexpr qc::span4<T> s4;

    //--------------------------------------------------------------------------
    // Vec2

    // constructors
    constexpr qc::vec2<T> v2_01;
    constexpr qc::vec2<T> v2_02(v2);
    constexpr qc::vec2<T> v2_03(std::move(v2));
    constexpr qc::vec2<T> v2_04(v);
    constexpr qc::vec2<T> v2_06(v3);
    constexpr qc::vec2<T> v2_07(v4);
    constexpr qc::vec2<T> v2_08(v, v);

    // access
    v2.at<0>();
    v2.at<1>();

    //--------------------------------------------------------------------------
    // Vec3

    // constructors
    constexpr qc::vec3<T> v3_01;
    constexpr qc::vec3<T> v3_02(v3);
    constexpr qc::vec3<T> v3_03(std::move(v3));
    constexpr qc::vec3<T> v3_04(v);
    constexpr qc::vec3<T> v3_06(v2);
    constexpr qc::vec3<T> v3_07(v4);
    constexpr qc::vec3<T> v3_08(v, v, v);
    constexpr qc::vec3<T> v3_16(v2, v);
    //constexpr qc::vec3<T> v3_18(v, v2);

    // access
    v3.at<0>();
    v3.at<1>();
    v3.at<2>();

    //v3.xy(); v3.rg(); v3.st();
    //v3.yz(); v3.gb(); v3.tp();

    //--------------------------------------------------------------------------
    // Vec4

    // constructors
    constexpr qc::vec4<T> v4_01;
    constexpr qc::vec4<T> v4_02(v4);
    constexpr qc::vec4<T> v4_03(std::move(v4));
    constexpr qc::vec4<T> v4_04(v);
    constexpr qc::vec4<T> v4_06(v2);
    constexpr qc::vec4<T> v4_07(v3);
    constexpr qc::vec4<T> v4_08(v, v, v, v);
    constexpr qc::vec4<T> v4_23(v2, v, v);
    //constexpr qc::vec4<T> v4_27(v, v2, v);
    //constexpr qc::vec4<T> v4_31(v, v, v2);
    constexpr qc::vec4<T> v4_35(v2, v2);
    constexpr qc::vec4<T> v4_36(v3, v);
    //constexpr qc::vec4<T> v4_38(v, v3);

    // access
    v4.at<0>();
    v4.at<1>();
    v4.at<2>();
    v4.at<3>();

    //v4.xy(); v4.rg(); v4.st();
    //v4.yz(); v4.gb(); v4.tp();
    //v4.zw(); v4.ba(); v4.pq();
    //v4.xyz(); v4.rgb(); v4.stp();
    //v4.yzw(); v4.gba(); v4.tpq();

    //--------------------------------------------------------------------------
    // Span1

    // constructors
    constexpr qc::span<T, 1> s1_1;
    constexpr qc::span<T, 1> s1_2(s1);
    constexpr qc::span<T, 1> s1_3(std::move(s1));
    constexpr qc::span<T, 1> s1_4(v, v);

    // other
    //s1.size();

    //--------------------------------------------------------------------------
    // Span2

    // constructors
    constexpr qc::span<T, 2> s2_1;
    constexpr qc::span<T, 2> s2_2(s2);
    constexpr qc::span<T, 2> s2_3(std::move(s2));
    constexpr qc::span<T, 2> s2_4(v2, v2);
    constexpr qc::span<T, 2> s2_5(v, v);
    constexpr qc::span<T, 2> s2_6(s1, s1);

    // other
    s2.x();
    s2.y();

    //s2.size();

    //--------------------------------------------------------------------------
    // Span3

    // constructors
    constexpr qc::span<T, 3> s3_1;
    constexpr qc::span<T, 3> s3_2(s3);
    constexpr qc::span<T, 3> s3_3(std::move(s3));
    constexpr qc::span<T, 3> s3_4(v3, v3);
    constexpr qc::span<T, 3> s3_5(v, v);
    constexpr qc::span<T, 3> s3_6(s1, s1, s1);
    //constexpr qc::span<T, 3> s3_7(s2, s1);
    //constexpr qc::span<T, 3> s3_8(s1, s2);

    // other
    s3.x();
    s3.y();
    s3.z();
    //s3.xy();
    //s3.yz();

    //s3.size();

    //--------------------------------------------------------------------------
    // Span4

    // constructors
    constexpr qc::span<T, 4> s4_1;
    constexpr qc::span<T, 4> s4_2(s4);
    constexpr qc::span<T, 4> s4_3(std::move(s4));
    constexpr qc::span<T, 4> s4_4(v4, v4);
    constexpr qc::span<T, 4> s4_5(v, v);
    constexpr qc::span<T, 4> s4_6(s1, s1, s1, s1);
    //constexpr qc::span<T, 4> s4_7(s2, s1, s1);
    //constexpr qc::span<T, 4> s4_8(s1, s2, s1);
    //constexpr qc::span<T, 4> s4_9(s1, s1, s2);
    //constexpr qc::span<T, 4> s4_10(s2, s2);
    //constexpr qc::span<T, 4> s4_11(s3, s1);
    //constexpr qc::span<T, 4> s4_12(s1, s3);

    // other
    s4.x();
    s4.y();
    s4.z();
    s4.w();
    //s4.xy();
    //s4.yz();
    //s4.xyz();
    //s4.yzw();


    //s4.size();
}

constexpr bool compileClassesConstexpr() {
    compileClassesConstexprT<qc::f32>();
    compileClassesConstexprT<qc::f64>();
    compileClassesConstexprT<qc::s08>();
    compileClassesConstexprT<qc::s16>();
    compileClassesConstexprT<qc::s32>();
    compileClassesConstexprT<qc::s64>();
    compileClassesConstexprT<qc::u08>();
    compileClassesConstexprT<qc::u16>();
    compileClassesConstexprT<qc::u32>();
    compileClassesConstexprT<qc::u64>();

    return true;
}

template <typename T1, typename T2>
void compileFunctionsTT() {
    T1 v; v;
    qc::vec2<T1> v2; v2;
    qc::vec3<T1> v3; v3;
    qc::vec4<T1> v4; v4;
    qc::span1<T1> s1; s1;
    qc::span2<T1> s2; s2;
    qc::span3<T1> s3; s3;
    qc::span4<T1> s4; s4;
    
    qc::transnorm<T2>(v2);
    qc::transnorm<T2>(v3);
    qc::transnorm<T2>(v4);
}

template <typename T>
void compileFunctionsT() {
    compileFunctionsTT<T, qc::f32>();
    compileFunctionsTT<T, qc::f64>();
    compileFunctionsTT<T, qc::s08>();
    compileFunctionsTT<T, qc::s16>();
    compileFunctionsTT<T, qc::s32>();
    compileFunctionsTT<T, qc::s64>();
    compileFunctionsTT<T, qc::u08>();
    compileFunctionsTT<T, qc::u16>();
    compileFunctionsTT<T, qc::u32>();
    compileFunctionsTT<T, qc::u64>();

    T v{};
    qc::vec2<T> v2;
    qc::vec3<T> v3;
    qc::vec4<T> v4;
    qc::span1<T> s1;
    qc::span2<T> s2;
    qc::span3<T> s3;
    qc::span4<T> s4;
    std::stringstream os;

    // arithmetic

    v2 += v2;
    v3 += v3;
    v4 += v4;
    v2 += v;
    v3 += v;
    v4 += v;

    v2 -= v2;
    v3 -= v3;
    v4 -= v4;
    v2 -= v;
    v3 -= v;
    v4 -= v;

    v2 *= v2;
    v3 *= v3;
    v4 *= v4;
    v2 *= v;
    v3 *= v;
    v4 *= v;

    v2 /= qc::vec2<T>(T(1));
    v3 /= qc::vec3<T>(T(1));
    v4 /= qc::vec4<T>(T(1));
    v2 /= T(1);
    v3 /= T(1);
    v4 /= T(1);

    v2 %= qc::vec2<T>(T(1));
    v3 %= qc::vec3<T>(T(1));
    v4 %= qc::vec4<T>(T(1));
    v2 %= T(1);
    v3 %= T(1);
    v4 %= T(1);

    ++v2;
    ++v3;
    ++v4;

    v2++;
    v3++;
    v4++;

    --v2;
    --v3;
    --v4;

    v2--;
    v3--;
    v4--;

    +v2;
    +v3;
    +v4;

    -v2;
    -v3;
    -v4;

    v2 + v2;
    v3 + v3;
    v4 + v4;
    v2 + v;
    v3 + v;
    v4 + v;
    v + v2;
    v + v3;
    v + v4;
    s1 + v;
    s2 + v2;
    s3 + v3;
    s4 + v4;
    v + s1;
    v2 + s2;
    v3 + s3;
    v4 + s4;

    v2 - v2;
    v3 - v3;
    v4 - v4;
    v2 - v;
    v3 - v;
    v4 - v;
    v - v2;
    v - v3;
    v - v4;
    s1 - v;
    s2 - v2;
    s3 - v3;
    s4 - v4;
    v - s1;
    v2 - s2;
    v3 - s3;
    v4 - s4;

    v2 * v2;
    v3 * v3;
    v4 * v4;
    v2 * v;
    v3 * v;
    v4 * v;
    v * v2;
    v * v3;
    v * v4;

    v2 / qc::vec2<T>(T(1));
    v3 / qc::vec3<T>(T(1));
    v4 / qc::vec4<T>(T(1));
    v2 / T(v);
    v3 / T(v);
    v4 / T(v);
    v / qc::vec2<T>(T(1));
    v / qc::vec3<T>(T(1));
    v / qc::vec4<T>(T(1));

    v2 % qc::vec2<T>(T(1));
    v3 % qc::vec3<T>(T(1));
    v4 % qc::vec4<T>(T(1));
    v2 % T(v);
    v3 % T(v);
    v4 % T(v);
    v % qc::vec2<T>(T(1));
    v % qc::vec3<T>(T(1));
    v % qc::vec4<T>(T(1));


    // comparison

    v2 == v2;
    v3 == v3;
    v4 == v4;
    v2 == v;
    v3 == v;
    v4 == v;
    v == v2;
    v == v3;
    v == v4;
    s1 == s1;
    s2 == s2;
    s3 == s3;
    s4 == s4;

    v2 != v2;
    v3 != v3;
    v4 != v4;
    v2 != v;
    v3 != v;
    v4 != v;
    v != v2;
    v != v3;
    v != v4;
    s1 != s1;
    s2 != s2;
    s3 != s3;
    s4 != s4;

    v2 < v2;
    v3 < v3;
    v4 < v4;
    v2 < v;
    v3 < v;
    v4 < v;
    v < v2;
    v < v3;
    v < v4;

    v2 > v2;
    v3 > v3;
    v4 > v4;
    v2 > v;
    v3 > v;
    v4 > v;
    v > v2;
    v > v3;
    v > v4;

    v2 <= v2;
    v3 <= v3;
    v4 <= v4;
    v2 <= v;
    v3 <= v;
    v4 <= v;
    v <= v2;
    v <= v3;
    v <= v4;

    v2 >= v2;
    v3 >= v3;
    v4 >= v4;
    v2 >= v;
    v3 >= v;
    v4 >= v;
    v >= v2;
    v >= v3;
    v >= v4;

    // condensation

    qc::sum(v2);
    qc::sum(v3);
    qc::sum(v4);

    qc::product(v2);
    qc::product(v3);
    qc::product(v4);

    // other

    os << v2;
    os << v3;
    os << v4;
    os << s1;
    os << s2;
    os << s3;
    os << s4;

    // uncategorized

    qc::magnitude2(v2);
    qc::magnitude2(v3);
    qc::magnitude2(v4);

    qc::dot(v2, v2);
    qc::dot(v3, v3);
    qc::dot(v4, v4);

    qc::cross(v2, v2);
    qc::cross(v3, v3);

    qc::parallel(v2, v2);
    qc::parallel(v3, v3);
    qc::parallel(v4, v4);

    qc::orthogonal(v2, v2);
    qc::orthogonal(v3, v3);
    qc::orthogonal(v4, v4);

    if constexpr (!std::is_unsigned_v<T>) {
        qc::ortho(v2);
        qc::ortho(v3);
    }

    qc::min(v2);
    qc::min(v3);
    qc::min(v4);

    qc::min(v2, v2);
    qc::min(v3, v3);
    qc::min(v4, v4);

    qc::min(v2, v2, v2, v2, v2);
    qc::min(v3, v3, v3, v3, v3);
    qc::min(v4, v4, v4, v4, v4);

    qc::min(v2, v);
    qc::min(v3, v);
    qc::min(v4, v);
    qc::min(v, v2);
    qc::min(v, v3);
    qc::min(v, v4);
    
    qc::max(v2);
    qc::max(v3);
    qc::max(v4);

    qc::max(v2, v2);
    qc::max(v3, v3);
    qc::max(v4, v4);

    qc::max(v2, v2, v2, v2, v2);
    qc::max(v3, v3, v3, v3, v3);
    qc::max(v4, v4, v4, v4, v4);

    qc::max(v2, v);
    qc::max(v3, v);
    qc::max(v4, v);
    qc::max(v, v2);
    qc::max(v, v3);
    qc::max(v, v4);

    qc::minify(v2, v2);
    qc::minify(v3, v3);
    qc::minify(v4, v4);
    qc::minify(v2, v);
    qc::minify(v3, v);
    qc::minify(v4, v);

    qc::maxify(v2, v2);
    qc::maxify(v3, v3);
    qc::maxify(v4, v4);
    qc::maxify(v2, v);
    qc::maxify(v3, v);
    qc::maxify(v4, v);

    qc::minmax(v2);
    qc::minmax(v3);
    qc::minmax(v4);

    qc::median(v3);

    qc::sort(v2);
    qc::sort(v3);
    qc::sort(v4);

    qc::clamp(v2, v, v);
    qc::clamp(v3, v, v);
    qc::clamp(v4, v, v);

    qc::clamp(v2, v2, v2);
    qc::clamp(v3, v3, v3);
    qc::clamp(v4, v4, v4);

    qc::clamp(v, s1);
    qc::clamp(v2, s2);
    qc::clamp(v3, s3);
    qc::clamp(v4, s4);

    qc::abs(v2);
    qc::abs(v3);
    qc::abs(v4);

    qc::zero(v2);
    qc::zero(v3);
    qc::zero(v4);

    qc::equal(v2, v2);
    qc::equal(v3, v3);
    qc::equal(v4, v4);

    qc::equal(v2);
    qc::equal(v3);
    qc::equal(v4);

    qc::round(v2);
    qc::round(v3);
    qc::round(v4);

    qc::floor(v2);
    qc::floor(v3);
    qc::floor(v4);

    qc::ceil(v2);
    qc::ceil(v3);
    qc::ceil(v4);

    qc::composite(v2, v2);
    qc::composite(v3, v3);
    qc::composite(v4, v4);

    qc::intersect(s1, s1);
    qc::intersect(s2, s2);
    qc::intersect(s3, s3);
    qc::intersect(s4, s4);

    qc::join(s1, s1);
    qc::join(s2, s2);
    qc::join(s3, s3);
    qc::join(s4, s4);
}

template <typename T>
void compileFunctionsFT() {
    T v{1};
    qc::vec2<T> v2;
    qc::vec3<T> v3;
    qc::vec4<T> v4;
    qc::span1<T> s1;
    qc::span2<T> s2;
    qc::span3<T> s3;
    qc::span4<T> s4;

    qc::equal_e(v2, v2);
    qc::equal_e(v3, v3);
    qc::equal_e(v4, v4);
    qc::equal_e(v2, v2, v2);
    qc::equal_e(v3, v3, v3);
    qc::equal_e(v4, v4, v4);

    qc::pow(v2, v);
    qc::pow(v3, v);
    qc::pow(v4, v);

    qc::pow(v2, v2);
    qc::pow(v3, v3);
    qc::pow(v4, v4);

    qc::exp(v2);
    qc::exp(v3);
    qc::exp(v4);

    qc::magnitude(v2);
    qc::magnitude(v3);
    qc::magnitude(v4);

    qc::normalize(v2);
    qc::normalize(v3);
    qc::normalize(v4);

    qc::normalizeAssign(v2);
    qc::normalizeAssign(v3);
    qc::normalizeAssign(v4);

    qc::orthogonalize(v2, v2);
    qc::orthogonalize(v3, v3);
    qc::orthogonalize(v4, v4);
    qc::orthogonalize(v3, v3, v3);
    qc::orthogonalize_n(v3, v3, v3);

    qc::reflect(v2, v2);
    qc::reflect(v3, v3);

    qc::angle(v2, v2);
    qc::angle_n(v2, v2);
    qc::angle(v3, v3);
    qc::angle_n(v3, v3);
    qc::angle(v4, v4);
    qc::angle_n(v4, v4);

    qc::mix(v2, v2, v);
    qc::mix(v3, v3, v);
    qc::mix(v4, v4, v);
    
    qc::mix(v, v, v2);
    qc::mix(v2, v2, v2);
    qc::mix(v3, v3, v2);
    qc::mix(v4, v4, v2);
    qc::mix(v, v, v, v3);
    qc::mix(v2, v2, v2, v3);
    qc::mix(v3, v3, v3, v3);
    qc::mix(v4, v4, v4, v3);
    qc::mix(v, v, v, v, v4);
    qc::mix(v2, v2, v2, v2, v4);
    qc::mix(v3, v3, v3, v3, v4);
    qc::mix(v4, v4, v4, v4, v4);
}

template <typename T>
void compileFunctionsIT() {
    T v{}; v;
    qc::vec2<T> v2; v2;
    qc::vec3<T> v3; v3;
    qc::vec4<T> v4; v4;
    qc::span1<T> s1; s1;
    qc::span2<T> s2; s2;
    qc::span3<T> s3; s3;
    qc::span4<T> s4; s4;
    
    qc::mipmaps(v2);
    qc::mipmaps(v3);
    qc::mipmaps(v4);
}

void compileFunctionsBT() {
    qc::bvec2 b2;
    qc::bvec3 b3;
    qc::bvec4 b4;

    b2 && b2;
    b3 && b3;
    b4 && b4;

    b2 || b2;
    b3 || b3;
    b4 || b4;

    !b2;
    !b3;
    !b4;
    
    qc::all(b2);
    qc::all(b3);
    qc::all(b4);

    qc::any(b2);
    qc::any(b3);
    qc::any(b4);
}

void compileFunctions() {
    compileFunctionsT<qc::f32>();
    compileFunctionsT<qc::f64>();
    compileFunctionsT<qc::s08>();
    compileFunctionsT<qc::s16>();
    compileFunctionsT<qc::s32>();
    compileFunctionsT<qc::s64>();
    compileFunctionsT<qc::u08>();
    compileFunctionsT<qc::u16>();
    compileFunctionsT<qc::u32>();
    compileFunctionsT<qc::u64>();
    
    compileFunctionsFT<qc::f32>();
    compileFunctionsFT<qc::f64>();

    compileFunctionsIT<qc::s08>();
    compileFunctionsIT<qc::s16>();
    compileFunctionsIT<qc::s32>();
    compileFunctionsIT<qc::s64>();
    compileFunctionsIT<qc::u08>();
    compileFunctionsIT<qc::u16>();
    compileFunctionsIT<qc::u32>();
    compileFunctionsIT<qc::u64>();

    compileFunctionsBT();
}

template <typename T1, typename T2>
constexpr void compileFunctionsConstexprTT() {
    constexpr T1 v(T1(1.0));
    constexpr qc::vec2<T1> v2(T1(1.0));
    constexpr qc::vec3<T1> v3(T1(1.0));
    constexpr qc::vec4<T1> v4(T1(1.0));
    constexpr qc::span1<T1> s1(v, v);
    constexpr qc::span2<T1> s2(v2, v2);
    constexpr qc::span3<T1> s3(v3, v3);
    constexpr qc::span4<T1> s4(v4, v4);


}

template <typename T>
constexpr void compileFunctionsConstexprT() {
    compileFunctionsConstexprTT<T, qc::f32>();
    compileFunctionsConstexprTT<T, qc::f64>();
    compileFunctionsConstexprTT<T, qc::s08>();
    compileFunctionsConstexprTT<T, qc::s16>();
    compileFunctionsConstexprTT<T, qc::s32>();
    compileFunctionsConstexprTT<T, qc::s64>();
    compileFunctionsConstexprTT<T, qc::u08>();
    compileFunctionsConstexprTT<T, qc::u16>();
    compileFunctionsConstexprTT<T, qc::u32>();
    compileFunctionsConstexprTT<T, qc::u64>();

    constexpr T v{1.0};
    constexpr qc::vec2<T> v2(T(1.0));
    constexpr qc::vec3<T> v3(T(1.0));
    constexpr qc::vec4<T> v4(T(1.0));
    constexpr qc::span1<T> s1(v, v);
    constexpr qc::span2<T> s2(v2, v2);
    constexpr qc::span3<T> s3(v3, v3);
    constexpr qc::span4<T> s4(v4, v4);

    // arithmetic

    //+v2;
    //+v3;
    //+v4;

    //-v2;
    //-v3;
    //-v4;

    //v2 + v2;
    //v3 + v3;
    //v4 + v4;
    //v2 + v;
    //v3 + v;
    //v4 + v;
    //v + v2;
    //v + v3;
    //v + v4;
    //s1 + v;
    //s2 + v2;
    //s3 + v3;
    //s4 + v4;
    //v + s1;
    //v2 + s2;
    //v3 + s3;
    //v4 + s4;

    //v2 - v2;
    //v3 - v3;
    //v4 - v4;
    //v2 - v;
    //v3 - v;
    //v4 - v;
    //v - v2;
    //v - v3;
    //v - v4;
    //s1 - v;
    //s2 - v2;
    //s3 - v3;
    //s4 - v4;
    //v - s1;
    //v2 - s2;
    //v3 - s3;
    //v4 - s4;

    //v2 * v2;
    //v3 * v3;
    //v4 * v4;
    //v2 * v;
    //v3 * v;
    //v4 * v;
    //v * v2;
    //v * v3;
    //v * v4;

    //v2 / qc::vec2<T>(1);
    //v3 / qc::vec3<T>(1);
    //v4 / qc::vec4<T>(1);
    //v2 / T(v);
    //v3 / T(v);
    //v4 / T(v);
    //v / qc::vec2<T>(1);
    //v / qc::vec3<T>(1);
    //v / qc::vec4<T>(1);

    //v2 % qc::vec2<T>(1);
    //v3 % qc::vec3<T>(1);
    //v4 % qc::vec4<T>(1);
    //v2 % T(v);
    //v3 % T(v);
    //v4 % T(v);
    //v % qc::vec2<T>(1);
    //v % qc::vec3<T>(1);
    //v % qc::vec4<T>(1);


    // comparison

    //v2 == v2;
    //v3 == v3;
    //v4 == v4;
    //v2 == v;
    //v3 == v;
    //v4 == v;
    //v == v2;
    //v == v3;
    //v == v4;
    //s2 == s2;
    //s3 == s3;
    //s4 == s4;

    //v2 != v2;
    //v3 != v3;
    //v4 != v4;
    //v2 != v;
    //v3 != v;
    //v4 != v;
    //v != v2;
    //v != v3;
    //v != v4;
    //s1 != s1;
    //s2 != s2;
    //s3 != s3;
    //s4 != s4;

    //v2 < v2;
    //v3 < v3;
    //v4 < v4;
    //v2 < v;
    //v3 < v;
    //v4 < v;
    //v < v2;
    //v < v3;
    //v < v4;

    //v2 > v2;
    //v3 > v3;
    //v4 > v4;
    //v2 > v;
    //v3 > v;
    //v4 > v;
    //v > v2;
    //v > v3;
    //v > v4;

    //v2 <= v2;
    //v3 <= v3;
    //v4 <= v4;
    //v2 <= v;
    //v3 <= v;
    //v4 <= v;
    //v <= v2;
    //v <= v3;
    //v <= v4;

    //v2 >= v2;
    //v3 >= v3;
    //v4 >= v4;
    //v2 >= v;
    //v3 >= v;
    //v4 >= v;
    //v >= v2;
    //v >= v3;
    //v >= v4;

    // condensation

    //qc::sum(v2);
    //qc::sum(v3);
    //qc::sum(v4);

    //qc::product(v2);
    //qc::product(v3);
    //qc::product(v4);

    // uncategorized

    //qc::min(v2);
    //qc::min(v3);
    //qc::min(v4);

    //qc::min(v2, v2);
    //qc::min(v3, v3);
    //qc::min(v4, v4);

    //qc::min(v2, v2, v2, v2, v2);
    //qc::min(v3, v3, v3, v3, v3);
    //qc::min(v4, v4, v4, v4, v4);

    //qc::min(v2, v);
    //qc::min(v3, v);
    //qc::min(v4, v);
    //qc::min(v, v2);
    //qc::min(v, v3);
    //qc::min(v, v4);
    
    //qc::max(v2);
    //qc::max(v3);
    //qc::max(v4);

    //qc::max(v2, v2);
    //qc::max(v3, v3);
    //qc::max(v4, v4);

    //qc::max(v2, v2, v2, v2, v2);
    //qc::max(v3, v3, v3, v3, v3);
    //qc::max(v4, v4, v4, v4, v4);

    //qc::max(v2, v);
    //qc::max(v3, v);
    //qc::max(v4, v);
    //qc::max(v, v2);
    //qc::max(v, v3);
    //qc::max(v, v4);

    //qc::minmax(v2);
    //qc::minmax(v3);
    //qc::minmax(v4);

    //qc::clamp(v2, v, v);
    //qc::clamp(v3, v, v);
    //qc::clamp(v4, v, v);

    //qc::clamp(v2, v2, v2);
    //qc::clamp(v3, v3, v3);
    //qc::clamp(v4, v4, v4);

    //qc::clamp(v, s1);
    //qc::clamp(v2, s2);
    //qc::clamp(v3, s3);
    //qc::clamp(v4, s4);

    //qc::abs(v2);
    //qc::abs(v3);
    //qc::abs(v4);

    //qc::zero(v2);
    //qc::zero(v3);
    //qc::zero(v4);

    //qc::equal(v2, v2);
    //qc::equal(v3, v3);
    //qc::equal(v4, v4);

    //qc::equal(v2);
    //qc::equal(v3);
    //qc::equal(v4);

    //qc::round(v2);
    //qc::round(v3);
    //qc::round(v4);

    //qc::floor(v2);
    //qc::floor(v3);
    //qc::floor(v4);

    //qc::ceil(v2);
    //qc::ceil(v3);
    //qc::ceil(v4);

    //qc::composite(v2, v2);
    //qc::composite(v3, v3);
    //qc::composite(v4, v4);

    //qc::intersect(s1, s1);
    //qc::intersect(s2, s2);
    //qc::intersect(s3, s3);
    //qc::intersect(s4, s4);

    //qc::join(s1, s1);
    //qc::join(s2, s2);
    //qc::join(s3, s3);
    //qc::join(s4, s4);
}

template <typename T>
constexpr void compileFunctionsConstexprFT() {
    constexpr T v{1.0};
    constexpr qc::vec2<T> v2(T(1.0));
    constexpr qc::vec3<T> v3(T(1.0));
    constexpr qc::vec4<T> v4(T(1.0));
    constexpr qc::span1<T> s1(v, v);
    constexpr qc::span2<T> s2(v2, v2);
    constexpr qc::span3<T> s3(v3, v3);
    constexpr qc::span4<T> s4(v4, v4);

    //qc::equal_e(v2, v2);
    //qc::equal_e(v3, v3);
    //qc::equal_e(v4, v4);
    //qc::equal_e(v2, v2, v2);
    //qc::equal_e(v3, v3, v3);
    //qc::equal_e(v4, v4. v4);

    //qc::mix(v2, v2, v);
    //qc::mix(v3, v3, v);
    //qc::mix(v4, v4, v);

    //qc::mix(v, v, v2);
    //qc::mix(v2, v2, v2);
    //qc::mix(v3, v3, v2);
    //qc::mix(v4, v4, v2);
    //qc::mix(v, v, v, v3);
    //qc::mix(v2, v2, v2, v3);
    //qc::mix(v3, v3, v3, v3);
    //qc::mix(v4, v4, v4, v3);
    //qc::mix(v, v, v, v, v4);
    //qc::mix(v2, v2, v2, v2, v4);
    //qc::mix(v3, v3, v3, v3, v4);
    //qc::mix(v4, v4, v4, v4, v4);
}

template <typename T>
constexpr void compileFunctionsConstexprIT() {
    constexpr T v{1.0};
    constexpr qc::vec2<T> v2(T(1.0));
    constexpr qc::vec3<T> v3(T(1.0));
    constexpr qc::vec4<T> v4(T(1.0));
    constexpr qc::span1<T> s1(v, v);
    constexpr qc::span2<T> s2(v2, v2);
    constexpr qc::span3<T> s3(v3, v3);
    constexpr qc::span4<T> s4(v4, v4);
    
    //qc::mipmaps(v2);
    //qc::mipmaps(v3);
    //qc::mipmaps(v4);
}

constexpr void compileBoolFunctionsConstexpr() {
    qc::bvec2 b2;
    qc::bvec3 b3;
    qc::bvec4 b4;

    //b2 && b2;
    //b3 && b3;
    //b4 && b4;

    //b2 || b2;
    //b3 || b3;
    //b4 || b4;

    //!b2;
    //!b3;
    //!b4;

    //qc::all(b2);
    //qc::all(b3);
    //qc::all(b4);

    //qc::any(b2);
    //qc::any(b3);
    //qc::any(b4);
}

constexpr bool compileFunctionsConstexpr() {
    compileFunctionsConstexprT<qc::f32>();
    compileFunctionsConstexprT<qc::f64>();
    compileBoolFunctionsConstexpr();

    return true;
}

template <typename T, int t_n>
void testPropertiesTN() {
    static_assert(std::is_standard_layout_v<qc::vec<T, t_n>>);
    static_assert(std::is_trivially_copyable_v<qc::vec<T, t_n>>);
    static_assert(std::is_trivially_copy_constructible_v<qc::vec<T, t_n>>);
    static_assert(std::is_trivially_move_constructible_v<qc::vec<T, t_n>>);
    static_assert(std::is_trivially_copy_assignable_v<qc::vec<T, t_n>>);
    static_assert(std::is_trivially_move_assignable_v<qc::vec<T, t_n>>);
    static_assert(std::is_trivially_destructible_v<qc::vec<T, t_n>>);
    static_assert(sizeof(qc::vec<T, t_n>) == t_n * sizeof(T));
    static_assert(sizeof(qc::vec<T, t_n>[4]) == 4 * t_n * sizeof(T));
    static_assert(alignof(qc::vec<T, t_n>) == alignof(T));
    static_assert(alignof(qc::vec<T, t_n>[4]) == alignof(T));

    static_assert(std::is_standard_layout_v<qc::span<T, t_n>>);
    static_assert(std::is_trivially_copyable_v<qc::span<T, t_n>>);
    static_assert(std::is_trivially_copy_constructible_v<qc::span<T, t_n>>);
    static_assert(std::is_trivially_move_constructible_v<qc::span<T, t_n>>);
    static_assert(std::is_trivially_copy_assignable_v<qc::span<T, t_n>>);
    static_assert(std::is_trivially_move_assignable_v<qc::span<T, t_n>>);
    static_assert(std::is_trivially_destructible_v<qc::span<T, t_n>>);
    static_assert(sizeof(qc::span<T, t_n>) == 2 * t_n * sizeof(T));
    static_assert(sizeof(qc::span<T, t_n>[4]) == 4 * 2 * t_n * sizeof(T));
    static_assert(alignof(qc::span<T, t_n>) == alignof(T));
    static_assert(alignof(qc::span<T, t_n>[4]) == alignof(T));
}

template <typename T>
void testPropertiesT() {
    testPropertiesTN<T, 2>();
    testPropertiesTN<T, 3>();
    testPropertiesTN<T, 4>();
}

void testProperties() {
    testPropertiesT<qc::f32>();
    testPropertiesT<qc::f64>();
    testPropertiesT<qc::s08>();
    testPropertiesT<qc::s16>();
    testPropertiesT<qc::s32>();
    testPropertiesT<qc::s64>();
    testPropertiesT<qc::u08>();
    testPropertiesT<qc::u16>();
    testPropertiesT<qc::u32>();
    testPropertiesT<qc::u64>();
}

template <typename T1, typename T2, int t_n>
constexpr void compileVecCastsTTN() {
    static_cast<qc::vec<T2, t_n>>(T1(0));
    static_cast<qc::vec<T2, t_n>>(qc::vec2<T1>());
    static_cast<qc::vec<T2, t_n>>(qc::vec3<T1>());
    static_cast<qc::vec<T2, t_n>>(qc::vec4<T1>());
}

template <typename T1, typename T2, int t_n>
constexpr void compileSpanCastsTTN() {
    static_cast<qc::span<T2, t_n>>(qc::span1<T1>());
    static_cast<qc::span<T2, t_n>>(qc::span2<T1>());
    static_cast<qc::span<T2, t_n>>(qc::span3<T1>());
    static_cast<qc::span<T2, t_n>>(qc::span4<T1>());
}

template <typename T1, typename T2>
constexpr void compileCastsTT() {
    compileVecCastsTTN<T1, T2, 2>();
    compileVecCastsTTN<T1, T2, 3>();
    compileVecCastsTTN<T1, T2, 4>();
    
    compileSpanCastsTTN<T1, T2, 1>();
    compileSpanCastsTTN<T1, T2, 2>();
    compileSpanCastsTTN<T1, T2, 3>();
    compileSpanCastsTTN<T1, T2, 4>();
}

template <typename T>
constexpr void compileCastsT() {
    compileCastsTT<T, qc::f32>();
    compileCastsTT<T, qc::f64>();
    compileCastsTT<T, qc::s08>();
    compileCastsTT<T, qc::s16>();
    compileCastsTT<T, qc::s32>();
    compileCastsTT<T, qc::s64>();
    compileCastsTT<T, qc::u08>();
    compileCastsTT<T, qc::u16>();
    compileCastsTT<T, qc::u32>();
    compileCastsTT<T, qc::u64>();
}

constexpr bool compileCasts() {
    compileCastsT<qc::f32>();
    compileCastsT<qc::f64>();
    compileCastsT<qc::s08>();
    compileCastsT<qc::s16>();
    compileCastsT<qc::s32>();
    compileCastsT<qc::s64>();
    compileCastsT<qc::u08>();
    compileCastsT<qc::u16>();
    compileCastsT<qc::u32>();
    compileCastsT<qc::u64>();

    return true;
}

void compileMembers() {
    int v{};
    qc::vec2<int> v2;
    qc::vec3<int> v3;
    qc::vec4<int> v4;
    qc::span1<int> s1;
    qc::span2<int> s2;
    qc::span3<int> s3;
    qc::span4<int> s4;

    v = v2.x; v = v2.y;
    v = v2.r; v = v2.g;
    v = v2.s; v = v2.t;
    v = v2.i; v = v2.j;
    v = v2._0; v = v2._1;

    v = v3.x; v = v3.y; v = v3.z;
    v = v3.r; v = v3.g; v = v3.b;
    v = v3.s; v = v3.t; v = v3.p;
    v = v3.i; v = v3.j; v = v3.k;
    v = v3.rad; v = v3.theta; v = v3.phi;
    v = v3.alpha; v = v3.beta; v = v3.gamma;
    v = v3._0; v = v3._1; v = v3._2;

    v = v4.x; v = v4.y; v = v4.z; v = v4.w;
    v = v4.r; v = v4.g; v = v4.b; v = v4.a;
    v = v4.s; v = v4.t; v = v4.p; v = v4.q;
    v = v4._0; v = v4._1; v = v4._2; v = v4._3;

    v = s1.min; v = s1.max;
    v2 = s2.min; v2 = s2.max;
    v3 = s3.min; v3 = s3.max;
    v4 = s4.min; v4 = s4.max;
}

template <typename T>
constexpr void compileConstantsT() {
    constexpr qc::vec2<T> px2(qc::px2<T>);
    constexpr qc::vec3<T> px3(qc::px3<T>);
    constexpr qc::vec4<T> px4(qc::px4<T>);
    constexpr qc::vec2<T> py2(qc::py2<T>);
    constexpr qc::vec3<T> py3(qc::py3<T>);
    constexpr qc::vec4<T> py4(qc::py4<T>);
    constexpr qc::vec3<T> pz3(qc::pz3<T>);
    constexpr qc::vec4<T> pz4(qc::pz4<T>);
    constexpr qc::vec4<T> pw4(qc::pw4<T>);
    constexpr qc::vec2<T> nx2(qc::nx2<T>);
    constexpr qc::vec3<T> nx3(qc::nx3<T>);
    constexpr qc::vec4<T> nx4(qc::nx4<T>);
    constexpr qc::vec2<T> ny2(qc::ny2<T>);
    constexpr qc::vec3<T> ny3(qc::ny3<T>);
    constexpr qc::vec4<T> ny4(qc::ny4<T>);
    constexpr qc::vec3<T> nz3(qc::nz3<T>);
    constexpr qc::vec4<T> nz4(qc::nz4<T>);
    constexpr qc::vec4<T> nw4(qc::nw4<T>);

    constexpr qc::vec2<T> iv2(qc::infvec<T, 2>);
    constexpr qc::vec3<T> iv3(qc::infvec<T, 3>);
    constexpr qc::vec4<T> iv4(qc::infvec<T, 4>);
}

template <typename T>
constexpr void compileConstantsFT() {
    constexpr qc::vec2<T> nv2(qc::nanvec<T, 2>);
    constexpr qc::vec3<T> nv3(qc::nanvec<T, 3>);
    constexpr qc::vec4<T> nv4(qc::nanvec<T, 4>);

    constexpr qc::span1<T> ns1(qc::nanspan<T, 1>);
    constexpr qc::span2<T> ns2(qc::nanspan<T, 2>);
    constexpr qc::span3<T> ns3(qc::nanspan<T, 3>);
    constexpr qc::span4<T> ns4(qc::nanspan<T, 4>);
}

template <typename T>
constexpr void compileConstantsST() {
    constexpr qc::span1<T> is1(qc::infspan<T, 1>);
    constexpr qc::span2<T> is2(qc::infspan<T, 2>);
    constexpr qc::span3<T> is3(qc::infspan<T, 3>);
    constexpr qc::span4<T> is4(qc::infspan<T, 4>);

    constexpr qc::span1<T> nulls1(qc::nullspan<T, 1>);
    constexpr qc::span2<T> nulls2(qc::nullspan<T, 2>);
    constexpr qc::span3<T> nulls3(qc::nullspan<T, 3>);
    constexpr qc::span4<T> nulls4(qc::nullspan<T, 4>);
}

constexpr bool compileConstants() {
    compileConstantsT<qc::f32>();
    compileConstantsT<qc::f64>();
    compileConstantsT<qc::s08>();
    compileConstantsT<qc::s16>();
    compileConstantsT<qc::s32>();
    compileConstantsT<qc::s64>();
    compileConstantsT<qc::u08>();
    compileConstantsT<qc::u16>();
    compileConstantsT<qc::u32>();
    compileConstantsT<qc::u64>();

    compileConstantsFT<qc::f32>();
    compileConstantsFT<qc::f64>();

    compileConstantsST<qc::f32>();
    compileConstantsST<qc::f64>();
    compileConstantsST<qc::s08>();
    compileConstantsST<qc::s16>();
    compileConstantsST<qc::s32>();
    compileConstantsST<qc::s64>();

    return true;
}

}

void testVector() {
    compileClasses();
    static_assert(compileClassesConstexpr());
    compileFunctions();
    static_assert(compileFunctionsConstexpr());
    testProperties();
    static_assert(compileCasts());
    compileMembers();
    static_assert(compileConstants());
}
