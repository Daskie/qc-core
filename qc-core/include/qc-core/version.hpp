#pragma once

#include <qc-core/core.hpp>

namespace qc
{
    struct alignas(u32) Version
    {
        SERIALIZABLE(3);

        u16 micro;
        u8 minor;
        u8 major;

        constexpr Version() = default;
        constexpr Version(u8 major, u8 minor, u16 micro);
        constexpr explicit Version(u32 v);

        constexpr explicit operator u32() const;

        constexpr bool operator==(const Version & other) const;
        constexpr std::strong_ordering operator<=>(const Version & other) const;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    inline constexpr Version::Version(const u8 major_, const u8 minor_, const u16 micro_) :
        micro{micro_},
        minor{minor_},
        major{major_}
    {}

    inline constexpr Version::Version(const u32 v)
    {
        *this = std::bit_cast<Version>(v);
    }

    inline constexpr Version::operator u32() const
    {
        return std::bit_cast<u32>(*this);
    }

    inline constexpr bool Version::operator==(const Version & other) const
    {
        return u32(*this) == u32(other);
    }

    inline constexpr std::strong_ordering Version::operator<=>(const Version & other) const
    {
        return u32(*this) <=> u32(other);
    }
}
