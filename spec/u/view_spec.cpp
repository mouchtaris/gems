#include "./view_spec.h"
#include "u/view.h"
#include "u/p.h"
#include <array>
namespace {
    using namespace u::view;

    constexpr auto back = std::array<int, 4> {4,5,6,7};
    constexpr auto v0 = ::u::view::view { back };
    static_assert(v0.size() == 4);
    static_assert(v0.remaining() == 4);
    static_assert(v0.has_remaining());
    static_assert(v0.first == 0);
    static_assert(v0.pos == 0);
    static_assert(v0.limit == 4);
    static_assert(v0.last == 4);
    static_assert(*begin(v0) == back[0]);
    static_assert(begin(v0) != end(v0));
    static_assert(v0.container[0] == 4);
    static_assert(v0.container[1] == 5);
    static_assert(v0.container[2] == 6);
    static_assert(v0.container[3] == 7);

    constexpr auto v1 = v0.emplace_back(0);
    static_assert(v1->size() == 3);
    static_assert(v1->remaining() == 3);
    static_assert(v1->has_remaining());
    static_assert(v1->first == 0);
    static_assert(v1->pos == 1);
    static_assert(v1->limit == 4);
    static_assert(v1->last == 4);
    static_assert(*begin(*v1) == back[1]);
    static_assert(begin(*v1) != end(*v1));
    static_assert(v1->container[0] == 0);
    static_assert(v1->container[1] == 5);
    static_assert(v1->container[2] == 6);
    static_assert(v1->container[3] == 7);
    static_assert(*begin(v1->container) == 0);
    static_assert(*std::next(begin(v1->container), 1) == 5);
    static_assert(*begin(*v1) == 5);
    static_assert(::u::view::is_view<std::remove_reference_t<decltype(*v1)>>::value);
    static_assert(*::u::view::begin(*v1) == 5);


    constexpr auto v2 = v1->emplace_back(1);
    static_assert(v2->size() == 2);
    static_assert(v2->remaining() == 2);
    static_assert(v2->has_remaining());
    static_assert(v2->first == 0);
    static_assert(v2->pos == 2);
    static_assert(v2->limit == 4);
    static_assert(v2->last == 4);
    static_assert(*begin(*v2) == back[2]);
    static_assert(begin(*v2) != end(*v2));
    static_assert(v2->container[0] == 0);
    static_assert(v2->container[1] == 1);
    static_assert(v2->container[2] == 6);
    static_assert(v2->container[3] == 7);
    static_assert(*begin(v2->container) == 0);
    static_assert(*std::next(begin(v2->container), 1) == 1);
    static_assert(*std::next(begin(v2->container), 2) == 6);
    static_assert(*begin(*v2) == 6);
    static_assert(::u::view::is_view<std::remove_reference_t<decltype(*v2)>>::value);
    static_assert(*::u::view::begin(*v2) == 6);

    constexpr auto v3 = v2->emplace_back(2);
    static_assert(v3->size() == 1);
    static_assert(v3->remaining() == 1);
    static_assert(v3->has_remaining());
    static_assert(v3->first == 0);
    static_assert(v3->pos == 3);
    static_assert(v3->limit == 4);
    static_assert(v3->last == 4);
    static_assert(*begin(*v3) == back[3]);
    static_assert(begin(*v3) != end(*v3));
    static_assert(v3->container[0] == 0);
    static_assert(v3->container[1] == 1);
    static_assert(v3->container[2] == 2);
    static_assert(v3->container[3] == 7);
    static_assert(*begin(v3->container) == 0);
    static_assert(*std::next(begin(v3->container), 1) == 1);
    static_assert(*std::next(begin(v3->container), 2) == 2);
    static_assert(*std::next(begin(v3->container), 3) == 7);
    static_assert(::u::view::is_view<std::remove_reference_t<decltype(*v3)>>::value);
    static_assert(*::u::view::begin(*v3) == 7);

    constexpr auto v4 = v3->emplace_back(3);
    static_assert(v4->size() == 0);
    static_assert(v4->remaining() == 0);
    static_assert(!v4->has_remaining());
    static_assert(v4->first == 0);
    static_assert(v4->pos == 4);
    static_assert(v4->limit == 4);
    static_assert(v4->last == 4);
    //static_assert(*begin(*v4) == back[3]);
    static_assert(begin(*v4) == end(*v4));
    static_assert(v4->container[0] == 0);
    static_assert(v4->container[1] == 1);
    static_assert(v4->container[2] == 2);
    static_assert(v4->container[3] == 3);
    static_assert(*begin(v4->container) == 0);
    static_assert(*std::next(begin(v4->container), 1) == 1);
    static_assert(*std::next(begin(v4->container), 2) == 2);
    static_assert(*std::next(begin(v4->container), 3) == 3);
    //static_assert(*begin(*v4) == 7);
    static_assert(is_view<std::remove_reference_t<decltype(*v4)>>::value);
    //static_assert(*::u::view::begin(*v4) == 7);

    constexpr auto v5 = v4->emplace_back(4);
    static_assert(v5 == std::nullopt);

    constexpr auto v6 = v4->flip();
    static_assert(v6.remaining() == 4);

    //
    // Subviewing
    //
    static_assert(v6.subview(0).remaining() == 4);
    static_assert(v6.subview(1).remaining() == 3);
    static_assert(v6.subview(2).remaining() == 2);
    static_assert(v6.subview(3).remaining() == 1);
    static_assert(v6.subview(4).remaining() == 0);
    static_assert(v6.subview(0, 1).remaining() == 1);
    static_assert(v6.subview(1, 1).remaining() == 1);
    static_assert(v6.subview(2, 1).remaining() == 1);
    static_assert(v6.subview(3, 1).remaining() == 1);
    static_assert(v6.subview(4, 1).remaining() == 0);
    static_assert(v6.subview(0, 4).remaining() == 4);
    static_assert(v6.subview(1, 4).remaining() == 3);
    static_assert(v6.subview(2, 4).remaining() == 2);
    static_assert(v6.subview(3, 4).remaining() == 1);
    static_assert(v6.subview(4, 4).remaining() == 0);
    static_assert(v6.subview(0, 5).remaining() == 4);
    static_assert(v6.subview(1, 5).remaining() == 3);
    static_assert(v6.subview(2, 5).remaining() == 2);
    static_assert(v6.subview(3, 5).remaining() == 1);
    static_assert(v6.subview(4, 5).remaining() == 0);

}
namespace u::spec::view
{
    void debug(spec)
    {
        debug__(( v0 ));
        debug__(( *v1 ));
        debug__(( *v2 ));
        debug__(( *v3 ));
        debug__(( *v4 ));
    }
    void runtime(spec)
    {
    }
}
