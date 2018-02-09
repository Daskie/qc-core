#include "QCUTest.hpp"

#include "QCU/CoreFunc.hpp"



namespace {



void compileTyping() {
    qcu::nat nat_;   nat_;
    qcu::unat unat_; unat_;

    qcu::operator""_n(0);
    qcu::operator""_un(0);

    qcu::s08 s08_; s08_;
    qcu::u08 u08_; u08_;
    qcu::s16 s16_; s16_;
    qcu::u16 u16_; u16_;
    qcu::s32 s32_; s32_;
    qcu::u32 u32_; u32_;
    qcu::f32 f32_; f32_;
    qcu::s64 s64_; s64_;
    qcu::u64 u64_; u64_;
    qcu::f64 f64_; f64_;

    qcu::array_t<int> a0{ 1, 2, 3 }; a0;
    qcu::array_t<int, 1> a1; a1;

    qcu::precision<1>::stype p08s_; p08s_;
    qcu::precision<2>::stype p16s_; p16s_;
    qcu::precision<4>::stype p32s_; p32s_;
    qcu::precision<8>::stype p64s_; p64s_;
    qcu::precision<1>::utype p08u_; p08u_;
    qcu::precision<2>::utype p16u_; p16u_;
    qcu::precision<4>::utype p32u_; p32u_;
    qcu::precision<8>::utype p64u_; p64u_;
    qcu::precision<4>::ftype p32f_; p32f_;
    qcu::precision<8>::ftype p64f_; p64f_;
}

template <typename T>
void compileConstantsT() {
    qcu::pi<T>;
    qcu::e<T>;
    qcu::phi<T>;
    qcu::infinity<T>;
    qcu::sqrt<2, T>;
    qcu::sqrt<1000, T>;
}

void compileConstants() {
    compileConstantsT<float>();
    compileConstantsT<double>();
    compileConstantsT<long double>();
}

template <typename T1, typename T2>
void compileFunctionsTT() {
    T1 v(1);

    qcu::transnorm<T2>(v);
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

    qcu::min(v, v);
    qcu::min(v, v, v);

    qcu::max(v, v);
    qcu::max(v, v, v);

    qcu::minmax(v);
    qcu::minmax(v, v);
    qcu::minmax(v, v, v);
    qcu::minmax(v, v, v, v);
    qcu::minmax(v, v, v, v, v);
    qcu::minmax(v, v, v, v, v, v);
    qcu::minmax(v, v, v, v, v, v, v);
    qcu::minmax(v, v, v, v, v, v, v, v);

    qcu::abs(v);

    qcu::clamp(v, v, v);

    qcu::zero(v);
    qcu::zero(v, v);

    qcu::equal(v, v);
    qcu::equal(v, v, v);

    qcu::sign(v);

    qcu::floor(v);

    qcu::ceil(v);

    qcu::mod(v, v);
    qcu::mod_q(v, v);

    qcu::sum(v, v, v, v, v);
    qcu::product(v, v, v, v, v);
}

template <typename T>
void compileFunctionsFT() {
    T v(1.0);

    qcu::equalE(v, v);
    qcu::equalE(v, v, v);

    qcu::fract(v);
    qcu::fract_i(v);

    qcu::mix(v, v, v);

    qcu::average(v, v, v, v, v);

    qcu::radians(v);

    qcu::degrees(v);
}

template <typename T>
void compileFunctionsIT() {
    T v(1);

    qcu::pow2<T>(int(v));

    qcu::isPow2(v);

    qcu::log2Floor(v);

    qcu::log2Ceil(v);

    qcu::floor2(v);

    qcu::ceil2(v);

    qcu::mipmaps(v);

    qcu::highBit(v);

    qcu::lowBit(v);
}

void compileFunctionsBT() {
    bool v(true);

    qcu::equal(v, v);
    qcu::equal(v, v, v);
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

    qcu::min(v, v);
    qcu::min(v, v, v);

    qcu::max(v, v);
    qcu::max(v, v, v);

    qcu::minmax(v);
    qcu::minmax(v, v);
    qcu::minmax(v, v, v);
    qcu::minmax(v, v, v, v);
    qcu::minmax(v, v, v, v, v);
    qcu::minmax(v, v, v, v, v, v);
    qcu::minmax(v, v, v, v, v, v, v);
    qcu::minmax(v, v, v, v, v, v, v, v);

    //qcu::clamp(v, v, v);

    //qcu::abs(v);

    //qcu::zero(v);
    //qcu::zero(v, v);

    //qcu::equal(v, v);
    //qcu::equal(v, v, v);

    //qcu::sign(v);

    //qcu::floor(v);

    //qcu::ceil(v);

    //qcu::mod(v, v);
    //qcu::mod_q(v, v);
    
    qcu::sum(v, v, v, v, v);
    qcu::product(v, v, v, v, v);
}

template <typename T>
constexpr void compileFunctionsConstexprFT() {
    constexpr T v(1.0);

    //qcu::equalE(v, v);
    //qcu::equalE(v, v, v);

    //qcu::fract(v);
    //qcu::fract_i(v);

    //qcu::mix(v, v, v);

    //qcu::average(v, v, v, v, v);

    qcu::radians(v);

    qcu::degrees(v);
}

template <typename T>
constexpr void compileFunctionsConstexprIT() {
    constexpr T v(1);

    qcu::pow2<T>(v);

    qcu::isPow2(v);

    //qcu::log2Floor(v);

    //qcu::log2Ceil(v);

    //qcu::floor2(v);

    //qcu::ceil2(v);

    //qcu::mipmaps(v);

    //qcu::highBit(v);

    //qcu::lowBit(v);
}

constexpr void compileFunctionsConstexprBT() {
    constexpr bool v(true);

    //qcu::equal(v, v);
    //qcu::equal(v, v, v);    
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