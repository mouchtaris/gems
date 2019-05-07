#include "./spec.h"
#include "./sock_spec.h"
#include "./u_spec.h"
#include "./config_spec.h"
#include "./fcgi_spec.h"
#include <tuple>
namespace
{
    constexpr auto modules = std::make_tuple(
        u::spec::spec{},
        sock::spec::spec{},
        config::spec::spec{},
        fcgi::spec::spec{}
    );
}

int main(int, char**)
{
    std::apply(spec::run_runtime, modules);
    std::apply(spec::run_debug, modules);
    return 0;
}
