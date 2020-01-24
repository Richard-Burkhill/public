#ifndef BOOST_DEV_BESPOKE_CONNECTION
#define BOOST_DEV_BESPOKE_CONNECTION

#include "tcp_connection.hpp"
#include <boost/shared_ptr.hpp>

class bespoke_connection : public tcp_connection 
{
public:
   using tcp_connection::tcp_connection;
   void start();

   boost::shared_ptr<tcp_connection> create(boost::asio::io_service& io_service);
   boost::shared_ptr<tcp_connection> create(tcp::socket);
};

#endif
