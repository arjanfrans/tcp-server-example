#include <boost/asio.hpp>
#include <memory>

#include "Server.h"
#include "Session.h"
#include "RequestHandler.h"

using boost::asio::ip::tcp;

Server::Server(short port, const std::shared_ptr<RequestHandler> requestHandler)
    : acceptor{this->ioService, tcp::endpoint(tcp::v4(), port)}, socket{this->ioService}, requestHandler{requestHandler} {
    this->accept();
}

void Server::run() {
    this->ioService.run();
}

void Server::accept() {
    this->acceptor.async_accept(this->socket, [this](boost::system::error_code ec) {
        if (!ec) {
            std::make_shared<Session>(std::move(this->socket), this->requestHandler)->start();
        }

        this->accept();
    });
}
