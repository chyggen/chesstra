#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>
#include <utility>
#include <string>

namespace ctra
{
    class display
    {
    public:

        display();

        std::string readUserInput();

        void writeGameStatus(std::string str);
        void writeUserOutput(std::string str);
        void updateBoard();

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
