#include <gtest/gtest.h>

#include <qc-core/core-ext.hpp>

using namespace qc::types;

#pragma warning(push)
#pragma warning(disable: 4101)
static void compileTyping()
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

    qc::stype<u8> stype_08_;
    qc::stype<u16> stype_16_;
    qc::stype<u32> stype_32_;
    qc::stype<u64> stype_64_;
    qc::utype<s8> utype_08_;
    qc::utype<s16> utype_16_;
    qc::utype<s32> utype_32_;
    qc::utype<s64> utype_64_;
    qc::ftype<u32> ftype_32_;
    qc::ftype<u64> ftype_64_;
}
#pragma warning(pop)

template <typename T1, typename T2>
static void compileFunctionsTT() {}

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
    T * vp{nullptr};

    qc::min(v, v);
    qc::min(vp, vp);
    qc::min(v, v, v);
    qc::min(v, v, v, v);
    qc::min(v, v, v, v, v);

    qc::max(v, v);
    qc::max(vp, vp);
    qc::max(v, v, v);
    qc::max(v, v, v, v);
    qc::max(v, v, v, v, v);

    qc::minify(v, v);
    qc::minify(vp, vp);
    qc::minify(v, v, v);
    qc::minify(v, v, v, v);
    qc::minify(v, v, v, v, v);

    qc::maxify(v, v);
    qc::maxify(vp, vp);
    qc::maxify(v, v, v);
    qc::maxify(v, v, v, v);
    qc::maxify(v, v, v, v, v);

    qc::minmax(v, v);
    qc::minmax(v, v, v);
    qc::minmax(v, v, v, v);
    qc::minmax(v, v, v, v, v);

    qc::median(v, v, v);

    qc::abs(v);

    qc::clamp(v, v, v);

    qc::isZero(v);
    qc::isZero(v, v);

    qc::areEqual(v, v);
    qc::areEqual(v, v, v);
    qc::areEqual(v, v, v, v);
    qc::areEqual(v, v, v, v, v);

    qc::sign(v);

    qc::round(v);

    qc::floor(v);

    qc::ceil(v);

    qc::mod(v, v);
    qc::mod_q(v, v);

    qc::sum(v, v, v, v, v);
    qc::product(v, v, v, v, v);
}

template <typename T>
static void compileFunctionsFT()
{
    T v{1.0};

    qc::areEqual_e(v, v);
    qc::areEqual_e(v, v, v);

    qc::pow(v, 1);
    qc::pow(v, 1u);

    qc::fract(v);
    qc::fract_i(v);

    qc::mix(v, v, v);

    qc::unmix(v, v, v);

    qc::average(v, v, v, v, v);

    qc::radians(v);

    qc::degrees(v);
}

template <typename T>
static void compileFunctionsIT()
{

}

template <typename T>
static void compileFunctionsUIT()
{
    T v{1u};

    qc::log2Floor(v);
}

static void compileFunctionsBT()
{
    bool v{true};

    qc::areEqual(v, v);
    qc::areEqual(v, v, v);
    qc::areEqual(v, v, v, v);
    qc::areEqual(v, v, v, v, v);
}

static void compileFunctions()
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

    compileFunctionsUIT<u8>();
    compileFunctionsUIT<u16>();
    compileFunctionsUIT<u32>();
    compileFunctionsUIT<u64>();

    compileFunctionsBT();
}

template <typename T1, typename T2>
static constexpr void compileFunctionsConstexprTT()
{
    //constexpr T1 v{1};

}

template <typename T>
static constexpr void compileFunctionsConstexprT()
{
    compileFunctionsConstexprTT<T, f32>();
    compileFunctionsConstexprTT<T, f64>();
    compileFunctionsConstexprTT<T, s8>();
    compileFunctionsConstexprTT<T, u8>();
    compileFunctionsConstexprTT<T, s16>();
    compileFunctionsConstexprTT<T, u16>();
    compileFunctionsConstexprTT<T, s32>();
    compileFunctionsConstexprTT<T, u32>();
    compileFunctionsConstexprTT<T, s64>();
    compileFunctionsConstexprTT<T, u64>();

    constexpr T v{1};
    constexpr T * vp{nullptr};

    qc::min(v, v);
    qc::min(vp, vp);
    qc::min(v, v, v);
    qc::min(v, v, v, v);
    qc::min(v, v, v, v, v);

    qc::max(v, v);
    qc::max(vp, vp);
    qc::max(v, v, v);
    qc::max(v, v, v, v);
    qc::max(v, v, v, v, v);

    //qc::minmax(v, v);
    //qc::minmax(v, v, v);
    //qc::minmax(v, v, v, v);
    //qc::minmax(v, v, v, v, v);

    //qc::median(v, v, v);

    //qc::clamp(v, v, v);

    //qc::abs(v);

    //qc::zero(v);
    //qc::zero(v, v);

    //qc::equal(v, v);
    //qc::equal(v, v, v
    //qc::equal(v, v, v, v);
    //qc::equal(v, v, v, v, v);

    //qc::sign(v);

    //qc::round(v);

    //qc::floor(v);

    //qc::ceil(v);

    //qc::mod(v, v);
    //qc::mod_q(v, v);

    qc::sum(v, v, v, v, v);
    qc::product(v, v, v, v, v);
}

