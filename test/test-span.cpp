#include <sstream>

#include <CppUnitTest.h>

#include <qc-core/span-ext.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template <typename T>
static void compileClassesT() {
    T v{};
    qc::core::vec2<T> v2;
    qc::core::vec3<T> v3;
    qc::core::vec4<T> v4;
    qc::core::span1<T> s1;
    qc::core::span2<T> s2;
    qc::core::span3<T> s3;
    qc::core::span4<T> s4;

    //--------------------------------------------------------------------------
    // Span1

    // constructors
    qc::core::span<T, 1> s1_1;
    qc::core::span<T, 1> s1_2(s1);
    qc::core::span<T, 1> s1_3(std::move(s1));
    qc::core::span<T, 1> s1_4(v, v);

    // asignment operators
    s1 = s1;
    s1 = std::move(s1);

    //--------------------------------------------------------------------------
    // Span2

    // constructors
    qc::core::span<T, 2> s2_1;
    qc::core::span<T, 2> s2_2(s2);
    qc::core::span<T, 2> s2_3(std::move(s2));
    qc::core::span<T, 2> s2_4(v2, v2);
    qc::core::span<T, 2> s2_5(v, v);
    qc::core::span<T, 2> s2_6(s1, s1);

    // asignment operators
    s2 = s2;
    s2 = std::move(s2);

    // other
    s2.x();
    s2.y();

    //--------------------------------------------------------------------------
    // Span3

    // constructors
    qc::core::span<T, 3> s3_1;
    qc::core::span<T, 3> s3_2(s3);
    qc::core::span<T, 3> s3_3(std::move(s3));
    qc::core::span<T, 3> s3_4(v3, v3);
    qc::core::span<T, 3> s3_5(v, v);
    qc::core::span<T, 3> s3_6(s1, s1, s1);
    qc::core::span<T, 3> s3_7(s2, s1);
    qc::core::span<T, 3> s3_8(s1, s2);

    // asignment operators
    s3 = s3;
    s3 = std::move(s3);

    // other
    s3.x();
    s3.y();
    s3.z();
    s3.xy();
    s3.yz();

    //--------------------------------------------------------------------------
    // Span4

    // constructors
    qc::core::span<T, 4> s4_1;
    qc::core::span<T, 4> s4_2(s4);
    qc::core::span<T, 4> s4_3(std::move(s4));
    qc::core::span<T, 4> s4_4(v4, v4);
    qc::core::span<T, 4> s4_5(v, v);
    qc::core::span<T, 4> s4_6(s1, s1, s1, s1);
    qc::core::span<T, 4> s4_7(s2, s1, s1);
    qc::core::span<T, 4> s4_8(s1, s2, s1);
    qc::core::span<T, 4> s4_9(s1, s1, s2);
    qc::core::span<T, 4> s4_10(s2, s2);
    qc::core::span<T, 4> s4_11(s3, s1);
    qc::core::span<T, 4> s4_12(s1, s3);

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
}

static void compileClasses() {
    compileClassesT<qc::core::f32>();
    compileClassesT<qc::core::f64>();
    compileClassesT<qc::core::s8>();
    compileClassesT<qc::core::s16>();
    compileClassesT<qc::core::s32>();
    compileClassesT<qc::core::s64>();
    compileClassesT<qc::core::u8>();
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
    constexpr qc::core::span1<T> s1;
    constexpr qc::core::span2<T> s2;
    constexpr qc::core::span3<T> s3;
    constexpr qc::core::span4<T> s4;

    //--------------------------------------------------------------------------
    // Span1

    // constructors
    constexpr qc::core::span<T, 1> s1_1;
    constexpr qc::core::span<T, 1> s1_2(s1);
    constexpr qc::core::span<T, 1> s1_3(std::move(s1));
    constexpr qc::core::span<T, 1> s1_4(v, v);

    //--------------------------------------------------------------------------
    // Span2

    // constructors
    constexpr qc::core::span<T, 2> s2_1;
    constexpr qc::core::span<T, 2> s2_2(s2);
    constexpr qc::core::span<T, 2> s2_3(std::move(s2));
    constexpr qc::core::span<T, 2> s2_4(v2, v2);
    constexpr qc::core::span<T, 2> s2_5(v, v);
    constexpr qc::core::span<T, 2> s2_6(s1, s1);

    // other
    s2.x();
    s2.y();

    //--------------------------------------------------------------------------
    // Span3

    // constructors
    constexpr qc::core::span<T, 3> s3_1;
    constexpr qc::core::span<T, 3> s3_2(s3);
    constexpr qc::core::span<T, 3> s3_3(std::move(s3));
    constexpr qc::core::span<T, 3> s3_4(v3, v3);
    constexpr qc::core::span<T, 3> s3_5(v, v);
    constexpr qc::core::span<T, 3> s3_6(s1, s1, s1);
    //constexpr qc::core::span<T, 3> s3_7(s2, s1);
    //constexpr qc::core::span<T, 3> s3_8(s1, s2);

    // other
    s3.x();
    s3.y();
    s3.z();
    //s3.xy();
    //s3.yz();

    //--------------------------------------------------------------------------
    // Span4

    // constructors
    constexpr qc::core::span<T, 4> s4_1;
    constexpr qc::core::span<T, 4> s4_2(s4);
    constexpr qc::core::span<T, 4> s4_3(std::move(s4));
    constexpr qc::core::span<T, 4> s4_4(v4, v4);
    constexpr qc::core::span<T, 4> s4_5(v, v);
    constexpr qc::core::span<T, 4> s4_6(s1, s1, s1, s1);
    //constexpr qc::core::span<T, 4> s4_7(s2, s1, s1);
    //constexpr qc::core::span<T, 4> s4_8(s1, s2, s1);
    //constexpr qc::core::span<T, 4> s4_9(s1, s1, s2);
    //constexpr qc::core::span<T, 4> s4_10(s2, s2);
    //constexpr qc::core::span<T, 4> s4_11(s3, s1);
    //constexpr qc::core::span<T, 4> s4_12(s1, s3);

    // other
    s4.x();
    s4.y();
    s4.z();
    s4.w();
    //s4.xy();
    //s4.yz();
    //s4.xyz();
    //s4.yzw();
}

