#pragma once

#include <memory>
#include <fstream>
#include <codecvt>
#include <string>
#include <sstream>
#include <iomanip>
#include <filesystem>

#include "core.hpp"

namespace qc::core::utils {

    template <typename T>
    T pairwiseSum(size_t n, const T * vals) {
        if (n == 0u) return T(0);
        if (n == 1u) return vals[0];
        if (n == 2u) return vals[0] + vals[1];
        return pairwiseSum(n >> 1, vals) + pairwiseSum((n + 1u) >> 1, vals + (n >> 1));
    }

    // Throws `std::system_error` on failure
    inline pair<std::unique_ptr<std::byte[]>, u64> readFile(const std::filesystem::path & path) {
        pair<std::unique_ptr<std::byte[]>, u64> result;

        result.second = std::filesystem::file_size(path);
        if (result.second > std::numeric_limits<size_t>::max() || result.second > u64(std::numeric_limits<std::streamsize>::max())) {
            throw std::system_error(std::make_error_code(std::errc::file_too_large));
        }

        result.first = std::make_unique<std::byte[]>(size_t(result.second));
        std::ifstream ifs(path, std::ios::in | std::ios::binary);
        ifs.exceptions(std::ios::badbit | std::ios::failbit);
        ifs.read(reinterpret_cast<char *>(result.first.get()), std::streamsize(result.second));

        return move(result);
    }

    // Throws `std::system_error` on failure
    inline void writeFile(const std::filesystem::path & path, const void * data, size_t size) {
        std::ofstream ofs(path, std::ios::out | std::ios::binary);
        ofs.exceptions(std::ios::badbit | std::ios::failbit);
        ofs.write(reinterpret_cast<const char *>(data), size);
    }

    inline std::string timeString(double seconds) {
        static const double secondsPerDay(86400.0);
        static const double secondsPerHour(3600.0);
        static const double secondsPerMinute(60.0);

        seconds = std::floor(seconds);
        double days(std::floor(seconds / secondsPerDay)); seconds -= days * secondsPerDay;
        double hours(std::floor(seconds / secondsPerHour)); seconds -= hours * secondsPerHour;
        double minutes(std::floor(seconds / secondsPerMinute)); seconds -= minutes * secondsPerMinute;

        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << int(days) << ":";
        ss << std::setw(2) << std::setfill('0') << int(hours) << ":";
        ss << std::setw(2) << std::setfill('0') << int(minutes) << ":";
        ss << std::setw(2) << std::setfill('0') << int(seconds);

        return ss.str();
    }

    namespace print {

        template <typename T>
        struct _binary_s {

            u08 data[sizeof(T)];
            int blockSize;

            _binary_s(const T & v, int blockSize) :
                blockSize(blockSize)
            {
                std::memcpy(data, &v, sizeof(T));
            }

            friend std::ostream & operator<<(std::ostream & os, const _binary_s & b) {
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

        template <typename T>
        inline _binary_s<T> binary(const T & v, int blockSize = sizeof(T)) {
            return _binary_s<T>(v, blockSize);
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
