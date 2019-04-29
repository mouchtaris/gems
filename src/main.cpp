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
    /// conf::*ptr => value:string_value => (config => config)
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
                (void) ptr;
                (void) value;
                //u::str::scanf(config.*ptr, value);
                return config;
            };

            return setter;
        };

        return factory;
    }

    //! A mod that does nothign
    constexpr Configuration noop(Configuration&& c)
    {
        return c;
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
    constexpr auto option_handlers = std::make_tuple(
        std::tuple { make_prefix_based_value_extractor("--socket_path="), make_setter_factory(&Configuration::socket_path) }
    );

    //! Make a handler factory from a handler pair
    ///
    /// opt:std::string_view => (Config => Config)
    ///
    /// This simply combines the extractor and the configuration mod into
    /// a single handler function that applies mod() if value_extractor()
    /// gives a value, and passes Configuration through otherwise.
    template <
        typename ValueExtractor,
        typename ConfigurationMod
    >
    constexpr auto make_option_handler_factory(ValueExtractor&& extract, ConfigurationMod&& config_mod)
    {
        auto&& factory = [extract, config_mod](std::string_view option)
        {
            auto&& option_handler = [extract, config_mod, option](Configuration config)
            {
                const auto&& value_opt = extract(option);
                if (value_opt)
                    return config_mod(*value_opt)(config);
                else
                    return config;
            };

            return std::move(option_handler);
        };

        return std::move(factory);
    }

    //! Compose all option handlers into a total.
    template <
        typename... HandlerPairs
    >
    constexpr auto make_total_option_handler(std::string_view option, HandlerPairs&&... pairs)
    {
        using stdx::get;

        return u::f::compose(make_option_handler_factory(get<0>(pairs), get<1>(pairs))(option)...);
    }

    //! Create an option handler
    /// (Config) => Config
    ///
    /// Pass the option through all handlers. Given a Configuration instance it will return a
    /// modified Configuration instance.
    constexpr auto make_option_handler_for_option(std::string_view option)
    {
        auto&& make_total_option_handler_for_option = [option](auto&&... pairs)
        {
            return make_total_option_handler(std::move(option), std::forward<decltype(pairs)>(pairs)...);
        };
        auto&& total_option_handler = apply(make_total_option_handler_for_option, option_handlers);
        return std::move(total_option_handler);
    }

    //! Handle all passed options.
    template <
        typename Iter
    >
    constexpr auto handle_options(const Iter first, const Iter last)
    {
        auto&& handle = [first, last](Configuration config)
        {
            for (Iter i = first; i != last; i = std::next(i))
                config = make_option_handler_for_option(*i)(config);
            return config;
        };
        return std::move(handle);
    }

    //
    // Test options
    //
    constexpr auto testopts = std::array {
        "--socket_path=/socker/path.sock"
    };
    constexpr auto testconfig = handle_options(begin(testopts), end(testopts))({});
    //static_assert__(
    //    std::string_view(begin(testconfig.socket_path.value), testconfig.socket_path.value.size())
    //    .compare("/socker/path.sock")
    //    == 0
    //);
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
    debug__(( begin(inc::testconfig.socket_path.value) ));

    return success? 0 : 1;
}
