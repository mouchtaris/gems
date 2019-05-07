#pragma once
#include <type_traits>
namespace stdx
{
    namespace _detail::is_detected {
        template <
            template <typename...> typename Trait,
            typename Enabler,
            typename ... Args
        >
        struct is_detected: public std::false_type{};

        template <
            template <typename...> typename Trait,
            typename... Args
        >
        struct is_detected<
            Trait,
            std::void_t<Trait<Args...>>,
            Args...
        >: public std::true_type{};
    }

    template <
        template <typename...> typename Trait,
        typename... Args
    >
    using is_detected = typename _detail::is_detected::template is_detected<Trait, void, Args...>::type;

    template <
        template <typename...> typename Trait,
        typename... Args
    >
    constexpr auto is_detected_v = is_detected<Trait, Args...>::value;
}
