#pragma once

#include <string>
#include "pieces.h"
#include "display.h"
#include "board.h"
#include "command_parser.h"


namespace ctra
{
    class game
    {
    public:

        enum class status
        {
            // value of 0 indicates in progress
            IN_PROG = 0,

            // values greater than 0 indicate a victory
            CHECKMATE = 1,

            // values less than 0 indicate a draw
            DRAW_AGREEMENT = -1
        };

        game() = default;
        game(const std::string& fen);
        
        void start();


    private:

        ctra::display disp;
        ctra::board board;

        void writeGameStatus(unsigned int fullmoveCount, bool whiteToMove, game::status stat);

    };
};