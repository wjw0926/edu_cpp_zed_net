//
// Created by jwW on 2019-10-15.
//

#include <netdb.h>
#include <arpa/inet.h>

#include "internet_address.hpp"
#include "error.hpp"

bool InternetAddress::SetHost(const char *host) {
    if (host == nullptr) {
        this->SetHost(INADDR_ANY);
        return true;
    } else {
        this->SetHost(inet_addr(host));
        if (this->GetHost() == INADDR_NONE) {
            struct hostent *hostent = gethostbyname(host);
            if (hostent) {
                this->SetHost(hostent->h_addr);
                return true;
            } else {
                Error::instance().SetMessage("Invalid host name");
                return false;
            }
        }
    }
    return true;
}
