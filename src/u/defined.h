#pragma once
#include <type_traits>
namespace u
{
    template <
        typename T,
        typename = void
    >
    struct defined: public std::true_type { };

    template <
        typename T
    >
    struct defined<
        T,
        std::enable_if_t<T::defined == false, void>
    >
    : public std::false_type { };

    template <
        typename T
    >
    constexpr auto defined_v = defined<T>::value;
}
