#include "config.h"
#include "u/view.h"
#include "u/p.h"

#include "msg/input_socket.h"

#include "msg/input_socket.h"
#include "msg/test_msg.h"

#include <type_traits>
#include <tuple>
#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <tuple>
//
#include <sys/select.h>
int select(
    int              nfds,
    fd_set           *readfds,
    fd_set           *writefds,
    fd_set           *errorfds,
    struct timeval   *timeout
);

namespace {
namespace inc
{
}
}

namespace
{
    constexpr auto nl = '\n';
    void help(int, char const* argv[])
    {
        std::cerr
            << "USAGE: " << argv[0] << " SOCKET_PATH" << nl
        ;
    }
}

int main(int argc, char const* argv[])
{
    const bool success = true
        && msg::spec::main(argc, argv) == 0
        ;

    if (argc < 2) {
        help(argc, argv);
        return 1;
    }

    return success? 0 : 1;
}
