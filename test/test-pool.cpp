#include <qc-core/pool.hpp>

#include <gtest/gtest.h>

using namespace qc::types;
using namespace qc::primitives;

template <typename T> using Unq = qc::Pool<T>::Unq;
template <typename T> using Shr = qc::Pool<T>::Shr;

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
    Unq<BigInt> e0{pool.unq(0)};
    ASSERT_EQ(1u, pool.pageN());
    ASSERT_EQ(1u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|_|_|_]
    Unq<BigInt> e1{pool.unq(1)};
    ASSERT_TRUE(&*e1 > &*e0);
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(2u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|_|_]
    Unq<BigInt> e2{pool.unq(2)};
    ASSERT_TRUE(&*e2 > &*e1);
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(3u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|3|_]
    Unq<BigInt> e3{pool.unq(3)};
    ASSERT_TRUE(&*e3 > &*e2);
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(4u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(3, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|3|4]
    Unq<BigInt> e4{pool.unq(4)};
    ASSERT_TRUE(&*e4 > &*e3);
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
    ASSERT_DEATH(static_cast<void>(pool.unq(5)), "");

    // [0|1|2|3|_]
    e4.reset();
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(4u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(3, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|_|_]
    e3.reset();
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(3u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|5|6]
    Unq<BigInt> e5{pool.unq(5)};
    Unq<BigInt> e6{pool.unq(6)};
    ASSERT_TRUE(&*e5 > &*e2);
    ASSERT_TRUE(&*e6 > &*e5);
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
    e0.reset();
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(4u, pool.size());
    it = pool.begin();
    ASSERT_EQ(1, it->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [_|_|2|5|6]
    e1.reset();
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(3u, pool.size());
    it = pool.begin();
    ASSERT_EQ(2, it->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [_|7|2|5|6]
    Unq<BigInt> e7{pool.unq(7)};
    ASSERT_TRUE(&*e7 < &*e2);
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(4u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [_|7|2|_|6]
    e5.reset();
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(3u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [_|7|_|_|6]
    e2.reset();
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(2u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [10|7|8|9|6]
    Unq<BigInt> e8{pool.unq(8)};
    Unq<BigInt> e9{pool.unq(9)};
    Unq<BigInt> e10{pool.unq(10)};
    ASSERT_TRUE(&*e8 > &*e7);
    ASSERT_TRUE(&*e9 > &*e8 && &*e9 < &*e6);
    ASSERT_TRUE(&*e10 < &*e7);
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(5u, pool.size());
    it = pool.begin();
    ASSERT_EQ(10, it->x);
    ASSERT_EQ(7, (++it)->x);
    ASSERT_EQ(8, (++it)->x);
    ASSERT_EQ(9, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [_|7|_|_|6]
    e8.reset();
    e9.reset();
    e10.reset();
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(2u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [_|_|_|_|6]
    e7.reset();
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(1u, pool.size());
    it = pool.begin();
    ASSERT_EQ(6, it->x);
    ASSERT_EQ(pool.end(), ++it);

    // [_|11|_|_|6]
    Unq<BigInt> e11{pool.unq(11)};
    ASSERT_TRUE(&*e11 < &*e6);
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(2u, pool.size());
    it = pool.begin();
    ASSERT_EQ(11, it->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [_|11|_|_|_]
    e6.reset();
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(1u, pool.size());
    it = pool.begin();
    ASSERT_EQ(11, it->x);
    ASSERT_EQ(pool.end(), ++it);

    // [_|_|_|_|_]
    e11.reset();
    ASSERT_EQ(3u, pool.pageN());
    ASSERT_EQ(0u, pool.size());
    ASSERT_EQ(pool.end(), pool.begin());
}

TEST(Pool, single)
{
    qc::Pool<s32> pool{1u};
    const u64 maxCapacity{255u};
    ASSERT_EQ(1u, pool.maxPageN());
    ASSERT_EQ(maxCapacity, pool.capacity());
    ASSERT_EQ(0u, pool.pageN());
    ASSERT_EQ(0u, pool.size());
    ASSERT_EQ(pool.end(), pool.begin());

    Unq<s32> e0{pool.unq(0)};
    ASSERT_EQ(maxCapacity, pool.capacity());
    ASSERT_EQ(1u, pool.pageN());
    ASSERT_EQ(1u, pool.size());
    auto it{pool.begin()};
    ASSERT_EQ(0, *it);
    ASSERT_EQ(pool.end(), ++it);

    e0.reset();
    ASSERT_EQ(maxCapacity, pool.capacity());
    ASSERT_EQ(1u, pool.pageN());
    ASSERT_EQ(0u, pool.size());
    ASSERT_EQ(pool.end(), pool.begin());
}

TEST(Pool, growthRate)
{
    struct PageVal { u8 data[qc::pageSize]; };

    {
        qc::Pool<PageVal> pool{25u};
        ASSERT_EQ(26u, pool.maxPageN());
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(0u, pool.pageN());

        Unq<PageVal> p1{pool.unq()};
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(2u, pool.pageN());

        Unq<PageVal> p2{pool.unq()};
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(4u, pool.pageN());

        Unq<PageVal> p3{pool.unq()};
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(4u, pool.pageN());

        Unq<PageVal> p4{pool.unq()};
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(8u, pool.pageN());

        Unq<PageVal> p5{pool.unq()};
        Unq<PageVal> p6{pool.unq()};
        Unq<PageVal> p7{pool.unq()};
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(8u, pool.pageN());

        Unq<PageVal> p8{pool.unq()};
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(16u, pool.pageN());

        Unq<PageVal> p9{pool.unq()};
        Unq<PageVal> p10{pool.unq()};
        Unq<PageVal> p11{pool.unq()};
        Unq<PageVal> p12{pool.unq()};
        Unq<PageVal> p13{pool.unq()};
        Unq<PageVal> p14{pool.unq()};
        Unq<PageVal> p15{pool.unq()};
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(16u, pool.pageN());

        Unq<PageVal> p16{pool.unq()};
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(26u, pool.pageN());
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

    Unq<HugeVal> v{pool.unq()};
    ASSERT_EQ(1u, pool.capacity());
    ASSERT_EQ(2u, pool.pageN());

    ++v->data[0];
    ++v->data[sizeof(HugeVal) - 1u];

    v.reset();
    ASSERT_EQ(1u, pool.capacity());
    ASSERT_EQ(2u, pool.pageN());
}

/*TEST(Pool, shrinkToFit)
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
}*/

TEST(Pool, iteratorAssignability)
{
    static_assert(std::is_assignable_v<qc::Pool<s32>::iterator, qc::Pool<s32>::iterator>);
    static_assert(std::is_assignable_v<qc::Pool<s32>::const_iterator, qc::Pool<s32>::iterator>);
    static_assert(!std::is_assignable_v<qc::Pool<s32>::iterator, qc::Pool<s32>::const_iterator>);
    static_assert(std::is_assignable_v<qc::Pool<s32>::const_iterator, qc::Pool<s32>::const_iterator>);
}

TEST(Pool, moveability)
{
    qc::Pool<u32> p2{10};
    Unq<u32> v;
    {
        qc::Pool<u32> p1{10};
        v = p1.unq(7u);
        ASSERT_FALSE(p1.empty());
        ASSERT_EQ(*v, 7u);
        p2 = std::move(p1);
        ASSERT_TRUE(p1.empty());
        ASSERT_FALSE(p2.empty());
        ASSERT_EQ(*v, 7u);
    }
    ASSERT_EQ(*v, 7u);
}
