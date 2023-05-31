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
        std::atomic_flag _pageInfoChecked{};

        void _verifyPageInfo()
        {
            // Only do this once
            if (!_pageInfoChecked.test_and_set()) [[unlikely]]
            {
                #ifdef QC_MSVC
                    SYSTEM_INFO sSysInfo;
                    ::GetSystemInfo(&sSysInfo);
                    ABORT_IF(pageSize != sSysInfo.dwPageSize || pageGranularity != sSysInfo.dwAllocationGranularity);
                #else
                    ABORT_IF(pageSize != ::getpagesize());
                #endif
            }
        }

        void * _mapPages(const u64 pageN, const bool commit)
        {
            _verifyPageInfo();

            if (!pageN)
            {
                return nullptr;
            }

            #ifdef QC_MSVC
                void * const baseAddress{::VirtualAlloc(
                    nullptr, // System selects base address
                    pageN * pageSize,
                    commit ? (u32(MEM_RESERVE) | u32(MEM_COMMIT)) : u32(MEM_RESERVE),
                    commit ? u32(PAGE_READWRITE) : u32(PAGE_NOACCESS))};
                ABORT_IF(!baseAddress);
                return baseAddress;
            #else
                // Overallocate to match Window's 64k granularity
                const u64 allocatedSize{pageN * pageSize + pageGranularity - pageSize};
                void * const baseAddress{::mmap(
                    nullptr, // System selects base address
                    allocatedSize, // Size of allocation
                    commit ? (PROT_READ | PROT_WRITE) : PROT_NONE,
                    MAP_PRIVATE | MAP_ANONYMOUS, // Mapping private memory, not a file
                    -1, // Anonymous mapping must use -1 for file descriptor
                    0)}; // No offset
                ABORT_IF(baseAddress == MAP_FAILED);

                // Determine excess
                std::byte * const unalignedStart{static_cast<std::byte *>(baseAddress)};
                std::byte * const alignedStart{std::bit_cast<std::byte *>((std::bit_cast<u64>(unalignedStart) + (pageGranularity - 1u)) & ~u64{pageGranularity - 1u})};
                std::byte * const alignedEnd{alignedStart + pageN * pageSize};
                std::byte * const unalignedEnd{unalignedStart + allocatedSize};

                // Unmap excess
                if (alignedStart != unalignedStart)
                {
                    ABORT_IF(::munmap(unalignedStart, u64(alignedStart - unalignedStart)));
                }
                if (alignedEnd != unalignedEnd)
                {
                    ABORT_IF(::munmap(alignedEnd, u64(unalignedEnd - alignedEnd)));
                }

                return alignedStart;
            #endif
        }
    }

    void * allocatePages(const u64 pageN)
    {
        return _mapPages(pageN, true);
    }

    void * reservePages(const u64 pageN)
    {
        return _mapPages(pageN, false);
    }

    void commitPages(void * const pageStart, const u64 pageN)
    {
        if (!pageStart || !pageN)
        {
            return;
        }

        // Ensure pointer is on page boundary
        ABORT_IF(std::bit_cast<u64>(pageStart) & (pageSize - 1u));

        #ifdef QC_MSVC
            ABORT_IF(!::VirtualAlloc(
                pageStart, // Base page address
                pageN * pageSize, // Size of commit
                MEM_COMMIT, // Actually pin the pages in physical swap space
                PAGE_READWRITE)); // Grant read/write access
        #else
            // Make already mapped memory read/writable
            ABORT_IF(::mprotect(pageStart, pageN * pageSize, PROT_READ | PROT_WRITE));
        #endif
    }

    void decommitPages(void * const pageStart, const u64 pageN)
    {
        if (!pageStart || !pageN)
        {
            return;
        }

        // Ensure pointer is on page boundary
        ABORT_IF(std::bit_cast<u64>(pageStart) & (pageSize - 1u));

        #ifdef QC_MSVC
            ABORT_IF(!::VirtualFree(pageStart, pageN * pageSize, MEM_DECOMMIT));
        #else
            // Make already mapped memory unread/unwritable
            ABORT_IF(::mprotect(pageStart, pageN * pageSize, PROT_NONE));
        #endif
    }

    void freePages(void * const pages, const u64 pageN)
    {
        if (!pages || !pageN)
        {
            return;
        }

        // Ensure pointer is on page boundary
        ABORT_IF(std::bit_cast<u64>(pages) & (pageSize - 1u));

        #ifdef QC_MSVC
            ABORT_IF(!::VirtualFree(pages, 0u, MEM_RELEASE));
        #else
            ABORT_IF(::munmap(pages, pageN * pageSize));
        #endif
    }
}
