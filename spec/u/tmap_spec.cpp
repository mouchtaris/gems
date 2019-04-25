#include "./tmap_spec.h"
#include "u/tmap.h"
#include "u/p.h"
#include <iostream>

#if 01
#   define local_static_assert__(EXPR) static_assert__(EXPR)
#else
#   define local_static_assert__(EXPR)
#endif

namespace u::spec::tmap
{
    using ::u::tmap::tpack;
    using ::u::tmap::eval_t;
    using ::u::tmap::is_defined;
    using ::u::tmap::is_defined_v;
    using ::u::tmap::has_head;
    using ::u::tmap::head;
    using ::u::tmap::has_tail;
    using ::u::tmap::tail;
    using ::u::tmap::map;
    using ::u::tmap::reduce;
    using ::u::tmap::or_else;
    using ::u::tmap::find_if;
    using ::u::tmap::partial;
    using ::u::tmap::append_optional;
    using ::u::tmap::select;
    using ::u::tmap::contains;
    using ::u::tmap::zip;
    using ::u::tmap::map_if;
    using ::u::tmap::compose;
    using ::u::tmap::prepend;
    using ::u::tmap::append;
    using ::u::tmap::less_equal;
    using ::u::p;

    struct A {};
    struct B {};
    struct C {};
    struct D {};

    //
    // tpack
    //
    using l0 = tpack<A, B>;

    //
    // tpack::into
    //
    local_static_assert__((
        std::is_same_v<
            l0::into<std::tuple, C, D>,
            std::tuple<C, D, A, B>
        >
    ));


    //
    // tpack::prepend
    //
    local_static_assert__((
        std::is_same_v<
            l0::prepend<C, D>,
            tpack<C, D, A, B>
        >
    ));

    //
    // tpack::append
    //
    local_static_assert__((
        std::is_same_v<
            l0::append<C, D>,
            tpack<A, B, C, D>
        >
    ));

    //
    // tpack::f
    //
    using l0f = l0::f<std::tuple, C>;
    using result = eval_t<l0f, D>;
    local_static_assert__((
        std::is_same_v<
            result,
            std::tuple<C, A, B, D>
        >
    ));


    //
    // eval(tpack)
    //
    local_static_assert__((
        eval_t<tpack<tpack<>::f<std::is_same>, A>, A>::value
    ));
    // Break down:
    // - tpack<>::f<std::is_same>
    //      turn std::is_same into evalable
    // - tpack<F, A>
    //      a pack with an F and a bound first arg (A)
    // - eval_t< tpack<...>, A >
    //      eval the bound F in tpack with an extra arg at the end (A)
    // - boils down to
    //      std::is_same<A, A>


    //
    // has_head
    // has_tail
    // head
    // tail
    //
    local_static_assert__((has_head<l0>::value));
    local_static_assert__((has_tail<l0>::value));
    local_static_assert__((has_head<tail<l0>>::value));
    local_static_assert__((has_tail<tail<l0>>::value));
    local_static_assert__((!has_head<tail<tail<l0>>>::value));
    local_static_assert__((!has_tail<tail<tail<l0>>>::value));
    local_static_assert__((std::is_same_v<head<l0>, A>));

    //
    // A stupid function with call<> implemented
    //
    struct Fcall
    {
        template <
            typename x
        >
        using call = std::array<x, 2>;
    };

    local_static_assert__((std::is_same_v<
        eval_t<Fcall, A>,
        std::array<A, 2>
    >));

    //
    // A stupid function that overloads eval()
    //
    struct Feval{};
    template <typename x> constexpr auto eval(Feval, x) -> std::array<x, 3> { return {}; }

    local_static_assert__((std::is_same_v<
        eval_t<Feval, A>,
        std::array<A, 3>
    >));

    //
    // is_defined
    //
    local_static_assert__((
        is_defined<Feval, tpack<A>>::value
    ));
    local_static_assert__((
        is_defined_v<Fcall, A>
    ));
    local_static_assert__((
        !is_defined_v<int, float>
    ));

    //
    // map<>
    //
    using map0 = eval_t<map, Fcall, tpack<A>>;
    local_static_assert__((std::is_same_v<
        map0,
        tpack<std::array<A, 2>>
    >));

    //
    // using map with tpacks
    //
    using l1 = eval_t<map, Fcall, l0>;

    local_static_assert__((
        std::is_same_v<
            l1,
            tpack<
                std::array<A, 2>,
                std::array<B, 2>
            >
        >
    ));


    //
    // A weird function, to test reducing
    //
    struct Weird { };
    constexpr auto eval(Weird, A, B) { return C{}; }

    //
    // reduce
    //
    local_static_assert__((std::is_same_v<
        eval_t<reduce, Weird, A, tpack<B>>,
        C
    >));


