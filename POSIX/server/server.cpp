#include <sys/socket.h>       /*  socket definitions        */
#include <sys/types.h>        /*  socket types              */
#include <arpa/inet.h>        /*  inet (3) funtions         */
#include <unistd.h>           /*  misc. UNIX functions      */

#include <iostream>
#include <cstring>
#include <vector>
#include <fcntl.h>

// Global constants
#define ECHO_PORT          (2002)
#define MAX_LINE           (1000)
#define LISTENQ            (1024)   // Backlog for listen()



class TCP_server {
protected:
    //A SOCKET is simply a typedef for an unsigned int.
    //In Unix, socket handles were just about same as file 
    //handles which were again unsigned ints.
    //Since this cannot be entirely true under Windows
    //a new data type called SOCKET was defined.
    unsigned int server;
    unsigned short port;
    int current_listening_socket;
    int current_connection_socket;
    std::vector<int> connection_sockets_vector;
public:    
    virtual ~TCP_server(){
        for (int connection_socket : connection_sockets_vector){
    	    if ( close(connection_socket) < 0 ) {
                std::cerr << "Error calling close()" << std::endl;
	        exit(EXIT_FAILURE);
	    }
        }
    }

    bool blocking_socket(int fd, bool blocking){
	if (fd < 0) return false;

	#ifdef _WIN32
		unsigned long mode = blocking ? 0 : 1;
		return (ioctlsocket(fd, FIONBIO, &mode) == 0) ? true : false;
	#else
		int flags = fcntl(fd, F_GETFL, 0);
		if (flags == -1) return false;
		flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
		return (fcntl(fd, F_SETFL, flags) == 0) ? true : false;
	#endif
    }

    #ifndef _WIN32
    void accept_connection (){
    	// Wait for a connection, then accept() it
	if ( (current_connection_socket = accept(current_listening_socket, NULL, NULL) ) < 0 ) {
	    std::cerr << "Error calling accept()" << std::endl;
	    exit(EXIT_FAILURE);
	}
	std::cout << "Accepted a connection" << std::endl;
	(void) blocking_socket(current_connection_socket, false);
	connection_sockets_vector.push_back(current_connection_socket);
	accept_connection();
    }
    
    void create_listening_socket() {
        struct sockaddr_in servaddr;  // socket address structure
        
        if ( (current_listening_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
	    std::cerr << "Error creating listening socket." << std::endl;
	    exit(EXIT_FAILURE);
        }

        // Set all bytes in socket address structure to zero, and fill in the relevant data members
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family      = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port        = htons(port);
        
        // Bind our socket addresss to the listening socket, and call listen()
        if ( bind(current_listening_socket, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0 ) {
	    std::cerr << "Error calling bind()" << std::endl;
	    exit(EXIT_FAILURE);
        }

        if ( listen(current_listening_socket, LISTENQ) < 0 ) {
	    std::cerr << "Error calling listen()" << std::endl;
	    exit(EXIT_FAILURE);
        }

        accept_connection();
    }
    #endif
    
    #ifdef _WIN32
    void accept_connection_windows() {
        //we will need variables to hold the client socket.
        //thus we declare them here.
        SOCKET client;
        sockaddr_in from;
        int fromlen = sizeof(from);

        std::string temp;

        //accept() will accept an incoming
        //client connection
        client = accept(server, (struct sockaddr*)&from, &fromlen);
        std::stringstream temp_str;
        temp_str << "Your IP is" << inet_ntoa(from.sin_addr);
        temp = temp_str.str();

        std::cout << "Connection from " << inet_ntoa(from.sin_addr) << "\r\n";

        //we simply send this string to the client
        send(client, temp.c_str(), temp.length(), 0);


        //close the client socket
        closesocket(client);
        accept_connection_windows();
    }
    
    void create_listener_windows() {
        //WSADATA is a struct that is filled up by the call 
        //to WSAStartup
        WSADATA wsaData;

        //The sockaddr_in specifies the address of the socket
        //for TCP/IP sockets. Other protocols use similar structures.
        sockaddr_in local;

        //WSAStartup initializes the program for calling WinSock.
        //The first parameter specifies the highest version of the 
        //WinSock specification, the program is allowed to use.
        int wsaret = WSAStartup(0x101, &wsaData);

        //WSAStartup returns zero on success.
        //If it fails we exit.
        if (wsaret != 0)
        {
            return;
        }

        //Now we populate the sockaddr_in structure
        local.sin_family = AF_INET; //Address family
        local.sin_addr.s_addr = INADDR_ANY; //Wild card IP address
        local.sin_port = htons(port); //port to use

        //the socket function creates our SOCKET
        server = socket(AF_INET, SOCK_STREAM, 0);

        //If the socket() function fails we exit
        if (server == INVALID_SOCKET)
        {
            return;
        }

        //bind links the socket we just created with the sockaddr_in 
        //structure. Basically it connects the socket with 
        //the local address and a specified port.
        //If it returns non-zero quit, as this indicates error
        if (bind(server, (sockaddr*)&local, sizeof(local)) != 0)
        {
            return;
        }

        //listen instructs the socket to listen for incoming 
        //connections from clients. The second arg is the backlog
        if (listen(server, 10) != 0)
        {
            return;
        }
        accept_connection_windows();
    }
    #endif
    
    TCP_server(unsigned short port) : port{port} {
	#ifdef _WIN32
	    create_listener_windows();
	#else
	    create_listening_socket();
	#endif
    }
};

int main(int argc, char *argv[]) {
    char      buffer[MAX_LINE];      //  character buffer

    TCP_server(ECHO_PORT);
}
