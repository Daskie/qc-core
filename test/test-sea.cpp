#include <qc-core/sea.hpp>

#include <gtest/gtest.h>

using namespace qc::types;

TEST(Sea, standard)
{
    // Assumes page size is 4096
    // Each BigInt is 2400 bytes, so 5 would fit into three pages
    ASSERT_EQ(4096u, qc::pageSize);
    struct BigInt { int x; u8 padding[2400u - sizeof(int)]; };

    // [_|_|_|_|_]
    qc::Sea<BigInt> sea{5u};
    ASSERT_EQ(3u, sea.maxPageCount());
    ASSERT_EQ(5u, sea.maxSize());
    ASSERT_EQ(0u, sea.pageCount());
    ASSERT_EQ(0u, sea.size());
    ASSERT_EQ(0u, sea.usedCount());
    auto it{sea.begin()};
    ASSERT_EQ(sea.end(), it);

    // [0|_|_|_|_]
    BigInt & e0{sea.construct(0)};
    ASSERT_EQ(1u, sea.pageCount());
    ASSERT_EQ(1u, sea.size());
    ASSERT_EQ(1u, sea.usedCount());
    it = sea.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(sea.end(), ++it);

    // [0|1|_|_|_]
    BigInt & e1{sea.construct(1)};
    ASSERT_EQ(&e0 + 1, &e1);
    ASSERT_EQ(3u, sea.pageCount());
    ASSERT_EQ(5u, sea.size());
    ASSERT_EQ(2u, sea.usedCount());
    it = sea.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(sea.end(), ++it);

    // [0|1|2|_|_]
    BigInt & e2{sea.construct(2)};
    ASSERT_EQ(&e1 + 1, &e2);
    ASSERT_EQ(5u, sea.size());
    ASSERT_EQ(3u, sea.usedCount());
    it = sea.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(sea.end(), ++it);

    // [0|1|2|3|_]
    BigInt & e3{sea.construct(3)};
    ASSERT_EQ(&e2 + 1, &e3);
    ASSERT_EQ(5u, sea.size());
    ASSERT_EQ(4u, sea.usedCount());
    it = sea.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(3, (++it)->x);
    ASSERT_EQ(sea.end(), ++it);

    // [0|1|2|3|4]
    BigInt & e4{sea.construct(4)};
    ASSERT_EQ(&e3 + 1, &e4);
    ASSERT_EQ(5u, sea.size());
    ASSERT_EQ(5u, sea.usedCount());
    it = sea.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(3, (++it)->x);
    ASSERT_EQ(4, (++it)->x);
    ASSERT_EQ(sea.end(), ++it);

    // [0|1|2|3|4]
    #pragma warning(suppress: 4834)
    EXPECT_THROW(sea.construct(5), qc::SeaError);

    // [0|1|2|3|_]
    sea.destruct(e4);
    ASSERT_EQ(5u, sea.size());
    ASSERT_EQ(4u, sea.usedCount());
    it = sea.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(3, (++it)->x);
    ASSERT_EQ(sea.end(), ++it);

    // [0|1|2|_|_]
    sea.destruct(e3);
    ASSERT_EQ(5u, sea.size());
    ASSERT_EQ(3u, sea.usedCount());
    it = sea.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(sea.end(), ++it);

    // [0|1|2|5|6]
    BigInt & e5{sea.construct(5)};
    BigInt & e6{sea.construct(6)};
    ASSERT_EQ(&e2 + 1, &e5);
    ASSERT_EQ(&e5 + 1, &e6);
    ASSERT_EQ(5u, sea.size());
    ASSERT_EQ(5u, sea.usedCount());
    it = sea.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(sea.end(), ++it);

    // [_|1|2|5|6]
    sea.destruct(e0);
    ASSERT_EQ(5u, sea.size());
    ASSERT_EQ(4u, sea.usedCount());
    it = sea.begin();
    ASSERT_EQ(1, it->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(sea.end(), ++it);

    // [_|_|2|5|6]
    sea.destruct(e1);
    ASSERT_EQ(5u, sea.size());
    ASSERT_EQ(3u, sea.usedCount());
    it = sea.begin();
    ASSERT_EQ(2, it->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(sea.end(), ++it);

    // [7|_|2|5|6]
    BigInt & e7{sea.construct(7)};
    ASSERT_EQ(&e2 - 2, &e7);
    ASSERT_EQ(5u, sea.size());
    ASSERT_EQ(4u, sea.usedCount());
    it = sea.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(sea.end(), ++it);

    // [7|_|2|_|6]
    sea.destruct(e5);
    ASSERT_EQ(5u, sea.size());
    ASSERT_EQ(3u, sea.usedCount());
    it = sea.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(sea.end(), ++it);

    // [7|_|_|_|6]
    sea.destruct(e2);
    ASSERT_EQ(5u, sea.size());
    ASSERT_EQ(2u, sea.usedCount());
    it = sea.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(sea.end(), ++it);

    // [7|8|9|10|6]
    BigInt & e8{sea.construct(8)};
    BigInt & e9{sea.construct(9)};
    BigInt & e10{sea.construct(10)};
    ASSERT_EQ(&e7 + 1, &e8);
    ASSERT_EQ(&e7 + 2, &e9);
    ASSERT_EQ(&e7 + 3, &e10);
    ASSERT_EQ(5u, sea.size());
    ASSERT_EQ(5u, sea.usedCount());
    it = sea.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(8, (++it)->x);
    ASSERT_EQ(9, (++it)->x);
    ASSERT_EQ(10, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(sea.end(), ++it);

    // [7|_|_|_|6]
    sea.destruct(e8);
    sea.destruct(e9);
    sea.destruct(e10);
    ASSERT_EQ(5u, sea.size());
    ASSERT_EQ(2u, sea.usedCount());
    it = sea.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(sea.end(), ++it);

    // [7|_|_|_|6]
    ASSERT_THROW(sea.destruct(e8), qc::SeaError);
    ASSERT_THROW(sea.destruct(e9), qc::SeaError);
    ASSERT_THROW(sea.destruct(e10), qc::SeaError);

    // [_|_|_|_|6]
    sea.destruct(e7);
    ASSERT_EQ(5u, sea.size());
    ASSERT_EQ(1u, sea.usedCount());
    it = sea.begin();
    ASSERT_EQ(6, it->x);
    ASSERT_EQ(sea.end(), ++it);

    // [11|_|_|_|6]
    BigInt & e11{sea.construct(11)};
    ASSERT_EQ(&e6 - 4, &e11);
    ASSERT_EQ(5u, sea.size());
    ASSERT_EQ(2u, sea.usedCount());
    it = sea.begin();
    ASSERT_EQ(11, it->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(sea.end(), ++it);

    // [11|_|_|_|_]
    sea.destruct(e6);
    ASSERT_EQ(5u, sea.size());
    ASSERT_EQ(1u, sea.usedCount());
    it = sea.begin();
    ASSERT_EQ(11, it->x);
    ASSERT_EQ(sea.end(), ++it);

    // [_|_|_|_|_]
    sea.destruct(e11);
    ASSERT_EQ(3u, sea.pageCount());
    ASSERT_EQ(5u, sea.size());
    ASSERT_EQ(0u, sea.usedCount());
    ASSERT_EQ(sea.end(), sea.begin());

    ASSERT_THROW(sea.destruct(e11), qc::SeaError);
}

TEST(Sea, single)
{
    qc::Sea<int> sea{1u};
    const size_t maxSize{qc::pageSize / sizeof(int)};
    ASSERT_EQ(1u, sea.maxPageCount());
    ASSERT_EQ(maxSize, sea.maxSize());
    ASSERT_EQ(0u, sea.pageCount());
    ASSERT_EQ(0u, sea.size());
    ASSERT_EQ(0u, sea.usedCount());
    ASSERT_EQ(sea.end(), sea.begin());

    int & e0{sea.construct(0)};
    ASSERT_EQ(1u, sea.pageCount());
    ASSERT_EQ(maxSize, sea.size());
    ASSERT_EQ(1u, sea.usedCount());
    auto it{sea.begin()};
    ASSERT_EQ(0, *it);
    ASSERT_EQ(sea.end(), ++it);

    sea.destruct(e0);
    ASSERT_EQ(1u, sea.pageCount());
    ASSERT_EQ(maxSize, sea.size());
    ASSERT_EQ(0u, sea.usedCount());
    ASSERT_EQ(sea.end(), sea.begin());
}

TEST(Sea, growthRate)
{
    ASSERT_EQ(4096u, qc::pageSize);
    struct PageVal { u8 data[4096u]; };

    {
        qc::Sea<PageVal> sea{24u};
        ASSERT_EQ(24u, sea.maxPageCount());
        ASSERT_EQ(24u, sea.maxSize());
        ASSERT_EQ(0u, sea.pageCount());
        ASSERT_EQ(0u, sea.size());

        static_cast<void>(sea.construct());
        ASSERT_EQ(1u, sea.pageCount());
        ASSERT_EQ(1u, sea.size());

        static_cast<void>(sea.construct());
        ASSERT_EQ(2u, sea.pageCount());
        ASSERT_EQ(2u, sea.size());

        static_cast<void>(sea.construct());
        ASSERT_EQ(4u, sea.pageCount());
        ASSERT_EQ(4u, sea.size());

        static_cast<void>(sea.construct());
        ASSERT_EQ(4u, sea.pageCount());
        ASSERT_EQ(4u, sea.size());

        static_cast<void>(sea.construct());
        ASSERT_EQ(8u, sea.pageCount());
        ASSERT_EQ(8u, sea.size());

        static_cast<void>(sea.construct());
        static_cast<void>(sea.construct());
        static_cast<void>(sea.construct());
        ASSERT_EQ(8u, sea.pageCount());
        ASSERT_EQ(8u, sea.size());

        static_cast<void>(sea.construct());
        ASSERT_EQ(24u, sea.pageCount());
        ASSERT_EQ(24u, sea.size());
    }

    {
        qc::Sea<PageVal> sea{25u};
        ASSERT_EQ(25u, sea.maxPageCount());
        ASSERT_EQ(25u, sea.maxSize());
        ASSERT_EQ(0u, sea.pageCount());
        ASSERT_EQ(0u, sea.size());

        static_cast<void>(sea.construct());
        ASSERT_EQ(1u, sea.pageCount());
        ASSERT_EQ(1u, sea.size());

        static_cast<void>(sea.construct());
        ASSERT_EQ(2u, sea.pageCount());
        ASSERT_EQ(2u, sea.size());

        static_cast<void>(sea.construct());
        ASSERT_EQ(4u, sea.pageCount());
        ASSERT_EQ(4u, sea.size());

        static_cast<void>(sea.construct());
        ASSERT_EQ(4u, sea.pageCount());
        ASSERT_EQ(4u, sea.size());

        static_cast<void>(sea.construct());
        ASSERT_EQ(8u, sea.pageCount());
        ASSERT_EQ(8u, sea.size());

        static_cast<void>(sea.construct());
        static_cast<void>(sea.construct());
        static_cast<void>(sea.construct());
        ASSERT_EQ(8u, sea.pageCount());
        ASSERT_EQ(8u, sea.size());

        static_cast<void>(sea.construct());
        ASSERT_EQ(16u, sea.pageCount());
        ASSERT_EQ(16u, sea.size());

        static_cast<void>(sea.construct());
        static_cast<void>(sea.construct());
        static_cast<void>(sea.construct());
        static_cast<void>(sea.construct());
        static_cast<void>(sea.construct());
        static_cast<void>(sea.construct());
        static_cast<void>(sea.construct());
        ASSERT_EQ(16u, sea.pageCount());
        ASSERT_EQ(16u, sea.size());

        static_cast<void>(sea.construct());
        ASSERT_EQ(25u, sea.pageCount());
        ASSERT_EQ(25u, sea.size());
    }
}

TEST(Sea, biggerThanPageVal)
{
    ASSERT_EQ(4096u, qc::pageSize);
    struct HugeVal { u8 data[5000u]; };

    qc::Sea<HugeVal> sea{1u};
    ASSERT_EQ(2u, sea.maxPageCount());
    ASSERT_EQ(1u, sea.maxSize());
    ASSERT_EQ(0u, sea.pageCount());
    ASSERT_EQ(0u, sea.size());

    HugeVal & v{sea.construct()};
    ASSERT_EQ(2u, sea.pageCount());
    ASSERT_EQ(1u, sea.size());

    ++v.data[0];
    ++v.data[sizeof(HugeVal) - 1u];

    sea.destruct(v);
    ASSERT_EQ(2u, sea.pageCount());
    ASSERT_EQ(1u, sea.size());
}

TEST(Sea, deferredMaxSize)
{
    qc::Sea<int> sea{};
    ASSERT_EQ(0u, sea.maxPageCount());
    ASSERT_EQ(0u, sea.maxSize());
    ASSERT_EQ(0u, sea.pageCount());
    ASSERT_EQ(0u, sea.size());

    EXPECT_THROW(static_cast<void>(sea.construct(0)), qc::SeaError);

    sea.setMaxSize(1u);
    ASSERT_EQ(1u, sea.maxPageCount());
    ASSERT_EQ(qc::pageSize / sizeof(int), sea.maxSize());
    ASSERT_EQ(0u, sea.pageCount());
    ASSERT_EQ(0u, sea.size());

    sea.setMaxSize(0u);
    ASSERT_EQ(0u, sea.maxPageCount());
    ASSERT_EQ(0u, sea.maxSize());
    ASSERT_EQ(0u, sea.pageCount());
    ASSERT_EQ(0u, sea.size());

    EXPECT_THROW(static_cast<void>(sea.construct(0)), qc::SeaError);

    sea.setMaxSize(qc::pageSize / sizeof(int) * 2u);
    ASSERT_EQ(2u, sea.maxPageCount());
    ASSERT_EQ(qc::pageSize / sizeof(int) * 2u, sea.maxSize());
    ASSERT_EQ(0u, sea.pageCount());
    ASSERT_EQ(0u, sea.size());

    sea.setMaxSize(1u);
    ASSERT_EQ(1u, sea.maxPageCount());
    ASSERT_EQ(qc::pageSize / sizeof(int), sea.maxSize());
    ASSERT_EQ(0u, sea.pageCount());
    ASSERT_EQ(0u, sea.size());

    [[maybe_unused]] int & v{sea.construct(0)};

    EXPECT_THROW(sea.setMaxSize(sea.maxSize()), qc::SeaError);
    EXPECT_THROW(sea.setMaxSize(qc::pageSize / sizeof(int) * 3u), qc::SeaError);
    EXPECT_THROW(sea.setMaxSize(1u), qc::SeaError);
    EXPECT_THROW(sea.setMaxSize(0u), qc::SeaError);
}

TEST(Sea, freeUnusedPages)
{
    const size_t intsPerPage{qc::pageSize / sizeof(int)};
    qc::Sea<int> sea{5u * intsPerPage};
    ASSERT_EQ(5u, sea.maxPageCount());
    ASSERT_EQ(5u * intsPerPage, sea.maxSize());
    ASSERT_EQ(0u, sea.pageCount());
    ASSERT_EQ(0u, sea.size());

    sea.freeUnusedPages();

    int * const ints{&sea.construct(0)};
    for (int i{1}; i < int(intsPerPage * 5u); ++i)
    {
        static_cast<void>(sea.construct(i));
    }
    ASSERT_EQ(5u, sea.pageCount());
    ASSERT_EQ(intsPerPage * 5u, sea.size());

    sea.freeUnusedPages();
    ASSERT_EQ(5u, sea.pageCount());
    ASSERT_EQ(intsPerPage * 5u, sea.size());

    for (int i{int(intsPerPage * 4u) + 1}; i < int(intsPerPage * 5u); ++i)
    {
        sea.destruct(ints[i]);
    }
    ASSERT_EQ(5u, sea.pageCount());
    ASSERT_EQ(intsPerPage * 5u, sea.size());

    sea.freeUnusedPages();
    ASSERT_EQ(5u, sea.pageCount());
    ASSERT_EQ(intsPerPage * 5u, sea.size());

    sea.destruct(ints[intsPerPage * 4u]);
    ASSERT_EQ(5u, sea.pageCount());
    ASSERT_EQ(intsPerPage * 5u, sea.size());

    sea.freeUnusedPages();
    ASSERT_EQ(4u, sea.pageCount());
    ASSERT_EQ(intsPerPage * 4u, sea.size());

    for (int i{int(1)}; i < int(intsPerPage * 4u) - 1; ++i)
    {
        sea.destruct(ints[i]);
    }
    ASSERT_EQ(4u, sea.pageCount());
    ASSERT_EQ(intsPerPage * 4u, sea.size());

    sea.freeUnusedPages();
    ASSERT_EQ(4u, sea.pageCount());
    ASSERT_EQ(intsPerPage * 4u, sea.size());

    sea.destruct(ints[intsPerPage * 4u - 1u]);
    ASSERT_EQ(4u, sea.pageCount());
    ASSERT_EQ(intsPerPage * 4u, sea.size());

    sea.freeUnusedPages();
    ASSERT_EQ(1u, sea.pageCount());
    ASSERT_EQ(intsPerPage * 1u, sea.size());

    sea.destruct(ints[0]);
    ASSERT_EQ(1u, sea.pageCount());
    ASSERT_EQ(intsPerPage * 1u, sea.size());

    sea.freeUnusedPages();
    ASSERT_EQ(0u, sea.pageCount());
    ASSERT_EQ(0u, sea.size());

    static_cast<void>(sea.construct(0));
    ASSERT_EQ(1u, sea.pageCount());
    ASSERT_EQ(intsPerPage * 1u, sea.size());
}

TEST(Sea, iteratorAssignability)
{
    static_assert(std::is_assignable_v<qc::Sea<int>::iterator, qc::Sea<int>::iterator>);
    static_assert(std::is_assignable_v<qc::Sea<int>::const_iterator, qc::Sea<int>::iterator>);
    static_assert(!std::is_assignable_v<qc::Sea<int>::iterator, qc::Sea<int>::const_iterator>);
    static_assert(std::is_assignable_v<qc::Sea<int>::const_iterator, qc::Sea<int>::const_iterator>);
}
