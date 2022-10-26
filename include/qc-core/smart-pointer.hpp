#pragma once

#include <qc-core/core.hpp>

namespace qc
{
    using Deleter = void (*)(void *);

    template <typename T>
    class Unq
    {
        template <typename T_> friend class Unq;

      public:

        Unq() noexcept = default;
        Unq(T * ptr, Deleter deleter) noexcept;

        Unq(const Unq &) = delete;
        Unq(Unq && other) noexcept;
        template <typename T_> requires std::derived_from<T_, T> Unq(Unq<T_> && other) noexcept;

        Unq & operator=(const Unq &) = delete;
        Unq & operator=(Unq && other) noexcept;

        ~Unq() noexcept;

        explicit operator bool() const noexcept { return _ptr; }

        T & operator*() noexcept { return *_ptr; }

        const T & operator*() const noexcept { return *_ptr; }

        T * operator->() noexcept { return _ptr; }

        const T * operator->() const noexcept { return _ptr; }

        T * get() noexcept { return _ptr; }

        const T * get() const noexcept { return _ptr; }

      private:

        T * _ptr{};
        Deleter _deleter{};
    };

    template <typename T>
    class Shr
    {
        template <typename T_> friend class Shr;

      public:

        struct Entry
        {
            static_assert(alignof(T) <= 8); // Ensure consistent value offset in case of inheritence

            u64 refCount;
            T val;

            Entry() = delete;
            template <typename... Args> Entry(Args &&... args);

            Entry(const Entry &) = delete;
            Entry(Entry &&) = delete;

            Entry & operator=(const Entry &) = delete;
            Entry & operator=(Entry &&) = delete;

            ~Entry() noexcept = default;
        };

        Shr() noexcept = default;
        Shr(Entry * entry, Deleter deleter) noexcept;

        Shr(const Shr & other) noexcept;
        template <typename T_> requires std::derived_from<T_, T> Shr(const Shr<T_> & other) noexcept;
        Shr(Shr && other) noexcept;
        template <typename T_> requires std::derived_from<T_, T> Shr(Shr<T_> && other) noexcept;

        Shr & operator=(const Shr & other) noexcept;
        Shr & operator=(Shr && other) noexcept;

        ~Shr() noexcept;

        explicit operator bool() const noexcept { return _entry; }

        T & operator*() noexcept { return _entry->val; }

        const T & operator*() const noexcept { return _entry->val; }

        T * operator->() noexcept { return &_entry->val; }

        const T * operator->() const noexcept { return &_entry->val; }

        T * get() noexcept { return _entry ? &_entry->val : nullptr; }

        const T * get() const noexcept { return _entry ? &_entry->val : nullptr; }

      private:

        Entry * _entry{};
        Deleter _deleter{};
    };

    template <typename T, typename... Args> Unq<T> makeUnique(Args &&... args);

    template <typename T, typename... Args> Shr<T> makeShared(Args &&... args);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    inline Unq<T>::Unq(T * const ptr, const Deleter deleter) noexcept :
        _ptr{ptr},
        _deleter{deleter}
    {}

    template <typename T>
    inline Unq<T>::Unq(Unq && other) noexcept :
        _ptr{std::exchange(other._ptr, nullptr)},
        _deleter{std::exchange(other._deleter, nullptr)}
    {}

    template <typename T>
    template <typename T_> requires std::derived_from<T_, T>
    inline Unq<T>::Unq(Unq<T_> && other) noexcept :
        _ptr{std::exchange(other._ptr, nullptr)},
        _deleter{std::exchange(other._deleter, nullptr)}
    {}

    template <typename T>
    inline Unq<T> & Unq<T>::operator=(Unq && other) noexcept
    {
        if (&other == this)
        {
            return *this;
        }

        if (_ptr)
        {
            _deleter(_ptr);
        }

        _ptr = std::exchange(other._ptr, nullptr);
        _deleter = std::exchange(other._deleter, nullptr);

        return *this;
    }

    template <typename T>
    inline Unq<T>::~Unq() noexcept
    {
        if (_ptr)
        {
            _deleter(_ptr);
        }

        if constexpr (debug)
        {
            _ptr = nullptr;
            _deleter = nullptr;
        }
    }

    template <typename T>
    template <typename... Args>
    inline Shr<T>::Entry::Entry(Args &&... args) :
        refCount{0u},
        val{std::forward<Args>(args)...}
    {}

    template <typename T>
    inline Shr<T>::Shr(Entry * const entry, const Deleter deleter) noexcept :
        _entry{entry},
        _deleter{deleter}
    {
        ++_entry->refCount;
    }

    template <typename T>
    inline Shr<T>::Shr(const Shr & other) noexcept :
        _entry{other._entry},
        _deleter{other._deleter}
    {
        ++_entry->refCount;
    }

    template <typename T>
    template <typename T_> requires std::derived_from<T_, T>
    inline Shr<T>::Shr(const Shr<T_> & other) noexcept :
        _entry{reinterpret_cast<Entry *>(other._entry)},
        _deleter{other._deleter}
    {
        ++_entry->refCount;
    }

    template <typename T>
    inline Shr<T>::Shr(Shr && other) noexcept :
        _entry{std::exchange(other._entry, nullptr)},
        _deleter{std::exchange(other._deleter, nullptr)}
    {}

    template <typename T>
    template <typename T_> requires std::derived_from<T_, T>
    inline Shr<T>::Shr(Shr<T_> && other) noexcept :
        _entry{reinterpret_cast<Entry *>(std::exchange(other._entry, nullptr))},
        _deleter{std::exchange(other._deleter, nullptr)}
    {}

    template <typename T>
    inline Shr<T> & Shr<T>::operator=(const Shr & other) noexcept
    {
        if (&other == this)
        {
            return *this;
        }

        if (_entry)
        {
            if (!--_entry->refCount)
            {
                _deleter(_entry);
            }
        }

        _entry = other._entry;
        _deleter = other._deleter;

        if (_entry)
        {
            ++_entry->refCount;
        }

        return *this;
    }

    template <typename T>
    inline Shr<T> & Shr<T>::operator=(Shr && other) noexcept
    {
        if (&other == this)
        {
            return *this;
        }

        if (_entry)
        {
            if (!--_entry->refCount)
            {
                _deleter(_entry);
            }
        }

        _entry = std::exchange(other._entry, nullptr);
        _deleter = std::exchange(other._deleter, nullptr);

        return *this;
    }

    template <typename T>
    inline Shr<T>::~Shr() noexcept
    {
        if (_entry)
        {
            if (!--_entry->refCount)
            {
                _deleter(_entry);
            }
        }

        if constexpr (debug)
        {
            _entry = nullptr;
            _deleter = nullptr;
        }
    }

    template <typename T, typename... Args>
    inline Unq<T> makeUnique(Args &&... args)
    {
        return Unq<T>(new T{std::forward<Args>(args)...}, [](void * ptr) { delete static_cast<T *>(ptr); });
    }

    template <typename T, typename... Args>
    inline Shr<T> makeShared(Args &&... args)
    {
        return Shr<T>{new typename Shr<T>::Entry{std::forward<Args>(args)...}, [](void * ptr) { delete static_cast<typename Shr<T>::Entry *>(ptr); }};
    }
}
