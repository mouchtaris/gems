#pragma once
#include "./traits.h"
#define _U__TRAITLIB__MEM_EX(NAME, TRAIT_NAME)                          \
    template <typename T>   constexpr auto TRAIT_NAME = &T::NAME;       \
    template <typename T>   using TRAIT_NAME##_t = decltype(&T::NAME)   \

#define _U__TRAITLIB__MEM(NAME)     _U__TRAITLIB__MEM_EX(NAME, NAME)    \

namespace u::traitlib
{
    //
    // Members
    //
    _U__TRAITLIB__MEM_EX(operator(), call_operator);

    _U__TRAITLIB__MEM(length);
    _U__TRAITLIB__MEM(message);


    //
    // Shapes
    //
    template <
        typename T,
        typename Self
    >
    using mod_of = std::conjunction<
        std::is_same<
            std::invoke_result_t<
                call_operator_t<T>,
                Self
            >,
            Self
        >
    >;
}
