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
    NonTrivial & operator=(const NonTrivial & other) { v = other.v; ++assignments; ++copies; return *this; }
    NonTrivial & operator=(NonTrivial && other) { v = other.v; ++assignments; ++moves; return *this; }
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
    {
        qc::List<NonTrivial> list{9, 8, 7};

        NonTrivial::reset();
        list = {1, 2, 3};
        ASSERT_EQ(NonTrivial::contructions, 6);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 3);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 6);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3}));

        std::vector<NonTrivial> vs{2, 2, 2, 2};
        NonTrivial::reset();
        list = std::span<const NonTrivial>{vs.cbegin(), vs.cend()};
        ASSERT_EQ(NonTrivial::contructions, 4);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 4);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 3);
        ASSERT_EQ(list, (IL<NonTrivial>{2, 2, 2, 2}));
    }
    {
        qc::List<NonTrivial> list{9, 8, 7};

        list = {1, 2, 3};
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3}));

        std::vector<NonTrivial> vs{2, 2, 2, 2};
        list = std::span<const NonTrivial>{vs.cbegin(), vs.cend()};
        ASSERT_EQ(list, (IL<NonTrivial>{2, 2, 2, 2}));
    }
}

TEST(List, assign)
{
    {
        qc::List<int> list{9, 8, 7};

        list.assign(6u, 3);
        ASSERT_EQ(list, (IL<int>{3, 3, 3, 3, 3, 3}));

        std::vector<int> vs{3, 2, 1};
        list.assign(vs.cbegin(), vs.cend());
        ASSERT_EQ(list, (IL<int>{3, 2, 1}));

        list.assign({1, 2, 3, 4});
        ASSERT_EQ(list, (IL<int>{1, 2, 3, 4}));

        list.assign(std::span<int>{vs.data(), vs.size()});
        ASSERT_EQ(list, (IL<int>{3, 2, 1}));
    }
    {
        qc::List<NonTrivial> list{9, 8, 7};

        NonTrivial::reset();
        list.assign(6u, 3);
        ASSERT_EQ(NonTrivial::contructions, 7);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 6);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 4);
        ASSERT_EQ(list, (IL<NonTrivial>{3, 3, 3, 3, 3, 3}));

        std::vector<NonTrivial> vs{3, 2, 1};
        NonTrivial::reset();
        list.assign(vs.cbegin(), vs.cend());
        ASSERT_EQ(NonTrivial::contructions, 3);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 3);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 6);
        ASSERT_EQ(list, (IL<NonTrivial>{3, 2, 1}));

        NonTrivial::reset();
        list.assign({1, 2, 3, 4});
        ASSERT_EQ(NonTrivial::contructions, 8);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 4);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 7);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4}));

        NonTrivial::reset();
        list.assign(std::span<NonTrivial>{vs.data(), vs.size()});
        ASSERT_EQ(NonTrivial::contructions, 3);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 3);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 4);
        ASSERT_EQ(list, (IL<NonTrivial>{3, 2, 1}));
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
        qc::List<NonTrivial> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        NonTrivial::reset();
        list.resize(3u);
        ASSERT_EQ(NonTrivial::contructions, 3);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(list.capacity(), 3u);
        ASSERT_EQ(list.size(), 3u);

        NonTrivial::reset();
        list.resize(1u);
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 2);
        ASSERT_EQ(list.capacity(), 3u);
        ASSERT_EQ(list.size(), 1u);

        NonTrivial::reset();
        list.resize(5u, 5);
        ASSERT_EQ(NonTrivial::contructions, 6);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 4);
        ASSERT_EQ(NonTrivial::moves, 1);
        ASSERT_EQ(NonTrivial::destructions, 2);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<NonTrivial>{0, 5, 5, 5, 5}));

        NonTrivial::reset();
        list.resize(3u, 3);
        ASSERT_EQ(NonTrivial::contructions, 1);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 3);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{0, 5, 5}));

        NonTrivial::reset();
        list.resize(0u);
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 3);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 0u);
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
        ASSERT_EQ(NonTrivial::contructions, 10);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 9);
        ASSERT_EQ(NonTrivial::destructions, 9);
        ASSERT_EQ(list.capacity(), 18u);
        ASSERT_EQ(list.size(), 10u);
    }
}

