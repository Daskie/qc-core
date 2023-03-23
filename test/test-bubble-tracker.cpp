#include <qc-core/bubble-tracker.hpp>

#include <gtest/gtest.h>

using namespace qc::types;
using namespace qc::primitives;

TEST(BubbleTracker, empty)
{
    qc::BubbleTracker<u32> bubbles{};
    ASSERT_TRUE(bubbles.bubbles().empty());

    ASSERT_FALSE(bubbles.remove(0u).first);
    ASSERT_FALSE(bubbles.remove(1u).first);
}

TEST(BubbleTracker, single)
{
    qc::BubbleTracker<u32> bubbles{};

    bubbles.add(0u, 1u);
    ASSERT_EQ(1u, bubbles.bubbles().size());
    ASSERT_EQ(0u, bubbles.bubbles().front().pos);
    ASSERT_EQ(1u, bubbles.bubbles().front().size);

    ASSERT_FALSE(bubbles.remove(0u).first);
    ASSERT_FALSE(bubbles.remove(2u).first);
    ASSERT_EQ((std::pair<bool, u32>{true, 0u}), bubbles.remove(1u));
    ASSERT_TRUE(bubbles.bubbles().empty());
}

TEST(BubbleTracker, adjacent)
{
    qc::BubbleTracker<u32> bubbles{};

    bubbles.add(1u, 1u);
    bubbles.add(2u, 1u);
    ASSERT_EQ(1u, bubbles.bubbles().size());
    bubbles.add(0u, 1u);
    ASSERT_EQ(1u, bubbles.bubbles().size());
    ASSERT_EQ(0u, bubbles.bubbles().front().pos);
    ASSERT_EQ(3u, bubbles.bubbles().front().size);

    ASSERT_EQ((std::pair<bool, u32>{true, 0u}), bubbles.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 1u}), bubbles.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 2u}), bubbles.remove(1u));
    ASSERT_TRUE(bubbles.bubbles().empty());
}

TEST(BubbleTracker, gapFill)
{
    qc::BubbleTracker<u32> bubbles{};

    bubbles.add(0u, 1u);
    bubbles.add(2u, 1u);
    ASSERT_EQ(2u, bubbles.bubbles().size());
    ASSERT_EQ(0u, bubbles.bubbles().front().pos);
    ASSERT_EQ(1u, bubbles.bubbles().front().size);
    ASSERT_EQ(2u, bubbles.bubbles().back().pos);
    ASSERT_EQ(1u, bubbles.bubbles().back().size);
    bubbles.add(1u, 1u);
    ASSERT_EQ(1u, bubbles.bubbles().size());
    ASSERT_EQ(0u, bubbles.bubbles().front().pos);
    ASSERT_EQ(3u, bubbles.bubbles().front().size);

    ASSERT_EQ((std::pair<bool, u32>{true, 0u}), bubbles.remove(3u));
    ASSERT_TRUE(bubbles.bubbles().empty());
}

TEST(BubbleTracker, separate)
{
    qc::BubbleTracker<u32> bubbles{};

    bubbles.add(0u, 1u);
    bubbles.add(2u, 2u);
    bubbles.add(5u, 3u);
    ASSERT_EQ(3u, bubbles.bubbles().size());

    ASSERT_EQ((std::pair<bool, u32>{true, 5u}), bubbles.remove(3u));
    ASSERT_EQ((std::pair<bool, u32>{true, 2u}), bubbles.remove(2u));
    ASSERT_EQ((std::pair<bool, u32>{true, 0u}), bubbles.remove(1u));
    ASSERT_TRUE(bubbles.bubbles().empty());

    bubbles.add(0u, 3u);
    bubbles.add(4u, 2u);
    bubbles.add(7u, 1u);
    ASSERT_EQ(3u, bubbles.bubbles().size());

    ASSERT_EQ((std::pair<bool, u32>{true, 7u}), bubbles.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 4u}), bubbles.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 5u}), bubbles.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 0u}), bubbles.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 1u}), bubbles.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 2u}), bubbles.remove(1u));
    ASSERT_TRUE(bubbles.bubbles().empty());

    bubbles.add(0u, 2u);
    bubbles.add(3u, 2u);
    ASSERT_EQ(2u, bubbles.bubbles().size());

    ASSERT_EQ((std::pair<bool, u32>{true, 0u}), bubbles.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 1u}), bubbles.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 3u}), bubbles.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 4u}), bubbles.remove(1u));
    ASSERT_TRUE(bubbles.bubbles().empty());
}

TEST(BubbleTracker, addZero)
{
    qc::BubbleTracker<s32> bubbles{};

    bubbles.add(0, 0);
    ASSERT_TRUE(bubbles.bubbles().empty());

    bubbles.add(0, -1);
    ASSERT_TRUE(bubbles.bubbles().empty());
}

TEST(BubbleTracker, removeZero)
{
    qc::BubbleTracker<u32> bubbles{};

    ASSERT_FALSE(bubbles.remove(0u).first);

    bubbles.add(0u, 1u);
    ASSERT_FALSE(bubbles.remove(0u).first);
}