static constexpr bool compileClassesConstexpr() {
    compileClassesConstexprT<qc::core::f32>();
    compileClassesConstexprT<qc::core::f64>();
    compileClassesConstexprT<qc::core::s8>();
    compileClassesConstexprT<qc::core::s16>();
    compileClassesConstexprT<qc::core::s32>();
    compileClassesConstexprT<qc::core::s64>();
    compileClassesConstexprT<qc::core::u8>();
    compileClassesConstexprT<qc::core::u16>();
    compileClassesConstexprT<qc::core::u32>();
    compileClassesConstexprT<qc::core::u64>();

    return true;
}

template <typename T>
static void compileFunctionsT() {
    T v{1};
    qc::core::vec2<T> v2{v};
    qc::core::vec3<T> v3{v};
    qc::core::vec4<T> v4{v};
    qc::core::span1<T> s1{v, v};
    qc::core::span2<T> s2{v, v};
    qc::core::span3<T> s3{v, v};
    qc::core::span4<T> s4{v, v};
    std::stringstream os;

    // arithmetic assignment

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

    // arithmetic

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

    // comparison

    s1 == s1;
    s2 == s2;
    s3 == s3;
    s4 == s4;

    s1 != s1;
    s2 != s2;
    s3 != s3;
    s4 != s4;

    // other

    os << s1;
    os << s2;
    os << s3;
    os << s4;

    // uncategorized

    qc::core::min(s1, v);
    qc::core::min(s2, v);
    qc::core::min(s2, v2);
    qc::core::min(s3, v);
    qc::core::min(s3, v3);
    qc::core::min(s4, v);
    qc::core::min(s4, v4);

    qc::core::max(s1, v);
    qc::core::max(s2, v);
    qc::core::max(s2, v2);
    qc::core::max(s3, v);
    qc::core::max(s3, v3);
    qc::core::max(s4, v);
    qc::core::max(s4, v4);

    qc::core::minify(s1, v);
    qc::core::minify(s2, v);
    qc::core::minify(s2, v2);
    qc::core::minify(s3, v);
    qc::core::minify(s3, v3);
    qc::core::minify(s4, v);
    qc::core::minify(s4, v4);

    qc::core::maxify(s1, v);
    qc::core::maxify(s2, v);
    qc::core::maxify(s2, v2);
    qc::core::maxify(s3, v);
    qc::core::maxify(s3, v3);
    qc::core::maxify(s4, v);
    qc::core::maxify(s4, v4);

    qc::core::clamp(v, s1);
    qc::core::clamp(v2, s2);
    qc::core::clamp(v3, s3);
    qc::core::clamp(v4, s4);

    qc::core::intersect(s1, s1);
    qc::core::intersect(s2, s2);
    qc::core::intersect(s3, s3);
    qc::core::intersect(s4, s4);

    qc::core::join(s1, s1);
    qc::core::join(s2, s2);
    qc::core::join(s3, s3);
    qc::core::join(s4, s4);

    qc::core::joinify(s1, s1);
    qc::core::joinify(s2, s2);
    qc::core::joinify(s3, s3);
    qc::core::joinify(s4, s4);
}

