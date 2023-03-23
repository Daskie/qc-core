#include <qc-core/core.hpp>
#include <qc-core/paging.hpp>

#include <gtest/gtest.h>

#ifdef QC_MSVC
    #define ASSERT_DEATH_IF_MSVC(statement, regex) ASSERT_DEATH(statement, regex)
#else
    #define ASSERT_DEATH_IF_MSVC(statement, regex) static_cast<void>(0)
#endif

using namespace qc::types;
using namespace qc::primitives;

TEST(Paging, allocate)
{
    ASSERT_EQ(qc::allocatePages(0u), nullptr);

    const u64 pageN{3u};
    u64 * const mem{static_cast<u64 *>(qc::allocatePages(pageN))};
    ASSERT_TRUE(mem);

    const u64 n{pageN * qc::pageSize / sizeof(u64)};
    for (u64 i{0u}; i < n; ++i)
    {
        mem[i] = i;
    }

    qc::freePages(nullptr, 0u);
    qc::freePages(nullptr, 1u);
    qc::freePages(mem, 0u);
    ASSERT_DEATH(qc::freePages(mem + 1, pageN), "");
    ASSERT_DEATH_IF_MSVC(qc::freePages(mem + qc::pageSize * pageN, 1u), "");
    qc::freePages(mem, pageN);
    ASSERT_DEATH_IF_MSVC(qc::freePages(mem, pageN), "");
}

TEST(Paging, reserveCommit)
{
    const u64 n{qc::pageSize / sizeof(u64)};

    ASSERT_EQ(qc::reservePages(0u), nullptr);

    u64 * const mem{static_cast<u64 *>(qc::reservePages(3u))};
    ASSERT_TRUE(mem);

    ASSERT_DEATH(mem[0] = 1, "");

    qc::commitPages(nullptr, 0u);
    qc::commitPages(nullptr, 1u);
    qc::commitPages(mem, 0u);
    ASSERT_DEATH(qc::commitPages(mem + 1, 1u), "");
    ASSERT_DEATH(qc::commitPages(mem + n * 1000u, 1u), "");

    qc::commitPages(mem, 1u);

    for (u64 i{0u}; i < n; ++i)
    {
        mem[i] = i;
    }

    qc::commitPages(mem, 1u);

    ASSERT_DEATH(mem[n] = n, "");

    qc::commitPages(mem + n, 2u);

    for (u64 i{n}; i < 2u * n; ++i)
    {
        mem[i] = i;
    }

    ASSERT_DEATH(qc::commitPages(mem + n * 1000u, 1u), "");
    ASSERT_DEATH_IF_MSVC(qc::commitPages(mem, 4u), "");

    qc::decommitPages(nullptr, 0u);
    qc::decommitPages(nullptr, 1u);
    qc::decommitPages(mem, 0u);
    ASSERT_DEATH(qc::decommitPages(mem + 1, 1u), "");
    ASSERT_DEATH(qc::decommitPages(mem + n * 1000u, 1u), "");

    qc::decommitPages(mem + n, 1u);
    mem[0] = 0u;
    ASSERT_DEATH(mem[n] = 1u, "");
    mem[n * 2u] = 2u;

    qc::decommitPages(mem + n, 1u);

    qc::commitPages(mem + n, 1u);
    mem[n] = 1u;

    ASSERT_DEATH_IF_MSVC(qc::decommitPages(mem, 4u), "");
    mem[0] = 0u;
    mem[n] = 1u;
    mem[n * 2u] = 2u;

    qc::decommitPages(mem, 3u);
    ASSERT_DEATH(mem[0] = 0u, "");
    ASSERT_DEATH(mem[n] = 1u, "");
    ASSERT_DEATH(mem[n * 2u] = 2u, "");

    qc::freePages(nullptr, 0u);
    qc::freePages(nullptr, 1u);
    qc::freePages(mem, 0u);
    ASSERT_DEATH(qc::freePages(mem + 1, 3u), "");
    ASSERT_DEATH_IF_MSVC(qc::freePages(mem + n, 1u), "");
    qc::freePages(mem, 3u);
    ASSERT_DEATH_IF_MSVC(qc::freePages(mem, 3u), "");
}
