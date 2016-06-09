#pragma once

#include <string>

class RequestHandler {
    public:
        virtual std::string handle(std::string input) = 0;
};
