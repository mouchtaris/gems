#pragma once
#include <functional>
namespace u::f
{
    //! Function composition for any number of functions
    //
    template <
        typename... Fs
    >
    struct Composer;

    //! Compose any number of functions.
    template <
        typename... Fs
    >
    constexpr auto compose(Fs&&... fs)
    {
        return Composer<Fs...>{}(std::forward<Fs>(fs)...);
    }

    //! Operator decoration for any number of functions
    template <
        typename F,
        typename G
    >
    constexpr auto operator >>(F&& f, G&& g)
    {
        return compose(
            std::forward<F>(f),
            std::forward<G>(g)
        );
    }

    //! Composer specilization for more than 2 functions
    template <
        typename F,
        typename... Fs
    >
    struct Composer<F, Fs...>
    {
        constexpr auto operator () (F&& f, Fs&&... fs) const &&
        {
            return f >> compose(std::forward<Fs>(fs)...);
        }
    };

    //! Composer specilization for 2 functions
    template <
        typename F,
        typename G
    >
    struct Composer<F, G>
    {
        constexpr auto operator () (F&& f, G&& g) const
        {
            // Necessarily capture functions by copy.
            return [f, g] (auto&& x)
            {
                // Forward argument properly.
                return g(f(std::forward<decltype(x)>(x)));
            };
        }
    };

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
