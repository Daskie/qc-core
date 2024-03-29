#include <qc-core/list.hpp>

#include <gtest/gtest.h>

template <typename T> using IL = std::initializer_list<T>;

using namespace qc::primitives;

struct NonTrivial
{
    inline static u32 contructions{0u};
    inline static u32 assignments{0u};
    inline static u32 copies{0u};
    inline static u32 moves{0u};
    inline static u32 destructions{0u};

    static void reset() { contructions = assignments = copies = moves = destructions = 0u; }

    s32 v{};

    NonTrivial() { ++contructions; }
    NonTrivial(const s32 v_) : v{v_} { ++contructions; }
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
        qc::List<s32> list{};
        ASSERT_TRUE(list.empty());
        ASSERT_EQ(list.size(), 0u);
        ASSERT_EQ(list.capacity(), 0u);
    }
    {
        NonTrivial::reset();
        qc::List<NonTrivial> list{};
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_TRUE(list.empty());
        ASSERT_EQ(list.size(), 0u);
        ASSERT_EQ(list.capacity(), 0u);
    }
    {
        qc::List<s32> list(7u);
        ASSERT_TRUE(!list.empty());
        ASSERT_EQ(list.size(), 7u);
        ASSERT_EQ(list.capacity(), 8u);
    }
    {
        NonTrivial::reset();
        qc::List<NonTrivial> list(7u);
        ASSERT_EQ(NonTrivial::contructions, 7u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_TRUE(!list.empty());
        ASSERT_EQ(list.size(), 7u);
        ASSERT_EQ(list.capacity(), 8u);
    }
    {
        qc::List<s32> list(7u, 7);
        ASSERT_EQ(list.size(), 7u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list, (IL<s32>{7, 7, 7, 7, 7, 7, 7}));
    }
    {
        NonTrivial::reset();
        qc::List<NonTrivial> list(7u, 7);
        ASSERT_EQ(NonTrivial::contructions, 8u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 7u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 1u);
        ASSERT_EQ(list.size(), 7u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list, (IL<NonTrivial>{7, 7, 7, 7, 7, 7, 7}));
    }
    {
        std::vector<s32> v{1, 2, 3, 4, 5};
        qc::List<s32> list{v.begin(), v.end()};
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4, 5}));
    }
    {
        std::vector<NonTrivial> v{1, 2, 3, 4, 5};
        NonTrivial::reset();
        qc::List<NonTrivial> list{v.begin(), v.end()};
        ASSERT_EQ(NonTrivial::contructions, 5u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 5u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4, 5}));
    }
    {
        qc::List<s32> list{1, 2, 3, 4, 5};
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4, 5}));
    }
    {
        NonTrivial::reset();
        qc::List<NonTrivial> list{1, 2, 3, 4, 5};
        ASSERT_EQ(NonTrivial::contructions, 10u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 5u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 5u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4, 5}));
    }
    {
        qc::List<s32> list{1, 2};
        ASSERT_EQ(list.size(), 2u);
        ASSERT_EQ(list.capacity(), 2u);
        ASSERT_EQ(list, (IL<s32>{1, 2}));
    }
    {
        qc::List<s32> list{1};
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list.capacity(), 2u);
        ASSERT_EQ(list, (IL<s32>{1}));
    }
    {
        qc::List<s32> l1{1, 2, 3};
        ASSERT_EQ(l1.capacity(), 4u);
        ASSERT_EQ(l1.size(), 3u);
        ASSERT_EQ(l1, (IL<s32>{1, 2, 3}));
    }
    {
        NonTrivial::reset();
        qc::List<NonTrivial> l1{1, 2, 3};
        ASSERT_EQ(NonTrivial::contructions, 6u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 3u);
        ASSERT_EQ(l1.capacity(), 4u);
        ASSERT_EQ(l1.size(), 3u);
        ASSERT_EQ(l1, (IL<NonTrivial>{1, 2, 3}));
    }
    {
        qc::List<s32> l1{1, 2, 3};
        ASSERT_EQ(l1.capacity(), 4u);
        ASSERT_EQ(l1.size(), 3u);
        ASSERT_EQ(l1, (IL<s32>{1, 2, 3}));

        qc::List<s32> l2(std::move(l1));
        ASSERT_EQ(l2.capacity(), 4u);
        ASSERT_EQ(l2.size(), 3u);
        ASSERT_EQ(l2, (IL<s32>{1, 2, 3}));
        ASSERT_EQ(l1.capacity(), 0u);
        ASSERT_EQ(l1.size(), 0u);
    }
    {
        NonTrivial::reset();
        qc::List<NonTrivial> l1{1, 2, 3};
        ASSERT_EQ(NonTrivial::contructions, 6u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 3u);
        ASSERT_EQ(l1.capacity(), 4u);
        ASSERT_EQ(l1.size(), 3u);
        ASSERT_EQ(l1, (IL<NonTrivial>{1, 2, 3}));

        NonTrivial::reset();
        qc::List<NonTrivial> l2(std::move(l1));
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(l2.capacity(), 4u);
        ASSERT_EQ(l2.size(), 3u);
        ASSERT_EQ(l2, (IL<NonTrivial>{1, 2, 3}));
        ASSERT_EQ(l1.capacity(), 0u);
        ASSERT_EQ(l1.size(), 0u);
    }
}

TEST(List, assignment)
{
    {
        qc::List<s32> l1{1, 2, 3};
        ASSERT_EQ(l1.size(), 3u);
        ASSERT_EQ(l1.capacity(), 4u);

        qc::List<s32> l2{};
        ASSERT_TRUE(l2.empty());

        l2 = std::move(l1);
        ASSERT_EQ(l2.size(), 3u);
        ASSERT_EQ(l2.capacity(), 4u);
        ASSERT_EQ(l2, (IL<s32>{1, 2, 3}));
        ASSERT_EQ(l1.size(), 0u);
        ASSERT_EQ(l1.capacity(), 0u);
    }
    {
        qc::List<s32> list{9, 8, 7};

        list = {1, 2, 3, 4};
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4}));

        s32 vs[]{3, 2, 1};
        list = qc::View<s32>{vs};
        ASSERT_EQ(list, (IL<s32>{3, 2, 1}));
    }
    {
        qc::List<NonTrivial> l1{1, 2, 3};
        ASSERT_EQ(l1.size(), 3u);
        ASSERT_EQ(l1.capacity(), 4u);

        qc::List<NonTrivial> l2{};
        ASSERT_TRUE(l2.empty());

        NonTrivial::reset();
        l2 = std::move(l1);
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(l2.size(), 3u);
        ASSERT_EQ(l2.capacity(), 4u);
        ASSERT_EQ(l2, (IL<NonTrivial>{1, 2, 3}));
        ASSERT_EQ(l1.size(), 0u);
        ASSERT_EQ(l1.capacity(), 0u);
    }
    {
        qc::List<NonTrivial> list{9, 8, 7};

        NonTrivial::reset();
        list = {1, 2, 3};
        ASSERT_EQ(NonTrivial::contructions, 6u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 6u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3}));

        NonTrivial vs[]{2, 2, 2, 2};
        NonTrivial::reset();
        list = qc::CView<NonTrivial>{vs};
        ASSERT_EQ(NonTrivial::contructions, 4u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 4u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{2, 2, 2, 2}));
    }
    {
        qc::List<NonTrivial> list{9, 8, 7};

        list = {1, 2, 3};
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3}));

        NonTrivial vs[]{2, 2, 2, 2};
        list = qc::CView<NonTrivial>{vs};
        ASSERT_EQ(list, (IL<NonTrivial>{2, 2, 2, 2}));
    }
    {
        qc::List<NonTrivial> list{9, 8, 7};

        NonTrivial::reset();
        list.assign(6u, 3);
        ASSERT_EQ(NonTrivial::contructions, 7u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 6u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 4u);
        ASSERT_EQ(list, (IL<NonTrivial>{3, 3, 3, 3, 3, 3}));

        std::vector<NonTrivial> vs{3, 2, 1};
        NonTrivial::reset();
        list.assign(vs.cbegin(), vs.cend());
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 6u);
        ASSERT_EQ(list, (IL<NonTrivial>{3, 2, 1}));

        NonTrivial::reset();
        list = {1, 2, 3, 4};
        ASSERT_EQ(NonTrivial::contructions, 8u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 4u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 7u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4}));

        NonTrivial::reset();
        list = qc::View<NonTrivial>{vs.data(), u32(vs.size())};
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 4u);
        ASSERT_EQ(list, (IL<NonTrivial>{3, 2, 1}));
    }
}

