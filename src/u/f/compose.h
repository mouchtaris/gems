#pragma once
#include <functional>
namespace u::f
{
    //! Basic compose 2 functions implementation
    template <
        typename F,
        typename G
    >
    constexpr auto operator >>(F&& f, G&& g)
    {
        // Necessarily capture functions by copy.
        return [f, g] (auto&& x) -> decltype(auto)
        {
            // Forward argument properly.
            return g(f(std::forward<decltype(x)>(x)));
        };
    }

    //! Compose any number of functions.
    template <
        typename... Fs
    >
    constexpr auto compose(Fs&&... fs) -> decltype(auto)
    {
        if constexpr (sizeof...(Fs) == 0)
            return [](auto&& x) -> decltype(auto)
            {
                return std::forward<decltype(x)>(x);
            };
        else if constexpr (sizeof...(Fs) == 1)
            return ( ... , std::forward<Fs>(fs));
        else
            return (std::forward<Fs>(fs) >> ...);
    }

    template <
        std::size_t N,
        typename F
    >
    constexpr auto f2n(F&& f)
    {
        if constexpr (N <= 1)
            return f;
        else
            return compose(f, f2n<N - 1>(f));
    }
}
