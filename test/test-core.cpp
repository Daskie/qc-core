#include <qc-core/core-ext.hpp>
#include <qc-core/list.hpp>

// gtest overrides FAIL macro
#pragma push_macro("FAIL")
#include <gtest/gtest.h>
#pragma pop_macro("FAIL")

using namespace qc::types;
using namespace qc::primitives;

enum TestEnum { a, b, c };

TEST(Core, debugRelease)
{
    #if defined QC_DEBUG
        static_assert(qc::debug);
        static_assert(!qc::release);
    #elif defined QC_RELEASE
        static_assert(!qc::debug);
        static_assert(qc::release);
    #else
        static_assert(false);
    #endif

}

TEST(Core, compiler)
{
    #if defined QC_MSVC
        static_assert(qc::compiler == qc::Compiler::msvc);
        static_assert(qc::msvc);
        static_assert(!qc::gcc);
    #elif defined QC_GCC
        static_assert(qc::compiler == qc::Compiler::gcc);
        static_assert(!qc::msvc);
        static_assert(qc::gcc);
    #else
        static_assert(qc::compiler == qc::Clatform::other);
        static_assert(!qc::msvc);
        static_assert(!qc::gcc);
    #endif
}

TEST(Core, platform)
{
    #if defined QC_WINDOWS
        static_assert(qc::platform == qc::Platform::windows);
        static_assert(qc::windows);
        static_assert(!qc::linux);
    #elif defined QC_LINUX
        static_assert(qc::platform == qc::Platform::linux);
        static_assert(!qc::windows);
        static_assert(qc::linux);
    #else
        static_assert(qc::platform == qc::Platform::other);
        static_assert(!qc::windows);
        static_assert(!qc::linux);
    #endif
}

TEST(Core, primitives)
{
    [[maybe_unused]] s8 s08_{0_s8};
    [[maybe_unused]] u8 u08_{0_u8};
    [[maybe_unused]] s16 s16_{0_s16};
    [[maybe_unused]] u16 u16_{0_u16};
    [[maybe_unused]] s32 s32_{0_s32};
    [[maybe_unused]] u32 u32_{0_u32};
    [[maybe_unused]] f32 f32_;
    [[maybe_unused]] s64 s64_{0_s64};
    [[maybe_unused]] u64 u64_{0_u64};
    [[maybe_unused]] f64 f64_;
}

template <Floating T>
static void compileNumbersT()
{
    static_cast<void>(qc::number::inf<T>);
    static_cast<void>(qc::number::nan<T>);
    static_cast<void>(qc::number::pi<T>);
    static_cast<void>(qc::number::e<T>);
    static_cast<void>(qc::number::phi<T>);
    static_cast<void>(qc::number::sqrt2<T>);
    static_cast<void>(qc::number::sqrt3<T>);
    static_cast<void>(qc::number::sqrt5<T>);
}

TEST(Core, numbers)
{
    compileNumbersT<f32>();
    compileNumbersT<f64>();
}

TEST(Core, classes)
{
    qc::Duo<s32> d1;
    static_cast<void>(d1.a);
    static_cast<void>(d1.b);
    static_cast<void>(d1[0u]);
    static_cast<void>(d1[1u]);
    static_cast<void>(d1[0]);
    static_cast<void>(d1[1]);
    static_cast<void>(d1[false]);
    static_cast<void>(d1[true]);
    for ([[maybe_unused]] s32 & v : d1) {}
    ASSERT_EQ(std::distance(d1.begin(), d1.end()), 2);

    qc::Duo<s32, std::string> d2;
    static_cast<void>(d2.a);
    static_cast<void>(d2.b);

    qc::Trio<s32> t1;
    static_cast<void>(t1.a);
    static_cast<void>(t1.b);
    static_cast<void>(t1.c);
    static_cast<void>(d1[0u]);
    static_cast<void>(d1[1u]);
    static_cast<void>(d1[2u]);
    static_cast<void>(d1[0]);
    static_cast<void>(d1[1]);
    static_cast<void>(d1[2]);
    for ([[maybe_unused]] s32 & v : t1) {}
    ASSERT_EQ(std::distance(t1.begin(), t1.end()), 3);

    qc::Trio<s32, std::string> t2;
    static_cast<void>(t2.a);
    static_cast<void>(t2.b);
    static_cast<void>(t2.b);

    qc::Trio<s32, std::string, TestEnum> t3;
    static_cast<void>(t3.a);
    static_cast<void>(t3.b);
    static_cast<void>(t3.b);
}

template <typename T1, typename T2>
static void compileFunctionsTT() {}

template <typename T1, typename T2>
static void compileFunctionsSITT()
{
    T1 v1{};
    T2 v2{};

    static_cast<void>(qc::min(v1, v2));
    static_cast<void>(qc::min(v1, v2, v1));
    static_cast<void>(qc::min(v1, v2, v1, v2));
    static_cast<void>(qc::min(v1, v2, v1, v2, v1));

    static_cast<void>(qc::max(v1, v2));
    static_cast<void>(qc::max(v1, v2, v1));
    static_cast<void>(qc::max(v1, v2, v1, v2));
    static_cast<void>(qc::max(v1, v2, v1, v2, v1));

    if constexpr (sizeof(T1) >= sizeof(T2))
    {
        qc::minify(v1, v2);
        qc::minify(v1, v2, v1);
        qc::minify(v1, v2, v1, v2);
        qc::minify(v1, v2, v1, v2, v1);

        qc::maxify(v1, v2);
        qc::maxify(v1, v2, v1);
        qc::maxify(v1, v2, v1, v2);
        qc::maxify(v1, v2, v1, v2, v1);
    }
}

template <typename T1, typename T2>
static void compileFunctionsUITT()
{
    T1 v1{};
    T2 v2{};

    static_cast<void>(qc::min(v1, v2));
    static_cast<void>(qc::min(v1, v2, v1));
    static_cast<void>(qc::min(v1, v2, v1, v2));
    static_cast<void>(qc::min(v1, v2, v1, v2, v1));

    static_cast<void>(qc::max(v1, v2));
    static_cast<void>(qc::max(v1, v2, v1));
    static_cast<void>(qc::max(v1, v2, v1, v2));
    static_cast<void>(qc::max(v1, v2, v1, v2, v1));

    if constexpr (sizeof(T1) >= sizeof(T2))
    {
        qc::minify(v1, v2);
        qc::minify(v1, v2, v1);
        qc::minify(v1, v2, v1, v2);
        qc::minify(v1, v2, v1, v2, v1);

        qc::maxify(v1, v2);
        qc::maxify(v1, v2, v1);
        qc::maxify(v1, v2, v1, v2);
        qc::maxify(v1, v2, v1, v2, v1);
    }
}

template <typename T1, typename T2>
static void compileFunctionsFTT()
{
    T1 v1{};
    T2 v2{};

    static_cast<void>(qc::min(v1, v2));
    static_cast<void>(qc::min(v1, v2, v1));
    static_cast<void>(qc::min(v1, v2, v1, v2));
    static_cast<void>(qc::min(v1, v2, v1, v2, v1));

    static_cast<void>(qc::max(v1, v2));
    static_cast<void>(qc::max(v1, v2, v1));
    static_cast<void>(qc::max(v1, v2, v1, v2));
    static_cast<void>(qc::max(v1, v2, v1, v2, v1));

    if constexpr (sizeof(T1) >= sizeof(T2))
    {
        qc::minify(v1, v2);
        qc::minify(v1, v2, v1);
        qc::minify(v1, v2, v1, v2);
        qc::minify(v1, v2, v1, v2, v1);

        qc::maxify(v1, v2);
        qc::maxify(v1, v2, v1);
        qc::maxify(v1, v2, v1, v2);
        qc::maxify(v1, v2, v1, v2, v1);
    }
}

template <typename T>
static void compileFunctionsT()
{
    compileFunctionsTT<T, f32>();
    compileFunctionsTT<T, f64>();
    compileFunctionsTT<T, s8>();
    compileFunctionsTT<T, u8>();
    compileFunctionsTT<T, s16>();
    compileFunctionsTT<T, u16>();
    compileFunctionsTT<T, s32>();
    compileFunctionsTT<T, u32>();
    compileFunctionsTT<T, s64>();
    compileFunctionsTT<T, u64>();

    T v{1};
    T * vp{};

    static_cast<void>(qc::min(vp, vp));
    static_cast<void>(qc::min(vp, vp, vp));

    static_cast<void>(qc::max(vp, vp));
    static_cast<void>(qc::max(vp, vp, vp));

    qc::minify(vp, vp);
    qc::minify(vp, vp, vp);

    qc::maxify(vp, vp);
    qc::maxify(vp, vp, vp);

    static_cast<void>(qc::median(v, v, v));

    static_cast<void>(qc::abs(v));
    qc::absify(v);

    static_cast<void>(qc::clamp(v, v, v));

    qc::clampify(v, v, v);

    static_cast<void>(qc::zeroish(v));
    static_cast<void>(qc::zeroish(v, v));

    static_cast<void>(qc::equalish(v, v));
    static_cast<void>(qc::equalish(v, v, v));

    static_cast<void>(qc::sign(v));

    static_cast<void>(qc::round<T>(v));

    static_cast<void>(qc::floor<T>(v));

    static_cast<void>(qc::ceil<T>(v));

    static_cast<void>(qc::mod(v, v));
    static_cast<void>(qc::mod_q(v, v));
}

template <typename T>
static void compileFunctionsIT()
{

}

template <typename T>
static void compileFunctionsSIT()
{
    compileFunctionsSITT<T, s8>();
    compileFunctionsSITT<T, s16>();
    compileFunctionsSITT<T, s32>();
    compileFunctionsSITT<T, s64>();
}

template <typename T>
static void compileFunctionsUIT()
{
    compileFunctionsUITT<T, u8>();
    compileFunctionsUITT<T, u16>();
    compileFunctionsUITT<T, u32>();
    compileFunctionsUITT<T, u64>();

    T v{1u};

    static_cast<void>(qc::log2Floor(v));
}

template <typename T>
static void compileFunctionsFT()
{
    compileFunctionsFTT<T, f32>();
    compileFunctionsFTT<T, f64>();

    T v{1.0};

    static_cast<void>(qc::equalish(v, v));
    static_cast<void>(qc::equalish(v, v, v));

    static_cast<void>(qc::round<s8>(v));
    static_cast<void>(qc::round<s16>(v));
    static_cast<void>(qc::round<s32>(v));
    static_cast<void>(qc::round<s64>(v));

    static_cast<void>(qc::floor<s8>(v));
    static_cast<void>(qc::floor<s16>(v));
    static_cast<void>(qc::floor<s32>(v));
    static_cast<void>(qc::floor<s64>(v));

    static_cast<void>(qc::ceil<s8>(v));
    static_cast<void>(qc::ceil<s16>(v));
    static_cast<void>(qc::ceil<s32>(v));
    static_cast<void>(qc::ceil<s64>(v));

    static_cast<void>(qc::pow(v, v));
    static_cast<void>(qc::pow(v, 1));
    static_cast<void>(qc::pow(v, 1u));

    static_cast<void>(qc::fract(v));
    static_cast<void>(qc::fract_i<s8>(v));
    static_cast<void>(qc::fract_i<s16>(v));
    static_cast<void>(qc::fract_i<s32>(v));
    static_cast<void>(qc::fract_i<s64>(v));

    static_cast<void>(qc::isInteger(v));

    static_cast<void>(qc::mix(v, v, v));

    static_cast<void>(qc::unmix(v, v, v));

    static_cast<void>(qc::radians(v));

    static_cast<void>(qc::degrees(v));
}

