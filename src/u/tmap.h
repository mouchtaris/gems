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

        template <
            std::size_t i
        >
        using get = std::
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


    //! Apply a function to a pack of elements
    struct map;
    template <
        typename... Args
    >
    constexpr auto eval(map)
    {
        if constexpr (sizeof...(Args) == 0)
            return std::declval<tpack<>>();
        else if constexpr (sizeof...(
    }


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
