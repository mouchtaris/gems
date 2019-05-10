#pragma once

template <
    typename Iter
>
struct buffer
{
    const Iter first;
    const Iter position;
    const Iter limit;
    const Iter last;
};

template <
    typename Container
>
auto make_buffer(Container&& cont)
{
    auto first = begin(cont);
    auto last = end(cont);
    return buffer<decltype(first)> { first, first, last, last,};
}
