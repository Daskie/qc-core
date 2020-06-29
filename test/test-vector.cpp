#include <sstream>

#include <CppUnitTest.h>

#include <qc-core/vector-ext.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace qc::core::types;

template <typename T>
static void compileClassesT() {
    T v{};
    vec2<T> v2;
    vec3<T> v3;
    vec4<T> v4;

    //--------------------------------------------------------------------------
    // Vec2

    // constructors
    vec2<T> v2_01;
    vec2<T> v2_02(v2);
    vec2<T> v2_03(std::move(v2));
    vec2<T> v2_04(v);
    vec2<T> v2_06(v3);
    vec2<T> v2_07(v4);
    vec2<T> v2_08(v, v);

    // assignment
    v2 = v2;
    v2 = std::move(v2);

    // Conversion
    static_cast<bool>(v2);

    // access
    v2[0];

    v2.at<0>();
    v2.at<1>();

    //--------------------------------------------------------------------------
    // Vec3

    // constructors
    vec3<T> v3_01;
    vec3<T> v3_02(v3);
    vec3<T> v3_03(std::move(v3));
    vec3<T> v3_04(v);
    vec3<T> v3_06(v2);
    vec3<T> v3_07(v4);
    vec3<T> v3_08(v, v, v);
    vec3<T> v3_16(v2, v);
    vec3<T> v3_18(v, v2);

    // assignment
    v3 = v3;
    v3 = std::move(v3);

    // Conversion
    static_cast<bool>(v3);

    // access
    v3[0];

    v3.at<0>();
    v3.at<1>();
    v3.at<2>();

    v3.xy();
    v3.yz();

    //--------------------------------------------------------------------------
    // Vec4

    // constructors
    vec4<T> v4_01;
    vec4<T> v4_02(v4);
    vec4<T> v4_03(std::move(v4));
    vec4<T> v4_04(v);
    vec4<T> v4_06(v2);
    vec4<T> v4_07(v3);
    vec4<T> v4_08(v, v, v, v);
    vec4<T> v4_23(v2, v, v);
    vec4<T> v4_27(v, v2, v);
    vec4<T> v4_31(v, v, v2);
    vec4<T> v4_35(v2, v2);
    vec4<T> v4_36(v3, v);
    vec4<T> v4_38(v, v3);

    // assignment
    v4 = v4;
    v4 = std::move(v4);

    // Conversion
    static_cast<bool>(v4);

    // access
    v4[0];

    v4.at<0>();
    v4.at<1>();
    v4.at<2>();
    v4.at<3>();

    v4.xy();
    v4.yz();
    v4.zw();
    v4.xyz();
    v4.yzw();
}

static void compileClasses() {
    compileClassesT<f32>();
    compileClassesT<f64>();
    compileClassesT<s08>();
    compileClassesT<s16>();
    compileClassesT<s32>();
    compileClassesT<s64>();
    compileClassesT<u08>();
    compileClassesT<u16>();
    compileClassesT<u32>();
    compileClassesT<u64>();
}

template <typename T>
static constexpr void compileClassesConstexprT() {
    constexpr T v{};
    constexpr vec2<T> v2;
    constexpr vec3<T> v3;
    constexpr vec4<T> v4;

    //--------------------------------------------------------------------------
    // Vec2

    // constructors
    constexpr vec2<T> v2_01;
    constexpr vec2<T> v2_02(v2);
    constexpr vec2<T> v2_03(std::move(v2));
    constexpr vec2<T> v2_04(v);
    constexpr vec2<T> v2_06(v3);
    constexpr vec2<T> v2_07(v4);
    constexpr vec2<T> v2_08(v, v);

    // Conversion
    static_cast<bool>(v2);

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
    constexpr vec3<T> v3_06(v2);
    constexpr vec3<T> v3_07(v4);
    constexpr vec3<T> v3_08(v, v, v);
    constexpr vec3<T> v3_16(v2, v);
    //constexpr vec3<T> v3_18(v, v2);

    // Conversion
    static_cast<bool>(v3);

    // access
    v3.at<0>();
    v3.at<1>();
    v3.at<2>();

    //v3.xy();
    //v3.yz();

    //--------------------------------------------------------------------------
    // Vec4

    // constructors
    constexpr vec4<T> v4_01;
    constexpr vec4<T> v4_02(v4);
    constexpr vec4<T> v4_03(std::move(v4));
    constexpr vec4<T> v4_04(v);
    constexpr vec4<T> v4_06(v2);
    constexpr vec4<T> v4_07(v3);
    constexpr vec4<T> v4_08(v, v, v, v);
    constexpr vec4<T> v4_23(v2, v, v);
    //constexpr vec4<T> v4_27(v, v2, v);
    //constexpr vec4<T> v4_31(v, v, v2);
    constexpr vec4<T> v4_35(v2, v2);
    constexpr vec4<T> v4_36(v3, v);
    //constexpr vec4<T> v4_38(v, v3);

    // Conversion
    static_cast<bool>(v4);

    // access
    v4.at<0>();
    v4.at<1>();
    v4.at<2>();
    v4.at<3>();

    //v4.xy();
    //v4.yz();
    //v4.zw();
    //v4.xyz();
    //v4.yzw();
}

