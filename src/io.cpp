#include "./io.h"
#include <fcntl.h>
#include <sys/select.h>
#include <unistd.h>

#include "p.h"
#include <iostream>

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

    namespace
    {
        constexpr ::timespec timeout{};
        static_assert(timeout.tv_sec == 0);
        static_assert(timeout.tv_nsec == 0);

        struct tmp_unblocker
        {
            int fd;
            int blocking;
            int set_nonblocking_status;

            tmp_unblocker(int fd):
                fd { fd }
            {
                if (fd < 0)
                    return;

                blocking = is_blocking(fd);
                if (blocking < 0)
                    return;

                set_nonblocking_status = set_nonblocking(fd);
            }

            ~tmp_unblocker()
            {
                if (fd < 0)
                    return;

                if (set_nonblocking_status < 0)
                    return;

                if (blocking < 0)
                    return;

                set_nonblocking(fd, !blocking);
            }
        };
    }
    int can_read(int fd)
    {
#if 0 // why?
        ::fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);
        assert__(( FD_ISSET(fd, &readfds) ));

        int status = ::pselect(1, &readfds, nullptr, nullptr, &timeout, nullptr);
        if (status < 0)
            return status;

        return FD_ISSET(fd, &readfds);
#else
        tmp_unblocker __unblocker { fd };

        int status = ::read(fd, nullptr, 0);
        if (status < 0)
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                return false; // cannot read
            else
                return status; // serious error
        else
            return true; // can read
#endif
    }
}
