#include "./unix_spec.h"

#include "sock/listen/unix.h"

#include "u/p.h"

#include <iostream>

namespace
{

}

namespace sock::spec::listen::unix_
{
    using u::p;

    void debug()
    {
        say__(( "We were all wondering why namespace unix:: didn't work." ));
        say__(( "So we made this debug call and we find out that it is" ));
        say__(( "a preprocessing macro. Naturally." ));
#ifdef unix
        debug__(( unix ));
#else
        debug__(( "Unix not defined, man" ));
#endif
        say__(( "And then some weird template problems, as usual." ));
        debug__(( p<sock::listen::unix_::sockaddr_unix_path>() ));
        debug__(( p<decltype(*begin(std::array<char const, 108>{}))>() ));
        debug__(( p<std::decay_t<decltype(*begin(std::array<char const, 108>{}))>>() ));
        debug__(( p<std::array<char const, 108>::value_type>() ));

        constexpr auto stderror = u::try_::StandardError{};
        constexpr auto error = errors::Error
            {
                stderror
            }
        ;
        constexpr auto creation_error = errors::SocketCreation
            {
                stderror,
            }
        ;
        using u::try_::wrap_std_error;
        using u::try_::StandardError;
        using creation_adt = u::try_::adt<sockfd_t, StandardError>;
        debug__(( p< decltype(error) >() ));
        debug__(( p< decltype(creation_error) >() ));
        debug__(( p<
            u::tmap::eval_t<
                u::tmap::contains,
                StandardError,
                create_result::altpack
            >
        >() ));
        debug__(( p< create_result >() ));
        debug__(( p< decltype(
                wrap_std_error<errors::SocketCreation>(
                    std::declval<creation_adt>()
                )
            )
        >() ));
        debug__(( p<
        u::tmap::eval_t<
            u::tmap::map_if,
            u::tmap::tpack<>::f<std::is_same, StandardError>,
            u::tmap::tpack<u::tmap::konst, errors::SocketCreation>,
            creation_adt::altpack
        >
        >() ));
        // Kill warnings
        (void) errors::SocketCreation { stderror };
        debug__(( std::is_convertible_v<
            errors::SocketCreation,
            decltype(wrap_std_error<errors::SocketCreation>(
                std::declval<creation_adt>()
            ))
        > ));
        auto omg = wrap_std_error<errors::SocketCreation>(
                creation_adt {
                    sockfd_t { 12 }
                }
            )
        ;
    }
}
