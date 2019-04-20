#pragma once
#include "u/traits.h"
#include <type_traits>
#include <tuple>
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
            template <typename...> typename R,
            typename... ExtraFront
        >
        using into = R<ExtraFront..., Ts...>;

        template <
            typename... Prefix
        >
        using prepend = tpack<Prefix..., Ts...>;

        template <
            template <typename...> typename F,
            typename... ExtraFront
        >
        struct f
        {
            template <
                typename... ExtraBack
            >
            using call = F<ExtraFront..., Ts..., ExtraBack...>;
        };
    };


    //! Check if a tpack that has a head (not empty)
    template <
        typename T
    >
    struct has_head: public std::false_type { };

    template <
        typename H,
        typename... Ts
    >
    struct has_head<tpack<H, Ts...>>: public std::true_type
    {
        using head = H;
    };

    template <
        typename T
    >
    using head_t = typename has_head<T>::head;


    //! Check if a tpack has a tail (not empty)
    template <
        typename T
    >
    struct has_tail: public std::false_type { };

    template <
        typename H,
        typename... Ts
    >
    struct has_tail<tpack<H, Ts...>>: public std::true_type
    {
        using tail = tpack<Ts...>;
    };

    template <
        typename T
    >
    using tail_t = typename has_tail<T>::tail;


    //! Eval if a type has ::call<>
    template <
        typename F,
        typename... Args
    >
    auto eval(F, Args...)
    -> typename F::template call<Args...>;


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


    //! Apply a function to a pack of elements
    struct map{};
    template <
        typename F,
        typename... Args
    >
    constexpr auto eval(map, F, Args...)
    {
        if constexpr (sizeof...(Args) == 0)
            return tpack{};
        else {
            using elements = tpack<Args...>;
            using head = eval_t<F, head_t<elements>>;
            using tail = typename tail_t<elements>::template into<eval_t, map, F>;
            return typename tail::template prepend<head>{};
        }
    }


    //! Reduce a pack
    template <
        typename F,
        typename Zero,
        typename... Pack
    >
    struct reduce_eval;

    template <
        typename F,
        typename Zero
    >
    struct reduce_eval<F, Zero>
    {
        using result = Zero;
    };

    template <
        typename F,
        typename Zero,
        typename Head,
        typename... Tail
    >
    struct reduce_eval<F, Zero, Head, Tail...>
    {
        using result = typename reduce_eval<
            F,
            eval_t<F, Zero, Head>,
            Tail...
        >::result;
    };

    struct reduce
    {
        template <
            typename... Args
        >
        using call = typename reduce_eval<Args...>::result;
    };


    //! Does a pack contain an element
    //template <
    //    typename T,
    //    typename... Ts
    //>
    //using contains = eval_t<
    //    map,
    //    tpack<T>::template f<std::is_same>,
    //    Ts...
    //    typename map<
    //        bind_front<std::is_same, T>::template call,
    //        Ts...
    //    >::result::template into<
    //        std::disjunction
    //    >
    //;
}
