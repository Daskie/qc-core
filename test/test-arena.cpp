#include <qc-core/arena.hpp>

#include <gtest/gtest.h>

using namespace qc::types;
using namespace qc::primitives;

namespace
{
    constexpr u64 _headerSize{16u};
}

TEST(Arena, growth)
{
    struct Page { std::byte bytes[qc::pageSize - _headerSize]; };

    qc::Arena arena{qc::pageSize * 8u};
    ASSERT_EQ(qc::pageSize * 8u, arena.capacity());
    ASSERT_EQ(0u, arena.size());

    qc::Unq<Page> p1{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize, arena.size());

    qc::Unq<Page> p2{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 2u, arena.size());

    qc::Unq<Page> p3{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 4u, arena.size());

    qc::Unq<Page> p4{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 4u, arena.size());

    qc::Unq<Page> p5{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 8u, arena.size());

    qc::Unq<Page> p6{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 8u, arena.size());

    qc::Unq<Page> p7{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 8u, arena.size());

    qc::Unq<Page> p8{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 8u, arena.size());

    p1.reset();
    p2.reset();
    p3.reset();
    p4.reset();
    p5.reset();
    p6.reset();
    p7.reset();
    p8.reset();
    ASSERT_EQ(qc::pageSize * 8u, arena.size());
}

TEST(Arena, shrinkToFit)
{
    struct Page { std::byte bytes[qc::pageSize - _headerSize]; };

    qc::Arena arena{qc::pageSize * 8u};
    ASSERT_EQ(qc::pageSize * 8u, arena.capacity());
    ASSERT_EQ(0u, arena.size());

    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 8u, arena.capacity());
    ASSERT_EQ(0u, arena.size());

    qc::Unq<Page> p1{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize, arena.size());

    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize, arena.size());

    qc::Unq<Page> p2{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 2u, arena.size());

    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 2u, arena.size());

    qc::Unq<Page> p3{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 4u, arena.size());

    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 4u, arena.size());

    qc::Unq<Page> p4{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 4u, arena.size());

    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 4u, arena.size());

    qc::Unq<Page> p5{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 8u, arena.size());

    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 8u, arena.size());

    qc::Unq<Page> p6{arena.unq<Page>()};
    qc::Unq<Page> p7{arena.unq<Page>()};
    qc::Unq<Page> p8{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 8u, arena.size());

    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 8u, arena.size());

    p8.reset();
    p7.reset();
    p6.reset();
    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 8u, arena.size());

    p4.reset();
    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 8u, arena.size());

    p5.reset();
    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 4u, arena.size());

    p3.reset();
    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 2u, arena.size());

    p2.reset();
    p1.reset();
    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 0u, arena.size());
}

TEST(Arena, alignment)
{
    qc::Arena arena{100u};

    qc::Unq<u64> v1{arena.unq<u64>(u64(1u))};
    ASSERT_EQ(0u, std::bit_cast<u64>(&*v1) & 0b111u);
    ASSERT_EQ(1u, *v1);

    qc::Unq<u32> v2{arena.unq<u32>(2u)};
    ASSERT_EQ(0u, std::bit_cast<u64>(&*v2) & 0b111u);
    ASSERT_EQ(2u, *v2);

    qc::Unq<u16> v3{arena.unq<u16>(u16(3u))};
    ASSERT_EQ(0u, std::bit_cast<u64>(&*v3) & 0b111u);
    ASSERT_EQ(3u, *v3);

    qc::Unq<u8> v4{arena.unq<u8>(u8(4u))};
    ASSERT_EQ(0u, std::bit_cast<u64>(&*v4) & 0b111u);
    ASSERT_EQ(4u, *v4);

    struct Eleven { std::byte bytes[11u]; };
    qc::Unq<Eleven> v5{arena.unq<Eleven>()};
    ASSERT_EQ(0u, std::bit_cast<u64>(&*v5) & 0b111u);
}

TEST(Arena, largeValue)
{
    struct Large { std::byte bytes[qc::pageSize + qc::pageSize / 2u - _headerSize]; };

    qc::Arena arena{qc::pageSize * 4u};

    qc::Unq<Large> l1{arena.unq<Large>()};
    ASSERT_EQ(qc::pageSize * 2u, arena.size());

    qc::Unq<Large> l2{arena.unq<Large>()};
    ASSERT_EQ(qc::pageSize * 4u, arena.size());

    ASSERT_DEATH(static_cast<void>(arena.unq<Large>()), "");

    l1.reset();

    qc::Unq<Large>l3{arena.unq<Large>()};
    ASSERT_EQ(qc::pageSize * 4u, arena.size());
}

TEST(Arena, unique)
{
    static thread_local bool destructed{false};

    struct Obj { int v{0}; ~Obj() { destructed = true; } };

    qc::Arena arena{100};

    qc::Unq<Obj> o1{arena.unq<Obj>(1)};
    ASSERT_EQ(1, (*o1).v);
    ASSERT_EQ(1, o1->v);
    ASSERT_EQ(&*o1, o1.get());
    ASSERT_TRUE(o1);

    ASSERT_EQ(o1, o1);
    ASSERT_EQ(o1, o1.get());
    ASSERT_EQ(o1.get(), o1);

    qc::Unq<Obj> o2{std::move(o1)};
    ASSERT_EQ(1, o2->v);

    ASSERT_NE(o2, o1);
    ASSERT_NE(o2, o1.get());
    ASSERT_NE(o2.get(), o1);

    o1 = std::move(o2);
    ASSERT_EQ(1, o1->v);

    destructed = false;
    o1 = {};
    ASSERT_TRUE(destructed);
    ASSERT_FALSE(o1);

    destructed = false;
    {
        qc::Unq<Obj> o3{arena.unq<Obj>(2)};
        ASSERT_EQ(2, o3->v);
    }
    ASSERT_TRUE(destructed);
}

