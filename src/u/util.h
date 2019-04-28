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
    ///
    /// Essentially we are trying to get the base type under a pointer
    /// or array indirection.
    ///
    /// Step0:
    ///     T const& => T: remove any extra cvrefs (could be const int* const&)
    /// Step1:
    ///     decay: if array turn to pointer (cvrefs removed alredy)
    /// Step2:
    ///     T* => T: remove pointer
    /// Step3:
    ///     const T& => T: remove cvrefs again
    template <
        typename T
    >
    using deptr_t =
        // step3
        stdx::remove_cvref_t<
            // step2
            std::remove_pointer_t<
                // step1
                std::decay_t<
                    // step0
                    stdx::remove_cvref_t<
                        T
                    >
                >
            >
        >;

    //! A template that is always false_type.
    ///
    /// Used to static_assert(false) in template metaprogramming.
    template <
        typename T
    >
    struct failure_guard: public std::false_type { };
}
