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

    qc::GeometricObjectPool<Val> pool{1u};
    EXPECT_EQ(1u, pool.capacity());
    EXPECT_EQ(0u, pool.count());

    pool.reserve(3u);
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

TEST(GeometricObjectPool, reserve)
{
    constexpr size_t multiple{sizeof(void *) * (qc::debug ?  2u : 1u) / sizeof(int)};

    int * ptrs[16u];

    qc::GeometricObjectPool<int> pool{1u};
    EXPECT_EQ(1u, pool.capacity());

    #pragma warning(suppress: 4834)
    ptrs[0] = pool.new_();
    EXPECT_EQ(1u, pool.capacity());

    #pragma warning(suppress: 4834)
    ptrs[1] = pool.new_();
    EXPECT_EQ(2u, pool.capacity());

    ptrs[2] = pool.new_();
    EXPECT_EQ(4u, pool.capacity());

    pool.reserve(16u);
    EXPECT_EQ(16u, pool.capacity());

    EXPECT_EQ(ptrs[2] + 1 * multiple, ptrs[3] = pool.new_());

    ptrs[4] = pool.new_();
    EXPECT_EQ(ptrs[4] + 1 * multiple, ptrs[5] = pool.new_());
    EXPECT_EQ(ptrs[4] + 2 * multiple, ptrs[6] = pool.new_());
    EXPECT_EQ(ptrs[4] + 3 * multiple, ptrs[7] = pool.new_());

    ptrs[8] = pool.new_();
    EXPECT_EQ(ptrs[8] + 1 * multiple, ptrs[ 9] = pool.new_());
    EXPECT_EQ(ptrs[8] + 2 * multiple, ptrs[10] = pool.new_());
    EXPECT_EQ(ptrs[8] + 3 * multiple, ptrs[11] = pool.new_());
    EXPECT_EQ(ptrs[8] + 4 * multiple, ptrs[12] = pool.new_());
    EXPECT_EQ(ptrs[8] + 5 * multiple, ptrs[13] = pool.new_());
    EXPECT_EQ(ptrs[8] + 6 * multiple, ptrs[14] = pool.new_());
    EXPECT_EQ(ptrs[8] + 7 * multiple, ptrs[15] = pool.new_());

    EXPECT_EQ(16u, pool.capacity());

    for (int * ptr : ptrs)
    {
        pool.delete_(ptr);
    }
}
