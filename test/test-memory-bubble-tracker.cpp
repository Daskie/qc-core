#include <qc-core/memory-bubble-tracker.hpp>

#include <gtest/gtest.h>

using namespace qc::types;

TEST(MemoryBubbleTracker, empty)
{
    qc::MemoryBubbleTracker<u32> mbt{};
    ASSERT_TRUE(mbt.bubbles().empty());

    ASSERT_FALSE(mbt.remove(0u).first);
    ASSERT_FALSE(mbt.remove(1u).first);
}

TEST(MemoryBubbleTracker, single)
{
    qc::MemoryBubbleTracker<u32> mbt{};

    mbt.add(0u, 1u);
    ASSERT_EQ(1u, mbt.bubbles().size());
    ASSERT_EQ(0u, mbt.bubbles().front().pos);
    ASSERT_EQ(1u, mbt.bubbles().front().size);

    ASSERT_FALSE(mbt.remove(0u).first);
    ASSERT_FALSE(mbt.remove(2u).first);
    ASSERT_EQ((std::pair<bool, u32>{true, 0u}), mbt.remove(1u));
    ASSERT_TRUE(mbt.bubbles().empty());
}

TEST(MemoryBubbleTracker, adjacent)
{
    qc::MemoryBubbleTracker<u32> mbt{};

    mbt.add(1u, 1u);
    mbt.add(2u, 1u);
    ASSERT_EQ(1u, mbt.bubbles().size());
    mbt.add(0u, 1u);
    ASSERT_EQ(1u, mbt.bubbles().size());
    ASSERT_EQ(0u, mbt.bubbles().front().pos);
    ASSERT_EQ(3u, mbt.bubbles().front().size);

    ASSERT_EQ((std::pair<bool, u32>{true, 0u}), mbt.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 1u}), mbt.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 2u}), mbt.remove(1u));
    ASSERT_TRUE(mbt.bubbles().empty());
}

TEST(MemoryBubbleTracker, gapFill)
{
    qc::MemoryBubbleTracker<u32> mbt{};

    mbt.add(0u, 1u);
    mbt.add(2u, 1u);
    ASSERT_EQ(2u, mbt.bubbles().size());
    ASSERT_EQ(0u, mbt.bubbles().front().pos);
    ASSERT_EQ(1u, mbt.bubbles().front().size);
    ASSERT_EQ(2u, mbt.bubbles().back().pos);
    ASSERT_EQ(1u, mbt.bubbles().back().size);
    mbt.add(1u, 1u);
    ASSERT_EQ(1u, mbt.bubbles().size());
    ASSERT_EQ(0u, mbt.bubbles().front().pos);
    ASSERT_EQ(3u, mbt.bubbles().front().size);

    ASSERT_EQ((std::pair<bool, u32>{true, 0u}), mbt.remove(3u));
    ASSERT_TRUE(mbt.bubbles().empty());
}

TEST(MemoryBubbleTracker, separate)
{
    qc::MemoryBubbleTracker<u32> mbt{};

    mbt.add(0u, 1u);
    mbt.add(2u, 2u);
    mbt.add(5u, 3u);
    ASSERT_EQ(3u, mbt.bubbles().size());

    ASSERT_EQ((std::pair<bool, u32>{true, 5u}), mbt.remove(3u));
    ASSERT_EQ((std::pair<bool, u32>{true, 2u}), mbt.remove(2u));
    ASSERT_EQ((std::pair<bool, u32>{true, 0u}), mbt.remove(1u));
    ASSERT_TRUE(mbt.bubbles().empty());

    mbt.add(0u, 3u);
    mbt.add(4u, 2u);
    mbt.add(7u, 1u);
    ASSERT_EQ(3u, mbt.bubbles().size());

    ASSERT_EQ((std::pair<bool, u32>{true, 7u}), mbt.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 4u}), mbt.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 5u}), mbt.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 0u}), mbt.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 1u}), mbt.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 2u}), mbt.remove(1u));
    ASSERT_TRUE(mbt.bubbles().empty());

    mbt.add(0u, 2u);
    mbt.add(3u, 2u);
    ASSERT_EQ(2u, mbt.bubbles().size());

    ASSERT_EQ((std::pair<bool, u32>{true, 0u}), mbt.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 1u}), mbt.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 3u}), mbt.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 4u}), mbt.remove(1u));
    ASSERT_TRUE(mbt.bubbles().empty());
}

TEST(MemoryBubbleTracker, removeZero)
{
    qc::MemoryBubbleTracker<u32> mbt{};

    ASSERT_FALSE(mbt.remove(0u).first);

    mbt.add(0u, 1u);
    ASSERT_FALSE(mbt.remove(0u).first);
}

TEST(MemoryBubbleTracker, removeTooLarge)
{
    qc::MemoryBubbleTracker<u32> mbt{};

    mbt.add(0u, 1u);
    ASSERT_FALSE(mbt.remove(2u).first);
}

