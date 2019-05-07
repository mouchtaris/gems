#include "config.h"
#include "u/view.h"
#include "u/p.h"
#include "u/str.h"
#include "u/f/compose.h"

#include "msg/input_socket.h"

#include "msg/input_socket.h"
#include "msg/test_msg.h"

#include "sock/listen/unix.h"

#include <type_traits>
#include <tuple>
#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <functional>
#include <sstream>
//
#include <sys/select.h>
int select(
    int              nfds,
    fd_set           *readfds,
    fd_set           *writefds,
    fd_set           *errorfds,
    struct timeval   *timeout
);

namespace
{
    struct Configuration
    {
        int test1 = 2;
        char test0;
        sock::sockaddr_unix_path    socket_path;
    };

    using chars = stdx::char_traits<char>;

    TRAIT_COND(is_config_mod, (
        stdx::is_same_v<
            stdx::invoke_result_t<T, Configuration&&>,
            Configuration&&
        >
    ));
    static_assert( !is_config_mod<chars>::value );

    constexpr auto handler0 = [](Configuration&& config) -> Configuration&&
    {
        config.test0 = 'h';
        return stdx::move(config);
    };
    static_assert__(( is_config_mod<decltype(handler0)>::value ));
    static_assert__(( handler0({}).test0 == 'h' ));

    constexpr Configuration&& handler1(Configuration&& config)
    {
        config.test1 = 3;
        return stdx::move(config);
    }
    static_assert__(( is_config_mod<decltype(handler1)>::value ));
    static_assert__(( handler1({}).test1 == 3 ));

    constexpr auto handler01 = u::f::compose(handler0, handler1);
    static_assert__(( is_config_mod<decltype(handler01)>::value ));
    static_assert__(( handler01(Configuration{}).test0 == 'h' ));
    static_assert__(( handler01(Configuration{}).test1 == 3 ));

    constexpr auto handlers = stdx::make_tuple(
        stdx::make_tuple( "--test0=", &Configuration::test0 ),
        stdx::make_tuple( "--test1=", &Configuration::test1 ),
        stdx::make_tuple("--socket_path=", &Configuration::socket_path )
    );

    template <
        typename Self,
        typename T
    >
    constexpr Self& set(Self& self, T Self::*ptr, stdx::string_view value)
    {
        u::str::scanf(self.*ptr, stdx::move(value));
        return self;
    }

    template <
        typename Self,
        typename T
    >
    constexpr auto make_set_if_prefix_handler(
            stdx::tuple<char const*, T Self::*> pair,
            stdx::string_view arg)
    {
        using stdx::get;

        return [&pair, arg](Configuration& config) -> Configuration&
        {
            const stdx::string_view prefix = u::str::view(get<0>(pair));

            if (starts_with(arg, prefix)) {
                auto&& target = get<1>(pair);
                stdx::string_view&& value = arg.substr(prefix.size());

                set(config, FWD(target), stdx::move(value));
            }

            return config;
        };
    }

    constexpr auto make_total_handler_factory = [](auto&&... pairs)
    {
        return [&pairs...](stdx::string_view arg)
        {
            return u::f::compose(make_set_if_prefix_handler(pairs, stdx::move(arg))...);
        };
    };

    //! arg => (Conf => Conf)
    constexpr auto total_handler_factory = stdx::apply(make_total_handler_factory, handlers);

    template <
        typename Args
    >
    constexpr Configuration parse_args(Args&& args, Configuration config)
    {
        for (std::string_view arg: FWD(args))
            total_handler_factory(stdx::move(arg))(config);
        return config;
    }

    constexpr auto testargs = stdx::array {
        "--test1=3",
        "--test0=h",
        "--socket_path=/tmp/m2_cgi.sock",
    };

    constexpr Configuration config = parse_args(testargs, {});
    static_assert__(( config.test0 == 'h' ));
    static_assert__(( config.test1 == 3 ));
    constexpr auto socket_path_arg = stdx::string_view { stdx::get<2>(testargs) };
    constexpr auto socket_path_prefix = stdx::string_view { "--socket_path=" };
    constexpr auto socket_path_expected_value = socket_path_arg.substr(socket_path_prefix.size());
    constexpr auto socket_path_value = stdx::string_view { begin(config.socket_path) };
    static_assert__(( socket_path_value.compare(socket_path_expected_value) == 0 ));

    void debug()
    {
        debug__(( socket_path_value ));
    }
}

namespace
{
    constexpr auto nl = '\n';
    void help(int, char const* argv[])
    {
        stdx::cerr
            << "USAGE: " << argv[0] << " SOCKET_PATH" << nl
        ;
    }
}

int main(int argc, char const* argv[])
{
    const bool success = true
        && msg::spec::main(argc, argv) == 0
        ;

    if (argc < 2) {
        help(argc, argv);
        return 1;
    }
    debug();

    return success? 0 : 1;
}
