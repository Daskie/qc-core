#pragma once



#include "CoreFunc.hpp"



namespace qc {



namespace bits {



template <typename T, eif_uintegral_t<T> = 0>
constexpr T rotateL(T v, int n);

template <typename T, eif_uintegral_t<T> = 0>
constexpr T rotateR(T v, int n);

template <typename SrcT, typename DstT, eif_t<std::is_integral_v<SrcT> && std::is_integral_v<DstT> && std::is_unsigned_v<SrcT> && std::is_unsigned_v<DstT> && (sizeof(DstT) > sizeof(SrcT))> = 0>
DstT spread(SrcT v);

template <typename SrcT, typename DstT, eif_t<std::is_integral_v<SrcT> && std::is_integral_v<DstT> && std::is_unsigned_v<SrcT> && std::is_unsigned_v<DstT> && (sizeof(DstT) >= sizeof(SrcT))> = 0>
DstT repeat(SrcT v);

template <typename T, eif_uintegral_t<T> = 0>
T interleave(T v);

template <typename T, eif_uintegral_t<T> = 0>
T scramble(T v);



}



}



#include "Bits.tpp"