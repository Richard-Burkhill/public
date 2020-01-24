#include "tcp_server.hpp"
#include "bespoke_connection.hpp"

#include <boost/shared_ptr.hpp>

#include <string>
#include <iostream>

int main ()
{
   boost::asio::io_service input_output_service;

   boost::shared_ptr <bespoke_connection> test_connection =
      boost::shared_ptr <bespoke_connection> (new bespoke_connection(input_output_service));

   test_connection->socket();

   boost::shared_ptr <tcp_server> test_server = 
      boost::shared_ptr <tcp_server> (
         new tcp_server (input_output_service, 54321, test_connection->create(input_output_service))
      );

   input_output_service.run();

   std::string key_press;
   std::cout << "Press any key" << std::endl;
   std::cin >> key_press;
}
