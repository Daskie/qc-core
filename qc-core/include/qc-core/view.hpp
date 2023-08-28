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

        finline View() = default;

        finline View(T * const data_, const u32 size_) : data{data_}, size{size_} { ASSERT(data_ || !size_); }

        finline View(T * const first, T * const last) : data{first}, size{u32(last - first)} { ASSERT(u64(last - first) <= std::numeric_limits<u32>::max()); }

        template <u64 n> finline View(T (&arr)[n]) : data{arr}, size{n} {}

        finline View(const View & other) = default;
        finline View(const View<std::remove_const_t<T>> & other) requires std::is_const_v<T> : data{other.data}, size{other.size} {}

        finline View & operator=(const View &) = default;

        nodisc finline explicit operator bool() const { return size; }

        nodisc View view(const u32 offset) const { ASSERT(offset <= size); return {data + offset, size - offset}; }
        nodisc View view(const u32 offset, const u32 n) const { ASSERT(offset + n <= size); return {data + offset, n}; }

        nodisc View viewFirst(const u32 n) const { ASSERT(n <= size); return {data, n}; }

        nodisc View viewLast(const u32 n) const { ASSERT(n <= size); return {data + size - n, n}; }

        nodisc finline View<const std::byte> bytes() const { return {reinterpret_cast<const std::byte *>(data), size * u32(sizeof(T))}; }

        nodisc finline T & operator[](const u32 i) const { ASSERT(i < size); return data[i]; }

        nodisc finline T & front() const { return *data; }

        nodisc finline T & back() const { return data[size - 1u]; }

        nodisc finline T * begin() const { return data; }

        nodisc finline T * end() const { return data + size; }

        nodisc finline bool operator==(const View &) const = default;
    };

    template <typename T> using CView = View<const T>;

    using StringView = View<char>;
    using StringCView = View<const char>;
}
