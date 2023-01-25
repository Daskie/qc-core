#include <gtest/gtest.h>

#include <qc-core/list.hpp>

template <typename T> using IL = std::initializer_list<T>;

struct NonTrivial
{
    inline static int contructions{0};
    inline static int assignments{0};
    inline static int copies{0};
    inline static int moves{0};
    inline static int destructions{0};

    static void reset() { contructions = assignments = copies = moves = destructions = 0; }

    int v{};

    NonTrivial() { ++contructions; }
    NonTrivial(const int v) : v{v} { ++contructions; }
    NonTrivial(const NonTrivial & other) : v{other.v} { ++contructions; ++copies; }
    NonTrivial(NonTrivial && other) : v{other.v} { ++contructions; ++moves; }
    NonTrivial & operator=(const NonTrivial & other) { v = other.v; ++assignments; ++copies; }
    NonTrivial & operator=(NonTrivial && other) { v = other.v; ++assignments; ++moves; }
    ~NonTrivial() { ++destructions; }
    bool operator==(const NonTrivial & other) const { return v == other.v; }
};

TEST(List, construction)
{
    {
        qc::List<int> list{};
        ASSERT_TRUE(list.empty());
        ASSERT_EQ(list.size(), 0u);
        ASSERT_EQ(list.capacity(), 0u);
    }
    {
        NonTrivial::reset();
        {
            qc::List<NonTrivial> list{};
            ASSERT_TRUE(list.empty());
            ASSERT_EQ(list.size(), 0u);
            ASSERT_EQ(list.capacity(), 0u);
        }
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);
    }
    {
        qc::List<int> list(7u);
        ASSERT_TRUE(!list.empty());
        ASSERT_EQ(list.size(), 7u);
        ASSERT_EQ(list.capacity(), 7u);
    }
    {
        NonTrivial::reset();
        {
            qc::List<NonTrivial> list(7u);
            ASSERT_TRUE(!list.empty());
            ASSERT_EQ(list.size(), 7u);
            ASSERT_EQ(list.capacity(), 7u);
        }
        ASSERT_EQ(NonTrivial::contructions, 7);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 7);
    }
    {
        qc::List<int> list(7u, 7);
        ASSERT_EQ(list.size(), 7u);
        ASSERT_EQ(list.capacity(), 7u);
        ASSERT_EQ(list, (IL<int>{7, 7, 7, 7, 7, 7, 7}));
    }
    {
        IL<NonTrivial> expected{7, 7, 7, 7, 7, 7, 7};
        NonTrivial::reset();
        {
            qc::List<NonTrivial> list(7u, 7);
            ASSERT_EQ(list.size(), 7u);
            ASSERT_EQ(list.capacity(), 7u);
            ASSERT_EQ(list, expected);
        }
        ASSERT_EQ(NonTrivial::contructions, 8);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 7);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 8);
    }
    {
        std::vector<int> v{1, 2, 3, 4, 5};
        qc::List<int> list{v.begin(), v.end()};
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3, 4, 5}));
    }
    {
        std::vector<NonTrivial> v{1, 2, 3, 4, 5};
        IL<NonTrivial> expected{1, 2, 3, 4, 5};
        NonTrivial::reset();
        {
            qc::List<NonTrivial> list{v.begin(), v.end()};
            ASSERT_EQ(list.size(), 5u);
            ASSERT_EQ(list.capacity(), 5u);
            ASSERT_EQ(list, expected);
        }
        ASSERT_EQ(NonTrivial::contructions, 5);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 5);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 5);
    }
    {
        qc::List<int> list{1, 2, 3, 4, 5};
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3, 4, 5}));
    }
    {
        IL<NonTrivial> expected{1, 2, 3, 4, 5};
        NonTrivial::reset();
        {
            qc::List<NonTrivial> list{1, 2, 3, 4, 5};
            ASSERT_EQ(list.size(), 5u);
            ASSERT_EQ(list.capacity(), 5u);
            ASSERT_EQ(list, expected);
        }
        ASSERT_EQ(NonTrivial::contructions, 10);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 5);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 10);
    }
    {
        qc::List<int> list{1, 2};
        ASSERT_EQ(list, (IL<int>{1, 2}));
    }
    {
        qc::List<int> list{1};
        ASSERT_EQ(list, (IL<int>{1}));
    }
    {
        qc::List<int> l1{1, 2, 3};
        ASSERT_EQ(l1.size(), 3u);
        ASSERT_EQ(l1.capacity(), 3u);

        qc::List<int> l2{std::move(l1)};
        ASSERT_EQ(l2.size(), 3u);
        ASSERT_EQ(l2.capacity(), 3u);
        ASSERT_EQ(l2, (IL<int>{1, 2, 3}));
        ASSERT_EQ(l1.size(), 0u);
        ASSERT_EQ(l1.capacity(), 0u);
    }
    {
        IL<NonTrivial> expected{1, 2, 3};
        NonTrivial::reset();
        {
            qc::List<NonTrivial> l1{1, 2, 3};
            ASSERT_EQ(l1.size(), 3u);
            ASSERT_EQ(l1.capacity(), 3u);

            ASSERT_EQ(NonTrivial::contructions, 6);
            ASSERT_EQ(NonTrivial::assignments, 0);
            ASSERT_EQ(NonTrivial::copies, 3);
            ASSERT_EQ(NonTrivial::moves, 0);
            ASSERT_EQ(NonTrivial::destructions, 3);
            NonTrivial::reset();

            qc::List<NonTrivial> l2{std::move(l1)};
            ASSERT_EQ(l2.size(), 3u);
            ASSERT_EQ(l2.capacity(), 3u);
            ASSERT_EQ(l2, expected);
            ASSERT_EQ(l1.size(), 0u);
            ASSERT_EQ(l1.capacity(), 0u);
        }
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 3);
    }
}

