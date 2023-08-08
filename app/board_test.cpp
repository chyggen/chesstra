#include <clocale>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include "game.h"

int main()
{
    std::setlocale(LC_ALL, "");
    ctra::display d;
    d.writeGameStatus("1. White to move");

    ctra::board b;
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
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    b.movePiece(ctra::E2, ctra::E4);
    d.updateBoard(b);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    b.movePiece(ctra::D7, ctra::D5);
    d.updateBoard(b);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    b.movePiece(ctra::E4, ctra::D5);
    d.updateBoard(b);
    
    // pause until enter is pressed
    d.readUserInput();

    return 0;
}