#pragma once

#include <qc-core/core.hpp>

namespace qc
{
    template <typename T>
    class View
    {
      public:

        T * data{};
        u32 size{};

        forceinline View() = default;

        forceinline View(T * const data_, const u32 size_) : data{data_}, size{size_} { assert(data_ || !size_); }

        forceinline View(T * const first, T * const last) : data{first}, size{u32(last - first)} { assert(u64(last - first) <= std::numeric_limits<u32>::max()); }

        template <u64 n> forceinline View(T (&arr)[n]) : data{arr}, size{n} {}

        forceinline View(const View &) = default;
        forceinline View(const View<std::remove_const_t<T>> & other) requires std::is_const_v<T> : data{other.data}, size{other.size} {}

        nodisc forceinline explicit operator bool() const { return size; }

        nodisc View view(const u32 offset) const { assert(offset <= size); return {data + offset, size - offset}; }
        nodisc View view(const u32 offset, const u32 n) const { assert(offset + n <= size); return {data + offset, n}; }

        nodisc View viewFirst(const u32 n) const { assert(n <= size); return {data, n}; }

        nodisc View viewLast(const u32 n) const { assert(n <= size); return {data + size - n, n}; }

        nodisc forceinline T & operator[](const u32 i) const { assert(i < size); return data[i]; }

        nodisc forceinline T & front() const { return *data; }

        nodisc forceinline T & back() const { return data[size - 1u]; }

        nodisc forceinline T * begin() const { return data; }

        nodisc forceinline T * end() const { return data + size; }

        nodisc forceinline bool operator==(const View &) const = default;
    };

    template <typename T> using CView = View<const T>;

    using StringView = View<char>;
    using StringCView = View<const char>;
}