TEST(Arena, shared)
{
    static thread_local bool destructed{false};

    struct Obj { int v{0}; ~Obj() { destructed = true; } };

    qc::Arena arena{100};

    qc::Shr<Obj> o1{arena.shr<Obj>(1)};
    ASSERT_EQ(1, (*o1).v);
    ASSERT_EQ(1, o1->v);
    ASSERT_EQ(&*o1, o1.get());
    ASSERT_TRUE(o1);

    ASSERT_EQ(1, o1->v);

    ASSERT_EQ(o1, o1);
    ASSERT_EQ(o1, o1.get());
    ASSERT_EQ(o1.get(), o1);

    qc::Shr<Obj> o2{std::move(o1)};
    ASSERT_EQ(1, o2->v);

    ASSERT_NE(o2, o1);
    ASSERT_NE(o2, o1.get());
    ASSERT_NE(o2.get(), o1);

    o1 = std::move(o2);
    ASSERT_EQ(1, o1->v);

    destructed = false;
    o1 = {};
    ASSERT_TRUE(destructed);
    ASSERT_FALSE(o1);

    o1 = arena.shr<Obj>(2);
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

    o1 = arena.shr<Obj>(3);
    ASSERT_EQ(3, o1->v);

    {
        qc::Shr<Obj> o3{o1};
        ASSERT_EQ(3, o3->v);
    }

    ASSERT_EQ(3, o1->v);

    {
        qc::Shr<Obj> o3{o1};
        ASSERT_EQ(3, o3->v);

        destructed = false;
        o1 = {};
        ASSERT_FALSE(destructed);
    }
    ASSERT_TRUE(destructed);

    {
        destructed = false;
        qc::Shr<Obj> o4{arena.shr<Obj>(4)};
        {
            qc::Shr<Obj> o5{arena.shr(o4.get())};
            ASSERT_FALSE(destructed);
            ASSERT_EQ(o5->v, 4);
        }
        ASSERT_FALSE(destructed);
        ASSERT_EQ(o4->v, 4);
    }
    ASSERT_TRUE(destructed);

    if constexpr (qc::debug)
    {
        qc::Unq<Obj> o6{arena.unq<Obj>(6)};
        EXPECT_DEBUG_DEATH(static_cast<void>(arena.shr(o6.get())), "");
    }
}

TEST(Arena, polymorphismUnique)
{
    qc::Arena arena{1000u};
    s32 x{0};

    struct A { s32 & x; A(s32 & x_) : x{x_} {}; virtual ~A() { ++x; } };
    struct B : A { s32 y{}; B(s32 & x_) : A{x_} {}; ~B() override { x += 10; } };

    {
        qc::Unq<A> a{arena.unq<A>(x)};
        ASSERT_EQ(0, x);

        a = {};
        ASSERT_EQ(1, x);

        a = arena.unq<A>(x);
        ASSERT_EQ(1, x);

        a = {};
        ASSERT_EQ(2, x);
    }

    x = 0;

    {
        qc::Unq<B> b{arena.unq<B>(x)};
        ASSERT_EQ(0, x);

        b = {};
        ASSERT_EQ(11, x);

        b = arena.unq<B>(x);
        ASSERT_EQ(11, x);

        b = {};
        ASSERT_EQ(22, x);
    }

    x = 0;

    {
        qc::Unq<A> a{arena.unq<B>(x)};
        ASSERT_EQ(0, x);

        a = {};
        ASSERT_EQ(11, x);

        a = arena.unq<B>(x);
        ASSERT_EQ(11, x);

        a = {};
        ASSERT_EQ(22, x);
    }
}

TEST(Arena, polymorphismShared)
{
    qc::Arena arena{1000u};
    s32 x{0};

    struct A { s32 & x; A(s32 & x_) : x{x_} {}; virtual ~A() { ++x; } };
    struct B : A { s32 y{}; B(s32 & x_) : A{x_} {}; ~B() override { x += 10; } };

    {
        qc::Shr<A> a{arena.shr<A>(x)};
        ASSERT_EQ(0, x);

        a = {};
        ASSERT_EQ(1, x);

        a = arena.shr<A>(x);
        ASSERT_EQ(1, x);

        a = {};
        ASSERT_EQ(2, x);
    }

    x = 0;

    {
        qc::Shr<B> b{arena.shr<B>(x)};
        ASSERT_EQ(0, x);

        b = {};
        ASSERT_EQ(11, x);

        b = arena.shr<B>(x);
        ASSERT_EQ(11, x);

        b = {};
        ASSERT_EQ(22, x);
    }

    x = 0;

    {
        qc::Shr<A> a{arena.shr<B>(x)};
        ASSERT_EQ(0, x);

        a = {};
        ASSERT_EQ(11, x);

        a = arena.shr<B>(x);
        ASSERT_EQ(11, x);

        a = {};
        ASSERT_EQ(22, x);
    }

    x = 0;

    {
        qc::Shr<A> a{arena.shr<A>(x)};
        qc::Shr<B> b{arena.shr<B>(x)};
        a = b;
    }
}
