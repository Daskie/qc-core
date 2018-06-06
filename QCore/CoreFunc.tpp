namespace qc {



template <typename T>
Q_CX_ABLE T clamp(const T & v, const T & min, const T & max) {
    return qc::min(qc::max(v, min), max);
}

template <typename T, eif_arithmetic_t<T>>
Q_CX_ABLE T abs(T v) {
    if constexpr (std::is_unsigned_v<T>) {
        return v;
    }
    if constexpr (std::is_signed_v<T>) {
        return v < T(0) ? -v : v;
    }
}

template <typename T, eif_arithmetic_t<T>>
Q_CX_ABLE bool zero(T v, T e) {
    if constexpr (std::is_floating_point_v<T>) {
        return abs(v) < e;
    }
    if constexpr (std::is_integral_v<T>) {
        return v == T(0);
    }
}

template <typename T>
Q_CX_ABLE bool equal(const T & v1, const T & v2) {
    if constexpr (std::is_floating_point_v<T>) {
        return zero(v1 - v2);
    }
    if constexpr (!std::is_floating_point_v<T>) {
        return v1 == v2;
    }
}

template <typename T, typename... Ts>
Q_CX_ABLE bool equal(const T & v1, const T & v2, const Ts &... rest) {
    return equal(v1, v2) && equal(v2, rest...);
}

template <typename T, eif_floating_t<T>>
Q_CX_ABLE bool equalE(T v1, T v2, T e) {
    return zero(v1 - v2, e);
}

template <typename T, eif_arithmetic_t<T>>
Q_CX_ABLE T sign(T v) {
    if constexpr (std::is_signed_v<T>) {
        return static_cast<T>(T(0) < v) - static_cast<T>(v < T(0));
    }
    if constexpr (std::is_unsigned_v<T>) {
        return static_cast<T>(v > T(0));
    }
}

template <typename T, eif_floating_t<T>>
Q_CX_ABLE nat floor(T v) {
    nat i = nat(v);
    return i - (v < i);
}

template <typename T, eif_integral_t<T>>
Q_CX_ABLE T floor(T v) {
    return v;
}

template <typename T, eif_floating_t<T>>
Q_CX_ABLE nat ceil(T v) {
    nat i = nat(v);
    return i + (v > i);
}

template <typename T, eif_integral_t<T>>
Q_CX_ABLE T ceil(T v) {
    return v;
}

template <typename T>
Q_CONSTEX T pow2(int v) {
    return T(1) << v;
}

template <typename T, eif_integral_t<T>>
Q_CONSTEX bool isPow2(T v) {
    return (v & (v - 1)) == 0;
}

template <typename T, eif_integral_t<T>>
Q_CONSTEX int log2Floor(T v) {
    static_assert(sizeof(T) <= 8, "log2Floor function needs updated for larger integer types");

    int log(0);

    if constexpr (sizeof(T) >= 8) {
        if (v & 0xFFFFFFFF00000000ULL) { v >>= 32; log += 32; }
    }
    if constexpr (sizeof(T) >= 4) {
        if (v & 0x00000000FFFF0000ULL) { v >>= 16; log += 16; }
    }
    if constexpr (sizeof(T) >= 2) {
        if (v & 0x000000000000FF00ULL) { v >>=  8; log +=  8; }
    }
    if (    v & 0x00000000000000F0ULL) { v >>=  4; log +=  4; }
    if (    v & 0x000000000000000CULL) { v >>=  2; log +=  2; }
    if (    v & 0x0000000000000002ULL) {           log +=  1; }

    return log;
}

template <typename T, eif_integral_t<T>>
Q_CONSTEX int log2Ceil(T v) {
    return log2Floor(2 * v - 1);
}

template <typename T, eif_integral_t<T>>
Q_CX_ABLE T floor2(T v) {
    return T(1) << log2Floor(v);
}

template <typename T, eif_integral_t<T>>
Q_CX_ABLE T ceil2(T v) {
    return T(1) << log2Ceil(v);
}

template <typename T, eif_integral_t<T>>
Q_CX_ABLE T mipmaps(T size) {
    return log2Floor(size) + 1;
}

template <typename T, eif_integral_t<T>>
Q_CX_ABLE T highBit(T v) {
    using UT = std::make_unsigned_t<T>;
    constexpr UT mask(UT(1) << (sizeof(T) * 8 - 1));

    return T(v & mask);
}

template <typename T, eif_integral_t<T>>
Q_CX_ABLE T lowBit(T v) {
    return v & T(1);
}

template <typename T, eif_integral_t<T>>
Q_CX_ABLE T iBit(T v, int i) {
    using UT = std::make_unsigned_t<T>;
    constexpr UT mask(UT(1) << i);

    return T(v & mask);
}

template <typename T, eif_floating_t<T>>
Q_CX_ABLE T fract(T v) {
    return v - nat(v);
}

template <typename T, eif_floating_t<T>>
Q_CX_ABLE std::pair<T, nat> fract_i(T v) {
    nat i = nat(v);
    return { v - i, i };
}

template <typename T, eif_arithmetic_t<T>>
Q_CX_ABLE T mod(T v, T d) {
    if constexpr (std::is_floating_point_v<T>) {
        return fract(v / d) * d;
    }
    if constexpr (std::is_integral_v<T>) {
        return v % d;
    }
}

template <typename T, eif_arithmetic_t<T>>
Q_CX_ABLE std::pair<T, T> mod_q(T v, T d) {
    if constexpr (std::is_floating_point_v<T>) {
        T q(v / d);
        return { fract(q) * d, q };
    }
    if constexpr (std::is_integral_v<T>) {
        d = abs(d);
        T q(v / d);
        return { v - q * d, q };
    }
}

template <typename T, eif_floating_t<T>>
Q_CX_ABLE T mix(T v1, T v2, T t) {
    return (T(1.0) - t) * v1 + t * v2;
}

template <typename T, typename... Args>
Q_CONSTEX T sum(const T & v, const Args &... args) {
    if constexpr (sizeof...(Args) == 0) {
        return v;
    }
    if constexpr (sizeof...(Args) > 0) {
        return v + sum(args...);
    }
}

template <typename T, typename... Args>
Q_CONSTEX T product(const T & v, const Args &... args) {
    if constexpr (sizeof...(Args) == 0) {
        return v;
    }
    if constexpr (sizeof...(Args) > 0) {
        return v * product(args...);
    }
}

template <typename T, eif_floating_t<T>, typename... Args>
Q_CX_ABLE T average(T v, Args... args) {
    return sum(v, args...) / (T(1) + sizeof...(Args));
}

template <typename T, eif_floating_t<T>>
Q_CX_ABLE T radians(T degrees) {
    return degrees * pi<T> / T(180.0);
}

template <typename T, eif_floating_t<T>>
Q_CX_ABLE T degrees(T radians) {
    return radians * T(180.0) / pi<T>;
}

template <typename To, typename From, eif_t<std::is_arithmetic_v<To> && std::is_arithmetic_v<From>>>
Q_CONSTEX To transnorm(From v) {
    if constexpr (std::is_same_v<From, To>) {
        return v;
    }
    // float -> float
    if constexpr (std::is_floating_point_v<To> && std::is_floating_point_v<From>) {
        return To(v);
    }
    if constexpr (std::is_integral_v<From> && std::is_integral_v<To>) {
        // signed int -> signed int / unsigned int -> unsigned int
        if constexpr (std::is_signed_v<From> == std::is_signed_v<To>) {
            if constexpr (sizeof(From) > sizeof(To)) {
                return To(v >> ((sizeof(From) - sizeof(To)) * 8));
            }
            if constexpr (sizeof(From) < sizeof(To)) {
                if (v == std::numeric_limits<From>::max()) return std::numeric_limits<To>::max();
                return To(v) << ((sizeof(To) - sizeof(From)) * 8);
            }
        }
        // signed int -> unsigned int
        if constexpr (std::is_signed_v<From>) {
            if constexpr (sizeof(From) == sizeof(To)) {
                if (v <= From(0)) return To(0);
                if (v == std::numeric_limits<From>::max()) return std::numeric_limits<To>::max();
                return To(v << 1);
            }
            if constexpr (sizeof(From) > sizeof(To)) {
                if (v <= From(0)) return To(0);
                return To(v >> ((sizeof(From) - sizeof(To)) * 8 - 1));
            }
            if constexpr (sizeof(From) < sizeof(To)) {
                if (v <= From(0)) return To(0);
                if (v == std::numeric_limits<From>::max()) return std::numeric_limits<To>::max();
                return To(v) << ((sizeof(To) - sizeof(From)) * 8 + 1);
            }
        }
        // unsigned int -> signed int
        if constexpr (std::is_unsigned_v<From>) {
            if constexpr (sizeof(From) == sizeof(To)) {
                return To(v >> 1);
            }
            if constexpr (sizeof(From) > sizeof(To)) {
                return To(v >> ((sizeof(From) - sizeof(To)) * 8 + 1));
            }
            if constexpr (sizeof(From) < sizeof(To)) {
                if (v == std::numeric_limits<From>::max()) return std::numeric_limits<To>::max();
                return To(v) << ((sizeof(To) - sizeof(From)) * 8 - 1);
            }
        }
    }
    if constexpr (std::is_floating_point_v<From> && std::is_integral_v<To>) {
        // float -> signed int
        if constexpr (std::is_signed_v<To>) {
            constexpr From maxVal(From(std::numeric_limits<To>::max()) + From(1.0));
            constexpr From upperThreshold(From(1.0) - From(1.0) / maxVal);
            if (v >=  upperThreshold) return std::numeric_limits<To>::max();
            if (v <= -upperThreshold) return std::numeric_limits<To>::min();
            return To(v * maxVal);
        }
        // float -> unsigned int
        if constexpr (std::is_unsigned_v<To>) {
            constexpr From maxVal(From(std::numeric_limits<To>::max()) + From(1.0));
            constexpr From upperThreshold(From(1.0) - From(1.0) / maxVal);
            if (v < From(0.0)) return To(0);
            if (v >= upperThreshold) return std::numeric_limits<To>::max();
            return To(v * maxVal);
        }
    }
    if constexpr (std::is_integral_v<From> && std::is_floating_point_v<To>) {
        // signed int -> float
        if constexpr (std::is_signed_v<From>) {
            constexpr To maxVal(To(std::numeric_limits<From>::max()) + To(1.0));
            if (v == std::numeric_limits<From>::max()) return To(1.0);
            return To(v) * (To(1.0) / maxVal);
        }
        // unsigned int -> float
        if constexpr (std::is_unsigned_v<From>) {
            constexpr To maxVal(To(std::numeric_limits<From>::max()) + To(1.0));
            if (v == std::numeric_limits<From>::max()) return To(1.0);
            return To(v) * (To(1.0) / maxVal);
        }
    }
}



}