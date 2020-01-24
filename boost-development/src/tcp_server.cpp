#include "tcp_server.hpp"
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>

tcp_server::tcp_server(boost::asio::io_service& io_service, unsigned int port, boost::shared_ptr<tcp_connection> new_connection)
    : acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
   boost::asio::socket_base::reuse_address option(true);
   std::cout << "setting option" << std::endl;
   acceptor_.set_option(option);
   std::cout << "do the acception" << std::endl;
   start_accept(new_connection);
}

void tcp_server::start_accept(boost::shared_ptr<tcp_connection> new_connection_ptr)
{
   std::cout << "Used shared_from_this()" << std::endl;

   m_new_connection_ptr = new_connection_ptr;
   std::cout << "member pointer for new connection" << std::endl;
   acceptor_.async_accept(new_connection_ptr->socket(),
      [this](boost::system::error_code ec)
      {
        std::cout << "In accept lambda function" << std::endl;
        if (!ec)
        {
           m_new_connection_ptr->start();
        }

        start_accept(m_new_connection_ptr->create(acceptor_.get_io_service()));
      }
   );
}
