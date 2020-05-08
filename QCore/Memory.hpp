#pragma once

#include <cstddef>

namespace qc {

    template <typename T> class RecordAllocator {

        template <typename> friend class RecordAllocator;

        public:

        using value_type = T;
        using size_type = size_t;
        using difference_type = std::ptrdiff_t;
        using propagate_on_container_copy_assignment = std::true_type;
        using propagate_on_container_move_assignment = std::true_type;
        using propagate_on_container_swap = std::true_type;
        using is_always_equal = std::true_type;

        constexpr RecordAllocator() noexcept :
            m_current(),
            m_total(),
            m_allocations(),
            m_deallocations()
        {}

        constexpr RecordAllocator(const RecordAllocator & other) noexcept = default;

        template <typename U>
        constexpr RecordAllocator(const RecordAllocator<U> & other) noexcept :
            m_current(other.m_current),
            m_total(other.m_total),
            m_allocations(other.m_allocations),
            m_deallocations(other.m_deallocations)
        {}

        T * allocate(size_t n) {
            size_t bytes(n * sizeof(T));
            m_current += bytes;
            m_total += bytes;
            ++m_allocations;
            return reinterpret_cast<T *>(::operator new(bytes));
        }

        void deallocate(T * p, size_t n) {
            size_t bytes(n * sizeof(T));
            m_current -= bytes;
            ++m_deallocations;
            ::operator delete(p);
        }

        size_t current() const { return m_current; }
        size_t total() const { return m_total; }
        size_t allocations() const { return m_allocations; }
        size_t deallocations() const { return m_deallocations; }

        private:

        size_t m_current;
        size_t m_total;
        size_t m_allocations;
        size_t m_deallocations;

    };

    template <typename T1, typename T2>
    inline bool operator==(const RecordAllocator<T1> & a1, const RecordAllocator<T2> & a2) noexcept {
        return true;
    }

    template <typename T1, typename T2>
    inline bool operator!=(const RecordAllocator<T1> & a1, const RecordAllocator<T2> & a2) noexcept {
        return false;
    }

}
