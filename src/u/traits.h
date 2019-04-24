#pragma once
#include <type_traits>
#define TRAIT(NAME, DECL)       \
    template <                  \
        typename T,             \
        typename = void         \
    >                           \
    struct NAME: public std::false_type { }; \
    template <                  \
        typename T              \
    >                           \
    struct NAME<                \
        T,                      \
        std::void_t<DECL>       \
    >: public std::true_type { }

#define TRAIT_COND(NAME, COND)  \
    TRAIT(NAME, u::traits::enable_if<(COND)>)

#define TRAIT_HAS_FIELD(FIELD, FIELD_TYPE)  \
    TRAIT_COND(has_##FIELD, (               \
        std::conjunction_v<                 \
            std::is_same<                   \
                decltype(T{}. FIELD),       \
                FIELD_TYPE                  \
            >                               \
        >                                   \
    ))
namespace u::traits
{
    //! Enable if condition
    ///
    /// A simpler variant of std::enable_if, which does
    /// not require a result type.
    ///
    /// Used in the TRAIT_* macro expansions, because
    /// no extra commas are required and the macro parses
    /// correctly.
    template <bool cond>
    using enable_if = std::enable_if_t<cond, void>;

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

#define TRAIT_TYPE(NAME)                    \
    template <typename T> struct NAME { };  \
    template <typename T> using NAME##_t = typename NAME<T>::type

#define TRAIT_FIELD(NAME) \
    template <typename T> struct NAME { }
