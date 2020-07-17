#include "bespoke_connection.hpp"
#include <iostream>

void bespoke_connection::start()
{
   std::cout << "starting bespoke_connection" << std::endl;
   std::vector<char> received_message;
   read (received_message);
}

boost::shared_ptr<tcp_connection> bespoke_connection::create(boost::asio::io_context& io_context)
{
   std::cout << "creating bespoke connection" << std::endl;
   return boost::shared_ptr<tcp_connection> (reinterpret_cast <tcp_connection*> (new bespoke_connection(io_context)));
}

boost::shared_ptr<tcp_connection> bespoke_connection::create(tcp::socket socket)
{
   return boost::shared_ptr<tcp_connection>(reinterpret_cast <tcp_connection*> (new bespoke_connection(std::move(socket))));
}
