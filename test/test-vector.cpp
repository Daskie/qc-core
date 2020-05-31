#include <sstream>

#include <qc-core/vector-ext.hpp>

template <typename T>
static void compileClassesT() {
    T v{};
    qc::core::vec2<T> v2;
    qc::core::vec3<T> v3;
    qc::core::vec4<T> v4;

    //--------------------------------------------------------------------------
    // Vec2

    // constructors
    qc::core::vec2<T> v2_01;
    qc::core::vec2<T> v2_02(v2);
    qc::core::vec2<T> v2_03(std::move(v2));
    qc::core::vec2<T> v2_04(v);
    qc::core::vec2<T> v2_06(v3);
    qc::core::vec2<T> v2_07(v4);
    qc::core::vec2<T> v2_08(v, v);

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
    qc::core::vec3<T> v3_01;
    qc::core::vec3<T> v3_02(v3);
    qc::core::vec3<T> v3_03(std::move(v3));
    qc::core::vec3<T> v3_04(v);
    qc::core::vec3<T> v3_06(v2);
    qc::core::vec3<T> v3_07(v4);
    qc::core::vec3<T> v3_08(v, v, v);
    qc::core::vec3<T> v3_16(v2, v);
    qc::core::vec3<T> v3_18(v, v2);

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

    v3.xy(); v3.rg(); v3.st();
    v3.yz(); v3.gb(); v3.tp();

    //--------------------------------------------------------------------------
    // Vec4

    // constructors
    qc::core::vec4<T> v4_01;
    qc::core::vec4<T> v4_02(v4);
    qc::core::vec4<T> v4_03(std::move(v4));
    qc::core::vec4<T> v4_04(v);
    qc::core::vec4<T> v4_06(v2);
    qc::core::vec4<T> v4_07(v3);
    qc::core::vec4<T> v4_08(v, v, v, v);
    qc::core::vec4<T> v4_23(v2, v, v);
    qc::core::vec4<T> v4_27(v, v2, v);
    qc::core::vec4<T> v4_31(v, v, v2);
    qc::core::vec4<T> v4_35(v2, v2);
    qc::core::vec4<T> v4_36(v3, v);
    qc::core::vec4<T> v4_38(v, v3);

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

    v4.xy(); v4.rg(); v4.st();
    v4.yz(); v4.gb(); v4.tp();
    v4.zw(); v4.ba(); v4.pq();
    v4.xyz(); v4.rgb(); v4.stp();
    v4.yzw(); v4.gba(); v4.tpq();
}

static void compileClasses() {
    compileClassesT<qc::core::f32>();
    compileClassesT<qc::core::f64>();
    compileClassesT<qc::core::s08>();
    compileClassesT<qc::core::s16>();
    compileClassesT<qc::core::s32>();
    compileClassesT<qc::core::s64>();
    compileClassesT<qc::core::u08>();
    compileClassesT<qc::core::u16>();
    compileClassesT<qc::core::u32>();
    compileClassesT<qc::core::u64>();
}

