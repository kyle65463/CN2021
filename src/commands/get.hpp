#include "command.hpp"

class ClientGet : public Command
{
public:
    ClientGet(const string &filename) : filename(filename) {}

    void execute(Connection *conn)
    {
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
    }

private:
    string filename;
};