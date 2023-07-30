#include <qc-core/view.hpp>

#include <gtest/gtest.h>

using namespace qc::types;
using namespace qc::primitives;

using qc::View;
using qc::CView;
using qc::StringView;
using qc::StringCView;

namespace
{
    s32 arr[10u]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
}

TEST(View, construction)
{
    // Default
    {
        const View<s32> view{};
        ASSERT_EQ(view.data, nullptr);
        ASSERT_EQ(view.size, 0u);
    }

    // Pointer and length
    {
        const View<s32> view{arr, 6u};
        ASSERT_EQ(view.data, arr);
        ASSERT_EQ(view.size, 6u);
    }

    // First and last pointers
    {
        const View<s32> view{arr, arr + 3};
        ASSERT_EQ(view.data, arr);
        ASSERT_EQ(view.size, 3u);
    }

    // Array
    {
        const View<s32> view{arr};
        ASSERT_EQ(view.data, arr);
        ASSERT_EQ(view.size, 10u);

        View<const s32>{arr};

        View{arr};
    }

    // Copy
    {
        const View<s32> view1{arr};
        const View<s32> view2{view1};
        ASSERT_EQ(view2.data, arr);
        ASSERT_EQ(view2.size, 10u);
    }

    // Mutable to const view
    {
        const View<s32> view1{arr};
        const CView<s32> view2{view1};
        ASSERT_EQ(view2.data, arr);
        ASSERT_EQ(view2.size, 10u);
    }
}

TEST(View, assignment)
{

    // Copy
    {
        View<s32> view1{};
        const View<s32> view2{arr};
        view1 = view2;
        ASSERT_EQ(view1.data, arr);
        ASSERT_EQ(view1.size, 10u);
    }

    // Mutable to const
    {
        CView<s32> view1{};
        const View<s32> view2{arr};
        view1 = view2;
        ASSERT_EQ(view1.data, arr);
        ASSERT_EQ(view1.size, 10u);
    }

    // Array
    {
        View<s32> view{};
        view = arr;
        ASSERT_EQ(view.data, arr);
        ASSERT_EQ(view.size, 10u);
    }
}

TEST(View, operatorBool)
{

    View<s32> view{};
    ASSERT_FALSE(view);
    view = arr;
    ASSERT_TRUE(view);
    view.size = 0u;
    ASSERT_FALSE(view);
}

TEST(View, view)
{
    const View<s32> view1{arr};

    {
        const View view2{view1.view(0u)};
        ASSERT_EQ(view2.data, arr);
        ASSERT_EQ(view2.size, 10u);
    }

    {
        const View view2{view1.view(0u, 0u)};
        ASSERT_EQ(view2.data, arr);
        ASSERT_EQ(view2.size, 0u);
    }

    {
        const View view2{view1.view(3u)};
        ASSERT_EQ(view2.data, arr + 3);
        ASSERT_EQ(view2.size, 7u);
    }

    {
        const View view2{view1.view(3u, 6u)};
        ASSERT_EQ(view2.data, arr + 3);
        ASSERT_EQ(view2.size, 6u);
    }
}

TEST(View, viewFirst)
{
    const View<s32> view1{arr};

    {
        const View view2{view1.viewFirst(0u)};
        ASSERT_EQ(view2.data, arr);
        ASSERT_EQ(view2.size, 0u);
    }

    {
        const View view2{view1.viewFirst(3u)};
        ASSERT_EQ(view2.data, arr);
        ASSERT_EQ(view2.size, 3u);
    }
}

TEST(View, viewLast)
{
    const View<s32> view1{arr};

    {
        const View view2{view1.viewLast(0u)};
        ASSERT_EQ(view2.data, arr + 10);
        ASSERT_EQ(view2.size, 0u);
    }

    {
        const View view2{view1.viewLast(3u)};
        ASSERT_EQ(view2.data, arr + 7);
        ASSERT_EQ(view2.size, 3u);
    }
}

TEST(View, indexOperator)
{
    const CView<s32> view{arr};
    ASSERT_EQ(view[1u], 1);
    ASSERT_EQ(view[5u], 5);
}

TEST(View, front)
{
    const CView<s32> view{arr};
    ASSERT_EQ(view.front(), 0);
}

TEST(View, back)
{
    const CView<s32> view{arr};
    ASSERT_EQ(view.back(), 9);
}

TEST(View, iteration)
{
    const CView<s32> view{arr};
    s32 expected{0};
    for (const s32 v : view)
    {
        ASSERT_EQ(v, expected);
        ++expected;
    }
}

TEST(View, equality)
{
    const View<s32> view1{arr};
    const View<s32> view2{arr, 4u};
    const View<s32> view3{};

    ASSERT_EQ(view1, view1);
    ASSERT_EQ(view3, view3);
    ASSERT_NE(view1, view2);
    ASSERT_NE(view1, view3);
}
