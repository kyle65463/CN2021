#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "connection/server_socket.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "usage: ./server <port>" << endl;
        return 0;
    }
    int port = stoi(argv[1]);
    cout << "hi " << port << endl;
    ServerSocket server = ServerSocket(port);
    while (1)
    {
        Connection *conn = server.makeConnection();
        string msg = "Hi from server";
        conn->sendMessage(msg);
        string res = conn->recvMessage();
        cout << "Get: " << res << endl;
        conn->closeConnection();
    }
}