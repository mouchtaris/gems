#pragma once
#include "./traits.h"
namespace u::traitlib
{
    template <typename T> constexpr auto length = &T::length;
    template <typename T> using length_t = decltype(length<T>);
}
