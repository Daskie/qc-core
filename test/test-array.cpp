#include <qc-core/array.hpp>

#include <gtest/gtest.h>

using namespace qc::primitives;

TEST(Array, nElementConstructor)
{
    // Single element
    {
        qc::Array<s32, 1u> arr{1};
        ASSERT_EQ(arr[0u], 1);
    }

    // Multiple elements
    {
        qc::Array<s32, 3u> arr{1, 2, 3};
        ASSERT_EQ(arr[0u], 1);
        ASSERT_EQ(arr[1u], 2);
        ASSERT_EQ(arr[2u], 3);
    }
}

TEST(Array, fillConstructor)
{
    qc::Array<s32, 3u> arr{qc::FillTag{}, 7};
    ASSERT_EQ(arr[0u], 7);
    ASSERT_EQ(arr[1u], 7);
    ASSERT_EQ(arr[2u], 7);
}
