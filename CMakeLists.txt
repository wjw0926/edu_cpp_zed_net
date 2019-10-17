cmake_minimum_required(VERSION 3.10)

project(edu_cpp_zed_net)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic)

add_executable(edu_cpp_zed_net
        main.cpp
        src/echoz.cpp
        src/udp_socket.cpp
        src/internet_address.cpp
        )
