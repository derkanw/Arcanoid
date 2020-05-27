#include "GameLoop.h"

int main()
{
    srand((unsigned)time(0));

    GameLoop game;
    game.Start();

    return 0;
}