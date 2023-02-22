#include <gtest/gtest.h>

#include <qc-core/e-box.hpp>

enum class Error { none, a, b, c };


TEST(EBox, value)
{
    const qc::EBox<std::string, Error> box{"hi"};
    ASSERT_TRUE(box);
    ASSERT_EQ(box, Error::none);
    ASSERT_EQ(box.error(), Error::none);
    ASSERT_EQ(*box, "hi");
    ASSERT_EQ(box->size(), 2u);
}

TEST(EBox, error)
{
    const qc::EBox<std::string, Error> box{Error::b};
    ASSERT_FALSE(box);
    ASSERT_EQ(box, Error::b);
    ASSERT_EQ(box.error(), Error::b);
}

TEST(EBox, defaultConstructor)
{
    static thread_local bool constructed;
    struct Dummy { Dummy() { constructed = true; } };

    constructed = false;
    const qc::EBox<Dummy, Error> b1{};
    ASSERT_TRUE(constructed);

    constructed = false;
    const qc::EBox<Dummy, Error> b2{Error::a};
    ASSERT_FALSE(constructed);
}

TEST(EBox, destruction)
{
    static thread_local bool destructed;
    struct Dummy { ~Dummy() { destructed = true; } };

    destructed = false;
    {
        qc::EBox<Dummy, Error> b{};
    }
    ASSERT_TRUE(destructed);

    destructed = false;
    {
        qc::EBox<Dummy, Error> b{Error::a};
    }
    ASSERT_FALSE(destructed);
}
