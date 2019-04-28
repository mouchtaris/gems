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

namespace {
namespace inc
{
    struct Configuration
    {
        sock::sockaddr_unix_path    socket_path;
    };

    using chars = std::char_traits<char>;

    //! Create a setter factory.
    ///
    /// Setter factory is configured with a pointer to a Configuration member.
    /// Calling the factory with a value will create a setter,
    /// which when called with a Configuration instance will set
    /// the member pointed by ptr with the value passed to the factory.
    template <
        typename T
    >
    constexpr auto make_setter_factory(T Configuration::*ptr)
    {
        //! A setter factory
        /// Called with a value, creates setters that will set this value
        /// on the member pointed by ptr when called with a Configuration
        /// instance.
        const auto&& factory = [ptr](std::string_view value)
        {
            //! A setter
            /// Will set value into *ptr.
            const auto&& setter = [ptr, value](Configuration config)
            {
                //TODO: comment in
                (void)ptr;
                //u::str::scanf(config.*ptr, value);
                return config;
            };

            return setter;
        };

        return factory;
    }

    //! Create a prefix-based value extractor.
    ///
    /// When called with a value, will extract the value if the prefix matches.
    constexpr auto make_prefix_based_value_extractor(char const* prefix)
    {
        //! A prefix-based value extractor
        /// Will extract a value if the prefix matches, returns nullopt otherwise.
        const auto&& extractor = [prefix](std::string_view arg) -> std::optional<std::string_view>
        {
            if (starts_with(arg, prefix))
                return arg.substr(chars::length(prefix));
            else
                return std::nullopt;
        };

        return extractor;
    }

    //! All option handlers
    ///
    /// Option handlers are pairs of
    ///
    ///     value_extractor => configuration_mod
    ///
    constexpr auto option_handlers = std::tuple {
        std::tuple { make_prefix_based_value_extractor("--socket_path="), make_setter_factory(&Configuration::socket_path) }
    };


    //! Handle an option
    ///
    /// Pass the option through all handlers.
    constexpr auto handle_option(std::string_view)
    {
        using stdx::get;

        //auto&& handler0 = get<0>(option_handlers);
        //auto&& extr0 = get<0>(handler0);
        //auto&& mod0 = get<1>(handler0);
        return 0;
    }
}
}

namespace
{
    constexpr auto nl = '\n';
    void help(int, char const* argv[])
    {
        std::cerr
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

    return success? 0 : 1;
}
