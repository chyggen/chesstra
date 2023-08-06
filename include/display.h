#pragma once

// Make sure ncurses widechar support is enabled
#ifndef _XOPEN_SOURCE_EXTENDED
    #define _XOPEN_SOURCE_EXTENDED
#endif

#include <ncursesw/ncurses.h>
#include <utility>
#include <string>
#include "board.h"

namespace ctra
{
    class display
    {
    public:

        display();

        std::string readUserInput();

        void writeGameStatus(const std::string str);
        void writeUserOutput(const std::string str);
        void updateBoard(const ctra::board& b);

        ~display();

    private:

        WINDOW* m_sqaures[8][8];
        WINDOW* m_commandWin;
        WINDOW* m_gameStatusWin;
        WINDOW* m_userOutWin;

        static const int COMMAND_WIN_Y = 6;
        static const int COMMAND_WIN_X = 20;

    };
}
