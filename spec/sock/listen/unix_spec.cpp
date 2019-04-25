#include "./unix_spec.h"

#include "sock/listen/unix.h"

#include "u/p.h"

#include <iostream>

namespace {

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
    }
}
