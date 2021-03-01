#ifndef CONTROLLER_H
#define CONTROLLER_H

//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "dot.h"
#include "ltexture.h"
#include "ltimer.h"

class Controller
{
    public:

    void handleEvent( SDL_Event& e, Dot &dot);

    private:
};

#endif