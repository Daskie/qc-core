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

#include "Math.hpp"



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

template <typename T, std::enable_if_t<std::is_floating_point<T>::value, int> = 0>
inline T rand(T min, T max) {
	static std::mt19937 mt(static_cast<std::mt19937::result_type>(std::chrono::system_clock::now().time_since_epoch().count()));
	//static std::mt19937 mt(0);
	static std::uniform_real_distribution<T> dist(static_cast<T>(0.0), static_cast<T>(1.0));

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


inline std::string convert(const std::wstring & wstr) {
	static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	return converter.to_bytes(wstr);
}

inline std::wstring convert(const std::string & str) {
	static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	return converter.from_bytes(str);
}

template <typename T, std::enable_if_t<std::is_floating_point<T>::value, int> = 0>
inline vec3<T> rgb2hsl(const vec3<T> & rgb) {
	vec3<T> hsl(0, 0, 0);

	nat minI(rgb.r <= rgb.g ? 0 : 1);
	if (rgb.b < rgb[minI]) minI = 2;
	nat maxI(rgb.r >= rgb.g ? 0 : 1);
	if (rgb.b > rgb[maxI]) maxI = 2;

	// lightness
	hsl.z = (rgb[minI] + rgb[maxI]) * static_cast<T>(0.5);

	if (hsl.z > 0 && hsl.z < static_cast<T>(1.0)) {
		// saturation
		if (hsl.z > static_cast<T>(0.5)) {
			hsl.y = (rgb[maxI] - rgb[minI]) / (static_cast<T>(2.0) - (hsl.z * static_cast<T>(2.0)));
		}
		else {
			hsl.y = (rgb[maxI] - rgb[minI]) / (hsl.z * static_cast<T>(2.0));
		}

		if (hsl.y > 0) {
			// hue
			hsl.x = maxI * static_cast<T>(1.0 / 3.0);
			hsl.x += (rgb[(maxI + 1) % 3] - rgb[((maxI + 2) % 3)]) / (rgb[maxI] - rgb[minI]) * static_cast<T>(1.0 / 6.0);
			hsl.x += static_cast<T>(1.0);
			hsl.x -= std::floor(hsl.x);
		}
	}

	return hsl;
}

template <typename T, std::enable_if_t<std::is_floating_point<T>::value, int> = 0>
inline vec3<T> hsl2rgb(const vec3<T> & hsl) {
	if (hsl.y == 0) {
		return vec3<T>(hsl.z, hsl.z, hsl.z);
	}

	vec3<T> rgb(0, 0, 0);
	T temp;

	// hue
	temp = std::round(hsl.x * static_cast<T>(3.0));
	nat maxI(static_cast<nat>(temp) % 3);
	rgb[maxI] = static_cast<T>(1.0);
	T secondaryWeight((hsl.x * static_cast<T>(3.0) - temp) * static_cast<T>(2.0));
	nat midI((maxI + nat(secondaryWeight > 0 ? std::ceil(secondaryWeight) : std::floor(secondaryWeight)) + 3) % 3);
	rgb[midI] = std::abs(secondaryWeight);

	// saturation
	temp = static_cast<T>(1.0) - hsl.y;
	rgb.r += (static_cast<T>(0.5) - rgb.r) * temp;
	rgb.g += (static_cast<T>(0.5) - rgb.g) * temp;
	rgb.b += (static_cast<T>(0.5) - rgb.b) * temp;

	// lightness
	temp = (hsl.z - static_cast<T>(0.5)) * static_cast<T>(2.0);
	if (hsl.z > static_cast<T>(0.5)) {
		rgb.r += (static_cast<T>(1.0) - rgb.r) * temp;
		rgb.g += (static_cast<T>(1.0) - rgb.g) * temp;
		rgb.b += (static_cast<T>(1.0) - rgb.b) * temp;
	}
	else {
		rgb.r += rgb.r * temp;
		rgb.g += rgb.g * temp;
		rgb.b += rgb.b * temp;
	}

	return rgb;
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

inline std::string timeString(double seconds) {
	static const double k_secondsPerDay(86400.0);
	static const double k_secondsPerHour(3600.0);
	static const double k_secondsPerMinute(60.0);
	
	seconds = std::floor(seconds);
	double days(std::floor(seconds / k_secondsPerDay)); seconds -= days * k_secondsPerDay;
	double hours(std::floor(seconds / k_secondsPerHour)); seconds -= hours * k_secondsPerHour;
	double minutes(std::floor(seconds / k_secondsPerMinute)); seconds -= minutes * k_secondsPerMinute;

	std::stringstream ss;

	ss << std::setw(2) << std::setfill('0') << static_cast<nat>(days) << ":";
	ss << std::setw(2) << std::setfill('0') << static_cast<nat>(hours) << ":";
	ss << std::setw(2) << std::setfill('0') << static_cast<nat>(minutes) << ":";
	ss << std::setw(2) << std::setfill('0') << static_cast<nat>(seconds);

	return ss.str();
}

}