TEST(List, bump)
{
    {
        qc::List<int> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        list.bump() = 1;
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<int>{1}));

        list.bump() = 2;
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 2u);
        ASSERT_EQ(list, (IL<int>{1, 2}));

        for (int & i : list.bump(14u)) i = 3;
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 16u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}));

        list.bump(1u).front() = 4;
        ASSERT_EQ(list.capacity(), 32u);
        ASSERT_EQ(list.size(), 17u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4}));
    }
}

TEST(List, emplace)
{
    {
        qc::List<int> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        int * it{list.emplace(list.end(), 4)};
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<int>{4}));

        it = list.emplace(list.begin(), 1);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 2u);
        ASSERT_EQ(list, (IL<int>{1, 4}));

        it = list.emplace(list.begin() + 1, 3);
        ASSERT_EQ(it, list.begin() + 1);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<int>{1, 3, 4}));

        it = list.emplace(list.begin() + 1, 2);
        ASSERT_EQ(it, list.begin() + 1);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3, 4}));

        list.emplace(list.end(), 5);
        list.emplace(list.end(), 6);
        list.emplace(list.end(), 7);
        list.emplace(list.end(), 8);
        list.emplace(list.end(), 9);
        list.emplace(list.end(), 10);
        list.emplace(list.end(), 11);
        list.emplace(list.end(), 12);
        list.emplace(list.end(), 13);
        list.emplace(list.end(), 14);
        list.emplace(list.end(), 15);
        list.emplace(list.end(), 16);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 16u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}));

        it = list.emplace(list.begin(), 0);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 32u);
        ASSERT_EQ(list.size(), 17u);
        ASSERT_EQ(list, (IL<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}));

        list.pop();
        list.shrink();
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 16u);
        ASSERT_EQ(list, (IL<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}));

        it = list.emplace(list.end(), 16);
        ASSERT_EQ(it, list.end() - 1);
        ASSERT_EQ(list.capacity(), 32u);
        ASSERT_EQ(list.size(), 17u);
        ASSERT_EQ(list, (IL<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}));

        list.erase(list.begin() + 8);
        list.shrink();
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 16u);
        ASSERT_EQ(list, (IL<int>{0, 1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 12, 13, 14, 15, 16}));

        it = list.emplace(list.begin() + 8, 8);
        ASSERT_EQ(it, list.begin() + 8);
        ASSERT_EQ(list.capacity(), 32u);
        ASSERT_EQ(list.size(), 17u);
        ASSERT_EQ(list, (IL<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}));
    }
    {
        qc::List<NonTrivial> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        NonTrivial::reset();
        NonTrivial * it{list.emplace(list.end(), 4)};
        ASSERT_EQ(NonTrivial::contructions, 1);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<NonTrivial>{4}));

        NonTrivial::reset();
        it = list.emplace(list.begin(), 1);
        ASSERT_EQ(NonTrivial::contructions, 2);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 1);
        ASSERT_EQ(NonTrivial::destructions, 1);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 2u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 4}));

        NonTrivial::reset();
        it = list.emplace(list.begin() + 1, 3);
        ASSERT_EQ(NonTrivial::contructions, 2);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 1);
        ASSERT_EQ(NonTrivial::destructions, 1);
        ASSERT_EQ(it, list.begin() + 1);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 3, 4}));

        NonTrivial::reset();
        it = list.emplace(list.begin() + 1, 2);
        ASSERT_EQ(NonTrivial::contructions, 2);
        ASSERT_EQ(NonTrivial::assignments, 1);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 2);
        ASSERT_EQ(NonTrivial::destructions, 1);
        ASSERT_EQ(it, list.begin() + 1);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4}));

        NonTrivial::reset();
        list.emplace(list.end(), 5);
        list.emplace(list.end(), 6);
        list.emplace(list.end(), 7);
        list.emplace(list.end(), 8);
        list.emplace(list.end(), 9);
        list.emplace(list.end(), 10);
        list.emplace(list.end(), 11);
        list.emplace(list.end(), 12);
        list.emplace(list.end(), 13);
        list.emplace(list.end(), 14);
        list.emplace(list.end(), 15);
        list.emplace(list.end(), 16);
        ASSERT_EQ(NonTrivial::contructions, 12);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 16u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}));

        NonTrivial::reset();
        it = list.emplace(list.begin(), 0);
        ASSERT_EQ(NonTrivial::contructions, 17);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 16);
        ASSERT_EQ(NonTrivial::destructions, 16);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 32u);
        ASSERT_EQ(list.size(), 17u);
        ASSERT_EQ(list, (IL<NonTrivial>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}));

        list.pop();
        list.shrink();
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 16u);
        ASSERT_EQ(list, (IL<NonTrivial>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}));

        NonTrivial::reset();
        it = list.emplace(list.end(), 16);
        ASSERT_EQ(NonTrivial::contructions, 17);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 16);
        ASSERT_EQ(NonTrivial::destructions, 16);
        ASSERT_EQ(it, list.end() - 1);
        ASSERT_EQ(list.capacity(), 32u);
        ASSERT_EQ(list.size(), 17u);
        ASSERT_EQ(list, (IL<NonTrivial>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}));

        list.erase(list.begin() + 8);
        list.shrink();
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 16u);
        ASSERT_EQ(list, (IL<NonTrivial>{0, 1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 12, 13, 14, 15, 16}));

        NonTrivial::reset();
        it = list.emplace(list.begin() + 8, 8);
        ASSERT_EQ(NonTrivial::contructions, 17);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 16);
        ASSERT_EQ(NonTrivial::destructions, 16);
        ASSERT_EQ(it, list.begin() + 8);
        ASSERT_EQ(list.capacity(), 32u);
        ASSERT_EQ(list.size(), 17u);
        ASSERT_EQ(list, (IL<NonTrivial>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}));
    }
}

