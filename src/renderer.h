#ifndef RENDERER_H
#define RENDERER_H

//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include "dot.h"
#include "ltexture.h"
#include "ltimer.h"

//decided to forward declare here, oops!
class LTexture;
class Dot;

class Renderer
{

public:
    //Starts up SDL and creates window
    bool init();

    //Loads media
    bool loadMedia(std::string path, LTexture &gDotTexture);

    //Frees media and shuts down SDL
    void close(LTexture &gDotTexture);

    //Updates the window title with vehicle temp and score
    //void UpdateTitle(int &a, int &t);

    void Render(Dot const dot);

    const int getScreenWidth() {return SCREEN_WIDTH;}
    const int getScreenHeight() {return SCREEN_HEIGHT;}

    //The window renderer
    SDL_Renderer *gRenderer = NULL;

    //The window we'll be rendering to
    SDL_Window *gWindow = NULL;

    //Screen dimension constnats
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    //Key Press surface constants
    enum KeyPressSurfaces
    {
        KEY_PRESS_SURFACE_DEFAULT,
        KEY_PRESS_SURFACE_UP,
        KEY_PRESS_SURFACE_DOWN,
        KEY_PRESS_SURFACE_LEFT,
        KEY_PRESS_SURFACE_RIGHT,
        KEY_PRESS_SURFACE_TOTAL
    };

    //Collision checker function --this should check one object against a vector of SDL_Rect...
    bool CheckCollision(Dot &a, Dot &b);


private:
    

};

#endif