#include <qc-core/enum-utils.hpp>

#include <gtest/gtest.h>

using namespace qc::types;
using namespace qc::primitives;

enum class Enum0 : s32 { a, b, c };
enum class Enum1 : s32 { a, b, c, _n };
enum class Enum2 : u32 { a, b, c };
enum class Enum3 : u32 { a, b, c, _n };
enum class Enum4 : u32 { a, _n };
enum class Enum5 : u32 { _n };
enum class Enum6 : u32 {};

TEST(EnumUtils, countableEnum)
{
    static_assert(!qc::CountableEnum<Enum0>);
    static_assert(!qc::CountableEnum<Enum1>);
    static_assert(!qc::CountableEnum<Enum2>);
    static_assert(qc::CountableEnum<Enum3>);
    static_assert(qc::CountableEnum<Enum4>);
    static_assert(!qc::CountableEnum<Enum5>);
    static_assert(!qc::CountableEnum<Enum6>);
}

TEST(EnumUtils, enumN)
{
    ASSERT_EQ(3u, qc::enumN<Enum3>);
    ASSERT_EQ(1u, qc::enumN<Enum4>);
}

TEST(EnumUtils, enumArray)
{
    ASSERT_EQ((qc::Array<Enum3, 3u>{Enum3::a, Enum3::b, Enum3::c}), qc::enumArray<Enum3>);
    ASSERT_EQ((qc::Array<Enum4, 1u>{Enum4::a}), qc::enumArray<Enum4>);
}
