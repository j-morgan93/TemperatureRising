#include "controller.h"

void Controller::handleEvent( SDL_Event& e, Dot &dot )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: dot.mVelY -= dot.DOT_VEL; break;
            case SDLK_DOWN: dot.mVelY += dot.DOT_VEL; break;
            case SDLK_LEFT: dot.mVelX -= dot.DOT_VEL; break;
            case SDLK_RIGHT: dot.mVelX += dot.DOT_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: dot.mVelY += dot.DOT_VEL; break;
            case SDLK_DOWN: dot.mVelY -= dot.DOT_VEL; break;
            case SDLK_LEFT: dot.mVelX += dot.DOT_VEL; break;
            case SDLK_RIGHT: dot.mVelX -= dot.DOT_VEL; break;
        }
    }
}