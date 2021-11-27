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
    string basepath = "src";
};
#endif