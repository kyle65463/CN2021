#include <vector>
#include <sys/select.h>
#include <fcntl.h>
#include "server_socket.hpp"

class Multiplexer
{
public:
    Multiplexer(ServerSocket &server, vector<Connection *> &conns) : server(server), conns(conns) {}

    void waitForReady()
    {
        // IO multiplexing
        FD_ZERO(&read_set);                // Reset the fd set
        FD_SET(server.getFd(), &read_set); // Turn on the bit of listening port
        for (int i = 0; i < conns.size(); i++)
            FD_SET(conns[i]->getFd(), &read_set); // Turn on the bit of request connections
        select(100, &read_set, NULL, NULL, NULL); // Check if there is any ready connection
    }

    bool isServerReady()
    {
        return FD_ISSET(server.getFd(), &read_set);
    }

    bool isConnectionReady(Connection *conn)
    {
        return FD_ISSET(conn->getFd(), &read_set);
    }

private:
    fd_set read_set;
    ServerSocket &server;
    vector<Connection *> &conns;
};