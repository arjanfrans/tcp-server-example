#include "network/Server.h"
#include <cstdlib>
#include <iostream>
#include <memory>

#include "CommandHandler.h"
#include "storage/BasicStorage.h"

#define  ELPP_NO_DEFAULT_LOG_FILE

#include "logger.h"

INITIALIZE_LOGGER

int main(int argc, char *argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: async_tcp_echo_server <port>\n";

            return 1;
        }

        auto storage = std::make_unique<BasicStorage>();
        auto commandHandler = std::make_shared<CommandHandler>(std::move(storage));

        Server server(std::atoi(argv[1]), commandHandler);

        server.run();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
