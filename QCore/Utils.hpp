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

template <typename T, eif_arithmetic_t<T> = 0>
inline T rand() {
    static std::mt19937 mt(static_cast<std::mt19937::result_type>(std::chrono::system_clock::now().time_since_epoch().count()));
    //static std::mt19937 mt(0);

    if constexpr (std::is_floating_point_v<T>) {
        static std::uniform_real_distribution<T> dist(T(0.0), T(1.0));
        return dist(mt);
    }
    if constexpr (std::is_integral_v<T>) {
        static std::uniform_real_distribution<double> dist(0.0, 1.0);
        return T(std::round(dist(mt) * double(RAND_MAX)));
    }
}

template <typename T, eif_arithmetic_t<T> = 0>
inline T rand(T min, T max) {
    if constexpr (std::is_floating_point_v<T>) {
        return rand<T>() * (max - min) + min;
    }
    if constexpr (std::is_integral_v<T>) {
        return rand<T>() % (max - min + 1) + min;
    }
}

template <typename T, eif_arithmetic_t<T> = 0>
inline T randCheap() {
    if constexpr (std::is_floating_point_v<T>) {
        constexpr T inv_max(T(1.0) / T(RAND_MAX));
        return std::rand() * inv_max;
    }
    if constexpr (std::is_integral_v<T>) {
        return T(std::rand());
    }
}

template <typename T, eif_arithmetic_t<T> = 0>
inline T randCheap(T min, T max) {
    if constexpr (std::is_floating_point_v<T>) {
        return randCheap<T>() * (max - min) + min;
    }
    if constexpr (std::is_integral_v<T>) {
        return randCheap<T>() % (max - min + 1) + min;
    }
}

template <typename T, int t_n, eif_floating_t<T> = 0>
inline vec<T, t_n> randVec() {
    if constexpr (t_n == 1) {
        return vec1<T>(rand<T>());
    }
    if constexpr (t_n == 2) {
        return vec2<T>(rand<T>(), rand<T>());
    }
    if constexpr (t_n == 3) {
        return vec3<T>(rand<T>(), rand<T>(), rand<T>());
    }
    if constexpr (t_n == 4) {
        return vec4<T>(rand<T>(), rand<T>(), rand<T>(), rand<T>());
    }
}

template <typename T, int t_n, eif_arithmetic_t<T> = 0>
inline vec<T, t_n> randVec(T min, T max) {
    if constexpr (t_n == 1) {
        return vec1<T>(rand(min, max));
    }
    if constexpr (t_n == 2) {
        return vec2<T>(rand(min, max), rand(min, max));
    }
    if constexpr (t_n == 3) {
        return vec3<T>(rand(min, max), rand(min, max), rand(min, max));
    }
    if constexpr (t_n == 4) {
        return vec4<T>(rand(min, max), rand(min, max), rand(min, max), rand(min, max));
    }
}

constexpr unsigned char toByte(float x) {
    return unsigned char((x < 0.0f ? 0.0f : (x > 1.0f ? 1.0f : x)) * 255.0f);
}

constexpr unsigned char toByte(double x) {
    return unsigned char((x < 0.0 ? 0.0 : (x > 1.0 ? 1.0 : x)) * 255.0);
}

//generates n random values between min and 1, the sum of which equals 1
//if min * n > 1, min will be scaled down so that min * n == 1
inline void randomDistribution(unat n, float * dest, float min) {
    if (min * n > 1.0f) {
        min = 1.0f / n;
    }
    float total = 0.0f;
    float excess = max(1.0f - n * min, 0.0f);
    for (unat i(0); i < n; ++i) {
        dest[i] = rand(0.0f, 1.0f);
        total += dest[i];
    }
    for (unat i(0); i < n; ++i) {
        dest[i] = dest[i] / total * excess + min;
    }
}

template <typename T>
class TriGrid {

    public:

    TriGrid(nat size) :
        size_(size),
        mapSize_((size + 1) * (size + 2) / 2),
        map_(new T[mapSize_]) {
    }

    T & at(nat a, nat b, nat c) const {
        return map_[abc2i(a, b, c)];
    }

    nat abc2i(nat a, nat b, nat c) const {
        return (size_ - a) * (size_ - a + 1) / 2 + (size_ - a - b);
    }

    void i2abc(nat i, nat * a, nat * b, nat * c) const {
        nat n = nat((std::sqrt(1 + 8 * i) - 1) / 2);
        *a = size_ - n;
        *b = n - (i - n * (n + 1) / 2);
        *c = size_ - *a - *b;
    }

    T * map() const {
        return map_.get();
    }

    nat size() const {
        return size_;
    }

    nat mapSize() const {
        return mapSize_;
    }

    private:

    const nat size_;
    const nat mapSize_;
    const std::unique_ptr<T []> map_;

};

template <typename T>
class TriWeb {
    
    public:

    enum class Side { AB, BC, CA };

    TriWeb(nat nTris, nat size) :
        tris_(new TriGrid<T>[nTris]),
        size_(size)	{
    }

