#pragma once
#include <string_view>
namespace u
{
    template <
        typename T
    >
    constexpr std::string_view p()
    {
        auto result = std::string_view { __PRETTY_FUNCTION__ };
        result.remove_prefix(29);
        result.remove_suffix(1);
        return result;
    }
}
#define debug__(EXPR) (std::cerr << #EXPR << ": " << (EXPR) << '\n')
