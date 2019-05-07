#pragma once
#include "u/stdx.h"
#include "u/str.h"
#include "u/f/compose.h"
#include <string_view>
namespace config
{
    //! Set a member value from a string value, using str::scanf().
    template <
        typename Self,
        typename T
    >
    constexpr Self& set(Self& self, T Self::*ptr, stdx::string_view value)
    {
        u::str::scanf(self.*ptr, stdx::move(value));
        return self;
    }

    //! Make a Self mod (Self => Self) that sets that value on
    /// pair.1 if the argument starts with the prefix pair.0.
    template <
        typename Self,
        typename T
    >
    constexpr auto make_set_if_prefix_handler(
            stdx::tuple<char const*, T Self::*> pair,
            stdx::string_view arg)
    {
        using stdx::get;

        return [&pair, arg](Self& config) -> Self&
        {
            const stdx::string_view prefix = u::str::view(get<0>(pair));

            if (starts_with(arg, prefix)) {
                T Self::*target = get<1>(pair);
                stdx::string_view&& value = arg.substr(prefix.size());

                set(config, FWD(target), stdx::move(value));
            }

            return config;
        };
    }

    //! Make a total handler (Self => Self) from all handlers defined
    /// in pairs, with make_set_if_prefix_handler().
    constexpr auto make_total_handler_factory = [](auto&&... pairs)
    {
        return [&pairs...](stdx::string_view arg)
        {
            return u::f::compose(make_set_if_prefix_handler(pairs, stdx::move(arg))...);
        };
    };

    //! Parse args with the if-prefix-* handlers given
    template <
        typename Self,
        typename Args,
        typename Handlers
    >
    constexpr decltype(auto) parse_args(Handlers&& handlers, Args&& args, Self&& config)
    {
        const auto total_handler_factory = stdx::apply(
            make_total_handler_factory,
            stdx::forward<Handlers>(handlers)
        );

        for (std::string_view arg: FWD(args))
            total_handler_factory(stdx::move(arg))(config);

        return stdx::forward<Self>(config);
    }
}
