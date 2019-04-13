#pragma once
#include "config.h"
#include "u/view.h"
#include <array>
namespace msg::input_socket
{
    //
    // ADT stuffs
    //

    using ByteChunk = u::view::view<
        std::array<std::byte, config::BYTE_CHUNK_SIZE>
    >;
    using Queue = u::view::view<
        std::array<ByteChunk, config::MESSAGE_QUEUE_SIZE>
    >;


    //
    // Input Socket Implementation Concept Reqquirements
    //

    TRAIT_COND(has_queue, (std::conjunction_v<
        u::view::is_view<decltype(queue(T{}))>
    >));

    TRAIT_COND(has_with_queue, (std::conjunction_v<
        std::is_same<
            std::remove_const_t<decltype(with_queue(T{}, Queue{}))>,
            T
        >
    >));

    TRAIT_COND(can_has_push, (std::conjunction_v<
        has_queue<T>,
        has_with_queue<T>
    >));


    //! Push a message to the input socket
    /// Conditionally accept a message in the input socket.
    /// If the socket cannot accept any more messages,
    /// return nullopt. If the socket can accept messages, return
    /// a modified socket with the message appended to the queue.
    template <
        typename InputSocket,
        typename = u::traits::enable_if<can_has_push<std::remove_reference_t<InputSocket>>::value>
    >
    constexpr std::optional<InputSocket> push(InputSocket&& socket, ByteChunk&& chunk)
    {
        auto&& q0 = queue(socket);
        auto&& q1 = q0.emplace_back(std::move(chunk));
        if (q1)
            return with_queue(std::move(socket), *q1);
        else
            return std::nullopt;
    }


    //
    // Input Socket Concept Requirements
    //

    TRAIT_COND(has_push, (
        std::is_same_v<
            decltype( push(T{}, ByteChunk{}) ),
            std::optional< T >
        >
    ));

    TRAIT_COND(is_input_socket, (std::conjunction_v<
        has_push<T>
    >));


    //! Default implementation
    struct Default
    {
        Queue q;
    };
    inline Queue queue(Default d) { return d.q; }
    inline Default with_queue(Default, Queue q2) { return { q2 }; }
    static_assert( is_input_socket<Default>::value );

}
