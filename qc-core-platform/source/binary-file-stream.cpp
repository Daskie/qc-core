#include <qc-core/binary-file-stream.hpp>

#include <qc-core/paging.hpp>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

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
    }

    BinaryOFStream::BinaryOFStream(const std::filesystem::path & file) :
        _fileHandle{INVALID_HANDLE_VALUE}
    {
        _fileHandle = CreateFileW(
            file.c_str(),
            GENERIC_WRITE,
            0,
            nullptr,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            nullptr);

        if (_fileHandle == INVALID_HANDLE_VALUE)
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

        if (_fileHandle != INVALID_HANDLE_VALUE)
        {
            if (!CloseHandle(std::exchange(_fileHandle, INVALID_HANDLE_VALUE)))
            {
                _error = true;
            }
        }

        return !_error;
    }

    void BinaryOFStream::_flush()
    {
        DWORD bytesWritten{};
        if (!WriteFile(_fileHandle, _buffer, DWORD(bufferSize - _remaining), &bytesWritten, nullptr))
        {
            _error = true;
            return;
        }

        _remaining += bytesWritten;
        _bufferPos -= bytesWritten;
    }

    BinaryIFStream::BinaryIFStream(const std::filesystem::path & file) :
        _fileHandle{INVALID_HANDLE_VALUE}
    {
        _fileHandle = CreateFileW(
            file.c_str(),
            GENERIC_READ,
            FILE_SHARE_READ,
            nullptr,
            OPEN_EXISTING,
            FILE_FLAG_SEQUENTIAL_SCAN,
            nullptr);

        if (_fileHandle == INVALID_HANDLE_VALUE)
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
        if (_fileHandle != INVALID_HANDLE_VALUE)
        {
            if (!CloseHandle(std::exchange(_fileHandle, INVALID_HANDLE_VALUE)))
            {
                _error = true;
            }
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

        DWORD bytesRead{};
        if (!ReadFile(_fileHandle, _bufferPos, DWORD(bufferSize - _remaining), &bytesRead, nullptr))
        {
            _error = true;
            return;
        }

        _remaining += bytesRead;
    }
}
