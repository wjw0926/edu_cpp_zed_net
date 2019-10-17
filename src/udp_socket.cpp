//
// Created by jwW on 2019-10-15.
//

#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>

#include "udp_socket.hpp"
#include "error.hpp"

void UDPSocket::Open(unsigned int port, int non_blocking) {
    // Create the socket
    this->SetSockfd(socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP));
    if (this->GetSockfd() <= 0) {
        UDPSocket::Close();
        Error::instance().SetMessage("Failed to create socket");
    }

    // Bind the socket to the port
    struct sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(this->GetSockfd(), (const struct sockaddr *) &address, sizeof(struct sockaddr_in)) != 0) {
        UDPSocket::Close();
        Error::instance().SetMessage("Failed to bind socket");
    }

    // Set the socket to non-blocking if necessary
    if (non_blocking) {
        if (fcntl(this->GetSockfd(), F_SETFL, O_NONBLOCK, non_blocking) != 0) {
            UDPSocket::Close();
            Error::instance().SetMessage("Failed to set socket to non-blocking");
        }
    }
}

void UDPSocket::Close() {
    if (this->GetSockfd() <= 0) {
        return;
    } else {
        close(this->GetSockfd());
    }
}

int UDPSocket::Send(InternetAddress destination, const void *data, int size) {
    if (this->GetSockfd() <= 0) {
        Error::instance().SetMessage("Socket is NULL");
        return -1;
    }

    struct sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = destination.GetHost();
    address.sin_port = htons(destination.GetPort());

    int sent_bytes = sendto(this->GetSockfd(), (const char *) data, size, 0, (const struct sockaddr *) &address, sizeof(struct sockaddr_in));
    if (sent_bytes != size) {
        Error::instance().SetMessage("Failed to send data");
        return -1;
    }

    return 0;
}

int UDPSocket::Receive(InternetAddress *sender, void *data, int size) {
    if (this->GetSockfd() <= 0) {
        Error::instance().SetMessage("Socket is NULL");
        return -1;
    }

    struct sockaddr_in from{};
    socklen_t from_length = sizeof(from);

    int received_bytes = recvfrom(this->GetSockfd(), (char *) data, size, 0, (struct sockaddr *) &from, &from_length);
    if (received_bytes <= 0) {
        return 0;
    }

    sender->SetHost(from.sin_addr.s_addr);
    sender->SetPort(ntohs(from.sin_port));

    return received_bytes;
}
