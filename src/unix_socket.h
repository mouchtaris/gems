#pragma once
namespace unix_socket
{
    int create();
    int close(int sockfd);
    int accept(int sockfd);

    struct socket_manager
    {
        int fd;

        int accept()
        {
            return unix_socket::accept(fd);
        }

        ~socket_manager()
        {
            close(fd);
        }
    };
}
