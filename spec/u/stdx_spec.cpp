#include "./stdx_spec.h"
#include "./stdx/make_array_spec.h"
#include "u/p.h"
#include "u/stdx.h"
#include "spec.h"
#include <tuple>
namespace u::spec::stdx
{
    constexpr auto modules = ::stdx::make_tuple(
        make_array::spec{}
    );

    using namespace ::std;
    using namespace ::stdx;

    //
    // Compiler flags
    //
#if defined(__GNUC__) || defined(__GNUG__)
    static_assert__(( STDX_GCC && GCC ));
    static_assert__(( !CLANG ));
#endif

    //
    // remove_cvref_t
    //
    static_assert__(( is_same_v<remove_cvref_t<int>, int> ));
    static_assert__(( is_same_v<remove_cvref_t<int&>, int> ));
    static_assert__(( is_same_v<remove_cvref_t<int&&>, int> ));
    static_assert__(( is_same_v<remove_cvref_t<const int&>, int> ));
    static_assert__(( is_same_v<remove_cvref_t<const int[2]>, int[2]> ));
    static_assert__(( is_same_v<remove_cvref_t<const int(&)[2]>, int[2]> ));
    static_assert__(( is_same_v<remove_cvref_t<int(int)>, int(int)> ));

    //
    // is_detected
    //
    template <typename T> using test_t = typename T::test;
    struct has_test { using test = int; };
    struct has_no_test { };
    static_assert__(( is_detected_v<test_t, has_test> ));
    static_assert__(( !is_detected_v<test_t, has_no_test> ));

    //
    // char8_t
    //
    static_assert__(( std::is_scalar_v<char8_t> ));

    void debug(spec)
    {
        stdx::apply(::spec::run_debug, modules);
    }

    void runtime(spec)
    {
        stdx::apply(::spec::run_runtime, modules);
    }
}