TEST(List, destruction)
{
    {
        NonTrivial::reset();
        qc::List<NonTrivial> list{1, 2, 3};
        ASSERT_EQ(NonTrivial::contructions, 6u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 3u);

        NonTrivial::reset();
    }
    ASSERT_EQ(NonTrivial::contructions, 0u);
    ASSERT_EQ(NonTrivial::assignments, 0u);
    ASSERT_EQ(NonTrivial::copies, 0u);
    ASSERT_EQ(NonTrivial::moves, 0u);
    ASSERT_EQ(NonTrivial::destructions, 3u);
}

TEST(List, operatorBool)
{
    qc::List<s32> list{};
    ASSERT_FALSE(list);

    list.push(1);
    ASSERT_TRUE(list);

    list.clear();
    ASSERT_FALSE(list);
}

TEST(List, operatorView)
{
    qc::List<s32> list{1, 2, 3};

    {
        const qc::View<s32> view{list};
        ASSERT_EQ(view.data, list.data());
        ASSERT_EQ(view.size, list.size());
    }

    {
        const qc::CView<s32> view{list};
        ASSERT_EQ(view.data, list.data());
        ASSERT_EQ(view.size, list.size());
    }
}

TEST(List, assign)
{
    {
        qc::List<s32> list{9, 8, 7};

        list.assign(6u, 3);
        ASSERT_EQ(list, (IL<s32>{3, 3, 3, 3, 3, 3}));

        std::vector<s32> vs{3, 2, 1};
        list.assign(vs.cbegin(), vs.cend());
        ASSERT_EQ(list, (IL<s32>{3, 2, 1}));
    }
    {
        qc::List<NonTrivial> list{9, 8, 7};

        NonTrivial::reset();
        list.assign(6u, 3);
        ASSERT_EQ(NonTrivial::contructions, 7u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 6u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 4u);
        ASSERT_EQ(list, (IL<NonTrivial>{3, 3, 3, 3, 3, 3}));

        std::vector<NonTrivial> vs{3, 2, 1};
        NonTrivial::reset();
        list.assign(vs.cbegin(), vs.cend());
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 6u);
        ASSERT_EQ(list, (IL<NonTrivial>{3, 2, 1}));
    }
}

TEST(List, fill)
{
    qc::List<s32> list{};
    list.fill(7);
    ASSERT_FALSE(list);

    list.resize(17u);
    list.fill(8);
    for (const s32 v : list) ASSERT_EQ(v, 8);
}

TEST(List, reserve)
{
    {
        qc::List<s32> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_TRUE(list.empty());

        list.reserve(0u);
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_TRUE(list.empty());

        list.reserve(1u);
        ASSERT_EQ(list.capacity(), 2u);
        ASSERT_TRUE(list.empty());

        list.reserve(0u);
        ASSERT_EQ(list.capacity(), 2u);
        ASSERT_TRUE(list.empty());

        list.reserve(17u);
        ASSERT_EQ(list.capacity(), 32u);
        ASSERT_TRUE(list.empty());

        list.reserve(4u);
        ASSERT_EQ(list.capacity(), 32u);
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
            ASSERT_EQ(list.capacity(), 2u);
            ASSERT_TRUE(list.empty());

            list.reserve(0u);
            ASSERT_EQ(list.capacity(), 2u);
            ASSERT_TRUE(list.empty());

            list.reserve(17u);
            ASSERT_EQ(list.capacity(), 32u);
            ASSERT_TRUE(list.empty());

            list.reserve(4u);
            ASSERT_EQ(list.capacity(), 32u);
            ASSERT_TRUE(list.empty());
        }
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
    }
}

TEST(List, resize)
{
    {
        qc::List<s32> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        list.resize(3u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);

        list.resize(1u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 1u);

        list.resize(5u, 5);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 5u);
        list[0u] = 0;
        ASSERT_EQ(list, (IL<s32>{0, 5, 5, 5, 5}));

        list.resize(3u, 3);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<s32>{0, 5, 5}));

        list.resize(0u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 0u);

        list.resize(3u);
        ASSERT_EQ(list, (IL<s32>{0, 5, 5}));
    }
    {
        qc::List<NonTrivial> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        NonTrivial::reset();
        list.resize(3u);
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);

        NonTrivial::reset();
        list.resize(1u);
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 2u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 1u);

        NonTrivial::reset();
        list.resize(5u, 5);
        ASSERT_EQ(NonTrivial::contructions, 6u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 4u);
        ASSERT_EQ(NonTrivial::moves, 1u);
        ASSERT_EQ(NonTrivial::destructions, 2u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<NonTrivial>{0, 5, 5, 5, 5}));

        NonTrivial::reset();
        list.resize(3u, 3);
        ASSERT_EQ(NonTrivial::contructions, 1u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 3u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{0, 5, 5}));

        NonTrivial::reset();
        list.resize(0u);
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 3u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 0u);

        list.resize(3u);
        ASSERT_EQ(list, (IL<NonTrivial>{0, 0, 0}));
    }
}

TEST(List, shrink)
{
    {
        qc::List<s32> list(8u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 8u);

        list.reserve(10u);
        ASSERT_EQ(list.capacity(), 16u);
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
        qc::List<s32> list(14u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 14u);

        list.clear();
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 0u);
    }
    {
        {
            qc::List<NonTrivial> list(14u);
            ASSERT_EQ(list.capacity(), 16u);
            ASSERT_EQ(list.size(), 14u);

            NonTrivial::reset();

            list.clear();
            ASSERT_EQ(list.capacity(), 16u);
            ASSERT_EQ(list.size(), 0u);
        }
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 14u);
    }
}

