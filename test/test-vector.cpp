#include <qc-core/vector-ext.hpp>

#pragma warning(push)
#pragma warning(disable: 4577)
#include <sstream>

#include <gtest/gtest.h>

using namespace qc::concepts;
using namespace qc::types;

template <typename T>
static void compileClassesT()
{
    T v{};
    vec2<T> v2{};
    vec3<T> v3{};
    vec4<T> v4{};

    //--------------------------------------------------------------------------
    // Vec2

    // constructors
    vec2<T> v2_01{};
    vec2<T> v2_02{v2};
    vec2<T> v2_03{std::move(v2)};
    vec2<T> v2_04{v};
    vec2<T> v2_06{v3};
    vec2<T> v2_07{v4};
    vec2<T> v2_08{v, v};

    // assignment
    v2 = v;
    v2 = v2;
    v2 = std::move(v2);

    // Conversion
    static_cast<bool>(v2);
    auto f2{[](const vec2<T>) {}};
    f2(v);

    // access
    static_cast<void>(v2[0]);

    static_cast<void>(v2.template at<0>());
    static_cast<void>(v2.template at<1>());

    //--------------------------------------------------------------------------
    // Vec3

    // constructors
    vec3<T> v3_01{};
    vec3<T> v3_02{v3};
    vec3<T> v3_03{std::move(v3)};
    vec3<T> v3_04{v};
    vec3<T> v3_06{v2};
    vec3<T> v3_07{v4};
    vec3<T> v3_08{v, v, v};
    vec3<T> v3_16{v2, v};
    vec3<T> v3_18{v, v2};

    // assignment
    v3 = v;
    v3 = v3;
    v3 = std::move(v3);
    v3 = v2;

    // Conversion
    static_cast<bool>(v3);
    auto f3{[](const vec3<T>) {}};
    f3(v);

    // access
    static_cast<void>(v3[0]);

    static_cast<void>(v3.template at<0>());
    static_cast<void>(v3.template at<1>());
    static_cast<void>(v3.template at<2>());

    static_cast<void>(v3.xy());
    static_cast<void>(v3.yz());

    //--------------------------------------------------------------------------
    // Vec4

    // constructors
    vec4<T> v4_01{};
    vec4<T> v4_02{v4};
    vec4<T> v4_03{std::move(v4)};
    vec4<T> v4_04{v};
    vec4<T> v4_06{v2};
    vec4<T> v4_07{v3};
    vec4<T> v4_08{v, v, v, v};
    vec4<T> v4_23{v2, v, v};
    vec4<T> v4_27{v, v2, v};
    vec4<T> v4_31{v, v, v2};
    vec4<T> v4_35{v2, v2};
    vec4<T> v4_36{v3, v};
    vec4<T> v4_38{v, v3};

    // assignment
    v4 = v;
    v4 = v4;
    v4 = std::move(v4);
    v4 = v2;
    v4 = v3;

    // Conversion
    static_cast<bool>(v4);
    auto f4{[](const vec4<T>) {}};
    f4(v);

    // access
    static_cast<void>(v4[0]);

    static_cast<void>(v4.template at<0>());
    static_cast<void>(v4.template at<1>());
    static_cast<void>(v4.template at<2>());
    static_cast<void>(v4.template at<3>());

    static_cast<void>(v4.xy());
    static_cast<void>(v4.yz());
    static_cast<void>(v4.zw());
    static_cast<void>(v4.xyz());
    static_cast<void>(v4.yzw());
}

static void compileClasses()
{
    compileClassesT<f32>();
    compileClassesT<f64>();
    compileClassesT<s8>();
    compileClassesT<s16>();
    compileClassesT<s32>();
    compileClassesT<s64>();
    compileClassesT<u8>();
    compileClassesT<u16>();
    compileClassesT<u32>();
    compileClassesT<u64>();
}

template <typename T1, typename T2>
static void compileFunctionsTT() {}

