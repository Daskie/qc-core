#include <qc-core/lot.hpp>

#include <gtest/gtest.h>

template <typename T> using IL = std::initializer_list<T>;

using namespace qc::primitives;

TEST(Lot, max_size)
{
    qc::Lot<s32> lot{};
    ASSERT_EQ(lot.max_size(), std::numeric_limits<u32>::max());
    ASSERT_EQ(qc::Lot<s32>::max_size(), lot.max_size());
}

TEST(Lot, construction)
{
    {
        qc::Lot<s32> lot{};
        ASSERT_TRUE(lot.empty());
        ASSERT_EQ(lot.size(), 0u);
        ASSERT_EQ(lot.capacity(), 0u);
    }
    {
        qc::Lot<s32> lot(7u);
        ASSERT_TRUE(!lot.empty());
        ASSERT_EQ(lot.size(), 7u);
        ASSERT_EQ(lot.capacity(), 7u);
    }
    {
        qc::Lot<s32> lot(7u, 7);
        ASSERT_EQ(lot.size(), 7u);
        ASSERT_EQ(lot.capacity(), 7u);
        ASSERT_EQ(lot, (IL<s32>{7, 7, 7, 7, 7, 7, 7}));
    }
    {
        std::vector<s32> v{1, 2, 3, 4, 5};
        qc::Lot<s32> lot{v.begin(), v.end()};
        ASSERT_EQ(lot.size(), 5u);
        ASSERT_EQ(lot.capacity(), 5u);
        ASSERT_EQ(lot, (IL<s32>{1, 2, 3, 4, 5}));
    }
    {
        qc::Lot<s32> lot{1, 2, 3, 4, 5};
        ASSERT_EQ(lot.size(), 5u);
        ASSERT_EQ(lot.capacity(), 5u);
        ASSERT_EQ(lot, (IL<s32>{1, 2, 3, 4, 5}));
    }
    {
        qc::Lot<s32> lot{1, 2};
        ASSERT_EQ(lot, (IL<s32>{1, 2}));
    }
    {
        qc::Lot<s32> lot{1};
        ASSERT_EQ(lot, (IL<s32>{1}));
    }
    {
        qc::Lot<s32> l1{1, 2, 3};
        ASSERT_EQ(l1.capacity(), 3u);
        ASSERT_EQ(l1.size(), 3u);
        ASSERT_EQ(l1, (IL<s32>{1, 2, 3}));
    }
    {
        qc::Lot<s32> l1{1, 2, 3};
        ASSERT_EQ(l1.capacity(), 3u);
        ASSERT_EQ(l1.size(), 3u);
        ASSERT_EQ(l1, (IL<s32>{1, 2, 3}));

        qc::Lot<s32> l2(std::move(l1));
        ASSERT_EQ(l2.capacity(), 3u);
        ASSERT_EQ(l2.size(), 3u);
        ASSERT_EQ(l2, (IL<s32>{1, 2, 3}));
        ASSERT_EQ(l1.capacity(), 0u);
        ASSERT_EQ(l1.size(), 0u);
    }
}

TEST(Lot, assignment)
{
    {
        qc::Lot<s32> l1{1, 2, 3};
        ASSERT_EQ(l1.size(), 3u);
        ASSERT_EQ(l1.capacity(), 3u);

        qc::Lot<s32> l2{};
        ASSERT_TRUE(l2.empty());

        l2 = std::move(l1);
        ASSERT_EQ(l2.size(), 3u);
        ASSERT_EQ(l2.capacity(), 3u);
        ASSERT_EQ(l2, (IL<s32>{1, 2, 3}));
        ASSERT_EQ(l1.size(), 0u);
        ASSERT_EQ(l1.capacity(), 0u);
    }
    {
        qc::Lot<s32> lot{9, 8, 7};

        lot = {1, 2, 3, 4};
        ASSERT_EQ(lot, (IL<s32>{1, 2, 3, 4}));

        std::vector<s32> vs{3, 2, 1};
        lot = std::span<s32>{vs.data(), vs.size()};
        ASSERT_EQ(lot, (IL<s32>{3, 2, 1}));
    }
}

