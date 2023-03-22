#include <qc-core/paging.hpp>

#include <atomic>
#include <bit>

#ifdef QC_MSVC
    #pragma warning(push)
    #pragma warning(disable: 5039)
    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX
    #include <windows.h>
    #pragma warning(pop)
#else
    #include <sys/mman.h>
    #include <unistd.h>
#endif

namespace qc
{
    namespace
    {
        std::atomic_flag _pageSizeChecked{};

        u64 _getPageSize()
        {
            #ifdef QC_MSVC
                SYSTEM_INFO sSysInfo;
                ::GetSystemInfo(&sSysInfo);
                return sSysInfo.dwPageSize;
            #else
                return u64(::getpagesize());
            #endif
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

    void * allocatePages(const u64 pageCount)
    {
        _verifyPageSize();

        if (!pageCount)
        {
            return nullptr;
        }

        void * baseAddress;
        #ifdef QC_MSVC
            baseAddress = ::VirtualAlloc(
                nullptr, // System selects base address
                pageCount * pageSize, // Size of allocation
                MEM_RESERVE | MEM_COMMIT, // Immediately pin pages in physical swap memory
                PAGE_READWRITE); // Grant read/write access
        #else
            baseAddress = ::mmap(
                nullptr, // System selects base address
                pageCount * pageSize,  // Size of allocation
                PROT_READ | PROT_WRITE, // Allow memory to be used immediately
                MAP_PRIVATE | MAP_ANONYMOUS, // Mapping private memory, not a file
                -1, // Anonymous mapping must use -1 for file descriptor
                0); // No offset
            ABORT_IF(baseAddress == MAP_FAILED);
        #endif

        ABORT_IF(!baseAddress);

        return baseAddress;
    }

    void * reservePages(const u64 pageCount)
    {
        _verifyPageSize();

        if (!pageCount)
        {
            return nullptr;
        }

        void * baseAddress;
        #ifdef QC_MSVC
            baseAddress = ::VirtualAlloc(
                nullptr, // System selects base address
                pageCount * pageSize, // Size of allocation
                MEM_RESERVE, // Only reserve pages, do not pin physical swap space
                PAGE_NOACCESS); // No access for uncommitted memory
        #else
            baseAddress = ::mmap(
                nullptr, // System selects base address
                pageCount * pageSize, // Size of allocation
                PROT_NONE, // Prevents the memory from being used until its been committed
                MAP_PRIVATE | MAP_ANONYMOUS, // Mapping private memory, not a file
                -1, // Anonymous mapping must use -1 for file descriptor
                0); // No offset
            ABORT_IF(baseAddress == MAP_FAILED);
        #endif

        ABORT_IF(!baseAddress);

        return baseAddress;
    }

    void commitPages(void * const pageStart, const u64 pageCount)
    {
        if (!pageStart || !pageCount)
        {
            return;
        }

        // Ensure pointer is on page boundary
        ABORT_IF(std::bit_cast<u64>(pageStart) & (pageSize - 1u));

        #ifdef QC_MSVC
            ABORT_IF(!::VirtualAlloc(
                pageStart, // Base page address
                pageCount * pageSize, // Size of commit
                MEM_COMMIT, // Actually pin the pages in physical swap space
                PAGE_READWRITE)); // Grant read/write access
        #else
            // Make already mapped memory read/writable
            ABORT_IF(::mprotect(pageStart, pageCount * pageSize, PROT_READ | PROT_WRITE));
        #endif
    }

    void decommitPages(void * const pageStart, const u64 pageCount)
    {
        if (!pageStart || !pageCount)
        {
            return;
        }

        // Ensure pointer is on page boundary
        ABORT_IF(std::bit_cast<u64>(pageStart) & (pageSize - 1u));

        #ifdef QC_MSVC
            ABORT_IF(!::VirtualFree(pageStart, pageCount * pageSize, MEM_DECOMMIT));
        #else
            // Make already mapped memory unread/unwritable
            ABORT_IF(::mprotect(pageStart, pageCount * pageSize, PROT_NONE));
        #endif
    }

    void freePages(void * const pages, const u64 pageCount)
    {
        if (!pages || !pageCount)
        {
            return;
        }

        // Ensure pointer is on page boundary
        ABORT_IF(std::bit_cast<u64>(pages) & (pageSize - 1u));

        #ifdef QC_MSVC
            ABORT_IF(!::VirtualFree(pages, 0u, MEM_RELEASE));
        #else
            ABORT_IF(::munmap(pages, pageCount * pageSize));
        #endif
    }
}
