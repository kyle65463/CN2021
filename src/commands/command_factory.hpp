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
    void initialize()
    {
    }

    static Command *parse(const string &input)
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
                cmd = new List();
        }
        if (tokens.size() == 2)
        {
            if (tokens[0] == "get")
                cmd = new Get(tokens[1]);
            if (tokens[0] == "put")
                cmd = new Put(tokens[1]);
        }
        return cmd;
    };
};