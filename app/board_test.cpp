#include <clocale>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include "game.h"
#include "board.h"

int main()
{
    ctra::board b;
    b.importFen("r3k2r/pppq1ppp/2n5/1B1pp1Bn/1b1PP1bN/2N5/PPPQ1PPP/R3K2R w KQkq - 12 9");
    b.updateAttackStats();

    std::cout << "black attacks:\n";
    for (int y = 7; y >=0 ; y--)
    {
        for (int x = 0; x < 8; x++)
        {
            ctra::square sq = ctra::getSquare(x, y);
            std::cout << b.attackStats(sq).black << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "white attacks:\n";
    for (int y = 7; y >=0 ; y--)
    {
        for (int x = 0; x < 8; x++)
        {
            ctra::square sq = ctra::getSquare(x, y);
            std::cout << b.attackStats(sq).white << " ";
        }
        std::cout << std::endl;
    }

    for (auto sq : b.at(ctra::E1)->getValidMoves(ctra::E1, b))
    {
          std::cout << ctra::getCoords(sq).first << ", " << ctra::getCoords(sq).second << std::endl;
        //   std::cout << b.at(sq)->getDisplayChar() << std::endl;
    }

    return 0;
}