#pragma once
#include <iterator>
#include <optional>
#include <functional>
namespace u::view
{
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
    >: public std::true_type { };

template <bool cond>
using enable_if = std::enable_if_t<cond, void>;

#define TRAIT_COND(NAME, COND)  \
    TRAIT(NAME, u::view::enable_if<(COND)>)
#define TRAIT_HAS_FIELD(FIELD, FIELD_TYPE)  \
    TRAIT_COND(has_##FIELD, (               \
        std::conjunction_v<                 \
            std::is_same<                   \
                decltype(T{}. FIELD),       \
                FIELD_TYPE                  \
            >                               \
        >                                   \
    ))

    TRAIT_COND(has_size, (
        std::is_same_v<
            decltype(T{}.size()),
            std::size_t
        >
    ));
    TRAIT(has_value_type, typename T::value_type);
    TRAIT(has_reference_type, typename T::reference_type);
    TRAIT(has_begin, decltype(begin(T{})));
    TRAIT_COND(deref_begin_is_value_type, (
        std::is_same_v<
            std::decay_t<decltype(*begin(T{}))>,
            typename T::value_type
        >
    ));
    TRAIT_COND(can_cmp_begin_end, (
        std::is_same_v<
            decltype(begin(T{}) != end(T{})),
            bool
        >
    ));
    TRAIT_COND(begin_is_advancable, (
        std::is_same_v<
            decltype(std::next(begin(T{}))),
            decltype(begin(T{}))
        >
    ));


    template <
        typename Container
    >
    struct view
    {
        static_assert(has_size<Container>::value);
        static_assert(has_value_type<Container>::value);
        static_assert(has_begin<Container>::value);
        static_assert(deref_begin_is_value_type<Container>::value);
        static_assert(can_cmp_begin_end<Container>::value);
        static_assert(begin_is_advancable<Container>::value);

        using container_type = Container;

        using this_type = view<Container>;

        using iterator_type =
            decltype(begin(std::declval<container_type>()));
        using iterator_traits =
            std::iterator_traits<iterator_type>;
        using value_type =
            typename iterator_traits::value_type;

        container_type container;
        std::size_t
            first = 0,
            pos = first,
            limit = container.size(),
            last = limit
        ;

        constexpr bool is_valid() const
        {
            return true
                && first <= pos
                && pos <= limit
                && limit <= last
                && last <= container.size()
            ;
        }

        constexpr std::size_t remaining() const
        {
            return limit - pos;
        }

        constexpr bool has_remaining() const
        {
            return remaining() > 0;
        }

        constexpr std::size_t size() const
        {
            return remaining();
        }

        template <
            typename... Args
        >
        std::optional<this_type> emplace_back(Args&&... args) const
        {
            if (!is_valid())
                return std::nullopt;
            else if (!has_remaining())
                return std::nullopt;
            else {
                auto container2 = container;
                *std::next(begin(container2), first) = value_type {
                    std::forward<Args>(args)...
                };

                auto view2 = this_type {
                    std::move(container2),
                    first, pos + 1, limit, last
                };

                return std::move(view2);
            }
        }
    };

    TRAIT_HAS_FIELD(container, typename T::container_type);
    TRAIT_HAS_FIELD(first, std::size_t);
    TRAIT_HAS_FIELD(last, std::size_t);
    TRAIT_COND(has_remaining, (
        std::is_same_v<
            decltype(T{}.remaining()),
            std::size_t
        >
    ));

    TRAIT_COND(is_view, (std::conjunction_v<
        has_container<T>,
        has_first<T>,
        has_last<T>,
        has_remaining<T>
    >));

    template <
        typename View,
        typename = std::enable_if_t<is_view<std::remove_reference_t<View>>::value, void>
    >
    constexpr auto begin(View&& view)
    {
        return std::next(begin(view.container), view.first);
    }

    template <
        typename View,
        typename = std::enable_if_t<is_view<std::remove_reference_t<View>>::value, void>
    >
    constexpr auto end(View&& view)
    {
        return std::next(begin(view), view.remaining());
    }
}
