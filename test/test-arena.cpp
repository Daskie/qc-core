#include <qc-core/arena.hpp>

#include <gtest/gtest.h>

using namespace qc::types;
using namespace qc::primitives;

template <typename T> using Unq = qc::Arena::Unq<T>;
template <typename T> using Shr = qc::Arena::Shr<T>;

namespace
{
    constexpr u64 _headerSize{8u};
}

TEST(Arena, growth)
{
    struct Page { std::byte bytes[qc::pageSize - _headerSize]; };

    qc::Arena arena{qc::pageSize * 8u - _headerSize};
    ASSERT_EQ(qc::pageSize * 8u - _headerSize, arena.capacity());
    ASSERT_EQ(0u, arena.size());

    Unq<Page> p1{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 2u - _headerSize, arena.size());

    Unq<Page> p2{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 4u - _headerSize, arena.size());

    Unq<Page> p3{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 4u - _headerSize, arena.size());

    Unq<Page> p4{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 8u - _headerSize, arena.size());

    Unq<Page> p5{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 8u - _headerSize, arena.size());

    Unq<Page> p6{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 8u - _headerSize, arena.size());

    Unq<Page> p7{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 8u - _headerSize, arena.size());

    p1.reset();
    p2.reset();
    p3.reset();
    p4.reset();
    p5.reset();
    p6.reset();
    p7.reset();
    ASSERT_EQ(qc::pageSize * 8u - _headerSize, arena.size());
}

TEST(Arena, shrinkToFit)
{
    struct Page { std::byte bytes[qc::pageSize - _headerSize]; };

    qc::Arena arena{qc::pageSize * 8u - _headerSize};
    ASSERT_EQ(qc::pageSize * 8u - _headerSize, arena.capacity());
    ASSERT_EQ(0u, arena.size());

    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 8u - _headerSize, arena.capacity());
    ASSERT_EQ(0u, arena.size());

    Unq<Page> p1{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 2u - _headerSize, arena.size());

    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 2u - _headerSize, arena.size());

    Unq<Page> p2{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 4u - _headerSize, arena.size());

    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 4u - _headerSize, arena.size());

    Unq<Page> p3{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 4u - _headerSize, arena.size());

    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 4u - _headerSize, arena.size());

    Unq<Page> p4{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 8u - _headerSize, arena.size());

    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 8u - _headerSize, arena.size());

    Unq<Page> p5{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 8u - _headerSize, arena.size());

    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 8u - _headerSize, arena.size());

    Unq<Page> p6{arena.unq<Page>()};
    Unq<Page> p7{arena.unq<Page>()};
    ASSERT_EQ(qc::pageSize * 8u - _headerSize, arena.size());

    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 8u - _headerSize, arena.size());

    p7.reset();
    p6.reset();
    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 8u - _headerSize, arena.size());

    p5.reset();
    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 8u - _headerSize, arena.size());

    p4.reset();
    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 4u - _headerSize, arena.size());

    p3.reset();
    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 4u - _headerSize, arena.size());

    p2.reset();
    arena.shrinkToFit();
    ASSERT_EQ(qc::pageSize * 2u - _headerSize, arena.size());

    p1.reset();
    arena.shrinkToFit();
    ASSERT_EQ(0u, arena.size());
}

TEST(Arena, alignment)
{
    qc::Arena arena{100u};

    Unq<u64> v1{arena.unq<u64>(u64(1u))};
    ASSERT_EQ(0u, std::bit_cast<u64>(&*v1) & 0b111u);
    ASSERT_EQ(1u, *v1);

    Unq<u32> v2{arena.unq<u32>(2u)};
    ASSERT_EQ(0u, std::bit_cast<u64>(&*v2) & 0b111u);
    ASSERT_EQ(2u, *v2);

    Unq<u16> v3{arena.unq<u16>(u16(3u))};
    ASSERT_EQ(0u, std::bit_cast<u64>(&*v3) & 0b111u);
    ASSERT_EQ(3u, *v3);

    Unq<u8> v4{arena.unq<u8>(u8(4u))};
    ASSERT_EQ(0u, std::bit_cast<u64>(&*v4) & 0b111u);
    ASSERT_EQ(4u, *v4);

    struct Eleven { std::byte bytes[11u]; };
    Unq<Eleven> v5{arena.unq<Eleven>()};
    ASSERT_EQ(0u, std::bit_cast<u64>(&*v5) & 0b111u);
}

TEST(Arena, largeValue)
{
    struct Large { std::byte bytes[qc::pageSize + qc::pageSize / 2u - _headerSize]; };

    qc::Arena arena{qc::pageSize * 4u - _headerSize};

    Unq<Large> l1{arena.unq<Large>()};
    ASSERT_EQ(qc::pageSize * 2u - _headerSize, arena.size());

    Unq<Large> l2{arena.unq<Large>()};
    ASSERT_EQ(qc::pageSize * 4u - _headerSize, arena.size());

    ASSERT_DEATH(static_cast<void>(arena.unq<Large>()), "");

    l1.reset();

    Unq<Large>l3{arena.unq<Large>()};
    ASSERT_EQ(qc::pageSize * 4u - _headerSize, arena.size());
}

TEST(Arena, unique)
{
    static thread_local bool destructed{false};

    struct Obj { int v{0}; ~Obj() { destructed = true; } };

    qc::Arena arena{100};

    Unq<Obj> o1{arena.unq<Obj>(1)};
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
        Unq<Obj> o3{arena.unq<Obj>(2)};
        ASSERT_EQ(2, o3->v);
    }
    ASSERT_TRUE(destructed);
}

TEST(Arena, shared)
{
    static thread_local bool destructed{false};

    struct Obj { int v{0}; ~Obj() { destructed = true; } };

    qc::Arena arena{100};

    Shr<Obj> o1{arena.shr<Obj>(1)};
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
        Shr<Obj> o4{arena.shr<Obj>(4)};
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
        Unq<Obj> o6{arena.unq<Obj>(6)};
        Shr<Obj> o7{arena.shrOf(&*o6)};
        EXPECT_DEBUG_DEATH(o6.reset(), "");
    }
}

TEST(Arena, polymorphismUnique)
{
    qc::Arena arena{1000u};
    s32 x{0};

    struct A { s32 & x; A(s32 & x_) : x{x_} {}; virtual ~A() { ++x; } };
    struct B : A { s32 y{}; B(s32 & x_) : A{x_} {}; ~B() override { x += 10; } };

    {
        Unq<A> a{arena.unq<A>(x)};
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
        Unq<B> b{arena.unq<B>(x)};
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
        Unq<A> a{arena.unq<B>(x)};
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
        Shr<A> a{arena.shr<A>(x)};
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
        Shr<B> b{arena.shr<B>(x)};
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
        Shr<A> a{arena.shr<B>(x)};
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
        Shr<A> a{arena.shr<A>(x)};
        Shr<B> b{arena.shr<B>(x)};
        a = b;
    }
}

TEST(Arena, moveability)
{
    qc::Arena a2{1000};
    Unq<u32> v;
    {
        qc::Arena a1{1000};
        v = a1.unq<u32>(7u);
        ASSERT_FALSE(a1.empty());
        ASSERT_EQ(*v, 7u);
        a2 = std::move(a1);
        ASSERT_TRUE(a1.empty());
        ASSERT_FALSE(a2.empty());
        ASSERT_EQ(*v, 7u);
    }
    ASSERT_EQ(*v, 7u);
    v.reset();
    ASSERT_TRUE(a2.empty());
}
