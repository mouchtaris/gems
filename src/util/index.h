#pragma once
#include <type_traits>
//! Index
//
namespace util::index
{
//! 0
struct _0;
//! Successor
template <typename> struct Succ;

//! Value<I>
/// Translate type index values to std::size_t values.
//
template <typename I> struct Value;
template <> struct Value<_0>
{
    static constexpr std::size_t value = 0;
};
template <typename Prev> struct Value
{
    static constexpr std::size_t value = Prev::value + 1;
};
template <typename I> constexpr std::size_t value_v = Value<I>::value;

//! Type
/// Translate std::size_t values to type index values.
//
template <std::size_t, typename = void> struct Type;
template <> struct Type<0>
{
    using type = _0;
};
template <std::size_t i> struct Type<i>
{
    using type = Succ<typename Type<i - 1>::type>;
};
template <std::size_t i> using type_t = typename Type<i>::type;

//! is_index
/// Check whether the given type is an index type.
//
template <typename T> struct is_index: public std::false_type { };
template <> struct is_index<_0>: public std::true_type { };
template <typename Prev> struct is_index<Succ<Prev>>: public std::true_type { };

//! minus1
/// Utility
//
template <typename T> using minus1 = type_t<value_v<T> - 1>;
}
