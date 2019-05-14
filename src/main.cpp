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












template <
    typename Chunk
>
struct read_completely_stage
{
    Chunk chunk;
    // TODO add send_back for unconsumed bytes
};
template <
    typename Chunk
>
read_completely_stage(Chunk&&) -> read_completely_stage<Chunk>;

template <
    typename Network,
    typename Chunk,
    std::size_t ChunkSize
>
decltype(auto) on_push(Network&& net, read_completely_stage<Chunk>& stage, bytes::chunk<ChunkSize> chunk)
{
    auto&& remainder = chunk.copy(stage.chunk);
    (void) remainder; // TODO: send_back

    if (stage.chunk.remaining == 0) {
        return push(std::forward<Network>(net), std::move(stage.chunk));
    }

    return std::forward<Network>(net);
}


template <typename... Ops> struct overload: Ops... { using Ops::operator()...; };
template <typename... Ops> overload(Ops&&...) -> overload<Ops...>;



int main(int, char**)
{
    unix_socket::socket_manager fcgi_listener { unix_socket::create() };
    return 0;
}
