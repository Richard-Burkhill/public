#ifndef BOOST_DEV_TCP_SERVER
#define BOOST_DEV_TCP_SERVER

#include "tcp_connection.hpp"
#include <iostream>

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

class tcp_server : public boost::enable_shared_from_this<tcp_server>
{
public:
  tcp_server() = delete;
  tcp_server(const tcp_server&) = delete;
  tcp_server(tcp_server&&) = default;

  tcp_server& operator=(const tcp_server&) = delete;
  tcp_server& operator=(tcp_server&&) = default;

  tcp_server(boost::asio::io_service& io_service, unsigned int port, boost::shared_ptr<tcp_connection> new_connection);

protected:

  void start_accept(boost::shared_ptr<tcp_connection> new_connection_ptr);
  void handle_accept();

  boost::asio::ip::tcp::acceptor acceptor_;
  boost::shared_ptr<tcp_connection> m_new_connection_ptr;
};

#endif
