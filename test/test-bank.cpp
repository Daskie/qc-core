#include <qc-core/bank.hpp>

#include <gtest/gtest.h>

using namespace qc::types;
using namespace qc::primitives;

TEST(Bank, general)
{
    qc::Bank<u32> bank{};
    ASSERT_EQ(0u, bank.capacity());
    ASSERT_EQ(0u, bank.size());
    ASSERT_TRUE(bank.empty());
    ASSERT_FALSE(bank);

    ASSERT_EQ(0u, bank.create(0u).i);
    ASSERT_EQ(0u, bank[0u]);
    ASSERT_EQ(16u, bank.capacity());
    ASSERT_EQ(1u, bank.size());
    ASSERT_FALSE(bank.empty());
    ASSERT_TRUE(bank);

    for (u32 i{1u}; i < 16u; ++i)
    {
        ASSERT_EQ(i, bank.create(i).i);
        ASSERT_EQ(i, bank[i]);
        ASSERT_EQ(16u, bank.capacity());
        ASSERT_EQ(i + 1u, bank.size());
    }

    ASSERT_EQ(16u, bank.create(16u).i);
    ASSERT_EQ(32u, bank.capacity());
    ASSERT_EQ(17u, bank.size());

    for (u32 i{0u}; i < 16u; ++i)
    {
        bank.destroy(i);
        ASSERT_EQ(32u, bank.capacity());
        ASSERT_EQ(16u - i, bank.size());
    }

    ASSERT_EQ(32u, bank.capacity());
    ASSERT_EQ(1u, bank.size());
    ASSERT_FALSE(bank.empty());
    ASSERT_EQ(16, bank[16u]);

    bank.destroy(16u);
    ASSERT_EQ(32u, bank.capacity());
    ASSERT_EQ(0u, bank.size());
    ASSERT_TRUE(bank.empty());
    ASSERT_FALSE(bank);
}

TEST(Bank, generalNontrivial)
{
    qc::Bank<std::unique_ptr<u32>> bank{};
    ASSERT_EQ(0u, bank.capacity());
    ASSERT_EQ(0u, bank.size());
    ASSERT_TRUE(bank.empty());
    ASSERT_FALSE(bank);

    ASSERT_EQ(0u, bank.create(new u32{0u}).i);
    ASSERT_EQ(0u, *bank[0u]);
    ASSERT_EQ(16u, bank.capacity());
    ASSERT_EQ(1u, bank.size());
    ASSERT_FALSE(bank.empty());
    ASSERT_TRUE(bank);

    for (u32 i{1u}; i < 16u; ++i)
    {
        ASSERT_EQ(i, bank.create(new u32{i}).i);
        ASSERT_EQ(i, *bank[i]);
        ASSERT_EQ(16u, bank.capacity());
        ASSERT_EQ(i + 1u, bank.size());
    }

    ASSERT_EQ(16u, bank.create(new u32{16u}).i);
    ASSERT_EQ(32u, bank.capacity());
    ASSERT_EQ(17u, bank.size());

    for (u32 i{0u}; i < 16u; ++i)
    {
        bank.destroy(i);
        ASSERT_EQ(32u, bank.capacity());
        ASSERT_EQ(16u - i, bank.size());
    }

    ASSERT_EQ(32u, bank.capacity());
    ASSERT_EQ(1u, bank.size());
    ASSERT_FALSE(bank.empty());
    ASSERT_EQ(16u, *bank[16u]);

    bank.destroy(16u);
    ASSERT_EQ(32u, bank.capacity());
    ASSERT_EQ(0u, bank.size());
    ASSERT_TRUE(bank.empty());
    ASSERT_FALSE(bank);
}

TEST(Bank, constructors)
{
    {
        qc::Bank<u32> bank{};
        ASSERT_EQ(bank.capacity(), 0u);
        ASSERT_TRUE(bank.empty());
    }
    {
        qc::Bank<u32> bank{7u};
        ASSERT_EQ(bank.capacity(), 16u);
        ASSERT_TRUE(bank.empty());
    }
    {
        qc::Bank<u32> bank{64u};
        ASSERT_EQ(bank.capacity(), 64u);
        ASSERT_TRUE(bank.empty());
    }
}

