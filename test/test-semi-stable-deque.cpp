#include <qc-core/random.hpp>
#include <qc-core/semi-stable-deque.hpp>

#include <deque>

#include <gtest/gtest.h>

using namespace qc::types;
using namespace qc::primitives;

template <typename T> using Deque = qc::SemiStableDeque<T>;

TEST(SemiStableDeque, general)
{
    Deque<int> deque{};
    ASSERT_EQ(0u, deque.size());
    ASSERT_TRUE(deque.empty());
    ASSERT_EQ(deque.begin(), deque.end());
    ASSERT_EQ(0u, deque.capacity());

    ASSERT_EQ(0u, deque.push_back(1).i);
    ASSERT_EQ(1, deque.back());
    ASSERT_EQ(1u, deque.size());
    ASSERT_EQ(16u, deque.capacity());

    // 1
    // 1, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _

    ASSERT_EQ(1u, deque.push_front(-1).i);
    ASSERT_EQ(-1, deque.front());
    ASSERT_EQ(2u, deque.size());
    ASSERT_EQ(16u, deque.capacity());

    // -1, 1
    // 1, -1, _, _, _, _, _, _, _, _, _, _, _, _, _, _

    for (int i{2}; i <= 8; ++i)
    {
        ASSERT_EQ(2 * i - 2, deque.push_back(i).i);
        ASSERT_EQ(i, deque.back());
        ASSERT_EQ(2 * i - 1, deque.size());
        ASSERT_EQ(16u, deque.capacity());

        ASSERT_EQ(2 * i - 1, deque.push_front(-i).i);
        ASSERT_EQ(-i, deque.front());
        ASSERT_EQ(2 * i, deque.size());
        ASSERT_EQ(16u, deque.capacity());
    }

    // -8, -7, -6, -5, -4, -3, -2, -1, 1, 2, 3, 4, 5, 6, 7, 8
    // 1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8, -8

    int expectedV{-8};
    for (const int v : deque)
    {
        ASSERT_EQ(expectedV, v);
        ++expectedV;
        if (expectedV == 0) ++expectedV;
    }

    expectedV = 1;
    for (u32 slotI{0u}; slotI < 16u; ++slotI)
    {
        ASSERT_EQ(expectedV, deque[slotI]);
        if (expectedV < 0) --expectedV;
        expectedV = -expectedV;
    }

    deque.push_back(0);
    ASSERT_EQ(0, deque.back());
    ASSERT_EQ(17u, deque.size());
    ASSERT_EQ(32u, deque.capacity());

    // -8, -7, -6, -5, -4, -3, -2, -1, 1, 2, 3, 4, 5, 6, 7, 8, 0
    // 1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8, -8, 0

    expectedV = -8;
    for (const int v : deque)
    {
        ASSERT_EQ(expectedV, v);
        ++expectedV;
        if (expectedV == 0) ++expectedV;
        if (expectedV == 9) expectedV = 0;
    }

    expectedV = 1;
    for (u32 slotI{0u}; slotI < 17u; ++slotI)
    {
        ASSERT_EQ(expectedV, deque[slotI]);
        if (expectedV < 0) --expectedV;
        expectedV = -expectedV;
        if (expectedV == 9) expectedV = 0;
    }

    deque.pop_back();
    ASSERT_EQ(16u, deque.size());
    ASSERT_EQ(32u, deque.capacity());

    // -8, -7, -6, -5, -4, -3, -2, -1, 1, 2, 3, 4, 5, 6, 7, 8
    // 1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8, -8

    for (int i{1}; i <= 7; i += 2)
    {
        deque.pop(uint(2 * i - 2));
        deque.pop(uint(2 * i - 1));
    }
    ASSERT_EQ(8u, deque.size());
    ASSERT_EQ(32u, deque.capacity());

    // -8, -6, -4, -2, 2, 4, 6, 8
    // _, _, 2, -2, _, _, 4, -4, _, _, 6, -6, _, _, 8, -8

    expectedV = -8;
    for (const int v : deque)
    {
        ASSERT_EQ(expectedV, v);
        expectedV += 2;
        if (expectedV == 0) expectedV = 2;
    }

    expectedV = 2;
    for (u32 slotI{2u}; slotI < 16u; slotI += 4)
    {
        ASSERT_EQ(expectedV, deque[slotI]);
        ASSERT_EQ(-expectedV, deque[slotI + 1u]);
        expectedV += 2;
    }

    for (int i{7}; i >= 1; i -= 2)
    {
        ASSERT_EQ(2 * i - 1, deque.push_front(-i).i);
        ASSERT_EQ(-i, deque.front());

        ASSERT_EQ(2 * i - 2, deque.push_back(i).i);
        ASSERT_EQ(i, deque.back());
    }
    ASSERT_EQ(16u, deque.size());
    ASSERT_EQ(32u, deque.capacity());

    // -1, -3, -5, -7, -8, -6, -4, -2, 2, 4, 6, 8, 7, 5, 3, 1
    // 1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8, -8

    expectedV = -1;
    for (const int v : deque)
    {
        ASSERT_EQ(expectedV, v);
        if (expectedV % 2) expectedV -= 2;
        else expectedV += 2;
        if (expectedV == -9) expectedV = -8;
        if (expectedV == 0) expectedV = 2;
        if (expectedV == 10) expectedV = 7;
    }

    expectedV = 1;
    for (u32 slotI{0u}; slotI < 16u; ++slotI)
    {
        ASSERT_EQ(expectedV, deque[slotI]);
        if (expectedV < 0) --expectedV;
        expectedV = -expectedV;
    }

    deque.clear();
    ASSERT_EQ(0u, deque.size());
    ASSERT_EQ(32u, deque.capacity());

    for (int i{0}; i < int(deque.capacity()); ++i)
    {
        const auto [newV, newI]{deque.push_back(i)};
        ASSERT_EQ(newV, i);
        ASSERT_EQ(newI, i);
    }
    ASSERT_EQ(32u, deque.size());
    ASSERT_EQ(32u, deque.capacity());

    deque.clear();
    ASSERT_EQ(0u, deque.size());
    ASSERT_EQ(32u, deque.capacity());
}

