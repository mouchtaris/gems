#pragma once
#include "sock/common.h"
namespace app
{
    struct Configuration
    {
        sock::sockaddr_unix_path    socket_path;
    };

    //! Definitions for the total handler
    constexpr auto handlers = stdx::make_tuple(
        stdx::make_tuple("--socket_path=", &Configuration::socket_path )
    );
}
