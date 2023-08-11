#pragma once

#include <string>
#include <vector>
#include "pieces.h"
#include "display.h"
#include "board.h"
#include "command_parser.h"


namespace ctra
{
    enum class tagField
    {
        Event,
        Site,
        White,
        Black,
        FEN,
        INVALID
    };

    class game
    {
    public:

        enum class gameStatus
        {
            // value of 0 indicates in progress
            IN_PROG = 0,

            // values greater than 0 indicate a victory
            CHECKMATE = 1,

            // values less than 0 indicate a draw
            DRAW_AGREEMENT = -1
        };

        game() = default;
        ~game();

        void start();

        //void addMove();

        bool startFromFen = false;
        bool autoSave = false;

        std::string whiteName = "?";
        std::string blackName = "?";
        std::string eventName = "game";
        std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    private:

        ctra::display disp;
        ctra::board board;
        gameStatus status = gameStatus::IN_PROG;

        std::vector<std::string> movelog;

        void writeGameStatus(unsigned int fullmoveCount, bool whiteToMove);

        std::string getResultStr();
        bool exportPGN();



    };
};