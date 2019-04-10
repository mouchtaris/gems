#pragma once
#include <cstddef>
#include <array>
#include "config.h"
namespace u::bchnk
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
        std::size_t Size
    >
    struct adt
    {
        std::array<std::byte, Size> data;
        std::size_t first = 0;
        std::size_t afterlast = data.size();

        constexpr std::size_t size() const
        {
            return afterlast - first;
        }

        constexpr std::byte const* begin() const
        {
            return data.data() + first;
        }

        constexpr std::byte const* end() const
        {
            return data.data() + afterlast;
        }
    };
}