TEST(BubbleTracker, removeTooLarge)
{
    qc::BubbleTracker<u32> bubbles{};

    bubbles.add(0u, 1u);
    ASSERT_FALSE(bubbles.remove(2u).first);
}

TEST(BubbleTracker, addOverlap)
{
    qc::BubbleTracker<u32> bubbles{};

    bubbles.add(2u, 1u);
    ASSERT_EQ(1u, bubbles.bubbles().size());

    bubbles.add(2u, 1u);
    ASSERT_EQ(1u, bubbles.bubbles().size());
    ASSERT_EQ(2u, bubbles.bubbles().front().pos);
    ASSERT_EQ(1u, bubbles.bubbles().front().size);

    bubbles.add(1u, 2u);
    ASSERT_EQ(1u, bubbles.bubbles().size());
    ASSERT_EQ(1u, bubbles.bubbles().front().pos);
    ASSERT_EQ(2u, bubbles.bubbles().front().size);

    bubbles.add(2u, 2u);
    ASSERT_EQ(1u, bubbles.bubbles().size());
    ASSERT_EQ(1u, bubbles.bubbles().front().pos);
    ASSERT_EQ(3u, bubbles.bubbles().front().size);

    bubbles.add(0u, 2u);
    ASSERT_EQ(1u, bubbles.bubbles().size());
    ASSERT_EQ(0u, bubbles.bubbles().front().pos);
    ASSERT_EQ(4u, bubbles.bubbles().front().size);

    bubbles.add(3u, 2u);
    ASSERT_EQ(1u, bubbles.bubbles().size());
    ASSERT_EQ(0u, bubbles.bubbles().front().pos);
    ASSERT_EQ(5u, bubbles.bubbles().front().size);
}

TEST(BubbleTracker, signedInteger)
{
    qc::BubbleTracker<s32> bubbles{};

    bubbles.add(1, 1);
    bubbles.add(3, 1);
    ASSERT_EQ(2u, bubbles.bubbles().size());

    bubbles.add(2, 1);
    ASSERT_EQ(1u, bubbles.bubbles().size());

    bubbles.add(0, 1);
    bubbles.add(4, 1);
    ASSERT_EQ(1u, bubbles.bubbles().size());

    bubbles.add(6, 2);
    ASSERT_EQ(2u, bubbles.bubbles().size());

    ASSERT_EQ(0, bubbles.bubbles().front().pos);
    ASSERT_EQ(5, bubbles.bubbles().front().size);
    ASSERT_EQ(6, bubbles.bubbles().back().pos);
    ASSERT_EQ(2, bubbles.bubbles().back().size);

    ASSERT_EQ((std::pair<bool, s32>{true, 6}), bubbles.remove(1));
    ASSERT_EQ((std::pair<bool, s32>{true, 7}), bubbles.remove(1));
    ASSERT_EQ((std::pair<bool, s32>{true, 0}), bubbles.remove(5));
    ASSERT_TRUE(bubbles.bubbles().empty());
}

TEST(BubbleTracker, pointer)
{
    s32 * p{};

    qc::BubbleTracker<s32 *> bubbles{};

    bubbles.add(p + 1, 1);
    bubbles.add(p + 3, 1);
    ASSERT_EQ(2u, bubbles.bubbles().size());

    bubbles.add(p + 2, 1);
    ASSERT_EQ(1u, bubbles.bubbles().size());

    bubbles.add(p + 0, 1);
    bubbles.add(p + 4, 1);
    ASSERT_EQ(1u, bubbles.bubbles().size());

    bubbles.add(p + 6, 2);
    ASSERT_EQ(2u, bubbles.bubbles().size());

    ASSERT_EQ(p + 0, bubbles.bubbles().front().pos);
    ASSERT_EQ(5, bubbles.bubbles().front().size);
    ASSERT_EQ(p + 6, bubbles.bubbles().back().pos);
    ASSERT_EQ(2, bubbles.bubbles().back().size);

    ASSERT_EQ((std::pair<bool, s32 *>{true, p + 6}), bubbles.remove(1));
    ASSERT_EQ((std::pair<bool, s32 *>{true, p + 7}), bubbles.remove(1));
    ASSERT_EQ((std::pair<bool, s32 *>{true, p + 0}), bubbles.remove(5));
    ASSERT_TRUE(bubbles.bubbles().empty());
}

TEST(BubbleTracker, tail)
{
    qc::BubbleTracker<u32> bubbles{};
    ASSERT_EQ(0u, bubbles.tail(0u));
    ASSERT_EQ(0u, bubbles.tail(1u));

    bubbles.add(0u, 1u);
    ASSERT_EQ(0u, bubbles.tail(0u));
    ASSERT_EQ(1u, bubbles.tail(1u));
    ASSERT_EQ(0u, bubbles.tail(2u));

    bubbles.add(2u, 3u);
    ASSERT_EQ(0u, bubbles.tail(0u));
    ASSERT_EQ(0u, bubbles.tail(1u));
    ASSERT_EQ(0u, bubbles.tail(2u));
    ASSERT_EQ(1u, bubbles.tail(3u));
    ASSERT_EQ(2u, bubbles.tail(4u));
    ASSERT_EQ(3u, bubbles.tail(5u));
    ASSERT_EQ(0u, bubbles.tail(6u));
}
