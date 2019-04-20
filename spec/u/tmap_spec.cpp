#include "./tmap_spec.h"
#include "u/tmap.h"
#include "u/p.h"
#include <iostream>
namespace u::spec::tmap
{
    using ::u::tmap::tpack;
    using ::u::tmap::eval_t;
    //using ::u::tmap::contains;
    using ::u::tmap::map;
    using ::u::p;


    struct A {};
    struct B {};
    struct C {};
    struct D {};
    using l0 = tpack<A, B>;

    static_assert(
        std::is_same_v<
            l0::into<std::tuple, C, D>,
            std::tuple<C, D, A, B>
        >
    );

    static_assert(
        std::is_same_v<
            l0::prepend<C, D>,
            tpack<C, D, A, B>
        >
    );

    using l0f = l0::f<std::tuple, C>;
    static_assert(
        std::is_same_v<
            eval_t<l0f, D>,
            std::tuple<C, A, B, D>
        >
    );


    struct F
    {
        template <
            typename x
        >
        using call = std::array<x, 2>;
    };
    //using l1 = l0::into<eval_t, map, F>;

    //static_assert(
    //    std::is_same_v<
    //        l1,
    //        std::tuple<
    //            std::array<A, 2>,
    //            std::array<B, 2>
    //        >
    //    >
    //);


    //using contains_a = bind_front<
    //    contains,
    //    A
    //>;

    //static_assert(
    //    l0::into<bind_front<contains, A>::call>::value
    //);

    //static_assert(
    //    l0::into<bind_front<contains, B>::call>::value
    //);

    //static_assert(
    //    !l0::into<bind_front<contains, C>::call>::value
    //);



    void debug()
    {
    }
}
