#pragma once

#include <iterator>

#include <qc-core/bank.hpp>

namespace qc
{
    ///
    /// The most significant differences between this and `std::deque`:
    ///   1. This does not provide reference stability. References and iterators are invalidated when the capacity grows
    ///   2. This DOES provide positional stability. That is, a `DequePos` remains valid in all cases
    ///
    /// Essentially, this allows you to `pop` a middle element without invalidating other elements, at the cost of
    ///   reference stability if only working with front/back operations
    ///
    template <typename T>
    class SemiStableDeque
    {
        static_assert(std::is_move_constructible_v<T>);
        static_assert(std::is_move_assignable_v<T>);

        template <bool constant, bool reverse> class _Iterator;

      public:

        using iterator = _Iterator<false, false>;
        using const_iterator = _Iterator<true, false>;
        using reverse_iterator = _Iterator<false, true>;
        using const_reverse_iterator = _Iterator<true, true>;

        SemiStableDeque() = default;

        SemiStableDeque(const SemiStableDeque &) = delete;
        SemiStableDeque(SemiStableDeque && other);

        SemiStableDeque & operator=(const SemiStableDeque &) = delete;
        SemiStableDeque & operator=(SemiStableDeque && other);

        ~SemiStableDeque();

        nodisc forceinline explicit operator bool() const { return bool(_elements); }

        struct NewElement { T & v; u32 i; };

        NewElement push_back(const T & v);
        NewElement push_back(T && v);

        NewElement push_front(const T & v);
        NewElement push_front(T && v);

        template <typename... Args> NewElement emplace_back(Args &&... args);

        template <typename... Args> NewElement emplace_front(Args &&... args);

        void pop_back();

        void pop_front();

        void pop(u32 pos);
        void pop(iterator it);

        nodisc T & front();
        nodisc const T & front() const;

        nodisc T & back();
        nodisc const T & back() const;

        nodisc T & operator[](u32 pos);
        nodisc const T & operator[](u32 pos) const;

        nodisc iterator getIterator(u32 pos);
        nodisc const_iterator getIterator(u32 pos) const;

        nodisc reverse_iterator getReverseIterator(u32 pos);
        nodisc const_reverse_iterator getReverseIterator(u32 pos) const;

        void clear();

        nodisc u32 size() const { return _elements.size(); }

        nodisc bool empty() const { return _elements.empty(); }

        nodisc u32 capacity() const { return _elements.capacity(); }

        nodisc iterator begin();
        nodisc const_iterator begin() const;
        nodisc const_iterator cbegin() const { return begin(); };

        nodisc iterator end();
        nodisc const_iterator end() const;
        nodisc const_iterator cend() const { return end(); };

        nodisc reverse_iterator rbegin();
        nodisc const_reverse_iterator rbegin() const;
        nodisc const_reverse_iterator crbegin() const { return rbegin(); };

        nodisc reverse_iterator rend();
        nodisc const_reverse_iterator rend() const;
        nodisc const_reverse_iterator crend() const { return rend(); };

      private:

        struct _Element
        {
            T value;
            u32 prevI;
            u32 nextI;

            template <typename... Args> _Element(u32 prevI, u32 nextI, Args &&... args);

            _Element(const _Element &) = delete;
            _Element(_Element && other) = default;

            _Element & operator=(const _Element &) = delete;
            _Element & operator=(_Element && other) = default;
        };

        inline constexpr static u32 _invalidI{~0_u32};

        Bank<_Element> _elements{};
        u32 _headI{_invalidI};
        u32 _tailI{_invalidI};
    };

    template <typename T>
    template <bool constant, bool reverse>
    class SemiStableDeque<T>::_Iterator
    {
        friend SemiStableDeque;

        using _T = ConstIf<T, constant>;
        using _Element = ConstIf<_Element, constant>;

      public:

        using iterator_category = std::forward_iterator_tag;
        using value_type = _T;
        using reference = value_type &;
        using pointer = value_type *;
        using difference_type = s64;

        _Iterator() = default;

        _Iterator(const _Iterator<false, reverse> &) requires (constant);

        _Iterator(const _Iterator &) = default;

        _Iterator & operator=(const _Iterator &) = default;

        nodisc reference operator*() const { return _element->value; }

        nodisc pointer operator->() const { return &_element->value; }

        _Iterator & operator++();
        _Iterator operator++(int);

