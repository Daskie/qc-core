#include <qc-core/paging.hpp>

#include <atomic>

#ifdef WIN32
    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX
    #include <windows.h>
#else
    #error "Platform not yet supported"
#endif

namespace qc
{
    static size_t _getPageSize() noexcept
    {
        SYSTEM_INFO sSysInfo;
        GetSystemInfo(&sSysInfo);
        return sSysInfo.dwPageSize;
    }

    const size_t pageSize{_getPageSize()};

    void * allocatePages(const size_t pageCount)
    {
        void * const baseAddress{VirtualAlloc(
            nullptr,                  // System selects base address
            pageCount * pageSize,             // Size of allocation
            MEM_RESERVE | MEM_COMMIT, // Immediately pin pages in physical swap memory
            PAGE_READWRITE)};         // Grant read/write access

        if (!baseAddress)
        {
            throw PageError{};
        }

        return baseAddress;
    }

    void * reservePages(const size_t pageCount)
    {
        void * const baseAddress{VirtualAlloc(
            nullptr,         // System selects base address
            pageCount * pageSize,    // Size of allocation
            MEM_RESERVE,     // Only reserve pages, do not pin physical swap space
            PAGE_NOACCESS)}; // No access for uncommitted memory

        if (!baseAddress)
        {
            throw PageError{};
        }

        return baseAddress;
    }

    void commitPages(void * const reservedPage, const size_t pageCount)
    {
        if (!reservedPage || !VirtualAlloc(
            reservedPage,    // Base page address
            pageCount * pageSize,    // Size of commit
            MEM_COMMIT,      // Actually pin the pages in physical swap space
            PAGE_READWRITE)) // Grant read/write access
        {
            throw PageError{};
        }
    }
}

