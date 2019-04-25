#pragma once
#include "u/stdx.h"
#include <optional>
namespace u::util
{
    template <
        typename Val,
        typename Default
    >
    constexpr auto or_else(Val&& val, Default&& dflt)
    {
        if constexpr (std::is_same_v<stdx::remove_cvref_t<Val>, std::nullopt_t>)
            return std::forward<Default>(dflt);
        else
            return std::forward<Val>(val);
    }
}
