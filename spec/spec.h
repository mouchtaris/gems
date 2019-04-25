#pragma once
#include "./sock_spec.h"
#include "./u_spec.h"
namespace spec
{
    constexpr auto run_debug = [](auto... mods)
    {
        (..., debug(mods));
    };

    constexpr auto run_runtime = [](auto... mods)
    {
        (..., runtime(mods));
    };
}
