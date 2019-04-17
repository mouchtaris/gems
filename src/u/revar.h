#pragma once
#include <variant>
namespace u
{
    template <
        typename... Variants
    >
    struct revar
    {
        std::variant<Variants...> var;
        template <
            typename... More
        >
        constexpr operator std::variant<Variants..., More...>() const
        {
            return std::visit(
                [](auto&& v) -> decltype(auto) { return std::forward<decltype(v)>(v); },
                var
            );
        }
    };

    template <typename... Variants> revar(std::variant<Variants...>) -> revar<Variants...>;

    template <
        typename... ErrorVariants
    >
    struct Errors
    {
        template <
            template <typename...> typename R,
            typename... Extra
        >
        using into = R<ErrorVariants..., Extra...>;
    };
}
