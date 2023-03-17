#pragma once

#include <string>
#include <string_view>

#include <qc-core/serializer.hpp>

namespace qc
{
    inline Serializer & operator<<(Serializer & s, const std::string & str)
    {
        return s << str.size() << StreamSpan<const char>{str.data(), str.size()};
    }

    inline Deserializer & operator>>(Deserializer & ds, std::string & str)
    {
        u64 size;
        if (ds >> size)
        {
            str.resize(size);
            ds >> StreamSpan<char>{str.data(), str.size()};
        }
        return ds;
    }

    // Must not serialize non-owning string forms
    Serializer & operator<<(Serializer & s, const char * str) = delete;
    Serializer & operator<<(Serializer & s, std::string_view str) = delete;
    Deserializer & operator>>(Deserializer & s, char * str) = delete;
    Deserializer & operator>>(Deserializer & s, const char * str) = delete;
    Deserializer & operator>>(Deserializer & s, std::string_view str) = delete;
}
