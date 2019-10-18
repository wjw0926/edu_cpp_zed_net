//
// Created by jwW on 2019-10-15.
//

#pragma once

#include "internet_address.hpp"

namespace cppzednet {
    class UDPSocket {
    public:
        UDPSocket() = default;

        ~UDPSocket() = default;

        int GetSockfd() { return sockfd_; };

        void SetSockfd(int sockfd) { sockfd_ = sockfd; };

        // Opens a UDP socket and binds it to a specified port
        // (use 0 to select a random open port)
        // Socket will not block if 'is_non_blocking' is true
        Error Open(unsigned int port, bool is_non_blocking);

        // Closes a previously opened socket
        Error Close();

        // Sends a specific amount of data to 'destination'
        Error Send(InternetAddress destination, const char *data, int size);

        // Receives a specific amount of data from 'sender'
        // Returns the number of bytes received, -1 otherwise
        int Receive(InternetAddress *sender, char *data, int size);

        // Check socket is available or not
        Error Check();

    private:
        int sockfd_ = 0;
    };
}
