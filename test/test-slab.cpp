#include <qc-core/slab.hpp>

#include <gtest/gtest.h>

using namespace qc::types;

TEST(Slab, standard)
{
    // Assumes page size is 4096
    // Each BigInt is 2400 bytes, so 5 would fit into three pages
    ASSERT_EQ(4096u, qc::pageSize);
    struct BigInt { int x; u8 padding[2400u - sizeof(int)]; };

    // [_|_|_|_|_]
    qc::Slab<BigInt> slab{5u};
    ASSERT_EQ(3u, slab.maxPageCount());
    ASSERT_EQ(5u, slab.maxSize());
    ASSERT_EQ(0u, slab.pageCount());
    ASSERT_EQ(0u, slab.size());
    ASSERT_EQ(0u, slab.usedCount());
    auto it{slab.begin()};
    ASSERT_EQ(slab.end(), it);

    // [0|_|_|_|_]
    BigInt & e0{slab.construct(0)};
    ASSERT_EQ(1u, slab.pageCount());
    ASSERT_EQ(1u, slab.size());
    ASSERT_EQ(1u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(slab.end(), ++it);

    // [0|1|_|_|_]
    BigInt & e1{slab.construct(1)};
    ASSERT_EQ(&e0 + 1, &e1);
    ASSERT_EQ(3u, slab.pageCount());
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(2u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(slab.end(), ++it);

    // [0|1|2|_|_]
    BigInt & e2{slab.construct(2)};
    ASSERT_EQ(&e1 + 1, &e2);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(3u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(slab.end(), ++it);

    // [0|1|2|3|_]
    BigInt & e3{slab.construct(3)};
    ASSERT_EQ(&e2 + 1, &e3);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(4u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(3, (++it)->x);
    ASSERT_EQ(slab.end(), ++it);

    // [0|1|2|3|4]
    BigInt & e4{slab.construct(4)};
    ASSERT_EQ(&e3 + 1, &e4);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(5u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(3, (++it)->x);
    ASSERT_EQ(4, (++it)->x);
    ASSERT_EQ(slab.end(), ++it);

    // [0|1|2|3|4]
    #pragma warning(suppress: 4834)
    EXPECT_THROW(slab.construct(5), qc::SlabError);

    // [0|1|2|3|_]
    slab.destruct(e4);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(4u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(3, (++it)->x);
    ASSERT_EQ(slab.end(), ++it);

    // [0|1|2|_|_]
    slab.destruct(e3);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(3u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(slab.end(), ++it);

    // [0|1|2|5|6]
    BigInt & e5{slab.construct(5)};
    BigInt & e6{slab.construct(6)};
    ASSERT_EQ(&e2 + 1, &e5);
    ASSERT_EQ(&e5 + 1, &e6);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(5u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(slab.end(), ++it);

    // [_|1|2|5|6]
    slab.destruct(e0);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(4u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(1, it->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(slab.end(), ++it);

    // [_|_|2|5|6]
    slab.destruct(e1);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(3u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(2, it->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(slab.end(), ++it);

    // [7|_|2|5|6]
    BigInt & e7{slab.construct(7)};
    ASSERT_EQ(&e2 - 2, &e7);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(4u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(slab.end(), ++it);

    // [7|_|2|_|6]
    slab.destruct(e5);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(3u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(slab.end(), ++it);

    // [7|_|_|_|6]
    slab.destruct(e2);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(2u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(slab.end(), ++it);

    // [7|8|9|10|6]
    BigInt & e8{slab.construct(8)};
    BigInt & e9{slab.construct(9)};
    BigInt & e10{slab.construct(10)};
    ASSERT_EQ(&e7 + 1, &e8);
    ASSERT_EQ(&e7 + 2, &e9);
    ASSERT_EQ(&e7 + 3, &e10);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(5u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(8, (++it)->x);
    ASSERT_EQ(9, (++it)->x);
    ASSERT_EQ(10, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(slab.end(), ++it);

    // [7|_|_|_|6]
    slab.destruct(e8);
    slab.destruct(e9);
    slab.destruct(e10);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(2u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(slab.end(), ++it);

    // [7|_|_|_|6]
    ASSERT_THROW(slab.destruct(e8), qc::SlabError);
    ASSERT_THROW(slab.destruct(e9), qc::SlabError);
    ASSERT_THROW(slab.destruct(e10), qc::SlabError);

    // [_|_|_|_|6]
    slab.destruct(e7);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(1u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(6, it->x);
    ASSERT_EQ(slab.end(), ++it);

    // [11|_|_|_|6]
    BigInt & e11{slab.construct(11)};
    ASSERT_EQ(&e6 - 4, &e11);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(2u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(11, it->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(slab.end(), ++it);

    // [11|_|_|_|_]
    slab.destruct(e6);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(1u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(11, it->x);
    ASSERT_EQ(slab.end(), ++it);

    // [_|_|_|_|_]
    slab.destruct(e11);
    ASSERT_EQ(3u, slab.pageCount());
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(0u, slab.usedCount());
    ASSERT_EQ(slab.end(), slab.begin());

    ASSERT_THROW(slab.destruct(e11), qc::SlabError);
}

TEST(Slab, single)
{
    qc::Slab<int> slab{1u};
    const size_t maxSize{qc::pageSize / sizeof(int)};
    ASSERT_EQ(1u, slab.maxPageCount());
    ASSERT_EQ(maxSize, slab.maxSize());
    ASSERT_EQ(0u, slab.pageCount());
    ASSERT_EQ(0u, slab.size());
    ASSERT_EQ(0u, slab.usedCount());
    ASSERT_EQ(slab.end(), slab.begin());

    int & e0{slab.construct(0)};
    ASSERT_EQ(1u, slab.pageCount());
    ASSERT_EQ(maxSize, slab.size());
    ASSERT_EQ(1u, slab.usedCount());
    auto it{slab.begin()};
    ASSERT_EQ(0, *it);
    ASSERT_EQ(slab.end(), ++it);

    slab.destruct(e0);
    ASSERT_EQ(1u, slab.pageCount());
    ASSERT_EQ(maxSize, slab.size());
    ASSERT_EQ(0u, slab.usedCount());
    ASSERT_EQ(slab.end(), slab.begin());
}

TEST(Slab, growthRate)
{
    ASSERT_EQ(4096u, qc::pageSize);
    struct PageVal { u8 data[4096u]; };

    {
        qc::Slab<PageVal> slab{24u};
        ASSERT_EQ(24u, slab.maxPageCount());
        ASSERT_EQ(24u, slab.maxSize());
        ASSERT_EQ(0u, slab.pageCount());
        ASSERT_EQ(0u, slab.size());

        static_cast<void>(slab.construct());
        ASSERT_EQ(1u, slab.pageCount());
        ASSERT_EQ(1u, slab.size());

        static_cast<void>(slab.construct());
        ASSERT_EQ(2u, slab.pageCount());
        ASSERT_EQ(2u, slab.size());

        static_cast<void>(slab.construct());
        ASSERT_EQ(4u, slab.pageCount());
        ASSERT_EQ(4u, slab.size());

        static_cast<void>(slab.construct());
        ASSERT_EQ(4u, slab.pageCount());
        ASSERT_EQ(4u, slab.size());

        static_cast<void>(slab.construct());
        ASSERT_EQ(8u, slab.pageCount());
        ASSERT_EQ(8u, slab.size());

        static_cast<void>(slab.construct());
        static_cast<void>(slab.construct());
        static_cast<void>(slab.construct());
        ASSERT_EQ(8u, slab.pageCount());
        ASSERT_EQ(8u, slab.size());

        static_cast<void>(slab.construct());
        ASSERT_EQ(24u, slab.pageCount());
        ASSERT_EQ(24u, slab.size());
    }

    {
        qc::Slab<PageVal> slab{25u};
        ASSERT_EQ(25u, slab.maxPageCount());
        ASSERT_EQ(25u, slab.maxSize());
        ASSERT_EQ(0u, slab.pageCount());
        ASSERT_EQ(0u, slab.size());

        static_cast<void>(slab.construct());
        ASSERT_EQ(1u, slab.pageCount());
        ASSERT_EQ(1u, slab.size());

        static_cast<void>(slab.construct());
        ASSERT_EQ(2u, slab.pageCount());
        ASSERT_EQ(2u, slab.size());

        static_cast<void>(slab.construct());
        ASSERT_EQ(4u, slab.pageCount());
        ASSERT_EQ(4u, slab.size());

        static_cast<void>(slab.construct());
        ASSERT_EQ(4u, slab.pageCount());
        ASSERT_EQ(4u, slab.size());

        static_cast<void>(slab.construct());
        ASSERT_EQ(8u, slab.pageCount());
        ASSERT_EQ(8u, slab.size());

        static_cast<void>(slab.construct());
        static_cast<void>(slab.construct());
        static_cast<void>(slab.construct());
        ASSERT_EQ(8u, slab.pageCount());
        ASSERT_EQ(8u, slab.size());

        static_cast<void>(slab.construct());
        ASSERT_EQ(16u, slab.pageCount());
        ASSERT_EQ(16u, slab.size());

        static_cast<void>(slab.construct());
        static_cast<void>(slab.construct());
        static_cast<void>(slab.construct());
        static_cast<void>(slab.construct());
        static_cast<void>(slab.construct());
        static_cast<void>(slab.construct());
        static_cast<void>(slab.construct());
        ASSERT_EQ(16u, slab.pageCount());
        ASSERT_EQ(16u, slab.size());

        static_cast<void>(slab.construct());
        ASSERT_EQ(25u, slab.pageCount());
        ASSERT_EQ(25u, slab.size());
    }
}

TEST(Slab, biggerThanPageVal)
{
    ASSERT_EQ(4096u, qc::pageSize);
    struct HugeVal { u8 data[5000u]; };

    qc::Slab<HugeVal> slab{1u};
    ASSERT_EQ(2u, slab.maxPageCount());
    ASSERT_EQ(1u, slab.maxSize());
    ASSERT_EQ(0u, slab.pageCount());
    ASSERT_EQ(0u, slab.size());

    HugeVal & v{slab.construct()};
    ASSERT_EQ(2u, slab.pageCount());
    ASSERT_EQ(1u, slab.size());

    ++v.data[0];
    ++v.data[sizeof(HugeVal) - 1u];

    slab.destruct(v);
    ASSERT_EQ(2u, slab.pageCount());
    ASSERT_EQ(1u, slab.size());
}

TEST(Slab, deferredMaxSize)
{
    qc::Slab<int> slab{};
    ASSERT_EQ(0u, slab.maxPageCount());
    ASSERT_EQ(0u, slab.maxSize());
    ASSERT_EQ(0u, slab.pageCount());
    ASSERT_EQ(0u, slab.size());

    EXPECT_THROW(static_cast<void>(slab.construct(0)), qc::SlabError);

    slab.setMaxSize(1u);
    ASSERT_EQ(1u, slab.maxPageCount());
    ASSERT_EQ(qc::pageSize / sizeof(int), slab.maxSize());
    ASSERT_EQ(0u, slab.pageCount());
    ASSERT_EQ(0u, slab.size());

    slab.setMaxSize(0u);
    ASSERT_EQ(0u, slab.maxPageCount());
    ASSERT_EQ(0u, slab.maxSize());
    ASSERT_EQ(0u, slab.pageCount());
    ASSERT_EQ(0u, slab.size());

    EXPECT_THROW(static_cast<void>(slab.construct(0)), qc::SlabError);

    slab.setMaxSize(qc::pageSize / sizeof(int) * 2u);
    ASSERT_EQ(2u, slab.maxPageCount());
    ASSERT_EQ(qc::pageSize / sizeof(int) * 2u, slab.maxSize());
    ASSERT_EQ(0u, slab.pageCount());
    ASSERT_EQ(0u, slab.size());

    slab.setMaxSize(1u);
    ASSERT_EQ(1u, slab.maxPageCount());
    ASSERT_EQ(qc::pageSize / sizeof(int), slab.maxSize());
    ASSERT_EQ(0u, slab.pageCount());
    ASSERT_EQ(0u, slab.size());

    [[maybe_unused]] int & v{slab.construct(0)};

    EXPECT_THROW(slab.setMaxSize(slab.maxSize()), qc::SlabError);
    EXPECT_THROW(slab.setMaxSize(qc::pageSize / sizeof(int) * 3u), qc::SlabError);
    EXPECT_THROW(slab.setMaxSize(1u), qc::SlabError);
    EXPECT_THROW(slab.setMaxSize(0u), qc::SlabError);
}

TEST(Slab, freeUnusedPages)
{
    const size_t intsPerPage{qc::pageSize / sizeof(int)};
    qc::Slab<int> slab{5u * intsPerPage};
    ASSERT_EQ(5u, slab.maxPageCount());
    ASSERT_EQ(5u * intsPerPage, slab.maxSize());
    ASSERT_EQ(0u, slab.pageCount());
    ASSERT_EQ(0u, slab.size());

    slab.freeUnusedPages();

    int * const ints{&slab.construct(0)};
    for (int i{1}; i < int(intsPerPage * 5u); ++i)
    {
        static_cast<void>(slab.construct(i));
    }
    ASSERT_EQ(5u, slab.pageCount());
    ASSERT_EQ(intsPerPage * 5u, slab.size());

    slab.freeUnusedPages();
    ASSERT_EQ(5u, slab.pageCount());
    ASSERT_EQ(intsPerPage * 5u, slab.size());

    for (int i{int(intsPerPage * 4u) + 1}; i < int(intsPerPage * 5u); ++i)
    {
        slab.destruct(ints[i]);
    }
    ASSERT_EQ(5u, slab.pageCount());
    ASSERT_EQ(intsPerPage * 5u, slab.size());

    slab.freeUnusedPages();
    ASSERT_EQ(5u, slab.pageCount());
    ASSERT_EQ(intsPerPage * 5u, slab.size());

    slab.destruct(ints[intsPerPage * 4u]);
    ASSERT_EQ(5u, slab.pageCount());
    ASSERT_EQ(intsPerPage * 5u, slab.size());

    slab.freeUnusedPages();
    ASSERT_EQ(4u, slab.pageCount());
    ASSERT_EQ(intsPerPage * 4u, slab.size());

    for (int i{int(1)}; i < int(intsPerPage * 4u) - 1; ++i)
    {
        slab.destruct(ints[i]);
    }
    ASSERT_EQ(4u, slab.pageCount());
    ASSERT_EQ(intsPerPage * 4u, slab.size());

    slab.freeUnusedPages();
    ASSERT_EQ(4u, slab.pageCount());
    ASSERT_EQ(intsPerPage * 4u, slab.size());

    slab.destruct(ints[intsPerPage * 4u - 1u]);
    ASSERT_EQ(4u, slab.pageCount());
    ASSERT_EQ(intsPerPage * 4u, slab.size());

    slab.freeUnusedPages();
    ASSERT_EQ(1u, slab.pageCount());
    ASSERT_EQ(intsPerPage * 1u, slab.size());

    slab.destruct(ints[0]);
    ASSERT_EQ(1u, slab.pageCount());
    ASSERT_EQ(intsPerPage * 1u, slab.size());

    slab.freeUnusedPages();
    ASSERT_EQ(0u, slab.pageCount());
    ASSERT_EQ(0u, slab.size());

    static_cast<void>(slab.construct(0));
    ASSERT_EQ(1u, slab.pageCount());
    ASSERT_EQ(intsPerPage * 1u, slab.size());
}

TEST(Slab, iteratorAssignability)
{
    static_assert(std::is_assignable_v<qc::Slab<int>::iterator, qc::Slab<int>::iterator>);
    static_assert(std::is_assignable_v<qc::Slab<int>::const_iterator, qc::Slab<int>::iterator>);
    static_assert(!std::is_assignable_v<qc::Slab<int>::iterator, qc::Slab<int>::const_iterator>);
    static_assert(std::is_assignable_v<qc::Slab<int>::const_iterator, qc::Slab<int>::const_iterator>);
}