TEST(Core, functions)
{
    compileFunctionsT<f32>();
    compileFunctionsT<f64>();
    compileFunctionsT<s8>();
    compileFunctionsT<u8>();
    compileFunctionsT<s16>();
    compileFunctionsT<u16>();
    compileFunctionsT<s32>();
    compileFunctionsT<u32>();
    compileFunctionsT<s64>();
    compileFunctionsT<u64>();

    compileFunctionsFT<f32>();
    compileFunctionsFT<f64>();

    compileFunctionsIT<s8>();
    compileFunctionsIT<u8>();
    compileFunctionsIT<s16>();
    compileFunctionsIT<u16>();
    compileFunctionsIT<s32>();
    compileFunctionsIT<u32>();
    compileFunctionsIT<s64>();
    compileFunctionsIT<u64>();

    compileFunctionsSIT<s8>();
    compileFunctionsSIT<s16>();
    compileFunctionsSIT<s32>();
    compileFunctionsSIT<s64>();

    compileFunctionsUIT<u8>();
    compileFunctionsUIT<u16>();
    compileFunctionsUIT<u32>();
    compileFunctionsUIT<u64>();

    // Non-matching min/max types

    u8 _u8{};
    u32 _u32{};
    u64 _u64{};
    s8 _s8{};
    s64 _s64{};
    f32 _f32{};
    f64 _f64{};

    static_cast<void>(qc::min(_u8, _u64));
    static_cast<void>(qc::min(_s8, _s64));
    static_cast<void>(qc::min(_u8, _s64));
    static_cast<void>(qc::min(_s8, _u32));
    static_cast<void>(qc::min(_u64, _u8));
    static_cast<void>(qc::min(_s64, _s8));
    static_cast<void>(qc::min(_s64, _u8));
    static_cast<void>(qc::min(_u32, _s8));
    static_cast<void>(qc::min(_f32, _f64));
    static_cast<void>(qc::min(_f64, _f32));

    static_cast<void>(qc::max(_u8, _u64));
    static_cast<void>(qc::max(_s8, _s64));
    static_cast<void>(qc::max(_u8, _s64));
    static_cast<void>(qc::max(_s8, _u32));
    static_cast<void>(qc::max(_u64, _u8));
    static_cast<void>(qc::max(_s64, _s8));
    static_cast<void>(qc::max(_s64, _u8));
    static_cast<void>(qc::max(_u32, _s8));
    static_cast<void>(qc::max(_f32, _f64));
    static_cast<void>(qc::max(_f64, _f32));

    static_cast<void>(qc::minify(_u64, _u8));
    static_cast<void>(qc::minify(_s64, _s8));
    static_cast<void>(qc::minify(_s64, _u32));
    static_cast<void>(qc::minify(_f64, _f32));

    static_cast<void>(qc::maxify(_u64, _u8));
    static_cast<void>(qc::maxify(_s64, _s8));
    static_cast<void>(qc::maxify(_s64, _u32));
    static_cast<void>(qc::maxify(_f64, _f32));
}

template <Integral T> static constexpr T halfVal{T(std::numeric_limits<T>::max() / 2 + T(1))};
template <Integral T> static constexpr T quarterVal{T(halfVal<T> / 2)};
template <Integral T> static constexpr T threeQuartersVal{T(halfVal<T> + quarterVal<T>)};

template <typename From, typename To>
void testTransnormFTFT()
{
    static_assert(To(0.0) == qc::transnorm<To>(From(0.0)));
    ASSERT_EQ(To(0.25), qc::transnorm<To>(From(0.25)));
    ASSERT_EQ(To(0.5), qc::transnorm<To>(From(0.5)));
    ASSERT_EQ(To(0.75), qc::transnorm<To>(From(0.75)));
    ASSERT_EQ(To(1.0), qc::transnorm<To>(From(1.0)));
}

template <typename From, typename To>
void testTransnormFTST()
{
    const f64 epsilon(1.0 / std::ldexp(1.0, std::numeric_limits<To>::digits));

    static_assert(To(-std::numeric_limits<To>::max()) == qc::transnorm<To>(From(-1.0)));
    ASSERT_NEAR(0.75, f64(qc::transnorm<To>(From(-0.75))) / f64(-std::numeric_limits<To>::max()), epsilon);
    ASSERT_NEAR(0.5, f64(qc::transnorm<To>(From(-0.5))) / f64(-std::numeric_limits<To>::max()), epsilon);
    ASSERT_NEAR(0.25, f64(qc::transnorm<To>(From(-0.25))) / f64(-std::numeric_limits<To>::max()), epsilon);
    ASSERT_EQ(To(0u), qc::transnorm<To>(From(0.0)));
    ASSERT_NEAR(0.25, f64(qc::transnorm<To>(From(0.25))) / f64(std::numeric_limits<To>::max()), epsilon);
    ASSERT_NEAR(0.5, f64(qc::transnorm<To>(From(0.5))) / f64(std::numeric_limits<To>::max()), epsilon);
    ASSERT_NEAR(0.75, f64(qc::transnorm<To>(From(0.75))) / f64(std::numeric_limits<To>::max()), epsilon);
    ASSERT_EQ(std::numeric_limits<To>::max(), qc::transnorm<To>(From(1.0)));

    ASSERT_GE(qc::transnorm<To>(From(-1.0) + std::numeric_limits<From>::epsilon()), qc::transnorm<To>(From(-1.0)));
    ASSERT_LE(qc::transnorm<To>(From(1.0) - std::numeric_limits<From>::epsilon()), qc::transnorm<To>(From(1.0)));
}

template <typename From, typename To>
void testTransnormFTUT()
{
    const f64 epsilon(1.0 / std::ldexp(1.0, std::numeric_limits<To>::digits));

    static_assert(To(0u) == qc::transnorm<To>(From(0.0)));
    ASSERT_NEAR(0.25, f64(qc::transnorm<To>(From(0.25))) / f64(std::numeric_limits<To>::max()), epsilon);
    ASSERT_NEAR(0.5, f64(qc::transnorm<To>(From(0.5))) / f64(std::numeric_limits<To>::max()), epsilon);
    ASSERT_NEAR(0.75, f64(qc::transnorm<To>(From(0.75))) / f64(std::numeric_limits<To>::max()), epsilon);
    ASSERT_EQ(std::numeric_limits<To>::max(), qc::transnorm<To>(From(1.0)));

    ASSERT_GE(qc::transnorm<To>(std::numeric_limits<From>::min()), qc::transnorm<To>(From(0.0)));
    ASSERT_LE(qc::transnorm<To>(From(1.0) - std::numeric_limits<From>::epsilon()), qc::transnorm<To>(From(1.0)));
}

template <typename From, typename To>
void testTransnormSTFT()
{
    const To epsilon{To(1.0 / std::ldexp(1.0, std::numeric_limits<From>::digits))};

    ASSERT_EQ(To(-1.0), qc::transnorm<To>(std::numeric_limits<From>::min()));
    ASSERT_NEAR(To(-0.75), qc::transnorm<To>(From(-threeQuartersVal<From>)), epsilon);
    ASSERT_NEAR(To(-0.5), qc::transnorm<To>(From(-halfVal<From>)), epsilon);
    ASSERT_NEAR(To(-0.25), qc::transnorm<To>(From(-quarterVal<From>)), epsilon);
    static_assert(To(0.0) == qc::transnorm<To>(From(0)));
    ASSERT_NEAR(To(0.25), qc::transnorm<To>(quarterVal<From>), epsilon);
    ASSERT_NEAR(To(0.5), qc::transnorm<To>(halfVal<From>), epsilon);
    ASSERT_NEAR(To(0.75), qc::transnorm<To>(threeQuartersVal<From>), epsilon);
    ASSERT_EQ(To(1.0), qc::transnorm<To>(std::numeric_limits<From>::max()));
}

template <typename From, typename To>
void testTransnormUTFT()
{
    const To epsilon{To(1.0 / std::ldexp(1.0, std::numeric_limits<From>::digits))};

    static_assert(To(0.0) == qc::transnorm<To>(From(0u)));
    ASSERT_NEAR(To(0.25), qc::transnorm<To>(quarterVal<From>), epsilon);
    ASSERT_NEAR(To(0.5), qc::transnorm<To>(halfVal<From>), epsilon);
    ASSERT_NEAR(To(0.75), qc::transnorm<To>(threeQuartersVal<From>), epsilon);
    ASSERT_EQ(To(1.0), qc::transnorm<To>(std::numeric_limits<From>::max()));
}

template <typename From, typename To>
void testTransnormUTUT()
{
    const f64 epsilon(1.0 / std::ldexp(1.0, qc::min(std::numeric_limits<To>::digits, std::numeric_limits<From>::digits)));

    static_assert(To(0u) == qc::transnorm<To>(From(0u)));
    ASSERT_NEAR(0.25, f64(qc::transnorm<To>(From(quarterVal<From>))) / f64(std::numeric_limits<To>::max()), epsilon);
    ASSERT_NEAR(0.5, f64(qc::transnorm<To>(From(halfVal<From>))) / f64(std::numeric_limits<To>::max()), epsilon);
    ASSERT_NEAR(0.75, f64(qc::transnorm<To>(From(threeQuartersVal<From>))) / f64(std::numeric_limits<To>::max()), epsilon);
    ASSERT_EQ(To(std::numeric_limits<To>::max()), qc::transnorm<To>(std::numeric_limits<From>::max()));
}

template <typename From>
void testTransnormST()
{
    testTransnormSTFT<From, f32>();
    testTransnormSTFT<From, f64>();
}

template <typename From>
void testTransnormUT()
{
    testTransnormUTUT<From, u8>();
    testTransnormUTUT<From, u16>();
    testTransnormUTUT<From, u32>();
    testTransnormUTUT<From, u64>();

    testTransnormUTFT<From, f32>();
    testTransnormUTFT<From, f64>();
}

template <typename From>
void testTransnormFT()
{
    testTransnormFTST<From, s8>();
    testTransnormFTST<From, s16>();
    testTransnormFTST<From, s32>();
    testTransnormFTST<From, s64>();

    testTransnormFTUT<From, u8>();
    testTransnormFTUT<From, u16>();
    testTransnormFTUT<From, u32>();
    testTransnormFTUT<From, u64>();

    testTransnormFTFT<From, f32>();
    testTransnormFTFT<From, f64>();
}

TEST(Core, transnorm)
{
    testTransnormST<s8>();
    testTransnormST<s16>();
    testTransnormST<s32>();
    testTransnormST<s64>();

    testTransnormUT<u8>();
    testTransnormUT<u16>();
    testTransnormUT<u32>();
    testTransnormUT<u64>();

    testTransnormFT<f32>();
    testTransnormFT<f64>();
}