TEST(List, push)
{
    {
        qc::List<s32> list{};
        const s32 v{1};
        ASSERT_EQ(list.push(v), 1);
        ASSERT_EQ(list.capacity(), 2u);
        ASSERT_EQ(list.size(), 1u);
    }
    {
        qc::List<NonTrivial> list{};
        const NonTrivial v{1};
        ASSERT_EQ(list.push(v).v, 1);
        ASSERT_EQ(list.capacity(), 2u);
        ASSERT_EQ(list.size(), 1u);
    }
    {
        qc::List<s32> list{};
        ASSERT_EQ(list.push(1), 1);
        ASSERT_EQ(list.capacity(), 2u);
        ASSERT_EQ(list.size(), 1u);
    }
    {
        qc::List<NonTrivial> list{};
        ASSERT_EQ(list.push(NonTrivial{1}).v, 1);
        ASSERT_EQ(list.capacity(), 2u);
        ASSERT_EQ(list.size(), 1u);
    }
    {
        qc::List<s32> list{};
        const qc::View<s32> view{list.push(3u, 1)};
        ASSERT_EQ(view.data, list.data());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list, (IL<s32>{1, 1, 1}));
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
    }
    {
        qc::List<s32> list{};
        const qc::View<s32> view{list.push(3u, 1)};
        ASSERT_EQ(view.data, list.data());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list, (IL<s32>{1, 1, 1}));
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
    }
    {
        qc::List<s32> list{};
        const std::vector<s32> vs{1, 2, 3};
        const qc::View<s32> view{list.push(vs.cbegin(), vs.cend())};
        ASSERT_EQ(view.data, list.data());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3}));
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
    }
    {
        qc::List<NonTrivial> list{};
        const std::vector<NonTrivial> vs{1, 2, 3};
        const qc::View<NonTrivial> view{list.push(vs.cbegin(), vs.cend())};
        ASSERT_EQ(view.data, list.data());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3}));
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
    }
    {
        qc::List<s32> list{};
        const qc::View<s32> view{list.push(IL<s32>{1, 2, 3})};
        ASSERT_EQ(view.data, list.data());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3}));
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
    }
    {
        qc::List<NonTrivial> list{};
        const qc::View<NonTrivial> view{list.push(IL<NonTrivial>{1, 2, 3})};
        ASSERT_EQ(view.data, list.data());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3}));
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
    }
    {
        qc::List<s32> list{};
        const qc::List<s32> vs{1, 2, 3};
        const qc::View<s32> view{list.push(vs.cview())};
        ASSERT_EQ(view.data, list.data());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3}));
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
    }
    {
        qc::List<NonTrivial> list{};
        const qc::List<NonTrivial> vs{1, 2, 3};
        const qc::View<NonTrivial> view{list.push(vs.cview())};
        ASSERT_EQ(view.data, list.data());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3}));
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
    }
}

TEST(List, empush)
{
    {
        qc::List<s32> list{};
        list.reserve(4u);

        ASSERT_EQ(list.empush(1), 1);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 1u);

        list.pop();
        ASSERT_EQ(list.empush(), 0);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 1u);
        list.back() = 1;

        ASSERT_EQ(list.empush(2), 2);
        ASSERT_EQ(list.empush(3), 3);
        ASSERT_EQ(list.empush(4), 4);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4}));

        ASSERT_EQ(list.empush(5), 5);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4, 5}));

        ASSERT_EQ(list.empush(6), 6);
        ASSERT_EQ(list.empush(7), 7);
        ASSERT_EQ(list.empush(8), 8);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 8u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4, 5, 6, 7, 8}));

        ASSERT_EQ(list.empush(9), 9);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 9u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4, 5, 6, 7, 8, 9}));
    }
    {
        qc::List<NonTrivial> list{};
        list.reserve(4u);

        NonTrivial::reset();
        ASSERT_EQ(list.empush(1).v, 1);
        ASSERT_EQ(NonTrivial::contructions, 1u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 1u);

        list.pop();
        ASSERT_EQ(list.empush().v, 0);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 1u);
        list.back().v = 1;

        NonTrivial::reset();
        ASSERT_EQ(list.empush(2).v, 2);
        ASSERT_EQ(list.empush(3).v, 3);
        ASSERT_EQ(list.empush(4).v, 4);
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4}));

        NonTrivial::reset();
        ASSERT_EQ(list.empush(5).v, 5);
        ASSERT_EQ(NonTrivial::contructions, 5u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 4u);
        ASSERT_EQ(NonTrivial::destructions, 4u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4, 5}));

        NonTrivial::reset();
        ASSERT_EQ(list.empush(6).v, 6);
        ASSERT_EQ(list.empush(7).v, 7);
        ASSERT_EQ(list.empush(8).v, 8);
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 8u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4, 5, 6, 7, 8}));

        NonTrivial::reset();
        ASSERT_EQ(list.empush(9).v, 9);
        ASSERT_EQ(NonTrivial::contructions, 9u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 8u);
        ASSERT_EQ(NonTrivial::destructions, 8u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 9u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4, 5, 6, 7, 8, 9}));
    }
}

TEST(List, bump)
{
    {
        qc::List<s32> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        list.bump() = 1;
        ASSERT_EQ(list.capacity(), 2u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<s32>{1}));

        list.bump() = 2;
        ASSERT_EQ(list.capacity(), 2u);
        ASSERT_EQ(list.size(), 2u);
        ASSERT_EQ(list, (IL<s32>{1, 2}));

        for (s32 & v : list.bump(2u)) v = 3;
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 3}));

        list.bump(1u).front() = 4;
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 3, 4}));

        list.clear();

        ASSERT_EQ(list.bump(), 1);
    }
    {
        qc::List<NonTrivial> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        list.bump().v = 1;
        ASSERT_EQ(list.capacity(), 2u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<NonTrivial>{1}));

        list.bump() = 2;
        ASSERT_EQ(list.capacity(), 2u);
        ASSERT_EQ(list.size(), 2u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2}));

        for (NonTrivial & v : list.bump(2u)) v.v = 3;
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 3}));

        list.bump(1u).front().v = 4;
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 3, 4}));

        list.clear();

        ASSERT_EQ(list.bump().v, 0);
    }
}

TEST(List, emplace)
{
    {
        qc::List<s32> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        s32 * it{list.emplace(list.end(), 4)};
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 2u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<s32>{4}));

        it = list.emplace(list.begin(), 1);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 2u);
        ASSERT_EQ(list.size(), 2u);
        ASSERT_EQ(list, (IL<s32>{1, 4}));

        it = list.emplace(list.begin() + 1, 3);
        ASSERT_EQ(it, list.begin() + 1);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<s32>{1, 3, 4}));

        it = list.emplace(list.begin() + 1, 2);
        ASSERT_EQ(it, list.begin() + 1);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4}));

        list.emplace(list.end(), 5);
        list.emplace(list.end(), 6);
        list.emplace(list.end(), 7);
        list.emplace(list.end(), 8);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 8u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4, 5, 6, 7, 8}));

        it = list.emplace(list.begin(), 0);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 9u);
        ASSERT_EQ(list, (IL<s32>{0, 1, 2, 3, 4, 5, 6, 7, 8}));

        list.pop();
        list.shrink();
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 8u);
        ASSERT_EQ(list, (IL<s32>{0, 1, 2, 3, 4, 5, 6, 7}));

        it = list.emplace(list.end(), 8);
        ASSERT_EQ(it, list.end() - 1);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 9u);
        ASSERT_EQ(list, (IL<s32>{0, 1, 2, 3, 4, 5, 6, 7, 8}));

        list.erase(list.begin() + 4);
        list.shrink();
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 8u);
        ASSERT_EQ(list, (IL<s32>{0, 1, 2, 3, 5, 6, 7, 8}));

        it = list.emplace(list.begin() + 4, 4);
        ASSERT_EQ(it, list.begin() + 4);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 9u);
        ASSERT_EQ(list, (IL<s32>{0, 1, 2, 3, 4, 5, 6, 7, 8}));
    }
    {
        qc::List<NonTrivial> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        NonTrivial::reset();
        NonTrivial * it{list.emplace(list.end(), 4)};
        ASSERT_EQ(NonTrivial::contructions, 1u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 2u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<NonTrivial>{4}));

        NonTrivial::reset();
        it = list.emplace(list.begin(), 1);
        ASSERT_EQ(NonTrivial::contructions, 2u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 1u);
        ASSERT_EQ(NonTrivial::destructions, 1u);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 2u);
        ASSERT_EQ(list.size(), 2u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 4}));

        NonTrivial::reset();
        it = list.emplace(list.begin() + 1, 3);
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 2u);
        ASSERT_EQ(NonTrivial::destructions, 2u);
        ASSERT_EQ(it, list.begin() + 1);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 3, 4}));

        NonTrivial::reset();
        it = list.emplace(list.begin() + 1, 2);
        ASSERT_EQ(NonTrivial::contructions, 2u);
        ASSERT_EQ(NonTrivial::assignments, 1u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 2u);
        ASSERT_EQ(NonTrivial::destructions, 1u);
        ASSERT_EQ(it, list.begin() + 1);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4}));

        NonTrivial::reset();
        list.emplace(list.end(), 5);
        ASSERT_EQ(NonTrivial::contructions, 5u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 4u);
        ASSERT_EQ(NonTrivial::destructions, 4u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4, 5}));

        NonTrivial::reset();
        list.emplace(list.end(), 6);
        list.emplace(list.end(), 7);
        list.emplace(list.end(), 8);
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 8u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4, 5, 6, 7, 8}));

        NonTrivial::reset();
        it = list.emplace(list.begin(), 0);
        ASSERT_EQ(NonTrivial::contructions, 9u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 8u);
        ASSERT_EQ(NonTrivial::destructions, 8u);
        ASSERT_EQ(it, list.begin());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 9u);
        ASSERT_EQ(list, (IL<NonTrivial>{0, 1, 2, 3, 4, 5, 6, 7, 8}));

        list.pop();
        list.shrink();
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 8u);
        ASSERT_EQ(list, (IL<NonTrivial>{0, 1, 2, 3, 4, 5, 6, 7}));

        NonTrivial::reset();
        it = list.emplace(list.end(), 8);
        ASSERT_EQ(NonTrivial::contructions, 9u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 8u);
        ASSERT_EQ(NonTrivial::destructions, 8u);
        ASSERT_EQ(it, list.end() - 1);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 9u);
        ASSERT_EQ(list, (IL<NonTrivial>{0, 1, 2, 3, 4, 5, 6, 7, 8}));

        list.erase(list.begin() + 4);
        list.shrink();
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 8u);
        ASSERT_EQ(list, (IL<NonTrivial>{0, 1, 2, 3, 5, 6, 7, 8}));

        NonTrivial::reset();
        it = list.emplace(list.begin() + 4, 4);
        ASSERT_EQ(NonTrivial::contructions, 9u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 8u);
        ASSERT_EQ(NonTrivial::destructions, 8u);
        ASSERT_EQ(it, list.begin() + 4);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 9u);
        ASSERT_EQ(list, (IL<NonTrivial>{0, 1, 2, 3, 4, 5, 6, 7, 8}));
    }
}

