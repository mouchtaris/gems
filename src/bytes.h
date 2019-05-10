#pragma once
#include <cstdint>
#include <array>
#include <algorithm>
namespace bytes
{
    using byte_t = uint8_t;

    // TODO: config
    constexpr std::size_t DEFAULT_BYTECHUNK_SIZE = 1024;

    template <
        std::size_t Size = DEFAULT_BYTECHUNK_SIZE
    >
    struct chunk
    {
        constexpr static std::size_t size = Size;

        std::array<byte_t, Size> bytes;
        std::size_t offset = 0;
        std::size_t remaining = Size;
    };

    template <
        std::size_t Size
    >
    constexpr byte_t* begin(chunk<Size>& chunk)
    {
        return std::next(begin(chunk.bytes), chunk.offset);
    }

    template <
        std::size_t Size
    >
    constexpr byte_t const* begin(chunk<Size> const& chunk)
    {
        return std::next(begin(chunk.bytes), chunk.offset);
    }

    template <
        std::size_t Size
    >
    constexpr byte_t const* end(chunk<Size> const& chunk)
    {
        return std::next(begin(chunk), chunk.remaining);
    }

    template <
        std::size_t SizeFrom,
        std::size_t SizeTo
    >
    constexpr chunk<SizeFrom> copy(chunk<SizeFrom> const& from, chunk<SizeTo>& into)
    {
        const auto n = std::min(from.remaining, into.remaining);
        std::copy_n(begin(from), n, begin(into));

        auto result = from;
        result.remaining -= n;
        into.remaining -= n;
        return result;
    }
}
