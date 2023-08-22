#pragma once

#include <qc-core/list.hpp>

namespace qc
{
    ///
    /// ...
    /// Properties:
    ///   Insertion: O(1)
    ///   Erasure: O(1)
    ///   Access: O(1)
    ///   Reference stable: No
    ///   Index stable: No
    ///   Order stable: No
    ///   Contiguous elements: Yes
    ///
    template <typename T>
    class Lot
    {
      public:

        static_assert(std::is_move_constructible_v<T>);

        using value_type = T;
        using reference = T &;
        using size_type = u32;
        using difference_type = s64;
        using const_reference = const T &;
        using pointer = T *;
        using const_pointer = const T *;
        using iterator = T *;
        using const_iterator = const T *;

        Lot() = default;
        forceinline explicit Lot(const u32 n) : _list(n) {}
        forceinline Lot(const u32 n, const T & v) : _list(n, v) {}
        template <typename It> forceinline Lot(const It first, const It last) : _list(first, last) {}
        forceinline Lot(const std::initializer_list<T> vs) : _list(vs) {}
        forceinline explicit Lot(const CView<T> vs) : _list(vs) {}

        Lot(const Lot &) = delete;
        Lot(Lot &&) = default;

        Lot & operator=(const Lot &) = delete;
        Lot & operator=(Lot &&) = default;

        forceinline Lot & operator=(const std::initializer_list<T> vs) { _list = vs; return *this; }
        forceinline Lot & operator=(const CView<T> vs) { _list = vs; return *this; }

        ~Lot() = default;

        nodisc forceinline explicit operator bool() const { return bool(_list); }

        nodisc forceinline operator View<T>() { return _list; }
        nodisc forceinline operator CView<T>() const { return _list; }

        forceinline void assign(const u32 n, const T & v) { _list.assign(n, v); }
        template <typename It> forceinline void assign(const It first, const It last) { _list.assign(first, last); }

        forceinline void fill(const T & v) { _list.fill(v); }

        forceinline void reserve(const u32 capacity) { _list.reserve(capacity); }

        forceinline void resize(const u32 n) { _list.resize(n); }
        forceinline void resize(const u32 n, const T & v) { _list.resize(n, v); }

        forceinline void shrink() { _list.shrink(); }

        forceinline void clear() { _list.clear(); }

        forceinline T & push(const T & v) { return _list.push(v); }
        forceinline T & push(T && v) { return _list.push(std::move(v)); }

        template <typename... Args> forceinline T & empush(Args &&... args) { return _list.empush(std::forward<Args>(args)...); }

        forceinline T & bump() { return _list.bump(); }
        forceinline View<T> bump(const u32 n) { return _list.bump(n); }

        T * erase(T * pos);
        u32 erase(const T & v);

        template <typename Pred> u32 eraseIf(Pred && pred);

        forceinline T * find(const T & v) { return _list.find(v); }
        forceinline const T * find(const T & v) const { return _list.find(v); }

        template <typename Pred> forceinline T * findIf(Pred && pred) { return _list.findIf(std::forward<Pred>(pred)); }
        template <typename Pred> forceinline const T * findIf(Pred && pred) const { return _list.findIf(std::forward<Pred>(pred)); }

        forceinline u32 count(const T & v) const { return _list.count(v); }

        template <typename Pred> forceinline u32 countIf(Pred && pred) const { return _list.countIf(std::forward<Pred>(pred)); }

        forceinline bool contains(const T & v) const { return _list.contains(v); }

        template <typename Pred> forceinline bool containsIf(Pred && pred) const { return _list.containsIf(std::forward<Pred>(pred)); }

        nodisc forceinline T & operator[](const u32 i) { return _list[i]; }
        nodisc forceinline const T & operator[](const u32 i) const { return _list[i]; }

        nodisc forceinline u32 capacity() const { return _list.capacity(); }

        nodisc forceinline u32 size() const { return _list.size(); }

        nodisc forceinline bool empty() const { return _list.empty(); }

        nodisc forceinline T * data() { return _list.data(); }
        nodisc forceinline const T * data() const { return _list.data(); }

        nodisc forceinline View<T> span() { return _list.span(); }
        nodisc forceinline CView<T> span() const { return _list.span(); }
        nodisc forceinline CView<T> cspan() const { return _list.cspan(); }

        nodisc forceinline T * begin() { return _list.begin(); }
        nodisc forceinline const T * begin() const { return _list.begin(); }
        nodisc forceinline const T * cbegin() const { return _list.cbegin(); }

        nodisc forceinline T * end() { return _list.end(); }
        nodisc forceinline const T * end() const { return _list.end(); }
        nodisc forceinline const T * cend() const { return _list.cend(); }

        nodisc bool operator==(const Lot &) const = default;
        nodisc forceinline bool operator==(const std::initializer_list<T> vs) const { return _list == vs; }

      private:

        List<T> _list{};
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    forceinline T * Lot<T>::erase(T * const pos)
    {
        _list.pop(*pos);
        return pos;
    }

    template <typename T>
    forceinline u32 Lot<T>::erase(const T & v)
    {
        return eraseIf([&v](const T & a) { return a == v; });
    }

    template <typename T>
    template <typename Pred>
    u32 Lot<T>::eraseIf(Pred && pred)
    {
        u32 n{0u};

        for (T * pos{begin()}, * end{this->end()}; pos < end; ++pos)
        {
            if (pred(*pos))
            {
                --end;
                *pos = std::move(*end);
                --pos;
                ++n;
            }
        }

        _list.pop(n);

        return n;
    }
}
