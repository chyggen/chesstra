#include "display.h"
#include "board.h"
#include <iostream>

namespace ctra
{
    display::display()
    {
        initscr();      //Start curses mode
        start_color();  //Start color mode
        init_pair(1, COLOR_BLACK, COLOR_WHITE );
        init_pair(2, COLOR_BLACK, COLOR_CYAN );
        nocbreak();                     // make getch calls wait for newline
        const char *s  = u8" ";

        for (int y = 0; y < 8; ++y)
        {
            for (int x = 0; x < 8; ++x)
            {
                m_sqaures[y][x] = newwin(1, 2, y, 2*x + BOARD_X_OFFSET);
                wbkgd(m_sqaures[y][x], COLOR_PAIR(((x+y) % 2)+1));
                wprintw(m_sqaures[y][x], s);
                wrefresh(m_sqaures[y][x]);
            }
        }

        m_xCoordWin = newwin(1, 16, 8, 2);
        // wprintw(m_xCoordWin, "a b c d e f g h ");
        wprintw(m_xCoordWin, u8"ａｂｃｄｅｆｇｈ");
        wrefresh(m_xCoordWin);
        m_yCoordWin = newwin(8, 2, 0, 0);
        wprintw(m_yCoordWin, "8 7 6 5 4 3 2 1 ");
        // wprintw(m_xCoordWin, u8"１２３４５６７８");

        wrefresh(m_yCoordWin);

        m_commandWin = newwin(2, 80, 
            ctra::display::COMMAND_WIN_Y, 
            ctra::display::COMMAND_WIN_X);
        m_userOutWin = newwin(2, 80, 3, 20);
        m_gameStatusWin = newwin(1, 30, 1, 20);
        m_fenWin = newwin(2, 90, 10, 0);
        
    }

    void display::updateBoard(const ctra::board& b)
    {
        for (int y = 0; y < 8; ++y)
        {
            for (int x = 0; x < 8; ++x)
            {
                wclear(m_sqaures[y][x]);
                if (b.at(x,y) != nullptr)
                {
                    wprintw(m_sqaures[y][x], b.at(x,y)->getDisplayChar().c_str());
                }
                wrefresh(m_sqaures[y][x]);
            }
        }

        std::string fenWinMsg = std::string("FEN:\n") + b.generateFEN().c_str();

        wclear(m_fenWin);
        wprintw(m_fenWin, fenWinMsg.c_str());
        wrefresh(m_fenWin);
    }

    std::string display::readUserInput()
    {
        int ch; // To read character input from user
        std::string input;

        while(ch = wgetch(m_commandWin))
        {
            if (ch != '\n')
            {
                input.push_back(ch);
            }
            else
            {
                break;
            }
        }
        wclear(m_commandWin);
        return input;
    }

    void display::writeGameStatus(const std::string msg)
    {
        wclear(m_gameStatusWin);
        wprintw(m_gameStatusWin, msg.c_str());
        wrefresh(m_gameStatusWin);
    }

    void display::writeUserOutput(const std::string msg)
    {
        wclear(m_userOutWin);
        wprintw(m_userOutWin, msg.c_str());
        wrefresh(m_userOutWin);
    }

    display::~display()
    {
        endwin();			            /* End curses mode		  */
    }

}
