#pragma once

#include <qc-core/core.hpp>

namespace qc
{
    template <typename T, Enum E>
    class EBox
    {
      public:

        EBox(E error);
        template <typename... Args> EBox(Args &&... args);

        EBox(const EBox &) = delete;
        EBox(EBox &&) = delete;

        EBox & operator=(const EBox &) = delete;
        EBox & operator=(EBox &&) = delete;

        ~EBox();

        [[nodiscard]] operator bool() const { return _error == E{}; }

        [[nodiscard]] operator E() const { return _error; }

        [[nodiscard]] E error() const { return _error; }

        [[nodiscard]] T & operator*();
        [[nodiscard]] const T & operator*() const;

        [[nodiscard]] T * operator->();
        [[nodiscard]] const T * operator->() const;

      private:

        // Putting val in union stops its default constructor and destructor from being called automatically
        union
        {
            T _val;
        };
        E _error;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T, Enum E>
    #pragma warning(suppress: 4582)
    inline EBox<T, E>::EBox(const E error) :
        _error{error}
    {}

    template <typename T, Enum E>
    template <typename... Args>
    inline EBox<T, E>::EBox(Args &&... args) :
        _val{std::forward<Args>(args)...},
        _error{}
    {}

    template <typename T, Enum E>
    inline EBox<T, E>::~EBox()
    #pragma warning(suppress: 4583)
    {
        if (*this)
        {
            _val.~T();
        }
    }

    template <typename T, Enum E>
    inline T & EBox<T, E>::operator*()
    {
        assert(*this);
        return _val;
    }

    template <typename T, Enum E>
    inline const T & EBox<T, E>::operator*() const
    {
        assert(*this);
        return _val;
    }

    template <typename T, Enum E>
    inline T * EBox<T, E>::operator->()
    {
        assert(*this);
        return &_val;
    }

    template <typename T, Enum E>
    inline const T * EBox<T, E>::operator->() const
    {
        assert(*this);
        return &_val;
    }
}
