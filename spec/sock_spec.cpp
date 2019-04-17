#include "./sock_spec.h"
#include "./sock/listen/unix_spec.h"
namespace sock::spec
{
    void debug()
    {
        listen::unix_::debug();
    }
}
