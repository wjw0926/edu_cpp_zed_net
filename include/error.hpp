//
// Created by jwW on 2019-10-15.
//

#pragma once

#include <string>

class Error {
public:
    static Error& instance() {
        static Error instance;
        return instance;
    }

    std::string GetMessage() { return message_; };
    void SetMessage(const std::string& message) { message_ = message; };

private:
    Error() = default;
    ~Error() = default;

    std::string message_;
};
