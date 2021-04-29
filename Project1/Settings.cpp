#include "Settings.h"
#include "nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

void Settings::init(const char *path)
{
    // load settings for window resolution
    std::ifstream ifs(path);
    json jf = json::parse(ifs);
    mWidth = jf["width"];
    mHeight = jf["height"];
    mFullscreen = jf["fullscreen"];
}