TEST(MemoryBubbleTracker, addOverlap)
{
    qc::MemoryBubbleTracker<u32> mbt{};

    mbt.add(2u, 1u);
    ASSERT_EQ(1u, mbt.bubbles().size());

    mbt.add(2u, 1u);
    ASSERT_EQ(1u, mbt.bubbles().size());
    ASSERT_EQ(2u, mbt.bubbles().front().pos);
    ASSERT_EQ(1u, mbt.bubbles().front().size);

    mbt.add(1u, 2u);
    ASSERT_EQ(1u, mbt.bubbles().size());
    ASSERT_EQ(1u, mbt.bubbles().front().pos);
    ASSERT_EQ(2u, mbt.bubbles().front().size);

    mbt.add(2u, 2u);
    ASSERT_EQ(1u, mbt.bubbles().size());
    ASSERT_EQ(1u, mbt.bubbles().front().pos);
    ASSERT_EQ(3u, mbt.bubbles().front().size);

    mbt.add(0u, 2u);
    ASSERT_EQ(1u, mbt.bubbles().size());
    ASSERT_EQ(0u, mbt.bubbles().front().pos);
    ASSERT_EQ(4u, mbt.bubbles().front().size);

    mbt.add(3u, 2u);
    ASSERT_EQ(1u, mbt.bubbles().size());
    ASSERT_EQ(0u, mbt.bubbles().front().pos);
    ASSERT_EQ(5u, mbt.bubbles().front().size);
}

TEST(MemoryBubbleTracker, signedInteger)
{
    qc::MemoryBubbleTracker<s32> mbt{};

    mbt.add(1, 1);
    mbt.add(3, 1);
    ASSERT_EQ(2u, mbt.bubbles().size());

    mbt.add(2, 1);
    ASSERT_EQ(1u, mbt.bubbles().size());

    mbt.add(0, 1);
    mbt.add(4, 1);
    ASSERT_EQ(1u, mbt.bubbles().size());

    mbt.add(6, 2);
    ASSERT_EQ(2u, mbt.bubbles().size());

    ASSERT_EQ(0, mbt.bubbles().front().pos);
    ASSERT_EQ(5, mbt.bubbles().front().size);
    ASSERT_EQ(6, mbt.bubbles().back().pos);
    ASSERT_EQ(2, mbt.bubbles().back().size);

    ASSERT_EQ((std::pair<bool, s32>{true, 6}), mbt.remove(1));
    ASSERT_EQ((std::pair<bool, s32>{true, 7}), mbt.remove(1));
    ASSERT_EQ((std::pair<bool, s32>{true, 0}), mbt.remove(5));
    ASSERT_TRUE(mbt.bubbles().empty());
}

TEST(MemoryBubbleTracker, pointer)
{
    int * p{};

    qc::MemoryBubbleTracker<int *> mbt{};

    mbt.add(p + 1, 1);
    mbt.add(p + 3, 1);
    ASSERT_EQ(2u, mbt.bubbles().size());

    mbt.add(p + 2, 1);
    ASSERT_EQ(1u, mbt.bubbles().size());

    mbt.add(p + 0, 1);
    mbt.add(p + 4, 1);
    ASSERT_EQ(1u, mbt.bubbles().size());

    mbt.add(p + 6, 2);
    ASSERT_EQ(2u, mbt.bubbles().size());

    ASSERT_EQ(p + 0, mbt.bubbles().front().pos);
    ASSERT_EQ(5, mbt.bubbles().front().size);
    ASSERT_EQ(p + 6, mbt.bubbles().back().pos);
    ASSERT_EQ(2, mbt.bubbles().back().size);

    ASSERT_EQ((std::pair<bool, int *>{true, p + 6}), mbt.remove(1));
    ASSERT_EQ((std::pair<bool, int *>{true, p + 7}), mbt.remove(1));
    ASSERT_EQ((std::pair<bool, int *>{true, p + 0}), mbt.remove(5));
    ASSERT_TRUE(mbt.bubbles().empty());
}

TEST(MemoryBubbleTracker, tail)
{
    qc::MemoryBubbleTracker<u32> mbt{};
    ASSERT_EQ(0u, mbt.tail(0u));
    ASSERT_EQ(0u, mbt.tail(1u));

    mbt.add(0u, 1u);
    ASSERT_EQ(0u, mbt.tail(0u));
    ASSERT_EQ(1u, mbt.tail(1u));
    ASSERT_EQ(0u, mbt.tail(2u));

    mbt.add(2u, 3u);
    ASSERT_EQ(0u, mbt.tail(0u));
    ASSERT_EQ(0u, mbt.tail(1u));
    ASSERT_EQ(0u, mbt.tail(2u));
    ASSERT_EQ(1u, mbt.tail(3u));
    ASSERT_EQ(2u, mbt.tail(4u));
    ASSERT_EQ(3u, mbt.tail(5u));
    ASSERT_EQ(0u, mbt.tail(6u));
}
