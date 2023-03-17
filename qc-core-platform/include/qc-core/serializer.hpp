#pragma once

#include <filesystem>

#include <qc-core/binary-file-stream.hpp>

namespace qc
{
    template <typename T> concept TriviallySerializable = Numeric<T> || Enum<T> || OneOf<T, bool, char> || T::triviallySerializable;
    template <typename T> concept HasSerializableN = Integral<decltype(T::serializableN)>;

    class Serializer
    {
      public:

        template <TriviallySerializable T> friend Serializer & operator<<(Serializer & s, const T & v);
        template <HasSerializableN T> friend Serializer & operator<<(Serializer & s, const T & v);
        template <TriviallyCopyable T> friend Serializer & operator<<(Serializer & s, StreamSpan<const T> srcSpan);

        Serializer(const std::filesystem::path & dstFile);

        explicit operator bool() const { return bool(_ofs); }

        bool close();

      private:

        BinaryOFStream _ofs;
    };

    class Deserializer
    {
      public:

        template <TriviallySerializable T> friend Deserializer & operator>>(Deserializer & ds, T & v);
        template <HasSerializableN T> friend Deserializer & operator>>(Deserializer & ds, T & v);
        template <TriviallyCopyable T> friend Deserializer & operator>>(Deserializer & ds, StreamSpan<T> dstSpan);

        Deserializer(const std::filesystem::path & srcFile);

        explicit operator bool() const { return bool(_ifs); }

        bool close();

      private:

        BinaryIFStream _ifs;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <TriviallySerializable T>
    Serializer & operator<<(Serializer & s, const T & v)
    {
        static_assert(std::is_trivially_copyable_v<T>);

        s._ofs << v;
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

    template <TriviallyCopyable T>
    Serializer & operator<<(Serializer & s, const StreamSpan<const T> srcSpan)
    {
        s._ofs << srcSpan;
        return s;
    }

    Serializer::Serializer(const std::filesystem::path & dstFile) :
        _ofs{dstFile}
    {}

    bool Serializer::close()
    {
        return _ofs.close();
    }

    template <TriviallySerializable T>
    Deserializer & operator>>(Deserializer & ds, T & v)
    {
        static_assert(std::is_trivially_copyable_v<T>);

        ds._ifs >> v;
        return ds;
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
    Deserializer & operator>>(Deserializer & ds, const StreamSpan<T> dstSpan)
    {
        ds._ifs >> dstSpan;
        return ds;
    }

    Deserializer::Deserializer(const std::filesystem::path & srcFile) :
        _ifs{srcFile}
    {}

    bool Deserializer::close()
    {
        return _ifs.close();
    }
}
