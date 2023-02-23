#pragma once

#include <qc-core/core.hpp>

namespace qc
{
    /// Assume pages are 4096 bytes for better compile-time optimization
    /// This is checked the first time pages are reserved, and the program will abort if the actual page size differs
    constexpr unat pageSize{4096u};

    ///
    /// Allocate a contiguous block of memory in page multiples
    ///
    /// Equivalent to `reservePages` + `commitPages`
    ///
    /// @param pageCount the number of pages to allocate
    /// @return the start of the allocated memory, or null if `pageCount` is 0
    ///
    [[nodiscard]] void * allocatePages(unat pageCount);

    ///
    /// Reserve a contiguous block of virtual memory without actually allocating any physical memory
    ///
    /// This memory cannot be used before being committed, see `commitPages`
    ///
    /// @param pageCount the number of pages to reserve
    /// @return the base of the reserved memory, or null if `pageCount` is 0
    ///
    [[nodiscard]] void * reservePages(unat pageCount);

    ///
    /// Commit a range of previously reserved pages to physical memory, allowing them to be used
    ///
    /// Committing the same page(s) multiple times has no effect
    ///
    /// @param pageStart the first page in the range to commit; pages must be currently reserved; no-op if null
    /// @param pageCount the number of pages to commit; no-op if zero
    ///
    void commitPages(void * pageStart, unat pageCount);

    ///
    /// Decommit a range of previously committed pages, freeing the associated physical memory back to the system
    ///
    /// Decommitting the same page(s) multiple times has no effect
    ///
    /// @param pageStart the first page in the range to decommit; pages must be currently reserved; no-op if null
    /// @param pageCount the number of pages to decommit; no-op if zero
    ///
    void decommitPages(void * pageStart, unat pageCount);

    ///
    /// Frees a previously allocated/reserved memory block both physically and virtually
    ///
    /// Pages can be committed or not, the memory is freed regardless
    ///
    /// @param pages must be the base page returned by `allocatePages`/`reservePages`; no-op if null
    ///
    void freePages(void * pages);
}