template <typename T>
static void compileFunctionsT()
{
    compileFunctionsTT<T, f32>();
    compileFunctionsTT<T, f64>();
    compileFunctionsTT<T, s8>();
    compileFunctionsTT<T, s16>();
    compileFunctionsTT<T, s32>();
    compileFunctionsTT<T, s64>();
    compileFunctionsTT<T, u8>();
    compileFunctionsTT<T, u16>();
    compileFunctionsTT<T, u32>();
    compileFunctionsTT<T, u64>();

    T v{};
    vec2<T> v2{};
    vec3<T> v3{};
    vec4<T> v4{};
    std::stringstream os{};

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

    static_cast<void>(v2 == v2);
    static_cast<void>(v3 == v3);
    static_cast<void>(v4 == v4);
    static_cast<void>(v2 == v);
    static_cast<void>(v3 == v);
    static_cast<void>(v4 == v);
    static_cast<void>(v == v2);
    static_cast<void>(v == v3);
    static_cast<void>(v == v4);

    static_cast<void>(v2 != v2);
    static_cast<void>(v3 != v3);
    static_cast<void>(v4 != v4);
    static_cast<void>(v2 != v);
    static_cast<void>(v3 != v);
    static_cast<void>(v4 != v);
    static_cast<void>(v != v2);
    static_cast<void>(v != v3);
    static_cast<void>(v != v4);

    static_cast<void>(v2 < v2);
    static_cast<void>(v3 < v3);
    static_cast<void>(v4 < v4);
    static_cast<void>(v2 < v);
    static_cast<void>(v3 < v);
    static_cast<void>(v4 < v);
    static_cast<void>(v < v2);
    static_cast<void>(v < v3);
    static_cast<void>(v < v4);

    static_cast<void>(v2 > v2);
    static_cast<void>(v3 > v3);
    static_cast<void>(v4 > v4);
    static_cast<void>(v2 > v);
    static_cast<void>(v3 > v);
    static_cast<void>(v4 > v);
    static_cast<void>(v > v2);
    static_cast<void>(v > v3);
    static_cast<void>(v > v4);

    static_cast<void>(v2 <= v2);
    static_cast<void>(v3 <= v3);
    static_cast<void>(v4 <= v4);
    static_cast<void>(v2 <= v);
    static_cast<void>(v3 <= v);
    static_cast<void>(v4 <= v);
    static_cast<void>(v <= v2);
    static_cast<void>(v <= v3);
    static_cast<void>(v <= v4);

    static_cast<void>(v2 >= v2);
    static_cast<void>(v3 >= v3);
    static_cast<void>(v4 >= v4);
    static_cast<void>(v2 >= v);
    static_cast<void>(v3 >= v);
    static_cast<void>(v4 >= v);
    static_cast<void>(v >= v2);
    static_cast<void>(v >= v3);
    static_cast<void>(v >= v4);

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

    if constexpr (!std::is_unsigned_v<T>)
    {
        qc::ortho(v2);
        qc::ortho(v3);
    }

    qc::min(v2);
    qc::min(v3);
    qc::min(v4);

    qc::min(v2, v2);
    qc::min(v3, v3);
    qc::min(v4, v4);

    qc::min(v2, v2, v2);
    qc::min(v3, v3, v3);
    qc::min(v4, v4, v4);

    qc::min(v2, v2, v2, v2);
    qc::min(v3, v3, v3, v3);
    qc::min(v4, v4, v4, v4);

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

    qc::max(v2, v2, v2);
    qc::max(v3, v3, v3);
    qc::max(v4, v4, v4);

    qc::max(v2, v2, v2, v2);
    qc::max(v3, v3, v3, v3);
    qc::max(v4, v4, v4, v4);

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

    qc::clampify(v2, v, v);
    qc::clampify(v3, v, v);
    qc::clampify(v4, v, v);
    qc::clampify(v2, v2, v2);
    qc::clampify(v3, v3, v3);
    qc::clampify(v4, v4, v4);

    qc::abs(v2);
    qc::abs(v3);
    qc::abs(v4);

    qc::absify(v2);
    qc::absify(v3);
    qc::absify(v4);

    qc::zeroish(v2);
    qc::zeroish(v3);
    qc::zeroish(v4);

    qc::equalish(v2, v2);
    qc::equalish(v3, v3);
    qc::equalish(v4, v4);

    qc::equalish(v2, v2, v);
    qc::equalish(v3, v3, v);
    qc::equalish(v4, v4, v);

    qc::equalish(v2, v);
    qc::equalish(v3, v);
    qc::equalish(v4, v);

    qc::equalish(v2, v, v);
    qc::equalish(v3, v, v);
    qc::equalish(v4, v, v);

    qc::sign(v2);
    qc::sign(v3);
    qc::sign(v3);

    qc::round<T>(v2);
    qc::round<T>(v3);
    qc::round<T>(v4);

    qc::floor<T>(v2);
    qc::floor<T>(v3);
    qc::floor<T>(v4);

    qc::ceil<T>(v2);
    qc::ceil<T>(v3);
    qc::ceil<T>(v4);

    qc::composite(v2, v2);
    qc::composite(v3, v3);
    qc::composite(v4, v4);
}

