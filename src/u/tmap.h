#pragma once
#include <type_traits>
#include "u/traits.h"
//! Type functional utilities
namespace u::tmap
{
    //! A simple type packager
    template <
        typename... Ts
    >
    struct tpack
    {
        template <
            template <typename...> typename R
        >
        using into = R<Ts...>;

        template <
            typename... Prefix
        >
        using prepend = tpack<Prefix..., Ts...>;
    };


    //! Dispatchy evaluation strategy
    template <
        typename F,
        typename... Args
    >
    using eval_t = decltype(
        eval(
            std::declval<F>(),
            std::declval<Args>()...
        )
    );


    //! Eval if a type has ::call<>
    template <
        typename F,
        typename... Args
    >
    auto eval(F, Args...)
    -> typename F::template call<Args...>;


    //! Bound type arguments to the front
    template <
        typename F,
        typename... Front
    >
    struct bound_front
    {
        template <
            typename... Args
        >
        using call = eval_t<F, Front..., Args...>;
    };

    //! Bind type argument to the front

    //! Apply a function to a pack of elements
    template <
        typename F,
        typename... Ts
    >
    struct map;

    template <
        typename F
    >
    struct map<F>
    {
        using result = tpack<>;
    };

    template <
        typename F,
        typename T,
        typename... Ts
    >
    struct map<F, T, Ts...>
    {
        using head = eval_t<F, T>;
        using tail = typename map<F, Ts...>::result;
        using result = typename tail::template into<bind_front<tpack, head>::template call>;
    };


    //! Does a pack contain an element
    template <
        typename T,
        typename... Ts
    >
    using contains = 
        typename map<
            bind_front<std::is_same, T>::template call,
            Ts...
        >::result::template into<
            std::disjunction
        >
    ;
}
