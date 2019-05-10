#pragma once
namespace unix_socket
{
    int create();
    int close(int sockfd);
    int accept(int sockfd);

    struct listening_socket
    {
        int fd = create();

        int accept()
        {
            return unix_socket::accept(fd);
        }

        ~listening_socket()
        {
            close(fd);
        }
    };
}
