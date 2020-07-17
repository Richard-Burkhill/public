#ifndef BOOST_DEV_TCP_CLIENT
#define BOOST_DEV_TCP_CLIENT

#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

class tcp_client : public boost::enable_shared_from_this<tcp_client>
{
public:
  tcp_client() = delete;
  tcp_client(const tcp_client&) = delete;
  tcp_client(tcp_client&&) = default;
  tcp_client& operator=(const tcp_client&) = delete;
  tcp_client& operator=(tcp_client&&) = default;

  tcp_client(boost::asio::io_service& io_service, std::string host, std::string port);

  boost::asio::ip::tcp::socket& socket();

  void write(void* data, size_t data_length);

  void write(std::string message);

  void read(std::vector<unsigned char>& received_data);
  void read(std::vector<char>& received_message);

private:

  void handle_write(const boost::system::error_code& error, size_t bytes_transferred);
  void handle_read(const boost::system::error_code& error, size_t bytes_transferred);

  boost::asio::ip::tcp::socket socket_;

};

#endif
