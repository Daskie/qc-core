#pragma once

#include <string>

#include <qc-core/core.hpp>

namespace qc
{
    enum CpuVendor
    {
        unknown,
        intel,
        amd
    };

    struct CpuInfo
    {
        CpuVendor vendor{};
        std::string brandStr{};
        bool isAvxSupported{};
        bool isAvx2Supported{};
    };

    extern const CpuInfo cpuInfo;
}
