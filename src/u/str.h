#pragma once
#include "u/traitlib.h"
#include "u/stdx.h"
#include "u/util.h"
#include <type_traits>
#include <string_view>
#include <iterator>
#include <cstring>
#include <algorithm>
#include <type_traits>
namespace std
{
    //! Start_with seems to be sometimes missing
    constexpr bool starts_with(string_view view, string_view prefix)
    {
        return std::char_traits<char>::compare(
            view.data(),
            prefix.data(),
            prefix.size()
        ) == 0;
    }
}
