#include "./unix.h"
#include <sys/socket.h>
#include <sys/un.h>
namespace sock::listen::unix_
{
    create_result create()
    {
        const int sockfd = ::socket(AF_UNIX, SOCK_STREAM, 0);
        if (sockfd < 0)
            return { errors::SocketCreation{} };
        return { sockfd };
    }

    ::sockaddr_un address(sockaddr_path path)
    {
        struct ::sockaddr_un serv_addr;
        ::bzero((char *) &serv_addr, sizeof(serv_addr));

        serv_addr.sun_family = AF_UNIX;

        ::strncpy(serv_addr.sun_path, path.container.data(), sizeof(serv_addr.sun_path) - 1);

        return serv_addr;
    }

    std::size_t address_len(::sockaddr_un serv_addr)
    {
        return 0u
            + ::strlen(serv_addr.sun_path)
            + sizeof(serv_addr.sun_family)
            ;
    }


    bind_result bind(sockaddr_path path)
    {
        // TODO comment in
        //const auto sockfdTry = create();
        //if (sockfdTry.is_failed())
        //    return sockfdTry;

        //const auto sockfd = std::get<sockfd_t>(sockfdTry);
        //const auto serv_addr = address(std::move(path));
        //const auto serv_len = address_len(serv_addr);

        //const int status = ::bind(
        //    sockfd,
        //    reinterpret_cast<const struct ::sockaddr *>(&serv_addr),
        //    serv_len
        //);

        //if (status < 0)
        //    return errors::SocketBinding{};

        //return sockfd;
        return {};
    }
}
