#include "display.h"

void ctra::display::update()
{
    initscr();
    printw("Hello World !!!");	/* Print Hello World		  */
	refresh();			/* Print it on to the real screen */
}