static void compileFunctions() {
    compileFunctionsT<qc::core::f32>();
    compileFunctionsT<qc::core::f64>();
    compileFunctionsT<qc::core::s8>();
    compileFunctionsT<qc::core::s16>();
    compileFunctionsT<qc::core::s32>();
    compileFunctionsT<qc::core::s64>();
    compileFunctionsT<qc::core::u8>();
    compileFunctionsT<qc::core::u16>();
    compileFunctionsT<qc::core::u32>();
    compileFunctionsT<qc::core::u64>();
}

template <typename T>
static constexpr void compileFunctionsConstexprT() {
    constexpr T v{1};
    constexpr qc::core::vec2<T> v2(v);
    constexpr qc::core::vec3<T> v3(v);
    constexpr qc::core::vec4<T> v4(v);
    constexpr qc::core::span1<T> s1(v, v);
    constexpr qc::core::span2<T> s2(v, v);
    constexpr qc::core::span3<T> s3(v, v);
    constexpr qc::core::span4<T> s4(v, v);

    // arithmetic assignment

    //s1 += v;
    //s2 += v;
    //s3 += v;
    //s4 += v;

    //s2 += v2;
    //s3 += v3;
    //s4 += v4;

    //s1 -= v;
    //s2 -= v;
    //s3 -= v;
    //s4 -= v;

    //s2 -= v2;
    //s3 -= v3;
    //s4 -= v4;

    // arithmetic

    //s1 + v;
    //s2 + v;
    //s3 + v;
    //s4 + v;

    //s2 + v2;
    //s3 + v3;
    //s4 + v4;

    //v + s1;
    //v + s2;
    //v + s3;
    //v + s4;

    //v2 + s2;
    //v3 + s3;
    //v4 + s4;

    //s1 - v;
    //s2 - v;
    //s3 - v;
    //s4 - v;

    //s2 - v2;
    //s3 - v3;
    //s4 - v4;

    //v - s1;
    //v - s2;
    //v - s3;
    //v - s4;

    //v2 - s2;
    //v3 - s3;
    //v4 - s4;

    // comparison

    //s1 == s1;
    //s2 == s2;
    //s3 == s3;
    //s4 == s4;

    //s1 != s1;
    //s2 != s2;
    //s3 != s3;
    //s4 != s4;

    // uncategorized

    //qc::core::min(s1, v);
    //qc::core::min(s2, v);
    //qc::core::min(s2, v2);
    //qc::core::min(s3, v);
    //qc::core::min(s3, v3);
    //qc::core::min(s4, v);
    //qc::core::min(s4, v4);
    //
    //qc::core::max(s1, v);
    //qc::core::max(s2, v);
    //qc::core::max(s2, v2);
    //qc::core::max(s3, v);
    //qc::core::max(s3, v3);
    //qc::core::max(s4, v);
    //qc::core::max(s4, v4);

    //qc::core::clamp(v, s1);
    //qc::core::clamp(v2, s2);
    //qc::core::clamp(v3, s3);
    //qc::core::clamp(v4, s4);

    //qc::core::intersect(s1, s1);
    //qc::core::intersect(s2, s2);
    //qc::core::intersect(s3, s3);
    //qc::core::intersect(s4, s4);

    //qc::core::join(s1, s1);
    //qc::core::join(s2, s2);
    //qc::core::join(s3, s3);
    //qc::core::join(s4, s4);
}

static constexpr bool compileFunctionsConstexpr() {
    compileFunctionsConstexprT<qc::core::f32>();
    compileFunctionsConstexprT<qc::core::f64>();
    compileFunctionsConstexprT<qc::core::s8>();
    compileFunctionsConstexprT<qc::core::s16>();
    compileFunctionsConstexprT<qc::core::s32>();
    compileFunctionsConstexprT<qc::core::s64>();
    compileFunctionsConstexprT<qc::core::u8>();
    compileFunctionsConstexprT<qc::core::u16>();
    compileFunctionsConstexprT<qc::core::u32>();
    compileFunctionsConstexprT<qc::core::u64>();

    return true;
}

template <typename T, int n>
static void testPropertiesTN() {
    static_assert(std::is_standard_layout_v<qc::core::span<T, n>>);
    static_assert(std::is_trivially_copyable_v<qc::core::span<T, n>>);
    static_assert(std::is_trivially_copy_constructible_v<qc::core::span<T, n>>);
    static_assert(std::is_trivially_move_constructible_v<qc::core::span<T, n>>);
    static_assert(std::is_trivially_copy_assignable_v<qc::core::span<T, n>>);
    static_assert(std::is_trivially_move_assignable_v<qc::core::span<T, n>>);
    static_assert(std::is_trivially_destructible_v<qc::core::span<T, n>>);
    static_assert(sizeof(qc::core::span<T, n>) == 2 * n * sizeof(T));
    static_assert(sizeof(qc::core::span<T, n>[4]) == 4 * 2 * n * sizeof(T));
    static_assert(alignof(qc::core::span<T, n>) == alignof(T));
    static_assert(alignof(qc::core::span<T, n>[4]) == alignof(T));
}

