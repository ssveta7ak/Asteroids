#include "UIManager.h"

bool UIManager::init(SDL_Renderer* renderer)
{
    bool success = true;
    SDL_Color textColor = { 255, 0, 0 };
    if (!mGameOverText.createFromRenderedText("GAME OVER", textColor, 70, renderer))
    {
        printf("Failed to render text texture!\n");
        success = false;
    }
    textColor = { 255, 255, 255 };
    if (!mInstruction.createFromRenderedText("ESCAPE:  Exit Game             ENTER:  New Game", textColor, 25, renderer))
    {
        printf("Failed to render text texture!\n");
        success = false;
    }
    textColor = { 255, 255, 255 };
    if (!mInstruction2.createFromRenderedText("ESCAPE:  Exit Game             ENTER:  Continue", textColor, 25, renderer))
    {
        printf("Failed to render text texture!\n");
        success = false;
    }
    textColor = { 0, 255, 0 };
    if (!mWinText.createFromRenderedText("YOU WIN!", textColor, 70, renderer))
    {
        printf("Failed to render text texture!\n");
        success = false;
    }
    return success;
}

void UIManager::render(SDL_Renderer* renderer, Image* textImage, int x, int y)
{
    SDL_Rect dest_rect;
    dest_rect.w = textImage->width(); 
    dest_rect.h = textImage->height();
    dest_rect.x = x; 
    dest_rect.y = y; 

    textImage->render(renderer, dest_rect);
}