// Basically the same as emplace
TEST(List, insertOne)
{
    {
        int v;
        qc::List<int> list{};
        list.insert(list.end(), 3);
        list.insert(list.end(), v = 4);
        list.insert(list.begin(), 1);
        list.insert(list.begin() + 1, v = 2);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3, 4}));
    }
    {
        qc::List<NonTrivial> list{};

        NonTrivial::reset();
        list.insert(list.end(), 3);
        ASSERT_EQ(NonTrivial::contructions, 2);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 1);
        ASSERT_EQ(NonTrivial::destructions, 1);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<NonTrivial>{3}));

        NonTrivial v{4};
        NonTrivial::reset();
        list.insert(list.end(), v);
        ASSERT_EQ(NonTrivial::contructions, 1);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 1);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 2u);
        ASSERT_EQ(list, (IL<NonTrivial>{3, 4}));

        NonTrivial::reset();
        list.insert(list.begin(), 1);
        ASSERT_EQ(NonTrivial::contructions, 3);
        ASSERT_EQ(NonTrivial::assignments, 1);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 3);
        ASSERT_EQ(NonTrivial::destructions, 2);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 3, 4}));

        v = 2;
        NonTrivial::reset();
        list.insert(list.begin() + 1, v);
        ASSERT_EQ(NonTrivial::contructions, 2);
        ASSERT_EQ(NonTrivial::assignments, 1);
        ASSERT_EQ(NonTrivial::copies, 1);
        ASSERT_EQ(NonTrivial::moves, 2);
        ASSERT_EQ(NonTrivial::destructions, 1);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4}));
    }
}

