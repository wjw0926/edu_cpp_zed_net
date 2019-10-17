//
// Created by jwW on 2019-10-15.
//

#pragma once

class InternetAddress {
public:
    InternetAddress() = default;
    ~InternetAddress() = default;

    unsigned int GetHost() { return host_; };
    unsigned short GetPort() { return port_; };

    void SetHost(unsigned int host) { host_ = host; };
    void SetPort(unsigned short port) { port_ = port; };

    bool SetHost(const char *host);

private:
    unsigned int host_ = 0;
    unsigned short port_ = 0;
};