static constexpr bool compileClassesConstexpr() {
    compileClassesConstexprT<f32>();
    compileClassesConstexprT<f64>();
    compileClassesConstexprT<s08>();
    compileClassesConstexprT<s16>();
    compileClassesConstexprT<s32>();
    compileClassesConstexprT<s64>();
    compileClassesConstexprT<u08>();
    compileClassesConstexprT<u16>();
    compileClassesConstexprT<u32>();
    compileClassesConstexprT<u64>();

    return true;
}

template <typename T1, typename T2>
static void compileFunctionsTT() {
    T1 v; v;
    vec2<T1> v2; v2;
    vec3<T1> v3; v3;
    vec4<T1> v4; v4;
}

template <typename T>
static void compileFunctionsT() {
    compileFunctionsTT<T, f32>();
    compileFunctionsTT<T, f64>();
    compileFunctionsTT<T, s08>();
    compileFunctionsTT<T, s16>();
    compileFunctionsTT<T, s32>();
    compileFunctionsTT<T, s64>();
    compileFunctionsTT<T, u08>();
    compileFunctionsTT<T, u16>();
    compileFunctionsTT<T, u32>();
    compileFunctionsTT<T, u64>();

    T v{};
    vec2<T> v2;
    vec3<T> v3;
    vec4<T> v4;
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

    v2 /= vec2<T>(T(1));
    v3 /= vec3<T>(T(1));
    v4 /= vec4<T>(T(1));
    v2 /= T(1);
    v3 /= T(1);
    v4 /= T(1);

    v2 %= vec2<T>(T(1));
    v3 %= vec3<T>(T(1));
    v4 %= vec4<T>(T(1));
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

    v2 - v2;
    v3 - v3;
    v4 - v4;
    v2 - v;
    v3 - v;
    v4 - v;
    v - v2;
    v - v3;
    v - v4;

    v2 * v2;
    v3 * v3;
    v4 * v4;
    v2 * v;
    v3 * v;
    v4 * v;
    v * v2;
    v * v3;
    v * v4;

    v2 / vec2<T>(T(1));
    v3 / vec3<T>(T(1));
    v4 / vec4<T>(T(1));
    v2 / T(1);
    v3 / T(1);
    v4 / T(1);
    v / vec2<T>(T(1));
    v / vec3<T>(T(1));
    v / vec4<T>(T(1));

    v2 % vec2<T>(T(1));
    v3 % vec3<T>(T(1));
    v4 % vec4<T>(T(1));
    v2 % T(1);
    v3 % T(1);
    v4 % T(1);
    v % vec2<T>(T(1));
    v % vec3<T>(T(1));
    v % vec4<T>(T(1));


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

    v2 != v2;
    v3 != v3;
    v4 != v4;
    v2 != v;
    v3 != v;
    v4 != v;
    v != v2;
    v != v3;
    v != v4;

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

    qc::core::sum(v2);
    qc::core::sum(v3);
    qc::core::sum(v4);

    qc::core::product(v2);
    qc::core::product(v3);
    qc::core::product(v4);

    // other

    os << v2;
    os << v3;
    os << v4;

    // uncategorized

    qc::core::magnitude2(v2);
    qc::core::magnitude2(v3);
    qc::core::magnitude2(v4);

    qc::core::dot(v2, v2);
    qc::core::dot(v3, v3);
    qc::core::dot(v4, v4);

    qc::core::cross(v2, v2);
    qc::core::cross(v3, v3);

    qc::core::parallel(v2, v2);
    qc::core::parallel(v3, v3);
    qc::core::parallel(v4, v4);

    qc::core::orthogonal(v2, v2);
    qc::core::orthogonal(v3, v3);
    qc::core::orthogonal(v4, v4);

    if constexpr (!std::is_unsigned_v<T>) {
        qc::core::ortho(v2);
        qc::core::ortho(v3);
    }

    qc::core::min(v2);
    qc::core::min(v3);
    qc::core::min(v4);

    qc::core::min(v2, v2);
    qc::core::min(v3, v3);
    qc::core::min(v4, v4);

    qc::core::min(v2, v2, v2);
    qc::core::min(v3, v3, v3);
    qc::core::min(v4, v4, v4);

    qc::core::min(v2, v2, v2, v2);
    qc::core::min(v3, v3, v3, v3);
    qc::core::min(v4, v4, v4, v4);

    qc::core::min(v2, v2, v2, v2, v2);
    qc::core::min(v3, v3, v3, v3, v3);
    qc::core::min(v4, v4, v4, v4, v4);

    qc::core::min(v2, v);
    qc::core::min(v3, v);
    qc::core::min(v4, v);
    qc::core::min(v, v2);
    qc::core::min(v, v3);
    qc::core::min(v, v4);

    qc::core::max(v2);
    qc::core::max(v3);
    qc::core::max(v4);

    qc::core::max(v2, v2);
    qc::core::max(v3, v3);
    qc::core::max(v4, v4);

    qc::core::max(v2, v2, v2);
    qc::core::max(v3, v3, v3);
    qc::core::max(v4, v4, v4);

    qc::core::max(v2, v2, v2, v2);
    qc::core::max(v3, v3, v3, v3);
    qc::core::max(v4, v4, v4, v4);

    qc::core::max(v2, v2, v2, v2, v2);
    qc::core::max(v3, v3, v3, v3, v3);
    qc::core::max(v4, v4, v4, v4, v4);

    qc::core::max(v2, v);
    qc::core::max(v3, v);
    qc::core::max(v4, v);
    qc::core::max(v, v2);
    qc::core::max(v, v3);
    qc::core::max(v, v4);

    qc::core::minify(v2, v2);
    qc::core::minify(v3, v3);
    qc::core::minify(v4, v4);
    qc::core::minify(v2, v);
    qc::core::minify(v3, v);
    qc::core::minify(v4, v);

    qc::core::maxify(v2, v2);
    qc::core::maxify(v3, v3);
    qc::core::maxify(v4, v4);
    qc::core::maxify(v2, v);
    qc::core::maxify(v3, v);
    qc::core::maxify(v4, v);

    qc::core::minmax(v2);
    qc::core::minmax(v3);
    qc::core::minmax(v4);

    qc::core::median(v3);

    qc::core::sort(v2);
    qc::core::sort(v3);
    qc::core::sort(v4);

    qc::core::clamp(v2, v, v);
    qc::core::clamp(v3, v, v);
    qc::core::clamp(v4, v, v);

    qc::core::clamp(v2, v2, v2);
    qc::core::clamp(v3, v3, v3);
    qc::core::clamp(v4, v4, v4);

    qc::core::abs(v2);
    qc::core::abs(v3);
    qc::core::abs(v4);

    qc::core::zero(v2);
    qc::core::zero(v3);
    qc::core::zero(v4);

    qc::core::equal(v2, v2, v2, v2, v2);
    qc::core::equal(v3, v3, v3, v3, v3);
    qc::core::equal(v4, v4, v4, v4, v4);

    qc::core::equal(v2);
    qc::core::equal(v3);
    qc::core::equal(v4);

    qc::core::sign(v2);
    qc::core::sign(v3);
    qc::core::sign(v3);

    qc::core::round(v2);
    qc::core::round(v3);
    qc::core::round(v4);

    qc::core::floor(v2);
    qc::core::floor(v3);
    qc::core::floor(v4);

    qc::core::ceil(v2);
    qc::core::ceil(v3);
    qc::core::ceil(v4);

    qc::core::composite(v2, v2);
    qc::core::composite(v3, v3);
    qc::core::composite(v4, v4);
}

