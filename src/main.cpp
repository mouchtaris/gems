#include "unix_socket.h"
#include "fcgi.h"
#include "bytes.h"
#include "p.h"
#include "io.h"
#include <iostream>
#include <sys/select.h>

struct fd_source
{
    int fd;
};

bool can_pull(fd_source src)
{
    ::fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(src.fd, &readfds);
    constexpr ::timespec timespec{};
    static_assert(timespec.tv_sec == 0);
    static_assert(timespec.tv_nsec == 0);
    int status = ::pselect(1, &readfds, nullptr, nullptr, &timespec, nullptr);
    if (status < 0)
        return false;
    return FD_ISSET(src.fd, &readfds) != 0;
}

int main(int, char**)
{
    unix_socket::socket_manager fcgi_socket { unix_socket::create() };
    debug__(( fcgi_socket.fd ));
    debug__(( io::is_blocking(fcgi_socket.fd) ));

    unix_socket::socket_manager fcgi_client { fcgi_socket.accept() };
    debug__(( fcgi_client.fd ));
    debug__(( io::is_blocking(fcgi_client.fd) ));

    ::fd_source source { fcgi_client.fd };
    debug__(( can_pull(source) ));
    debug__(( io::is_blocking(source.fd) ));

    return 0;
}