TEST(List, insertN)
{
    {
        qc::List<int> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        int * it{list.insert(list.begin(), 0u, 1)};
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        it = list.insert(list.begin(), 1u, 1);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<int>{1}));

        list.clear();
        it = list.insert(list.begin(), 3u, 2);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<int>{2, 2, 2}));

        it = list.insert(list.begin(), 0u, 3);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<int>{2, 2, 2}));

        it = list.insert(list.end(), 0u, 3);
        ASSERT_EQ(it, list.end());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<int>{2, 2, 2}));

        it = list.insert(list.begin(), 3u, 1);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 6u);
        ASSERT_EQ(list, (IL<int>{1, 1, 1, 2, 2, 2}));

        it = list.insert(list.end(), 3u, 4);
        ASSERT_EQ(it, list.end() - 3);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 9u);
        ASSERT_EQ(list, (IL<int>{1, 1, 1, 2, 2, 2, 4, 4, 4}));

        it = list.insert(list.end() - 3, 3u, 3);
        ASSERT_EQ(it, list.end() - 6);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<int>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}));

        list.shrink();
        ASSERT_EQ(list.capacity(), 12u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<int>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}));

        it = list.insert(list.begin(), 0u, 0);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 12u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<int>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}));

        it = list.insert(list.begin(), 3u, 0);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 24u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<int>{0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}));

        list.erase(list.begin(), list.begin() + 3);
        list.shrink();
        ASSERT_EQ(list.capacity(), 12u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<int>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}));

        it = list.insert(list.end(), 3u, 0);
        ASSERT_EQ(it, list.end() - 3);
        ASSERT_EQ(list.capacity(), 24u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<int>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 0, 0, 0}));

        list.erase(list.end() - 3, list.end());
        list.shrink();
        ASSERT_EQ(list.capacity(), 12u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<int>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}));

        it = list.insert(list.begin() + 6, 3u, 0);
        ASSERT_EQ(it, list.begin() + 6);
        ASSERT_EQ(list.capacity(), 24u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<int>{1, 1, 1, 2, 2, 2, 0, 0, 0, 3, 3, 3, 4, 4, 4}));
    }
    {
        qc::List<NonTrivial> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        NonTrivial v{1};
        NonTrivial::reset();
        NonTrivial * it{list.insert(list.begin(), 0u, v)};
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        v.v = 1;
        NonTrivial::reset();
        it = list.insert(list.begin(), 1u, v);
        ASSERT_EQ(NonTrivial::contructions, 1);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 1);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<NonTrivial>{1}));

        list.clear();
        v.v = 2;
        NonTrivial::reset();
        it = list.insert(list.begin(), 3u, v);
        ASSERT_EQ(NonTrivial::contructions, 3);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 3);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{2, 2, 2}));

        v.v = 3;
        NonTrivial::reset();
        it = list.insert(list.begin(), 0u, v);
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{2, 2, 2}));

        v.v = 3;
        NonTrivial::reset();
        it = list.insert(list.end(), 0u, v);
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(it, list.end());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{2, 2, 2}));

        v.v = 1;
        NonTrivial::reset();
        it = list.insert(list.begin(), 3u, v);
        ASSERT_EQ(NonTrivial::contructions, 3);
        ASSERT_EQ(NonTrivial::assignments, 3);
        ASSERT_EQ(NonTrivial::copies, 3);
        ASSERT_EQ(NonTrivial::moves, 3);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 6u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 1, 1, 2, 2, 2}));

        v.v = 4;
        NonTrivial::reset();
        it = list.insert(list.end(), 3u, v);
        ASSERT_EQ(NonTrivial::contructions, 3);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 3);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(it, list.end() - 3);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 9u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 1, 1, 2, 2, 2, 4, 4, 4}));

        v.v = 3;
        NonTrivial::reset();
        it = list.insert(list.end() - 3, 3u, v);
        ASSERT_EQ(NonTrivial::contructions, 3);
        ASSERT_EQ(NonTrivial::assignments, 3);
        ASSERT_EQ(NonTrivial::copies, 3);
        ASSERT_EQ(NonTrivial::moves, 3);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(it, list.end() - 6);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}));

        list.shrink();
        ASSERT_EQ(list.capacity(), 12u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}));

        v.v = 0;
        NonTrivial::reset();
        it = list.insert(list.begin(), 0u, v);
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 12u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}));

        v.v = 0;
        NonTrivial::reset();
        it = list.insert(list.begin(), 3u, v);
        ASSERT_EQ(NonTrivial::contructions, 15);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 3);
        ASSERT_EQ(NonTrivial::moves, 12);
        ASSERT_EQ(NonTrivial::destructions, 12);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 24u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<NonTrivial>{0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}));

        list.erase(list.begin(), list.begin() + 3);
        list.shrink();
        ASSERT_EQ(list.capacity(), 12u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}));

        v.v = 0;
        NonTrivial::reset();
        it = list.insert(list.end(), 3u, v);
        ASSERT_EQ(NonTrivial::contructions, 15);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 3);
        ASSERT_EQ(NonTrivial::moves, 12);
        ASSERT_EQ(NonTrivial::destructions, 12);
        ASSERT_EQ(it, list.end() - 3);
        ASSERT_EQ(list.capacity(), 24u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 0, 0, 0}));

        list.erase(list.end() - 3, list.end());
        list.shrink();
        ASSERT_EQ(list.capacity(), 12u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}));

        v.v = 0;
        NonTrivial::reset();
        it = list.insert(list.begin() + 6, 3u, v);
        ASSERT_EQ(NonTrivial::contructions, 15);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 3);
        ASSERT_EQ(NonTrivial::moves, 12);
        ASSERT_EQ(NonTrivial::destructions, 12);
        ASSERT_EQ(it, list.begin() + 6);
        ASSERT_EQ(list.capacity(), 24u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 1, 1, 2, 2, 2, 0, 0, 0, 3, 3, 3, 4, 4, 4}));
    }
}

