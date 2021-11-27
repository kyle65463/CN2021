#include <iostream>
#include <algorithm>
#include "connection/multiplexer.hpp"
using namespace std;

bool disconnected(Connection *conn)
{
    return conn->getDisconnected();
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "usage: ./server <port>" << endl;
        return 0;
    }
    int port = stoi(argv[1]);
    ServerSocket server = ServerSocket(port);
    vector<Connection *> conns;
    Multiplexer mux = Multiplexer(server, conns);

    server.startListening();
    cout << "server is listening on port " << port << endl;
    while (1)
    {
        cout << "n_con=" << conns.size() << endl;
        mux.waitForReady();
        if (mux.isServerReady())
        {
            Connection *conn = server.makeConnection();
            conns.push_back(conn);
            conn->sendMessage("Hi, how are you");
        }

        for (int i = 0; i < conns.size(); i++)
        {
            Connection *conn = conns[i];
            if (mux.isConnectionReady(conn))
            {
                conn->sendMessage("yo man");
                cout << conn->getFd() << " " << conn->recvMessage() << endl;
                if (conn->getDisconnected())
                {
                    cout << conn->getFd() << " is disconnected" << endl;
                }
            }
        }

        conns.erase(remove_if(conns.begin(), conns.end(), disconnected), conns.end());
    }
    cout << "sever ends" << endl;
}