        nodisc u32 pos() const { return u32(_element - _elements); }

        nodisc bool operator==(const _Iterator & other) const;

      private:

        _Element * _elements{};
        _Element * _element{};

        _Iterator(_Element * elements, _Element * element);
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    inline SemiStableDeque<T>::SemiStableDeque(SemiStableDeque && other) :
        _elements{std::move(other._elements)},
        _headI{other._headI},
        _tailI{other._tailI}
    {
        other._headI = _invalidI;
        other._tailI = _invalidI;
    }

    template <typename T>
    inline SemiStableDeque<T> & SemiStableDeque<T>::operator=(SemiStableDeque && other)
    {
        if (&other == this)
        {
            return *this;
        }

        _elements = std::move(other._elements);
        _headI = other._headI;
        _tailI = other._tailI;

        other._headI = _invalidI;
        other._tailI = _invalidI;

        return *this;
    }

    template <typename T>
    inline SemiStableDeque<T>::~SemiStableDeque()
    {
        if constexpr (qc::debug)
        {
            _headI = _invalidI;
            _tailI = _invalidI;
        }
    }

    template <typename T>
    inline auto SemiStableDeque<T>::push_back(const T & v) -> NewElement
    {
        return emplace_back(v);
    }

    template <typename T>
    inline auto SemiStableDeque<T>::push_back(T && v) -> NewElement
    {
        return emplace_back(std::move(v));
    }

    template <typename T>
    inline auto SemiStableDeque<T>::push_front(const T & v) -> NewElement
    {
        return emplace_front(v);
    }

    template <typename T>
    inline auto SemiStableDeque<T>::push_front(T && v) -> NewElement
    {
        return emplace_front(std::move(v));
    }

    template <typename T>
    template <typename... Args>
    inline auto SemiStableDeque<T>::emplace_back(Args &&... args) -> NewElement
    {
        const auto [element, elementI]{_elements.create(_tailI, _invalidI, std::forward<Args>(args)...)};

        if (_tailI != _invalidI) _elements[_tailI].nextI = elementI;
        _tailI = elementI;

        if (_headI == _invalidI) _headI = elementI;

        return {element.value, elementI};
    }

    template <typename T>
    template <typename... Args>
    inline auto SemiStableDeque<T>::emplace_front(Args &&... args) -> NewElement
    {
        const auto [element, elementI]{_elements.create(_invalidI, _headI, std::forward<Args>(args)...)};

        if (_headI != _invalidI) _elements[_headI].prevI = elementI;
        _headI = elementI;

        if (_tailI == _invalidI) _tailI = elementI;

        return {element.value, elementI};
    }

    template <typename T>
    inline void SemiStableDeque<T>::pop_back()
    {
        assert(_tailI != _invalidI);

        pop(_tailI);
    }

    template <typename T>
    inline void SemiStableDeque<T>::pop_front()
    {
        assert(_headI != _invalidI);

        pop(_headI);
    }

    template <typename T>
    inline void SemiStableDeque<T>::pop(const u32 pos)
    {
        _Element & element{_elements[pos]};

        if (element.prevI != _invalidI)
        {
            _elements[element.prevI].nextI = element.nextI;
        }
        else
        {
            _headI = element.nextI;
        }

        if (element.nextI != _invalidI)
        {
            _elements[element.nextI].prevI = element.prevI;
        }
        else
        {
            _tailI = element.prevI;
        }

        _elements.destroy(pos);
    }

    template <typename T>
    inline void SemiStableDeque<T>::pop(const iterator it)
    {
        pop(it.pos());
    }

    template <typename T>
    inline T & SemiStableDeque<T>::front()
    {
        return const_cast<T &>(const_cast<const SemiStableDeque &>(*this).front());
    }

    template <typename T>
    inline const T & SemiStableDeque<T>::front() const
    {
        assert(_headI != _invalidI);

        return _elements[_headI].value;
    }

    template <typename T>
    inline T & SemiStableDeque<T>::back()
    {
        return const_cast<T &>(const_cast<const SemiStableDeque &>(*this).back());
    }

    template <typename T>
    inline const T & SemiStableDeque<T>::back() const
    {
        assert(_tailI != _invalidI);

        return _elements[_tailI].value;
    }

    template <typename T>
    inline T & SemiStableDeque<T>::operator[](const u32 pos)
    {
        return _elements[pos].value;
    }

