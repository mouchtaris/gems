#pragma once
#include <functional>
namespace u::f
{
    template <
        typename F,
        typename G
    >
    constexpr auto compose(F&& f, G&& g)
    {
        // Necessarily capture functions by copy.
        return [f, g](auto&& x)
        {
            // Forward argument properly.
            return g(f(std::forward<decltype(x)>(x)));
        };
    }
}
