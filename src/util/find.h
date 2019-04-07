#pragma once
#include "tuple.h"
namespace util
{
//! Find
//
template <
    template <typename...> typename Predicate,
    typename Tuple,
    typename = void
>
struct Find { };

template <
    template <typename...> typename Predicate,
    typename Tuple
>
struct Find<
    Predicate,
    Tuple,
    std::void_t<
        std::enable_if_t<is_tuple<Tuple>::value, void>,
        std::enable_if_t<!Tuple::empty, void>,
        decltype(Predicate<typename Tuple::head>::value)
    >
>
{
    using index = void;
};
}
