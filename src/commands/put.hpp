#include "command.hpp"

class ClientPut : public Command
{
public:
    ClientPut(const string &filename) : filename(filename) {}

    void execute(Connection *conn)
    {
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
    }

private:
    string filename;
};