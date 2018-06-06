namespace qc {



namespace bits {



template <typename SrcT, typename DstT, eif_t<std::is_integral_v<SrcT> && std::is_integral_v<DstT> && std::is_unsigned_v<SrcT> && std::is_unsigned_v<DstT> && (sizeof(DstT) > sizeof(SrcT))>>
inline DstT spread(SrcT v) {
    constexpr int factor(sizeof(DstT) / sizeof(SrcT) - 1);
    
    DstT w(v);

    if constexpr (sizeof(SrcT) >= 4) {
        w = ((w << (16 * factor)) | w) & DstT(0x0000FFFF0000FFFFULL);
    }
    if constexpr (sizeof(SrcT) >= 2) {
        w = ((w << ( 8 * factor)) | w) & DstT(0x00FF00FF00FF00FFULL);
    }
        w = ((w << ( 4 * factor)) | w) & DstT(0x0F0F0F0F0F0F0F0FULL);
        w = ((w << ( 2 * factor)) | w) & DstT(0x3333333333333333ULL);
        w = ((w << ( 1 * factor)) | w) & DstT(0x5555555555555555ULL);

    return w;
}

template <typename SrcT, typename DstT, eif_t<std::is_integral_v<SrcT> && std::is_integral_v<DstT> && std::is_unsigned_v<SrcT> && std::is_unsigned_v<DstT> && (sizeof(DstT) >= sizeof(SrcT))>>
inline DstT repeat(SrcT v) {
    constexpr int factor(sizeof(DstT) / sizeof(SrcT));

    DstT w(v);

    if constexpr (factor >= 2) {
        w |= w << (sizeof(SrcT) * 1 * 8);
    }
    if constexpr (factor >= 4) {
        w |= w << (sizeof(SrcT) * 2 * 8);
    }
    if constexpr (factor >= 8) {
        w |= w << (sizeof(SrcT) * 4 * 8);
    }

    return w;
}

template <typename T, eif_uintegral_t<T>>
inline T interleave(T v) {
    if constexpr (sizeof(T) > 1) {
        using H = match_sign_t<precision_ut<max(int(sizeof(T) / 2), int(1))>, T>;

        H h1 = H(v >> sizeof(H) * 8), h2 = H(v);

        return (spread<H, T>(h1) << 1) | spread<H, T>(h2);
    }
    if constexpr (sizeof(T) == 1) {
        T h1(v >> 4), h2(v);

        h1 = ((h1 << 2) | h1) & T(0x33);
        h1 = ((h1 << 1) | h1) & T(0x55);
        h2 = ((h2 << 2) | h2) & T(0x33);
        h2 = ((h2 << 1) | h2) & T(0x55);

        return (h1 << 1) | h2;
    }
}

template <typename T, eif_uintegral_t<T>>
constexpr T rotateL(T v, int n) {
    return (v << n) | (v >> (sizeof(T) * 8 - n));
}

template <typename T, eif_uintegral_t<T>>
constexpr T rotateR(T v, int n) {
    return (v >> n) | (v << (sizeof(T) * 8 - n));
}

template <typename T, eif_uintegral_t<T>>
inline T scramble(T v) {
    if constexpr (sizeof(T) == 1) {
        return v;
    }

    if constexpr (sizeof(T) == 2) {
        u64 w(0);

        w |= spread<u08, u64>(u08(v)) << 0; v >>= 8;
        w |= spread<u08, u64>(u08(v)) << 4; v >>= 8;

        return u16(w >> 45) | u16(w >> 30) | u16(w >> 15) | u16(w);
    }

    if constexpr (sizeof(T) == 4) {
        u64 w(0);

        w |= spread<u08, u64>(u08(v)) << 0; v >>= 8;
        w |= spread<u08, u64>(u08(v)) << 2; v >>= 8;
        w |= spread<u08, u64>(u08(v)) << 4; v >>= 8;
        w |= spread<u08, u64>(u08(v)) << 6; v >>= 8;

        return u32(w >> 31) | u32(w);
    }

    if constexpr (sizeof(T) == 8) {
        u64 w(0);

        w |= spread<u08, u64>(u08(v)) << 0; v >>= 8;
        w |= spread<u08, u64>(u08(v)) << 1; v >>= 8;
        w |= spread<u08, u64>(u08(v)) << 2; v >>= 8;
        w |= spread<u08, u64>(u08(v)) << 3; v >>= 8;
        w |= spread<u08, u64>(u08(v)) << 4; v >>= 8;
        w |= spread<u08, u64>(u08(v)) << 5; v >>= 8;
        w |= spread<u08, u64>(u08(v)) << 6; v >>= 8;
        w |= spread<u08, u64>(u08(v)) << 7; v >>= 8;

        return w;
    }
}



}



}