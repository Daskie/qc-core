#include <sstream>

#include <gtest/gtest.h>

#include <qc-core/span-ext.hpp>

template <typename T>
static void compileClassesT()
{
    T v{};
    qc::vec2<T> v2{};
    qc::vec3<T> v3{};
    qc::vec4<T> v4{};
    qc::span1<T> s1{};
    qc::span2<T> s2{};
    qc::span3<T> s3{};
    qc::span4<T> s4{};

    //--------------------------------------------------------------------------
    // Span1

    // constructors
    qc::span<T, 1> s1_1{};
    qc::span<T, 1> s1_2{s1};
    qc::span<T, 1> s1_3{std::move(s1)};
    qc::span<T, 1> s1_4{v, v};

    // assignment operators
    s1 = s1;
    s1 = std::move(s1);

    // other
    s1.size();
    s1.contains(v);

    //--------------------------------------------------------------------------
    // Span2

    // constructors
    qc::span<T, 2> s2_1{};
    qc::span<T, 2> s2_2{s2};
    qc::span<T, 2> s2_3{std::move(s2)};
    qc::span<T, 2> s2_4{v2, v2};
    qc::span<T, 2> s2_5{v, v};
    qc::span<T, 2> s2_6{s1, s1};

    // assignment operators
    s2 = s2;
    s2 = std::move(s2);

    // other
    s2.size();
    s2.x();
    s2.y();

    //--------------------------------------------------------------------------
    // Span3

    // constructors
    qc::span<T, 3> s3_1{};
    qc::span<T, 3> s3_2{s3};
    qc::span<T, 3> s3_3{std::move(s3)};
    qc::span<T, 3> s3_4{v3, v3};
    qc::span<T, 3> s3_5{v, v};
    qc::span<T, 3> s3_6{s1, s1, s1};
    qc::span<T, 3> s3_7{s2, s1};
    qc::span<T, 3> s3_8{s1, s2};

    // assignment operators
    s3 = s3;
    s3 = std::move(s3);

    // other
    s3.size();
    s3.contains(v3);
    s3.x();
    s3.y();
    s3.z();
    s3.xy();
    s3.yz();

    //--------------------------------------------------------------------------
    // Span4

    // constructors
    qc::span<T, 4> s4_1{};
    qc::span<T, 4> s4_2{s4};
    qc::span<T, 4> s4_3{std::move(s4)};
    qc::span<T, 4> s4_4{v4, v4};
    qc::span<T, 4> s4_5{v, v};
    qc::span<T, 4> s4_6{s1, s1, s1, s1};
    qc::span<T, 4> s4_7{s2, s1, s1};
    qc::span<T, 4> s4_8{s1, s2, s1};
    qc::span<T, 4> s4_9{s1, s1, s2};
    qc::span<T, 4> s4_10{s2, s2};
    qc::span<T, 4> s4_11{s3, s1};
    qc::span<T, 4> s4_12{s1, s3};

    // assignment operators
    s4 = s4;
    s4 = std::move(s4);

    // other
    s4.size();
    s4.contains(v4);
    s4.x();
    s4.y();
    s4.z();
    s4.w();
    s4.xy();
    s4.yz();
    s4.xyz();
    s4.yzw();
}

template <typename T>
static void compileClassesPT()
{
    using P = T *;
    P p{};
    qc::span1<P> s1{};

    // constructors
    qc::span<P, 1> s1_1{};
    qc::span<P, 1> s1_2{s1};
    qc::span<P, 1> s1_3{std::move(s1)};
    qc::span<P, 1> s1_4{p, p};

    // assignment operators
    s1 = s1;
    s1 = std::move(s1);

    // other
    s1.size();
}

static void compileClasses()
{
    compileClassesT<qc::f32>();
    compileClassesT<qc::f64>();
    compileClassesT<qc::s8>();
    compileClassesT<qc::s16>();
    compileClassesT<qc::s32>();
    compileClassesT<qc::s64>();
    compileClassesT<qc::u8>();
    compileClassesT<qc::u16>();
    compileClassesT<qc::u32>();
    compileClassesT<qc::u64>();

    compileClassesPT<std::byte>();
}

