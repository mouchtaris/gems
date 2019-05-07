#pragma once
namespace stdx
{
    constexpr bool GCC =
#if defined(__GNUC__) || defined(__GNUG__)
#define STDX_GCC 1
        true
#else
        false
#endif
        ;

    constexpr bool CLANG =
#if defined(__clang__)
#define STDX_CLANG 1
        true
#else
        false
#endif
        ;

    static_assert(GCC | CLANG);
}
