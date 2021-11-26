#include <iostream>
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
    cout << "server is listening on port " << port << endl;
    ServerSocket server = ServerSocket(port);
    while (1)
    {
        Connection *conn = server.makeConnection();
        conn->recvFile("test_out.png");
        conn->recvFile("test_out2.png");
        conn->closeConnection();
    }
}