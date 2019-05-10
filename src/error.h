#include <type_traits>
#include <variant>
#include <cstring>
namespace error
{
    // TODO: config
    constexpr size_t STD_ERROR_MSG_LENGTH = 4096;

    struct std_error { char msg[STD_ERROR_MSG_LENGTH]; };

    struct fcgi_socket_accept: public std_error{};

    using all = std::variant<
        fcgi_socket_accept
    >;

    template <
        typename T,
        typename = std::enable_if_t<
            std::is_base_of_v<std_error, T>
        >
    >
    T&& make_std_error(T&& result, int errno_)
    {
        ::bzero(result.msg, STD_ERROR_MSG_LENGTH);
        ::strerror_r(errno_, result.msg, STD_ERROR_MSG_LENGTH);
        return std::move(result);
    }

    void print(std_error const&);
}
