# vim: et ts=4 sw=4

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
cmake_minimum_required(VERSION 3.12)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(_compile_options INTERFACE)
target_compile_features(_compile_options INTERFACE cxx_std_20)
target_compile_options(_compile_options INTERFACE -Wall -Wextra -pedantic -O0 -g)
target_include_directories(_compile_options INTERFACE src)
target_compile_definitions(_compile_options INTERFACE DEBUG=)

add_library(libutil)
target_link_libraries(libutil PRIVATE _compile_options)
target_sources(libutil PRIVATE
    src/util/arrays.cpp
    src/util/find.cpp
    src/util/index.cpp
    src/util/lazy_conditional.cpp
    src/util/lib.cpp
    src/util/p.cpp
    src/util/seri.cpp
    src/util/test.cpp
    src/util/tuple.cpp
)


add_executable(main)
target_link_libraries(main PRIVATE _compile_options)
target_link_libraries(main PRIVATE
)

target_sources(main PRIVATE
    src/main.cpp
)
