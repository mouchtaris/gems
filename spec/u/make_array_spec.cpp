#include "./make_array_spec.h"
#include "u/arr/make_array.h"
#include "u/p.h"
#include <cstddef>
using u::p;
namespace
{
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
}
namespace u::spec::make_array
{
    void debug(spec)
    {
        debug__(( p<decltype(subj)>() ));
        debug__(( p<decltype(subj)::value_type>() ));
    }

    void runtime(spec)
    {
    }
}
