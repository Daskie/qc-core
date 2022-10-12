#include <qc-core/stable-lot.hpp>

#include <gtest/gtest.h>

using namespace qc::types;

TEST(Lot, standard)
{
    // Assumes page size is 4096
    // Each BigInt is 2400 bytes, so 5 would fit into three pages
    ASSERT_EQ(4096u, qc::pageSize);
    struct BigInt { int x; u8 padding[2400u - sizeof(int)]; };

    // [_|_|_|_|_]
    qc::StableLot<BigInt> lot{5u};
    ASSERT_EQ(3u, lot.maxPageCount());
    ASSERT_EQ(5u, lot.maxSize());
    ASSERT_EQ(0u, lot.pageCount());
    ASSERT_EQ(0u, lot.size());
    ASSERT_EQ(0u, lot.usedCount());
    auto it{lot.begin()};
    ASSERT_EQ(lot.end(), it);

    // [0|_|_|_|_]
    BigInt & e0{lot.construct(0)};
    ASSERT_EQ(1u, lot.pageCount());
    ASSERT_EQ(1u, lot.size());
    ASSERT_EQ(1u, lot.usedCount());
    it = lot.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(lot.end(), ++it);

    // [0|1|_|_|_]
    BigInt & e1{lot.construct(1)};
    ASSERT_EQ(&e0 + 1, &e1);
    ASSERT_EQ(3u, lot.pageCount());
    ASSERT_EQ(5u, lot.size());
    ASSERT_EQ(2u, lot.usedCount());
    it = lot.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(lot.end(), ++it);

    // [0|1|2|_|_]
    BigInt & e2{lot.construct(2)};
    ASSERT_EQ(&e1 + 1, &e2);
    ASSERT_EQ(5u, lot.size());
    ASSERT_EQ(3u, lot.usedCount());
    it = lot.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(lot.end(), ++it);

    // [0|1|2|3|_]
    BigInt & e3{lot.construct(3)};
    ASSERT_EQ(&e2 + 1, &e3);
    ASSERT_EQ(5u, lot.size());
    ASSERT_EQ(4u, lot.usedCount());
    it = lot.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(3, (++it)->x);
    ASSERT_EQ(lot.end(), ++it);

    // [0|1|2|3|4]
    BigInt & e4{lot.construct(4)};
    ASSERT_EQ(&e3 + 1, &e4);
    ASSERT_EQ(5u, lot.size());
    ASSERT_EQ(5u, lot.usedCount());
    it = lot.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(3, (++it)->x);
    ASSERT_EQ(4, (++it)->x);
    ASSERT_EQ(lot.end(), ++it);

    // [0|1|2|3|4]
    #pragma warning(suppress: 4834)
    EXPECT_THROW(lot.construct(5), qc::StableLotError);

    // [0|1|2|3|_]
    lot.destruct(e4);
    ASSERT_EQ(5u, lot.size());
    ASSERT_EQ(4u, lot.usedCount());
    it = lot.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(3, (++it)->x);
    ASSERT_EQ(lot.end(), ++it);

    // [0|1|2|_|_]
    lot.destruct(e3);
    ASSERT_EQ(5u, lot.size());
    ASSERT_EQ(3u, lot.usedCount());
    it = lot.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(lot.end(), ++it);

    // [0|1|2|5|6]
    BigInt & e5{lot.construct(5)};
    BigInt & e6{lot.construct(6)};
    ASSERT_EQ(&e2 + 1, &e5);
    ASSERT_EQ(&e5 + 1, &e6);
    ASSERT_EQ(5u, lot.size());
    ASSERT_EQ(5u, lot.usedCount());
    it = lot.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(lot.end(), ++it);

    // [_|1|2|5|6]
    lot.destruct(e0);
    ASSERT_EQ(5u, lot.size());
    ASSERT_EQ(4u, lot.usedCount());
    it = lot.begin();
    ASSERT_EQ(1, it->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(lot.end(), ++it);

    // [_|_|2|5|6]
    lot.destruct(e1);
    ASSERT_EQ(5u, lot.size());
    ASSERT_EQ(3u, lot.usedCount());
    it = lot.begin();
    ASSERT_EQ(2, it->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(lot.end(), ++it);

    // [7|_|2|5|6]
    BigInt & e7{lot.construct(7)};
    ASSERT_EQ(&e2 - 2, &e7);
    ASSERT_EQ(5u, lot.size());
    ASSERT_EQ(4u, lot.usedCount());
    it = lot.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(lot.end(), ++it);

    // [7|_|2|_|6]
    lot.destruct(e5);
    ASSERT_EQ(5u, lot.size());
    ASSERT_EQ(3u, lot.usedCount());
    it = lot.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(lot.end(), ++it);

    // [7|_|_|_|6]
    lot.destruct(e2);
    ASSERT_EQ(5u, lot.size());
    ASSERT_EQ(2u, lot.usedCount());
    it = lot.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(lot.end(), ++it);

    // [7|8|9|10|6]
    BigInt & e8{lot.construct(8)};
    BigInt & e9{lot.construct(9)};
    BigInt & e10{lot.construct(10)};
    ASSERT_EQ(&e7 + 1, &e8);
    ASSERT_EQ(&e7 + 2, &e9);
    ASSERT_EQ(&e7 + 3, &e10);
    ASSERT_EQ(5u, lot.size());
    ASSERT_EQ(5u, lot.usedCount());
    it = lot.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(8, (++it)->x);
    ASSERT_EQ(9, (++it)->x);
    ASSERT_EQ(10, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(lot.end(), ++it);

    // [7|_|_|_|6]
    lot.destruct(e8);
    lot.destruct(e9);
    lot.destruct(e10);
    ASSERT_EQ(5u, lot.size());
    ASSERT_EQ(2u, lot.usedCount());
    it = lot.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(lot.end(), ++it);

    // [7|_|_|_|6]
    ASSERT_THROW(lot.destruct(e8), qc::StableLotError);
    ASSERT_THROW(lot.destruct(e9), qc::StableLotError);
    ASSERT_THROW(lot.destruct(e10), qc::StableLotError);

    // [_|_|_|_|6]
    lot.destruct(e7);
    ASSERT_EQ(5u, lot.size());
    ASSERT_EQ(1u, lot.usedCount());
    it = lot.begin();
    ASSERT_EQ(6, it->x);
    ASSERT_EQ(lot.end(), ++it);

    // [11|_|_|_|6]
    BigInt & e11{lot.construct(11)};
    ASSERT_EQ(&e6 - 4, &e11);
    ASSERT_EQ(5u, lot.size());
    ASSERT_EQ(2u, lot.usedCount());
    it = lot.begin();
    ASSERT_EQ(11, it->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(lot.end(), ++it);

    // [11|_|_|_|_]
    lot.destruct(e6);
    ASSERT_EQ(5u, lot.size());
    ASSERT_EQ(1u, lot.usedCount());
    it = lot.begin();
    ASSERT_EQ(11, it->x);
    ASSERT_EQ(lot.end(), ++it);

    // [_|_|_|_|_]
    lot.destruct(e11);
    ASSERT_EQ(3u, lot.pageCount());
    ASSERT_EQ(5u, lot.size());
    ASSERT_EQ(0u, lot.usedCount());
    ASSERT_EQ(lot.end(), lot.begin());

    ASSERT_THROW(lot.destruct(e11), qc::StableLotError);
}

TEST(Lot, single)
{
    qc::StableLot<int> lot{1u};
    const size_t maxSize{qc::pageSize / sizeof(int)};
    ASSERT_EQ(1u, lot.maxPageCount());
    ASSERT_EQ(maxSize, lot.maxSize());
    ASSERT_EQ(0u, lot.pageCount());
    ASSERT_EQ(0u, lot.size());
    ASSERT_EQ(0u, lot.usedCount());
    ASSERT_EQ(lot.end(), lot.begin());

    int & e0{lot.construct(0)};
    ASSERT_EQ(1u, lot.pageCount());
    ASSERT_EQ(maxSize, lot.size());
    ASSERT_EQ(1u, lot.usedCount());
    auto it{lot.begin()};
    ASSERT_EQ(0, *it);
    ASSERT_EQ(lot.end(), ++it);

    lot.destruct(e0);
    ASSERT_EQ(1u, lot.pageCount());
    ASSERT_EQ(maxSize, lot.size());
    ASSERT_EQ(0u, lot.usedCount());
    ASSERT_EQ(lot.end(), lot.begin());
}

TEST(Lot, growthRate)
{
    ASSERT_EQ(4096u, qc::pageSize);
    struct PageVal { u8 data[4096u]; };

    {
        qc::StableLot<PageVal> lot{24u};
        ASSERT_EQ(24u, lot.maxPageCount());
        ASSERT_EQ(24u, lot.maxSize());
        ASSERT_EQ(0u, lot.pageCount());
        ASSERT_EQ(0u, lot.size());

        static_cast<void>(lot.construct());
        ASSERT_EQ(1u, lot.pageCount());
        ASSERT_EQ(1u, lot.size());

        static_cast<void>(lot.construct());
        ASSERT_EQ(2u, lot.pageCount());
        ASSERT_EQ(2u, lot.size());

        static_cast<void>(lot.construct());
        ASSERT_EQ(4u, lot.pageCount());
        ASSERT_EQ(4u, lot.size());

        static_cast<void>(lot.construct());
        ASSERT_EQ(4u, lot.pageCount());
        ASSERT_EQ(4u, lot.size());

        static_cast<void>(lot.construct());
        ASSERT_EQ(8u, lot.pageCount());
        ASSERT_EQ(8u, lot.size());

        static_cast<void>(lot.construct());
        static_cast<void>(lot.construct());
        static_cast<void>(lot.construct());
        ASSERT_EQ(8u, lot.pageCount());
        ASSERT_EQ(8u, lot.size());

        static_cast<void>(lot.construct());
        ASSERT_EQ(24u, lot.pageCount());
        ASSERT_EQ(24u, lot.size());
    }

    {
        qc::StableLot<PageVal> lot{25u};
        ASSERT_EQ(25u, lot.maxPageCount());
        ASSERT_EQ(25u, lot.maxSize());
        ASSERT_EQ(0u, lot.pageCount());
        ASSERT_EQ(0u, lot.size());

        static_cast<void>(lot.construct());
        ASSERT_EQ(1u, lot.pageCount());
        ASSERT_EQ(1u, lot.size());

        static_cast<void>(lot.construct());
        ASSERT_EQ(2u, lot.pageCount());
        ASSERT_EQ(2u, lot.size());

        static_cast<void>(lot.construct());
        ASSERT_EQ(4u, lot.pageCount());
        ASSERT_EQ(4u, lot.size());

        static_cast<void>(lot.construct());
        ASSERT_EQ(4u, lot.pageCount());
        ASSERT_EQ(4u, lot.size());

        static_cast<void>(lot.construct());
        ASSERT_EQ(8u, lot.pageCount());
        ASSERT_EQ(8u, lot.size());

        static_cast<void>(lot.construct());
        static_cast<void>(lot.construct());
        static_cast<void>(lot.construct());
        ASSERT_EQ(8u, lot.pageCount());
        ASSERT_EQ(8u, lot.size());

        static_cast<void>(lot.construct());
        ASSERT_EQ(16u, lot.pageCount());
        ASSERT_EQ(16u, lot.size());

        static_cast<void>(lot.construct());
        static_cast<void>(lot.construct());
        static_cast<void>(lot.construct());
        static_cast<void>(lot.construct());
        static_cast<void>(lot.construct());
        static_cast<void>(lot.construct());
        static_cast<void>(lot.construct());
        ASSERT_EQ(16u, lot.pageCount());
        ASSERT_EQ(16u, lot.size());

        static_cast<void>(lot.construct());
        ASSERT_EQ(25u, lot.pageCount());
        ASSERT_EQ(25u, lot.size());
    }
}

TEST(Lot, biggerThanPageVal)
{
    ASSERT_EQ(4096u, qc::pageSize);
    struct HugeVal { u8 data[5000u]; };

    qc::StableLot<HugeVal> lot{1u};
    ASSERT_EQ(2u, lot.maxPageCount());
    ASSERT_EQ(1u, lot.maxSize());
    ASSERT_EQ(0u, lot.pageCount());
    ASSERT_EQ(0u, lot.size());

    HugeVal & v{lot.construct()};
    ASSERT_EQ(2u, lot.pageCount());
    ASSERT_EQ(1u, lot.size());

    ++v.data[0];
    ++v.data[sizeof(HugeVal) - 1u];

    lot.destruct(v);
    ASSERT_EQ(2u, lot.pageCount());
    ASSERT_EQ(1u, lot.size());
}

TEST(Lot, deferredMaxSize)
{
    qc::StableLot<int> lot{};
    ASSERT_EQ(0u, lot.maxPageCount());
    ASSERT_EQ(0u, lot.maxSize());
    ASSERT_EQ(0u, lot.pageCount());
    ASSERT_EQ(0u, lot.size());

    EXPECT_THROW(static_cast<void>(lot.construct(0)), qc::StableLotError);

    lot.setMaxSize(1u);
    ASSERT_EQ(1u, lot.maxPageCount());
    ASSERT_EQ(qc::pageSize / sizeof(int), lot.maxSize());
    ASSERT_EQ(0u, lot.pageCount());
    ASSERT_EQ(0u, lot.size());

    lot.setMaxSize(0u);
    ASSERT_EQ(0u, lot.maxPageCount());
    ASSERT_EQ(0u, lot.maxSize());
    ASSERT_EQ(0u, lot.pageCount());
    ASSERT_EQ(0u, lot.size());

    EXPECT_THROW(static_cast<void>(lot.construct(0)), qc::StableLotError);

    lot.setMaxSize(qc::pageSize / sizeof(int) * 2u);
    ASSERT_EQ(2u, lot.maxPageCount());
    ASSERT_EQ(qc::pageSize / sizeof(int) * 2u, lot.maxSize());
    ASSERT_EQ(0u, lot.pageCount());
    ASSERT_EQ(0u, lot.size());

    lot.setMaxSize(1u);
    ASSERT_EQ(1u, lot.maxPageCount());
    ASSERT_EQ(qc::pageSize / sizeof(int), lot.maxSize());
    ASSERT_EQ(0u, lot.pageCount());
    ASSERT_EQ(0u, lot.size());

    [[maybe_unused]] int & v{lot.construct(0)};

    EXPECT_THROW(lot.setMaxSize(lot.maxSize()), qc::StableLotError);
    EXPECT_THROW(lot.setMaxSize(qc::pageSize / sizeof(int) * 3u), qc::StableLotError);
    EXPECT_THROW(lot.setMaxSize(1u), qc::StableLotError);
    EXPECT_THROW(lot.setMaxSize(0u), qc::StableLotError);
}

TEST(Lot, freeUnusedPages)
{
    const size_t intsPerPage{qc::pageSize / sizeof(int)};
    qc::StableLot<int> lot{5u * intsPerPage};
    ASSERT_EQ(5u, lot.maxPageCount());
    ASSERT_EQ(5u * intsPerPage, lot.maxSize());
    ASSERT_EQ(0u, lot.pageCount());
    ASSERT_EQ(0u, lot.size());

    lot.freeUnusedPages();

    int * const ints{&lot.construct(0)};
    for (int i{1}; i < int(intsPerPage * 5u); ++i)
    {
        static_cast<void>(lot.construct(i));
    }
    ASSERT_EQ(5u, lot.pageCount());
    ASSERT_EQ(intsPerPage * 5u, lot.size());

    lot.freeUnusedPages();
    ASSERT_EQ(5u, lot.pageCount());
    ASSERT_EQ(intsPerPage * 5u, lot.size());

    for (int i{int(intsPerPage * 4u) + 1}; i < int(intsPerPage * 5u); ++i)
    {
        lot.destruct(ints[i]);
    }
    ASSERT_EQ(5u, lot.pageCount());
    ASSERT_EQ(intsPerPage * 5u, lot.size());

    lot.freeUnusedPages();
    ASSERT_EQ(5u, lot.pageCount());
    ASSERT_EQ(intsPerPage * 5u, lot.size());

    lot.destruct(ints[intsPerPage * 4u]);
    ASSERT_EQ(5u, lot.pageCount());
    ASSERT_EQ(intsPerPage * 5u, lot.size());

    lot.freeUnusedPages();
    ASSERT_EQ(4u, lot.pageCount());
    ASSERT_EQ(intsPerPage * 4u, lot.size());

    for (int i{int(1)}; i < int(intsPerPage * 4u) - 1; ++i)
    {
        lot.destruct(ints[i]);
    }
    ASSERT_EQ(4u, lot.pageCount());
    ASSERT_EQ(intsPerPage * 4u, lot.size());

    lot.freeUnusedPages();
    ASSERT_EQ(4u, lot.pageCount());
    ASSERT_EQ(intsPerPage * 4u, lot.size());

    lot.destruct(ints[intsPerPage * 4u - 1u]);
    ASSERT_EQ(4u, lot.pageCount());
    ASSERT_EQ(intsPerPage * 4u, lot.size());

    lot.freeUnusedPages();
    ASSERT_EQ(1u, lot.pageCount());
    ASSERT_EQ(intsPerPage * 1u, lot.size());

    lot.destruct(ints[0]);
    ASSERT_EQ(1u, lot.pageCount());
    ASSERT_EQ(intsPerPage * 1u, lot.size());

    lot.freeUnusedPages();
    ASSERT_EQ(0u, lot.pageCount());
    ASSERT_EQ(0u, lot.size());

    static_cast<void>(lot.construct(0));
    ASSERT_EQ(1u, lot.pageCount());
    ASSERT_EQ(intsPerPage * 1u, lot.size());
}

TEST(Lot, iteratorAssignability)
{
    static_assert(std::is_assignable_v<qc::StableLot<int>::iterator, qc::StableLot<int>::iterator>);
    static_assert(std::is_assignable_v<qc::StableLot<int>::const_iterator, qc::StableLot<int>::iterator>);
    static_assert(!std::is_assignable_v<qc::StableLot<int>::iterator, qc::StableLot<int>::const_iterator>);
    static_assert(std::is_assignable_v<qc::StableLot<int>::const_iterator, qc::StableLot<int>::const_iterator>);
}