// Initializer list overload just calls the range overload, so only using initializer lists for convenience
TEST(List, insertRange)
{
    {
        qc::List<int> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        int * it{list.insert(list.begin(), IL<int>{})};
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        it = list.insert(list.begin(), IL<int>{1});
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<int>{1}));

        list.clear();
        it = list.insert(list.begin(), IL<int>{1, 2, 3});
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3}));

        it = list.insert(list.begin(), IL<int>{});
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3}));

        it = list.insert(list.end(), IL<int>{});
        ASSERT_EQ(it, list.end());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3}));

        it = list.insert(list.begin(), IL<int>{4, 5, 6});
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 6u);
        ASSERT_EQ(list, (IL<int>{4, 5, 6, 1, 2, 3}));

        it = list.insert(list.end(), IL<int>{7, 8, 9});
        ASSERT_EQ(it, list.end() - 3);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 9u);
        ASSERT_EQ(list, (IL<int>{4, 5, 6, 1, 2, 3, 7, 8, 9}));

        it = list.insert(list.end() - 3, IL<int>{10, 11, 12});
        ASSERT_EQ(it, list.end() - 6);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<int>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        list.shrink();
        ASSERT_EQ(list.capacity(), 12u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<int>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        it = list.insert(list.begin(), IL<int>{});
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 12u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<int>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        it = list.insert(list.begin(), IL<int>{13, 14, 15});
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 24u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<int>{13, 14, 15, 4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        list.erase(list.begin(), list.begin() + 3);
        list.shrink();
        ASSERT_EQ(list.capacity(), 12u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<int>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        it = list.insert(list.end(), IL<int>{13, 14, 15});
        ASSERT_EQ(it, list.end() - 3);
        ASSERT_EQ(list.capacity(), 24u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<int>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9, 13, 14, 15}));

        list.erase(list.end() - 3, list.end());
        list.shrink();
        ASSERT_EQ(list.capacity(), 12u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<int>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        it = list.insert(list.begin() + 6, IL<int>{13, 14, 15});
        ASSERT_EQ(it, list.begin() + 6);
        ASSERT_EQ(list.capacity(), 24u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<int>{4, 5, 6, 1, 2, 3, 13, 14, 15, 10, 11, 12, 7, 8, 9}));
    }
    {
        qc::List<NonTrivial> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        IL<NonTrivial> v{};
        NonTrivial::reset();
        NonTrivial * it{list.insert(list.begin(), v)};
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        v = {1};
        NonTrivial::reset();
        it = list.insert(list.begin(), v);
        ASSERT_EQ(NonTrivial::contructions, 1);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 1);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<NonTrivial>{1}));

        list.clear();
        v = {1, 2, 3};
        NonTrivial::reset();
        it = list.insert(list.begin(), v);
        ASSERT_EQ(NonTrivial::contructions, 3);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 3);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3}));

        v = {};
        NonTrivial::reset();
        it = list.insert(list.begin(), v);
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3}));

        v = {};
        NonTrivial::reset();
        it = list.insert(list.end(), v);
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(it, list.end());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3}));

        v = {4, 5, 6};
        NonTrivial::reset();
        it = list.insert(list.begin(), v);
        ASSERT_EQ(NonTrivial::contructions, 3);
        ASSERT_EQ(NonTrivial::assignments, 3);
        ASSERT_EQ(NonTrivial::copies, 3);
        ASSERT_EQ(NonTrivial::moves, 3);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 6u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3}));

        v = {7, 8, 9};
        NonTrivial::reset();
        it = list.insert(list.end(), v);
        ASSERT_EQ(NonTrivial::contructions, 3);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 3);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(it, list.end() - 3);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 9u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3, 7, 8, 9}));

        v = {10, 11, 12};
        NonTrivial::reset();
        it = list.insert(list.end() - 3, v);
        ASSERT_EQ(NonTrivial::contructions, 3);
        ASSERT_EQ(NonTrivial::assignments, 3);
        ASSERT_EQ(NonTrivial::copies, 3);
        ASSERT_EQ(NonTrivial::moves, 3);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(it, list.end() - 6);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        list.shrink();
        ASSERT_EQ(list.capacity(), 12u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        v = {};
        NonTrivial::reset();
        it = list.insert(list.begin(), v);
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 12u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        v = {13, 14, 15};
        NonTrivial::reset();
        it = list.insert(list.begin(), v);
        ASSERT_EQ(NonTrivial::contructions, 15);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 3);
        ASSERT_EQ(NonTrivial::moves, 12);
        ASSERT_EQ(NonTrivial::destructions, 12);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 24u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<NonTrivial>{13, 14, 15, 4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        list.erase(list.begin(), list.begin() + 3);
        list.shrink();
        ASSERT_EQ(list.capacity(), 12u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        v = {13, 14, 15};
        NonTrivial::reset();
        it = list.insert(list.end(), v);
        ASSERT_EQ(NonTrivial::contructions, 15);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 3);
        ASSERT_EQ(NonTrivial::moves, 12);
        ASSERT_EQ(NonTrivial::destructions, 12);
        ASSERT_EQ(it, list.end() - 3);
        ASSERT_EQ(list.capacity(), 24u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9, 13, 14, 15}));

        list.erase(list.end() - 3, list.end());
        list.shrink();
        ASSERT_EQ(list.capacity(), 12u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        v = {13, 14, 15};
        NonTrivial::reset();
        it = list.insert(list.begin() + 6, v);
        ASSERT_EQ(NonTrivial::contructions, 15);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 3);
        ASSERT_EQ(NonTrivial::moves, 12);
        ASSERT_EQ(NonTrivial::destructions, 12);
        ASSERT_EQ(it, list.begin() + 6);
        ASSERT_EQ(list.capacity(), 24u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3, 13, 14, 15, 10, 11, 12, 7, 8, 9}));
    }
}