template <typename T>
static constexpr void compileClassesConstexprT() {
    constexpr T v{};
    constexpr qc::core::vec2<T> v2;
    constexpr qc::core::vec3<T> v3;
    constexpr qc::core::vec4<T> v4;

    //--------------------------------------------------------------------------
    // Vec2

    // constructors
    constexpr qc::core::vec2<T> v2_01;
    constexpr qc::core::vec2<T> v2_02(v2);
    constexpr qc::core::vec2<T> v2_03(std::move(v2));
    constexpr qc::core::vec2<T> v2_04(v);
    constexpr qc::core::vec2<T> v2_06(v3);
    constexpr qc::core::vec2<T> v2_07(v4);
    constexpr qc::core::vec2<T> v2_08(v, v);

    // Conversion
    static_cast<bool>(v2);

    // access
    v2.at<0>();
    v2.at<1>();

    //--------------------------------------------------------------------------
    // Vec3

    // constructors
    constexpr qc::core::vec3<T> v3_01;
    constexpr qc::core::vec3<T> v3_02(v3);
    constexpr qc::core::vec3<T> v3_03(std::move(v3));
    constexpr qc::core::vec3<T> v3_04(v);
    constexpr qc::core::vec3<T> v3_06(v2);
    constexpr qc::core::vec3<T> v3_07(v4);
    constexpr qc::core::vec3<T> v3_08(v, v, v);
    constexpr qc::core::vec3<T> v3_16(v2, v);
    //constexpr qc::core::vec3<T> v3_18(v, v2);

    // Conversion
    static_cast<bool>(v3);

    // access
    v3.at<0>();
    v3.at<1>();
    v3.at<2>();

    //v3.xy(); v3.rg(); v3.st();
    //v3.yz(); v3.gb(); v3.tp();

    //--------------------------------------------------------------------------
    // Vec4

    // constructors
    constexpr qc::core::vec4<T> v4_01;
    constexpr qc::core::vec4<T> v4_02(v4);
    constexpr qc::core::vec4<T> v4_03(std::move(v4));
    constexpr qc::core::vec4<T> v4_04(v);
    constexpr qc::core::vec4<T> v4_06(v2);
    constexpr qc::core::vec4<T> v4_07(v3);
    constexpr qc::core::vec4<T> v4_08(v, v, v, v);
    constexpr qc::core::vec4<T> v4_23(v2, v, v);
    //constexpr qc::core::vec4<T> v4_27(v, v2, v);
    //constexpr qc::core::vec4<T> v4_31(v, v, v2);
    constexpr qc::core::vec4<T> v4_35(v2, v2);
    constexpr qc::core::vec4<T> v4_36(v3, v);
    //constexpr qc::core::vec4<T> v4_38(v, v3);

    // Conversion
    static_cast<bool>(v4);

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
}

static constexpr bool compileClassesConstexpr() {
    compileClassesConstexprT<qc::core::f32>();
    compileClassesConstexprT<qc::core::f64>();
    compileClassesConstexprT<qc::core::s08>();
    compileClassesConstexprT<qc::core::s16>();
    compileClassesConstexprT<qc::core::s32>();
    compileClassesConstexprT<qc::core::s64>();
    compileClassesConstexprT<qc::core::u08>();
    compileClassesConstexprT<qc::core::u16>();
    compileClassesConstexprT<qc::core::u32>();
    compileClassesConstexprT<qc::core::u64>();

    return true;
}

template <typename T1, typename T2>
static void compileFunctionsTT() {
    T1 v; v;
    qc::core::vec2<T1> v2; v2;
    qc::core::vec3<T1> v3; v3;
    qc::core::vec4<T1> v4; v4;

    qc::core::transnorm<T2>(v2);
    qc::core::transnorm<T2>(v3);
    qc::core::transnorm<T2>(v4);
}

template <typename T>
static void compileFunctionsT() {
    compileFunctionsTT<T, qc::core::f32>();
    compileFunctionsTT<T, qc::core::f64>();
    compileFunctionsTT<T, qc::core::s08>();
    compileFunctionsTT<T, qc::core::s16>();
    compileFunctionsTT<T, qc::core::s32>();
    compileFunctionsTT<T, qc::core::s64>();
    compileFunctionsTT<T, qc::core::u08>();
    compileFunctionsTT<T, qc::core::u16>();
    compileFunctionsTT<T, qc::core::u32>();
    compileFunctionsTT<T, qc::core::u64>();

    T v{};
    qc::core::vec2<T> v2;
    qc::core::vec3<T> v3;
    qc::core::vec4<T> v4;
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

    v2 /= qc::core::vec2<T>(T(1));
    v3 /= qc::core::vec3<T>(T(1));
    v4 /= qc::core::vec4<T>(T(1));
    v2 /= T(1);
    v3 /= T(1);
    v4 /= T(1);

    v2 %= qc::core::vec2<T>(T(1));
    v3 %= qc::core::vec3<T>(T(1));
    v4 %= qc::core::vec4<T>(T(1));
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

    v2 / qc::core::vec2<T>(T(1));
    v3 / qc::core::vec3<T>(T(1));
    v4 / qc::core::vec4<T>(T(1));
    v2 / T(1);
    v3 / T(1);
    v4 / T(1);
    v / qc::core::vec2<T>(T(1));
    v / qc::core::vec3<T>(T(1));
    v / qc::core::vec4<T>(T(1));

    v2 % qc::core::vec2<T>(T(1));
    v3 % qc::core::vec3<T>(T(1));
    v4 % qc::core::vec4<T>(T(1));
    v2 % T(1);
    v3 % T(1);
    v4 % T(1);
    v % qc::core::vec2<T>(T(1));
    v % qc::core::vec3<T>(T(1));
    v % qc::core::vec4<T>(T(1));


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
    qc::core::vec2<T> v2;
    qc::core::vec3<T> v3;
    qc::core::vec4<T> v4;

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
}

