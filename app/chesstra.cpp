#include <clocale>
#include <iostream>
#include <sstream>
#include "game.h"

int main()
{
    std::setlocale(LC_ALL, "");
    ctra::display d;
    d.writeGameStatus("1. White to move");
    
    for (int i = 3; i > 0; --i)
    {
        std::string str = d.readUserInput();
        std::stringstream ss;
        ss << "you typed:" << std::endl << 
            str << std::endl;
        d.writeUserOutput(ss.str());
    }

    return 0;
}