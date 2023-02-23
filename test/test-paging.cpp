#include <qc-core/core.hpp>
#include <qc-core/paging.hpp>

#include <gtest/gtest.h>

using namespace qc::concepts;
using namespace qc::types;

TEST(Paging, allocate)
{
    #pragma warning(suppress: 4834)
    ASSERT_EQ(qc::allocatePages(0u), nullptr);

    const unat pageCount{3u};
    unat * const mem{static_cast<unat *>(qc::allocatePages(pageCount))};
    ASSERT_TRUE(mem);

    const unat n{pageCount * qc::pageSize / sizeof(unat)};
    for (unat i{0u}; i < n; ++i)
    {
        mem[i] = i;
    }

    qc::freePages(nullptr);
    ASSERT_DEATH(qc::freePages(mem + 1), "");
    qc::freePages(mem);
    ASSERT_DEATH(qc::freePages(mem), "");
}

TEST(Paging, reserveCommit)
{
    #pragma warning(suppress: 4834)
    ASSERT_EQ(qc::reservePages(0u), nullptr);

    unat * const mem{static_cast<size_t *>(qc::reservePages(3u))};
    ASSERT_TRUE(mem);

    ASSERT_DEATH(mem[0] = 1, "");

    qc::commitPages(nullptr, 0u);
    qc::commitPages(nullptr, 1u);
    qc::commitPages(mem, 0u);
    ASSERT_DEATH(qc::commitPages(mem + 1, 1u), "");

    qc::commitPages(mem, 1u);

    const size_t n{qc::pageSize / sizeof(size_t)};
    for (size_t i{0u}; i < n; ++i)
    {
        mem[i] = i;
    }

    qc::commitPages(mem, 1u);

    ASSERT_DEATH(mem[n] = n, "");

    qc::commitPages(mem + n, 2u);

    for (size_t i{n}; i < 2u * n; ++i)
    {
        mem[i] = i;
    }

    ASSERT_DEATH(qc::commitPages(mem + n * 3u, 1u), "");
    ASSERT_DEATH(qc::commitPages(mem, 4u), "");

    qc::decommitPages(nullptr, 0u);
    qc::decommitPages(nullptr, 1u);
    qc::decommitPages(mem, 0u);
    ASSERT_DEATH(qc::decommitPages(mem + 1, 1u), "");

    qc::decommitPages(mem + n, 1u);
    mem[0] = 0u;
    ASSERT_DEATH(mem[n] = 1u, "");
    mem[n * 2u] = 2u;

    qc::decommitPages(mem + n, 1u);

    qc::commitPages(mem + n, 1u);
    mem[n] = 1u;

    ASSERT_DEATH(qc::decommitPages(mem, 4u), "");
    mem[0] = 0u;
    mem[n] = 1u;
    mem[n * 2u] = 2u;

    qc::decommitPages(mem, 3u);
    ASSERT_DEATH(mem[0] = 0u, "");
    ASSERT_DEATH(mem[n] = 1u, "");
    ASSERT_DEATH(mem[n * 2u] = 2u, "");

    qc::freePages(nullptr);
    ASSERT_DEATH(qc::freePages(mem + 1), "");
    qc::freePages(mem);
    ASSERT_DEATH(qc::freePages(mem), "");
}
