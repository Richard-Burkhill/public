#include "tcp_connection.hpp"

#include <iostream>

#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>

tcp_connection::tcp_connection(boost::asio::io_context& io_context)
    : socket_(io_context)
{
}

tcp_connection::tcp_connection(tcp::socket socket)
    : socket_(std::move(socket))
{
}

void tcp_connection::start()
{
   std::cout << "started the tcp_connection" << std::endl;
}

int tcp_connection::read(std::vector<char>& received_message)
{
   boost::shared_ptr<tcp_connection> self(shared_from_this());
   return socket_.read_some(boost::asio::buffer(received_message));
}

int tcp_connection::write(std::vector<char>& message)
{
    boost::shared_ptr<tcp_connection> self(shared_from_this());

    return boost::asio::write (socket_, boost::asio::buffer(message));
}

boost::shared_ptr<tcp_connection> tcp_connection::create(boost::asio::io_context& io_context)
{
   return boost::shared_ptr<tcp_connection>(new tcp_connection(io_context));
}

boost::shared_ptr<tcp_connection> tcp_connection::create(tcp::socket socket)
{
   return boost::shared_ptr<tcp_connection>(new tcp_connection(std::move(socket)));
}

tcp::socket& tcp_connection::socket(void)
{
   return socket_;
}