TEST(List, pop)
{
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

TEST(List, popN)
{
    {
        qc::List<int> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        list.pop(0u);
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        list = {1, 2, 3, 4, 5, 6};
        ASSERT_EQ(list.capacity(), 6u);
        ASSERT_EQ(list.size(), 6u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3, 4, 5, 6}));

        list.pop(0u);
        ASSERT_EQ(list.capacity(), 6u);
        ASSERT_EQ(list.size(), 6u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3, 4, 5, 6}));

        list.pop(1u);
        ASSERT_EQ(list.capacity(), 6u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3, 4, 5}));

        list.pop(2u);
        ASSERT_EQ(list.capacity(), 6u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3}));

        list.pop(3u);
        ASSERT_EQ(list.capacity(), 6u);
        ASSERT_EQ(list.size(), 0u);

        list.pop(0u);
        ASSERT_EQ(list.capacity(), 6u);
        ASSERT_EQ(list.size(), 0u);
    }
    {
        qc::List<NonTrivial> list{1, 2, 3};

        NonTrivial::reset();
        list.pop(2u);
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 2);
    }
}

TEST(List, erase)
{
    {
        qc::List<int> list{1, 2, 3, 4, 5};
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3, 4, 5}));

        int * it{list.erase(list.end() - 1)};
        ASSERT_EQ(it, list.end());
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3, 4}));

        ASSERT_EQ(*list.erase(list.begin() + 2), 4);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<int>{1, 2, 4}));

        ASSERT_EQ(*list.erase(list.begin()), 2);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 2u);
        ASSERT_EQ(list, (IL<int>{2, 4}));

        ASSERT_EQ(*list.erase(list.begin()), 4);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<int>{4}));

        it = list.erase(list.begin());
        ASSERT_EQ(it, list.end());
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 0u);
    }
    {
        qc::List<NonTrivial> list{1, 2, 3, 4, 5};
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4, 5}));

        NonTrivial::reset();
        NonTrivial * it{list.erase(list.end() - 1)};
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 1);
        ASSERT_EQ(it, list.end());
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4}));

        NonTrivial::reset();
        ASSERT_EQ(list.erase(list.begin() + 2)->v, 4);
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 1);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 1);
        ASSERT_EQ(NonTrivial::destructions, 1);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 4}));

        NonTrivial::reset();
        ASSERT_EQ(list.erase(list.begin())->v, 2);
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 2);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 2);
        ASSERT_EQ(NonTrivial::destructions, 1);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 2u);
        ASSERT_EQ(list, (IL<NonTrivial>{2, 4}));

        NonTrivial::reset();
        ASSERT_EQ(list.erase(list.begin())->v, 4);
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 1);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 1);
        ASSERT_EQ(NonTrivial::destructions, 1);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<NonTrivial>{4}));

        NonTrivial::reset();
        it = list.erase(list.begin());
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 1);
        ASSERT_EQ(it, list.end());
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 0u);
    }
    {
        qc::List<int> list{1, 2, 3, 4, 5};
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3, 4, 5}));

        ASSERT_EQ(list.erase(list.begin(), list.begin()), list.begin());
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3, 4, 5}));

        ASSERT_EQ(list.erase(list.end(), list.end()), list.end());
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3, 4, 5}));

        int * it{list.erase(list.begin(), list.end())};
        ASSERT_EQ(it, list.end());
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 0u);
    }
    {
        qc::List<NonTrivial> list{1, 2, 3, 4, 5};
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4, 5}));

        NonTrivial::reset();
        ASSERT_EQ(list.erase(list.begin(), list.begin()), list.begin());
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4, 5}));

        NonTrivial::reset();
        ASSERT_EQ(list.erase(list.end(), list.end()), list.end());
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 0);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4, 5}));

        NonTrivial::reset();
        NonTrivial * it{list.erase(list.begin(), list.end())};
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 5);
        ASSERT_EQ(it, list.end());
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 0u);
    }
    {
        qc::List<int> list{1, 2, 3, 4, 5, 6, 7, 8};
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 8u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3, 4, 5, 6, 7, 8}));

        ASSERT_EQ(*list.erase(list.begin(), list.begin() + 1), 2);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 7u);
        ASSERT_EQ(list, (IL<int>{2, 3, 4, 5, 6, 7, 8}));

        int * it{list.erase(list.end() - 1, list.end())};
        ASSERT_EQ(it, list.end());
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 6u);
        ASSERT_EQ(list, (IL<int>{2, 3, 4, 5, 6, 7}));

        ASSERT_EQ(*list.erase(list.begin() + 1, list.end() - 1), 7);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 2u);
        ASSERT_EQ(list, (IL<int>{2, 7}));
    }
    {
        qc::List<NonTrivial> list{1, 2, 3, 4, 5, 6, 7, 8};
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 8u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4, 5, 6, 7, 8}));

        NonTrivial::reset();
        ASSERT_EQ(list.erase(list.begin(), list.begin() + 1)->v, 2);
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 7);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 7);
        ASSERT_EQ(NonTrivial::destructions, 1);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 7u);
        ASSERT_EQ(list, (IL<NonTrivial>{2, 3, 4, 5, 6, 7, 8}));

        NonTrivial::reset();
        NonTrivial * it{list.erase(list.end() - 1, list.end())};
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 0);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 0);
        ASSERT_EQ(NonTrivial::destructions, 1);
        ASSERT_EQ(it, list.end());
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 6u);
        ASSERT_EQ(list, (IL<NonTrivial>{2, 3, 4, 5, 6, 7}));

        NonTrivial::reset();
        ASSERT_EQ(list.erase(list.begin() + 1, list.end() - 1)->v, 7);
        ASSERT_EQ(NonTrivial::contructions, 0);
        ASSERT_EQ(NonTrivial::assignments, 1);
        ASSERT_EQ(NonTrivial::copies, 0);
        ASSERT_EQ(NonTrivial::moves, 1);
        ASSERT_EQ(NonTrivial::destructions, 4);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 2u);
        ASSERT_EQ(list, (IL<NonTrivial>{2, 7}));
    }
}

