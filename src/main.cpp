#include "config.h"
#include "util/lib.h"
#include <type_traits>
#include <tuple>
#include <array>
#include <iostream>

//! strbuf
//
namespace strbuf
{
    using adt = std::array<char, config::STRING_BUFFER_SIZE>;
}

//! adt::tag
//
namespace adt
{
    template <typename T> struct Tag{};
}


#include <sys/select.h>
int select(int nfds, fd_set  *readfds, fd_set  *writefds, fd_set *errorfds, struct timeval *timeout);

int main(int, char**)
{
}
