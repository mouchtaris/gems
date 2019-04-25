#pragma once
#include "u/try.h"
#include "u/view.h"
#include <sys/un.h>
namespace sock
{
    inline namespace common
    {
        namespace errors
        {
            struct Error: public u::try_::Error
            {
                u::try_::StandardError stderror;
            };
            struct SocketCreation: public Error{};
            struct SocketBinding: public Error{};
        }

        struct sockfd_t { int value; };

        struct sockaddr_unix_path {
            u::view::view<std::array<char, sizeof(::sockaddr_un{}.sun_path)>> value;
        };
        static_assert(sockaddr_unix_path{}.value.size() == 108);

        using Creation = u::tmap::tpack<sockfd_t, errors::SocketCreation>;
        using Binding = Creation::append<errors::SocketBinding>;

        using create_result = Creation::into<u::try_::adt>;
        using bind_result = Binding::into<u::try_::adt>;
    }
}
