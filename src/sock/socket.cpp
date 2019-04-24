#include "./socket.h"
#include <type_traits>  // std::is_*
#include <utility>      // std::forward
#include <sys/socket.h> // ::shutdown
#include <unistd.h>     // ::close
namespace
{
    using namespace sock;
    using ::u::try_::stdtry;
    using ::u::try_::adt;
    using ::u::try_::StandardError;

    constexpr auto INVALID_FD = -666;
    static_assert(std::is_same_v<
        std::remove_const_t<decltype(INVALID_FD)>,
        decltype(sockfd_t{}.value)
    >);

    //! A decoration for private operations
    struct deco
    {
        sock::socket& self;

        auto fd() const
        {
            return self.fd.value;
        }

        bool is_fd_valid() const
        {
            return fd() > 2;
        }

        using close_result = adt<int, StandardError>;

        Closing close()
        {
            if (!is_fd_valid())
                return StandardError {
                    { },
                    { "Invalid FD" }
                };

            const auto fd = deco::fd();

            auto&& try_shutdown = stdtry(
                [fd]() { return ::shutdown(fd, ::SHUT_RDWR); }
            );
            RETURN_IF_ERROR(try_shutdown);

            auto&& try_close = stdtry(
                [fd]() { return ::close(fd); }
            );
            RETURN_IF_ERROR(try_close);

            return fd;
        }

        void clear_fd()
        {
            self.fd.value = INVALID_FD;
        }

        Closing moved()
        {
            auto&& try_close = close();
            clear_fd();
            return try_close;
        }
    };
}

namespace sock
{
    socket::socket(socket&& other):
        fd { std::move(other.fd) }
    {
        Closing result = deco { other }.moved();
        if (is_error(result))
            throw result;
    }

    socket::~socket()
    {
        Closing result = deco { *this }.moved();
        if (is_error(result))
            // TODO: comment in
        {} // throw result;
    }
}