template <typename T>
static void compileFunctionsIT() {
    T v{}; v;
    qc::core::vec2<T> v2; v2;
    qc::core::vec3<T> v3; v3;
    qc::core::vec4<T> v4; v4;
}

template <typename T>
static void compileFunctionsUIT() {
    T v{}; v;
    qc::core::vec2<T> v2; v2;
    qc::core::vec3<T> v3; v3;
    qc::core::vec4<T> v4; v4;

    qc::core::mipmaps(v2);
    qc::core::mipmaps(v3);
    qc::core::mipmaps(v4);
}

static void compileFunctionsBT() {
    qc::core::bvec2 b2;
    qc::core::bvec3 b3;
    qc::core::bvec4 b4;

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
    compileFunctionsT<qc::core::f32>();
    compileFunctionsT<qc::core::f64>();
    compileFunctionsT<qc::core::s08>();
    compileFunctionsT<qc::core::s16>();
    compileFunctionsT<qc::core::s32>();
    compileFunctionsT<qc::core::s64>();
    compileFunctionsT<qc::core::u08>();
    compileFunctionsT<qc::core::u16>();
    compileFunctionsT<qc::core::u32>();
    compileFunctionsT<qc::core::u64>();

    compileFunctionsFT<qc::core::f32>();
    compileFunctionsFT<qc::core::f64>();

    compileFunctionsIT<qc::core::s08>();
    compileFunctionsIT<qc::core::s16>();
    compileFunctionsIT<qc::core::s32>();
    compileFunctionsIT<qc::core::s64>();
    compileFunctionsIT<qc::core::u08>();
    compileFunctionsIT<qc::core::u16>();
    compileFunctionsIT<qc::core::u32>();
    compileFunctionsIT<qc::core::u64>();

    compileFunctionsBT();
}

template <typename T1, typename T2>
static constexpr void compileFunctionsConstexprTT() {
    constexpr T1 v(T1(1.0));
    constexpr qc::core::vec2<T1> v2(T1(1.0));
    constexpr qc::core::vec3<T1> v3(T1(1.0));
    constexpr qc::core::vec4<T1> v4(T1(1.0));


}

template <typename T>
static constexpr void compileFunctionsConstexprT() {
    compileFunctionsConstexprTT<T, qc::core::f32>();
    compileFunctionsConstexprTT<T, qc::core::f64>();
    compileFunctionsConstexprTT<T, qc::core::s08>();
    compileFunctionsConstexprTT<T, qc::core::s16>();
    compileFunctionsConstexprTT<T, qc::core::s32>();
    compileFunctionsConstexprTT<T, qc::core::s64>();
    compileFunctionsConstexprTT<T, qc::core::u08>();
    compileFunctionsConstexprTT<T, qc::core::u16>();
    compileFunctionsConstexprTT<T, qc::core::u32>();
    compileFunctionsConstexprTT<T, qc::core::u64>();

    constexpr T v{1.0};
    constexpr qc::core::vec2<T> v2(T(1.0));
    constexpr qc::core::vec3<T> v3(T(1.0));
    constexpr qc::core::vec4<T> v4(T(1.0));

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

    //v2 / qc::core::vec2<T>(1);
    //v3 / qc::core::vec3<T>(1);
    //v4 / qc::core::vec4<T>(1);
    //v2 / T(v);
    //v3 / T(v);
    //v4 / T(v);
    //v / qc::core::vec2<T>(1);
    //v / qc::core::vec3<T>(1);
    //v / qc::core::vec4<T>(1);

    //v2 % qc::core::vec2<T>(1);
    //v3 % qc::core::vec3<T>(1);
    //v4 % qc::core::vec4<T>(1);
    //v2 % T(v);
    //v3 % T(v);
    //v4 % T(v);
    //v % qc::core::vec2<T>(1);
    //v % qc::core::vec3<T>(1);
    //v % qc::core::vec4<T>(1);


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
    constexpr qc::core::vec2<T> v2(T(1.0));
    constexpr qc::core::vec3<T> v3(T(1.0));
    constexpr qc::core::vec4<T> v4(T(1.0));

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
    constexpr qc::core::vec2<T> v2(T(1.0));
    constexpr qc::core::vec3<T> v3(T(1.0));
    constexpr qc::core::vec4<T> v4(T(1.0));

    //qc::core::mipmaps(v2);
    //qc::core::mipmaps(v3);
    //qc::core::mipmaps(v4);
}