TEST(List, assignment)
{
    {
        qc::List<int> l1{1, 2, 3};
        ASSERT_EQ(l1.size(), 3u);
        ASSERT_EQ(l1.capacity(), 3u);

        qc::List<int> l2{};
        ASSERT_TRUE(l2.empty());

        l2 = std::move(l1);
        ASSERT_EQ(l2.size(), 3u);
        ASSERT_EQ(l2.capacity(), 3u);
        ASSERT_EQ(l2, (IL<int>{1, 2, 3}));
        ASSERT_EQ(l1.size(), 0u);
        ASSERT_EQ(l1.capacity(), 0u);
    }
    {
        IL<NonTrivial> expected{1, 2, 3};
        NonTrivial::reset();
        {
            qc::List<NonTrivial> l1{1, 2, 3};
            ASSERT_EQ(l1.size(), 3u);
            ASSERT_EQ(l1.capacity(), 3u);

            qc::List<NonTrivial> l2{};
            ASSERT_TRUE(l2.empty());

            ASSERT_EQ(NonTrivial::contructions, 6);
            ASSERT_EQ(NonTrivial::assignments, 0);
            ASSERT_EQ(NonTrivial::copies, 3);
            ASSERT_EQ(NonTrivial::moves, 0);
            ASSERT_EQ(NonTrivial::destructions, 3);
            NonTrivial::reset();

            l2 = std::move(l1);
            ASSERT_EQ(l2.size(), 3u);
            ASSERT_EQ(l2.capacity(), 3u);
            ASSERT_EQ(l2, expected);
            ASSERT_EQ(l1.size(), 0u);
            ASSERT_EQ(l1.capacity(), 0u);
        }
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 3);
    }
}

TEST(List, swap)
{
    using std::swap;

    {
        qc::List<int> l1{1, 2, 3};
        ASSERT_EQ(l1.size(), 3u);
        ASSERT_EQ(l1.capacity(), 3u);
        ASSERT_EQ(l1, (IL<int>{1, 2, 3}));

        qc::List<int> l2{4, 5, 6, 7};
        ASSERT_EQ(l2.size(), 4u);
        ASSERT_EQ(l2.capacity(), 4u);
        ASSERT_EQ(l2, (IL<int>{4, 5, 6, 7}));

        swap(l1, l2);
        ASSERT_EQ(l1.size(), 4u);
        ASSERT_EQ(l1.capacity(), 4u);
        ASSERT_EQ(l1, (IL<int>{4, 5, 6, 7}));
        ASSERT_EQ(l2.size(), 3u);
        ASSERT_EQ(l2.capacity(), 3u);
        ASSERT_EQ(l2, (IL<int>{1, 2, 3}));
    }
}

TEST(List, reserve)
{
    {
        qc::List<int> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_TRUE(list.empty());

        list.reserve(0u);
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_TRUE(list.empty());

        list.reserve(1u);
        ASSERT_EQ(list.capacity(), 1u);
        ASSERT_TRUE(list.empty());

        list.reserve(0u);
        ASSERT_EQ(list.capacity(), 1u);
        ASSERT_TRUE(list.empty());

        list.reserve(17u);
        ASSERT_EQ(list.capacity(), 17u);
        ASSERT_TRUE(list.empty());

        list.reserve(4u);
        ASSERT_EQ(list.capacity(), 17u);
        ASSERT_TRUE(list.empty());
    }
    {
        NonTrivial::reset();
        {
            qc::List<NonTrivial> list{};
            ASSERT_EQ(list.capacity(), 0u);
            ASSERT_TRUE(list.empty());

            list.reserve(0u);
            ASSERT_EQ(list.capacity(), 0u);
            ASSERT_TRUE(list.empty());

            list.reserve(1u);
            ASSERT_EQ(list.capacity(), 1u);
            ASSERT_TRUE(list.empty());

            list.reserve(0u);
            ASSERT_EQ(list.capacity(), 1u);
            ASSERT_TRUE(list.empty());

            list.reserve(17u);
            ASSERT_EQ(list.capacity(), 17u);
            ASSERT_TRUE(list.empty());

            list.reserve(4u);
            ASSERT_EQ(list.capacity(), 17u);
            ASSERT_TRUE(list.empty());
        }
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);
    }
}

