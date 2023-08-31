#pragma once

#include <qc-core/core.hpp>

namespace qc
{
    /// The actual page size on modern operating systems is 4k, but on Windows all page allocations are aligned to 64k.
    ///   For this reason, we may as well always allocate multiples of 64k, so we're pretending a page is actually 64k.
    ///   Unix does not have this property, but we can easily simulate it
    /// Hardcoded for compile-time optimization; it is checked the first time pages are reserved and the program will
    ///   abort if the actual value differs
    inline constexpr u64 pageSize{64u * 1024u};

    ///
    /// Allocate a contiguous block of memory
    ///
    /// Equivalent to `reservePages` + `commitPages`
    ///
    /// @param n number of pages to allocate
    /// @return start of the allocated memory, or null if `n` is 0
    ///
    nodisc void * allocatePages(u64 n);

    ///
    /// Reserve a contiguous block of virtual memory without actually allocating any physical memory
    ///
    /// This memory cannot be used before being committed, see `commitPages`
    ///
    /// @param n number of pages to reserve
    /// @return base of the reserved memory, or null if `n` is 0
    ///
    nodisc void * reservePages(u64 n);

    ///
    /// Commit a range of previously reserved pages to physical memory, allowing them to be used
    ///
    /// Committing the same page(s) multiple times has no effect
    ///
    /// @param start first page in the range to commit; pages must be currently reserved; no-op if null
    /// @param n number of pages to commit; no-op if zero
    ///
    void commitPages(void * start, u64 n);

    ///
    /// Decommit a range of previously committed pages, freeing the associated physical memory back to the system
    ///
    /// Decommitting the same page(s) multiple times has no effect
    ///
    /// @param start first page in the range to decommit; pages must be currently reserved; no-op if null
    /// @param n number of pages to decommit; no-op if zero
    ///
    void decommitPages(void * start, u64 n);

    ///
    /// Frees a previously allocated/reserved memory block both physically and virtually
    ///
    /// Pages can be committed or not, the memory is freed regardless
    ///
    /// @param start must be the base page returned by `allocatePages`/`reservePages`; no-op if null
    /// @param n must be the number of pages returned by `allocatePages`/`reservePages`; no-op if zero
    ///
    void freePages(void * start, u64 n);
}
