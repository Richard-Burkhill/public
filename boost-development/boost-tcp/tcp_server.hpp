#ifndef BOOST_DEV_TCP_SERVER
#define BOOST_DEV_TCP_SERVER

#include "tcp_connection.hpp"
#include <iostream>

#include <boost/asio/ip/tcp.hpp>

class tcp_server : public boost::enable_shared_from_this<tcp_server>
{
public:
  tcp_server() = delete;
  tcp_server(const tcp_server&) = delete;
  tcp_server(tcp_server&&) = default;

  tcp_server& operator=(const tcp_server&) = delete;
  tcp_server& operator=(tcp_server&&) = default;

  tcp_server(boost::asio::io_context& io_context, unsigned int port, boost::shared_ptr<tcp_connection> new_connection);

  void write(boost::shared_ptr<tcp_connection> new_connection_ptr, void* data, size_t data_length);

  void write(boost::shared_ptr<tcp_connection> new_connection_ptr, std::string message);

  void read(boost::shared_ptr<tcp_connection> new_connection_ptr, std::string& received_message);
  void read(boost::shared_ptr<tcp_connection> new_connection_ptr, std::vector<unsigned char>& received_data);
  void read(boost::shared_ptr<tcp_connection> new_connection_ptr, std::vector<char>& received_message);

protected:

  void start_accept(boost::shared_ptr<tcp_connection> new_connection_ptr);
  void handle_accept();
  void handle_read(const boost::system::error_code& error, size_t bytes_transferred);

  boost::asio::ip::tcp::acceptor acceptor_;
  boost::shared_ptr<tcp_connection> m_new_connection_ptr;
};

#endif