TEST(Lot, operatorBool)
{
    qc::Lot<s32> lot{};
    ASSERT_FALSE(lot);

    lot.push(1);
    ASSERT_TRUE(lot);

    lot.clear();
    ASSERT_FALSE(lot);
}

TEST(Lot, assign)
{
    qc::Lot<s32> lot{9, 8, 7};

    lot.assign(6u, 3);
    ASSERT_EQ(lot, (IL<s32>{3, 3, 3, 3, 3, 3}));

    std::vector<s32> vs{3, 2, 1};
    lot.assign(vs.cbegin(), vs.cend());
    ASSERT_EQ(lot, (IL<s32>{3, 2, 1}));
}

TEST(Lot, reserve)
{
    qc::Lot<s32> lot{};
    ASSERT_EQ(lot.capacity(), 0u);
    ASSERT_TRUE(lot.empty());

    lot.reserve(0u);
    ASSERT_EQ(lot.capacity(), 0u);
    ASSERT_TRUE(lot.empty());

    lot.reserve(1u);
    ASSERT_EQ(lot.capacity(), 1u);
    ASSERT_TRUE(lot.empty());

    lot.reserve(0u);
    ASSERT_EQ(lot.capacity(), 1u);
    ASSERT_TRUE(lot.empty());

    lot.reserve(17u);
    ASSERT_EQ(lot.capacity(), 17u);
    ASSERT_TRUE(lot.empty());

    lot.reserve(4u);
    ASSERT_EQ(lot.capacity(), 17u);
    ASSERT_TRUE(lot.empty());
}

TEST(Lot, resize)
{
    qc::Lot<s32> lot{};
    ASSERT_EQ(lot.capacity(), 0u);
    ASSERT_EQ(lot.size(), 0u);

    lot.resize(3u);
    ASSERT_EQ(lot.capacity(), 3u);
    ASSERT_EQ(lot.size(), 3u);

    lot.resize(1u);
    *lot.begin() = 0;
    ASSERT_EQ(lot.capacity(), 3u);
    ASSERT_EQ(lot.size(), 1u);
    ASSERT_EQ(lot, (IL<s32>{0}));

    lot.resize(5u, 5);
    ASSERT_EQ(lot.capacity(), 5u);
    ASSERT_EQ(lot.size(), 5u);
    ASSERT_EQ(lot, (IL<s32>{0, 5, 5, 5, 5}));

    lot.resize(3u, 3);
    ASSERT_EQ(lot.capacity(), 5u);
    ASSERT_EQ(lot.size(), 3u);
    ASSERT_EQ(lot, (IL<s32>{0, 5, 5}));

    lot.resize(0u);
    ASSERT_EQ(lot.capacity(), 5u);
    ASSERT_EQ(lot.size(), 0u);
}

TEST(Lot, shrink)
{
    qc::Lot<s32> lot(8u);
    ASSERT_EQ(lot.capacity(), 8u);
    ASSERT_EQ(lot.size(), 8u);

    lot.reserve(10u);
    ASSERT_EQ(lot.capacity(), 10u);
    ASSERT_EQ(lot.size(), 8u);

    lot.shrink();
    ASSERT_EQ(lot.capacity(), 8u);
    ASSERT_EQ(lot.size(), 8u);

    lot.clear();
    ASSERT_EQ(lot.capacity(), 8u);
    ASSERT_EQ(lot.size(), 0u);

    lot.shrink();
    ASSERT_EQ(lot.capacity(), 0u);
    ASSERT_EQ(lot.size(), 0u);
}

TEST(Lot, clear)
{
    qc::Lot<s32> lot(14u);
    ASSERT_EQ(lot.capacity(), 14u);
    ASSERT_EQ(lot.size(), 14u);

    lot.clear();
    ASSERT_EQ(lot.capacity(), 14u);
    ASSERT_EQ(lot.size(), 0u);
}

