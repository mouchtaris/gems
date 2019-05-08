#pragma once
#include "sock/common.h"
#include "u/tmap.h"
#include "bytebuf.h"
namespace adt
{
    struct byte_t{};
    struct stream_t{};

    //! Type byte size
    constexpr stdx::size_t bytesize(byte_t) { return 1; }
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
            stdx::tuple<Ts...>{}
        );
    }

    template <
        typename T
    >
    using bytes = ::bytes<bytesize(T{})>;
}
namespace fcgi::record
{
    using namespace adt;

    struct version: byte_t{};
    struct type: byte_t{};
    struct requestIdB1: byte_t{};
    struct requestIdB0: byte_t{};
    struct contentLengthB1: byte_t{};
    struct contentLengthB0: byte_t{};
    struct paddingLength: byte_t{};
    struct reserved: byte_t{};
    struct contentData: stream_t{};
    struct paddingData: stream_t{};

    using adt = u::tmap::tpack<
        struct version,
        struct type,
        struct requestIdB1,
        struct requestIdB0,
        struct contentLengthB1,
        struct contentLengthB0,
        struct paddingLength,
        struct reserved,
        struct contentData,
        struct paddingData
    >;
}
