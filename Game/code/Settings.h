#pragma once

class Settings
{
public:
    void init(const char *path);
    int width() const { return mWidth; }
    int height() const { return mHeight; }
    bool fullscreen() const { return mFullscreen; }

private:
    int mWidth;
    int mHeight;
    bool mFullscreen;
};