TEST(Lot, push)
{
    {
        qc::Lot<s32> lot{};
        lot.push();
        ASSERT_EQ(lot.capacity(), 16u);
        ASSERT_EQ(lot.size(), 1u);
    }
    {
        qc::Lot<s32> lot{};
        ASSERT_EQ(lot.capacity(), 0u);
        ASSERT_EQ(lot.size(), 0u);

        ASSERT_EQ(lot.push(1), 1);
        ASSERT_EQ(lot.capacity(), 16u);
        ASSERT_EQ(lot.size(), 1u);
        ASSERT_EQ(lot, (IL<s32>{1}));

        ASSERT_EQ(lot.push(2), 2);
        ASSERT_EQ(lot.push(3), 3);
        ASSERT_EQ(lot.push(4), 4);
        ASSERT_EQ(lot.push(5), 5);
        ASSERT_EQ(lot.push(6), 6);
        ASSERT_EQ(lot.push(7), 7);
        ASSERT_EQ(lot.push(8), 8);
        ASSERT_EQ(lot.push(9), 9);
        ASSERT_EQ(lot.push(10), 10);
        ASSERT_EQ(lot.push(11), 11);
        ASSERT_EQ(lot.push(12), 12);
        ASSERT_EQ(lot.push(13), 13);
        ASSERT_EQ(lot.push(14), 14);
        ASSERT_EQ(lot.push(15), 15);
        ASSERT_EQ(lot.push(16), 16);
        ASSERT_EQ(lot.capacity(), 16u);
        ASSERT_EQ(lot.size(), 16u);
        ASSERT_EQ(lot, (IL<s32>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}));

        ASSERT_EQ(lot.push(17), 17);
        ASSERT_EQ(lot.capacity(), 32u);
        ASSERT_EQ(lot.size(), 17u);
        ASSERT_EQ(lot, (IL<s32>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17}));
    }
    {
        qc::Lot<s32> lot(3u);
        ASSERT_EQ(lot.capacity(), 3u);
        ASSERT_EQ(lot.size(), 3u);

        lot.push();
        ASSERT_EQ(lot.capacity(), 16u);
        ASSERT_EQ(lot.size(), 4u);
    }
    {
        qc::Lot<s32> lot(9u);
        ASSERT_EQ(lot.capacity(), 9u);
        ASSERT_EQ(lot.size(), 9u);

        lot.push();
        ASSERT_EQ(lot.capacity(), 18u);
        ASSERT_EQ(lot.size(), 10u);
    }
}

TEST(Lot, bump)
{
    qc::Lot<s32> lot{};
    ASSERT_EQ(lot.capacity(), 0u);
    ASSERT_EQ(lot.size(), 0u);

    lot.bump() = 1;
    ASSERT_EQ(lot.capacity(), 16u);
    ASSERT_EQ(lot.size(), 1u);
    ASSERT_EQ(lot, (IL<s32>{1}));

    lot.bump() = 2;
    ASSERT_EQ(lot.capacity(), 16u);
    ASSERT_EQ(lot.size(), 2u);
    ASSERT_EQ(lot, (IL<s32>{1, 2}));

    for (s32 & i : lot.bump(14u)) i = 3;
    ASSERT_EQ(lot.capacity(), 16u);
    ASSERT_EQ(lot.size(), 16u);
    ASSERT_EQ(lot, (IL<s32>{1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}));

    lot.bump(1u).front() = 4;
    ASSERT_EQ(lot.capacity(), 32u);
    ASSERT_EQ(lot.size(), 17u);
    ASSERT_EQ(lot, (IL<s32>{1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4}));
}

