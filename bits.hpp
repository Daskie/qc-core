#pragma once

#include "include/qc-core/core-ext.hpp"

namespace qc::bits
{

    template <UnsignedIntegral SrcT, UnsignedIntegral DstT> requires (sizeof(DstT) > sizeof(SrcT)) DstT spread(SrcT v);

    template <UnsignedIntegral SrcT, UnsignedIntegral DstT> requires (sizeof(DstT) >= sizeof(SrcT)) DstT repeat(SrcT v);

    template <UnsignedIntegral T> T interleave(T v);

    template <UnsignedIntegral T> T scramble(T v);

}

// INLINE IMPLEMENTATION ///////////////////////////////////////////////////////////////////////////////////////////////

namespace qc::bits
{

    template <UnsignedIntegral SrcT, UnsignedIntegral DstT> requires (sizeof(DstT) > sizeof(SrcT))
    inline DstT spread(const SrcT v)
    {
        constexpr uint factor{sizeof(DstT) / sizeof(SrcT) - 1u};

        DstT w{v};

        if constexpr (sizeof(SrcT) >= 4u)
        {
            w = ((w << (factor << 4)) | w) & DstT(0x0000FFFF0000FFFF);
        }
        if constexpr (sizeof(SrcT) >= 2u)
        {
            w = ((w << (factor << 3)) | w) & DstT(0x00FF00FF00FF00FF);
        }
        w = ((w << (factor << 2)) | w) & DstT(0x0F0F0F0F0F0F0F0F);
        w = ((w << (factor << 1)) | w) & DstT(0x3333333333333333);
        w = ((w << (factor << 0)) | w) & DstT(0x5555555555555555);

        return w;
    }

    template <UnsignedIntegral SrcT, UnsignedIntegral DstT> requires (sizeof(DstT) >= sizeof(SrcT))
    inline DstT repeat(const SrcT v)
    {
        constexpr uint factor{sizeof(DstT) / sizeof(SrcT)};

        DstT w{v};

        if constexpr (factor >= 2u)
        {
            w |= w << sizeof(SrcT) * 1u * 8u;
        }
        if constexpr (factor >= 4u)
        {
            w |= w << sizeof(SrcT) * 2u * 8u;
        }
        if constexpr (factor >= 8u)
        {
            w |= w << sizeof(SrcT) * 4u * 8u;
        }

        return w;
    }

    template <UnsignedIntegral T>
    inline T interleave(const T v)
    {
        if constexpr (sizeof(T) > 1u)
        {
            using H = typename sized<sizeof(T) / 2u>::utype;

            const H h1{H(v >> sizeof(H) * 8u)}, h2{H(v)};

            return (spread<H, T>(h1) << 1) | spread<H, T>(h2);
        }
        if constexpr (sizeof(T) == 1u)
        {
            T h1{T(v >> 4)};
            T h2{v};

            h1 = ((h1 << 2) | h1) & T(0x33);
            h1 = ((h1 << 1) | h1) & T(0x55);
            h2 = ((h2 << 2) | h2) & T(0x33);
            h2 = ((h2 << 1) | h2) & T(0x55);

            return (h1 << 1) | h2;
        }
    }

    template <UnsignedIntegral T>
    inline T scramble(T v)
    {
        if constexpr (sizeof(T) == 1u)
        {
            return v;
        }

        if constexpr (sizeof(T) == 2u)
        {
            u64 w(0u);

            w |= spread<u8, u64>(u8(v)) << 0; v >>= 8;
            w |= spread<u8, u64>(u8(v)) << 4; v >>= 8;

            return u16(w >> 45) | u16(w >> 30) | u16(w >> 15) | u16(w);
        }

        if constexpr (sizeof(T) == 4u)
        {
            u64 w(0u);

            w |= spread<u8, u64>(u8(v)) << 0; v >>= 8;
            w |= spread<u8, u64>(u8(v)) << 2; v >>= 8;
            w |= spread<u8, u64>(u8(v)) << 4; v >>= 8;
            w |= spread<u8, u64>(u8(v)) << 6; v >>= 8;

            return u32(w >> 31) | u32(w);
        }

        if constexpr (sizeof(T) == 8u)
        {
            u64 w(0u);

            w |= spread<u8, u64>(u8(v)) << 0; v >>= 8;
            w |= spread<u8, u64>(u8(v)) << 1; v >>= 8;
            w |= spread<u8, u64>(u8(v)) << 2; v >>= 8;
            w |= spread<u8, u64>(u8(v)) << 3; v >>= 8;
            w |= spread<u8, u64>(u8(v)) << 4; v >>= 8;
            w |= spread<u8, u64>(u8(v)) << 5; v >>= 8;
            w |= spread<u8, u64>(u8(v)) << 6; v >>= 8;
            w |= spread<u8, u64>(u8(v)) << 7; v >>= 8;

            return w;
        }
    }

} // namespace qc::bits
