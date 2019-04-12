#include "config.h"
#include "u/test.h"
#include "u/view.h"
#include "u/p.h"
#include <type_traits>
#include <tuple>
#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <tuple>
//
#include <sys/select.h>
int select(
    int              nfds,
    fd_set           *readfds,
    fd_set           *writefds,
    fd_set           *errorfds,
    struct timeval   *timeout
);

using std::get;

constexpr auto lol = u::view::view<std::array<int, 4>>{};
constexpr auto lol2 = lol.emplace_back(5);
static_assert(lol2->size() == 3);

int main(int argc, char const* argv[])
{
    return u::spec::main(argc, argv);
}
