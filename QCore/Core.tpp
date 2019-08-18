namespace qc {

template <typename T, typename>
Q_CONSTEX T min(T v1, T v2) {
    return v1 < v2 ? v1 : v2;
}

template <typename T1, typename T2, typename T3, typename... Ts>
Q_CONSTEX decltype(auto) min(T1 && v1, T2 && v2, T3 && v3, Ts &&... vs) {
    return min(forward<T1>(v1), min(forward<T2>(v2), forward<T3>(v3), forward<Ts>(vs)...));
}

template <typename T, typename>
Q_CONSTEX T max(T v1, T v2) {
    return v1 > v2 ? v1 : v2;
}

template <typename T1, typename T2, typename T3, typename... Ts>
Q_CONSTEX decltype(auto) max(T1 && v1, T2 && v2, T3 && v3, Ts &&... vs) {
    return max(forward<T1>(v1), max(forward<T2>(v2), forward<T3>(v3), forward<Ts>(vs)...));
}

template <typename T, typename>
inline T & minify(T & min, T v) {
    return (v < min) ? min = v : min;
}

template <typename T, typename T1, typename T2, typename... Ts>
inline T & minify(T & min, T1 && v1, T2 && v2, Ts &&... vs) {
    return minify(minify(min, forward<T1>(v1)), forward<T2>(v2), forward<Ts>(vs)...);
}

template <typename T, typename>
inline T & maxify(T & max, T v) {
    return (v > max) ? max = v : max;
}

template <typename T, typename T1, typename T2, typename... Ts>
inline T & maxify(T & min, T1 && v1, T2 && v2, Ts && ... vs) {
    return maxify(maxify(min, forward<T1>(v1)), forward<T2>(v2), forward<Ts>(vs)...);
}

}