template <typename T>
static constexpr void compileFunctionsConstexprFT()
{
    //constexpr T v{1.0};

    //qc::equal_e(v, v);
    //qc::equal_e(v, v, v);

    //qc::fract(v);
    //qc::fract_i(v);

    //qc::mix(v, v, v);

    //qc::average(v, v, v, v, v);

    //qc::radians(v);

    //qc::degrees(v);
}

template <typename T>
static constexpr void compileFunctionsConstexprIT()
{

}

template <typename T>
static constexpr void compileFunctionsConstexprUIT()
{
    constexpr T v{1};

    qc::log2Floor(v);
}

static constexpr void compileFunctionsConstexprBT()
{
    //constexpr bool v{true};

    //qc::equal(v, v);
    //qc::equal(v, v, v);
    //qc::equal(v, v, v, v);
    //qc::equal(v, v, v, v, v);
}

static constexpr bool compileFunctionsConstexpr()
{
    compileFunctionsConstexprT<f32>();
    compileFunctionsConstexprT<f64>();
    compileFunctionsConstexprT<s8>();
    compileFunctionsConstexprT<u8>();
    compileFunctionsConstexprT<s16>();
    compileFunctionsConstexprT<u16>();
    compileFunctionsConstexprT<s32>();
    compileFunctionsConstexprT<u32>();
    compileFunctionsConstexprT<s64>();
    compileFunctionsConstexprT<u64>();

    compileFunctionsConstexprFT<f32>();
    compileFunctionsConstexprFT<f64>();

    compileFunctionsConstexprIT<s8>();
    compileFunctionsConstexprIT<u8>();
    compileFunctionsConstexprIT<s16>();
    compileFunctionsConstexprIT<u16>();
    compileFunctionsConstexprIT<s32>();
    compileFunctionsConstexprIT<u32>();
    compileFunctionsConstexprIT<s64>();
    compileFunctionsConstexprIT<u64>();

    compileFunctionsConstexprUIT<u8>();
    compileFunctionsConstexprUIT<u16>();
    compileFunctionsConstexprUIT<u32>();
    compileFunctionsConstexprUIT<u64>();

    compileFunctionsConstexprBT();

    return true;
}

TEST(core, compilation)
{
    compileTyping();
    compileFunctions();
    static_assert(compileFunctionsConstexpr());
}

template <Integral T> static constexpr T halfVal{T(std::numeric_limits<T>::max() / 2 + T(1))};
template <Integral T> static constexpr T quarterVal{T(halfVal<T> / 2)};
template <Integral T> static constexpr T threeQuartersVal{T(halfVal<T> + quarterVal<T>)};

template <typename From, typename To>
void testTransnormFTFT()
{
    EXPECT_EQ(To(0.0), qc::transnorm<To>(From(0.0)));
    EXPECT_EQ(To(0.25), qc::transnorm<To>(From(0.25)));
    EXPECT_EQ(To(0.5), qc::transnorm<To>(From(0.5)));
    EXPECT_EQ(To(0.75), qc::transnorm<To>(From(0.75)));
    EXPECT_EQ(To(1.0), qc::transnorm<To>(From(1.0)));
}

template <typename From, typename To>
void testTransnormFTST()
{
    const double epsilon(1.0 / std::ldexp(1.0, std::numeric_limits<To>::digits));

    EXPECT_EQ(To(std::numeric_limits<To>::min()), qc::transnorm<To>(From(-1.0)));
    EXPECT_NEAR(0.75, double(qc::transnorm<To>(From(-0.75))) / double(std::numeric_limits<To>::min()), epsilon);
    EXPECT_NEAR(0.5, double(qc::transnorm<To>(From(-0.5))) / double(std::numeric_limits<To>::min()), epsilon);
    EXPECT_NEAR(0.25, double(qc::transnorm<To>(From(-0.25))) / double(std::numeric_limits<To>::min()), epsilon);
    EXPECT_EQ(To(0u), qc::transnorm<To>(From(0.0)));
    EXPECT_NEAR(0.25, double(qc::transnorm<To>(From(0.25))) / double(std::numeric_limits<To>::max()), epsilon);
    EXPECT_NEAR(0.5, double(qc::transnorm<To>(From(0.5))) / double(std::numeric_limits<To>::max()), epsilon);
    EXPECT_NEAR(0.75, double(qc::transnorm<To>(From(0.75))) / double(std::numeric_limits<To>::max()), epsilon);
    EXPECT_EQ(std::numeric_limits<To>::max(), qc::transnorm<To>(From(1.0)));
}

