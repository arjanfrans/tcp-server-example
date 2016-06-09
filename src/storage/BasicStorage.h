#pragma once

#include <string>
#include <map>

#include "Storage.h"
#include "Result.h"

struct StringComparator
{
    bool operator()(std::string a, std::string b) {
        return a.compare(b) == 0;
    }
};

class BasicStorage : public Storage {
    public:
        Result get(std::string key) override;
        bool set(std::string key, std::string value) override;
        bool del(std::string key) override;

    private:
        std::map<std::string, std::string, StringComparator> data;
};
