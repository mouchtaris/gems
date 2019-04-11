#include "config.h"
#include "u/test.h"
#include "u/bchnk.h"
#include "u/view.h"
#include "u/p.h"
#include <type_traits>
#include <tuple>
#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <tuple>
//
#include <sys/select.h>
int select(
    int              nfds,
    fd_set           *readfds,
    fd_set           *writefds,
    fd_set           *errorfds,
    struct timeval   *timeout
);

namespace msg
{
    using ByteChunk = u::bchnk::adt<config::BYTE_CHUNK_SIZE>;

    //! InputSocket concept requirements
    TRAIT_COND(InputSocket, (
        std::is_same_v<
            decltype(
                push(
                    std::declval<T>(),
                    std::declval<ByteChunk>()
                )
            ),
            std::optional<T>
        >
    ));

    struct impl0_tag{};
    using impl0 = std::tuple<
        impl0_tag,
        u::view::view<std::array<ByteChunk, config::MESSAGE_QUEUE_SIZE>>
    >;

    std::optional<impl0> push(impl0 socket, ByteChunk chunk)
    {
        auto&& message_queue = std::get<1>(socket);
        auto&& message_queue2 = message_queue.emplace_back(std::move(chunk));

        if (!message_queue2.has_value())
            return std::nullopt;

        impl0 impl2 = {
            {},
            message_queue2.value()
        };
        return std::move(impl2);
    }
}

int main(int argc, char const* argv[])
{
    auto socket = msg::impl0{};
    push(socket, msg::ByteChunk{});
    static_assert(msg::InputSocket<msg::impl0>::value);
    return u::spec::main(argc, argv);
}
