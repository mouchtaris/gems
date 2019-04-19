#include "./tmap_spec.h"
#include "u/tmap.h"
#include "u/p.h"
#include <iostream>
namespace u::spec::tmap
{
    using ::u::tmap::tpack;
    using ::u::tmap::contains;
    using ::u::tmap::bind_front;
    using ::u::tmap::f;
    using ::u::tmap::map;
    using ::u::p;

    struct A;
    struct B;
    struct C;
    using l0 = tpack<A, B>;
    using contains_a = bind_front<
        contains,
        A
    >;

    static_assert(
        l0::into<bind_front<contains, A>::call>::value
    );

    static_assert(
        l0::into<bind_front<contains, B>::call>::value
    );

    static_assert(
        !l0::into<bind_front<contains, C>::call>::value
    );


    struct F
    {
        template <
            typename x
        >
        using call = x[2];
    };
    using l1 = l0::into<
        bind_front<
            map,
            F
        >::call
    >::result::into<std::tuple>;

    static_assert(
        std::is_same_v<
            l1,
            std::tuple<A[2], B[2]>
        >
    );



    void debug()
    {
        debug__(( p< bind_front<std::is_same, int>::call<float>         >() ));
        debug__((    bind_front<std::is_same, int>::call<float>::value      ));
        debug__(( p< map< bind_front<f<std::is_same>, int>::call<float>, int >::result  >() ));
    }
}
