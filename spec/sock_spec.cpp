#include "./sock_spec.h"
#include "./sock/listen/unix_spec.h"
namespace sock::spec
{
    void runtime(spec)
    {
    }

    void debug(spec)
    {
        listen::unix_::debug();
    }
}
