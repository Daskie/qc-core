#include <qc-core/array.hpp>

#include <gtest/gtest.h>

using namespace qc::primitives;

TEST(Array, construction)
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

    // Fill
    {
        qc::Array<s32, 3u> arr{qc::FillTag{}, 7};
        ASSERT_EQ(arr[0u], 7);
        ASSERT_EQ(arr[1u], 7);
        ASSERT_EQ(arr[2u], 7);
    }

    // Copy
    {
        qc::Array<std::string, 3u> arr1{"a", "b", "c"};
        qc::Array<std::string, 3u> arr2{arr1};
        ASSERT_EQ(arr1, arr2);
        ASSERT_EQ(arr1[1], "b");
        ASSERT_EQ(arr2[1], "b");
    }

    // Move
    {
        qc::Array<std::string, 3u> arr1{"a", "b", "c"};
        qc::Array<std::string, 3u> arr2{std::move(arr1)};
        ASSERT_NE(arr1, arr2);
        ASSERT_TRUE(arr1[1].empty());
        ASSERT_EQ(arr2[1], "b");
    }
}

TEST(Array, assignment)
{
    // Copy
    {
        qc::Array<std::string, 3u> arr1{"a", "b", "c"};
        qc::Array<std::string, 3u> arr2{"d", "e", "f"};
        arr1 = arr2;
        ASSERT_EQ(arr1, arr2);
        ASSERT_EQ(arr1[1], "e");
        ASSERT_EQ(arr2[1], "e");
    }

    // Move
    {
        qc::Array<std::string, 3u> arr1{"a", "b", "c"};
        qc::Array<std::string, 3u> arr2{"d", "e", "f"};
        arr1 = std::move(arr2);
        ASSERT_NE(arr1, arr2);
        ASSERT_EQ(arr1[1], "e");
        ASSERT_TRUE(arr2[1].empty());
    }
}

TEST(Array, operatorView)
{
    qc::Array<s32, 3u> arr{1, 2, 3};

    {
        const qc::View<s32> view{arr};
        ASSERT_EQ(view.data, arr.data);
        ASSERT_EQ(view.size, arr.size);
    }

    {
        const qc::CView<s32> view{arr};
        ASSERT_EQ(view.data, arr.data);
        ASSERT_EQ(view.size, arr.size);
    }
}

TEST(Array, fill)
{
    qc::Array<s32, 6u> arr{};
    arr.fill(6);
    for (const s32 v : arr) ASSERT_EQ(v, 6);
}

TEST(Array, get)
{
    qc::Array<s32, 5u> arr{0, 1, 2, 3, 4};
    ASSERT_EQ(arr.get<1u>(), 1);
    ASSERT_EQ(arr.get<3u>(), 3);
}

TEST(Array, indexOperator)
{
    qc::Array<s32, 5u> arr{0, 1, 2, 3, 4};
    ASSERT_EQ(arr[2u], 2);
    ASSERT_EQ(arr[4u], 4);
}

TEST(Array, structuredBinding)
{
    qc::Array<s32, 3u> arr{0, 1, 2};
    const auto [a, b, c]{arr};
    ASSERT_EQ(a, 0);
    ASSERT_EQ(b, 1);
    ASSERT_EQ(c, 2);
}

TEST(Array, front)
{
    qc::Array<s32, 3u> arr{7, 6, 5};
    ASSERT_EQ(arr.front(), 7);
}

TEST(Array, back)
{
    qc::Array<s32, 3u> arr{7, 6, 5};
    ASSERT_EQ(arr.back(), 5);
}

TEST(Array, iteration)
{
    qc::Array<s32, 3u> arr{2, 4, 6};
    s32 expected{2};
    for (const s32 v : arr)
    {
        ASSERT_EQ(v, expected);
        expected += 2;
    }
}

TEST(Array, equality)
{
    qc::Array<s32, 3u> arr1{1, 2, 3};
    qc::Array<s32, 3u> arr2{1, 2, 3};
    qc::Array<s32, 3u> arr3{1, 2, 4};
    ASSERT_EQ(arr1, arr1);
    ASSERT_EQ(arr1, arr2);
    ASSERT_NE(arr1, arr3);
}
