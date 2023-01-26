#include <gtest/gtest.h>

#include <qc-core/enum-utils.hpp>

using namespace qc::concepts;
using namespace qc::types;

enum class Enum0 : int { a, b, c };
enum class Enum1 : int { a, b, c, _n };
enum class Enum2 : uint { a, b, c };
enum class Enum3 : uint { a, b, c, _n };
enum class Enum4 : uint { _n };
enum class Enum5 : uint {};

TEST(enumUtils, countableEnum)
{
    static_assert(!qc::CountableEnum<Enum0>);
    static_assert(!qc::CountableEnum<Enum1>);
    static_assert(!qc::CountableEnum<Enum2>);
    static_assert(qc::CountableEnum<Enum3>);
    static_assert(qc::CountableEnum<Enum4>);
    static_assert(!qc::CountableEnum<Enum5>);
}

TEST(enumUtils, enumCount)
{
    EXPECT_EQ(3u, qc::enumCount<Enum3>);
    EXPECT_EQ(0u, qc::enumCount<Enum4>);
}

#if 0

template <typename E> concept Compiles = requires
{
    typename qc::EnumIterator<E>;
    typename qc::EnumIteration<E>;
};

TEST(enumIterator, compiles)
{
    EXPECT_FALSE(Compiles<Enum0>);
    EXPECT_FALSE(Compiles<Enum1>);
    EXPECT_FALSE(Compiles<Enum2>);
    EXPECT_TRUE(Compiles<Enum3>);
    EXPECT_TRUE(Compiles<Enum4>);
    EXPECT_FALSE(Compiles<Enum5>);

    EXPECT_FALSE(Compiles<const Enum0>);
    EXPECT_TRUE(Compiles<const Enum3>);
}

TEST(enumIterator, forLoop)
{
    Enum3 ref{Enum3::a};
    uint count{0u};

    for (qc::EnumIterator<Enum3> it{Enum3::a}; it != qc::EnumIterator<Enum3>{Enum3::_n}; ++it) {
        EXPECT_EQ(ref, *it);
        ++reinterpret_cast<uint &>(ref);
        ++count;
    }

    EXPECT_EQ(static_cast<uint>(Enum3::_n), count);
}

TEST(enumIterator, forLoopEmpty)
{
    EXPECT_EQ(Enum4::_n, *qc::iterateEnum<Enum4>.begin());
    EXPECT_EQ(Enum4::_n, *qc::iterateEnum<Enum4>.end());
}

TEST(enumIterator, forEach)
{
    Enum3 ref{Enum3::a};
    uint count{0u};

    for (const Enum3 e : qc::iterateEnum<Enum3>) {
        EXPECT_EQ(ref, e);
        ++reinterpret_cast<uint &>(ref);
        ++count;
    }

    EXPECT_EQ(static_cast<uint>(Enum3::_n), count);
}

#pragma warning(suppress: 4702)
TEST(enumIterator, forEachEmpty)
{
    #pragma warning(suppress: 4189)
    for (const Enum4 e : qc::iterateEnum<Enum4>) {
        FAIL();
    }
}

#endif

TEST(enumUtils, enumArray)
{
    EXPECT_EQ((std::array<Enum3, 3u>{Enum3::a, Enum3::b, Enum3::c}), qc::enumArray<Enum3>);
    EXPECT_EQ((std::array<Enum4, 0u>{}), qc::enumArray<Enum4>);
}
