#include <qc-core/span-ext.hpp>

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
    span1<T> s1{};
    span2<T> s2{};
    span3<T> s3{};
    span4<T> s4{};

    //--------------------------------------------------------------------------
    // Span1

    // constructors
    span<T, 1> s1_1{};
    span<T, 1> s1_2{s1};
    span<T, 1> s1_3{std::move(s1)};
    span<T, 1> s1_4{v, v};

    // assignment operators
    s1 = s1;
    s1 = std::move(s1);

    // other
    s1.size();
    s1.contains(v);

    //--------------------------------------------------------------------------
    // Span2

    // constructors
    span<T, 2> s2_1{};
    span<T, 2> s2_2{s2};
    span<T, 2> s2_3{std::move(s2)};
    span<T, 2> s2_4{v2, v2};
    span<T, 2> s2_5{v, v};
    span<T, 2> s2_6{s1, s1};

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
    span<T, 3> s3_1{};
    span<T, 3> s3_2{s3};
    span<T, 3> s3_3{std::move(s3)};
    span<T, 3> s3_4{v3, v3};
    span<T, 3> s3_5{v, v};
    span<T, 3> s3_6{s1, s1, s1};
    span<T, 3> s3_7{s2, s1};
    span<T, 3> s3_8{s1, s2};

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
    span<T, 4> s4_1{};
    span<T, 4> s4_2{s4};
    span<T, 4> s4_3{std::move(s4)};
    span<T, 4> s4_4{v4, v4};
    span<T, 4> s4_5{v, v};
    span<T, 4> s4_6{s1, s1, s1, s1};
    span<T, 4> s4_7{s2, s1, s1};
    span<T, 4> s4_8{s1, s2, s1};
    span<T, 4> s4_9{s1, s1, s2};
    span<T, 4> s4_10{s2, s2};
    span<T, 4> s4_11{s3, s1};
    span<T, 4> s4_12{s1, s3};

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
    span1<P> s1{};

    // constructors
    span<P, 1> s1_1{};
    span<P, 1> s1_2{s1};
    span<P, 1> s1_3{std::move(s1)};
    span<P, 1> s1_4{p, p};

    // assignment operators
    s1 = s1;
    s1 = std::move(s1);

    // other
    s1.size();
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

    compileClassesPT<std::byte>();
}

template <typename T>
static void compileFunctionsT()
{
    T v{1};
    vec2<T> v2{v};
    vec3<T> v3{v};
    vec4<T> v4{v};
    span1<T> s1{v, v};
    span2<T> s2{v, v};
    span3<T> s3{v, v};
    span4<T> s4{v, v};
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

    static_cast<void>(s1 == s1);
    static_cast<void>(s2 == s2);
    static_cast<void>(s3 == s3);
    static_cast<void>(s4 == s4);

    static_cast<void>(s1 != s1);
    static_cast<void>(s2 != s2);
    static_cast<void>(s3 != s3);
    static_cast<void>(s4 != s4);

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

    qc::round<T>(s1);
    qc::round<T>(s2);
    qc::round<T>(s3);
    qc::round<T>(s4);

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
static void compileFunctionsFT()
{
    span1<T> s1{};
    span2<T> s2{};
    span3<T> s3{};
    span4<T> s4{};

    qc::round<s8>(s1);
    qc::round<s16>(s1);
    qc::round<s32>(s1);
    qc::round<s64>(s1);
    qc::round<s8>(s2);
    qc::round<s16>(s2);
    qc::round<s32>(s2);
    qc::round<s64>(s2);
    qc::round<s8>(s3);
    qc::round<s16>(s3);
    qc::round<s32>(s3);
    qc::round<s64>(s3);
    qc::round<s8>(s4);
    qc::round<s16>(s4);
    qc::round<s32>(s4);
    qc::round<s64>(s4);
}

template <typename T>
static void compileFunctionsPT()
{
    using P = T *;
    P p{};
    s64 v{};
    span1<P> s{p, p};
    std::stringstream os{};

    s += v;
    s -= v;
    s + v;
    s - v;
    static_cast<void>(s == s);
    static_cast<void>(s != s);
    os << s;
    qc::min(s, p);
    qc::max(s, p);
    qc::minify(s, p);
    qc::maxify(s, p);
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

    compileFunctionsPT<int>();
}

template <typename T, int n>
static void testPropertiesTN()
{
    static_assert(std::is_standard_layout_v<span<T, n>>);
    static_assert(std::is_trivially_default_constructible_v<span<T, n>>);
    static_assert(std::is_trivially_copyable_v<span<T, n>>);
    static_assert(std::is_trivially_copy_constructible_v<span<T, n>>);
    static_assert(std::is_trivially_move_constructible_v<span<T, n>>);
    static_assert(std::is_trivially_copy_assignable_v<span<T, n>>);
    static_assert(std::is_trivially_move_assignable_v<span<T, n>>);
    static_assert(std::is_trivially_destructible_v<span<T, n>>);
    static_assert(sizeof(span<T, n>) == 2 * n * sizeof(T));
    static_assert(sizeof(span<T, n>[4]) == 4 * 2 * n * sizeof(T));
    static_assert(alignof(span<T, n>) == alignof(T));
    static_assert(alignof(span<T, n>[4]) == alignof(T));
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
static void compileCastsTTN()
{
    span1<T1> s1{};
    span2<T1> s2{};
    span3<T1> s3{};
    span4<T1> s4{};

    { span<T2, n> s{s1}; }
    { span<T2, n> s{s2}; }
    { span<T2, n> s{s3}; }
    { span<T2, n> s{s4}; }

    static_cast<span<T2, n>>(s1);
    static_cast<span<T2, n>>(s2);
    static_cast<span<T2, n>>(s3);
    static_cast<span<T2, n>>(s4);

    static_cast<bool>(s1);
    static_cast<bool>(s2);
    static_cast<bool>(s3);
    static_cast<bool>(s4);
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
}

static void compileCasts()
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
}

template <typename T>
static void compileConstantsT()
{
    constexpr span1<T> is1{qc::fullSpan<T, 1>};
    constexpr span2<T> is2{qc::fullSpan<T, 2>};
    constexpr span3<T> is3{qc::fullSpan<T, 3>};
    constexpr span4<T> is4{qc::fullSpan<T, 4>};

    constexpr span1<T> nulls1{qc::nullSpan<T, 1>};
    constexpr span2<T> nulls2{qc::nullSpan<T, 2>};
    constexpr span3<T> nulls3{qc::nullSpan<T, 3>};
    constexpr span4<T> nulls4{qc::nullSpan<T, 4>};
}

static void compileConstants()
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
}