template <typename T>
static void compileFunctionsFT() {
    T v{1};
    vec2<T> v2;
    vec3<T> v3;
    vec4<T> v4;

    qc::core::equal_e(v2, v);
    qc::core::equal_e(v3, v);
    qc::core::equal_e(v4, v);
    qc::core::equal_e(v2, v2, v);
    qc::core::equal_e(v3, v3, v);
    qc::core::equal_e(v4, v4, v);

    qc::core::pow(v2, v);
    qc::core::pow(v3, v);
    qc::core::pow(v4, v);

    qc::core::pow(v2, v2);
    qc::core::pow(v3, v3);
    qc::core::pow(v4, v4);

    qc::core::exp(v2);
    qc::core::exp(v3);
    qc::core::exp(v4);

    qc::core::magnitude(v2);
    qc::core::magnitude(v3);
    qc::core::magnitude(v4);

    qc::core::normalize(v2);
    qc::core::normalize(v3);
    qc::core::normalize(v4);

    qc::core::normalizeAssign(v2);
    qc::core::normalizeAssign(v3);
    qc::core::normalizeAssign(v4);

    qc::core::orthogonalize(v2, v2);
    qc::core::orthogonalize(v3, v3);
    qc::core::orthogonalize(v4, v4);
    qc::core::orthogonalize(v3, v3, v3);
    qc::core::orthogonalize_n(v3, v3, v3);

    qc::core::reflect(v2, v2);
    qc::core::reflect(v3, v3);

    qc::core::angle(v2, v2);
    qc::core::angle_n(v2, v2);
    qc::core::angle(v3, v3);
    qc::core::angle_n(v3, v3);
    qc::core::angle(v4, v4);
    qc::core::angle_n(v4, v4);

    qc::core::mix(v2, v2, v);
    qc::core::mix(v3, v3, v);
    qc::core::mix(v4, v4, v);

    qc::core::mix(v, v, v2);
    qc::core::mix(v2, v2, v2);
    qc::core::mix(v3, v3, v2);
    qc::core::mix(v4, v4, v2);
    qc::core::mix(v, v, v, v3);
    qc::core::mix(v2, v2, v2, v3);
    qc::core::mix(v3, v3, v3, v3);
    qc::core::mix(v4, v4, v4, v3);
    qc::core::mix(v, v, v, v, v4);
    qc::core::mix(v2, v2, v2, v2, v4);
    qc::core::mix(v3, v3, v3, v3, v4);
    qc::core::mix(v4, v4, v4, v4, v4);

    qc::core::smoothstep(v2, v2, v);
    qc::core::smoothstep(v3, v3, v);
    qc::core::smoothstep(v4, v4, v);

    qc::core::transnorm<fvec2>(v2);
    qc::core::transnorm<fvec3>(v3);
    qc::core::transnorm<fvec4>(v4);
    qc::core::transnorm<dvec2>(v2);
    qc::core::transnorm<dvec3>(v3);
    qc::core::transnorm<dvec4>(v4);
    qc::core::transnorm<cvec2>(v2);
    qc::core::transnorm<cvec3>(v3);
    qc::core::transnorm<cvec4>(v4);
    qc::core::transnorm<svec2>(v2);
    qc::core::transnorm<svec3>(v3);
    qc::core::transnorm<svec4>(v4);
    qc::core::transnorm<ivec2>(v2);
    qc::core::transnorm<ivec3>(v3);
    qc::core::transnorm<ivec4>(v4);
    qc::core::transnorm<lvec2>(v2);
    qc::core::transnorm<lvec3>(v3);
    qc::core::transnorm<lvec4>(v4);
    qc::core::transnorm<ucvec2>(v2);
    qc::core::transnorm<ucvec3>(v3);
    qc::core::transnorm<ucvec4>(v4);
    qc::core::transnorm<usvec2>(v2);
    qc::core::transnorm<usvec3>(v3);
    qc::core::transnorm<usvec4>(v4);
    qc::core::transnorm<uivec2>(v2);
    qc::core::transnorm<uivec3>(v3);
    qc::core::transnorm<uivec4>(v4);
    qc::core::transnorm<ulvec2>(v2);
    qc::core::transnorm<ulvec3>(v3);
    qc::core::transnorm<ulvec4>(v4);
}

