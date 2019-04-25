#include "./stdx_spec.h"
#include "u/p.h"
#include "u/stdx.h"
namespace u::spec::stdx
{
    using namespace ::std;
    using namespace ::stdx;
    static_assert__(( is_same_v<remove_cvref_t<int>, int> ));
    static_assert__(( is_same_v<remove_cvref_t<int&>, int> ));
    static_assert__(( is_same_v<remove_cvref_t<int&&>, int> ));
    static_assert__(( is_same_v<remove_cvref_t<const int&>, int> ));
    static_assert__(( is_same_v<remove_cvref_t<const int[2]>, int[2]> ));
    static_assert__(( is_same_v<remove_cvref_t<const int(&)[2]>, int[2]> ));
    static_assert__(( is_same_v<remove_cvref_t<int(int)>, int(int)> ));

    void debug(spec)
    {
    }

    void runtime(spec)
    {
    }
}
