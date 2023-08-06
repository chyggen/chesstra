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
    std::cout << b.at(ctra::E1) << std::endl;
    b.assignEmpty(ctra::pieceID::king, ctra::colour::white, ctra::E1);
    std::cout << (b.at(ctra::E1) == nullptr) << std::endl;
    d.updateBoard(b);
    
    // pause until enter is pressed
    d.readUserInput();


    return 0;
}