template <typename T>
static void testPropertiesT() {
    testPropertiesTN<T, 1>();
    testPropertiesTN<T, 2>();
    testPropertiesTN<T, 3>();
    testPropertiesTN<T, 4>();
}

static void testProperties() {
    testPropertiesT<qc::core::f32>();
    testPropertiesT<qc::core::f64>();
    testPropertiesT<qc::core::s8>();
    testPropertiesT<qc::core::s16>();
    testPropertiesT<qc::core::s32>();
    testPropertiesT<qc::core::s64>();
    testPropertiesT<qc::core::u8>();
    testPropertiesT<qc::core::u16>();
    testPropertiesT<qc::core::u32>();
    testPropertiesT<qc::core::u64>();
}

template <typename T1, typename T2, int n>
static constexpr void compileCastsTTN() {
    qc::core::span1<T1> s1;
    qc::core::span2<T1> s2;
    qc::core::span3<T1> s3;
    qc::core::span4<T1> s4;

    { qc::core::span<T2, n> s(s1); }
    { qc::core::span<T2, n> s(s2); }
    { qc::core::span<T2, n> s(s3); }
    { qc::core::span<T2, n> s(s4); }

    static_cast<qc::core::span<T2, n>>(s1);
    static_cast<qc::core::span<T2, n>>(s2);
    static_cast<qc::core::span<T2, n>>(s3);
    static_cast<qc::core::span<T2, n>>(s4);
}

template <typename T1, typename T2>
static constexpr void compileCastsTT() {
    compileCastsTTN<T1, T2, 1>();
    compileCastsTTN<T1, T2, 2>();
    compileCastsTTN<T1, T2, 3>();
    compileCastsTTN<T1, T2, 4>();
}

template <typename T>
static constexpr void compileCastsT() {
    compileCastsTT<T, qc::core::f32>();
    compileCastsTT<T, qc::core::f64>();
    compileCastsTT<T, qc::core::s8>();
    compileCastsTT<T, qc::core::s16>();
    compileCastsTT<T, qc::core::s32>();
    compileCastsTT<T, qc::core::s64>();
    compileCastsTT<T, qc::core::u8>();
    compileCastsTT<T, qc::core::u16>();
    compileCastsTT<T, qc::core::u32>();
    compileCastsTT<T, qc::core::u64>();
}

static constexpr bool compileCasts() {
    compileCastsT<qc::core::f32>();
    compileCastsT<qc::core::f64>();
    compileCastsT<qc::core::s8>();
    compileCastsT<qc::core::s16>();
    compileCastsT<qc::core::s32>();
    compileCastsT<qc::core::s64>();
    compileCastsT<qc::core::u8>();
    compileCastsT<qc::core::u16>();
    compileCastsT<qc::core::u32>();
    compileCastsT<qc::core::u64>();

    return true;
}

template <typename T>
static constexpr void compileConstantsFT() {
    constexpr qc::core::span1<T> is1(qc::core::infspan<T, 1>);
    constexpr qc::core::span2<T> is2(qc::core::infspan<T, 2>);
    constexpr qc::core::span3<T> is3(qc::core::infspan<T, 3>);
    constexpr qc::core::span4<T> is4(qc::core::infspan<T, 4>);

    constexpr qc::core::span1<T> ns1(qc::core::nanspan<T, 1>);
    constexpr qc::core::span2<T> ns2(qc::core::nanspan<T, 2>);
    constexpr qc::core::span3<T> ns3(qc::core::nanspan<T, 3>);
    constexpr qc::core::span4<T> ns4(qc::core::nanspan<T, 4>);

    constexpr qc::core::span1<T> nulls1(qc::core::nullspan<T, 1>);
    constexpr qc::core::span2<T> nulls2(qc::core::nullspan<T, 2>);
    constexpr qc::core::span3<T> nulls3(qc::core::nullspan<T, 3>);
    constexpr qc::core::span4<T> nulls4(qc::core::nullspan<T, 4>);
}

static constexpr bool compileConstants() {
    compileConstantsFT<qc::core::f32>();
    compileConstantsFT<qc::core::f64>();

    return true;
}

TEST_CLASS(TestSpan) {

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

};
