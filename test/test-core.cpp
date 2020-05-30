#include <qc-core/core-ext.hpp>

static void compileTyping() {
    using namespace qc::core::types;

    s08 s08_; s08_;
    u08 u08_; u08_;
    s16 s16_; s16_;
    u16 u16_; u16_;
    s32 s32_; s32_;
    u32 u32_; u32_;
    f32 f32_; f32_;
    s64 s64_; s64_;
    u64 u64_; u64_;
    f64 f64_; f64_;

    qc::core::array_t<int> a0{ 1, 2, 3 }; a0;
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

    pair<int, int> p;

    duo<int> d;
}

template <typename T>
static void compileConstantsT() {
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
    compileConstantsT<float>();
    compileConstantsT<double>();
    compileConstantsT<qc::core::s08>();
    compileConstantsT<qc::core::u08>();
    compileConstantsT<qc::core::s16>();
    compileConstantsT<qc::core::u16>();
    compileConstantsT<qc::core::s32>();
    compileConstantsT<qc::core::u32>();
    compileConstantsT<qc::core::s64>();
    compileConstantsT<qc::core::u64>();

    compileConstantsFT<float>();
    compileConstantsFT<double>();
}

template <typename T1, typename T2>
static void compileFunctionsTT() {
    T1 v(1);

    qc::core::transnorm<T2>(v);
}

template <typename T>
static void compileFunctionsT() {
    compileFunctionsTT<T, qc::core::f32>();
    compileFunctionsTT<T, qc::core::f64>();
    compileFunctionsTT<T, qc::core::s08>();
    compileFunctionsTT<T, qc::core::u08>();
    compileFunctionsTT<T, qc::core::s16>();
    compileFunctionsTT<T, qc::core::u16>();
    compileFunctionsTT<T, qc::core::s32>();
    compileFunctionsTT<T, qc::core::u32>();
    compileFunctionsTT<T, qc::core::s64>();
    compileFunctionsTT<T, qc::core::u64>();

    T v(1);
    T * vp(nullptr);

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
    T v(1.0);

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
    T v(1);

    qc::core::log2Floor(v);

    qc::core::log2Ceil(v);

    qc::core::mipmaps(v);
}

static void compileFunctionsBT() {
    bool v(true);

    qc::core::equal(v, v);
    qc::core::equal(v, v, v);
    qc::core::equal(v, v, v, v);
    qc::core::equal(v, v, v, v, v);
}

static void compileFunctions() {
    compileFunctionsT<qc::core::f32>();
    compileFunctionsT<qc::core::f64>();
    compileFunctionsT<qc::core::s08>();
    compileFunctionsT<qc::core::u08>();
    compileFunctionsT<qc::core::s16>();
    compileFunctionsT<qc::core::u16>();
    compileFunctionsT<qc::core::s32>();
    compileFunctionsT<qc::core::u32>();
    compileFunctionsT<qc::core::s64>();
    compileFunctionsT<qc::core::u64>();

    compileFunctionsFT<qc::core::f32>();
    compileFunctionsFT<qc::core::f64>();

    compileFunctionsIT<qc::core::s08>();
    compileFunctionsIT<qc::core::u08>();
    compileFunctionsIT<qc::core::s16>();
    compileFunctionsIT<qc::core::u16>();
    compileFunctionsIT<qc::core::s32>();
    compileFunctionsIT<qc::core::u32>();
    compileFunctionsIT<qc::core::s64>();
    compileFunctionsIT<qc::core::u64>();

    compileFunctionsUIT<qc::core::u08>();
    compileFunctionsUIT<qc::core::u16>();
    compileFunctionsUIT<qc::core::u32>();
    compileFunctionsUIT<qc::core::u64>();

    compileFunctionsBT();
}

template <typename T1, typename T2>
static constexpr void compileFunctionsConstexprTT() {
    constexpr T1 v(1);

}

template <typename T>
static constexpr void compileFunctionsConstexprT() {
    compileFunctionsConstexprTT<T, qc::core::f32>();
    compileFunctionsConstexprTT<T, qc::core::f64>();
    compileFunctionsConstexprTT<T, qc::core::s08>();
    compileFunctionsConstexprTT<T, qc::core::u08>();
    compileFunctionsConstexprTT<T, qc::core::s16>();
    compileFunctionsConstexprTT<T, qc::core::u16>();
    compileFunctionsConstexprTT<T, qc::core::s32>();
    compileFunctionsConstexprTT<T, qc::core::u32>();
    compileFunctionsConstexprTT<T, qc::core::s64>();
    compileFunctionsConstexprTT<T, qc::core::u64>();

    constexpr T v(1);
    constexpr T * vp(nullptr);

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
    constexpr T v(1.0);

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
    constexpr T v(1);

    qc::core::log2Floor(v);

    qc::core::log2Ceil(v);

    //qc::core::mipmaps(v);
}

static constexpr void compileFunctionsConstexprBT() {
    constexpr bool v(true);

    //qc::core::equal(v, v);
    //qc::core::equal(v, v, v);
    //qc::core::equal(v, v, v, v);
    //qc::core::equal(v, v, v, v, v);
}

static constexpr bool compileFunctionsConstexpr() {
    compileFunctionsConstexprT<qc::core::f32>();
    compileFunctionsConstexprT<qc::core::f64>();
    compileFunctionsConstexprT<qc::core::s08>();
    compileFunctionsConstexprT<qc::core::u08>();
    compileFunctionsConstexprT<qc::core::s16>();
    compileFunctionsConstexprT<qc::core::u16>();
    compileFunctionsConstexprT<qc::core::s32>();
    compileFunctionsConstexprT<qc::core::u32>();
    compileFunctionsConstexprT<qc::core::s64>();
    compileFunctionsConstexprT<qc::core::u64>();

    compileFunctionsConstexprFT<qc::core::f32>();
    compileFunctionsConstexprFT<qc::core::f64>();

    compileFunctionsConstexprIT<qc::core::s08>();
    compileFunctionsConstexprIT<qc::core::u08>();
    compileFunctionsConstexprIT<qc::core::s16>();
    compileFunctionsConstexprIT<qc::core::u16>();
    compileFunctionsConstexprIT<qc::core::s32>();
    compileFunctionsConstexprIT<qc::core::u32>();
    compileFunctionsConstexprIT<qc::core::s64>();
    compileFunctionsConstexprIT<qc::core::u64>();

    compileFunctionsConstexprUIT<qc::core::u08>();
    compileFunctionsConstexprUIT<qc::core::u16>();
    compileFunctionsConstexprUIT<qc::core::u32>();
    compileFunctionsConstexprUIT<qc::core::u64>();

    compileFunctionsConstexprBT();

    return true;
}

void testCore() {
    compileTyping();
    compileConstants();
    compileFunctions();
    static_assert(compileFunctionsConstexpr());
}
