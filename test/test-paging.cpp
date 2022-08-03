#include <qc-core/paging.hpp>

#include <gtest/gtest.h>

#include <qc-core/core.hpp>

using namespace qc::types;

TEST(Paging, pageSize)
{
    ASSERT_TRUE(std::has_single_bit(qc::pageSize));
    ASSERT_GE(qc::pageSize, 1024u);
}

TEST(Paging, allocate)
{
    const size_t pageCount{3u};
    size_t * const mem{static_cast<size_t *>(qc::allocatePages(pageCount))};
    ASSERT_TRUE(mem);

    const size_t n{pageCount * qc::pageSize / sizeof(size_t)};
    for (size_t i{0u}; i < n; ++i)
    {
        mem[i] = i;
    }

    #pragma warning(suppress: 4834)
    EXPECT_THROW(qc::allocatePages(0u), qc::PageError);
}

TEST(Paging, reserveCommit)
{
    const size_t pageCount{3u};
    size_t * const mem{static_cast<size_t *>(qc::reservePages(pageCount))};
    ASSERT_TRUE(mem);

    EXPECT_DEATH(mem[0] = 1, "");

    qc::commitPages(mem, 1u);

    const size_t n{qc::pageSize / sizeof(size_t)};
    for (size_t i{0u}; i < n; ++i)
    {
        mem[i] = i;
    }

    EXPECT_DEATH(mem[n] = n, "");

    qc::commitPages(mem + n, 2u);

    for (size_t i{n}; i < 2u * n; ++i)
    {
        mem[i] = i;
    }

    #pragma warning(suppress: 4834)
    EXPECT_THROW(qc::reservePages(0u), qc::PageError);

    EXPECT_THROW(qc::commitPages(nullptr, 0u), qc::PageError);
    EXPECT_THROW(qc::commitPages(nullptr, 1u), qc::PageError);
    EXPECT_THROW(qc::commitPages(mem, 0u), qc::PageError);
    qc::commitPages(mem, 3u);
}
