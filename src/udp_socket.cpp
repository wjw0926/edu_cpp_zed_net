//
// Created by jwW on 2019-10-15.
//

#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>

#include "udp_socket.hpp"
#include "error.hpp"

Error UDPSocket::Open(unsigned int port, bool is_non_blocking) {
    // Create the socket
    SetSockfd(socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP));
    if (GetSockfd() <= 0) {
        return Error{ErrorCode::CreateSocket, "Failed to create socket"};
    }

    // Bind the socket to the port
    struct sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(GetSockfd(), (const struct sockaddr *) &address, sizeof(struct sockaddr_in)) != 0) {
        Close();
        return Error{ErrorCode::BindSocket, "Failed to bind socket"};
    }

    // Set the socket to non-blocking if necessary
    if (is_non_blocking) {
        if (fcntl(GetSockfd(), F_SETFL, O_NONBLOCK, is_non_blocking) != 0) {
            Close();
            return Error{ErrorCode::SetNonBlocking, "Failed to set socket to non-blocking"};
        }
    }
    return Error{ErrorCode::Success, "Success"};
}

Error UDPSocket::Close() {
    if (GetSockfd() <= 0) {
        return Error{ErrorCode::InvalidSocket, "Socket is not exist"};
    } else {
        close(GetSockfd());
        return Error{ErrorCode::Success, "Success"};
    }
}

Error UDPSocket::Send(InternetAddress destination, const void *data, int size) {
    struct sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = destination.GetHost();
    address.sin_port = htons(destination.GetPort());

    int sent_bytes = sendto(GetSockfd(), (const char *) data, size, 0, (const struct sockaddr *) &address, sizeof(struct sockaddr_in));
    if (sent_bytes != size) {
        return Error{ErrorCode::SendData, "Failed to send data"};
    }

    return Error{ErrorCode::Success, "Success"};
}

int UDPSocket::Receive(InternetAddress *sender, void *data, int size) {
    struct sockaddr_in from{};
    socklen_t from_length = sizeof(from);

    int received_bytes = recvfrom(GetSockfd(), (char *) data, size, 0, (struct sockaddr *) &from, &from_length);
    if (received_bytes <= 0) {
        return 0;
    }

    sender->SetHost(from.sin_addr.s_addr);
    sender->SetPort(ntohs(from.sin_port));

    return received_bytes;
}

Error UDPSocket::Check() {
    if (GetSockfd() <= 0) {
        return Error{ErrorCode::InvalidSocket, "Socket is not exist"};
    } else {
        return Error{ErrorCode::Success, "Success"};
    }
}
