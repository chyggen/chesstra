#include <clocale>
#include <iostream>
#include "game.h"


int main(int argc, char* argv[])
{
    // enable wide character support
    std::setlocale(LC_ALL, "");

    ctra::game g;

    // parse input flags
    int argIdx = 1;
    while(argIdx < argc)
    {
        std::string flag = argv[argIdx];
        if (flag == "-a" || flag == "--autosave")
        {
            g.autoSave = true;
            argIdx++;
        }
        if (flag == "-f" || flag == "--fen")
        {
            g.startFromFen = true;
            g.fen = argv[argIdx + 1];
            argIdx += 2;
        }
        if (flag == "-w" || flag == "--white")
        {
            g.whiteName = argv[argIdx + 1];
            argIdx += 2;
        }
        if (flag == "-b" || flag == "--black")
        {
            g.blackName = argv[argIdx + 1];
            argIdx += 2;
        }
        if (flag == "-e" || flag == "--event")
        {
            g.eventName = argv[argIdx + 1];
            argIdx += 2;
        }
    }
    
    // start the game
    g.start();

    return 0;
}