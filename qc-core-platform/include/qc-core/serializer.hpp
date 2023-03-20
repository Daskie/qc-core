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

        Serializer(const std::filesystem::path & dstFile);

        explicit operator bool() const { return bool(_ofs); }

        bool close();

        template <TriviallySerializable T> Serializer & operator<<(const T & v);
        template <HasSerializableN T> Serializer & operator<<(const T & v);
        template <TriviallyCopyable T> Serializer & operator<<(StreamSpan<const T> srcSpan);

      private:

        BinaryOFStream _ofs;
    };

    class Deserializer
    {
      public:

        Deserializer(const std::filesystem::path & srcFile);

        explicit operator bool() const { return bool(_ifs); }

        bool close();

        template <TriviallySerializable T> Deserializer & operator>>(T & v);
        template <HasSerializableN T> Deserializer & operator>>(T & v);
        template <TriviallyCopyable T> Deserializer & operator>>(StreamSpan<T> dstSpan);

      private:

        BinaryIFStream _ifs;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    bool Serializer::close()
    {
        return _ofs.close();
    }

    template <TriviallySerializable T>
    Serializer & Serializer::operator<<(const T & v)
    {
        static_assert(std::is_trivially_copyable_v<T>);

        _ofs << v;
        return *this;
    }

    template <HasSerializableN T>
    Serializer & Serializer::operator<<(const T & v)
    {
        if constexpr (T::serializableN == 1)
        {
            const auto & [v1]{v};
            return *this << v1;
        }
        else if constexpr (T::serializableN == 2)
        {
            const auto & [v1, v2]{v};
            return *this << v1 << v2;
        }
        else if constexpr (T::serializableN == 3)
        {
            const auto & [v1, v2, v3]{v};
            return *this << v1 << v2 << v3;
        }
        else if constexpr (T::serializableN == 4)
        {
            const auto & [v1, v2, v3, v4]{v};
            return *this << v1 << v2 << v3 << v4;
        }
        else if constexpr (T::serializableN == 5)
        {
            const auto & [v1, v2, v3, v4, v5]{v};
            return *this << v1 << v2 << v3 << v4 << v5;
        }
        else if constexpr (T::serializableN == 6)
        {
            const auto & [v1, v2, v3, v4, v5, v6]{v};
            return *this << v1 << v2 << v3 << v4 << v5 << v6;
        }
        else if constexpr (T::serializableN == 7)
        {
            const auto & [v1, v2, v3, v4, v5, v6, v7]{v};
            return *this << v1 << v2 << v3 << v4 << v5 << v6 << v7;
        }
        else if constexpr (T::serializableN == 8)
        {
            const auto & [v1, v2, v3, v4, v5, v6, v7, v8]{v};
            return *this << v1 << v2 << v3 << v4 << v5 << v6 << v7 << v8;
        }
        else
        {
            static_assert(!sizeof(T));
        }
    }

    template <TriviallyCopyable T>
    Serializer & Serializer::operator<<(const StreamSpan<const T> srcSpan)
    {
        _ofs << srcSpan;
        return *this;
    }

    Serializer::Serializer(const std::filesystem::path & dstFile) :
        _ofs{dstFile}
    {}

    Deserializer::Deserializer(const std::filesystem::path & srcFile) :
        _ifs{srcFile}
    {}

    bool Deserializer::close()
    {
        return _ifs.close();
    }

    template <TriviallySerializable T>
    Deserializer & Deserializer::operator>>(T & v)
    {
        static_assert(std::is_trivially_copyable_v<T>);

        _ifs >> v;
        return *this;
    }

    template <HasSerializableN T>
    Deserializer & Deserializer::operator>>(T & v)
    {
        if constexpr (T::serializableN == 1)
        {
            auto & [v1]{v};
            return *this >> v1;
        }
        else if constexpr (T::serializableN == 2)
        {
            auto & [v1, v2]{v};
            return *this >> v1 >> v2;
        }
        else if constexpr (T::serializableN == 3)
        {
            auto & [v1, v2, v3]{v};
            return *this >> v1 >> v2 >> v3;
        }
        else if constexpr (T::serializableN == 4)
        {
            auto & [v1, v2, v3, v4]{v};
            return *this >> v1 >> v2 >> v3 >> v4;
        }
        else if constexpr (T::serializableN == 5)
        {
            auto & [v1, v2, v3, v4, v5]{v};
            return *this >> v1 >> v2 >> v3 >> v4 >> v5;
        }
        else if constexpr (T::serializableN == 6)
        {
            auto & [v1, v2, v3, v4, v5, v6]{v};
            return *this >> v1 >> v2 >> v3 >> v4 >> v5 >> v6;
        }
        else if constexpr (T::serializableN == 7)
        {
            auto & [v1, v2, v3, v4, v5, v6, v7]{v};
            return *this >> v1 >> v2 >> v3 >> v4 >> v5 >> v6 >> v7;
        }
        else if constexpr (T::serializableN == 8)
        {
            auto & [v1, v2, v3, v4, v5, v6, v7, v8]{v};
            return *this >> v1 >> v2 >> v3 >> v4 >> v5 >> v6 >> v7 >> v8;
        }
        else
        {
            static_assert(!sizeof(T));
        }
    }

    template <TriviallyCopyable T>
    Deserializer & Deserializer::operator>>(const StreamSpan<T> dstSpan)
    {
        _ifs >> dstSpan;
        return *this;
    }
}
