#include <memory>
#include <string>
#include <regex>

#include "CommandHandler.h"
#include "storage/Storage.h"

CommandHandler::CommandHandler(std::unique_ptr<Storage> storage)
    : storage{std::move(storage)} {}

std::string CommandHandler::handle(std::string input) {
    std::regex setRegex("^(SET)\\s+\"(.*?)\"\\s+\"(.*?)\"$");
    std::regex getRegex("^(GET)\\s+\"(.*?)\"$");
    std::regex delRegex("^(DEL)\\s+\"(.*?)\"$");
    std::smatch matches;

    if (std::regex_match(input, matches, setRegex)) {
        auto command = matches[1].str();
        auto key = matches[2].str();
        auto value = matches[3].str();

        auto set = this->storage->set(key, value);

        if (set) {
            return std::string("INSERTED");
        }

        return std::string("FAILED_INSERT");
    } else if (std::regex_match(input, matches, getRegex)) {
        auto command = matches[1].str();
        auto key = matches[2].str();

        auto result = this->storage->get(key);

        if (result.isFound()) {
            return result.getValue();
        }

        return std::string("NOT_FOUND");
    } else if (std::regex_match(input, matches, delRegex)) {
        auto command = matches[1].str();
        auto key = matches[2].str();
        auto value = matches[3].str();

        auto deleted = this->storage->del(key);

        if (deleted) {
            return std::string("DELETED");
        }

        return std::string("FAILED_DELETE");
    } else {
        return std::string("INVALID_INPUT");
    }
} 
