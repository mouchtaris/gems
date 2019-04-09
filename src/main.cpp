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

    bool should_exit(System)
    {
        return true;
    }

    using Mod = std::function<System (System)>;
    namespace mods
    {
        constexpr auto id = [](System system) { return system; };

        constexpr auto receive_messages = id;
        constexpr auto dispatch_messages = id;

        using u::f::operator>>;
        constexpr auto loop = id
            >> receive_messages
            >> dispatch_messages
        ;
    }

    void main_loop()
    {
        System system;
        while(!should_exit(system))
            system = mods::loop(system);
    }

}
int main(int argc, char const* argv[])
{
    main_loop();
    return u::spec::main(argc, argv);
}
