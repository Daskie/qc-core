#include <qc-core/arena.hpp>

#include <gtest/gtest.h>

using namespace qc::concepts;
using namespace qc::types;

TEST(Arena, setCapacity)
{
    {
        qc::Arena arena{};
        ASSERT_EQ(0u, arena.capacity());

        ASSERT_DEATH(static_cast<void>(arena.create<int>(0)), "");

        arena.setCapacity(1u);
        ASSERT_EQ(qc::pageSize, arena.capacity());

        ASSERT_DEBUG_DEATH(arena.setCapacity(qc::pageSize * 2u), "");
        ASSERT_DEBUG_DEATH(arena.setCapacity(1u), "");
        ASSERT_DEBUG_DEATH(arena.setCapacity(0u), "");
    }

    {
        qc::Arena arena{1u};
        ASSERT_EQ(qc::pageSize, arena.capacity());

        ASSERT_DEBUG_DEATH(arena.setCapacity(qc::pageSize * 2u), "");
        ASSERT_DEBUG_DEATH(arena.setCapacity(1u), "");
        ASSERT_DEBUG_DEATH(arena.setCapacity(0u), "");
    }
}

TEST(Arena, growth)
{
    struct Page { std::byte bytes[qc::pageSize - 8u]; };

    qc::Arena arena{qc::pageSize * 8u};
    ASSERT_EQ(qc::pageSize * 8u, arena.capacity());
    ASSERT_EQ(0u, arena.size());

    Page & p1{arena.create<Page>()};
    ASSERT_EQ(qc::pageSize, arena.size());

    Page & p2{arena.create<Page>()};
    ASSERT_EQ(qc::pageSize * 2u, arena.size());

    Page & p3{arena.create<Page>()};
    ASSERT_EQ(qc::pageSize * 4u, arena.size());

    Page & p4{arena.create<Page>()};
    ASSERT_EQ(qc::pageSize * 4u, arena.size());

    Page & p5{arena.create<Page>()};
    ASSERT_EQ(qc::pageSize * 8u, arena.size());

    Page & p6{arena.create<Page>()};
    ASSERT_EQ(qc::pageSize * 8u, arena.size());

    Page & p7{arena.create<Page>()};
    ASSERT_EQ(qc::pageSize * 8u, arena.size());

    Page & p8{arena.create<Page>()};
    ASSERT_EQ(qc::pageSize * 8u, arena.size());

    arena.destroy(p1);
    arena.destroy(p2);
    arena.destroy(p3);
    arena.destroy(p4);
    arena.destroy(p5);
    arena.destroy(p6);
    arena.destroy(p7);
    arena.destroy(p8);
    ASSERT_EQ(qc::pageSize * 8u, arena.size());
}

TEST(Arena, shrinkToFit)
{
    struct Page { std::byte bytes[qc::pageSize - 8u]; };

    qc::Arena arena{qc::pageSize * 8u};
    ASSERT_EQ(qc::pageSize * 8u, arena.capacity());
    ASSERT_EQ(0u, arena.size());

    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 8u, arena.capacity());
    ASSERT_EQ(0u, arena.size());

    Page & p1{arena.create<Page>()};
    ASSERT_EQ(qc::pageSize, arena.size());

    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize, arena.size());

    Page & p2{arena.create<Page>()};
    ASSERT_EQ(qc::pageSize * 2u, arena.size());

    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 2u, arena.size());

    Page & p3{arena.create<Page>()};
    ASSERT_EQ(qc::pageSize * 4u, arena.size());

    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 4u, arena.size());

    Page & p4{arena.create<Page>()};
    ASSERT_EQ(qc::pageSize * 4u, arena.size());

    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 4u, arena.size());

    Page & p5{arena.create<Page>()};
    ASSERT_EQ(qc::pageSize * 8u, arena.size());

    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 8u, arena.size());

    Page & p6{arena.create<Page>()};
    Page & p7{arena.create<Page>()};
    Page & p8{arena.create<Page>()};
    ASSERT_EQ(qc::pageSize * 8u, arena.size());

    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 8u, arena.size());

    arena.destroy(p8);
    arena.destroy(p7);
    arena.destroy(p6);
    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 8u, arena.size());

    arena.destroy(p4);
    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 8u, arena.size());

    arena.destroy(p5);
    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 4u, arena.size());

    arena.destroy(p3);
    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 2u, arena.size());

    arena.destroy(p2);
    arena.destroy(p1);
    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 0u, arena.size());
}

