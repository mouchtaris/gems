# vim: et ts=4 sw=4

#set(CMAKE_CXX_COMPILER /usr/bin/clang++)
cmake_minimum_required(VERSION 3.12)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(_compile_options INTERFACE)
target_compile_features(_compile_options INTERFACE cxx_std_20)
target_compile_options(_compile_options INTERFACE -Wall -Wextra -Werror -pedantic -O0 -g -fdiagnostics-color=always)
target_include_directories(_compile_options INTERFACE src)
target_compile_definitions(_compile_options INTERFACE DEBUG=)


add_library(u)
target_link_libraries(u PRIVATE _compile_options)
target_sources(u PRIVATE
    src/u/f/compose.cpp
    src/u/f.cpp
    src/u/p.cpp
    src/u/stdx/compiler.cpp
    src/u/stdx.cpp
    src/u/stdx/is_detected.cpp
    src/u/stdx/is_detected.cpp
    src/u/stdx/make_array.cpp
    src/u/stdx/remove_cvref.cpp
    src/u/str.cpp
    src/u/tmap.cpp
    src/u/traitlib.cpp
    src/u/traits.cpp
    src/u/try.cpp
    src/u/util.cpp
    src/u/view.cpp
    src/bytebuf.cpp
)


add_library(adt)
target_link_libraries(adt PRIVATE _compile_options)
target_sources(adt PRIVATE
    src/adt/adt_tag.cpp
    src/adt/bytesize.cpp
    src/adt/types.cpp
    src/adt.cpp
)


add_library(sock)
target_link_libraries(sock PRIVATE _compile_options)
target_sources(sock PRIVATE
    src/sock/common.cpp
    src/sock/listen/unix.cpp
    src/sock/socket.cpp
)


add_library(msg)
target_link_libraries(msg PRIVATE _compile_options)
target_sources(msg PRIVATE
    src/msg/input_socket.cpp
    src/msg/test_msg.cpp
)


add_library(config)
target_link_libraries(config PRIVATE _compile_options)
target_sources(config PRIVATE
    src/config/parse.cpp
    src/config/config.cpp
)


add_library(app)
target_link_libraries(app PRIVATE _compile_options)
target_sources(app PRIVATE
    src/app/Configuration.cpp
)


add_library(fcgi)
target_link_libraries(fcgi PRIVATE _compile_options)
target_sources(fcgi PRIVATE
    src/fcgi/record.cpp
)


add_executable(spec)
target_link_libraries(spec PRIVATE _compile_options)
target_include_directories(spec PRIVATE spec)
target_sources(spec PRIVATE
    spec/config/parse_spec.cpp
    spec/config_spec.cpp
    spec/sock/listen/unix_spec.cpp
    spec/sock_spec.cpp
    spec/spec.cpp
    spec/u/compose_spec.cpp
    spec/u/f_spec.cpp
    spec/u_spec.cpp
    spec/u/stdx/make_array_spec.cpp
    spec/u/stdx_spec.cpp
    spec/u/str_spec.cpp
    spec/u/tmap_spec.cpp
    spec/u/traitlib_spec.cpp
    spec/u/try_spec.cpp
    spec/u/view_spec.cpp
    spec/fcgi_spec.cpp
    spec/fcgi/record_spec.cpp
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
