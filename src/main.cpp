#include "config.h"
#include "u/view.h"
#include "u/p.h"

#include "msg/input_socket.h"

#include "u/test_u.h"
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

namespace inc
{
    template <
        typename InputSockets,
    >
    struct SocketInterface
    {

    };
}


int main(int argc, char const* argv[])
{
    const bool success = true
        && u::spec::main(argc, argv) == 0
        && msg::spec::main(argc, argv) == 0
        ;
    return success? 0 : 1;
}
