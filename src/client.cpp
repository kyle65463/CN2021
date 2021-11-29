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
        fs::create_directory(clientBasepath); // create client_dir folder

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

    bool isLoggedIn = false;
    while (1)
    {
        string output = conn->recvMessage();
        cout << output;
        if (output == "connect successfully\n")
            isLoggedIn = true;

        string input;
        getline(cin, input);
        conn->sendMessage(input); // Send input to server first

        // Execute the command
        if (isLoggedIn)
        {
            Command *cmd = CommandFactory::parse(input);
            if (cmd != NULL)
                cmd->execute(conn);
        }
    }
}