TEST(Core, binarySearch)
{
    qc::List<s32> v0{};
    qc::List<s32> v1{1};
    qc::List<s32> v2{1, 3};
    qc::List<s32> v3{1, 3, 5};
    qc::List<s32> v4{1, 3, 5, 7};
    qc::List<s32> v5{1, 3, 5, 7, 9};

    qc::List<s32> vv4{1, 3, 3, 5};
    qc::List<s32> vv5{1, 3, 3, 3, 5};

    qc::List<s32> vvv2{1, 1};
    qc::List<s32> vvv3{1, 1, 1};

    ASSERT_EQ(0, qc::lowerBound(v0.begin(), v0.end(), 0) - v0.begin());
    ASSERT_EQ(0, qc::upperBound(v0.begin(), v0.end(), 0) - v0.begin());

    ASSERT_EQ(0, qc::lowerBound(v1.begin(), v1.end(), 0) - v1.begin());
    ASSERT_EQ(0, qc::upperBound(v1.begin(), v1.end(), 0) - v1.begin());
    ASSERT_EQ(0, qc::lowerBound(v1.begin(), v1.end(), 1) - v1.begin());
    ASSERT_EQ(1, qc::upperBound(v1.begin(), v1.end(), 1) - v1.begin());
    ASSERT_EQ(1, qc::lowerBound(v1.begin(), v1.end(), 2) - v1.begin());
    ASSERT_EQ(1, qc::upperBound(v1.begin(), v1.end(), 2) - v1.begin());

    ASSERT_EQ(0, qc::lowerBound(v2.begin(), v2.end(), 0) - v2.begin());
    ASSERT_EQ(0, qc::upperBound(v2.begin(), v2.end(), 0) - v2.begin());
    ASSERT_EQ(0, qc::lowerBound(v2.begin(), v2.end(), 1) - v2.begin());
    ASSERT_EQ(1, qc::upperBound(v2.begin(), v2.end(), 1) - v2.begin());
    ASSERT_EQ(1, qc::lowerBound(v2.begin(), v2.end(), 2) - v2.begin());
    ASSERT_EQ(1, qc::upperBound(v2.begin(), v2.end(), 2) - v2.begin());
    ASSERT_EQ(1, qc::lowerBound(v2.begin(), v2.end(), 3) - v2.begin());
    ASSERT_EQ(2, qc::upperBound(v2.begin(), v2.end(), 3) - v2.begin());
    ASSERT_EQ(2, qc::lowerBound(v2.begin(), v2.end(), 4) - v2.begin());
    ASSERT_EQ(2, qc::upperBound(v2.begin(), v2.end(), 4) - v2.begin());

    ASSERT_EQ(0, qc::lowerBound(v3.begin(), v3.end(), 0) - v3.begin());
    ASSERT_EQ(0, qc::upperBound(v3.begin(), v3.end(), 0) - v3.begin());
    ASSERT_EQ(0, qc::lowerBound(v3.begin(), v3.end(), 1) - v3.begin());
    ASSERT_EQ(1, qc::upperBound(v3.begin(), v3.end(), 1) - v3.begin());
    ASSERT_EQ(1, qc::lowerBound(v3.begin(), v3.end(), 2) - v3.begin());
    ASSERT_EQ(1, qc::upperBound(v3.begin(), v3.end(), 2) - v3.begin());
    ASSERT_EQ(1, qc::lowerBound(v3.begin(), v3.end(), 3) - v3.begin());
    ASSERT_EQ(2, qc::upperBound(v3.begin(), v3.end(), 3) - v3.begin());
    ASSERT_EQ(2, qc::lowerBound(v3.begin(), v3.end(), 4) - v3.begin());
    ASSERT_EQ(2, qc::upperBound(v3.begin(), v3.end(), 4) - v3.begin());
    ASSERT_EQ(2, qc::lowerBound(v3.begin(), v3.end(), 5) - v3.begin());
    ASSERT_EQ(3, qc::upperBound(v3.begin(), v3.end(), 5) - v3.begin());
    ASSERT_EQ(3, qc::lowerBound(v3.begin(), v3.end(), 6) - v3.begin());
    ASSERT_EQ(3, qc::upperBound(v3.begin(), v3.end(), 6) - v3.begin());

    ASSERT_EQ(0, qc::lowerBound(v4.begin(), v4.end(), 0) - v4.begin());
    ASSERT_EQ(0, qc::upperBound(v4.begin(), v4.end(), 0) - v4.begin());
    ASSERT_EQ(0, qc::lowerBound(v4.begin(), v4.end(), 1) - v4.begin());
    ASSERT_EQ(1, qc::upperBound(v4.begin(), v4.end(), 1) - v4.begin());
    ASSERT_EQ(1, qc::lowerBound(v4.begin(), v4.end(), 2) - v4.begin());
    ASSERT_EQ(1, qc::upperBound(v4.begin(), v4.end(), 2) - v4.begin());
    ASSERT_EQ(1, qc::lowerBound(v4.begin(), v4.end(), 3) - v4.begin());
    ASSERT_EQ(2, qc::upperBound(v4.begin(), v4.end(), 3) - v4.begin());
    ASSERT_EQ(2, qc::lowerBound(v4.begin(), v4.end(), 4) - v4.begin());
    ASSERT_EQ(2, qc::upperBound(v4.begin(), v4.end(), 4) - v4.begin());
    ASSERT_EQ(2, qc::lowerBound(v4.begin(), v4.end(), 5) - v4.begin());
    ASSERT_EQ(3, qc::upperBound(v4.begin(), v4.end(), 5) - v4.begin());
    ASSERT_EQ(3, qc::lowerBound(v4.begin(), v4.end(), 6) - v4.begin());
    ASSERT_EQ(3, qc::upperBound(v4.begin(), v4.end(), 6) - v4.begin());
    ASSERT_EQ(3, qc::lowerBound(v4.begin(), v4.end(), 7) - v4.begin());
    ASSERT_EQ(4, qc::upperBound(v4.begin(), v4.end(), 7) - v4.begin());
    ASSERT_EQ(4, qc::lowerBound(v4.begin(), v4.end(), 8) - v4.begin());
    ASSERT_EQ(4, qc::upperBound(v4.begin(), v4.end(), 8) - v4.begin());

    ASSERT_EQ(0, qc::lowerBound(v5.begin(), v5.end(),  0) - v5.begin());
    ASSERT_EQ(0, qc::upperBound(v5.begin(), v5.end(),  0) - v5.begin());
    ASSERT_EQ(0, qc::lowerBound(v5.begin(), v5.end(),  1) - v5.begin());
    ASSERT_EQ(1, qc::upperBound(v5.begin(), v5.end(),  1) - v5.begin());
    ASSERT_EQ(1, qc::lowerBound(v5.begin(), v5.end(),  2) - v5.begin());
    ASSERT_EQ(1, qc::upperBound(v5.begin(), v5.end(),  2) - v5.begin());
    ASSERT_EQ(1, qc::lowerBound(v5.begin(), v5.end(),  3) - v5.begin());
    ASSERT_EQ(2, qc::upperBound(v5.begin(), v5.end(),  3) - v5.begin());
    ASSERT_EQ(2, qc::lowerBound(v5.begin(), v5.end(),  4) - v5.begin());
    ASSERT_EQ(2, qc::upperBound(v5.begin(), v5.end(),  4) - v5.begin());
    ASSERT_EQ(2, qc::lowerBound(v5.begin(), v5.end(),  5) - v5.begin());
    ASSERT_EQ(3, qc::upperBound(v5.begin(), v5.end(),  5) - v5.begin());
    ASSERT_EQ(3, qc::lowerBound(v5.begin(), v5.end(),  6) - v5.begin());
    ASSERT_EQ(3, qc::upperBound(v5.begin(), v5.end(),  6) - v5.begin());
    ASSERT_EQ(3, qc::lowerBound(v5.begin(), v5.end(),  7) - v5.begin());
    ASSERT_EQ(4, qc::upperBound(v5.begin(), v5.end(),  7) - v5.begin());
    ASSERT_EQ(4, qc::lowerBound(v5.begin(), v5.end(),  8) - v5.begin());
    ASSERT_EQ(4, qc::upperBound(v5.begin(), v5.end(),  8) - v5.begin());
    ASSERT_EQ(4, qc::lowerBound(v5.begin(), v5.end(),  9) - v5.begin());
    ASSERT_EQ(5, qc::upperBound(v5.begin(), v5.end(),  9) - v5.begin());
    ASSERT_EQ(5, qc::lowerBound(v5.begin(), v5.end(), 10) - v5.begin());
    ASSERT_EQ(5, qc::upperBound(v5.begin(), v5.end(), 10) - v5.begin());

    ASSERT_EQ(0, qc::lowerBound(vv4.begin(), vv4.end(), 0) - vv4.begin());
    ASSERT_EQ(0, qc::upperBound(vv4.begin(), vv4.end(), 0) - vv4.begin());
    ASSERT_EQ(0, qc::lowerBound(vv4.begin(), vv4.end(), 1) - vv4.begin());
    ASSERT_EQ(1, qc::upperBound(vv4.begin(), vv4.end(), 1) - vv4.begin());
    ASSERT_EQ(1, qc::lowerBound(vv4.begin(), vv4.end(), 2) - vv4.begin());
    ASSERT_EQ(1, qc::upperBound(vv4.begin(), vv4.end(), 2) - vv4.begin());
    ASSERT_EQ(1, qc::lowerBound(vv4.begin(), vv4.end(), 3) - vv4.begin());
    ASSERT_EQ(3, qc::upperBound(vv4.begin(), vv4.end(), 3) - vv4.begin());
    ASSERT_EQ(3, qc::lowerBound(vv4.begin(), vv4.end(), 4) - vv4.begin());
    ASSERT_EQ(3, qc::upperBound(vv4.begin(), vv4.end(), 4) - vv4.begin());
    ASSERT_EQ(3, qc::lowerBound(vv4.begin(), vv4.end(), 5) - vv4.begin());
    ASSERT_EQ(4, qc::upperBound(vv4.begin(), vv4.end(), 5) - vv4.begin());
    ASSERT_EQ(4, qc::lowerBound(vv4.begin(), vv4.end(), 6) - vv4.begin());
    ASSERT_EQ(4, qc::upperBound(vv4.begin(), vv4.end(), 6) - vv4.begin());

    ASSERT_EQ(0, qc::lowerBound(vv5.begin(), vv5.end(), 0) - vv5.begin());
    ASSERT_EQ(0, qc::upperBound(vv5.begin(), vv5.end(), 0) - vv5.begin());
    ASSERT_EQ(0, qc::lowerBound(vv5.begin(), vv5.end(), 1) - vv5.begin());
    ASSERT_EQ(1, qc::upperBound(vv5.begin(), vv5.end(), 1) - vv5.begin());
    ASSERT_EQ(1, qc::lowerBound(vv5.begin(), vv5.end(), 2) - vv5.begin());
    ASSERT_EQ(1, qc::upperBound(vv5.begin(), vv5.end(), 2) - vv5.begin());
    ASSERT_EQ(1, qc::lowerBound(vv5.begin(), vv5.end(), 3) - vv5.begin());
    ASSERT_EQ(4, qc::upperBound(vv5.begin(), vv5.end(), 3) - vv5.begin());
    ASSERT_EQ(4, qc::lowerBound(vv5.begin(), vv5.end(), 4) - vv5.begin());
    ASSERT_EQ(4, qc::upperBound(vv5.begin(), vv5.end(), 4) - vv5.begin());
    ASSERT_EQ(4, qc::lowerBound(vv5.begin(), vv5.end(), 5) - vv5.begin());
    ASSERT_EQ(5, qc::upperBound(vv5.begin(), vv5.end(), 5) - vv5.begin());
    ASSERT_EQ(5, qc::lowerBound(vv5.begin(), vv5.end(), 6) - vv5.begin());
    ASSERT_EQ(5, qc::upperBound(vv5.begin(), vv5.end(), 6) - vv5.begin());

    ASSERT_EQ(0, qc::lowerBound(vvv2.begin(), vvv2.end(), 0) - vvv2.begin());
    ASSERT_EQ(0, qc::upperBound(vvv2.begin(), vvv2.end(), 0) - vvv2.begin());
    ASSERT_EQ(0, qc::lowerBound(vvv2.begin(), vvv2.end(), 1) - vvv2.begin());
    ASSERT_EQ(2, qc::upperBound(vvv2.begin(), vvv2.end(), 1) - vvv2.begin());
    ASSERT_EQ(2, qc::lowerBound(vvv2.begin(), vvv2.end(), 2) - vvv2.begin());
    ASSERT_EQ(2, qc::upperBound(vvv2.begin(), vvv2.end(), 2) - vvv2.begin());

    ASSERT_EQ(0, qc::lowerBound(vvv3.begin(), vvv3.end(), 0) - vvv3.begin());
    ASSERT_EQ(0, qc::upperBound(vvv3.begin(), vvv3.end(), 0) - vvv3.begin());
    ASSERT_EQ(0, qc::lowerBound(vvv3.begin(), vvv3.end(), 1) - vvv3.begin());
    ASSERT_EQ(3, qc::upperBound(vvv3.begin(), vvv3.end(), 1) - vvv3.begin());
    ASSERT_EQ(3, qc::lowerBound(vvv3.begin(), vvv3.end(), 2) - vvv3.begin());
    ASSERT_EQ(3, qc::upperBound(vvv3.begin(), vvv3.end(), 2) - vvv3.begin());
}

