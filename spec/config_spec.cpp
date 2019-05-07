#include "./config_spec.h"
#include "./config/parse_spec.h"
#include "./spec.h"
#include "u/stdx.h"
#include <tuple>
namespace
{
    using namespace config::spec;
    constexpr auto modules = stdx::make_tuple(
        parse::spec{}
    );
}
namespace config::spec
{
    void debug(spec)
    {
        stdx::apply(::spec::run_debug, modules);
    }

    void runtime(spec)
    {
        stdx::apply(::spec::run_runtime, modules);
    }
}