TEST(List, eraseIf)
{
    {
        qc::List<int> list{};

        ASSERT_EQ(list.eraseIf([](int) { return true; }), 0u);
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        list = {1, 2, 3, 4, 5};

        ASSERT_EQ(list.eraseIf([](int) { return false; }), 0u);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<int>{1, 2, 3, 4, 5}));

        ASSERT_EQ(list.eraseIf([](int) { return true; }), 5u);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 0u);

        list = {1, 2, 3, 4, 5};

        ASSERT_EQ(list.eraseIf([](int v) { return v == 1; }), 1u);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<int>{2, 3, 4, 5}));

        ASSERT_EQ(list.eraseIf([](int v) { return v == 5; }), 1u);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<int>{2, 3, 4}));

        ASSERT_EQ(list.eraseIf([](int v) { return v == 3; }), 1u);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 2u);
        ASSERT_EQ(list, (IL<int>{2, 4}));

        list = {1, 2, 3, 4, 5};

        ASSERT_EQ(list.eraseIf([](int v) { return v > 1 && v < 5; }), 3u);
        ASSERT_EQ(list.capacity(), 5u);
        ASSERT_EQ(list.size(), 2u);
        ASSERT_EQ(list, (IL<int>{1, 5}));

        list = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        ASSERT_EQ(list.eraseIf([](int v) { return v > 1 && v < 5; }), 6u);
        ASSERT_EQ(list.capacity(), 10u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<int>{1, 5, 1, 5}));

        list = {1, 2, 3, 4, 5, 6, 7, 8};

        ASSERT_EQ(list.eraseIf([](int v) { return v % 2 == 0; }), 4u);
        ASSERT_EQ(list.capacity(), 10u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<int>{1, 3, 5, 7}));

        list = {1, 2, 3, 4, 5, 6, 7, 8};

        ASSERT_EQ(list.eraseIf([](int v) { return v % 2 == 1; }), 4u);
        ASSERT_EQ(list.capacity(), 10u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<int>{2, 4, 6, 8}));
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

TEST(List, typeWithInitializerListConstructor)
{
    {
        qc::List<std::vector<size_t>> list{};
        list.push(4u, 5u);
        ASSERT_EQ(list.front(), (std::vector<size_t>{5u, 5u, 5u, 5u}));

        list.emplace(list.end(), 2u, 3u);
        ASSERT_EQ(list.back(), (std::vector<size_t>{3u, 3u}));
    }
}