TEST(Bank, reserve)
{
    qc::Bank<u32> bank{};
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
    qc::Bank<u32> bank{};

    ASSERT_EQ(0u, bank.create(0u).i);
    ASSERT_EQ(0u, bank[0u]);

    ASSERT_EQ(1u, bank.create(1u).i);
    ASSERT_EQ(1u, bank[1u]);

    bank.destroy(0u);

    ASSERT_EQ(0u, bank.create(2u).i);
    ASSERT_EQ(2u, bank[0u]);

    ASSERT_EQ(2u, bank.create(3u).i);
    ASSERT_EQ(3u, bank[2u]);

    bank.destroy(2u);

    ASSERT_EQ(2u, bank.create(4u).i);
    ASSERT_EQ(4u, bank[2u]);

    ASSERT_EQ(3u, bank.size());

    ASSERT_EQ(16u, bank.capacity());
    bank.reserve(32u);
    ASSERT_EQ(32u, bank.capacity());

    for (u32 i{0u}; i < 16u; ++i)
    {
        ASSERT_EQ(16u + i, bank.create(5u + i).i);
        ASSERT_EQ(5u + i, bank[16u + i]);
    }

    ASSERT_EQ(19u, bank.size());

    for (u32 i{0u}; i < 13u; ++i)
    {
        ASSERT_EQ(3u + i, bank.create(21u + i).i);
        ASSERT_EQ(21u + i, bank[3u + i]);
    }

    ASSERT_EQ(32u, bank.size());

    for (u32 i{0u}; i < 32u; ++i)
    {
        bank.destroy(31u - i);
    }

    ASSERT_EQ(0u, bank.size());

    for (u32 i{0u}; i < 32u; ++i)
    {
        ASSERT_EQ(i, bank.create(100u + i).i);
        ASSERT_EQ(100u + i, bank[i]);
    }

    ASSERT_EQ(32u, bank.size());
    ASSERT_EQ(32u, bank.capacity());
}

TEST(Bank, clear)
{
    qc::Bank<u32> bank{};

    bank.clear();
    ASSERT_TRUE(bank.empty());
    ASSERT_EQ(0u, bank.capacity());

    auto [e0, i0]{bank.create(0u)};
    ASSERT_EQ(0u, e0);
    ASSERT_EQ(0u, i0);
    ASSERT_EQ(1u, bank.size());
    ASSERT_EQ(16u, bank.capacity());

    bank.clear();
    ASSERT_TRUE(bank.empty());
    ASSERT_EQ(16u, bank.capacity());

    auto [e1, i1]{bank.create(1u)};
    ASSERT_EQ(1u, e1);
    ASSERT_EQ(0u, i1);
    auto [e2, i2]{bank.create(2u)};
    ASSERT_EQ(2u, e2);
    ASSERT_EQ(1u, i2);
    auto [e3, i3]{bank.create(3u)};
    ASSERT_EQ(3u, e3);
    ASSERT_EQ(2u, i3);
    ASSERT_EQ(16u, bank.capacity());

    bank.clear();
    ASSERT_TRUE(bank.empty());
    ASSERT_EQ(16u, bank.capacity());

    auto [e4, i4]{bank.create(4u)};
    ASSERT_EQ(4u, e4);
    ASSERT_EQ(0u, i4);
    auto [e5, i5]{bank.create(5u)};
    ASSERT_EQ(5u, e5);
    ASSERT_EQ(1u, i5);
    auto [e6, i6]{bank.create(6u)};
    ASSERT_EQ(6u, e6);
    ASSERT_EQ(2u, i6);
    ASSERT_EQ(16u, bank.capacity());

    bank.clear();
    ASSERT_TRUE(bank.empty());
    ASSERT_EQ(16u, bank.capacity());
}

TEST(Bank, clearNontrivial)
{
    qc::Bank<std::unique_ptr<u32>> bank{};

    bank.clear();
    ASSERT_TRUE(bank.empty());
    ASSERT_EQ(0u, bank.capacity());

    auto [e0, i0]{bank.create(new u32{0u})};
    ASSERT_EQ(0u, *e0);
    ASSERT_EQ(0u, i0);
    ASSERT_EQ(1u, bank.size());
    ASSERT_EQ(16u, bank.capacity());

    bank.clear();
    ASSERT_TRUE(bank.empty());
    ASSERT_EQ(16u, bank.capacity());

    auto [e1, i1]{bank.create(new u32{1u})};
    ASSERT_EQ(1u, *e1);
    ASSERT_EQ(0u, i1);
    auto [e2, i2]{bank.create(new u32{2u})};
    ASSERT_EQ(2u, *e2);
    ASSERT_EQ(1u, i2);
    auto [e3, i3]{bank.create(new u32{3u})};
    ASSERT_EQ(3u, *e3);
    ASSERT_EQ(2u, i3);
    ASSERT_EQ(16u, bank.capacity());

    bank.clear();
    ASSERT_TRUE(bank.empty());
    ASSERT_EQ(16u, bank.capacity());
}
