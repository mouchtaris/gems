#pragma once
#include "./common.h"
namespace sock
{
    //! A basic socket
    ///
    /// Mainly provides resource management (moving, cleaning up).
    ///
    struct socket
    {
        sockfd_t fd;

        socket() = delete;
        socket(socket const&) = delete;
        socket(socket&&);
        ~socket();
    };
}
