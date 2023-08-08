#include <clocale>
#include <iostream>
#include <sstream>
#include "game.h"

int main()
{
    std::setlocale(LC_ALL, "");
    ctra::display d;
    d.writeGameStatus("1. White to move");

    ctra::board b;
    // fill the board in the default position
    b.assignEmpty(ctra::pieceID::rook,      ctra::colour::white, ctra::A1);
    b.assignEmpty(ctra::pieceID::knight,    ctra::colour::white, ctra::B1);
    b.assignEmpty(ctra::pieceID::bishop,    ctra::colour::white, ctra::C1);
    b.assignEmpty(ctra::pieceID::queen,     ctra::colour::white, ctra::D1);
    b.assignEmpty(ctra::pieceID::king,      ctra::colour::white, ctra::E1);
    b.assignEmpty(ctra::pieceID::bishop,    ctra::colour::white, ctra::F1);
    b.assignEmpty(ctra::pieceID::knight,    ctra::colour::white, ctra::G1);
    b.assignEmpty(ctra::pieceID::rook,      ctra::colour::white, ctra::H1);

    b.assignEmpty(ctra::pieceID::pawn,      ctra::colour::white, ctra::A2);
    b.assignEmpty(ctra::pieceID::pawn,      ctra::colour::white, ctra::B2);
    b.assignEmpty(ctra::pieceID::pawn,      ctra::colour::white, ctra::C2);
    b.assignEmpty(ctra::pieceID::pawn,      ctra::colour::white, ctra::D2);
    b.assignEmpty(ctra::pieceID::pawn,      ctra::colour::white, ctra::E2);
    b.assignEmpty(ctra::pieceID::pawn,      ctra::colour::white, ctra::F2);
    b.assignEmpty(ctra::pieceID::pawn,      ctra::colour::white, ctra::G2);
    b.assignEmpty(ctra::pieceID::pawn,      ctra::colour::white, ctra::H2);

    b.assignEmpty(ctra::pieceID::pawn,      ctra::colour::black, ctra::A7);
    b.assignEmpty(ctra::pieceID::pawn,      ctra::colour::black, ctra::B7);
    b.assignEmpty(ctra::pieceID::pawn,      ctra::colour::black, ctra::C7);
    b.assignEmpty(ctra::pieceID::pawn,      ctra::colour::black, ctra::D7);
    b.assignEmpty(ctra::pieceID::pawn,      ctra::colour::black, ctra::E7);
    b.assignEmpty(ctra::pieceID::pawn,      ctra::colour::black, ctra::F7);
    b.assignEmpty(ctra::pieceID::pawn,      ctra::colour::black, ctra::G7);
    b.assignEmpty(ctra::pieceID::pawn,      ctra::colour::black, ctra::H7);

    b.assignEmpty(ctra::pieceID::rook,      ctra::colour::black, ctra::A8);
    b.assignEmpty(ctra::pieceID::knight,    ctra::colour::black, ctra::B8);
    b.assignEmpty(ctra::pieceID::bishop,    ctra::colour::black, ctra::C8);
    b.assignEmpty(ctra::pieceID::queen,     ctra::colour::black, ctra::D8);
    b.assignEmpty(ctra::pieceID::king,      ctra::colour::black, ctra::E8);
    b.assignEmpty(ctra::pieceID::bishop,    ctra::colour::black, ctra::F8);
    b.assignEmpty(ctra::pieceID::knight,    ctra::colour::black, ctra::G8);
    b.assignEmpty(ctra::pieceID::rook,      ctra::colour::black, ctra::H8);


    std::cout << (b.at(ctra::E1) == nullptr) << std::endl;
    d.updateBoard(b);
    
    // pause until enter is pressed
    d.readUserInput();


    return 0;
}