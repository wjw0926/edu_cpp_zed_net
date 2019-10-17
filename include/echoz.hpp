//
// Created by jwW on 2019-10-15.
//

#ifndef ZED_NET_ECHOZ_HPP
#define ZED_NET_ECHOZ_HPP


class Echoz {
public:
    Echoz() = default;
    ~Echoz() = default;

    static int RunServer(unsigned short port);
    static int RunClient(const char *host, unsigned short port);

    // Converts an address's host name into a decimal formatted string
    // Returns NULL on failure (call 'Error::instance().GetMessage' for more info)
    static const char *HostToStr(unsigned int host);
};


#endif //ZED_NET_ECHOZ_HPP
