#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

namespace ctra
{
    class display
    {
    public:

        void update()
        {
            initscr();                      /* Start curses mode 		  */
            // WINDOW* win = newwin(10, 30, 0, 0);
            const char *s  = u8"♜ ♖ ♜ ♖ ♜";
            printw(s);
            refresh();			            /* Print it on to the real screen */
            getch();			            /* Wait for user input */
            endwin();			            /* End curses mode		  */
        }
    };
}
