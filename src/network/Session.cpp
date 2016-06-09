#include <cstdlib>
#include <memory>
#include <boost/asio.hpp>
#include <string>

#include "Session.h"
#include "RequestHandler.h"

using boost::asio::ip::tcp;

Session::Session (tcp::socket socket, const std::shared_ptr<RequestHandler> requestHandler)
    : requestHandler{requestHandler}, socket{std::move(socket)} {}

void Session::start () {
    this->read();
}

void Session::read () {
    auto self(this->shared_from_this());

    this->socket.async_read_some(boost::asio::buffer(this->dataBuffer, max_length), [this, self](boost::system::error_code ec, std::size_t) {
        if (!ec) {
            auto input = std::string(this->dataBuffer);
            auto response = this->requestHandler->handle(input);

            this->write(response);
            this->dataBuffer[max_length] = '\0';
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
