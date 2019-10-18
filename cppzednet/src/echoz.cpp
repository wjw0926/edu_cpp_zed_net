//
// Created by jwW on 2019-10-15.
//

#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

#include "echoz.hpp"
#include "udp_socket.hpp"
#include "error.hpp"

int Echoz::RunServer(unsigned short port) {
    UDPSocket udp_socket;
    Error open = udp_socket.Open(port, false);
    if (open.code != ErrorCode::Success) {
        std::cout << "Error: " << open.message << std::endl;
        return -1;
    }

    std::cout << "Running echo server on port " << port << std::endl;

    char buffer[256];

    while (strcmp(buffer, "done") != 0) {
        Error receive_check = udp_socket.Check();
        if (receive_check.code != ErrorCode::Success) {
            std::cout << "Error: " << receive_check.message << std::endl;
            return -1;
        }

        InternetAddress address{};
        int bytes_read = udp_socket.Receive(&address, reinterpret_cast<char *>(&buffer), sizeof(buffer));
        if (bytes_read > 0) {
            std::cout << "Received " << bytes_read << " bytes from "
                      << HostToStr(address.GetHost()) << ":"
                      << address.GetPort() << ": "
                      << buffer << std::endl;

            Error send_check = udp_socket.Check();
            if (send_check.code != ErrorCode::Success) {
                std::cout << "Error: " << send_check.message << std::endl;
                return -1;
            }

            std::cout << "Echoing..." << std::endl;
            Error send = udp_socket.Send(address, buffer, sizeof(buffer));
            if (send.code != ErrorCode::Success) {
                std::cout << "Error: " << send.message << std::endl;
                return -1;
            }
        } else if (bytes_read < 0) {
            std::cout << "Error: failed to receive data from socket" << std::endl;
        } else {
            std::cout << "Nothing received" << std::endl;
        }
    }

    std::cout << "Done!" << std::endl;
    udp_socket.Close();

    return 0;
}

int Echoz::RunClient(const char *host, unsigned short port) {
    UDPSocket udp_socket;
    Error open_check = udp_socket.Open(0, false);
    if (open_check.code != ErrorCode::Success) {
        std::cout << "Error: " << open_check.message << std::endl;
        return -1;
    }

    InternetAddress address{};

    Error error = address.SetHost(host);
    if (error.code != ErrorCode::Success) {
        std::cout << "Error: " << error.message << std::endl;
        udp_socket.Close();
        return -1;
    }
    address.SetPort(port);

    std::cout << "Running client! Type \"done\" to exit." << std::endl;

    char buffer[256];

    while (strcmp(buffer, "done") != 0) {
        std::cout << "Message: ";

        fgets(buffer, 256, stdin);
        buffer[strlen(buffer) - 1] = '\0';

        Error send_check = udp_socket.Check();
        if (send_check.code != ErrorCode::Success) {
            std::cout << "Error: " << send_check.message << std::endl;
            return -1;
        }

        std::cout << "Sending..." << std::endl;
        Error send = udp_socket.Send(address, buffer, sizeof(buffer));
        if (send.code != ErrorCode::Success) {
            std::cout << "Error: " << send.message << std::endl;
            return -1;
        }

        Error receive_check = udp_socket.Check();
        if (receive_check.code != ErrorCode::Success) {
            std::cout << "Error: " << receive_check.message << std::endl;
            return -1;
        }

        InternetAddress sender{};
        int bytes_read = udp_socket.Receive(&sender, reinterpret_cast<char *>(&buffer), sizeof(buffer));
        if (bytes_read > 0) {
            std::cout << "Received " << bytes_read << " bytes from "
                      << HostToStr(sender.GetHost()) << ":"
                      << sender.GetPort() << ": "
                      << buffer << std::endl;
        } else if (bytes_read < 0) {
            std::cout << "Error: failed to receive data from socket" << std::endl;
        } else {
            std::cout << "Nothing received" << std::endl;
        }
    }

    std::cout << "Done!" << std::endl;
    udp_socket.Close();

    return 0;
}

const char *Echoz::HostToStr(unsigned int host) {
    struct in_addr in{};
    in.s_addr = host;

    return inet_ntoa(in);
}
