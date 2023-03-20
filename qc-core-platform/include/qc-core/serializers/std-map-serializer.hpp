#pragma once

#include <map>

#include <qc-core/serializer.hpp>

namespace qc
{
    template <typename K, typename V>
    inline Serializer & operator<<(Serializer & s, const std::map<K, V> & map)
    {
        s << map.size();

        for (const auto & [k, v] : map)
        {
            s << k << v;
        }

        return s;
    }

    template <typename K, typename T>
    inline Deserializer & operator>>(Deserializer & ds, std::map<K, T> & map)
    {
        static_assert(std::is_default_constructible_v<K> && std::is_default_constructible_v<T>);

        u64 size;
        if (ds >> size)
        {
            K k;
            T v;

            for (; size; --size)
            {
                if (!(ds >> k >> v))
                {
                    break;
                }

                map.emplace(std::move(k), std::move(v));
            }
        }

        return ds;
    }
}
