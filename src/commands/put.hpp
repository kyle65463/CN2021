#include "command.hpp"

class Put : public Command
{
public:
    Put(const string& filename) : filename(filename) {}

private:
    string filename;
};