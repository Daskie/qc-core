#include <qc-core/pool.hpp>

#include <gtest/gtest.h>

#include <qc-core/lot.hpp>
#include <qc-core/random.hpp>

namespace
{
    using namespace qc::types;
    using namespace qc::primitives;

    template <typename T> using Unq = qc::Pool<T>::Unq;
    template <typename T> using CUnq = qc::Pool<T>::CUnq;
    template <typename T> using Shr = qc::Pool<T>::Shr;
    template <typename T> using CShr = qc::Pool<T>::CShr;

    constexpr u64 _metaSize{8u};

    struct _Bubble
    {
        s64 i;
        s64 n;
        u64 ordinal;

        bool operator==(const _Bubble &) const = default;
        friend std::ostream & operator<<(std::ostream & os, const _Bubble & b) { return os << "{" << b.i << ", " << b.n << ", " << b.ordinal << "}"; }
    };
}

namespace qc
{
    struct PoolFriend
    {
        template <typename T>
        static std::vector<_Bubble> bubbles(Pool<T> & pool, const s64 pretendPoolCapacity)
        {
            std::vector<_Bubble> bubbles{};

            for (typename Pool<T>::_Chunk * bubble{pool._firstBubble}; bubble; bubble = bubble->bubble.nextOffset ? bubble->nextBubble() : nullptr)
            {
                const s64 startI{bubble - pool._chunksStart};
                if (startI >= pretendPoolCapacity)
                {
                    break;
                }
                const s64 endI{startI + bubble->bubble.headTailOffset + 1};
                bubbles.emplace_back(startI, min(endI, pretendPoolCapacity) - startI, bubble->bubble.ordinal - (u64(pretendPoolCapacity) < pool.capacity()));
            }

            return bubbles;
        }
    };
}

using qc::PoolFriend;

