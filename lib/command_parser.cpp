#include "command_parser.h"
#include <regex>
#include <cctype>

namespace ctra
{
    command command_parser::identifyCommand(const std::string& cmd)
    {
        for (int i = 0; i < NUM_COMMANDS; ++i) 
        {
            const std::string& pattern = cmd_patterns[i];
            std::regex regexPattern(pattern);
            if (std::regex_search(cmd, regexPattern))
            {
                // found a command match, return the corresponding commmand
                return static_cast<command>(i);
            }
        }

        // command not recognized, return invalid command
        return command::INVALID;
    }

    std::pair<ctra::square, ctra::square> command_parser::parseTwoSquare(const std::string& cmd)
    {
        char srcx = tolower(cmd[0]) - 'a';
        char srcy = cmd[1] - '1';
        char destx = tolower(cmd[3]) - 'a';
        char desty = cmd[4] - '1';

        ctra::square src = getSquare(srcx, srcy);
        ctra::square dest = getSquare(destx, desty);

        return std::pair<ctra::square, ctra::square>(src, dest);
    }

}