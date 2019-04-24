#pragma once
#include <type_traits>

namespace stdx
{
    template< class T >
    struct remove_cvref {
        typedef std::remove_cv_t<std::remove_reference_t<T>> type;
    };

    template< class T >
    using remove_cvref_t = typename remove_cvref<T>::type;

    namespace _detail {
        template <
            template <class...> class Trait,
            class Enabler,
            class... Args
        >
        struct is_detected: public std::false_type{};

        template <
            template <class...> class Trait,
            class... Args
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
    using is_detected = typename _detail::is_detected<Trait, void, Args...>::type;

    template <
        template <typename...> typename Trait,
        typename... Args
    >
    constexpr auto is_detected_v = is_detected<Trait, Args...>::value;
}

enum char8_t: char;
