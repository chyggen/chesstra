#include "board.h"
#include <utility>
#include <iostream>
#include <array>

namespace ctra
{

    enum class command
    {
        INVALID = -1,
        MOVE_TWO_SQUARE,
        MOVE_ALGEBRAIC,
        MOVE_UNDO,
        MOVE_COMMENT,
        GAME_RESIGN,
        GAME_DRAW,
        GET_FEN,
        GET_PGN,
        QUIT
    };

    static const int NUM_COMMANDS = 9;

    // regex patterns for identifying commands
    static const std::array<std::string, 9> cmd_patterns = 
    {
        // two square move regex pattern
        "^[A-Ha-h][1-8]\\s[A-Ha-h][1-8]$",

        // algebraic move regex pattern
        // unimplemented thus far, use a pattern which matches nothing
        "\\A\\Z",

        // undo move pattern
        "^undo$",

        // add game comment pattern
        "^com\\s.*",

        // resign game pattern
        "^resign$",

        // draw game pattern
        "^draw$",
        
        // generate FEN string pattern
        "^fen$",

        // generate PGN file pattern
        "^pgn$",

        // quit program command
        "^quit$"
    };

    class command_parser
    {
    public:

        // Identifies what type of command is described by str
        static command identifyCommand(const std::string& cmd);
        
        static std::pair<ctra::square, ctra::square> parseTwoSquare(const std::string& cmd);

    private:

    };
}