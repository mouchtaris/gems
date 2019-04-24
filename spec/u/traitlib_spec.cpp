#include "./traitlib_spec.h"
#include "u/traitlib.h"
#include "u/traits.h"
#include "u/p.h"
namespace
{
    struct length0 { int length; };
    struct length1 { static int length; };
    struct length2 { int length(); };
    struct length3 { static int length(); };
    struct length4 { int length(int); };
    struct length5 { static int length(int); };
    int length1::length;
    int length2::length() { return 0; }
    int length3::length() { return 0; }
    int length4::length(int x) { return x; }
    int length5::length(int x) { return x; }

    using namespace u::traitlib;
    using u::traits::is_detected_v;

    static_assert__(( is_detected_v<length_t, length0> ));
    static_assert__(( is_detected_v<length_t, length1> ));
    static_assert__(( is_detected_v<length_t, length2> ));
    static_assert__(( is_detected_v<length_t, length3> ));
    static_assert__(( is_detected_v<length_t, length4> ));
    static_assert__(( is_detected_v<length_t, length5> ));
}

namespace u::spec::traitlib
{
    void runtime()
    {
    }

    void debug()
    {
    }
}
