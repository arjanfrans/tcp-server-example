#pragma once

#include <boost/asio.hpp>
#include <string>
#include <memory>

#include "RequestHandler.h"

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
    public:
        Session(tcp::socket socket, const std::shared_ptr<RequestHandler> requestHandler);

        void start();

    private:
        void read();
        void write(std::string output);
        void handleRead(const boost::system::error_code &ec, std::size_t size); 
        std::shared_ptr<RequestHandler> requestHandler;

        boost::asio::streambuf inputBuffer;

        tcp::socket socket;
        enum { max_length = 1024 };
        char dataBuffer[max_length];
};
