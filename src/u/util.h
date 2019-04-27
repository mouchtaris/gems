#pragma once
#include "u/stdx.h"
#include <optional>
namespace u::util
{
    template <
        typename Val,
        typename Default
    >
    constexpr auto or_else(Val&& val, Default&& dflt)
    {
        if constexpr (std::is_same_v<stdx::remove_cvref_t<Val>, std::nullopt_t>)
            return std::forward<Default>(dflt);
        else
            return std::forward<Val>(val);
    }

    template <
        typename Result,
        typename Op = std::nullopt_t
    >
    struct if_defined
    {
        Op op = std::nullopt;

        template <
            typename Op2
        >
        static constexpr auto rebind(Op2&& op)
        -> if_defined<Result, Op2>
        {
            return { std::forward<Op2>(op) };
        }

        template <
            typename Arg
        >
        constexpr Result operator ()(Arg&& arg) const
        {
            if constexpr (stdx::is_detected_v<std::invoke_result_t, Op, Arg>)
                return op(std::forward<Arg>(arg));
            else
                return std::forward<Arg>(arg);
        }
    };

    template <
        typename T
    >
    constexpr decltype(auto) fwd(T val)
    {
        return val;
    }


    //! Strip all cv-ptr-cv-ref qualifiers from a type.
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
