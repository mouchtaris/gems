#pragma once
#include "u/tmap.h"
#include <variant>
namespace u::try_
{
    struct Error { };

    namespace _detail
    {
        constexpr bool is_error(Error const&) { return true; }
        constexpr bool is_error(...) { return false; }

        constexpr auto is_error_visitor = [](auto&& v) { return is_error(v); };

        template <
            typename... Ts
        >
        constexpr bool is_error(std::variant<Ts...> const& v)
        {
            return std::visit(is_error_visitor, v);
        }

        template <
            typename VarA,
            typename VarB,
            typename = std::enable_if_t<
                ::u::tmap::eval_t<
                    ::u::tmap::less_equal,
                    VarA,
                    VarB
                >::value,
                void
            >
        >
        struct get_revar
        {
            using var_a = typename VarA::template into<std::variant>;
            using var_b = typename VarB::template into<std::variant>;
            static constexpr var_b revar(var_a va)
            {
                return std::visit(
                    [](auto&& v) -> var_b { return std::forward<decltype(v)>(v); },
                    va
                );
            }
        };
    }

    template <
        typename... Alts
    >
    struct adt
    {
        using variant_type = std::variant<Alts...>;

        variant_type value;

        using altpack = ::u::tmap::tpack<Alts...>;

        constexpr adt() = default;
        constexpr adt(variant_type&& value): value { std::move(value) } {}

        template <
            typename... Alts2
        >
        using get_revar = _detail::get_revar<
            typename adt<Alts2...>::altpack,
            altpack
        >;

        template <
            typename... Alts2,
            typename = get_revar<Alts2...>
        >
        constexpr adt(const adt<Alts2...>& other):
            value { get_revar<Alts2...>::revar(other.value) }
        { }
    };

    template <
        typename... Alts
    >
    constexpr bool is_error(adt<Alts...> const& v)
    {
        return _detail::is_error(v.value);
    }
}
