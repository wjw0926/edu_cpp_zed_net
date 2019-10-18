//
// Created by jwW on 2019-10-15.
//

#pragma once

#include <netdb.h>
#include <arpa/inet.h>
#include "error.hpp"

namespace cppzednet {
    class InternetAddress {
    public:
        InternetAddress() = default;

        ~InternetAddress() = default;

        unsigned int GetHost() { return host_; };

        unsigned short GetPort() { return port_; };

        void SetHost(unsigned int host) { host_ = host; };

        void SetPort(unsigned short port) { port_ = port; };

        Error SetHost(const char *host) {
            if (host == nullptr) {
                SetHost(INADDR_ANY);
            } else {
                SetHost(inet_addr(host));

                if (GetHost() == INADDR_NONE) {
                    struct hostent *hostent = gethostbyname(host);

                    if (hostent) {
                        SetHost(hostent->h_addr);
                    } else {
                        return Error{ErrorCode::InvalidHost, "Invalid host name"};
                    }
                }
            }

            return Error{ErrorCode::Success, "Success"};
        };

    private:
        unsigned int host_ = 0;
        unsigned short port_ = 0;
    };
}
