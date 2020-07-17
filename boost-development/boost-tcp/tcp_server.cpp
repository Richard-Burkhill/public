#include "tcp_server.hpp"
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>

tcp_server::tcp_server(boost::asio::io_context& io_context, unsigned int port, boost::shared_ptr<tcp_connection> new_connection)
    : acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
   boost::asio::socket_base::reuse_address option(true);
   std::cout << "setting option" << std::endl;
   acceptor_.set_option(option);
   std::cout << "do the accepting" << std::endl;
   start_accept(new_connection);
}

void tcp_server::start_accept(boost::shared_ptr<tcp_connection> new_connection_ptr)
{
   m_new_connection_ptr = new_connection_ptr;
   std::cout << "Waiting for connection" << std::endl;
   acceptor_.accept(new_connection_ptr->socket());
   std::cout << "Accpeted connection" << std::endl;
   m_new_connection_ptr->start();
}

void tcp_server::write(boost::shared_ptr<tcp_connection> new_connection_ptr, void* data, size_t data_length)
{
    boost::asio::write(new_connection_ptr->socket(), boost::asio::buffer(data, data_length));
}

void tcp_server::write(boost::shared_ptr<tcp_connection> new_connection_ptr, std::string message)
{
    boost::asio::write(new_connection_ptr->socket(), boost::asio::buffer(message));
}

void tcp_server::read(boost::shared_ptr<tcp_connection> new_connection_ptr, std::vector<unsigned char>& received_data)
{
    boost::asio::async_read(new_connection_ptr->socket(), boost::asio::buffer(received_data),
        boost::bind(&tcp_server::handle_read, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void tcp_server::read(boost::shared_ptr<tcp_connection> new_connection_ptr, std::string& received_message)
{
    boost::asio::read_until(new_connection_ptr->socket(), new_connection_ptr->response_, 'o');
    //std::istream is(&new_connection_ptr->response_);
    //std::getline(is, received_message);
}

void tcp_server::read(boost::shared_ptr<tcp_connection> new_connection_ptr, std::vector<char>& received_message)
{
    std::string msg;
    read(new_connection_ptr, msg);
    std::copy(msg.begin(), msg.end(), std::back_inserter(received_message));
}

void tcp_server::handle_read(const boost::system::error_code& error, size_t bytes_transferred)
{
    std::cout << "handling client read" << std::endl;
}