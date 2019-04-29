#include "./compose_spec.h"
#include "u/f/compose.h"
#include "u/p.h"
#define st__(EXPR) static_assert__(EXPR)
namespace
{
    using u::f::compose;
    constexpr auto f = [](int x) { return x + 1; };
    constexpr auto g = [](int x) { return x - 1; };
    constexpr auto fog = compose(f, g, f, g, f, g);
    st__(fog(0) == 0);
    st__(compose(f, g)(0) == 0);
    st__(compose(f)(0) == 1);
    st__(compose()(0) == 0);

    struct anon{};
    void runtime(anon)
    {
        auto f_ = f;
        auto g_ = g;
        auto fog_ = compose(f_, g_, f_, g_, f_, g_);
        auto oops = []() { return false; };
        assert__(( fog_(0) == 0 ));
        assert__(( oops() ));

        auto persists = []() {
           auto f = ([](int x) { return x + 1; });
           auto g = ([](int x) { return x - 1; });
           return compose(f, g, f, g, f, g);
        };
        assert__(( persists()(0) == 0 ));
    }
}
namespace u::spec::compose
{
    void debug(spec)
    {
    }

    void runtime(spec)
    {
        runtime(anon{});
    }
}
