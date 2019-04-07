#pragma once
#include <array>
namespace util
{
template <std::size_t N, typename T, std::size_t... Index>
constexpr auto make_array_impl(T (& arr)[N], std::index_sequence<Index...>)
    -> std::array<T, N>
{
    return { arr[Index]... };
}

template <std::size_t N, typename T>
constexpr auto make_array(T (& arr)[N])
    -> std::array<T, N>
{
    return make_array_impl(arr, std::make_index_sequence<N>{});
}
}
