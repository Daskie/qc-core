#pragma once



#include <cstdint>
#include <type_traits>
#include <cmath>
#include <limits>



namespace qmu {



using  nat =  intptr_t;
using unat = uintptr_t;

using   s08 =   int8_t;
using   u08 =  uint8_t;
using   s16 =  int16_t;
using   u16 = uint16_t;
using   s32 =  int32_t;
using   u32 = uint32_t;
using   s64 =  int64_t;
using   u64 = uint64_t;
struct  s128 {
	union {
		struct { s64 s64_1, s64_2; };
		struct { s32 s32_1, s32_2, s32_3, s32_4; };
	};
};
struct u128 {
	union {
		struct { u64 u64_1, u64_2; };
		struct { u32 u32_1, u32_2, u32_3, u32_4; };
	};
};

template <nat t_p> struct precision;
template        <> struct precision< 32> { using stype =  s32; using utype =  u32; };
template        <> struct precision< 64> { using stype =  s64; using utype =  u64; };
template        <> struct precision<128> { using stype = s128; using utype = u128; };

template <nat t_p> using precision_st  = typename precision<t_p>::stype;
template <nat t_p> using precision_ut = typename precision<t_p>::utype;

constexpr nat gk_nat_p = sizeof(nat) * 8;



template <typename T1, typename T2>
using match_sign_t = std::conditional_t<std::is_signed<T2>::value, std::make_signed_t<T1>, std::make_unsigned_t<T1>>;



template <typename T>
constexpr const T & min(const T & a, const T & b) {
	return a < b ? a : b;
}

template <typename T>
constexpr const T & max(const T & a, const T & b) {
	return a > b ? a : b;
}

template <typename T, typename... Ts>
constexpr const T & min(const T & a, const T & b, const Ts & ... rest) {
	return min(a < b ? a : b, rest...);
}

template <typename T, typename... Ts>
constexpr const T & max(const T & a, const T & b, const Ts & ... rest) {
	return max(a > b ? a : b, rest...);
}

template <typename T>
constexpr T clamp(const T & v, const T & min, const T & max) {
	return v >= min ? (v <= max ? v : max) : min;
}

template <typename T, std::enable_if_t<!std::is_unsigned<T>::value, int> = 0>
constexpr T abs(const T & v) {
	return v < 0 ? -v : v;
}

template <typename T, std::enable_if_t<std::is_unsigned<T>::value, int> = 0>
constexpr T abs(const T & v) {
	return v;
}

template <typename T, std::enable_if_t<std::is_floating_point<T>::value, int> = 0>
constexpr bool zero(const T & v, const T & e = std::numeric_limits<T>::min()) {
	return abs(v) < e;
}

template <typename T, std::enable_if_t<!std::is_floating_point<T>::value, int> = 0>
constexpr bool zero(const T & v) {
	return v == 0;
}

template <typename T, std::enable_if_t<std::is_floating_point<T>::value, int> = 0>
constexpr bool equal(const T & v1, const T & v2, const T & e = std::numeric_limits<T>::min()) {
	return zero(v1 - v2, e);
}

template <typename T, std::enable_if_t<!std::is_floating_point<T>::value, int> = 0>
constexpr bool zero(const T & v1, const T & v2) {
	return zero(v1 - v2);
}


template <typename T, std::enable_if_t<std::is_integral<T>::value && sizeof(T) == 1, int> = 0>
inline match_sign_t<nat, T> log2(T x) {
	match_sign_t<nat, T> log(0);
	if (x & 0xF0) { x >>=  4; log +=  4; }
	if (x & 0x0C) { x >>=  2; log +=  2; }
	if (x & 0x02) {			  log +=  1; }
	return log;
}

template <typename T, std::enable_if_t<std::is_integral<T>::value && sizeof(T) == 2, int> = 0>
inline match_sign_t<nat, T> log2(T x) {
	match_sign_t<nat, T> log(0);
	if (x & 0xFF00) { x >>=  8; log +=  8; }
	if (x & 0x00F0) { x >>=  4; log +=  4; }
	if (x & 0x000C) { x >>=  2; log +=  2; }
	if (x & 0x0002) {			log +=  1; }
	return log;
}

template <typename T, std::enable_if_t<std::is_integral<T>::value && sizeof(T) == 4, int> = 0>
inline match_sign_t<nat, T> log2(T x) {
	match_sign_t<nat, T> log(0);
	if (x & 0xFFFF0000) { x >>= 16; log += 16; }
	if (x & 0x0000FF00) { x >>=  8; log +=  8; }
	if (x & 0x000000F0) { x >>=  4; log +=  4; }
	if (x & 0x0000000C) { x >>=  2; log +=  2; }
	if (x & 0x00000002) {			log +=  1; }
	return log;
}

template <typename T, std::enable_if_t<std::is_integral<T>::value && sizeof(T) == 8, int> = 0>
inline match_sign_t<nat, T> log2(T x) {
	match_sign_t<nat, T> log(0);
	if (x & 0xFFFFFFFF00000000) { x >>= 32; log += 32; }
	if (x & 0x00000000FFFF0000) { x >>= 16; log += 16; }
	if (x & 0x000000000000FF00) { x >>=  8; log +=  8; }
	if (x & 0x00000000000000F0) { x >>=  4; log +=  4; }
	if (x & 0x000000000000000C) { x >>=  2; log +=  2; }
	if (x & 0x0000000000000002) {			log +=  1; }
	return log;
}

inline float log2(float v) {
	return std::log2f(v);
}

inline double log2(double v) {
	return std::log2(v);
}

template <typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
constexpr bool isPow2(T v) {
	return (v & (v - 1)) == 0;
}

template <typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
inline T floor2(T v) {
	if (v == 0) return 0;
	return T(1) << log2(v);
}

template <typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
inline T ceil2(T v) {
	if (v == 0) return 0;
	return floor2(v * 2 - 1);
}



}