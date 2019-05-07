#pragma once
#include "u/traitlib.h"
#include "u/stdx.h"
#include "u/util.h"
#include <type_traits>
#include <string_view>
#include <iterator>
#include <cstring>
#include <algorithm>
#include <type_traits>
namespace u::str
{
    constexpr int strncmp(char const* a, char const* b, std::size_t n)
    {
        if (n == 0)
            return 0;
        int diff = *a - *b;
        if (diff == 0)
            return strncmp(a + 1, b + 1, n - 1);
        return diff;
    }

    constexpr char* strncpy(char const* src, char* dst, std::size_t n)
    {
        if (n == 0)
            return dst;
        *dst = *src;
        return strncpy(src + 1, dst + 1, n - 1);
    }

    constexpr std::size_t strlen(char const* str, std::size_t accum = 0)
    {
        if (*str == '\0')
            return accum;
        return strlen(str + 1, accum + 1);
    }
}

namespace std
{
    //! Start_with seems to be sometimes missing
    constexpr bool starts_with(string_view view, string_view prefix)
    {
#if defined(HAS_STD_STRING_VIEW_STARTS_WITH)
        return view.starts_with(prefix);
#else
        return u::str::strncmp(
            view.data(),
            prefix.data(),
            prefix.size()
        ) == 0;
#endif
    }
}

namespace u::str
{
    namespace _detail
    {
        //! Is Str a char_ptr after removing all indirections?
        template <
            typename Str
        >
        using is_char_ptr = std::conjunction<
            stdx::is_pointer<stdx::remove_cvref_t<Str>>,
            stdx::is_same<u::util::deptr_t<Str>, char>
        >;
    }

    //! Anything to string view
    template <
        typename Str
    >
    constexpr std::string_view view(Str&& str)
    {
        if constexpr (_detail::is_char_ptr<Str>::value)
            return str;
        else if constexpr (
            stdx::is_detected_v<traitlib::iterator_element_t, Str> &&
            stdx::is_same_v<util::deptr_t<traitlib::begin_t<Str>>, char>
        )
            return { begin(str), util::iterable_size(str) };
        else if constexpr (std::is_same_v<stdx::remove_cvref_t<Str>, std::string_view>)
            return str;
        else
            static_assert(util::failure_guard<Str>::value,
                "view not defined for this type yet"
            );
    }

    // Result of view(Str) -- can be used for is_detected.
    template <
        typename Str
    >
    using view_t = decltype(view(std::declval<Str>()));

    template <
        typename Char
    >
    constexpr int to_int(Char&& c)
    {
        using traits = stdx::char_traits<stdx::remove_reference_t<Char>>;
        constexpr auto zero = traits::to_int_type('0');
        auto val = traits::to_int_type(stdx::forward<Char>(c));
        return val - zero;
    }

    template <
        typename Char
    >
    constexpr int to_int(stdx::basic_string_view<Char> view)
    {
        int result = 0;
        int radix = 1;
        const auto end = rend(view);
        for (auto i = rbegin(view); i != end; ++i) {
            result += radix * to_int(*i);
            radix *= 10;
        }
        return result;
    }

    //! Scanf in a typesafe and constexpr way
    template <
        typename T,
        typename Str
    >
    constexpr void scanf(T&& into, Str&& str)
    {
        const std::string_view v = view(stdx::forward<Str>(str));

        if constexpr (stdx::is_same_v<T, char&>)
            into = v[0];

        else if constexpr (stdx::is_same_v<T, int&>)
            into = to_int(v);

        else if constexpr (stdx::is_detected_v<traitlib::iterator_element_t, T>)
            if constexpr (stdx::is_same_v<traitlib::begin_t<T>, char*>)
                u::str::strncpy(
                    v.data(),
                    begin(into),
                    stdx::min(
                        util::iterable_size(into),
                        v.size()
                    )
                );
            else
                static_assert(util::failure_guard<T>::value,
                    "iterable of not char* not supported yet"
                );

        else
            static_assert(util::failure_guard<T>::value,
                "scanf not defined for this yet"
            );
    }

    // Result of calling scanf() -- can be used in is_detected
    template <
        typename T,
        typename Str
    >
    using scanf_t = decltype(scanf(
        stdx::declval<T>(),
        stdx::declval<Str>()
    ));
}
