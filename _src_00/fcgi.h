#pragma once
#include <stdint.h> // uint8_t
#include <stddef.h> // size_t
#include "bytes.h"
// typedef struct {
//     unsigned char version;
//     unsigned char type;
//     unsigned char requestIdB1;
//     unsigned char requestIdB0;
//     unsigned char contentLengthB1;
//     unsigned char contentLengthB0;
//     unsigned char paddingLength;
//     unsigned char reserved;
//     unsigned char contentData[contentLength];
//     unsigned char paddingData[paddingLength];
// } FCGI_Record;

namespace fcgi_record
{
    static constexpr size_t version = 0;
    static constexpr size_t type = 1;
    static constexpr size_t requestIdB1 = 2;
    static constexpr size_t requestIdB0 = 3;
    static constexpr size_t contentLengthB1 = 4;
    static constexpr size_t contentLengthB0 = 5;
    static constexpr size_t paddingLength = 6;
    static constexpr size_t reserved = 6;
    static constexpr size_t bytesize = reserved + 1;

    using bytes = ::bytes::chunk<bytesize>;
}
