#include "./fcgi_spec.h"
#include "spec.h"
#include "./fcgi/record_spec.h"
#include "u/stdx.h"
#include <tuple>
namespace
{
    using namespace fcgi::spec;

    constexpr auto modules = std::make_tuple(
        record::spec{}
    );
}
namespace fcgi::spec
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
