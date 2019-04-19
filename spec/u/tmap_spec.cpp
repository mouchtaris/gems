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

    void debug()
    {
    }
}
