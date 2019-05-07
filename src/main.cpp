#include "config/config.h"
#include "u/view.h"
#include "u/p.h"
#include "u/str.h"
#include "u/f/compose.h"
#include "config/parse.h"
#include "app/Configuration.h"

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
    constexpr auto testargs = stdx::array {
        "--socket_path=/tmp/m2_cgi.sock",
    };

    constexpr auto config = config::parse_args(app::handlers, testargs, app::Configuration{});
    constexpr auto socket_path_arg = stdx::string_view { stdx::get<0>(testargs) };
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
