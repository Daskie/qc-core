#include <CppUnitTest.h>

#include <qc-core/core-ext.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace qc::core::types;

namespace Microsoft::VisualStudio::CppUnitTestFramework {
    template <>
    static std::wstring ToString<uint16_t>(const uint16_t & v) {
        return std::to_wstring(v);
    }
}

static void compileTyping() {
    s8 s08_; s08_;
    u8 u08_; u08_;
    s16 s16_; s16_;
    u16 u16_; u16_;
    s32 s32_; s32_;
    u32 u32_; u32_;
    f32 f32_; f32_;
    s64 s64_; s64_;
    u64 u64_; u64_;
    f64 f64_; f64_;

    qc::core::array_t<int> a0{1, 2, 3}; a0;
    qc::core::array_t<int, 1> a1; a1;

    qc::core::stype<1> stype_08_; stype_08_;
    qc::core::stype<2> stype_16_; stype_16_;
    qc::core::stype<4> stype_32_; stype_32_;
    qc::core::stype<8> stype_64_; stype_64_;
    qc::core::utype<1> utype_08_; utype_08_;
    qc::core::utype<2> utype_16_; utype_16_;
    qc::core::utype<4> utype_32_; utype_32_;
    qc::core::utype<8> utype_64_; utype_64_;
    qc::core::ftype<4> ftype_32_; ftype_32_;
    qc::core::ftype<8> ftype_64_; ftype_64_;
}

template <typename T>
static void compileConstantsFT() {
    qc::core::pi<T>;
    qc::core::e<T>;
    qc::core::phi<T>;
    qc::core::sqrt2<T>;
    qc::core::sqrt3<T>;
    qc::core::sqrt5<T>;
    qc::core::infinity<T>;
}

static void compileConstants() {
    compileConstantsFT<float>();
    compileConstantsFT<double>();
}

template <typename T1, typename T2>
static void compileFunctionsTT() {}

template <typename T>
static void compileFunctionsT() {
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

    qc::core::min(v, v);
    qc::core::min(vp, vp);
    qc::core::min(v, v, v);
    qc::core::min(v, v, v, v);
    qc::core::min(v, v, v, v, v);

    qc::core::max(v, v);
    qc::core::max(vp, vp);
    qc::core::max(v, v, v);
    qc::core::max(v, v, v, v);
    qc::core::max(v, v, v, v, v);

    qc::core::minify(v, v);
    qc::core::minify(vp, vp);
    qc::core::minify(v, v, v);
    qc::core::minify(v, v, v, v);
    qc::core::minify(v, v, v, v, v);

    qc::core::maxify(v, v);
    qc::core::maxify(vp, vp);
    qc::core::maxify(v, v, v);
    qc::core::maxify(v, v, v, v);
    qc::core::maxify(v, v, v, v, v);

    qc::core::minmax(v);
    qc::core::minmax(v, v);
    qc::core::minmax(v, v, v);
    qc::core::minmax(v, v, v, v);
    qc::core::minmax(v, v, v, v, v);

    qc::core::median(v, v, v);

    qc::core::abs(v);

    qc::core::clamp(v, v, v);

    qc::core::zero(v);
    qc::core::zero(v, v);

    qc::core::equal(v, v);
    qc::core::equal(v, v, v);
    qc::core::equal(v, v, v, v);
    qc::core::equal(v, v, v, v, v);

    qc::core::sign(v);

    qc::core::round(v);

    qc::core::floor(v);

    qc::core::ceil(v);

    qc::core::mod(v, v);
    qc::core::mod_q(v, v);

    qc::core::sum(v, v, v, v, v);
    qc::core::product(v, v, v, v, v);
}

template <typename T>
static void compileFunctionsFT() {
    T v{1.0};

    qc::core::equal_e(v, v);
    qc::core::equal_e(v, v, v);

    qc::core::pow(v, 1);
    qc::core::pow(v, 1u);

    qc::core::fract(v);
    qc::core::fract_i(v);

    qc::core::mix(v, v, v);

    qc::core::unmix(v, v, v);

    qc::core::average(v, v, v, v, v);

    qc::core::radians(v);

    qc::core::degrees(v);
}

template <typename T>
static void compileFunctionsIT() {

}

template <typename T>
static void compileFunctionsUIT() {
    T v{1u};

    qc::core::log2Floor(v);

    qc::core::log2Ceil(v);

    qc::core::mipmaps(v);
}

static void compileFunctionsBT() {
    bool v{true};

    qc::core::equal(v, v);
    qc::core::equal(v, v, v);
    qc::core::equal(v, v, v, v);
    qc::core::equal(v, v, v, v, v);
}