TEST(Lot, erase)
{
    {
        qc::Lot<s32> lot{1, 2, 3, 4, 5};
        ASSERT_EQ(lot.capacity(), 5u);
        ASSERT_EQ(lot.size(), 5u);
        ASSERT_EQ(lot, (IL<s32>{1, 2, 3, 4, 5}));

        s32 * it{lot.erase(lot.end() - 1)};
        ASSERT_EQ(it, lot.end());
        ASSERT_EQ(lot.capacity(), 5u);
        ASSERT_EQ(lot.size(), 4u);
        ASSERT_EQ(lot, (IL<s32>{1, 2, 3, 4}));

        ASSERT_EQ(*lot.erase(lot.begin() + 1), 4);
        ASSERT_EQ(lot.capacity(), 5u);
        ASSERT_EQ(lot.size(), 3u);
        ASSERT_EQ(lot, (IL<s32>{1, 4, 3}));

        ASSERT_EQ(*lot.erase(lot.begin()), 3);
        ASSERT_EQ(lot.capacity(), 5u);
        ASSERT_EQ(lot.size(), 2u);
        ASSERT_EQ(lot, (IL<s32>{3, 4}));

        ASSERT_EQ(*lot.erase(lot.begin()), 4);
        ASSERT_EQ(lot.capacity(), 5u);
        ASSERT_EQ(lot.size(), 1u);
        ASSERT_EQ(lot, (IL<s32>{4}));

        it = lot.erase(lot.begin());
        ASSERT_EQ(it, lot.end());
        ASSERT_EQ(lot.capacity(), 5u);
        ASSERT_EQ(lot.size(), 0u);
    }
    {
        qc::Lot<s32> lot{};
        ASSERT_EQ(lot.erase(7), 0u);
    }
    {
        qc::Lot<s32> lot{7};
        ASSERT_EQ(lot.erase(7), 1u);
        ASSERT_TRUE(lot.empty());
    }
    {
        qc::Lot<s32> lot{1, 2, 3, 4, 1, 2, 3, 1, 2, 1};
        ASSERT_EQ(lot.erase(2), 3u);
        ASSERT_EQ(lot, (IL<s32>{1, 1, 3, 4, 1, 1, 3}));
    }
    {
        qc::Lot<s32> lot{7, 7, 3, 7, 7};
        ASSERT_EQ(lot.erase(7), 4u);
        ASSERT_EQ(lot, (IL<s32>{3}));
    }
    {
        qc::Lot<s32> lot{1, 2, 3, 4, 5};
        ASSERT_EQ(lot.erase(7), 0u);
        ASSERT_EQ(lot, (IL<s32>{1, 2, 3, 4, 5}));
    }
}

