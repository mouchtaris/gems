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
    using contains0 = _detail::contains<T, Ts...>;


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

    template <
        template <typename...> typename
    >
    using needs_template_t = void;

    template <
        typename F,
        typename _impl = void
    >
    struct evaluation_strategy;

    template <
        typename F
    >
    struct evaluation_strategy<F, needs_template_t<F::template call>
    {
        template <
            typename... Args
        >
        using call = typename F::template call<Args...>;
    };

    template <
        typename F,
        typename... Args
    >
    using eval = evaluation_strategy<F>::call<Args...>;

    //! Bind the given args for front use
    template <
        typename F,
        typename... Front
    >
    struct bind_front
    {
        template <
            typename... Args
        >
        using call = eval<F, Front..., Args...>;
    };

    //! Turn a normal template to a function
    template <
        template <typename...> typename F
    >
    struct f {
    template <

        template <
            typename... Args
        >
        using call = F<Args...>;
    };

    //! Apply a template "function" to each element in a pack.
    struct map;

    template <
        typename F,
        typename... Args
    >
    struct eval_map;

    template <
        typename F
    >
    
        using result = tpack<>;
    };

    template <
        typename F,
        typename T,
        typename... Ts
    >
    struct map<F, T, Ts...>
    {
        using head = eval<F, T>;
        using tail = evalmap<F, Ts...>::result;
        using result = typename tail::template into<
            bind_front<
                tpack,
                head
            >::template call
        >;
    };


    //! Does a tpack contain a given type?
    template <
        typename T,
        typename... Ts
    >
    using contains2 =
        typename map<
            bind_front<
                std::is_same, T
            >,
            Ts...
        >::result::template into<
            std::conjunction
        >;
    ;

    template <
        typename T,
        typename... Ts
    >
    using contains = contains0<T, Ts...>;
}
