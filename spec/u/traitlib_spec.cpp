#include "./traitlib_spec.h"
#include "u/traitlib.h"
#include "u/traits.h"
#include "u/p.h"
#include "u/tmap.h"
using u::p;
namespace
{
    //
    // Basic trait assumptions
    //
    struct length0 { int length; };
    struct length1 { static int length; };
    struct length2 { int length(); };
    struct length3 { static int length(); };
    struct length4 { int length(int); };
    struct length5 { static int length(int); };
    struct length6 { };
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
    static_assert__(( !is_detected_v<length_t, length6> ));

    //
    // Expected trait names
    //
#define EXPECT(NAME)                                                \
    struct has_##NAME       { int NAME = 0; };                      \
    struct has_no_##NAME    { };                                    \
    static_assert__((  is_detected_v<NAME##_t, has_##NAME>      )); \
    static_assert__(( !is_detected_v<NAME##_t, has_no_##NAME>   ))  \

    EXPECT(length);
    EXPECT(message);

    struct has_call_operator { void operator()() const; };
    struct has_no_call_operator { };
    static_assert__((  is_detected_v<call_operator_t, has_call_operator> ));
    static_assert__(( !is_detected_v<call_operator_t, has_no_call_operator> ));

    //
    // iterable interface
    //
    constexpr int* begin(length0) { return nullptr; }
    constexpr int* end(length0) { return nullptr; }
    static_assert__(( stdx::is_detected_v<iterator_element_t, length0> ));
}

namespace u::spec::traitlib
{
    void runtime(spec)
    {
    }

    void debug(spec)
    {
    }
}