template <typename T>
static void compileFunctionsT()
{
    T v{1};
    qc::vec2<T> v2{v};
    qc::vec3<T> v3{v};
    qc::vec4<T> v4{v};
    qc::span1<T> s1{v, v};
    qc::span2<T> s2{v, v};
    qc::span3<T> s3{v, v};
    qc::span4<T> s4{v, v};
    std::stringstream os;

    s1 += v;
    s2 += v;
    s3 += v;
    s4 += v;

    s2 += v2;
    s3 += v3;
    s4 += v4;

    s1 -= v;
    s2 -= v;
    s3 -= v;
    s4 -= v;

    s2 -= v2;
    s3 -= v3;
    s4 -= v4;

    s1 *= v;
    s2 *= v;
    s3 *= v;
    s4 *= v;

    s2 *= v2;
    s3 *= v3;
    s4 *= v4;

    s1 /= v;
    s2 /= v;
    s3 /= v;
    s4 /= v;

    s2 /= v2;
    s3 /= v3;
    s4 /= v4;

    s1 &= s1;
    s2 &= s2;
    s3 &= s3;
    s4 &= s4;

    s1 |= s1;
    s2 |= s2;
    s3 |= s3;
    s4 |= s4;

    s1 + v;
    s2 + v;
    s3 + v;
    s4 + v;

    s2 + v2;
    s3 + v3;
    s4 + v4;

    v + s1;
    v + s2;
    v + s3;
    v + s4;

    v2 + s2;
    v3 + s3;
    v4 + s4;

    s1 - v;
    s2 - v;
    s3 - v;
    s4 - v;

    s2 - v2;
    s3 - v3;
    s4 - v4;

    v - s1;
    v - s2;
    v - s3;
    v - s4;

    v2 - s2;
    v3 - s3;
    v4 - s4;

    s1 * v;
    s2 * v;
    s3 * v;
    s4 * v;

    s2 * v2;
    s3 * v3;
    s4 * v4;

    v * s1;
    v * s2;
    v * s3;
    v * s4;

    v2 * s2;
    v3 * s3;
    v4 * s4;

    s1 / v;
    s2 / v;
    s3 / v;
    s4 / v;

    s2 / v2;
    s3 / v3;
    s4 / v4;

    s1 == s1;
    s2 == s2;
    s3 == s3;
    s4 == s4;

    s1 != s1;
    s2 != s2;
    s3 != s3;
    s4 != s4;

    s1 & s1;
    s2 & s2;
    s3 & s3;
    s4 & s4;

    s1 | s1;
    s2 | s2;
    s3 | s3;
    s4 | s4;

    os << s1;
    os << s2;
    os << s3;
    os << s4;

    qc::min(s1, v);
    qc::min(s2, v);
    qc::min(s2, v2);
    qc::min(s3, v);
    qc::min(s3, v3);
    qc::min(s4, v);
    qc::min(s4, v4);

    qc::max(s1, v);
    qc::max(s2, v);
    qc::max(s2, v2);
    qc::max(s3, v);
    qc::max(s3, v3);
    qc::max(s4, v);
    qc::max(s4, v4);

    qc::minify(s1, v);
    qc::minify(s2, v);
    qc::minify(s2, v2);
    qc::minify(s3, v);
    qc::minify(s3, v3);
    qc::minify(s4, v);
    qc::minify(s4, v4);

    qc::maxify(s1, v);
    qc::maxify(s2, v);
    qc::maxify(s2, v2);
    qc::maxify(s3, v);
    qc::maxify(s3, v3);
    qc::maxify(s4, v);
    qc::maxify(s4, v4);

    qc::round(s1);
    qc::round(s2);
    qc::round(s3);
    qc::round(s4);

    qc::clamp(s1, v, v);
    qc::clamp(s2, v, v);
    qc::clamp(s3, v, v);
    qc::clamp(s4, v, v);
    qc::clamp(s2, v2, v2);
    qc::clamp(s3, v3, v3);
    qc::clamp(s4, v4, v4);
    qc::clamp(v, s1);
    qc::clamp(v2, s2);
    qc::clamp(v3, s3);
    qc::clamp(v4, s4);

    qc::clampify(s1, v, v);
    qc::clampify(s2, v, v);
    qc::clampify(s3, v, v);
    qc::clampify(s4, v, v);
    qc::clampify(s2, v2, v2);
    qc::clampify(s3, v3, v3);
    qc::clampify(s4, v4, v4);
    qc::clampify(v, s1);
    qc::clampify(v2, s2);
    qc::clampify(v3, s3);
    qc::clampify(v4, s4);
}

template <typename T>
static void compileFunctionsPT()
{
    using P = T *;
    P p{};
    intptr_t v{};
    qc::span1<P> s{p, p};
    std::stringstream os{};

    s += v;
    s -= v;
    s + v;
    s - v;
    s == s;
    s != s;
    os << s;
    qc::min(s, p);
    qc::max(s, p);
    qc::minify(s, p);
    qc::maxify(s, p);
}

static void compileFunctions()
{
    compileFunctionsT<qc::f32>();
    compileFunctionsT<qc::f64>();
    compileFunctionsT<qc::s8>();
    compileFunctionsT<qc::s16>();
    compileFunctionsT<qc::s32>();
    compileFunctionsT<qc::s64>();
    compileFunctionsT<qc::u8>();
    compileFunctionsT<qc::u16>();
    compileFunctionsT<qc::u32>();
    compileFunctionsT<qc::u64>();
}

