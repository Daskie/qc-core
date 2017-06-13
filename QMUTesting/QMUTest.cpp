#include "QMUTest.hpp"

#include "QMU/QMU.hpp"



namespace {



void compileTyping() {
    qmu::nat nat_;   nat_;
    qmu::unat unat_; unat_;

    qmu::operator""_n(0);
    qmu::operator""_un(0);

    qmu::s08 s08_; s08_;
    qmu::u08 u08_; u08_;
    qmu::s16 s16_; s16_;
    qmu::u16 u16_; u16_;
    qmu::s32 s32_; s32_;
    qmu::u32 u32_; u32_;
    qmu::s64 s64_; s64_;
    qmu::u64 u64_; u64_;

    qmu::precision< 8>::stype p8s_;  p8s_;
    qmu::precision< 8>::utype p8u_;  p8u_;
    qmu::precision<16>::stype p16s_; p16s_;
    qmu::precision<16>::utype p16u_; p16u_;
    qmu::precision<32>::stype p32s_; p32s_;
    qmu::precision<32>::utype p32u_; p32u_;
    qmu::precision<64>::stype p64s_; p64s_;
    qmu::precision<64>::utype p64u_; p64u_;
}

template <typename T>
void compileConstantsT() {
    qmu::pi<T>;
    qmu::e<T>;
    qmu::phi<T>;
    qmu::sqrt<T, 2>;
    qmu::sqrt<T, 3>;
    qmu::infinity<T>;
}

void compileConstants() {
    compileConstantsT<float>();
    compileConstantsT<double>();
    compileConstantsT<long double>();
}

template <typename T>
void compileFunctionsT() {
    T v(0);

    qmu::min(v, v);
    qmu::min(v, v, v);

    qmu::max(v, v);
    qmu::max(v, v, v);

    qmu::abs(v);

    qmu::clamp(v, v, v);

    qmu::zero(v);

    qmu::equal(v, v);
    qmu::equal(v, v, v);

    qmu::sign(v);
}

template <typename T>
void compileFunctionsFT() {
    T v(0.0);

    qmu::trunc(v);

    qmu::fract(v);

    qmu::mix(v, v, v);

    qmu::radians(v);

    qmu::degrees(v);
}

template <typename T>
void compileFunctionsIT() {
    T v(0);

    qmu::log2(v);

    qmu::isPow2(v);

    qmu::floor2(v);

    qmu::ceil2(v);

    qmu::highBit(v);

    qmu::lowBit(v);
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
    compileFunctionsT<signed long long>();
    compileFunctionsT<bool>();

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
    compileFunctionsIT<signed long long>();
}

template <typename T>
constexpr void compileFunctionsConstexprT() {
    constexpr T v(0);

    qmu::min(v, v);
    qmu::min(v, v, v);

    qmu::max(v, v);
    qmu::max(v, v, v);

    qmu::abs(v);

    qmu::clamp(v, v, v);

    qmu::zero(v);

    qmu::equal(v, v);
    qmu::equal(v, v, v);

    qmu::sign(v);
}

template <typename T>
constexpr void compileFunctionsConstexprFT() {
    constexpr T v(0.0);

    qmu::trunc(v);

    qmu::fract(v);

    qmu::mix(v, v, v);

    qmu::radians(v);

    qmu::degrees(v);
}

template <typename T>
constexpr void compileFunctionsConstexprIT() {
    constexpr T v(0);

    qmu::log2(v);

    qmu::isPow2(v);

    qmu::floor2(v);

    qmu::ceil2(v);

    qmu::highBit(v);

    qmu::lowBit(v);
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
    compileFunctionsConstexprT<signed long long>();
    compileFunctionsConstexprT<bool>();

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
    compileFunctionsConstexprIT<signed long long>();

    return true;
}



}



void testQMU() {
    compileTyping();
    compileConstants();
    compileFunctions();
    static_assert(compileFunctionsConstexpr(), "");
}