#pragma once

#include <qc-core/list.hpp>
#include <qc-core/serializer.hpp>

namespace qc
{
    template <typename T>
    inline Serializer & operator<<(Serializer & s, const List<T> & list)
    {
        s << list.size();

        if constexpr (TriviallyCopyable<T>)
        {
            s << StreamSpan<const T>{list.data(), list.size()};
        }
        else
        {
            for (const T & v : list) s << v;
        }

        return s;
    }

    template <typename T>
    inline Deserializer & operator>>(Deserializer & ds, List<T> & list)
    {
        u64 size;
        if (ds >> size)
        {
            list.resize(size);

            if constexpr (TriviallyCopyable<T>)
            {
                ds >> StreamSpan<T>{list.data(), list.size()};
            }
            else
            {
                for (T & v : list) ds >> v;
            }
        }

        return ds;
    }
}
