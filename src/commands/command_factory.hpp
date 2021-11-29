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

        bool formatError = false;
        if (tokens.size() > 0)
        {
            if (tokens[0] == "ls")
            {
                if (tokens.size() == 1)
                {
                    if (serverSide)
                        return new ServerList();
                    else
                        return new ClientList();
                }
                else
                    formatError = true;
            }
            if (tokens[0] == "get")
            {
                if (tokens.size() == 2)
                {

                    if (serverSide)
                        return new ServerGet(tokens[1]);
                    else
                        return new ClientGet(tokens[1]);
                }
                else
                    formatError = true;
            }
            if (tokens[0] == "put")
            {
                if (tokens.size() == 2)
                {
                    if (serverSide)
                        return new ServerPut(tokens[1]);
                    else
                        return new ClientPut(tokens[1]);
                }
                else
                    formatError = true;
            }
        }
        if (formatError)
        {
            if (serverSide)

                return new ServerCommandFormatError();
            else
                return new ClientCommandFormatError();
        }
        if (serverSide)
            return new ServerCommandNotFound();
        else
            return new ClientCommandNotFound();
    };
};