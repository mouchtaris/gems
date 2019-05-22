#pragma once
#include <cerrno>
#include <cstring>
#include <ostream>

struct std_error
{
    int code = errno;
};

inline std::ostream& operator << (std::ostream& o, std_error e)
{
    return o << "std_error{" << ::strerror(e.code) << '}';
}
