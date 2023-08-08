#include <clocale>
#include <iostream>
#include <sstream>
#include "game.h"


int main()
{
    // initialize components
    std::setlocale(LC_ALL, "");
    ctra::display d;
    ctra::board b;
    d.writeGameStatus("1. White to move");

    
    // fill the board in the default position
    b.assignPiece(ctra::pieceID::rook,      ctra::colour::white, ctra::A1);
    b.assignPiece(ctra::pieceID::knight,    ctra::colour::white, ctra::B1);
    b.assignPiece(ctra::pieceID::bishop,    ctra::colour::white, ctra::C1);
    b.assignPiece(ctra::pieceID::queen,     ctra::colour::white, ctra::D1);
    b.assignPiece(ctra::pieceID::king,      ctra::colour::white, ctra::E1);
    b.assignPiece(ctra::pieceID::bishop,    ctra::colour::white, ctra::F1);
    b.assignPiece(ctra::pieceID::knight,    ctra::colour::white, ctra::G1);
    b.assignPiece(ctra::pieceID::rook,      ctra::colour::white, ctra::H1);

    b.assignPiece(ctra::pieceID::pawn,      ctra::colour::white, ctra::A2);
    b.assignPiece(ctra::pieceID::pawn,      ctra::colour::white, ctra::B2);
    b.assignPiece(ctra::pieceID::pawn,      ctra::colour::white, ctra::C2);
    b.assignPiece(ctra::pieceID::pawn,      ctra::colour::white, ctra::D2);
    b.assignPiece(ctra::pieceID::pawn,      ctra::colour::white, ctra::E2);
    b.assignPiece(ctra::pieceID::pawn,      ctra::colour::white, ctra::F2);
    b.assignPiece(ctra::pieceID::pawn,      ctra::colour::white, ctra::G2);
    b.assignPiece(ctra::pieceID::pawn,      ctra::colour::white, ctra::H2);

    b.assignPiece(ctra::pieceID::pawn,      ctra::colour::black, ctra::A7);
    b.assignPiece(ctra::pieceID::pawn,      ctra::colour::black, ctra::B7);
    b.assignPiece(ctra::pieceID::pawn,      ctra::colour::black, ctra::C7);
    b.assignPiece(ctra::pieceID::pawn,      ctra::colour::black, ctra::D7);
    b.assignPiece(ctra::pieceID::pawn,      ctra::colour::black, ctra::E7);
    b.assignPiece(ctra::pieceID::pawn,      ctra::colour::black, ctra::F7);
    b.assignPiece(ctra::pieceID::pawn,      ctra::colour::black, ctra::G7);
    b.assignPiece(ctra::pieceID::pawn,      ctra::colour::black, ctra::H7);

    b.assignPiece(ctra::pieceID::rook,      ctra::colour::black, ctra::A8);
    b.assignPiece(ctra::pieceID::knight,    ctra::colour::black, ctra::B8);
    b.assignPiece(ctra::pieceID::bishop,    ctra::colour::black, ctra::C8);
    b.assignPiece(ctra::pieceID::queen,     ctra::colour::black, ctra::D8);
    b.assignPiece(ctra::pieceID::king,      ctra::colour::black, ctra::E8);
    b.assignPiece(ctra::pieceID::bishop,    ctra::colour::black, ctra::F8);
    b.assignPiece(ctra::pieceID::knight,    ctra::colour::black, ctra::G8);
    b.assignPiece(ctra::pieceID::rook,      ctra::colour::black, ctra::H8);

    d.updateBoard(b);
    
    for (;;)
    {
        std::string str = d.readUserInput();
        ctra::command c = ctra::command_parser::identifyCommand(str);

        if (c == ctra::command::QUIT)
        {
            return 0;
        }
        else if (c == ctra::command::INVALID)
        {
            d.writeUserOutput("command not recognized");
        }
        else if (c == ctra::command::MOVE_TWO_SQUARE)
        {
            auto sq_pair = ctra::command_parser::parseTwoSquare(str);
            bool valid_move = b.movePiece(sq_pair.first, sq_pair.second);
            if (valid_move) 
            {
                d.writeUserOutput("valid move"); 
            }
            else 
            {
                d.writeUserOutput("invalid move"); 
            }
            d.updateBoard(b);
        }
        else
        {
            std::stringstream ss;
            ss << "command:" << std::endl << 
                static_cast<int>(c);
            d.writeUserOutput(ss.str());
        }
       
    }

    return 0;
}