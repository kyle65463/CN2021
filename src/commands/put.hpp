#include "command.hpp"

class ClientPut : public Command
{
public:
    ClientPut(const string &filename) : filename(filename) {}

    void execute(Connection *conn)
    {
        string fullFilename = clientBasepath + "/" + filename;
        conn->sendFile(fullFilename);
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
        bool err = conn->recvFile(serverBasepath + "/" + filename);
        if (!err)
            conn->sendMessage("put " + filename + " successfully\n");
        else
            conn->sendMessage("The " + filename + " doesn’t exist\n");
    }

private:
    string filename;
};