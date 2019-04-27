#pragma once
#include "u/util.h"
namespace u::f
{
    template <
        typename Op
    >
    constexpr auto flip(Op&& op)
    {
        return [op](auto&& a, auto&& b)
        {
            return op(util::fwd(b), util::fwd(a));
        };
    }
}
