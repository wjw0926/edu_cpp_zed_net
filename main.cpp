#include <string>
#include <iostream>
#include "cppzednet/include/echoz.hpp"

int main(int argc, char* argv[]) {
    std::string option = argv[1];

    if (argc == 3 && option == "-server") {
        return Echoz::RunServer(static_cast<unsigned short>(std::stoul(argv[2])));
    } else if (argc == 4 && option == "-client") {
        return Echoz::RunClient(argv[2], static_cast<unsigned short>(std::stoul(argv[3])));
    }

    std::cout << "Usage: edu_cpp_zed_net [-server [port] or -client [host] [port]" << std::endl;

    return 0;
}
