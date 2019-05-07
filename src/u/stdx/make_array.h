#pragma once
#include <array>
namespace stdx
{
    namespace _detail::make_array
    {
        template <
            std::size_t N,
            typename T,
            std::size_t... Index
        >
        constexpr auto make_array_impl(T (& arr)[N], std::index_sequence<Index...>)
        {
            return std::array<T, N> { arr[Index]... };
        }
    }


    template <std::size_t N, typename T>
    constexpr auto make_array(T (& arr)[N])
    {
        using _detail::make_array::make_array_impl;
        return make_array_impl(arr, std::make_index_sequence<N>{});
    }
}
