#include <qc-core/core-ext.hpp>
#include <qc-core/list.hpp>

// gtest overrides FAIL macro
#pragma push_macro("FAIL")
#include <gtest/gtest.h>
#pragma pop_macro("FAIL")

using namespace qc::types;
using namespace qc::primitives;

enum TestEnum { a, b, c };

#pragma warning(push)
#pragma warning(disable: 4101)
TEST(Core, primitives)
{
    s8 s08_;
    u8 u08_;
    s16 s16_;
    u16 u16_;
    s32 s32_;
    u32 u32_;
    f32 f32_;
    s64 s64_;
    u64 u64_;
    f64 f64_;

    schar schar_;
    uchar uchar_;
    ushort ushort_;
    uint uint_;
    ulong ulong_;
    llong llong_;
    ullong ullong_;
    ldouble ldouble_;
}
#pragma warning(pop)

#pragma warning(push)
#pragma warning(disable: 4555)
template <Floating T>
static void compileNumbersT()
{
    static_cast<void>(qc::infinity<T>);
    static_cast<void>(qc::nan<T>);
    static_cast<void>(qc::pi<T>);
    static_cast<void>(qc::e<T>);
    static_cast<void>(qc::phi<T>);
    static_cast<void>(qc::sqrt2<T>);
    static_cast<void>(qc::sqrt3<T>);
    static_cast<void>(qc::sqrt5<T>);
}
#pragma warning(pop)

TEST(Core, numbers)
{
    compileNumbersT<float>();
    compileNumbersT<double>();
}

TEST(Core, classes)
{
    qc::Duo<int> d1;
    static_cast<void>(d1.a);
    static_cast<void>(d1.b);
    static_cast<void>(d1[0u]);
    static_cast<void>(d1[1u]);
    static_cast<void>(d1[0]);
    static_cast<void>(d1[1]);
    static_cast<void>(d1[false]);
    static_cast<void>(d1[true]);
    #pragma warning(suppress: 4189)
    for (int & v : d1) {}
    ASSERT_EQ(std::distance(d1.begin(), d1.end()), 2);

    qc::Duo<int, std::string> d2;
    static_cast<void>(d2.a);
    static_cast<void>(d2.b);

    qc::Trio<int> t1;
    static_cast<void>(t1.a);
    static_cast<void>(t1.b);
    static_cast<void>(t1.c);
    static_cast<void>(d1[0u]);
    static_cast<void>(d1[1u]);
    static_cast<void>(d1[2u]);
    static_cast<void>(d1[0]);
    static_cast<void>(d1[1]);
    static_cast<void>(d1[2]);
    #pragma warning(suppress: 4189)
    for (int & v : t1) {}
    ASSERT_EQ(std::distance(t1.begin(), t1.end()), 3);

    qc::Trio<int, std::string> t2;
    static_cast<void>(t2.a);
    static_cast<void>(t2.b);
    static_cast<void>(t2.b);

    qc::Trio<int, std::string, TestEnum> t3;
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
    const double epsilon(1.0 / std::ldexp(1.0, std::numeric_limits<To>::digits));

    static_assert(To(-std::numeric_limits<To>::max()) == qc::transnorm<To>(From(-1.0)));
    ASSERT_NEAR(0.75, double(qc::transnorm<To>(From(-0.75))) / double(-std::numeric_limits<To>::max()), epsilon);
    ASSERT_NEAR(0.5, double(qc::transnorm<To>(From(-0.5))) / double(-std::numeric_limits<To>::max()), epsilon);
    ASSERT_NEAR(0.25, double(qc::transnorm<To>(From(-0.25))) / double(-std::numeric_limits<To>::max()), epsilon);
    ASSERT_EQ(To(0u), qc::transnorm<To>(From(0.0)));
    ASSERT_NEAR(0.25, double(qc::transnorm<To>(From(0.25))) / double(std::numeric_limits<To>::max()), epsilon);
    ASSERT_NEAR(0.5, double(qc::transnorm<To>(From(0.5))) / double(std::numeric_limits<To>::max()), epsilon);
    ASSERT_NEAR(0.75, double(qc::transnorm<To>(From(0.75))) / double(std::numeric_limits<To>::max()), epsilon);
    ASSERT_EQ(std::numeric_limits<To>::max(), qc::transnorm<To>(From(1.0)));

    ASSERT_GE(qc::transnorm<To>(From(-1.0) + std::numeric_limits<From>::epsilon()), qc::transnorm<To>(From(-1.0)));
    ASSERT_LE(qc::transnorm<To>(From(1.0) - std::numeric_limits<From>::epsilon()), qc::transnorm<To>(From(1.0)));
}

