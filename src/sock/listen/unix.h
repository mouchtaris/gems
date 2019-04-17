#pragma once
#include "u/view.h"
#include "u/revar.h"
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

    using Creation = u::Errors<sockfd_t, errors::SocketCreation>;
    using Binding = Creation::into<u::Errors, errors::SocketBinding>;

    using create_result = Creation::into<std::variant>;
    using bind_result = Binding::into<std::variant>;

    create_result   create();
    ::sockaddr_un   address(sockaddr_path);
    std::size_t     address_len(::sockaddr_un);
    bind_result     bind(sockaddr_path);
}
