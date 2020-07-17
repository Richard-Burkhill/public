#include "tcp_server.hpp"
#include "bespoke_connection.hpp"

#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>

#include <string>
#include <iostream>

int main ()
{
   boost::asio::io_context input_output_service;
   input_output_service.run();
   boost::shared_ptr <bespoke_connection> test_connection =
      boost::shared_ptr <bespoke_connection> (new bespoke_connection(input_output_service));

   test_connection->socket();

   boost::shared_ptr <tcp_server> test_server = 
      boost::shared_ptr <tcp_server> (
         new tcp_server (input_output_service, 54321, test_connection->create(input_output_service))
      );



   std::string received_message;
   //size_t amount_read = 0;
   while (received_message == "") {
       test_server->read(test_connection, received_message);
       //std::cout << "Amount read is: " << amount_read << std::endl;
       boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
   }

       

   //test_server->write(test_connection, "Hello world!");

   std::string key_press;
   std::cout << "Press any key" << std::endl;
   std::cin >> key_press;
}
