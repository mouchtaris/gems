#pragma once
#include "u/view.h"
#include "u/try_.h"
#include <variant>
#include <sys/un.h>
namespace sock::listen::unix_
{
    namespace errors
    {
        struct SocketCreation{};
        struct SocketBinding{};
    }

    using sockfd_t = int;
    using sockaddr_path = u::view::view<std::array<char, sizeof(::sockaddr_un{}.sun_path)>>;
    static_assert(sockaddr_path{}.size() == 108);

    using Creation = u::try_<sockfd_t, errors::SocketCreation>;
    using Binding = Creation::or_error<errors::SocketBinding>;

    using create_result = Creation;
    using bind_result = Binding;

    create_result   create();
    ::sockaddr_un   address(sockaddr_path);
    std::size_t     address_len(::sockaddr_un);
    bind_result     bind(sockaddr_path);
}
