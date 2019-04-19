#include "./tmap_spec.h"
#include "u/tmap.h"
namespace u::spec::tmap
{
    using ::u::tmap::tpack;
    using ::u::tmap::contains;
    using ::u::tmap::bind_front;

    struct A;
    struct B;
    struct C;
    using l0 = tpack<A, B>;
    using contains_a = bind_front<
        contains,
        A
    >;

    static_assert(
        l0::into<bind_front<contains, A>::result>::value
    );

    static_assert(
        l0::into<bind_front<contains, B>::result>::value
    );

    static_assert(
        !l0::into<bind_front<contains, C>::result>::value
    );


    struct f
    {
        template <
            typename x
        >
        using call = x[2];
    };
    using l1 = l0::into<
        bind_front<
            ::u::tmap::map,
            f
        >::result
    >::result::into<std::tuple>;

    static_assert(
        std::is_same_v<
            l1,
            std::tuple<A[2], B[2]>
        >
    );



    void debug()
    {
    }
}
