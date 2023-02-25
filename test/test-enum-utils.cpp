#include <qc-core/enum-utils.hpp>

#include <gtest/gtest.h>

using namespace qc::concepts;
using namespace qc::types;

enum class Enum0 : int { a, b, c };
enum class Enum1 : int { a, b, c, _n };
enum class Enum2 : uint { a, b, c };
enum class Enum3 : uint { a, b, c, _n };
enum class Enum4 : uint { _n };
enum class Enum5 : uint {};

TEST(EnumUtils, countableEnum)
{
    static_assert(!qc::CountableEnum<Enum0>);
    static_assert(!qc::CountableEnum<Enum1>);
    static_assert(!qc::CountableEnum<Enum2>);
    static_assert(qc::CountableEnum<Enum3>);
    static_assert(qc::CountableEnum<Enum4>);
    static_assert(!qc::CountableEnum<Enum5>);
}

TEST(EnumUtils, enumCount)
{
    ASSERT_EQ(3u, qc::enumCount<Enum3>);
    ASSERT_EQ(0u, qc::enumCount<Enum4>);
}

#if 0

template <typename E> concept Compiles = requires
{
    typename qc::EnumIterator<E>;
    typename qc::EnumIteration<E>;
};

TEST(enumIterator, compiles)
{
    ASSERT_FALSE(Compiles<Enum0>);
    ASSERT_FALSE(Compiles<Enum1>);
    ASSERT_FALSE(Compiles<Enum2>);
    ASSERT_TRUE(Compiles<Enum3>);
    ASSERT_TRUE(Compiles<Enum4>);
    ASSERT_FALSE(Compiles<Enum5>);

    ASSERT_FALSE(Compiles<const Enum0>);
    ASSERT_TRUE(Compiles<const Enum3>);
}

TEST(enumIterator, forLoop)
{
    Enum3 ref{Enum3::a};
    uint count{0u};

    for (qc::EnumIterator<Enum3> it{Enum3::a}; it != qc::EnumIterator<Enum3>{Enum3::_n}; ++it) {
        ASSERT_EQ(ref, *it);
        ++reinterpret_cast<uint &>(ref);
        ++count;
    }

    ASSERT_EQ(static_cast<uint>(Enum3::_n), count);
}

TEST(enumIterator, forLoopEmpty)
{
    ASSERT_EQ(Enum4::_n, *qc::iterateEnum<Enum4>.begin());
    ASSERT_EQ(Enum4::_n, *qc::iterateEnum<Enum4>.end());
}

TEST(enumIterator, forEach)
{
    Enum3 ref{Enum3::a};
    uint count{0u};

    for (const Enum3 e : qc::iterateEnum<Enum3>) {
        ASSERT_EQ(ref, e);
        ++reinterpret_cast<uint &>(ref);
        ++count;
    }

    ASSERT_EQ(static_cast<uint>(Enum3::_n), count);
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

TEST(EnumUtils, enumArray)
{
    ASSERT_EQ((std::array<Enum3, 3u>{Enum3::a, Enum3::b, Enum3::c}), qc::enumArray<Enum3>);
    ASSERT_EQ((std::array<Enum4, 0u>{}), qc::enumArray<Enum4>);
}
