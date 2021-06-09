#pragma once

#include "Image.h"
#include <memory>

class UIManager
{
public:
    bool init(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer, Image* text, int x, int y);

    Image* GameOverText() { return mGameOverText.get(); }
    Image* Instruction() { return mInstruction.get(); }
    Image* Instruction2() { return mInstruction2.get(); }
    Image* WinText() { return mWinText.get(); }

private:
    std::unique_ptr<Image> mGameOverText;
    std::unique_ptr<Image> mInstruction;
    std::unique_ptr<Image> mInstruction2;
    std::unique_ptr<Image> mWinText;
};
