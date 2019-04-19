#pragma once
#include <variant>
namespace u
{
    template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
    template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

    template <
        typename R,
        typename... Errors
    >
    struct try_
    {
        template <
            typename NewError
        >
        using or_error = try_<
            R,
            Errors...,
            NewError
        >;

        using variant_type = std::variant<R, Errors...>;

        variant_type value;

        template <
            typename... Args
        >
        constexpr try_(Args&&... args):
            value { std::forward<Args>(args)... }
        {
        }

        constexpr bool is_failed() const
        {
            return !std::holds_alternative<R>(value);
        }
    };
}
