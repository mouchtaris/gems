#pragma once
#include "std_error.h"
#include "io.h"
#include "bytes.h"
#include <cstdint>
#include <unistd.h>
#include <variant>
template <
    std::size_t ChunkSize
>
struct fd_source
{
    constexpr static std::size_t chunk_size = ChunkSize;
    int fd;
};

template <
    std::size_t ChunkSize
>
auto can_emit(fd_source<ChunkSize> const& source)
-> std::variant<std_error, bool>
{
    const int can_read = io::can_read(source.fd);

    if (can_read < 0)
        return std_error{};

    if (can_read == 0)
        return false;

    return true;
}

template <
    typename Network,
    std::size_t ChunkSize
>
decltype(auto) on_emit(Network&& net, fd_source<ChunkSize> const& source)
{
    auto&& can_emit_try = can_emit(source);
    if (std::holds_alternative<std_error>(can_emit_try))
        return error(std::forward<Network>(net), std::get<std_error>(std::move(can_emit_try)));

    const bool can_read = std::get<bool>(std::move(can_emit_try));

    if (!can_read)
        return std::forward<Network>(net);

    bytes::chunk<ChunkSize> bs;
    const int read = ::read(source.fd, begin(bs), bs.remaining);

    if (read < 0)
        return error(std::forward<Network>(net), std_error{});

    return push(std::forward<Network>(net), std::move(bs).next(read).flip());
}
