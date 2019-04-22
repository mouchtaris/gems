#pragma once
#include <string_view>
#include <ostream>
#include <deque>
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

    template <
        typename T
    >
    void _debug__(std::ostream& o, char const* expr, T&& val)
    {
        o
        << u::c::BG
        << u::c::SEG << expr << ": "
        << u::c::SAY << val
        << u::c::RSNL;
    }

    inline void _assert__(std::ostream& o, char const* expr, bool val)
    {
        o
        << u::c::BG
        << u::c::SEG << "[:. "
        << u::c::T << expr
        << u::c::SEG << " .::. "
        << (val ? (o << u::c::SUCC << "¯\\_(ツ)_/¯")
            : (o << u::c::FAIL << " :'( "), "")
        << u::c::SEG << " .:]"
        << u::c::RSNL
        ;
    }

    inline void _say__(std::ostream& o, char const* msg)
    {
        o
        << u::c::BG
        << u::c::SEG << "[:. "
        << u::c::SAY << msg
        << u::c::SEG << " .:]"
        << u::c::RSNL
        ;
    }

}
#define debug__(EXPR)   u::_debug__(std::cerr, #EXPR, (EXPR))
#define assert__(EXPR)  u::_assert__(std::cerr, #EXPR, (EXPR))
#define say__(EXPR)     u::_say__(std::cerr, #EXPR)
#define static_assert__(EXPR)   static_assert(EXPR)
