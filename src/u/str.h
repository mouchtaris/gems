#pragma once
#include "u/traits.h"
#include <type_traits>
#include <string_view>
#include <iterator>
namespace u::str
{
    TRAIT_COND(has_begin, (
        std::is_same_v<
            std::remove_const_t<std::remove_pointer_t<decltype(begin(std::declval<T>()))>>,
            char
        >
    ));

    TRAIT_COND(has_end, (
        std::is_same_v<
            std::remove_const_t<std::remove_pointer_t<decltype(end(std::declval<T>()))>>,
            char
        >
    ));

    template <
        typename View,
        typename = std::enable_if_t<
            std::conjunction_v<
                has_begin<View>,
                has_end<View>,
                std::is_reference<View>
            >,
            void
        >
    >
    constexpr std::string_view view(View&& view)
    {
        const auto first = begin(view);
        const auto last = end(view);
        const std::size_t size = std::distance(first, last);
        return { first, size };
    }
}
