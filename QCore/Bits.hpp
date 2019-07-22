#pragma once



#include "CoreFunc.hpp"



namespace qc {



namespace bits {



template <typename T, typename = eif_uintegral_t<T>>
constexpr T rotateL(T v, int n);

template <typename T, typename = eif_uintegral_t<T>>
constexpr T rotateR(T v, int n);

template <typename SrcT, typename DstT, typename = eif_t<is_integral_v<SrcT> && is_integral_v<DstT> && is_unsigned_v<SrcT> && is_unsigned_v<DstT> && (sizeof(DstT) > sizeof(SrcT))>>
DstT spread(SrcT v);

template <typename SrcT, typename DstT, typename = eif_t<is_integral_v<SrcT> && is_integral_v<DstT> && is_unsigned_v<SrcT> && is_unsigned_v<DstT> && (sizeof(DstT) >= sizeof(SrcT))>>
DstT repeat(SrcT v);

template <typename T, typename = eif_uintegral_t<T>>
T interleave(T v);

template <typename T, typename = eif_uintegral_t<T>>
T scramble(T v);



}



}



#include "Bits.tpp"