template <typename T>
static void compileFunctionsIT() {
    T v{}; v;
    vec2<T> v2; v2;
    vec3<T> v3; v3;
    vec4<T> v4; v4;
}

template <typename T>
static void compileFunctionsSIT() {
    T v{}; v;
    vec2<T> v2; v2;
    vec3<T> v3; v3;
    vec4<T> v4; v4;

    qc::core::transnorm<fvec2>(v2);
    qc::core::transnorm<fvec3>(v3);
    qc::core::transnorm<fvec4>(v4);
    qc::core::transnorm<dvec2>(v2);
    qc::core::transnorm<dvec3>(v3);
    qc::core::transnorm<dvec4>(v4);
}

template <typename T>
static void compileFunctionsUIT() {
    T v{}; v;
    vec2<T> v2; v2;
    vec3<T> v3; v3;
    vec4<T> v4; v4;

    qc::core::transnorm<fvec2>(v2);
    qc::core::transnorm<fvec3>(v3);
    qc::core::transnorm<fvec4>(v4);
    qc::core::transnorm<dvec2>(v2);
    qc::core::transnorm<dvec3>(v3);
    qc::core::transnorm<dvec4>(v4);
    qc::core::transnorm<ucvec2>(v2);
    qc::core::transnorm<ucvec3>(v3);
    qc::core::transnorm<ucvec4>(v4);
    qc::core::transnorm<usvec2>(v2);
    qc::core::transnorm<usvec3>(v3);
    qc::core::transnorm<usvec4>(v4);
    qc::core::transnorm<uivec2>(v2);
    qc::core::transnorm<uivec3>(v3);
    qc::core::transnorm<uivec4>(v4);
    qc::core::transnorm<ulvec2>(v2);
    qc::core::transnorm<ulvec3>(v3);
    qc::core::transnorm<ulvec4>(v4);

    qc::core::mipmaps(v2);
    qc::core::mipmaps(v3);
    qc::core::mipmaps(v4);
}

static void compileFunctionsBT() {
    bvec2 b2;
    bvec3 b3;
    bvec4 b4;

    b2 && b2;
    b3 && b3;
    b4 && b4;

    b2 || b2;
    b3 || b3;
    b4 || b4;

    !b2;
    !b3;
    !b4;

    qc::core::all(b2);
    qc::core::all(b3);
    qc::core::all(b4);

    qc::core::any(b2);
    qc::core::any(b3);
    qc::core::any(b4);
}

