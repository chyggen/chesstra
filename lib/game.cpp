#include "game.h"
#include <sstream>

namespace ctra
{
    game::game(const std::string& fen) : board(fen), disp()
    {}
    
    void game::start()
    {
        writeGameStatus(board.fullmoveCounter(), board.whiteToMove(), status::IN_PROG);
        
        disp.updateBoard(board);
        
        for (;;)
        {
            std::string str = disp.readUserInput();
            command c = command_parser::identifyCommand(str);

            if (c == command::QUIT)
            {
                return;
            }
            else if (c == command::INVALID)
            {
                disp.writeUserOutput("command not recognized");
            }
            else if (c == command::MOVE_TWO_SQUARE)
            {
                auto sq_pair = command_parser::parseTwoSquare(str);
                moveResult move_res = board.movePiece(sq_pair.first, sq_pair.second);
                if (isLegal(move_res)) 
                {
                    disp.writeUserOutput("valid move"); 
                }
                else 
                {
                    disp.writeUserOutput("invalid move"); 
                }
                disp.updateBoard(board);
                writeGameStatus(board.fullmoveCounter(), board.whiteToMove(), status::IN_PROG);
            }
            else
            {
                std::stringstream ss;
                ss << "command:" << std::endl << 
                    static_cast<int>(c);
                disp.writeUserOutput(ss.str());
            }
        
        }
    }

    void game::writeGameStatus(unsigned int fullmoveCount, bool whiteToMove, game::status stat)
    {
        std::stringstream msg;
        msg << fullmoveCount << ". ";
        switch (stat)
        {
            case game::status::IN_PROG:
                msg << (whiteToMove ? "White to move" : "Black to move");
                break;

            case game::status::CHECKMATE:
                msg << (whiteToMove ? "Black is victorious!" : "White is victorious!");
                break;

            case game::status::DRAW_AGREEMENT:
                msg << "Game drawn by agreement";
                break;
        }
        disp.writeGameStatus(msg.str());
    }
}