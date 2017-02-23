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

#include "QMath.hpp"



namespace qmu {

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
constexpr const T & min(const T & a, const T & b) {
	return a < b ? a : b;
}

template <typename T>
constexpr const T & max(const T & a, const T & b) {
	return a > b ? a : b;
}

template <typename T, typename... Ts>
constexpr const T & min(const T & a, const T & b, const Ts & ... rest) {
	return min(a < b ? a : b, rest...);
}

template <typename T, typename... Ts>
constexpr const T & max(const T & a, const T & b, const Ts & ... rest) {
	return max(a > b ? a : b, rest...);
}

template <typename T>
constexpr const T & clamp(const T & v, const T & min, const T & max) {
	return v < min ? min : (v > max ? max : v);
}

template <typename T>
inline std::unique_ptr<T[]> make_unique_init(nat size, const T & val) {
	std::unique_ptr<T[]> arr = std::make_unique<T[]>(size);
	for (nat i(0); i < size; ++i) {
		arr[i] = val;
	}
	return std::move(arr);
}

template <typename T>
inline void fill(T * arr, nat n, const T & val) {
	for (nat i(0); i < n; ++i) {
		arr[i] = val;
	}
}

template <typename T>
inline void copy(const T * src, T * dest, nat n) {
	memcpy(dest, src, n * sizeof(T));
}

template <typename T>
inline void copy(const T * src, T * dest, nat n, nat offset, nat stride, nat grouping) {
	if (stride <= grouping) {
		memcpy(dest + offset, src, n * sizeof(T));
		return;
	}

	nat i = 0, j, k = offset;
	while (i < n) {
		for (j = 0; j < grouping; ++j, ++i) {
			dest[k + j] = src[i];
		}

		k += stride;
	}
}

inline bool fileExists(const std::string & path) {
	struct stat buffer;
	return stat(path.c_str(), &buffer) == 0;
}

inline nat detFileSize(std::ifstream & ifs) {
	nat initpos = (nat)ifs.tellg();
	ifs.seekg(0, std::ios::end);
	nat size = (nat)ifs.tellg();
	ifs.seekg(0, static_cast<int>(initpos));
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

inline float rand(float min, float max) {
	static std::mt19937 mt(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
	static std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	return dist(mt) * (max - min) + min;
}

constexpr unsigned char toByte(float x) {
	return static_cast<unsigned char>((x < 0.0f ? 0.0f : (x > 1.0f ? 1.0f : x)) * 255.0f);
}

constexpr unsigned char toByte(double x) {
	return static_cast<unsigned char>((x < 0.0 ? 0.0 : (x > 1.0 ? 1.0 : x)) * 255.0);
}

//generates n random values between min and 1, the sum of which equals 1
//if min * n > 1, min will be scaled down so that min * n == 1
inline void randomDistribution(nat n, float * dest, float min) {
	if (min * n > 1.0f) {
		min = 1.0f / n;
	}
	float total = 0.0f;
	float excess = max(1.0f - n * min, 0.0f);
	for (nat i(0); i < n; ++i) {
		dest[i] = rand(0.0f, 1.0f);
		total += dest[i];
	}
	for (nat i(0); i < n; ++i) {
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
		nat n = nat((sqrt(1 + 8 * i) - 1) / 2);
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
	const std::unique_ptr<T[]> map_;

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
		nat * toInc1, * toDec1, * toInc2 *toDec2;
		switch (s1) {
			case AB: a1 = size; b1 = 0; c1 = 0; toInc1 = &b1; toDec1 = &a1; break;
			case BC: a1 = 0; b1 = size; c1 = 0; toInc1 = &c1; toDec1 = &b1; break;
			case CA: a1 = 0; b1 = 0; c1 = size; toInc1 = &a1; toDec1 = &c1; break;
		}
		switch (s2) {
			case AB: a1 = 0; b1 = size; c1 = 0; toInc2 = &a2; toDec2 = &b2; break;
			case BC: a1 = 0; b1 = 0; c1 = size; toInc2 = &b2; toDec2 = &c2; break;
			case CA: a1 = size; b1 = 0; c1 = 0; toInc2 = &c2; toDec2 = &a2; break;
		}
		for (nat i(0); i <= size; ++i) {
			tris_[i1].at(a1, b1, c1) = tris_[i2].at(a2, b2, c2);
			++toInc1; --toDec1;
			++toInc2; --toDec2;
		}
	}

	private:

	nat size_;
	std::unique_ptr<TriGrid<T>[]> tris_;
};

//selection sort
template <typename T>
inline void sortAsc(T * arr, nat n) {
	nat min_i;
	T temp;
	for (nat i(0); i < n - 1; ++i) {
		min_i = i;
		for (nat j(i + 1); j < n; ++j) {
			if (arr[j] < arr[min_i]) {
				min_i = j;
			}
		}
		if (min_i != i) {
			temp = arr[i];
			arr[i] = arr[min_i];
			arr[min_i] = temp;
		}
	}
}

//selection sort
template <typename T>
inline void sortDesc(T * arr, nat n) {
	nat max_i;
	T temp;
	for (nat i(0); i < n - 1; ++i) {
		max_i = i;
		for (nat j(i + 1); j < n; ++j) {
			if (arr[j] > arr[max_i]) {
				max_i = j;
			}
		}
		if (max_i != i) {
			temp = arr[i];
			arr[i] = arr[max_i];
			arr[max_i] = temp;
		}
	}
}

inline bool is0(float v) {
	return abs(v) < std::numeric_limits<float>::min();
}

inline bool is0(double v) {
	return abs(v) < std::numeric_limits<double>::min();
}

template <typename T1, typename T2>
using sign_match_t = std::conditional_t<std::is_signed<T2>::value, std::make_signed_t<T1>, std::make_unsigned_t<T1>>;

template <typename T, std::enable_if_t<std::is_integral<T>::value && sizeof(T) == 1, int> = 0>
inline sign_match_t<nat, T> log2(T x) {
	sign_match_t<nat, T> log(0);
	if (x & 0xF0) { x >>=  4; log +=  4; }
	if (x & 0x0C) { x >>=  2; log +=  2; }
	if (x & 0x02) {			  log +=  1; }
	return log;
}

template <typename T, std::enable_if_t<std::is_integral<T>::value && sizeof(T) == 2, int> = 0>
inline sign_match_t<nat, T> log2(T x) {
	sign_match_t<nat, T> log(0);
	if (x & 0xFF00) { x >>=  8; log +=  8; }
	if (x & 0x00F0) { x >>=  4; log +=  4; }
	if (x & 0x000C) { x >>=  2; log +=  2; }
	if (x & 0x0002) {			log +=  1; }
	return log;
}

template <typename T, std::enable_if_t<std::is_integral<T>::value && sizeof(T) == 4, int> = 0>
inline sign_match_t<nat, T> log2(T x) {
	sign_match_t<nat, T> log(0);
	if (x & 0xFFFF0000) { x >>= 16; log += 16; }
	if (x & 0x0000FF00) { x >>=  8; log +=  8; }
	if (x & 0x000000F0) { x >>=  4; log +=  4; }
	if (x & 0x0000000C) { x >>=  2; log +=  2; }
	if (x & 0x00000002) {			log +=  1; }
	return log;
}

template <typename T, std::enable_if_t<std::is_integral<T>::value && sizeof(T) == 8, int> = 0>
inline sign_match_t<nat, T> log2(T x) {
	sign_match_t<nat, T> log(0);
	if (x & 0xFFFFFFFF00000000) { x >>= 32; log += 32; }
	if (x & 0x00000000FFFF0000) { x >>= 16; log += 16; }
	if (x & 0x000000000000FF00) { x >>=  8; log +=  8; }
	if (x & 0x00000000000000F0) { x >>=  4; log +=  4; }
	if (x & 0x000000000000000C) { x >>=  2; log +=  2; }
	if (x & 0x0000000000000002) {			log +=  1; }
	return log;
}

inline float log2(float v) {
	return std::log2f(v);
}

inline double log2(double v) {
	return std::log2(v);
}

template <typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
constexpr bool isPow2(T v) {
	return (v & (v - 1)) == 0;
}

template <typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
inline T floor2(T v) {
	if (v == 0) return 0;
	return 1LL << log2(v);
}

template <typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
inline T ceil2(T v) {
	if (v == 0) return 0;
	return floor2(v * 2 - 1);
}


inline std::string convert(const std::wstring & wstr) {
	static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	return converter.to_bytes(wstr);
}

inline std::wstring convert(const std::string & str) {
	static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	return converter.from_bytes(str);
}

constexpr float avgCol(const fvec4 & color) {
	return (color.r + color.g + color.b) / 3.0f;
}

inline fvec3 rgb2hsl(const fvec3 & color) {
	float rgb[3]{ color.r, color.g, color.b };
	fvec3 hsl(0.0f, 0.0f, 0.0f);

	nat minI = color.r < color.g ? 0 : 1;
	if (color.b < rgb[minI]) minI = 2;
	nat maxI = color.r > color.g ? 0 : 1;
	if (color.b > rgb[maxI]) maxI = 2;

	//lightness
	hsl.z = (rgb[minI] + rgb[maxI]) / 2.0f;

	//saturation
	if (hsl.z > 0.0f && hsl.z < 1.0f) {
		if (hsl.z > 0.5f) {
			hsl.y = (rgb[maxI] - rgb[minI]) / (2.0f - rgb[maxI] - rgb[minI]);
		}
		else {
			hsl.y = (rgb[maxI] - rgb[minI]) / (rgb[maxI] + rgb[minI]);
		}

		//hue
		if (hsl.y > 0.0f) {
			hsl.x = maxI / 3.0f;
			hsl.x += (rgb[(maxI + 1) % 3] - rgb[((maxI + 2) % 3)]) / (rgb[maxI] - rgb[minI]) * (1.0f / 6.0f);
			hsl.x += 1.0f;
			hsl.x -= (nat)hsl.x;
		}
	}

	return hsl;
}

inline fvec3 hsl2rgb(const fvec3 & color) {
	if (color.y == 0) {
		return fvec3(color.z, color.z, color.z);
	}

	float rgb[3]{ 0.0f, 0.0f, 0.0f };
	float temp;

	//process hue
	temp = round(color.x * 3.0f);
	nat maxI = (nat)temp % 3;
	rgb[maxI] = 1.0f;
	float secondaryWeight = (color.x * 3.0f - temp) * 2.0f;
	if (secondaryWeight != 0) {
		nat midI = (maxI + nat(secondaryWeight > 0 ? ceil(secondaryWeight) : floor(secondaryWeight)) + 3) % 3;
		rgb[midI] = abs(secondaryWeight);
	}

	//process saturation
	temp = 1.0f - color.y;
	rgb[0] += (0.5f - rgb[0]) * temp;
	rgb[1] += (0.5f - rgb[1]) * temp;
	rgb[2] += (0.5f - rgb[2]) * temp;

	//process lightness
	temp = (color.z - 0.5f) * 2.0f;
	if (color.z > 0.5f) {
		rgb[0] += (1.0f - rgb[0]) * temp;
		rgb[1] += (1.0f - rgb[1]) * temp;
		rgb[2] += (1.0f - rgb[2]) * temp;
	}
	else {
		rgb[0] += rgb[0] * temp;
		rgb[1] += rgb[1] * temp;
		rgb[2] += rgb[2] * temp;
	}

	return fvec3(rgb[0], rgb[1], rgb[2]);
}

inline bool readTextFile(const std::string & filepath, std::string & str_dst) {
	std::ifstream ifs(filepath);
	if (!ifs.good()) {
		return false;
	}

	std::stringstream ss;
	ss << ifs.rdbuf();
	ifs.close();
	str_dst = ss.str();

	return true;
}

}