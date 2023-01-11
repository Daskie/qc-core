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
    template <Numeric T, int n> span<T, n> round(const span<T, n> & s);
    template <SignedIntegral R, Floating T, int n> span<R, n> round(const span<T, n> & s);

    //
    // ...
    //
    template <NumericOrPointer T, int n> std::ostream & operator<<(std::ostream & os, const span<T, n> & s);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <Numeric T, int n>
    inline span<T, n> round(const span<T, n> & s)
    {
        if constexpr (Floating<T>)
        {
            return {round(s.min), round(s.max)};
        }
        else
        {
            return s;
        }
    }

    template <SignedIntegral R, Floating T, int n>
    inline span<R, n> round(const span<T, n> & s)
    {
        return {round<R>(s.min), round<R>(s.max)};
    }

    template <NumericOrPointer T, int n>
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
}