// Basically the same as emplace
TEST(List, insertOne)
{
    {
        s32 v;
        qc::List<s32> list{};
        list.insert(list.end(), 3);
        list.insert(list.end(), v = 4);
        list.insert(list.begin(), 1);
        list.insert(list.begin() + 1, v = 2);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4}));
    }
    {
        qc::List<NonTrivial> list{};
        list.reserve(4u);

        NonTrivial::reset();
        list.insert(list.end(), 3);
        ASSERT_EQ(NonTrivial::contructions, 2u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 1u);
        ASSERT_EQ(NonTrivial::destructions, 1u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<NonTrivial>{3}));

        NonTrivial v{4};
        NonTrivial::reset();
        list.insert(list.end(), v);
        ASSERT_EQ(NonTrivial::contructions, 1u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 1u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 2u);
        ASSERT_EQ(list, (IL<NonTrivial>{3, 4}));

        NonTrivial::reset();
        list.insert(list.begin(), 1);
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 1u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 3u);
        ASSERT_EQ(NonTrivial::destructions, 2u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 3, 4}));

        v = 2;
        NonTrivial::reset();
        list.insert(list.begin() + 1, v);
        ASSERT_EQ(NonTrivial::contructions, 2u);
        ASSERT_EQ(NonTrivial::assignments, 1u);
        ASSERT_EQ(NonTrivial::copies, 1u);
        ASSERT_EQ(NonTrivial::moves, 2u);
        ASSERT_EQ(NonTrivial::destructions, 1u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4}));
    }
}

TEST(List, insertN)
{
    {
        qc::List<s32> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        qc::View<s32> view{list.insert(list.begin(), 0u, 1)};
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 0u);
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        view = list.insert(list.begin(), 1u, 1);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 1u);
        ASSERT_EQ(list.capacity(), 2u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<s32>{1}));

        list.clear();
        view = list.insert(list.begin(), 3u, 2);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<s32>{2, 2, 2}));

        view = list.insert(list.begin(), 0u, 3);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 0u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<s32>{2, 2, 2}));

        view = list.insert(list.end(), 0u, 3);
        ASSERT_EQ(view.data, list.end());
        ASSERT_EQ(view.size, 0u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<s32>{2, 2, 2}));

        view = list.insert(list.begin(), 3u, 1);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 6u);
        ASSERT_EQ(list, (IL<s32>{1, 1, 1, 2, 2, 2}));

        view = list.insert(list.end(), 3u, 4);
        ASSERT_EQ(view.data, list.end() - 3);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 9u);
        ASSERT_EQ(list, (IL<s32>{1, 1, 1, 2, 2, 2, 4, 4, 4}));

        view = list.insert(list.end() - 3, 3u, 3);
        ASSERT_EQ(view.data, list.end() - 6);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<s32>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}));

        view = list.insert(list.begin(), 0u, 0);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 0u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<s32>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}));

        view = list.insert(list.begin(), 3u, 0);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<s32>{0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}));

        list.erase(list.begin(), list.begin() + 3);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<s32>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}));

        view = list.insert(list.end(), 3u, 0);
        ASSERT_EQ(view.data, list.end() - 3);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<s32>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 0, 0, 0}));

        list.erase(list.end() - 3, list.end());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<s32>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}));

        view = list.insert(list.begin() + 6, 3u, 0);
        ASSERT_EQ(view.data, list.begin() + 6);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<s32>{1, 1, 1, 2, 2, 2, 0, 0, 0, 3, 3, 3, 4, 4, 4}));
    }
    {
        qc::List<NonTrivial> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        NonTrivial v{1};
        NonTrivial::reset();
        qc::View<NonTrivial> view{list.insert(list.begin(), 0u, v)};
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 0u);
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        v.v = 1;
        NonTrivial::reset();
        view = list.insert(list.begin(), 1u, v);
        ASSERT_EQ(NonTrivial::contructions, 1u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 1u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 1u);
        ASSERT_EQ(list.capacity(), 2u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<NonTrivial>{1}));

        list.clear();
        v.v = 2;
        NonTrivial::reset();
        view = list.insert(list.begin(), 3u, v);
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{2, 2, 2}));

        v.v = 3;
        NonTrivial::reset();
        view = list.insert(list.begin(), 0u, v);
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 0u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{2, 2, 2}));

        v.v = 3;
        NonTrivial::reset();
        view = list.insert(list.end(), 0u, v);
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.end());
        ASSERT_EQ(view.size, 0u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{2, 2, 2}));

        v.v = 1;
        NonTrivial::reset();
        view = list.insert(list.begin(), 3u, v);
        ASSERT_EQ(NonTrivial::contructions, 6u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 3u);
        ASSERT_EQ(NonTrivial::destructions, 3u);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 6u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 1, 1, 2, 2, 2}));

        v.v = 4;
        NonTrivial::reset();
        view = list.insert(list.end(), 3u, v);
        ASSERT_EQ(NonTrivial::contructions, 9u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 6u);
        ASSERT_EQ(NonTrivial::destructions, 6u);
        ASSERT_EQ(view.data, list.end() - 3);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 9u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 1, 1, 2, 2, 2, 4, 4, 4}));

        v.v = 3;
        NonTrivial::reset();
        view = list.insert(list.end() - 3, 3u, v);
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 3u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 3u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.end() - 6);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}));

        v.v = 0;
        NonTrivial::reset();
        view = list.insert(list.begin(), 0u, v);
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 0u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}));

        v.v = 0;
        NonTrivial::reset();
        view = list.insert(list.begin(), 3u, v);
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 12u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 12u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<NonTrivial>{0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}));

        list.erase(list.begin(), list.begin() + 3);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}));

        v.v = 0;
        NonTrivial::reset();
        view = list.insert(list.end(), 3u, v);
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.end() - 3);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 0, 0, 0}));

        list.erase(list.end() - 3, list.end());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}));

        v.v = 0;
        NonTrivial::reset();
        view = list.insert(list.begin() + 6, 3u, v);
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 6u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 6u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.begin() + 6);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 1, 1, 2, 2, 2, 0, 0, 0, 3, 3, 3, 4, 4, 4}));
    }
}

