#pragma once
namespace util
{
template <
    bool condition,
    template <typename...> typename True,
    template <typename...> typename False,
    typename... Args
>
struct lazy_conditional;
template <
    template <typename...> typename True,
    template <typename...> typename False,
    typename... Args
>
struct lazy_conditional<true, True, False, Args...>
{
    using type = True<Args...>;
};
template <
    template <typename...> typename True,
    template <typename...> typename False,
    typename... Args
>
struct lazy_conditional<false, True, False, Args...>
{
    using type = False<Args...>;
};
template <
    bool condition,
    template <typename...> typename True,
    template <typename...> typename False,
    typename... Args
>
using lazy_conditional_t = typename lazy_conditional<condition, True, False, Args...>::type;

//! identity_t
/// Helpers for lazy conditional, actually
//
template <typename T> using identity_t = T;
}
