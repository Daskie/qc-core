#include <qc-core/pool.hpp>

#include <gtest/gtest.h>

using namespace qc::types;
using namespace qc::primitives;

TEST(Pool, standard)
{
    // Assumes page size is 4096
    // Each BigInt is 2400 bytes, so 5 would fit into three pages
    ASSERT_EQ(4096u, qc::pageSize);
    struct BigInt
    {
        s32 x;
        u8 padding[2400u - sizeof(s32)];

        BigInt() = default;
        BigInt(s32 x_) : x{x_} {}
    };

    // [_|_|_|_|_]
    qc::Pool<BigInt> pool{5u};
    ASSERT_EQ(3u, pool.maxPageN());
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(0u, pool.pageN());
    ASSERT_EQ(0u, pool.size());
    auto it{pool.begin()};
    ASSERT_EQ(pool.end(), it);

    // [0|_|_|_|_]
    BigInt & e0{pool.create(0)};
    ASSERT_EQ(1u, pool.pageN());
    ASSERT_EQ(1u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|_|_|_]
    BigInt & e1{pool.create(1)};
    ASSERT_EQ(&e0 + 1, &e1);
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(2u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|_|_]
    BigInt & e2{pool.create(2)};
    ASSERT_EQ(&e1 + 1, &e2);
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(3u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|3|_]
    BigInt & e3{pool.create(3)};
    ASSERT_EQ(&e2 + 1, &e3);
    ASSERT_EQ(3u, pool.pageN());
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
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(5u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(3, (++it)->x);
    ASSERT_EQ(4, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|3|4]
    ASSERT_DEATH(static_cast<void>(pool.create(5)), "");

    // [0|1|2|3|_]
    pool.destroy(e4);
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(4u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(3, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|_|_]
    pool.destroy(e3);
    ASSERT_EQ(3u, pool.pageN());
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
    ASSERT_EQ(3u, pool.pageN());
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
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(4u, pool.size());
    it = pool.begin();
    ASSERT_EQ(1, it->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [_|_|2|5|6]
    pool.destroy(e1);
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(3u, pool.size());
    it = pool.begin();
    ASSERT_EQ(2, it->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [7|_|2|5|6]
    BigInt & e7{pool.create(7)};
    ASSERT_EQ(&e2 - 2, &e7);
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(4u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [7|_|2|_|6]
    pool.destroy(e5);
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(3u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [7|_|_|_|6]
    pool.destroy(e2);
    ASSERT_EQ(3u, pool.pageN());
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
    ASSERT_EQ(3u, pool.pageN());
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
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(2u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [7|_|_|_|6]
    ASSERT_DEBUG_DEATH(pool.destroy(e8), "");
    ASSERT_DEBUG_DEATH(pool.destroy(e9), "");
    ASSERT_DEBUG_DEATH(pool.destroy(e10), "");

    // [_|_|_|_|6]
    pool.destroy(e7);
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(1u, pool.size());
    it = pool.begin();
    ASSERT_EQ(6, it->x);
    ASSERT_EQ(pool.end(), ++it);

    // [11|_|_|_|6]
    BigInt & e11{pool.create(11)};
    ASSERT_EQ(&e6 - 4, &e11);
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(2u, pool.size());
    it = pool.begin();
    ASSERT_EQ(11, it->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [11|_|_|_|_]
    pool.destroy(e6);
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(1u, pool.size());
    it = pool.begin();
    ASSERT_EQ(11, it->x);
    ASSERT_EQ(pool.end(), ++it);

    // [_|_|_|_|_]
    pool.destroy(e11);
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(0u, pool.size());
    ASSERT_EQ(pool.end(), pool.begin());

    ASSERT_DEBUG_DEATH(pool.destroy(e11), "");
}

TEST(Pool, single)
{
    qc::Pool<s32> pool{1u};
    const u64 maxCapacity{qc::pageSize / sizeof(s32)};
    ASSERT_EQ(1u, pool.maxPageN());
    ASSERT_EQ(maxCapacity, pool.capacity());
    ASSERT_EQ(0u, pool.pageN());
    ASSERT_EQ(0u, pool.size());
    ASSERT_EQ(pool.end(), pool.begin());

    s32 & e0{pool.create(0)};
    ASSERT_EQ(maxCapacity, pool.capacity());
    ASSERT_EQ(1u, pool.pageN());
    ASSERT_EQ(1u, pool.size());
    auto it{pool.begin()};
    ASSERT_EQ(0, *it);
    ASSERT_EQ(pool.end(), ++it);

    pool.destroy(e0);
    ASSERT_EQ(maxCapacity, pool.capacity());
    ASSERT_EQ(1u, pool.pageN());
    ASSERT_EQ(0u, pool.size());
    ASSERT_EQ(pool.end(), pool.begin());
}

TEST(Pool, growthRate)
{
    struct PageVal { u8 data[qc::pageSize]; };

    {
        qc::Pool<PageVal> pool{24u};
        ASSERT_EQ(24u, pool.maxPageN());
        ASSERT_EQ(24u, pool.capacity());
        ASSERT_EQ(0u, pool.pageN());

        static_cast<void>(pool.create());
        ASSERT_EQ(24u, pool.capacity());
        ASSERT_EQ(1u, pool.pageN());

        static_cast<void>(pool.create());
        ASSERT_EQ(24u, pool.capacity());
        ASSERT_EQ(2u, pool.pageN());

        static_cast<void>(pool.create());
        ASSERT_EQ(24u, pool.capacity());
        ASSERT_EQ(4u, pool.pageN());

        static_cast<void>(pool.create());
        ASSERT_EQ(24u, pool.capacity());
        ASSERT_EQ(4u, pool.pageN());

        static_cast<void>(pool.create());
        ASSERT_EQ(24u, pool.capacity());
        ASSERT_EQ(8u, pool.pageN());

        static_cast<void>(pool.create());
        static_cast<void>(pool.create());
        static_cast<void>(pool.create());
        ASSERT_EQ(24u, pool.capacity());
        ASSERT_EQ(8u, pool.pageN());

        static_cast<void>(pool.create());
        ASSERT_EQ(24u, pool.capacity());
        ASSERT_EQ(24u, pool.pageN());
    }

    {
        qc::Pool<PageVal> pool{25u};
        ASSERT_EQ(25u, pool.maxPageN());
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(0u, pool.pageN());

        static_cast<void>(pool.create());
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(1u, pool.pageN());

        static_cast<void>(pool.create());
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(2u, pool.pageN());

        static_cast<void>(pool.create());
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(4u, pool.pageN());

        static_cast<void>(pool.create());
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(4u, pool.pageN());

        static_cast<void>(pool.create());
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(8u, pool.pageN());

        static_cast<void>(pool.create());
        static_cast<void>(pool.create());
        static_cast<void>(pool.create());
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(8u, pool.pageN());

        static_cast<void>(pool.create());
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(16u, pool.pageN());

        static_cast<void>(pool.create());
        static_cast<void>(pool.create());
        static_cast<void>(pool.create());
        static_cast<void>(pool.create());
        static_cast<void>(pool.create());
        static_cast<void>(pool.create());
        static_cast<void>(pool.create());
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(16u, pool.pageN());

        static_cast<void>(pool.create());
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(25u, pool.pageN());
    }
}

TEST(Pool, biggerThanPageVal)
{
    ASSERT_EQ(4096u, qc::pageSize);
    struct HugeVal { u8 data[5000u]; };

    qc::Pool<HugeVal> pool{1u};
    ASSERT_EQ(2u, pool.maxPageN());
    ASSERT_EQ(1u, pool.capacity());
    ASSERT_EQ(0u, pool.pageN());

    HugeVal & v{pool.create()};
    ASSERT_EQ(1u, pool.capacity());
    ASSERT_EQ(2u, pool.pageN());

    ++v.data[0];
    ++v.data[sizeof(HugeVal) - 1u];

    pool.destroy(v);
    ASSERT_EQ(1u, pool.capacity());
    ASSERT_EQ(2u, pool.pageN());
}

TEST(Pool, setCapacity)
{
    qc::Pool<s32> pool{};
    ASSERT_EQ(0u, pool.maxPageN());
    ASSERT_EQ(0u, pool.capacity());
    ASSERT_EQ(0u, pool.pageN());

    ASSERT_DEATH(static_cast<void>(pool.create(0)), "");

    pool.setCapacity(1u);
    ASSERT_EQ(1u, pool.maxPageN());
    ASSERT_EQ(qc::pageSize / sizeof(s32), pool.capacity());
    ASSERT_EQ(0u, pool.pageN());

    pool.setCapacity(0u);
    ASSERT_EQ(0u, pool.maxPageN());
    ASSERT_EQ(0u, pool.capacity());
    ASSERT_EQ(0u, pool.pageN());

    ASSERT_DEATH(static_cast<void>(pool.create(0)), "");

    pool.setCapacity(qc::pageSize / sizeof(s32) * 2u);
    ASSERT_EQ(2u, pool.maxPageN());
    ASSERT_EQ(qc::pageSize / sizeof(s32) * 2u, pool.capacity());
    ASSERT_EQ(0u, pool.pageN());

    pool.setCapacity(1u);
    ASSERT_EQ(1u, pool.maxPageN());
    ASSERT_EQ(qc::pageSize / sizeof(s32), pool.capacity());
    ASSERT_EQ(0u, pool.pageN());

    [[maybe_unused]] s32 & v{pool.create(0)};

    ASSERT_DEBUG_DEATH(pool.setCapacity(pool.capacity()), "");
    ASSERT_DEBUG_DEATH(pool.setCapacity(qc::pageSize / sizeof(s32) * 3u), "");
    ASSERT_DEBUG_DEATH(pool.setCapacity(1u), "");
    ASSERT_DEBUG_DEATH(pool.setCapacity(0u), "");
}

TEST(Pool, shrinkToFit)
{
    const u64 intsPerPage{qc::pageSize / sizeof(s32)};
    qc::Pool<s32> pool{5u * intsPerPage};
    ASSERT_EQ(5u, pool.maxPageN());
    ASSERT_EQ(5u * intsPerPage, pool.capacity());
    ASSERT_EQ(0u, pool.pageN());

    pool.shrinkToFit();

    s32 * const ints{&pool.create(0)};
    for (s32 i{1}; i < s32(intsPerPage * 5u); ++i)
    {
        static_cast<void>(pool.create(i));
    }
    ASSERT_EQ(5u, pool.pageN());

    pool.shrinkToFit();
    ASSERT_EQ(5u, pool.pageN());

    for (s32 i{s32(intsPerPage * 4u) + 1}; i < s32(intsPerPage * 5u); ++i)
    {
        pool.destroy(ints[i]);
    }
    ASSERT_EQ(5u, pool.pageN());

    pool.shrinkToFit();
    ASSERT_EQ(5u, pool.pageN());

    pool.destroy(ints[intsPerPage * 4u]);
    ASSERT_EQ(5u, pool.pageN());

    pool.shrinkToFit();
    ASSERT_EQ(4u, pool.pageN());

    for (s32 i{1}; i < s32(intsPerPage * 4u) - 1; ++i)
    {
        pool.destroy(ints[i]);
    }
    ASSERT_EQ(4u, pool.pageN());

    pool.shrinkToFit();
    ASSERT_EQ(4u, pool.pageN());

    pool.destroy(ints[intsPerPage * 4u - 1u]);
    ASSERT_EQ(4u, pool.pageN());

    pool.shrinkToFit();
    ASSERT_EQ(1u, pool.pageN());

    pool.destroy(ints[0]);
    ASSERT_EQ(1u, pool.pageN());

    pool.shrinkToFit();
    ASSERT_EQ(0u, pool.pageN());

    static_cast<void>(pool.create(0));
    ASSERT_EQ(1u, pool.pageN());
}

TEST(Pool, iteratorAssignability)
{
    static_assert(std::is_assignable_v<qc::Pool<s32>::iterator, qc::Pool<s32>::iterator>);
    static_assert(std::is_assignable_v<qc::Pool<s32>::const_iterator, qc::Pool<s32>::iterator>);
    static_assert(!std::is_assignable_v<qc::Pool<s32>::iterator, qc::Pool<s32>::const_iterator>);
    static_assert(std::is_assignable_v<qc::Pool<s32>::const_iterator, qc::Pool<s32>::const_iterator>);
}
