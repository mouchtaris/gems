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
        typename... Args
    >
    constexpr auto eval(map, Args...)
    {
        if constexpr (sizeof...(Args) <= 1) {
            return tpack<>{};
        }
        else {
            using args = tpack<Args...>;

            using F = head_t<args>;
            using elements = tail_t<args>;

            using head = eval_t<F, head_t<elements>>;

            constexpr auto tail_eval = []() {
                if constexpr (has_tail<elements>::value)
                    return typename tail_t<elements>::template into<eval_t, map, F>{};
                else
                    return tpack<>{};
            };
            using tail = decltype(tail_eval());

            return typename tail::template prepend<head>{};
        }
    }


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
