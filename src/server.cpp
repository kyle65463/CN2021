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
        string msg = "Hi from server";
        conn->sendMessage(msg);
        string res = conn->recvMessage();
        size_t datasize = 1;
        FILE *fd = fopen("test_out.png", "wb");
        while (datasize > 0)
        {
            char text[1024];
            datasize = recv(conn->fd, text, sizeof(text), 0);
            fwrite(&text, 1, datasize, fd);
        }
        fclose(fd);
        cout << "Get: " << res << endl;
        conn->closeConnection();
    }
}