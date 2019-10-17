//
// Created by jwW on 2019-10-15.
//

#ifndef ZED_NET_INTERNET_ADDRESS_HPP
#define ZED_NET_INTERNET_ADDRESS_HPP


class InternetAddress {
public:
    InternetAddress() = default;
    ~InternetAddress() = default;

    inline unsigned int GetHost() { return this->host_; };
    inline unsigned short GetPort() { return this->port_; };

    inline void SetHost(unsigned int host) { this->host_ = host; };
    inline void SetPort(unsigned short port) { this->port_ = port; };

    bool SetHost(const char *host);

private:
    unsigned int host_ = 0;
    unsigned short port_ = 0;
};


#endif //ZED_NET_INTERNET_ADDRESS_HPP
