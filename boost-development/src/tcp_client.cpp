#include "tcp_client.hpp"

#include <iostream>

#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/connect.hpp>

tcp_client::tcp_client(boost::asio::io_service& io_service, std::string host, std::string port)
   : socket_(io_service)
{
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(), host, port);
    boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

    std::cout << "About to connect" << std::endl;
    boost::asio::connect(socket_, iterator);
    std::cout << "Connected" << std::endl;
    //std::vector<char> receieved_msg;
    //read(receieved_msg);
    //std::string str(receieved_msg.begin(),receieved_msg.end());
    //std::cout << str << std::endl;
}

boost::asio::ip::tcp::socket& tcp_client::socket()
{
   return socket_;
}

void tcp_client::write(void* data, size_t data_length)
{
   boost::asio::async_write(socket_, boost::asio::buffer(data, data_length),
      boost::bind(&tcp_client::handle_write, shared_from_this(),
      boost::asio::placeholders::error,
      boost::asio::placeholders::bytes_transferred));
}

void tcp_client::write(std::string message)
{
   boost::asio::async_write(socket_, boost::asio::buffer(message),
      boost::bind(&tcp_client::handle_write, shared_from_this(),
      boost::asio::placeholders::error,
      boost::asio::placeholders::bytes_transferred));
}

void tcp_client::read(std::vector<unsigned char>& received_data)
{
   boost::asio::async_read(socket_, boost::asio::buffer(received_data),
      boost::bind(&tcp_client::handle_read, shared_from_this(),
      boost::asio::placeholders::error,
      boost::asio::placeholders::bytes_transferred));
}

void tcp_client::read(std::vector<char>& received_message)
{
   boost::asio::async_read(socket_, boost::asio::buffer(received_message),
      boost::bind(&tcp_client::handle_read, shared_from_this(),
      boost::asio::placeholders::error,
      boost::asio::placeholders::bytes_transferred));
}

void tcp_client::handle_write(const boost::system::error_code& error, size_t bytes_transferred)
{
}

void tcp_client::handle_read(const boost::system::error_code& error, size_t bytes_transferred)
{
   std::cout << "handling client read" << std::endl;
}
