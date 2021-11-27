#include "command.hpp"

class Get : public Command
{
public:
    Get(const string& filename) : filename(filename) {}

private:
    string filename;
};