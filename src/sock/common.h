#pragma once
#include "u/try.h"
#include "u/view.h"
#include <sys/un.h>
namespace sock
{
    //! Common types and fun for all of socketing
    inline namespace common
    {
        //! Errors that can happen when having fun with sockets.
        namespace errors
        {
            //! Base error type for socket fun
            struct Error: public u::try_::StandardErrorWrapper
            {
                using u::try_::StandardErrorWrapper::StandardErrorWrapper;
            };

            //! A socket creation error
            /// Can happen when trying to create a socket.
            struct SocketCreation: public Error
            {
                using Error::Error;
            };

            //! A socket binding error
            /// Can happen when trying to bind a socket.
            struct SocketBinding: public Error{};

            //! A socket de-initialization error
            /// Can happen when closing/destroying a socket.
            struct Closing: public Error{};
        }

        struct sockfd_t { int value; };

        using sockaddr_unix_path = u::view::view<std::array<char, sizeof(::sockaddr_un{}.sun_path)>>;
#if defined(unix)
        static_assert(sockaddr_unix_path{}.size() == 108);
#elif defined(__APPLE__)
        // TODO: figure mac size
        //static_assert(sockaddr_unix_path{}.value.size() == 108);
#endif

        using Creation = u::tmap::tpack<sockfd_t, errors::SocketCreation>;
        using Binding = Creation::append<errors::SocketBinding>;

        using create_result = Creation::into<u::try_::adt>;
        using bind_result = Binding::into<u::try_::adt>;
    }
}