TEST(Lot, eraseIf)
{
    qc::Lot<s32> lot{};

    ASSERT_EQ(lot.eraseIf([](s32) { return true; }), 0u);
    ASSERT_EQ(lot.capacity(), 0u);
    ASSERT_EQ(lot.size(), 0u);

    lot = {1, 2, 3, 4, 5};

    ASSERT_EQ(lot.eraseIf([](s32) { return false; }), 0u);
    ASSERT_EQ(lot.capacity(), 5u);
    ASSERT_EQ(lot.size(), 5u);
    ASSERT_EQ(lot, (IL<s32>{1, 2, 3, 4, 5}));

    ASSERT_EQ(lot.eraseIf([](s32) { return true; }), 5u);
    ASSERT_EQ(lot.capacity(), 5u);
    ASSERT_EQ(lot.size(), 0u);

    lot = {1, 2, 3, 4, 5};

    ASSERT_EQ(lot.eraseIf([](s32 v) { return v == 1; }), 1u);
    ASSERT_EQ(lot.capacity(), 5u);
    ASSERT_EQ(lot.size(), 4u);
    ASSERT_EQ(lot, (IL<s32>{5, 2, 3, 4}));

    ASSERT_EQ(lot.eraseIf([](s32 v) { return v == 5; }), 1u);
    ASSERT_EQ(lot.capacity(), 5u);
    ASSERT_EQ(lot.size(), 3u);
    ASSERT_EQ(lot, (IL<s32>{4, 2, 3}));

    ASSERT_EQ(lot.eraseIf([](s32 v) { return v == 3; }), 1u);
    ASSERT_EQ(lot.capacity(), 5u);
    ASSERT_EQ(lot.size(), 2u);
    ASSERT_EQ(lot, (IL<s32>{4, 2}));

    lot = {1, 2, 3, 4, 5};

    ASSERT_EQ(lot.eraseIf([](s32 v) { return v > 1 && v < 5; }), 3u);
    ASSERT_EQ(lot.capacity(), 5u);
    ASSERT_EQ(lot.size(), 2u);
    ASSERT_EQ(lot, (IL<s32>{1, 5}));

    lot = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    ASSERT_EQ(lot.eraseIf([](s32 v) { return v > 1 && v < 5; }), 6u);
    ASSERT_EQ(lot.capacity(), 10u);
    ASSERT_EQ(lot.size(), 4u);
    ASSERT_EQ(lot, (IL<s32>{1, 5, 1, 5}));

    lot = {1, 2, 3, 4, 5, 6, 7, 8};

    ASSERT_EQ(lot.eraseIf([](s32 v) { return v % 2 == 0; }), 4u);
    ASSERT_EQ(lot.capacity(), 10u);
    ASSERT_EQ(lot.size(), 4u);
    ASSERT_EQ(lot, (IL<s32>{1, 7, 3, 5}));

    lot = {1, 2, 3, 4, 5, 6, 7, 8};

    ASSERT_EQ(lot.eraseIf([](s32 v) { return v % 2 == 1; }), 4u);
    ASSERT_EQ(lot.capacity(), 10u);
    ASSERT_EQ(lot.size(), 4u);
    ASSERT_EQ(lot, (IL<s32>{8, 2, 6, 4}));
}

TEST(Lot, find)
{
    {
        qc::Lot<s32> lot{};
        ASSERT_EQ(lot.find(7), lot.end());
    }
    {
        qc::Lot<s32> lot{1};
        ASSERT_EQ(lot.find(7), lot.end());
    }
    {
        qc::Lot<s32> lot{7};
        ASSERT_EQ(lot.find(7), lot.begin());
    }
    {
        qc::Lot<s32> lot{1, 2, 3};
        ASSERT_EQ(lot.find(7), lot.end());
    }
    {
        qc::Lot<s32> lot{7, 2, 3};
        ASSERT_EQ(lot.find(7), lot.begin());
    }
    {
        qc::Lot<s32> lot{1, 7, 3};
        ASSERT_EQ(lot.find(7), lot.begin() + 1);
    }
    {
        qc::Lot<s32> lot{1, 2, 7};
        ASSERT_EQ(lot.find(7), lot.begin() + 2);
    }
    {
        qc::Lot<s32> lot{7, 7, 7};
        ASSERT_EQ(lot.find(7), lot.begin());
    }
}

TEST(Lot, findIf)
{
    {
        qc::Lot<s32> lot{};
        ASSERT_EQ(lot.findIf([](s32) { return true; }), lot.end());
    }
    {
        qc::Lot<s32> lot{1, 2, 3};
        ASSERT_EQ(lot.findIf([](s32) { return true; }), lot.begin());
    }
    {
        qc::Lot<s32> lot{7};
        ASSERT_EQ(lot.findIf([](s32 v) { return v % 2 == 0; }), lot.end());
    }
    {
        qc::Lot<s32> lot{1, 2, 3};
        ASSERT_EQ(lot.findIf([](s32 v) { return v % 2 == 0; }), lot.begin() + 1);
    }
    {
        qc::Lot<s32> lot{1, 2, 3};
        ASSERT_EQ(lot.findIf([](s32) { return false; }), lot.end());
    }
}

