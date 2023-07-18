#include "display.h"
#include <clocale>
#include <iostream>

int main()
{
    std::setlocale(LC_ALL, "");

    std::cout << L"\uE030" << std::endl;
    ctra::display d;
    d.update();
    return 0;
}