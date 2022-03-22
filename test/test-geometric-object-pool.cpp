#include <qc-core/geometric-object-pool.hpp>

#include <gtest/gtest.h>

#include <qc-core/random.hpp>

struct Val
{
    inline static size_t constructionCount{0u};
    inline static size_t destructionCount{0u};
    int v{};
    Val(const int v) : v{v} { ++constructionCount; }
    ~Val() { ++destructionCount; }
};

TEST(GeometricObjectPool, defaultInitialCapacity)
{
    qc::GeometricObjectPool<Val> pool{};
    EXPECT_EQ(qc::GeometricObjectPool<int>::defaultInitialCapacity, pool.capacity());
}

TEST(GeometricObjectPool, standard)
{
    qc::Random random{};

    qc::GeometricObjectPool<Val> pool{4u};
    EXPECT_EQ(4u, pool.capacity());
    EXPECT_EQ(0u, pool.count());

    Val * v{pool.new_(0)};
    EXPECT_EQ(0, v->v);
    EXPECT_EQ(4u, pool.capacity());
    EXPECT_EQ(1u, pool.count());
    EXPECT_EQ(Val::constructionCount, 1u);
    EXPECT_EQ(Val::destructionCount, 0u);

    pool.delete_(v);
    EXPECT_EQ(4u, pool.capacity());
    EXPECT_EQ(0u, pool.count());
    EXPECT_EQ(Val::constructionCount, 1u);
    EXPECT_EQ(Val::destructionCount, 1u);

    Val::constructionCount = 0u;
    Val::destructionCount = 0u;

    std::array<Val *, 16u> vals{};

    for (int i{0}; i < 4; ++i)
    {
        vals[i] = pool.new_(i);
    }
    for (int i{0}; i < 4; ++i)
    {
        EXPECT_EQ(i, vals[i]->v);
    }
    EXPECT_EQ(4u, pool.capacity());
    EXPECT_EQ(4u, pool.count());
    EXPECT_EQ(Val::constructionCount, 4u);
    EXPECT_EQ(Val::destructionCount, 0u);

    vals[4] = pool.new_(4);
    EXPECT_EQ(4, vals[4]->v);
    EXPECT_EQ(8u, pool.capacity());
    EXPECT_EQ(5u, pool.count());
    EXPECT_EQ(Val::constructionCount, 5u);
    EXPECT_EQ(Val::destructionCount, 0u);

    for (int i{5}; i < 8; ++i)
    {
        vals[i] = pool.new_(i);
    }
    for (int i{5}; i < 8; ++i)
    {
        EXPECT_EQ(i, vals[i]->v);
    }
    EXPECT_EQ(8u, pool.capacity());
    EXPECT_EQ(8u, pool.count());
    EXPECT_EQ(Val::constructionCount, 8u);
    EXPECT_EQ(Val::destructionCount, 0u);

    vals[8] = pool.new_(8);
    EXPECT_EQ(8, vals[8]->v);
    EXPECT_EQ(16u, pool.capacity());
    EXPECT_EQ(9u, pool.count());
    EXPECT_EQ(Val::constructionCount, 9u);
    EXPECT_EQ(Val::destructionCount, 0u);

    for (int i{9}; i < 16; ++i)
    {
        vals[i] = pool.new_(i);
    }
    for (int i{9}; i < 16; ++i)
    {
        EXPECT_EQ(i, vals[i]->v);
    }
    EXPECT_EQ(16u, pool.capacity());
    EXPECT_EQ(16u, pool.count());
    EXPECT_EQ(Val::constructionCount, 16u);
    EXPECT_EQ(Val::destructionCount, 0u);

    std::shuffle(vals.begin(), vals.end(), random.engine());

    for (int i{0}; i < 8; ++i)
    {
        pool.delete_(vals[i]);
    }
    EXPECT_EQ(16u, pool.capacity());
    EXPECT_EQ(8u, pool.count());
    EXPECT_EQ(Val::constructionCount, 16u);
    EXPECT_EQ(Val::destructionCount, 8u);

    for (int i{0}; i < 8; ++i)
    {
        vals[i] = pool.new_(16 + i);
    }
    for (int i{0}; i < 8; ++i)
    {
        EXPECT_EQ(16 + i, vals[i]->v);
    }
    EXPECT_EQ(16u, pool.capacity());
    EXPECT_EQ(16u, pool.count());
    EXPECT_EQ(Val::constructionCount, 24u);
    EXPECT_EQ(Val::destructionCount, 8u);

    std::shuffle(vals.begin(), vals.end(), random.engine());

    for (int i{0}; i < 16; ++i)
    {
        pool.delete_(vals[i]);
    }
    EXPECT_EQ(16u, pool.capacity());
    EXPECT_EQ(0u, pool.count());
    EXPECT_EQ(Val::constructionCount, 24u);
    EXPECT_EQ(Val::destructionCount, 24u);

    Val::constructionCount = 0u;
    Val::destructionCount = 0u;

    v = pool.new_(0);
    EXPECT_EQ(0, v->v);
    EXPECT_EQ(16u, pool.capacity());
    EXPECT_EQ(1u, pool.count());
    EXPECT_EQ(Val::constructionCount, 1u);
    EXPECT_EQ(Val::destructionCount, 0u);

    pool.delete_(v);
    EXPECT_EQ(16u, pool.capacity());
    EXPECT_EQ(0u, pool.count());
    EXPECT_EQ(Val::constructionCount, 1u);
    EXPECT_EQ(Val::destructionCount, 1u);
}
