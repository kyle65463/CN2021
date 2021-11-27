#include "command.hpp"

class Get : public Command
{
public:
    Get(const string &filename) : filename(filename) {}

    void execute(Connection *conn)
    {
    }

private:
    string filename;
};