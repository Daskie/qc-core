#pragma once

#include <iterator>
#include <type_traits>

#include <qc-core/array.hpp>

namespace qc
{
    inline namespace types
    {
        template <typename E> concept CountableEnum = Enum<E> && Unsigned<std::underlying_type_t<E>> && std::to_underlying(E::_n) >= 1u;
    }

    template <CountableEnum E> constexpr u64 enumN{u64(E::_n)};

    namespace _private::enum_utils
    {
        template <CountableEnum E>
        consteval Array<E, enumN<E>> makeEnumArray()
        {
            Array<E, enumN<E>> array{};
            for (E v{}; v != E::_n; v = E(std::to_underlying(v) + 1u))
            {
                array[std::to_underlying(v)] = v;
            }
            return array;
        }
    }

    template <CountableEnum E> constexpr Array<E, enumN<E>> enumArray{_private::enum_utils::makeEnumArray<E>()};
}
