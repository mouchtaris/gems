#include "./try_spec.h"
#include "u/try.h"
#include "u/p.h"
#include <iostream>
#define st(EXPR) static_assert__(EXPR); assert__(EXPR);
namespace u::spec::try_
{
    using ::u::p;
    using ::u::try_::Error;
    using ::u::try_::_detail::is_error;
    using ::u::try_::_detail::ID;
    using ::u::try_::adt;

    struct AnError: public Error {};
    struct NotAnError {};

    using var_t = std::variant<AnError, NotAnError>;

    constexpr var_t an_error = AnError{};
    constexpr var_t not_an_error = NotAnError{};

    using var_a = adt<AnError>;
    using var_b = adt<AnError, NotAnError>;

    static_assert(std::is_convertible_v<var_a, var_b>);

    void debug()
    {
        st( is_error    (   AnError     {}  ));
        st( !is_error   (   NotAnError  {}  ));
        st( is_error    (   an_error        ));
        st( !is_error   (   not_an_error    ));
    }
}