TEST(List, resize)
{
    {
        qc::List<int> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        list.resize(3u);
        ASSERT_EQ(list.capacity(), 3u);
        ASSERT_EQ(list.size(), 3u);

        list.resize(1u);
        ASSERT_EQ(list.capacity(), 3u);
        ASSERT_EQ(list.size(), 1u);

        list.resize(5u, 5);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 5u);
        list[0] = 0;
        ASSERT_EQ(list, (IL<int>{0, 5, 5, 5, 5}));

        list.resize(3u, 3);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<int>{0, 5, 5}));

        list.resize(0u);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 0u);
    }
    {
        IL<NonTrivial> expected5{0, 5, 5, 5, 5};
        IL<NonTrivial> expected3{0, 5, 5};

        qc::List<NonTrivial> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        NonTrivial::reset();

        list.resize(3u);
        ASSERT_EQ(list.capacity(), 3u);
        ASSERT_EQ(list.size(), 3u);

        ASSERT_EQ(NonTrivial::contructions, 3);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);

        NonTrivial::reset();

        list.resize(1u);
        ASSERT_EQ(list.capacity(), 3u);
        ASSERT_EQ(list.size(), 1u);

        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 2);

        NonTrivial::reset();

        list.resize(5u, 5);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, expected5);

        ASSERT_EQ(NonTrivial::contructions, 6);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 4);
        ASSERT_EQ(NonTrivial::moves, 1);
        ASSERT_EQ(NonTrivial::destructions, 2);

        NonTrivial::reset();

        list.resize(3u, 3);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, expected3);

        ASSERT_EQ(NonTrivial::contructions, 1);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 3);

        NonTrivial::reset();

        list.resize(0u);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 0u);

        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 3);
    }
}

TEST(List, shrink)
{
    {
        qc::List<int> list(8u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 8u);

        list.reserve(10u);
        ASSERT_EQ(list.capacity(), 10u);
        ASSERT_EQ(list.size(), 8u);

        list.shrink();
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 8u);

        list.clear();
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 0u);

        list.shrink();
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);
    }
}

TEST(List, clear)
{
    {
        qc::List<int> list(14u);
        ASSERT_EQ(list.capacity(), 14u);
        ASSERT_EQ(list.size(), 14u);

        list.clear();
        ASSERT_EQ(list.capacity(), 14u);
        ASSERT_EQ(list.size(), 0u);
    }
    {
        {
            qc::List<NonTrivial> list(14u);
            ASSERT_EQ(list.capacity(), 14u);
            ASSERT_EQ(list.size(), 14u);

            NonTrivial::reset();

            list.clear();
            ASSERT_EQ(list.capacity(), 14u);
            ASSERT_EQ(list.size(), 0u);
        }
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 14);
    }
}

