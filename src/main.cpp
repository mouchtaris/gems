#include "unix_socket.h"
#include "fcgi.h"
#include "bytes.h"
#include "p.h"
#include "io.h"
#include <iostream>
#include <sys/select.h>
#include <unistd.h>
#include <optional>
#include <variant>

template <
    std::size_t ChunkSize
>
struct fd_source
{
    constexpr static std::size_t chunk_size = ChunkSize;
    int fd;
};

struct std_error
{
    int code = errno;
};

template <
    std::size_t ChunkSize
>
auto emit(fd_source<ChunkSize> source)
->
    std::variant<
        std_error,
        std::optional<bytes::chunk<ChunkSize>>
    >
{
    const int can_read = io::can_read(source.fd);
    if (can_read < 0)
        return std_error{};
    if (can_read == 0)
        return std::nullopt;

    bytes::chunk<ChunkSize> bs;
    const int read = ::read(source.fd, begin(bs), bs.remaining);
    if (read < 0)
        return std_error{};
    return bs.next(read).flip();
}



template <
    std::size_t ChunkSize
>
struct read_completely_stage
{
    bytes::chunk<ChunkSize> chunk;
};

template <
    typename Stream,
    std::size_t ChunkSize
>
Stream&& push(Stream&& stream, read_completely_stage<ChunkSize> stage, bytes::chunk<ChunkSize> chunk)
{
    auto&& remainder = chunk.copy(stage.chunk);

}


int main(int, char**)
{
    unix_socket::socket_manager fcgi_socket { unix_socket::create() };
    unix_socket::socket_manager fcgi_client { fcgi_socket.accept() };

    using fd_source = ::fd_source<1>;
    fd_source source { fcgi_client.fd };
    io::set_nonblocking(fcgi_client.fd, false);

    while (!io::can_read(source.fd))
        ;

    const auto bs_try = emit(source);
    const auto bs_opt = std::get<std::optional<bytes::chunk<fd_source::chunk_size>>>(bs_try);
    const auto bs = *bs_opt;

    ::fcgi_record::bytes fcgi_record{};

    (void)bs;
    (void)fcgi_record;
    return 0;
}
