#include "QMUTest.hpp"

#include "QMU/QMU.hpp"



using namespace qmu;



namespace {



void testTyping() {
    nat nat_;   nat_;
    unat unat_; unat_;

    0_n;
    0_un;

    s08 s08_; s08_;
    u08 u08_; u08_;
    s16 s16_; s16_;
    u16 u16_; u16_;
    s32 s32_; s32_;
    u32 u32_; u32_;
    s64 s64_; s64_;
    u64 u64_; u64_;

    precision< 8>::stype p8s_;  p8s_;
    precision< 8>::utype p8u_;  p8u_;
    precision<16>::stype p16s_; p16s_;
    precision<16>::utype p16u_; p16u_;
    precision<32>::stype p32s_; p32s_;
    precision<32>::utype p32u_; p32u_;
    precision<64>::stype p64s_; p64s_;
    precision<64>::utype p64u_; p64u_;
}

template <typename T>
void testConstantsT() {
    pi<T>;
    e<T>;
    phi<T>;
    qmu::sqrt<T, 2>;
    qmu::sqrt<T, 3>;
    infinity<T>;
}

void testConstants() {
    testConstantsT<float>();
    testConstantsT<double>();
    testConstantsT<long double>();
}

template <typename T>
void testFunctionsT() {
    T v(0);

    min(v, v);
    min(v, v, v);

    max(v, v);
    max(v, v, v);

    clamp(v, v, v);

    abs(v);

    zero(v);

    equal(v, v);

    sign(v);
}

template <typename T>
void testFunctionsFT() {
    T v(0.0);

    trunc(v);

    fract(v);

    mix(v, v, v);

    radians(v);

    degrees(v);
}

template <typename T>
void testFunctionsIT() {
    T v(0);

    qmu::log2(v);

    isPow2(v);

    floor2(v);

    ceil2(v);

    highBit(v);

    lowBit(v);
}

void testFunctions() {
    testFunctionsT<float>();
    testFunctionsT<double>();
    testFunctionsT<long double>();
    testFunctionsT<signed char>();
    testFunctionsT<unsigned char>();
    testFunctionsT<signed short>();
    testFunctionsT<unsigned short>();
    testFunctionsT<signed int>();
    testFunctionsT<unsigned short>();
    testFunctionsT<signed long>();
    testFunctionsT<unsigned long>();
    testFunctionsT<signed long long>();
    testFunctionsT<signed long long>();
    testFunctionsT<bool>();

    testFunctionsFT<float>();
    testFunctionsFT<double>();
    testFunctionsFT<long double>();
    
    testFunctionsIT<signed char>();
    testFunctionsIT<unsigned char>();
    testFunctionsIT<signed short>();
    testFunctionsIT<unsigned short>();
    testFunctionsIT<signed int>();
    testFunctionsIT<unsigned short>();
    testFunctionsIT<signed long>();
    testFunctionsIT<unsigned long>();
    testFunctionsIT<signed long long>();
    testFunctionsIT<signed long long>();
}



}



void testQMU() {
    testTyping();
    testConstants();
    testFunctions();
}