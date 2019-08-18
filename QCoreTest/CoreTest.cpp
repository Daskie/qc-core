#include "QCoreTest.hpp"

#include "QCore/CoreFunc.hpp"

namespace {

void compileTyping() {
    qc::nat nat_;   nat_;
    qc::unat unat_; unat_;

    qc::operator""_n(0);
    qc::operator""_un(0);

    qc::s08 s08_; s08_;
    qc::u08 u08_; u08_;
    qc::s16 s16_; s16_;
    qc::u16 u16_; u16_;
    qc::s32 s32_; s32_;
    qc::u32 u32_; u32_;
    qc::f32 f32_; f32_;
    qc::s64 s64_; s64_;
    qc::u64 u64_; u64_;
    qc::f64 f64_; f64_;

    qc::s08_fast s08_fast_; s08_fast_;
    qc::u08_fast u08_fast_; u08_fast_;
    qc::s16_fast s16_fast_; s16_fast_;
    qc::u16_fast u16_fast_; u16_fast_;
    qc::s32_fast s32_fast_; s32_fast_;
    qc::u32_fast u32_fast_; u32_fast_;
    qc::s64_fast s64_fast_; s64_fast_;
    qc::u64_fast u64_fast_; u64_fast_;

    qc::array_t<int> a0{ 1, 2, 3 }; a0;
    qc::array_t<int, 1> a1; a1;

    qc::stype<1> stype_08_; stype_08_;
    qc::stype<2> stype_16_; stype_16_;
    qc::stype<4> stype_32_; stype_32_;
    qc::stype<8> stype_64_; stype_64_;
    qc::utype<1> utype_08_; utype_08_;
    qc::utype<2> utype_16_; utype_16_;
    qc::utype<4> utype_32_; utype_32_;
    qc::utype<8> utype_64_; utype_64_;
    qc::ftype<4> ftype_32_; ftype_32_;
    qc::ftype<8> ftype_64_; ftype_64_;

    qc::stype_fast<1> stype_fast_08_; stype_fast_08_;
    qc::stype_fast<2> stype_fast_16_; stype_fast_16_;
    qc::stype_fast<4> stype_fast_32_; stype_fast_32_;
    qc::stype_fast<8> stype_fast_64_; stype_fast_64_;
    qc::utype_fast<1> utype_fast_08_; utype_fast_08_;
    qc::utype_fast<2> utype_fast_16_; utype_fast_16_;
    qc::utype_fast<4> utype_fast_32_; utype_fast_32_;
    qc::utype_fast<8> utype_fast_64_; utype_fast_64_;
}

template <typename T>
void compileConstantsT() {
    qc::infinity<T>;
}

template <typename T>
void compileConstantsFT() {
    qc::pi<T>;
    qc::e<T>;
    qc::phi<T>;
    qc::sqrt2<T>;
    qc::sqrt3<T>;
    qc::sqrt5<T>;
}

void compileConstants() {
    compileConstantsT<float>();
    compileConstantsT<double>();
    compileConstantsT<qc::s08>();
    compileConstantsT<qc::u08>();
    compileConstantsT<qc::s16>();
    compileConstantsT<qc::u16>();
    compileConstantsT<qc::s32>();
    compileConstantsT<qc::u32>();
    compileConstantsT<qc::s64>();
    compileConstantsT<qc::u64>();

    compileConstantsFT<float>();
    compileConstantsFT<double>();
}

template <typename T1, typename T2>
void compileFunctionsTT() {
    T1 v(1);

    qc::transnorm<T2>(v);
}

template <typename T>
void compileFunctionsT() {
    compileFunctionsTT<T, qc::f32>();
    compileFunctionsTT<T, qc::f64>();
    compileFunctionsTT<T, qc::s08>();
    compileFunctionsTT<T, qc::u08>();
    compileFunctionsTT<T, qc::s16>();
    compileFunctionsTT<T, qc::u16>();
    compileFunctionsTT<T, qc::s32>();
    compileFunctionsTT<T, qc::u32>();
    compileFunctionsTT<T, qc::s64>();
    compileFunctionsTT<T, qc::u64>();

    T v(1);
    T * vp(nullptr);

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

    qc::minmax(v);
    qc::minmax(v, v);
    qc::minmax(v, v, v);
    qc::minmax(v, v, v, v);
    qc::minmax(v, v, v, v, v);

    qc::median(v, v, v);

    qc::abs(v);

    qc::clamp(v, v, v);

    qc::zero(v);
    qc::zero(v, v);

    qc::equal(v, v);
    qc::equal(v, v, v);
    qc::equal(v, v, v, v);
    qc::equal(v, v, v, v, v);

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
void compileFunctionsFT() {
    T v(1.0);

    qc::equal_e(v, v);
    qc::equal_e(v, v, v);

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
void compileFunctionsIT() {
    T v(1);

    qc::pow2<T>(int(v));

    qc::isPow2(v);

    qc::log2Floor(v);

    qc::log2Ceil(v);

    qc::floor2(v);

    qc::ceil2(v);

    qc::mipmaps(v);

    qc::highBit(v);

    qc::lowBit(v);
}

void compileFunctionsBT() {
    bool v(true);

    qc::equal(v, v);
    qc::equal(v, v, v);
    qc::equal(v, v, v, v);
    qc::equal(v, v, v, v, v);
}

void compileFunctions() {
    compileFunctionsT<qc::f32>();
    compileFunctionsT<qc::f64>();
    compileFunctionsT<qc::s08>();
    compileFunctionsT<qc::u08>();
    compileFunctionsT<qc::s16>();
    compileFunctionsT<qc::u16>();
    compileFunctionsT<qc::s32>();
    compileFunctionsT<qc::u32>();
    compileFunctionsT<qc::s64>();
    compileFunctionsT<qc::u64>();

    compileFunctionsFT<qc::f32>();
    compileFunctionsFT<qc::f64>();

    compileFunctionsIT<qc::s08>();
    compileFunctionsIT<qc::u08>();
    compileFunctionsIT<qc::s16>();
    compileFunctionsIT<qc::u16>();
    compileFunctionsIT<qc::s32>();
    compileFunctionsIT<qc::u32>();
    compileFunctionsIT<qc::s64>();
    compileFunctionsIT<qc::u64>();

    compileFunctionsBT();
}

template <typename T1, typename T2>
constexpr void compileFunctionsConstexprTT() {
    constexpr T1 v(1);

}

template <typename T>
constexpr void compileFunctionsConstexprT() {
    compileFunctionsConstexprTT<T, qc::f32>();
    compileFunctionsConstexprTT<T, qc::f64>();
    compileFunctionsConstexprTT<T, qc::s08>();
    compileFunctionsConstexprTT<T, qc::u08>();
    compileFunctionsConstexprTT<T, qc::s16>();
    compileFunctionsConstexprTT<T, qc::u16>();
    compileFunctionsConstexprTT<T, qc::s32>();
    compileFunctionsConstexprTT<T, qc::u32>();
    compileFunctionsConstexprTT<T, qc::s64>();
    compileFunctionsConstexprTT<T, qc::u64>();

    constexpr T v(1);
    constexpr T * vp(nullptr);

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
constexpr void compileFunctionsConstexprFT() {
    constexpr T v(1.0);

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
constexpr void compileFunctionsConstexprIT() {
    constexpr T v(1);

    qc::pow2<T>(v);

    qc::isPow2(v);

    //qc::log2Floor(v);

    //qc::log2Ceil(v);

    //qc::floor2(v);

    //qc::ceil2(v);

    //qc::mipmaps(v);

    //qc::highBit(v);

    //qc::lowBit(v);
}

constexpr void compileFunctionsConstexprBT() {
    constexpr bool v(true);

    //qc::equal(v, v);
    //qc::equal(v, v, v);
    //qc::equal(v, v, v, v);
    //qc::equal(v, v, v, v, v);
}

constexpr bool compileFunctionsConstexpr() {
    compileFunctionsConstexprT<qc::f32>();
    compileFunctionsConstexprT<qc::f64>();
    compileFunctionsConstexprT<qc::s08>();
    compileFunctionsConstexprT<qc::u08>();
    compileFunctionsConstexprT<qc::s16>();
    compileFunctionsConstexprT<qc::u16>();
    compileFunctionsConstexprT<qc::s32>();
    compileFunctionsConstexprT<qc::u32>();
    compileFunctionsConstexprT<qc::s64>();
    compileFunctionsConstexprT<qc::u64>();

    compileFunctionsConstexprFT<qc::f32>();
    compileFunctionsConstexprFT<qc::f64>();

    compileFunctionsConstexprIT<qc::s08>();
    compileFunctionsConstexprIT<qc::u08>();
    compileFunctionsConstexprIT<qc::s16>();
    compileFunctionsConstexprIT<qc::u16>();
    compileFunctionsConstexprIT<qc::s32>();
    compileFunctionsConstexprIT<qc::u32>();
    compileFunctionsConstexprIT<qc::s64>();
    compileFunctionsConstexprIT<qc::u64>();
    
    compileFunctionsConstexprBT();

    return true;
}

}

void testCore() {
    compileTyping();
    compileConstants();
    compileFunctions();
    static_assert(compileFunctionsConstexpr());
}
