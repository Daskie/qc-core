#include <sstream>

#include <CppUnitTest.h>

#include <qc-core/span-ext.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template <typename T>
static void compileClassesT() {
    T v{};
    qc::vec2<T> v2;
    qc::vec3<T> v3;
    qc::vec4<T> v4;
    qc::span1<T> s1;
    qc::span2<T> s2;
    qc::span3<T> s3;
    qc::span4<T> s4;

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
}

static void compileClasses() {
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
}

template <typename T>
static constexpr void compileClassesConstexprT() {
    constexpr T v{};
    constexpr qc::vec2<T> v2;
    constexpr qc::vec3<T> v3;
    constexpr qc::vec4<T> v4;
    constexpr qc::span1<T> s1;
    constexpr qc::span2<T> s2;
    constexpr qc::span3<T> s3;
    constexpr qc::span4<T> s4;

    //--------------------------------------------------------------------------
    // Span1

    // constructors
    constexpr qc::span<T, 1> s1_1;
    constexpr qc::span<T, 1> s1_2(s1);
    constexpr qc::span<T, 1> s1_3(std::move(s1));
    constexpr qc::span<T, 1> s1_4(v, v);

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
}

static constexpr bool compileClassesConstexpr() {
    compileClassesConstexprT<qc::f32>();
    compileClassesConstexprT<qc::f64>();
    compileClassesConstexprT<qc::s8>();
    compileClassesConstexprT<qc::s16>();
    compileClassesConstexprT<qc::s32>();
    compileClassesConstexprT<qc::s64>();
    compileClassesConstexprT<qc::u8>();
    compileClassesConstexprT<qc::u16>();
    compileClassesConstexprT<qc::u32>();
    compileClassesConstexprT<qc::u64>();

    return true;
}

template <typename T>
static void compileFunctionsT() {
    T v{1};
    qc::vec2<T> v2{v};
    qc::vec3<T> v3{v};
    qc::vec4<T> v4{v};
    qc::span1<T> s1{v, v};
    qc::span2<T> s2{v, v};
    qc::span3<T> s3{v, v};
    qc::span4<T> s4{v, v};
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

    qc::clamp(v, s1);
    qc::clamp(v2, s2);
    qc::clamp(v3, s3);
    qc::clamp(v4, s4);

    qc::intersect(s1, s1);
    qc::intersect(s2, s2);
    qc::intersect(s3, s3);
    qc::intersect(s4, s4);

    qc::join(s1, s1);
    qc::join(s2, s2);
    qc::join(s3, s3);
    qc::join(s4, s4);

    qc::joinify(s1, s1);
    qc::joinify(s2, s2);
    qc::joinify(s3, s3);
    qc::joinify(s4, s4);
}

static void compileFunctions() {
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

template <typename T>
static constexpr void compileFunctionsConstexprT() {
    constexpr T v{1};
    constexpr qc::vec2<T> v2(v);
    constexpr qc::vec3<T> v3(v);
    constexpr qc::vec4<T> v4(v);
    constexpr qc::span1<T> s1(v, v);
    constexpr qc::span2<T> s2(v, v);
    constexpr qc::span3<T> s3(v, v);
    constexpr qc::span4<T> s4(v, v);

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

    //qc::min(s1, v);
    //qc::min(s2, v);
    //qc::min(s2, v2);
    //qc::min(s3, v);
    //qc::min(s3, v3);
    //qc::min(s4, v);
    //qc::min(s4, v4);
    //
    //qc::max(s1, v);
    //qc::max(s2, v);
    //qc::max(s2, v2);
    //qc::max(s3, v);
    //qc::max(s3, v3);
    //qc::max(s4, v);
    //qc::max(s4, v4);

    //qc::clamp(v, s1);
    //qc::clamp(v2, s2);
    //qc::clamp(v3, s3);
    //qc::clamp(v4, s4);

    //qc::intersect(s1, s1);
    //qc::intersect(s2, s2);
    //qc::intersect(s3, s3);
    //qc::intersect(s4, s4);

    //qc::join(s1, s1);
    //qc::join(s2, s2);
    //qc::join(s3, s3);
    //qc::join(s4, s4);
}

static constexpr bool compileFunctionsConstexpr() {
    compileFunctionsConstexprT<qc::f32>();
    compileFunctionsConstexprT<qc::f64>();
    compileFunctionsConstexprT<qc::s8>();
    compileFunctionsConstexprT<qc::s16>();
    compileFunctionsConstexprT<qc::s32>();
    compileFunctionsConstexprT<qc::s64>();
    compileFunctionsConstexprT<qc::u8>();
    compileFunctionsConstexprT<qc::u16>();
    compileFunctionsConstexprT<qc::u32>();
    compileFunctionsConstexprT<qc::u64>();

    return true;
}

template <typename T, int n>
static void testPropertiesTN() {
    static_assert(std::is_standard_layout_v<qc::span<T, n>>);
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
static void testPropertiesT() {
    testPropertiesTN<T, 1>();
    testPropertiesTN<T, 2>();
    testPropertiesTN<T, 3>();
    testPropertiesTN<T, 4>();
}

static void testProperties() {
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
static constexpr void compileCastsTTN() {
    qc::span1<T1> s1;
    qc::span2<T1> s2;
    qc::span3<T1> s3;
    qc::span4<T1> s4;

    { qc::span<T2, n> s(s1); }
    { qc::span<T2, n> s(s2); }
    { qc::span<T2, n> s(s3); }
    { qc::span<T2, n> s(s4); }

    static_cast<qc::span<T2, n>>(s1);
    static_cast<qc::span<T2, n>>(s2);
    static_cast<qc::span<T2, n>>(s3);
    static_cast<qc::span<T2, n>>(s4);
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

static constexpr bool compileCasts() {
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

    return true;
}

template <typename T>
static constexpr void compileConstantsFT() {
    constexpr qc::span1<T> is1(qc::infspan<T, 1>);
    constexpr qc::span2<T> is2(qc::infspan<T, 2>);
    constexpr qc::span3<T> is3(qc::infspan<T, 3>);
    constexpr qc::span4<T> is4(qc::infspan<T, 4>);

    constexpr qc::span1<T> ns1(qc::nanspan<T, 1>);
    constexpr qc::span2<T> ns2(qc::nanspan<T, 2>);
    constexpr qc::span3<T> ns3(qc::nanspan<T, 3>);
    constexpr qc::span4<T> ns4(qc::nanspan<T, 4>);

    constexpr qc::span1<T> nulls1(qc::nullspan<T, 1>);
    constexpr qc::span2<T> nulls2(qc::nullspan<T, 2>);
    constexpr qc::span3<T> nulls3(qc::nullspan<T, 3>);
    constexpr qc::span4<T> nulls4(qc::nullspan<T, 4>);
}

static constexpr bool compileConstants() {
    compileConstantsFT<qc::f32>();
    compileConstantsFT<qc::f64>();

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