static constexpr void compileBoolFunctionsConstexpr() {
    qc::core::bvec2 b2;
    qc::core::bvec3 b3;
    qc::core::bvec4 b4;

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
    compileFunctionsConstexprT<qc::core::f32>();
    compileFunctionsConstexprT<qc::core::f64>();
    compileBoolFunctionsConstexpr();

    return true;
}

template <typename T, int n>
static void testPropertiesTN() {
    static_assert(std::is_standard_layout_v<qc::core::vec<T, n>>);
    static_assert(std::is_trivially_copyable_v<qc::core::vec<T, n>>);
    static_assert(std::is_trivially_copy_constructible_v<qc::core::vec<T, n>>);
    static_assert(std::is_trivially_move_constructible_v<qc::core::vec<T, n>>);
    static_assert(std::is_trivially_copy_assignable_v<qc::core::vec<T, n>>);
    static_assert(std::is_trivially_move_assignable_v<qc::core::vec<T, n>>);
    static_assert(std::is_trivially_destructible_v<qc::core::vec<T, n>>);
    static_assert(sizeof(qc::core::vec<T, n>) == n * sizeof(T));
    static_assert(sizeof(qc::core::vec<T, n>[4]) == 4 * n * sizeof(T));
    static_assert(alignof(qc::core::vec<T, n>) == alignof(T));
    static_assert(alignof(qc::core::vec<T, n>[4]) == alignof(T));
}

template <typename T>
static void testPropertiesT() {
    testPropertiesTN<T, 2>();
    testPropertiesTN<T, 3>();
    testPropertiesTN<T, 4>();
}

static void testProperties() {
    testPropertiesT<qc::core::f32>();
    testPropertiesT<qc::core::f64>();
    testPropertiesT<qc::core::s08>();
    testPropertiesT<qc::core::s16>();
    testPropertiesT<qc::core::s32>();
    testPropertiesT<qc::core::s64>();
    testPropertiesT<qc::core::u08>();
    testPropertiesT<qc::core::u16>();
    testPropertiesT<qc::core::u32>();
    testPropertiesT<qc::core::u64>();
}

template <typename T1, typename T2, int n>
static constexpr void compileVecCastsTTN() {
    qc::core::vec2<T1> v2;
    qc::core::vec2<T1> v3;
    qc::core::vec2<T1> v4;

    { qc::core::vec<T2, n> v(v2); }
    { qc::core::vec<T2, n> v(v3); }
    { qc::core::vec<T2, n> v(v4); }

    static_cast<qc::core::vec<T2, n>>(v2);
    static_cast<qc::core::vec<T2, n>>(v3);
    static_cast<qc::core::vec<T2, n>>(v4);
}

template <typename T1, typename T2>
static constexpr void compileCastsTT() {
    compileVecCastsTTN<T1, T2, 2>();
    compileVecCastsTTN<T1, T2, 3>();
    compileVecCastsTTN<T1, T2, 4>();
}

