#pragma once



#include <cstdint>



namespace qmu {



namespace type {



using  nat =  intptr_t;
using unat = uintptr_t;
using fnat = std::conditional_t<sizeof(nat) == 4,
			     float,
			 std::conditional_t<sizeof(nat) == 8,
			    double,
			      void>>;

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
template        <> struct precision< 32> { using type =  s32; using utype = u32; };
template        <> struct precision< 64> { using type =  s64; using utype = u64; };
template        <> struct precision<128> { using type = s128; using utype = u128; };

template <nat t_p> using precision_t  = typename precision<t_p>::type;
template <nat t_p> using precision_ut = typename precision<t_p>::utype;

constexpr nat gk_nat_p = sizeof(nat) * 8;



}



}