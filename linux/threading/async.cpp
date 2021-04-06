#include <future>
#include <vector>
#include <algorithm>
#include <iostream>

#include <sys/socket.h>       /*  socket definitions        */
#include <sys/types.h>        /*  socket types              */
#include <arpa/inet.h>        /*  inet (3) funtions         */
#include <unistd.h>           /*  misc. UNIX functions      */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace std;

struct Asyncable {
    private:
        const int MAX_LINE = 1000;

        int worker (char* szAddress, int remotePort){
            int       conn_s;                /*  connection socket         */
            struct    sockaddr_in servaddr;  /*  socket address structure  */
            char     *endptr;                /*  for strtol()              */
            char buffer[] = 
"Come live with me and be my love,\nAnd we will all the pleasures prove,\nThat Valleys, groves, hills, and fields,\nWoods, or steepy mountain yields.\n\nAnd we will sit upon the Rocks,\nSeeing the Shepherds feed their flocks,\nBy shallow Rivers to whose falls\nMelodious birds sing Madrigals.\n\nAnd I will make thee beds of Roses\nAnd a thousand fragrant posies,\nA cap of flowers, and a kirtle\nEmbroidered all with leaves of Myrtle;\n\nA gown made of the finest wool\nWhich from our pretty Lambs we pull;\nFair lined slippers for the cold,\nWith buckles of the purest gold;\n\nA belt of straw and Ivy buds,\nWith Coral clasps and Amber studs:\nAnd if these pleasures may thee move,\nCome live with me, and be my love.\n\nThe Shepherds’ Swains shall dance and sing\nFor thy delight each May-morning:\nIf these delights thy mind may move,\nThen live with me, and be my love.";

            /*  Create the listening socket  */
            if ( (conn_s = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
               fprintf(stderr, "ECHOCLNT: Error creating listening socket.\n");
               exit(EXIT_FAILURE);
            }

            /*  Set all bytes in socket address structure to
                zero, and fill in the relevant data members   */
            memset(&servaddr, 0, sizeof(servaddr));
            servaddr.sin_family      = AF_INET;
            servaddr.sin_port        = htons(remotePort);

            /*  Set the remote IP address  */
            if ( inet_aton(szAddress, &servaddr.sin_addr) <= 0 ) {
               printf("ECHOCLNT: Invalid remote IP address.\n");
               exit(EXIT_FAILURE);
            }
            
            /*  connect() to the remote echo server  */
            if ( connect(conn_s, (struct sockaddr *) &servaddr, sizeof(servaddr) ) < 0 ) {
               printf("ECHOCLNT: Error calling connect()\n");
               exit(EXIT_FAILURE);
            }

            /*  Send string to echo server, and retrieve response  */
            while (1){
                write(conn_s, buffer, strlen(buffer));
            }
            //read(conn_s, buffer, strlen(buffer));

            return conn_s;
        }

    public:
        Asyncable(){}
        Asyncable (const Asyncable& rhs){}
        Asyncable (char* szAddress, int remotePort){
            worker(szAddress, remotePort);
        }
        Asyncable& operator=(Asyncable& rhs){return *this;}
        int operator() (char* szAddress, int remotePort, int* socket_addr){
            return worker(szAddress, remotePort);
        }
};

void asyncWithNestedLambdas (){
    auto a1 = async(launch::deferred, [] (){ vector<int> v(50); generate(v.begin(), v.end(), 
    [] () -> int { static int similarToGlobal = 0; static int count = 1; cout << "Deferred counting " << count++ << endl; return similarToGlobal += 100;});});

    async(launch::async, [] (){ vector<int> v(100); generate(v.begin(), v.end(), 
    [] () -> int { static int similarToGlobal = 0; static int count = 1; cout << "Generate count " << count++ << endl; return similarToGlobal += 2;});});
    a1.wait();
}

int main (int argc, char** argv){
    asyncWithNestedLambdas();

    char localHost[10]="127.0.0.1";
    int remotePort=0;
    async(launch::async, [&localHost, &remotePort] () { vector<int> v(65535); generate(v.begin(), v.end(), [&localHost, &remotePort]() -> int { int socket_addr; async(launch::async, Asyncable(), &localHost[0], remotePort++, &socket_addr); return socket_addr; });});
}
