#include <iostream>
#include "connection/client_socket.hpp"
#include "commands/command_factory.hpp"
using namespace std;
namespace fs = std::__fs::filesystem;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "usage: ./server <ip:port>" << endl;
        return 0;
    }
    string clientBasepath = "client_dir";
    if (!fs::is_directory(clientBasepath) || !fs::exists(clientBasepath))
        fs::create_directory(clientBasepath); // create server_dir folder
    
    string ipport = argv[1];
    string ip = ipport.substr(0, ipport.find(':'));
    int port = stoi(ipport.substr(ipport.find(':') + 1));
    ClientSocket client = ClientSocket(port, ip);
    Connection *conn = client.makeConnection();
    if (client.getHasError())
    {
        cout << "connection error" << endl;
        return 0;
    }

    while (1)
    {
        cout << conn->recvMessage();
        string input;
        getline(cin, input);
        conn->sendMessage(input); // Send input to server first
        Command *cmd = CommandFactory::parse(input);
        if (cmd != NULL)
            cmd->execute(conn);
    }
}