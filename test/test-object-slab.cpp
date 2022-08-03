#include <qc-core/object-slab.hpp>

#include <gtest/gtest.h>

using namespace qc::types;

TEST(ObjectSlab, standard)
{
    // [_|_|_|_|_]
    qc::ObjectSlab<int> slab{5u};
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(0u, slab.usedCount());
    auto it{slab.begin()};
    ASSERT_EQ(slab.end(), it);

    // [0|_|_|_|_]
    int & e0{slab.construct(0)};
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(1u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(0, *it);
    ASSERT_EQ(slab.end(), ++it);

    // [0|1|_|_|_]
    int & e1{slab.construct(1)};
    ASSERT_EQ(&e0 + 1, &e1);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(2u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(0, *it);
    ASSERT_EQ(1, *++it);
    ASSERT_EQ(slab.end(), ++it);

    // [0|1|2|_|_]
    int & e2{slab.construct(2)};
    ASSERT_EQ(&e1 + 1, &e2);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(3u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(0, *it);
    ASSERT_EQ(1, *++it);
    ASSERT_EQ(2, *++it);
    ASSERT_EQ(slab.end(), ++it);

    // [0|1|2|3|_]
    int & e3{slab.construct(3)};
    ASSERT_EQ(&e2 + 1, &e3);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(4u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(0, *it);
    ASSERT_EQ(1, *++it);
    ASSERT_EQ(2, *++it);
    ASSERT_EQ(3, *++it);
    ASSERT_EQ(slab.end(), ++it);

    // [0|1|2|3|4]
    int & e4{slab.construct(4)};
    ASSERT_EQ(&e3 + 1, &e4);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(5u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(0, *it);
    ASSERT_EQ(1, *++it);
    ASSERT_EQ(2, *++it);
    ASSERT_EQ(3, *++it);
    ASSERT_EQ(4, *++it);
    ASSERT_EQ(slab.end(), ++it);

    // [0|1|2|3|4]
    #pragma warning(suppress: 4834)
    EXPECT_THROW(slab.construct(5), qc::ObjectSlabError);

    // [0|1|2|3|_]
    slab.destruct(e4);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(4u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(0, *it);
    ASSERT_EQ(1, *++it);
    ASSERT_EQ(2, *++it);
    ASSERT_EQ(3, *++it);
    ASSERT_EQ(slab.end(), ++it);

    // [0|1|2|_|_]
    slab.destruct(e3);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(3u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(0, *it);
    ASSERT_EQ(1, *++it);
    ASSERT_EQ(2, *++it);
    ASSERT_EQ(slab.end(), ++it);

    // [0|1|2|5|6]
    int & e5{slab.construct(5)};
    int & e6{slab.construct(6)};
    ASSERT_EQ(&e2 + 1, &e5);
    ASSERT_EQ(&e5 + 1, &e6);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(5u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(0, *it);
    ASSERT_EQ(1, *++it);
    ASSERT_EQ(2, *++it);
    ASSERT_EQ(5, *++it);
    ASSERT_EQ(6, *++it);
    ASSERT_EQ(slab.end(), ++it);

    // [_|1|2|5|6]
    slab.destruct(e0);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(4u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(1, *it);
    ASSERT_EQ(2, *++it);
    ASSERT_EQ(5, *++it);
    ASSERT_EQ(6, *++it);
    ASSERT_EQ(slab.end(), ++it);

    // [_|_|2|5|6]
    slab.destruct(e1);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(3u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(2, *it);
    ASSERT_EQ(5, *++it);
    ASSERT_EQ(6, *++it);
    ASSERT_EQ(slab.end(), ++it);

    // [7|_|2|5|6]
    int & e7{slab.construct(7)};
    ASSERT_EQ(&e2 - 2, &e7);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(4u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(7, *it);
    ASSERT_EQ(2, *++it);
    ASSERT_EQ(5, *++it);
    ASSERT_EQ(6, *++it);
    ASSERT_EQ(slab.end(), ++it);

    // [7|_|2|_|6]
    slab.destruct(e5);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(3u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(7, *it);
    ASSERT_EQ(2, *++it);
    ASSERT_EQ(6, *++it);
    ASSERT_EQ(slab.end(), ++it);

    // [7|_|_|_|6]
    slab.destruct(e2);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(2u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(7, *it);
    ASSERT_EQ(6, *++it);
    ASSERT_EQ(slab.end(), ++it);

    // [7|8|9|10|6]
    int & e8{slab.construct(8)};
    int & e9{slab.construct(9)};
    int & e10{slab.construct(10)};
    ASSERT_EQ(&e7 + 1, &e8);
    ASSERT_EQ(&e7 + 2, &e9);
    ASSERT_EQ(&e7 + 3, &e10);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(5u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(7, *it);
    ASSERT_EQ(8, *++it);
    ASSERT_EQ(9, *++it);
    ASSERT_EQ(10, *++it);
    ASSERT_EQ(6, *++it);
    ASSERT_EQ(slab.end(), ++it);

    // [7|_|_|_|6]
    slab.destruct(e8);
    slab.destruct(e9);
    slab.destruct(e10);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(2u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(7, *it);
    ASSERT_EQ(6, *++it);
    ASSERT_EQ(slab.end(), ++it);

    // [7|_|_|_|6]
    ASSERT_DEBUG_DEATH(slab.destruct(e8), "");
    ASSERT_DEBUG_DEATH(slab.destruct(e9), "");
    ASSERT_DEBUG_DEATH(slab.destruct(e10), "");

    // [_|_|_|_|6]
    slab.destruct(e7);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(1u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(6, *it);
    ASSERT_EQ(slab.end(), ++it);

    // [11|_|_|_|6]
    int & e11{slab.construct(11)};
    ASSERT_EQ(&e6 - 4, &e11);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(2u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(11, *it);
    ASSERT_EQ(6, *++it);
    ASSERT_EQ(slab.end(), ++it);

    // [11|_|_|_|_]
    slab.destruct(e6);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(1u, slab.usedCount());
    it = slab.begin();
    ASSERT_EQ(11, *it);
    ASSERT_EQ(slab.end(), ++it);

    // [_|_|_|_|_]
    slab.destruct(e11);
    ASSERT_EQ(5u, slab.size());
    ASSERT_EQ(0u, slab.usedCount());
    ASSERT_EQ(slab.end(), slab.begin());

    ASSERT_DEBUG_DEATH(slab.destruct(e11), "");
}

TEST(ObjectSlab, single)
{
    qc::ObjectSlab<int> slab{1u};
    ASSERT_EQ(1u, slab.size());
    ASSERT_EQ(0u, slab.usedCount());
    ASSERT_EQ(slab.end(), slab.begin());

    int & e0{slab.construct(0)};
    ASSERT_EQ(1u, slab.size());
    ASSERT_EQ(1u, slab.usedCount());
    auto it{slab.begin()};
    ASSERT_EQ(0, *it);
    ASSERT_EQ(slab.end(), ++it);

    slab.destruct(e0);
    ASSERT_EQ(1u, slab.size());
    ASSERT_EQ(0u, slab.usedCount());
    ASSERT_EQ(slab.end(), slab.begin());
}
