#pragma once

#include <string>
#include <memory>
#include "network/RequestHandler.h"
#include "storage/Storage.h"

class CommandHandler : public RequestHandler {

    public:
        CommandHandler(std::unique_ptr<Storage> storage);
        std::string handle(std::string input) override;

    private:
        std::unique_ptr<Storage> storage;
};
