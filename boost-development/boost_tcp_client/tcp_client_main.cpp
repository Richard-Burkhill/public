#include "tcp_client.hpp"
#include <boost/shared_ptr.hpp>

#include <string>
#include <iostream>

int main ()
{
   boost::asio::io_context input_output_service;
   input_output_service.run();
   boost::shared_ptr <tcp_client> test_client = 
      boost::shared_ptr <tcp_client> (new tcp_client (input_output_service, "127.0.0.1", "54321"));

   test_client->write("Hello world with bells on it");

   std::cout << "Please type a message to send" << std::endl;
   std::string message;
   std::cin >> message;
   //test_client->read (message);

   std::cin >> message;
}
