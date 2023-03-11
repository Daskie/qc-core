#include <qc-core/cpu.hpp>

#include <gtest/gtest.h>

using namespace qc::types;
using namespace qc::primitives;

TEST(Cpu, info)
{
    const qc::CpuInfo & info{qc::cpuInfo};

    ASSERT_NE(info.vendor, qc::CpuVendor::unknown);
    ASSERT_FALSE(info.brandStr.empty());
    ASSERT_TRUE(info.isAvxSupported);
    ASSERT_TRUE(info.isAvx2Supported);
}
