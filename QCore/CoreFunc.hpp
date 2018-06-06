#pragma once



#include "Core.hpp"



namespace qc {




template <typename T>
Q_CX_ABLE T clamp(const T & v, const T & min, const T & max);

// allows unsigned and constexpr
template <typename T, eif_arithmetic_t<T> = 0>
Q_CX_ABLE T abs(T v);

template <typename T, eif_arithmetic_t<T> = 0>
Q_CX_ABLE bool zero(T v, T e = std::numeric_limits<T>::epsilon());

template <typename T>
Q_CX_ABLE bool equal(const T & v1, const T & v2);

template <typename T, typename... Ts>
Q_CX_ABLE bool equal(const T & v1, const T & v2, const Ts &... rest);

template <typename T, eif_floating_t<T> = 0>
Q_CX_ABLE bool equalE(T v1, T v2, T e = std::numeric_limits<T>::epsilon());

template <typename T, eif_arithmetic_t<T> = 0>
Q_CX_ABLE T sign(T v);

// ~2x faster than std::floor
// doesn't work with some edge cases
template <typename T, eif_floating_t<T> = 0>
Q_CX_ABLE nat floor(T v);

template <typename T, eif_integral_t<T> = 0>
Q_CX_ABLE T floor(T v);

// ~2x faster than std::ceil
// doesn't work with some edge cases
template <typename T, eif_floating_t<T> = 0>
Q_CX_ABLE nat ceil(T v);

template <typename T, eif_integral_t<T> = 0>
Q_CX_ABLE T ceil(T v);

template <typename T>
Q_CONSTEX T pow2(int v);

template <typename T, eif_integral_t<T> = 0>
Q_CONSTEX bool isPow2(T v);

template <typename T, eif_integral_t<T> = 0>
Q_CONSTEX int log2Floor(T v);

template <typename T, eif_integral_t<T> = 0>
Q_CONSTEX int log2Ceil(T v);

template <typename T, eif_integral_t<T> = 0>
Q_CX_ABLE T floor2(T v);

template <typename T, eif_integral_t<T> = 0>
Q_CX_ABLE T ceil2(T v);

template <typename T, eif_integral_t<T> = 0>
Q_CX_ABLE T mipmaps(T size);

template <typename T, eif_integral_t<T> = 0>
Q_CX_ABLE T highBit(T v);

template <typename T, eif_integral_t<T> = 0>
Q_CX_ABLE T lowBit(T v);

template <typename T, eif_integral_t<T> = 0>
Q_CX_ABLE T iBit(T v, int i);

// ~3.3x faster than std::modf
template <typename T, eif_floating_t<T> = 0>
Q_CX_ABLE T fract(T v);

template <typename T, eif_floating_t<T> = 0>
Q_CX_ABLE std::pair<T, nat> fract_i(T v);

// ~2.5x faster than std::fmod
template <typename T, eif_arithmetic_t<T> = 0>
Q_CX_ABLE T mod(T v, T d);

template <typename T, eif_arithmetic_t<T> = 0>
Q_CX_ABLE std::pair<T, T> mod_q(T v, T d);

template <typename T, eif_floating_t<T> = 0>
Q_CX_ABLE T mix(T v1, T v2, T t);

template <typename T, typename... Args>
Q_CONSTEX T sum(const T & v, const Args &... args);

template <typename T, typename... Args>
Q_CONSTEX T product(const T & v, const Args &... args);

template <typename T, eif_floating_t<T> = 0, typename... Args>
Q_CX_ABLE T average(T v, Args... args);

template <typename T, eif_floating_t<T> = 0>
Q_CX_ABLE T radians(T degrees);

template <typename T, eif_floating_t<T> = 0>
Q_CX_ABLE T degrees(T radians);

// converts between normalized types
// works with floats and integers, signed and unsigned
template <typename To, typename From, eif_t<std::is_arithmetic_v<To> && std::is_arithmetic_v<From>> = 0>
Q_CONSTEX To transnorm(From v);



}



#include "CoreFunc.tpp"