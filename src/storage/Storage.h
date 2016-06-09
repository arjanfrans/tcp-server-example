#pragma once

#include <string>
#include "Result.h"

class Storage {
    public:
        virtual Result get(std::string key) = 0;
        virtual bool set(std::string key, std::string value) = 0;
        virtual bool del(std::string key) = 0;
};
