#pragma once
#include "./traits.h"
#define _U__TRAITLIB__MEM(NAME)     \
    template <typename T>   constexpr auto NAME = &T::NAME; \
    template <typename T>   using NAME##_t = decltype(NAME<T>)
namespace u::traitlib
{
    _U__TRAITLIB__MEM(length);
    _U__TRAITLIB__MEM(message);
}
