#ifndef RENDERER_H
#define RENDERER_H

//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
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
    bool loadMedia(LTexture &gDotTexture);

    //Frees media and shuts down SDL
    void close(LTexture &gDotTexture);

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

private:
    

};

#endif