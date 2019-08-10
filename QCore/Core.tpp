namespace qc {

template <typename T, typename>
Q_CONSTEX T min(T a, T b) {
    return a < b ? a : b;
}

template <typename T, typename... Ts, typename>
Q_CONSTEX T min(T a, T b, Ts... rest) {
    return min(a < b ? a : b, rest...);
}

template <typename T, typename>
Q_CONSTEX T max(T a, T b) {
    return a > b ? a : b;
}

template <typename T, typename... Ts, typename>
Q_CONSTEX T max(T a, T b, Ts... rest) {
    return max(a > b ? a : b, rest...);
}

template <typename T, typename>
inline T & minify(T & min, T v) {
    if (v < min) min = v;
    return min;
}

template <typename T, typename>
inline T & maxify(T & max, T v) {
    if (v > max) max = v;
    return max;
}

}