TEST(List, insertRangeIt)
{
    {
        qc::List<s32> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        std::vector<s32> vs{};
        qc::View<s32> view{list.insert(list.begin(), vs.begin(), vs.end())};
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 0u);
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        vs = {1};
        view = list.insert(list.begin(), vs.begin(), vs.end());
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 1u);
        ASSERT_EQ(list.capacity(), 2u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<s32>{1}));

        list.clear();
        vs = {1, 2, 3};
        view = list.insert(list.begin(), vs.begin(), vs.end());
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3}));

        vs = {};
        view = list.insert(list.begin(), vs.begin(), vs.end());
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 0u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3}));

        vs = {};
        view = list.insert(list.end(), vs.begin(), vs.end());
        ASSERT_EQ(view.data, list.end());
        ASSERT_EQ(view.size, 0u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3}));

        vs = {4, 5, 6};
        view = list.insert(list.begin(), vs.begin(), vs.end());
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 6u);
        ASSERT_EQ(list, (IL<s32>{4, 5, 6, 1, 2, 3}));

        vs = {7, 8, 9};
        view = list.insert(list.end(), vs.begin(), vs.end());
        ASSERT_EQ(view.data, list.end() - 3);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 9u);
        ASSERT_EQ(list, (IL<s32>{4, 5, 6, 1, 2, 3, 7, 8, 9}));

        vs = {10, 11, 12};
        view = list.insert(list.end() - 3, vs.begin(), vs.end());
        ASSERT_EQ(view.data, list.end() - 6);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<s32>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        vs = {};
        view = list.insert(list.begin(), vs.begin(), vs.end());
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 0u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<s32>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        vs = {13, 14, 15};
        view = list.insert(list.begin(), vs.begin(), vs.end());
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<s32>{13, 14, 15, 4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        list.erase(list.begin(), list.begin() + 3);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<s32>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        vs = {13, 14, 15};
        view = list.insert(list.end(), vs.begin(), vs.end());
        ASSERT_EQ(view.data, list.end() - 3);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<s32>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9, 13, 14, 15}));

        list.erase(list.end() - 3, list.end());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<s32>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        vs = {13, 14, 15};
        view = list.insert(list.begin() + 6, vs.begin(), vs.end());
        ASSERT_EQ(view.data, list.begin() + 6);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<s32>{4, 5, 6, 1, 2, 3, 13, 14, 15, 10, 11, 12, 7, 8, 9}));
    }
    {
        qc::List<NonTrivial> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        std::vector<NonTrivial> vs{};
        NonTrivial::reset();
        qc::View<NonTrivial> view{list.insert(list.begin(), vs.begin(), vs.end())};
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 0u);
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        vs = {1};
        NonTrivial::reset();
        view = list.insert(list.begin(), vs.begin(), vs.end());
        ASSERT_EQ(NonTrivial::contructions, 1u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 1u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 1u);
        ASSERT_EQ(list.capacity(), 2u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<NonTrivial>{1}));

        list.clear();
        vs = {1, 2, 3};
        NonTrivial::reset();
        view = list.insert(list.begin(), vs.begin(), vs.end());
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3}));

        vs = {};
        NonTrivial::reset();
        view = list.insert(list.begin(), vs.begin(), vs.end());
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3}));

        vs = {};
        NonTrivial::reset();
        view = list.insert(list.end(), vs.begin(), vs.end());
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.end());
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3}));

        vs = {4, 5, 6};
        NonTrivial::reset();
        view = list.insert(list.begin(), vs.begin(), vs.end());
        ASSERT_EQ(NonTrivial::contructions, 6u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 3u);
        ASSERT_EQ(NonTrivial::destructions, 3u);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 6u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3}));

        vs = {7, 8, 9};
        NonTrivial::reset();
        view = list.insert(list.end(), vs.begin(), vs.end());
        ASSERT_EQ(NonTrivial::contructions, 9u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 6u);
        ASSERT_EQ(NonTrivial::destructions, 6u);
        ASSERT_EQ(view.data, list.end() - 3);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 9u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3, 7, 8, 9}));

        vs = {10, 11, 12};
        NonTrivial::reset();
        view = list.insert(list.end() - 3, vs.begin(), vs.end());
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 3u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 3u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.end() - 6);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        vs = {};
        NonTrivial::reset();
        view = list.insert(list.begin(), vs.begin(), vs.end());
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 0u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        vs = {13, 14, 15};
        NonTrivial::reset();
        view = list.insert(list.begin(), vs.begin(), vs.end());
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 12u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 12u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<NonTrivial>{13, 14, 15, 4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        list.erase(list.begin(), list.begin() + 3);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        vs = {13, 14, 15};
        NonTrivial::reset();
        view = list.insert(list.end(), vs.begin(), vs.end());
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.end() - 3);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9, 13, 14, 15}));

        list.erase(list.end() - 3, list.end());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        vs = {13, 14, 15};
        NonTrivial::reset();
        view = list.insert(list.begin() + 6, vs.begin(), vs.end());
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 6u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 6u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.begin() + 6);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3, 13, 14, 15, 10, 11, 12, 7, 8, 9}));
    }
}

