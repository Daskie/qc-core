#pragma once



#include <memory>
#include <fstream>
#include <random>
#include <chrono>
#include <limits>
#include <locale>
#include <codecvt>
#include <string>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <filesystem>

#include "Math.hpp"



namespace qc {

// So what's the deal with all this fancy rvalue shit? Perfect forwarding.
//	(T &) &		=>	T&
//	(T &) &&	=>	T&
//	(T &&) &	=>	T&
//	(T &&) &&	=>	T&&
// so basically, along with std::forward, the return type is guaranteed to match
// the input type. So min(myObj1, myObj2) would be min(T &, T &) and would
// return T & or MyObj &. On the other hand, min(literal1, literal2) would be
// min(T &&, T &&) and would return T && or int &&.
// std::forward is the same as static_cast<T&&>(thing) and basically casts T to
// T &&, T & to T &, and T && to T&&. std::move, on the other hand, will cast
// anything/everything to T &&.
//
// the reason for using T && over const T & in the min/max functions is to allow
// the direct use of values, for example: min(myInt, 4) or min(Obj(x), Obj(y))
//
// the auto business is so you can use one lvalue and one rvalue argument

template <typename T>
inline std::unique_ptr<T []> make_unique_init(unat size, const T & val) {
    std::unique_ptr<T []> arr = std::make_unique<T []>(size);
    for (unat i(0); i < size; ++i) {
        arr[i] = val;
    }
    return std::move(arr);
}

template <typename T>
inline void fill(T * arr, unat n, const T & val) {
    for (unat i(0); i < n; ++i) {
        arr[i] = val;
    }
}

template <typename T>
inline void copy(const T * src, T * dest, unat n) {
    std::memcpy(dest, src, n * sizeof(T));
}

template <typename T>
inline void copy(const T * src, T * dest, unat n, unat offset, unat stride, unat grouping) {
    if (stride <= grouping) {
        std::memcpy(dest + offset, src, n * sizeof(T));
        return;
    }

    unat i(0), j, k(offset);
    while (i < n) {
        for (j = 0; j < grouping; ++j, ++i) {
            dest[k + j] = src[i];
        }

        k += stride;
    }
}

template <typename T>
T pairwiseSum(unat n, const T * vals) {
    if (n == 0) return T(0);
    if (n == 1) return vals[0];
    if (n == 2) return vals[0] + vals[1];
    return pairwiseSum(n / 2, vals) + pairwiseSum((n + 1) / 2, vals + n / 2);
}

template <typename T>
inline std::unique_ptr<T[]> duplicate(const T * src, unat n) {
    T * arr(reinterpret_cast<T *>(std::malloc(n * sizeof(T))));
    std::memcpy(arr, src, n * sizeof(T));
    return std::unique_ptr<T[]>(arr);
}

template <typename T>
inline std::unique_ptr<T[]> duplicate(const std::unique_ptr<T[]> & src, unat n) {
    return duplicate(src.get(), n);
}

inline bool fileExists(const std::string & path) {
    struct stat buffer;
    return stat(path.c_str(), &buffer) == 0;
}

inline unat detFileSize(std::ifstream & ifs) {
    ifs.seekg(0, std::ios::end);
    unat size(ifs.tellg());
    ifs.seekg(0);
    return size;
}

namespace {
const unsigned char trail_table[256]{
    //-0	-1	-2	-3	-4	-5	-6	-7	-8	-9	-A	-B	-C	-D	-E	-F
    8,	0,	1,	0,	2,	0,	1,	0,	3,	0,	1,	0,	2,	0,	1,	0,	//0-
    4,	0,	1,	0,	2,	0,	1,	0,	3,	0,	1,	0,	2,	0,	1,	0,	//1-
    5,	0,	1,	0,	2,	0,	1,	0,	3,	0,	1,	0,	2,	0,	1,	0,	//2-
    4,	0,	1,	0,	2,	0,	1,	0,	3,	0,	1,	0,	2,	0,	1,	0,	//3-
    6,	0,	1,	0,	2,	0,	1,	0,	3,	0,	1,	0,	2,	0,	1,	0,	//4-
    4,	0,	1,	0,	2,	0,	1,	0,	3,	0,	1,	0,	2,	0,	1,	0,	//5-
    5,	0,	1,	0,	2,	0,	1,	0,	3,	0,	1,	0,	2,	0,	1,	0,	//6-
    4,	0,	1,	0,	2,	0,	1,	0,	3,	0,	1,	0,	2,	0,	1,	0,	//7-
    7,	0,	1,	0,	2,	0,	1,	0,	3,	0,	1,	0,	2,	0,	1,	0,	//8-
    4,	0,	1,	0,	2,	0,	1,	0,	3,	0,	1,	0,	2,	0,	1,	0,	//9-
    5,	0,	1,	0,	2,	0,	1,	0,	3,	0,	1,	0,	2,	0,	1,	0,	//A-
    4,	0,	1,	0,	2,	0,	1,	0,	3,	0,	1,	0,	2,	0,	1,	0,	//B-
    6,	0,	1,	0,	2,	0,	1,	0,	3,	0,	1,	0,	2,	0,	1,	0,	//C-
    4,	0,	1,	0,	2,	0,	1,	0,	3,	0,	1,	0,	2,	0,	1,	0,	//D-
    5,	0,	1,	0,	2,	0,	1,	0,	3,	0,	1,	0,	2,	0,	1,	0,	//E-
    4,	0,	1,	0,	2,	0,	1,	0,	3,	0,	1,	0,	2,	0,	1,	0,	//F-
};
}

inline unsigned char trailingZeroes(u08 x) {
    return trail_table[x];
}

inline unsigned char trailingZeroes(u32 x) {
    unsigned char count = 0;
    count += trail_table[x & 0xFF];
    if (count < 8) {
        return count;
    }
    x >>= 8;
    count += trail_table[x & 0xFF];
    if (count < 16) {
        return count;
    }
    x >>= 8;
    count += trail_table[x & 0xFF];
    if (count < 24) {
        return count;
    }
    x >>= 8;
    count += trail_table[x & 0xFF];
    return count;
}


//inline std::string convert(const std::wstring & wstr) {
//    static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
//
//    return converter.to_bytes(wstr);
//}

//inline std::wstring convert(const std::string & str) {
//    static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
//
//    return converter.from_bytes(str);
//}

// Will throw `std::system_error` on failure
inline std::pair<std::unique_ptr<std::byte[]>, size_t> readFile(const std::filesystem::path & path) {
    std::pair<std::unique_ptr<std::byte[]>, size_t> result;
    result.second = std::filesystem::file_size(path);
    result.first = std::make_unique<std::byte[]>(result.second);
    std::ifstream ifs(path, std::ios::in | std::ios::binary);
    ifs.exceptions(std::ios::badbit | std::ios::failbit);
    ifs.read(reinterpret_cast<char *>(result.first.get()), result.second);
    return std::move(result);
}

// Will throw `std::system_error` on failure
inline void writeFile(const std::filesystem::path & path, const void * data, size_t size) {
    std::ofstream ofs(path, std::ios::out | std::ios::binary);
    ofs.exceptions(std::ios::badbit | std::ios::failbit);
    ofs.write(reinterpret_cast<const char *>(data), size);
}

inline std::vector<std::string> tokenize(const std::string & str) {
    std::vector<std::string> words;
    size_t startI(0);
    while (true) {
        while (startI < str.size() && std::isspace(str.at(startI))) ++startI;
        if (startI >= str.size()) break;
        size_t endI(startI + 1);
        while (endI < str.size() && !std::isspace(str.at(endI))) ++endI;
        words.emplace_back(str.substr(startI, endI - startI));
        startI = endI;
    }
    return std::move(words);
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