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
    conn->sendFile("test.png");
    conn->sendFile("test.png");
}