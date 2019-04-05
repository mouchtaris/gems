#pragma once
namespace util::seri
{
    template <typename... Tags> struct TagIndex
    {
        template <typename Tag> using add = TagIndex<Tags..., Tag>;
    };
}

#include <array>
template <std::size_t N, typename T, std::size_t... Index>
constexpr auto make_array_impl(T (& arr)[N], std::index_sequence<Index...>)
    -> std::array<T, N>
{
    return { arr[Index]... };
}
template <std::size_t N, typename T>
constexpr auto make_array(T (& arr)[N])
    -> std::array<T, N>
{
    return make_array_impl(arr, std::make_index_sequence<N>{});
}

template <typename T> char const* p() { return __PRETTY_FUNCTION__; }
#define debug__(EXPR) (std::cerr << #EXPR << ": " << (EXPR) << '\n')

#include <tuple>
#include <type_traits>
namespace util::tupl
{
    template <typename... Ts> using t = std::tuple<Ts...>;

    //! Super Epic
    //
    template <
        typename MyAgent = std::void_t<>,
        typename... Elements
    >
    struct IdManager
    {
        using self = IdManager<MyAgent, Elements...>;

        static constexpr auto Order = sizeof...(Elements);

        using drop =
            std::conditional_t<
                Order == 0,
                    std::void_t<>,
                    IdManager<Elements...>
            >;

        template <typename Agent> using add = IdManager<
            Agent,
            MyAgent,
            Elements...
        >;

        template <typename Agent> static constexpr bool is_mine()
            { return std::is_same_v<MyAgent, Agent>; }

        template <typename Agent> static constexpr std::size_t id() {
            if constexpr (is_mine<Agent>())
                return Order;
            if constexpr (Order > 0)
                return drop::template id<Agent>();
            return 0;
        }
    };

    //! Super epic
    //
    template <
        typename... Elements
    >
    struct Tuple
    {
        template <std::size_t i> using get =
            std::tuple_element_t<i, std::tuple<Elements...>>;
    };


    namespace Function {
        struct Tag;
        struct F;
        struct T;
        struct Args;

        struct tag;
        using ids = IdManager<>
            ::add<F>
            ::add<T>
            ::add<Args>
        ;

        template <typename key, typename func> using get =
            typename func::template get<ids::id<key>()>
        ;
    };

    template <
        typename... Elements
    >
    struct System
    {
        static constexpr bool has_first = sizeof...(Elements) > 0;
        using els = Tuple<Elements...>;
        using first = std::conditional_t<has_first, typename els::template get<0>, void>;

        template <
            typename F,
            typename T,
            typename... Args
        >
        using def = System<
            Tuple<Function::Tag, F, T, Tuple<Args...>>,
            Elements...
        >;

        template <
            typename F,
            typename... Args
        >
        static constexpr bool is_func()
        {
            if (!has_first)
                return false;
            using Function::get;
            return
                std::is_same_v<get<void, first>, Function::Tag> &&
                std::is_same_v<get<Function::F, first>, F> &&
                std::is_same_v<get<Function::Args, first>, Tuple<Args...>> &&
                true
            ;
        }


        template <
            typename F,
            typename... Args
        >
        using eval = void;
    };

}
