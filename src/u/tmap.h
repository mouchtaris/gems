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
        using prepend = into<tpack, Prefix...>;

        template <
            typename... Suffix
        >
        using append = typename tpack<Suffix...>::template into<tpack, Ts...>;

        //! Turn a native template func into an evalable
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
        typename... Args
    >
    using eval_t = decltype(
        eval(
            std::declval<Args>()...
        )
    );

    //! A tpack<> can itself be a function if its elements
    /// are a well-defined function sequence.
    template <
        typename Pack,
        typename... ExtraBack
    >
    constexpr auto eval(Pack, ExtraBack...)
    -> typename Pack::template append<ExtraBack...>::template into<eval_t>
    { }


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
        typename Pack
    >
    constexpr auto eval(map, F, Pack)
    {
        if constexpr (Pack::size == 0)
            return tpack{};
        else {
            using head = eval_t<F, head<Pack>>;
            using tail = eval_t<map, F, tail<Pack>>;
            return typename tail::template prepend<head>{};
        }
    }


    //! Reduce a pack
    struct reduce { };
    template <
        typename F,
        typename Zero,
        typename Pack
    >
    constexpr auto eval(reduce, F, Zero, Pack)
    {
        if constexpr (!has_head<Pack>::value)
            return Zero{};
        else {
            using head_ = head<Pack>;
            using one = eval_t<F, Zero, head_>;
            using tail_ = tail<Pack>;
            using rest = eval_t<reduce, F, one, tail_>;
            return rest{};
        }
    }


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
        typename Pack
    >
    constexpr auto eval(find_if, Predicate, Pack)
    {
        using mapped = eval_t<map, _detail::predicate_to_option<Predicate>, Pack>;
        using result = eval_t<reduce, or_else, tpack<>, mapped>;
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
        typename Pack
    >
    constexpr auto eval(select, F, Pack)
    {
        using optionals = eval_t<map, partial<F>, Pack>;
        using result = eval_t<reduce, append_optional, tpack<>, optionals>;
        return result{};
    }


    //! Check if an element is contained in a list, but std::is_same
    /// comparison.
    struct contains { };
    template <
        typename T,
        typename Pack
    >
    constexpr auto eval(contains, T, Pack)
    {
        using predicate = typename tpack<T>::template f<std::is_same>;
        using predicate2 = _detail::predicate_to_option<predicate>;
        using found = eval_t<map, predicate2, Pack>;
        using result = eval_t<reduce, append_optional, tpack<>, found>;
        if constexpr (result::size == 0)
            return std::false_type{};
        else
            return std::true_type{};
    }


    //! Compose
    template <
        typename F,
        typename G
    >
    struct composed { };

    template <
        typename F,
        typename G,
        typename... Args
    >
    constexpr auto eval(composed<F, G>, Args...)
    {
        using f = eval_t<F, Args...>;
        using g = eval_t<G, f>;
        return g{};
    }

    struct compose { };
    template <
        typename F,
        typename G
    >
    constexpr auto eval(compose, F, G)
    -> composed<F, G>
    { }


    //! Prepend as an evalable
    struct prepend { };
    template <
        typename PackA,
        typename PackB
    >
    constexpr auto eval(prepend, PackA, PackB)
    -> typename PackB::template into<PackA::template prepend>
    { }


    //! Append as an evalable
    struct append { };
    template <
        typename PackA,
        typename PackB
    >
    constexpr auto eval(append, PackA, PackB)
    -> typename PackB::template into<PackA::template append>
    { }


    //! A generic less_equal operator.
    ///
    /// For tpack<>s this is equal to comparing that A is a
    /// non-strict subset of B.
    struct less_equal { };

    template <
        typename PackA,
        typename PackB
    >
    constexpr auto eval(less_equal, PackA, PackB)
    {
        using pack1 = tpack<>::f<tpack>;
        using eval_f = tpack<>::f<eval_t>;

        using make_checks =
            composed<
                composed<
                    pack1,
                    tpack<append, tpack<contains>>
                >,
                tpack<prepend, tpack<PackB>>
            >;
        using checks = eval_t<map, make_checks, PackA>;
        using results = eval_t<map, eval_f, checks>;
        using result = typename results::template into<std::conjunction>;

        return result{};
    }

}
