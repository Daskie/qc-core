#include <qc-core/paging.hpp>

#include <gtest/gtest.h>

#include <qc-core/core.hpp>

using namespace qc::concepts;
using namespace qc::types;

TEST(Paging, allocate)
{
    #pragma warning(suppress: 4834)
    EXPECT_THROW(qc::allocatePages(0u), qc::PageError);

    const unat pageCount{3u};
    unat * const mem{static_cast<unat *>(qc::allocatePages(pageCount))};
    ASSERT_TRUE(mem);

    const unat n{pageCount * qc::pageSize / sizeof(unat)};
    for (unat i{0u}; i < n; ++i)
    {
        mem[i] = i;
    }

    qc::freePages(nullptr);
    EXPECT_THROW(qc::freePages(mem + 1), qc::PageError);
    qc::freePages(mem);
    EXPECT_THROW(qc::freePages(mem), qc::PageError);
}

TEST(Paging, reserveCommit)
{
    #pragma warning(suppress: 4834)
    EXPECT_THROW(qc::reservePages(0u), qc::PageError);

    unat * const mem{static_cast<size_t *>(qc::reservePages(3u))};
    ASSERT_TRUE(mem);

    EXPECT_DEATH(mem[0] = 1, "");

    qc::commitPages(nullptr, 0u);
    EXPECT_THROW(qc::commitPages(nullptr, 1u), qc::PageError);
    qc::commitPages(mem, 0u);
    EXPECT_THROW(qc::commitPages(mem + 1, 1u), qc::PageError);

    qc::commitPages(mem, 1u);

    const size_t n{qc::pageSize / sizeof(size_t)};
    for (size_t i{0u}; i < n; ++i)
    {
        mem[i] = i;
    }

    qc::commitPages(mem, 1u);

    EXPECT_DEATH(mem[n] = n, "");

    qc::commitPages(mem + n, 2u);

    for (size_t i{n}; i < 2u * n; ++i)
    {
        mem[i] = i;
    }

    EXPECT_THROW(qc::commitPages(mem + n * 3u, 1u), qc::PageError);
    EXPECT_THROW(qc::commitPages(mem, 4u), qc::PageError);

    qc::decommitPages(nullptr, 0u);
    qc::decommitPages(nullptr, 1u);
    qc::decommitPages(mem, 0u);
    EXPECT_THROW(qc::decommitPages(mem + 1, 1u), qc::PageError);

    qc::decommitPages(mem + n, 1u);
    mem[0] = 0u;
    EXPECT_DEATH(mem[n] = 1u, "");
    mem[n * 2u] = 2u;

    qc::decommitPages(mem + n, 1u);

    qc::commitPages(mem + n, 1u);
    mem[n] = 1u;

    EXPECT_THROW(qc::decommitPages(mem, 4u), qc::PageError);
    mem[0] = 0u;
    mem[n] = 1u;
    mem[n * 2u] = 2u;

    qc::decommitPages(mem, 3u);
    EXPECT_DEATH(mem[0] = 0u, "");
    EXPECT_DEATH(mem[n] = 1u, "");
    EXPECT_DEATH(mem[n * 2u] = 2u, "");

    qc::freePages(nullptr);
    EXPECT_THROW(qc::freePages(mem + 1), qc::PageError);
    qc::freePages(mem);
    EXPECT_THROW(qc::freePages(mem), qc::PageError);
}
