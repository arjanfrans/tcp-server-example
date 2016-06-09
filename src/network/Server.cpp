#include <memory>
#include <boost/asio.hpp>

#include "Server.h"
#include "Session.h"

using boost::asio::ip::tcp;

Server::Server (short port) : acceptor(this->ioService, tcp::endpoint(tcp::v4(), port)), socket(this->ioService) {
    this->accept();
}

void Server::run () {
    this->ioService.run();
}

void Server::accept () {
    this->acceptor.async_accept(this->socket, [this](boost::system::error_code ec) {
        if (!ec) {
            std::make_shared<Session>(std::move(this->socket))->start();
        }

        this->accept();
    });
}
