#pragma once
#include "./stdx/is_detected.h"
#include "./stdx/compiler.h"
#include "./stdx/remove_cvref.h"
#include "./stdx/make_array.h"
#include <type_traits>

namespace stx { using namespace stdx; }

#if defined(STDX_GCC) && STDX_GCC
enum char8_t: char;
#else
#   error No definition for char8_t.
#endif
