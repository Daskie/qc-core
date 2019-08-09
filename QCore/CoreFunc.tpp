namespace qc {

template <typename T, typename>
Q_CX_ABLE duo<T> minmax(T a) {
    return {a, a};
}

template <typename T, typename>
Q_CX_ABLE duo<T> minmax(T a, T b) {
    return (a < b) ? duo<T>{ a, b } : duo<T>{b, a};
}

template <typename T, typename... Ts, typename>
Q_CX_ABLE duo<T> minmax(T a, T b, Ts... rest) {
    auto [m1, M1](minmax(a, b));
    auto [m2, M2](minmax(rest...));
    return {min(m1, m2), max(M1, M2)};
}

template <typename T, typename>
Q_CX_ABLE T median(T a, T b, T c) {
    if (a > b) std::swap(a, b);
    if (b > c) std::swap(b, c);
    return max(a, b);
}

template <typename T>
Q_CX_ABLE T clamp(const T & v, const T & min, const T & max) {
    return qc::min(qc::max(v, min), max);
}

template <typename T, typename>
Q_CX_ABLE T abs(T v) {
    if constexpr (is_unsigned_v<T>) {
        return v;
    }
    if constexpr (is_signed_v<T>) {
        return v < 0 ? -v : v;
    }
}

template <typename T, typename>
Q_CX_ABLE bool zero(T v, T e) {
    if constexpr (is_floating_point_v<T>) {
        return abs(v) < e;
    }
    if constexpr (is_integral_v<T>) {
        return v == T(0);
    }
}

template <typename T>
Q_CX_ABLE bool equal(const T & v1, const T & v2) {
    if constexpr (is_floating_point_v<T>) {
        return zero(v1 - v2);
    }
    if constexpr (!is_floating_point_v<T>) {
        return v1 == v2;
    }
}

template <typename T, typename... Ts>
Q_CX_ABLE bool equal(const T & v1, const T & v2, const Ts &... rest) {
    return equal(v1, v2) && equal(v2, rest...);
}

template <typename T, typename>
Q_CX_ABLE bool equal_e(T v1, T v2, T e) {
    return zero(v1 - v2, e);
}

template <typename T, typename>
Q_CX_ABLE T sign(T v) {
    if constexpr (is_signed_v<T>) {
        return static_cast<T>(0 < v) - static_cast<T>(v < 0);
    }
    if constexpr (is_unsigned_v<T>) {
        return static_cast<T>(v > 0u);
    }
}

template <typename T, typename>
Q_CX_ABLE nat floor(T v) {
    nat i = nat(v);
    return i - (v < i);
}

template <typename T, typename>
Q_CX_ABLE T floor(T v) {
    return v;
}

template <typename T, typename>
Q_CX_ABLE nat ceil(T v) {
    nat i = nat(v);
    return i + (v > i);
}

template <typename T, typename>
Q_CX_ABLE T ceil(T v) {
    return v;
}

template <typename T, typename>
Q_CX_ABLE T pow(T v, int e) {
    if (e >= 0) {
        return pow(v, uint(e));
    }
    else {
        return pow(T(1.0) / v, uint(-e));
    }
}

template <typename T, typename>
Q_CX_ABLE T pow(T v, uint e) {
    T r(T(1.0));

    do {
        if (e & 1u) r *= v; // exponent is odd
        e >>= 1;
        v *= v;
    } while (e);

    return r;
}

template <typename T, typename>
Q_CONSTEX T pow2(int v) {
    return T(1) << v;
}

template <typename T, typename>
Q_CONSTEX bool isPow2(T v) {
    return !(v & (v - T(1)));
}

template <typename T, typename>
Q_CONSTEX int log2Floor(T v) {
    static_assert(sizeof(T) <= 8u);

    int log(0);
    if constexpr (sizeof(T) >= 8u) if (v & 0xFFFFFFFF00000000) { v >>= 32; log += 32; }
    if constexpr (sizeof(T) >= 4u) if (v & 0x00000000FFFF0000) { v >>= 16; log += 16; }
    if constexpr (sizeof(T) >= 2u) if (v & 0x000000000000FF00) { v >>=  8; log +=  8; }
                                   if (v & 0x00000000000000F0) { v >>=  4; log +=  4; }
                                   if (v & 0x000000000000000C) { v >>=  2; log +=  2; }
                                   if (v & 0x0000000000000002) {           log +=  1; }
    return log;
}

template <typename T, typename>
Q_CONSTEX int log2Ceil(T v) {
    return (v & (v - T(1))) ? log2Floor(v - T(1)) + T(1) : log2Floor(v);
}

template <typename T, typename>
Q_CONSTEX T floor2(T v) {
    v = smear(v);
    return v ^ (v >> 1);
}

template <typename T, typename>
Q_CONSTEX T ceil2(T v) {
    return smear(v - T(1)) + T(1);
}

template <typename T, typename>
Q_CX_ABLE T mipmaps(T size) {
    return log2Floor(size) + T(1);
}

template <typename T, typename>
Q_CX_ABLE T highBit(T v) {
    using UT = std::make_unsigned_t<T>;
    constexpr UT mask(UT(1) << (sizeof(T) * 8u - 1u));

    return T(v & mask);
}

template <typename T, typename>
Q_CX_ABLE T lowBit(T v) {
    return v & T(1);
}

template <typename T, typename>
Q_CX_ABLE T iBit(T v, int i) {
    return v & (T(1) << i);
}

template <typename T, typename>
Q_CONSTEX T smear(T v) {
                                  v |= v >>  1;
                                  v |= v >>  2;
                                  v |= v >>  4;
    if constexpr (sizeof(T) >= 2u) v |= v >>  8;
    if constexpr (sizeof(T) >= 4u) v |= v >> 16;
    if constexpr (sizeof(T) >= 8u) v |= v >> 32;
    return v;
}

template <typename T, typename>
Q_CX_ABLE T fract(T v) {
    return v - nat(v);
}

template <typename T, typename>
Q_CX_ABLE pair<T, nat> fract_i(T v) {
    nat i = nat(v);
    return { v - i, i };
}

template <typename T, typename>
Q_CX_ABLE T mod(T v, T d) {
    if constexpr (is_floating_point_v<T>) {
        return fract(v / d) * d;
    }
    if constexpr (is_integral_v<T>) {
        return v % d;
    }
}

template <typename T, typename>
Q_CX_ABLE duo<T> mod_q(T v, T d) {
    if constexpr (is_floating_point_v<T>) {
        T q(v / d);
        return { fract(q) * d, q };
    }
    if constexpr (is_integral_v<T>) {
        d = abs(d);
        T q(v / d);
        return { v - q * d, q };
    }
}

template <typename T, typename>
Q_CX_ABLE T mix(T v1, T v2, T t) {
    return (T(1.0) - t) * v1 + t * v2;
}

template <typename T, typename... Args>
Q_CONSTEX T sum(const T & v, const Args &... args) {
    if constexpr (sizeof...(Args) == 0) {
        return v;
    }
    else {
        return v + sum(args...);
    }
}

template <typename T, typename... Args>
Q_CONSTEX T product(const T & v, const Args &... args) {
    if constexpr (sizeof...(Args) == 0) {
        return v;
    }
    else {
        return v * product(args...);
    }
}

template <typename T, typename, typename... Args>
Q_CX_ABLE T average(T v, Args... args) {
    return sum(v, args...) / T(sizeof...(Args) + 1u);
}

template <typename T, typename>
Q_CX_ABLE T radians(T degrees) {
    static constexpr T k_factor(pi<T> / T(180.0));
    return degrees * k_factor;
}

template <typename T, typename>
Q_CX_ABLE T degrees(T radians) {
    static constexpr T k_factor(T(180.0) / pi<T>);
    return radians * k_factor;
}

template <typename To, typename From, typename>
Q_CONSTEX To transnorm(From v) {
    if constexpr (is_same_v<From, To>) {
        return v;
    }
    // float -> float
    if constexpr (is_floating_point_v<To> && is_floating_point_v<From>) {
        return To(v);
    }
    if constexpr (is_integral_v<From> && is_integral_v<To>) {
        // signed int -> signed int / unsigned int -> unsigned int
        if constexpr (is_signed_v<From> == is_signed_v<To>) {
            if constexpr (sizeof(From) > sizeof(To)) {
                return To(v >> ((sizeof(From) - sizeof(To)) * 8u));
            }
            if constexpr (sizeof(From) < sizeof(To)) {
                if (v == std::numeric_limits<From>::max()) return std::numeric_limits<To>::max();
                return To(v) << ((sizeof(To) - sizeof(From)) * 8u);
            }
        }
        // signed int -> unsigned int
        if constexpr (is_signed_v<From>) {
            if constexpr (sizeof(From) == sizeof(To)) {
                if (v <= 0) return 0u;
                if (v == std::numeric_limits<From>::max()) return std::numeric_limits<To>::max();
                return To(v << 1);
            }
            if constexpr (sizeof(From) > sizeof(To)) {
                if (v <= 0) return 0u;
                return To(v >> ((sizeof(From) - sizeof(To)) * 8u - 1u));
            }
            if constexpr (sizeof(From) < sizeof(To)) {
                if (v <= 0) return 0u;
                if (v == std::numeric_limits<From>::max()) return std::numeric_limits<To>::max();
                return To(v) << ((sizeof(To) - sizeof(From)) * 8u + 1u);
            }
        }
        // unsigned int -> signed int
        if constexpr (is_unsigned_v<From>) {
            if constexpr (sizeof(From) == sizeof(To)) {
                return To(v >> 1);
            }
            if constexpr (sizeof(From) > sizeof(To)) {
                return To(v >> ((sizeof(From) - sizeof(To)) * 8u + 1u));
            }
            if constexpr (sizeof(From) < sizeof(To)) {
                if (v == std::numeric_limits<From>::max()) return std::numeric_limits<To>::max();
                return To(v) << ((sizeof(To) - sizeof(From)) * 8u - 1u);
            }
        }
    }
    if constexpr (is_floating_point_v<From> && is_integral_v<To>) {
        // float -> signed int
        if constexpr (is_signed_v<To>) {
            constexpr From maxVal(From(std::numeric_limits<To>::max()) + From(1.0));
            constexpr From upperThreshold(From(1.0) - From(1.0) / maxVal);
            if (v >=  upperThreshold) return std::numeric_limits<To>::max();
            if (v <= -upperThreshold) return std::numeric_limits<To>::min();
            return To(v * maxVal);
        }
        // float -> unsigned int
        if constexpr (is_unsigned_v<To>) {
            constexpr From maxVal(From(std::numeric_limits<To>::max()) + From(1.0));
            constexpr From upperThreshold(From(1.0) - From(1.0) / maxVal);
            if (v < From(0.0)) return 0u;
            if (v >= upperThreshold) return std::numeric_limits<To>::max();
            return To(v * maxVal);
        }
    }
    if constexpr (is_integral_v<From> && is_floating_point_v<To>) {
        // signed int -> float
        if constexpr (is_signed_v<From>) {
            constexpr To maxVal(To(std::numeric_limits<From>::max()) + To(1.0));
            if (v == std::numeric_limits<From>::max()) return To(1.0);
            return To(v) * (To(1.0) / maxVal);
        }
        // unsigned int -> float
        if constexpr (is_unsigned_v<From>) {
            constexpr To maxVal(To(std::numeric_limits<From>::max()) + To(1.0));
            if (v == std::numeric_limits<From>::max()) return To(1.0);
            return To(v) * (To(1.0) / maxVal);
        }
    }
}

}