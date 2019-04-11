#pragma once
#include "config.h"
#include "u/view.h"
#include <array>
namespace u::bchnk
{
    //! A byte chunk view.
    template <
        std::size_t Size
    >
    using adt = u::view::view<std::array<std::byte, Size>>;
}
