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

#include "u/f/compose.h"
namespace {

    struct System
    {
    };

    using Mod = std::function<System (System)>;
    namespace mods
    {
        constexpr auto receive_messages = [](System system)
        {
            return system;
        };
    }

    void mfain_loop()
    {
        System system;
        mods::receive_messages(system);
    }

}
int main(int argc, char const* argv[])
{
    return u::spec::main(argc, argv);
}
