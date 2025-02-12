#include <string>
#include <iostream>
#include "cppzednet/include/echoz.hpp"

int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 4) {
        std::cout << "Usage: edu_cpp_zed_net (-server <port> | -client <host> <port>)" << std::endl;
        return 0;
    }

    std::string option = argv[1];

    if (argc == 3 && option == "-server") {
        return cppzednet::Echoz::RunServer(static_cast<unsigned short>(std::stoul(argv[2])));
    } else if (argc == 4 && option == "-client") {
        return cppzednet::Echoz::RunClient(argv[2], static_cast<unsigned short>(std::stoul(argv[3])));
    }
}
