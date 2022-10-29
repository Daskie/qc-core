#pragma once
#pragma once

#include <iostream>

#include <qc-core/span.hpp>
#include <qc-core/vector-ext.hpp>

namespace qc
{
    //
    // ...
    //
    template <Numeric T, int n> std::ostream & operator<<(std::ostream & os, const span<T, n> & s);

    //
    // ...
    //
    template <Floating T, int n> span<intmax_t, n> round(const span<T, n> & s);
    template <Integral T, int n> span<T, n> round(const span<T, n> & s);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <Numeric T, int n>
    inline std::ostream & operator<<(std::ostream & os, const span<T, n> & s)
    {
        os << "[";
        if constexpr (n == 1) os << "[";
        os << s.min;
        if constexpr (n == 1) os << "][";
        os << s.max;
        if constexpr (n == 1) os << "]";
        os << "]";
        return os;
    }

    template <Floating T, int n>
    inline span<intmax_t, n> round(const span<T, n> & s)
    {
        return {round(s.min), round(s.max)};
    }

    template <Integral T, int n>
    inline span<T, n> round(const span<T, n> & s)
    {
        return s;
    }
}
