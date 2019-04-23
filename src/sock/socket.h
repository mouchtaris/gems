#pragma once
#include "./common.h"
#include "u/try.h"
namespace sock
{
    //! A socket de-initialization error
    ///
    /// Can be thrown by socket constructors and destructors.
    using Closing = ::u::try_::adt<
        int,
        ::u::try_::StandardError
    >;

    //! A basic socket
    ///
    /// Mainly provides resource management (moving, cleaning up).
    ///
    struct socket
    {
        sockfd_t fd;

        socket() = delete;
        socket(socket const&) = delete;

        //! Move another socket
        ///
        /// Can throw a Closing instance, if de-initializing the
        /// other socket fails.
        ///
        /// @throws Closing
        socket(socket&&);

        //! Deinitialize this socket
        ///
        /// Can throw a Closing instance, if de-initializing
        /// this socket fails.
        ///
        /// @throws Closing
        ~socket();
    };
}
