#include <cstdlib>
#include <memory>
#include <boost/asio.hpp>
#include <string>

#include "Session.h"
#include "RequestHandler.h"
#include "../logger.h"

using boost::asio::ip::tcp;

Session::Session (tcp::socket socket, const std::shared_ptr<RequestHandler> requestHandler)
    : requestHandler{requestHandler}, socket{std::move(socket)} {}

void Session::start () {
    this->read();
}

void Session::read () {
    auto self(this->shared_from_this());

    boost::asio::async_read_until(this->socket, this->inputBuffer, '\n', [this, self](boost::system::error_code ec, std::size_t) {
        if (!ec) {
            std::istream inputStream(&this->inputBuffer);
            std::string input;
            std::getline(inputStream, input);

            auto response = this->requestHandler->handle(input);

            LOG(INFO) << "res: " + response;
            this->write(response + "\n");
        } else {
            LOG(INFO) << "error: " + ec.message();
        }
    });
}

void Session::write (std::string output) {
    auto self(this->shared_from_this());

    boost::asio::async_write(this->socket, boost::asio::buffer(output, output.size()), [this, self](boost::system::error_code ec, std::size_t) {
        if (!ec) {
            this->read();
        }
    });
}