TEST(Arena, alignment)
{
    qc::Arena arena{100u};

    u64 & v1{arena.create<u64>(u64(1u))};
    ASSERT_EQ(0u, std::bit_cast<u64>(&v1) & 0b111u);
    ASSERT_EQ(1u, v1);

    u32 & v2{arena.create<u32>(u32(2u))};
    ASSERT_EQ(0u, std::bit_cast<u64>(&v2) & 0b111u);
    ASSERT_EQ(2u, v2);

    u16 & v3{arena.create<u16>(u16(3u))};
    ASSERT_EQ(0u, std::bit_cast<u64>(&v3) & 0b111u);
    ASSERT_EQ(3u, v3);

    u8 & v4{arena.create<u8>(u8(4u))};
    ASSERT_EQ(0u, std::bit_cast<u64>(&v4) & 0b111u);
    ASSERT_EQ(4u, v4);

    struct Eleven { std::byte bytes[11u]; };
    Eleven & v5{arena.create<Eleven>()};
    ASSERT_EQ(0u, std::bit_cast<u64>(&v5) & 0b111u);

    arena.destroy(v1);
    arena.destroy(v2);
    arena.destroy(v3);
    arena.destroy(v4);
    arena.destroy(v5);
}

TEST(Arena, largeValue)
{
    struct Large { std::byte bytes[qc::pageSize + qc::pageSize / 2u - 8u]; };

    qc::Arena arena{qc::pageSize * 4u};

    Large & l1{arena.create<Large>()};
    ASSERT_EQ(qc::pageSize * 2u, arena.size());

    Large & l2{arena.create<Large>()};
    ASSERT_EQ(qc::pageSize * 4u, arena.size());

    ASSERT_DEATH(static_cast<void>(arena.create<Large>()), "");

    arena.destroy(l1);

    Large & l3{arena.create<Large>()};
    ASSERT_EQ(qc::pageSize * 4u, arena.size());

    arena.destroy(l2);
    arena.destroy(l3);
}

TEST(Arena, unique)
{
    struct Obj { int v{0}; ~Obj() { v = -1; } };

    qc::Arena arena{100};

    qc::Unq<Obj> o1{arena.createUnique<Obj>(1)};
    ASSERT_EQ(1, (*o1).v);
    ASSERT_EQ(1, o1->v);
    ASSERT_EQ(&*o1, o1.get());
    ASSERT_TRUE(o1);

    int & v1{o1->v};
    qc::Unq<Obj> o2{std::move(o1)};
    ASSERT_EQ(1, v1);

    o1 = std::move(o2);
    ASSERT_EQ(1, v1);

    o1 = {};
    ASSERT_EQ(-1, v1);
    ASSERT_FALSE(o1);

    {
        qc::Unq<Obj> o3{arena.createUnique<Obj>(2)};
        ASSERT_EQ(2, v1);
    }

    ASSERT_EQ(-1, v1);
}

TEST(Arena, shared)
{
    struct Obj { int v{0}; ~Obj() { v = -1; } };

    qc::Arena arena{100};

    qc::Shr<Obj> o1{arena.createShared<Obj>(1)};
    ASSERT_EQ(1, (*o1).v);
    ASSERT_EQ(1, o1->v);
    ASSERT_EQ(&*o1, o1.get());
    ASSERT_TRUE(o1);

    int & v1{o1->v};
    ASSERT_EQ(1, v1);

    qc::Shr<Obj> o2{std::move(o1)};
    ASSERT_EQ(1, v1);

    o1 = std::move(o2);
    ASSERT_EQ(1, v1);

    o1 = {};
    ASSERT_EQ(-1, v1);
    ASSERT_FALSE(o1);

    o1 = arena.createShared<Obj>(2);
    ASSERT_EQ(2, v1);

    o2 = o1;
    ASSERT_EQ(2, v1);

    o1 = {};
    ASSERT_EQ(2, v1);

    o2 = {};
    ASSERT_EQ(-1, v1);

    o1 = arena.createShared<Obj>(3);
    ASSERT_EQ(3, v1);

    {
        qc::Shr<Obj> o3{o1};
        ASSERT_EQ(3, v1);
    }

    ASSERT_EQ(3, v1);

    {
        qc::Shr<Obj> o3{o1};
        ASSERT_EQ(3, v1);

        o1 = {};
        ASSERT_EQ(3, v1);
    }

    ASSERT_EQ(-1, v1);
}

TEST(Arena, polymorphism)
{
    struct A { int x{0}; virtual ~A() { x -= 1; } };
    struct B : A { int y{0}; ~B() override { x -= 2; } };

    qc::Arena arena{100};

    {
        A & a{arena.create<A>()};
        int & x{a.x};
        ASSERT_EQ(0, x);

        arena.destroy(a);
        ASSERT_EQ(-1, x);
    }

    {
        B & b{arena.create<B>()};
        int & x{b.x};
        ASSERT_EQ(0, x);

        arena.destroy(b);
        ASSERT_EQ(-3, x);
    }

    {
        A & a{arena.create<B>()};
        int & x{a.x};
        ASSERT_EQ(0, x);

        arena.destroy(a);
        ASSERT_EQ(-3, x);
    }
}
