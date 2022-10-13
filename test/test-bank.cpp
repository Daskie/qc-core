#include <qc-core/bank.hpp>

#include <gtest/gtest.h>

using namespace qc::types;

TEST(Bank, general)
{
    qc::Bank<int> bank{};
    ASSERT_EQ(0u, bank.capacity());
    ASSERT_EQ(0u, bank.size());
    ASSERT_TRUE(bank.empty());

    ASSERT_EQ(0u, bank.create(0).i);
    ASSERT_EQ(0, bank[0u]);
    ASSERT_EQ(16u, bank.capacity());
    ASSERT_EQ(1u, bank.size());
    ASSERT_FALSE(bank.empty());

    for (int i{1}; i < 16; ++i)
    {
        ASSERT_EQ(i, bank.create(i).i);
        ASSERT_EQ(i, bank[i]);
        ASSERT_EQ(16u, bank.capacity());
        ASSERT_EQ(i + 1, bank.size());
    }

    ASSERT_EQ(16u, bank.create(16).i);
    ASSERT_EQ(32u, bank.capacity());
    ASSERT_EQ(17u, bank.size());

    for (int i{0}; i < 16; ++i)
    {
        bank.destroy(i);
        ASSERT_EQ(32u, bank.capacity());
        ASSERT_EQ(16 - i, bank.size());
    }

    ASSERT_EQ(32u, bank.capacity());
    ASSERT_EQ(1u, bank.size());
    ASSERT_FALSE(bank.empty());
    ASSERT_EQ(16, bank[16u]);

    bank.destroy(16u);
    ASSERT_EQ(32u, bank.capacity());
    ASSERT_EQ(0u, bank.size());
    ASSERT_TRUE(bank.empty());
}

TEST(Bank, generalNontrivial)
{
    qc::Bank<std::unique_ptr<int>> bank{};
    ASSERT_EQ(0u, bank.capacity());
    ASSERT_EQ(0u, bank.size());
    ASSERT_TRUE(bank.empty());

    ASSERT_EQ(0u, bank.create(new int{0}).i);
    ASSERT_EQ(0, *bank[0u]);
    ASSERT_EQ(16u, bank.capacity());
    ASSERT_EQ(1u, bank.size());
    ASSERT_FALSE(bank.empty());

    for (int i{1}; i < 16; ++i)
    {
        ASSERT_EQ(i, bank.create(new int{i}).i);
        ASSERT_EQ(i, *bank[i]);
        ASSERT_EQ(16u, bank.capacity());
        ASSERT_EQ(i + 1, bank.size());
    }

    ASSERT_EQ(16, bank.create(new int{16}).i);
    ASSERT_EQ(32u, bank.capacity());
    ASSERT_EQ(17u, bank.size());

    for (int i{0}; i < 16; ++i)
    {
        bank.destroy(i);
        ASSERT_EQ(32u, bank.capacity());
        ASSERT_EQ(16 - i, bank.size());
    }

    ASSERT_EQ(32u, bank.capacity());
    ASSERT_EQ(1u, bank.size());
    ASSERT_FALSE(bank.empty());
    ASSERT_EQ(16, *bank[16u]);

    bank.destroy(16u);
    ASSERT_EQ(32u, bank.capacity());
    ASSERT_EQ(0u, bank.size());
    ASSERT_TRUE(bank.empty());
}

TEST(Bank, reserve)
{
    qc::Bank<int> bank{};
    ASSERT_EQ(0u, bank.capacity());
    ASSERT_EQ(0u, bank.size());

    bank.reserve(0u);
    ASSERT_EQ(0u, bank.capacity());
    ASSERT_EQ(0u, bank.size());

    bank.reserve(1u);
    ASSERT_EQ(16u, bank.capacity());
    ASSERT_EQ(0u, bank.size());

    bank.reserve(16u);
    ASSERT_EQ(16u, bank.capacity());
    ASSERT_EQ(0u, bank.size());

    bank.reserve(17u);
    ASSERT_EQ(32u, bank.capacity());
    ASSERT_EQ(0u, bank.size());

    bank.reserve(0u);
    ASSERT_EQ(32u, bank.capacity());
    ASSERT_EQ(0u, bank.size());
}

TEST(Bank, freeOrder)
{
    qc::Bank<int> bank{};

    ASSERT_EQ(0u, bank.create(0).i);
    ASSERT_EQ(0, bank[0u]);

    ASSERT_EQ(1u, bank.create(1).i);
    ASSERT_EQ(1, bank[1u]);

    bank.destroy(0u);

    ASSERT_EQ(0u, bank.create(2).i);
    ASSERT_EQ(2, bank[0u]);

    ASSERT_EQ(2u, bank.create(3).i);
    ASSERT_EQ(3, bank[2u]);

    bank.destroy(2u);

    ASSERT_EQ(2u, bank.create(4).i);
    ASSERT_EQ(4, bank[2u]);

    ASSERT_EQ(3u, bank.size());

    ASSERT_EQ(16u, bank.capacity());
    bank.reserve(32u);
    ASSERT_EQ(32u, bank.capacity());

    for (int i{0}; i < 16; ++i)
    {
        ASSERT_EQ(16u + u32(i), bank.create(5 + i).i);
        ASSERT_EQ(5 + i, bank[16u + u32(i)]);
    }

    ASSERT_EQ(19u, bank.size());

    for (int i{0}; i < 13; ++i)
    {
        ASSERT_EQ(3u + u32(i), bank.create(21 + i).i);
        ASSERT_EQ(21 + i, bank[3u + u32(i)]);
    }

    ASSERT_EQ(32u, bank.size());

    for (int i{0}; i < 32; ++i)
    {
        bank.destroy(31 - i);
    }

    ASSERT_EQ(0u, bank.size());

    for (int i{0}; i < 32; ++i)
    {
        ASSERT_EQ(u32(i), bank.create(100 + i).i);
        ASSERT_EQ(100 + i, bank[i]);
    }

    ASSERT_EQ(32u, bank.size());
    ASSERT_EQ(32u, bank.capacity());
}