// Initializer list overload just calls the view overload, so only using initializer lists for convenience
TEST(List, insertRangeContiguous)
{
    {
        qc::List<s32> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        qc::View<s32> view{list.insert(list.begin(), IL<s32>{})};
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 0u);
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        view = list.insert(list.begin(), IL<s32>{1});
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 1u);
        ASSERT_EQ(list.capacity(), 2u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<s32>{1}));

        list.clear();
        view = list.insert(list.begin(), IL<s32>{1, 2, 3});
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3}));

        view = list.insert(list.begin(), IL<s32>{});
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 0u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3}));

        view = list.insert(list.end(), IL<s32>{});
        ASSERT_EQ(view.data, list.end());
        ASSERT_EQ(view.size, 0u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3}));

        view = list.insert(list.begin(), IL<s32>{4, 5, 6});
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 6u);
        ASSERT_EQ(list, (IL<s32>{4, 5, 6, 1, 2, 3}));

        view = list.insert(list.end(), IL<s32>{7, 8, 9});
        ASSERT_EQ(view.data, list.end() - 3);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 9u);
        ASSERT_EQ(list, (IL<s32>{4, 5, 6, 1, 2, 3, 7, 8, 9}));

        view = list.insert(list.end() - 3, IL<s32>{10, 11, 12});
        ASSERT_EQ(view.data, list.end() - 6);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<s32>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        view = list.insert(list.begin(), IL<s32>{});
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 0u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<s32>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        view = list.insert(list.begin(), IL<s32>{13, 14, 15});
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<s32>{13, 14, 15, 4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        list.erase(list.begin(), list.begin() + 3);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<s32>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        view = list.insert(list.end(), IL<s32>{13, 14, 15});
        ASSERT_EQ(view.data, list.end() - 3);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<s32>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9, 13, 14, 15}));

        list.erase(list.end() - 3, list.end());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<s32>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        view = list.insert(list.begin() + 6, IL<s32>{13, 14, 15});
        ASSERT_EQ(view.data, list.begin() + 6);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<s32>{4, 5, 6, 1, 2, 3, 13, 14, 15, 10, 11, 12, 7, 8, 9}));
    }
    {
        qc::List<NonTrivial> list{};
        list.reserve(4u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 0u);

        IL<NonTrivial> v1{};
        NonTrivial::reset();
        qc::View<NonTrivial> view{list.insert(list.begin(), v1)};
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 0u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 0u);

        IL<NonTrivial> v2{1};
        NonTrivial::reset();
        view = list.insert(list.begin(), v2);
        ASSERT_EQ(NonTrivial::contructions, 1u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 1u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 1u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<NonTrivial>{1}));

        list.clear();
        IL<NonTrivial> v3{1, 2, 3};
        NonTrivial::reset();
        view = list.insert(list.begin(), v3);
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3}));

        IL<NonTrivial> v4{};
        NonTrivial::reset();
        view = list.insert(list.begin(), v4);
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3}));

        IL<NonTrivial> v5{};
        NonTrivial::reset();
        view = list.insert(list.end(), v5);
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.end());
        ASSERT_EQ(list.capacity(), 4u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3}));

        IL<NonTrivial> v6{4, 5, 6};
        NonTrivial::reset();
        view = list.insert(list.begin(), v6);
        ASSERT_EQ(NonTrivial::contructions, 6u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 3u);
        ASSERT_EQ(NonTrivial::destructions, 3u);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 6u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3}));

        IL<NonTrivial> v7{7, 8, 9};
        NonTrivial::reset();
        view = list.insert(list.end(), v7);
        ASSERT_EQ(NonTrivial::contructions, 9u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 6u);
        ASSERT_EQ(NonTrivial::destructions, 6u);
        ASSERT_EQ(view.data, list.end() - 3);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 9u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3, 7, 8, 9}));

        IL<NonTrivial> v8{10, 11, 12};
        NonTrivial::reset();
        view = list.insert(list.end() - 3, v8);
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 3u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 3u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.end() - 6);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        IL<NonTrivial> v9{};
        NonTrivial::reset();
        view = list.insert(list.begin(), v9);
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 0u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        IL<NonTrivial> v10{13, 14, 15};
        NonTrivial::reset();
        view = list.insert(list.begin(), v10);
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 12u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 12u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.begin());
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<NonTrivial>{13, 14, 15, 4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        list.erase(list.begin(), list.begin() + 3);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        IL<NonTrivial> v11{13, 14, 15};
        NonTrivial::reset();
        view = list.insert(list.end(), v11);
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.end() - 3);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9, 13, 14, 15}));

        list.erase(list.end() - 3, list.end());
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 12u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9}));

        IL<NonTrivial> v12{13, 14, 15};
        NonTrivial::reset();
        view = list.insert(list.begin() + 6, v12);
        ASSERT_EQ(NonTrivial::contructions, 3u);
        ASSERT_EQ(NonTrivial::assignments, 6u);
        ASSERT_EQ(NonTrivial::copies, 3u);
        ASSERT_EQ(NonTrivial::moves, 6u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(view.data, list.begin() + 6);
        ASSERT_EQ(view.size, 3u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 15u);
        ASSERT_EQ(list, (IL<NonTrivial>{4, 5, 6, 1, 2, 3, 13, 14, 15, 10, 11, 12, 7, 8, 9}));
    }
}

TEST(List, pop)
{
    {
        qc::List<s32> list{1, 2, 3, 4, 5};
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4, 5}));

        list.pop();
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4}));

        list.pop();
        list.pop();
        list.pop();
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<s32>{1}));

        list.pop();
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 0u);
    }
    {
        qc::List<NonTrivial> list{1, 2, 3};

        NonTrivial::reset();
        list.pop();
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 1u);
    }
}

TEST(List, popN)
{
    {
        qc::List<s32> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        list.pop(0u);
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        list = {1, 2, 3, 4, 5, 6};
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 6u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4, 5, 6}));

        list.pop(0u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 6u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4, 5, 6}));

        list.pop(1u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4, 5}));

        list.pop(2u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3}));

        list.pop(3u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 0u);

        list.pop(0u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 0u);
    }
    {
        qc::List<NonTrivial> list{1, 2, 3};

        NonTrivial::reset();
        list.pop(2u);
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 2u);
    }
}

TEST(List, popNDst)
{
    {
        s32 vs[10u];

        qc::List<s32> list{};
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        list.pop(qc::View<s32>{});
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        list.pop(qc::View<s32>{vs, 0u});
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        list = {1, 2, 3, 4, 5, 6};
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 6u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4, 5, 6}));

        list.pop(qc::View<s32>{vs, 0u});
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 6u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4, 5, 6}));

        list.pop(qc::View<s32>{vs, 1u});
        ASSERT_EQ(vs[0u], 6);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4, 5}));

        list.pop(qc::View<s32>{vs, 2u});
        ASSERT_EQ(vs[0u], 4);
        ASSERT_EQ(vs[1u], 5);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3}));

        list.pop(qc::View<s32>{vs, 3u});
        ASSERT_EQ(vs[0u], 1);
        ASSERT_EQ(vs[1u], 2);
        ASSERT_EQ(vs[2u], 3);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 0u);

        list.pop(qc::View<s32>{vs, 0u});
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 0u);
    }
    {
        NonTrivial vs[10u];

        qc::List<NonTrivial> list{1, 2, 3};

        NonTrivial::reset();
        list.pop(qc::View<NonTrivial>{vs, 2u});
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 2u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 2u);
        ASSERT_EQ(NonTrivial::destructions, 2u);
        ASSERT_EQ(vs[0u].v, 2);
        ASSERT_EQ(vs[1u].v, 3);
    }
}

