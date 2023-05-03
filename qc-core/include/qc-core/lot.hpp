#pragma once

///
/// Insertion: O(1)
/// Erasure: O(1)
/// Access: O(1)
/// Reference stable: No
/// Index stable: No
/// Order stable: No
/// Contiguous elements: Yes
///

#include <qc-core/list.hpp>

namespace qc
{
    template <typename T>
    class Lot
    {
      public:

        static_assert(std::is_move_constructible_v<T>);

        using value_type = T;
        using reference = T &;
        using size_type = u64;
        using difference_type = s64;
        using const_reference = const T &;
        using pointer = T *;
        using const_pointer = const T *;
        using iterator = T *;
        using const_iterator = const T *;

        static constexpr u64 max_size() { return List<T>::max_size(); }

        Lot() = default;
        explicit Lot(u64 n);
        Lot(u64 n, const T & v);
        template <typename It> Lot(It first, It last);
        Lot(std::initializer_list<T> vs);
        explicit Lot(std::span<const T> vs);

        Lot(const Lot &) = delete;
        Lot(Lot &&) = default;

        Lot & operator=(const Lot &) = delete;
        Lot & operator=(Lot &&) = default;

        Lot & operator=(std::initializer_list<T> vs);
        Lot & operator=(std::span<const T> vs);

        ~Lot() = default;

        void assign(u64 n, const T & v);
        template <typename It> void assign(It first, It last);

        void reserve(u64 capacity);

        void resize(u64 n);
        void resize(u64 n, const T & v);

        void shrink();

        void clear();

        template <typename... Args> T & push(Args &&... args);

        T & bump() requires std::is_trivially_default_constructible_v<T>;
        std::span<T> bump(u64 n) requires std::is_trivially_default_constructible_v<T>;

        T * erase(T * pos);
        u64 erase(const T & v);

        template <typename Pred> u64 eraseIf(Pred && pred);

        T * find(const T & v);
        const T * find(const T & v) const;

        template <typename Pred> T * findIf(Pred && pred);
        template <typename Pred> const T * findIf(Pred && pred) const;

        u64 count(const T & v) const;

        template <typename Pred> u64 countIf(Pred && pred) const;

        bool contains(const T & v) const;

        template <typename Pred> bool containsIf(Pred && pred) const;

        nodisc u64 capacity() const;

        nodisc u64 size() const;

        nodisc bool empty() const;

        nodisc T * data();
        nodisc const T * data() const;

        nodisc std::span<T> span();
        nodisc std::span<const T> span() const;
        nodisc std::span<const T> cspan() const;

        nodisc T * begin();
        nodisc const T * begin() const;
        nodisc const T * cbegin() const;

        nodisc T * end();
        nodisc const T * end() const;
        nodisc const T * cend() const;

        nodisc bool operator==(const Lot &) const = default;
        nodisc bool operator==(std::initializer_list<T> vs) const;

      private:

        List<T> _list{};
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    forceinline Lot<T>::Lot(const u64 n) :
        _list(n)
    {}

    template <typename T>
    forceinline Lot<T>::Lot(const u64 n, const T & v) :
        _list(n, v)
    {}

    template <typename T>
    template <typename It>
    forceinline Lot<T>::Lot(const It first, const It last) :
        _list(first, last)
    {}

    template <typename T>
    forceinline Lot<T>::Lot(const std::initializer_list<T> vs) :
        _list(vs)
    {}

    template <typename T>
    forceinline Lot<T>::Lot(const std::span<const T> vs) :
        _list(vs)
    {}

    template <typename T>
    forceinline Lot<T> & Lot<T>::operator=(const std::initializer_list<T> vs)
    {
        _list = vs;
        return *this;
    }

    template <typename T>
    forceinline Lot<T> & Lot<T>::operator=(const std::span<const T> vs)
    {
        _list = vs;
        return *this;
    }

    template <typename T>
    forceinline void Lot<T>::assign(const u64 n, const T & v)
    {
        _list.assign(n, v);
    }

    template <typename T>
    template <typename It>
    forceinline void Lot<T>::assign(const It first, const It last)
    {
        _list.assign(first, last);
    }

    template <typename T>
    forceinline void Lot<T>::reserve(const u64 capacity)
    {
        _list.reserve(capacity);
    }