static void compileFunctions() {
    compileFunctionsT<f32>();
    compileFunctionsT<f64>();
    compileFunctionsT<s08>();
    compileFunctionsT<s16>();
    compileFunctionsT<s32>();
    compileFunctionsT<s64>();
    compileFunctionsT<u08>();
    compileFunctionsT<u16>();
    compileFunctionsT<u32>();
    compileFunctionsT<u64>();

    compileFunctionsFT<f32>();
    compileFunctionsFT<f64>();

    compileFunctionsIT<s08>();
    compileFunctionsIT<s16>();
    compileFunctionsIT<s32>();
    compileFunctionsIT<s64>();
    compileFunctionsIT<u08>();
    compileFunctionsIT<u16>();
    compileFunctionsIT<u32>();
    compileFunctionsIT<u64>();

    compileFunctionsSIT<s08>();
    compileFunctionsSIT<s16>();
    compileFunctionsSIT<s32>();
    compileFunctionsSIT<s64>();

    compileFunctionsUIT<u08>();
    compileFunctionsUIT<u16>();
    compileFunctionsUIT<u32>();
    compileFunctionsUIT<u64>();

    compileFunctionsBT();
}

template <typename T1, typename T2>
static constexpr void compileFunctionsConstexprTT() {
    constexpr T1 v{T1(1.0)};
    constexpr vec2<T1> v2(T1(1.0));
    constexpr vec3<T1> v3(T1(1.0));
    constexpr vec4<T1> v4(T1(1.0));


}

template <typename T>
static constexpr void compileFunctionsConstexprT() {
    compileFunctionsConstexprTT<T, f32>();
    compileFunctionsConstexprTT<T, f64>();
    compileFunctionsConstexprTT<T, s08>();
    compileFunctionsConstexprTT<T, s16>();
    compileFunctionsConstexprTT<T, s32>();
    compileFunctionsConstexprTT<T, s64>();
    compileFunctionsConstexprTT<T, u08>();
    compileFunctionsConstexprTT<T, u16>();
    compileFunctionsConstexprTT<T, u32>();
    compileFunctionsConstexprTT<T, u64>();

    constexpr T v{1.0};
    constexpr vec2<T> v2(T(1.0));
    constexpr vec3<T> v3(T(1.0));
    constexpr vec4<T> v4(T(1.0));

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

    //v2 - v2;
    //v3 - v3;
    //v4 - v4;
    //v2 - v;
    //v3 - v;
    //v4 - v;
    //v - v2;
    //v - v3;
    //v - v4;

    //v2 * v2;
    //v3 * v3;
    //v4 * v4;
    //v2 * v;
    //v3 * v;
    //v4 * v;
    //v * v2;
    //v * v3;
    //v * v4;

    //v2 / vec2<T>(1);
    //v3 / vec3<T>(1);
    //v4 / vec4<T>(1);
    //v2 / T(v);
    //v3 / T(v);
    //v4 / T(v);
    //v / vec2<T>(1);
    //v / vec3<T>(1);
    //v / vec4<T>(1);

    //v2 % vec2<T>(1);
    //v3 % vec3<T>(1);
    //v4 % vec4<T>(1);
    //v2 % T(v);
    //v3 % T(v);
    //v4 % T(v);
    //v % vec2<T>(1);
    //v % vec3<T>(1);
    //v % vec4<T>(1);


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

    //v2 != v2;
    //v3 != v3;
    //v4 != v4;
    //v2 != v;
    //v3 != v;
    //v4 != v;
    //v != v2;
    //v != v3;
    //v != v4;

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

    //qc::core::sum(v2);
    //qc::core::sum(v3);
    //qc::core::sum(v4);

    //qc::core::product(v2);
    //qc::core::product(v3);
    //qc::core::product(v4);

    // uncategorized

    //qc::core::min(v2);
    //qc::core::min(v3);
    //qc::core::min(v4);

    //qc::core::min(v2, v2);
    //qc::core::min(v3, v3);
    //qc::core::min(v4, v4);

    //qc::core::min(v2, v2, v2);
    //qc::core::min(v3, v3, v3);
    //qc::core::min(v4, v4, v4);

    //qc::core::min(v2, v2, v2, v2);
    //qc::core::min(v3, v3, v3, v3);
    //qc::core::min(v4, v4, v4, v4);

    //qc::core::min(v2, v2, v2, v2, v2);
    //qc::core::min(v3, v3, v3, v3, v3);
    //qc::core::min(v4, v4, v4, v4, v4);

    //qc::core::min(v2, v);
    //qc::core::min(v3, v);
    //qc::core::min(v4, v);
    //qc::core::min(v, v2);
    //qc::core::min(v, v3);
    //qc::core::min(v, v4);

    //qc::core::max(v2);
    //qc::core::max(v3);
    //qc::core::max(v4);

    //qc::core::max(v2, v2);
    //qc::core::max(v3, v3);
    //qc::core::max(v4, v4);

    //qc::core::max(v2, v2, v2);
    //qc::core::max(v3, v3, v3);
    //qc::core::max(v4, v4, v4);

    //qc::core::max(v2, v2, v2, v2);
    //qc::core::max(v3, v3, v3, v3);
    //qc::core::max(v4, v4, v4, v4);

    //qc::core::max(v2, v2, v2, v2, v2);
    //qc::core::max(v3, v3, v3, v3, v3);
    //qc::core::max(v4, v4, v4, v4, v4);

    //qc::core::max(v2, v);
    //qc::core::max(v3, v);
    //qc::core::max(v4, v);
    //qc::core::max(v, v2);
    //qc::core::max(v, v3);
    //qc::core::max(v, v4);

    //qc::core::minmax(v2);
    //qc::core::minmax(v3);
    //qc::core::minmax(v4);

    //qc::core::clamp(v2, v, v);
    //qc::core::clamp(v3, v, v);
    //qc::core::clamp(v4, v, v);

    //qc::core::clamp(v2, v2, v2);
    //qc::core::clamp(v3, v3, v3);
    //qc::core::clamp(v4, v4, v4);

    //qc::core::abs(v2);
    //qc::core::abs(v3);
    //qc::core::abs(v4);

    //qc::core::zero(v2);
    //qc::core::zero(v3);
    //qc::core::zero(v4);

    //qc::core::equal(v2, v2, v2, v2, v2);
    //qc::core::equal(v3, v3, v3, v3, v3);
    //qc::core::equal(v4, v4, v4, v4, v4);

    //qc::core::equal(v2);
    //qc::core::equal(v3);
    //qc::core::equal(v4);

    //qc::core::sign(v2);
    //qc::core::sign(v3);
    //qc::core::sign(v3);

    //qc::core::round(v2);
    //qc::core::round(v3);
    //qc::core::round(v4);

    //qc::core::floor(v2);
    //qc::core::floor(v3);
    //qc::core::floor(v4);

    //qc::core::ceil(v2);
    //qc::core::ceil(v3);
    //qc::core::ceil(v4);

    //qc::core::composite(v2, v2);
    //qc::core::composite(v3, v3);
    //qc::core::composite(v4, v4);
}