template <typename T, int n>
static void testPropertiesTN()
{
    static_assert(std::is_standard_layout_v<qc::span<T, n>>);
    static_assert(std::is_trivially_default_constructible_v<qc::span<T, n>>);
    static_assert(std::is_trivially_copyable_v<qc::span<T, n>>);
    static_assert(std::is_trivially_copy_constructible_v<qc::span<T, n>>);
    static_assert(std::is_trivially_move_constructible_v<qc::span<T, n>>);
    static_assert(std::is_trivially_copy_assignable_v<qc::span<T, n>>);
    static_assert(std::is_trivially_move_assignable_v<qc::span<T, n>>);
    static_assert(std::is_trivially_destructible_v<qc::span<T, n>>);
    static_assert(sizeof(qc::span<T, n>) == 2 * n * sizeof(T));
    static_assert(sizeof(qc::span<T, n>[4]) == 4 * 2 * n * sizeof(T));
    static_assert(alignof(qc::span<T, n>) == alignof(T));
    static_assert(alignof(qc::span<T, n>[4]) == alignof(T));
}

template <typename T>
static void testPropertiesT()
{
    testPropertiesTN<T, 1>();
    testPropertiesTN<T, 2>();
    testPropertiesTN<T, 3>();
    testPropertiesTN<T, 4>();
}

static void testProperties()
{
    testPropertiesT<qc::f32>();
    testPropertiesT<qc::f64>();
    testPropertiesT<qc::s8>();
    testPropertiesT<qc::s16>();
    testPropertiesT<qc::s32>();
    testPropertiesT<qc::s64>();
    testPropertiesT<qc::u8>();
    testPropertiesT<qc::u16>();
    testPropertiesT<qc::u32>();
    testPropertiesT<qc::u64>();
}

template <typename T1, typename T2, int n>
static void compileCastsTTN()
{
    qc::span1<T1> s1{};
    qc::span2<T1> s2{};
    qc::span3<T1> s3{};
    qc::span4<T1> s4{};

    { qc::span<T2, n> s{s1}; }
    { qc::span<T2, n> s{s2}; }
    { qc::span<T2, n> s{s3}; }
    { qc::span<T2, n> s{s4}; }

    static_cast<qc::span<T2, n>>(s1);
    static_cast<qc::span<T2, n>>(s2);
    static_cast<qc::span<T2, n>>(s3);
    static_cast<qc::span<T2, n>>(s4);
}

template <typename T1, typename T2>
static void compileCastsTT()
{
    compileCastsTTN<T1, T2, 1>();
    compileCastsTTN<T1, T2, 2>();
    compileCastsTTN<T1, T2, 3>();
    compileCastsTTN<T1, T2, 4>();
}

template <typename T>
static void compileCastsT()
{
    compileCastsTT<T, qc::f32>();
    compileCastsTT<T, qc::f64>();
    compileCastsTT<T, qc::s8>();
    compileCastsTT<T, qc::s16>();
    compileCastsTT<T, qc::s32>();
    compileCastsTT<T, qc::s64>();
    compileCastsTT<T, qc::u8>();
    compileCastsTT<T, qc::u16>();
    compileCastsTT<T, qc::u32>();
    compileCastsTT<T, qc::u64>();
}

static void compileCasts()
{
    compileCastsT<qc::f32>();
    compileCastsT<qc::f64>();
    compileCastsT<qc::s8>();
    compileCastsT<qc::s16>();
    compileCastsT<qc::s32>();
    compileCastsT<qc::s64>();
    compileCastsT<qc::u8>();
    compileCastsT<qc::u16>();
    compileCastsT<qc::u32>();
    compileCastsT<qc::u64>();
}

template <typename T>
static void compileConstantsT()
{
    constexpr qc::span1<T> is1{qc::fullSpan<T, 1>};
    constexpr qc::span2<T> is2{qc::fullSpan<T, 2>};
    constexpr qc::span3<T> is3{qc::fullSpan<T, 3>};
    constexpr qc::span4<T> is4{qc::fullSpan<T, 4>};

    constexpr qc::span1<T> nulls1{qc::nullSpan<T, 1>};
    constexpr qc::span2<T> nulls2{qc::nullSpan<T, 2>};
    constexpr qc::span3<T> nulls3{qc::nullSpan<T, 3>};
    constexpr qc::span4<T> nulls4{qc::nullSpan<T, 4>};
}

static void compileConstants()
{
    compileConstantsT<qc::f32>();
    compileConstantsT<qc::f64>();
    compileConstantsT<qc::s8>();
    compileConstantsT<qc::s16>();
    compileConstantsT<qc::s32>();
    compileConstantsT<qc::s64>();
    compileConstantsT<qc::u8>();
    compileConstantsT<qc::u16>();
    compileConstantsT<qc::u32>();
    compileConstantsT<qc::u64>();
}

TEST(span, compilation)
{
    compileClasses();
    compileFunctions();
    testProperties();
    compileCasts();
    compileConstants();
}
