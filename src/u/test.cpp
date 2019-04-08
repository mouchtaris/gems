#include "u/test.h"
#include "u/arr/make_array.h"
#include "u/p.h"
#include "u/f/compose.h"
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

    static_assert(check(std::make_index_sequence<length>{}), "");

    void debug()
    {
        debug__(( p<decltype(subj)>() ));
        debug__(( p<decltype(subj)::value_type>() ));
    }
}
namespace compose {
    constexpr auto f = [](int x) { return x + 1; };
    constexpr auto g = [](int x) { return x - 1; };
    constexpr auto fog = u::f::compose(f, g);
    static_assert(fog(0) == 0, "");

    void runtime() {
        auto f_ = f;
        auto g_ = g;
        auto fog_ = u::f::compose(f_, g_);
        auto oops = []() { return false; };
        assert__(( fog_(0) == 0 ));
        assert__(( oops() ));

        auto persists = []() {
            return u::f::compose(
                [](int x) { return x + 1; },
                [](int x) { return x - 1; }
            );
        };
        assert__(( persists()(0) == 0 ));
    }
}}
}

int ::u::spec::main(int, char const*[])
{
    ::spec::make_array::debug();
    ::spec::compose::runtime();
    return 0;
}