template <typename T>
static constexpr void compileFunctionsConstexprFT() {
    constexpr T v{1.0};
    constexpr vec2<T> v2(T(1.0));
    constexpr vec3<T> v3(T(1.0));
    constexpr vec4<T> v4(T(1.0));

    //qc::core::equal_e(v2);
    //qc::core::equal_e(v3);
    //qc::core::equal_e(v4);
    //qc::core::equal_e(v2, v);
    //qc::core::equal_e(v3, v);
    //qc::core::equal_e(v4, v);

    //qc::core::equal_e(v2, v2);
    //qc::core::equal_e(v3, v3);
    //qc::core::equal_e(v4, v4);
    //qc::core::equal_e(v2, v2, v);
    //qc::core::equal_e(v3, v3, v);
    //qc::core::equal_e(v4, v4, v);

    //qc::core::mix(v2, v2, v);
    //qc::core::mix(v3, v3, v);
    //qc::core::mix(v4, v4, v);

    //qc::core::mix(v, v, v2);
    //qc::core::mix(v2, v2, v2);
    //qc::core::mix(v3, v3, v2);
    //qc::core::mix(v4, v4, v2);
    //qc::core::mix(v, v, v, v3);
    //qc::core::mix(v2, v2, v2, v3);
    //qc::core::mix(v3, v3, v3, v3);
    //qc::core::mix(v4, v4, v4, v3);
    //qc::core::mix(v, v, v, v, v4);
    //qc::core::mix(v2, v2, v2, v2, v4);
    //qc::core::mix(v3, v3, v3, v3, v4);
    //qc::core::mix(v4, v4, v4, v4, v4);

    //qc::core::smoothstep(v2, v2, v);
    //qc::core::smoothstep(v3, v3, v);
    //qc::core::smoothstep(v4, v4, v);
}

template <typename T>
static constexpr void compileFunctionsConstexprIT() {
    constexpr T v{1.0};
    constexpr vec2<T> v2(T(1.0));
    constexpr vec3<T> v3(T(1.0));
    constexpr vec4<T> v4(T(1.0));

    //qc::core::mipmaps(v2);
    //qc::core::mipmaps(v3);
    //qc::core::mipmaps(v4);
}

static constexpr void compileBoolFunctionsConstexpr() {
    bvec2 b2;
    bvec3 b3;
    bvec4 b4;

    //b2 && b2;
    //b3 && b3;
    //b4 && b4;

    //b2 || b2;
    //b3 || b3;
    //b4 || b4;

    //!b2;
    //!b3;
    //!b4;

    //qc::core::all(b2);
    //qc::core::all(b3);
    //qc::core::all(b4);

    //qc::core::any(b2);
    //qc::core::any(b3);
    //qc::core::any(b4);
}

static constexpr bool compileFunctionsConstexpr() {
    compileFunctionsConstexprT<f32>();
    compileFunctionsConstexprT<f64>();
    compileBoolFunctionsConstexpr();

    return true;
}

