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
    constexpr auto back = std::array<int, 4> {4,5,6,7};
    constexpr auto v0 = ::u::view::view { back };
    static_assert(v0.size() == 4);
    static_assert(v0.remaining() == 4);
    static_assert(v0.has_remaining());
    static_assert(v0.first == 0);
    static_assert(v0.pos == 0);
    static_assert(v0.limit == 4);
    static_assert(v0.last == 4);
    static_assert(*begin(v0) == back[0]);
    static_assert(begin(v0) != end(v0));
    static_assert(v0.container[0] == 4);
    static_assert(v0.container[1] == 5);
    static_assert(v0.container[2] == 6);
    static_assert(v0.container[3] == 7);

    constexpr auto v1 = v0.emplace_back(0);
    static_assert(v1->size() == 3);
    static_assert(v1->remaining() == 3);
    static_assert(v1->has_remaining());
    static_assert(v1->first == 0);
    static_assert(v1->pos == 1);
    static_assert(v1->limit == 4);
    static_assert(v1->last == 4);
    static_assert(*begin(*v1) == back[1]);
    static_assert(begin(*v1) != end(*v1));
    static_assert(v1->container[0] == 0);
    static_assert(v1->container[1] == 5);
    static_assert(v1->container[2] == 6);
    static_assert(v1->container[3] == 7);
    static_assert(*begin(v1->container) == 0);
    static_assert(*std::next(begin(v1->container), 1) == 5);
    static_assert(*begin(*v1) == 5);
    static_assert(::u::view::is_view<std::remove_reference_t<decltype(*v1)>>::value);
    static_assert(*::u::view::begin(*v1) == 5);


    constexpr auto v2 = v1->emplace_back(1);
    static_assert(v2->size() == 2);
    static_assert(v2->remaining() == 2);
    static_assert(v2->has_remaining());
    static_assert(v2->first == 0);
    static_assert(v2->pos == 2);
    static_assert(v2->limit == 4);
    static_assert(v2->last == 4);
    static_assert(*begin(*v2) == back[2]);
    static_assert(begin(*v2) != end(*v2));
    static_assert(v2->container[0] == 0);
    static_assert(v2->container[1] == 1);
    static_assert(v2->container[2] == 6);
    static_assert(v2->container[3] == 7);
    static_assert(*begin(v2->container) == 0);
    static_assert(*std::next(begin(v2->container), 1) == 1);
    static_assert(*std::next(begin(v2->container), 2) == 6);
    static_assert(*begin(*v2) == 6);
    static_assert(::u::view::is_view<std::remove_reference_t<decltype(*v2)>>::value);
    static_assert(*::u::view::begin(*v2) == 6);

    constexpr auto v3 = v2->emplace_back(2);
    static_assert(v3->size() == 1);
    static_assert(v3->remaining() == 1);
    static_assert(v3->has_remaining());
    static_assert(v3->first == 0);
    static_assert(v3->pos == 3);
    static_assert(v3->limit == 4);
    static_assert(v3->last == 4);
    static_assert(*begin(*v3) == back[3]);
    static_assert(begin(*v3) != end(*v3));
    static_assert(v3->container[0] == 0);
    static_assert(v3->container[1] == 1);
    static_assert(v3->container[2] == 2);
    static_assert(v3->container[3] == 7);
    static_assert(*begin(v3->container) == 0);
    static_assert(*std::next(begin(v3->container), 1) == 1);
    static_assert(*std::next(begin(v3->container), 2) == 2);
    static_assert(*std::next(begin(v3->container), 3) == 7);
    static_assert(::u::view::is_view<std::remove_reference_t<decltype(*v3)>>::value);
    static_assert(*::u::view::begin(*v3) == 7);

    constexpr auto v4 = v3->emplace_back(3);
    static_assert(v4->size() == 0);
    static_assert(v4->remaining() == 0);
    static_assert(!v4->has_remaining());
    static_assert(v4->first == 0);
    static_assert(v4->pos == 4);
    static_assert(v4->limit == 4);
    static_assert(v4->last == 4);
    //static_assert(*begin(*v4) == back[3]);
    static_assert(begin(*v4) == end(*v4));
    static_assert(v4->container[0] == 0);
    static_assert(v4->container[1] == 1);
    static_assert(v4->container[2] == 2);
    static_assert(v4->container[3] == 3);
    static_assert(*begin(v4->container) == 0);
    static_assert(*std::next(begin(v4->container), 1) == 1);
    static_assert(*std::next(begin(v4->container), 2) == 2);
    static_assert(*std::next(begin(v4->container), 3) == 3);
    //static_assert(*begin(*v4) == 7);
    static_assert(::u::view::is_view<std::remove_reference_t<decltype(*v4)>>::value);
    //static_assert(*::u::view::begin(*v4) == 7);

    constexpr auto v5 = v4->emplace_back(4);
    static_assert(v5 == std::nullopt);

    void debug()
    {
        debug__(( v0 ));
        debug__(( *v1 ));
        debug__(( *v2 ));
        debug__(( *v3 ));
        debug__(( *v4 ));
        debug__(( (v5 == std::nullopt ? "nullopt" : "SOMETHING") ));
    }
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
    ::spec::view::debug();
    ::spec::msg::input_socket::debug();
    return 0;
}
