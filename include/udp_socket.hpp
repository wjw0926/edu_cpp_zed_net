//
// Created by jwW on 2019-10-15.
//

#ifndef ZED_NET_UDP_SOCKET_HPP
#define ZED_NET_UDP_SOCKET_HPP

#include "internet_address.hpp"


class UDPSocket {
public:
    UDPSocket() = default;
    ~UDPSocket() = default;

    inline int GetSockfd() { return this->sockfd_; };
    inline void SetSockfd(int sockfd) { this->sockfd_ = sockfd; };

    // Opens a UDP socket and binds it to a specified port
    // (use 0 to select a random open port)
    // Socket will not block if 'non-blocking' is non-zero
    void Open(unsigned int port, int non_blocking);

    // Closes a previously opened socket
    void Close();

    // Sends a specific amount of data to 'destination'
    // Returns 0 on success, -1 otherwise (call 'Error::instance().GetMessage' for more info)
    int Send(InternetAddress destination, const void *data, int size);

    // Receives a specific amount of data from 'sender'
    // Returns the number of bytes received, -1 otherwise (call 'Error::instance().GetMessage' for more info)
    int Receive(InternetAddress *sender, void *data, int size);

private:
    int sockfd_ = 0;
};


#endif //ZED_NET_UDP_SOCKET_HPP