TEST(Span, compilation)
{
    compileClasses();
    compileFunctions();
    testProperties();
    compileCasts();
    compileConstants();
}

template <typename T>
void testSpanConceptT()
{
    static_assert(Span<span1<T>>);
    static_assert(Span<span2<T>>);
    static_assert(Span<span3<T>>);
    static_assert(Span<span4<T>>);

    static_assert(Span1<span1<T>>);
    static_assert(!Span1<span2<T>>);
    static_assert(!Span1<span3<T>>);
    static_assert(!Span1<span4<T>>);

    static_assert(Span2<span2<T>>);
    static_assert(!Span2<span1<T>>);
    static_assert(!Span2<span3<T>>);
    static_assert(!Span2<span4<T>>);

    static_assert(Span3<span3<T>>);
    static_assert(!Span3<span1<T>>);
    static_assert(!Span3<span2<T>>);
    static_assert(!Span3<span4<T>>);

    static_assert(Span4<span4<T>>);
    static_assert(!Span4<span1<T>>);
    static_assert(!Span4<span2<T>>);
    static_assert(!Span4<span3<T>>);
}

template <typename T>
void testFloaterSpanConceptT()
{
    static_assert(FloatingVector<vec2<T>>);
    static_assert(FloatingVector<vec3<T>>);
    static_assert(FloatingVector<vec4<T>>);
}

template <typename T>
void testIntegerSpanConceptT()
{
    static_assert(IntegralVector<vec2<T>>);
    static_assert(IntegralVector<vec3<T>>);
    static_assert(IntegralVector<vec4<T>>);
}

template <typename T>
void testSignedIntegerSpanConceptT()
{
    static_assert(SignedIntegralVector<vec2<T>>);
    static_assert(SignedIntegralVector<vec3<T>>);
    static_assert(SignedIntegralVector<vec4<T>>);
}

template <typename T>
void testUnsignedIntegerSpanConceptT()
{
    static_assert(UnsignedIntegralVector<vec2<T>>);
    static_assert(UnsignedIntegralVector<vec3<T>>);
    static_assert(UnsignedIntegralVector<vec4<T>>);
}

TEST(Span, concepts)
{
    testSpanConceptT<s8>();
    testSpanConceptT<u8>();
    testSpanConceptT<s16>();
    testSpanConceptT<u16>();
    testSpanConceptT<f32>();
    testSpanConceptT<s32>();
    testSpanConceptT<u32>();
    testSpanConceptT<f64>();
    testSpanConceptT<s64>();
    testSpanConceptT<u64>();
    static_assert(!Span<int>);

    testFloaterSpanConceptT<f32>();
    testFloaterSpanConceptT<f64>();
    static_assert(!FloatingSpan<ivec2>);

    testIntegerSpanConceptT<s8>();
    testIntegerSpanConceptT<u8>();
    testIntegerSpanConceptT<s16>();
    testIntegerSpanConceptT<u16>();
    testIntegerSpanConceptT<s32>();
    testIntegerSpanConceptT<u32>();
    testIntegerSpanConceptT<s64>();
    testIntegerSpanConceptT<u64>();
    static_assert(!IntegralSpan<fvec2>);

    testSignedIntegerSpanConceptT<s8>();
    testSignedIntegerSpanConceptT<s16>();
    testSignedIntegerSpanConceptT<s32>();
    testSignedIntegerSpanConceptT<s64>();
    static_assert(!SignedIntegralSpan<uivec2>);

    testUnsignedIntegerSpanConceptT<u8>();
    testUnsignedIntegerSpanConceptT<u16>();
    testUnsignedIntegerSpanConceptT<u32>();
    testUnsignedIntegerSpanConceptT<u64>();
    static_assert(!UnsignedIntegralSpan<ivec2>);

    static_assert(PointerSpan<span1<int *>>);
    static_assert(PointerSpan<span1<const int *>>);
    static_assert(Span1<span1<int *>>);
    static_assert(Span1<span1<const int *>>);
    static_assert(!PointerSpan<ispan1>);
}