template <typename T>
static constexpr void compileCastsT() {
    compileCastsTT<T, qc::core::f32>();
    compileCastsTT<T, qc::core::f64>();
    compileCastsTT<T, qc::core::s08>();
    compileCastsTT<T, qc::core::s16>();
    compileCastsTT<T, qc::core::s32>();
    compileCastsTT<T, qc::core::s64>();
    compileCastsTT<T, qc::core::u08>();
    compileCastsTT<T, qc::core::u16>();
    compileCastsTT<T, qc::core::u32>();
    compileCastsTT<T, qc::core::u64>();
}

static constexpr bool compileCasts() {
    compileCastsT<qc::core::f32>();
    compileCastsT<qc::core::f64>();
    compileCastsT<qc::core::s08>();
    compileCastsT<qc::core::s16>();
    compileCastsT<qc::core::s32>();
    compileCastsT<qc::core::s64>();
    compileCastsT<qc::core::u08>();
    compileCastsT<qc::core::u16>();
    compileCastsT<qc::core::u32>();
    compileCastsT<qc::core::u64>();

    return true;
}

template <typename T>
static constexpr void compileConstantsT() {
    constexpr qc::core::vec2<T> px2(qc::core::px2<T>);
    constexpr qc::core::vec3<T> px3(qc::core::px3<T>);
    constexpr qc::core::vec4<T> px4(qc::core::px4<T>);
    constexpr qc::core::vec2<T> py2(qc::core::py2<T>);
    constexpr qc::core::vec3<T> py3(qc::core::py3<T>);
    constexpr qc::core::vec4<T> py4(qc::core::py4<T>);
    constexpr qc::core::vec3<T> pz3(qc::core::pz3<T>);
    constexpr qc::core::vec4<T> pz4(qc::core::pz4<T>);
    constexpr qc::core::vec4<T> pw4(qc::core::pw4<T>);
    constexpr qc::core::vec2<T> nx2(qc::core::nx2<T>);
    constexpr qc::core::vec3<T> nx3(qc::core::nx3<T>);
    constexpr qc::core::vec4<T> nx4(qc::core::nx4<T>);
    constexpr qc::core::vec2<T> ny2(qc::core::ny2<T>);
    constexpr qc::core::vec3<T> ny3(qc::core::ny3<T>);
    constexpr qc::core::vec4<T> ny4(qc::core::ny4<T>);
    constexpr qc::core::vec3<T> nz3(qc::core::nz3<T>);
    constexpr qc::core::vec4<T> nz4(qc::core::nz4<T>);
    constexpr qc::core::vec4<T> nw4(qc::core::nw4<T>);
}

template <typename T>
static constexpr void compileConstantsFT() {
    constexpr qc::core::vec2<T> iv2(qc::core::infvec<T, 2>);
    constexpr qc::core::vec3<T> iv3(qc::core::infvec<T, 3>);
    constexpr qc::core::vec4<T> iv4(qc::core::infvec<T, 4>);

    constexpr qc::core::vec2<T> nv2(qc::core::nanvec<T, 2>);
    constexpr qc::core::vec3<T> nv3(qc::core::nanvec<T, 3>);
    constexpr qc::core::vec4<T> nv4(qc::core::nanvec<T, 4>);
}

static constexpr bool compileConstants() {
    compileConstantsT<qc::core::f32>();
    compileConstantsT<qc::core::f64>();
    compileConstantsT<qc::core::s08>();
    compileConstantsT<qc::core::s16>();
    compileConstantsT<qc::core::s32>();
    compileConstantsT<qc::core::s64>();
    compileConstantsT<qc::core::u08>();
    compileConstantsT<qc::core::u16>();
    compileConstantsT<qc::core::u32>();
    compileConstantsT<qc::core::u64>();

    compileConstantsFT<qc::core::f32>();
    compileConstantsFT<qc::core::f64>();

    return true;
}

void testVector() {
    compileClasses();
    static_assert(compileClassesConstexpr());
    compileFunctions();
    static_assert(compileFunctionsConstexpr());
    testProperties();
    static_assert(compileCasts());
    static_assert(compileConstants());
}