TEST(Core, types)
{
    struct Dummy {};

    static_assert(std::same_as<qc::LargerOf<s16, s8>, s16>);
    static_assert(std::same_as<qc::LargerOf<s32, f64>, f64>);

    static_assert(std::same_as<qc::Common<s8, s8>, s8>);
    static_assert(std::same_as<qc::Common<s8, s64>, s64>);
    static_assert(std::same_as<qc::Common<s64, s8>, s64>);
    static_assert(std::same_as<qc::Common<s64, s64>, s64>);

    static_assert(std::same_as<qc::Common<u8, u8>, u8>);
    static_assert(std::same_as<qc::Common<u8, u64>, u64>);
    static_assert(std::same_as<qc::Common<u64, u8>, u64>);
    static_assert(std::same_as<qc::Common<u64, u64>, u64>);

    static_assert(std::same_as<qc::Common<u8, s8>, s16>);
    static_assert(std::same_as<qc::Common<s8, u8>, s16>);
    static_assert(std::same_as<qc::Common<u8, s16>, s16>);
    static_assert(std::same_as<qc::Common<s16, u8>, s16>);
    static_assert(std::same_as<qc::Common<u8, s32>, s32>);
    static_assert(std::same_as<qc::Common<s32, u8>, s32>);
    static_assert(std::same_as<qc::Common<u8, s64>, s64>);
    static_assert(std::same_as<qc::Common<s64, u8>, s64>);

    static_assert(std::same_as<qc::Common<u16, s8>, s32>);
    static_assert(std::same_as<qc::Common<s8, u16>, s32>);
    static_assert(std::same_as<qc::Common<u16, s16>, s32>);
    static_assert(std::same_as<qc::Common<s16, u16>, s32>);
    static_assert(std::same_as<qc::Common<u16, s32>, s32>);
    static_assert(std::same_as<qc::Common<s32, u16>, s32>);
    static_assert(std::same_as<qc::Common<u16, s64>, s64>);
    static_assert(std::same_as<qc::Common<s64, u16>, s64>);

    static_assert(std::same_as<qc::Common<u32, s8>, s64>);
    static_assert(std::same_as<qc::Common<s8, u32>, s64>);
    static_assert(std::same_as<qc::Common<u32, s16>, s64>);
    static_assert(std::same_as<qc::Common<s16, u32>, s64>);
    static_assert(std::same_as<qc::Common<u32, s32>, s64>);
    static_assert(std::same_as<qc::Common<s32, u32>, s64>);
    static_assert(std::same_as<qc::Common<u32, s64>, s64>);
    static_assert(std::same_as<qc::Common<s64, u32>, s64>);

    static_assert(std::same_as<qc::Common<f32, f32>, f32>);
    static_assert(std::same_as<qc::Common<f32, f64>, f64>);
    static_assert(std::same_as<qc::Common<f64, f32>, f64>);
    static_assert(std::same_as<qc::Common<f64, f64>, f64>);

    static_assert(OneOf<Dummy, Dummy>);
    static_assert(!OneOf<Dummy, void>);
    static_assert(OneOf<Dummy, Dummy, Dummy>);
    static_assert(OneOf<Dummy, Dummy, void>);
    static_assert(OneOf<Dummy, void, Dummy>);
    static_assert(!OneOf<Dummy, void, void>);
    static_assert(OneOf<Dummy, void, void, Dummy, void, void>);
    static_assert(!OneOf<Dummy, void, void, void, void, void>);

    static_assert(Same<Dummy, Dummy>);
    static_assert(Same<Dummy &, Dummy &>);
    static_assert(Same<Dummy *, Dummy *>);
    static_assert(Same<Dummy &&, Dummy &&>);
    static_assert(!Same<Dummy, Dummy &>);
    static_assert(!Same<Dummy, Dummy *>);
    static_assert(!Same<Dummy &, Dummy &&>);
    static_assert(!Same<Dummy &, const Dummy &>);
    static_assert(!Same<Dummy *, const Dummy *>);
    static_assert(!Same<Dummy &&, const Dummy &&>);

    static_assert(Sameish<Dummy, Dummy>);
    static_assert(Sameish<const Dummy, Dummy>);
    static_assert(Sameish<Dummy &, Dummy>);
    static_assert(Sameish<const Dummy &, Dummy>);
    static_assert(Sameish<qc::CArray<Dummy, 8u>, Dummy *>);

    static_assert(Void<void>);
    static_assert(!Void<s32>);

    static_assert(Boolean<bool>);
    static_assert(!Boolean<s32>);

    static_assert(Integral<s8>);
    static_assert(Integral<s16>);
    static_assert(Integral<s32>);
    static_assert(Integral<s64>);
    static_assert(Integral<u8>);
    static_assert(Integral<u16>);
    static_assert(Integral<u32>);
    static_assert(Integral<u64>);
    static_assert(!Integral<f32>);
    static_assert(!Integral<f64>);
    static_assert(!Integral<bool>);
    static_assert(!Integral<char>);
    static_assert(!Integral<void *>);
    static_assert(!Integral<TestEnum>);

    static_assert(SignedIntegral<s8>);
    static_assert(SignedIntegral<s16>);
    static_assert(SignedIntegral<s32>);
    static_assert(SignedIntegral<s64>);
    static_assert(!SignedIntegral<u8>);
    static_assert(!SignedIntegral<u16>);
    static_assert(!SignedIntegral<u32>);
    static_assert(!SignedIntegral<u64>);
    static_assert(!SignedIntegral<f32>);
    static_assert(!SignedIntegral<f64>);
    static_assert(!SignedIntegral<bool>);
    static_assert(!SignedIntegral<char>);
    static_assert(!SignedIntegral<void *>);
    static_assert(!SignedIntegral<TestEnum>);

    static_assert(!UnsignedIntegral<s8>);
    static_assert(!UnsignedIntegral<s16>);
    static_assert(!UnsignedIntegral<s32>);
    static_assert(!UnsignedIntegral<s64>);
    static_assert(UnsignedIntegral<u8>);
    static_assert(UnsignedIntegral<u16>);
    static_assert(UnsignedIntegral<u32>);
    static_assert(UnsignedIntegral<u64>);
    static_assert(!UnsignedIntegral<f32>);
    static_assert(!UnsignedIntegral<f64>);
    static_assert(!UnsignedIntegral<bool>);
    static_assert(!UnsignedIntegral<char>);
    static_assert(!UnsignedIntegral<void *>);
    static_assert(!UnsignedIntegral<TestEnum>);

    static_assert(!Floating<s8>);
    static_assert(!Floating<s16>);
    static_assert(!Floating<s32>);
    static_assert(!Floating<s64>);
    static_assert(!Floating<u8>);
    static_assert(!Floating<u16>);
    static_assert(!Floating<u32>);
    static_assert(!Floating<u64>);
    static_assert(Floating<f32>);
    static_assert(Floating<f64>);
    static_assert(!Floating<bool>);
    static_assert(!Floating<char>);
    static_assert(!Floating<void *>);
    static_assert(!Floating<TestEnum>);

    static_assert(Numeric<s8>);
    static_assert(Numeric<s16>);
    static_assert(Numeric<s32>);
    static_assert(Numeric<s64>);
    static_assert(Numeric<u8>);
    static_assert(Numeric<u16>);
    static_assert(Numeric<u32>);
    static_assert(Numeric<u64>);
    static_assert(Numeric<f32>);
    static_assert(Numeric<f64>);
    static_assert(!Numeric<bool>);
    static_assert(!Numeric<char>);
    static_assert(!Numeric<void *>);
    static_assert(!Numeric<TestEnum>);

    static_assert(Signed<s8>);
    static_assert(Signed<s16>);
    static_assert(Signed<s32>);
    static_assert(Signed<s64>);
    static_assert(!Signed<u8>);
    static_assert(!Signed<u16>);
    static_assert(!Signed<u32>);
    static_assert(!Signed<u64>);
    static_assert(Signed<f32>);
    static_assert(Signed<f64>);
    static_assert(!Signed<bool>);
    static_assert(!Signed<char>);
    static_assert(!Signed<void *>);
    static_assert(!Signed<TestEnum>);

    static_assert(!Unsigned<s8>);
    static_assert(!Unsigned<s16>);
    static_assert(!Unsigned<s32>);
    static_assert(!Unsigned<s64>);
    static_assert(Unsigned<u8>);
    static_assert(Unsigned<u16>);
    static_assert(Unsigned<u32>);
    static_assert(Unsigned<u64>);
    static_assert(!Unsigned<f32>);
    static_assert(!Unsigned<f64>);
    static_assert(!Unsigned<bool>);
    static_assert(!Unsigned<char>);
    static_assert(!Unsigned<void *>);
    static_assert(!Unsigned<TestEnum>);

    static_assert(!Enum<s8>);
    static_assert(!Enum<s16>);
    static_assert(!Enum<s32>);
    static_assert(!Enum<s64>);
    static_assert(!Enum<u8>);
    static_assert(!Enum<u16>);
    static_assert(!Enum<u32>);
    static_assert(!Enum<u64>);
    static_assert(!Enum<f32>);
    static_assert(!Enum<f64>);
    static_assert(!Enum<bool>);
    static_assert(!Enum<char>);
    static_assert(!Enum<void *>);
    static_assert(Enum<TestEnum>);

    static_assert(EnumOrBoolean<TestEnum>);
    static_assert(EnumOrBoolean<bool>);
    static_assert(!EnumOrBoolean<s32>);

    static_assert(qc::EqualityComparable<s32, s32>);
    static_assert(qc::EqualityComparable<s32, f64>);
    static_assert(qc::EqualityComparable<s32 *, s32 *>);
    static_assert(qc::EqualityComparable<s32 *, const s32 *>);
    static_assert(qc::EqualityComparable<s32 *, void *>);
    static_assert(!qc::EqualityComparable<s32, s32 *>);

    static_assert(qc::ImplicitlyConvertibleTo<u32, u64>);
    static_assert(!qc::ImplicitlyConvertibleTo<u64, u32>);
    static_assert(!qc::ImplicitlyConvertibleTo<f32, u32>);
    static_assert(qc::ImplicitlyConvertibleTo<f32 *, void *>);
    static_assert(!qc::ImplicitlyConvertibleTo<void *, f32 *>);

    static_assert(qc::ExplicitlyConvertibleTo<u32, u64>);
    static_assert(qc::ExplicitlyConvertibleTo<u64, u32>);
    static_assert(qc::ExplicitlyConvertibleTo<f32, u32>);
    static_assert(!qc::ExplicitlyConvertibleTo<f32, f32 *>);
    static_assert(qc::ExplicitlyConvertibleTo<f32 *, void *>);
    static_assert(qc::ExplicitlyConvertibleTo<void *, f32 *>);

    static_assert(std::is_same_v<qc::ConstIf<s32, true>, const s32>);
    static_assert(std::is_same_v<qc::ConstIf<s32, false>, s32>);
    static_assert(std::is_same_v<qc::ConstIf<const s32, true>, const s32>);
    static_assert(std::is_same_v<qc::ConstIf<const s32, false>, s32>);

    static_assert(std::is_same_v<qc::ConstAs<s32, f32>, s32>);
    static_assert(std::is_same_v<qc::ConstAs<s32, const f32>, const s32>);
    static_assert(std::is_same_v<qc::ConstAs<const s32, f32>, s32>);
    static_assert(std::is_same_v<qc::ConstAs<const s32, const f32>, const s32>);

    static_assert(qc::CommonExists<s8, s64>);
    static_assert(qc::CommonExists<u8, u64>);
    static_assert(qc::CommonExists<s8, u8>);
    static_assert(qc::CommonExists<s8, u16>);
    static_assert(qc::CommonExists<s8, u32>);
    static_assert(!qc::CommonExists<s8, u64>);
    static_assert(qc::CommonExists<s16, u8>);
    static_assert(qc::CommonExists<s16, u16>);
    static_assert(qc::CommonExists<s16, u32>);
    static_assert(!qc::CommonExists<s16, u64>);
    static_assert(qc::CommonExists<s32, u8>);
    static_assert(qc::CommonExists<s32, u16>);
    static_assert(qc::CommonExists<s32, u32>);
    static_assert(!qc::CommonExists<s32, u64>);
    static_assert(qc::CommonExists<s64, u8>);
    static_assert(qc::CommonExists<s64, u16>);
    static_assert(qc::CommonExists<s64, u32>);
    static_assert(!qc::CommonExists<s64, u64>);

    static_assert(qc::InclusiveSuperOf<s64, s64>);
    static_assert(qc::InclusiveSuperOf<u64, u64>);
    static_assert(qc::InclusiveSuperOf<f64, f64>);

    static_assert(!qc::ExclusiveSuperOf<s64, s64>);
    static_assert(!qc::ExclusiveSuperOf<u64, u64>);
    static_assert(!qc::ExclusiveSuperOf<f64, f64>);

    static_assert(qc::InclusiveSuperOf<s64, s64>);
    static_assert(qc::InclusiveSuperOf<s64, s8>);
    static_assert(!qc::InclusiveSuperOf<s8, s64>);
    static_assert(qc::InclusiveSuperOf<u64, u64>);
    static_assert(qc::InclusiveSuperOf<u64, u8>);
    static_assert(!qc::InclusiveSuperOf<u8, u64>);
    static_assert(qc::InclusiveSuperOf<f64, f64>);
    static_assert(qc::InclusiveSuperOf<f64, f32>);
    static_assert(!qc::InclusiveSuperOf<f32, f64>);

    static_assert(!qc::ExclusiveSuperOf<s64, s64>);
    static_assert(qc::ExclusiveSuperOf<s64, s8>);
    static_assert(!qc::ExclusiveSuperOf<s8, s64>);
    static_assert(!qc::ExclusiveSuperOf<u64, u64>);
    static_assert(qc::ExclusiveSuperOf<u64, u8>);
    static_assert(!qc::ExclusiveSuperOf<u8, u64>);
    static_assert(!qc::ExclusiveSuperOf<f64, f64>);
    static_assert(qc::ExclusiveSuperOf<f64, f32>);
    static_assert(!qc::ExclusiveSuperOf<f32, f64>);

    static_assert(qc::InclusiveSuperOf<s16, u8>);
    static_assert(qc::InclusiveSuperOf<s32, u16>);
    static_assert(qc::InclusiveSuperOf<s64, u32>);
    static_assert(!qc::InclusiveSuperOf<u8, s8>);
    static_assert(!qc::InclusiveSuperOf<u16, s16>);
    static_assert(!qc::InclusiveSuperOf<u32, s32>);
    static_assert(!qc::InclusiveSuperOf<u64, s64>);

    static_assert(qc::ExclusiveSuperOf<s16, u8>);
    static_assert(qc::ExclusiveSuperOf<s32, u16>);
    static_assert(qc::ExclusiveSuperOf<s64, u32>);
    static_assert(!qc::ExclusiveSuperOf<u8, s8>);
    static_assert(!qc::ExclusiveSuperOf<u16, s16>);
    static_assert(!qc::ExclusiveSuperOf<u32, s32>);
    static_assert(!qc::ExclusiveSuperOf<u64, s64>);

    static_assert(qc::InclusiveSubOf<s64, s64>);
    static_assert(qc::InclusiveSubOf<u64, u64>);
    static_assert(qc::InclusiveSubOf<f64, f64>);

    static_assert(!qc::ExclusiveSubOf<s64, s64>);
    static_assert(!qc::ExclusiveSubOf<u64, u64>);
    static_assert(!qc::ExclusiveSubOf<f64, f64>);

    static_assert(qc::InclusiveSubOf<s64, s64>);
    static_assert(qc::InclusiveSubOf<s8, s64>);
    static_assert(!qc::InclusiveSubOf<s64, s8>);
    static_assert(qc::InclusiveSubOf<u64, u64>);
    static_assert(qc::InclusiveSubOf<u8, u64>);
    static_assert(!qc::InclusiveSubOf<u64, u8>);
    static_assert(qc::InclusiveSubOf<f64, f64>);
    static_assert(qc::InclusiveSubOf<f32, f64>);
    static_assert(!qc::InclusiveSubOf<f64, f32>);

    static_assert(!qc::ExclusiveSubOf<s64, s64>);
    static_assert(qc::ExclusiveSubOf<s8, s64>);
    static_assert(!qc::ExclusiveSubOf<s64, s8>);
    static_assert(!qc::ExclusiveSubOf<u64, u64>);
    static_assert(qc::ExclusiveSubOf<u8, u64>);
    static_assert(!qc::ExclusiveSubOf<u64, u8>);
    static_assert(!qc::ExclusiveSubOf<f64, f64>);
    static_assert(qc::ExclusiveSubOf<f32, f64>);
    static_assert(!qc::ExclusiveSubOf<f64, f32>);

    static_assert(qc::InclusiveSubOf<u8, s16>);
    static_assert(qc::InclusiveSubOf<u16, s32>);
    static_assert(qc::InclusiveSubOf<u32, s64>);
    static_assert(!qc::InclusiveSubOf<s8, u8>);
    static_assert(!qc::InclusiveSubOf<s16, u16>);
    static_assert(!qc::InclusiveSubOf<s32, u32>);
    static_assert(!qc::InclusiveSubOf<s64, u64>);

    static_assert(qc::ExclusiveSubOf<u8, s16>);
    static_assert(qc::ExclusiveSubOf<u16, s32>);
    static_assert(qc::ExclusiveSubOf<u32, s64>);
    static_assert(!qc::ExclusiveSubOf<s8, u8>);
    static_assert(!qc::ExclusiveSubOf<s16, u16>);
    static_assert(!qc::ExclusiveSubOf<s32, u32>);
    static_assert(!qc::ExclusiveSubOf<s64, u64>);

    static_assert(qc::InclusiveSignedSuperOf<s64, s64>);
    static_assert(qc::InclusiveSignedSuperOf<s64, s32>);
    static_assert(!qc::InclusiveSignedSuperOf<s32, s64>);
    static_assert(!qc::InclusiveSignedSuperOf<s64, u8>);
    static_assert(!qc::InclusiveSignedSuperOf<s64, f32>);

    static_assert(!qc::ExclusiveSignedSuperOf<s64, s64>);
    static_assert(qc::ExclusiveSignedSuperOf<s64, s32>);
    static_assert(!qc::ExclusiveSignedSuperOf<s32, s64>);
    static_assert(!qc::ExclusiveSignedSuperOf<s64, u8>);
    static_assert(!qc::ExclusiveSignedSuperOf<s64, f32>);

    static_assert(qc::InclusiveSignedSubOf<s64, s64>);
    static_assert(qc::InclusiveSignedSubOf<s32, s64>);
    static_assert(!qc::InclusiveSignedSubOf<s64, s32>);
    static_assert(!qc::InclusiveSignedSubOf<u8, s64>);
    static_assert(!qc::InclusiveSignedSubOf<f32, s64>);

    static_assert(!qc::ExclusiveSignedSubOf<s64, s64>);
    static_assert(qc::ExclusiveSignedSubOf<s32, s64>);
    static_assert(!qc::ExclusiveSignedSubOf<s64, s32>);
    static_assert(!qc::ExclusiveSignedSubOf<u8, s64>);
    static_assert(!qc::ExclusiveSignedSubOf<f32, s64>);

    static_assert(qc::InclusiveUnsignedSuperOf<u64, u64>);
    static_assert(qc::InclusiveUnsignedSuperOf<u64, u32>);
    static_assert(!qc::InclusiveUnsignedSuperOf<u32, u64>);
    static_assert(!qc::InclusiveUnsignedSuperOf<u64, s8>);
    static_assert(!qc::InclusiveUnsignedSuperOf<u64, f32>);

    static_assert(!qc::ExclusiveUnsignedSuperOf<u64, u64>);
    static_assert(qc::ExclusiveUnsignedSuperOf<u64, u32>);
    static_assert(!qc::ExclusiveUnsignedSuperOf<u32, u64>);
    static_assert(!qc::ExclusiveUnsignedSuperOf<u64, s8>);
    static_assert(!qc::ExclusiveUnsignedSuperOf<u64, f32>);

    static_assert(qc::InclusiveUnsignedSubOf<u64, u64>);
    static_assert(qc::InclusiveUnsignedSubOf<u32, u64>);
    static_assert(!qc::InclusiveUnsignedSubOf<u64, u32>);
    static_assert(!qc::InclusiveUnsignedSubOf<s8, u64>);
    static_assert(!qc::InclusiveUnsignedSubOf<f32, u64>);

    static_assert(!qc::ExclusiveUnsignedSubOf<u64, u64>);
    static_assert(qc::ExclusiveUnsignedSubOf<u32, u64>);
    static_assert(!qc::ExclusiveUnsignedSubOf<u64, u32>);
    static_assert(!qc::ExclusiveUnsignedSubOf<s8, u64>);
    static_assert(!qc::ExclusiveUnsignedSubOf<f32, u64>);

    static_assert(qc::InclusiveFloatingSuperOf<f64, f64>);
    static_assert(qc::InclusiveFloatingSuperOf<f64, f32>);
    static_assert(!qc::InclusiveFloatingSuperOf<f32, f64>);
    static_assert(!qc::InclusiveFloatingSuperOf<f32, u8>);
    static_assert(!qc::InclusiveFloatingSuperOf<f32, s8>);

    static_assert(!qc::ExclusiveFloatingSuperOf<f64, f64>);
    static_assert(qc::ExclusiveFloatingSuperOf<f64, f32>);
    static_assert(!qc::ExclusiveFloatingSuperOf<f32, f64>);
    static_assert(!qc::ExclusiveFloatingSuperOf<f32, u8>);
    static_assert(!qc::ExclusiveFloatingSuperOf<f32, s8>);

    static_assert(qc::InclusiveFloatingSubOf<f64, f64>);
    static_assert(qc::InclusiveFloatingSubOf<f32, f64>);
    static_assert(!qc::InclusiveFloatingSubOf<f64, f32>);
    static_assert(!qc::InclusiveFloatingSubOf<u8, f32>);
    static_assert(!qc::InclusiveFloatingSubOf<s8, f32>);

    static_assert(!qc::ExclusiveFloatingSubOf<f64, f64>);
    static_assert(qc::ExclusiveFloatingSubOf<f32, f64>);
    static_assert(!qc::ExclusiveFloatingSubOf<f64, f32>);
    static_assert(!qc::ExclusiveFloatingSubOf<u8, f32>);
    static_assert(!qc::ExclusiveFloatingSubOf<s8, f32>);
}

