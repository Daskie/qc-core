#pragma once

#include "Core.hpp"

namespace qc {

template <typename T,                 typename = eif_arithmetic_t<T>> Q_CX_ABLE duo<T> minmax(T a);
template <typename T,                 typename = eif_arithmetic_t<T>> Q_CX_ABLE duo<T> minmax(T a, T b);
template <typename T, typename... Ts, typename = eif_arithmetic_t<T>> Q_CX_ABLE duo<T> minmax(T a, T b, Ts... rest);

template <typename T, typename = eif_arithmetic_t<T>> Q_CX_ABLE T median(T a, T b, T c);

template <typename T> Q_CX_ABLE T clamp(const T & v, const T & min, const T & max);

// allows unsigned and constexpr
template <typename T, typename = eif_arithmetic_t<T>> Q_CX_ABLE T abs(T v);

template <typename T, typename = eif_arithmetic_t<T>> Q_CX_ABLE bool zero(T v, T e = std::numeric_limits<T>::epsilon());

template <typename T> Q_CX_ABLE bool equal(const T & v1, const T & v2);
template <typename T, typename... Ts> Q_CX_ABLE bool equal(const T & v1, const T & v2, const Ts &... rest);

template <typename T, typename = eif_floating_t<T>> Q_CX_ABLE bool equal_e(T v1, T v2, T e = std::numeric_limits<T>::epsilon());

template <typename T, typename = eif_arithmetic_t<T>> Q_CX_ABLE int sign(T v);

// ~12x faster than std::llround
// Only works for "normal" values of absolute magnitude smaller than roughly one quadrillion for doubles or one million for floats
// Any exact 0.5 value is not guaranteed to round up - it may go either way
Q_CX_ABLE s64 round(double v);
Q_CX_ABLE s32 round(float v);
template <typename T, typename = eif_integral_t<T>> Q_CX_ABLE T round(T v);

// ~2x faster than std::floor
// doesn't work with extememly large or extremely small floating point values
template <typename T, typename = eif_floating_t<T>> Q_CX_ABLE nat floor(T v);
template <typename T, typename = eif_integral_t<T>> Q_CX_ABLE T floor(T v);

// ~2x faster than std::ceil
// doesn't work with extememly large or extremely small floating point values
template <typename T, typename = eif_floating_t<T>> Q_CX_ABLE nat ceil(T v);
template <typename T, typename = eif_integral_t<T>> Q_CX_ABLE T ceil(T v);

// ~2.15x faster than std::pow
template <typename T, typename = eif_floating_t<T>> Q_CX_ABLE T pow(T v, int e);
template <typename T, typename = eif_floating_t<T>> Q_CX_ABLE T pow(T v, uint e);

template <typename T, typename = eif_integral_t<T>> Q_CONSTEX T pow2(int v);

template <typename T, typename = eif_integral_t<T>> Q_CONSTEX bool isPow2(T v);

template <typename T, typename = eif_integral_t<T>> Q_CONSTEX int log2Floor(T v);

template <typename T, typename = eif_integral_t<T>> Q_CONSTEX int log2Ceil(T v);

template <typename T, typename = eif_integral_t<T>> Q_CONSTEX T floor2(T v);

template <typename T, typename = eif_integral_t<T>> Q_CONSTEX T ceil2(T v);

template <typename T, typename = eif_integral_t<T>> Q_CX_ABLE int mipmaps(T size);

template <typename T, typename = eif_integral_t<T>> Q_CX_ABLE T highBit(T v);

template <typename T, typename = eif_integral_t<T>> Q_CX_ABLE T lowBit(T v);

template <typename T, typename = eif_integral_t<T>> Q_CX_ABLE T iBit(T v, int i);

template <typename T, typename = eif_integral_t<T>> Q_CONSTEX T smear(T v);

// ~3.3x faster than std::modf
template <typename T, typename = eif_floating_t<T>> Q_CX_ABLE T fract(T v);

template <typename T, typename = eif_floating_t<T>> Q_CX_ABLE pair<T, nat> fract_i(T v);

// ~2.5x faster than std::fmod
template <typename T, typename = eif_arithmetic_t<T>> Q_CX_ABLE T mod(T v, T d);

template <typename T, typename = eif_arithmetic_t<T>> Q_CX_ABLE duo<T> mod_q(T v, T d);

template <typename T, typename = eif_floating_t<T>> Q_CX_ABLE T mix(T v1, T v2, T t);

template <typename T, typename... Args> Q_CONSTEX T sum(const T & v, const Args &... args);

template <typename T, typename... Args> Q_CONSTEX T product(const T & v, const Args &... args);

template <typename T, typename = eif_floating_t<T>, typename... Args> Q_CX_ABLE T average(T v, Args... args);

template <typename T, typename = eif_floating_t<T>> Q_CX_ABLE T radians(T degrees);

template <typename T, typename = eif_floating_t<T>> Q_CX_ABLE T degrees(T radians);

// converts between normalized types
// works with floats and integers, signed and unsigned
template <typename To, typename From, typename = eif_t<is_arithmetic_v<To> && is_arithmetic_v<From>>> Q_CONSTEX To transnorm(From v);

}

#include "CoreFunc.tpp"