template <typename T>
static void compileFunctionsFT()
{
    T v{1};
    vec2<T> v2{};
    vec3<T> v3{};
    vec4<T> v4{};

    qc::round<s8>(v2);
    qc::round<s8>(v3);
    qc::round<s8>(v4);
    qc::round<s16>(v2);
    qc::round<s16>(v3);
    qc::round<s16>(v4);
    qc::round<s32>(v2);
    qc::round<s32>(v3);
    qc::round<s32>(v4);
    qc::round<s64>(v2);
    qc::round<s64>(v3);
    qc::round<s64>(v4);

    qc::floor<s8>(v2);
    qc::floor<s8>(v3);
    qc::floor<s8>(v4);
    qc::floor<s16>(v2);
    qc::floor<s16>(v3);
    qc::floor<s16>(v4);
    qc::floor<s32>(v2);
    qc::floor<s32>(v3);
    qc::floor<s32>(v4);
    qc::floor<s64>(v2);
    qc::floor<s64>(v3);
    qc::floor<s64>(v4);

    qc::ceil<s8>(v2);
    qc::ceil<s8>(v3);
    qc::ceil<s8>(v4);
    qc::ceil<s16>(v2);
    qc::ceil<s16>(v3);
    qc::ceil<s16>(v4);
    qc::ceil<s32>(v2);
    qc::ceil<s32>(v3);
    qc::ceil<s32>(v4);
    qc::ceil<s64>(v2);
    qc::ceil<s64>(v3);
    qc::ceil<s64>(v4);

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

    qc::distance(v2, v2);
    qc::distance(v3, v3);
    qc::distance(v4, v4);

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

    qc::smoothstep(v2, v2, v);
    qc::smoothstep(v3, v3, v);
    qc::smoothstep(v4, v4, v);

    qc::transnorm<f32>(v2);
    qc::transnorm<f32>(v3);
    qc::transnorm<f32>(v4);
    qc::transnorm<f64>(v2);
    qc::transnorm<f64>(v3);
    qc::transnorm<f64>(v4);
    qc::transnorm<s8>(v2);
    qc::transnorm<s8>(v3);
    qc::transnorm<s8>(v4);
    qc::transnorm<s16>(v2);
    qc::transnorm<s16>(v3);
    qc::transnorm<s16>(v4);
    qc::transnorm<s32>(v2);
    qc::transnorm<s32>(v3);
    qc::transnorm<s32>(v4);
    qc::transnorm<s64>(v2);
    qc::transnorm<s64>(v3);
    qc::transnorm<s64>(v4);
    qc::transnorm<u8>(v2);
    qc::transnorm<u8>(v3);
    qc::transnorm<u8>(v4);
    qc::transnorm<u16>(v2);
    qc::transnorm<u16>(v3);
    qc::transnorm<u16>(v4);
    qc::transnorm<u32>(v2);
    qc::transnorm<u32>(v3);
    qc::transnorm<u32>(v4);
    qc::transnorm<u64>(v2);
    qc::transnorm<u64>(v3);
    qc::transnorm<u64>(v4);
}

template <typename T>
static void compileFunctionsST()
{
    vec2<T> v2{};
    vec2<T> v3{};
    vec2<T> v4{};

    qc::distance2(v2, v2);
    qc::distance2(v3, v3);
    qc::distance2(v4, v4);

    qc::rotateCW(v2);
    qc::rotateCCW(v2);
}

template <typename T>
static void compileFunctionsIT() {}

template <typename T>
static void compileFunctionsSIT()
{
    vec2<T> v2{};
    vec3<T> v3{};
    vec4<T> v4{};

    qc::transnorm<f32>(v2);
    qc::transnorm<f32>(v3);
    qc::transnorm<f32>(v4);
    qc::transnorm<f64>(v2);
    qc::transnorm<f64>(v3);
    qc::transnorm<f64>(v4);
}

