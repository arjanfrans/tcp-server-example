#include <memory>
#include <boost/asio.hpp>

#include "Session.h"

using boost::asio::ip::tcp;

Session::Session (tcp::socket socket) : socket_(std::move(socket)) {}

void Session::start () {
    this->read();
}

void Session::read () {
    auto self(this->shared_from_this());

    socket_.async_read_some(boost::asio::buffer(data_, max_length), [this, self](boost::system::error_code ec, std::size_t length) {
        if (!ec) {
            this->write(length);
        }
    });
}

void Session::write (std::size_t length) {
    auto self(this->shared_from_this());

    boost::asio::async_write(this->socket_, boost::asio::buffer(this->data_, length), [this, self](boost::system::error_code ec, std::size_t length) {
        if (!ec) {
            this->read();
        }
    });
}
