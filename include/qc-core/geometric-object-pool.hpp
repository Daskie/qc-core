#pragma once

#include <qc-core/geometric-mono-allocator.hpp>

namespace qc
{
    ///
    /// Simple, fast single-element allocator whose backing memory capacity is increasing powers of two
    ///
    /// Example growth over time:
    ///   Capacity  2: AA -- ---- --------
    ///   Capacity  4: AA BB ---- --------
    ///   Capacity  8: AA BB CCCC --------
    ///   Capacity 16: AA BB CCCC DDDDDDDD
    ///
    template <typename T>
    class GeometricObjectPool
    {
        using _Allocator = GeometricMonoAllocator<sizeof(T), alignof(T)>;

        public: //--------------------------------------------------------------

        inline static constexpr size_t defaultInitialCapacity{_Allocator::defaultInitialCapacity};

        GeometricObjectPool() noexcept = default;
        explicit GeometricObjectPool(size_t initialCapacity) noexcept;

        GeometricObjectPool(const GeometricObjectPool &) = delete;
        GeometricObjectPool(GeometricObjectPool && other) noexcept = default;

        GeometricObjectPool & operator=(const GeometricObjectPool &) = delete;
        GeometricObjectPool & operator=(GeometricObjectPool && other) noexcept = default;

        ~GeometricObjectPool() noexcept = default;

        void reserve(size_t capacity);

        template <typename... Args> [[nodiscard]] T * new_(Args &&... args);

        void delete_(T * v) noexcept(qc::debug);

        size_t capacity() const noexcept { return _allocator.capacity(); }

        size_t count() const noexcept { return _allocator.count(); }

        private: //-------------------------------------------------------------

        _Allocator _allocator{};
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    GeometricObjectPool<T>::GeometricObjectPool(const size_t initialCapacity) noexcept :
        _allocator{initialCapacity}
    {}

    template <typename T>
    void GeometricObjectPool<T>::reserve(const size_t capacity)
    {
        _allocator.reserve(capacity);
    }

    template <typename T>
    template <typename... Args>
    T * GeometricObjectPool<T>::new_(Args &&... args)
    {
        return new (_allocator.allocate()) T{std::forward<Args>(args)...};
    }

    template <typename T>
    void GeometricObjectPool<T>::delete_(T * const v) noexcept(qc::debug)
    {
        v->~T();
        _allocator.deallocate(v);
    }
}
