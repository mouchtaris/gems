#pragma once
#include "sock/common.h"
#include "u/tmap.h"
#include "u/stdx.h"
#include "bytebuf.h"
#include "adt.h"
namespace adt
{

    //! A bytes{} struct for the bytesize of T{}
    template <
        typename T
    >
    using bytes = ::bytes<bytesize(T{})>;

//    //! The runtime representation of an ADT
//    template <typename T> struct runtime;
//    template <typename... T> using runtime_t = typename runtime<T...>::type;
//    template <> struct runtime<byte_t> { using type = uint8_t; };
//    // runtime<stream_t> : not defined
//    template <
//        typename... Ts
//    >
//    struct runtime<u::tmap::tpack<Ts...>>
//    {
//        using type = typename u::tmap::eval_t<
//            u::tmap::select,
//            u::tmap::tpack<>::f<runtime_t>,
//            u::tmap::tpack<Ts...>
//        >
//        ::template prepend<adt_tag>
//        ::template into<stx::tuple>
//        ;
//    };
//
//    static_assert__(( stx::is_same_v<
//        runtime_t<u::tmap::tpack<byte_t, stream_t>>,
//        stx::tuple<adt_tag, uint8_t>
//    > ));
//
//    //! 
//    template <typename Runtime, typename T> struct get_impl;
}
namespace fcgi::record
{
    using namespace adt;

    struct version: byte_t{};
    struct type: byte_t{};
    struct requestIdB1: byte_t{};
    struct requestIdB0: byte_t{};
    struct contentLengthB1: byte_t{};
    struct contentLengthB0: byte_t{};
    struct paddingLength: byte_t{};
    struct reserved: byte_t{};
    struct contentData: stream_t{};
    struct paddingData: stream_t{};

    using adt = u::tmap::tpack<
        struct version,
        struct type,
        struct requestIdB1,
        struct requestIdB0,
        struct contentLengthB1,
        struct contentLengthB0,
        struct paddingLength,
        struct reserved,
        struct contentData,
        struct paddingData
    >;
}
