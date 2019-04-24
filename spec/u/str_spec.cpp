#include "./str_spec.h"
#include "u/str.h"
#include "u/p.h"
#include <array>
#include <iostream>
namespace u::spec::str
{
    using namespace ::u::str;

    constexpr char const* lol = "lol";
    constexpr std::array<char, 4> lol1 { "lol" };

    void debug()
    {
        debug__(( ::strlen("lol") ));
    }

    void runtime()
    {
    }
}
