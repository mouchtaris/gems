#include "./spec.h"
#include <tuple>
namespace
{
    constexpr auto modules = std::make_tuple(
        u::spec::spec{},
        sock::spec::spec{}
    );
}

int main(int, char**)
{
    std::apply(spec::run_runtime, modules);
    std::apply(spec::run_debug, modules);
    return 0;
}