template <typename T>
static void compileFunctionsUIT()
{
    T v{};
    vec2<T> v2{};
    vec3<T> v3{};
    vec4<T> v4{};

    v2 &= v2;
    v3 &= v3;
    v4 &= v4;
    v2 &= v;
    v3 &= v;
    v4 &= v;

    v2 |= v2;
    v3 |= v3;
    v4 |= v4;
    v2 |= v;
    v3 |= v;
    v4 |= v;

    v2 ^= v2;
    v3 ^= v3;
    v4 ^= v4;
    v2 ^= v;
    v3 ^= v;
    v4 ^= v;

    v2 >>= 1;
    v3 >>= 1;
    v4 >>= 1;

    v2 <<= 1;
    v3 <<= 1;
    v4 <<= 1;

    ~v2;
    ~v3;
    ~v4;

    v2 & v2;
    v3 & v3;
    v4 & v4;
    v2 & v;
    v3 & v;
    v4 & v;
    v & v2;
    v & v3;
    v & v4;

    v2 | v2;
    v3 | v3;
    v4 | v4;
    v2 | v;
    v3 | v;
    v4 | v;
    v | v2;
    v | v3;
    v | v4;

    v2 ^ v2;
    v3 ^ v3;
    v4 ^ v4;
    v2 ^ v;
    v3 ^ v;
    v4 ^ v;
    v ^ v2;
    v ^ v3;
    v ^ v4;

    v2 >> 1;
    v3 >> 1;
    v4 >> 1;

    v2 << 1;
    v3 << 1;
    v4 << 1;

    qc::transnorm<f32>(v2);
    qc::transnorm<f32>(v3);
    qc::transnorm<f32>(v4);
    qc::transnorm<f64>(v2);
    qc::transnorm<f64>(v3);
    qc::transnorm<f64>(v4);
    qc::transnorm<u8>(v2);
    qc::transnorm<u8>(v3);
    qc::transnorm<u8>(v4);
    qc::transnorm<u16>(v2);
    qc::transnorm<u16>(v3);
    qc::transnorm<u16>(v4);
    qc::transnorm<u32>(v2);
    qc::transnorm<u32>(v3);
    qc::transnorm<u32>(v4);
    qc::transnorm<u64>(v2);
    qc::transnorm<u64>(v3);
    qc::transnorm<u64>(v4);

    qc::mipmaps(v2);
    qc::mipmaps(v3);
    qc::mipmaps(v4);
}

static void compileFunctionsBT()
{
    bool b1{};
    bvec2 b2{};
    bvec3 b3{};
    bvec4 b4{};

    b1 && b2;
    b2 && b1;
    b2 && b2;
    b1 && b3;
    b3 && b1;
    b3 && b3;
    b1 && b4;
    b4 && b1;
    b4 && b4;

    b1 || b2;
    b2 || b1;
    b2 || b2;
    b1 || b3;
    b3 || b1;
    b3 || b3;
    b1 || b4;
    b4 || b1;
    b4 || b4;

    !b2;
    !b3;
    !b4;

    static_cast<void>(qc::all(b1));
    static_cast<void>(qc::all(b2));
    static_cast<void>(qc::all(b3));
    static_cast<void>(qc::all(b4));

    static_cast<void>(qc::any(b1));
    static_cast<void>(qc::any(b2));
    static_cast<void>(qc::any(b3));
    static_cast<void>(qc::any(b4));
}