template <typename From, typename To>
void testTransnormFTUT()
{
    const double epsilon(1.0 / std::ldexp(1.0, std::numeric_limits<To>::digits));

    static_assert(To(0u) == qc::transnorm<To>(From(0.0)));
    ASSERT_NEAR(0.25, double(qc::transnorm<To>(From(0.25))) / double(std::numeric_limits<To>::max()), epsilon);
    ASSERT_NEAR(0.5, double(qc::transnorm<To>(From(0.5))) / double(std::numeric_limits<To>::max()), epsilon);
    ASSERT_NEAR(0.75, double(qc::transnorm<To>(From(0.75))) / double(std::numeric_limits<To>::max()), epsilon);
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
    const double epsilon(1.0 / std::ldexp(1.0, qc::min(std::numeric_limits<To>::digits, std::numeric_limits<From>::digits)));

    static_assert(To(0u) == qc::transnorm<To>(From(0u)));
    ASSERT_NEAR(0.25, double(qc::transnorm<To>(From(quarterVal<From>))) / double(std::numeric_limits<To>::max()), epsilon);
    ASSERT_NEAR(0.5, double(qc::transnorm<To>(From(halfVal<From>))) / double(std::numeric_limits<To>::max()), epsilon);
    ASSERT_NEAR(0.75, double(qc::transnorm<To>(From(threeQuartersVal<From>))) / double(std::numeric_limits<To>::max()), epsilon);
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
    qc::List<int> v0{};
    qc::List<int> v1{1};
    qc::List<int> v2{1, 3};
    qc::List<int> v3{1, 3, 5};
    qc::List<int> v4{1, 3, 5, 7};
    qc::List<int> v5{1, 3, 5, 7, 9};

    qc::List<int> vv4{1, 3, 3, 5};
    qc::List<int> vv5{1, 3, 3, 3, 5};

    qc::List<int> vvv2{1, 1};
    qc::List<int> vvv3{1, 1, 1};

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
    static_assert(std::same_as<qc::LargerOf<int, double>, double>);

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
    static_assert(OneOf<Dummy, const Dummy>);
    static_assert(!OneOf<Dummy, int>);
    static_assert(OneOf<const Dummy, Dummy>);
    static_assert(OneOf<Dummy, Dummy, Dummy>);
    static_assert(OneOf<Dummy, Dummy, int>);
    static_assert(OneOf<Dummy, int, Dummy>);
    static_assert(!OneOf<Dummy, int, int>);
    static_assert(OneOf<Dummy, int, int, Dummy, int, int>);
    static_assert(!OneOf<Dummy, int, int, int, int, int>);

    static_assert(Same<Dummy, Dummy>);
    static_assert(Same<Dummy, const Dummy>);
    static_assert(Same<Dummy &, Dummy &>);
    static_assert(Same<Dummy *, Dummy *>);
    static_assert(Same<Dummy &&, Dummy &&>);
    static_assert(!Same<Dummy, Dummy &>);
    static_assert(!Same<Dummy, Dummy *>);
    static_assert(!Same<Dummy &, Dummy &&>);
    static_assert(!Same<Dummy &, const Dummy &>);
    static_assert(!Same<Dummy *, const Dummy *>);
    static_assert(!Same<Dummy &&, const Dummy &&>);

    static_assert(Void<void>);
    static_assert(!Void<int>);

    static_assert(Boolean<bool>);
    static_assert(!Boolean<int>);

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
    static_assert(!EnumOrBoolean<int>);

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

    static_assert(qc::SuperOf<s64, s64>);
    static_assert(qc::SuperOf<s64, s8>);
    static_assert(!qc::SuperOf<s8, s64>);
    static_assert(qc::SuperOf<u64, u64>);
    static_assert(qc::SuperOf<u64, u8>);
    static_assert(!qc::SuperOf<u8, u64>);
    static_assert(qc::SuperOf<f64, f64>);
    static_assert(qc::SuperOf<f64, f32>);
    static_assert(!qc::SuperOf<f32, f64>);

    static_assert(qc::SuperOf<s16, u8>);
    static_assert(qc::SuperOf<s32, u16>);
    static_assert(qc::SuperOf<s64, u32>);
    static_assert(!qc::SuperOf<u8, s8>);
    static_assert(!qc::SuperOf<u16, s16>);
    static_assert(!qc::SuperOf<u32, s32>);
    static_assert(!qc::SuperOf<u64, s64>);

    static_assert(qc::SubOf<s64, s64>);
    static_assert(qc::SubOf<s8, s64>);
    static_assert(!qc::SubOf<s64, s8>);
    static_assert(qc::SubOf<u64, u64>);
    static_assert(qc::SubOf<u8, u64>);
    static_assert(!qc::SubOf<u64, u8>);
    static_assert(qc::SubOf<f64, f64>);
    static_assert(qc::SubOf<f32, f64>);
    static_assert(!qc::SubOf<f64, f32>);

    static_assert(qc::SubOf<u8, s16>);
    static_assert(qc::SubOf<u16, s32>);
    static_assert(qc::SubOf<u32, s64>);
    static_assert(!qc::SubOf<s8, u8>);
    static_assert(!qc::SubOf<s16, u16>);
    static_assert(!qc::SubOf<s32, u32>);
    static_assert(!qc::SubOf<s64, u64>);

    static_assert(qc::SignedSuperOf<s64, s64>);
    static_assert(qc::SignedSuperOf<s64, s32>);
    static_assert(!qc::SignedSuperOf<s32, s64>);
    static_assert(!qc::SignedSuperOf<s64, u8>);
    static_assert(!qc::SignedSuperOf<s64, f32>);

    static_assert(qc::SignedSubOf<s64, s64>);
    static_assert(qc::SignedSubOf<s32, s64>);
    static_assert(!qc::SignedSubOf<s64, s32>);
    static_assert(!qc::SignedSubOf<u8, s64>);
    static_assert(!qc::SignedSubOf<f32, s64>);

    static_assert(qc::UnsignedSuperOf<u64, u64>);
    static_assert(qc::UnsignedSuperOf<u64, u32>);
    static_assert(!qc::UnsignedSuperOf<u32, u64>);
    static_assert(!qc::UnsignedSuperOf<u64, s8>);
    static_assert(!qc::UnsignedSuperOf<u64, f32>);

    static_assert(qc::UnsignedSubOf<u64, u64>);
    static_assert(qc::UnsignedSubOf<u32, u64>);
    static_assert(!qc::UnsignedSubOf<u64, u32>);
    static_assert(!qc::UnsignedSubOf<s8, u64>);
    static_assert(!qc::UnsignedSubOf<f32, u64>);

    static_assert(qc::FloatingSuperOf<f64, f64>);
    static_assert(qc::FloatingSuperOf<f64, f32>);
    static_assert(!qc::FloatingSuperOf<f32, f64>);
    static_assert(!qc::FloatingSuperOf<f32, u8>);
    static_assert(!qc::FloatingSuperOf<f32, s8>);

    static_assert(qc::FloatingSubOf<f64, f64>);
    static_assert(qc::FloatingSubOf<f32, f64>);
    static_assert(!qc::FloatingSubOf<f64, f32>);
    static_assert(!qc::FloatingSubOf<u8, f32>);
    static_assert(!qc::FloatingSubOf<s8, f32>);
}

