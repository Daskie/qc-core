#include <qc-core/binary-file-stream.hpp>

#include <qc-core/paging.hpp>

#ifdef QC_MSVC
    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX
    #include <windows.h>
#else
    #include <fcntl.h>
    #include <unistd.h>
#endif

namespace qc
{
    namespace
    {
        static_assert(_BinaryStreamCommon::bufferSize % pageSize == 0u);
        constexpr u64 _bufferPageCount{_BinaryStreamCommon::bufferSize / pageSize};

        // Keep one buffer per thread around for reuse
        thread_local std::byte * _availableBuffer{};

        std::byte * _getBuffer()
        {
            if (_availableBuffer)
            {
                return std::exchange(_availableBuffer, nullptr);
            }
            else
            {
                return static_cast<std::byte *>(allocatePages(_bufferPageCount));
            }
        }

        void _releaseBuffer(std::byte * buffer)
        {
            if (_availableBuffer)
            {
                freePages(buffer, _bufferPageCount);
            }
            else
            {
                _availableBuffer = buffer;
            }
        }

        s64 _openFile(const std::filesystem::path & file, const bool readWrite)
        {
            #ifdef QC_MSVC
                return std::bit_cast<s64>(::CreateFileW(
                    file.c_str(),
                    DWORD(readWrite ? GENERIC_WRITE : GENERIC_READ),
                    DWORD(readWrite ? 0 : FILE_SHARE_READ),
                    nullptr,
                    DWORD(readWrite ? CREATE_ALWAYS : OPEN_EXISTING),
                    DWORD(readWrite ? FILE_ATTRIBUTE_NORMAL : FILE_FLAG_SEQUENTIAL_SCAN),
                    nullptr));
            #else
                if (readWrite)
                {
                    return ::creat(file.c_str(), 0644u);
                }
                else
                {
                    return ::open(file.c_str(), O_RDONLY);
                }
            #endif
        }

        s64 _readFile(const s64 fd, std::byte * const dst, const u64 bytes)
        {
            #ifdef QC_MSVC
                DWORD bytesRead{};
                const bool success{bool(::ReadFile(
                    std::bit_cast<HANDLE>(fd),
                    dst,
                    DWORD(min(bytes, std::numeric_limits<DWORD>::max())),
                    &bytesRead,
                    nullptr))};
                return success ? bytesRead : -1;
            #else
                return ::read(s32(fd), dst, bytes);
            #endif
        }

        bool _writeFile(const s64 fd, const std::byte * src, u64 bytes)
        {
            do
            {
                s64 bytesWritten;
                #ifdef QC_MSVC
                    DWORD bytesWritten_;
                    const bool success{bool(::WriteFile(
                        std::bit_cast<HANDLE>(fd),
                        src,
                        DWORD(min(bytes, std::numeric_limits<DWORD>::max())),
                        &bytesWritten_,
                        nullptr))};
                    bytesWritten = success ? bytesWritten_ : -1;
                #else
                    bytesWritten = ::write(s32(fd), src, bytes);
                #endif

                if (bytesWritten < 0)
                {
                    return false;
                }

                src += bytesWritten;
                bytes -= u64(bytesWritten);
            }
            while (bytes);

            return true;
        }

        bool _closeFile(const s64 fd)
        {
            #ifdef QC_MSVC
                return ::CloseHandle(std::bit_cast<HANDLE>(fd));
            #else
                return !::close(int(fd));
            #endif
        }

    }

    BinaryOFStream::BinaryOFStream(const std::filesystem::path & file)
    {
        _fd = _openFile(file, true);

        if (_fd == -1)
        {
            _error = true;
            return;
        }

        _buffer = _getBuffer();
        _error = !_buffer;
        _bufferPos = _buffer;
        _remaining = bufferSize;
    }

    BinaryOFStream::~BinaryOFStream()
    {
        close();

        if (_buffer)
        {
            _releaseBuffer(_buffer);
        }
    }

    bool BinaryOFStream::close()
    {
        if (!_error && _remaining < bufferSize)
        {
            _flush();
        }

        if (_fd != -1)
        {
            _error = !_closeFile(_fd) || _error;
            _fd = -1;
        }

        return !_error;
    }

    void BinaryOFStream::_flush()
    {
        const u64 bytes{bufferSize - _remaining};

        if (!_writeFile(_fd, _buffer, bytes))
        {
            _error = true;
            return;
        }

        _remaining += bytes;
        _bufferPos -= bytes;
    }

    BinaryIFStream::BinaryIFStream(const std::filesystem::path & file)
    {
        _fd = _openFile(file, false);

        if (_fd == -1)
        {
            _error = true;
            return;
        }

        _buffer = _getBuffer();
        _error = !_buffer;
    }

    BinaryIFStream::~BinaryIFStream()
    {
        close();

        if (_buffer)
        {
            _releaseBuffer(_buffer);
        }
    }

    bool BinaryIFStream::close()
    {
        if (_fd != -1)
        {
            _error = !_closeFile(_fd) || _error;
            _fd = -1;
        }

        return !_error;
    }

    void BinaryIFStream::_readMore()
    {
        // Move any left over data to the front of the buffer
        if (_remaining)
        {
            memmove(_buffer, _bufferPos, _remaining);
        }

        _bufferPos = _buffer + _remaining;

        const s64 bytesRead(_readFile(_fd, _bufferPos, bufferSize - _remaining));

        if (bytesRead < 0)
        {
            _error = true;
            return;
        }

        _remaining += u64(bytesRead);
    }
}
