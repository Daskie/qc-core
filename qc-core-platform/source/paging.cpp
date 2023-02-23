#include <qc-core/paging.hpp>

#include <atomic>

#ifdef WIN32
    #pragma warning(push)
    #pragma warning(disable: 5039)
    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX
    #include <windows.h>
    #pragma warning(pop)
#else
    #error "Platform not yet supported"
#endif

namespace qc
{
    namespace
    {
        std::atomic_flag _pageSizeChecked{};

        unat _getPageSize()
        {
            SYSTEM_INFO sSysInfo;
            GetSystemInfo(&sSysInfo);
            return sSysInfo.dwPageSize;
        }

        void _verifyPageSize()
        {
            // Only do this once
            if (!_pageSizeChecked.test_and_set()) [[unlikely]]
            {
                ABORT_IF(pageSize != _getPageSize());
            }
        }
    }

    void * allocatePages(const unat pageCount)
    {
        _verifyPageSize();

        if (!pageCount)
        {
            return nullptr;
        }

        void * const baseAddress{VirtualAlloc(
            nullptr,                  // System selects base address
            pageCount * pageSize,     // Size of allocation
            MEM_RESERVE | MEM_COMMIT, // Immediately pin pages in physical swap memory
            PAGE_READWRITE)};         // Grant read/write access

        ABORT_IF(!baseAddress);

        return baseAddress;
    }

    void * reservePages(const unat pageCount)
    {
        _verifyPageSize();

        if (!pageCount)
        {
            return nullptr;
        }

        void * const baseAddress{VirtualAlloc(
            nullptr,              // System selects base address
            pageCount * pageSize, // Size of allocation
            MEM_RESERVE,          // Only reserve pages, do not pin physical swap space
            PAGE_NOACCESS)};      // No access for uncommitted memory

        ABORT_IF(!baseAddress);

        return baseAddress;
    }

    void commitPages(void * const pageStart, const unat pageCount)
    {
        if (!pageStart || !pageCount)
        {
            return;
        }

        // Ensure pointer is on page boundary
        ABORT_IF(std::bit_cast<unat>(pageStart) & (pageSize - 1u));

        ABORT_IF(!VirtualAlloc(
            pageStart,            // Base page address
            pageCount * pageSize, // Size of commit
            MEM_COMMIT,           // Actually pin the pages in physical swap space
            PAGE_READWRITE));     // Grant read/write access
    }

    void decommitPages(void * const pageStart, const size_t pageCount)
    {
        if (!pageStart || !pageCount)
        {
            return;
        }

        // Ensure pointer is on page boundary
        ABORT_IF(std::bit_cast<unat>(pageStart) & (pageSize - 1u));

        ABORT_IF(!VirtualFree(
            pageStart,            // Base page address
            pageCount * pageSize, // Size of commit
            MEM_DECOMMIT));       // Actually pin the pages in physical swap space
    }

    void freePages(void * const pages)
    {
        if (!pages)
        {
            return;
        }

        // Ensure pointer is on page boundary
        ABORT_IF(std::bit_cast<unat>(pages) & (pageSize - 1u));

        ABORT_IF(!VirtualFree(
            pages,         // Base page address
            0u,            // Size of commit
            MEM_RELEASE)); // Actually pin the pages in physical swap space
    }
}
