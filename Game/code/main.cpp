#include "Game.h"

int main(int argc, char* argv[])
{
    Game game;
    game.init("Game");
    while (game.running())
    {
        game.handleEvents();
        game.update();
        game.render();
    }
    return 0;
}
