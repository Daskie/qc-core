#include <qc-core/paging.hpp>

#include <atomic>
#include <bit>

#ifdef QC_MSVC
    #include <qc-core/windows-includes-pre.hpp>
    #include <windows.h>
    #include <qc-core/windows-includes-post.hpp>
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
                    ABORT_IF(pageSize < sSysInfo.dwPageSize || pageSize != sSysInfo.dwAllocationGranularity);
                #else
                    ABORT_IF(pageSize < u64(::getpagesize()));
                #endif
            }
        }

        void * _mapPages(const u64 n, const bool commit)
        {
            _verifyPageInfo();

            if (!n)
            {
                return nullptr;
            }

            #ifdef QC_MSVC
                void * const baseAddress{::VirtualAlloc(
                    nullptr, // System selects base address
                    n * pageSize,
                    commit ? (u32(MEM_RESERVE) | u32(MEM_COMMIT)) : u32(MEM_RESERVE),
                    commit ? u32(PAGE_READWRITE) : u32(PAGE_NOACCESS))};
                ABORT_IF(!baseAddress);
                return baseAddress;
            #else
                // Overallocate to match Window's 64k granularity
                const u64 allocatedSize{n * pageSize + pageSize};
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
                std::byte * const alignedStart{std::bit_cast<std::byte *>((std::bit_cast<u64>(unalignedStart) + (pageSize - 1u)) & ~u64{pageSize - 1u})};
                std::byte * const alignedEnd{alignedStart + n * pageSize};
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

    void * allocatePages(const u64 n)
    {
        return _mapPages(n, true);
    }

    void * reservePages(const u64 n)
    {
        return _mapPages(n, false);
    }

    void commitPages(void * const start, const u64 n)
    {
        if (!start || !n)
        {
            return;
        }

        // Ensure pointer is on page boundary
        ABORT_IF(std::bit_cast<u64>(start) & (pageSize - 1u));

        #ifdef QC_MSVC
            ABORT_IF(!::VirtualAlloc(
                start, // Base page address
                n * pageSize, // Size of commit
                MEM_COMMIT, // Actually pin the pages in physical swap space
                PAGE_READWRITE)); // Grant read/write access
        #else
            // Make already mapped memory read/writable
            ABORT_IF(::mprotect(start, n * pageSize, PROT_READ | PROT_WRITE));
        #endif
    }

    void decommitPages(void * const start, const u64 n)
    {
        if (!start || !n)
        {
            return;
        }

        // Ensure pointer is on page boundary
        ABORT_IF(std::bit_cast<u64>(start) & (pageSize - 1u));

        #ifdef QC_MSVC
            ABORT_IF(!::VirtualFree(start, n * pageSize, MEM_DECOMMIT));
        #else
            // Make already mapped memory unread/unwritable
            ABORT_IF(::mprotect(start, n * pageSize, PROT_NONE));
        #endif
    }

    void freePages(void * const start, const u64 n)
    {
        if (!start || !n)
        {
            return;
        }

        // Ensure pointer is on page boundary
        ABORT_IF(std::bit_cast<u64>(start) & (pageSize - 1u));

        #ifdef QC_MSVC
            ABORT_IF(!::VirtualFree(start, 0u, MEM_RELEASE));
        #else
            ABORT_IF(::munmap(start, n * pageSize));
        #endif
    }
}
