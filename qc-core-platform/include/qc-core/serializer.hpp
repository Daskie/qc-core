#pragma once

#include <filesystem>

#include <qc-core/binary-file-stream.hpp>

namespace qc
{
    template <typename T> concept Serializable = Numeric<T> || Enum<T> || OneOf<T, bool, char> || T::_serializableN > 0u;

    class Serializer
    {
      public:

        Serializer(const std::filesystem::path & dstFile);

        explicit operator bool() const { return bool(_ofs); }

        bool close();

        template <Serializable T> Serializer & operator<<(const T & v);
        template <typename T> Serializer & operator<<(StreamSpan<const T> srcSpan);

      private:

        BinaryOFStream _ofs;
    };

    class Deserializer
    {
      public:

        Deserializer(const std::filesystem::path & srcFile);

        explicit operator bool() const { return bool(_ifs); }

        bool close();

        template <Serializable T> Deserializer & operator>>(T & v);
        template <typename T> Deserializer & operator>>(StreamSpan<T> dstSpan);

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

    template <Serializable T>
    Serializer & Serializer::operator<<(const T & v)
    {
        // TODO: Ensure serializableN size matches actual size of type
        if constexpr(std::is_trivially_copyable_v<T>)
        {
            _ofs << v;
            return *this;
        }
        else
        {
            if constexpr (T::_serializableN == 1u)
            {
                const auto & [v1]{v};
                return *this << v1;
            }
            else if constexpr (T::_serializableN == 2u)
            {
                const auto & [v1, v2]{v};
                return *this << v1 << v2;
            }
            else if constexpr (T::_serializableN == 3u)
            {
                const auto & [v1, v2, v3]{v};
                return *this << v1 << v2 << v3;
            }
            else if constexpr (T::_serializableN == 4u)
            {
                const auto & [v1, v2, v3, v4]{v};
                return *this << v1 << v2 << v3 << v4;
            }
            else if constexpr (T::_serializableN == 5u)
            {
                const auto & [v1, v2, v3, v4, v5]{v};
                return *this << v1 << v2 << v3 << v4 << v5;
            }
            else if constexpr (T::_serializableN == 6u)
            {
                const auto & [v1, v2, v3, v4, v5, v6]{v};
                return *this << v1 << v2 << v3 << v4 << v5 << v6;
            }
            else if constexpr (T::_serializableN == 7u)
            {
                const auto & [v1, v2, v3, v4, v5, v6, v7]{v};
                return *this << v1 << v2 << v3 << v4 << v5 << v6 << v7;
            }
            else if constexpr (T::_serializableN == 8u)
            {
                const auto & [v1, v2, v3, v4, v5, v6, v7, v8]{v};
                return *this << v1 << v2 << v3 << v4 << v5 << v6 << v7 << v8;
            }
            else
            {
                static_assert(!sizeof(T));
            }
        }
    }

    template <typename T>
    Serializer & Serializer::operator<<(const StreamSpan<const T> srcSpan)
    {
        if constexpr (Serializable<T> && TriviallyCopyable<T>)
        {
            _ofs << srcSpan;
        }
        else
        {
            for (const T & v : srcSpan)
            {
                *this << v;
            }
        }

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

    template <Serializable T>
    Deserializer & Deserializer::operator>>(T & v)
    {
        if constexpr (std::is_trivially_copyable_v<T>)
        {
            _ifs >> v;
            return *this;
        }
        else
        {
            if constexpr (T::_serializableN == 1u)
            {
                auto & [v1]{v};
                return *this >> v1;
            }
            else if constexpr (T::_serializableN == 2u)
            {
                auto & [v1, v2]{v};
                return *this >> v1 >> v2;
            }
            else if constexpr (T::_serializableN == 3u)
            {
                auto & [v1, v2, v3]{v};
                return *this >> v1 >> v2 >> v3;
            }
            else if constexpr (T::_serializableN == 4u)
            {
                auto & [v1, v2, v3, v4]{v};
                return *this >> v1 >> v2 >> v3 >> v4;
            }
            else if constexpr (T::_serializableN == 5u)
            {
                auto & [v1, v2, v3, v4, v5]{v};
                return *this >> v1 >> v2 >> v3 >> v4 >> v5;
            }
            else if constexpr (T::_serializableN == 6u)
            {
                auto & [v1, v2, v3, v4, v5, v6]{v};
                return *this >> v1 >> v2 >> v3 >> v4 >> v5 >> v6;
            }
            else if constexpr (T::_serializableN == 7u)
            {
                auto & [v1, v2, v3, v4, v5, v6, v7]{v};
                return *this >> v1 >> v2 >> v3 >> v4 >> v5 >> v6 >> v7;
            }
            else if constexpr (T::_serializableN == 8u)
            {
                auto & [v1, v2, v3, v4, v5, v6, v7, v8]{v};
                return *this >> v1 >> v2 >> v3 >> v4 >> v5 >> v6 >> v7 >> v8;
            }
            else
            {
                static_assert(!sizeof(T));
            }
        }
    }

    template <typename T>
    Deserializer & Deserializer::operator>>(const StreamSpan<T> dstSpan)
    {
        if constexpr (Serializable<T> && TriviallyCopyable<T>)
        {
            _ifs >> dstSpan;
        }
        else
        {
            for (T & v : dstSpan)
            {
                *this >> v;
            }
        }

        return *this;
    }
}