TEST(Pool, standard)
{
    // Assumes page size is 64k
    // Each BigInt+meta is 28,000 bytes, so 7 chunks would fit into three pages
    ASSERT_EQ(64u * 1024u, qc::pageSize);
    struct BigInt
    {
        s32 x;
        u8 padding[28'000u - sizeof(s32) - _metaSize];

        BigInt() = default;
        BigInt(s32 x) : x{x} {}
    };

    // [_|_|_|_|_]
    qc::Pool<BigInt> pool{5u};
    ASSERT_EQ(3u, pool.reservedPageN());
    ASSERT_EQ(5u, pool.capacity());
    ASSERT_EQ(0u, pool.committedPageN());
    ASSERT_EQ(0u, pool.size());
    auto it{pool.begin()};
    ASSERT_EQ(pool.end(), it);

    // [0|_|_|_|_]
    Unq<BigInt> e0{pool.unq(0)};
    ASSERT_EQ(3u, pool.committedPageN());
    ASSERT_EQ(1u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|_|_|_]
    Unq<BigInt> e1{pool.unq(1)};
    ASSERT_TRUE(&*e1 > &*e0);
    ASSERT_EQ(3u, pool.committedPageN());
    ASSERT_EQ(2u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|_|_]
    Unq<BigInt> e2{pool.unq(2)};
    ASSERT_TRUE(&*e2 > &*e1);
    ASSERT_EQ(3u, pool.committedPageN());
    ASSERT_EQ(3u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|3|_]
    Unq<BigInt> e3{pool.unq(3)};
    ASSERT_TRUE(&*e3 > &*e2);
    ASSERT_EQ(3u, pool.committedPageN());
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
    ASSERT_EQ(3u, pool.committedPageN());
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
    ASSERT_EQ(3u, pool.committedPageN());
    ASSERT_EQ(4u, pool.size());
    it = pool.begin();
    ASSERT_EQ(0, it->x);
    ASSERT_EQ(1, (++it)->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(3, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [0|1|2|_|_]
    e3.reset();
    ASSERT_EQ(3u, pool.committedPageN());
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
    ASSERT_EQ(3u, pool.committedPageN());
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
    ASSERT_EQ(3u, pool.committedPageN());
    ASSERT_EQ(4u, pool.size());
    it = pool.begin();
    ASSERT_EQ(1, it->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [_|_|2|5|6]
    e1.reset();
    ASSERT_EQ(3u, pool.committedPageN());
    ASSERT_EQ(3u, pool.size());
    it = pool.begin();
    ASSERT_EQ(2, it->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [7|_|2|5|6]
    Unq<BigInt> e7{pool.unq(7)};
    ASSERT_TRUE(&*e7 < &*e2);
    ASSERT_EQ(3u, pool.committedPageN());
    ASSERT_EQ(4u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(5, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [7|_|2|_|6]
    e5.reset();
    ASSERT_EQ(3u, pool.committedPageN());
    ASSERT_EQ(3u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(2, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [7|_|_|_|6]
    e2.reset();
    ASSERT_EQ(3u, pool.committedPageN());
    ASSERT_EQ(2u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [7|8|9|10|6]
    Unq<BigInt> e8{pool.unq(8)};
    Unq<BigInt> e9{pool.unq(9)};
    Unq<BigInt> e10{pool.unq(10)};
    ASSERT_TRUE(&*e8 < &*e9);
    ASSERT_TRUE(&*e9 < &*e10);
    ASSERT_TRUE(&*e10 < &*e6);
    ASSERT_EQ(3u, pool.committedPageN());
    ASSERT_EQ(5u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(8, (++it)->x);
    ASSERT_EQ(9, (++it)->x);
    ASSERT_EQ(10, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [7|_|9|_|6]
    e10.reset();
    e8.reset();
    ASSERT_EQ(3u, pool.committedPageN());
    ASSERT_EQ(3u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(9, (++it)->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [7|_|_|_|6]
    e8.reset();
    e9.reset();
    e10.reset();
    ASSERT_EQ(3u, pool.committedPageN());
    ASSERT_EQ(2u, pool.size());
    it = pool.begin();
    ASSERT_EQ(7, it->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [_|_|_|_|6]
    e7.reset();
    ASSERT_EQ(3u, pool.committedPageN());
    ASSERT_EQ(1u, pool.size());
    it = pool.begin();
    ASSERT_EQ(6, it->x);
    ASSERT_EQ(pool.end(), ++it);

    // [11|_|_|_|6]
    Unq<BigInt> e11{pool.unq(11)};
    ASSERT_TRUE(&*e11 < &*e6);
    ASSERT_EQ(3u, pool.committedPageN());
    ASSERT_EQ(2u, pool.size());
    it = pool.begin();
    ASSERT_EQ(11, it->x);
    ASSERT_EQ(6, (++it)->x);
    ASSERT_EQ(pool.end(), ++it);

    // [11|_|_|_|_]
    e6.reset();
    ASSERT_EQ(3u, pool.committedPageN());
    ASSERT_EQ(1u, pool.size());
    it = pool.begin();
    ASSERT_EQ(11, it->x);
    ASSERT_EQ(pool.end(), ++it);

    // [_|_|_|_|_]
    e11.reset();
    ASSERT_EQ(3u, pool.committedPageN());
    ASSERT_EQ(0u, pool.size());
    ASSERT_EQ(pool.end(), pool.begin());
}

TEST(Pool, bubbles)
{
    // [00|01|02|03|04|05|06|07|08|09|10|11|12]
    qc::Pool<s32> pool{100u};
    Unq<s32> e0{pool.unq(0)};
    Unq<s32> e1{pool.unq(1)};
    Unq<s32> e2{pool.unq(2)};
    Unq<s32> e3{pool.unq(3)};
    Unq<s32> e4{pool.unq(4)};
    Unq<s32> e5{pool.unq(5)};
    Unq<s32> e6{pool.unq(6)};
    Unq<s32> e7{pool.unq(7)};
    Unq<s32> e8{pool.unq(8)};
    Unq<s32> e9{pool.unq(9)};
    Unq<s32> e10{pool.unq(10)};
    Unq<s32> e11{pool.unq(11)};
    Unq<s32> e12{pool.unq(12)};
    ASSERT_EQ(PoolFriend::bubbles(pool, 13), std::vector<_Bubble>{});

    // New bubble
    // [00|01|02|03|04|05|__|07|08|09|10|11|12]
    e6.reset();
    ASSERT_EQ(PoolFriend::bubbles(pool, 13), (std::vector<_Bubble>{{6, 1, 0}}));

    // Append to bubble
    // [00|01|02|03|04|05|__|__|08|09|10|11|12]
    e7.reset();
    ASSERT_EQ(PoolFriend::bubbles(pool, 13), (std::vector<_Bubble>{{6, 2, 0}}));
    // [00|01|02|03|04|05|__|__|__|09|10|11|12]
    e8.reset();
    ASSERT_EQ(PoolFriend::bubbles(pool, 13), (std::vector<_Bubble>{{6, 3, 0}}));

    // Prepend to bubble
    // [00|01|02|03|04|05|06|__|__|09|10|11|12]
    e6 = pool.unq(6);
    // [00|01|02|03|04|05|06|07|__|09|10|11|12]
    e7 = pool.unq(7);
    ASSERT_EQ(PoolFriend::bubbles(pool, 13), (std::vector<_Bubble>{{8, 1, 0}}));
    // [00|01|02|03|04|05|06|__|__|09|10|11|12]
    e7.reset();
    ASSERT_EQ(PoolFriend::bubbles(pool, 13), (std::vector<_Bubble>{{7, 2, 0}}));
    // [00|01|02|03|04|05|__|__|__|09|10|11|12]
    e6.reset();
    ASSERT_EQ(PoolFriend::bubbles(pool, 13), (std::vector<_Bubble>{{6, 3, 0}}));

    // Join bubbles in order with nothing between or adjacent
    // [00|01|02|03|__|05|__|__|__|09|10|11|12]
    e4.reset();
    ASSERT_EQ(PoolFriend::bubbles(pool, 13), (std::vector<_Bubble>{{4, 1, 1}, {6, 3, 0}}));
    // [00|01|02|03|__|__|__|__|__|09|10|11|12]
    e5.reset();
    ASSERT_EQ(PoolFriend::bubbles(pool, 13), (std::vector<_Bubble>{{4, 5, 0}}));

    // Join bubbles out of order with nothing between or adjacent
    // [00|01|02|03|__|__|__|__|__|09|__|11|12]
    e10.reset();
    ASSERT_EQ(PoolFriend::bubbles(pool, 13), (std::vector<_Bubble>{{10, 1, 1}, {4, 5, 0}}));
    // [00|01|02|03|__|__|__|__|__|__|__|11|12]
    e9.reset();
    ASSERT_EQ(PoolFriend::bubbles(pool, 13), (std::vector<_Bubble>{{4, 7, 0}}));

    // Join bubbles in order with things adjacent and between
    // [00|01|02|03|04|05|06|07|08|09|10|11|12]
    e4 = pool.unq(4);
    e5 = pool.unq(5);
    e6 = pool.unq(6);
    e7 = pool.unq(7);
    e8 = pool.unq(8);
    e9 = pool.unq(9);
    e10 = pool.unq(10);
    // [00|01|02|03|04|05|06|07|08|09|10|__|12]
    e11.reset();
    // [00|01|02|03|04|__|06|07|08|09|10|__|12]
    e5.reset();
    // [00|01|02|03|04|__|06|07|08|__|10|__|12]
    e9.reset();
    // [00|01|02|03|04|__|06|__|08|__|10|__|12]
    e7.reset();
    // [00|01|02|__|04|__|06|__|08|__|10|__|12]
    e3.reset();
    // [00|__|02|__|04|__|06|__|08|__|10|__|12]
    e1.reset();
    ASSERT_EQ(PoolFriend::bubbles(pool, 13), (std::vector<_Bubble>{{1, 1, 5}, {3, 1, 4}, {7, 1, 3}, {9, 1, 2}, {5, 1, 1}, {11, 1, 0}}));
    // [00|__|02|__|__|__|06|__|08|__|10|__|12]
    e4.reset();
    ASSERT_EQ(PoolFriend::bubbles(pool, 13), (std::vector<_Bubble>{{1, 1, 5}, {7, 1, 3}, {9, 1, 2}, {3, 3, 1}, {11, 1, 0}}));

    // Join bubbles out of order with things adjacent and between
    // [00|01|02|03|04|05|06|07|08|09|10|11|12]
    e1 = pool.unq(1);
    e7 = pool.unq(7);
    e9 = pool.unq(9);
    e3 = pool.unq(3);
    e4 = pool.unq(4);
    e5 = pool.unq(5);
    e11 = pool.unq(11);
    // [00|__|02|03|04|05|06|07|08|09|10|11|12]
    e1.reset();
    // [00|__|02|03|04|05|06|__|08|09|10|11|12]
    e7.reset();
    // [00|__|02|__|04|05|06|__|08|09|10|11|12]
    e3.reset();
    // [00|__|02|__|04|__|06|__|08|09|10|11|12]
    e5.reset();
    // [00|__|02|__|04|__|06|__|08|__|10|11|12]
    e9.reset();
    // [00|__|02|__|04|__|06|__|08|__|10|__|12]
    e11.reset();
    ASSERT_EQ(PoolFriend::bubbles(pool, 13), (std::vector<_Bubble>{{11, 1, 5}, {9, 1, 4}, {5, 1, 3}, {3, 1, 2}, {7, 1, 1}, {1, 1, 0}}));
    // [00|__|02|__|04|__|06|__|__|__|10|__|12]
    e8.reset();
    ASSERT_EQ(PoolFriend::bubbles(pool, 13), (std::vector<_Bubble>{{11, 1, 5}, {5, 1, 3}, {3, 1, 2}, {7, 3, 1}, {1, 1, 0}}));
}

TEST(Pool, single)
{
    qc::Pool<s32> pool{1u};
    const u64 maxCapacity{2728u};
    ASSERT_EQ(1u, pool.reservedPageN());
    ASSERT_EQ(maxCapacity, pool.capacity());
    ASSERT_EQ(0u, pool.committedPageN());
    ASSERT_EQ(0u, pool.size());
    ASSERT_EQ(pool.end(), pool.begin());

    Unq<s32> e0{pool.unq(0)};
    ASSERT_EQ(maxCapacity, pool.capacity());
    ASSERT_EQ(1u, pool.committedPageN());
    ASSERT_EQ(1u, pool.size());
    auto it{pool.begin()};
    ASSERT_EQ(0, *it);
    ASSERT_EQ(pool.end(), ++it);

    e0.reset();
    ASSERT_EQ(maxCapacity, pool.capacity());
    ASSERT_EQ(1u, pool.committedPageN());
    ASSERT_EQ(0u, pool.size());
    ASSERT_EQ(pool.end(), pool.begin());
}

TEST(Pool, growthRate)
{
    struct PageVal { u8 data[qc::pageSize - _metaSize]; };

    {
        qc::Pool<PageVal> pool{25u};
        ASSERT_EQ(27u, pool.reservedPageN());
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(0u, pool.committedPageN());

        Unq<PageVal> p1{pool.unq()};
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(3u, pool.committedPageN());

        Unq<PageVal> p2{pool.unq()};
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(6u, pool.committedPageN());

        Unq<PageVal> p3{pool.unq()};
        Unq<PageVal> p4{pool.unq()};
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(6u, pool.committedPageN());

        Unq<PageVal> p5{pool.unq()};
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(12u, pool.committedPageN());

        Unq<PageVal> p6{pool.unq()};
        Unq<PageVal> p7{pool.unq()};
        Unq<PageVal> p8{pool.unq()};
        Unq<PageVal> p9{pool.unq()};
        Unq<PageVal> p10{pool.unq()};
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(12u, pool.committedPageN());

        Unq<PageVal> p11{pool.unq()};
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(27u, pool.committedPageN());

        Unq<PageVal> p12{pool.unq()};
        Unq<PageVal> p13{pool.unq()};
        Unq<PageVal> p14{pool.unq()};
        Unq<PageVal> p15{pool.unq()};
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(27u, pool.committedPageN());

        Unq<PageVal> p16{pool.unq()};
        ASSERT_EQ(25u, pool.capacity());
        ASSERT_EQ(27u, pool.committedPageN());
    }
}

TEST(Pool, biggerThanPageVal)
{
    ASSERT_EQ(1u << 16, qc::pageSize);
    struct HugeVal { u8 data[66'000u]; };

    qc::Pool<HugeVal> pool{1u};
    ASSERT_EQ(4u, pool.reservedPageN());
    ASSERT_EQ(1u, pool.capacity());
    ASSERT_EQ(0u, pool.committedPageN());

    Unq<HugeVal> v{pool.unq()};
    ASSERT_EQ(1u, pool.capacity());
    ASSERT_EQ(4u, pool.committedPageN());

    ++v->data[0];
    ++v->data[sizeof(HugeVal) - 1u];

    v.reset();
    ASSERT_EQ(1u, pool.capacity());
    ASSERT_EQ(4u, pool.committedPageN());
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
    v.reset();
    ASSERT_TRUE(p2.empty());
}

TEST(Pool, unique)
{
    static thread_local bool destructed{false};

    struct Obj { int v{0}; ~Obj() { destructed = true; } };

    qc::Pool<Obj> pool{100};

    Unq<Obj> o1{pool.unq(1)};
    ASSERT_EQ(1, (*o1).v);
    ASSERT_EQ(1, o1->v);
    ASSERT_TRUE(o1);

    ASSERT_EQ(o1, o1);
    ASSERT_EQ(o1, &*o1);
    ASSERT_EQ(&*o1, o1);

    Unq<Obj> o2{std::move(o1)};
    ASSERT_EQ(1, o2->v);

    ASSERT_NE(o2, o1);
    ASSERT_NE(o2, &*o1);
    ASSERT_NE(&*o2, o1);

    o1 = std::move(o2);
    ASSERT_EQ(1, o1->v);

    destructed = false;
    o1 = {};
    ASSERT_TRUE(destructed);
    ASSERT_FALSE(o1);

    destructed = false;
    {
        Unq<Obj> o3{pool.unq(2)};
        ASSERT_EQ(2, o3->v);
    }
    ASSERT_TRUE(destructed);
}

TEST(Pool, shared)
{
    static thread_local bool destructed{false};

    struct Obj { int v{0}; ~Obj() { destructed = true; } };

    qc::Pool<Obj> arena{100};

    Shr<Obj> o1{arena.shr(1)};
    ASSERT_EQ(1, (*o1).v);
    ASSERT_EQ(1, o1->v);
    ASSERT_TRUE(o1);

    ASSERT_EQ(1, o1->v);

    ASSERT_EQ(o1, o1);
    ASSERT_EQ(o1, &*o1);
    ASSERT_EQ(&*o1, o1);

    Shr<Obj> o2{std::move(o1)};
    ASSERT_EQ(1, o2->v);

    ASSERT_NE(o2, o1);
    ASSERT_NE(o2, &*o1);
    ASSERT_NE(&*o2, o1);

    o1 = std::move(o2);
    ASSERT_EQ(1, o1->v);

    destructed = false;
    o1 = {};
    ASSERT_TRUE(destructed);
    ASSERT_FALSE(o1);

    o1 = arena.shr(2);
    ASSERT_EQ(2, o1->v);

    o2 = o1;
    ASSERT_EQ(2, o2->v);

    ASSERT_EQ(o1, o2);

    destructed = false;
    o1 = {};
    ASSERT_FALSE(destructed);

    destructed = false;
    o2 = {};
    ASSERT_TRUE(destructed);

    o1 = arena.shr(3);
    ASSERT_EQ(3, o1->v);

    {
        Shr<Obj> o3{o1};
        ASSERT_EQ(3, o3->v);
    }

    ASSERT_EQ(3, o1->v);

    {
        Shr<Obj> o3{o1};
        ASSERT_EQ(3, o3->v);

        destructed = false;
        o1 = {};
        ASSERT_FALSE(destructed);
    }
    ASSERT_TRUE(destructed);

    {
        destructed = false;
        Shr<Obj> o4{arena.shr(4)};
        {
            Shr<Obj> o5{arena.shrOf(&*o4)};
            ASSERT_FALSE(destructed);
            ASSERT_EQ(o5->v, 4);
        }
        ASSERT_FALSE(destructed);
        ASSERT_EQ(o4->v, 4);
    }
    ASSERT_TRUE(destructed);

    if constexpr (qc::debug)
    {
        Unq<Obj> o6{arena.unq(6)};
        Shr<Obj> o7{arena.shrOf(&*o6)};
        EXPECT_DEBUG_DEATH(o6.reset(), "");
    }
}

TEST(Pool, uniqueConst)
{
    qc::Pool<s32> pool{100u};

    Unq<s32> v1{pool.unq(1)};
    CUnq<s32> v2{pool.cunq(2)};
    CUnq<s32> v3{std::move(v1)};
    v2 = std::move(v1);
    static_cast<void>(v1 == v2);
    static_assert(std::is_const_v<std::remove_reference_t<decltype(*v2)>>);
}

TEST(Pool, sharedConst)
{
    qc::Pool<s32> pool{100u};

    Shr<s32> v1{pool.shr(1)};
    CShr<s32> v2{pool.cshr(2)};
    CShr<s32> v3{v1};
    CShr<s32> v4{std::move(v1)};
    v2 = v1;
    v2 = std::move(v1);
    static_cast<void>(v1 == v2);
    static_assert(std::is_const_v<std::remove_reference_t<decltype(*v2)>>);
}

TEST(Pool, shrinkToFit)
{
    struct HalfPage { u8 data[qc::pageSize / 2u - 8u]; };

    qc::Pool<HalfPage> pool{6u};
    ASSERT_EQ(pool.capacity(), 6u);
    ASSERT_EQ(pool.reservedPageN(), 4u);
    ASSERT_EQ(pool.committedPageN(), 0u);
    ASSERT_EQ(PoolFriend::bubbles(pool, 6u), (std::vector<_Bubble>{}));

    pool.shrinkToFit();
    ASSERT_EQ(pool.committedPageN(), 0u);
    ASSERT_EQ(PoolFriend::bubbles(pool, 6u), (std::vector<_Bubble>{}));

    Unq<HalfPage> e1{pool.unq()};
    Unq<HalfPage> e2{pool.unq()};
    Unq<HalfPage> e3{pool.unq()};
    Unq<HalfPage> e4{pool.unq()};
    Unq<HalfPage> e5{pool.unq()};
    Unq<HalfPage> e6{pool.unq()};
    ASSERT_EQ(pool.committedPageN(), 4u);
    ASSERT_EQ(PoolFriend::bubbles(pool, 6u), (std::vector<_Bubble>{}));

    pool.shrinkToFit();
    ASSERT_EQ(pool.committedPageN(), 4u);
    ASSERT_EQ(PoolFriend::bubbles(pool, 6u), (std::vector<_Bubble>{}));

    e1.reset();
    e2.reset();
    e3.reset();
    e4.reset();
    e5.reset();
    pool.shrinkToFit();
    ASSERT_EQ(pool.committedPageN(), 4u);
    ASSERT_EQ(PoolFriend::bubbles(pool, 6u), (std::vector<_Bubble>{{0, 5, 0}}));

    e1 = pool.unq();
    e2 = pool.unq();
    e3 = pool.unq();
    e4 = pool.unq();
    e5 = pool.unq();
    e6.reset();
    ASSERT_EQ(pool.committedPageN(), 4u);
    ASSERT_EQ(PoolFriend::bubbles(pool, 6u), (std::vector<_Bubble>{{5, 1, 0}}));

    pool.shrinkToFit();
    ASSERT_EQ(pool.committedPageN(), 4u);
    ASSERT_EQ(PoolFriend::bubbles(pool, 6u), (std::vector<_Bubble>{{5, 1, 0}}));

    e5.reset();
    ASSERT_EQ(pool.committedPageN(), 4u);
    ASSERT_EQ(PoolFriend::bubbles(pool, 6u), (std::vector<_Bubble>{{4, 2, 0}}));

    pool.shrinkToFit();
    ASSERT_EQ(pool.committedPageN(), 3u);
    ASSERT_EQ(PoolFriend::bubbles(pool, 6u), (std::vector<_Bubble>{}));

    e5 = pool.unq();
    ASSERT_EQ(pool.committedPageN(), 4u);
    ASSERT_EQ(PoolFriend::bubbles(pool, 6u), (std::vector<_Bubble>{{5, 1, 0}}));

    e5.reset();
    e4.reset();
    ASSERT_EQ(pool.committedPageN(), 4u);
    ASSERT_EQ(PoolFriend::bubbles(pool, 6u), (std::vector<_Bubble>{{3, 3, 0}}));

    pool.shrinkToFit();
    ASSERT_EQ(pool.committedPageN(), 3u);
    ASSERT_EQ(PoolFriend::bubbles(pool, 6u), (std::vector<_Bubble>{{3, 1, 0}}));

    e4 = pool.unq();
    e5 = pool.unq();
    e5.reset();
    e4.reset();
    e3.reset();
    ASSERT_EQ(pool.committedPageN(), 4u);
    ASSERT_EQ(PoolFriend::bubbles(pool, 6u), (std::vector<_Bubble>{{2, 4, 0}}));

    pool.shrinkToFit();
    ASSERT_EQ(pool.committedPageN(), 2u);
    ASSERT_EQ(PoolFriend::bubbles(pool, 6u), (std::vector<_Bubble>{}));

    e2.reset();
    e1.reset();
    ASSERT_EQ(pool.committedPageN(), 2u);
    ASSERT_EQ(PoolFriend::bubbles(pool, 6u), (std::vector<_Bubble>{{0, 2, 0}}));

    pool.shrinkToFit();
    ASSERT_EQ(pool.committedPageN(), 0u);
    ASSERT_EQ(PoolFriend::bubbles(pool, 6u), (std::vector<_Bubble>{}));

    e1 = pool.unq();
    e2 = pool.unq();
    e3 = pool.unq();
    e4 = pool.unq();
    e5 = pool.unq();
    e6 = pool.unq();
    e3.reset();
    e5.reset();
    e6.reset();
    ASSERT_EQ(pool.committedPageN(), 4u);
    ASSERT_EQ(PoolFriend::bubbles(pool, 6u), (std::vector<_Bubble>{{4, 2, 1}, {2, 1, 0}}));

    pool.shrinkToFit();
    ASSERT_EQ(pool.committedPageN(), 3u);
    ASSERT_EQ(PoolFriend::bubbles(pool, 6u), (std::vector<_Bubble>{{2, 1, 0}}));

    e4.reset();
    e1.reset();
    ASSERT_EQ(pool.committedPageN(), 3u);
    ASSERT_EQ(PoolFriend::bubbles(pool, 6u), (std::vector<_Bubble>{{0, 1, 1}, {2, 2, 0}}));

    pool.shrinkToFit();
    ASSERT_EQ(pool.committedPageN(), 2u);
    ASSERT_EQ(PoolFriend::bubbles(pool, 6u), (std::vector<_Bubble>{{0, 1, 1}}));

    e1 = pool.unq();
    e3 = pool.unq();
    e4 = pool.unq();
    e5 = pool.unq();
    e6 = pool.unq();
    e1.reset();
    e5.reset();
    e6.reset();
    e3.reset();
    ASSERT_EQ(pool.committedPageN(), 4u);
    ASSERT_EQ(PoolFriend::bubbles(pool, 6u), (std::vector<_Bubble>{{2, 1, 2}, {4, 2, 1}, {0, 1, 0}}));

    pool.shrinkToFit();
    ASSERT_EQ(pool.committedPageN(), 3u);
    ASSERT_EQ(PoolFriend::bubbles(pool, 6u), (std::vector<_Bubble>{{2, 1, 2}, {0, 1, 0}}));
}

TEST(Pool, stress)
{
    qc::Random random{};

    qc::Pool<s32> pool{1u};
    const u64 initCapacity{pool.capacity()};
    ASSERT_GT(initCapacity, 100u);

    const u64 growShrinkCycleN{10u};

    qc::Lot<Unq<s32>> vals{};

    for (u64 cycleI{0u}; cycleI < growShrinkCycleN; ++cycleI)
    {
        while (!pool.full())
        {
            const bool grow{vals.empty() || (random.next() & 0b11u)};

            if (grow)
            {
                vals.push(pool.unq(random.next<s32>()));
            }
            else
            {
                vals.erase(vals.begin() + random.next<u64>(vals.size()));
            }

            ASSERT_EQ(pool.size(), vals.size());
        }

        ASSERT_EQ(pool.capacity(), initCapacity);

        while (!pool.empty())
        {
            const bool shrink{pool.full() || (random.next() & 0b11u)};

            if (shrink)
            {
                vals.erase(vals.begin() + random.next<u64>(vals.size()));
            }
            else
            {
                vals.push(pool.unq(random.next<s32>()));
            }

            ASSERT_EQ(pool.size(), vals.size());
        }
    }
}
