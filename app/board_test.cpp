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