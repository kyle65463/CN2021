#include <string>
#include <iostream>
#include <sstream>
#include <filesystem>
#include "command.hpp"
namespace fs = std::__fs::filesystem;

class ClientList : public Command
{
public:
    void execute(Connection *conn)
    {
    }
};

class ServerList : public Command
{
public:
    void execute(Connection *conn)
    {
        stringstream ss;
        for (const auto &entry : fs::directory_iterator(serverBasepath))
        {
            string path = entry.path().string();
            string trimmedPath = path.substr(serverBasepath.size() + 1, path.size()); // Remove basepath
            ss << trimmedPath << endl;
        }
        conn->sendMessage(ss.str());
    }
};