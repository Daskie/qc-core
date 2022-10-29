#include <qc-core/ring-deque.hpp>

#include <deque>

#include <gtest/gtest.h>

#include <qc-core/random.hpp>

using namespace qc::types;
template <typename T> using Deque = qc::RingDeque<T>;

TEST(SemiStableDeque, general)
{
    Deque<int> deque{};
    ASSERT_EQ(0u, deque.size());
    ASSERT_TRUE(deque.empty());
    ASSERT_EQ(deque.begin(), deque.end());
    ASSERT_EQ(0u, deque.capacity());

    ASSERT_EQ(0, deque.push_back(0));
    ASSERT_EQ(0, deque.back());
    ASSERT_EQ(0, deque.front());
    ASSERT_EQ(1u, deque.size());
    ASSERT_FALSE(deque.empty());
    ASSERT_EQ(16u, deque.capacity());

    deque.pop_back();
    ASSERT_EQ(0u, deque.size());
    ASSERT_EQ(16u, deque.capacity());

    ASSERT_EQ(1, deque.push_front(1));
    ASSERT_EQ(1, deque.back());
    ASSERT_EQ(1, deque.front());
    ASSERT_EQ(1u, deque.size());
    ASSERT_EQ(16u, deque.capacity());

    deque.pop_front();
    ASSERT_EQ(0u, deque.size());

    ASSERT_EQ(2, deque.push_back(2));
    ASSERT_EQ(2, deque.back());
    ASSERT_EQ(2, deque.front());
    ASSERT_EQ(1u, deque.size());
    ASSERT_EQ(16u, deque.capacity());

    deque.pop_front();
    ASSERT_EQ(0u, deque.size());

    ASSERT_EQ(3, deque.push_front(3));
    ASSERT_EQ(3, deque.back());
    ASSERT_EQ(3, deque.front());
    ASSERT_EQ(1u, deque.size());
    ASSERT_EQ(16u, deque.capacity());

    deque.pop_back();
    ASSERT_EQ(0u, deque.size());

    for (int i{0}; i < 16; ++i)
    {
        deque.push_back(i);
    }
    ASSERT_EQ(16u, deque.size());
    ASSERT_EQ(16u, deque.capacity());
    int expected{0};
    for (int v : deque)
    {
        ASSERT_EQ(expected, v);
        ++expected;
    }

    deque.push_front(-1);
    ASSERT_EQ(17u, deque.size());
    ASSERT_EQ(32u, deque.capacity());

    for (int i{-2}; i >= -16; --i)
    {
        deque.push_front(i);
    }
    ASSERT_EQ(32u, deque.size());
    ASSERT_EQ(32u, deque.capacity());
    expected = -16;
    for (int v : deque)
    {
        ASSERT_EQ(expected, v);
        ++expected;
    }

    deque.clear();
    ASSERT_EQ(0u, deque.size());
    ASSERT_EQ(32u, deque.capacity());

    for (int i{0}; i < 32; ++i)
    {
        ASSERT_EQ(i, deque.push_back(i));
        ASSERT_EQ(i + 1, deque.size());
    }

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
                if (random.next<bool>())
                {
                    stdDeque.pop_back();
                    deque.pop_back();
                }
                else
                {
                    stdDeque.pop_front();
                    deque.pop_front();
                }
            }

            ASSERT_EQ(stdDeque.size(), deque.size());
            if (!stdDeque.empty())
            {
                ASSERT_EQ(stdDeque.back(), deque.back());
                ASSERT_EQ(stdDeque.front(), deque.front());
            }
        }

        {
            auto stdIt{stdDeque.cbegin()};
            auto it{deque.cbegin()};
            for (; stdIt != stdDeque.cend(); ++stdIt, ++it)
            {
                ASSERT_EQ(*stdIt, *it);
            }
        }

        while (!stdDeque.empty())
        {
            if (random.next<bool>())
            {
                stdDeque.pop_back();
                deque.pop_back();
            }
            else
            {
                stdDeque.pop_front();
                deque.pop_front();

            }

            ASSERT_EQ(stdDeque.size(), deque.size());
            if (!stdDeque.empty())
            {
                ASSERT_EQ(stdDeque.size(), deque.size());
                ASSERT_EQ(stdDeque.back(), deque.back());
                ASSERT_EQ(stdDeque.front(), deque.front());
            }
        }
    }
}