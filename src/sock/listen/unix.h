#pragma once
#include "u/view.h"
#include "u/tmap.h"
#include <variant>
#include <sys/un.h>
namespace sock::listen::unix_
{
    namespace errors
    {
        struct Error{};
        struct SocketCreation: public Error{};
        struct SocketBinding: public Error{};
    }

    struct sockfd_t { int value; };

    struct sockaddr_path {
        u::view::view<std::array<char, sizeof(::sockaddr_un{}.sun_path)>> value;
    };
    static_assert(sockaddr_path{}.value.size() == 108);

    using Creation = u::try_::adt<sockfd_t, errors::SocketCreation>;
    using Binding = u::try_::adt<errors::SocketBinding>;

    using create_result = Creation;
    using bind_result = Binding;

    create_result   create();
    ::sockaddr_un   address(sockaddr_path);
    std::size_t     address_len(::sockaddr_un);
    bind_result     bind(sockaddr_path);
}
