#include "./str_spec.h"
#include "u/str.h"
#include "u/p.h"
#include "u/view.h"
#include <array>
#include <iostream>
namespace
{
    using namespace ::u::str;
    using stdx::is_detected;
    using std::negation;

    //
    // char_ptr_t
    //
    template <
        typename char_t = char,
        typename fail = std::false_type
    >
    using char_ptr_t_detected = std::conjunction<
        negation<fail>,
        is_detected<char_ptr_t, char_t const* const &&>,
        is_detected<char_ptr_t, char_t const* const &>,
        is_detected<char_ptr_t, char_t const* const >,
        is_detected<char_ptr_t, char_t const* &&>,
        is_detected<char_ptr_t, char_t const* &>,
        is_detected<char_ptr_t, char_t const* >,
        is_detected<char_ptr_t, char_t * const &&>,
        is_detected<char_ptr_t, char_t * const &>,
        is_detected<char_ptr_t, char_t * const >,
        is_detected<char_ptr_t, char_t * &&>,
        is_detected<char_ptr_t, char_t * &>,
        is_detected<char_ptr_t, char_t * >,
        negation< is_detected<char_ptr_t, char_t  const &&> >,
        negation< is_detected<char_ptr_t, char_t  const &> >,
        negation< is_detected<char_ptr_t, char_t  const > >,
        negation< is_detected<char_ptr_t, char_t  &&> >,
        negation< is_detected<char_ptr_t, char_t  &> >,
        negation< is_detected<char_ptr_t, char_t  > >
    >;

    template <
        typename char_t,
        typename fail = std::false_type
    >
    constexpr auto char_ptr_t_detected_v = char_ptr_t_detected<char_t, fail>::value;

    static_assert__(( char_ptr_t_detected_v<char> ));
    static_assert__(( char_ptr_t_detected_v<signed char> ));
    static_assert__(( !char_ptr_t_detected_v<unsigned char> ));
    static_assert__(( char_ptr_t_detected_v<wchar_t> ));
    static_assert__(( char_ptr_t_detected_v<char8_t> ));
    static_assert__(( char_ptr_t_detected_v<char16_t> ));
    static_assert__(( char_ptr_t_detected_v<char32_t> ));
    static_assert__(( !char_ptr_t_detected_v<short> ));
    static_assert__(( !char_ptr_t_detected_v<int> ));
    static_assert__(( !char_ptr_t_detected_v<long> ));
    static_assert__(( !char_ptr_t_detected_v<unsigned short> ));
    static_assert__(( !char_ptr_t_detected_v<unsigned long> ));

    //
    // view
    //
    constexpr char const* lol = "lol";
    constexpr std::array<char, 4> lol1 { "lol" };

    static_assert__(( view(lol).size() == 3 ));
    static_assert__(( view(lol1).size() == 4 ));

    constexpr auto src0 = std::array<char, 12>{"hi bob"};
    constexpr auto src1 = u::view::view { src0 };
    constexpr auto v0 = u::str::view(src0);
    constexpr auto v1 = u::str::view(src1);
    static_assert(v0.size() == src0.size());
    static_assert(v1.size() == src1.size());

    //
    // cmp
    //
    static_assert__(( cmp(lol, lol1) == 0 ));
    static_assert__(( cmp(lol1, lol) == 0 ));
    static_assert__(( cmp(src0, v0) == 0 ));
    static_assert__(( cmp(src0, src1) == 0 ));
    static_assert__(( cmp(v0, v1) == 0 ));
    static_assert__(( cmp(v0, lol1) != 0 ));

    //
    // copy
    //
    static_assert__(( cmp("hi", copy("hi", std::array<char, 5>{}.data())) == 0 ));
}
namespace u::spec::str
{
    void debug(spec)
    {
        debug__(( ::strlen("lol") ));
    }

    void runtime(spec)
    {
    }
}
