#include "tcp_connection.hpp"

#include <iostream>

#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>

tcp_connection::tcp_connection(boost::asio::io_service& io_service)
    : socket_(io_service)
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
   socket_.async_read_some
      (boost::asio::buffer(received_message),
         [this, self](boost::system::error_code ec, std::size_t length) -> int
         {
            if (!ec)
            {
               return length;
            }
            else
            {
               return -1;
            }
         }
      );
}

int tcp_connection::write(std::vector<char>& message)
{
    boost::shared_ptr<tcp_connection> self(shared_from_this());

    boost::asio::async_write
       (socket_, boost::asio::buffer(message),
          [this, self](boost::system::error_code ec, std::size_t length) -> int
          {
             if (!ec)
             {
                return 0;
             }
             else
             {
                return -1;
             }
          }
       );
}

boost::shared_ptr<tcp_connection> tcp_connection::create(boost::asio::io_service& io_service)
{
   return boost::shared_ptr<tcp_connection>(new tcp_connection(io_service));
}

boost::shared_ptr<tcp_connection> tcp_connection::create(tcp::socket socket)
{
   return boost::shared_ptr<tcp_connection>(new tcp_connection(std::move(socket)));
}

tcp::socket& tcp_connection::socket(void)
{
   return socket_;
}
