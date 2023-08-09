#include <clocale>
#include <iostream>
#include "game.h"


int main()
{
    // enable wide character support
    std::setlocale(LC_ALL, "");

    // start the game
    ctra::game g;
    g.start();

    return 0;
}