#include "./test_msg.h"
#include "./input_socket.h"
#include "u/f/compose.h"
#include "u/p.h"
#include <iostream>
namespace {
using u::p;

namespace spec {
namespace input_socket {
    using ::msg::input_socket::Queue;
    using ::msg::input_socket::has_with_queue;
    using ::msg::input_socket::has_queue;
    using ::msg::input_socket::can_has_push;
    using ::msg::input_socket::has_push;
    using ::msg::input_socket::is_input_socket;
    using std::get;

    struct adt {
        Queue queue;
    };

    constexpr Queue queue(adt self)
    {
        return self.queue;
    }

    constexpr adt with_queue(adt, Queue q2)
    {
        return { q2 };
    }
#ifdef __clang__
    static_assert(&with_queue); // for un-emittance-warning
#endif
    static_assert(is_input_socket<adt>::value);
        static_assert(has_push<adt>::value);
            static_assert(std::is_default_constructible_v<adt>);
            static_assert(std::is_default_constructible_v<Queue>);
            static_assert(can_has_push<adt>::value);
                static_assert(has_queue<adt>::value);
                static_assert(has_with_queue<adt>::value);

    constexpr auto inpsock = adt{};
    static_assert(queue(inpsock).size() == config::MESSAGE_QUEUE_SIZE);


    using ::msg::input_socket::ByteChunk;
    static_assert( !!::msg::input_socket::push(adt{}, ByteChunk{}) );

#ifndef __clang__
    const auto pusher = [](std::optional<adt> a) -> std::optional<adt> {
        if (a)
            return ::msg::input_socket::push(std::move(*a), ByteChunk{});
        else
           return std::nullopt;
    };
    constexpr auto push_all = u::f::f2n<Queue{}.size()>(pusher);

    constexpr auto full = push_all(adt{});
    static_assert( !!full );
    static_assert( !::msg::input_socket::push(adt{*full}, ByteChunk{}) );
#endif
    void debug()
    {
    }
}//input_socket::
}//spec::
}//<anon>:

int msg::spec::main(int, char const*[])
{
    ::spec::input_socket::debug();
    return 0;
}
