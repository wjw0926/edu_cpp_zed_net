//
// Created by jwW on 2019-10-15.
//

#pragma once

#include <string>

namespace cppzednet {
    enum class ErrorCode {
        Success = 0,
        CreateSocket = 1,
        BindSocket = 2,
        SetNonBlocking = 3,
        InvalidSocket = 4,
        InvalidHost = 5,
        SendData = 6
    };

    struct Error {
        ErrorCode code;
        std::string message;
    };
}
