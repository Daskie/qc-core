#pragma once

#include <filesystem>
#include <fstream>

#include <qc-core/core.hpp>

namespace qc
{
    template <typename T> concept TriviallySerializable = Numeric<T> || Enum<T> || OneOf<T, bool, char> || T::triviallySerializable;
    template <typename T> concept HasSerializableN = Integral<decltype(T::serializableN)>;
    template <typename T> concept TriviallyCopyable = std::is_trivially_copyable_v<T>;

    template <TriviallyCopyable T> struct SerializeSpan { const T * src; u64 n; };
    template <TriviallyCopyable T> struct DeserializeSpan { T * dst; u64 n; };

    class Serializer
    {
      public:

        template <TriviallySerializable T> friend Serializer & operator<<(Serializer & s, const T & v);
        template <HasSerializableN T> friend Serializer & operator<<(Serializer & s, const T & v);
        template <TriviallyCopyable T> friend Serializer & operator<<(Serializer & s, SerializeSpan<T> srcSpan);

        Serializer(const std::filesystem::path & dstFile);

        explicit operator bool() const { return !_error; }

      private:

        std::ofstream _ofs;
        bool _error;
    };

    class Deserializer
    {
      public:

        template <TriviallySerializable T> friend Deserializer & operator>>(Deserializer & ds, T & v);
        template <HasSerializableN T> friend Deserializer & operator>>(Deserializer & ds, T & v);
        template <TriviallyCopyable T> friend Deserializer & operator>>(Deserializer & s, DeserializeSpan<T> dstSpan);

        Deserializer(const std::filesystem::path & srcFile);

        explicit operator bool() const { return !_error; }

      private:

        std::ifstream _ifs;
        bool _error;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <TriviallySerializable T>
    Serializer & operator<<(Serializer & s, const T & v)
    {
        static_assert(std::is_trivially_copyable_v<T>);

        if (!s._error)
        {
            s._error = !s._ofs.write(std::bit_cast<const char *>(&v), sizeof(T)).good();
        }

        return s;
    }

    template <HasSerializableN T>
    Serializer & operator<<(Serializer & s, const T & v)
    {
        if constexpr (T::serializableN == 1)
        {
            const auto & [v1]{v};
            return s << v1;
        }
        else if constexpr (T::serializableN == 2)
        {
            const auto & [v1, v2]{v};
            return s << v1 << v2;
        }
        else if constexpr (T::serializableN == 3)
        {
            const auto & [v1, v2, v3]{v};
            return s << v1 << v2 << v3;
        }
        else if constexpr (T::serializableN == 4)
        {
            const auto & [v1, v2, v3, v4]{v};
            return s << v1 << v2 << v3 << v4;
        }
        else if constexpr (T::serializableN == 5)
        {
            const auto & [v1, v2, v3, v4, v5]{v};
            return s << v1 << v2 << v3 << v4 << v5;
        }
        else if constexpr (T::serializableN == 6)
        {
            const auto & [v1, v2, v3, v4, v5, v6]{v};
            return s << v1 << v2 << v3 << v4 << v5 << v6;
        }
        else if constexpr (T::serializableN == 7)
        {
            const auto & [v1, v2, v3, v4, v5, v6, v7]{v};
            return s << v1 << v2 << v3 << v4 << v5 << v6 << v7;
        }
        else if constexpr (T::serializableN == 8)
        {
            const auto & [v1, v2, v3, v4, v5, v6, v7, v8]{v};
            return s << v1 << v2 << v3 << v4 << v5 << v6 << v7 << v8;
        }
        else
        {
            static_assert(!sizeof(T));
        }
    }

    Serializer::Serializer(const std::filesystem::path & dstFile) :
        _ofs{dstFile, std::ios::out | std::ios::binary},
        _error{!_ofs.good()}
    {}

    template <TriviallyCopyable T>
    Serializer & operator<<(Serializer & s, const SerializeSpan<T> srcSpan)
    {
        static_assert(sizeof(std::streamsize) <= sizeof(u64));

        if (srcSpan.n > u64(std::numeric_limits<std::streamsize>::max()) / sizeof(T))
        {
            s._error = true;
        }

        if (!s._error)
        {
            s._error = !s._ofs.write(std::bit_cast<const char *>(srcSpan.src), std::streamsize(srcSpan.n * sizeof(T))).good();
        }

        return s;
    }

    template <TriviallySerializable T>
    Deserializer & operator>>(Deserializer & s, T & v)
    {
        if (!s._error)
        {
            s._error = !s._ifs.read(std::bit_cast<char *>(&v), sizeof(T)).good();
        }

        return s;
    }

    template <HasSerializableN T>
    Deserializer & operator>>(Deserializer & s, T & v)
    {
        if constexpr (T::serializableN == 1)
        {
            auto & [v1]{v};
            return s >> v1;
        }
        else if constexpr (T::serializableN == 2)
        {
            auto & [v1, v2]{v};
            return s >> v1 >> v2;
        }
        else if constexpr (T::serializableN == 3)
        {
            auto & [v1, v2, v3]{v};
            return s >> v1 >> v2 >> v3;
        }
        else if constexpr (T::serializableN == 4)
        {
            auto & [v1, v2, v3, v4]{v};
            return s >> v1 >> v2 >> v3 >> v4;
        }
        else if constexpr (T::serializableN == 5)
        {
            auto & [v1, v2, v3, v4, v5]{v};
            return s >> v1 >> v2 >> v3 >> v4 >> v5;
        }
        else if constexpr (T::serializableN == 6)
        {
            auto & [v1, v2, v3, v4, v5, v6]{v};
            return s >> v1 >> v2 >> v3 >> v4 >> v5 >> v6;
        }
        else if constexpr (T::serializableN == 7)
        {
            auto & [v1, v2, v3, v4, v5, v6, v7]{v};
            return s >> v1 >> v2 >> v3 >> v4 >> v5 >> v6 >> v7;
        }
        else if constexpr (T::serializableN == 8)
        {
            auto & [v1, v2, v3, v4, v5, v6, v7, v8]{v};
            return s >> v1 >> v2 >> v3 >> v4 >> v5 >> v6 >> v7 >> v8;
        }
        else
        {
            static_assert(!sizeof(T));
        }
    }

    template <TriviallyCopyable T>
    Deserializer & operator>>(Deserializer & ds, const DeserializeSpan<T> dstSpan)
    {
        static_assert(sizeof(std::streamsize) <= sizeof(u64));

        if (dstSpan.n > u64(std::numeric_limits<std::streamsize>::max()) / sizeof(T))
        {
            ds._error = true;
        }

        if (!ds._error)
        {
            ds._error = !ds._ifs.read(std::bit_cast<char *>(dstSpan.dst), std::streamsize(dstSpan.n * sizeof(T))).good();
        }

        return ds;
    }

    Deserializer::Deserializer(const std::filesystem::path & srcFile) :
        _ifs{srcFile, std::ios::in | std::ios::binary},
        _error{!_ifs.good()}
    {}
}
