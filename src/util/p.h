#pragma once
namespace util
{
template <typename T> char const* p() { return __PRETTY_FUNCTION__; }
}
#define debug__(EXPR) (std::cerr << #EXPR << ": " << (EXPR) << '\n')
