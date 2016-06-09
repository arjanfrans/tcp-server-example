#pragma once

#include <string>

class Result {
    public:
        Result();
        Result(std::string value);

        std::string getValue();
        bool isFound();

    private:
        std::string value;
        bool found;
};
