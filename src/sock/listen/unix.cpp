#include "./unix.h"
#include <sys/socket.h>
#include <sys/un.h>
using u::try_::stdtry;
using u::try_::wrap_std_error;
namespace sock::listen::unix_
{
    create_result create()
    {
        return {};
        // TODO: comment int
        //const auto create_op = std::bind(
        //    ::socket, AF_UNIX, SOCK_STREAM, 0
        //);
        //const auto create_try = wrap_std_error<errors::SocketCreation>(stdtry(create_op));

        //RETURN_IF_ERROR(create_try);

        //return sockfd_t { create_try.first() };
    }

    ::sockaddr_un address(sockaddr_unix_path path)
    {
        struct ::sockaddr_un serv_addr;
        ::bzero((char *) &serv_addr, sizeof(serv_addr));

        serv_addr.sun_family = AF_UNIX;

        ::strncpy(
            serv_addr.sun_path,
            path.value.container.data(),
            sizeof(serv_addr.sun_path) - 1
        );

        return serv_addr;
    }

    std::size_t address_len(::sockaddr_un serv_addr)
    {
        return 0u
            + ::strlen(serv_addr.sun_path)
            + sizeof(serv_addr.sun_family)
            ;
    }


    bind_result bind(const sockaddr_unix_path path)
    {
        (void)path;
        return {};
        //const auto sockfdTry = create();

        //if (is_error(sockfdTry))
        //    return sockfdTry;

        //const auto sockfd = sockfdTry.first();
        //const auto serv_addr = address(path);
        //const auto serv_len = address_len(serv_addr);

        //const auto bind_op = std::bind(
        //    ::bind,
        //    sockfd.value,
        //    reinterpret_cast<const struct ::sockaddr *>(&serv_addr),
        //    serv_len
        //);
        //const auto bind_try = wrap_std_error<errors::SocketBinding>(stdtry(bind_op));

        //RETURN_IF_ERROR(bind_try);

        //return sockfd;
    }
}