static void compileFunctions() {
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
static constexpr void compileFunctionsConstexprTT() {
    constexpr T1 v{1};

}

template <typename T>
static constexpr void compileFunctionsConstexprT() {
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

    qc::core::min(v, v);
    qc::core::min(vp, vp);
    qc::core::min(v, v, v);
    qc::core::min(v, v, v, v);
    qc::core::min(v, v, v, v, v);

    qc::core::max(v, v);
    qc::core::max(vp, vp);
    qc::core::max(v, v, v);
    qc::core::max(v, v, v, v);
    qc::core::max(v, v, v, v, v);

    //qc::core::minmax(v, v);
    //qc::core::minmax(v, v, v);
    //qc::core::minmax(v, v, v, v);
    //qc::core::minmax(v, v, v, v, v);

    //qc::core::median(v, v, v);

    //qc::core::clamp(v, v, v);

    //qc::core::abs(v);

    //qc::core::zero(v);
    //qc::core::zero(v, v);

    //qc::core::equal(v, v);
    //qc::core::equal(v, v, v
    //qc::core::equal(v, v, v, v);
    //qc::core::equal(v, v, v, v, v);

    //qc::core::sign(v);

    //qc::core::round(v);

    //qc::core::floor(v);

    //qc::core::ceil(v);

    //qc::core::mod(v, v);
    //qc::core::mod_q(v, v);

    qc::core::sum(v, v, v, v, v);
    qc::core::product(v, v, v, v, v);
}

template <typename T>
static constexpr void compileFunctionsConstexprFT() {
    constexpr T v{1.0};

    //qc::core::equal_e(v, v);
    //qc::core::equal_e(v, v, v);

    //qc::core::fract(v);
    //qc::core::fract_i(v);

    //qc::core::mix(v, v, v);

    //qc::core::average(v, v, v, v, v);

    //qc::core::radians(v);

    //qc::core::degrees(v);
}

template <typename T>
static constexpr void compileFunctionsConstexprIT() {

}

template <typename T>
static constexpr void compileFunctionsConstexprUIT() {
    constexpr T v{1};

    qc::core::log2Floor(v);

    qc::core::log2Ceil(v);

    //qc::core::mipmaps(v);
}

static constexpr void compileFunctionsConstexprBT() {
    constexpr bool v{true};

    //qc::core::equal(v, v);
    //qc::core::equal(v, v, v);
    //qc::core::equal(v, v, v, v);
    //qc::core::equal(v, v, v, v, v);
}

static constexpr bool compileFunctionsConstexpr() {
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

TEST_CLASS(TestCore) {

    public:

    TEST_METHOD(testCompilation) {
        compileTyping();
        compileConstants();
        compileFunctions();
        static_assert(compileFunctionsConstexpr());
    }

    template <Integral T> static constexpr T halfVal{T(std::numeric_limits<T>::max() / 2 + T(1))};
    template <Integral T> static constexpr T quarterVal{T(halfVal<T> / 2)};
    template <Integral T> static constexpr T threeQuartersVal{T(halfVal<T> + quarterVal<T>)};

    template <typename From, typename To>
    void testTransnormFTFT() {
        Assert::AreEqual(To(0.0), qc::core::transnorm<To>(From(0.0)));
        Assert::AreEqual(To(0.25), qc::core::transnorm<To>(From(0.25)));
        Assert::AreEqual(To(0.5), qc::core::transnorm<To>(From(0.5)));
        Assert::AreEqual(To(0.75), qc::core::transnorm<To>(From(0.75)));
        Assert::AreEqual(To(1.0), qc::core::transnorm<To>(From(1.0)));
    }

    template <typename From, typename To>
    void testTransnormFTST() {
        const double epsilon(1.0 / std::ldexp(1.0, std::numeric_limits<To>::digits));

        Assert::AreEqual(To(std::numeric_limits<To>::min()), qc::core::transnorm<To>(From(-1.0)));
        Assert::AreEqual(0.75, double(qc::core::transnorm<To>(From(-0.75))) / double(std::numeric_limits<To>::min()), epsilon);
        Assert::AreEqual(0.5, double(qc::core::transnorm<To>(From(-0.5))) / double(std::numeric_limits<To>::min()), epsilon);
        Assert::AreEqual(0.25, double(qc::core::transnorm<To>(From(-0.25))) / double(std::numeric_limits<To>::min()), epsilon);
        Assert::AreEqual(To(0u), qc::core::transnorm<To>(From(0.0)));
        Assert::AreEqual(0.25, double(qc::core::transnorm<To>(From(0.25))) / double(std::numeric_limits<To>::max()), epsilon);
        Assert::AreEqual(0.5, double(qc::core::transnorm<To>(From(0.5))) / double(std::numeric_limits<To>::max()), epsilon);
        Assert::AreEqual(0.75, double(qc::core::transnorm<To>(From(0.75))) / double(std::numeric_limits<To>::max()), epsilon);
        Assert::AreEqual(std::numeric_limits<To>::max(), qc::core::transnorm<To>(From(1.0)));
    }

    template <typename From, typename To>
    void testTransnormFTUT() {
        const double epsilon(1.0 / std::ldexp(1.0, std::numeric_limits<To>::digits));

        Assert::AreEqual(To(0u), qc::core::transnorm<To>(From(0.0)));
        Assert::AreEqual(0.25, double(qc::core::transnorm<To>(From(0.25))) / double(std::numeric_limits<To>::max()), epsilon);
        Assert::AreEqual(0.5, double(qc::core::transnorm<To>(From(0.5))) / double(std::numeric_limits<To>::max()), epsilon);
        Assert::AreEqual(0.75, double(qc::core::transnorm<To>(From(0.75))) / double(std::numeric_limits<To>::max()), epsilon);
        Assert::AreEqual(std::numeric_limits<To>::max(), qc::core::transnorm<To>(From(1.0)));
    }

    template <typename From, typename To>
    void testTransnormSTFT() {
        const To epsilon{To(1.0 / std::ldexp(1.0, std::numeric_limits<From>::digits))};

        Assert::AreEqual(To(-1.0), qc::core::transnorm<To>(std::numeric_limits<From>::min()));
        Assert::AreEqual(To(-0.75), qc::core::transnorm<To>(From(-threeQuartersVal<From>)), epsilon);
        Assert::AreEqual(To(-0.5), qc::core::transnorm<To>(From(-halfVal<From>)), epsilon);
        Assert::AreEqual(To(-0.25), qc::core::transnorm<To>(From(-quarterVal<From>)), epsilon);
        Assert::AreEqual(To(0.0), qc::core::transnorm<To>(From(0)));
        Assert::AreEqual(To(0.25), qc::core::transnorm<To>(quarterVal<From>), epsilon);
        Assert::AreEqual(To(0.5), qc::core::transnorm<To>(halfVal<From>), epsilon);
        Assert::AreEqual(To(0.75), qc::core::transnorm<To>(threeQuartersVal<From>), epsilon);
        Assert::AreEqual(To(1.0), qc::core::transnorm<To>(std::numeric_limits<From>::max()));
    }

    template <typename From, typename To>
    void testTransnormUTFT() {
        const To epsilon{To(1.0 / std::ldexp(1.0, std::numeric_limits<From>::digits))};

        Assert::AreEqual(To(0.0), qc::core::transnorm<To>(From(0u)));
        Assert::AreEqual(To(0.25), qc::core::transnorm<To>(quarterVal<From>), epsilon);
        Assert::AreEqual(To(0.5), qc::core::transnorm<To>(halfVal<From>), epsilon);
        Assert::AreEqual(To(0.75), qc::core::transnorm<To>(threeQuartersVal<From>), epsilon);
        Assert::AreEqual(To(1.0), qc::core::transnorm<To>(std::numeric_limits<From>::max()));
    }

    template <typename From, typename To>
    void testTransnormUTUT() {
        const double epsilon(1.0 / std::ldexp(1.0, qc::core::min(std::numeric_limits<To>::digits, std::numeric_limits<From>::digits)));

        Assert::AreEqual(To(0u), qc::core::transnorm<To>(From(0u)));
        Assert::AreEqual(0.25, double(qc::core::transnorm<To>(From(quarterVal<From>))) / double(std::numeric_limits<To>::max()), epsilon);
        Assert::AreEqual(0.5, double(qc::core::transnorm<To>(From(halfVal<From>))) / double(std::numeric_limits<To>::max()), epsilon);
        Assert::AreEqual(0.75, double(qc::core::transnorm<To>(From(threeQuartersVal<From>))) / double(std::numeric_limits<To>::max()), epsilon);
        Assert::AreEqual( To(std::numeric_limits<To>::max()), qc::core::transnorm<To>(std::numeric_limits<From>::max()));
    }

    template <typename From>
    void testTransnormST() {
        testTransnormSTFT<From, f32>();
        testTransnormSTFT<From, f64>();
    }

    template <typename From>
    void testTransnormUT() {
        testTransnormUTUT<From, u8>();
        testTransnormUTUT<From, u16>();
        testTransnormUTUT<From, u32>();
        testTransnormUTUT<From, u64>();

        testTransnormUTFT<From, f32>();
        testTransnormUTFT<From, f64>();
    }

    template <typename From>
    void testTransnormFT() {
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

    TEST_METHOD(testTransnorm) {
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

};
