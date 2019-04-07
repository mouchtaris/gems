#pragma once
#include "index.h"
#include "lazy_conditional.h"
namespace util
{
//! Super epic
//
template <typename... Elements> struct Tuple;
//
template <> struct Tuple<>
{
    static constexpr bool empty = true;
    template <typename Index> using get = void;
};
//
template <
    typename Head,
    typename... Tail
>
struct Tuple<Head, Tail...>
{
    static constexpr bool empty = false;
    template <typename = void> using head_f = Head;
    template <typename = void> using tail_f = Tuple<Tail...>;
    using head = head_f<>;
    using tail = tail_f<>;

    template <
        typename i,
        typename = std::void_t<
            std::enable_if_t<index::is_index<i>::value, void>
        >
    >
    using get = std::conditional_t<
        index::value_v<i> == 0,
        Head,
        lazy_conditional_t<tail::empty,
            std::void_t,
            tail::template get,
            index::minus1<i>
        >
    >;

    template <typename Obj>
    using push_front = Tuple<Obj, Head, Tail...>;

    template <typename Obj>
    using push_back = Tuple<Head, Tail..., Obj>;

    using pop_front = tail;

    template <
        template <typename...> typename Constructor
    >
    using apply_to = Constructor<Head, Tail...>;
};

//! is_tuple
//
template <typename T> struct is_tuple: public std::false_type { };
//
template <
    typename... Elements
>
struct is_tuple<Tuple<Elements...>>: public std::true_type { };
}
