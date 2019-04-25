#pragma once
#include "u/try.h"
#include "u/view.h"
#include <sys/un.h>
namespace sock
{
    inline namespace common
    {
        namespace errors
        {
            struct Error: public u::try_::Error
            {
                u::try_::StandardError stderror;

                Error() = default;

                template <
                    typename Arg,
                    std::enable_if_t<
                        std::is_same_v<
                            stdx::remove_cvref_t<Arg>,
                            u::try_::StandardError
                        >,
                        int
                    > = 0
                >
                constexpr Error(Arg&& arg):
                    u::try_::Error {},
                    stderror { std::forward<Arg>(arg) }
                {}
            };
            struct SocketCreation: public Error
            {
                using Error::Error;
            };
            struct SocketBinding: public Error{};
        }

        struct sockfd_t { int value; };

        struct sockaddr_unix_path {
            u::view::view<std::array<char, sizeof(::sockaddr_un{}.sun_path)>> value;
        };
#if defined(unix)
        static_assert(sockaddr_unix_path{}.value.size() == 108);
#elif defined(__APPLE__)
        // TODO: figure mac size
        //static_assert(sockaddr_unix_path{}.value.size() == 108);
#endif

        using Creation = u::tmap::tpack<sockfd_t, errors::SocketCreation>;
        using Binding = Creation::append<errors::SocketBinding>;

        using create_result = Creation::into<u::try_::adt>;
        using bind_result = Binding::into<u::try_::adt>;
    }
}
