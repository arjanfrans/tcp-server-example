#pragma once

#include <memory>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Server {
    public:
        Server(short port);

        void run ();

    private:
        void accept ();

        boost::asio::io_service ioService;
        tcp::acceptor acceptor;
        tcp::socket socket;
};

