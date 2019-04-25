#include "./try_spec.h"
#include "u/try.h"
#include "u/p.h"
#include <iostream>
#define st(EXPR) static_assert__(EXPR); assert__(EXPR);
namespace
{
    using ::u::p;
    using namespace ::u::try_;
    using ::u::try_::_detail::is_error;

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


    static_assert__(( std_check_error(0) == false ));
    static_assert__(( std_check_error(1) == false ));
    static_assert__(( std_check_error(-1) == true ));

    int stdfail()
    {
        errno = 12;
        return -1;
    }

    int stdok()
    {
        return 12;
    }

    struct custom_result{bool failed;};
    struct custom_error: public u::try_::Error{};
    struct custom_check_result
    {
        bool failed;
        inline operator bool() const { return failed; }
    };
    custom_result       custom_fail() { return { true }; }
    custom_result       custom_succ() { return { false }; }
    custom_check_result custom_check_error(custom_result x) { return { x.failed }; }
    custom_error        custom_to_error(custom_result) { return {}; }
}

namespace u::spec::try_
{
    void debug(spec)
    {
    }

    void runtime(spec)
    {
        using u::try_::stdtry;

        assert__(( is_error(stdtry(stdfail)) ));
        assert__(( not is_error(stdtry(stdok)) ));

        assert__(( is_error(stdtry(custom_fail, custom_check_error, custom_to_error)) ));
        assert__(( not is_error(stdtry(custom_succ, custom_check_error, custom_to_error)) ));
    }
}