TEST(List, erase)
{
    {
        qc::List<s32> list{1, 2, 3, 4, 5};
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4, 5}));

        s32 * it{list.erase(list.end() - 1)};
        ASSERT_EQ(it, list.end());
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4}));

        ASSERT_EQ(*list.erase(list.begin() + 2), 4);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 4}));

        ASSERT_EQ(*list.erase(list.begin()), 2);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 2u);
        ASSERT_EQ(list, (IL<s32>{2, 4}));

        ASSERT_EQ(*list.erase(list.begin()), 4);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<s32>{4}));

        it = list.erase(list.begin());
        ASSERT_EQ(it, list.end());
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 0u);
    }
    {
        qc::List<NonTrivial> list{1, 2, 3, 4, 5};
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4, 5}));

        NonTrivial::reset();
        NonTrivial * it{list.erase(list.end() - 1)};
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 1u);
        ASSERT_EQ(it, list.end());
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4}));

        NonTrivial::reset();
        ASSERT_EQ(list.erase(list.begin() + 2)->v, 4);
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 1u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 1u);
        ASSERT_EQ(NonTrivial::destructions, 1u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 4}));

        NonTrivial::reset();
        ASSERT_EQ(list.erase(list.begin())->v, 2);
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 2u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 2u);
        ASSERT_EQ(NonTrivial::destructions, 1u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 2u);
        ASSERT_EQ(list, (IL<NonTrivial>{2, 4}));

        NonTrivial::reset();
        ASSERT_EQ(list.erase(list.begin())->v, 4);
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 1u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 1u);
        ASSERT_EQ(NonTrivial::destructions, 1u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 1u);
        ASSERT_EQ(list, (IL<NonTrivial>{4}));

        NonTrivial::reset();
        it = list.erase(list.begin());
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 1u);
        ASSERT_EQ(it, list.end());
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 0u);
    }
    {
        qc::List<s32> list{1, 2, 3, 4, 5};
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4, 5}));

        ASSERT_EQ(list.erase(list.begin(), list.begin()), list.begin());
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4, 5}));

        ASSERT_EQ(list.erase(list.end(), list.end()), list.end());
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4, 5}));

        s32 * it{list.erase(list.begin(), list.end())};
        ASSERT_EQ(it, list.end());
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 0u);
    }
    {
        qc::List<NonTrivial> list{1, 2, 3, 4, 5};
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4, 5}));

        NonTrivial::reset();
        ASSERT_EQ(list.erase(list.begin(), list.begin()), list.begin());
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4, 5}));

        NonTrivial::reset();
        ASSERT_EQ(list.erase(list.end(), list.end()), list.end());
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 0u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4, 5}));

        NonTrivial::reset();
        NonTrivial * it{list.erase(list.begin(), list.end())};
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 5u);
        ASSERT_EQ(it, list.end());
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 0u);
    }
    {
        qc::List<s32> list{1, 2, 3, 4, 5, 6, 7, 8};
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 8u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4, 5, 6, 7, 8}));

        ASSERT_EQ(*list.erase(list.begin(), list.begin() + 1), 2);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 7u);
        ASSERT_EQ(list, (IL<s32>{2, 3, 4, 5, 6, 7, 8}));

        s32 * it{list.erase(list.end() - 1, list.end())};
        ASSERT_EQ(it, list.end());
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 6u);
        ASSERT_EQ(list, (IL<s32>{2, 3, 4, 5, 6, 7}));

        ASSERT_EQ(*list.erase(list.begin() + 1, list.end() - 1), 7);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 2u);
        ASSERT_EQ(list, (IL<s32>{2, 7}));
    }
    {
        qc::List<NonTrivial> list{1, 2, 3, 4, 5, 6, 7, 8};
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 8u);
        ASSERT_EQ(list, (IL<NonTrivial>{1, 2, 3, 4, 5, 6, 7, 8}));

        NonTrivial::reset();
        ASSERT_EQ(list.erase(list.begin(), list.begin() + 1)->v, 2);
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 7u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 7u);
        ASSERT_EQ(NonTrivial::destructions, 1u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 7u);
        ASSERT_EQ(list, (IL<NonTrivial>{2, 3, 4, 5, 6, 7, 8}));

        NonTrivial::reset();
        NonTrivial * it{list.erase(list.end() - 1, list.end())};
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 0u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 0u);
        ASSERT_EQ(NonTrivial::destructions, 1u);
        ASSERT_EQ(it, list.end());
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 6u);
        ASSERT_EQ(list, (IL<NonTrivial>{2, 3, 4, 5, 6, 7}));

        NonTrivial::reset();
        ASSERT_EQ(list.erase(list.begin() + 1, list.end() - 1)->v, 7);
        ASSERT_EQ(NonTrivial::contructions, 0u);
        ASSERT_EQ(NonTrivial::assignments, 1u);
        ASSERT_EQ(NonTrivial::copies, 0u);
        ASSERT_EQ(NonTrivial::moves, 1u);
        ASSERT_EQ(NonTrivial::destructions, 4u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 2u);
        ASSERT_EQ(list, (IL<NonTrivial>{2, 7}));
    }
    {
        qc::List<s32> list{};
        ASSERT_EQ(list.erase(7), 0u);
    }
    {
        qc::List<s32> list{7};
        ASSERT_EQ(list.erase(7), 1u);
        ASSERT_TRUE(list.empty());
    }
    {
        qc::List<s32> list{1, 2, 3, 4, 1, 2, 3, 1, 2, 1};
        ASSERT_EQ(list.erase(2), 3u);
        ASSERT_EQ(list, (IL<s32>{1, 3, 4, 1, 3, 1, 1}));
    }
    {
        qc::List<s32> list{7, 7, 3, 7, 7};
        ASSERT_EQ(list.erase(7), 4u);
        ASSERT_EQ(list, (IL<s32>{3}));
    }
    {
        qc::List<s32> list{1, 2, 3, 4, 5};
        ASSERT_EQ(list.erase(7), 0u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4, 5}));
    }
}

TEST(List, eraseIf)
{
    {
        qc::List<s32> list{};

        ASSERT_EQ(list.eraseIf([](s32) { return true; }), 0u);
        ASSERT_EQ(list.capacity(), 0u);
        ASSERT_EQ(list.size(), 0u);

        list = {1, 2, 3, 4, 5};

        ASSERT_EQ(list.eraseIf([](s32) { return false; }), 0u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 5u);
        ASSERT_EQ(list, (IL<s32>{1, 2, 3, 4, 5}));

        ASSERT_EQ(list.eraseIf([](s32) { return true; }), 5u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 0u);

        list = {1, 2, 3, 4, 5};

        ASSERT_EQ(list.eraseIf([](s32 v) { return v == 1; }), 1u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<s32>{2, 3, 4, 5}));

        ASSERT_EQ(list.eraseIf([](s32 v) { return v == 5; }), 1u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 3u);
        ASSERT_EQ(list, (IL<s32>{2, 3, 4}));

        ASSERT_EQ(list.eraseIf([](s32 v) { return v == 3; }), 1u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 2u);
        ASSERT_EQ(list, (IL<s32>{2, 4}));

        list = {1, 2, 3, 4, 5};

        ASSERT_EQ(list.eraseIf([](s32 v) { return v > 1 && v < 5; }), 3u);
        ASSERT_EQ(list.capacity(), 8u);
        ASSERT_EQ(list.size(), 2u);
        ASSERT_EQ(list, (IL<s32>{1, 5}));

        list = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        ASSERT_EQ(list.eraseIf([](s32 v) { return v > 1 && v < 5; }), 6u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<s32>{1, 5, 1, 5}));

        list = {1, 2, 3, 4, 5, 6, 7, 8};

        ASSERT_EQ(list.eraseIf([](s32 v) { return v % 2 == 0; }), 4u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<s32>{1, 3, 5, 7}));

        list = {1, 2, 3, 4, 5, 6, 7, 8};

        ASSERT_EQ(list.eraseIf([](s32 v) { return v % 2 == 1; }), 4u);
        ASSERT_EQ(list.capacity(), 16u);
        ASSERT_EQ(list.size(), 4u);
        ASSERT_EQ(list, (IL<s32>{2, 4, 6, 8}));
    }
}

TEST(List, find)
{
    {
        qc::List<s32> list{};
        ASSERT_EQ(list.find(7), list.end());
    }
    {
        qc::List<s32> list{1};
        ASSERT_EQ(list.find(7), list.end());
    }
    {
        qc::List<s32> list{7};
        ASSERT_EQ(list.find(7), list.begin());
    }
    {
        qc::List<s32> list{1, 2, 3};
        ASSERT_EQ(list.find(7), list.end());
    }
    {
        qc::List<s32> list{7, 2, 3};
        ASSERT_EQ(list.find(7), list.begin());
    }
    {
        qc::List<s32> list{1, 7, 3};
        ASSERT_EQ(list.find(7), list.begin() + 1);
    }
    {
        qc::List<s32> list{1, 2, 7};
        ASSERT_EQ(list.find(7), list.begin() + 2);
    }
    {
        qc::List<s32> list{7, 7, 7};
        ASSERT_EQ(list.find(7), list.begin());
    }
}

