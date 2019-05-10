#include "unix_socket.h"
#include "fcgi.h"
#include "bytes.h"
#include "p.h"
#include "io.h"
#include <iostream>
#include <sys/select.h>
#include <unistd.h>

struct fd_source
{
    int fd;
};

int main(int, char**)
{
    unix_socket::socket_manager fcgi_socket { unix_socket::create() };
    debug__(( fcgi_socket.fd ));
    debug__(( io::is_blocking(fcgi_socket.fd) ));

    unix_socket::socket_manager fcgi_client { fcgi_socket.accept() };
    debug__(( fcgi_client.fd ));
    debug__(( io::is_blocking(fcgi_client.fd) ));

    ::fd_source source { fcgi_client.fd };
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
    return 0;
}
