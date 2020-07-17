#ifndef BOOST_DEV_TCP_CONNECTION
#define BOOST_DEV_TCP_CONNECTION

#include <string>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
{
public:
  tcp_connection(boost::asio::io_service& io_service);
  tcp_connection(tcp::socket socket);

  virtual void start();
  int read(std::vector<char>& received_message);
  int write(std::vector<char>& message);

  virtual boost::shared_ptr<tcp_connection> create(boost::asio::io_service& io_service);
  virtual boost::shared_ptr<tcp_connection> create(tcp::socket);
  tcp::socket& socket(void);

private:
  tcp::socket socket_;
};

#endif
