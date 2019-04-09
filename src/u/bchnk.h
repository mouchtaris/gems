#pragma once
#include <cstddef>
#include <array>
#include "config.h"
namespace u::bchk
{
    //! A byte chunk view.
    /// A bytebuffer is a byte array, with extra information
    /// on the valid part of the array for reading.
    ///
    /// The difference from all other views of STD lib is that
    /// byte-chunks come with storage, and they restrict the viww
    /// window to it as well. The reason is that no dynamic allocation
    /// is needed this way, and bytechunks can be passes around as
    /// POD object.
    //
    template <
        typename BC,
        typename = void
    >
    struct byte_chunk_traits
    {
        static constexpr bool defined = false;
    };

    template <
        typename BC
    >
    struct byte_chunk_traits<
        BC,
        std::void_t<
            std::enable_if_t<std::tuple_size<BC>::value == 3, void>
        >
    >
    {
    };

    template <
        std::size_t Size
    >
    using Adt = std::tuple<
        std::array<std::byte, Size>,
        std::size_t,
        std::size_t
    >;

    template <
        std::size_t Size
    >
    static constexpr Adt<Size> create()
    {
        return {
            {},
            0,
            Size - 1
        };
    }
}
