#include "Game.h"
#include "nlohmann/json.hpp"
#include <fstream> 

using json = nlohmann::json;

int main(int argc, char* argv[])
{
    std::ifstream ifs("assets/settings.json");
    json jf = json::parse(ifs);
    int width = jf["width"];
    int height = jf["height"];
    bool fullscreen = jf["fullscreen"];

    Game game;
    game.init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, fullscreen);
    while (game.running()) 
    {
        game.handleEvents();
        game.update();
        game.render();
    }
    return 0;
}
