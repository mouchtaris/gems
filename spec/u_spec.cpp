#include "./u_spec.h"
#include "./u/try_spec.h"
#include "./u/tmap_spec.h"
#include "./u/str_spec.h"
#include "./u/stdx_spec.h"
namespace u::spec
{
    void debug()
    {
        try_::debug();
        tmap::debug();
        str::debug();
        stdx::debug();
    }

    void runtime()
    {
        str::runtime();
        stdx::runtime();
    }
}
