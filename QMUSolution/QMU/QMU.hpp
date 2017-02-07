#pragma once



#include <cstdint>



namespace qmu {



using  nat =  intptr_t;
using unat = uintptr_t;
using fnat = std::conditional_t<sizeof(nat) == 4,
			     float,
			 std::conditional_t<sizeof(nat) == 8,
			    double,
			      void>>;

using     i8 =   int8_t;
using    ui8 =  uint8_t;
using    i16 =  int16_t;
using   ui16 = uint16_t;
using    i32 =  int32_t;
using   ui32 = uint32_t;
using    i64 =  int64_t;
using   ui64 = uint64_t;
struct  i128 {
	union {
		struct { i32 i32_1, i32_2, i32_3, i32_4; };
		struct { i64 i64_1, i64_2; };
	};
};
struct ui128 {
	union {
		struct { ui32 ui32_1, ui32_2, ui32_3, ui32_4; };
		struct { ui64 ui64_1, ui64_2; };
	};
};

template <nat t_p> struct precision;
template        <> struct precision< 32> { using type =  i32; using utype =  ui32; };
template        <> struct precision< 64> { using type =  i64; using utype =  ui64; };
template        <> struct precision<128> { using type = i128; using utype = ui128; };

template <nat t_p> using precision_t  = typename precision<t_p>::type;
template <nat t_p> using precision_ut = typename precision<t_p>::utype;

constexpr nat gk_nat_p = sizeof(nat) * 8;



}