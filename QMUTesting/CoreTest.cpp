#include "QMUTest.hpp"

#include "QMU/Core.hpp"



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
    qmu::f32 f32_; f32_;
    qmu::s64 s64_; s64_;
    qmu::u64 u64_; u64_;
    qmu::f64 f64_; f64_;

    qmu::array_t<int> a0{ 1, 2, 3 }; a0;
    qmu::array_t<int, 1> a1; a1;

    qmu::precision<1>::stype p08s_; p08s_;
    qmu::precision<2>::stype p16s_; p16s_;
    qmu::precision<4>::stype p32s_; p32s_;
    qmu::precision<8>::stype p64s_; p64s_;
    qmu::precision<1>::utype p08u_; p08u_;
    qmu::precision<2>::utype p16u_; p16u_;
    qmu::precision<4>::utype p32u_; p32u_;
    qmu::precision<8>::utype p64u_; p64u_;
    qmu::precision<4>::ftype p32f_; p32f_;
    qmu::precision<8>::ftype p64f_; p64f_;
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

template <typename T1, typename T2>
void compileFunctionsTT() {
    T1 v(1);

    qmu::transnorm<T2>(v);
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

    qmu::min(v, v);
    qmu::min(v, v, v);

    qmu::max(v, v);
    qmu::max(v, v, v);

    qmu::minmax(v);
    qmu::minmax(v, v);
    qmu::minmax(v, v, v);
    qmu::minmax(v, v, v, v);
    qmu::minmax(v, v, v, v, v);
    qmu::minmax(v, v, v, v, v, v);
    qmu::minmax(v, v, v, v, v, v, v);
    qmu::minmax(v, v, v, v, v, v, v, v);

    qmu::abs(v);

    qmu::clamp(v, v, v);

    qmu::zero(v);

    qmu::equal(v, v);
    qmu::equal(v, v, v);

    qmu::sign(v);

    qmu::floor(v);

    qmu::ceil(v);

    qmu::mod(v, v);
    qmu::mod_q(v, v);

    qmu::sum(v, v, v, v, v);
    qmu::product(v, v, v, v, v);
}

template <typename T>
void compileFunctionsFT() {
    T v(1.0);

    qmu::fract(v);
    qmu::fract_i(v);

    qmu::mix(v, v, v);

    qmu::average(v, v, v, v, v);

    qmu::radians(v);

    qmu::degrees(v);
}

template <typename T>
void compileFunctionsIT() {
    T v(1);

    qmu::pow2<T>(v);

    qmu::isPow2(v);

    qmu::log2Floor(v);

    qmu::log2Ceil(v);

    qmu::floor2(v);

    qmu::ceil2(v);

    qmu::highBit(v);

    qmu::lowBit(v);

    qmu::bits::rotateL(v, 0);

    qmu::bits::rotateR(v, 0);

    qmu::bits::interleave(v);

    qmu::bits::scramble(v);
}

void compileFunctionsBT() {
    bool v(true);

    qmu::equal(v, v);
    qmu::equal(v, v, v);

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

    qmu::bits::spread<qmu::u08, qmu::u16>(-1);
    qmu::bits::spread<qmu::u08, qmu::u32>(-1);
    qmu::bits::spread<qmu::u08, qmu::u64>(-1);
    qmu::bits::spread<qmu::u16, qmu::u32>(-1);
    qmu::bits::spread<qmu::u16, qmu::u64>(-1);
    qmu::bits::spread<qmu::u32, qmu::u64>(-1);
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

    qmu::min(v, v);
    qmu::min(v, v, v);

    qmu::max(v, v);
    qmu::max(v, v, v);

    qmu::minmax(v);
    qmu::minmax(v, v);
    qmu::minmax(v, v, v);
    qmu::minmax(v, v, v, v);
    qmu::minmax(v, v, v, v, v);
    qmu::minmax(v, v, v, v, v, v);
    qmu::minmax(v, v, v, v, v, v, v);
    qmu::minmax(v, v, v, v, v, v, v, v);

    qmu::abs(v);

    qmu::clamp(v, v, v);

    qmu::zero(v);

    qmu::equal(v, v);
    qmu::equal(v, v, v);

    qmu::sign(v);

    qmu::floor(v);

    qmu::ceil(v);

    qmu::mod(v, v);
    qmu::mod_q(v, v);
    
    qmu::sum(v, v, v, v, v);
    qmu::product(v, v, v, v, v);
}

template <typename T>
constexpr void compileFunctionsConstexprFT() {
    constexpr T v(1.0);

    qmu::fract(v);
    qmu::fract_i(v);

    qmu::mix(v, v, v);

    qmu::average(v, v, v, v, v);

    qmu::radians(v);

    qmu::degrees(v);
}

template <typename T>
constexpr void compileFunctionsConstexprIT() {
    constexpr T v(1);

    qmu::pow2<T>(v);

    qmu::isPow2(v);

    qmu::log2Floor(v);

    qmu::log2Ceil(v);

    qmu::floor2(v);

    qmu::ceil2(v);

    qmu::highBit(v);

    qmu::lowBit(v);

    qmu::bits::rotateL(v, 0);

    qmu::bits::rotateR(v, 0);

    qmu::bits::interleave(v);

    qmu::bits::scramble(v);
}

constexpr void compileFunctionsConstexprBT() {
    constexpr bool v(true);

    qmu::equal(v, v);
    qmu::equal(v, v, v);

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

    qmu::bits::spread<qmu::u08, qmu::u16>(-1);
    qmu::bits::spread<qmu::u08, qmu::u32>(-1);
    qmu::bits::spread<qmu::u08, qmu::u64>(-1);
    qmu::bits::spread<qmu::u16, qmu::u32>(-1);
    qmu::bits::spread<qmu::u16, qmu::u64>(-1);
    qmu::bits::spread<qmu::u32, qmu::u64>(-1);

    return true;
}



}



void testQMU() {
    compileTyping();
    compileConstants();
    compileFunctions();
    static_assert(compileFunctionsConstexpr(), "");
}