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
    src/u/test.cpp
    src/u/f/compose.cpp
    src/u/bchnk.cpp
)


add_executable(main)
target_link_libraries(main PRIVATE _compile_options)
target_link_libraries(main PRIVATE
    u
)
target_sources(main PRIVATE
    src/main.cpp
)