TEST(Core, abort)
{
    ASSERT_DEATH(ABORT(), "");
    ABORT_IF(false);
    ASSERT_DEATH(ABORT_IF(true), "");
}

TEST(Core, assert)
{
    ASSERT(true);
    ASSERT_DEBUG_DEATH(ASSERT(false), "");
}

TEST(Core, fail)
{
    const auto fail{[]() -> bool { FAIL(); }};
    ASSERT_FALSE(fail());

    const auto failIf{[](const bool condition) -> bool { FAIL_IF(condition); return true; }};
    ASSERT_TRUE(failIf(false));
    ASSERT_FALSE(failIf(true));
}

TEST(Core, checkResult)
{
    s32 v;
    const auto doThing{[&v](const bool succeed) {++v; return succeed; }};

    v = 0;
    CHECK_RESULT(doThing(true));
    ASSERT_EQ(v, 1);
    ASSERT_DEATH(CHECK_RESULT(doThing(false)), "");

    v = 0;
    CHECK_RESULT_EXT(doThing(true), r);
    ASSERT_EQ(v, 1);
    ASSERT_DEATH(CHECK_RESULT_EXT(doThing(false), r), "");

    v = 0;
    CHECK_RESULT_DEBUG(doThing(true));
    ASSERT_EQ(v, 1);
    ASSERT_DEBUG_DEATH(CHECK_RESULT_DEBUG(doThing(false)), "");
    if constexpr (!qc::debug)
    {
        ASSERT_EQ(v, 2);
    }

    v = 0;
    CHECK_RESULT_EXT_DEBUG(doThing(true), r);
    ASSERT_EQ(v, 1);
    ASSERT_DEBUG_DEATH(CHECK_RESULT_EXT_DEBUG(doThing(false), r), "");
    if constexpr (!qc::debug)
    {
        ASSERT_EQ(v, 2);
    }
}

