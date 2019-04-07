#include "config.h"
#include "util/lib.h"
#include "util/is_template.h"
#include <type_traits>
#include <tuple>
#include <array>
#include <iostream>

//! well_formed
//
template <typename T, typename = std::void_t<>>
struct well_formed: public std::false_type { };

//! adt::tag
//
namespace adt
{
    template <typename Tag> struct tag{};
}


#include <sys/select.h>
int select(int nfds, fd_set  *readfds, fd_set  *writefds, fd_set *errorfds, struct timeval *timeout);

namespace uri::path
{
    struct tag;
    using t = std::tuple<adt::tag<tag>,
        std::array<char, config::MAX_URL_PATH_LENGTH>
    >;
}

namespace fcgi::message
{
    struct tag;
    using t = std::tuple<adt::tag<tag>,
        uri::path::t
    >;
}

using TagIndex = util::seri::TagIndex<>
    ::add<uri::path::tag>
    ::add<fcgi::message::tag>
    ;

struct t0;
struct t1;
struct t2;
struct t3;
struct t4;
using ids = util::tupl::IdManager<>
::add<t0>
::add<t1>
::add<t2>
::add<t3>
;

int main(int, char**)
{
    using util::p;
    //constexpr auto path = uri::path::t{{}, {
    //    "/v1/users/2/booking/services"
    //}};
    //constexpr auto msg = fcgi::message::t{{}, {
    //    path
    //}};
    //(void)&msg;
    constexpr auto lols = util::make_array("aalol");
    debug__((util::is_template<std::tuple, std::tuple<int>>::value));
    debug__((util::is_template<std::basic_string, std::tuple<>>::value));
    debug__((util::is_template<std::tuple, std::tuple<int, float>, int, float>::value));
    debug__((ids::id<t0>()));
    debug__((ids::id<t1>()));
    debug__((ids::id<t2>()));
    debug__((ids::id<t3>()));
    debug__((ids::id<t4>()));
    debug__((std::is_same_v<ids, util::tupl::IdManager<t3, t2, t1, t0, void>>));
    debug__((std::is_same_v<std::decay_t<decltype(lols)>, std::array<char const, sizeof(decltype(lols))>>));
    debug__((p<ids>()));
    debug__((ids::is_mine<t3>()));
    debug__((ids::is_mine<t2>()));
    debug__((ids::is_mine<t1>()));
    debug__((ids::is_mine<t0>()));
    debug__((p<ids::drop>()));
    debug__((ids::drop::is_mine<t3>()));
    debug__((ids::drop::is_mine<t2>()));
    debug__((ids::drop::is_mine<t1>()));
    debug__((ids::drop::is_mine<t0>()));
}
