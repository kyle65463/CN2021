#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "command.hpp"
#include "ls.hpp"
#include "get.hpp"
#include "put.hpp"
using namespace std;

class CommandFactory
{
public:
    static Command *parse(const string &input, bool serverSide = false)
    {
        // Tokenize the input
        vector<string> tokens;
        istringstream iss(input);
        copy(istream_iterator<string>(iss),
             istream_iterator<string>(),
             back_inserter(tokens));

        Command *cmd = NULL;
        if (tokens.size() == 1)
        {
            if (tokens[0] == "ls")
            {
                if (serverSide)
                    cmd = new ServerList();
                else
                    cmd = new ClientList();
            }
        }
        if (tokens.size() == 2)
        {
            if (tokens[0] == "get")
            {
                if (serverSide)
                    cmd = new ServerGet(tokens[1]);
                else
                    cmd = new ClientGet(tokens[1]);
            }
            if (tokens[0] == "put")
            {
                if (serverSide)
                    cmd = new ServerPut(tokens[1]);
                else
                    cmd = new ClientPut(tokens[1]);
            }
        }
        return cmd;
    };
};