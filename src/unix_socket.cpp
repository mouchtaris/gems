#include "./unix_socket.h"
#include <sys/socket.h> // sockaddr, sockert(), bind(), listen(), accept()
#include <sys/un.h> // sockaddr_un
#include <algorithm>
#include <string_view>
#include <unistd.h> // close
#include <cstdio> // stderr
#include <sys/stat.h> // chmod
#include <fcntl.h> // fcntl
namespace unix_socket
{
    namespace
    {
        constexpr auto path = std::string_view { "/tmp/m3.sock" };

        sockaddr_un make_address()
        {
            sockaddr_un result;

            constexpr auto zero_begin_i = path.size();
            constexpr auto zero_end_i = sizeof(result.sun_path) / sizeof(*result.sun_path);
            const auto zero_begin = std::next(result.sun_path, zero_begin_i);
            const auto zero_end = std::next(result.sun_path, zero_end_i);

            result.sun_family = AF_UNIX;

            std::copy(begin(path), end(path), result.sun_path);
            std::fill(zero_begin, zero_end, 0x00);

            return result;
        }

        constexpr auto addr_len = path.size() + sizeof(sockaddr_un{}.sun_family);

        int bind(int sockfd)
        {
            const auto address = make_address();
            return ::bind(
                sockfd,
                reinterpret_cast<sockaddr const*>(&address),
                sizeof(sockaddr_un)
            );
        }

        int set_blocking(int sockfd, bool blocking = true)
        {
            int flags = ::fcntl(sockfd, F_GETFL, 0);
            if (flags < 0)
                return flags;

            if (blocking)
                flags &= ~O_NONBLOCK;
            else
                flags |= O_NONBLOCK;

            return ::fcntl(sockfd, F_SETFL, flags) != -1 ? 0 : -1;
        }
    }

    int create()
    {
        int sockfd = ::socket(AF_UNIX, SOCK_STREAM, 0);
        if (sockfd < 2)
            return sockfd;

        int status = bind(sockfd); // local bind
        if (status < 0)
            return status;

        status = ::listen(sockfd, 0);
        if (status < 0)
            return status;

        status = ::chmod(path.data(), 0777);
        if (status < 0)
            return status;

        status = set_blocking(sockfd, false);
        if (status < 0)
            return status;

        return sockfd;
    }

    int close(int sockfd)
    {
        int status = ::shutdown(sockfd, ::SHUT_RDWR);
        if (status < 0)
            return status;

        status = ::close(sockfd);
        if (status < 0)
            return status;

        return ::unlink(path.data());
    }

    int accept(int sockfd)
    {
        ::sockaddr_un cli_addr;
        unsigned int cli_addr_len = sizeof(cli_addr);

        int clifd = ::accept(
            sockfd,
            reinterpret_cast<sockaddr*>(&cli_addr),
            &cli_addr_len
        );
        if (clifd < 0)
            return clifd;

        fprintf(stderr, "Accepted %d %s.\n", clifd, cli_addr.sun_path);
        return clifd;
    }
}
