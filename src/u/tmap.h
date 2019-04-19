#pragma once
#include <type_traits>
//! Type functional utilities
namespace u::tmap
{
    namespace _detail
    {


        template <
            typename T,
            typename... Ts
        >
        struct contains: public std::false_type { };

        template <
            typename T,
            typename... Ts
        >
        struct contains<T, T, Ts...>: public std::true_type { };

        template <
            typename T,
            typename U,
            typename... Ts
        >
        struct contains<T, U, Ts...>: public contains<T, Ts...> { };
    }
    template <
        typename T,
        typename... Ts
    >
    using contains = _detail::contains<T, Ts...>;


    //! Pack type variable arguments for later use
    template <
        typename... Ts
    >
    struct tpack
    {
        template <
            template <typename...> typename R
        >
        using into = R<Ts...>;
    };


    //! Bind the given args for front use
    template <
        template <typename...> typename F,
        typename... Front
    >
    struct bind_front
    {
        template <
            typename... Args
        >
        using result = F<Front..., Args...>;
    };


    //! Apply a template "function" to each element in a pack.
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
        using head = typename F::template call<T>;
        using tail = typename map<F, Ts...>::result;
        using result = typename tail::template into<
            bind_front<
                tpack,
                head
            >::template result
        >;
    };
}
