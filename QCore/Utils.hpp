#pragma once

#include <memory>
#include <fstream>
#include <codecvt>
#include <string>
#include <sstream>
#include <iomanip>
#include <filesystem>

#include "Core.hpp"

namespace qc {

template <typename T>
T pairwiseSum(unat n, const T * vals) {
    if (n == 0u) return T(0);
    if (n == 1u) return vals[0];
    if (n == 2u) return vals[0] + vals[1];
    return pairwiseSum(n >> 1, vals) + pairwiseSum((n + 1u) >> 1, vals + (n >> 1));
}

namespace detail {
    constexpr uchar trail_table[256]{
     // -0  -1  -2  -3  -4  -5  -6  -7  -8  -9  -A  -B  -C  -D  -E  -F
        8u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, // 0-
        4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, // 1-
        5u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, // 2-
        4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, // 3-
        6u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, // 4-
        4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, // 5-
        5u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, // 6-
        4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, // 7-
        7u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, // 8-
        4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, // 9-
        5u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, // A-
        4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, // B-
        6u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, // C-
        4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, // D-
        5u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, // E-
        4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, // F-
    };
}

template <typename T, typename = eif_uintegral_t<T>>
inline int trailingZeroes(T v) {
    int count(detail::trail_table[v & 0xFF]);
    for (int i(1); i < sizeof(T); ++i) {
        if (count < 8 * i) {
            return count;
        }
        v >>= 8;
        count += detail::trail_table[v & 0xFF];
    }
    return count;
}

// Will throw `std::system_error` on failure
inline pair<std::unique_ptr<std::byte[]>, size_t> readFile(const std::filesystem::path & path) {
    pair<std::unique_ptr<std::byte[]>, size_t> result;
    result.second = std::filesystem::file_size(path);
    result.first = std::make_unique<std::byte[]>(result.second);
    std::ifstream ifs(path, std::ios::in | std::ios::binary);
    ifs.exceptions(std::ios::badbit | std::ios::failbit);
    ifs.read(reinterpret_cast<char *>(result.first.get()), result.second);
    return move(result);
}

// Will throw `std::system_error` on failure
inline void writeFile(const std::filesystem::path & path, const void * data, size_t size) {
    std::ofstream ofs(path, std::ios::out | std::ios::binary);
    ofs.exceptions(std::ios::badbit | std::ios::failbit);
    ofs.write(reinterpret_cast<const char *>(data), size);
}

inline std::string timeString(double seconds) {
    static const double k_secondsPerDay(86400.0);
    static const double k_secondsPerHour(3600.0);
    static const double k_secondsPerMinute(60.0);
    
    seconds = std::floor(seconds);
    double days(std::floor(seconds / k_secondsPerDay)); seconds -= days * k_secondsPerDay;
    double hours(std::floor(seconds / k_secondsPerHour)); seconds -= hours * k_secondsPerHour;
    double minutes(std::floor(seconds / k_secondsPerMinute)); seconds -= minutes * k_secondsPerMinute;

    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << int(days) << ":";
    ss << std::setw(2) << std::setfill('0') << int(hours) << ":";
    ss << std::setw(2) << std::setfill('0') << int(minutes) << ":";
    ss << std::setw(2) << std::setfill('0') << int(seconds);

    return ss.str();
}

namespace print {

namespace detail {

template <typename T>
struct binary_s {

    u08 data[sizeof(T)];
    int blockSize;

    binary_s(const T & v, int blockSize) :
        blockSize(blockSize)
    {
        std::memcpy(data, &v, sizeof(T));
    }

    friend std::ostream & operator<<(std::ostream & os, const binary_s & b) {
        int nBlocks(sizeof(T) / b.blockSize);

        for (int blockI(0); blockI < nBlocks; ++blockI) {
            for (int byteI(b.blockSize - 1); byteI >= 0; --byteI) {
                u08 byte(b.data[blockI * b.blockSize + byteI]);
                for (int bitI(0); bitI < 8; ++bitI) {
                    os << ((byte & 0b10000000) ? "1" : "0");
                    byte <<= 1;
                }
            }
            if (blockI != nBlocks - 1) os << " ";
        }

        return os;
    }

};

}

template <typename T>
detail::binary_s<T> binary(const T & v, int blockSize = sizeof(T)) {
    return detail::binary_s<T>(v, blockSize);
}

struct repeat {

    std::string s;
    int n;

    repeat(const std::string & s, int n) : s(s), n(n) {}

    friend std::ostream & operator<<(std::ostream & os, const repeat & r) {
        for (int i(0); i < r.n; ++i) {
            os << r.s;
        }
        return os;
    }

};

struct line {

    int n;

    line(int n) : n(n) {}

    friend std::ostream & operator<<(std::ostream & os, const line & l) {
        return os << repeat("-", l.n);
    }

};

}

}
