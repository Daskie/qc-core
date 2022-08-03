#pragma once

namespace qc
{
    struct PageError {};

    extern const size_t pageSize;

    [[nodiscard]] void * allocatePages(size_t pageCount);

    // Reserve pages in the virtual address space of the process.
    [[nodiscard]] void * reservePages(size_t pageCount);

    void commitPages(void * reservedPage, size_t pageCount);
}
