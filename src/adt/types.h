#pragma once
#include "./adt_tag.h"
#include "u/tmap.h"
namespace adt
{
    //
    // Basic types for ADTs
    //

    //! A Byte type
    struct byte_t{};

    //! A Stream type
    struct stream_t{};

    //! An aggregation (cartecian product) of other types
    template <
        typename... Types
    >
    using cart_t = u::tmap::tpack<
        adt_tag,
        Types...
    >;
}
