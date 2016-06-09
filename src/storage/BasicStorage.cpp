#include <string>

#include "BasicStorage.h"
#include "Result.h"

bool BasicStorage::set(std::string key, std::string value) {
    this->data.insert({key, value});

    return true;
}

bool BasicStorage::del(std::string key) {
    auto value = this->data.find(key);

    if (value != this->data.end()) {
        this->data.erase(value);

        return true;
    }

    return false;
}

Result BasicStorage::get(std::string key) {
    auto value = this->data.find(key);

    if (value != this->data.end()) {
        Result result(value->second);

        return result;
    }

    Result result;

    return result; 
}
