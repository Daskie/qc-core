#include <gtest/gtest.h>

#include <qc-core/enum-iterator.hpp>

using namespace qc::types;

enum class Enum0 : int { a, b, c };
enum class Enum1 : int { a, b, c, _n };
enum class Enum2 : uint { a, b, c };
enum class Enum3 : uint { a, b, c, _n };
enum class Enum4 : uint { _n };
enum class Enum5 : uint {};

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
    EXPECT_EQ(Enum4::_n, *qc::EnumIteration<Enum4>{}.begin());
    EXPECT_EQ(Enum4::_n, *qc::EnumIteration<Enum4>{}.end());
}

TEST(enumIterator, forEach)
{
    Enum3 ref{Enum3::a};
    uint count{0u};

    for (const Enum3 e : qc::EnumIteration<Enum3>{}) {
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
    for (const Enum4 e : qc::EnumIteration<Enum4>{}) {
        FAIL();
    }
}
