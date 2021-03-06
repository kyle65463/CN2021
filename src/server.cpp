#include <iostream>
#include <algorithm>
#include "connection/multiplexer.hpp"
#include "commands/command_factory.hpp"
using namespace std;
namespace fs = std::filesystem;

bool isDisconnected(Connection *conn) { return conn->getIsDisconnected(); }

void removeDisconnectedConnections(vector<Connection *> &conns)
{
    // for (int i = 0; i < conns.size(); i++)
    //     if (conns[i]->getIsDisconnected())
    //         cout << conns[i]->getFd() << " is disconnected" << endl;
    conns.erase(remove_if(conns.begin(), conns.end(), isDisconnected), conns.end());
}

bool isUsernameDuplicated(const string &username, vector<Connection *> &conns)
{
    for (int i = 0; i < conns.size(); i++)
        if (conns[i]->getIsLoggedIn() && conns[i]->getUsername() == username)
            return true;
    return false;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "usage: ./server <port>" << endl;
        return 0;
    }

    string serverBasepath = "server_dir";
    if (!fs::is_directory(serverBasepath) || !fs::exists(serverBasepath))
        fs::create_directory(serverBasepath); // create server_dir folder

    int port = stoi(argv[1]);
    ServerSocket server = ServerSocket(port);
    vector<Connection *> conns;
    Multiplexer mux = Multiplexer(server, conns);

    // Start the server
    server.startListening();
    if (server.getHasError())
    {
        cout << "bind error" << endl;
        return 0;
    }

    while (1)
    {
        mux.waitForReady();
        if (mux.isServerReady())
        {
            Connection *conn = server.makeConnection();
            conns.push_back(conn);
            conn->sendMessage("input your username:\n");
        }

        for (int i = 0; i < conns.size(); i++)
        {
            Connection *conn = conns[i];
            if (mux.isConnectionReady(conn))
            {
                if (!conn->getIsLoggedIn())
                {
                    // Get client's username for login
                    string username = conn->recvMessage();
                    if (isUsernameDuplicated(username, conns))
                        conn->sendMessage("username is in used, please try another:\n");
                    else
                    {
                        conn->login(username);
                        conn->sendMessage("connect successfully\n");
                    }
                }
                else
                {
                    // Get client's commands
                    string input = conn->recvMessage();
                    Command *cmd = CommandFactory::parse(input, true);
                    if (cmd != NULL)
                        cmd->execute(conn);
                }
            }
        }

        removeDisconnectedConnections(conns);
    }
}