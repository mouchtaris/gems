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

int main(int, char**)
{
    unix_socket::socket_manager fcgi_socket { unix_socket::create() };
    debug__(( fcgi_socket.fd ));
    debug__(( io::is_blocking(fcgi_socket.fd) ));

    unix_socket::socket_manager fcgi_client { fcgi_socket.accept() };
    debug__(( fcgi_client.fd ));
    debug__(( io::is_blocking(fcgi_client.fd) ));

    using fd_source = ::fd_source<1>;
    fd_source source { fcgi_client.fd };
    debug__(( io::is_blocking(source.fd) ));
    debug__(( io::can_read(source.fd) ));
    io::set_nonblocking(fcgi_client.fd, false);
    debug__(( io::is_blocking(source.fd) ));

    while (!io::can_read(source.fd))
        ;
    debug__(( io::can_read(source.fd) ));

    ::fcgi_record::bytes fcgi_record{};
    debug__(( ::read(source.fd, begin(fcgi_record.bytes), fcgi_record.remaining) ));
    debug__(( io::is_blocking(source.fd) ));

    const auto bs_try = emit(source);
    debug__(( std::holds_alternative<std_error>(bs_try) ));
    const auto bs_opt = std::get<std::optional<bytes::chunk<fd_source::chunk_size>>>(bs_try);
    debug__(( bs_opt.has_value() ));
    const auto bs = *bs_opt;
    debug__(( bs.remaining ));
    return 0;
}
