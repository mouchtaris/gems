#pragma once
#include "u/traitlib.h"
#include "u/stdx.h"
#include <type_traits>
#include <string_view>
#include <iterator>
#include <cstring>

namespace u::str
{
    template <
        typename T
    >
    using char_traits = std::char_traits<
        std::remove_pointer_t<stdx::remove_cvref_t<T>>
    >;
}

// TODO: comment in
//! A char* is also an iterable!
//template <
//    typename CharPtr,
//    std::enable_if_t<
//        u::traits::is_detected_v<u::str::char_traits, CharPtr>,
//        int
//    > = 0
//>
//constexpr CharPtr begin(CharPtr&& cstr)
//{
//    return cstr;
//}
//
//template <
//    typename CharPtr,
//    std::enable_if_t<
//        u::traits::is_detected_v<u::str::char_traits, CharPtr>,
//        int
//    > = 0
//>
////! A char* is also an iterable!
//constexpr CharPtr end(CharPtr&& cstr)
//{
//    return cstr + u::str::char_traits<CharPtr>::length(cstr);
//}

namespace u::str
{
    template <
        typename View
    >
    constexpr std::string_view view(View const& view)
    {
        const auto first = begin(view);
        const auto last = end(view);
        const std::size_t size = std::distance(first, last);
        return { first, size };
    }

    template <
        typename T
    >
    using view_t = decltype(view(std::declval<T>()));
}
