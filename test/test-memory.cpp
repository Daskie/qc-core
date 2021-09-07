#include <qc-core/memory.hpp>

#include <gtest/gtest.h>

using namespace qc::types;
using qc::memory::_PoolFriend;

struct qc::memory::_PoolFriend
{
    static size_t * getHead(qc::memory::Pool & pool)
    {
        return pool._head;
    }
};

TEST(memory, poolCapacity)
{
    ASSERT_THROW(qc::memory::Pool{2u * sizeof(size_t) - 1u}, std::exception);
    ASSERT_EQ(2u * sizeof(size_t), qc::memory::Pool{2u * sizeof(size_t)}.capacity());
    ASSERT_EQ(3u * sizeof(size_t), qc::memory::Pool{2u * sizeof(size_t) + 1u}.capacity());
    ASSERT_EQ(3u * sizeof(size_t), qc::memory::Pool{3u * sizeof(size_t)}.capacity());
    ASSERT_EQ(4u * sizeof(size_t), qc::memory::Pool{3u * sizeof(size_t) + 1u}.capacity());
    ASSERT_EQ(4u * sizeof(size_t), qc::memory::Pool{4u * sizeof(size_t)}.capacity());
}

TEST(memory, poolAllocateDeallocate)
{
    qc::memory::Pool pool{120 * sizeof(size_t)};
    ASSERT_EQ(120u * sizeof(size_t), pool.capacity());

    size_t * const data{const_cast<size_t *>(static_cast<const size_t *>(pool.data()))};
    ASSERT_EQ(0, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(120u, data[0]);
    ASSERT_EQ(120u, data[1]);
    ASSERT_EQ(0u, data[120]);
    ASSERT_EQ(0u, data[121]);

    // One full allocation

    ASSERT_EQ(0, pool.allocate<size_t>(120u) - data);
    ASSERT_EQ(120, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(0u, data[120]);
    ASSERT_EQ(0u, data[121]);

    // Shouldn't be able to allocate more

    ASSERT_THROW(pool.allocate<size_t>(1u), std::bad_alloc);
    ASSERT_EQ(120, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(0u, data[120]);
    ASSERT_EQ(0u, data[121]);

    // Full deallocation

    pool.deallocate(data, 120u);
    ASSERT_EQ(0, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(120u, data[0]);
    ASSERT_EQ(120u, data[1]);

    // Allocate into three blocks

    ASSERT_EQ(0, pool.allocate<size_t>(40u) - data);
    ASSERT_EQ(40, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(80u, data[40]);
    ASSERT_EQ(80u, data[41]);

    ASSERT_EQ(40, pool.allocate<size_t>(40u) - data);
    ASSERT_EQ(80, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(40u, data[80]);
    ASSERT_EQ(40u, data[81]);

    ASSERT_EQ(80, pool.allocate<size_t>(40u) - data);
    ASSERT_EQ(120, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(0u, data[120]);
    ASSERT_EQ(0u, data[121]);

    // Should not be able to allocate more

    ASSERT_THROW(pool.allocate<size_t>(1u), std::bad_alloc);
    ASSERT_EQ(120, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(0u, data[120]);
    ASSERT_EQ(0u, data[121]);

    // Deallocate middle block

    pool.deallocate(data + 40, 40u);
    ASSERT_EQ(40, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(40u, data[40]);
    ASSERT_EQ(80u, data[41]);

    // Try to overstuff

    ASSERT_THROW(pool.allocate<size_t>(41u), std::bad_alloc);
    ASSERT_EQ(40, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(40u, data[40]);
    ASSERT_EQ(80u, data[41]);

    // Partial middle allocation

    ASSERT_EQ(40, pool.allocate<size_t>(20u) - data);
    ASSERT_EQ(60, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(20u, data[60]);
    ASSERT_EQ(60u, data[61]);

    // Full middle allocation

    ASSERT_EQ(60, pool.allocate<size_t>(20u) - data);
    ASSERT_EQ(120, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(0u, data[120]);
    ASSERT_EQ(0u, data[121]);

    // Reallocate first block

    pool.deallocate(data, 40u);
    ASSERT_EQ(0, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(40u, data[0]);
    ASSERT_EQ(120u, data[1]);

    ASSERT_EQ(0, pool.allocate<size_t>(40u) - data);
    ASSERT_EQ(120, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(0u, data[120]);
    ASSERT_EQ(0u, data[121]);

    // Deallocate first block

    pool.deallocate(data, 40u);
    ASSERT_EQ(0, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(40u, data[0]);
    ASSERT_EQ(120u, data[1]);

    // Try to allocate such that there is a gap of one

    ASSERT_THROW(pool.allocate<size_t>(39u), std::bad_alloc);
    ASSERT_EQ(0, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(40u, data[0]);
    ASSERT_EQ(120u, data[1]);

    // Just enough room for meta

    ASSERT_EQ(0, pool.allocate<size_t>(38u) - data);
    ASSERT_EQ(38, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(2u, data[38]);
    ASSERT_EQ(82u, data[39]);

    // Allocate minimum size block

    ASSERT_EQ(38, pool.allocate<size_t>(2u) - data);
    ASSERT_EQ(120, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(0u, data[120]);
    ASSERT_EQ(0u, data[121]);

    // Deallocate small block at beginning

    pool.deallocate(data, 10u);
    ASSERT_EQ(0, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(10u, data[0]);
    ASSERT_EQ(120u, data[1]);

    // Deallocate larger block at end

    pool.deallocate(data + 80, 40u);
    ASSERT_EQ(0, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(10u, data[0]);
    ASSERT_EQ(80u, data[1]);
    ASSERT_EQ(40u, data[80]);
    ASSERT_EQ(40u, data[81]);

    // Allocate larger block

    ASSERT_EQ(80, pool.allocate<size_t>(40u) - data);
    ASSERT_EQ(0, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(10u, data[0]);
    ASSERT_EQ(120u, data[1]);

    // Deallocate small blocks in middle and end

    pool.deallocate(data + 20, 20u);
    ASSERT_EQ(0, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(10u, data[0]);
    ASSERT_EQ(20u, data[1]);
    ASSERT_EQ(20u, data[20]);
    ASSERT_EQ(100u, data[21]);

    pool.deallocate(data + 100, 20u);
    ASSERT_EQ(0, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(10u, data[0]);
    ASSERT_EQ(20u, data[1]);
    ASSERT_EQ(20u, data[20]);
    ASSERT_EQ(80u, data[21]);
    ASSERT_EQ(20u, data[100]);
    ASSERT_EQ(20u, data[101]);

    // Deallocate a block after a free block

    pool.deallocate(data + 40, 20u);
    ASSERT_EQ(0, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(10u, data[0]);
    ASSERT_EQ(20u, data[1]);
    ASSERT_EQ(40u, data[20]);
    ASSERT_EQ(80u, data[21]);

    // Deallocate a block before a free block

    pool.deallocate(data + 80, 20u);
    ASSERT_EQ(0, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(10u, data[0]);
    ASSERT_EQ(20u, data[1]);
    ASSERT_EQ(40u, data[20]);
    ASSERT_EQ(60u, data[21]);
    ASSERT_EQ(40u, data[80]);
    ASSERT_EQ(40u, data[81]);

    // Deallocate a block between two free blocks

    pool.deallocate(data + 60, 20u);
    ASSERT_EQ(0, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(10u, data[0]);
    ASSERT_EQ(20u, data[1]);
    ASSERT_EQ(100u, data[20]);
    ASSERT_EQ(100u, data[21]);

    // Deallocate remaining

    pool.deallocate(data + 10, 10u);
    ASSERT_EQ(0, _PoolFriend::getHead(pool) - data);
    ASSERT_EQ(120u, data[0]);
    ASSERT_EQ(120u, data[1]);
}
