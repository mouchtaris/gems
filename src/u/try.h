#pragma once
#include <variant>
namespace u::try_
{
    struct Error { };

    constexpr bool is_error(Error const&) { return true; }
    constexpr bool is_error(...) { return false; }
    template <
        typename... Ts
    >
    constexpr bool is_error(std::variant<Ts...> const& v)
    {
        return std::visit(
            [](auto&& v) { return is_error(v); },
            v
        );
    }
}
