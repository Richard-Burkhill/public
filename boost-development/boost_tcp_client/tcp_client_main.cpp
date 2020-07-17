#include "tcp_client.hpp"
#include <boost/shared_ptr.hpp>

#include <string>
#include <iostream>

int main ()
{
   boost::asio::io_service input_output_service;

   boost::shared_ptr <tcp_client> test_client = 
      boost::shared_ptr <tcp_client> (
         new tcp_client (input_output_service, "192.168.1.18", "54321")
      );
   input_output_service.run();

   std::cout << "Please type a message to send" << std::endl;
   std::string message;
   std::cin >> message;
   test_client->write (message);

   std::cin >> message;
}
