#pragma once

namespace qc
{
    struct PageError {};

    /// Assume pages are 4096 bytes for better compile-time optimization
    /// This is checked the first time pages are reserved, and an exception is thrown if the actual page size differs
    constexpr size_t pageSize{4096u};

    ///
    /// Allocate a contiguous block of memory in page multiples
    ///
    /// Equivalent to `reservePages` + `commitPages`
    ///
    /// @param pageCount the number of pages to allocate
    /// @return the start of the allocated memory
    /// @throw PageError if `pageCount` is 0 or the allocation fails
    ///
    [[nodiscard]] void * allocatePages(size_t pageCount);

    ///
    /// Reserve a contiguous block of virtual memory without actually allocating any physical memory
    ///
    /// This memory cannot be used before being committed, see `commitPages`
    ///
    /// @param pageCount the number of pages to reserve
    /// @return the base of the reserved memory
    /// @throw PageError if `pageCount` is 0 or the reservation fails
    ///
    [[nodiscard]] void * reservePages(size_t pageCount);

    ///
    /// Commit a range of previously reserved pages to physical memory, allowing them to be used
    ///
    /// Committing the same page(s) multiple times has no effect
    ///
    /// @param pageStart the first page in the range to commit; pages must be currently reserved; no-op if null
    /// @param pageCount the number of pages to commit; no-op if zero
    /// @throw PageError if the commit fails
    ///
    void commitPages(void * pageStart, size_t pageCount);

    ///
    /// Decommit a range of previously committed pages, freeing the associated physical memory back to the system
    ///
    /// Decommitting the same page(s) multiple times has no effect
    ///
    /// @param pageStart the first page in the range to decommit; pages must be currently reserved; no-op if null
    /// @param pageCount the number of pages to decommit; no-op if zero
    /// @throw PageError if the decommit fails
    ///
    void decommitPages(void * pageStart, size_t pageCount);

    ///
    /// Frees a previously allocated/reserved memory block both physically and virtually
    ///
    /// Pages can be committed or not, the memory is freed regardless
    ///
    /// @param pages must be the base page returned by `allocatePages`/`reservePages`; no-op if null
    /// @throw PageError if the free fails
    ///
    void freePages(void * pages);
}
