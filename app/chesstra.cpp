#include <clocale>
#include <iostream>
#include "game.h"


int main(int argc, char* argv[])
{
    // enable wide character support
    std::setlocale(LC_ALL, "");

    // parse input flags

    int argIdx = 1;
    std::string fen = "";
    while(argIdx < argc)
    {
        std::string flag = argv[argIdx];
        if (flag == "-f" || flag == "--fen")
        {
            fen = argv[argIdx + 1];
            argIdx += 2;
        }

    }
    
    // start the game
    if (fen != "")
    {
        ctra::game g(fen);
        g.start();
    }
    else 
    {
        ctra::game g;
        g.start();
    }
    return 0;
}