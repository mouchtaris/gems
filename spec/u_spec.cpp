#include "./u_spec.h"
#include "./u/try__spec.h"
#include "./u/tmap_spec.h"
namespace u::spec
{
    void debug()
    {
        try_::debug();
        tmap::debug();
    }
}
