#include "network_communication-as_a_task.h"

int main() {
    tasks_processor::run_delayed(boost::posix_time::seconds(1), &send_auth);
    tasks_processor::add_listener(g_port_num, &authorizer::on_connection_accpet);
    assert(!g_authed);

    tasks_processor::start();
    assert(g_authed);
}
// Big part of code for this recipe
// in in this header:

bool g_authed = false;

void process_server_response(
        connection_ptr&& soc,
        const boost::system::error_code& err)
{
    if (err && err != boost::asio::error::eof) {
        std::cerr << "Client error on receive: " << err.message() << '\n';
        assert(false);
    }

    if (soc->data.size() != 2) {
        std::cerr << "Wrong bytes count\n";
        assert(false);
    }

    if (soc->data != "OK") {
        std::cerr << "Wrong response: " << soc->data << '\n';
        assert(false);
    }

    g_authed = true;
    soc->shutdown();
    tasks_processor::stop();
}

void receive_auth_response(
    connection_ptr&& soc,
    const boost::system::error_code& err)
{
    if (err) {
        std::cerr << "Error on sending data: " << err.message() << '\n';
        assert(false);
    }

    async_read_data(
        std::move(soc),
        &process_server_response,
        2
    );
}

void send_auth() {
    connection_ptr soc = tasks_processor::create_connection(
        "127.0.0.1", g_port_num
    );
    soc->data = "auth_name";

    async_write_data(
        std::move(soc),
        &receive_auth_response
    );
}

