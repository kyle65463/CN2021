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
        cout << conn->recvMessage();
    }
};

class ServerList : public Command
{
public:
    void execute(Connection *conn)
    {
        // List the directory
        stringstream ss;
        vector<string> paths;
        for (const auto &entry : fs::directory_iterator(serverBasepath))
        {
            string path = entry.path().string();
            string trimmedPath = path.substr(serverBasepath.size() + 1, path.size()); // Remove basepath
            paths.push_back(trimmedPath);
        }

        // Sort and send the result
        sort(paths.begin(), paths.end());
        for (auto &path : paths)
            ss << path << endl;
        conn->sendMessage(ss.str());
    }
};