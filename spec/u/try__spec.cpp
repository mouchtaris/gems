#include "./try__spec.h"
#include "u/try_.h"
namespace u::spec::try_
{
    struct E0{};
    struct E1{};
    struct E2{};
    struct R0{};
    struct R1{};

    using T0 = u::try_<R0, E0>;
    static_assert(std::is_default_constructible_v<T0>);
    static_assert(std::is_convertible_v<R0, T0>);
    static_assert(std::is_convertible_v<E0, T0>);
    static_assert(std::is_convertible_v<T0::variant_type, T0>);

    void debug()
    {
    }
}
