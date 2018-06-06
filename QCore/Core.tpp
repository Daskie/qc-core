namespace qc {



template <typename T>
Q_CONSTEX const T & min(const T & a, const T & b) {
    return a < b ? a : b;
}

template <typename T, typename... Ts>
Q_CONSTEX const T & min(const T & a, const T & b, const Ts &... rest) {
    return min(a < b ? a : b, rest...);
}

template <typename T>
Q_CONSTEX const T & max(const T & a, const T & b) {
    return a > b ? a : b;
}

template <typename T, typename... Ts>
Q_CONSTEX const T & max(const T & a, const T & b, const Ts &... rest) {
    return max(a > b ? a : b, rest...);
}

template <typename T>
Q_CONSTEX std::pair<const T &, const T &> minmax(const T & a) {
    return { a, a };
}

template <typename T>
Q_CONSTEX std::pair<const T &, const T &> minmax(const T & a, const T & b) {
    if (a < b) {
        return { a, b };
    }
    else {
        return { b, a };
    }
}

template <typename T>
Q_CONSTEX std::pair<const T &, const T &> minmax(const T & a, const T & b, const T & c) {
    auto mm(minmax(a, b)); // apparently can't use structed bindings in constexpr function
    return { min(mm.first, c), max(mm.second, c) };
}

template <typename T>
Q_CONSTEX std::pair<const T &, const T &> minmax(const T & a, const T & b, const T & c, const T & d) {
    auto mm1(minmax(a, b));
    auto mm2(minmax(c, d));
    return { min(mm1.first, mm2.first), max(mm1.second, mm2.second) };
}

template <typename T, typename... Ts>
Q_CONSTEX std::pair<const T &, const T &> minmax(const T & a, const T & b, const T & c, const T & d, const Ts &... rest) {
    auto mm1(minmax(a, b, c, d));
    auto mm2(minmax(rest...));
    return { min(mm1.first, mm2.first), max(mm1.second, mm2.second) };
}



}