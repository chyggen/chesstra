#include "display.h"

ctra::display::display()
{
    initscr();      //Start curses mode
    start_color();  //Start color mode
    init_pair(0, COLOR_BLACK, COLOR_WHITE);
    init_pair(1, COLOR_BLACK, COLOR_BLUE);
    const char *s  = u8"♖";


    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            m_sqaures[y][x] = newwin(1,2,y,2*x);
            wbkgd(m_sqaures[y][x], COLOR_PAIR((x+y) % 2));
            wprintw(m_sqaures[y][x], s);
            wrefresh(m_sqaures[y][x]);
        }
    }
    
    m_commandWin = newwin(1, 20, 
        ctra::display::COMMAND_WIN_Y, 
        ctra::display::COMMAND_WIN_X);
    
}

void ctra::display::update()
{
    // WINDOW* win = newwin(10, 30, 0, 0);
    
    // printw(s);
    // refresh();			            /* Print it on to the real screen */
    wgetch(m_commandWin);			            /* Wait for user input */
    wrefresh(m_commandWin);
}

ctra::display::~display()
{
    endwin();			            /* End curses mode		  */
}
