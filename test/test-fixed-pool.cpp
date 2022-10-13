#include <qc-core/fixed-pool.hpp>

#include <gtest/gtest.h>

using namespace qc::types;

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

TEST(FixedPool, iteratorAssignability)
{
    static_assert(std::is_assignable_v<qc::FixedPool<int>::iterator, qc::FixedPool<int>::iterator>);
    static_assert(std::is_assignable_v<qc::FixedPool<int>::const_iterator, qc::FixedPool<int>::iterator>);
    static_assert(!std::is_assignable_v<qc::FixedPool<int>::iterator, qc::FixedPool<int>::const_iterator>);
    static_assert(std::is_assignable_v<qc::FixedPool<int>::const_iterator, qc::FixedPool<int>::const_iterator>);
}
