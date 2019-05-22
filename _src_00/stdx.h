#pragma once
#include <type_traits>
namespace std
{
    inline namespace stdx
    {
        //
        // remove_cvref
        //
        template <
            typename T
        >
        struct remove_cvref
        {
            using type = std::remove_cv_t<std::remove_reference_t<T>>;
        };

        template <
            typename T
        >
        using remove_cvref_t = typename remove_cvref<T>::type;

        //
        // is_detected
        //
        namespace is_detected_details
        {
            template <
                template <typename...> typename Trait,
                typename Enabler,
                typename... At
            >
            struct is_detected: public std::false_type{};

            template <
                template <typename...> typename Trait,
                typename... At
            >
            struct is_detected<Trait, std::void_t<Trait<At...>>, At...>: public std::true_type{};
        }

        template <
            template <typename...> typename Trait,
            typename... At
        >
        using is_detected = typename is_detected_details::is_detected<Trait, void, At...>::type;

        template <
            template <typename...> typename Trait,
            typename... At
        >
        constexpr auto is_detected_v = is_detected<Trait, At...>::value;
    }
}