static void compileFunctions()
{
    compileFunctionsT<f32>();
    compileFunctionsT<f64>();
    compileFunctionsT<s8>();
    compileFunctionsT<s16>();
    compileFunctionsT<s32>();
    compileFunctionsT<s64>();
    compileFunctionsT<u8>();
    compileFunctionsT<u16>();
    compileFunctionsT<u32>();
    compileFunctionsT<u64>();

    compileFunctionsFT<f32>();
    compileFunctionsFT<f64>();

    compileFunctionsST<s8>();
    compileFunctionsST<s16>();
    compileFunctionsST<s32>();
    compileFunctionsST<s64>();
    compileFunctionsST<f32>();
    compileFunctionsST<f64>();

    compileFunctionsIT<s8>();
    compileFunctionsIT<s16>();
    compileFunctionsIT<s32>();
    compileFunctionsIT<s64>();
    compileFunctionsIT<u8>();
    compileFunctionsIT<u16>();
    compileFunctionsIT<u32>();
    compileFunctionsIT<u64>();

    compileFunctionsSIT<s8>();
    compileFunctionsSIT<s16>();
    compileFunctionsSIT<s32>();
    compileFunctionsSIT<s64>();

    compileFunctionsUIT<u8>();
    compileFunctionsUIT<u16>();
    compileFunctionsUIT<u32>();
    compileFunctionsUIT<u64>();

    compileFunctionsBT();
}