    template <typename T>
    forceinline void Lot<T>::resize(const u64 n)
    {
        _list.resize(n);
    }

    template <typename T>
    forceinline void Lot<T>::resize(const u64 n, const T & v)
    {
        _list.resize(n, v);
    }

    template <typename T>
    forceinline void Lot<T>::shrink()
    {
        _list.shrink();
    }

    template <typename T>
    forceinline void Lot<T>::clear()
    {
        _list.clear();
    }

    template <typename T>
    template <typename... Args>
    forceinline T & Lot<T>::push(Args &&... args)
    {
        return _list.push(std::forward<Args>(args)...);
    }

    template <typename T>
    forceinline T & Lot<T>::bump() requires std::is_trivially_default_constructible_v<T>
    {
        return _list.bump();
    }

    template <typename T>
    forceinline std::span<T> Lot<T>::bump(const u64 n) requires std::is_trivially_default_constructible_v<T>
    {
        return _list.bump(n);
    }

    template <typename T>
    forceinline T * Lot<T>::erase(T * const pos)
    {
        _list.pop(*pos);
        return pos;
    }

    template <typename T>
    forceinline u64 Lot<T>::erase(const T & v)
    {
        return eraseIf([&v](const T & a) { return a == v; });
    }

    template <typename T>
    template <typename Pred>
    forceinline u64 Lot<T>::eraseIf(Pred && pred)
    {
        u64 n{0u};

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

    template <typename T>
    forceinline T * Lot<T>::find(const T & v)
    {
        return _list.find(v);
    }

    template <typename T>
    forceinline const T * Lot<T>::find(const T & v) const
    {
        return _list.find(v);
    }

    template <typename T>
    template <typename Pred>
    forceinline T * Lot<T>::findIf(Pred && pred)
    {
        return _list.findIf(std::forward<Pred>(pred));
    }

    template <typename T>
    template <typename Pred>
    forceinline const T * Lot<T>::findIf(Pred && pred) const
    {
        return _list.findIf(std::forward<Pred>(pred));
    }

    template <typename T>
    forceinline u64 Lot<T>::count(const T & v) const
    {
        return _list.count(v);
    }

    template <typename T>
    template <typename Pred>
    forceinline u64 Lot<T>::countIf(Pred && pred) const
    {
        return _list.countIf(std::forward<Pred>(pred));
    }

    template <typename T>
    forceinline bool Lot<T>::contains(const T & v) const
    {
        return _list.contains(v);
    }

    template <typename T>
    template <typename Pred>
    forceinline bool Lot<T>::containsIf(Pred && pred) const
    {
        return _list.countIf(std::forward<Pred>(pred));
    }

    template <typename T>
    forceinline u64 Lot<T>::capacity() const
    {
        return _list.capacity();
    }

    template <typename T>
    forceinline u64 Lot<T>::size() const
    {
        return _list.size();
    }

    template <typename T>
    forceinline bool Lot<T>::empty() const
    {
        return _list.empty();
    }

    template <typename T>
    forceinline T * Lot<T>::data()
    {
        return _list.data();
    }

    template <typename T>
    forceinline const T * Lot<T>::data() const
    {
        return _list.data();
    }

    template <typename T>
    forceinline std::span<T> Lot<T>::span()
    {
        return _list.span();
    }

    template <typename T>
    forceinline std::span<const T> Lot<T>::span() const
    {
        return _list.span();
    }

    template <typename T>
    forceinline std::span<const T> Lot<T>::cspan() const
    {
        return span();
    }

    template <typename T>
    forceinline T * Lot<T>::begin()
    {
        return _list.begin();
    }

    template <typename T>
    forceinline const T * Lot<T>::begin() const
    {
        return _list.begin();
    }

    template <typename T>
    forceinline const T * Lot<T>::cbegin() const
    {
        return begin();
    }

    template <typename T>
    forceinline T * Lot<T>::end()
    {
        return _list.end();
    }

    template <typename T>
    forceinline const T * Lot<T>::end() const
    {
        return _list.end();
    }

    template <typename T>
    forceinline const T * Lot<T>::cend() const
    {
        return end();
    }

    template <typename T>
    inline bool Lot<T>::operator==(const std::initializer_list<T> vs) const
    {
        return _list == vs;
    }
}
