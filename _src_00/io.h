#pragma once
namespace io
{
    int is_blocking(int fd);
    int set_nonblocking(int fd, bool non_blocking = true);
    int can_read(int fd);

    struct unblocker
    {
        int fd;
        int errno_;
        int blocking;
        int setting;

        unblocker(int);
        ~unblocker();
    };
}
