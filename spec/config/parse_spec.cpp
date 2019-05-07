#include "./parse_spec.h"
#include "config/parse.h"
#include "u/p.h"
namespace
{
    struct Conf
    {
        char c;
        int i;
        stdx::array<char, 12> ac;
    };

    constexpr auto defs = stdx::tuple {
        stdx::tuple { "--c=", &Conf::c },
        stdx::tuple { "--i=", &Conf::i },
        stdx::tuple { "--ac=", &Conf::ac },
    };

    constexpr auto opts = stdx::array {
        "--c=h",
        "--i=124",
        "--ac=hello",
    };

    constexpr auto config = ::config::parse_args(defs, opts, Conf{});

    static_assert__(( config.c == 'h' ));
    static_assert__(( config.i == 124 ));
    static_assert__(( u::str::strncmp(config.ac.data(), "hello", u::str::strlen("hello")) == 0 ));
}
namespace config::spec::parse
{
    void debug(spec)
    {
    }

    void runtime(spec)
    {
    }
}
