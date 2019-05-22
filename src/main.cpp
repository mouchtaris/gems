#include "unix_socket.h"
#include "fcgi.h"
#include "bytes.h"
#include "p.h"
#include "fd_source.h"
#include "io.h"
#include "std_error.h"
#include <iostream>
#include <sys/select.h>
#include <unistd.h>
#include <optional>
#include <variant>
#include <cstring>
#include <tuple>
#include "stream.h"

template <typename... Ops> struct overload: Ops... { using Ops::operator()...; };
template <typename... Ops> overload(Ops&&...) -> overload<Ops...>;

struct socket_accepting_source
{
    int fd;
};
auto emit(socket_accepting_source source)
    -> std::variant<
        std_error,
        std::optional<int>
    >
{
    io::unblocker tmp_unblock { source.fd };
    if (tmp_unblock.blocking < 0 || tmp_unblock.setting < 0)
        return std_error { tmp_unblock.errno_ };

    const int accepted = unix_socket::accept(source.fd);

    if (accepted < 0)
        if (errno == EWOULDBLOCK || errno == EAGAIN)
            return std::nullopt;
        else
            return std_error{};
    else
        return accepted;
}

struct filter_emittions_stage{};
template <
    typename Sink
>
auto on_push(filter_emittions_stage&&, std::variant<std_error, std::optional<int>> && val, Sink&& sink)
{

}

int main(int, char**)
{
    socket_accepting_source source { unix_socket::create() };
    return 0;
}
