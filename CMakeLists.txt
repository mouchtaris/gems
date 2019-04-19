# vim: et ts=4 sw=4

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
cmake_minimum_required(VERSION 3.12)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(_compile_options INTERFACE)
target_compile_features(_compile_options INTERFACE cxx_std_20)
target_compile_options(_compile_options INTERFACE -Wall -Wextra -pedantic -O0 -g)
target_include_directories(_compile_options INTERFACE src)
target_compile_definitions(_compile_options INTERFACE DEBUG=)


add_library(u)
target_link_libraries(u PRIVATE _compile_options)
target_sources(u PRIVATE
    src/u/arr/make_array.cpp
    src/u/test_u.cpp
    src/u/f/compose.cpp
    src/u/view.cpp
    src/u/tmap.cpp
    src/u/traits.cpp
    src/u/str.cpp
    src/u/try_.cpp
)


add_library(sock)
target_link_libraries(sock PRIVATE _compile_options)
target_sources(sock PRIVATE
    src/sock/listen/unix.cpp
)


add_library(msg)
target_link_libraries(msg PRIVATE _compile_options)
target_sources(msg PRIVATE
    src/msg/input_socket.cpp
    src/msg/test_msg.cpp
)


add_executable(spec)
target_link_libraries(spec PRIVATE _compile_options)
target_sources(spec PRIVATE
    spec/sock/listen/unix_spec.cpp
    spec/sock_spec.cpp
    spec/u/try__spec.cpp
    spec/u/tmap_spec.cpp
    spec/u_spec.cpp
    spec/spec.cpp
)

add_executable(main)
target_link_libraries(main PRIVATE _compile_options)
target_link_libraries(main PRIVATE
    msg
    u
)
target_sources(main PRIVATE
    src/main.cpp
)
