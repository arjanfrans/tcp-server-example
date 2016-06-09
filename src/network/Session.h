#pragma once

#include <memory>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
    public:
        Session (tcp::socket socket);

        void start ();

    private:
        void read ();
        void write (std::size_t length);

        tcp::socket socket_;
        enum { max_length = 1024 };
        char data_[max_length];
};
