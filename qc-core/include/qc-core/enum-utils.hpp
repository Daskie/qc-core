#pragma once

#include <array>
#include <iterator>
#include <type_traits>

#include <qc-core/core.hpp>

namespace qc
{
    inline namespace types
    {
        template <typename E> concept CountableEnum = Enum<E> && Unsigned<std::underlying_type_t<E>> && requires { E::_n; };
    }

    template <CountableEnum E> constexpr u64 enumN{u64(E::_n)};

    namespace _private::enumUtils
    {
        template <CountableEnum E>
        constexpr std::array<E, enumN<E>> makeEnumArray()
        {
            std::array<E, enumN<E>> array{};
            for (E v{}; v != E::_n; v = E(std::to_underlying(v) + 1u))
            {
                array[std::to_underlying(v)] = v;
            }
            return array;
        }
    }

    template <CountableEnum E> constexpr std::array<E, enumN<E>> enumArray{_private::enumUtils::makeEnumArray<E>()};
}
