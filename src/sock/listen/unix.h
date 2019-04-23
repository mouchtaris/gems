#pragma once
#include "../common.h"
#include "u/view.h"
#include "u/try.h"
#include "u/tmap.h"
#include <variant>
#include <sys/un.h>
namespace sock::listen::unix_
{
    using namespace sock::common;

    create_result   create();
    ::sockaddr_un   address(sockaddr_unix_path);
    std::size_t     address_len(::sockaddr_un);
    bind_result     bind(sockaddr_unix_path);
}
