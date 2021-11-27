#include "command.hpp"

class ClientPut : public Command
{
public:
    ClientPut(const string &filename) : filename(filename) {}

    void execute(Connection *conn)
    {
        conn->sendFile(clientBasepath + "/" + filename);
    }

private:
    string filename;
};

class ServerPut : public Command
{
public:
    ServerPut(const string &filename) : filename(filename) {}

    void execute(Connection *conn)
    {
        conn->recvFile(serverBasepath + "/" + filename);
    }

private:
    string filename;
};