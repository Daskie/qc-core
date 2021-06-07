#include <qc-core/memory.hpp>

#include <gtest/gtest.h>

using namespace qc::types;

struct QcMemoryPoolFriend {

    static u64 * getHead(qc::memory::Pool & pool) {
        return pool._head;
    }

};

TEST(memory, poolCapacity) {
    ASSERT_THROW(qc::memory::Pool{15u}, std::exception);
    ASSERT_EQ(16u, qc::memory::Pool{16u}.capacity());
    ASSERT_EQ(24u, qc::memory::Pool{17u}.capacity());
    ASSERT_EQ(24u, qc::memory::Pool{24u}.capacity());
    ASSERT_EQ(32u, qc::memory::Pool{25u}.capacity());
    ASSERT_EQ(32u, qc::memory::Pool{32u}.capacity());
}

TEST(memory, poolAllocateDeallocate) {
    qc::memory::Pool pool{120 * 8u};
    ASSERT_EQ(120u * 8u, pool.capacity());

    u64 * const data{const_cast<u64 *>(static_cast<const u64 *>(pool.data()))};
    ASSERT_EQ(0, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(120u, data[0]);
    ASSERT_EQ(120u, data[1]);
    ASSERT_EQ(0u, data[120]);
    ASSERT_EQ(0u, data[121]);

    // One full allocation

    ASSERT_EQ(0, pool.allocate<u64>(120u) - data);
    ASSERT_EQ(120, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(0u, data[120]);
    ASSERT_EQ(0u, data[121]);

    // Shouldn't be able to allocate more

    ASSERT_THROW(pool.allocate<u64>(1u), std::bad_alloc);
    ASSERT_EQ(120, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(0u, data[120]);
    ASSERT_EQ(0u, data[121]);

    // Full deallocation

    pool.deallocate(data, 120u);
    ASSERT_EQ(0, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(120u, data[0]);
    ASSERT_EQ(120u, data[1]);

    // Allocate into three blocks

    ASSERT_EQ(0, pool.allocate<u64>(40u) - data);
    ASSERT_EQ(40, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(80u, data[40]);
    ASSERT_EQ(80u, data[41]);

    ASSERT_EQ(40, pool.allocate<u64>(40u) - data);
    ASSERT_EQ(80, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(40u, data[80]);
    ASSERT_EQ(40u, data[81]);

    ASSERT_EQ(80, pool.allocate<u64>(40u) - data);
    ASSERT_EQ(120, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(0u, data[120]);
    ASSERT_EQ(0u, data[121]);

    // Should not be able to allocate more

    ASSERT_THROW(pool.allocate<u64>(1u), std::bad_alloc);
    ASSERT_EQ(120, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(0u, data[120]);
    ASSERT_EQ(0u, data[121]);

    // Deallocate middle block

    pool.deallocate(data + 40, 40u);
    ASSERT_EQ(40, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(40u, data[40]);
    ASSERT_EQ(80u, data[41]);

    // Try to overstuff

    ASSERT_THROW(pool.allocate<u64>(41u), std::bad_alloc);
    ASSERT_EQ(40, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(40u, data[40]);
    ASSERT_EQ(80u, data[41]);

    // Partial middle allocation

    ASSERT_EQ(40, pool.allocate<u64>(20u) - data);
    ASSERT_EQ(60, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(20u, data[60]);
    ASSERT_EQ(60u, data[61]);

    // Full middle allocation

    ASSERT_EQ(60, pool.allocate<u64>(20u) - data);
    ASSERT_EQ(120, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(0u, data[120]);
    ASSERT_EQ(0u, data[121]);

    // Reallocate first block

    pool.deallocate(data, 40u);
    ASSERT_EQ(0, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(40u, data[0]);
    ASSERT_EQ(120u, data[1]);

    ASSERT_EQ(0, pool.allocate<u64>(40u) - data);
    ASSERT_EQ(120, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(0u, data[120]);
    ASSERT_EQ(0u, data[121]);

    // Deallocate first block

    pool.deallocate(data, 40u);
    ASSERT_EQ(0, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(40u, data[0]);
    ASSERT_EQ(120u, data[1]);

    // Try to allocate such that there is a gap of one

    ASSERT_THROW(pool.allocate<u64>(39u), std::bad_alloc);
    ASSERT_EQ(0, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(40u, data[0]);
    ASSERT_EQ(120u, data[1]);

    // Just enough room for meta

    ASSERT_EQ(0, pool.allocate<u64>(38u) - data);
    ASSERT_EQ(38, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(2u, data[38]);
    ASSERT_EQ(82u, data[39]);

    // Allocate minimum size block

    ASSERT_EQ(38, pool.allocate<u64>(2u) - data);
    ASSERT_EQ(120, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(0u, data[120]);
    ASSERT_EQ(0u, data[121]);

    // Deallocate small block at beginning

    pool.deallocate(data, 10u);
    ASSERT_EQ(0, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(10u, data[0]);
    ASSERT_EQ(120u, data[1]);

    // Deallocate larger block at end

    pool.deallocate(data + 80, 40u);
    ASSERT_EQ(0, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(10u, data[0]);
    ASSERT_EQ(80u, data[1]);
    ASSERT_EQ(40u, data[80]);
    ASSERT_EQ(40u, data[81]);

    // Allocate larger block

    ASSERT_EQ(80, pool.allocate<u64>(40u) - data);
    ASSERT_EQ(0, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(10u, data[0]);
    ASSERT_EQ(120u, data[1]);

    // Deallocate small blocks in middle and end

    pool.deallocate(data + 20, 20u);
    ASSERT_EQ(0, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(10u, data[0]);
    ASSERT_EQ(20u, data[1]);
    ASSERT_EQ(20u, data[20]);
    ASSERT_EQ(100u, data[21]);

    pool.deallocate(data + 100, 20u);
    ASSERT_EQ(0, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(10u, data[0]);
    ASSERT_EQ(20u, data[1]);
    ASSERT_EQ(20u, data[20]);
    ASSERT_EQ(80u, data[21]);
    ASSERT_EQ(20u, data[100]);
    ASSERT_EQ(20u, data[101]);

    // Deallocate a block after a free block

    pool.deallocate(data + 40, 20u);
    ASSERT_EQ(0, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(10u, data[0]);
    ASSERT_EQ(20u, data[1]);
    ASSERT_EQ(40u, data[20]);
    ASSERT_EQ(80u, data[21]);

    // Deallocate a block before a free block

    pool.deallocate(data + 80, 20u);
    ASSERT_EQ(0, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(10u, data[0]);
    ASSERT_EQ(20u, data[1]);
    ASSERT_EQ(40u, data[20]);
    ASSERT_EQ(60u, data[21]);
    ASSERT_EQ(40u, data[80]);
    ASSERT_EQ(40u, data[81]);

    // Deallocate a block between two free blocks

    pool.deallocate(data + 60, 20u);
    ASSERT_EQ(0, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(10u, data[0]);
    ASSERT_EQ(20u, data[1]);
    ASSERT_EQ(100u, data[20]);
    ASSERT_EQ(100u, data[21]);

    // Deallocate remaining

    pool.deallocate(data + 10, 10u);
    ASSERT_EQ(0, QcMemoryPoolFriend::getHead(pool) - data);
    ASSERT_EQ(120u, data[0]);
    ASSERT_EQ(120u, data[1]);
}
