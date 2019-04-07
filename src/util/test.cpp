#include "lib.h"
namespace {
namespace test {
namespace util::index {
    using namespace ::util::index;
    static_assert(
        is_index<_0>::value,
        ""
    );
    static_assert(
        is_index<Succ<_0>>::value,
        ""
    );
    static_assert(
        is_index<Succ<Succ<_0>>>::value,
        ""
    );
}
}
}
