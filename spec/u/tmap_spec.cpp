#include "./tmap_spec.h"
#include "u/tmap.h"
#include "u/p.h"
#include <iostream>
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
    static_assert(
        std::is_same_v<
            l0::into<std::tuple, C, D>,
            std::tuple<C, D, A, B>
        >
    );

    //
    // tpack::prepend
    //
    static_assert(
        std::is_same_v<
            l0::prepend<C, D>,
            tpack<C, D, A, B>
        >
    );

    //
    // tpack::f
    //
    using l0f = l0::f<std::tuple, C>;
    using result = eval_t<l0f, D>;
    static_assert(
        std::is_same_v<
            result,
            std::tuple<C, A, B, D>
        >
    );


    //
    // has_head
    // has_tail
    // head
    // tail
    //
    static_assert(has_head<l0>::value);
    static_assert(has_tail<l0>::value);
    static_assert(has_head<tail<l0>>::value);
    static_assert(has_tail<tail<l0>>::value);
    static_assert(!has_head<tail<tail<l0>>>::value);
    static_assert(!has_tail<tail<tail<l0>>>::value);
    static_assert(std::is_same_v<head<l0>, A>);

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

    static_assert(std::is_same_v<
        eval_t<Fcall, A>,
        std::array<A, 2>
    >);

    //
    // A stupid function that overloads eval()
    //
    struct Feval{};
    template <typename x> constexpr auto eval(Feval, x) -> std::array<x, 3> { return {}; }

    static_assert(std::is_same_v<
        eval_t<Feval, A>,
        std::array<A, 3>
    >);

    //
    // is_defined
    //
    static_assert(
        is_defined<Feval, tpack<A>>::value
    );
    static_assert(
        is_defined_v<Fcall, A>
    );
    static_assert(
        !is_defined_v<int, float>
    );

    //
    // map<>
    //
    using map0 = eval_t<map, Fcall, A>;
    static_assert(std::is_same_v<
        map0,
        tpack<std::array<A, 2>>
    >);

    //
    // using map with tpacks
    //
    using l1 = l0::into<eval_t, map, Fcall>;

    static_assert(
        std::is_same_v<
            l1,
            tpack<
                std::array<A, 2>,
                std::array<B, 2>
            >
        >
    );


    //
    // A weird function, to test reducing
    //
    struct Weird { };
    constexpr auto eval(Weird, A, B) { return C{}; }

    //
    // reduce
    //
    static_assert(std::is_same_v<
        eval_t<reduce, Weird, A, B>,
        C
    >);


    //
    // or_else
    //
    static_assert(std::is_same_v<
        eval_t<or_else, tpack<>, A>,
        A
    >);
    static_assert(std::is_same_v<
        eval_t<or_else, A, tpack<>>,
        A
    >);
    static_assert(std::is_same_v<
        eval_t<or_else, A, B>,
        A
    >);
    static_assert(std::is_same_v<
        eval_t<or_else, tpack<>, tpack<A>>,
        tpack<A>
    >);
    static_assert(std::is_same_v<
        eval_t<or_else, tpack<>, tpack<>>,
        tpack<>
    >);
    static_assert(std::is_same_v<
        eval_t<or_else, tpack<A>, tpack<B>>,
        tpack<A>
    >);


    //
    // reduce + or_else
    //
    static_assert(std::is_same_v<
        eval_t<reduce, or_else, tpack<>, tpack<>, tpack<>, A>,
        A
    >);


    //
    // find_if
    //
    using is_A = tpack<A>::f<std::is_same>;
    static_assert(std::is_same_v<
        eval_t<find_if, is_A, C, B, A, D>,
        tpack<A>
    >);
    static_assert(std::is_same_v<
        eval_t<find_if, is_A, C, B, A, D>,
        tpack<A>
    >);
    static_assert(std::is_same_v<
        eval_t<find_if, is_A, C, B, A, D>,
        tpack<A>
    >);


    //
    // partial
    //
    static_assert(std::is_same_v<
        eval_t<partial<Weird>, A, B>,
        tpack<C>
    >);
    static_assert(std::is_same_v<
        eval_t<partial<Weird>, A, C>,
        tpack<>
    >);


    //
    // append_optional
    //
    static_assert(std::is_same_v<
        eval_t<append_optional, tpack<>, tpack<>>,
        tpack<>
    >);
    static_assert(std::is_same_v<
        eval_t<append_optional, tpack<A>, tpack<>>,
        tpack<A>
    >);
    static_assert(std::is_same_v<
        eval_t<append_optional, tpack<>, tpack<A>>,
        tpack<A>
    >);
    static_assert(std::is_same_v<
        eval_t<append_optional, tpack<A, B, C>, tpack<D>>,
        tpack<A, B, C, D>
    >);


    //
    // select
    //
    //! a weird function defined only on A and C
    struct Weird2 { };
    constexpr B eval(Weird2, A) { return {}; }
    constexpr D eval(Weird2, C) { return {}; }

    static_assert(std::is_same_v<
        eval_t<select, Weird2, A, B, C, D>,
        tpack<B, D>
    >);

    //
    // contains
    //
    static_assert(
        l0::into<eval_t, contains, A>::value
    );
    static_assert(
        l0::into<eval_t, contains, B>::value
    );
    static_assert(
        !l0::into<eval_t, contains, C>::value
    );


    void debug()
    {
    }
}
