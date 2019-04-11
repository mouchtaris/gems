#include "u/arr/make_array.h"
#include "u/bchnk.h"
#include "u/defined.h"
#include "u/f/compose.h"
#include "u/p.h"
#include "u/test.h"
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
namespace defined {
    using ::u::defined;

    struct yes_defined {};
    struct yes_defined_2 { static constexpr bool defined = true; };
    struct not_defined { static constexpr bool defined = false; };

    static_assert(defined<yes_defined>::value);
    static_assert(defined<yes_defined_2>::value);
    static_assert(!defined<not_defined>::value);
}
namespace bytechunk {
    using namespace ::u::bchnk;
    using ::u::defined;

    constexpr auto bc = u::bchnk::adt<12>{};
    static_assert(bc.size() == 12);

    constexpr auto bc0 = ::u::bchnk::adt<13>{ {}, 5, 9 };
    static_assert(end(bc0) - begin(bc0) == bc0.size());
}
}}

int ::u::spec::main(int, char const*[])
{
    ::spec::make_array::debug();
    ::spec::compose::runtime();
    return 0;
}
