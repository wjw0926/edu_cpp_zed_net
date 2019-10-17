//
// Created by jwW on 2019-10-15.
//

#pragma once

#include <netdb.h>
#include "error.hpp"

class InternetAddress {
public:
    InternetAddress() = default;
    ~InternetAddress() = default;

    unsigned int GetHost() { return host_; };
    unsigned short GetPort() { return port_; };

    void SetHost(unsigned int host) { host_ = host; };
    void SetPort(unsigned short port) { port_ = port; };

    bool SetHost(const char *host) {
        if (host == nullptr) {
            SetHost(INADDR_ANY);
            return true;
        } else {
            SetHost(inet_addr(host));

            if (GetHost() == INADDR_NONE) {
                struct hostent *hostent = gethostbyname(host);

                if (hostent) {
                    SetHost(hostent->h_addr);
                    return true;
                } else {
                    Error::instance().SetMessage("Invalid host name");
                    return false;
                }
            }
        }
        return true;
    };

private:
    unsigned int host_ = 0;
    unsigned short port_ = 0;
};
