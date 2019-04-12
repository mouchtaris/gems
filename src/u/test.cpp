#include "u/arr/make_array.h"
#include "u/f/compose.h"
#include "u/p.h"
#include "u/test.h"
#include "u/view.h"
#include "msg/input_socket.h"
#include <iostream>
#include <type_traits>
#include <algorithm>
using u::p;

namespace {
namespace spec {
namespace make_array {
    constexpr std::size_t length = 58;
    using type = char;
    constexpr type source[length] = {1, 2, 3, 4, 5, 90, 34, 121, 67, 2};

    constexpr auto subj = u::arr::make_array(source);

    template <std::size_t... I>
    constexpr bool check(std::index_sequence<I...>)
    {
        return
            std::is_same_v<decltype(subj)::value_type, std::add_const_t<type>> &&
            ((source[I] == subj[I]) && ...) &&
            true
        ;
    }

    static_assert(check(std::make_index_sequence<length>{}));

    void debug()
    {
        debug__(( p<decltype(subj)>() ));
        debug__(( p<decltype(subj)::value_type>() ));
    }
}
namespace compose {
    using u::f::compose;
    constexpr auto f = [](int x) { return x + 1; };
    constexpr auto g = [](int x) { return x - 1; };
    constexpr auto fog = compose(f, g, f, g, f, g);
    static_assert(fog(0) == 0);

    void runtime() {
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
namespace view {
    constexpr auto back = std::array<int, 4> {};
    constexpr auto v0 = ::u::view::view { back };
}
namespace msg::input_socket {
    using ::msg::input_socket::Queue;
    using ::msg::input_socket::has_with_queue;
    using ::msg::input_socket::has_queue;
    using ::msg::input_socket::can_has_push;
    using ::msg::input_socket::has_push;
    using ::msg::input_socket::is_input_socket;
    using std::get;

    struct adl {};
    using adt = std::tuple<adl, Queue>;

    constexpr Queue queue(adt self)
    {
        return get<1>(self);
    }

    constexpr adt with_queue(adt, Queue q2)
    {
        using std::get;
        return { {}, q2 };
    }
    static_assert(is_input_socket<adt>::value);
        static_assert(has_push<adt>::value);
            static_assert(std::is_default_constructible_v<adt>);
            static_assert(std::is_default_constructible_v<Queue>);
            static_assert(can_has_push<adt>::value);
                static_assert(has_queue<adt>::value);
                static_assert(has_with_queue<adt>::value);

    constexpr auto inpsock = adt{{}, {}};;
    static_assert(queue(inpsock).size() == config::MESSAGE_QUEUE_SIZE);
    void debug()
    {
        debug__(( queue(inpsock).size() ));
    }
}
}}

int ::u::spec::main(int, char const*[])
{
    ::spec::make_array::debug();
    ::spec::compose::runtime();
    ::spec::msg::input_socket::debug();
    return 0;
}