TEST(Core, scopeGuard)
{
    static thread_local bool called;
    const auto proc{[]() { called = true; }};

    called = false;
    {
        qc::ScopeGuard guard1{proc};
    }
    ASSERT_TRUE(called);

    called = false;
    {
        qc::ScopeGuard guard2{static_cast<void (*)()>(proc)};
    }
    ASSERT_TRUE(called);

    called = false;
    {
        qc::ScopeGuard guard3{std::function{proc}};
    }
    ASSERT_TRUE(called);

    called = false;
    {
        qc::ScopeGuard guard3{proc};
        guard3.release();
    }
    ASSERT_FALSE(called);
}

template <Floating F, SignedIntegral I>
static void testRound(const I v)
{
    ASSERT_EQ(qc::round<I>(F(v)), v);
    ASSERT_EQ(qc::round<I>(F(v) + F(0.1)), v);
    ASSERT_EQ(qc::round<I>(F(v) - F(0.1)), v);
    ASSERT_EQ(qc::round<I>(F(v) + F(0.5)), (v + (v > 0)) / 2 * 2);
    ASSERT_EQ(qc::round<I>(F(v) - F(0.5)), (v - (v < 0)) / 2 * 2);
}

template <Floating F, SignedIntegral I>
static void testRoundTT()
{
    testRound<F, I>(0);
    testRound<F, I>(1);
    testRound<F, I>(-1);
    testRound<F, I>(10);
    testRound<F, I>(-10);
    testRound<F, I>(100);
    testRound<F, I>(-100);
}

template <Floating F>
static void testRoundT()
{
    testRoundTT<F, s8>();
    testRoundTT<F, s16>();
    testRoundTT<F, s32>();
    testRoundTT<F, s64>();
}

TEST(Core, round)
{
    testRoundT<f32>();
    testRoundT<f64>();

    ASSERT_EQ(qc::round<s8>(f32(std::numeric_limits<s8>::max())), std::numeric_limits<s8>::max());
    ASSERT_EQ(qc::round<s8>(f32(std::numeric_limits<s8>::min())), std::numeric_limits<s8>::min());
    testRound<f32, s8>(std::numeric_limits<s8>::max() - 1);
    testRound<f32, s8>(std::numeric_limits<s8>::min() + 1);

    ASSERT_EQ(qc::round<s16>(f32(std::numeric_limits<s16>::max())), std::numeric_limits<s16>::max());
    ASSERT_EQ(qc::round<s16>(f32(std::numeric_limits<s16>::min())), std::numeric_limits<s16>::min());
    testRound<f32, s16>(std::numeric_limits<s16>::max() - 1);
    testRound<f32, s16>(std::numeric_limits<s16>::min() + 1);

    ASSERT_EQ(qc::round<s32>(f32(1 << 30)), 1 << 30);
    ASSERT_EQ(qc::round<s32>(f32(-(1 << 30))), -(1 << 30));

    ASSERT_EQ(qc::round<s32>(f32((1 << 24) - 1)), (1 << 24) - 1);
    ASSERT_EQ(qc::round<s32>(f32(-((1 << 24) - 1))), -((1 << 24) - 1));

    ASSERT_EQ(qc::round<s8>(f64(std::numeric_limits<s8>::max())), std::numeric_limits<s8>::max());
    ASSERT_EQ(qc::round<s8>(f64(std::numeric_limits<s8>::min())), std::numeric_limits<s8>::min());
    testRound<f64, s8>(std::numeric_limits<s8>::max() - 1);
    testRound<f64, s8>(std::numeric_limits<s8>::min() + 1);

    ASSERT_EQ(qc::round<s16>(f64(std::numeric_limits<s16>::max())), std::numeric_limits<s16>::max());
    ASSERT_EQ(qc::round<s16>(f64(std::numeric_limits<s16>::min())), std::numeric_limits<s16>::min());
    testRound<f64, s16>(std::numeric_limits<s16>::max() - 1);
    testRound<f64, s16>(std::numeric_limits<s16>::min() + 1);

    ASSERT_EQ(qc::round<s32>(f64(std::numeric_limits<s32>::max())), std::numeric_limits<s32>::max());
    ASSERT_EQ(qc::round<s32>(f64(std::numeric_limits<s32>::min())), std::numeric_limits<s32>::min());
    testRound<f64, s32>(std::numeric_limits<s32>::max() - 1);
    testRound<f64, s32>(std::numeric_limits<s32>::min() + 1);

    testRound<f64, s64>((1_s64 << 50) - 2);
    testRound<f64, s64>(-((1_s64 << 50) - 2));
}

template <Floating F, SignedIntegral I>
static void testFloor(const I v)
{
    ASSERT_EQ(qc::floor<I>(F(v) - 1.0), v - 1);
    ASSERT_EQ(qc::floor<I>(F(v) - 0.9), v - 1);
    ASSERT_EQ(qc::floor<I>(F(v) - 0.5), v - 1);
    ASSERT_EQ(qc::floor<I>(F(v) - 0.1), v - 1);
    ASSERT_EQ(qc::floor<I>(F(v)), v);
    ASSERT_EQ(qc::floor<I>(F(v) + 0.1), v);
    ASSERT_EQ(qc::floor<I>(F(v) + 0.5), v);
    ASSERT_EQ(qc::floor<I>(F(v) + 0.9), v);
    ASSERT_EQ(qc::floor<I>(F(v) + 1.0), v + 1);
}

template <Floating F, SignedIntegral I>
static void testFloorTT()
{
    testFloor<f32, I>(0);
    testFloor<f32, I>(1);
    testFloor<f32, I>(-1);
    testFloor<f32, I>(100);
    testFloor<f32, I>(-100);
}

template <Floating F>
static void testFloorT()
{
    testFloorTT<F, s8>();
    testFloorTT<F, s16>();
    testFloorTT<F, s32>();
    testFloorTT<F, s64>();
}

TEST(Core, floor)
{
    testFloorT<f32>();
    testFloorT<f64>();

    ASSERT_EQ(qc::floor<s8>(f32(std::numeric_limits<s8>::max())), std::numeric_limits<s8>::max());
    ASSERT_EQ(qc::floor<s8>(f32(std::numeric_limits<s8>::min())), std::numeric_limits<s8>::min());
    testFloor<f32, s8>(std::numeric_limits<s8>::max() - 1);
    testFloor<f32, s8>(std::numeric_limits<s8>::min() + 1);

    ASSERT_EQ(qc::floor<s16>(f32(std::numeric_limits<s16>::max())), std::numeric_limits<s16>::max());
    ASSERT_EQ(qc::floor<s16>(f32(std::numeric_limits<s16>::min())), std::numeric_limits<s16>::min());
    testFloor<f32, s16>(std::numeric_limits<s16>::max() - 1);
    testFloor<f32, s16>(std::numeric_limits<s16>::min() + 1);

    ASSERT_EQ(qc::floor<s8>(f64(std::numeric_limits<s8>::max())), std::numeric_limits<s8>::max());
    ASSERT_EQ(qc::floor<s8>(f64(std::numeric_limits<s8>::min())), std::numeric_limits<s8>::min());
    testFloor<f64, s8>(std::numeric_limits<s8>::max() - 1);
    testFloor<f64, s8>(std::numeric_limits<s8>::min() + 1);

    ASSERT_EQ(qc::floor<s16>(f64(std::numeric_limits<s16>::max())), std::numeric_limits<s16>::max());
    ASSERT_EQ(qc::floor<s16>(f64(std::numeric_limits<s16>::min())), std::numeric_limits<s16>::min());
    testFloor<f64, s16>(std::numeric_limits<s16>::max() - 1);
    testFloor<f64, s16>(std::numeric_limits<s16>::min() + 1);

    ASSERT_EQ(qc::floor<s32>(f64(std::numeric_limits<s32>::max())), std::numeric_limits<s32>::max());
    ASSERT_EQ(qc::floor<s32>(f64(std::numeric_limits<s32>::min())), std::numeric_limits<s32>::min());
    testFloor<f64, s32>(std::numeric_limits<s32>::max() - 1);
    testFloor<f64, s32>(std::numeric_limits<s32>::min() + 1);

    testFloor<f64, s64>(1_s64 << 49);
    testFloor<f64, s64>(-(1_s64 << 49));
}

