#pragma once
#include "u/tmap.h"
#include "u/str.h"
#include <variant>
#include <cerrno>
#include <cstring>
#include <optional>
namespace u::try_
{
    struct Error { };

    struct StandardError: public Error
    {
        static constexpr auto MAX_MESSAGE_LENGTH = 1024;
        std::array<char, 1024> message;
    };

    struct StandardErrorWrapper: public Error
    {
        StandardError cause;
    };

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
            typename VarB
        >
        constexpr VarB revar(VarA var)
        {
            return std::visit(
                [](auto&& v) -> VarB { return std::forward<decltype(v)>(v); },
                var
            );
        }

        template <
            typename VarA,
            typename VarB,
            typename = void
        >
        struct can_revar: public std::false_type { };

        template <
            typename VarA,
            typename VarB
        >
        struct can_revar<VarA, VarB, std::void_t<
            decltype(revar<VarA, VarB>(std::declval<VarA>()))
        >>: public std::true_type { };

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
                return _detail::revar<var_a, var_b>(std::move(va));
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
        constexpr adt(variant_type value): value { std::move(value) } {}

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


        template <
            typename Arg,
            std::enable_if_t<
                std::disjunction_v<
                    ::u::tmap::eval_t<
                        ::u::tmap::contains,
                        Arg,
                        altpack
                    >
                >,
               int
            > = 0
        >
        constexpr adt(Arg&& arg):
            value { std::forward<Arg>(arg) }
        { }

        template <
            typename... Alts2,
            typename = get_revar<Alts2...>
        >
        constexpr adt(const std::variant<Alts2...>& var):
            value { _detail::revar<variant_type, std::variant<Alts2...>>(var) }
        { }

        //! Assume first variant type is success value, and return
        /// variant as that type.
        constexpr auto first() const
        {
            return std::get<std::variant_alternative_t<0, variant_type>>(value);
        }
    };

    template <
        typename... Alts
    >
    constexpr bool is_error(adt<Alts...> const& v)
    {
        return _detail::is_error(v.value);
    }


    //! The std way of checkiing for errors
    constexpr auto std_check_error = [](int result) -> bool
    {
        return result < 0;
    };

    //! The std way of transforming to an error
    constexpr auto std_to_error = [](int) -> StandardError
    {
        const auto errno_ = errno;
        StandardError result;
        auto&& msg = std::string_view { ::strerror(errno_) };
        strncpy(
            result.message.data(),
            msg.data(),
            msg.size()
        );
        return result;
    };

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

    //! A typical try flow
    template <
        typename Op,
        typename CheckError = std::nullopt_t,
        typename ToError = std::nullopt_t
    >
    constexpr auto stdtry(
        Op&& op,
        CheckError&& check_error = std::nullopt_t { std::nullopt },
        ToError&& to_error = std::nullopt_t { std::nullopt }
    )
    -> adt<
        std::invoke_result_t<Op>,
        std::invoke_result_t<
            std::invoke_result_t<
                decltype(or_else<ToError, decltype(std_to_error)>),
                ToError,
                decltype(std_to_error)
            >,
            std::invoke_result_t<Op>
        >
    >
    {
        auto&& result = op();
        if (or_else(check_error, std_check_error)(result))
            return or_else(to_error, std_to_error)(result);
        return result;
    }

    template <
        typename Error,
        typename... Alts,
        std::enable_if_t<
            u::tmap::eval_t<
                u::tmap::contains,
                StandardError,
                u::tmap::tpack<Alts...>
            >::value,
            int
        > = 0
    >
    constexpr auto wrap_std_error(adt<Alts...> adt)
    ->
        u::tmap::eval_t<
            u::tmap::map_if,
            u::tmap::tpack<>::f<std::is_same, StandardError>,
            Error,
            u::tmap::tpack<Alts...>
        >
    {
        return std::visit(
            [](auto&& v)
            {
                if constexpr (std::is_same_v<stdx::remove_cvref_t<decltype(v)>, StandardError>)
                    return Error { { { std::forward<decltype(v)>(v) } } };
                else
                    return std::forward<decltype(v)>(v);
            },
            adt.value
        );
    }
}

#define RETURN_IF_ERROR(VAL)            \
    if (is_error(VAL)) return (VAL)
