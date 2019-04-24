#pragma once
#include "../common.h"
#include "u/view.h"
#include "u/try.h"
#include "u/tmap.h"
#include "u/traits.h"
#include <variant>
#include <sys/un.h>
namespace sock::listen::unix_
{
    using namespace sock::common;

    create_result   create();
    ::sockaddr_un   address(sockaddr_unix_path);
    std::size_t     address_len(::sockaddr_un);
    bind_result     bind(sockaddr_unix_path);

    //! Something sufficient to describe a unix socket.
    template <
        typename PathIterable
    >
    struct adt
    {
        PathIterable& path;
    };

    //!
    template <
        typename PathIterable
    >
    adt(PathIterable&&) -> adt<std::remove_reference_t<PathIterable>>;

    //! Create and bind a UNIX Socket.
    template <
        typename Adt
    >
    auto create_and_bind(Adt&& adt)
    {
        sockaddr_unix_path path;
        std::copy_n(
            begin(adt.path)
        );
    }
}
