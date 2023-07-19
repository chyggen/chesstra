#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>
#include <utility>

namespace ctra
{
    class display
    {
    public:

        display();

        void update();

        ~display();

    private:

        static constexpr int COMMAND_WIN_Y = 6;
        static constexpr int COMMAND_WIN_X = 20;

        WINDOW* m_sqaures[8][8];
        WINDOW* m_commandWin;
    };
}
