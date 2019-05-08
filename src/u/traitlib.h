#pragma once
#include "./stdx.h"
#include "./traits.h"
#define _U__TRAITLIB__MEM_EX(NAME, TRAIT_NAME)                          \
    template <typename T>   constexpr auto TRAIT_NAME = &T::NAME;       \
    template <typename T>   using TRAIT_NAME##_t = decltype(&T::NAME)   \

#define _U__TRAITLIB__MEM(NAME)     _U__TRAITLIB__MEM_EX(NAME, NAME)    \

#define _U__TRAITLIB__API(FNAME)                                        \
    template <typename T>   using FNAME##_t = decltype(FNAME(std::declval<T>()))

namespace u::traitlib
{
    //
    // Members
    //
    _U__TRAITLIB__MEM_EX(operator(), call_operator);

    _U__TRAITLIB__MEM(length);
    _U__TRAITLIB__MEM(message);

    //
    // Standard types
    //
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

    //
    // Iterable interface
    //
    _U__TRAITLIB__API(begin);
    _U__TRAITLIB__API(end);

    //! Get the iterator element type, as seen by dereferencing
    /// begin(T) or end(T).
    ///
    /// This template is enabled if both begin(T) and end(T) yield
    /// the same dereferenced type.
    template <
        typename T,
        typename = stdx::enable_if_t<
            stdx::conjunction_v<
                stdx::is_same<
                    decltype(*stdx::declval<begin_t<T>>()),
                    decltype(*stdx::declval<end_t<T>>())
                >
            >
        >
    >
    using iterator_element_t =
        decltype(*stdx::declval<begin_t<T>>())
    ;
}
