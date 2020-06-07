#pragma once

#include <cstddef>

namespace qc::core {

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
            _current(),
            _total(),
            _allocations(),
            _deallocations()
        {}

        constexpr RecordAllocator(const RecordAllocator & other) noexcept = default;

        template <typename U>
        constexpr RecordAllocator(const RecordAllocator<U> & other) noexcept :
            _current(other._current),
            _total(other._total),
            _allocations(other._allocations),
            _deallocations(other._deallocations)
        {}

        T * allocate(const size_t n) {
            const size_t bytes(n * sizeof(T));
            _current += bytes;
            _total += bytes;
            ++_allocations;
            return reinterpret_cast<T *>(::operator new(bytes));
        }

        void deallocate(T * const p, const size_t n) {
            const size_t bytes(n * sizeof(T));
            _current -= bytes;
            ++_deallocations;
            ::operator delete(p);
        }

        size_t current() const { return _current; }
        size_t total() const { return _total; }
        size_t allocations() const { return _allocations; }
        size_t deallocations() const { return _deallocations; }

        private:

        size_t _current;
        size_t _total;
        size_t _allocations;
        size_t _deallocations;

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
