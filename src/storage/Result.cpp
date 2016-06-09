#include <string>
#include "Result.h"

Result::Result() : found{false} {}

Result::Result(std::string value) : value{value}, found{true} {}

std::string Result::getValue() {
    return this->value;
}

bool Result::isFound () {
    return this->found;
}
