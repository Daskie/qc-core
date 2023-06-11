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
    nodisc inline T pairwiseSum(const u64 n, const T * const vals)
    {
        if (n == 0u) return T(0);
        if (n == 1u) return vals[0];
        if (n == 2u) return vals[0] + vals[1];
        return pairwiseSum(n >> 1, vals) + pairwiseSum((n + 1u) >> 1, vals + (n >> 1));
    }

    // TODO: Version that maps file to memory for bulk transfers, non-sequential access, or both reading and writing
    // TODO: Once have our own string class, return some kind of dynamic array result instead to avoid 4GB list limit
    template <typename DstContainer>
    nodisc inline Result<DstContainer> _readFile(const std::filesystem::path & path)
    {
        DstContainer dst{};

        std::error_code ec{};
        const u64 size{std::filesystem::file_size(path, ec)};

        // Issue with file, or file too large
        FAIL_IF(ec || size > dst.max_size() || size > u64(std::numeric_limits<std::streamsize>::max()));

        std::ifstream ifs{path, std::ios::binary};

        // Failed to open file
        FAIL_IF(!ifs.good());

        dst.resize(typename DstContainer::size_type(size)); // TODO: string version initializes its memory - potential performance concern for large files

        ifs.read(std::bit_cast<char *>(dst.data()), std::streamsize(size));

        // Failed to read file
        FAIL_IF(!ifs.good());

        return dst;
    }

    ///
    /// @return the content of the file, or empty list if failure
    ///
    nodisc inline Result<List<u8>> readFile(const std::filesystem::path & path)
    {
        return _readFile<List<u8>>(path);
    }

    ///
    /// @return the content of the file, or empty string if failure
    ///
    nodisc inline Result<std::string> readTextFile(const std::filesystem::path & path)
    {
        return _readFile<std::string>(path);
    }

    /// @return whether the file was successfully written
    nodisc inline bool writeFile(const std::filesystem::path & path, const void * const data, const u64 size)
    {
        // No data provided
        FAIL_IF(size && !data);

        // Data too large
        FAIL_IF(size > uintmax_t(std::numeric_limits<std::streamsize>::max()));

        std::ofstream ofs{path, std::ios::out | std::ios::binary};

        // Failed to open file
        FAIL_IF(!ofs.good());

        return ofs.write(static_cast<const char *>(data), std::streamsize(size)).good();
    }

    /// @return whether the file was successfully written
    nodisc inline bool writeTextFile(const std::filesystem::path & path, const std::string_view str)
    {
        return writeFile(path, str.data(), str.size());
    }
}
