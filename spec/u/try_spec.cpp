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
    using ::u::try_::adt;

    struct AnError: public Error {};
    struct NotAnError {};
    struct AnUnrelated {};

    using var_t = std::variant<AnError, NotAnError>;

    constexpr var_t an_error = AnError{};
    constexpr var_t not_an_error = NotAnError{};

    using var_a = adt<AnError>;
    using var_b = adt<AnError, NotAnError>;
    using var_c = adt<AnUnrelated, AnError>;

    static_assert__(( is_error    (   AnError     {}  )                 ));
    static_assert__(( !is_error   (   NotAnError  {}  )                 ));
    static_assert__(( is_error    (   an_error        )                 ));
    static_assert__(( !is_error   (   not_an_error    )                 ));
    static_assert__(( std::is_convertible_v<var_a, var_b>               ));
    static_assert__(( std::is_convertible_v<var_a::variant_type, var_b> ));
    static_assert__(( std::is_convertible_v<var_b::variant_type, var_b> ));
    static_assert__(( std::is_convertible_v<AnError, var_a>             ));
    static_assert__(( std::is_convertible_v<AnError, var_b>             ));
    static_assert__(( std::is_convertible_v<NotAnError, var_b>          ));
    static_assert__(( std::is_convertible_v<AnUnrelated, var_c>         ));
    static_assert__(( !std::is_convertible_v<AnUnrelated, var_a>        ));
    static_assert__(( !std::is_convertible_v<AnUnrelated, var_b>        ));
    static_assert__((  std::is_convertible_v<var_a, var_c>              ));
    static_assert__(( !std::is_convertible_v<var_b, var_c>              ));
    static_assert__(( !std::is_convertible_v<var_c, var_a>              ));
    static_assert__(( !std::is_convertible_v<var_c, var_b>              ));

    void debug()
    {
    }
}
