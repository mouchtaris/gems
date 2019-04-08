#pragma once
#include <cstddef>
namespace config
{
    //! Path size
    /// Specifies the maximum size of a path string
    /// (URI path, Filesystem path, whatever).
    constexpr std::size_t PATH_SIZE = 1024;
}
