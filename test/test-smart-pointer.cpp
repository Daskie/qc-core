#include <qc-core/smart-pointer.hpp>

#include <gtest/gtest.h>

using namespace qc::primitives;

using qc::Unq;
using qc::Shr;

struct Obj
{
    inline static u32 destructCount{0};

    s32 v{0};

    ~Obj() { ++destructCount; }
};

TEST(SmartPointer, unique)
{
    Obj::destructCount = 0u;

    qc::Unq<Obj> o0{};
    ASSERT_EQ(nullptr, o0.get());
    ASSERT_FALSE(o0);

    qc::Unq<Obj> o1{qc::makeUnique<Obj>(1)};
    ASSERT_EQ(1, (*o1).v);
    ASSERT_EQ(1, o1->v);
    ASSERT_EQ(&*o1, o1.get());
    ASSERT_TRUE(o1);

    qc::Unq<Obj> o2{std::move(o1)};
    ASSERT_EQ(1, o2->v);
    ASSERT_EQ(0u, Obj::destructCount);

    o1 = std::move(o2);
    ASSERT_EQ(1, o1->v);
    ASSERT_EQ(0u, Obj::destructCount);

    o1 = {};
    ASSERT_EQ(nullptr, o0.get());
    ASSERT_FALSE(o1);
    ASSERT_EQ(1u, Obj::destructCount);

    {
        qc::Unq<Obj> o3{qc::makeUnique<Obj>(2)};
        ASSERT_EQ(2, o3->v);
    }

    ASSERT_EQ(2u, Obj::destructCount);
}

TEST(SmartPointer, shared)
{
    Obj::destructCount = 0u;

    qc::Shr<Obj> o0{};
    ASSERT_EQ(nullptr, o0.get());
    ASSERT_FALSE(o0);

    qc::Shr<Obj> o1{qc::makeShared<Obj>(1)};
    ASSERT_EQ(1, (*o1).v);
    ASSERT_EQ(1, o1->v);
    ASSERT_EQ(&*o1, o1.get());
    ASSERT_TRUE(o1);

    qc::Shr<Obj> o2{std::move(o1)};
    ASSERT_EQ(1, o2->v);
    ASSERT_EQ(0u, Obj::destructCount);

    o1 = std::move(o2);
    ASSERT_EQ(1, o1->v);

    o1 = {};
    ASSERT_FALSE(o1);
    ASSERT_EQ(1u, Obj::destructCount);

    o1 = qc::makeShared<Obj>(2);
    ASSERT_EQ(2, o1->v);

    o2 = o1;
    ASSERT_EQ(2, o2->v);
    ASSERT_EQ(1u, Obj::destructCount);

    o1 = {};
    ASSERT_EQ(2, o2->v);
    ASSERT_EQ(1u, Obj::destructCount);

    o2 = {};
    ASSERT_EQ(2u, Obj::destructCount);

    o1 = qc::makeShared<Obj>(3);
    ASSERT_EQ(3, o1->v);

    {
        qc::Shr<Obj> o3{o1};
        ASSERT_EQ(3, o3->v);
    }

    ASSERT_EQ(3, o1->v);
    ASSERT_EQ(2u, Obj::destructCount);

    {
        qc::Shr<Obj> o3{o1};
        ASSERT_EQ(3, o3->v);

        o1 = {};
        ASSERT_EQ(3, o3->v);
        ASSERT_EQ(2u, Obj::destructCount);
    }

    ASSERT_EQ(3u, Obj::destructCount);
}

TEST(Arena, polymorphismUnique)
{
    s32 x{0};

    struct A { s32 & x; A(s32 & x_) : x{x_} {}; virtual ~A() { ++x; } };
    struct B : A { s32 y{}; B(s32 & x_) : A{x_} {}; ~B() override { x += 10; } };

    {
        qc::Unq<A> a{qc::makeUnique<A>(x)};
        ASSERT_EQ(0, x);

        a = {};
        ASSERT_EQ(1, x);

        a = qc::makeUnique<A>(x);
        ASSERT_EQ(1, x);

        a = {};
        ASSERT_EQ(2, x);
    }

    x = 0;

    {
        qc::Unq<B> b{qc::makeUnique<B>(x)};
        ASSERT_EQ(0, x);

        b = {};
        ASSERT_EQ(11, x);

        b = qc::makeUnique<B>(x);
        ASSERT_EQ(11, x);

        b = {};
        ASSERT_EQ(22, x);
    }

    x = 0;

    {
        qc::Unq<A> a{qc::makeUnique<B>(x)};
        ASSERT_EQ(0, x);

        a = {};
        ASSERT_EQ(11, x);

        a = qc::makeUnique<B>(x);
        ASSERT_EQ(11, x);

        a = {};
        ASSERT_EQ(22, x);
    }
}

TEST(Arena, polymorphismShared)
{
    s32 x{0};

    struct A { s32 & x; A(s32 & x_) : x{x_} {}; virtual ~A() { ++x; } };
    struct B : A { s32 y{}; B(s32 & x_) : A{x_} {}; ~B() override { x += 10; } };

    {
        qc::Shr<A> a{qc::makeShared<A>(x)};
        ASSERT_EQ(0, x);

        a = {};
        ASSERT_EQ(1, x);

        a = qc::makeShared<A>(x);
        ASSERT_EQ(1, x);

        a = {};
        ASSERT_EQ(2, x);
    }

    x = 0;

    {
        qc::Shr<B> b{qc::makeShared<B>(x)};
        ASSERT_EQ(0, x);

        b = {};
        ASSERT_EQ(11, x);

        b = qc::makeShared<B>(x);
        ASSERT_EQ(11, x);

        b = {};
        ASSERT_EQ(22, x);
    }

    x = 0;

    {
        qc::Shr<A> a{qc::makeShared<B>(x)};
        ASSERT_EQ(0, x);

        a = {};
        ASSERT_EQ(11, x);

        a = qc::makeShared<B>(x);
        ASSERT_EQ(11, x);

        a = {};
        ASSERT_EQ(22, x);
    }

    x = 0;

    {
        qc::Shr<A> a{qc::makeShared<A>(x)};
        qc::Shr<B> b{qc::makeShared<B>(x)};
        a = b;
    }
}
