#include <qc-core/pool.hpp>

#include <gtest/gtest.h>

using namespace qc::types;

TEST(Pool, standard)
{
    // Assumes page size is 4096
    // Each BigInt is 2400 bytes, so 5 would fit into three pages
    ASSERT_EQ(4096u, qc::pageSize);
    struct BigInt { int x; u8 padding[2400u - sizeof(int)]; };

    // [_|_|_|_|_]
    qc::Pool<BigInt> pool{5u};
    ASSERT_EQ(3u, pool.maxPageCount());
    ASSERT_EQ(5u, pool.maxCapacity());
    ASSERT_EQ(0u, pool.pageCount());
    ASSERT_EQ(0u, pool.capacity());
    ASSERT_EQ(0u, pool.size());
    auto it{pool.begin()};
    ASSERT_EQ(pool.end(), it);

    // [0|_|_|_|_]
    BigInt & e0{pool.create(0)};
    ASSERT_EQ(1u, pool.pageCount());
    ASSERT_EQ(1u, pool.capacity());
    ASSERT_EQ(1u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|_|_|_]
    BigInt & e1{pool.create(1)};
    ASSERT_EQ(&e0 + 1, &e1);
    ASSERT_EQ(3u, pool.pageCount());
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(2u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|_|_]
    BigInt & e2{pool.create(2)};
    ASSERT_EQ(&e1 + 1, &e2);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(3u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|3|_]
    BigInt & e3{pool.create(3)};
    ASSERT_EQ(&e2 + 1, &e3);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(4u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(3, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|3|4]
    BigInt & e4{pool.create(4)};
    ASSERT_EQ(&e3 + 1, &e4);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(5u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(3, (++it)->x);
    ASSERT_EQ(4, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|3|4]
    #pragma warning(suppress: 4834)
    EXPECT_THROW(pool.create(5), qc::PoolError);

    // [0|1|2|3|_]
    pool.destroy(e4);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(4u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(3, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|_|_]
    pool.destroy(e3);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(3u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|5|6]
    BigInt & e5{pool.create(5)};
    BigInt & e6{pool.create(6)};
    ASSERT_EQ(&e2 + 1, &e5);
    ASSERT_EQ(&e5 + 1, &e6);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(5u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [_|1|2|5|6]
    pool.destroy(e0);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(4u, pool.size());
    it = pool.begin();
    ASSERT_EQ(1, it->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [_|_|2|5|6]
    pool.destroy(e1);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(3u, pool.size());
    it = pool.begin();
    ASSERT_EQ(2, it->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [7|_|2|5|6]
    BigInt & e7{pool.create(7)};
    ASSERT_EQ(&e2 - 2, &e7);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(4u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [7|_|2|_|6]
    pool.destroy(e5);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(3u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [7|_|_|_|6]
    pool.destroy(e2);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(2u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [7|8|9|10|6]
    BigInt & e8{pool.create(8)};
    BigInt & e9{pool.create(9)};
    BigInt & e10{pool.create(10)};
    ASSERT_EQ(&e7 + 1, &e8);
    ASSERT_EQ(&e7 + 2, &e9);
    ASSERT_EQ(&e7 + 3, &e10);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(5u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(8, (++it)->x);
    ASSERT_EQ(9, (++it)->x);
    ASSERT_EQ(10, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [7|_|_|_|6]
    pool.destroy(e8);
    pool.destroy(e9);
    pool.destroy(e10);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(2u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [7|_|_|_|6]
    ASSERT_THROW(pool.destroy(e8), qc::PoolError);
    ASSERT_THROW(pool.destroy(e9), qc::PoolError);
    ASSERT_THROW(pool.destroy(e10), qc::PoolError);

    // [_|_|_|_|6]
    pool.destroy(e7);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(1u, pool.size());
    it = pool.begin();
    ASSERT_EQ(6, it->x);
    ASSERT_EQ(pool.end(), ++it);

    // [11|_|_|_|6]
    BigInt & e11{pool.create(11)};
    ASSERT_EQ(&e6 - 4, &e11);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(2u, pool.size());
    it = pool.begin();
    ASSERT_EQ(11, it->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [11|_|_|_|_]
    pool.destroy(e6);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(1u, pool.size());
    it = pool.begin();
    ASSERT_EQ(11, it->x);
    ASSERT_EQ(pool.end(), ++it);

    // [_|_|_|_|_]
    pool.destroy(e11);
    ASSERT_EQ(3u, pool.pageCount());
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(0u, pool.size());
    ASSERT_EQ(pool.end(), pool.begin());

    ASSERT_THROW(pool.destroy(e11), qc::PoolError);
}

TEST(FixedPool, standard)
{
    // [_|_|_|_|_]
    qc::FixedPool<int> pool{5u};
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(0u, pool.size());
    auto it{pool.begin()};
    ASSERT_EQ(pool.end(), it);

    // [0|_|_|_|_]
    int & e0{pool.create(0)};
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(1u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, *it);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|_|_|_]
    int & e1{pool.create(1)};
    ASSERT_EQ(&e0 + 1, &e1);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(2u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, *it);
    ASSERT_EQ(1, *++it);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|_|_]
    int & e2{pool.create(2)};
    ASSERT_EQ(&e1 + 1, &e2);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(3u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, *it);
    ASSERT_EQ(1, *++it);
    ASSERT_EQ(2, *++it);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|3|_]
    int & e3{pool.create(3)};
    ASSERT_EQ(&e2 + 1, &e3);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(4u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, *it);
    ASSERT_EQ(1, *++it);
    ASSERT_EQ(2, *++it);
    ASSERT_EQ(3, *++it);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|3|4]
    int & e4{pool.create(4)};
    ASSERT_EQ(&e3 + 1, &e4);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(5u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, *it);
    ASSERT_EQ(1, *++it);
    ASSERT_EQ(2, *++it);
    ASSERT_EQ(3, *++it);
    ASSERT_EQ(4, *++it);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|3|4]
    #pragma warning(suppress: 4834)
    EXPECT_THROW(pool.create(5), qc::PoolError);

    // [0|1|2|3|_]
    pool.destroy(e4);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(4u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, *it);
    ASSERT_EQ(1, *++it);
    ASSERT_EQ(2, *++it);
    ASSERT_EQ(3, *++it);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|_|_]
    pool.destroy(e3);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(3u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, *it);
    ASSERT_EQ(1, *++it);
    ASSERT_EQ(2, *++it);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|5|6]
    int & e5{pool.create(5)};
    int & e6{pool.create(6)};
    ASSERT_EQ(&e2 + 1, &e5);
    ASSERT_EQ(&e5 + 1, &e6);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(5u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, *it);
    ASSERT_EQ(1, *++it);
    ASSERT_EQ(2, *++it);
    ASSERT_EQ(5, *++it);
    ASSERT_EQ(6, *++it);
    ASSERT_EQ(pool.end(), ++it);

    // [_|1|2|5|6]
    pool.destroy(e0);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(4u, pool.size());
    it = pool.begin();
    ASSERT_EQ(1, *it);
    ASSERT_EQ(2, *++it);
    ASSERT_EQ(5, *++it);
    ASSERT_EQ(6, *++it);
    ASSERT_EQ(pool.end(), ++it);

    // [_|_|2|5|6]
    pool.destroy(e1);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(3u, pool.size());
    it = pool.begin();
    ASSERT_EQ(2, *it);
    ASSERT_EQ(5, *++it);
    ASSERT_EQ(6, *++it);
    ASSERT_EQ(pool.end(), ++it);

    // [7|_|2|5|6]
    int & e7{pool.create(7)};
    ASSERT_EQ(&e2 - 2, &e7);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(4u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, *it);
    ASSERT_EQ(2, *++it);
    ASSERT_EQ(5, *++it);
    ASSERT_EQ(6, *++it);
    ASSERT_EQ(pool.end(), ++it);

    // [7|_|2|_|6]
    pool.destroy(e5);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(3u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, *it);
    ASSERT_EQ(2, *++it);
    ASSERT_EQ(6, *++it);
    ASSERT_EQ(pool.end(), ++it);

    // [7|_|_|_|6]
    pool.destroy(e2);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(2u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, *it);
    ASSERT_EQ(6, *++it);
    ASSERT_EQ(pool.end(), ++it);

    // [7|8|9|10|6]
    int & e8{pool.create(8)};
    int & e9{pool.create(9)};
    int & e10{pool.create(10)};
    ASSERT_EQ(&e7 + 1, &e8);
    ASSERT_EQ(&e7 + 2, &e9);
    ASSERT_EQ(&e7 + 3, &e10);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(5u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, *it);
    ASSERT_EQ(8, *++it);
    ASSERT_EQ(9, *++it);
    ASSERT_EQ(10, *++it);
    ASSERT_EQ(6, *++it);
    ASSERT_EQ(pool.end(), ++it);

    // [7|_|_|_|6]
    pool.destroy(e8);
    pool.destroy(e9);
    pool.destroy(e10);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(2u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, *it);
    ASSERT_EQ(6, *++it);
    ASSERT_EQ(pool.end(), ++it);

    // [7|_|_|_|6]
    ASSERT_THROW(pool.destroy(e8), qc::PoolError);
    ASSERT_THROW(pool.destroy(e9), qc::PoolError);
    ASSERT_THROW(pool.destroy(e10), qc::PoolError);

    // [_|_|_|_|6]
    pool.destroy(e7);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(1u, pool.size());
    it = pool.begin();
    ASSERT_EQ(6, *it);
    ASSERT_EQ(pool.end(), ++it);

    // [11|_|_|_|6]
    int & e11{pool.create(11)};
    ASSERT_EQ(&e6 - 4, &e11);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(2u, pool.size());
    it = pool.begin();
    ASSERT_EQ(11, *it);
    ASSERT_EQ(6, *++it);
    ASSERT_EQ(pool.end(), ++it);

    // [11|_|_|_|_]
    pool.destroy(e6);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(1u, pool.size());
    it = pool.begin();
    ASSERT_EQ(11, *it);
    ASSERT_EQ(pool.end(), ++it);

    // [_|_|_|_|_]
    pool.destroy(e11);
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(0u, pool.size());
    ASSERT_EQ(pool.end(), pool.begin());

    ASSERT_THROW(pool.destroy(e11), qc::PoolError);
}

TEST(Pool, single)
{
    qc::Pool<int> pool{1u};
    const size_t maxSize{qc::pageSize / sizeof(int)};
    ASSERT_EQ(1u, pool.maxPageCount());
    ASSERT_EQ(maxSize, pool.maxCapacity());
    ASSERT_EQ(0u, pool.pageCount());
    ASSERT_EQ(0u, pool.capacity());
    ASSERT_EQ(0u, pool.size());
    ASSERT_EQ(pool.end(), pool.begin());

    int & e0{pool.create(0)};
    ASSERT_EQ(1u, pool.pageCount());
    ASSERT_EQ(maxSize, pool.capacity());
    ASSERT_EQ(1u, pool.size());
    auto it{pool.begin()};
    ASSERT_EQ(0, *it);
    ASSERT_EQ(pool.end(), ++it);

    pool.destroy(e0);
    ASSERT_EQ(1u, pool.pageCount());
    ASSERT_EQ(maxSize, pool.capacity());
    ASSERT_EQ(0u, pool.size());
    ASSERT_EQ(pool.end(), pool.begin());
}

TEST(FixedPool, single)
{
    qc::FixedPool<int> pool{1u};
    ASSERT_EQ(1u, pool.capacity());
    ASSERT_EQ(0u, pool.size());
    ASSERT_EQ(pool.end(), pool.begin());

    int & e0{pool.create(0)};
    ASSERT_EQ(1u, pool.size());
    auto it{pool.begin()};
    ASSERT_EQ(0, *it);
    ASSERT_EQ(pool.end(), ++it);

    pool.destroy(e0);
    ASSERT_EQ(0u, pool.size());
    ASSERT_EQ(pool.end(), pool.begin());
}

TEST(Pool, growthRate)
{
    ASSERT_EQ(4096u, qc::pageSize);
    struct PageVal { u8 data[4096u]; };

    {
        qc::Pool<PageVal> pool{24u};
        ASSERT_EQ(24u, pool.maxPageCount());
        ASSERT_EQ(24u, pool.maxCapacity());
        ASSERT_EQ(0u, pool.pageCount());
        ASSERT_EQ(0u, pool.capacity());

        static_cast<void>(pool.create());
        ASSERT_EQ(1u, pool.pageCount());
        ASSERT_EQ(1u, pool.capacity());

        static_cast<void>(pool.create());
        ASSERT_EQ(2u, pool.pageCount());
        ASSERT_EQ(2u, pool.capacity());

        static_cast<void>(pool.create());
        ASSERT_EQ(4u, pool.pageCount());
        ASSERT_EQ(4u, pool.capacity());

        static_cast<void>(pool.create());
        ASSERT_EQ(4u, pool.pageCount());
        ASSERT_EQ(4u, pool.capacity());

        static_cast<void>(pool.create());
        ASSERT_EQ(8u, pool.pageCount());
        ASSERT_EQ(8u, pool.capacity());

        static_cast<void>(pool.create());
        static_cast<void>(pool.create());
        static_cast<void>(pool.create());
        ASSERT_EQ(8u, pool.pageCount());
        ASSERT_EQ(8u, pool.capacity());

        static_cast<void>(pool.create());
        ASSERT_EQ(24u, pool.pageCount());
        ASSERT_EQ(24u, pool.capacity());
    }

    {
        qc::Pool<PageVal> pool{25u};
        ASSERT_EQ(25u, pool.maxPageCount());
        ASSERT_EQ(25u, pool.maxCapacity());
        ASSERT_EQ(0u, pool.pageCount());
        ASSERT_EQ(0u, pool.capacity());

        static_cast<void>(pool.create());
        ASSERT_EQ(1u, pool.pageCount());
        ASSERT_EQ(1u, pool.capacity());

        static_cast<void>(pool.create());
        ASSERT_EQ(2u, pool.pageCount());
        ASSERT_EQ(2u, pool.capacity());

        static_cast<void>(pool.create());
        ASSERT_EQ(4u, pool.pageCount());
        ASSERT_EQ(4u, pool.capacity());

        static_cast<void>(pool.create());
        ASSERT_EQ(4u, pool.pageCount());
        ASSERT_EQ(4u, pool.capacity());

        static_cast<void>(pool.create());
        ASSERT_EQ(8u, pool.pageCount());
        ASSERT_EQ(8u, pool.capacity());

        static_cast<void>(pool.create());
        static_cast<void>(pool.create());
        static_cast<void>(pool.create());
        ASSERT_EQ(8u, pool.pageCount());
        ASSERT_EQ(8u, pool.capacity());

        static_cast<void>(pool.create());
        ASSERT_EQ(16u, pool.pageCount());
        ASSERT_EQ(16u, pool.capacity());

        static_cast<void>(pool.create());
        static_cast<void>(pool.create());
        static_cast<void>(pool.create());
        static_cast<void>(pool.create());
        static_cast<void>(pool.create());
        static_cast<void>(pool.create());
        static_cast<void>(pool.create());
        ASSERT_EQ(16u, pool.pageCount());
        ASSERT_EQ(16u, pool.capacity());

        static_cast<void>(pool.create());
        ASSERT_EQ(25u, pool.pageCount());
        ASSERT_EQ(25u, pool.capacity());
    }
}

TEST(Pool, biggerThanPageVal)
{
    ASSERT_EQ(4096u, qc::pageSize);
    struct HugeVal { u8 data[5000u]; };

    qc::Pool<HugeVal> pool{1u};
    ASSERT_EQ(2u, pool.maxPageCount());
    ASSERT_EQ(1u, pool.maxCapacity());
    ASSERT_EQ(0u, pool.pageCount());
    ASSERT_EQ(0u, pool.capacity());

    HugeVal & v{pool.create()};
    ASSERT_EQ(2u, pool.pageCount());
    ASSERT_EQ(1u, pool.capacity());

    ++v.data[0];
    ++v.data[sizeof(HugeVal) - 1u];

    pool.destroy(v);
    ASSERT_EQ(2u, pool.pageCount());
    ASSERT_EQ(1u, pool.capacity());
}

TEST(Pool, setMaxCapacity)
{
    qc::Pool<int> pool{};
    ASSERT_EQ(0u, pool.maxPageCount());
    ASSERT_EQ(0u, pool.maxCapacity());
    ASSERT_EQ(0u, pool.pageCount());
    ASSERT_EQ(0u, pool.capacity());

    EXPECT_THROW(static_cast<void>(pool.create(0)), qc::PoolError);

    pool.setMaxCapacity(1u);
    ASSERT_EQ(1u, pool.maxPageCount());
    ASSERT_EQ(qc::pageSize / sizeof(int), pool.maxCapacity());
    ASSERT_EQ(0u, pool.pageCount());
    ASSERT_EQ(0u, pool.capacity());

    pool.setMaxCapacity(0u);
    ASSERT_EQ(0u, pool.maxPageCount());
    ASSERT_EQ(0u, pool.maxCapacity());
    ASSERT_EQ(0u, pool.pageCount());
    ASSERT_EQ(0u, pool.capacity());

    EXPECT_THROW(static_cast<void>(pool.create(0)), qc::PoolError);

    pool.setMaxCapacity(qc::pageSize / sizeof(int) * 2u);
    ASSERT_EQ(2u, pool.maxPageCount());
    ASSERT_EQ(qc::pageSize / sizeof(int) * 2u, pool.maxCapacity());
    ASSERT_EQ(0u, pool.pageCount());
    ASSERT_EQ(0u, pool.capacity());

    pool.setMaxCapacity(1u);
    ASSERT_EQ(1u, pool.maxPageCount());
    ASSERT_EQ(qc::pageSize / sizeof(int), pool.maxCapacity());
    ASSERT_EQ(0u, pool.pageCount());
    ASSERT_EQ(0u, pool.capacity());

    [[maybe_unused]] int & v{pool.create(0)};

    EXPECT_THROW(pool.setMaxCapacity(pool.maxCapacity()), qc::PoolError);
    EXPECT_THROW(pool.setMaxCapacity(qc::pageSize / sizeof(int) * 3u), qc::PoolError);
    EXPECT_THROW(pool.setMaxCapacity(1u), qc::PoolError);
    EXPECT_THROW(pool.setMaxCapacity(0u), qc::PoolError);
}

TEST(FixedPool, setCapacity)
{
    qc::FixedPool<int> pool{};
    ASSERT_EQ(0u, pool.capacity());

    EXPECT_THROW(static_cast<void>(pool.create(0)), qc::PoolError);

    pool.setCapacity(1u);
    ASSERT_EQ(1u, pool.capacity());

    EXPECT_THROW(pool.setCapacity(2u), qc::PoolError);
    EXPECT_THROW(pool.setCapacity(0u), qc::PoolError);
}

TEST(Pool, freeUnusedPages)
{
    const size_t intsPerPage{qc::pageSize / sizeof(int)};
    qc::Pool<int> pool{5u * intsPerPage};
    ASSERT_EQ(5u, pool.maxPageCount());
    ASSERT_EQ(5u * intsPerPage, pool.maxCapacity());
    ASSERT_EQ(0u, pool.pageCount());
    ASSERT_EQ(0u, pool.capacity());

    pool.freeUnusedPages();

    int * const ints{&pool.create(0)};
    for (int i{1}; i < int(intsPerPage * 5u); ++i)
    {
        static_cast<void>(pool.create(i));
    }
    ASSERT_EQ(5u, pool.pageCount());
    ASSERT_EQ(intsPerPage * 5u, pool.capacity());

    pool.freeUnusedPages();
    ASSERT_EQ(5u, pool.pageCount());
    ASSERT_EQ(intsPerPage * 5u, pool.capacity());

    for (int i{int(intsPerPage * 4u) + 1}; i < int(intsPerPage * 5u); ++i)
    {
        pool.destroy(ints[i]);
    }
    ASSERT_EQ(5u, pool.pageCount());
    ASSERT_EQ(intsPerPage * 5u, pool.capacity());

    pool.freeUnusedPages();
    ASSERT_EQ(5u, pool.pageCount());
    ASSERT_EQ(intsPerPage * 5u, pool.capacity());

    pool.destroy(ints[intsPerPage * 4u]);
    ASSERT_EQ(5u, pool.pageCount());
    ASSERT_EQ(intsPerPage * 5u, pool.capacity());

    pool.freeUnusedPages();
    ASSERT_EQ(4u, pool.pageCount());
    ASSERT_EQ(intsPerPage * 4u, pool.capacity());

    for (int i{int(1)}; i < int(intsPerPage * 4u) - 1; ++i)
    {
        pool.destroy(ints[i]);
    }
    ASSERT_EQ(4u, pool.pageCount());
    ASSERT_EQ(intsPerPage * 4u, pool.capacity());

    pool.freeUnusedPages();
    ASSERT_EQ(4u, pool.pageCount());
    ASSERT_EQ(intsPerPage * 4u, pool.capacity());

    pool.destroy(ints[intsPerPage * 4u - 1u]);
    ASSERT_EQ(4u, pool.pageCount());
    ASSERT_EQ(intsPerPage * 4u, pool.capacity());

    pool.freeUnusedPages();
    ASSERT_EQ(1u, pool.pageCount());
    ASSERT_EQ(intsPerPage * 1u, pool.capacity());

    pool.destroy(ints[0]);
    ASSERT_EQ(1u, pool.pageCount());
    ASSERT_EQ(intsPerPage * 1u, pool.capacity());

    pool.freeUnusedPages();
    ASSERT_EQ(0u, pool.pageCount());
    ASSERT_EQ(0u, pool.capacity());

    static_cast<void>(pool.create(0));
    ASSERT_EQ(1u, pool.pageCount());
    ASSERT_EQ(intsPerPage * 1u, pool.capacity());
}

TEST(Pool, iteratorAssignability)
{
    static_assert(std::is_assignable_v<qc::Pool<int>::iterator, qc::Pool<int>::iterator>);
    static_assert(std::is_assignable_v<qc::Pool<int>::const_iterator, qc::Pool<int>::iterator>);
    static_assert(!std::is_assignable_v<qc::Pool<int>::iterator, qc::Pool<int>::const_iterator>);
    static_assert(std::is_assignable_v<qc::Pool<int>::const_iterator, qc::Pool<int>::const_iterator>);
}

TEST(FixedPool, iteratorAssignability)
{
    static_assert(std::is_assignable_v<qc::FixedPool<int>::iterator, qc::FixedPool<int>::iterator>);
    static_assert(std::is_assignable_v<qc::FixedPool<int>::const_iterator, qc::FixedPool<int>::iterator>);
    static_assert(!std::is_assignable_v<qc::FixedPool<int>::iterator, qc::FixedPool<int>::const_iterator>);
    static_assert(std::is_assignable_v<qc::FixedPool<int>::const_iterator, qc::FixedPool<int>::const_iterator>);
}

TEST(PoolCommon, baseClassNonconstructible)
{
    static_assert(!std::is_default_constructible_v<qc::_Pool<int>>);
}
