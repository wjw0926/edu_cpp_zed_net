cmake_minimum_required(VERSION 3.10)

project(edu_cpp_zed_net)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(cppzednet)

# Reference: https://gist.github.com/lefticus/10191322#c-coding-standards-part-0-automated-code-analysis
# -Wall: basic warning option
# -Wextra: extra warning option
# -Wshadow: warn the user if a variable declaration shadows another with the same name in the same scope
# -Wnon-virtual-dtor: warn the user if a class with virtual functions has a non-virtual destructor; This can lead to hard to track down memory errors
# -pedantic: warn about non-portable code, C++ that uses language extensions
add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic)

add_executable(edu_cpp_zed_net
        main.cpp
        )

target_link_libraries(edu_cpp_zed_net
        cppzednet
        )