    template <typename T>
    inline const T & SemiStableDeque<T>::operator[](const u32 pos) const
    {
        return _elements[pos].value;
    }

    template <typename T>
    inline auto SemiStableDeque<T>::getIterator(const u32 pos) -> iterator
    {
        return iterator{&_elements[0u], &_elements[pos]};
    }

    template <typename T>
    inline auto SemiStableDeque<T>::getIterator(const u32 pos) const -> const_iterator
    {
        return const_iterator{&_elements[0u], &_elements[pos]};
    }

    template <typename T>
    inline auto SemiStableDeque<T>::getReverseIterator(const u32 pos) -> reverse_iterator
    {
        return reverse_iterator{&_elements[0u], &_elements[pos]};
    }

    template <typename T>
    inline auto SemiStableDeque<T>::getReverseIterator(const u32 pos) const -> const_reverse_iterator
    {
        return const_reverse_iterator{&_elements[0u], &_elements[pos]};
    }

    template <typename T>
    inline void SemiStableDeque<T>::clear()
    {
        _elements.clear();
        _headI = _invalidI;
        _tailI = _invalidI;
    }

    template <typename T>
    inline auto SemiStableDeque<T>::begin() -> iterator
    {
        return _headI != _invalidI ? iterator{&_elements[0u], &_elements[_headI]} : iterator{};
    }

    template <typename T>
    inline auto SemiStableDeque<T>::begin() const -> const_iterator
    {
        return _headI != _invalidI ? const_iterator{&_elements[0u], &_elements[_headI]} : const_iterator{};
    }

    template <typename T>
    inline auto SemiStableDeque<T>::end() -> iterator
    {
        return iterator{};
    }

    template <typename T>
    inline auto SemiStableDeque<T>::end() const -> const_iterator
    {
        return const_iterator{};
    }

    template <typename T>
    inline auto SemiStableDeque<T>::rbegin() -> reverse_iterator
    {
        return _tailI != _invalidI ? reverse_iterator{&_elements[0u], &_elements[_tailI]} : reverse_iterator{};
    }

    template <typename T>
    inline auto SemiStableDeque<T>::rbegin() const -> const_reverse_iterator
    {
        return _tailI != _invalidI ? const_reverse_iterator{&_elements[0u], &_elements[_tailI]} : const_reverse_iterator{};
    }

    template <typename T>
    inline auto SemiStableDeque<T>::rend() -> reverse_iterator
    {
        return reverse_iterator{};
    }

    template <typename T>
    inline auto SemiStableDeque<T>::rend() const -> const_reverse_iterator
    {
        return const_reverse_iterator{};
    }

    template <typename T>
    template <typename... Args>
    inline SemiStableDeque<T>::_Element::_Element(const u32 prevI_, const u32 nextI_, Args &&... args) :
        value{std::forward<Args>(args)...},
        prevI{prevI_},
        nextI{nextI_}
    {}

    template <typename T>
    template <bool constant, bool reverse>
    SemiStableDeque<T>::_Iterator<constant, reverse>::_Iterator(const _Iterator<false, reverse> & other) requires (constant) :
        _elements{other._elements},
        _element{other._element}
    {}

    template <typename T>
    template <bool constant, bool reverse>
    SemiStableDeque<T>::_Iterator<constant, reverse>::_Iterator(_Element * const elements, _Element * const element) :
        _elements{elements},
        _element{element}
    {}

    template <typename T>
    template <bool constant, bool reverse>
    auto SemiStableDeque<T>::_Iterator<constant, reverse>::operator++() -> _Iterator &
    {
        if constexpr (!reverse)
        {
            _element = _element->nextI != _invalidI ? _elements + _element->nextI : nullptr;
        }
        else
        {
            _element = _element->prevI != _invalidI ? _elements + _element->prevI : nullptr;
        }

        return *this;
    }

    template <typename T>
    template <bool constant, bool reverse>
    auto SemiStableDeque<T>::_Iterator<constant, reverse>::operator++(int) -> _Iterator
    {
        const _Iterator tmp{*this};
        ++*this;
        return tmp;
    }

    template <typename T>
    template <bool constant, bool reverse>
    bool SemiStableDeque<T>::_Iterator<constant, reverse>::operator==(const _Iterator & other) const
    {
        return _element == other._element;
    }
}
