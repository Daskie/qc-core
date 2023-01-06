#include <qc-core/unique-ordered-vector.hpp>

#include <gtest/gtest.h>

TEST(UniqueOrderedVector, standard)
{
    qc::UniqueOrderedVector<int> vals{};

    EXPECT_EQ(0u, vals.size());
    EXPECT_FALSE(vals.contains(0));
    EXPECT_EQ(vals.end(), vals.find(0));
    EXPECT_FALSE(vals.erase(0));

    {
        const auto [it, res]{vals.insert(3)};
        EXPECT_EQ(vals.begin(), it);
        EXPECT_TRUE(res);
    }
    {
        const auto [it, res]{vals.insert(3)};
        EXPECT_EQ(vals.begin(), it);
        EXPECT_FALSE(res);
    }
    EXPECT_EQ(1u, vals.size());
    EXPECT_TRUE(vals.contains(3));
    EXPECT_NE(vals.end(), vals.find(3));

    {
        const auto [it, res]{vals.insert(5)};
        EXPECT_EQ(vals.begin() + 1, it);
        EXPECT_TRUE(res);
    }
    {
        const auto [it, res]{vals.insert(1)};
        EXPECT_EQ(vals.begin(), it);
        EXPECT_TRUE(res);
    }
    EXPECT_EQ(3u, vals.size());

    {
        int expected{1};
        for (const int v: vals)
        {
            EXPECT_EQ(expected, v);
            expected += 2;
        }
    }

    {
        auto it{vals.rbegin()};
        EXPECT_EQ(5, *it);
        ++it;
        EXPECT_EQ(3, *it);
        ++it;
        EXPECT_EQ(1, *it);
        ++it;
        EXPECT_EQ(vals.rend(), it);
    }

    EXPECT_EQ(vals.begin(), vals.lowerBound(0));
    EXPECT_EQ(vals.begin(), vals.lowerBound(1));
    EXPECT_EQ(vals.begin() + 1, vals.lowerBound(2));
    EXPECT_EQ(vals.begin() + 1, vals.lowerBound(3));
    EXPECT_EQ(vals.begin() + 2, vals.lowerBound(4));
    EXPECT_EQ(vals.begin() + 2, vals.lowerBound(5));
    EXPECT_EQ(vals.end(), vals.lowerBound(6));

    EXPECT_TRUE(vals.erase(3));
    EXPECT_FALSE(vals.contains(3));

    EXPECT_EQ(5, *vals.erase(vals.begin()));

    vals.clear();
    EXPECT_TRUE(vals.empty());
}