TEST(Core, abort)
{
    ASSERT_DEATH(ABORT(), "");
    ABORT_IF(false);
    ASSERT_DEATH(ABORT_IF(true), "");
}

TEST(Core, fail)
{
    const auto fail{[]() -> bool { FAIL(); }};
    ASSERT_FALSE(fail());

    const auto failIf{[](const bool condition) -> bool { FAIL_IF(condition); return true; }};
    ASSERT_TRUE(failIf(false));
    ASSERT_FALSE(failIf(true));
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
    testRoundT<float>();
    testRoundT<double>();

    ASSERT_EQ(qc::round<s8>(float(std::numeric_limits<s8>::max())), std::numeric_limits<s8>::max());
    ASSERT_EQ(qc::round<s8>(float(std::numeric_limits<s8>::min())), std::numeric_limits<s8>::min());
    testRound<float, s8>(std::numeric_limits<s8>::max() - 1);
    testRound<float, s8>(std::numeric_limits<s8>::min() + 1);

    ASSERT_EQ(qc::round<s16>(float(std::numeric_limits<s16>::max())), std::numeric_limits<s16>::max());
    ASSERT_EQ(qc::round<s16>(float(std::numeric_limits<s16>::min())), std::numeric_limits<s16>::min());
    testRound<float, s16>(std::numeric_limits<s16>::max() - 1);
    testRound<float, s16>(std::numeric_limits<s16>::min() + 1);

    ASSERT_EQ(qc::round<s32>(float(1 << 30)), 1 << 30);
    ASSERT_EQ(qc::round<s32>(float(-(1 << 30))), -(1 << 30));

    ASSERT_EQ(qc::round<s32>(float((1 << 24) - 1)), (1 << 24) - 1);
    ASSERT_EQ(qc::round<s32>(float(-((1 << 24) - 1))), -((1 << 24) - 1));

    ASSERT_EQ(qc::round<s8>(double(std::numeric_limits<s8>::max())), std::numeric_limits<s8>::max());
    ASSERT_EQ(qc::round<s8>(double(std::numeric_limits<s8>::min())), std::numeric_limits<s8>::min());
    testRound<double, s8>(std::numeric_limits<s8>::max() - 1);
    testRound<double, s8>(std::numeric_limits<s8>::min() + 1);

    ASSERT_EQ(qc::round<s16>(double(std::numeric_limits<s16>::max())), std::numeric_limits<s16>::max());
    ASSERT_EQ(qc::round<s16>(double(std::numeric_limits<s16>::min())), std::numeric_limits<s16>::min());
    testRound<double, s16>(std::numeric_limits<s16>::max() - 1);
    testRound<double, s16>(std::numeric_limits<s16>::min() + 1);

    ASSERT_EQ(qc::round<s32>(double(std::numeric_limits<s32>::max())), std::numeric_limits<s32>::max());
    ASSERT_EQ(qc::round<s32>(double(std::numeric_limits<s32>::min())), std::numeric_limits<s32>::min());
    testRound<double, s32>(std::numeric_limits<s32>::max() - 1);
    testRound<double, s32>(std::numeric_limits<s32>::min() + 1);

    testRound<double, s64>((s64(1) << 50) - 2);
    testRound<double, s64>(-((s64(1) << 50) - 2));
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
    testFloor<float, I>(0);
    testFloor<float, I>(1);
    testFloor<float, I>(-1);
    testFloor<float, I>(100);
    testFloor<float, I>(-100);
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
    testFloorT<float>();
    testFloorT<double>();

    ASSERT_EQ(qc::floor<s8>(float(std::numeric_limits<s8>::max())), std::numeric_limits<s8>::max());
    ASSERT_EQ(qc::floor<s8>(float(std::numeric_limits<s8>::min())), std::numeric_limits<s8>::min());
    testFloor<float, s8>(std::numeric_limits<s8>::max() - 1);
    testFloor<float, s8>(std::numeric_limits<s8>::min() + 1);

    ASSERT_EQ(qc::floor<s16>(float(std::numeric_limits<s16>::max())), std::numeric_limits<s16>::max());
    ASSERT_EQ(qc::floor<s16>(float(std::numeric_limits<s16>::min())), std::numeric_limits<s16>::min());
    testFloor<float, s16>(std::numeric_limits<s16>::max() - 1);
    testFloor<float, s16>(std::numeric_limits<s16>::min() + 1);

    ASSERT_EQ(qc::floor<s8>(double(std::numeric_limits<s8>::max())), std::numeric_limits<s8>::max());
    ASSERT_EQ(qc::floor<s8>(double(std::numeric_limits<s8>::min())), std::numeric_limits<s8>::min());
    testFloor<double, s8>(std::numeric_limits<s8>::max() - 1);
    testFloor<double, s8>(std::numeric_limits<s8>::min() + 1);

    ASSERT_EQ(qc::floor<s16>(double(std::numeric_limits<s16>::max())), std::numeric_limits<s16>::max());
    ASSERT_EQ(qc::floor<s16>(double(std::numeric_limits<s16>::min())), std::numeric_limits<s16>::min());
    testFloor<double, s16>(std::numeric_limits<s16>::max() - 1);
    testFloor<double, s16>(std::numeric_limits<s16>::min() + 1);

    ASSERT_EQ(qc::floor<s32>(double(std::numeric_limits<s32>::max())), std::numeric_limits<s32>::max());
    ASSERT_EQ(qc::floor<s32>(double(std::numeric_limits<s32>::min())), std::numeric_limits<s32>::min());
    testFloor<double, s32>(std::numeric_limits<s32>::max() - 1);
    testFloor<double, s32>(std::numeric_limits<s32>::min() + 1);

    testFloor<double, s64>(s64(1) << 49);
    testFloor<double, s64>(-(s64(1) << 49));
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
    testCeil<float, I>(0);
    testCeil<float, I>(1);
    testCeil<float, I>(-1);
    testCeil<float, I>(100);
    testCeil<float, I>(-100);
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
    testCeilT<float>();
    testCeilT<double>();

    ASSERT_EQ(qc::ceil<s8>(float(std::numeric_limits<s8>::max())), std::numeric_limits<s8>::max());
    ASSERT_EQ(qc::ceil<s8>(float(std::numeric_limits<s8>::min())), std::numeric_limits<s8>::min());
    testCeil<float, s8>(std::numeric_limits<s8>::max() - 1);
    testCeil<float, s8>(std::numeric_limits<s8>::min() + 1);

    ASSERT_EQ(qc::ceil<s16>(float(std::numeric_limits<s16>::max())), std::numeric_limits<s16>::max());
    ASSERT_EQ(qc::ceil<s16>(float(std::numeric_limits<s16>::min())), std::numeric_limits<s16>::min());
    testCeil<float, s16>(std::numeric_limits<s16>::max() - 1);
    testCeil<float, s16>(std::numeric_limits<s16>::min() + 1);

    ASSERT_EQ(qc::ceil<s8>(double(std::numeric_limits<s8>::max())), std::numeric_limits<s8>::max());
    ASSERT_EQ(qc::ceil<s8>(double(std::numeric_limits<s8>::min())), std::numeric_limits<s8>::min());
    testCeil<double, s8>(std::numeric_limits<s8>::max() - 1);
    testCeil<double, s8>(std::numeric_limits<s8>::min() + 1);

    ASSERT_EQ(qc::ceil<s16>(double(std::numeric_limits<s16>::max())), std::numeric_limits<s16>::max());
    ASSERT_EQ(qc::ceil<s16>(double(std::numeric_limits<s16>::min())), std::numeric_limits<s16>::min());
    testCeil<double, s16>(std::numeric_limits<s16>::max() - 1);
    testCeil<double, s16>(std::numeric_limits<s16>::min() + 1);

    ASSERT_EQ(qc::ceil<s32>(double(std::numeric_limits<s32>::max())), std::numeric_limits<s32>::max());
    ASSERT_EQ(qc::ceil<s32>(double(std::numeric_limits<s32>::min())), std::numeric_limits<s32>::min());
    testCeil<double, s32>(std::numeric_limits<s32>::max() - 1);
    testCeil<double, s32>(std::numeric_limits<s32>::min() + 1);

    testCeil<double, s64>(s64(1) << 49);
    testCeil<double, s64>(-(s64(1) << 49));
}
