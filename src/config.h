#pragma once
#include <cstddef>
namespace config
{
    //! Path size
    /// Specifies the maximum size of a path string
    /// (URI path, Filesystem path, whatever).
    constexpr std::size_t PATH_SIZE = 1024;

    //! Bytechunk size
    /// The number of byte in every incoming bytechunk
    /// message.
    constexpr std::size_t BYTE_CHUNK_SIZE = 56;

    //! Message queue
    /// Specifies the maximum number of bytechunk
    /// input messages that can be held PER INPUT
    /// SOCKET in the messaging system
    ///
    /// Memory requirements:
    ///     MESSAGE_QUEUE_SIZE * BYTE_CHUNK_SIZE
    constexpr std::size_t MESSAGE_QUEUE_SIZE = 16;
}
