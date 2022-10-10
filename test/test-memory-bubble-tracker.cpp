#include <qc-core/memory-bubble-tracker.hpp>

#include <gtest/gtest.h>

using namespace qc::types;

namespace qc::_internal
{
    class MemoryBubbleTrackerFriend
    {
      public:

        template <typename P> using Bubble = typename MemoryBubbleTracker<P>::_Bubble;

        template <typename P>
        static const std::vector<Bubble<P>> & bubbles(const MemoryBubbleTracker<P> & mbt) noexcept
        {
            return mbt._bubbles;
        }
    };
}

using MBTF = qc::_internal::MemoryBubbleTrackerFriend;

TEST(MemoryBubbleTracker, empty)
{
    using Bubble = MBTF::Bubble<u32>;

    qc::MemoryBubbleTracker<u32> mbt{};
    ASSERT_TRUE(MBTF::bubbles(mbt).empty());

    ASSERT_FALSE(mbt.remove(0u).first);
    ASSERT_FALSE(mbt.remove(1u).first);
}

TEST(MemoryBubbleTracker, single)
{
    using Bubble = MBTF::Bubble<u32>;

    qc::MemoryBubbleTracker<u32> mbt{};

    mbt.add(0u, 1u);
    ASSERT_EQ(1u, MBTF::bubbles(mbt).size());
    ASSERT_EQ(0u, MBTF::bubbles(mbt).front().pos);
    ASSERT_EQ(1u, MBTF::bubbles(mbt).front().size);

    ASSERT_FALSE(mbt.remove(0u).first);
    ASSERT_FALSE(mbt.remove(2u).first);
    ASSERT_EQ((std::pair<bool, u32>{true, 0u}), mbt.remove(1u));
    ASSERT_TRUE(MBTF::bubbles(mbt).empty());
}

TEST(MemoryBubbleTracker, adjacent)
{
    using Bubble = MBTF::Bubble<u32>;

    qc::MemoryBubbleTracker<u32> mbt{};

    mbt.add(1u, 1u);
    mbt.add(2u, 1u);
    ASSERT_EQ(1u, MBTF::bubbles(mbt).size());
    mbt.add(0u, 1u);
    ASSERT_EQ(1u, MBTF::bubbles(mbt).size());
    ASSERT_EQ(0u, MBTF::bubbles(mbt).front().pos);
    ASSERT_EQ(3u, MBTF::bubbles(mbt).front().size);

    ASSERT_EQ((std::pair<bool, u32>{true, 0u}), mbt.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 1u}), mbt.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 2u}), mbt.remove(1u));
    ASSERT_TRUE(MBTF::bubbles(mbt).empty());
}

TEST(MemoryBubbleTracker, gapFill)
{
    using Bubble = MBTF::Bubble<u32>;

    qc::MemoryBubbleTracker<u32> mbt{};

    mbt.add(0u, 1u);
    mbt.add(2u, 1u);
    ASSERT_EQ(2u, MBTF::bubbles(mbt).size());
    ASSERT_EQ(0u, MBTF::bubbles(mbt).front().pos);
    ASSERT_EQ(1u, MBTF::bubbles(mbt).front().size);
    ASSERT_EQ(2u, MBTF::bubbles(mbt).back().pos);
    ASSERT_EQ(1u, MBTF::bubbles(mbt).back().size);
    mbt.add(1u, 1u);
    ASSERT_EQ(1u, MBTF::bubbles(mbt).size());
    ASSERT_EQ(0u, MBTF::bubbles(mbt).front().pos);
    ASSERT_EQ(3u, MBTF::bubbles(mbt).front().size);

    ASSERT_EQ((std::pair<bool, u32>{true, 0u}), mbt.remove(3u));
    ASSERT_TRUE(MBTF::bubbles(mbt).empty());
}

TEST(MemoryBubbleTracker, separate)
{
    using Bubble = MBTF::Bubble<u32>;

    qc::MemoryBubbleTracker<u32> mbt{};

    mbt.add(0u, 1u);
    mbt.add(2u, 2u);
    mbt.add(5u, 3u);
    ASSERT_EQ(3u, MBTF::bubbles(mbt).size());

    ASSERT_EQ((std::pair<bool, u32>{true, 5u}), mbt.remove(3u));
    ASSERT_EQ((std::pair<bool, u32>{true, 2u}), mbt.remove(2u));
    ASSERT_EQ((std::pair<bool, u32>{true, 0u}), mbt.remove(1u));
    ASSERT_TRUE(MBTF::bubbles(mbt).empty());

    mbt.add(0u, 3u);
    mbt.add(4u, 2u);
    mbt.add(7u, 1u);
    ASSERT_EQ(3u, MBTF::bubbles(mbt).size());

    ASSERT_EQ((std::pair<bool, u32>{true, 7u}), mbt.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 4u}), mbt.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 5u}), mbt.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 0u}), mbt.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 1u}), mbt.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 2u}), mbt.remove(1u));
    ASSERT_TRUE(MBTF::bubbles(mbt).empty());

    mbt.add(0u, 2u);
    mbt.add(3u, 2u);
    ASSERT_EQ(2u, MBTF::bubbles(mbt).size());

    ASSERT_EQ((std::pair<bool, u32>{true, 0u}), mbt.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 1u}), mbt.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 3u}), mbt.remove(1u));
    ASSERT_EQ((std::pair<bool, u32>{true, 4u}), mbt.remove(1u));
    ASSERT_TRUE(MBTF::bubbles(mbt).empty());
}

