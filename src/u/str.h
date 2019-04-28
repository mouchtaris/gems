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
namespace std
{
    //! Start_with seems to be sometimes missing
    constexpr bool starts_with(string_view view, string_view prefix)
    {
#if defined(HAS_STD_STRING_VIEW_STARTS_WITH)
        return view.starts_with(prefix);
#else
        return std::char_traits<char>::compare(
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
        typename Str,
        std::enable_if_t<
            stdx::disjunction_v<
                _detail::is_char_ptr<Str>
            >,
            int
        > = 0
    >
    constexpr std::string_view view(Str&& str)
    {
        if constexpr (_detail::is_char_ptr<Str>::value)
            return str;
        else
            static_assert(util::failure_guard<Str>::value,
                "view not defined for this type yet"
            );
    }

    template <
        typename Str
    >
    using view_t = decltype(view(std::declval<Str>()));

    template <
        typename T,
        typename Str
    >
    constexpr void scanf(T& into, Str&& str)
    {
        constexpr auto v = view(stdx::forward<Str>(str));

        if constexpr (stdx::is_same_v<T, char>)
            into = v[0];

        else if constexpr (stdx::is_detected_v<traitlib::iterator_element_t, T>)
            if constexpr (stdx::is_same_v<traitlib::iterator_element_t<T>, char>)
                ;
            else
                static_assert(util::failure_guard<T>::value,
                    "iterable of not char* not supported yet"
                );

        else
            static_assert(util::failure_guard<T>::value,
                "scanf not defined for this yet"
            );
    }

    template <
        typename T,
        typename Str
    >
    using scanf_t = decltype(scanf(
        stdx::declval<T>(),
        stdx::declval<Str>()
    ));
}