template <Floating F, SignedIntegral I>
static void testCeil(const I v)
{
    ASSERT_EQ(qc::ceil<I>(F(v) - 1.0), v - 1);
    ASSERT_EQ(qc::ceil<I>(F(v) - 0.9), v);
    ASSERT_EQ(qc::ceil<I>(F(v) - 0.5), v);
    ASSERT_EQ(qc::ceil<I>(F(v) - 0.1), v);
    ASSERT_EQ(qc::ceil<I>(F(v)), v);
    ASSERT_EQ(qc::ceil<I>(F(v) + 0.1), v + 1);
    ASSERT_EQ(qc::ceil<I>(F(v) + 0.5), v + 1);
    ASSERT_EQ(qc::ceil<I>(F(v) + 0.9), v + 1);
    ASSERT_EQ(qc::ceil<I>(F(v) + 1.0), v + 1);
}

template <Floating F, SignedIntegral I>
static void testCeilTT()
{
    testCeil<f32, I>(0);
    testCeil<f32, I>(1);
    testCeil<f32, I>(-1);
    testCeil<f32, I>(100);
    testCeil<f32, I>(-100);
}

template <Floating F>
static void testCeilT()
{
    testCeilTT<F, s8>();
    testCeilTT<F, s16>();
    testCeilTT<F, s32>();
    testCeilTT<F, s64>();
}

TEST(Core, ceil)
{
    testCeilT<f32>();
    testCeilT<f64>();

    ASSERT_EQ(qc::ceil<s8>(f32(std::numeric_limits<s8>::max())), std::numeric_limits<s8>::max());
    ASSERT_EQ(qc::ceil<s8>(f32(std::numeric_limits<s8>::min())), std::numeric_limits<s8>::min());
    testCeil<f32, s8>(std::numeric_limits<s8>::max() - 1);
    testCeil<f32, s8>(std::numeric_limits<s8>::min() + 1);

    ASSERT_EQ(qc::ceil<s16>(f32(std::numeric_limits<s16>::max())), std::numeric_limits<s16>::max());
    ASSERT_EQ(qc::ceil<s16>(f32(std::numeric_limits<s16>::min())), std::numeric_limits<s16>::min());
    testCeil<f32, s16>(std::numeric_limits<s16>::max() - 1);
    testCeil<f32, s16>(std::numeric_limits<s16>::min() + 1);

    ASSERT_EQ(qc::ceil<s8>(f64(std::numeric_limits<s8>::max())), std::numeric_limits<s8>::max());
    ASSERT_EQ(qc::ceil<s8>(f64(std::numeric_limits<s8>::min())), std::numeric_limits<s8>::min());
    testCeil<f64, s8>(std::numeric_limits<s8>::max() - 1);
    testCeil<f64, s8>(std::numeric_limits<s8>::min() + 1);

    ASSERT_EQ(qc::ceil<s16>(f64(std::numeric_limits<s16>::max())), std::numeric_limits<s16>::max());
    ASSERT_EQ(qc::ceil<s16>(f64(std::numeric_limits<s16>::min())), std::numeric_limits<s16>::min());
    testCeil<f64, s16>(std::numeric_limits<s16>::max() - 1);
    testCeil<f64, s16>(std::numeric_limits<s16>::min() + 1);

    ASSERT_EQ(qc::ceil<s32>(f64(std::numeric_limits<s32>::max())), std::numeric_limits<s32>::max());
    ASSERT_EQ(qc::ceil<s32>(f64(std::numeric_limits<s32>::min())), std::numeric_limits<s32>::min());
    testCeil<f64, s32>(std::numeric_limits<s32>::max() - 1);
    testCeil<f64, s32>(std::numeric_limits<s32>::min() + 1);

    testCeil<f64, s64>(1_s64 << 49);
    testCeil<f64, s64>(-(1_s64 << 49));
}

