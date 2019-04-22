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
        static constexpr std::size_t size = sizeof...(Ts);

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
    using head = typename has_head<T>::head;


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
    using tail = typename has_tail<T>::tail;


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


    //! Check if a function is defined at the given arguments
    /// (or at all).
    template <
        typename F,
        typename ArgPack,
        typename = void
    >
    struct is_defined: public std::false_type { };

    template <
        typename F,
        typename ArgPack
    >
    struct is_defined<
        F,
        ArgPack,
        std::void_t<
            typename ArgPack::template into<eval_t, F>
        >
    >
    : public std::true_type { };

    template <
        typename F,
        typename... Args
    >
    constexpr bool is_defined_v = is_defined<F, tpack<Args...>>::value;


    //! Apply a function to a pack of elements
    struct map { };
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
            using head = eval_t<F, head<elements>>;
            using tail = typename tail<elements>::template into<eval_t, map, F>;
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


    //! An or_else idea
    struct or_else { };
    template <
        typename T
    >
    constexpr auto eval(or_else, tpack<>, T) -> T { }

    template <
        typename T
    >
    constexpr auto eval(or_else, tpack<>, tpack<T>) -> tpack<T> { }

    template <
        typename A,
        typename B
    >
    constexpr auto eval(or_else, A, B) -> A { }


    //! Find an element from a pack matching a predicate
    namespace _detail
    {
        template <
            typename Predicate
        >
        struct predicate_to_option {};

        template <
            typename Predicate,
            typename... Args
        >
        constexpr auto eval(predicate_to_option<Predicate>, Args...)
        -> std::conditional_t<
            eval_t<Predicate, Args...>::value,
            tpack<Args...>,
            tpack<>
        >
        { }
    }
    struct find_if { };
    template <
        typename Predicate,
        typename... Elements
    >
    constexpr auto eval(find_if, Predicate, Elements...)
    {
        using mapped = eval_t<map, _detail::predicate_to_option<Predicate>, Elements...>;
        using result = typename mapped::template into<eval_t, reduce, or_else>;
        return result{};
    }


    //! Turn a function into a partial function.
    ///
    /// Return the result of the original function in a tpack<>
    /// if the original function is defined, and an empty
    /// tpack<> otherwise.
    template <
        typename F
    >
    struct partial { };
    template <
        typename F,
        typename... Args
    >
    constexpr auto eval(partial<F>, Args...) -> tpack<eval_t<F, Args...>> { }
    template <
        typename F,
        typename... Args
    >
    constexpr auto eval(partial<F>, Args...)
    -> std::enable_if_t<
        !is_defined_v<F, Args...>,
        tpack<>
    >
    { }


    //! Append a non-empty optional value to a list.
    struct append_optional { };
    template <
        typename T,
        typename... Elements
    >
    constexpr auto eval(append_optional, tpack<Elements...>, tpack<T>)
    -> tpack<Elements..., T>
    { }
    template <
        typename... Elements
    >
    constexpr auto eval(append_optional, tpack<Elements...>, tpack<>)
    -> tpack<Elements...>
    { }


    //! Select elements for which F is defined, mapping the results
    /// to the result of F.
    struct select { };
    template <
        typename F,
        typename... Elements
    >
    constexpr auto eval(select, F, Elements...)
    {
        using optionals = eval_t<map, partial<F>, Elements...>;
        using result = typename optionals::
            template into<eval_t, reduce, append_optional, tpack<>>;
        return result{};
    }


    //! Check if an element is contained in a list, but std::is_same
    /// comparison.
    struct contains { };
    template <
        typename T,
        typename... Elements
    >
    constexpr auto eval(contains, T, Elements...)
    {
        using predicate = typename tpack<T>::template f<std::is_same>;
        using predicate2 = _detail::predicate_to_option<predicate>;
        using found = eval_t<map, predicate2, Elements...>;
        using result = typename found::
            template into<eval_t, reduce, append_optional, tpack<>>;
        if constexpr (result::size == 0)
            return std::false_type { };
        else
            return std::true_type {};
    }
}
