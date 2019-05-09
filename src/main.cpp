#include "config/config.h"
#include "u/view.h"
#include "u/p.h"
#include "u/str.h"
#include "u/f/compose.h"
#include "config/parse.h"
#include "app/Configuration.h"
#include "fcgi/record.h"
#include "u/stdx.h"
#include "msg/input_socket.h"
#include "msg/input_socket.h"
#include "msg/test_msg.h"
#include "sock/listen/unix.h"
#include "bytebuf.h"
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
    namespace stx { using namespace stdx; }
    constexpr auto testargs = stdx::array {
        "--socket_path=/tmp/m2_cgi.sock",
    };

    constexpr auto config = config::parse_args(app::handlers, testargs, app::Configuration{});
        constexpr auto socket_path_arg = stdx::string_view { stdx::get<0>(testargs) };
        constexpr auto socket_path_prefix = stdx::string_view { "--socket_path=" };
        constexpr auto socket_path_expected_value = socket_path_arg.substr(socket_path_prefix.size());
        constexpr auto socket_path_value = stdx::string_view { begin(config.socket_path) };
        static_assert__(( socket_path_value.compare(socket_path_expected_value) == 0 ));


    namespace event
    {
        struct FcgiData { bytebuf buf; };
        using all = stdx::variant<
            FcgiData
        >;
    }

    namespace handler
    {
        struct FcgiRecord { adt::bytes<fcgi::record::adt> bytes; };
        struct PrintFcgiRecord { FcgiRecord rec; };
        using all = stdx::variant<
            FcgiRecord,
            PrintFcgiRecord
        >;
    }

    struct State
    {
        handler::all handler;
        bytebuf fcgi_data;
    };


    State&& reduce(State&& state, handler::FcgiRecord rec)
    {
        state.fcgi_data = read(state.fcgi_data, rec.bytes);
        if (rec.bytes.has_remaining())
            state.handler = stx::move(rec);
        else
            state.handler = handler::PrintFcgiRecord { stx::move(rec) };
        return stx::move(state);
    }

    State&& reduce(State&& state, handler::PrintFcgiRecord)
    {
        return stx::move(state);
    }

    State&& reduce(State&& state)
    {
        return stx::visit(
            [&state](auto&& handler) -> State&& { return reduce(stx::move(state), stx::move(handler)); },
            state.handler
        );
    }


    constexpr State test_state()
    {
        return {
            .handler = handler::FcgiRecord{},
            .fcgi_data = {
                { 1, 2, 3, 4 },
                0, 0, 4, 4
            },
        };
    }
    static_assert__(( test_state().fcgi_data.remaining() == 4 ));
    void debug()
    {
        debug__(( socket_path_value ));
        debug__(( sizeof(bytebuf) ));
        assert__(( !reduce(test_state()).fcgi_data.has_remaining() ));
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
