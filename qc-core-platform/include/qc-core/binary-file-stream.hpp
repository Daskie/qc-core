#pragma once

#include <filesystem>

#include <qc-core/core.hpp>

namespace qc
{
    template <TriviallyCopyable T> struct StreamSpan { T * vs; u64 n; };

    class _BinaryStreamCommon
    {
      public:

        static constexpr u64 bufferSize{4096u * 4u};

      protected:

        template <u64 n> struct _Bytes { std::byte bytes[n]; };

        static constexpr u64 _maxDirectCopySize{64u};
    };

    class BinaryOFStream : public _BinaryStreamCommon
    {
      public:

        explicit BinaryOFStream(const std::filesystem::path & file);

        ~BinaryOFStream();

        template <TriviallyCopyable T> BinaryOFStream & operator<<(const T & src);
        template <TriviallyCopyable T> BinaryOFStream & operator<<(StreamSpan<const T> src);

        nodisc explicit operator bool() const { return !_error; }

        bool close();

      private:

        bool _error{};
        void * _fileHandle{};
        std::byte * _buffer{};
        std::byte * _bufferPos{};
        u64 _remaining{};

        void _flush();
    };

    class BinaryIFStream : public _BinaryStreamCommon
    {
      public:

        explicit BinaryIFStream(const std::filesystem::path & file);

        ~BinaryIFStream();

        template <TriviallyCopyable T> BinaryIFStream & operator>>(T & dst);
        template <TriviallyCopyable T> BinaryIFStream & operator>>(StreamSpan<T> dst);

        nodisc explicit operator bool() const { return !_error; }

        bool close();

      private:

        bool _error{};
        void * _fileHandle{};
        std::byte * _buffer{};
        std::byte * _bufferPos{};
        u64 _remaining{};

        void _readMore();
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <TriviallyCopyable T>
    inline BinaryOFStream & BinaryOFStream::operator<<(const T & src)
    {
        if (_error)
        {
            return *this;
        }

        if constexpr (sizeof(T) <= _maxDirectCopySize)
        {
            // Not enough space left in buffer
            if (_remaining < sizeof(T)) [[unlikely]]
            {
                _flush();

                if (_error)
                {
                    return *this;
                }
            }

            *reinterpret_cast<_Bytes<sizeof(T)> *>(_bufferPos) = reinterpret_cast<const _Bytes<sizeof(T)> &>(src);
            _bufferPos += sizeof(T);
            _remaining -= sizeof(T);
            return *this;
        }
        else
        {
            return *this << StreamSpan{&src, 1u};
        }
    }

    template <TriviallyCopyable T>
    inline BinaryOFStream & BinaryOFStream::operator<<(const StreamSpan<const T> src)
    {
        if (_error)
        {
            return *this;
        }

        StreamSpan<const std::byte> srcBytes{reinterpret_cast<const std::byte *>(src.vs), src.n * sizeof(T)};

        while (srcBytes.n)
        {
            // No space left in buffer
            if (!_remaining)
            {
                _flush();

                if (_error)
                {
                    return *this;
                }
            }

            const u64 bytesToCopy{min(srcBytes.n, _remaining)};
            memcpy(_bufferPos, srcBytes.vs, bytesToCopy);
            srcBytes.vs += bytesToCopy;
            srcBytes.n -= bytesToCopy;
            _bufferPos += bytesToCopy;
            _remaining -= bytesToCopy;
        }

        return *this;
    }

    template <TriviallyCopyable T>
    inline BinaryIFStream & BinaryIFStream::operator>>(T & dst)
    {
        if (_error)
        {
            return *this;
        }

        if constexpr (sizeof(T) <= _maxDirectCopySize)
        {
            // Buffer doesn't have enough data
            if (_remaining < sizeof(T)) [[unlikely]]
            {
                _readMore();

                if (_error || _remaining < sizeof(T))
                {
                    _error = true;
                    return *this;
                }
            }

            reinterpret_cast<_Bytes<sizeof(T)> &>(dst) = *reinterpret_cast<const _Bytes<sizeof(T)> *>(_bufferPos);
            _bufferPos += sizeof(T);
            _remaining -= sizeof(T);
            return *this;
        }
        else
        {
            return *this >> StreamSpan<T>{&dst, 1u};
        }
    }

    template <TriviallyCopyable T>
    inline BinaryIFStream & BinaryIFStream::operator>>(const StreamSpan<T> dst)
    {
        if (_error)
        {
            return *this;
        }

        StreamSpan<std::byte> dstBytes{reinterpret_cast<std::byte *>(dst.vs), dst.n * sizeof(T)};

        while (dstBytes.n)
        {
            // Buffer doesn't have enough data
            if (!_remaining)
            {
                _readMore();

                if (_error)
                {
                    return *this;
                }
            }

            const u64 bytesToCopy{min(dstBytes.n, _remaining)};
            memcpy(dstBytes.vs, _bufferPos, bytesToCopy);
            dstBytes.vs += bytesToCopy;
            dstBytes.n -= bytesToCopy;
            _bufferPos += bytesToCopy;
            _remaining -= bytesToCopy;
        }

        return *this;
    }
}
