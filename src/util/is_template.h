#pragma once
#include <type_traits>
namespace util
{
    //! is_template
    //
    /// Use like:
    ///     is_template<std::tuple, std::tuple<int, float>, int, float>::value == true;
    ///     is_template<std::string, std::tuple<>> == false;
    //
    template <
        template <typename...> typename,
        typename = std::void_t<>,
        typename...
    >
    struct is_template: public std::false_type { };

    template <
        template <typename...> typename Template,
        typename... Args
    >
    struct is_template<Template,
        Template<Args...>,
        Args...
    >: public std::true_type { };
}
