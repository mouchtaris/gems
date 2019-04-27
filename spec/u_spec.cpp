#include "./u_spec.h"
#include "./u/try_spec.h"
#include "./u/tmap_spec.h"
#include "./u/str_spec.h"
#include "./u/stdx_spec.h"
#include "./u/traitlib_spec.h"
#include "./u/view_spec.h"
#include "./u/make_array_spec.h"
#include "./u/compose_spec.h"
#include "./u/f_spec.h"
#include <tuple>
namespace u::spec
{
    constexpr auto modules = std::tuple {
        try_::spec{},
        tmap::spec{},
        str::spec{},
        stdx::spec{},
        traitlib::spec{},
        view::spec{},
        make_array::spec{},
        compose::spec{},
        f::spec{},
    };

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