template <typename T, int n>
static void testPropertiesTN() {
    static_assert(std::is_standard_layout_v<vec<T, n>>);
    static_assert(std::is_trivially_copyable_v<vec<T, n>>);
    static_assert(std::is_trivially_copy_constructible_v<vec<T, n>>);
    static_assert(std::is_trivially_move_constructible_v<vec<T, n>>);
    static_assert(std::is_trivially_copy_assignable_v<vec<T, n>>);
    static_assert(std::is_trivially_move_assignable_v<vec<T, n>>);
    static_assert(std::is_trivially_destructible_v<vec<T, n>>);
    static_assert(sizeof(vec<T, n>) == n * sizeof(T));
    static_assert(sizeof(vec<T, n>[4]) == 4 * n * sizeof(T));
    static_assert(alignof(vec<T, n>) == alignof(T));
    static_assert(alignof(vec<T, n>[4]) == alignof(T));
}

template <typename T>
static void testPropertiesT() {
    testPropertiesTN<T, 2>();
    testPropertiesTN<T, 3>();
    testPropertiesTN<T, 4>();
}

static void testProperties() {
    testPropertiesT<f32>();
    testPropertiesT<f64>();
    testPropertiesT<s08>();
    testPropertiesT<s16>();
    testPropertiesT<s32>();
    testPropertiesT<s64>();
    testPropertiesT<u08>();
    testPropertiesT<u16>();
    testPropertiesT<u32>();
    testPropertiesT<u64>();
}

template <typename T1, typename T2, int n>
static constexpr void compileVecCastsTTN() {
    vec2<T1> v2;
    vec2<T1> v3;
    vec2<T1> v4;

    { vec<T2, n> v(v2); }
    { vec<T2, n> v(v3); }
    { vec<T2, n> v(v4); }

    static_cast<vec<T2, n>>(v2);
    static_cast<vec<T2, n>>(v3);
    static_cast<vec<T2, n>>(v4);
}

template <typename T1, typename T2>
static constexpr void compileCastsTT() {
    compileVecCastsTTN<T1, T2, 2>();
    compileVecCastsTTN<T1, T2, 3>();
    compileVecCastsTTN<T1, T2, 4>();
}

template <typename T>
static constexpr void compileCastsT() {
    compileCastsTT<T, f32>();
    compileCastsTT<T, f64>();
    compileCastsTT<T, s08>();
    compileCastsTT<T, s16>();
    compileCastsTT<T, s32>();
    compileCastsTT<T, s64>();
    compileCastsTT<T, u08>();
    compileCastsTT<T, u16>();
    compileCastsTT<T, u32>();
    compileCastsTT<T, u64>();
    compileCastsTT<T, bool>();
}

static constexpr bool compileCasts() {
    compileCastsT<f32>();
    compileCastsT<f64>();
    compileCastsT<s08>();
    compileCastsT<s16>();
    compileCastsT<s32>();
    compileCastsT<s64>();
    compileCastsT<u08>();
    compileCastsT<u16>();
    compileCastsT<u32>();
    compileCastsT<u64>();
    compileCastsT<bool>();

    return true;
}

template <typename T>
static constexpr void compileConstantsT() {
    constexpr vec2<T> px2(qc::core::px2<T>);
    constexpr vec3<T> px3(qc::core::px3<T>);
    constexpr vec4<T> px4(qc::core::px4<T>);
    constexpr vec2<T> py2(qc::core::py2<T>);
    constexpr vec3<T> py3(qc::core::py3<T>);
    constexpr vec4<T> py4(qc::core::py4<T>);
    constexpr vec3<T> pz3(qc::core::pz3<T>);
    constexpr vec4<T> pz4(qc::core::pz4<T>);
    constexpr vec4<T> pw4(qc::core::pw4<T>);
    constexpr vec2<T> nx2(qc::core::nx2<T>);
    constexpr vec3<T> nx3(qc::core::nx3<T>);
    constexpr vec4<T> nx4(qc::core::nx4<T>);
    constexpr vec2<T> ny2(qc::core::ny2<T>);
    constexpr vec3<T> ny3(qc::core::ny3<T>);
    constexpr vec4<T> ny4(qc::core::ny4<T>);
    constexpr vec3<T> nz3(qc::core::nz3<T>);
    constexpr vec4<T> nz4(qc::core::nz4<T>);
    constexpr vec4<T> nw4(qc::core::nw4<T>);
}

template <typename T>
static constexpr void compileConstantsFT() {
    constexpr vec2<T> iv2(qc::core::infvec<T, 2>);
    constexpr vec3<T> iv3(qc::core::infvec<T, 3>);
    constexpr vec4<T> iv4(qc::core::infvec<T, 4>);

    constexpr vec2<T> nv2(qc::core::nanvec<T, 2>);
    constexpr vec3<T> nv3(qc::core::nanvec<T, 3>);
    constexpr vec4<T> nv4(qc::core::nanvec<T, 4>);
}

static constexpr bool compileConstants() {
    compileConstantsT<f32>();
    compileConstantsT<f64>();
    compileConstantsT<s08>();
    compileConstantsT<s16>();
    compileConstantsT<s32>();
    compileConstantsT<s64>();
    compileConstantsT<u08>();
    compileConstantsT<u16>();
    compileConstantsT<u32>();
    compileConstantsT<u64>();

    compileConstantsFT<f32>();
    compileConstantsFT<f64>();

    return true;
}

