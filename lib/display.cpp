#include "display.h"

ctra::display::display()
{
    initscr();      //Start curses mode
    start_color();  //Start color mode
    init_pair(1, COLOR_BLACK, COLOR_BLACK );
    init_pair(2, COLOR_BLACK, COLOR_BLUE );
    nocbreak();                     // make getch calls wait for newline
    const char *s  = u8"♜";


    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            m_sqaures[y][x] = newwin(1,2,y,2*x);
            wbkgd(m_sqaures[y][x], COLOR_PAIR(((x+y) % 2)+1));
            wprintw(m_sqaures[y][x], s);
            wrefresh(m_sqaures[y][x]);
        }
    }
    
    m_commandWin = newwin(1, 20, 
        ctra::display::COMMAND_WIN_Y, 
        ctra::display::COMMAND_WIN_X);
    m_userOutWin = newwin(2, 20, 3, 20);
    m_gameStatusWin = newwin(1, 20, 1, 20);
    
}

std::string ctra::display::readUserInput()
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

void ctra::display::writeGameStatus(std::string msg)
{
    wclear(m_gameStatusWin);
    wprintw(m_gameStatusWin, msg.c_str());
    wrefresh(m_gameStatusWin);
}

void ctra::display::writeUserOutput(std::string msg)
{
    wclear(m_userOutWin);
    wprintw(m_userOutWin, msg.c_str());
    wrefresh(m_userOutWin);
}

ctra::display::~display()
{
    endwin();			            /* End curses mode		  */
}
