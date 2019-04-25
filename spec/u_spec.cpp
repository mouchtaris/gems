#include "./u_spec.h"
#include "./u/try_spec.h"
#include "./u/tmap_spec.h"
#include "./u/str_spec.h"
#include "./u/stdx_spec.h"
#include <tuple>
namespace u::spec
{
    constexpr auto modules = std::make_tuple(
        try_::spec{},
        tmap::spec{},
        str::spec{},
        stdx::spec{}
    );

    void debug(spec)
    {
        std::apply(
            [](auto... x) { (..., debug(x)); },
            modules
        );
    }

    void runtime(spec)
    {
        std::apply(
            [](auto... x) { (..., runtime(x)); },
            modules
        );
    }
}
