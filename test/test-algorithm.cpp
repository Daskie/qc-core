#include <qc-core/algorithm.hpp>
#include <qc-core/list.hpp>

#include <gtest/gtest.h>

using namespace qc::types;
using namespace qc::primitives;

TEST(Algorithm, median)
{
    if constexpr (qc::debug) { ASSERT_DEATH(qc::median(qc::List<s32>{}.cspan()), ""); }
    ASSERT_EQ(qc::median(qc::List<s32>{1}.cspan()), 1);
    ASSERT_EQ(qc::median(qc::List<s32>{1, 1}.cspan()), 1);
    ASSERT_EQ(qc::median(qc::List<s32>{1, 2}.cspan()), 1);
    ASSERT_EQ(qc::median(qc::List<s32>{2, 1}.cspan()), 1);
    ASSERT_EQ(qc::median(qc::List<s32>{1, 1, 1}.cspan()), 1);
    ASSERT_EQ(qc::median(qc::List<s32>{1, 2, 3}.cspan()), 2);
    ASSERT_EQ(qc::median(qc::List<s32>{3, 1, 2}.cspan()), 2);
    ASSERT_EQ(qc::median(qc::List<s32>{4, 1, 3, 2}.cspan()), 2);
    ASSERT_EQ(qc::median(qc::List<s32>{5, 1, 4, 2}.cspan()), 3);

    ASSERT_EQ(qc::median(qc::List<float>{1.0f}.cspan()), 1.0f);
    ASSERT_EQ(qc::median(qc::List<float>{1.0f, 2.0f}.cspan()), 1.5f);
    ASSERT_EQ(qc::median(qc::List<float>{2.0f, 3.0f, 1.0f}.cspan()), 2.0f);
    ASSERT_EQ(qc::median(qc::List<float>{3.0f, 4.0f, 1.0f, 2.0f}.cspan()), 2.5f);
}

TEST(Algorithm, medianOrdered)
{
    if constexpr (qc::debug) { ASSERT_DEATH(qc::medianOrdered(qc::List<s32>{}.cspan()), ""); }
    ASSERT_EQ(qc::medianOrdered(qc::List<s32>{1}.cspan()), 1);
    ASSERT_EQ(qc::medianOrdered(qc::List<s32>{1, 1}.cspan()), 1);
    ASSERT_EQ(qc::medianOrdered(qc::List<s32>{1, 2}.cspan()), 1);
    ASSERT_EQ(qc::medianOrdered(qc::List<s32>{1, 1, 1}.cspan()), 1);
    ASSERT_EQ(qc::medianOrdered(qc::List<s32>{1, 2, 3}.cspan()), 2);
    ASSERT_EQ(qc::medianOrdered(qc::List<s32>{1, 2, 3, 4}.cspan()), 2);
    ASSERT_EQ(qc::medianOrdered(qc::List<s32>{1, 2, 4, 5}.cspan()), 3);

    ASSERT_EQ(qc::medianOrdered(qc::List<float>{1.0f}.cspan()), 1.0f);
    ASSERT_EQ(qc::medianOrdered(qc::List<float>{1.0f, 2.0f}.cspan()), 1.5f);
    ASSERT_EQ(qc::medianOrdered(qc::List<float>{1.0f, 2.0f, 3.0f}.cspan()), 2.0f);
    ASSERT_EQ(qc::medianOrdered(qc::List<float>{1.0f, 2.0f, 3.0f, 4.0f}.cspan()), 2.5f);
}
