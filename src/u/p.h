#pragma once
#include <string_view>
#include <ostream>
#include <deque>
#include <iostream>
namespace u
{
    template <
        typename T
    >
    constexpr std::string_view p()
    {
        constexpr auto length = &std::char_traits<char>::length;
        auto result = std::string_view { __PRETTY_FUNCTION__ };
#if defined(__clang__)
        constexpr auto compiler_prefix = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        constexpr auto compiler_suffix = "]";
        static_assert(length(compiler_prefix) == 29);
#elif defined(__GNUC__) || defined(__GNUG__)
        constexpr auto compiler_prefix = "constexpr std::string_view u::p() [with T = ";
        constexpr auto compiler_suffix = "; std::string_view = std::basic_string_view<char>]";
#endif
        result.remove_prefix(length(compiler_prefix));
        result.remove_suffix(length(compiler_suffix));
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
        constexpr auto ID = methystos;
    }

    constexpr std::string_view _basename(char const* file)
    {
        std::string_view file_view { file };
        const auto slash = file_view.rfind("/");
        if (slash == std::string_view::npos)
            return file_view;

        const auto begin = slash + 1;
        const auto end = file_view.rfind(".");
        if (end == std::string_view::npos)
            return file_view.substr(begin);

        const auto len = end - begin;
        return file_view.substr(begin, len);
    }

    template <
        typename T
    >
    void _debug__(std::ostream& o, char const* file, char const* expr, T&& val)
    {
        o
        << u::c::BG
        << u::c::SEG << "[:. "
        << u::c::ID << _basename(file)
        << u::c::SEG << " .:] "
        << u::c::T << expr << ": "
        << u::c::SAY << val
        << u::c::RSNL;
    }

    inline void _assert__(std::ostream& o, char const* file, char const* expr, bool val)
    {
        o
        << u::c::BG
        << u::c::SEG << "[:. "
        << u::c::ID << _basename(file)
        << u::c::SEG << " .:] "
        << u::c::T << expr
        << u::c::SEG << " .::. "
        << (val ? (o << u::c::SUCC << "¯\\_(ツ)_/¯")
            : (o << u::c::FAIL << " :'( "), "")
        << u::c::SEG << " .:]"
        << u::c::RSNL
        ;
    }

    inline void _say__(std::ostream& o, char const* file, char const* msg)
    {
        o
        << u::c::BG
        << u::c::SEG << "[:. "
        << u::c::ID << _basename(file)
        << u::c::SEG << " .:] "
        << u::c::SAY << msg
        << u::c::RSNL
        ;
    }

}
#define debug__(EXPR)   u::_debug__(std::cerr, __FILE__, #EXPR, (EXPR))
#define assert__(EXPR)  u::_assert__(std::cerr, __FILE__, #EXPR, (EXPR))
#define say__(EXPR)     u::_say__(std::cerr, __FILE__, #EXPR)
#define static_assert__(EXPR)   static_assert(EXPR)