template <typename T, int n>
static void testPropertiesTN()
{
    static_assert(std::is_standard_layout_v<vec<T, n>>);
    static_assert(std::is_trivially_default_constructible_v<vec<T, n>>);
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
static void testPropertiesT()
{
    testPropertiesTN<T, 2>();
    testPropertiesTN<T, 3>();
    testPropertiesTN<T, 4>();
}

static void testProperties()
{
    testPropertiesT<f32>();
    testPropertiesT<f64>();
    testPropertiesT<s8>();
    testPropertiesT<s16>();
    testPropertiesT<s32>();
    testPropertiesT<s64>();
    testPropertiesT<u8>();
    testPropertiesT<u16>();
    testPropertiesT<u32>();
    testPropertiesT<u64>();
}

template <typename T1, typename T2, int n>
static constexpr void compileVecCastsTTN()
{
    vec2<T1> v2{};
    vec2<T1> v3{};
    vec2<T1> v4{};

    { vec<T2, n> v{v2}; }
    { vec<T2, n> v{v3}; }
    { vec<T2, n> v{v4}; }

    static_cast<vec<T2, n>>(v2);
    static_cast<vec<T2, n>>(v3);
    static_cast<vec<T2, n>>(v4);
}

template <typename T1, typename T2>
static constexpr void compileCastsTT()
{
    compileVecCastsTTN<T1, T2, 2>();
    compileVecCastsTTN<T1, T2, 3>();
    compileVecCastsTTN<T1, T2, 4>();
}

template <typename T>
static constexpr void compileCastsT()
{
    compileCastsTT<T, f32>();
    compileCastsTT<T, f64>();
    compileCastsTT<T, s8>();
    compileCastsTT<T, s16>();
    compileCastsTT<T, s32>();
    compileCastsTT<T, s64>();
    compileCastsTT<T, u8>();
    compileCastsTT<T, u16>();
    compileCastsTT<T, u32>();
    compileCastsTT<T, u64>();
    compileCastsTT<T, bool>();
}

static constexpr bool compileCasts()
{
    compileCastsT<f32>();
    compileCastsT<f64>();
    compileCastsT<s8>();
    compileCastsT<s16>();
    compileCastsT<s32>();
    compileCastsT<s64>();
    compileCastsT<u8>();
    compileCastsT<u16>();
    compileCastsT<u32>();
    compileCastsT<u64>();
    compileCastsT<bool>();

    return true;
}

template <typename T>
static constexpr void compileConstantsT()
{
    constexpr vec2<T> px2{qc::px2<T>};
    constexpr vec3<T> px3{qc::px3<T>};
    constexpr vec4<T> px4{qc::px4<T>};
    constexpr vec2<T> py2{qc::py2<T>};
    constexpr vec3<T> py3{qc::py3<T>};
    constexpr vec4<T> py4{qc::py4<T>};
    constexpr vec3<T> pz3{qc::pz3<T>};
    constexpr vec4<T> pz4{qc::pz4<T>};
    constexpr vec4<T> pw4{qc::pw4<T>};
    constexpr vec2<T> nx2{qc::nx2<T>};
    constexpr vec3<T> nx3{qc::nx3<T>};
    constexpr vec4<T> nx4{qc::nx4<T>};
    constexpr vec2<T> ny2{qc::ny2<T>};
    constexpr vec3<T> ny3{qc::ny3<T>};
    constexpr vec4<T> ny4{qc::ny4<T>};
    constexpr vec3<T> nz3{qc::nz3<T>};
    constexpr vec4<T> nz4{qc::nz4<T>};
    constexpr vec4<T> nw4{qc::nw4<T>};
}

static constexpr bool compileConstants()
{
    compileConstantsT<f32>();
    compileConstantsT<f64>();
    compileConstantsT<s8>();
    compileConstantsT<s16>();
    compileConstantsT<s32>();
    compileConstantsT<s64>();
    compileConstantsT<u8>();
    compileConstantsT<u16>();
    compileConstantsT<u32>();
    compileConstantsT<u64>();

    return true;
}

TEST(Vector, compilation)
{
    compileClasses();
    compileFunctions();
    testProperties();
    static_assert(compileCasts());
    static_assert(compileConstants());
}

template <typename T>
void testVectorConceptT()
{
    static_assert(Vector<vec2<T>>);
    static_assert(Vector<vec3<T>>);
    static_assert(Vector<vec4<T>>);

    static_assert(Vector2<vec2<T>>);
    static_assert(!Vector2<vec3<T>>);
    static_assert(!Vector2<vec4<T>>);

    static_assert(Vector3<vec3<T>>);
    static_assert(!Vector3<vec2<T>>);
    static_assert(!Vector3<vec4<T>>);

    static_assert(Vector4<vec4<T>>);
    static_assert(!Vector4<vec2<T>>);
    static_assert(!Vector4<vec3<T>>);
}

template <typename T>
void testFloaterVectorConceptT()
{
    static_assert(FloatingVector<vec2<T>>);
    static_assert(FloatingVector<vec3<T>>);
    static_assert(FloatingVector<vec4<T>>);
}

template <typename T>
void testIntegerVectorConceptT()
{
    static_assert(IntegralVector<vec2<T>>);
    static_assert(IntegralVector<vec3<T>>);
    static_assert(IntegralVector<vec4<T>>);
}

template <typename T>
void testSignedIntegerVectorConceptT()
{
    static_assert(SignedIntegralVector<vec2<T>>);
    static_assert(SignedIntegralVector<vec3<T>>);
    static_assert(SignedIntegralVector<vec4<T>>);
}

template <typename T>
void testUnsignedIntegerVectorConceptT()
{
    static_assert(UnsignedIntegralVector<vec2<T>>);
    static_assert(UnsignedIntegralVector<vec3<T>>);
    static_assert(UnsignedIntegralVector<vec4<T>>);
}

TEST(Vector, concepts)
{
    testVectorConceptT<s8>();
    testVectorConceptT<u8>();
    testVectorConceptT<s16>();
    testVectorConceptT<u16>();
    testVectorConceptT<f32>();
    testVectorConceptT<s32>();
    testVectorConceptT<u32>();
    testVectorConceptT<f64>();
    testVectorConceptT<s64>();
    testVectorConceptT<u64>();
    testVectorConceptT<bool>();
    static_assert(!Vector<int>);

    testFloaterVectorConceptT<f32>();
    testFloaterVectorConceptT<f64>();
    static_assert(!FloatingVector<ivec2>);

    testIntegerVectorConceptT<s8>();
    testIntegerVectorConceptT<u8>();
    testIntegerVectorConceptT<s16>();
    testIntegerVectorConceptT<u16>();
    testIntegerVectorConceptT<s32>();
    testIntegerVectorConceptT<u32>();
    testIntegerVectorConceptT<s64>();
    testIntegerVectorConceptT<u64>();
    static_assert(!IntegralVector<fvec2>);

    testSignedIntegerVectorConceptT<s8>();
    testSignedIntegerVectorConceptT<s16>();
    testSignedIntegerVectorConceptT<s32>();
    testSignedIntegerVectorConceptT<s64>();
    static_assert(!SignedIntegralVector<uivec2>);

    testUnsignedIntegerVectorConceptT<u8>();
    testUnsignedIntegerVectorConceptT<u16>();
    testUnsignedIntegerVectorConceptT<u32>();
    testUnsignedIntegerVectorConceptT<u64>();
    static_assert(!UnsignedIntegralVector<ivec2>);

    static_assert(BooleanVector<bvec2>);
    static_assert(BooleanVector<bvec3>);
    static_assert(BooleanVector<bvec4>);
    static_assert(!BooleanVector<fvec2>);
}
#pragma warning(pop)
