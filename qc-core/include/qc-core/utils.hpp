#pragma once

#include <cmath>

#include <fstream>
#include <codecvt>
#include <string>
#include <sstream>
#include <iomanip>
#include <filesystem>

#include <qc-core/core.hpp>
#include <qc-core/list.hpp>

namespace qc::utils
{
    template <typename T>
    inline T pairwiseSum(const u64 n, const T * const vals)
    {
        if (n == 0u) return T(0);
        if (n == 1u) return vals[0];
        if (n == 2u) return vals[0] + vals[1];
        return pairwiseSum(n >> 1, vals) + pairwiseSum((n + 1u) >> 1, vals + (n >> 1));
    }

    template <typename DstContainer>
    inline Result<DstContainer> _readFile(const std::filesystem::path & path)
    {
        DstContainer dst{};

        std::error_code ec{};
        const u64 size{std::filesystem::file_size(path, ec)};

        // Issue with file, or file too large
        if (ec || size > dst.max_size() || size > u64(std::numeric_limits<std::streamsize>::max()))
        {
            return {};
        }

        // TODO: Map file into memory instead
        std::ifstream ifs{path, std::ios::binary};

        // Failed to open file
        if (!ifs.good())
        {
            return {};
        }

        dst.resize(size); // TODO: string version initializes its memory - potential performance concern for large files

        ifs.read(std::bit_cast<char *>(dst.data()), std::streamsize(size));

        // Failed to read file
        if (!ifs.good())
        {
            return {};
        }

        return dst;
    }

    ///
    /// @return the content of the file, or empty list if failure
    ///
    [[nodiscard]] inline Result<List<u8>> readFile(const std::filesystem::path & path)
    {
        return _readFile<List<u8>>(path);
    }

    ///
    /// @return the content of the file, or empty string if failure
    ///
    [[nodiscard]] inline Result<std::string> readTextFile(const std::filesystem::path & path)
    {
        return _readFile<std::string>(path);
    }

    /// @return whether the file was successfully written
    [[nodiscard]] inline bool writeFile(const std::filesystem::path & path, const void * const data, const u64 size)
    {
        if (!data)
        {
            assert(false);
            return false;
        }

        // Data too large
        if (size > uintmax_t(std::numeric_limits<std::streamsize>::max()))
        {
            return false;
        }

        std::ofstream ofs{path, std::ios::out | std::ios::binary};

        // Failed to open file
        if (!ofs.good())
        {
            return false;
        }

        return ofs.write(static_cast<const char *>(data), std::streamsize(size)).good();
    }

    /// @return whether the file was successfully written
    [[nodiscard]] inline bool writeTextFile(const std::filesystem::path & path, const std::string_view str)
    {
        return writeFile(path, str.data(), str.size());
    }

    inline std::string timeString(double seconds)
    {
        static constexpr double secondsPerMinute(60.0);
        static constexpr double secondsPerHour(60.0 * secondsPerMinute);
        static constexpr double secondsPerDay(24.0 * secondsPerHour);

        seconds = std::floor(seconds);

        const double days{std::floor(seconds / secondsPerDay)};
        seconds -= days * secondsPerDay;

        const double hours{std::floor(seconds / secondsPerHour)};
        seconds -= hours * secondsPerHour;

        const double minutes{std::floor(seconds / secondsPerMinute)};
        seconds -= minutes * secondsPerMinute;

        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << int(days) << ":";
        ss << std::setw(2) << std::setfill('0') << int(hours) << ":";
        ss << std::setw(2) << std::setfill('0') << int(minutes) << ":";
        ss << std::setw(2) << std::setfill('0') << int(seconds);

        return ss.str();
    }

    namespace print
    {
        template <typename T>
        struct _binary_s
        {
            alignas(T) u8 data[sizeof(T)];
            int blockSize;

            _binary_s(const T & v, const int blockSize) :
                data{},
                blockSize{blockSize}
            {
                std::copy_n(reinterpret_cast<const u8 *>(&v), sizeof(T), data);
            }

            friend std::ostream & operator<<(std::ostream & os, const _binary_s & b)
            {
                const int nBlocks{sizeof(T) / b.blockSize};

                for (int blockI{0}; blockI < nBlocks; ++blockI)
                {
                    for (int byteI{b.blockSize - 1}; byteI >= 0; --byteI)
                    {
                        u8 byte(b.data[blockI * b.blockSize + byteI]);
                        for (int bitI{0}; bitI < 8; ++bitI)
                        {
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
        inline _binary_s<T> binary(const T & v, const int blockSize = sizeof(T))
        {
            return _binary_s<T>(v, blockSize);
        }

        struct repeat
        {
            std::string s;
            int n;

            repeat(std::string s, const int n) : s(std::move(s)), n(n) {}

            friend std::ostream & operator<<(std::ostream & os, const repeat & r)
            {
                for (int i{0}; i < r.n; ++i)
                {
                    os << r.s;
                }
                return os;
            }
        };

        struct line
        {
            int n;

            explicit line(const int n) : n(n) {}

            friend std::ostream & operator<<(std::ostream & os, const line & l)
            {
                return os << repeat("-", l.n);
            }
        };
    }
}
