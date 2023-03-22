#include <qc-core/version.hpp>

#include <gtest/gtest.h>

using namespace qc::primitives;
using qc::Version;

TEST(Version, u32Conversion)
{
    static_assert(u32(Version{0x12u, 0x34u, 0x5678u}) == 0x12'34'5678u);
    static_assert(Version{0x12'34'5678u} == Version{0x12u, 0x34u, 0x5678u});
}

TEST(Version, comparison)
{
    static_assert(Version{0u, 0u, 0u} == Version{0u, 0u, 0u});
    static_assert(Version{0u, 0u, 0u} != Version{0u, 0u, 1u});
    static_assert(Version{0u, 0u, 0u} < Version{0u, 0u, 1u});
    static_assert(Version{0u, 0u, 0u} <= Version{0u, 0u, 1u});
    static_assert(Version{0u, 1u, 0u} > Version{0u, 0u, 2u});
    static_assert(Version{0u, 1u, 0u} >= Version{0u, 0u, 2u});
    static_assert(Version{1u, 0u, 0u} > Version{0u, 2u, 3u});
    static_assert(Version{1u, 0u, 0u} >= Version{0u, 2u, 3u});
}
