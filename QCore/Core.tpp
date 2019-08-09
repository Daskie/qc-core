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

}
