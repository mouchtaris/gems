#pragma once
#include "./types.h"
namespace adt
{
    // constexpr size_t bytesize(TYPE);

    constexpr size_t bytesize(byte_t) { return 1; }
    constexpr stdx::size_t bytesize(stream_t) { return 0; }
    template <
        typename... Ts
    >
    constexpr stdx::size_t bytesize(u::tmap::tpack<Ts...> = {})
    {
        return stdx::apply(
            [](auto&&... vals)
            {
                return (
                    bytesize(stdx::forward<decltype(vals)>(vals)) + ...
                );
            },
            stx::tuple<Ts...>{}
        );
    }
}