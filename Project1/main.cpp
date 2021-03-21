#include "SDL.h"
#include "Game.h"
#include <windows.h>

int main(int argc, char* argv[])
{
    Game game;
    OutputDebugStringA("Test message!!!!!!!!!!!!\n");
    game.init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
    while (game.running()) 
    {
        game.handleEvents();
        game.update();
        game.render();
    }
    return 0;
}