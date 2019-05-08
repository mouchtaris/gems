#pragma once
#include "./traits.h"
#include <iterator>
#include <optional>
#include <functional>
#include <ostream>
namespace u::view
{
    //
    // Container concept requirements
    //

    TRAIT_COND(has_size, (
        std::is_same_v<
            decltype(T{}.size()),
            std::size_t
        >
    ));
    TRAIT(has_value_type, typename T::value_type);
    TRAIT(has_reference_type, typename T::reference_type);
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


    //! View decoration
    ///
    /// A view decoration holds a backing storage container,
    /// while adapting the limits of iterating over it.
    /// 
    template <
        typename Container
    >
    struct view
    {
        static_assert(has_size<Container>::value);
        static_assert(has_value_type<Container>::value);
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
        constexpr std::optional<this_type> emplace_back(Args&&... args) const
        {
            if (!is_valid())
                return std::nullopt;
            else if (!has_remaining())
                return std::nullopt;
            else {
                this_type self2 = *this;
                *begin(self2) = value_type { std::forward<Args>(args)... };
                self2.pos += 1;
                return std::move(self2);
            }
        }

        constexpr this_type flip() const
        {
            return {
                container,
                first, 0,
                pos, last
            };
        }

        static constexpr std::size_t npos = -1;
        constexpr this_type subview(std::size_t from = 0, std::size_t n = npos) const
        {
            const auto first2 = first;
            const auto pos2 = stdx::min(pos + from, limit);
            const auto limit2 = 
                pos2 < stdx::numeric_limits<stdx::size_t>::max() - n ?
                    stdx::min(pos2 + n, limit) :
                    limit
                ;
            const auto last2 = last;
            return { container, first2, pos2, limit2, last2 };
        }
    };

    //
    // View deduction guides
    //
    template <
        typename Container
    >
    view(Container&&) -> view<
        std::remove_const_t<
            std::remove_reference_t<Container>
        >
    >;

    //
    // View concept requirements
    //

    TRAIT_HAS_FIELD(container, typename T::container_type);
    TRAIT_HAS_FIELD(first, std::size_t);
    TRAIT_HAS_FIELD(last, std::size_t);
    TRAIT_COND(has_remaining, (
        std::is_same_v<
            decltype(T{}.remaining()),
            std::size_t
        >
    ));
    TRAIT(has_flip, decltype(
        T{}.flip()
    ));

    TRAIT_COND(is_view_impl, (std::conjunction_v<
        has_container<T>,
        has_first<T>,
        has_last<T>,
        has_remaining<T>,
        has_flip<T>
    >));
    template <
        typename T
    >
    using is_view = is_view_impl<std::remove_reference_t<T>>;
    template <
        typename T
    >
    using if_view = std::enable_if_t<is_view<T>::value, void>;

    //
    // External API
    //
    template <
        typename T
    >
    using container_type = typename T::container_type;


    //! Get the adapted begin() of a view.
    template <
        typename View,
        typename = if_view<View>
    >
    constexpr auto begin(View&& view)
    {
        return std::next(begin(view.container), view.pos);
    }

    //! Get the adapted end() of a view.
    template <
        typename View,
        typename = if_view<View>
    >
    constexpr auto end(View&& view)
    {
        return std::next(begin(view), view.remaining());
    }

    template <
        typename View,
        typename = if_view<View>
    >
    std::ostream& operator <<(std::ostream& out, View&& view)
    {
        out << '{';
        std::size_t current = 0;
        const auto print_marks_and_then = [&view, &current, &out](auto&& el) -> std::ostream& {
            if (current != 0 && current != view.last)
                out << ", ";
            if (current == view.first)
                out << "[[";
            if (current == view.pos)
                out << "->";
            if (current == view.limit)
                out << "<-";
            if (current == view.last)
                out << "]]";
            return out << el;
        };
        for (auto&& el: view.container) {
            print_marks_and_then(std::forward<decltype(el)>(el));
            ++current;
        }
        return print_marks_and_then('}');
    }
}
