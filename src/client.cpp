#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
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
    string msg = "yoyoyo I'm client";
    conn->sendMessage(msg);
    string res = conn->recvMessage();
    cout << "Get: " << res << endl;
}