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

    namespace c
    {
        constexpr auto babyblack = "\x1b[48;5;17m";
        constexpr auto existenzpink = "\x1b[38;5;145m";
        constexpr auto warpink = "\x1b[38;5;215m";
        constexpr auto surgery = "\x1b[38;5;75m";
        constexpr auto palelime = "\x1b[38;5;149m";
        constexpr auto bloody = "\x1b[38;5;196m";
        constexpr auto methystos = "\x1b[38;5;99m";

        constexpr auto RSBG = "\x1b[49m\n";
        constexpr auto RSFG = "\x1b[39m";
        constexpr auto RS   = "\x1b[39m\x1b[49m";
        constexpr auto RSNL = "\x1b[39m\x1b[49m\n";

        constexpr auto BG = babyblack;
        constexpr auto SEG = warpink;
        constexpr auto T = surgery;
        constexpr auto SUCC = palelime;
        constexpr auto FAIL = bloody;
        constexpr auto SAY = methystos;
    }
}
#define debug__(EXPR) (std::cerr    \
        << u::c::BG                 \
        << u::c::SEG << #EXPR << ": "   \
        << u::c::SAY << (EXPR)      \
        << u::c::RSNL               \
    )
#define assert__(EXPR) (std::cerr   \
        << u::c::BG                 \
        << u::c::SEG << "[:. "      \
        << u::c::T << #EXPR         \
        << u::c::SEG << " .::. "    \
        << ((EXPR) ? (std::cerr << u::c::SUCC << "¯\\_(ツ)_/¯") \
            : (std::cerr << u::c::FAIL << " :'( "), "")  \
        << u::c::SEG << " .:]"      \
        << u::c::RSNL               \
    )
#define say__(EXPR) (std::cerr      \
        << u::c::BG                 \
        << u::c::SEG << "[:. "      \
        << u::c::SAY << (#EXPR)     \
        << u::c::SEG << " .:]"      \
        << u::c::RSNL               \
    )
