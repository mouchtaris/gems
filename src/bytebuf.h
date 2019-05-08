#pragma once
#include "u/stdx.h"
#include "u/view.h"
#include "u/p.h"
#include "u/traitlib.h"
#include "u/util.h"
#include <cstring>

//! Store S num of bytes
template <
    stdx::size_t S
> using bytes = u::view::view<stdx::array<uint8_t, S>>;

//! Serialized (bytes) storaeg with sizeof(T)
template <
    typename T
> using serial = bytes<sizeof(T)>;

//! Plain 1024 bytes long bytebuf
using bytebuf_data = uint8_t[1024];
//! Plain 1024 bytes long bytebuf
using bytebuf = serial<bytebuf_data>;
// Assert that sizeof(uint8_t) == 1
static_assert__(( bytebuf{}.size() == sizeof(bytebuf_data) ));

//! Read from a bytebuf into a memory segment
template <
    typename T,
    typename = stdx::enable_if_t<
        stdx::conjunction_v<
            stdx::is_trivial<
                stdx::remove_cvref_t<
                    u::traitlib::iterator_element_t<T>
                >
            >,
            stdx::is_pointer<
                stdx::remove_cvref_t<
                    u::traitlib::begin_t<T>
                >
            >
        >
    >
>
bytebuf read(bytebuf from, T&& into)
{
    const auto n = stdx::min(from.remaining(), u::util::iterable_size(into));
    stdx::memcpy(begin(into), begin(from), n);
    return from.subview(n);
}

