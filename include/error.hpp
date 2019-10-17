//
// Created by jwW on 2019-10-15.
//

#ifndef ZED_NET_ERROR_HPP
#define ZED_NET_ERROR_HPP


#include <string>

class Error {
public:
    static Error& instance() {
        static Error instance;
        return instance;
    }

    inline std::string GetMessage() { return this->message_; };
    inline void SetMessage(const std::string& message) { this->message_ = message; };

private:
    Error() = default;
    ~Error() = default;

    std::string message_;
};


#endif //ZED_NET_ERROR_HPP
