#pragma once
#include <type_traits>

namespace stdx
{
    constexpr bool GCC =
#if defined(__GNUC__) || defined(__GNUG__)
#define STDX_GCC 1
        true
#else
        false
#endif
        ;

    constexpr bool CLANG =
#if defined(__clang__)
#define STDX_CLANG 1
        true
#else
        false
#endif
        ;

    static_assert(GCC | CLANG);

    template<
        typename T
    >
    struct remove_cvref {
        typedef std::remove_cv_t<std::remove_reference_t<T>> type;
    };

    template<
        typename T
    >
    using remove_cvref_t = typename remove_cvref<T>::type;

    namespace _detail {
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
    using is_detected = typename _detail::is_detected<Trait, void, Args...>::type;

    template <
        template <typename...> typename Trait,
        typename... Args
    >
    constexpr auto is_detected_v = is_detected<Trait, Args...>::value;
}

#if defined(STDX_GCC) && STDX_GCC
enum char8_t: char;
#endif
