#include <qc-core/cpu.hpp>

#include <bit>

#ifdef QC_MSVC
    #include <intrin.h>
#else
    #include <cpuid.h>
#endif

namespace qc
{
    namespace
    {
        struct _Regs
        {
            u32 eax, ebx, ecx, edx;

            std::string_view str() const
            {
                return {std::bit_cast<const char *>(this), sizeof(*this)};
            }
        };

        _Regs _cpuid(const u32 id)
        {
            _Regs regs;
            #ifdef QC_MSVC
                ::__cpuidex(std::bit_cast<int *>(&regs.eax), int(id), 0);
            #else
                __cpuid_count(id, 0, regs.eax, regs.ebx, regs.ecx, regs.edx);
            #endif
            return regs;
        }

        CpuInfo _getCpuInfo()
        {
            CpuInfo info{};

            // Get vendor string and highest valid function ID
            _Regs regs0{_cpuid(0x0u)};
            const u32 maxId{regs0.eax};

            std::swap(regs0.ecx, regs0.edx);
            std::string_view vendorStr{regs0.str().substr(4u)};
            if (vendorStr == "GenuineIntel")
            {
                info.vendor = CpuVendor::intel;
            }
            else if (vendorStr == "AuthenticAMD")
            {
                info.vendor = CpuVendor::amd;
            }
            else
            {
                info.vendor = CpuVendor::unknown;
            }

            // Get AVX support
            if (maxId >= 0x1u)
            {
                const _Regs regs1{_cpuid(0x1u)};
                info.isAvxSupported = bool(regs1.ecx & (1u << 28));
            }

            // Get AVX2 support
            if (maxId >= 0x7u)
            {
                const _Regs regs7{_cpuid(0x7u)};
                info.isAvx2Supported = bool(regs7.ebx & (1u << 5));
            }

            // Get highest valid extended ID
            const _Regs extRegs0{_cpuid(0x80000000u)};
            const u32 maxExtId{extRegs0.eax};

            // Get brand string
            if (maxExtId >= 0x80000004)
            {
                const _Regs extRegs2{_cpuid(0x80000002u)};
                const _Regs extRegs3{_cpuid(0x80000003u)};
                const _Regs extRegs4{_cpuid(0x80000004u)};
                info.brandStr += extRegs2.str();
                info.brandStr += extRegs3.str();
                info.brandStr += extRegs4.str();
            }

            return info;
        }
    }

    const CpuInfo cpuInfo{_getCpuInfo()};
}
