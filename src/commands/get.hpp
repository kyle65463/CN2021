#include "command.hpp"

class ClientGet : public Command
{
public:
    ClientGet(const string &filename) : filename(filename) {}

    void execute(Connection *conn)
    {
        string fullFilename = clientBasepath + "/" + filename;
        conn->recvFile(fullFilename);
    }

private:
    string filename;
};

class ServerGet : public Command
{
public:
    ServerGet(const string &filename) : filename(filename) {}

    void execute(Connection *conn)
    {
        string fullFilename = serverBasepath + "/" + filename;
        bool err = conn->sendFile(fullFilename);
        if (!err)
            conn->sendMessage("get " + filename + " successfully\n");
        else
            conn->sendMessage("The " + filename + " doesn’t exist\n");
    }

private:
    string filename;
};