#include <qc-core/core.hpp>

#include <gtest/gtest.h>

TEST(Result, value)
{
    const qc::Result<std::string> box{"hi"};
    ASSERT_TRUE(box);
    ASSERT_EQ(*box, "hi");
    ASSERT_EQ(box->size(), 2u);
}

TEST(Result, error)
{
    const qc::Result<std::string> box{};
    ASSERT_FALSE(box);
}

TEST(Result, defaultConstructor)
{
    static thread_local bool constructed;
    struct Dummy { Dummy() { constructed = true; } };

    constructed = false;
    const qc::Result<Dummy> b1{Dummy{}};
    ASSERT_TRUE(constructed);

    constructed = false;
    const qc::Result<Dummy> b2{};
    ASSERT_FALSE(constructed);
}

TEST(Result, destruction)
{
    static thread_local bool destructed;
    struct Dummy { ~Dummy() { destructed = true; } };

    destructed = false;
    {
        qc::Result<Dummy> b{Dummy{}};
    }
    ASSERT_TRUE(destructed);

    destructed = false;
    {
        qc::Result<Dummy> b{};
    }
    ASSERT_FALSE(destructed);
}

TEST(Result, noDefaultConstructor)
{
    struct Dummy { int x; Dummy(const int x) : x{x} {} };

    const qc::Result<Dummy> b1{7};
    ASSERT_TRUE(b1);
    ASSERT_EQ(b1->x, 7);

    const qc::Result<Dummy> b2{};
    ASSERT_FALSE(b2);
}
