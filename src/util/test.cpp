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
namespace util::tupl {
    using namespace ::util;
    static_assert(is_tuple<Tuple<>>::value, "");
    static_assert(!is_tuple<int>::value, "");
}
namespace util::find {
    using namespace ::util;
    struct A;
    template <typename B> using pred = std::is_same<A, B>;
    using has_it = Tuple<A, double, void, A, float>;
    using hasnt_it = Tuple<double, void, float>;

    static_assert(::util::is_tuple<has_it>::value, "");
    static_assert(::util::is_tuple<hasnt_it>::value, "");
    static_assert(pred<A>::value, "");
    using find = ::util::Find<
        pred,
        has_it
    >;
    //constexpr std::size_t idx =
    //    ::util::index::value_v<find::index>
    //;
    //static_assert(idx == 0, "");
}
}
}
