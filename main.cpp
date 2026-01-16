#include <ctime>
#include <cstdlib>
#include <windows.h> // For Windows UTF-8 console
#include "Game.cpp"

int main()
{
    // Set UTF-8 for Windows console
    SetConsoleOutputCP(CP_UTF8);

    srand(time(0));
    Game g;
    g.start();
    return 0;
}