    //
    // or_else
    //
    local_static_assert__((std::is_same_v<
        eval_t<or_else, tpack<>, A>,
        A
    >));
    local_static_assert__((std::is_same_v<
        eval_t<or_else, A, tpack<>>,
        A
    >));
    local_static_assert__((std::is_same_v<
        eval_t<or_else, A, B>,
        A
    >));
    local_static_assert__((std::is_same_v<
        eval_t<or_else, tpack<>, tpack<A>>,
        tpack<A>
    >));
    local_static_assert__((std::is_same_v<
        eval_t<or_else, tpack<>, tpack<>>,
        tpack<>
    >));
    local_static_assert__((std::is_same_v<
        eval_t<or_else, tpack<A>, tpack<B>>,
        tpack<A>
    >));


    //
    // reduce + or_else
    //
    local_static_assert__((std::is_same_v<
        eval_t<reduce, or_else, tpack<>, tpack<tpack<>, tpack<>, tpack<>, A>>,
        A
    >));


    //
    // find_if
    //
    using is_A = tpack<A>::f<std::is_same>;
    local_static_assert__((std::is_same_v<
        eval_t<find_if, is_A, tpack<C, B, A, D>>,
        tpack<A>
    >));
    local_static_assert__((std::is_same_v<
        eval_t<find_if, is_A, tpack<C, B, A, D>>,
        tpack<A>
    >));
    local_static_assert__((std::is_same_v<
        eval_t<find_if, is_A, tpack<C, B, A, D>>,
        tpack<A>
    >));


    //
    // partial
    //
    local_static_assert__((std::is_same_v<
        eval_t<partial<Weird>, A, B>,
        tpack<C>
    >));
    local_static_assert__((std::is_same_v<
        eval_t<partial<Weird>, A, C>,
        tpack<>
    >));


    //
    // append_optional
    //
    local_static_assert__((std::is_same_v<
        eval_t<append_optional, tpack<>, tpack<>>,
        tpack<>
    >));
    local_static_assert__((std::is_same_v<
        eval_t<append_optional, tpack<A>, tpack<>>,
        tpack<A>
    >));
    local_static_assert__((std::is_same_v<
        eval_t<append_optional, tpack<>, tpack<A>>,
        tpack<A>
    >));
    local_static_assert__((std::is_same_v<
        eval_t<append_optional, tpack<A, B, C>, tpack<D>>,
        tpack<A, B, C, D>
    >));


    //
    // select
    //
    //! a weird function defined only on A and C
    struct Weird2 { };
    constexpr B eval(Weird2, A) { return {}; }
    constexpr D eval(Weird2, C) { return {}; }

    local_static_assert__((std::is_same_v<
        eval_t<select, Weird2, tpack<A, B, C, D>>,
        tpack<B, D>
    >));

    //
    // zip
    //
    local_static_assert__(( std::is_same_v<
        eval_t<zip, tpack<A, B>, tpack<B, C>>,
        tpack<
            tpack<A, B>,
            tpack<B, C>
        >
    > ));

    //
    // map_if
    //
    local_static_assert__(( std::is_same_v<
        eval_t<
            map_if,
            tpack<B>::f<std::is_same>,
            A,
            tpack<A, B, C, D>
        >,
        tpack<A, A, C, D
    > ));

    //
    // contains
    //
    local_static_assert__((
        eval_t<contains, A, l0>::value
    ));
    local_static_assert__((
        eval_t<contains, B, l0>::value
    ));
    local_static_assert__((
        !eval_t<contains, C, l0>::value
    ));


    //
    // compose
    //
    struct a2b { };
    struct b2c { };
    constexpr B eval(a2b, A) { return {}; }
    constexpr C eval(b2c, B) { return {}; }
    local_static_assert__((std::is_same_v<
        eval_t<eval_t<compose, a2b, b2c>, A>,
        C
    >));


    //
    // prepend
    //
    local_static_assert__((std::is_same_v<
        eval_t<prepend, tpack<A, B>, tpack<C, D>>,
        tpack<C, D, A, B>
    >));

    //
    // append
    //
    local_static_assert__((std::is_same_v<
        eval_t<append, tpack<A, B>, tpack<C, D>>,
        tpack<A, B, C, D>
    >));


    //
    // less_equal for tpack<>s
    //
    local_static_assert__((
        eval_t<less_equal, tpack<A, B, C>, tpack<A, B, C, D>>::value
    ));
    local_static_assert__((
        !eval_t<less_equal, tpack<A, B, C, D>, tpack<A, B, C>>::value
    ));

    void runtime(spec)
    {
    }

    void debug(spec)
    {
    }
}
