#include "command.hpp"

class Put : public Command
{
public:
    Put(const string &filename) : filename(filename) {}

    void execute(Connection *conn)
    {
    }

private:
    string filename;
};