    TriGrid<T> & tri(nat i) {
        return tris_[i];
    }

    void bind(nat i1, Side s1, nat i2, Side s2) {
        TriGrid<T> & tg1 = tris_.at(i1);
        TriGrid<T> & tg2 = tris_.at(i2);

        nat a1, b1, c1, a2, b2, c2;
        nat * toInc1, * toDec1, * toInc2, * toDec2;
        switch (s1) {
            case AB : a1 = size; b1 = 0; c1 = 0; toInc1 = &b1; toDec1 = &a1; break;
            case BC : a1 = 0; b1 = size; c1 = 0; toInc1 = &c1; toDec1 = &b1; break;
            case CA : a1 = 0; b1 = 0; c1 = size; toInc1 = &a1; toDec1 = &c1; break;
        }
        switch (s2) {
            case AB : a1 = 0; b1 = size; c1 = 0; toInc2 = &a2; toDec2 = &b2; break;
            case BC : a1 = 0; b1 = 0; c1 = size; toInc2 = &b2; toDec2 = &c2; break;
            case CA : a1 = size; b1 = 0; c1 = 0; toInc2 = &c2; toDec2 = &a2; break;
        }
        for (nat i(0); i <= size; ++i) {
            tris_[i1].at(a1, b1, c1) = tris_[i2].at(a2, b2, c2);
            ++toInc1; --toDec1;
            ++toInc2; --toDec2;
        }
    }

    private:

    nat size_;
    std::unique_ptr<TriGrid<T> []> tris_;
};


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

template <typename T, eif_floating_t<T> = 0>
inline vec3<T> rgb2hsl(const vec3<T> & rgb) {
    vec3<T> hsl(0, 0, 0);

    int minI(rgb.r <= rgb.g ? 0 : 1);
    if (rgb.b < rgb[minI]) minI = 2;
    int maxI(rgb.r >= rgb.g ? 0 : 1);
    if (rgb.b > rgb[maxI]) maxI = 2;

    // lightness
    hsl.z = (rgb[minI] + rgb[maxI]) * T(0.5);

    if (hsl.z > 0 && hsl.z < T(1.0)) {
        // saturation
        if (hsl.z > T(0.5)) {
            hsl.y = (rgb[maxI] - rgb[minI]) / (T(2.0) - (hsl.z * T(2.0)));
        }
        else {
            hsl.y = (rgb[maxI] - rgb[minI]) / (hsl.z * T(2.0));
        }

        if (hsl.y > 0) {
            // hue
            hsl.x = maxI * T(1.0 / 3.0);
            hsl.x += (rgb[(maxI + 1) % 3] - rgb[((maxI + 2) % 3)]) / (rgb[maxI] - rgb[minI]) * T(1.0 / 6.0);
            hsl.x += T(1.0);
            hsl.x -= std::floor(hsl.x);
        }
    }

    return hsl;
}

template <typename T, eif_floating_t<T> = 0>
inline vec3<T> hsl2rgb(const vec3<T> & hsl) {
    if (hsl.y == 0) {
        return vec3<T>(hsl.z, hsl.z, hsl.z);
    }

    vec3<T> rgb(0, 0, 0);
    T temp;

    // hue
    temp = std::round(hsl.x * T(3.0));
    int maxI(int(temp) % 3);
    rgb[maxI] = T(1.0);
    T secondaryWeight((hsl.x * T(3.0) - temp) * T(2.0));
    int midI((maxI + int(secondaryWeight > 0 ? std::ceil(secondaryWeight) : std::floor(secondaryWeight)) + 3) % 3);
    rgb[midI] = abs(secondaryWeight);

    // saturation
    temp = T(1.0) - hsl.y;
    rgb.r += (T(0.5) - rgb.r) * temp;
    rgb.g += (T(0.5) - rgb.g) * temp;
    rgb.b += (T(0.5) - rgb.b) * temp;

    // lightness
    temp = (hsl.z - T(0.5)) * T(2.0);
    if (hsl.z > T(0.5)) {
        rgb.r += (T(1.0) - rgb.r) * temp;
        rgb.g += (T(1.0) - rgb.g) * temp;
        rgb.b += (T(1.0) - rgb.b) * temp;
    }
    else {
        rgb.r += rgb.r * temp;
        rgb.g += rgb.g * temp;
        rgb.b += rgb.b * temp;
    }

    return rgb;
}

inline std::pair<bool, std::string> readTextFile(const std::string & filepath) {
    std::ifstream ifs{filepath};
    if (!ifs.good()) {
        return {};
    }
    std::string str{
        std::istreambuf_iterator<char>{ifs},
        std::istreambuf_iterator<char>{}
    };
    if (!ifs.good()) {
        return {};
    }
    return {true, std::move(str)};
}

inline bool writeTextFile(const std::string & filepath, const std::string & str) {
    std::ofstream ofs{filepath};
    if (!ofs.good()) {
        return false;
    }
    ofs << str;
    return ofs.good();
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