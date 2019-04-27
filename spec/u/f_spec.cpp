#include "./f_spec.h"
#include "u/f.h"
#include "u/p.h"
#define st__(EXPR) static_assert__((EXPR))
namespace
{
    using namespace u::f;

    //
    // flip
    //
    constexpr auto sb = [](int a, int b) { return a - b; };
    st__(( sb(3, 2) == 1 ));
    st__(( flip(sb)(3, 2) == -1 ));
}
namespace u::spec::f
{
    void debug(spec)
    {
    }

    void runtime(spec)
    {
    }
}
