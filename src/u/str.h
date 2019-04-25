#pragma once
#include "u/traitlib.h"
#include "u/stdx.h"
#include <type_traits>
#include <string_view>
#include <iterator>
#include <cstring>

namespace u::str
{
    namespace _detail
    {
        template <
            typename T
        >
        using deptr_t = std::remove_const_t<std::remove_pointer_t<stdx::remove_cvref_t<T>>>;

        template <
            typename char_t
        >
        using is_char = std::disjunction<
            std::is_same<char_t, char>,
            std::is_same<char_t, signed char>,
            std::is_same<char_t, wchar_t>,
            std::is_same<char_t, char8_t>,
            std::is_same<char_t, char16_t>,
            std::is_same<char_t, char32_t>
        >;
    }

    template <
        typename T,
        typename = std::enable_if_t<
            std::conjunction_v<
                std::is_pointer<stdx::remove_cvref_t<T>>,
                _detail::is_char<_detail::deptr_t<T>>
            >,
            void
        >
    >
    using char_ptr_t = _detail::deptr_t<T>;
}
//
//! A char* is also an iterable!
template <
    typename CharPtr,
    std::enable_if_t<
        stdx::is_detected_v<u::str::char_ptr_t, CharPtr>,
        int
    > = 0
>
constexpr stdx::remove_cvref_t<CharPtr> begin(CharPtr&& cstr)
{
    return cstr;
}

template <
    typename CharPtr,
    std::enable_if_t<
        stdx::is_detected_v<u::str::char_ptr_t, CharPtr>,
        int
    > = 0
>
//! A char* is also an iterable!
constexpr stdx::remove_cvref_t<CharPtr> end(CharPtr&& cstr)
{
    return cstr + std::char_traits<u::str::char_ptr_t<CharPtr>>::length(cstr);
}

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
