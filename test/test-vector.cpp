#include <sstream>

#include <qc-core/vector-func.hpp>

template <typename T>
static void compileClassesT() {
    T v{};
    qc::vec2<T> v2;
    qc::vec3<T> v3;
    qc::vec4<T> v4;

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
}

static void compileClasses() {
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
static constexpr void compileClassesConstexprT() {
    constexpr T v{};
    constexpr qc::vec2<T> v2;
    constexpr qc::vec3<T> v3;
    constexpr qc::vec4<T> v4;

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
}

static constexpr bool compileClassesConstexpr() {
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
static void compileFunctionsTT() {
    T1 v; v;
    qc::vec2<T1> v2; v2;
    qc::vec3<T1> v3; v3;
    qc::vec4<T1> v4; v4;

    qc::transnorm<T2>(v2);
    qc::transnorm<T2>(v3);
    qc::transnorm<T2>(v4);
}

template <typename T>
static void compileFunctionsT() {
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

    v2 / qc::vec2<T>(T(1));
    v3 / qc::vec3<T>(T(1));
    v4 / qc::vec4<T>(T(1));
    v2 / T(1);
    v3 / T(1);
    v4 / T(1);
    v / qc::vec2<T>(T(1));
    v / qc::vec3<T>(T(1));
    v / qc::vec4<T>(T(1));

    v2 % qc::vec2<T>(T(1));
    v3 % qc::vec3<T>(T(1));
    v4 % qc::vec4<T>(T(1));
    v2 % T(1);
    v3 % T(1);
    v4 % T(1);
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

    qc::abs(v2);
    qc::abs(v3);
    qc::abs(v4);

    qc::zero(v2);
    qc::zero(v3);
    qc::zero(v4);

    qc::equal(v2, v2, v2, v2, v2);
    qc::equal(v3, v3, v3, v3, v3);
    qc::equal(v4, v4, v4, v4, v4);

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
}

template <typename T>
static void compileFunctionsFT() {
    T v{1};
    qc::vec2<T> v2;
    qc::vec3<T> v3;
    qc::vec4<T> v4;

    qc::equal_e(v2, v);
    qc::equal_e(v3, v);
    qc::equal_e(v4, v);
    qc::equal_e(v2, v2, v);
    qc::equal_e(v3, v3, v);
    qc::equal_e(v4, v4, v);

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

    qc::smoothstep(v2, v2, v);
    qc::smoothstep(v3, v3, v);
    qc::smoothstep(v4, v4, v);
}

template <typename T>
static void compileFunctionsIT() {
    T v{}; v;
    qc::vec2<T> v2; v2;
    qc::vec3<T> v3; v3;
    qc::vec4<T> v4; v4;
}

template <typename T>
static void compileFunctionsUIT() {
    T v{}; v;
    qc::vec2<T> v2; v2;
    qc::vec3<T> v3; v3;
    qc::vec4<T> v4; v4;

    qc::mipmaps(v2);
    qc::mipmaps(v3);
    qc::mipmaps(v4);
}

static void compileFunctionsBT() {
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

static void compileFunctions() {
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
static constexpr void compileFunctionsConstexprTT() {
    constexpr T1 v(T1(1.0));
    constexpr qc::vec2<T1> v2(T1(1.0));
    constexpr qc::vec3<T1> v3(T1(1.0));
    constexpr qc::vec4<T1> v4(T1(1.0));


}

template <typename T>
static constexpr void compileFunctionsConstexprT() {
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

    //qc::min(v2, v2, v2);
    //qc::min(v3, v3, v3);
    //qc::min(v4, v4, v4);

    //qc::min(v2, v2, v2, v2);
    //qc::min(v3, v3, v3, v3);
    //qc::min(v4, v4, v4, v4);

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

    //qc::max(v2, v2, v2);
    //qc::max(v3, v3, v3);
    //qc::max(v4, v4, v4);

    //qc::max(v2, v2, v2, v2);
    //qc::max(v3, v3, v3, v3);
    //qc::max(v4, v4, v4, v4);

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

    //qc::abs(v2);
    //qc::abs(v3);
    //qc::abs(v4);

    //qc::zero(v2);
    //qc::zero(v3);
    //qc::zero(v4);

    //qc::equal(v2, v2, v2, v2, v2);
    //qc::equal(v3, v3, v3, v3, v3);
    //qc::equal(v4, v4, v4, v4, v4);

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
}

template <typename T>
static constexpr void compileFunctionsConstexprFT() {
    constexpr T v{1.0};
    constexpr qc::vec2<T> v2(T(1.0));
    constexpr qc::vec3<T> v3(T(1.0));
    constexpr qc::vec4<T> v4(T(1.0));

    //qc::equal_e(v2);
    //qc::equal_e(v3);
    //qc::equal_e(v4);
    //qc::equal_e(v2, v);
    //qc::equal_e(v3, v);
    //qc::equal_e(v4, v);

    //qc::equal_e(v2, v2);
    //qc::equal_e(v3, v3);
    //qc::equal_e(v4, v4);
    //qc::equal_e(v2, v2, v);
    //qc::equal_e(v3, v3, v);
    //qc::equal_e(v4, v4, v);

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

    //qc::smoothstep(v2, v2, v);
    //qc::smoothstep(v3, v3, v);
    //qc::smoothstep(v4, v4, v);
}

template <typename T>
static constexpr void compileFunctionsConstexprIT() {
    constexpr T v{1.0};
    constexpr qc::vec2<T> v2(T(1.0));
    constexpr qc::vec3<T> v3(T(1.0));
    constexpr qc::vec4<T> v4(T(1.0));

    //qc::mipmaps(v2);
    //qc::mipmaps(v3);
    //qc::mipmaps(v4);
}

static constexpr void compileBoolFunctionsConstexpr() {
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

static constexpr bool compileFunctionsConstexpr() {
    compileFunctionsConstexprT<qc::f32>();
    compileFunctionsConstexprT<qc::f64>();
    compileBoolFunctionsConstexpr();

    return true;
}

template <typename T, int t_n>
static void testPropertiesTN() {
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
}

template <typename T>
static void testPropertiesT() {
    testPropertiesTN<T, 2>();
    testPropertiesTN<T, 3>();
    testPropertiesTN<T, 4>();
}

static void testProperties() {
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
static constexpr void compileVecCastsTTN() {
    qc::vec2<T1> v2;
    qc::vec2<T1> v3;
    qc::vec2<T1> v4;

    { qc::vec<T2, t_n> v(v2); }
    { qc::vec<T2, t_n> v(v3); }
    { qc::vec<T2, t_n> v(v4); }

    static_cast<qc::vec<T2, t_n>>(v2);
    static_cast<qc::vec<T2, t_n>>(v3);
    static_cast<qc::vec<T2, t_n>>(v4);
}

template <typename T1, typename T2>
static constexpr void compileCastsTT() {
    compileVecCastsTTN<T1, T2, 2>();
    compileVecCastsTTN<T1, T2, 3>();
    compileVecCastsTTN<T1, T2, 4>();
}

template <typename T>
static constexpr void compileCastsT() {
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

static constexpr bool compileCasts() {
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

template <typename T>
static constexpr void compileConstantsT() {
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
}

template <typename T>
static constexpr void compileConstantsFT() {
    constexpr qc::vec2<T> iv2(qc::infvec<T, 2>);
    constexpr qc::vec3<T> iv3(qc::infvec<T, 3>);
    constexpr qc::vec4<T> iv4(qc::infvec<T, 4>);

    constexpr qc::vec2<T> nv2(qc::nanvec<T, 2>);
    constexpr qc::vec3<T> nv3(qc::nanvec<T, 3>);
    constexpr qc::vec4<T> nv4(qc::nanvec<T, 4>);
}

static constexpr bool compileConstants() {
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