GCC_DIAGNOSTIC_PUSH
GCC_DIAGNOSTIC_IGNORED("-Wuseless-cast")
TEST(Core, checkedCast)
{
    using qc::checkedCast;

    // To f32
    {
        ASSERT_EQ(checkedCast<f32>(std::numeric_limits<f32>::min()), std::numeric_limits<f32>::min());

        ASSERT_DEATH(static_cast<void>(checkedCast<f32>(std::numeric_limits<f64>::min())), "");

        ASSERT_EQ(checkedCast<f32>(std::numeric_limits<s8>::max()), 127.0f);

        ASSERT_EQ(checkedCast<f32>(std::numeric_limits<s16>::max()), 32767.0f);

        ASSERT_EQ(checkedCast<f32>(s32(16777216)), 16777216.0f);
        ASSERT_DEATH(static_cast<void>(checkedCast<f32>(s32(16777217))), "");

        ASSERT_EQ(checkedCast<f32>(s64(16777216)), 16777216.0f);
        ASSERT_DEATH(static_cast<void>(checkedCast<f32>(s64(16777217))), "");

        ASSERT_EQ(checkedCast<f32>(std::numeric_limits<u8>::max()), 255.0f);

        ASSERT_EQ(checkedCast<f32>(std::numeric_limits<u16>::max()), 65535.0f);

        ASSERT_EQ(checkedCast<f32>(u32(16777216u)), 16777216.0f);
        ASSERT_DEATH(static_cast<void>(checkedCast<f32>(u32(16777217u))), "");

        ASSERT_EQ(checkedCast<f32>(s64(16777216u)), 16777216.0f);
        ASSERT_DEATH(static_cast<void>(checkedCast<f32>(u64(16777217u))), "");
    }

    // To f64
    {
        ASSERT_EQ(checkedCast<f64>(std::numeric_limits<f32>::min()), std::numeric_limits<f32>::min());

        ASSERT_EQ(checkedCast<f64>(std::numeric_limits<f64>::min()), std::numeric_limits<f64>::min());

        ASSERT_EQ(checkedCast<f64>(std::numeric_limits<s8>::max()), 127.0);

        ASSERT_EQ(checkedCast<f64>(std::numeric_limits<s16>::max()), 32767.0);

        ASSERT_EQ(checkedCast<f64>(std::numeric_limits<s32>::max()), 2147483647.0);

        ASSERT_EQ(checkedCast<f64>(s64(9007199254740992)), 9007199254740992.0);
        ASSERT_DEATH(static_cast<void>(checkedCast<f64>(s64(9007199254740993))), "");

        ASSERT_EQ(checkedCast<f64>(std::numeric_limits<u8>::max()), 255.0);

        ASSERT_EQ(checkedCast<f64>(std::numeric_limits<u16>::max()), 65535.0);

        ASSERT_EQ(checkedCast<f64>(std::numeric_limits<u32>::max()), 4294967295.0);

        ASSERT_EQ(checkedCast<f64>(u64(9007199254740992u)), 9007199254740992.0);
        ASSERT_DEATH(static_cast<void>(checkedCast<f64>(u64(9007199254740993u))), "");
    }

    // To s8
    {
        ASSERT_EQ(checkedCast<s8>(127.0f), s8(127));
        ASSERT_DEATH(static_cast<void>(checkedCast<s8>(128.0f)), "");
        ASSERT_EQ(checkedCast<s8>(-128.0f), s8(-128));
        ASSERT_DEATH(static_cast<void>(checkedCast<s8>(-129.0f)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<s8>(0.5f)), "");

        ASSERT_EQ(checkedCast<s8>(127.0), s8(127));
        ASSERT_DEATH(static_cast<void>(checkedCast<s8>(128.0)), "");
        ASSERT_EQ(checkedCast<s8>(-128.0), s8(-128));
        ASSERT_DEATH(static_cast<void>(checkedCast<s8>(-129.0)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<s8>(0.5)), "");

        ASSERT_EQ(checkedCast<s8>(s8(127)), s8(127));
        ASSERT_EQ(checkedCast<s8>(s8(-128)), s8(-128));

        ASSERT_EQ(checkedCast<s8>(s16(127)), s8(127));
        ASSERT_DEATH(static_cast<void>(checkedCast<s8>(s16(128))), "");
        ASSERT_EQ(checkedCast<s8>(s16(-128)), s8(-128));
        ASSERT_DEATH(static_cast<void>(checkedCast<s8>(s16(-129))), "");

        ASSERT_EQ(checkedCast<s8>(s32(127)), s8(127));
        ASSERT_DEATH(static_cast<void>(checkedCast<s8>(s32(128))), "");
        ASSERT_EQ(checkedCast<s8>(s32(-128)), s8(-128));
        ASSERT_DEATH(static_cast<void>(checkedCast<s8>(s32(-129))), "");

        ASSERT_EQ(checkedCast<s8>(s64(127)), s8(127));
        ASSERT_DEATH(static_cast<void>(checkedCast<s8>(s64(128))), "");
        ASSERT_EQ(checkedCast<s8>(s64(-128)), s8(-128));
        ASSERT_DEATH(static_cast<void>(checkedCast<s8>(s64(-129))), "");

        ASSERT_EQ(checkedCast<s8>(u8(127u)), s8(127));
        ASSERT_DEATH(static_cast<void>(checkedCast<s8>(u8(128u))), "");

        ASSERT_EQ(checkedCast<s8>(u16(127u)), s8(127));
        ASSERT_DEATH(static_cast<void>(checkedCast<s8>(u16(128u))), "");

        ASSERT_EQ(checkedCast<s8>(u32(127u)), s8(127));
        ASSERT_DEATH(static_cast<void>(checkedCast<s8>(u32(128u))), "");

        ASSERT_EQ(checkedCast<s8>(u64(127u)), s8(127));
        ASSERT_DEATH(static_cast<void>(checkedCast<s8>(u64(128u))), "");
    }

    // To s16
    {
        ASSERT_EQ(checkedCast<s16>(32767.0f), s16(32767));
        ASSERT_DEATH(static_cast<void>(checkedCast<s16>(32768.0f)), "");
        ASSERT_EQ(checkedCast<s16>(-32768.0f), s16(-32768));
        ASSERT_DEATH(static_cast<void>(checkedCast<s16>(-32769.0f)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<s16>(0.5f)), "");

        ASSERT_EQ(checkedCast<s16>(32767.0), s16(32767));
        ASSERT_DEATH(static_cast<void>(checkedCast<s16>(32768.0)), "");
        ASSERT_EQ(checkedCast<s16>(-32768.0), s16(-32768));
        ASSERT_DEATH(static_cast<void>(checkedCast<s16>(-32769.0)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<s16>(0.5)), "");

        ASSERT_EQ(checkedCast<s16>(s8(127)), s16(127));
        ASSERT_EQ(checkedCast<s16>(s8(-128)), s16(-128));

        ASSERT_EQ(checkedCast<s16>(s16(32767)), s16(32767));
        ASSERT_EQ(checkedCast<s16>(s16(-32768)), s16(-32768));

        ASSERT_EQ(checkedCast<s16>(s32(32767)), s16(32767));
        ASSERT_DEATH(static_cast<void>(checkedCast<s16>(s32(32768))), "");
        ASSERT_EQ(checkedCast<s16>(s32(-32768)), s16(-32768));
        ASSERT_DEATH(static_cast<void>(checkedCast<s16>(s32(-32769))), "");

        ASSERT_EQ(checkedCast<s16>(s64(32767)), s16(32767));
        ASSERT_DEATH(static_cast<void>(checkedCast<s16>(s64(32768))), "");
        ASSERT_EQ(checkedCast<s16>(s64(-32768)), s16(-32768));
        ASSERT_DEATH(static_cast<void>(checkedCast<s16>(s64(-32769))), "");

        ASSERT_EQ(checkedCast<s16>(u8(255u)), s16(255));

        ASSERT_EQ(checkedCast<s16>(u16(32767u)), s16(32767));
        ASSERT_DEATH(static_cast<void>(checkedCast<s16>(u16(32768u))), "");

        ASSERT_EQ(checkedCast<s16>(u32(32767u)), s16(32767));
        ASSERT_DEATH(static_cast<void>(checkedCast<s16>(u32(32768u))), "");

        ASSERT_EQ(checkedCast<s16>(u64(32767u)), s16(32767));
        ASSERT_DEATH(static_cast<void>(checkedCast<s16>(u64(32768u))), "");
    }

    // To s32
    {
        ASSERT_EQ(checkedCast<s32>(2147483520.0f), s32(2147483520));
        ASSERT_DEATH(static_cast<void>(checkedCast<s32>(qc::gcc ? 2147483904.0f : 2147483648.0f)), "");
        ASSERT_EQ(checkedCast<s32>(-2147483648.0f), s32(-2147483648));
        ASSERT_DEATH(static_cast<void>(checkedCast<s32>(-2147483777.0f)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<s32>(0.5f)), "");

        ASSERT_EQ(checkedCast<s32>(2147483647.0), s32(2147483647));
        ASSERT_DEATH(static_cast<void>(checkedCast<s32>(2147483648.0)), "");
        ASSERT_EQ(checkedCast<s32>(-2147483648.0), s32(-2147483648));
        ASSERT_DEATH(static_cast<void>(checkedCast<s32>(-2147483649.0)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<s32>(0.5)), "");

        ASSERT_EQ(checkedCast<s32>(s8(127)), s32(127));
        ASSERT_EQ(checkedCast<s32>(s8(-128)), s32(-128));

        ASSERT_EQ(checkedCast<s32>(s16(32767)), s32(32767));
        ASSERT_EQ(checkedCast<s32>(s16(-32768)), s32(-32768));

        ASSERT_EQ(checkedCast<s32>(s32(2147483647)), s32(2147483647));
        ASSERT_EQ(checkedCast<s32>(s32(-2147483648)), s32(-2147483648));

        ASSERT_EQ(checkedCast<s32>(s64(2147483647)), s32(2147483647));
        ASSERT_DEATH(static_cast<void>(checkedCast<s32>(s64(2147483648))), "");
        ASSERT_EQ(checkedCast<s32>(s64(-2147483648)), s32(-2147483648));
        ASSERT_DEATH(static_cast<void>(checkedCast<s32>(s64(-2147483649))), "");

        ASSERT_EQ(checkedCast<s32>(u8(255u)), s32(255));

        ASSERT_EQ(checkedCast<s32>(u16(65535u)), s32(65535));

        ASSERT_EQ(checkedCast<s32>(u32(2147483647u)), s32(2147483647));
        ASSERT_DEATH(static_cast<void>(checkedCast<s32>(u32(2147483648u))), "");

        ASSERT_EQ(checkedCast<s32>(u64(2147483647u)), s32(2147483647));
        ASSERT_DEATH(static_cast<void>(checkedCast<s32>(u64(2147483648u))), "");
    }

    // To s64
    {
        ASSERT_EQ(checkedCast<s64>(9223371487098961920.0f), s64(9223371487098961920));
        ASSERT_DEATH(static_cast<void>(checkedCast<s64>(qc::gcc ? 9223373136366403584.0f : 9223372036854775808.0f)), "");
        ASSERT_EQ(checkedCast<s64>(-9223372036854775808.0f), std::numeric_limits<s64>::min());
        ASSERT_DEATH(static_cast<void>(checkedCast<s64>(-9223372586610589697.0f)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<s64>(0.5f)), "");

        ASSERT_EQ(checkedCast<s64>(9223372036854774784.0), s64(9223372036854774784));
        ASSERT_DEATH(static_cast<void>(checkedCast<s64>(qc::gcc ? 9223372036854777856.0 : 9223372036854775808.0)), "");
        ASSERT_EQ(checkedCast<s64>(-9223372036854775808.0), std::numeric_limits<s64>::min());
        ASSERT_DEATH(static_cast<void>(checkedCast<s64>(-9223372036854776833.0)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<s64>(0.5)), "");

        ASSERT_EQ(checkedCast<s64>(s8(127)), s64(127));
        ASSERT_EQ(checkedCast<s64>(s8(-128)), s64(-128));

        ASSERT_EQ(checkedCast<s64>(s16(32767)), s64(32767));
        ASSERT_EQ(checkedCast<s64>(s16(-32768)), s64(-32768));

        ASSERT_EQ(checkedCast<s64>(s32(2147483647)), s64(2147483647));
        ASSERT_EQ(checkedCast<s64>(s32(-2147483648)), s64(-2147483648));

        ASSERT_EQ(checkedCast<s64>(std::numeric_limits<s64>::max()), std::numeric_limits<s64>::max());
        ASSERT_EQ(checkedCast<s64>(std::numeric_limits<s64>::min()), std::numeric_limits<s64>::min());

        ASSERT_EQ(checkedCast<s64>(u8(255u)), s64(255));

        ASSERT_EQ(checkedCast<s64>(u16(65535u)), s64(65535));

        ASSERT_EQ(checkedCast<s64>(u32(4294967295u)), s64(4294967295));

        ASSERT_EQ(checkedCast<s64>(u64(9223372036854775807u)), std::numeric_limits<s64>::max());
        ASSERT_DEATH(static_cast<void>(checkedCast<s64>(u64(9223372036854775808u))), "");
    }

    // To u8
    {
        ASSERT_EQ(checkedCast<u8>(255.0f), u8(255u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u8>(256.0f)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<u8>(-1.0f)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<u8>(0.5f)), "");

        ASSERT_EQ(checkedCast<u8>(255.0), u8(255u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u8>(256.0)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<u8>(-1.0)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<u8>(0.5)), "");

        ASSERT_EQ(checkedCast<u8>(s8(127)), u8(127u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u8>(s8(-1))), "");

        ASSERT_EQ(checkedCast<u8>(s16(255)), u8(255u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u8>(s16(256))), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<u8>(s16(-1))), "");

        ASSERT_EQ(checkedCast<u8>(s32(255)), u8(255u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u8>(s32(256))), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<u8>(s32(-1))), "");

        ASSERT_EQ(checkedCast<u8>(s64(255)), u8(255u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u8>(s64(256))), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<u8>(s64(-1))), "");

        ASSERT_EQ(checkedCast<u8>(u8(255u)), u8(255u));

        ASSERT_EQ(checkedCast<u8>(u16(255u)), u8(255u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u8>(u16(256u))), "");

        ASSERT_EQ(checkedCast<u8>(u32(255u)), u8(255u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u8>(u32(256u))), "");

        ASSERT_EQ(checkedCast<u8>(u64(255u)), u8(255u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u8>(u64(256u))), "");
    }

    // To u16
    {
        ASSERT_EQ(checkedCast<u16>(65535.0f), u16(65535u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u16>(65536.0f)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<u16>(-1.0f)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<u16>(0.5f)), "");

        ASSERT_EQ(checkedCast<u16>(65535.0), u16(65535u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u16>(65536.0)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<u16>(-1.0)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<u16>(0.5)), "");

        ASSERT_EQ(checkedCast<u16>(s8(127)), u16(127u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u16>(s8(-1))), "");

        ASSERT_EQ(checkedCast<u16>(s16(32767)), u16(32767u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u16>(s16(-1))), "");

        ASSERT_EQ(checkedCast<u16>(s32(65535)), u16(65535u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u16>(s32(65536))), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<u16>(s32(-1))), "");

        ASSERT_EQ(checkedCast<u16>(s64(65535)), u16(65535u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u16>(s64(65536))), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<u16>(s64(-1))), "");

        ASSERT_EQ(checkedCast<u16>(u8(255u)), u16(255u));

        ASSERT_EQ(checkedCast<u16>(u16(65535u)), u16(65535u));

        ASSERT_EQ(checkedCast<u16>(u32(65535u)), u16(65535u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u16>(u32(65536u))), "");

        ASSERT_EQ(checkedCast<u16>(u64(65535u)), u16(65535u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u16>(u64(65536u))), "");
    }

    // To u32
    {
        ASSERT_EQ(checkedCast<u32>(4294967040.0f), u32(4294967040u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u32>(qc::gcc ? 4294967808.0f : 4294967296.0f)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<u32>(-1.0f)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<u32>(0.5f)), "");

        ASSERT_EQ(checkedCast<u32>(4294967295.0), u32(4294967295u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u32>(4294967296.0)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<u32>(-1.0)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<u32>(0.5)), "");

        ASSERT_EQ(checkedCast<u32>(s8(127)), u32(127u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u32>(s8(-1))), "");

        ASSERT_EQ(checkedCast<u32>(s16(32767)), u32(32767u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u32>(s16(-1))), "");

        ASSERT_EQ(checkedCast<u32>(s32(2147483647)), u32(2147483647u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u32>(s32(-1))), "");

        ASSERT_EQ(checkedCast<u32>(s64(4294967295)), u32(4294967295u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u32>(s64(4294967296))), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<u32>(s64(-1))), "");

        ASSERT_EQ(checkedCast<u32>(u8(255u)), u32(255u));

        ASSERT_EQ(checkedCast<u32>(u16(65535u)), u32(65535u));

        ASSERT_EQ(checkedCast<u32>(u32(4294967295u)), u32(4294967295u));

        ASSERT_EQ(checkedCast<u32>(u64(4294967295u)), u32(4294967295u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u32>(u64(4294967296u))), "");
    }

    // To u64
    {
        ASSERT_EQ(checkedCast<u64>(18446742974197923840.0f), u64(18446742974197923840u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u64>(qc::gcc ? 18446746272732807168.0f : 18446744073709551616.0f)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<u64>(-1.0f)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<u64>(0.5f)), "");

        ASSERT_EQ(checkedCast<u64>(18446744073709549568.0), u64(18446744073709549568u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u64>(qc::gcc ? 18446744073709555712.0 : 18446744073709551616.0)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<u64>(-1.0)), "");
        ASSERT_DEATH(static_cast<void>(checkedCast<u64>(0.5)), "");

        ASSERT_EQ(checkedCast<u64>(s8(127)), u64(127u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u64>(s8(-1))), "");

        ASSERT_EQ(checkedCast<u64>(s16(32767)), u64(32767u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u64>(s16(-1))), "");

        ASSERT_EQ(checkedCast<u64>(s32(2147483647)), u64(2147483647u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u64>(s32(-1))), "");

        ASSERT_EQ(checkedCast<u64>(s64(9223372036854775807)), u64(9223372036854775807u));
        ASSERT_DEATH(static_cast<void>(checkedCast<u64>(s64(-1))), "");

        ASSERT_EQ(checkedCast<u64>(u8(255u)), u64(255u));

        ASSERT_EQ(checkedCast<u64>(u16(65535u)), u64(65535u));

        ASSERT_EQ(checkedCast<u64>(u32(4294967295u)), u64(4294967295u));

        ASSERT_EQ(checkedCast<u64>(u64(18446744073709551615u)), u64(18446744073709551615u));
    }
}
GCC_DIAGNOSTIC_POP

TEST(Core, assertCast)
{
    ASSERT_EQ(qc::assertCast<u8>(1.0f), 1u);

    if constexpr (qc::debug)
    {
        ASSERT_DEBUG_DEATH(qc::assertCast<u8>(-1.0f), "");
    }
    else
    {
        ASSERT_EQ(qc::assertCast<u8>(-1.0f), qc::msvc ? 255u : 0u);
    }
}