TEST(List, push)
{
    {
        qc::List<int> list{};
        list.push();
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 1u);
    }
    {
        qc::List<NonTrivial> list{};
        list.push();
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 1u);
    }
    {
        qc::List<NonTrivial> list{};
        list.push(1);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 1u);
    }
    {
        qc::List<NonTrivial> list{};
        list.push(NonTrivial{1});
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 1u);
    }
    {
        qc::List<int> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        ASSERT_EQ(list.push(1), 1);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<int>{1}));

        ASSERT_EQ(list.push(2), 2);
        ASSERT_EQ(list.push(3), 3);
        ASSERT_EQ(list.push(4), 4);
        ASSERT_EQ(list.push(5), 5);
        ASSERT_EQ(list.push(6), 6);
        ASSERT_EQ(list.push(7), 7);
        ASSERT_EQ(list.push(8), 8);
        ASSERT_EQ(list.push(9), 9);
        ASSERT_EQ(list.push(10), 10);
        ASSERT_EQ(list.push(11), 11);
        ASSERT_EQ(list.push(12), 12);
        ASSERT_EQ(list.push(13), 13);
        ASSERT_EQ(list.push(14), 14);
        ASSERT_EQ(list.push(15), 15);
        ASSERT_EQ(list.push(16), 16);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 16u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}));

        ASSERT_EQ(list.push(17), 17);
        ASSERT_EQ(list.capacity(), 32u);
        ASSERT_EQ(list.size(), 17u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17}));
    }
    {
        qc::List<int> list(3u);
        ASSERT_EQ(list.capacity(), 3u);
        ASSERT_EQ(list.size(), 3u);

        list.push();
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 4u);
    }
    {
        qc::List<int> list(9u);
        ASSERT_EQ(list.capacity(), 9u);
        ASSERT_EQ(list.size(), 9u);

        list.push();
        ASSERT_EQ(list.capacity(), 18u);
        ASSERT_EQ(list.size(), 10u);
    }
    {
        qc::List<NonTrivial> list(9u);
        ASSERT_EQ(list.capacity(), 9u);
        ASSERT_EQ(list.size(), 9u);

        NonTrivial::reset();

        list.push();
        ASSERT_EQ(list.capacity(), 18u);
        ASSERT_EQ(list.size(), 10u);

        ASSERT_EQ(NonTrivial::contructions, 10);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 9);
        ASSERT_EQ(NonTrivial::destructions, 9);
    }
}

TEST(List, bump)
{
    {
        qc::List<int> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        list.bump();
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 1u);

        list.bump();
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 2u);

        list.bump(14u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 16u);

        list.bump(1u);
        ASSERT_EQ(list.capacity(), 32u);
        ASSERT_EQ(list.size(), 17u);
    }
}

TEST(List, pop)
{
    {
        qc::List<int> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        list.pop();
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);
    }
    {
        qc::List<int> list{1, 2, 3, 4, 5};
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3, 4, 5}));

        list.pop();
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3, 4}));

        list.pop();
        list.pop();
        list.pop();
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<int>{1}));

        list.pop();
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 0u);

        list.pop();
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 0u);
    }
    {
        qc::List<NonTrivial> list{1, 2, 3};

        NonTrivial::reset();

        list.pop();

        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 1);
    }
}

TEST(List, subscript)
{
    {
        qc::List<int> list{1, 2, 3};
        ASSERT_EQ(1, list[0]);
        ASSERT_EQ(2, list[1]);
        ASSERT_EQ(3, list[2]);
    }
}

TEST(List, front)
{
    {
        qc::List<int> list{1, 2, 3};
        ASSERT_EQ(1, list.front());
    }
}

TEST(List, back)
{
    {
        qc::List<int> list{1, 2, 3};
        ASSERT_EQ(3, list.back());
    }
}

TEST(List, data)
{
    {
        qc::List<int> list{};
        ASSERT_EQ(list.data(), nullptr);
    }
    {
        qc::List<int> list{1, 2, 3};
        int * data{list.data()};
        ASSERT_EQ(1, data[0]);
        ASSERT_EQ(2, data[1]);
        ASSERT_EQ(3, data[2]);
    }
}

TEST(List, iteration)
{
    {
        qc::List<int> list{1, 2, 3};

        auto it{list.begin()};
        ASSERT_NE(it, list.end());
        ASSERT_EQ(*it, 1);

        ++it;
        ASSERT_NE(it, list.end());
        ASSERT_EQ(*it, 2);

        ++it;
        ASSERT_NE(it, list.end());
        ASSERT_EQ(*it, 3);

        ++it;
        ASSERT_EQ(it, list.end());

        int expected{1};
        for (const int i : list)
        {
            ASSERT_EQ(i, expected);
            ++expected;
        }
    }
    {
        qc::List<NonTrivial> list{1, 2, 3};

        auto it{list.begin()};
        ASSERT_NE(it, list.end());
        ASSERT_EQ(it->v, 1);

        ++it;
        ASSERT_NE(it, list.end());
        ASSERT_EQ(it->v, 2);

        ++it;
        ASSERT_NE(it, list.end());
        ASSERT_EQ(it->v, 3);

        ++it;
        ASSERT_EQ(it, list.end());

        int expected{1};
        for (const NonTrivial & v : list)
        {
            ASSERT_EQ(v.v, expected);
            ++expected;
        }
    }
}

TEST(List, equality)
{
    {
        qc::List<int> l1{1, 2, 3};
        qc::List<int> l2{1, 2, 3};
        qc::List<int> l3{1, 2};
        qc::List<int> l4{};

        ASSERT_EQ(l1, l1);
        ASSERT_EQ(l1, l2);
        ASSERT_NE(l1, l3);
        ASSERT_NE(l1, l4);
        ASSERT_EQ(l4, l4);
    }
}