TEST(SemiStableDeque, iteratorAssignability)
{
    static_assert(std::is_assignable_v<Deque<int>::iterator, Deque<int>::iterator>);
    static_assert(std::is_assignable_v<Deque<int>::const_iterator, Deque<int>::iterator>);
    static_assert(!std::is_assignable_v<Deque<int>::iterator, Deque<int>::const_iterator>);
    static_assert(std::is_assignable_v<Deque<int>::const_iterator, Deque<int>::const_iterator>);

    static_assert(std::is_assignable_v<Deque<int>::reverse_iterator, Deque<int>::reverse_iterator>);
    static_assert(std::is_assignable_v<Deque<int>::const_reverse_iterator, Deque<int>::reverse_iterator>);
    static_assert(!std::is_assignable_v<Deque<int>::reverse_iterator, Deque<int>::const_reverse_iterator>);
    static_assert(std::is_assignable_v<Deque<int>::const_reverse_iterator, Deque<int>::const_reverse_iterator>);

    static_assert(!std::is_assignable_v<Deque<int>::iterator, Deque<int>::reverse_iterator>);
    static_assert(!std::is_assignable_v<Deque<int>::const_iterator, Deque<int>::reverse_iterator>);
    static_assert(!std::is_assignable_v<Deque<int>::iterator, Deque<int>::const_reverse_iterator>);
    static_assert(!std::is_assignable_v<Deque<int>::const_iterator, Deque<int>::const_reverse_iterator>);
}

TEST(SemiStableDeque, stress)
{
    const u32 iterations{250u};
    const u32 minSize{100u};
    const u32 maxSize{1000u};

    for (u32 iteration{0u}; iteration < iterations; ++iteration)
    {
        qc::Random random{};
        const u32 size{random.next<u32>(minSize, maxSize + 1u)};

        std::deque<int> stdDeque{};
        Deque<int> deque{};

        while (stdDeque.size() < size)
        {
            const bool add{stdDeque.empty() || random.next<u32>(3u)};
            if (add)
            {
                const int v{random.next<int>(1000)};
                if (random.next<bool>())
                {
                    stdDeque.push_back(v);
                    deque.push_back(v);
                }
                else
                {
                    stdDeque.push_front(v);
                    deque.push_front(v);
                }
            }
            else
            {
                const u32 eraseI{random.next<u32>(u32(stdDeque.size()))};
                stdDeque.erase(stdDeque.begin() + s64(eraseI));
                auto it{deque.begin()};
                for (u32 i{0u}; i < eraseI; ++i, ++it);
                deque.pop(it);
            }

            ASSERT_EQ(stdDeque.size(), deque.size());
        }

        {
            auto stdIt{stdDeque.cbegin()};
            auto it{deque.cbegin()};
            for (; stdIt != stdDeque.cend(); ++stdIt, ++it)
            {
                ASSERT_EQ(*stdIt, *it);
            }
        }

        {
            auto stdIt{stdDeque.crbegin()};
            auto it{deque.crbegin()};
            for (; stdIt != stdDeque.crend(); ++stdIt, ++it)
            {
                ASSERT_EQ(*stdIt, *it);
            }
        }

        while (!stdDeque.empty())
        {
            const u32 eraseI{random.next<u32>(u32(stdDeque.size()))};
            const auto stdIt{stdDeque.begin() + s64(eraseI)};
            auto it{deque.begin()};
            for (u32 i{0u}; i < eraseI; ++i, ++it);

            ASSERT_EQ(*stdIt, *it);

            stdDeque.erase(stdDeque.begin() + s64(eraseI));
            deque.pop(it);

            ASSERT_EQ(stdDeque.size(), deque.size());
        }
    }
}
