#include "./str_spec.h"
#include "u/str.h"
#include "u/p.h"
#include <array>
#include <iostream>
namespace u::spec::str
{
    using namespace ::u::str;
    using ::u::p;

    constexpr char const* lol = "lol";
    constexpr std::array<char, 4> lol1 { "lol" };

    template <
        typename char_t = char,
        typename fail = std::false_type
    >
    using char_ptr_t_detected = std::conjunction<
        std::negation<fail>,
        u::traits::is_detected<u::str::char_ptr_t, char_t const* const &&>,
        u::traits::is_detected<u::str::char_ptr_t, char_t const* const &>,
        u::traits::is_detected<u::str::char_ptr_t, char_t const* const >,
        u::traits::is_detected<u::str::char_ptr_t, char_t const* &&>,
        u::traits::is_detected<u::str::char_ptr_t, char_t const* &>,
        u::traits::is_detected<u::str::char_ptr_t, char_t const* >,
        u::traits::is_detected<u::str::char_ptr_t, char_t * const &&>,
        u::traits::is_detected<u::str::char_ptr_t, char_t * const &>,
        u::traits::is_detected<u::str::char_ptr_t, char_t * const >,
        u::traits::is_detected<u::str::char_ptr_t, char_t * &&>,
        u::traits::is_detected<u::str::char_ptr_t, char_t * &>,
        u::traits::is_detected<u::str::char_ptr_t, char_t * >,
        std::negation< u::traits::is_detected<u::str::char_ptr_t, char_t  const &&> >,
        std::negation< u::traits::is_detected<u::str::char_ptr_t, char_t  const &> >,
        std::negation< u::traits::is_detected<u::str::char_ptr_t, char_t  const > >,
        std::negation< u::traits::is_detected<u::str::char_ptr_t, char_t  &&> >,
        std::negation< u::traits::is_detected<u::str::char_ptr_t, char_t  &> >,
        std::negation< u::traits::is_detected<u::str::char_ptr_t, char_t  > >
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

    void debug()
    {
        debug__(( ::strlen("lol") ));
    }

    void runtime()
    {
    }
}
