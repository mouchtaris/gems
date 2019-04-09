#pragma once
#include "u/f/compose.h"
namespace msg
{
    struct System
    {
    };

    template <
        typename T
    >
    using Prop = std::function<T (System)>;
    namespace props
    {
        constexpr auto should_exit = [](System) { return true; };
    }


    inline bool should_exit(System)
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

    inline void main_loop()
    {
        System system;
        while(!should_exit(system))
            system = mods::loop(system);
    }
}