TEST(MemoryBubbleTracker, removeZero)
{
    using Bubble = MBTF::Bubble<u32>;

    qc::MemoryBubbleTracker<u32> mbt{};

    ASSERT_FALSE(mbt.remove(0u).first);

    mbt.add(0u, 1u);
    ASSERT_FALSE(mbt.remove(0u).first);
}

TEST(MemoryBubbleTracker, removeTooLarge)
{
    using Bubble = MBTF::Bubble<u32>;

    qc::MemoryBubbleTracker<u32> mbt{};

    mbt.add(0u, 1u);
    ASSERT_FALSE(mbt.remove(2u).first);
}

TEST(MemoryBubbleTracker, addOverlap)
{
    using Bubble = MBTF::Bubble<u32>;

    qc::MemoryBubbleTracker<u32> mbt{};

    mbt.add(2u, 1u);
    ASSERT_EQ(1u, MBTF::bubbles(mbt).size());

    mbt.add(2u, 1u);
    ASSERT_EQ(1u, MBTF::bubbles(mbt).size());
    ASSERT_EQ(2u, MBTF::bubbles(mbt).front().pos);
    ASSERT_EQ(1u, MBTF::bubbles(mbt).front().size);

    mbt.add(1u, 2u);
    ASSERT_EQ(1u, MBTF::bubbles(mbt).size());
    ASSERT_EQ(1u, MBTF::bubbles(mbt).front().pos);
    ASSERT_EQ(2u, MBTF::bubbles(mbt).front().size);

    mbt.add(2u, 2u);
    ASSERT_EQ(1u, MBTF::bubbles(mbt).size());
    ASSERT_EQ(1u, MBTF::bubbles(mbt).front().pos);
    ASSERT_EQ(3u, MBTF::bubbles(mbt).front().size);

    mbt.add(0u, 2u);
    ASSERT_EQ(1u, MBTF::bubbles(mbt).size());
    ASSERT_EQ(0u, MBTF::bubbles(mbt).front().pos);
    ASSERT_EQ(4u, MBTF::bubbles(mbt).front().size);

    mbt.add(3u, 2u);
    ASSERT_EQ(1u, MBTF::bubbles(mbt).size());
    ASSERT_EQ(0u, MBTF::bubbles(mbt).front().pos);
    ASSERT_EQ(5u, MBTF::bubbles(mbt).front().size);
}

TEST(MemoryBubbleTracker, signedInteger)
{
    using Bubble = MBTF::Bubble<s32>;

    qc::MemoryBubbleTracker<s32> mbt{};

    mbt.add(1, 1);
    mbt.add(3, 1);
    ASSERT_EQ(2u, MBTF::bubbles(mbt).size());

    mbt.add(2, 1);
    ASSERT_EQ(1u, MBTF::bubbles(mbt).size());

    mbt.add(0, 1);
    mbt.add(4, 1);
    ASSERT_EQ(1u, MBTF::bubbles(mbt).size());

    mbt.add(6, 2);
    ASSERT_EQ(2u, MBTF::bubbles(mbt).size());

    ASSERT_EQ(0, MBTF::bubbles(mbt).front().pos);
    ASSERT_EQ(5, MBTF::bubbles(mbt).front().size);
    ASSERT_EQ(6, MBTF::bubbles(mbt).back().pos);
    ASSERT_EQ(2, MBTF::bubbles(mbt).back().size);

    ASSERT_EQ((std::pair<bool, s32>{true, 6}), mbt.remove(1));
    ASSERT_EQ((std::pair<bool, s32>{true, 7}), mbt.remove(1));
    ASSERT_EQ((std::pair<bool, s32>{true, 0}), mbt.remove(5));
    ASSERT_TRUE(MBTF::bubbles(mbt).empty());
}

TEST(MemoryBubbleTracker, pointer)
{
    using Bubble = MBTF::Bubble<int *>;

    int * p{};

    qc::MemoryBubbleTracker<int *> mbt{};

    mbt.add(p + 1, 1);
    mbt.add(p + 3, 1);
    ASSERT_EQ(2u, MBTF::bubbles(mbt).size());

    mbt.add(p + 2, 1);
    ASSERT_EQ(1u, MBTF::bubbles(mbt).size());

    mbt.add(p + 0, 1);
    mbt.add(p + 4, 1);
    ASSERT_EQ(1u, MBTF::bubbles(mbt).size());

    mbt.add(p + 6, 2);
    ASSERT_EQ(2u, MBTF::bubbles(mbt).size());

    ASSERT_EQ(p + 0, MBTF::bubbles(mbt).front().pos);
    ASSERT_EQ(5, MBTF::bubbles(mbt).front().size);
    ASSERT_EQ(p + 6, MBTF::bubbles(mbt).back().pos);
    ASSERT_EQ(2, MBTF::bubbles(mbt).back().size);

    ASSERT_EQ((std::pair<bool, int *>{true, p + 6}), mbt.remove(1));
    ASSERT_EQ((std::pair<bool, int *>{true, p + 7}), mbt.remove(1));
    ASSERT_EQ((std::pair<bool, int *>{true, p + 0}), mbt.remove(5));
    ASSERT_TRUE(MBTF::bubbles(mbt).empty());
}
