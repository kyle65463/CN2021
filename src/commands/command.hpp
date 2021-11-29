#ifndef SOME_UNIQUE_NAME_HERE
#define SOME_UNIQUE_NAME_HERE
#include <string>
#include <vector>
using namespace std;

class Command
{
public:
    virtual void execute(Connection *conn) = 0;

protected:
    string serverBasepath = "server_dir";
    string clientBasepath = "client_dir";
};

class ServerCommandNotFound : public Command
{
public:
    void execute(Connection *conn)
    {
        conn->sendMessage("Command not found\n");
    }
};

class ClientCommandNotFound : public Command
{
public:
    void execute(Connection *conn)
    {
    }
};

class ServerCommandFormatError : public Command
{
public:
    void execute(Connection *conn)
    {
        conn->sendMessage("Command format error\n");
    }
};

class ClientCommandFormatError : public Command
{
public:
    void execute(Connection *conn)
    {
    }
};
#endif