#include "./try_spec.h"
#include "u/try.h"
#include "u/p.h"
#include <iostream>
#define st(EXPR) static_assert__(EXPR); assert__(EXPR);
namespace u::spec::try_
{
    using ::u::try_::Error;
    using ::u::try_::is_error;

    struct AnError: public Error {};
    struct NotAnError {};

    using var_t = std::variant<AnError, NotAnError>;

    constexpr var_t an_error = AnError{};
    constexpr var_t not_an_error = NotAnError{};

    void debug()
    {
        st( is_error    (   AnError     {}  ));
        st( !is_error   (   NotAnError  {}  ));
        st( is_error    (   an_error        ));
        st( !is_error   (   not_an_error    ));
    }
}
