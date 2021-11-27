#include <iostream>
#include "connection/client_socket.hpp"
#include "commands/command_factory.hpp"
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
    if (conn->getHasError())
    {
        cout << "Connection error" << endl;
        return 0;
    }

    while (1)
    {
        cout << conn->recvMessage();
        string input;
        getline(cin, input);
        conn->sendMessage(input); // Send input first
        Command *cmd = CommandFactory::parse(input);
        if (cmd != NULL)
            cmd->execute(conn);
    }
}