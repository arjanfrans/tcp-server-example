#pragma once

#include <boost/asio.hpp>
#include <memory>

#include "RequestHandler.h"

using boost::asio::ip::tcp;

class Server {

    public:
        Server(short port, const std::shared_ptr<RequestHandler> requestHandler);

        void run();

    private:
        void accept();
        std::shared_ptr<RequestHandler> requestHandler;

        boost::asio::io_service ioService;
        tcp::acceptor acceptor;
        tcp::socket socket;
};