template <typename From, typename To>
void testTransnormFTUT()
{
    const double epsilon(1.0 / std::ldexp(1.0, std::numeric_limits<To>::digits));

    EXPECT_EQ(To(0u), qc::transnorm<To>(From(0.0)));
    EXPECT_NEAR(0.25, double(qc::transnorm<To>(From(0.25))) / double(std::numeric_limits<To>::max()), epsilon);
    EXPECT_NEAR(0.5, double(qc::transnorm<To>(From(0.5))) / double(std::numeric_limits<To>::max()), epsilon);
    EXPECT_NEAR(0.75, double(qc::transnorm<To>(From(0.75))) / double(std::numeric_limits<To>::max()), epsilon);
    EXPECT_EQ(std::numeric_limits<To>::max(), qc::transnorm<To>(From(1.0)));
}

template <typename From, typename To>
void testTransnormSTFT()
{
    const To epsilon{To(1.0 / std::ldexp(1.0, std::numeric_limits<From>::digits))};

    EXPECT_EQ(To(-1.0), qc::transnorm<To>(std::numeric_limits<From>::min()));
    EXPECT_NEAR(To(-0.75), qc::transnorm<To>(From(-threeQuartersVal<From>)), epsilon);
    EXPECT_NEAR(To(-0.5), qc::transnorm<To>(From(-halfVal<From>)), epsilon);
    EXPECT_NEAR(To(-0.25), qc::transnorm<To>(From(-quarterVal<From>)), epsilon);
    EXPECT_EQ(To(0.0), qc::transnorm<To>(From(0)));
    EXPECT_NEAR(To(0.25), qc::transnorm<To>(quarterVal<From>), epsilon);
    EXPECT_NEAR(To(0.5), qc::transnorm<To>(halfVal<From>), epsilon);
    EXPECT_NEAR(To(0.75), qc::transnorm<To>(threeQuartersVal<From>), epsilon);
    EXPECT_EQ(To(1.0), qc::transnorm<To>(std::numeric_limits<From>::max()));
}

template <typename From, typename To>
void testTransnormUTFT()
{
    const To epsilon{To(1.0 / std::ldexp(1.0, std::numeric_limits<From>::digits))};

    EXPECT_EQ(To(0.0), qc::transnorm<To>(From(0u)));
    EXPECT_NEAR(To(0.25), qc::transnorm<To>(quarterVal<From>), epsilon);
    EXPECT_NEAR(To(0.5), qc::transnorm<To>(halfVal<From>), epsilon);
    EXPECT_NEAR(To(0.75), qc::transnorm<To>(threeQuartersVal<From>), epsilon);
    EXPECT_EQ(To(1.0), qc::transnorm<To>(std::numeric_limits<From>::max()));
}

template <typename From, typename To>
void testTransnormUTUT()
{
    const double epsilon(1.0 / std::ldexp(1.0, qc::min(std::numeric_limits<To>::digits, std::numeric_limits<From>::digits)));

    EXPECT_EQ(To(0u), qc::transnorm<To>(From(0u)));
    EXPECT_NEAR(0.25, double(qc::transnorm<To>(From(quarterVal<From>))) / double(std::numeric_limits<To>::max()), epsilon);
    EXPECT_NEAR(0.5, double(qc::transnorm<To>(From(halfVal<From>))) / double(std::numeric_limits<To>::max()), epsilon);
    EXPECT_NEAR(0.75, double(qc::transnorm<To>(From(threeQuartersVal<From>))) / double(std::numeric_limits<To>::max()), epsilon);
    EXPECT_EQ( To(std::numeric_limits<To>::max()), qc::transnorm<To>(std::numeric_limits<From>::max()));
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

TEST(core, transnorm)
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

TEST(core, concepts)
{
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

    static_assert(SignedNumeric<s8>);
    static_assert(SignedNumeric<s16>);
    static_assert(SignedNumeric<s32>);
    static_assert(SignedNumeric<s64>);
    static_assert(!SignedNumeric<u8>);
    static_assert(!SignedNumeric<u16>);
    static_assert(!SignedNumeric<u32>);
    static_assert(!SignedNumeric<u64>);
    static_assert(SignedNumeric<f32>);
    static_assert(SignedNumeric<f64>);
    static_assert(!SignedNumeric<bool>);
    static_assert(!SignedNumeric<char>);
    static_assert(!SignedNumeric<void *>);
}
