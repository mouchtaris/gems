#include "./error.h"
#include <cstdio>
namespace error
{
    void print(std_error const& error)
    {
        fprintf(stderr, "Error: %s\n", error.msg);
    }
}