TEST(Lot, count)
{
    {
        qc::Lot<s32> lot{};
        ASSERT_EQ(lot.count(7), 0u);
    }
    {
        qc::Lot<s32> lot{1};
        ASSERT_EQ(lot.count(7), 0u);
    }
    {
        qc::Lot<s32> lot{7};
        ASSERT_EQ(lot.count(7), 1u);
    }
    {
        qc::Lot<s32> lot{1, 2, 3};
        ASSERT_EQ(lot.count(7), 0u);
    }
    {
        qc::Lot<s32> lot{7, 2, 3};
        ASSERT_EQ(lot.count(7), 1u);
    }
    {
        qc::Lot<s32> lot{1, 7, 3};
        ASSERT_EQ(lot.count(7), 1u);
    }
    {
        qc::Lot<s32> lot{1, 2, 7};
        ASSERT_EQ(lot.count(7), 1u);
    }
    {
        qc::Lot<s32> lot{7, 7, 7};
        ASSERT_EQ(lot.count(7), 3u);
    }
}

TEST(Lot, countIf)
{
    {
        qc::Lot<s32> lot{};
        ASSERT_EQ(lot.countIf([](s32) { return true; }), 0u);
    }
    {
        qc::Lot<s32> lot{1, 2, 3};
        ASSERT_EQ(lot.countIf([](s32) { return true; }), 3u);
    }
    {
        qc::Lot<s32> lot{7};
        ASSERT_EQ(lot.countIf([](s32 v) { return v % 2 == 0; }), 0u);
    }
    {
        qc::Lot<s32> lot{1, 2, 3};
        ASSERT_EQ(lot.countIf([](s32 v) { return v % 2 == 0; }), 1u);
    }
    {
        qc::Lot<s32> lot{1, 2, 3};
        ASSERT_EQ(lot.countIf([](s32) { return false; }), 0u);
    }
}

TEST(Lot, contains)
{
    {
        qc::Lot<s32> lot{5};
        ASSERT_FALSE(lot.contains(7));
    }
    {
        qc::Lot<s32> lot{7};
        ASSERT_TRUE(lot.contains(7));
    }
}

TEST(Lot, containsIf)
{
    {
        qc::Lot<s32> lot{7};
        ASSERT_FALSE(lot.containsIf([](s32 v) { return v % 2 == 0; }));
    }
    {
        qc::Lot<s32> lot{8};
        ASSERT_TRUE(lot.containsIf([](s32 v) { return v % 2 == 0; }));
    }
}

TEST(Lot, data)
{
    {
        qc::Lot<s32> lot{};
        ASSERT_EQ(lot.data(), nullptr);
    }
    {
        qc::Lot<s32> lot{1, 2, 3};
        s32 * data{lot.data()};
        ASSERT_EQ(1, data[0]);
        ASSERT_EQ(2, data[1]);
        ASSERT_EQ(3, data[2]);
    }
}

TEST(Lot, iteration)
{
    qc::Lot<s32> lot{1, 2, 3};

    auto it{lot.begin()};
    ASSERT_NE(it, lot.end());
    ASSERT_EQ(*it, 1);

    ++it;
    ASSERT_NE(it, lot.end());
    ASSERT_EQ(*it, 2);

    ++it;
    ASSERT_NE(it, lot.end());
    ASSERT_EQ(*it, 3);

    ++it;
    ASSERT_EQ(it, lot.end());

    s32 expected{1};
    for (const s32 i : lot)
    {
        ASSERT_EQ(i, expected);
        ++expected;
    }
}

TEST(Lot, equality)
{
    qc::Lot<s32> l1{1, 2, 3};
    qc::Lot<s32> l2{1, 2, 3};
    qc::Lot<s32> l3{1, 2};
    qc::Lot<s32> l4{};

    ASSERT_EQ(l1, l1);
    ASSERT_EQ(l1, l2);
    ASSERT_NE(l1, l3);
    ASSERT_NE(l1, l4);
    ASSERT_EQ(l4, l4);
}