TEST(List, findIf)
{
    {
        qc::List<s32> list{};
        ASSERT_EQ(list.findIf([](s32) { return true; }), list.end());
    }
    {
        qc::List<s32> list{1, 2, 3};
        ASSERT_EQ(list.findIf([](s32) { return true; }), list.begin());
    }
    {
        qc::List<s32> list{7};
        ASSERT_EQ(list.findIf([](s32 v) { return v % 2 == 0; }), list.end());
    }
    {
        qc::List<s32> list{1, 2, 3};
        ASSERT_EQ(list.findIf([](s32 v) { return v % 2 == 0; }), list.begin() + 1);
    }
    {
        qc::List<s32> list{1, 2, 3};
        ASSERT_EQ(list.findIf([](s32) { return false; }), list.end());
    }
}

TEST(List, count)
{
    {
        qc::List<s32> list{};
        ASSERT_EQ(list.count(7), 0u);
    }
    {
        qc::List<s32> list{1};
        ASSERT_EQ(list.count(7), 0u);
    }
    {
        qc::List<s32> list{7};
        ASSERT_EQ(list.count(7), 1u);
    }
    {
        qc::List<s32> list{1, 2, 3};
        ASSERT_EQ(list.count(7), 0u);
    }
    {
        qc::List<s32> list{7, 2, 3};
        ASSERT_EQ(list.count(7), 1u);
    }
    {
        qc::List<s32> list{1, 7, 3};
        ASSERT_EQ(list.count(7), 1u);
    }
    {
        qc::List<s32> list{1, 2, 7};
        ASSERT_EQ(list.count(7), 1u);
    }
    {
        qc::List<s32> list{7, 7, 7};
        ASSERT_EQ(list.count(7), 3u);
    }
}

TEST(List, countIf)
{
    {
        qc::List<s32> list{};
        ASSERT_EQ(list.countIf([](s32) { return true; }), 0u);
    }
    {
        qc::List<s32> list{1, 2, 3};
        ASSERT_EQ(list.countIf([](s32) { return true; }), 3u);
    }
    {
        qc::List<s32> list{7};
        ASSERT_EQ(list.countIf([](s32 v) { return v % 2 == 0; }), 0u);
    }
    {
        qc::List<s32> list{1, 2, 3};
        ASSERT_EQ(list.countIf([](s32 v) { return v % 2 == 0; }), 1u);
    }
    {
        qc::List<s32> list{1, 2, 3};
        ASSERT_EQ(list.countIf([](s32) { return false; }), 0u);
    }
}

TEST(List, contains)
{
    {
        qc::List<s32> list{5};
        ASSERT_FALSE(list.contains(7));
    }
    {
        qc::List<s32> list{7};
        ASSERT_TRUE(list.contains(7));
    }
}

TEST(List, containsIf)
{
    {
        qc::List<s32> list{7};
        ASSERT_FALSE(list.containsIf([](s32 v) { return v % 2 == 0; }));
    }
    {
        qc::List<s32> list{8};
        ASSERT_TRUE(list.containsIf([](s32 v) { return v % 2 == 0; }));
    }
}

TEST(List, subscript)
{
    {
        qc::List<s32> list{1, 2, 3};
        ASSERT_EQ(1, list[0u]);
        ASSERT_EQ(2, list[1u]);
        ASSERT_EQ(3, list[2u]);
    }
}

TEST(List, front)
{
    {
        qc::List<s32> list{1, 2, 3};
        ASSERT_EQ(1, list.front());
    }
}

TEST(List, back)
{
    {
        qc::List<s32> list{1, 2, 3};
        ASSERT_EQ(3, list.back());
    }
}

TEST(List, data)
{
    {
        qc::List<s32> list{};
        ASSERT_EQ(list.data(), nullptr);
    }
    {
        qc::List<s32> list{1, 2, 3};
        s32 * data{list.data()};
        ASSERT_EQ(1, data[0u]);
        ASSERT_EQ(2, data[1u]);
        ASSERT_EQ(3, data[2u]);
    }
}

TEST(List, iteration)
{
    {
        qc::List<s32> list{1, 2, 3};

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

        s32 expected{1};
        for (const s32 i : list)
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

        s32 expected{1};
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
        qc::List<s32> l1{1, 2, 3};
        qc::List<s32> l2{1, 2, 3};
        qc::List<s32> l3{1, 2};
        qc::List<s32> l4{};

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
        qc::List<std::vector<u64>> list{};
        list.empush(4u, 5u);
        ASSERT_EQ(list.front(), (std::vector<u64>{5u, 5u, 5u, 5u}));

        list.emplace(list.end(), 2u, 3u);
        ASSERT_EQ(list.back(), (std::vector<u64>{3u, 3u}));
    }
}

TEST(List, pushIterator)
{
    qc::List<std::string> list{};
    ASSERT_EQ(list.size(), 0u);

    qc::PushIterator<std::string> it{list.pushIterator()};

    *it = std::string{"a"};
    ASSERT_EQ(list.size(), 1u);
    ASSERT_EQ(list, (IL<std::string>{"a"}));

    const std::string bStr{"b"};
    *it = bStr;
    ASSERT_EQ(list.size(), 2u);
    ASSERT_EQ(list, (IL<std::string>{"a", "b"}));

    std::string cStr{"c"};
    *it = std::move(cStr);
    ASSERT_EQ(list.size(), 3u);
    ASSERT_EQ(list, (IL<std::string>{"a", "b", "c"}));
    ASSERT_TRUE(cStr.empty());
}

TEST(List, nonMoveAssignableType)
{
    struct Unassignable
    {
        s32 v;
        Unassignable(const s32 v_) : v{v_} {}
        Unassignable(Unassignable &&) = default;
        Unassignable(const Unassignable &) = default;
        Unassignable & operator=(const Unassignable &) = delete;
        Unassignable & operator=(Unassignable &&) = delete;
        ~Unassignable() { v = -1; }
        bool operator==(const Unassignable & other) const = default;
    };

    qc::List<Unassignable> list{};

    list.push(0);
    ASSERT_EQ(list, (IL<Unassignable>{0}));

    list.push(Unassignable{1});
    ASSERT_EQ(list, (IL<Unassignable>{0, 1}));

    const Unassignable u1{2};
    list.push(u1);
    ASSERT_EQ(list, (IL<Unassignable>{0, 1, 2}));

    list.insert(list.begin(), Unassignable{3});
    ASSERT_EQ(list, (IL<Unassignable>{3, 0, 1, 2}));

    const Unassignable u2{4};
    list.insert(list.begin(), u2);
    ASSERT_EQ(list, (IL<Unassignable>{4, 3, 0, 1, 2}));

    list.emplace(list.begin(), 5);
    ASSERT_EQ(list, (IL<Unassignable>{5, 4, 3, 0, 1, 2}));

    list.insert(list.begin(), 3u, Unassignable{6});
    ASSERT_EQ(list, (IL<Unassignable>{6, 6, 6, 5, 4, 3, 0, 1, 2}));

    list.insert(list.begin(), {Unassignable{9}, Unassignable{8}, Unassignable{7}});
    ASSERT_EQ(list, (IL<Unassignable>{9, 8, 7, 6, 6, 6, 5, 4, 3, 0, 1, 2}));

    list.pop();
    ASSERT_EQ(list, (IL<Unassignable>{9, 8, 7, 6, 6, 6, 5, 4, 3, 0, 1}));

    list.pop(3u);
    ASSERT_EQ(list, (IL<Unassignable>{9, 8, 7, 6, 6, 6, 5, 4}));

    list.erase(list.begin());
    ASSERT_EQ(list, (IL<Unassignable>{8, 7, 6, 6, 6, 5, 4}));

    list.erase(list.begin(), list.begin() + 3);
    ASSERT_EQ(list, (IL<Unassignable>{6, 6, 5, 4}));

    ASSERT_LT(list.capacity(), 32u);
    list.reserve(32u);
    ASSERT_EQ(list, (IL<Unassignable>{6, 6, 5, 4}));

    list.clear();
    ASSERT_TRUE(list.empty());
}