TEST_CLASS(TestVector) {

    public:

    TEST_METHOD(testCompilation) {
        compileClasses();
        static_assert(compileClassesConstexpr());
        compileFunctions();
        static_assert(compileFunctionsConstexpr());
        testProperties();
        static_assert(compileCasts());
        static_assert(compileConstants());
    }

    template <typename T>
    void testVectorConceptT() {
        static_assert(Vector<vec2<T>>);
        static_assert(Vector<vec3<T>>);
        static_assert(Vector<vec4<T>>);
    }

    template <typename T>
    void testFloaterVectorConceptT() {
        static_assert(FloatingVector<vec2<T>>);
        static_assert(FloatingVector<vec3<T>>);
        static_assert(FloatingVector<vec4<T>>);
    }

    template <typename T>
    void testIntegerVectorConceptT() {
        static_assert(IntegralVector<vec2<T>>);
        static_assert(IntegralVector<vec3<T>>);
        static_assert(IntegralVector<vec4<T>>);
    }

    template <typename T>
    void testSignedIntegerVectorConceptT() {
        static_assert(SignedIntegralVector<vec2<T>>);
        static_assert(SignedIntegralVector<vec3<T>>);
        static_assert(SignedIntegralVector<vec4<T>>);
    }

    template <typename T>
    void testUnsignedIntegerVectorConceptT() {
        static_assert(UnsignedIntegralVector<vec2<T>>);
        static_assert(UnsignedIntegralVector<vec3<T>>);
        static_assert(UnsignedIntegralVector<vec4<T>>);
    }

    TEST_METHOD(testConcepts) {
        testVectorConceptT<s08>();
        testVectorConceptT<u08>();
        testVectorConceptT<s16>();
        testVectorConceptT<u16>();
        testVectorConceptT<f32>();
        testVectorConceptT<s32>();
        testVectorConceptT<u32>();
        testVectorConceptT<f64>();
        testVectorConceptT<s64>();
        testVectorConceptT<u64>();
        static_assert(!Vector<int>);

        testFloaterVectorConceptT<f32>();
        testFloaterVectorConceptT<f64>();
        static_assert(!FloatingVector<ivec2>);

        testIntegerVectorConceptT<s08>();
        testIntegerVectorConceptT<u08>();
        testIntegerVectorConceptT<s16>();
        testIntegerVectorConceptT<u16>();
        testIntegerVectorConceptT<s32>();
        testIntegerVectorConceptT<u32>();
        testIntegerVectorConceptT<s64>();
        testIntegerVectorConceptT<u64>();
        static_assert(!IntegralVector<fvec2>);

        testSignedIntegerVectorConceptT<s08>();
        testSignedIntegerVectorConceptT<s16>();
        testSignedIntegerVectorConceptT<s32>();
        testSignedIntegerVectorConceptT<s64>();
        static_assert(!SignedIntegralVector<uivec2>);

        testUnsignedIntegerVectorConceptT<u08>();
        testUnsignedIntegerVectorConceptT<u16>();
        testUnsignedIntegerVectorConceptT<u32>();
        testUnsignedIntegerVectorConceptT<u64>();
        static_assert(!UnsignedIntegralVector<ivec2>);

        static_assert(BooleanVector<bvec2>);
        static_assert(BooleanVector<bvec3>);
        static_assert(BooleanVector<bvec4>);
        static_assert(!BooleanVector<fvec2>);

        static_assert(Vector2<cvec2>);
        static_assert(Vector2<ucvec2>);
        static_assert(Vector2<svec2>);
        static_assert(Vector2<usvec2>);
        static_assert(Vector2<fvec2>);
        static_assert(Vector2<ivec2>);
        static_assert(Vector2<uivec2>);
        static_assert(Vector2<lvec2>);
        static_assert(Vector2<ulvec2>);
        static_assert(Vector2<dvec2>);
        static_assert(!Vector2<ivec3>);

        static_assert(Vector3<cvec3>);
        static_assert(Vector3<ucvec3>);
        static_assert(Vector3<svec3>);
        static_assert(Vector3<usvec3>);
        static_assert(Vector3<fvec3>);
        static_assert(Vector3<ivec3>);
        static_assert(Vector3<uivec3>);
        static_assert(Vector3<lvec3>);
        static_assert(Vector3<ulvec3>);
        static_assert(Vector3<dvec3>);
        static_assert(!Vector3<ivec4>);

        static_assert(Vector4<cvec4>);
        static_assert(Vector4<ucvec4>);
        static_assert(Vector4<svec4>);
        static_assert(Vector4<usvec4>);
        static_assert(Vector4<fvec4>);
        static_assert(Vector4<ivec4>);
        static_assert(Vector4<uivec4>);
        static_assert(Vector4<lvec4>);
        static_assert(Vector4<ulvec4>);
        static_assert(Vector4<dvec4>);
        static_assert(!Vector4<ivec2>);
    }

};
