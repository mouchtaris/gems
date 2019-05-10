#include "./io.h"
#include <fcntl.h>
namespace io
{
    int fd_flags(int fd)
    {
        int flags = ::fcntl(fd, F_GETFL, 0);
        if (flags < 0)
            return -1;
        return flags;
    }

    int set_nonblocking(int fd, bool non_blocking)
    {
        int flags = fd_flags(fd);
        if (flags < 0)
            return flags;

        if (non_blocking)
            flags |= O_NONBLOCK;
        else
            flags &= ~O_NONBLOCK;

        return ::fcntl(fd, F_SETFL, flags) != -1 ? 0 : -1;
    }

    int is_blocking(int fd)
    {
        int flags = fd_flags(fd);
        if (flags < 0)
            return flags;

        if ((flags & O_NONBLOCK) != 0)
            return 0;
        else
            return 1;
    }
}
