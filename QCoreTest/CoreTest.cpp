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

    qc::array_t<int> a0{ 1, 2, 3 }; a0;
    qc::array_t<int, 1> a1; a1;

    qc::precision<1>::stype p08s_; p08s_;
    qc::precision<2>::stype p16s_; p16s_;
    qc::precision<4>::stype p32s_; p32s_;
    qc::precision<8>::stype p64s_; p64s_;
    qc::precision<1>::utype p08u_; p08u_;
    qc::precision<2>::utype p16u_; p16u_;
    qc::precision<4>::utype p32u_; p32u_;
    qc::precision<8>::utype p64u_; p64u_;
    qc::precision<4>::ftype p32f_; p32f_;
    qc::precision<8>::ftype p64f_; p64f_;
}

template <typename T>
void compileConstantsT() {
    qc::pi<T>;
    qc::e<T>;
    qc::phi<T>;
    qc::infinity<T>;
    qc::sqrt<2, T>;
    qc::sqrt<1000, T>;
}

void compileConstants() {
    compileConstantsT<float>();
    compileConstantsT<double>();
    compileConstantsT<long double>();
}

template <typename T1, typename T2>
void compileFunctionsTT() {
    T1 v(1);

    qc::transnorm<T2>(v);
}

template <typename T>
void compileFunctionsT() {
    compileFunctionsTT<T, float>();
    compileFunctionsTT<T, double>();
    compileFunctionsTT<T, long double>();
    compileFunctionsTT<T, signed char>();
    compileFunctionsTT<T, unsigned char>();
    compileFunctionsTT<T, signed short>();
    compileFunctionsTT<T, unsigned short>();
    compileFunctionsTT<T, signed int>();
    compileFunctionsTT<T, unsigned short>();
    compileFunctionsTT<T, signed long>();
    compileFunctionsTT<T, unsigned long>();
    compileFunctionsTT<T, signed long long>();
    compileFunctionsTT<T, unsigned long long>();

    T v(1);

    qc::min(v, v);
    qc::min(v, v, v);

    qc::max(v, v);
    qc::max(v, v, v);

    qc::minmax(v);
    qc::minmax(v, v);
    qc::minmax(v, v, v);
    qc::minmax(v, v, v, v);
    qc::minmax(v, v, v, v, v);
    qc::minmax(v, v, v, v, v, v);
    qc::minmax(v, v, v, v, v, v, v);
    qc::minmax(v, v, v, v, v, v, v, v);

    qc::abs(v);

    qc::clamp(v, v, v);

    qc::zero(v);
    qc::zero(v, v);

    qc::equal(v, v);
    qc::equal(v, v, v);

    qc::sign(v);

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

    qc::equalE(v, v);
    qc::equalE(v, v, v);

    qc::fract(v);
    qc::fract_i(v);

    qc::mix(v, v, v);

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
}

void compileFunctions() {
    compileFunctionsT<float>();
    compileFunctionsT<double>();
    compileFunctionsT<long double>();
    compileFunctionsT<signed char>();
    compileFunctionsT<unsigned char>();
    compileFunctionsT<signed short>();
    compileFunctionsT<unsigned short>();
    compileFunctionsT<signed int>();
    compileFunctionsT<unsigned short>();
    compileFunctionsT<signed long>();
    compileFunctionsT<unsigned long>();
    compileFunctionsT<signed long long>();
    compileFunctionsT<unsigned long long>();

    compileFunctionsFT<float>();
    compileFunctionsFT<double>();
    compileFunctionsFT<long double>();
    
    compileFunctionsIT<signed char>();
    compileFunctionsIT<unsigned char>();
    compileFunctionsIT<signed short>();
    compileFunctionsIT<unsigned short>();
    compileFunctionsIT<signed int>();
    compileFunctionsIT<unsigned short>();
    compileFunctionsIT<signed long>();
    compileFunctionsIT<unsigned long>();
    compileFunctionsIT<signed long long>();
    compileFunctionsIT<unsigned long long>();

    compileFunctionsBT();
}

template <typename T1, typename T2>
constexpr void compileFunctionsConstexprTT() {
    constexpr T1 v(1);

}

template <typename T>
constexpr void compileFunctionsConstexprT() {
    compileFunctionsConstexprTT<T, float>();
    compileFunctionsConstexprTT<T, double>();
    compileFunctionsConstexprTT<T, long double>();
    compileFunctionsConstexprTT<T, signed char>();
    compileFunctionsConstexprTT<T, unsigned char>();
    compileFunctionsConstexprTT<T, signed short>();
    compileFunctionsConstexprTT<T, unsigned short>();
    compileFunctionsConstexprTT<T, signed int>();
    compileFunctionsConstexprTT<T, unsigned short>();
    compileFunctionsConstexprTT<T, signed long>();
    compileFunctionsConstexprTT<T, unsigned long>();
    compileFunctionsConstexprTT<T, signed long long>();
    compileFunctionsConstexprTT<T, unsigned long long>();

    constexpr T v(1);

    qc::min(v, v);
    qc::min(v, v, v);

    qc::max(v, v);
    qc::max(v, v, v);

    qc::minmax(v);
    qc::minmax(v, v);
    qc::minmax(v, v, v);
    qc::minmax(v, v, v, v);
    qc::minmax(v, v, v, v, v);
    qc::minmax(v, v, v, v, v, v);
    qc::minmax(v, v, v, v, v, v, v);
    qc::minmax(v, v, v, v, v, v, v, v);

    //qc::clamp(v, v, v);

    //qc::abs(v);

    //qc::zero(v);
    //qc::zero(v, v);

    //qc::equal(v, v);
    //qc::equal(v, v, v);

    //qc::sign(v);

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

    //qc::equalE(v, v);
    //qc::equalE(v, v, v);

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
}

constexpr bool compileFunctionsConstexpr() {
    compileFunctionsConstexprT<float>();
    compileFunctionsConstexprT<double>();
    compileFunctionsConstexprT<long double>();
    compileFunctionsConstexprT<signed char>();
    compileFunctionsConstexprT<unsigned char>();
    compileFunctionsConstexprT<signed short>();
    compileFunctionsConstexprT<unsigned short>();
    compileFunctionsConstexprT<signed int>();
    compileFunctionsConstexprT<unsigned short>();
    compileFunctionsConstexprT<signed long>();
    compileFunctionsConstexprT<unsigned long>();
    compileFunctionsConstexprT<signed long long>();
    compileFunctionsConstexprT<unsigned long long>();

    compileFunctionsConstexprFT<float>();
    compileFunctionsConstexprFT<double>();
    compileFunctionsConstexprFT<long double>();
    
    compileFunctionsConstexprIT<signed char>();
    compileFunctionsConstexprIT<unsigned char>();
    compileFunctionsConstexprIT<signed short>();
    compileFunctionsConstexprIT<unsigned short>();
    compileFunctionsConstexprIT<signed int>();
    compileFunctionsConstexprIT<unsigned short>();
    compileFunctionsConstexprIT<signed long>();
    compileFunctionsConstexprIT<unsigned long>();
    compileFunctionsConstexprIT<signed long long>();
    compileFunctionsConstexprIT<unsigned long long>();
    
    compileFunctionsConstexprBT();

    return true;
}



}



void testCore() {
    compileTyping();
    compileConstants();
    compileFunctions();
    static_assert(compileFunctionsConstexpr(), "");
}