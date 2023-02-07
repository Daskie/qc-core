#include <qc-core/cpu.hpp>

#ifdef WIN32
    #include <intrin.h>
#else
    #error "Platform not yet supported"
#endif

namespace qc
{
    namespace
    {
        struct _Regs
        {
            int eax, ebx, ecx, edx;

            int * data() { return &eax; }
        };

        CpuInfo _getCpuInfo()
        {
            // Can't use AVX if we're checking for the existence of AVX
            #ifdef __AVX__
            static_assert(false)
            #endif

            CpuInfo info{};

            // Process ID 0

            _Regs regs{};

            // Calling __cpuid with 0x0 as the function_id argument gets the number of the highest valid function ID
            __cpuid(regs.data(), 0x0);

            const int maxId{regs.eax};

            // Capture vendor string

            union
            {
                int blocks[4u]; // Extra for terminator
                char chars[16u];
            } vendorData{};

            vendorData.blocks[0] = regs.ebx;
            vendorData.blocks[1] = regs.edx;
            vendorData.blocks[2] = regs.ecx;

            const std::string_view vendorStr{vendorData.chars};

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

            // Process ID 0x7
            if (maxId >= 0x7)
            {
                __cpuid(regs.data(), 0x7);

                info.isAvx2Supported = bool(regs.ebx & (1 << 5));
            }

            // Process extended IDs

            // Calling __cpuid with 0x80000000 as the function_id argument gets the number of the highest valid extended ID
            __cpuid(regs.data(), 0x80000000);

            const int maxExtId{regs.eax};

            // Capture brand string

            union
            {
                int blocks[13u]; // Extra for terminator
                char chars[52u];
            } brandData{};

            if (maxExtId >= 0x80000004)
            {
                __cpuid(regs.data(), 0x80000002);
                brandData.blocks[0] = regs.eax;
                brandData.blocks[1] = regs.ebx;
                brandData.blocks[2] = regs.ecx;
                brandData.blocks[3] = regs.edx;

                __cpuid(regs.data(), 0x80000003);
                brandData.blocks[4] = regs.eax;
                brandData.blocks[5] = regs.ebx;
                brandData.blocks[6] = regs.ecx;
                brandData.blocks[7] = regs.edx;

                __cpuid(regs.data(), 0x80000004);
                brandData.blocks[ 8] = regs.eax;
                brandData.blocks[ 9] = regs.ebx;
                brandData.blocks[10] = regs.ecx;
                brandData.blocks[11] = regs.edx;
            }

            info.brandStr = brandData.chars;

            return info;
        }
    }

    const CpuInfo cpuInfo{_getCpuInfo()};
}
