#include "seri.h"
#include "arrays.h"
#include "p.h"
#include "lazy_conditional.h"
#include "index.h"
#include <tuple>
#include <type_traits>
namespace util::tupl
{


    //! Super Epic
    //
    template <
        typename MyAgent = void,
        typename... Elements
    >
    struct IdManager
    {
        static constexpr std::size_t Order = sizeof...(Elements);
        using drop = IdManager<
            Elements...
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
    }
}
