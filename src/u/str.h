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
    //! The underlying char type after deptr-ing a type
    template <
        typename T,
        typename = std::enable_if_t<
            std::conjunction_v<
                std::is_pointer<stdx::remove_cvref_t<T>>,
                util::is_char<util::deptr_t<T>>
            >,
            void
        >
    >
    using char_ptr_t = util::deptr_t<T>;

    //! Char traits for a type after deptr-ing it
    template <
        typename T
    >
    using char_traits = std::char_traits<char_ptr_t<T>>;
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

namespace std
{
    //! Start_with seems to be sometimes missing
    constexpr bool starts_with(string_view view, string_view prefix)
    {
        return std::char_traits<char>::compare(
            view.data(),
            prefix.data(),
            prefix.size()
        ) == 0;
    }
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


    //! Compare any to any
    template <
        typename A,
        typename B
    >
    constexpr auto cmp(A const& a, B const& b)
    {
        const auto va = view(a);
        const auto vb = view(b);
        const auto astr = va.data();
        const auto bstr = vb.data();
        const auto n = std::min(va.size(), vb.size());
        using ct = char_traits<decltype(astr)>;
        return ct::compare(astr, bstr, n);
    }


    //! Copy any to any
    template <
        typename Src,
        typename Dest
    >
    constexpr auto copy(Src const& src, Dest&& dest)
    {
        const auto vsrc = view(util::fwd(src));
        const auto srcstr = vsrc.data();
        using ct = char_traits<decltype(dest)>;
        const auto n = std::min(vsrc.size(), ct::length(dest));
        return ct::copy(dest, srcstr, n);
    }
}
