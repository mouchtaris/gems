#include "config.h"
#include "u/test.h"
#include <type_traits>
#include <tuple>
#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
//
#include <sys/select.h>
int select(int nfds, fd_set  *readfds, fd_set  *writefds, fd_set *errorfds, struct timeval *timeout);
#include "msg/system.h"

int main(int argc, char const* argv[])
{
    msg::main_loop();
    return u::spec::main(argc, argv);
}
