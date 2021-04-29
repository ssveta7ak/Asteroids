#pragma once

#include "Image.h"

class UIManager
{
public:
    bool init(SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer, Image *text, int x, int y);

    Image *GameOverText() { return &mGameOverText; }
    Image *Instruction() { return &mInstruction; }
    Image *Instruction2() { return &mInstruction2; }
    Image *WinText() { return &mWinText; }

private:
    Image mGameOverText;
    Image mInstruction;
    Image mInstruction2;
    Image mWinText;
};
