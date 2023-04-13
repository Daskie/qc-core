#include <qc-core/enum-utils.hpp>

#include <gtest/gtest.h>

using namespace qc::types;
using namespace qc::primitives;

enum class Enum0 : s32 { a, b, c };
enum class Enum1 : s32 { a, b, c, _n };
enum class Enum2 : u32 { a, b, c };
enum class Enum3 : u32 { a, b, c, _n };
enum class Enum4 : u32 { _n };
enum class Enum5 : u32 {};

TEST(EnumUtils, countableEnum)
{
    static_assert(!qc::CountableEnum<Enum0>);
    static_assert(!qc::CountableEnum<Enum1>);
    static_assert(!qc::CountableEnum<Enum2>);
    static_assert(qc::CountableEnum<Enum3>);
    static_assert(qc::CountableEnum<Enum4>);
    static_assert(!qc::CountableEnum<Enum5>);
}

TEST(EnumUtils, enumN)
{
    ASSERT_EQ(3u, qc::enumN<Enum3>);
    ASSERT_EQ(0u, qc::enumN<Enum4>);
}

TEST(EnumUtils, enumArray)
{
    ASSERT_EQ((std::array<Enum3, 3u>{Enum3::a, Enum3::b, Enum3::c}), qc::enumArray<Enum3>);
    ASSERT_EQ((std::array<Enum4, 0u>{}), qc::enumArray<Enum4>);
}
