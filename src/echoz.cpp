//
// Created by jwW on 2019-10-15.
//

#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory>
#include <iostream>

#include "echoz.hpp"
#include "udp_socket.hpp"
#include "error.hpp"

int Echoz::RunServer(unsigned short port) {
    auto udp_socket = std::make_unique<UDPSocket>();
    udp_socket->Open(port, 0);

    std::cout << "Running echo server on port " << port << std::endl;

    char buffer[256];

    while (strcmp(buffer, "done") != 0) {
        InternetAddress address{};

        int bytes_read = udp_socket->Receive(&address, &buffer, sizeof(buffer));
        if (bytes_read) {
            std::cout << "Received " << bytes_read << " bytes from "
                      << Echoz::HostToStr(address.GetHost()) << ":"
                      << address.GetPort() << ": "
                      << buffer << std::endl;

            std::cout << "Echoing..." << std::endl;
            udp_socket->Send(address, buffer, sizeof(buffer));
        }
    }

    std::cout << "Done!" << std::endl;
    udp_socket->Close();

    return 0;
}

int Echoz::RunClient(const char *host, unsigned short port) {
    auto udp_socket = std::make_unique<UDPSocket>();
    udp_socket->Open(0, 0);

    InternetAddress address{};

    if (!address.SetHost(host)) {
        std::cout << "Error: " << Error::instance().GetMessage() << std::endl;
        udp_socket->Close();

        return -1;
    }
    address.SetPort(port);

    std::cout << "Running client! Type \"done\" to exit." << std::endl;

    char buffer[256];

    while (strcmp(buffer, "done") != 0) {
        std::cout << "Message: ";

        fgets(buffer, 256, stdin);
        buffer[strlen(buffer) - 1] = '\0';

        std::cout << "Sending..." << std::endl;
        udp_socket->Send(address, buffer, sizeof(buffer));

        InternetAddress sender{};

        int bytes_read = udp_socket->Receive(&sender, &buffer, sizeof(buffer));
        if (bytes_read) {
            std::cout << "Received " << bytes_read << " bytes from "
                      << Echoz::HostToStr(sender.GetHost()) << ":"
                      << sender.GetPort() << ": "
                      << buffer << std::endl;
        }
    }

    std::cout << "Done!" << std::endl;
    udp_socket->Close();

    return 0;
}

const char *Echoz::HostToStr(unsigned int host) {
    struct in_addr in{};
    in.s_addr = host;

    return inet_ntoa(in);
}
