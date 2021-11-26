#include <iostream>
#include "connection/client_socket.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "usage: ./server <ip:port>" << endl;
        return 0;
    }
    string ipport = argv[1];
    string ip = ipport.substr(0, ipport.find(':'));
    int port = stoi(ipport.substr(ipport.find(':') + 1));
    ClientSocket client = ClientSocket(port, ip);
    Connection *conn = client.makeConnection();
    if(conn->getHasError()) {
        cout << "Connection error" << endl;
        return 0;
    }
    string msg = "yoyoyo I'm client";
    conn->sendMessage(msg);
    string res = conn->recvMessage();
    cout << "Get: " << res << endl;

    FILE *fd = fopen("test.png", "rb");
    size_t rret, wret;
    int bytes_read;
    char buffer[1024];
    while (!feof(fd))
    {
        
        if ((bytes_read = fread(&buffer, 1, 1024, fd)) > 0)
            send(conn->fd, buffer, bytes_read, 0);
        else
            break;
    }
    fclose(fd);
}